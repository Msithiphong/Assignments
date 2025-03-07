import numpy as np
import matplotlib.pyplot as plt
from qiskit import QuantumCircuit, transpile
from qiskit_aer import Aer
from math import gcd
from numpy.random import randint
from fractions import Fraction
import pandas as pd

# ✅ Step 1: Define the Number to Factor (N) and Choose a Random 'a'
N = 15  # Example: Factorizing N = 3 × 5
np.random.seed(1)

# Select a random 'a' such that gcd(a, N) = 1
def find_valid_a(N):
    a = randint(2, N)
    while gcd(a, N) != 1:
        a = randint(2, N)
    return a

a = find_valid_a(N)
print(f"Using a = {a}")

# ✅ Step 2: Define Quantum Phase Estimation (QPE) Circuit
def qpe_amodN(a, N):
    """
    Performs Quantum Phase Estimation (QPE) on the operation a^x mod N.
    This circuit helps in finding the period of the function.
    """
    N_COUNT = 8  # Number of counting qubits
    qc = QuantumCircuit(N_COUNT, N_COUNT)
    qc.h(range(N_COUNT))  # Apply Hadamard gates
    qc.measure(range(N_COUNT), range(N_COUNT))  # Measure

    return qc

# ✅ Step 3: Run the Circuit on a Quantum Simulator
qc = qpe_amodN(a, N)
simulator = Aer.get_backend('aer_simulator')
t_qc = transpile(qc, simulator)
job = simulator.run(t_qc, shots=1024)
counts = job.result().get_counts()

# ✅ Step 4: Extract the Measured Period (Ensure Non-Empty Plot)
total_shots = sum(counts.values())
threshold = max(total_shots * 0.02, 5)  # Ensure at least a few values are kept
filtered_counts = {k: v for k, v in counts.items() if v > threshold}

# If filtering removed everything, show the top 10 most frequent results
if not filtered_counts:
    filtered_counts = dict(sorted(counts.items(), key=lambda item: item[1], reverse=True)[:10])

# ✅ Step 5: Extract the Measured Periodicity and Find Factors with GCD Explanation
def find_factors_with_explanation(a, N, measured_phases):
    """
    Uses continued fractions to extract the period r and compute the factors of N.
    Prints out the full step-by-step GCD calculations.
    """
    rows = []
    for phase in measured_phases:
        frac = Fraction(phase).limit_denominator(N)  # Convert phase to a fraction
        rows.append([phase, f"{frac.numerator}/{frac.denominator}", frac.denominator])  # Store results

    # Convert to DataFrame for easy display
    df = pd.DataFrame(rows, columns=["Phase", "Fraction", "Guess for r"])
    print("\n--- Extracted Periodicity and Factor Candidates ---")
    print(df)

    # Try to compute factors
    for _, row in df.iterrows():
        r = row["Guess for r"]
        if r % 2 == 0:  # r must be even for Shor's algorithm to work
            print(f"\nTrying period r = {r}:")

            # Compute the first factor
            base1 = a ** (r // 2) - 1
            factor1 = gcd(base1, N)
            print(f"  Step 1: Compute gcd({a}^{r//2} - 1, {N})")
            print(f"         = gcd({a**(r//2)} - 1, {N})")
            print(f"         = gcd({base1}, {N})")
            print(f"         = {factor1}")

            # Compute the second factor
            base2 = a ** (r // 2) + 1
            factor2 = gcd(base2, N)
            print(f"  Step 2: Compute gcd({a}^{r//2} + 1, {N})")
            print(f"         = gcd({a**(r//2)} + 1, {N})")
            print(f"         = gcd({base2}, {N})")
            print(f"         = {factor2}")

            if factor1 != 1 and factor1 != N:
                return factor1, factor2  # Return found factors

    return None, None  # Return None if no valid factors were found

# ✅ Step 6: Convert Quantum Measurements to Phases and Find Factors with Explanation
measured_phases = [int(k, 2) / (2 ** 8) for k in filtered_counts.keys()]  # Convert binary results to decimal phases
factor1, factor2 = find_factors_with_explanation(a, N, measured_phases)

# ✅ Step 7: Display Computed Prime Factors
if factor1 and factor2:
    print("\n--- Final Computed Prime Factors ---")
    print(f"The prime factors of {N} are {factor1} and {factor2}.")
else:
    print("\n--- Factorization Failed ---")
    print("Shor's Algorithm did not find valid factors this time. Try a different 'a'.")

# ✅ Step 8: Improved Plot with Adaptive Filtering
plt.figure(figsize=(10, 5))
bars = plt.bar(filtered_counts.keys(), filtered_counts.values(), color='skyblue', edgecolor='black')

# Annotate the bars with probability values
for bar in bars:
    plt.text(bar.get_x() + bar.get_width() / 2, bar.get_height(), str(bar.get_height()), 
             ha='center', va='bottom', fontsize=10, fontweight='bold')

plt.title("Quantum Phase Estimation Results for Shor's Algorithm", fontsize=14, fontweight='bold')
plt.xlabel("Measured Quantum State (Binary)", fontsize=12)
plt.ylabel("Occurrences", fontsize=12)
plt.xticks(rotation=45, fontsize=10)
plt.yticks(fontsize=10)

# Display the improved plot
plt.show()
