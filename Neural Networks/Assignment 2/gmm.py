import randomFunc
import discriminantFunc as disc
import numpy as np
import naiveBayes as naive
import matplotlib.pyplot as plt
import math

clusterA = 5
clusterB = 5
no_of_points = 100
mean_classA = [0,0]
mean_classB = [2.5, 2.5]
sigma_classA = [0.1,0.2]
sigma_classB = [0.2, 0.1]
multiplication_ratio = 0.4

'''
*	This function is to generate data from a  
*	gaussian distribution given variance and mean
*	author: Deepak
'''
def generate_data():
	size_clusterA = no_of_points//clusterA
	size_clusterB = no_of_points//clusterB

	colorA = ['#2AFB05','#4CD933', '#56CF41', '#56CF41', '#27C40B','#71FB58' ]
	colorB = ['#DD3E28','#BB6B20', '#E518B4', '#B4703B','#FB10A2', '#AA5B43']

	for i in range(clusterA):
		tmp = []
		if i!=clusterA-1:
			tmp = randomFunc.generate_N_random([x+i*multiplication_ratio for x in mean_classA], sigma_classA, 2, size_clusterA)
		else:
			tmp = randomFunc.generate_N_random([x+i*multiplication_ratio for x in mean_classA], sigma_classA, 2, no_of_points - size_clusterA*i)
		naive.add_plotting_data(tmp,'ro', colorA[i])
	
	for i in range(clusterB):
		tmp = []
		if i!= clusterB-1:
			tmp = randomFunc.generate_N_random([x+i*multiplication_ratio for x in mean_classB], sigma_classB, 2, size_clusterB)
		else:	
			tmp = randomFunc.generate_N_random([x+i*multiplication_ratio for x in mean_classB], sigma_classB, 2, no_of_points - size_clusterB*i) 
		naive.add_plotting_data(tmp, 'ro', colorB[i])
	naive.plot_curve("GMM",[-1,6,-1,6])

'''
*	This function gives difference between the discriminant 
*	functions of the two classes
*	author: Deepak
'''
def get_diff_of_dscriminant_function(i,j):
	discA = 0
	discB = 0
	for i in range(clusterA):
		discA += disc.get_discriminant([i,j], [x+i*multiplication_ratio for x in mean_classA], sigma_classA, 0.5)
	for i in range(clusterB):
		discB += disc.get_discriminant([i,j], [x+i*multiplication_ratio for x in mean_classB], sigma_classB, 0.5)
	return discA - discB

'''
*	This function generates naive bayes decision boundary
*	author: Deepak
'''
def generate_GMM_decision_boundary():
	pos = []
	neg = []
	for i in np.arange(-1, 6, 0.01):
		for j in np.arange(-1, 6, 0.01):
			diff = get_diff_of_dscriminant_function(i,j)
			if  diff >= 0:
				pos.append([i,j])
			else:
				neg.append([i,j])
	naive.add_plotting_data(pos, '.', 'black')
	naive.add_plotting_data(neg, '.', 'white')
	generate_data()

if __name__ == "__main__":
	generate_GMM_decision_boundary()