
import math

log123 = math.log10(123)
log124 = math.log10(124)
log2   = math.log10(2)
logcheck = log124-log123
#print(logcheck)


def isa123(q, debug):
    Nflt = (q + log123)/log2
    N = int(Nflt)
    #N = int(math.floor(Nflt))
    test = N * log2 - log123 - q
    if test >= 0 and test <= logcheck: 
        if debug: print("int ", q, N, test)
        #print("Floor: ", N,flush=True)
        return N
    N = int(Nflt) + 1
    test = N * log2 - log123 - q
    if test >= 0 and test <= logcheck:
        if 0 and debug: print("+1", q, N, test)
        return N
            
    N = int(Nflt) - 1   
    test = N * log2 - log123 - q
    if test >= 0 and test <= logcheck:
        if debug: print("-1", q, N, test)
        return N

    return 0

#isa123(112)
#exit(1)

count = 0
q = 10
n = 0
debug = True
while count < 678910:
#while count < 45:
    n = isa123(q, debug)
    if n > 0:
        #print("*****  ",n, q)
        count += 1
    q += 1
print(n)

# 193060512 is not correct
#  193060223 - value obtained when running for 678909
# int  19962927 66315415 0.0
