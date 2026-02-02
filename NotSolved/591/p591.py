

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
    while n % 2 == 0:
        factors.append(2)
        n //= 2

    # Now n must be odd, we only need to check odd numbers
    divisor = 3

    # Optimized loop to reduce redundant divisions
    while divisor * divisor <= n:
        while n % divisor == 0:
            factors.append(divisor)
            n //= divisor
        divisor += 2  # Increment by 2 to skip even numbers

    # If n is still greater than 1, it's a prime factor itself
    if n > 1:
        factors.append(n)

    return factors
        
        
#dave = Prime("/home/dave/projecteuler/primes", 1)
s = 0
LAST_INT=100
for i in range(2, LAST_INT +  1):
    fs = prime_factor(i)
    mp = max(fs)
    mn = fs.count(mp)
    s += mp * mn
print(s)
