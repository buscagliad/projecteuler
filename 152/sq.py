from itertools import combinations
import math

MAXNUM = 80
primes = [7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79]

def prod(t):
    pr = 1
    for a in t:
        pr *= a
    return pr

def pout(p, sumsq, nums):
    print("Prime: ", p, "  sumsq: ", sumsq, "  nums: ", end = "")
    for l in nums:
        print(int(math.sqrt(l))*p, " ", end = "")
    print()
    

def findrecips(p, MAXNUM):
    n = MAXNUM // p
    sq = [i*i for i in range(1,n+1)]
    psq = p * p
    for k in range(2, len(sq)+1):
        ll = list(combinations(sq, k))
        #print(ll)
        for a in ll:
            sumsq = 0
            if k == 2:
                sumsq = a[0] + a[1]
                if sumsq % psq == 0:
                    print("Prime: ", p, "  sumsq: ", sumsq, "  nums: ", a)
            else:
                al = list(combinations(a, k-1))
                for tu in al:
                    sumsq += prod(tu)
                if sumsq % psq == 0:
                    pout(p, sumsq, a)
                # prod = 1
                # print(al)
                # for x in al:
                    # prod *= x
                # sums += prod
            # if sums % pd == 0:
                # for d in a:
                    # print(math.sqrt(d), " ", end = "")
                # print()

for p in primes:
    g = findrecips(p, MAXNUM)
    # for a in g:
        # print(a)
