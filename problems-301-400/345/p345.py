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

    
# To maximize, we minimize the negative of the matrix
row_ind, col_ind = linear_sum_assignment(-matrix)

selected_sum = matrix[row_ind, col_ind].sum()

print("Selected positions (row, col):")
for r, c in zip(row_ind, col_ind):
    print(f"  Row {r} → Col {c}  =  {matrix[r][c]}")

print(f"Maximum sum: {selected_sum}")
