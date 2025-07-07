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
        #print("a: ", a, datetime.now(), flush=True)
        for b in range(1, 27):
            if a == b: continue
            #print("b: ", b, datetime.now(), flush=True)
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
                                    print(a,',',b,',',c,',',d,',',e,',',f,',',g,',')
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

#    for i in range(1, 27):
#        print(i, B[i], C[i], D[i], E[i], F[i], G[i])
#    print(sum(B), sum(C), sum(D), sum(E), sum(F), sum(G))
    for l in range(1, 7):
        for r in range(1, 7):
            print(l, r, LR[l][r])
#    for a in LR: print(a, " : ", sum(a))
    return sum(B)+sum(C)+sum(D)+sum(E)+sum(F)+sum(G)
    
#
# This function is counting the cases where l < K-1
#
# l,r < K
# last > l
#
# <------- A ------------>     <------- B ------>
# __ __ __ __ __ __ __ _l_ _K_ _r_ __ __ __ __ __
#
# want to find the number of decreasing sequences from the set P = {1, 2, ..., 26} - {used numbers}
# where {used numbers} is l, K, r, and the B-1 numbers used by the decreasing sequence from r
#
# The numbers we have available for the 'rest of A' are the numbers {26, 25, ..., l+1}
#
# There are some numbers that need to be excluded depending on l
#    Case 1: l < r
#        we remove l, l + 1, ..., r - 1, r and K which is r - l + 1  + 1 (K) numbers
#        = r - l + 2
#        so the number of choices for 'rest of A' are (26 - (l+1) + 1) - (r - l + 2)
#        = 24 - r
#
#        set A = choose(24 - r, A - 1)
#        set B = choose(r - 1, B - 1)  # we have to exclude numbers
#
#    Case 2: l > r
#         we remove l, l+1, ..., K, which is K - l + 1 numbers
#         so the number of choices for the 'rest of A' are (26 - (K - l + 1) numbers
#         = 25 - K + l
# 
# 
# used = count of numbers used to right of last
# K is the TRANSITION number  
#
'''
def decSeqs(A, l, K, r, B):
    if l == r: return 0
    elif l < r:
        Right = choose(r - 3, B - 1)
    else:
        Right = choose(r - 2, B - 1)
    s = choose(26 - l, A - 1) * choose(r - 1, B - 1)
    #
    # create sets for numbers to left of l, called, t, where
    # t < r, l < t < K, and t > K
    #
    for t in range(1, K):  # all posible numbers for t, creating {l + t}
        n = l + t
        if n == r: continue
        if n >= K: continue
        #
        # A - t is the size of the numbers to fill in with numbers 
        sizeT = 26 - (t + 1) - (B + 2) + 1
        if l+t < r:
            Right = choose(r - 2 - t, B - 1)
        elif l+t > r:
            Right = choose(r - 3, B - 1)
        Left = choose(sizeT, A - 1 - t)
        Middle = choose(l - t, t)
        print("t: ", t, "  Left: ", Left, "  Middle: ", Middle, "  Right: ", Right)
        s += Left * Middle * Right
    return s
'''

def decSeqs(A, l, K, r, B):
    if l == r: return 0

    s = choose(26 - l, A - 1) * choose(r - 1, B - 1)
    #
    # create sets for numbers to left of l, called, t, where
    # t < r, l < t < K, and t > K
    #
    for t in range(1, K):  +# all posible numbers for t, creating {l + t}
        elif l < r:
            Right = choose(r - 3, B - 1)
        else:
            Right = choose(r - 2, B - 1)
        n = l + t
        if n == r: continue
        if n >= K: continue
        #
        # A - t is the size of the numbers to fill in with numbers 
        sizeT = 26 - (t + 1) - (B + 2) + 1
        if l+t < r:
            Right = choose(r - 2 - t, B - 1)
        elif l+t > r:
            Right = choose(r - 3, B - 1)
        Left = choose(sizeT, A - 1 - t)
        Middle = choose(l - t, t)
        print("t: ", t, "  Left: ", Left, "  Middle: ", Middle, "  Right: ", Right)
        s += Left * Middle * Right
    return s


K = 7
m = 4
A = 3
B = 3
sv = 0
for l in range(1,K):
    print("*******  l: ", l, " ******************")
    for r in range(1,K):
        print(l, r, decSeqs(A, l, K, r, B))
        '''
        if l == r: continue
        # if l > r:
            # #
            # # if there is any room between l and K, we have some choices
            # # also, if r is much less
            # extra = max(0, K - l - 1)
        if l < r:
            Bcombos = choose(r - 2, B - 1)
            tot = choose(26 - K, A - 1) * Bcombos
            print("total: ", tot)
            #
            # add the l+1 to r-1 
            # r, l and this new number take up 3 choices, thus, r - 3 choose B - 1 for the right
            l2r = max(0, r - l - 1) * choose(26 - B - 3, A - 2) * choose(r - 3, B - 1)
            if l2r: print("l2r: ", l2r)
            tot += l2r
            #
            # add the r+1 to K-1
            for Q in range(r+1, K):
                toChooseFrom = B + 3 + Q - r
                totx = choose(26-toChooseFrom, A-2) * Bcombos
                tot += totx
                print("Q: ", Q, "  totx: ", totx, " tot:", tot)
            print("l<r:: l: ", l, "  r: ", r,  "  v: ", tot)
            
        else: # l > r
            #
            # to left of l, all numbers bigger than K is 26 - K is choose(26-K,A-1)
            # and to right of r is choose(r-1,B-1)
            tot = choose(26 - K, A - 1) * choose(r - 1, B - 1)
            for j in range(l+1, K):
                tot += choose(26-l,A-2) * choose(r - 1, B - 1)
            print("l>r:: l: ", l, "  r: ", r, "  v: ", tot)
            sv += tot
        '''

print("Sum: ", sv)
#d7 = doseven()
#print("All seven char combos: ", d7)

'''
# <------- A ------>      <----- B ----->
# ___ ___ ___ ___ _l_ _K_ _r_ ___ ___ ___
#
# <--- 26 - K -->
# <- 26-K+n-->   n in range of 1 to l - r + 1
#     and
# <- 26-K+n-->   n in range of l+1 to K-1
#    
#
if l < r
    # right side combos are 
    rs = choose(r - 2, B - 1)
    # left side combos are
    ls = choose(26 - K, A - 1)
    tot = rs * ls
    # need to add the options left of l
    # which means there are A-2 holes to fill
    # reducing by 1 our choices as we cycle thru numbers from
    # l+1 to K-1
    for n in range(1, l - r):
        tot += choose(26 - K - n, A - 2) * rs
else:  # l > r
    #
    # just like above, where we 
        
'''
       
