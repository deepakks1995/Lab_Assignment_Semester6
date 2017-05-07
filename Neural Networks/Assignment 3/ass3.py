from resnet50 import ResNet50
from keras.preprocessing import image
from keras.layers import *
from keras.layers.core import Flatten, Dense, Dropout
from keras.models import Sequential,Model
from imagenet_utils import preprocess_input, decode_predictions
import numpy as np
import os
import random                                                                                                                                                                                                                                                                   

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
    new_layer2 = Dense(7,activation="softmax")(new_layer1)
    model_1 = Model(input=model.input, output=[new_layer2])
    model_1.compile(optimizer="adam", loss='categorical_crossentropy',metrics=['accuracy'])
    model_1.summary()
    data_folder = "/training_data"
    class_folders = os.listdir(os.getcwd()+data_folder)
    training_data = {}
    for i in range(7):
        training_data[i] = []
    for name in sorted(class_folders):
        y = int(name[5])-1 #for 0 based indexing
        # print "class: ",y," data being procesed"
        y_ = np.zeros(7) #7 classes
        y_[y] = 1
        # print "class: ",y_," data being procesed"
        for img_name in os.listdir(os.getcwd()+data_folder+'/'+name):
            img_path = os.getcwd()+data_folder+'/'+name+"/"+img_name
            x = get_img(img_path).reshape(224,224,3)
            training_data[y].append(x)
    # now training for every class
    class_weight = {}
    total_samples = 0.0
    for i in range(7):
        total_samples += len(training_data[i])
    for y in range(7):
        y_ = np.zeros(7)
        y_[y] = 1
        class_weight[y] = len(training_data[y])/total_samples
        
        print class_weight[y],' No. of samples:',len(training_data[y])
    X_=[]
    Y_=[]
    for y in range(7):
        y_ = np.zeros(7)
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

    model_1.fit(np.array(_X_),np.array(_Y_),epochs=2,verbose=1,shuffle=True,validation_split=0.1,class_weight=class_weight) 