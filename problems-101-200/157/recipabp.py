import math
import primefac
import sys
import numpy as np
import time

debug = False

def complexGaussSum( N ):
    # Add contributions from Gaussian integer divisors with b != 0
    # Only consider (a + bi) with b > 0 and gcd(a, b) == 1
    result = 0
    max_c = int(math.isqrt(N))
    for b in range(1, max_c + 1):
        for a in range(1, max_c + 1):
            if math.gcd(a, b) > 1:
                continue
            norm = a * a + b * b
            if norm > N:
                break
            for k in range(1, N // norm + 1):
                contrib = 2 * a * k * (N // (k * norm))
                result += contrib
    return result

    
def sumFactors(N):
    fs = 0
    for d in range(1, N+1):
        sf = d * (N//d)
        fs += sf
    return fs
            
def gint(n):
    start = time.process_time()
    # your code here    
    debug = False
    gc = complexGaussSum(n)
    print("complexGaussSum: ", gc, " time: ", time.process_time() - start, "seconds")
    
    start = time.process_time()
    gs = sumFactors(n)
    print("sumFactors: ", gs, " time: ", time.process_time() - start, "seconds")
    print("Gauss sum: ", gs, "  Sum factors: ", gc, "  Total: ", gs+gc)
    return gs + gc


## NOTE: gint(10**5) should equal 17924657155
print(gint(10**5))

# complexGaussSum:  9746583700166398  time:  63.485101259000004 seconds
# sumFactors:  8224670422194237  time:  3.728455689999997 seconds
# Gauss sum:  8224670422194237   Sum factors:  9746583700166398   Total:  17971254122360635
# 17971254122360635


