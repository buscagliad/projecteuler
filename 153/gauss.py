import math
import primefac
import sys

debug = False

def complexGaussSum( N ):
    cgsum = 0
    cgcnt = 0
    #rootN = int(math.sqrt(N) + 0.000001) 
    if debug: print("******* Gauss Sum: ", N)
    for a in range(1, N+1):
        a2 = a * a
        for b in range(1, N+1):
            s = a2 + b * b
            if s > N : break
            if a == b:
                cgcnt += 2
                cgsum += 2*a
                if debug: print("a == b", a, b, 2*a)
            else: 
                cgcnt += 4
                cgsum += 2 * (a + b)
                if debug: print("a != b", a, b, 2*(a+b))
    print ("Count gauss circle integer points at ", N, " is ", cgcnt)
    return cgsum

# Function to count Lattice
# points on a circle
def countLattice(r):

    if (r <= 0):
        return 0  

    # Initialize result as 4 for (r, 0), (-r. 0),
    # (0, r) and (0, -r)
    result = 4 * r

    # Check every value that can be potential x
    for x in range(1, r):
    
        # Find a potential y
        ySquare = r*r - x*x 
        y = int(math.sqrt(ySquare)) 

        # checking whether square root is an integer
        # or not. Count increments by 4 for four 
        # different quadrant values
        if (y*y == ySquare):
            result += 2 * (x + y)
     

    return result 

def sumfac(k):
    factors = list( primefac.primefac(k) )
    #print("sumfac:  k=", k, factors)
    unique = set(factors)
    # if len(factors) == 1:
        # print("Prime: ", unique)
    #print("u=", unique)
    #print("sumfac: factors: ", factors)
    #print("sumfac: unique: ", unique)
    ps = 1
    for u in unique:
        ai = factors.count(u)+1
        ps *= (u ** ai - 1) // (u - 1)
        #print(u, ps)
    #print(ps)
    return ps
            
def gint(n):
    gc = complexGaussSum(n)
    gs = 0
    for k in range(1, n+1):
    #for k in range(49, 52):
        factors = list( primefac.primefac(k) )
        #print("k=", k, factors)
        unique = set(factors)
        # if len(factors) == 1:
            # print("Prime: ", unique)
        #print("u=", unique)
        s = 1
        #print("gint: factors: ", factors)
        #print("gint: unique: ", unique)
        ps = 1
        for u in unique:
            ai = factors.count(u)+1
            ps *= (u ** ai - 1) // (u - 1)
            #print(u, ps)
        #print(ps)
        gs += ps
    print(gs, gc, gs+gc)
    return gs + gc
n=1000
print(sumfac(1225))
print(complexGaussSum(144))
exit(1)
#print(n, complexGaussSum(n), countLattice(n)-1)
#exit(1)
print( gint(100000))
exit(1)
cursum = 0
for n in range(1, 101):
    if debug: print("********* n: ", n)
    factors = list( primefac.primefac(n) )
    gi = gint(n)
    cursum += gi
    print(n, "   S(n) = ", cursum)
    # if (n == 5 or n == 10 or 
        # n == 50 or n == 100 or 
        # n == 500 or n == 1000 or n == 10000):
        # print(n, "   S(n) = ", cursum)

print(gint(2450))
