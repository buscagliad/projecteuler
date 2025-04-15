import math

def gcd(a, b):
    while b:
        a, b = b, a % b
    return a

def generate_primitive_pythagorean_triples(N):
    triples = []
    m = 2
    while True:
        for n in range(1, m):
            if (m - n) % 2 == 1 and gcd(m, n) == 1:  # m-n odd and coprime
                a = m*m - n*n
                b = 2*m*n
                c = m*m + n*n
                if c > N:
                    return triples
                triples.append(tuple(sorted((a, b, c))))
        m += 1

# Example usage:
#N = int(input("Enter the maximum value of c: "))
N = 10000
triples = generate_primitive_pythagorean_triples(N)
for triple in triples:
    print(triple)
