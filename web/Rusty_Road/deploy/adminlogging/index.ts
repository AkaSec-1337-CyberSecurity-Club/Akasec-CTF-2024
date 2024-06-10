import { $ } from "bun";
import figlet from "figlet";

const server = Bun.serve({
  async fetch(req) {
    const url = new URL(req.url);

    const API_KEY = process.env.API_KEY;

    const key = req.headers.get("Authorization");

    if (key !== API_KEY) {
      return new Response(figlet.textSync("401!"), { status: 401 });
    }

    if (req.method !== "POST") {
      return new Response(figlet.textSync("405!"), { status: 405 });
    }
    if (req.headers.get("Content-Type") !== "application/json") {
      return new Response(figlet.textSync("415!"), { status: 415 });
    }

    const body = await req.json();

    if (!body.message) {
      return new Response(figlet.textSync("400!"), { status: 400 });
    }

    if (url.pathname === "/log") {
      await $`logger ${body.message}`;
      return new Response("Logged!", { status: 200 });
    }

    return new Response(figlet.textSync("404!"), { status: 404 });
  },
});

console.log(`Listening on http://localhost:${server.port} ...`);
