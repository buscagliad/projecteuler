
from sympy.ntheory import isprime
    
sumn = 0
# primes={}
# def isprime(num):
    # """Checks if a number is prime."""
    # #if num in primes: return primes[num]
    
    # if num <= 1:
        # return False

    # # Iterate from 2 to the square root of the number
    # for i in range(2, int(num ** 0.5) + 1):
        # if num % i == 0:
            # #primes[num] = False
            # return False
    # #primes[num] = True
    # return True

for n in range(2, 150000000, 2):
    if n % 7 == 0: continue
    if n % 3 == 0: continue
    if n % 13 == 0: continue
    n2 = n * n
    #print(n, n2, flush=True)
    if isprime(n2+5):
        continue
    if isprime(n2+11):
        continue
    if isprime(n2+15):
        continue
    if isprime(n2+17):
        continue
    if isprime(n2+19):
        continue
    if isprime(n2+21):
        continue
    if isprime(n2+23):
        continue
    if isprime(n2+25):
        continue
    if isprime(n2 + 1):
        if isprime(n2 + 3):
            if isprime(n2 + 7):
                if isprime(n2 + 9):
                   if isprime(n2+13):
                        if isprime(n2+27):
                            print("Found: ", n, flush=True)
                            sumn += n

print("Sum is: ", sumn)
