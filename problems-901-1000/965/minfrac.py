import math
import numpy as np

#
# sorting took the longest time
# discovered - after I got the solution
# there is something called the Stern-Brocot tree that
# generates these sets of rational numbers without
# the need to sort
# xxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
# Number points:  30397487
# End of sorting
# ...................................................................................................
# ALL GOOD - area =  0.0003452201133311098
# which is the correct answer, but took a few minutes to run
#


def oneval(n, d, N):
    return d

def fn(x, N):
    minx = 1
    minn = N
    for n in range(1, N+1):
        i, f = math.modf(n*x)
        if i < minx:
            minx = i
            minn = n
        #print(i, f, n, minx)
    #print(x, N)
    return minn, minx

def doplots(N, ppts):
    xs = []
    ys = []
    for k in range(ppts):
        xs.append( k / ppts )
        n, y = fn( k/ppts, N )
        ys.append( y )

    # for i, x in enumerate(xs):
        # print(x, ys[i])
    plt.plot(xs, ys)
    plt.xlabel('X-axis')
    plt.ylabel('Y-axis')
    plt.title('fN(x)  N = ' + str(N))
    plt.show()
    
    
def ipts(N):
    x = [(0, 0, 1), (1,1,1)]
    info = []
    mlen = 1000000
    for denom in range(1, N+1):
        for num in range(1, denom):
            k = math.gcd(num, denom)
            #print("num: ", num, "  denom: ", denom, "  k = ", k)
            # n = num // k
            # d = denom // k
            if k > 1: continue
            x.append((num/denom,num,denom))
            #info.append((num, denom, num/denom, yn))
        if len(x) > mlen:
            print("x", end="", flush=True)
            mlen += 1000000
    print("\nNumber points: ", len(x), flush=True)
    x.sort(key=lambda tup: tup[0])
    print("End of sorting", flush=True)
    return x
    
    
N = 10000
apts=ipts(N)
x0 = apts[0][0]
area = 0
s0 = 1
pct = 0.01 * len(apts)
npct = pct
for i, (x1, n, s1)  in enumerate(apts):
    #n = oneval(n, slope, N)
    da = s0 * (x1 - x0) * (x1 - x0) /  2
    area += da
    #print(i, " >> ",x0, x1, n, s0, da, area)
    x0 = x1
    s0 = s1
    if i > npct:
        print(".", end="", flush=True)
        npct += pct
print()
print("ALL GOOD - area = ", area)
print(flush = True)
# doplots(N, 100*N)
# exit(1)

