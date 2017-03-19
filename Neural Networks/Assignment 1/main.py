import sys
import numpy
import matplotlib.pyplot as plt
import math
import func

'''
* this is a program to run Simple Model for estimating a function
* run : python main.py <complexity> <training-points-file> <test-points-file> -1
* author :ff Amanshu Raikwar
'''

MIN_X = 0
MAX_X = 2000
plotVerticalPadding = 1
ORIGINAL_GRAPH_LINE_COLOR = "#1B5E20"
ESTIMATED_GRAPH_LINE_COLOR = "#B71C1C"
POINT_COLOR = "#FF9800"
POINT_EDGE_COLOR = "#212121"
GRAPH_LINE_LEAST_COUNT = 0.1

#getting intrinsic noise from func file
intrinsicNoise = func.INTRINSIC_NOISE

#function for getting list of Y values given W vector and list of X values
def getY(W,sampleX):
	sampleY = numpy.zeros(len(sampleX), dtype = numpy.float)
	for i in range(len(sampleX)):
		temp = 0
		for j in range(len(W)):
			temp += W[j] * math.pow(sampleX[i], j)
		sampleY[i] = temp
	return sampleY

fig=plt.figure()
subplot=fig.add_subplot(111)

#model complexity
M = int(sys.argv[1])

#file names containing training points and test points
trainFileName = sys.argv[2]
testFileName = sys.argv[3]

trainPoints = []
testPoints = []

#reading training file
with open(trainFileName) as curFile:
	content = curFile.read().splitlines()
	for linei in range(len(content)):
		value=content[linei].split(" ")
		trainPoints.append([float(value[0]), float(value[1])])
		subplot.plot(
			float(value[0]), 
			float(value[1]),
			color=POINT_COLOR,
			marker="o",
			markeredgecolor=POINT_EDGE_COLOR)

noOfTrainPoints = len(trainPoints)
trainPoints = numpy.array(trainPoints)

#reading test file
with open(testFileName) as curFile:
	content = curFile.read().splitlines()
	for linei in range(len(content)):
		value=content[linei].split(" ")
		testPoints.append([float(value[0]), float(value[1])])

noOfTestPoints = len(testPoints)
testPoints = numpy.array(testPoints)

coeff = numpy.zeros((M+1, M+1), dtype = numpy.float)
cons = numpy.zeros(M+1, dtype = numpy.float)

#getting coefficients of equations
for j in range(M+1):	
	tempCons = 0
	for n in range(0, noOfTrainPoints):
		tempCons = tempCons + trainPoints[n][1]*math.pow(trainPoints[n][0], j)
	cons[j] = tempCons

	for i in range(M+1):
		tempCoeff = 0
		for n in range(0, noOfTrainPoints):
			tempCoeff = tempCoeff + math.pow(trainPoints[n][0], i+j)	
		coeff[j][i] = tempCoeff

#soliving equations to get W vector
W = numpy.linalg.solve(coeff, cons)

#plotting graphs
sampleX = numpy.arange(MIN_X, MAX_X, GRAPH_LINE_LEAST_COUNT)
estimatedFxLine, = subplot.plot(sampleX, getY(W, sampleX), 'k', color=ESTIMATED_GRAPH_LINE_COLOR, linewidth=2)
actualFxLine, = subplot.plot(sampleX, func.f(sampleX), 'k', color=ORIGINAL_GRAPH_LINE_COLOR, linewidth=2)

plt.legend([actualFxLine, estimatedFxLine], ["Original f(x)", "Estimated f(x)"])

subplot.set_xlabel("x")
subplot.set_ylabel("y")

plt.axis(
	[MIN_X, MAX_X,
	func.MIN_Y-intrinsicNoise-plotVerticalPadding,
	func.MAX_Y+intrinsicNoise+plotVerticalPadding])

#calculating training error
temp = 0
tempY = getY(W, trainPoints[:,0])

for i in range(len(trainPoints)):
	temp = temp + math.pow(trainPoints[i][1] - tempY[i], 2)

temp = numpy.sqrt(temp/noOfTrainPoints)
trainError = math.ceil(temp*10000)/10000

#calculating test error
temp = 0
tempY = getY(W, testPoints[:,0])

for i in range(len(testPoints)):
	temp = temp + math.pow(testPoints[i][1] - tempY[i], 2)

temp = numpy.sqrt(temp/noOfTestPoints)
testError = math.ceil(temp*10000)/10000

#printing appropriate values for use in other programs
if int(sys.argv[4]) == 0:
	print str(M)+" "+str(trainError)+" "+str(testError)
elif int(sys.argv[4]) == 1:
	print str(noOfTestPoints + noOfTrainPoints)+" "+str(trainError)+" "+str(testError)

#adding text info to plot
subplot.text(
	40,
	func.MIN_Y-intrinsicNoise-plotVerticalPadding+0.1,
	"MODEL_COMPLEXITY:"
	+str(M)
	+"\n"
	+"TRAINING_ERROR:"
	+str(trainError)
	+" "
	+"TEST_ERROR:"
	+str(testError)
	+"\n"
	+"TRAINING_DATA_POINTS:"
	+str(noOfTrainPoints)
	+" "
	+"TEST_DATA_POINTS:"
	+str(noOfTestPoints))

#saving plot as a .png file
fig.savefig(
	"outputs/simpleModel("
	+str(noOfTrainPoints)
	+", "
	+str(noOfTestPoints)
	+", "
	+str(M)
	+").png")