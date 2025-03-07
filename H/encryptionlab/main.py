import math
from sympy import mod_inverse

N = 55
e = 11

C = 4

def factorize_n(n):
    for i in range(2, int(math.sqrt(n)) + 1):
        if n % i == 0:
            return i, n
    return None, None

p, q = factorize_n(N) 

if p and q:
    print(f"Factors of N found: p = {p}, q = {q}")
    phi_N = (p - 1) * (q - 1)
    print(f"Computed phi(N) is  {phi_N}")
    d = mod_inverse(e, phi_N)
    print(f"Computed Private Key is {d}")
    M = pow(C, d, N)
    print(f"Decrypted Message is {M}")

else:
    print("Failed to find the proper result")