import numpy as np
matrix = np.loadtxt("day-03.txt", dtype='str', comments=None, delimiter=None)

def tree_count(matrix, right, down): 
    trees = 0
    pos = 0
    i = 0
    while i < len(matrix):
        if matrix[i][pos] == '#':
            trees += 1
        
        pos = (pos + right) % len(matrix[i])
        i = i + down
    
    return trees

directions = [[1, 1], [3, 1], [5, 1], [7, 1], [1, 2]]
product = 1
for d in directions:
    product *= tree_count(matrix, d[0], d[1])

print(product) 


