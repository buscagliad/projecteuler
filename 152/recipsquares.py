import copy

MAXINT = 80

primes = [11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97]

rs = [0]*(MAXINT+2) # number squared
ss = [0]*(MAXINT+2) # ss[n] = sum of recip squares from n to MAXINT
ex = []     # excluded numbers

for p in primes:
    i = 1
    while i * p < MAXINT:
        ex.append(p*i)
        i += 1

for r in range(2, (MAXINT+1)):
    s = 0
    rs[r] = 1/r/r
    for n in range(r, MAXINT+1):
        if n in ex: continue
        n2 = n * n
        s += 1/n2
    ss[r] = s
    
print(rs)
print(ss)
print(ex)
def prodsum(v):
    global rs
    ps = 0
    for i, a in enumerate(v):
        if i < 2: continue
        if a > 0: ps += rs[i]
    return ps
##
## solver recursively viewing it as a connected graph, summing along the
## way, and exitting whenever == 1/2, and report
##                          or > 1/2, just exit that path
##
## q[0] is the sum
## q[1] is the current index
## q[n] = 1 or 0 if 1/n/n is in the sum
## all solutions must include n = 2

q=[]
# for k in range(127,1,-1):
    # x = [0] * 82
    # x[1] = 7
    # x[2] = 1
    # m = k
    # for j in range(3,8):
        # x[j] = m % 2
        # m //= 2
    # x[0] = prodsum(x)
    # q.append(x)
x = [0] * (MAXINT+2)
x[1] = 2
x[2] = 1
x[0] = prodsum(x)
q.append(x)

for a in q:
    print(a)
# A Python program to print all 
# combinations of given length
from itertools import combinations
 
# Get all combinations of [1, 2, 3]
# and length 2
 
# for p in [7, 11, 13, 17, 19, 23, 31, 37]:
    # k = 80 // p
    # c = []
    # for i in range(1, k+1):
        # c.append(p * p * i * i)
    # for i in range(2, k+1):
        # comb = combinations(c, i)
        # for m in (list(comb)):
            # ms = 0
            # for mm in m:
                # ms += mm % p*p
                # print(ms, m)
            # if ms == 0:
                # print("Combos: ", m, ms)
# exit(1)
loop = 0
count = 0
def zout(z):
    print(" sum: ", z[0], " length: ", z[1], "  elements: ", end="")
    for i in range(2, MAXINT+1):
        if z[i] > 0: print(i, " ", end = "")
    print(flush=True)

LIMIT = 0.5
EPSILON = 0.000000000000001
ABOVE_LIMIT = LIMIT + 2 * EPSILON
BELOW_LIMIT = LIMIT - 2 * EPSILON

while q:
    loop += 1
    r = q.pop()
    #print("Q size: ", len(q), r[0])
    diff = abs(r[0] - 0.5)
    if diff < EPSILON:
        count += 1
        print(count, " Sum found: ", r[0], end = "")
        zout(r)
        continue
    #if diff < ss[MAXINT]:
    #    continue
    n = r[1] + 1
    if n > MAXINT: continue
    if n in ex: 
        r[1] += 1
        q.append(r) # skip this value
        #print("Skipping: ", n)
        continue
    if ss[n] + r[0] < BELOW_LIMIT: 
        #print("Removing: ", end="") 
        #zout(r)
        continue
    if r[0] > 0.5: 
        #print("Sum exceeded: ", r[0], r[1])
        continue
    ##
    ## don't include 1/n^2
    r1 = copy.deepcopy(r)
    r2 = copy.deepcopy(r)
    r1[1] = n
    r1[n] = 0
    ## if there is a possibility to find a solution add to queue
    q.append(r1)
    #print(loop, n, len(q), r1[0], r1[1], prodsum(r1))
    ##
    ## include 1/n^2
    r2[0] += rs[n]
    r2[1] = n
    r2[n] = 1
    q.append(r2)
    #print(loop, n, len(q), r2[0], r2[1], prodsum(r2))
