import numpy as np
import matplotlib.pyplot as plt
import matplotlib.patches as mpatches
#from matplotlib import style
#style.use("ggplot")
from sklearn import svm,decomposition
from sklearn.neural_network import MLPClassifier
classBGColor = {}
classBGColor[1] = '#EC7063'
classBGColor[2] = '#A569BD'
classBGColor[3] = '#5DADE2'
classBGColor[4] = '#58D68D'

classTrainingColor = {}
classTrainingColor[1] = '#17202A'
classTrainingColor[2] = '#E74C3C'
classTrainingColor[3] = '#F1C40F'
classTrainingColor[4] = '#186A3B'

class TrainData:
	"""Training Data Class for TrainData"""
	def __init__(self, filename, classlabel):
		self.dataset = []
		self.classlabel = []


		# File io
		with open(filename) as file:
			lines = file.readlines()
		for line in lines:
			self.dataset.append(np.array(map(float,line.split())))
			self.classlabel.append(classlabel)
		

	def append(self,filename,classlabel):
		with open(filename) as file:
			lines = file.readlines()
		for line in lines:
			self.dataset.append(np.array(map(float,line.split())))
			self.classlabel.append(classlabel)

class TestData:
	def __init__(self,filename,actuallabel):
		self.dataset = []
		self.actuallabel = []
		with open(filename) as file:
			lines = file.readlines()
		for line in lines:
			self.dataset.append(np.array(map(float,line.split())))
			self.actuallabel.append(actuallabel)
		

	def append(self,filename,actuallabel):
		with open(filename) as file:
			lines = file.readlines()
		for line in lines:
			self.dataset.append(np.array(map(float,line.split())))
			self.actuallabel.append(actuallabel)

def plot(filename,deg,dim,kern,c_val):
	is1d = False
	for i in range(len(train.dataset)):
		pt = train.dataset[i]
		if(len(pt) == 1):
			pt = np.append(pt,0)
			is1d = True
		classlabel = train.classlabel[i]
		plt.plot(pt[0],pt[1],color = classTrainingColor[classlabel],marker = 'D',zorder = '3')
	# For region
	Xs = np.arange(plt.gca().get_xlim()[0],plt.gca().get_xlim()[1],(plt.gca().get_xlim()[1]-plt.gca().get_xlim()[0])/70)
	Ys = np.arange (plt.gca().get_ylim()[0],plt.gca().get_ylim()[1],(plt.gca().get_ylim()[1]-plt.gca().get_ylim()[0])/70)
	for i in Xs:
		for j in Ys:
			if(is1d):
				classlabel = clf.predict(np.array([i]).reshape(1,-1))
			else:	
				classlabel = clf.predict(np.array([i,j]).reshape(1,-1))
			plt.plot(i,j,color = classBGColor[classlabel[0]],marker = '.',zorder = '1')

	legend_handles = []
	for classlabel in set(train.classlabel):
		legend_handles.append(mpatches.Patch(color=classTrainingColor[classlabel], label=("Class "+str(classlabel))))
	plt.legend(handles=legend_handles)
	
	plt.title("SVM for C = "+str(c_val)+" Kernel = "+kern+str(deg)+" Dataset = "+filename[3:])
	plt.savefig(filename+"c="+str(c_val)+kern+str(deg)+"pca="+str(dim)+".png")
	plt.show()


print "Enter number of classes"
num_classes = int(raw_input())
files_train = {}
for i in range(1,num_classes+1):
	print "Enter filename(relative path) for ith class(training)"
	files_train[i] = raw_input().strip()
train = TrainData(files_train[1],1)

for i in xrange(2,1+num_classes):
	train.append(files_train[i],i)

files_test = {}
for i in range(1,num_classes+1):
	print "Enter filename(relative path) for ",i,"th ","class test file"
	files_test[i] = raw_input().strip()

test = TestData(files_test[1],1)
for i in xrange(2,1+num_classes):
	test.append(files_test[i],i)

print "Enter the value of C for SVM"
c_val = float(raw_input())

print "Enter the kernel type for SVM('linear','poly','rbf','sigmoid')"
kern = (raw_input().strip())
deg = int(0)
if kern=="poly":
	print "Enter Degree for poly kernel"
	deg = int(raw_input())

print "Reduce dimension by PCA? (Enter desired dimension or '0' for using original dimension)"
dim = int(raw_input())
assert(dim<len(train.dataset[0]))
##########PCA###################
if(dim>0):
	pca = decomposition.PCA(n_components=dim)
	print pca
	pca.fit(train.dataset)
	train.dataset = pca.transform(train.dataset)
	test.dataset = pca.transform(test.dataset)


print "New Dimension = ",len(train.dataset[0])

#########CLASSIFIER#############
# clf = MLPClassifier(solver='lbfgs', alpha=1e-5,hidden_layer_sizes=(100,50), random_state=1)
clf = svm.SVC(C=c_val,kernel=kern,degree = deg)
print clf.fit(train.dataset,train.classlabel)
predictedlabels = clf.predict(test.dataset)
confusion_matrix = np.zeros((num_classes,num_classes))
for i in range(len(predictedlabels)):
	actual_label = test.actuallabel[i]
	predicted_label = predictedlabels[i]
	confusion_matrix[actual_label-1][predicted_label-1]+=1

print "*********Confusion Matrix*********\n", confusion_matrix,"\n**********************************\n"
# for i in range(num_classes):
total_test_data = len(test.dataset)
acc=float(0)
for i in range(num_classes):
	acc += confusion_matrix[i][i]
acc /= float(total_test_data)
print "Accuracy = ",acc
filename = files_train[1][0:4]

##########output file##############
with open("OUTPUTS"+filename,"a") as file:
	print >>file, "*********Confusion Matrix*********\n", confusion_matrix,"\n**********************************\n"
	# for i in range(num_classes):
	total_test_data = len(test.dataset)
	acc=float(0)
	for i in range(num_classes):
		acc += confusion_matrix[i][i]
	acc /= float(total_test_data)
	print >>file, "Accuracy = ",acc
	print >>file, "SVM for C = "+str(c_val)+" Kernel = "+kern+str(deg)+" Dataset = "+filename+" PCA= "+str(dim)
	print >>file, "\n\n__________________________________________________________________________________________________\n\n"
if(len(train.dataset[0])<3):
	plot("svm"+filename,deg,dim,kern,c_val)

