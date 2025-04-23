
N=20000
PTEN = 12
N=200000
PTEN = 12
fact5s = [0]*(N+1)
sfact5s = [0]*(N+1)
fact2s = [0]*(N+1)
sfact2s = [0]*(N+1)
for i in range(1, N+1):
    f = i
    count = 0
    while f % 5 == 0:
        count += 1
        f //= 5
    fact5s[i] = count
    count = 0
    while f % 2 == 0:
        count += 1
        f //= 2
    fact2s[i] = count

sfact5s[1] = fact5s[1]
sfact2s[1] = fact2s[1]
for i in range(2, N+1):
    sfact2s[i] = sfact2s[i-1] + fact2s[i]
    sfact5s[i] = sfact5s[i-1] + fact5s[i]
print("Done")

# compute the number of factors of five in n choose k

def fives(n, k):
    count = 0
    return sfact5s[n]-sfact5s[k-1]

def twos(n, k):
    count = 0
    return sfact2s[n]-sfact2s[k-1]

print(N, "!  has ", sfact5s[N], " factors of 5, and ", sfact2s[N], "factors of 2")

#print(sfacts)

# (x + y + z)^n = SUM[n!/(m! * l! * (n-m-l)!) * x^m * y^m * z ^(n-m-l)] from 0 to n
# the coefficient n!/(m! * l! * (n-m-l)!) is divisible by 10^R whenenver
# the coeeficient has at least R factors of 2 and 5 (each)
# Since 2 and 5 are relatively prime, we need to just see how many
# factors of 2 and 5 exist in n!, m!, l! and (n-m-l)! 
# sfact2s[k] and sfact5s[k] will provide the number of factors or 2 and 5
# respectively for k!
#
# c2 = sfact2s[n] - sfact2s[m] - sfact2s[k] - sfact2s[l]
# c5 = sfact5s[n] - sfact5s[m] - sfact5s[k] - sfact5s[l]
# provides the number of factors of 2 and 5 in each coefficient
# if c2 and c5 are both >= R, then the coefficient is divisible by 10^R
#

total = 0
combos = 0
n5 = sfact5s[N]
n2 = sfact2s[N]
early = 0
for m in range(N+1):
    if m % 200: print ("m = ", m//1000/10, end='\r')
    perm = 0
    ss = 0
    cn5 = n5 - sfact5s[m]
    cn2 = n2 - sfact2s[m]
    if cn2 < PTEN or cn5 < PTEN: 
        combos += 1
        early += 1
        continue
    for l in range(N - m + 1):
        k = N - l - m
        combos += 1
        #print(m, l, k, m+l+k)
        #
        # there should be some logic that will let us skip over
        # coefficients once 12 is reached 
        # is there symmetry at play??
        #
        c5 = cn5 - sfact5s[k] - sfact5s[l]
        c2 = cn2 - sfact2s[k] - sfact2s[l]
        if c2 < PTEN or c5 < PTEN: 
            #print(c5, c2, m, l, k)
            continue
        else: 
            #if ss > 1: print(m, l, ss)
            perm += 1
            total += 1
            #print(n5, m5, c, m, l, k)
            #print(total, m, l, k, c)
    #print(m, perm)
print()
print(early, total, combos)
