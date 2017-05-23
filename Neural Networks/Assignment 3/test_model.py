
from resnet50 import ResNet50
from keras.preprocessing import image
from keras.layers import *
from keras.layers.core import Flatten, Dense, Dropout
from keras.models import Sequential,Model
from imagenet_utils import preprocess_input, decode_predictions
from sklearn.cross_validation import train_test_split
from sklearn.metrics import classification_report, confusion_matrix
from keras.utils import np_utils
from keras.models import model_from_json
from PIL import Image
import splitImages as split
import numpy as np
import os
import random   

epochs = 20

def printDistinguish(text):
    print "\n**--**"
    print str(text)
    print "**--**\n"

def plot_model(history):
	split.add_plotting_data([[_, itr] for (_, itr) in zip(range(len(history.history['acc'])), history.history['acc'])], 'ro-', 'red', 'train')
	split.add_plotting_data([[_, itr] for (_, itr) in zip(range(len(history.history['val_acc'])), history.history['val_acc'])], 'ro-', 'blue', 'test')
	split.plot_curve("Model_Acc_vs_Val_Acc", False, ['Epochs', 'Accuracy'])

	split.add_plotting_data([[_, itr] for (_, itr) in zip(range(len(history.history['loss'])), history.history['loss'])], 'ro-', 'red', 'train')
	split.add_plotting_data([[_, itr] for (_, itr) in zip(range(len(history.history['val_loss'])), history.history['val_loss'])], 'ro-', 'blue', 'test')
	split.plot_curve("Model_Loss_vs_Val_loss", False, ['Epochs', 'Loss'])

def model():
	model = ResNet50(weights='imagenet')
	model.layers.pop()
	for layer in model.layers:
		layer.trainable=False	
	new_layer1 = Dropout(0.4)(model.layers[-1].output)
	new_layer2 = Dense(3,activation="softmax")(new_layer1)
	model_1 = Model(input=model.input, output=[new_layer2])
	model_1.compile(optimizer="adam", loss='categorical_crossentropy',metrics=['accuracy'])
	model_1.summary()
	return model_1

def calc_precision_and_recall(conf_matrix):
	target_names = ['Fut', 'Lum', 'Sec']
	for i in range(3):
		print "Precision for class" + target_names[i],
		sum = 0.0
		for j in range(3):
			sum = sum + conf_matrix[i][j]
		precision_class = conf_matrix[i][i] / sum
		print ": " + str(precision_class)

	for i in range(3):
		print "Recall for class" + target_names[i],
		sum = 0.0
		for j in range(3):
			sum = sum + conf_matrix[j][i]
		recall_class = conf_matrix[i][i] / sum
		print ": " + str(recall_class)


if __name__ == '__main__':
	global epochs
	
	train_data, test_data, train_labels, test_labels, class_weight = split.split_train_test_data(1, 'training_data-dev', 'testPath')
	for i in range(len(train_data)):
		train_data[i] = np.expand_dims(train_data[i], axis=0)
		train_data[i] = preprocess_input(train_data[i])
		train_data[i] = train_data[i].reshape(224,224,3)
	for i in range(len(test_data)):
		test_data[i] = np.expand_dims(test_data[i], axis=0)
		test_data[i] = preprocess_input(test_data[i])
		test_data[i] = test_data[i].reshape(32,32,3)

	json_file = open('model_79_acc_70_val.json', 'r')
	model_1 = json_file.read()
	json_file.close()
	model_1 = model_from_json(model_1)
	model_1.load_weights("model.h5")
	model_1.compile(optimizer="adam", loss='categorical_crossentropy',metrics=['accuracy'])

	scores = model_1.evaluate(np.array(test_data), np.array(test_labels), verbose=0)

	# plot_model(history)

	print (str(model_1.metrics_names) + "\n" + str(scores) + "\n")

	predicted_labels = model_1.predict(np.array(test_data))
	
	predicted_labels = np.argmax(predicted_labels, axis=1)

	conf_matrix = confusion_matrix(np.argmax(test_labels, axis=1), predicted_labels)

	printDistinguish("CONFUSION MATRIX:\n"+ str(conf_matrix) )

	calc_precision_and_recall(conf_matrix) 

	# test_labels_generated = []
	# for list in test_labels:
	# 	if list[0] == 1:
	# 		test_labels_generated.append(0)
	# 	elif list[1] == 1:
	# 		test_labels_generated.append(1)
	# 	elif list[2] == 1:
	# 		test_labels_generated.append(2)
	# 	elif list[3] == 1:
	# 		test_labels_generated.append(3)
	# 	elif list[4] == 1:
	# 		test_labels_generated.append(4)
	# 	elif list[5] == 1:
	# 		test_labels_generated.append(5)
	# 	else:
	# 		test_labels_generated.append(6)

	# test_path = "testPath"
	# listings = os.listdir(test_path)
	# f = open('image.html','w')
	# message="""<html><body>"""
	# for file in listings:
	# 	actual = ""
	# 	predict = ""
	# 	path= test_path + "/" + file
	# 	file=int(file)
	# 	if(test_labels_generated[file]== 0):
	# 		actual = "Class1"
	# 	elif (test_labels_generated[file]== 1):
	# 		actual = "Class2"
	# 	elif (test_labels_generated[file]== 2):
	# 		actual = "sec"

	# 	if(predicted_labels[file]== 0):
	# 		predict = "fut"
	# 	elif(predicted_labels[file]== 1):
	# 		predict = "lum"
	# 	elif(predicted_labels[file]== 2):
	# 		predict = "sec"
	# 	if predict != actual:
	# 		message += """<figure>
	# 		<p style="float: left; font-size: 9pt; text-align: center; width: 18%; margin-right: 2%; margin-bottom: 0.5em;">
	# 		<img src=""" + path  + " " + """alt="Mountain View" style="width: 100%">
	# 		<caption> true class = """ + actual + "," + " " + """predicted class=""" + predict +  """</caption></p>
	# 		</figure>"""
	# message += """</body></html>"""
	# f.write(message)
	# f.close()