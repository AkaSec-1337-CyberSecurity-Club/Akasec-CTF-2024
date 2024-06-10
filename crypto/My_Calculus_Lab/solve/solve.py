from Crypto.Cipher import AES
from Crypto.Util.Padding import unpad
import hashlib
from sympy import symbols, Eq, solve, exp, sqrt
import random

key = 60
encrypted = "805534c14e694348a67da0d75165623cf603c2a98405b34fe3ba8752ce24f5040c39873ec2150a61591b233490449b8b7bedaf83aa9d4b57d6469cd3f78fdf55"

x, C1, C2 = symbols('x C1 C2')

f = C1 * exp(((3+sqrt(3))/2)*x) + C2 * exp(((3-sqrt(3))/2)*x)
f_prime = f.diff(x)

original_f = f
original_f_prime = f_prime

original_C1 = C1
original_C2 = C2

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

for f_0 in range(15):
    for f_prime_0 in range(15):

        f = original_f
        f_prime = original_f_prime

        C1 = original_C1
        C2 = original_C2

        if f_0 | f_prime_0 == 14:
            eq1 = Eq(f.subs(x, 0), f_0)
            eq2 = Eq(f_prime.subs(x, 0), f_prime_0)

            solution = solve((eq1, eq2), (C1, C2))

            if solution:
                try:
                    C1 = solution[C1]
                    C2 = solution[C2]

                    f = f.subs({'C1': C1, 'C2': C2})
                    f_prime = f_prime.subs({'C1': C1, 'C2': C2})

                    plaintext = decrypt(encrypted, key)

                    if plaintext.startswith("AKASEC{"):
                        print("Flag:", plaintext)
                        break
                except ValueError:
                    pass