import numpy as np
a = np.array([[1,2], [3,4]])
b = np.array([1,2])
x = np.linalg.solve(a, b)
print x