import copy

MAXINT = 80

primes = [11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97]

rs = [0]*(MAXINT+2) # number squared
ss = [0]*(MAXINT+2) # ss[n] = sum of recip squares from n to MAXINT



    
#print(rs)
#print(ss)
#print(ex)



from itertools import combinations
import math

primes = [7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79]
bad_primes = [False] * (MAXINT + 2)

def zout(z):
    print(" sum: ", z[0], " length: ", z[1], "  elements: ", end="")
    for i in range(2, MAXINT+1):
        if z[i] < 0: print("x", i, " ", end = "", sep="")
        if z[i] > 0: print(i, " ", end = "")
    print(flush=True)

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
    
def prodsum(v):
    global rs
    ps = 0
    for i, a in enumerate(v):
        if i < 2: continue
        if a > 0: ps += rs[i]
    return ps

def findrecips(p, maxn):
    global bad_primes
    n = maxn // p
    # print(n, flush=True)
    if n == 0: return []
    sq = [i*i for i in range(1,n+1)]
    psq = p * p
    rv = []
    for k in range(2, len(sq)+1):
        ll = list(combinations(sq, k))
        #print(ll)
        for a in ll:
            sumsq = 0
            if k == 2:
                sumsq = a[0] + a[1]
                if sumsq % psq == 0:
                    #pout(p, sumsq, a)
                    rv.append(a)
            else:
                al = list(combinations(a, k-1))
                for tu in al:
                    sumsq += prod(tu)
                if sumsq % psq == 0:
                    #pout(p, sumsq, a)
                    rv.append(a)
    return rv
#
# compute all reciprocal squares and the sums from n to MAXINT
#
for r in range(2, (MAXINT+1)):
    s = 0
    rs[r] = 1/r/r
    for n in range(r, MAXINT+1):
        if bad_primes[n]: continue
        n2 = n * n
        s += 1/n2
    ss[r] = s
##
## start the list of possible solutions
## solutions will include all off the non repeating multiple of 7's
## when combined CAN produces a potential solution
## all of the multiples of 13 - there turns out to be only 1
## we will include solutions with 7's and no 13's
## with 13's and no sevens
## with 13's and sevens
## and with neither
##

qq=[]

##
## we will creat solutions with 7's and 13's (we know this in advance
## since i've run this program many many times)
##
psets={}
qindex = 0
primeruns = []
for p in primes:
    g = findrecips(p, MAXINT)
    if len(g) == 0: 
        #print("BAD PRIME:", p)
        k = 1
        while k*p < MAXINT:
            bad_primes[k*p] = True
            k += 1
    else:
        psets[p]=(qindex,qindex+len(g))
        qindex += len(g)
        for pl in g:
            print(pl)
            pr = []
            for a in pl:
                pr.append(int(p*math.sqrt(a)+0.1))
            primeruns.append(pr)

for p in primeruns:
    print(p)
print(psets)
##
## psets contains the indexes into qq for the prime sets
## of numbers
##
## need to append to qq all of the combinations from the two
## sets from psets (I know there are only two from 7 and 13 - the
## rest of the primes are not allowed in the solution
##

def createsol(inc7, inc13):
    global bad_primes
    x = [0] * (MAXINT + 2)
    x[1] = 3
    x[2] = 1
    x[3] = 1 # 1/4 and 1/9 has to be in any solution
    for i in inc7:
        x[i] = 1
    k = 7
    while k < MAXINT:
        if x[k] == 0: x[k] = -1
        k += 7
    for i in inc13:
        x[i] = 1
    k = 13
    while k < MAXINT:
        if x[k] == 0: x[k] = -1
        k += 13
    for i in range(MAXINT+1):
        if bad_primes[i]: x[i] = -1
    x[0] = prodsum(x)
    return x

s7, e7 = psets[7]
s13, e13 = psets[13]
##
## create solutions with both 7's and 13's
##
qq.append(createsol([],[]))
for i in range(s7,e7):
    qq.append(createsol(primeruns[i], [])) # sevens, no 13s
    for j in range(s13, e13):
        qq.append(createsol(primeruns[i], primeruns[j])) # 7's and 13's
for j in range(s13, e13):
    qq.append(createsol([], primeruns[j])) # no 7's, 13s

for q in qq:
    zout(q)
# ## create solutions with just 7's
# ##
# ## create solution with just 13's
# ##
# ## create solution with NO 7's or 13's
# ##
# for i in range(s7,e7):
    # both = [0] * (MAXINT + 2)
    # j7 = [0] * (MAXINT + 2)
    # j13 = [0] * (MAXINT + 2)
    # x[1] = 3
    # x[2] = 1
    # x[3] = 1 # 1/4 and 1/9 has to be in any solution
    # k = 7
    # while k < MAXINT:
        # if k in qq[i]: x[k] = 1
        # else: x[k] = -1
        # k += 7
        # for k in bad_primes:
            # x[k] = -1
        # x[0] = prodsum(x)
        # qq.append(x)

    # for j in range(s13, e13):

        # ##
        # ## x has only 7's - no 13's
        # ##
        # k = 13
        # while k < MAXINT:
            # x[k] = -1
            # k += 13        
        # for k in bad_primes:
            # x[k] = -1
        # x[0] = prodsum(x)
        # qq.append(x)
        # ##
        # ## now include 13's
        # k = 13
        # while k < MAXINT:
            # if k in qq[i]: x[k] = 1
            # k += 13
        # x[0] = prodsum(x)
        # qq.append(x)
            



# # s7, e7 = psets[7]
# # s13, e13 = psets[13]
# # for i in range(s7,e7):
    # # for j in range(s13, e13):
        # # x = [0] * (MAXINT + 2)
        # # x[1] = 3
        # # x[2] = 1
        # # x[3] = 1 # 1/4 and 1/9 has to be in any solution
        # # #print(a, flush=True)
        # # ##
        # # ## x[k*p] will be -1 or 1 if k*p is or is not in the 
        # # ## sum squared recips that add to a non-repeating
        # # ## fraction
        # # for l in a:
        # # n = int(p*math.sqrt(l)+0.1)
        # # #print(n)
        # # x[n] = 1
        # # t = p
        # # while t < MAXINT:
        # # if x[t] == 0: x[t] = -1
        # # t += p
        # # x[0] = prodsum(x)
        # # qq.append(x)
                    
# ## now add in the other solution types that can include
# ## all the above - and NONE of the above
# ##
# xall = [0] * (MAXINT + 2)
# xmin = [0] * (MAXINT + 2)
# for a in qq:
    # ## xall - whenever there is a non-zero number - add a 1
    # ## xmin - whenever there is a non-zero number - add a -1
    # xall[2] = 1
    # xmin[2] = 1
    # xall[3] = 1
    # xmin[3] = 1
    # for i in range(4, MAXINT+1):
        # if a[i] != 0: xall[i] = 1 
        # if a[i] != 0: xmin[i] = -1 
# xall[1] = 3
# xmin[1] = 3
# xall[0] = prodsum(xall)
# xmin[0] = prodsum(xmin)
# qq.append(xall)
# qq.append(xmin)

for a in qq:
    for i in range(7, MAXINT+1):
        if bad_primes[i]: a[i] = -1
    zout(a)

# A Python program to print all 
# combinations of given length
from itertools import combinations
 
loop = 0
count = 0

LIMIT = 0.5
EPSILON = 0.000000000000001
ABOVE_LIMIT = LIMIT + 2 * EPSILON
BELOW_LIMIT = LIMIT - 2 * EPSILON

q = qq
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
    #
    while r[n] != 0 and n < MAXINT: n += 1
    if n > MAXINT: continue

    if ss[n] + r[0] < BELOW_LIMIT: 
        #print(len(q), " Removing: ", end="") 
        #zout(r)
        continue
    if r[0] > ABOVE_LIMIT: 
        #print("Sum exceeded: ", r[0], r[1])
        continue
    ##
    ## don't include 1/n^2
    r1 = copy.deepcopy(r)
    r2 = copy.deepcopy(r)
    #print(loop, n, len(q), r1[0], r1[1], prodsum(r1))
    ##
    ## include 1/n^2
    r2[0] += rs[n]
    r2[1] = n
    r2[n] = 1
    if r2[0] < ABOVE_LIMIT:
        q.append(r2)
        #zout(r2)
    #print(loop, n, len(q), r2[0], r2[1], prodsum(r2))
    r1[1] = n
    r1[n] = -1
    if r1[0] + ss[n] > BELOW_LIMIT:
        ## if there is a possibility to find a solution add to queue
        q.append(r1)
        #zout(r1)
