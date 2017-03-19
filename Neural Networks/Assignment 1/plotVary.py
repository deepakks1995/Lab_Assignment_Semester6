import sys
import matplotlib.pyplot as plt

'''
* This program is to plot training_error and test_error against any value
* run : python plotVary.py <input-file> <x-axis-label>
* author : Amanshu Raikwar
'''
TRAIN_GRAPH_LINE_COLOR = "#1A237E"
TEST_GRAPH_LINE_COLOR = "#B71C1C"

#input file name
inputFileName = sys.argv[1]

varyVars = []
trainError = []
testError = []

#reading input file
with open(inputFileName) as curFile:
	content = curFile.read().splitlines()
	for linei in range(len(content)):
		value=content[linei].split(" ")
		varyVars.append(float(value[0]))
		trainError.append(float(value[1]))
		testError.append(float(value[2]))

fig=plt.figure()
subplot=fig.add_subplot(111)

#plotting graphs
trainErrorLine, = subplot.plot(varyVars, trainError, 'k', color=TRAIN_GRAPH_LINE_COLOR, linewidth=2)
testErrorLine, = subplot.plot(varyVars, testError, 'k', color=TEST_GRAPH_LINE_COLOR, linewidth=2)

plt.legend([trainErrorLine, testErrorLine], ["training", "test"])

subplot.set_xlabel(sys.argv[2])
subplot.set_ylabel('eRMS')

#saving plot as a .png file
fig.savefig(
	"outputs/"
	+sys.argv[2]
	+"_vs_eRMS("
	+").png")
