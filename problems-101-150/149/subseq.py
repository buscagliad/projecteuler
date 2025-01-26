import numpy as np
ROW = 2000
COL = 2000
ENTRIES = ROW*COL
s = [0] * (ENTRIES)
v = [0] * ROW

def max_subarray_sum(arr):
    """
    Finds the maximum sum of a subarray using Kadane's algorithm.

    Args:
        arr (list): The input array.

    Returns:
        int: The maximum sum found.
    """

    # Handle empty arrays
    if not arr:
        return 0

    max_current = max_global = arr[0]

    for num in arr[1:]:
        max_current = max(num, max_current + num)
        max_global = max(max_global, max_current)

    return max_global


for k in range(ENTRIES):
    if k <= 55:
        s[k] = (100003 - 200003 * k + 300007 * k  * k * k) % 1000000 - 500000
    else:
        s[k] = (s[k-24] + s[k-55] + 1000000) % 1000000 - 500000


def getrow(row):
    global s, v
    i = 0
    for k in range(COL * row, COL * (row+1)):
        v[i] = s[k]
        i += 1
    return v
    
def getcol(col):
    global s, v
    i = 0
    for k in range(col, ENTRIES, ROW):
        v[i] = s[k]
        i += 1
    return v

def zerov():
    global v
    for i in range(COL):
        v[i] = 0

def getdiag(row, col):
    global s, v
    i = 0
    k = row * ROW + col
    zerov()
    while row < ROW and col < COL:
        v[i] = s[k]
        row -= 1
        col += 1
        k = row * ROW + col
        i += 1
    return v
    

def getantidiag(row, col):
    global s, v
    i = 0
    k = row * ROW + col
    zerov()
    while row < ROW and col < COL:
        v[i] = s[k]
        row += 1
        col -= 1
        k = row * ROW + col
        i += 1
    return v

maxval = 0
##
## do rows first
##
for row in range(ROW):
    maxval = max(maxval, max_subarray_sum(getrow(row)))

##
## do columns next
##
for col in range(COL):
    maxval = max(maxval, max_subarray_sum(getcol(col)))

##
## do diagonals
##
for k in range(COL):
    maxval = max(maxval, max_subarray_sum(getdiag(0,k)))
    maxval = max(maxval, max_subarray_sum(getdiag(k,COL)))
    maxval = max(maxval, max_subarray_sum(getantidiag(0,k)))
    maxval = max(maxval, max_subarray_sum(getantidiag(k,0)))

print(maxval)
