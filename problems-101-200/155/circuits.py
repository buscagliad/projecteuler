
DEBUG= False

'''
We first start by identifying all possible values
that can be formed by N resistors, sg[N] is that
set of values.
Clearly, SG[1] = 1
Then we start building up in values of N, noting (in general)
SG[K] = SG[K-1] - we start with all the previous values created
SG[K] += SG[m] (*) SG[l]  for all l+m = K
With the operator (*) combining each element from SG[m] and
SG[l] both is series and parallel
At the end of this, we reduce SG[K] to remove redundant elements

The final answer will be the SG[18]


'''

def same(a, b):
    delta = abs(a-b)
    if delta < 1e-14: return True
    return False


def compressed(g):
    g.sort()
    last = g[0]
    rg = [g[0]]
    for r in g:
        if same(last, r): continue
        last = r
        rg.append(r)
    return rg    

def sumseriesANDparallel(A, B):
    if DEBUG: print("A:", A)
    if DEBUG: print("B:", B)
    AB = []
    for a in A:
        for b in B:
            p = 1.0/(1.0/a + 1.0/b)
            s = a + b
            if DEBUG: print("a, b, p, s: ", a, b, p, s)
            AB.append(p)
            AB.append(s)
    if DEBUG: print("AB: ", AB)
    return AB



    
sg = [[],[1]]
MaxNumberOfResistors = 18
for N in range(2, MaxNumberOfResistors+1):
    if DEBUG: print("********", N, "********************")
    g = [N, 1/N]
    for a in sg[N-1]: g.append(a)
    for m in range(1, N//2+1):
        l = N - m
        if DEBUG: print("N, l, m", N, l, m)
        sp = sumseriesANDparallel(sg[l], sg[m])
        for a in sp: g.append(a)
    if DEBUG: print("len(sp): ", len(sp))
    sg.append(compressed(g))
    if DEBUG: print("N, sg[N]:", N, sg[N])
    
               
csum = 0
debug = False
for R in range(1, MaxNumberOfResistors+1):
    #if R == MaxNumberOfResistors: debug = True
    print(R, len(sg[R]))

## Incorrect>>> Total number of recips:  356950   unique:  356201
## Incorrect>>> Total number of recips:  356951   unique:  20838
## Correct answer is: 3857447
