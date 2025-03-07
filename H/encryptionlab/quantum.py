from qiskit import QuantumCircuit, transpile
from qiskit_aer import Aer
from math import gcd
import numpy as np
import matplotlib.pyplot as plt

from numpy.random import randint
from fractions import Fraction
from qiskit.visualization import plot_histogram

N = 15
np.random.seed(1)
a = randint(2, N)

while gcd(a, N) != 1:
    a = randint
    
print(f"Using a= {a}")

def c_amodN(a, power, N):
    U = QuantumCircuit(4)
    for _ in range(power):
        if a in [2, 13]:
            U.swap(2,3)
            U.swap(1,2)
            U.swap(0,1)
        if a in [7, 8]:
            U.swap(0,1)    
            U.swap(1,2)
            U.swap(2,3)

        if a in [4, 11]:
            U.swap(1,3)
            U.swap(0,2)
        if a in [7, 11, 13]:
            for q in range(4):
                U.x(q)
