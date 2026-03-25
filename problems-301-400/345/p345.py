import numpy as np
from scipy.optimize import linear_sum_assignment


def readmat(filename):
    first = True
    arr = []
    with open(filename, 'r') as f:
        for line in f.readlines():
            l = []
            for n in line.strip().split():
                l.append(int(n))
            #print(l)
            arr.append(l)
    return np.array(arr)
    
matrix = readmat('data.txt')

# elem: rows[], cols[], sum
# rows are rows available for summing
# cols are columns available for summing
# sum is the current sum
leastsum = 10000000000000000000
def getsum(mat, rows, cols, sursum):
    for r in range(0: len(mat[0]):
        if r in rows: continue
        for c in range(0: len(mat[0]):
            if c in cols: continue
            cursum += mat[r][c]
            if cursum > leastsum: continue
            


def minmatsum(mat):
	nrow = len(mat[0])
	ncol = len(mat)
	if nrow != ncol:
		print("ERROR - minmatsum, not a square matrix ", nrow, " x ", ncol);
		return None
	print("GOOD - minmatsum is a square matrix ", nrow, " x ", ncol);	


minmatsum(matrix)
exit(1)
# To maximize, we minimize the negative of the matrix
row_ind, col_ind = linear_sum_assignment(-matrix)

selected_sum = matrix[row_ind, col_ind].sum()

print("Selected positions (row, col):")
for r, c in zip(row_ind, col_ind):
    print(f"  Row {r} → Col {c}  =  {matrix[r][c]}")

print(f"Maximum sum: {selected_sum}")
