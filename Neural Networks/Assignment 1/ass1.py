
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
_lambda = 0.545
cal_training_errors = False
errors_ytraining = []
errors_xtraining = []
data_yaxis_testing = []
data_xaxis_testing = []
errors_ytesting = []
errors_xtesting = []
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

def solve_equations(data_x,data_y):
	cons = np.zeros((model_complexity))
	for j in range(model_complexity):
		sum = 0
		for n in range(len(data_x)):
			sum += data_y[n] * (data_x[n]**j)
		cons[j] = sum
	coeff = np.zeros((model_complexity, model_complexity))
	for j in range(model_complexity):
		for i in range(model_complexity):
			sum = 0
			for itr in range(len(data_y)):
				sum += data_x[itr]**(i+j)
			coeff[j][i] = sum
			if i == j:
				coeff[j][i] += _lambda
	solution = np.linalg.solve(coeff, cons)
	return solution

def solve_rest_question():
	
	global data_xaxis, data_yaxis, data_yaxis_testing, data_xaxis_testing
	# print solution
	solution = solve_equations(data_xaxis, data_yaxis)
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
	
def cal_errors():
		global data_yaxis, data_xaxis, data_xaxis_testing,data_yaxis_testing
		solution = solve_equations(data_xaxis_testing, data_yaxis_testing)
		sum = 0
		for n in range(len(data_yaxis_testing)):
			temp = 0
			for j in range(model_complexity):
				temp += solution[j] * (data_xaxis_testing[n] ** j)
			temp = data_yaxis_testing[n] - temp
			sum += temp ** 2
		sum /= len(data_xaxis_testing)
		errors_ytesting.append(math.sqrt(sum))
		errors_xtesting.append(model_complexity)

		solution1 = solve_equations(data_xaxis, data_yaxis)
		sum = 0
		for n in range(len(data_yaxis)):
			temp = 0
			for j in range(model_complexity):
				temp += solution1[j] * (data_xaxis[n] ** j)
			temp = data_yaxis[n] - temp
			sum += temp ** 2
		sum /= len(data_xaxis)
		errors_ytraining.append(math.sqrt(sum))
		errors_xtraining.append(model_complexity)
		return sum

def plot_errors(errors_x, errors_y,errors_x1,errors_y1, name):
	fig1 = plt.figure(name)
	fig1_ax1 = fig1.add_subplot(111)
	line1, = fig1_ax1.plot(errors_x, errors_y, label="Training")

	fig_ax2 = fig1.add_subplot(111)
	line2, = fig1_ax1.plot(errors_x1, errors_y1, label="Testing")
	fig1.legend([line1, line2], ['Training', 'Testing'])
	plt.show()

def main():

	global cal_training_errors
	global model_complexity
	for itr in range(size_sample):
		data.append(uniform(_min_limit_, _max_limit_))

	for itr in range(size_sample):
		if itr < int(size_sample*_dividing_ratio_):
			if randint(0,100)%2 == 0:
				data_yaxis.append(math.sin(data[itr]) + _intrinsic_noise)
			else:
				data_yaxis.append(math.sin(data[itr]) - _intrinsic_noise)
			data_xaxis.append(data[itr])
		else:
			if randint(0,100)%2 == 0:
				data_yaxis_testing.append(math.sin(data[itr]) + _intrinsic_noise)
			else:
				data_yaxis_testing.append(math.sin(data[itr]) - _intrinsic_noise)
			data_xaxis_testing.append(data[itr])
	_solve_first_question()
	solve_rest_question()

	cal_training_errors = True
	for j in range(15):
		model_complexity = j
		cal_errors()
	print errors_ytraining
	print errors_xtraining
	plot_errors(errors_xtraining, errors_ytraining,errors_xtesting,errors_ytesting,"Question 2 Errors")


if __name__ == '__main__':
	main()

