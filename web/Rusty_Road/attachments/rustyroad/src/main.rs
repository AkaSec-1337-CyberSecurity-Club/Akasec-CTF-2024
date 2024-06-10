#[macro_use] extern crate rocket;

use rocket::form::Form;
use rocket::http::ContentType;
use rocket::response::Redirect;
use rocket::serde::{json::Json};
use serde::{Serialize, Deserialize};
use jsonwebtoken::{encode, Header, EncodingKey, decode, Validation, Algorithm, DecodingKey, TokenData};
use jsonwebtoken::errors::Result;
use rand::Rng;
use rand::distributions::Alphanumeric;
use lazy_static::lazy_static;
use rocket::http::Cookie;
use rocket::http::CookieJar;
use std::sync::Mutex;
use bcrypt::{hash, verify, DEFAULT_COST};
use rocket_dyn_templates::{Template, context};
use serde_json::json;
use serde_json::Value;
use reqwest::header;
use std::time::Duration;

lazy_static! {
    static ref SECRET: String = {
        let secret: String = rand::thread_rng()
            .sample_iter(&Alphanumeric)
            .take(30)
            .map(char::from)
            .collect();
        secret
    };

    static ref PASSWORD: String = "REDACTED".to_string();

    static ref API_KEY: String = std::env::var("API_KEY").expect("API_KEY must be set");

    static ref USERS: Mutex<Vec<User>> = Mutex::new(vec![
        User {
            username: "admin".to_string(),
            password: hash_password(&PASSWORD),
        }
    ]);
}

#[derive(Debug, Deserialize, Serialize)]
struct Claims {
    username: String,
    user_type: String,
    exp: usize,
}

#[derive(FromForm)]
struct RegisterForm {
    username: String,
    password: String,
}

#[derive(Debug)]
struct User {
    username: String,
    password: String,
}

fn add_user(username: &str, password: &str) {
    // println!("{:?}", USERS.lock().unwrap());
    USERS.lock().unwrap().push(User {
        username: username.to_string(),
        password: password.to_string(),
    });
    // println!("{:?}", USERS.lock().unwrap());
}

fn validate_token(token: &str) -> Result<TokenData<Claims>> {
    let decoding_key = DecodingKey::from_secret(SECRET.as_ref());
    decode::<Claims>(token, &decoding_key, &Validation::new(Algorithm::HS256))
}

fn subs(input: String) -> String {
    input.replace("PASSWORD", &PASSWORD)
}

fn hash_password(password: &str) -> String {
    hash(password, DEFAULT_COST).unwrap()
}

#[get("/logout")]
fn logout(cookies: &CookieJar<'_>) -> Redirect {
    cookies.remove("token");
    Redirect::to(uri!(home))
}

#[get("/register")]
fn register_form() -> (ContentType, Template) {
    (ContentType::HTML, Template::render("register", context! {}))
}

#[post("/register", data = "<form>")]
fn register(form: Form<RegisterForm>, cookies: &CookieJar<'_>) -> Redirect {

    let username = subs(form.username.clone());
    if username.contains("admin") || username.contains(PASSWORD.as_str()) {
        return Redirect::to("/register");
    }

    let password = subs(form.password.clone());
    let password = hash_password(&password);

    //println!("{:?}, {:?}", username, password);
    add_user(&username, &password);

    let claims = Claims {
        username: form.username.clone(),
        user_type: "user".to_string(),
        exp: 10000000000,
    };
    let token = encode(&Header::default(), &claims, &EncodingKey::from_secret(SECRET.as_ref())).unwrap();

    cookies.add(Cookie::new("token", token.clone()));

    Redirect::to("/")
}

#[get("/login")]
fn login_form() -> (ContentType, Template) {
    (ContentType::HTML, Template::render("login", context! {}))
}

#[post("/login", data = "<form>")]
fn login(form: Form<RegisterForm>, cookies: &CookieJar<'_>) -> Redirect {
    let username = form.username.clone();
    let password = form.password.clone();

    let users_lock = USERS.lock().unwrap();

    let user = users_lock.iter().find(|user| user.username == username);
    if let Some(user) = user {
        //println!("{:?}", username);
        //println!("{:?}", password);
        //println!("{:?}", users_lock);
        if verify(&password, &user.password).unwrap() {
            let user_type = if username == "admin" {
                "admin".to_string()
            } else {
                "user".to_string()
            };
            let claims = Claims {
                username: form.username.clone(),
                user_type,
                exp: 10000000000,
            };
            let token = encode(&Header::default(), &claims, &EncodingKey::from_secret(SECRET.as_ref())).unwrap();

            cookies.add(Cookie::new("token", token.clone()));

            return Redirect::to("/");
        }
    }

    Redirect::to("/login")
}

#[get("/")]
fn home(cookies: &CookieJar<'_>) -> (ContentType, Template) {
    let token = cookies.get("token").map(|cookie| cookie.value()).unwrap_or("");
    match validate_token(token) {
        Ok(data) => {
            if data.claims.user_type == "user" {
                (ContentType::HTML, Template::render("main", context! { main: format!("Hello {}", data.claims.username)}))
            }
            else if data.claims.user_type == "admin" {
                (ContentType::HTML, Template::render("main", context! { main: "Hello Admin".to_string()}))
            } else {
                (ContentType::HTML, Template::render("main", context! { main: "Access Denied".to_string()}))
            }
        },
        Err(_) => (ContentType::HTML, Template::render("main", context! { main: "Unauthorized".to_string()})),
    }
}

#[get("/admin")]
fn admin(cookies: &CookieJar<'_>) -> (ContentType, Template) {
    let token = cookies.get("token").map(|cookie| cookie.value()).unwrap_or("");
    match validate_token(token) {
        Ok(data) => {
            if data.claims.user_type == "admin" {
                (ContentType::HTML, Template::render("main", context! { main: "Welcome Admin".to_string()}))
            } else {
                (ContentType::HTML, Template::render("main", context! { main: "Access Denied".to_string()}))
            }
        },
        Err(_) => (ContentType::HTML, Template::render("main", context! { main: "Unauthorized".to_string()})),
    }
}

#[post("/log", format = "json", data = "<log_data>")]
async fn admin_log(cookies: &CookieJar<'_>, log_data: Json<Value>) -> Json<String> {
    let token = cookies.get("token").map(|cookie| cookie.value()).unwrap_or("");
    match validate_token(token) {
        Ok(data) => {
            if data.claims.user_type == "admin" {
                let client = reqwest::Client::new();
                let res = client.post("http://adminlogging:3000/log")
                    .header(header::AUTHORIZATION, API_KEY.as_str())
                    .json(&log_data.into_inner())
                    .send()
                    .await
                    .expect("Failed to send request");

                if res.status().is_success() {
                    Json("{ \"status\": \"Logged successfully\" }".to_string())
                } else {
                    Json("{ \"status\": \"Failed to log\" }".to_string())
                }
            } else {
                Json("{ \"status\": \"Access Denied\" }".to_string())
            }
        },
        Err(_) => Json("{ \"status\": \"Unauthorized\" }".to_string()),
    }
}

#[launch]
async fn rocket() -> _ {
    tokio::spawn(
        async move {
            loop {
                let client = reqwest::Client::new();
                let res = client.post("http://adminlogging:3000/log")
                    .header(header::AUTHORIZATION, API_KEY.as_str())
                    .json(&json!({ "message": "Backend Alive" }))
                    .send()
                    .await
                    .expect("Failed to send request");

                if res.status().is_success() {
                    println!("Adminlogging service is healthy");
                } else {
                    println!("Adminlogging service failed to log");
                }

                tokio::time::sleep(Duration::from_secs(60)).await;
            }
        }
    );

    rocket::build()
        .mount("/", routes![register_form, register, home, admin, admin_log, login_form, login, logout])
        .attach(Template::fairing())
}
