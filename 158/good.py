from itertools import permutations
from math import comb

def cntML(M, L):
    return comb(26,L) * comb(L-1, M-1)

for L in range(3, 7):
    for M in range(2, L+1):
        print("L = ", L, "M = ", M, "  count: ", cntML(M, L))

exit(1)

def good(l):
    a = l[0]
    n = 0
    for b in l[1:]:
        if b > a: n += 1
        a = b
    return n

T=[n for n in range(1,27)]

def G(L):
    k = 0
    for s in permutations(T, L):
        if good(s) ==  1: k += 1
        #print(s, good(s))
    return k
    
print(5, G(7))
