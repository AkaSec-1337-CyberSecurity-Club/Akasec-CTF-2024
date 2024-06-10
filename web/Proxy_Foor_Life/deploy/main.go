package main

import (
    "os"
    "io"
    "fmt"
    "net/http"
    _ "net/http/pprof"
    "html/template"
    "github.com/doyensec/safeurl"
)

var templates = template.Must(template.ParseGlob("templates/*.html"))

func indexHandler(w http.ResponseWriter, r *http.Request) {
    if r.Method == http.MethodPost {
        config := safeurl.GetConfigBuilder().
            Build()

        client := safeurl.Client(config)

        url := r.FormValue("url")

        _, err := client.Get(url)
        if err != nil {
            renderTemplate(w, "index", map[string]string{"error": "The URL you entered is dangerous and not allowed."})
            fmt.Println(err)
            return
        }

        resp, err := http.Get(url)
        if err != nil {
            fmt.Println(err)
            return
        }
        defer resp.Body.Close()

        body, _ := io.ReadAll(resp.Body)
        renderTemplate(w, "index", map[string]interface{}{"result": template.HTML(body)})
        return
    }

    renderTemplate(w, "index", nil)
}



func renderTemplate(w http.ResponseWriter, tmpl string, data interface{}) {
    err := templates.ExecuteTemplate(w, tmpl+".html", data)
    if err != nil {
        http.Error(w, err.Error(), http.StatusInternalServerError)
    }
}

func flagHandler(w http.ResponseWriter, r *http.Request) {
    args := os.Args
    flag := args[1]
    if 1 == 0 { // can you beat this :) !?
        fmt.Fprint(w, flag)
    } else {
        fmt.Fprint(w, "Nahhhhhhh")
    }
}

func main() {
    http.HandleFunc("/", indexHandler)
    http.HandleFunc("/flag", flagHandler)
    http.ListenAndServe(":1337", nil)
}
