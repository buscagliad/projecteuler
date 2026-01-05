
import numpy as np

LIMIT = 100
a = np.zeros(2*LIMIT+1, dtype = int)


a[0] = 0
a[1] = 1
LASTX = 0
LASTY = 0
LASTY5 = 0
for n in range(1,LIMIT):
    twon = 2 * n
    twonp1 = twon + 1
    a[twon] = 2 * a[n]
    print("EVEN: ", a[twon], a[twon-2], a[twon-1], (a[twon-2] - 2 * a[twon-1]) // 3)
    # if a[twon] == twon:
        # X = twon
        # Y = sum(a[:twon+1])
        # if LASTY != 0:
            # print("EVEN:: ZERO found! ", X, Y, X//LASTX, Y-LASTY)
        # LASTX = X
        # LASTY = Y
    a[twonp1] = a[n] - 3 * a[n+1]
    # if a[twonp1] % 5*n == 0:
        # X5 = twonp1
        # Y5 = sum(a[:twonp1+1])
        # if LASTY5 != 0:
            # print("FIVE::found! ", X5, Y5, X5//LASTX5, Y5-LASTY5)
        # LASTX5 = X5
        # LASTY5 = Y5
    # if sum(a[:twon+2]) == 0:
        # print("ODD: ZERO found! ", twon+1)
    #print(a[twonp1], a[twon], (3 * a[twon]) // 2)
    print("ODD: ", a[twonp1], a[twonp1-2], a[twonp1-1])

C = 2 ** 13
print(a[C:LIMIT+1], sum(a[C:LIMIT+1]))
