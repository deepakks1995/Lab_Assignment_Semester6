
from resnet50 import ResNet50
from keras.preprocessing import image
from keras.layers import *
from keras.layers.core import Flatten, Dense, Dropout
from keras.models import Sequential,Model
from imagenet_utils import preprocess_input, decode_predictions
from sklearn.cross_validation import train_test_split
from sklearn.metrics import classification_report, confusion_matrix
from keras.utils import np_utils
import numpy as np
import os
import random   

def printDistinguish(text):
    print "\n**--**"
    print str(text)
    print "**--**\n"


def get_img(img_path):
    img = image.load_img(img_path, target_size=(224, 224))
    x = image.img_to_array(img)
    x = np.expand_dims(x, axis=0)
    x = preprocess_input(x)
    return x

if __name__ == '__main__':
    model = ResNet50(weights='imagenet')
    model.layers.pop() # remove last layer
    for layer in model.layers:
        layer.trainable=False
    new_layer1 = Dropout(0.4)(model.layers[-1].output)
    new_layer2 = Dense(3,activation="softmax")(new_layer1)
    model_1 = Model(input=model.input, output=[new_layer2])
    model_1.compile(optimizer="adam", loss='categorical_crossentropy',metrics=['accuracy'])
    model_1.summary()
    data_folder = "/training-data"
    class_folders = os.listdir(os.getcwd()+data_folder)
    training_data = {}
    for i in range(3):
        training_data[i] = []
    for name in sorted(class_folders):
        y = int(name[3])-1 #for 0 based indexing
        # print "class: ",y," data being procesed"
        y_ = np.zeros(3) #7 classes
        y_[y] = 1
        # print "class: ",y_," data being procesed"
        for img_name in os.listdir(os.getcwd()+data_folder+'/'+name):
            img_path = os.getcwd()+data_folder+'/'+name+"/"+img_name
            x = get_img(img_path).reshape(224,224,3)
            training_data[y].append(x)
    # now training for every class
    class_weight = {}
    total_samples = 0.0
    for i in range(3):
        total_samples += len(training_data[i])
    for y in range(3):
        y_ = np.zeros(3)
        y_[y] = 1
        class_weight[y] = len(training_data[y])/total_samples
        
        print class_weight[y],' No. of samples:',len(training_data[y])
    X_=[]
    Y_=[]
    for y in range(3):
        y_ = np.zeros(3)
        y_[y] = 1
        X = training_data[y]
        Y = [y_ for _ in range(len(X))]
        for i in range(len(X)):
            X_.append(X[i])
            Y_.append(Y[i])
    shuf_indecies = [itr for itr in range(len(X_))]
    random.shuffle(shuf_indecies) # will be used to shuffle initial training data so that validation split is uniform
    _X_ = []
    _Y_ = []
    for i in shuf_indecies:
        _X_.append(X_[i])
        _Y_.append(Y_[i])
    
    cls_no = 3
    train_data, test_data, train_labels, test_labels = train_test_split(_X_, _Y_, test_size=0.4, random_state=3)

    model_1.fit(np.array(train_data),
    	np.array(train_labels),
    		epochs=10,
    			verbose=1,
    				shuffle=True,
    					batch_size=64,
    					validation_data=(np.array(test_data), np.array(test_labels)),
    						class_weight=class_weight)

    scores = model_1.evaluate(np.array(test_data), np.array(test_labels), verbose=0)
    
    predicted_labels = model_1.predict(np.array(test_data))
    
    predicted_labels = np.argmax(predicted_labels, axis=1)
    
    target_names = ['Fut', 'Lum', 'Sec']
    
    conf_matrix = confusion_matrix(np.argmax(test_labels, axis=1), predicted_labels)
    
    printDistinguish("CONFUSION MATRIX:\n"+ str(conf_matrix) )

    for i in range(3):
    	print "Precision for class " + target_names[i]
    	sum = 0.0
    	for j in range(3):
    		sum = sum + conf_matrix[i][j]
    	precision_class = conf_matrix[i][i] / sum
    	print ": " + str(precision_class) 