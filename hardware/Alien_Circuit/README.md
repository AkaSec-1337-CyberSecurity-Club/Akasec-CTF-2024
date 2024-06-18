# Alien Circuit

## Description

![image](https://github.com/AkaSec-1337-CyberSecurity-Club/Akasec-CTF-2024/assets/73129654/d59f2936-8b79-4092-9c62-8707471a57ae)

**schematic.txt**

![image](https://github.com/AkaSec-1337-CyberSecurity-Club/Akasec-CTF-2024/assets/73129654/4c0414fa-4ccf-4672-ba0f-69d4b2026c11)

Plus these parameters:
```
Important Information:

bn (logic high = 3.3V)

R1 = 100Ω
R2 = 200Ω

Vout = 1.0100160293633633097836165218520645928533165673701591638847239768412297771673628701675769728865523783884907827854645836850813325581348710325049612453127737826117688733914936444315081605041365932902096V
```

The circuit combines three important parts of electronic components, a R-2R DAC (Digital to Analog Conveter), a non-inverting amplifier, and a network of resistors.

If you know how to reverse the effect of each component of the circuit youll know how get back to the flag from the given `Vout`.

## Resistor Tree

As intimidating as it seems this can be broken down to just to two resistors:

![image](https://github.com/AkaSec-1337-CyberSecurity-Club/Akasec-CTF-2024/assets/73129654/01c8ccf8-6f00-429f-abc8-a4d24deabce0)

with Z1 = 4 ohm and Z2 = 1 ohm.

then you can apply the voltage divider rule to get the input voltage of the original resistor tree:

![image](https://github.com/AkaSec-1337-CyberSecurity-Club/Akasec-CTF-2024/assets/73129654/ae9659f4-fcbe-4dc1-a251-dc956112600b)

## The non-inverting amplifier

The formula of this non inverting op-amp is straight forward:

$$
V_{in} = \frac{V_{out}}{1 + \left(\frac{R_2}{R_1}\right)}
$$

## The R-2R DAC

This is also straigh forward, you can reference any decent R-2R DAC explanation online to get the general formula to use to solve this problem:

![image](https://github.com/AkaSec-1337-CyberSecurity-Club/Akasec-CTF-2024/assets/73129654/37bac0b2-b857-4468-9bae-394bb62cfad1)

The equation goes like this:

![image](https://github.com/AkaSec-1337-CyberSecurity-Club/Akasec-CTF-2024/assets/73129654/a44eb5fe-5a2e-4c66-b86d-53d471f9a42f)

So that implies that the $Value$ equals:

$$
Value = \frac{V_{out} \times 2^N}{V_{ref}}
$$

## The Implementation

So by combining these three parts, we can get back to our flag, here is the python implementation (we used `decimal` for precise arithmetic calculation):

```py
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
```

## More Interesting Write-ups:
These writeups: [ihuomtia](https://ihuomtia.onrender.com/akasec-hw-alien-circuit), [jbryant0653](https://jbryant0653.github.io/CTF%20Writeups/Hardware/%E2%80%9CAlien%20Circuit%E2%80%9D%20akaCTF2024%20Hardware.html) are more comprehesive than mine (the author 😊), I recommend you check them out.
