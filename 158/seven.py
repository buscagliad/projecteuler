from datetime import datetime
from math import comb
import numpy as np


def choose(n, k):
    if k == 0: return 1
    if n <= 0: return 0
    if k <= 0: return 0
    if n < k: return 0
    return comb(n, k)

def dothree():
    B = [0]*27
    C = [0]*27
    for c in range(1, 27):
        for a in range(1, 27):
            for b in range(1, 27):
                    # continue if any two are equal
                    if a == b or a == c or b == c : continue
                    # slot B is big element
                    # a < B > c > d
                    if a < b and b > c :
                        B[b] += 1
     
                    # slot C is big element
                    # a > b < C > d
                    elif a > b and b < c :
                        C[c] += 1
                    
    for i in range(1, 27):
        print(i, B[i], C[i])
    print(sum(B), sum(C))
    return sum(B) + sum(C)
    
def dofour():
    B = [0]*27
    C = [0]*27
    D = [0]*27   
    for a in range(1, 27):
        for b in range(1, 27):
            for c in range(1, 27):
                for d in range(1, 27):
                    # continue if any two are equal
                    if (a == b or a == c or a == d or
                        b == c or b == d or c == d) : continue
                    # slot B is big element
                    # a < B > c > d
                    if a < b and b > c and c > d :
                        B[b] += 1
     
                    # slot C is big element
                    # a > b < C > d
                    elif a > b and b < c and c > d:
                        C[c] += 1
                    # slot D is big element
                    # a > b > c < D
                    elif a > b and b > c and c < d:
                        #if d == 23:
                        #    print(a, b, c, d)
                        D[d] += 1
    for i in range(1, 27):
        print(i, B[i], C[i], D[i])
    print(sum(B), sum(C), sum(D))
    return sum(B)+sum(C)+sum(D)

def dofive():
    B = [0]*27
    C = [0]*27
    D = [0]*27   
    E = [0]*27   
    for a in range(1, 27):
        for b in range(1, 27):
            for c in range(1, 27):
                for d in range(1, 27):
                    for e in range(1, 27):
                        # continue if any two are equal
                        if (a == b or a == c or a == d or a == e or
                            b == c or b == d or b == e or
                            c == d or c == e or d == e) : continue
                        # slot B is big element
                        # a < B > c > d > e
                        if a < b and b > c and c > d and d > e :
                            B[b] += 1
         
                        # slot C is big element
                        # a > b < C > d > e
                        elif a > b and b < c and c > d and d > e:
                            C[c] += 1
                        # slot D is big element
                        # a > b > c < D > e
                        elif a > b and b > c and c < d and d > e:
                            #if d == 23:
                            #    print(a, b, c, d)
                            D[d] += 1
                        # a > b > c > d < E
                        elif a > b and b > c and c > d and d < e:
                            #if d == 23:
                            #    print(a, b, c, d)
                            E[e] += 1
    for i in range(1, 27):
        print(i, B[i], C[i], D[i], E[i])
    print(sum(B), sum(C), sum(D), sum(E))
    return sum(B)+sum(C)+sum(D)+sum(E)


def doseven():
    B = [0]*27
    C = [0]*27
    D = [0]*27   
    E = [0]*27   
    F = [0]*27   
    G = [0]*27
    LR = np.zeros([8,8], dtype=int)
    for a in range(1, 27):
        print("a: ", a, datetime.now(), flush=True)
        for b in range(1, 27):
            if a == b: continue
            print("b: ", b, datetime.now(), flush=True)
            for c in range(1, 27):
                if b == c or a == c: continue
                #for d in range(1, 27):
                for d in range(7,8):
                    if d == a or d == b or d == c: continue
                    for e in range(1, 27):
                        if e == a or e == b or e == c or e == d: continue
                        for f in range(1, 27):
                            if f == a or f == b or f == c or f == d or f == e: continue
                            for g in range(1, 27):
                                if g == a or g == b or g == c or g == d or g == e or g == f: continue
                                
                                # slot B is big element
                                # a < B > c > d > e > f > g
                                if a < b and b > c and c > d and d > e and e > f and f > g:
                                    B[b] += 1
                 
                                # slot C is big element
                                # a > b < C > d > e > f > g
                                elif a > b and b < c and c > d and d > e and e > f and f > g:
                                    C[c] += 1
                                # slot D is big element
                                # a > b > c < D > e > f > g
                                elif a > b and b > c and c < d and d > e and e > f and f > g:
                                    #if d == 23:
                                    #    print(a, b, c, d)
                                    D[d] += 1
                                    LR[c][e] += 1
                                # a > b > c > d < E > f > g
                                elif a > b and b > c and c > d and d < e and e > f and f > g:
                                    #if d == 23:
                                    #    print(a, b, c, d)
                                    E[e] += 1
                                # a > b > c > d > e > F > g
                                elif a > b and b > c and c > d and d > e and e < f and f > g:
                                    #if d == 23:
                                    #    print(a, b, c, d)
                                    F[f] += 1
                                # a > b > c > d > e > f > G
                                elif a > b and b > c and c > d and d > e and e > f and f < g:
                                    #if d == 23:
                                    #    print(a, b, c, d)
                                    G[g] += 1

    for i in range(1, 27):
        print(i, B[i], C[i], D[i], E[i], F[i], G[i])
    print(sum(B), sum(C), sum(D), sum(E), sum(F), sum(G))
    for l in range(1, 7):
        for r in range(1, 7):
            print(l, r, LR[l][r])
    for a in LR: print(a, " : ", sum(a))
    return sum(B)+sum(C)+sum(D)+sum(E)+sum(F)+sum(G)

K = 7
m = 4
A = 3
B = 3
sv = 0
for l in range(1,K):
    print("*******  l: ", l, " ******************")
    for r in range(1,K):
        if l == r: continue
        # if l > r:
            # #
            # # if there is any room between l and K, we have some choices
            # # also, if r is much less
            # extra = max(0, K - l - 1)
        if r > l:
            extra = K - l - 1 - B
            v = choose(26 - K + extra, A - 1) * choose(r - 2, B - 1)
            #v += choose(26 - K - 1, A - 1) * choose(r - 1, B - 1)
            print("l<r:: r: ", r, "  l: ", l, "  v: ", v)
            sv += v
        else: # l > r
            extra = K - r - 1
            lesser = l - r - 1
            v = choose(26 - K + extra, A - 1) * choose(r - 1 - lesser, B - 1)
            print("l>r:: r: ", r, "  l: ", l, "  v: ", v)
            sv += v

print("Sum: ", sv)
#d7 = doseven()
#print("All seven char combos: ", d7)
