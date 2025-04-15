import math

debug = False

BN = 1000
N = BN//2+1

data=[0]*(N+1)


def findab(n):
    sa = 0
    comma = False
    for a in range(1, n):
        for b in range(1, n):
            an = a * n
            bn = b * n
            ab = a*a + b*b
            if (an // ab) * ab == an:
                if (bn // ab) * ab == bn:
                    #print(a, " + ", b, "i  ", a, " - ", b,"i")
                    if debug:
                        if comma: print(",", sep="", end="")
                        print("(", a, ",", b, ")", sep="", end="")
                    sa += 2 * a
                    comma = True
                    data[a] += 1
                    #print(a, " appending ", n, data[a])
    if debug: print()
    return sa

suma = 0
for n in range(1, N+1):
    if debug: print(n, ",", end="")
    suma += findab(n)

k = 0
print(suma)
for i in range(1,N+1):
    if debug: print(i, data[i])
    k += 2 * i * data[i]
print(k)
