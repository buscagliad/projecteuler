from datetime import datetime


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
    for a in range(1, 27):
        print("a: ", a, datetime.now(), flush=True)
        for b in range(1, 27):
            if a == b continue
            print("b: ", b, datetime.now(), flush=True)
            for c in range(1, 27):
                if b == c or a == c: continue
                for d in range(1, 27):
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
    return sum(B)+sum(C)+sum(D)+sum(E)+sum(F)+sum(G)

d7 = doseven()
print("All seven char combos: ", d7)
