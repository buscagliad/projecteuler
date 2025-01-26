
import numpy as np

HORIZ = 3
VERT = 2

grid = set()


def init(g):
    for h in range(0, HORIZ*2+1, 2):
        for v in range(0, VERT*2+1, 2):
            g.add((h,v))
    for h in range(1, HORIZ*2+1, 2):
        for v in range(1, VERT*2+1, 2):
            g.add((h,v))

init(grid)

print(grid)
print(len(grid))

def counthv(hor, ver):
    hv = 0
    for h in range(0, hor*2 + 1, 2):
        for v in range(0, ver*2+1, 2):
            hv += ( (hor*2 - h)//2 ) * ( (ver*2 - v)//2 )
    return hv

def countslant(hor, ver):
    hv = 0
    for h in range(1, hor*2, 2):
        for v in range(1, ver*2, 2):
            hv += ( (hor*2 + 1 - h)//2 ) * ( (ver*2 + 1 - v)//2 )
    return hv

for h in range(1, HORIZ+1):
    for v in range(1, VERT+1):
        print("HORIZ: ", h, "  VERT: ", v, "  counthv: ", counthv(h,v), "   countsland: ", countslant(h,v))
