from math import comb

# def F(b, m):
    # b -= 1
    # if b < m: return 0
    # if b == m: return 1
    # return comb(b, m)

# def F(N, k, l):
    # if not (1 < k < l <= N):
        # return 0  # invalid parameters
    # total = 0
    # comb_l_1_k_1 = comb(l - 1, k - 1)  # number of ways to split sides
    # for x in range(l, N + 1):
        # total += comb(x - 1, l - 1) * comb_l_1_k_1
    # return total
    
#
# P(L) is the number of sequences formed by L
# numbers from the set {1..26} such that 
# a[1] > a[2] > ... > a[m-1] < a[m] > a[m+1] > ... > a[L]
#
# Q(l, k) is the number of decreasing sequences of length l with last value >= k
# F(l, k) is the number or decreasing sequences of lenght l with starting value <= k
# 
# P(L):
#       s = 0
#       for (m = 2 .. L)  # m is the position of the 'big' element
#           for (k = 2, ..., 26) # all possible values of k (k can NEVER be 1)
#               eQ = Q(m, k-1)
#               sk = 0
#               for nk in range(k, 27):
#                   sk += eq * F(L-m-1, k-1)
#
# Q(l, k) is the number of decreasing sequences of length l with last value <= k
#
# Let U = {26, 25, 23, ..., k} : {x : 27-j, j = 1, 2, ..., k}
#   size(U) = l
#   there are l choices for the last element, l-1 for the element to its left ...
#   and 26-l for the last, this is divided by l! to account for ordering
#   NOTE: if l < k, there are 0 such sequences
#         if l == k, there is 1, otherwise there are k choose l choices
#         
#   
#
def Q2(l, k):
    if k < 0 : rv = 0
    #elif k < l: rv = 0
    else:
        s = 0
        for t in range(1, 25):
            #if 25 - t < 1: continue
            s += comb(25-t, l-1)
        rv = s
    #print("Q(",l,",",k,") = ", rv)
    return rv

def Q(l, k):
    if k < 0 : rv = 0
    #elif k < l: rv = 0
    else:
        s = 0
        for t in range(1, min(26,k+1)):
            #if 25 - t < 1: continue
            s += comb(25-t, l-1)
        rv = s
    #print("Q(",l,",",k,") = ", rv)
    return rv
    
    
# F(l, k) is the number or decreasing sequences of lenght l with starting value <= k
#
def F(l, k):
    #print("F l: ", l, " k: ", k)
    if l == 0: rv = 1
    elif k == 0: rv =  0
    elif k < 1: rv = 0
    elif l < 1: rv = 0
    #elif l < k: rv = 0
    else: 
        rv = comb(k, l)
        #print("F(",l,",",k,") = ", rv)
    return rv

def P(L, debug = False):
    s = 0
    for m in range(2, L+1):
        sk = 0
        #for k in range(max(L-m, 1), min(26,24+m)):
        for k in range(1, 27):
            #f = F(L-m, k -(L-m+1))
            #q = Q(m-1, k
            q1 = Q(m-1, k-2)
            f1 = F(L-m, k-1)
            q2 = Q(m-1, k-1)
            f2 = F(L-m, k-2)
            sk += q1 * f1 + q2 * f2

            if(debug): print(k, "  m: ", m, "  Q: ", q, "  F: ", f, "  s: ", q*f)
        if(debug): print("P(",L,")   m = ",m, "  sk = ",sk)
        s += sk
    return s
L = 3
s = 0
m = 2
for k in range(max(L-m, 1), 24+m):
    q = Q(m-1, k-1)
    f = F(L-m, k)
    sx = q * f
    # print(k, "  Q: ", q, "  F: ", f, "  s: ", sx)
    s += sx
print("Length 3, item at 2: ", s)

s = 0
m = 3
for k in range(max(L-m, 1), 24+m):
    q = Q(m-1, k-1)
    f = F(L-m-1, k-1)
    sx = q * f
    #print(k, "  Q: ", q, "  F: ", f, "  s: ", sx)
    s += sx
print("Length 3, item at 3: ", s)
#
# Q is checking out correctly
#
# for k in range(1, 27):
    # print(k, Q(2, k))

# for k in range(1, 27):
    # print(k, Q(3, k))
# for l in range(2, 6):
    # for k in range(10, 20):
        # print(l, k, F(l, k))

for L in range(5, 6):
    print(L, P(L, True))
exit(0)
# tms = 0
# #
# # N = 4
# #
# # a < b > c > d
# for a in range(1, 27):
    # for b in range(a+1, 27):
        # for c in range(1, b):
            # if c == a: continue
            # for d in range(1, c):
                # if d == a: continue
                # tms += 1

# print("Combinations of a < B > c < d : ", tms)

# a > b < C > d
xyz = 0
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

# d3 = dothree()
# print(" All three char combos: ", d3)
d4 = dofour()
print(" All four char combos: ", d4)
d5 = dofive()
print(" All five char combos: ", d5)

