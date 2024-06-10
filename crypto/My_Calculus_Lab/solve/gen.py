from Crypto.Cipher import AES
from Crypto.Util.Padding import pad, unpad
import hashlib
import random
from sympy import symbols, exp, sqrt, Eq, solve

FLAG = b'AKASEC{d1d_y0u_3nj0y_c41cu1u5_101?}'

key = random.getrandbits(7)

x, C1, C2 = symbols('x C1 C2')

f = C1 * exp(((3+sqrt(3))/2)*x) + C2 * exp(((3-sqrt(3))/2)*x)
f_prime = f.diff(x)

f_0 = 4
f_prime_0 = 14

eq1 = Eq(f.subs(x, 0), f_0)
eq2 = Eq(f_prime.subs(x, 0), f_prime_0)

solution = solve((eq1, eq2), (C1, C2))

C1 = solution[C1]
C2 = solution[C2]

f = f.subs({'C1': C1, 'C2': C2})

def encrypt(message, key):
    global f
    global x
    point = f.subs(x, key).evalf(100)
    point_hash = hashlib.sha256(str(point).encode()).digest()[:16]
    cipher = AES.new(point_hash, AES.MODE_CBC)
    iv = cipher.iv
    ciphertext = cipher.encrypt(pad(message, AES.block_size))
    return iv.hex() + ciphertext.hex()

def decrypt(ciphertext, key):
    global f
    global x
    point = f.subs(x, key).evalf(100)
    point_hash = hashlib.sha256(str(point).encode()).digest()[:16]
    iv = bytes.fromhex(ciphertext[:32])
    ciphertext = bytes.fromhex(ciphertext[32:])
    cipher = AES.new(point_hash, AES.MODE_CBC, iv=iv)
    plaintext = unpad(cipher.decrypt(ciphertext), AES.block_size)
    return plaintext.decode()

ciphertext = encrypt(FLAG, key)
message = decrypt(ciphertext, key)

print(f"Key: {key}")
print(f"Encrypted: {ciphertext}")
print(f"Decrypted: {message}")
