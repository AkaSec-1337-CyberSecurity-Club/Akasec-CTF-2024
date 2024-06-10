from decimal import *

from Crypto.Util.number import bytes_to_long, long_to_bytes

getcontext().prec = 200
provided = Decimal('1.0100160293633633097836165218520645928533165673701591638847239768412297771673628701675769728865523783884907827854645836850813325581348710325049612453127737826117688733914936444315081605041365932902096')


provided = provided * Decimal(5)

R_1 = 100
R_2 = 200

provided = provided / Decimal(1 + (R_2 / R_1))

V_REF = Decimal(3.3)

#V_OUT = (V_REF*(FLAG_NUM/Decimal(2**463)))

i = 0
while True:
    res = (provided / V_REF) * Decimal(2**i)
    res = long_to_bytes(int(res))
    if b'AKASEC{' in res and b'}' in res:
        print (res)
        break
    i+=1
