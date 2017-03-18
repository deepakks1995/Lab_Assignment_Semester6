import randomFunc
import numpy as np
import math

'''
*	This function gives value corresponding to discriminant function
*	given the mean vector, x as input values, sigma vector, and 
*	probablitiy of class i
*	author: Deepak
'''
def get_discriminant(x, mean, sigma, probability):
	inverse_cov_matrix = []
	x_minus_u_matrix = []
	x_minus_u_transpose_matrix = []
	determinant = 1;
	cov_matrix = (sigma if isinstance(sigma[0], list) else randomFunc.generate_diagnol_matrix(sigma)) if isinstance(sigma, list) else quit()
	for i in range(len(sigma)):
		inverse_cov_matrix.append(np.zeros(len(sigma)))
		inverse_cov_matrix[i][i] = 1/cov_matrix[i][i]
		determinant *= x[i]
		x[i] -= mean[i]
	x_minus_u_transpose_matrix.append(x)
	temp_matrix = np.matmul(x_minus_u_transpose_matrix, inverse_cov_matrix)
	for i in range(len(sigma)):
		x_minus_u_matrix.append([])
		x_minus_u_matrix[i].append(x[i])
	ans = np.matmul(temp_matrix, x_minus_u_matrix)
	ans *= (-0.5)
	ans = ans - (len(sigma)/2)*np.log(2*math.pi) - ( 0.5 * np.log(determinant) ) + np.log(probability)
	return ans

# if __name__=="__main__":
# 	x = [1,2,3,4,5]
# 	mean = [1,2,3,4,5]
# 	sigma = [1,2,3,4,5]
# 	probability = 0.5
# 	print get_discriminant(x, mean, sigma, probability)

