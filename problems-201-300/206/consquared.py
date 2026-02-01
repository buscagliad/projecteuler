import math

def issol(n):
    for k in [0,9,8,7,6,5,4,3,2,1]:
        if n % 10 != k: return False
        n //= 100
    return True


def solve():
    for j in range(1010101,38902662):
        k = 1000000000 + j * 10
        if (issol(k*k)): 
            print("Solution: ", k, k*k)

sm = 1020304050607080900
lg = 1929394959697989990

smrt = math.sqrt(sm)
smsq = int(smrt*smrt)

lgrt = math.sqrt(lg)
lgsq = int(lgrt*lgrt)

print(sm, smrt, smsq)
print(lg, lgrt, lgsq)

solve()
