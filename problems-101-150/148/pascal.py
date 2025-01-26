import numpy as np
Nrows = 1000

p = np.zeros([Nrows+2,Nrows+3], dtype=int)
p[1,1] = 1
p[2,1] = 1
p[2,2] = 1

for n in range(3,Nrows+1):
    p[n,1] = n
    for i in range(n+2):
        p[n,i+1] = (p[n-1,i]+p[n-1,i+1])%7


def algo(N):
    v = 0
    c = 0
    GM = 1
    SUM7 = 1+2+3+4+5+6+7
    M = 1
    ROW = 1
    G7 = 1
    S=[0,1,3,6,10,15,21,28]
    while ROW < N:
        ROW += 7
        if ROW >= N:
            v += S[ROW%7] * GM
            break
        else:
            v += SUM7 * M
        M += GM
        if ROW == 7 * M:
            GM += 1
            M = GM
    return v
    
for N in range(5,200,8):
    print("N = ", N, "  algo: ", algo(N))

# exit(1)

def rowksum(K):
    if K == 0:
        return "0"
    prod = 1
    while K > 0:
        prod *= (K % 7 + 1)
        K //= 7
    return prod

cnt = 0
for n in range(1,Nrows+1):
    row7 = 0
    for k in range(1,n+2):
        if (p[n,k] < 0): 
            print("OVERFLOW at n,k: ", n, k)
            exit(1)

        #print(p[n,k]," ",end="")
        if p[n,k] != 0: 
            cnt += 1
            row7 += 1
        
    print("Row: ", n, "  7's: ", row7, n-row7, rowksum(n-1))
NumEntries = Nrows * (Nrows + 1) // 2
print("Of the ", NumEntries, "numbers in the pascal table of ", Nrows, "rows, there are")
print(cnt, "values not divisible by 7 and ", NumEntries-cnt, "that are divisible by 7")

