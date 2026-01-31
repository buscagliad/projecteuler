# Re-run after execution environment reset
import math

def legendre(n, p):
    count = 0
    while n > 0:
        n //= p
        count += n
    return count

n = 100

count = 0
total = 0

for a in range(n + 1):
    for b in range(n + 1 - a):
        c = n - a - b
        v2 = legendre(n, 2) - (legendre(a, 2) + legendre(b, 2) + legendre(c, 2))
        v5 = legendre(n, 5) - (legendre(a, 5) + legendre(b, 5) + legendre(c, 5))
        total += 1
        if v2 >= 2 and v5 >= 2:
        #if v5 >= 2:
            print(a, b, c, a+b+c, v5)
            count += 1

print(count, total)
