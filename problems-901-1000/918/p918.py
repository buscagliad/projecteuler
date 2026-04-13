
import numpy as np

def a(s, n):
    if n < 100:
        return s.a[n]
    if n % 2 == 0:
        return 2 * a(s, n//2)
    else:
        k = (n - 1) // 2
        return a(s, k) - 3 * a(s, k+1)

def SofN(s, N):
    if N % 2 == 0:
        return 4 - a(s, N//2) 
    k = (N - 1)//2 
    return 4 - 3 * a(s, k+1)

class seq:
    def __init__(self, ft, maxn):
        self.a = [0] * (maxn + 2)
        self.sum = [0] * (maxn + 2)
        self.a[1] = ft
        self.n = 1
        self.sum[1] = ft
        self.maxn = maxn
    def next(self):
        self.n += 1
        if self.n > self.maxn + 1:
            print("Max n hit")
            exit(1)
        if self.n % 2 == 1:
            m = (self.n - 1) // 2
            self.a[self.n] = self.a[m] - 3 * self.a[m+1]
        else:
            m = self.n // 2
            self.a[self.n] = 2 * self.a[m]
        self.sum[self.n] = self.sum[self.n-1]
        self.sum[self.n] += self.a[self.n]
    def list(self, M):
        s = 0
        for i in range(1, M+1):
            s += self.a[i]
            if i % 2 == 1:
                k = (i - 1)//2 + 1
                ts = 4-3*self.a[k]
            else:
                k = i//2
                ts = - self.a[k] + 4
            print(i, "a[",i,"]=",self.a[i], " sum: ", s, " short cut sum: ", ts)
 

s = seq(1, 1000)
    
for _ in range(1000):
    s.next()

print(SofN(s, 1000000000000))
