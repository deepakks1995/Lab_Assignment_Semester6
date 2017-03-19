from random import uniform
import numpy as np
import math

'''
*	This function is to convert a 1-d array
*	to a 2-d diagnol array
*	author: Deepak
'''
def generate_diagnol_matrix(singular):
	array = np.zeros((len(singular), len(singular)))
	for i in range(0,len(singular)):
		array[i][i] = singular[i];
	return array

'''
*	This function is to return a value
*	corresponding to a pseudo random number in gaussian distribution
*	author: Deepak
'''
def norm_distribution(mean, sigma):
	return (1/math.sqrt(2*math.pi*sigma)) * (math.e ** (-( (uniform(0,1) - mean)**2)/(2*(sigma**2)) ) )

'''
*	This function is to generate a random variable
*	taking a mean vector and sigma vector either of 2-d or 1-d
*	author: Deepak
'''
def generate_random(mean, sigma, d):
	cov_matrix = generate_diagnol_matrix(sigma)
	x = np.zeros(d)
	for i in range(0,d):
		x[i] = 12*norm_distribution(0,1) - 6
	lamda, psi = np.linalg.eig(cov_matrix)
	for i in range(len(lamda)):
		lamda[i] = math.sqrt(lamda[i])
	Q = np.matmul((generate_diagnol_matrix(lamda)),psi)
	y = np.matmul(Q,x) + mean
	y = np.random.multivariate_normal(mean, cov_matrix)
	return y

'''
*	This function is to generate N random numbers from 
*	a gaussian distribution
*	author: Deepak
'''
def generate_N_random(mean, sigma, d, n):
	list = []
	for i in range(n):
		list.append(generate_random(mean, sigma, d));
	return list

# if __name__=="__main__":
# 	generate_N_random(np.array([1,2,3]), [1,2,3], 3, 5) 