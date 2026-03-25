import sympy


MAXN =    10000
MAXN = 50000000
pcount = 0
for n in range(2, MAXN + 1):
    v = 2 * n * n - 1
    tf = sympy.isprime(v)
    #print(v, sympy.isprime(v), sympy.ntheory.factorint(v))
    if tf: pcount += 1

print(pcount)
