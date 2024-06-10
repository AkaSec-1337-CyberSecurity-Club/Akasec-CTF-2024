from flask import Flask, redirect

app = Flask(__name__)

first = True

@app.route("/")
def hello_world():
    global first
    if first:
        first = False
        return redirect("http://example.com/")
    return redirect("http://localhost:1337/debug/pprof/cmdline")
