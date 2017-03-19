# how to run
# python generatePoints.py no-of-points dividing-ratio intrinsic-noise training-file-name test-file-name
# author - amanshu raikwar

import sys
import func
import random
import matplotlib.pyplot as plt
import numpy

'''
* This program generates random points according to given function and intrinsic noise in file func
* run : python generatePoints.py <total-number-of-points> <train/total-ratio> <training-data-file> <test-data-file>
* author : Amanshu Raikwar
'''

MIN_X = 0
MAX_X = 2000
plotVerticalPadding = 1
POINT_COLOR = "#FF9800"
POINT_EDGE_COLOR = "#212121"
GRAPH_LINE_COLOR = "#1B5E20"
GRAPH_LINE_LEAST_COUNT = 0.1

#total no of points
pointsNo = int(sys.argv[1])

#trainingPoints/totalPoints
dividingRatio = float(sys.argv[2])

if(dividingRatio >= 1):
	print "ERROR: invalid dividing ratio, should be less than 1"
	quit()

#intrinsic noise
intrinsicNoise = func.INTRINSIC_NOISE

#data file names
trainFileName = sys.argv[3]
testFileName = sys.argv[4]

trainFile = open(trainFileName, "w+")
testFile = open(testFileName, "w+")

trainFlag = True

fig=plt.figure()
subplot=fig.add_subplot(111)

#writing data to files
for pointi in range(0, pointsNo):	
	if trainFlag:
		if (pointi / float(pointsNo)) >= dividingRatio:
			trainFlag = False
	
	temp=random.randrange(2)
	curX = random.uniform(MIN_X,MAX_X)

	if temp == 0:
		curY = func.f(curX)+intrinsicNoise
	else:
		curY = func.f(curX)-intrinsicNoise

	if trainFlag:
		subplot.plot(curX,curY,color=POINT_COLOR,marker="o",markeredgecolor=POINT_EDGE_COLOR)
		trainFile.write(str(curX)+" "+str(curY)+"\n")
	else:
		testFile.write(str(curX)+" "+str(curY)+"\n")

#plotting graph
sampleX = numpy.arange(MIN_X, MAX_X, GRAPH_LINE_LEAST_COUNT)
subplot.plot(sampleX, func.f(sampleX), 'k', color=GRAPH_LINE_COLOR, linewidth=2)

plt.axis(
	[MIN_X, MAX_X, 
	func.MIN_Y-intrinsicNoise-plotVerticalPadding, 
	func.MAX_Y+intrinsicNoise+plotVerticalPadding])

#adding text info to plot
subplot.text(
	40, 
	func.MIN_Y-intrinsicNoise-plotVerticalPadding+0.1, 
	"INTRINSIC_NOISE:"
	+str(intrinsicNoise)
	+"\n"
	+"TRAINING_DATA_POINTS:"
	+str(int(pointsNo*dividingRatio))
	+" "
	+"TEST_DATA_POINTS:"
	+str(pointsNo - int(pointsNo*dividingRatio)))

#saving plot as a .png file
fig.savefig(
	"outputs/trainingPoints("
	+str(int(pointsNo*dividingRatio))
	+", "
	+str(pointsNo - int(pointsNo*dividingRatio))
	+").png")
