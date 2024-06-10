from Crypto.Cipher import AES
from Crypto.Util.Padding import pad
import hashlib
import sympy as sp
import random

FLAG = b'REDACTED'

key = random.getrandbits(7)

x = sp.symbols('x')

f = "REDACTED"
f_prime = "REDACTED"
f_second_prime = "REDACTED"

assert(2*f_second_prime - 6*f_prime + 3*f == 0)
assert(f.subs(x, 0) | f_prime.subs(x, 0) == 14)

def encrypt(message, key):
    global f
    global x
    point = f.subs(x, key).evalf(100)
    point_hash = hashlib.sha256(str(point).encode()).digest()[:16]
    cipher = AES.new(point_hash, AES.MODE_CBC)
    iv = cipher.iv
    ciphertext = cipher.encrypt(pad(message, AES.block_size))
    return iv.hex() + ciphertext.hex()

encrypted = encrypt(FLAG, key)

print(f"Key: {key}")
print(f"Encrypted: {encrypted}")
