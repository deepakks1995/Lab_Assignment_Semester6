
import sys
import math
from random import uniform, randint
import matplotlib.pyplot as plt
import numpy as np

# Variables Initialization Space
model_complexity = 10
size_sample = 100
_min_limit_ = 0
_max_limit_ = 10
_intrinsic_noise = 0.2567
_dividing_ratio_ = 0.75
data = []
data_xaxis = []
data_yaxis = []
model_complexity += 1
#	...

def _solve_first_question():
	
	_max_ = 0
	#data.sort()

	fig = plt.figure("Original Function")
	fig_ax1 = fig.add_subplot(111)
	
	fig_ax1.plot(data_xaxis,data_yaxis,'ro')
	fig_ax2 = fig.add_subplot(111)
	fig_x = np.arange(_min_limit_,_max_limit_,0.0001)
	fig_y = np.sin(fig_x)
	fig_ax2.plot(fig_x, fig_y)

	for itr in range(15):
		if _max_ < data[itr]:
			_max_ = data[itr]
	fig2 = plt.figure("Error ")
	ax1 = fig2.add_subplot(111)
	ax1.plot(data_xaxis[:15], data_yaxis[:15],'ro')
	ax2 = fig2.add_subplot(111)
	x = np.arange(_min_limit_,_max_, 0.0001)
	y = np.sin(x)
	ax2.plot(x,y)
	for itr in range(15):
		ax3 = fig2.add_subplot(111)
		lines = ax3.plot([data_xaxis[itr], data_xaxis[itr] ], [data_yaxis[itr], math.sin(data[itr]) ])
		lines[0].set_color('red')
	#plt.show()

def solve_second_question():
	cons = np.zeros((model_complexity))
	for j in range(model_complexity):
		sum = 0
		for n in range(len(data_xaxis)):
			sum += data_yaxis[n] * (data_xaxis[n]**j)
		cons[j] = sum
	coeff = np.zeros((model_complexity, model_complexity))
	for j in range(model_complexity):
		for i in range(model_complexity):
			sum = 0
			for itr in range(len(data_yaxis)):
				sum += data_xaxis[itr]**(i+j)
			coeff[j][i] = sum
	solution = np.linalg.solve(coeff, cons)
	print solution

	fig1 = plt.figure("Estimated Function")
	fig1_ax1 = fig1.add_subplot(111)
	
	fig1_ax1.plot(data_xaxis,data_yaxis,'ro')
	fig1_ax2 = fig1.add_subplot(111)
	fig1_x = np.arange(_min_limit_,_max_limit_,0.0001)
	fig1_y = np.sin(fig1_x)
	fig1_ax2.plot(fig1_x, fig1_y)
	y = []
	x = np.arange(_min_limit_,_max_limit_,0.001)
	for itr in range(len(x)):
		sum = 0
		for i in range(model_complexity):
			sum += solution[i] * (x[itr]**i)
		y.append(sum)

	fig1_ax3 = fig1.add_subplot(111)
	fig1_ax3.set_ylim(-1, 2)
	fig1_ax3.plot(x,y)
	plt.show()


def main():

	for itr in range(size_sample):
		data.append(uniform(_min_limit_, _max_limit_))
	for itr in range(int(size_sample*_dividing_ratio_)):
		if randint(0,100)%2 == 0:
			data_yaxis.append(math.sin(data[itr]) + _intrinsic_noise)
		else:
			data_yaxis.append(math.sin(data[itr]) - _intrinsic_noise)
		data_xaxis.append(data[itr])
	# _solve_first_question()
	solve_second_question()

if __name__ == '__main__':
	main()

