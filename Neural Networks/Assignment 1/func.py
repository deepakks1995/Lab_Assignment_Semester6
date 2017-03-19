import numpy

'''
* This program is for deciding which function is to be estimated
* This function also decides the intrinsic noise
* author : Amanshu Raikwar
'''

MAX_Y = 1
MIN_Y = -1
INTRINSIC_NOISE = 0.2
def f(x):
	return numpy.sin(x/100)