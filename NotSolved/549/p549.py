import math

#
# vp answers the question: how many factors of p are in k
#
def vp(k: int, p: int) -> int:
    if k == 0:
        return float('inf')   # by convention
    if p <= 1:
        raise ValueError("p must be a prime >= 2")

    k = abs(k)
    count = 0
    while k % p == 0:
        k //= p
        count += 1
    return count


class Prime:
    def __init__(self, pdir, max_prime):
        self.primes = []
        for i in range (1, 2):
            file = pdir + '/primes'
            if i < 9:
                file += '0'
            file += str(i) + '.txt'
            for i, l in enumerate(open(file, 'r')):
                if i < 2: continue
                for j in l.split():
                    self.primes.append(int(j))
        #print(self.primes)
    def isprime(self, n):
        if n in self.primes: return true
        return false


        
def prime_factor(n):
    factors = []

    # Handling even numbers separately
    cnt = 0
    while n % 2 == 0:
        cnt += 1
        n //= 2
    if cnt:
        factors.append((2, cnt))

    # Now n must be odd, we only need to check odd numbers
    divisor = 3

    # Optimized loop to reduce redundant divisions
    while divisor * divisor <= n:
        cnt = 0
        while n % divisor == 0:
            cnt += 1
            n //= divisor
        if cnt:
            factors.append((divisor, cnt))
        divisor += 2  # Increment by 2 to skip even numbers

    # If n is still greater than 1, it's a prime factor itself
    if n > 1:
        factors.append((n, 1))

    return factors


def test_prime_factor(n):
    fs = prime_factor(n)
    s = 1
    for (p, a) in fs:
        s *= p ** a
    print("N: ", n, s, "  Factors: ", fs)


MAXTN = 1000
fn = [0]*MAXTN
tri_num = 0
index = 1
for tn in range(1,MAXTN-3):
    tri_num += tn
    fn[index] = tri_num
    index += 1

#for i in range(1,6):
#    print(i, fn[i])

def tri(n):
    global fn
    ix = 1
    while fn[ix] < n:
        ix += 1
    print("tri - n: ", n, "  ix: ", ix, " fn: ", fn[ix])
    return ix
    
pkmap = {}


# Tests whether the given integer is a prime number.
def is_prime(x: int) -> bool:
	if x <= 1:
		return False
	elif x <= 3:
		return True
	elif x % 2 == 0:
		return False
	else:
		for i in range(3, int(math.sqrt(x)) + 1, 2):
			if x % i == 0:
				return False
		return True

# returns the smallest n, such that p^k divides n!
#
def numfacs(p, k):
    nfacs = 0
    n = 0
    while nfacs < k:
        add = 0
        n += p
        g = n
        if g % k == 0:
            while g % p == 0:
                add += 1
                g = g // p
        else:
            add = 1
        if nfacs >= k: return n
        nfacs += add
        print(p, k, n, add, nfacs)
    return n


# for p in [2]: #, 3, 5, 7]:
    # for k in range(1, 4):
        # print(p, k, numfacs(p, k))
# exit(1)

#
# for all n < 10^4  that are prime - determine what k
# is the smallest k such that 


def fillspk():
    global pkmap
    for p in range(2, 4): #10000):
        if is_prime(p):
            #
            # m represents the number such that m! <= 10^8 < (m+1)!
            m = int(8*math.log(10)/math.log(p))
            vpv = [0]*(m+1)
            for j in range(1, m+1):
                vpv[j] = vp(j, p) + vpv[j-1] + 1
            #print(vpv)
            k = 2
            while k < m+1:
                if k % p == 0:
                    print("HELLO")
            # lv = 1
            # pkmap[(p,1)] = p
            # for c, rv in enumerate(vpv[1:]):
                # rc = c+1
                # #print(rc, lv, rv)
                # for j in range(lv, rv):
                    # pkmap[(p, j+1)] = rc*3
                    # #print(j, rc)
                # lv = rv
            #print(pkmap)
            #exit(1)
            
            # we will cycle through each factor of the prime number 
            # keeping track of how many factors are in k!
            # pkmap(p,k) = Ap for some integer A, where (Ap)! divides p^k
            # pkmap(p,1) = p for all prime p
            # pkmap(p,2) = 2p
 
# s(3,1)	3
# s(3,2)	6
# s(3,3)	9
# s(3,4)	9
# s(3,5)	12
# s(3,6)	15
# s(3,7)	18
# s(3,8)	18
# s(3,9)	21
# s(3,10)	24
# s(3,11)	27
# s(3,12)	27
# s(3,13)	27
# s(3,14)	30
# s(3,15)	33
# s(3,16)	36
# s(3,17)	36
# s(3,18)	39
# s(3,19)	42
# s(3,20)	45

fillspk()

for k in range(1,10):
    for p in [2,3]:
        pk = (p,k)
        print(pk, pkmap[pk])

exit(1)

def s(p, k):
    global pkmap
    if (p,k) in pkmap:
        print((p,k), " in pkmap")
        return pkmap[(p,k)]
    pwrs = 0
    np = 0
    while pwrs < k:
        np += p
        pwrs += int(np / p )
        print(pwrs, k, np, p)
    pkmap[(p,k)] = np
    return np

facts = []
facts.append((0,0)) # 0'th element
facts.append((1,0)) # 1st element (both are not used)

def factor(n):
    global facts
    rfs = []
    usen = 0
    for prime in [2,3,5,7]:
        if n == prime:
            break
        if n % prime == 0:
            fs = facts[n//prime]
            usen = prime
            break
    if usen:
        print(fs)
        for (p, a) in fs:
            if p == usen: a += 1
            rfs.append((p,a))
    else:
        rfs = prime_factor(n)
    facts.append(rfs)
    return rfs

def maxpf(n, fs):
    mpf = 0
    for (k, pwr) in fs:
        nf = s(k, pwr)
        print("k:",k, "  pwr:", pwr, "  nf:", nf)
        if nf > mpf:
            mpf = nf
    ff = math.factorial(mpf)
    if ( ff  //  n ) * n != ff:
        print("not divisible: n: ", n, "   mpf: ", mpf, "  mpf!: ", ff)
    return mpf

def test1(n):
    fs = prime_factor(n)
    mp = maxpf(n, fs)
    print(n, " factors: ", fs, " min fac: ", mp)
    exit(1)
#test1(64)

def pfac(i):
    for n in range(2, i+1):
        print("-------",n,"-------------")
        fs = prime_factor(n)
        mp = maxpf(n, fs)
        print(n, " factors: ", fs, " min fac: ", mp)

# pfac(27)
# exit(1)

def hardway(n, mp):
    MAXHW=12
    if mp > MAXHW: return 0
    f = 1
    for i in range(2, MAXHW):
        f *= i
        if f % n == 0: return i
    return -1
        
    
#dave = Prime("/home/dave/projecteuler/primes", 1)
total = 0
LAST_INT=100
for i in range(2, LAST_INT +  1):
    #print("--------------------")
    fs = prime_factor(i)
    mp = maxpf(i, fs)
    print(i, " factors: ", fs, " min fac: ", mp, "  HARDWAY: ", hardway(i, mp))
    total += mp
print(total)
