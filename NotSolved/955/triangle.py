
import math

def isTriangular(n: int) -> bool:
    """
    when 8.0*n+1.0 is a perfect square it is triangular
    """
    x = 8*n+1
    root = math.isqrt(x)
    return root*root == x

def getTriangle(n: int) -> int:
    return (n * (n + 1)) // 2
    
def getNtriangle(n: int) -> int:
    twon = 2 * n
    rad = 1 + 4 * twon
    root = math.isqrt(rad)
    return (root - 1) // 2

for n in range(5,10):
    tn = getTriangle(n)
    on = getNtriangle/*(tn)
    print(n, tn, on)

exit(1)
    

def test4():
    for N in range(5, 13):
        tn = getTriangle(N)
        Nx = getNtriangle(tn)
        print (N, tn, Nx)

def test3x():
    tk = 1
    a = 3
    index = 0
    test3over = False
    while not test3over:
        n = 1
        tfound = False
        while not tfound:
            a = a + n
            n += 1
            index += 1
            if isTriangular(a):
                tk += 1
                print("a: ", a, " index: ", index, "  tk: ", tk, flush = True)
                if tk == 30: exit(1)
                n = 1
#  a:  1439056  index:  2964   tk:  10                    
            
def test3():
    tk = 0
    a = 3
    index = 0

    tfound = False
    while not tfound:
        if not isTriangular(a):
            a = a + n
            n += 1
            index += 1
        else:
            tk += 1
            trin = getNtriangle(a)
            print("a: ", a, " index: ", index, "  tk: ", tk, " triang N: ", trin, flush = True)
            if tk == 10: exit(1)
            n = getTriangle(trin)
            index += trin
            a += n
#  a:  1439056  index:  2964   tk:  10                    

def test1():
    tan = 3
    an = 7
    anm1 = 6
    index = 3
    anp1 = 4

    while tan < 71:
        index += 1
        #print(an)
        
        anp1 = 2 * an - anm1 + 1
        n = index
        #print(an, (2+4*n+n*n)//2, end="")
        anm1 = an
        an = anp1
        if isTriangular(an):
            print("T", index, tan, anp1, flush=True)
            tan += 1
            index += 1
            print("the ", index, " triangle number in the sequence is ", an)
            anm1 = an
            anp1 = an + 1
            an = anp1

# for n in range(14390500, 14392000):
    # if isTriangular(n): print(n, " is a triangle number")
    
def test2():
    a = 7
    t = 2
    for n in range(4, 11):
        if isTriangular(a): 
            a += 1
            t += 1
        else:
            a = (14 - 3 * n + n * n) // 2 + t
        print(n, a)
        

test3x()
