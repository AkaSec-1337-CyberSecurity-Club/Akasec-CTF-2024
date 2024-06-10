
from Crypto.Util.number import bytes_to_long, long_to_bytes
from decimal import *

getcontext().prec = 200

flag = b'AKASEC{r_2r_d4c_plu5_0p_4mp_plu5_r351570r_7r33_3qu4l5_fun}'

FLAG_NUM = Decimal(bytes_to_long(flag))


"""
Vout/Vin=1+(R2/R1)

Vout = (1+(R2/R1)) * Vin
"""

V_REF = Decimal(3.3)
V_OUT = (V_REF*(FLAG_NUM/Decimal(2**len(bin(int(FLAG_NUM))[2:]))))

print(len(bin(int(FLAG_NUM))[2:]))


R_1 = 100
R_2 = 200

V_OUT = V_OUT * Decimal(1 + (R_2 / R_1))

V_OUT = V_OUT / Decimal(5)

print(V_OUT)