import randomFunc
import discriminantFunc as disc
import numpy as np
import matplotlib.pyplot as plt
import math

data_classA = []
data_classB = []
mean_classA = [0,0]
mean_classB = [1, 1]
sigma_classA = [0.1,0.2]
sigma_classB = [0.2, 0.1]
plotting_data = []
plotting_type = []
plotting_color = []

'''
*	This function is to generate data from a  
*	gaussian distribution given variance and mean
*	author: Deepak
'''
def generate_data():
	global data_classA, data_classB
	data_classA = randomFunc.generate_N_random(mean_classA, sigma_classA, 2, 100)
	data_classB = randomFunc.generate_N_random(mean_classB, sigma_classB, 2, 100)
	add_plotting_data(data_classA, 'ro', 'red')
	add_plotting_data(data_classB, 'ro', 'blue')
	plot_curve()

'''
*	This function is to plot curves with different types
*	author: Deepak
'''
def plot_curve():
	global plotting_data
	for i in range(len(plotting_data)):
		x = y = []
		x = [itr[0].tolist() for itr in plotting_data[i]]
		y = [itr[1].tolist() for itr in plotting_data[i]]
		plt.plot(x,y,plotting_type[i], color=plotting_color[i])
	plt.show()
	return True

'''
*	This function is to add data to a global variable
*	which is used to plot in future
*	author: Deepak
'''
def add_plotting_data(x,str,color):
	global plotting_data
	plotting_data.append(x)
	plotting_type.append(str)
	plotting_color.append(color)
	return True

'''
*	This function generates naive bayes decision boundary
*	author: Deepak
'''
def generate_naive_bayes_decision_boundary():
	pos = []
	neg = []
	for i in np.arange(-1, 2.5, 0.01):
		for j in np.arange(-1.5,2, 0.01):
			diff = disc.get_discriminant([i,j], mean_classA, sigma_classA, 0.5) - disc.get_discriminant([i,j], mean_classB, sigma_classB, 0.5)
			if  diff >= 0:
				pos.append([i,j])
			else:
				neg.append([i,j])
	add_plotting_data(pos, '.', 'black')
	add_plotting_data(neg, '.', 'white')
	generate_data()

if __name__ == "__main__":
	generate_naive_bayes_decision_boundary()