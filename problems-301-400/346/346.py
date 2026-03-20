import math

maxn = 10**12
#maxn = 10000
maxbase = int(math.sqrt(maxn)) + 1
lnmaxn = math.log(maxn)
repu_size = int(math.sqrt(maxn)) + 1

A = 0
a = 1
s = 1
reps=set()
for a in range(2, maxbase):
    A = 0
    A = a*a+a+1
    while (A < maxn):
        n = 2
        while True:
            if (A < maxn):
                if not A in reps:
                    s += A
                    reps.add(A)
                    #print(a, n, A, s)
            else:
                break
            n += 1
            A += a**n

print(s)
