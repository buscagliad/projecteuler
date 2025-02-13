import math
import primefac
import sys
import numpy as np
import time

debug = False

def complexGaussSum( N ):
    global debug
    debug = False
    cgcnt = 0
    rootN = int(math.sqrt(N) + 0.000001) 
    A = rootN
    cgsum = (N - A) * ( N + A + 3) // 2
    #rootN = N // 2
    if debug: print("******* Gauss Sum: ", N, rootN)
    print("a,b,gcd,s,nn")
    for a in range(1, rootN+1):
        a2 = a * a
        for b in range(1, a+1):  ## a >= b
            s = a2 + b * b
            gcd = np.gcd(a, b)
            nn = s // gcd
            if debug: print("a, b, s, nn:", a, b, s, nn)
            if nn > N: continue
            print(a, ",", b, ",", gcd, ",", gcd, ",", nn, sep="")
            if a == b:
                cgcnt += 2
                Nsum = 2 * a * (N // nn)
                cgsum += Nsum
                if debug: print("a == b", " a=", a, " b=", b, " nn=", nn, " N=",  N, 
                    " s=", s, " Nsum: ", Nsum,   " cgsum=", cgsum)
            else: 
                cgcnt += 4
                Nsum = 2 * (a + b) * (N // nn)
                cgsum += Nsum
                if debug: print("a != b", " a=", a, " b=", b, " nn=", nn, " N=",  N, 
                    " s=", s, " Nsum: ", Nsum,   " cgsum=", cgsum)
    print ("Sum1:: Count gauss circle integer points at ", N, " is ", cgsum)
    debug = False
    return cgsum


def sumfac(k):
    factors = list( primefac.primefac(k) )
    unique = set(factors)

    ps = 1
    for u in unique:
        ai = factors.count(u)+1
        ps *= (u ** ai - 1) // (u - 1)
    return ps

def sumsumfacold(N):
    fs = 0
    for k in range(1, N+1):
        sf = sumfac(k)
        fs += sf
    return fs
    
def sumsumfacnew(N):
    fs = 0
    for d in range(1, N+1):
        sf = d * (N//d)
        fs += sf
    return fs
            
def gint(n):
    start = time.process_time()
    # your code here    
    debug = False
    gc = 0
    gc = complexGaussSum(n)
    print("complexGaussSum: ", time.process_time() - start)
    # start = time.process_time()
    # gs = sumsumfacold(n)
    
    # print("sumFactors OLD: ", gs, " time: ", time.process_time() - start)
    start = time.process_time()
    gs = sumsumfacnew(n)
    print("sumFactors NEW: ", gs, " time: ", time.process_time() - start)
    print("Gauss sum: ", gs, "  Sum factors: ", gc, "  Total: ", gs+gc)
    return gs + gc


## NOTE: gint(10**5) should equal 17924657155
print(gint(100000))
#print(gint(5, False))
exit(1)
#print(n, complexGaussSum(n), countLattice(n)-1)
#exit(1)
# Sum1:: Count gauss circle integer points at  10000  is  95975212
# complexGaussSum:  31.597766464000003
# sumFactors:  0.027652417999998846
# 82256014 95975212 178231226
# 178231226
##                                 8293695535
## NOTE: gint(10**5) should equal 17924657155
