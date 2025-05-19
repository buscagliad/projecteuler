import math

def F(b, m):
    b -= 1
    if b < m: return 0
    if b == m: return 1
    return math.comb(b, m)


tms = 0
#
# N = 4
#
# a < b > c > d
for a in range(1, 27):
    for b in range(a+1, 27):
        for c in range(1, b):
            if c == a: continue
            for d in range(1, c):
                if d == a: continue
                tms += 1

print("Combinations of a < B > c < d : ", tms)

# a > b < C > d
xyz = 0
for c in range(1, 27):
    bsum = 0
    for a in range(1, 27):
        for b in range(1, 27):
            for d in range(1, 27):
                if (a > b and b < c and c > d and
                   a != b and a != c and a != d and
                   b != c and b != d and c != d) : 
                    xyz += 1
                    bsum += 1
                    if c == 3:
                        print(a,b,c,d)
    print("c = ", c, " num: ", bsum)
print("1:: Combinations of a > b < C > d", xyz)
tms=0
# for a in range(1, 27):
    # for b in range(1, a):
        # for c in range(b+1, 27):
            # if c == a: continue
            # for d in range(1, c):
                # if d == a: continue
                # if d == b: continue
                # if a < b or b > c or c < d:
                    # print("ERROR", a, b, c, d)
                # tms += 1
# print("2:: Combinations of a > b < C > d", tms)

# a > b > c < d
for a in range(1, 27):
    for b in range(1, a):
        for c in range(1, b):
            if c == a: continue
            for d in range(c+1, 27):
                if d == a: continue
                tms += 1
print(tms)


# x = 0
# for a in range(1, 26):
    # u = 26 - a
    # x += u * (u - 1) * (u - 2)
# print(x//2)

x = 0
for a in range(1, 27):
    l = max(a-1, 26-a)
    cx = (26-a) * (a-1)* (a-1)
    x+=cx
    print("** c=", a, "  num: ", cx)
print(" a > b < C > d: ", x)
