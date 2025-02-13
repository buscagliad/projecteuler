import math
import primefac
import sys
import numpy as np

debug = False
Ca = [0]*100001
Cb = [0]*100001
Cn = [0]*100001

def complexGaussSum( N ):
    global Ca, Cb, Cn
    cgsum = 0
    cgcnt = 0
    rootN = int(math.sqrt(N) + 0.000001) 
    rootN = N
    if debug: print("******* Gauss Sum: ", N, rootN)
    for a in range(1, rootN+1):
        a2 = a * a
        for b in range(1, a+1):  ## a >= b
            s = a2 + b * b
            gcd = np.gcd(a, b)
            nn = s // gcd
            if nn > N: continue
            Cn[nn] += 1
            if debug: print("a, b, s, nn:", a, b, s, nn)
            #print(a, ",", b, ",", gcd, ",", gcd, ",", nn, sep="")
            if a == b:
                cgcnt += 2
                Nsum = 2 * a * (N // nn)
                cgsum += Nsum
                Ca[a] += 2
                Cb[b] += 2
                if debug: print("a == b", " a=", a, " b=", b, " nn=", nn, " N=",  N, 
                    " s=", s, " Nsum: ", Nsum,   " cgsum=", cgsum)
            else: 
                Ca[a] += 2
                Cb[b] += 2
                cgcnt += 4
                Nsum = 2 * (a + b) * (N // nn)
                cgsum += Nsum
                if debug: print("a != b", " a=", a, " b=", b, " nn=", nn, " N=",  N, 
                    " s=", s, " Nsum: ", Nsum,   " cgsum=", cgsum)
    print ("Sum1:: Count gauss circle integer points at ", N, " is ", cgsum)
    return cgsum


def sumfac(k):
    factors = list( primefac.primefac(k) )
    unique = set(factors)

    ps = 1
    for u in unique:
        ai = factors.count(u)+1
        ps *= (u ** ai - 1) // (u - 1)
    return ps

def sumsumfacnew(N):
    fs = 0
    for d in range(1, N+1):
        sf = d * (N//d)
        fs += sf
    return fs
            

def gint(n):
    gc = complexGaussSum(n)
    gs = sumsumfacnew(n)
    # for k in range(1, n+1):
        # sf =  sumfac(k)
        # if k % 1000000 == 0: print(k, sf, gs, flush=True)
        # gs += sf
    print(gs, gc, gs+gc)
    return gs + gc
n=1000
# print(sumfac(1225))
# print(complexGaussSum(10**5))
# print(complexGaussSum2(10**5))
# print(gint(10**5,False))
# print(gint(10**5,True))
## Sum Factors: 9699916320
## Gauss Integers: 8224740835
## NOTE: gint(10**5) should equal 17924657155
N = 1000
print(gint(N))
print("a,Ca,b,Cb,n,Cn")
for i in range(1,N+1):
    print(i, ",", Ca[i], ",", i, ",", Cb[i], ",", i, ",", Cn[i])

#print(gint(5, False))
exit(1)
#print(n, complexGaussSum(n), countLattice(n)-1)
#exit(1)
