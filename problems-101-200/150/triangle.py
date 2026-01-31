import numpy as np
ROW = 1000
COL = 1000
ENTRIES = 500500
# ROW = 10
# COL = 10
# ENTRIES = 55
MOD = 2**20
SUB = 2**19
s = [0] * (ENTRIES)
sums = np.zeros([ROW,COL], dtype = int)


def init():
    global s
    t=0
    for k in range(ENTRIES):
        t = (615949*t + 797807) % MOD
        s[k] = t - SUB


def initx():
    global s, ENTRIES, ROW, COL
    t=0
    ENTRIES = 21
    ROW = COL = 6
    s =         [15,
              -14, -7,
            20,  -13,  -5,
        -3,     8,   23,  -26,
      1,    -4,    -5,  -18,   5,
    -16,  31,   2,     9,    28,   3]

def trinum(n):
    return n * (n + 1) // 2
    
init()

def rcmap(row, col):
    return row * (row+1) // 2 + col
    
# for row in range(10):
    # for col in range(row+1):
        # print(row, col, rcmap(row,col))
# exit(1)
##
## returns the sum of s[k]
## at row (row + nrow) 
## starting at column col thru col+nrow
def gettri(row, col, nrow):
    global s
    v = 0
    k = rcmap(row+nrow, col)
    #print("gettri:  row: ", row, "  col: ", col, " nrow: ", nrow, "  k: ", k, end ="")
    for c in range(nrow+1):
        v += s[k+c]
    #print("  sum: ", v)
    return v

##
## returns the sum of s[k]
## for the triangele with point at row, col
## extending below for nrow's
##
def sumtri(row, col, nrow):
    global s
    v = 0
    for nr in range(nrow+1):
        k = rcmap(row+nr, col)
        #print("gettri:  row: ", row, "  col: ", col, " nrow: ", nrow, "  k: ", k, end ="")
        for c in range(nr+1):
            v += s[k+c]
        #print("  sum: ", v)
    return v


# k = 0
# for r in range(ROW):
    # for c in range(r+1):
        # sums[r][c] = s[k]
        # k += 1

# for n in range(ROW,1, -1):
    # t = n * (n+1) // 2
    # print("sum(sk): ", sum(s[:t]))
    # print("sumtri: ", sumtri(0,0,n-1))

def printsum(sx):
    for r in range(ROW):
        for c in range(r+1):
            print(sx[r][c], " ",end="")
            #sums[r][c] = s[k]
        print()

minval = 0
##
## do rows first
##
done = False
nrow = 1
# while not done:
    # nrow += 1
def minrc(sx):
    mr = 0
    mc = 0
    mv = 55555555555555555550
    for r in range(ROW):
        for c in range(r+1):
            if sx[r][c] < mv:
                mr = r
                mc = c
                mv = sx[r][c]
    return mv, mr, mc

#printsum(sums)
#print("sums--> ", sums[0][0])
#for nrow in range(1,ROW+1):
for nrow in range(ROW+1):
    print("Attempting row: ", nrow, flush=True)
    for row in range(ROW-nrow):
        for col in range(row+1):
            a = gettri(row,col,nrow)
            #print(row, col, a, sums[row][col], " --> ", end="")

            sums[row][col] += a
            #print(sums[row][col])
    #printsum(sums)
    mv, mrow, mcol = minrc(sums)
    if mv < minval:
        minval = mv
        print("Minvalue: ", minval, " found at row/col: ", mrow, mcol, " nrows: ", nrow, " --> ", sumtri(mrow,mcol,nrow))


print(minval)
