
import math # math.isqrt efficent integer square root calculator
import numpy as np

def intsqrt(n) -> bool:
    a = math.isqrt(n)
    return a * a == n

def triinv(G):
    l = 1 + 8 * G
    return (math.isqrt(l) - 1 ) // 2

def trinum(n):
    return (n * (n + 1))// 2
    
def istrinum(n):
    a = math.isqrt(8*n + 1)    
    return (a*a)==n, a
    

def nexttn(k, lastn):
    done = False
    #n = math.isqrt(k)
    #n = math.isqrt(k)
    n = lastn
    print(n, k)
    n = 1
    while not done:
        n += 1
        s = trinum(n) + k
        if istrinum(s):
            done = True
    return n, s

def test():
    H=9824657984729697
    for n in range(H, H+5):
        print(n, trinum(n), triinv(trinum(n)))

    lastn = 1
    n = 6
    tk = 2
    index = 2
    while tk < 30:
        nadder, newn = nexttn(n, lastn)
        lastn = n
        index += nadder
        tk += 1
        print("Tk: ", tk, " Index: ", index, " Value: ", newn, math.isqrt(n), newn-n, flush=True)
        n = newn


MAX = 100000
tri = np.zeros([MAX], dtype = int)
tri[0] = 0
for i in range(1, MAX):
    tri[i] = i + tri[i-1]


test()

print(tri[MAX-1], trinum(MAX-1))
print(tri[2], trinum(2))
T = np.zeros([71], dtype = int)
T[0] = 3
k = 0
index = 0
s = 0
for t in range(1, 12):
    for j in range(0, MAX-1):
        s += 1
        d = tri[index+j+1] - T[k]
        #print(d, j, index, k, flush=True)
        ist, tnum = istrinum(d)
        print(ist, tnum)
        if ist:
            s += 1
            k += 1
            T[k] = T[k-1] + d
            index += tnum
            print("k: ", k, "  index: ", index, "  T[k]: ", T[k], "  d: ", d, "  s: ", s, flush=True)
            break

