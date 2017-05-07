import numpy
from keras.models import Sequential
from keras.layers import Dense
from keras.layers import Dropout
from keras.layers import Flatten
from keras.layers.convolutional import Convolution2D
from keras.layers.convolutional import MaxPooling2D
from keras.layers.convolutional import ZeroPadding2D
from keras.utils import np_utils
from keras.optimizers import SGD,RMSprop,adam
from keras import backend as K
from keras.models import model_from_json
import matplotlib.pyplot as plt
import matplotlib
import os
import os.path
import theano
from PIL import Image
from numpy import *
from sklearn.metrics import classification_report,confusion_matrix
from sklearn.utils import shuffle
from sklearn.cross_validation import train_test_split

K.set_image_dim_ordering('th')

# input image dimensions
img_rows, img_cols = 128, 128

# number of channels
img_channels = 1
epochs=8

#%%
#  data
path1_fut = 'fut'    #path of folder of ear images    
path2_fut_processed ='fut-p'  #path of folder to save ear images
path1_lum = 'lum'    #path of folder of fkp images
path2_lum_processed ='lum-p'  #path of folder to save fkp images
path1_sec = 'sec'    #path of folder of iris images
path2_sec_processed ='sec-p'  #path of folder to save iris images

list_fut = os.listdir(path1_fut)
list_lum = os.listdir(path1_lum)
list_sec = os.listdir(path1_sec)

fut_samples = size(list_fut)
lum_samples = size(list_lum)
sec_samples = size(list_sec)
num_samples = fut_samples + lum_samples + sec_samples
print num_samples

# save the processed ear images
for file in list_fut:
    im = Image.open(path1_fut + '/' + file)  
    img = im.resize((img_rows,img_cols))
    gray = img.convert('L')
                #need to do some lume processing here          
    gray.save(path2_fut_processed +'/' + file.split(".")[0], format="JPEG")

# save the processed fkp images
for file in list_lum :
    im = Image.open(path1_lum + '/' + file)  
    img = im.resize((img_rows,img_cols))
    gray = img.convert('L')
                #need to do some lume processing here          
    gray.save(path2_lum_processed +'/' + file.split(".")[0], format="JPEG")

# save the processed iris images
for file in list_sec:
    im = Image.open(path1_sec + '/' + file)  
    img = im.resize((img_rows,img_cols))
    gray = img.convert('L')
                #need to do some lume processing here          
    gray.save(path2_sec_processed +'/' + file.split(".")[0], format="JPEG")


#Processing for ear images
fut_imlist = os.listdir(path2_fut_processed)
print fut_imlist
fut_im1 = array(Image.open(path2_fut_processed + '/' + fut_imlist[0])) # open one ear image to get size
fut_m,fut_n = fut_im1.shape[0:2] # get the size of the ear images
fut_imnbr = len(fut_imlist) # get the number of ear images

# create matrix to store all flattened ear images
fut_immatrix = array([array(Image.open(path2_fut_processed + '/' + fut_im2)).flatten()
              for fut_im2 in fut_imlist],'f')


#Processing for fkp images
lum_imlist = os.listdir(path2_lum_processed)
print lum_imlist
lum_im1 = array(Image.open(path2_lum_processed + '/' + lum_imlist[0])) # open one ear image to get size
lum_m,lum_n = lum_im1.shape[0:2] # get the size of the ear images
lum_imnbr = len(lum_imlist) # get the number of ear images

# create matrix to store all flattened ear images
lum_immatrix = array([array(Image.open(path2_lum_processed + '/' + lum_im2)).flatten()
              for lum_im2 in lum_imlist],'f')


sec_imlist = os.listdir(path2_sec_processed)
print sec_imlist
sec_im1 = array(Image.open(path2_sec_processed + '/' + sec_imlist[0])) # open one ear image to get size
sec_m,sec_n = sec_im1.shape[0:2] # get the size of the ear images
sec_imnbr = len(sec_imlist) # get the number of ear images

# create matrix to store all flattened ear images
sec_immatrix = array([array(Image.open(path2_sec_processed + '/' + sec_im2)).flatten()
              for sec_im2 in sec_imlist],'f')


# Combining each matrix
immatrix = numpy.concatenate((fut_immatrix, lum_immatrix), axis=0)
immatrix = numpy.concatenate((immatrix, sec_immatrix), axis=0)


label=numpy.ones((num_samples,),dtype = int)
label[0:99]=0
label[100:199]=1
label[200:]=2

data,Label = shuffle(immatrix,label, random_state=2)
train_data = [data,Label]

(X, y) = (train_data[0],train_data[1])
# number of output classes
nb_classes = 3
# STEP 1: split X and y into training and testing sets

X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=2)
X_train = X_train.reshape(X_train.shape[0], 1, img_rows, img_cols)
X_test = X_test.reshape(X_test.shape[0], 1, img_rows, img_cols)


# Save the test images in a file for displaying in the browser
size = X_test.shape[0]
for imgn in range(size):
    img = Image.fromarray(X_test[imgn][0])
    img = img.convert('L')
    img.save('test-image' +'/' +  str(imgn), "JPEG")


# Data preprocessing
X_train = X_train.astype('float32')
X_test = X_test.astype('float32')
mean1 = numpy.mean(X_train) # for finding the mean for centering  to zero
X_train -= mean1
X_test -= mean1
# convert class vectors to binary class matrices
Y_train = np_utils.to_categorical(y_train, nb_classes)
Y_test = np_utils.to_categorical(y_test, nb_classes)


def larger_model():
	# create model
    model = Sequential()
    model.add(ZeroPadding2D((1,1),input_shape=(1,img_rows,img_cols)))
    model.add(Convolution2D(32, 3, 3, activation='relu'))
    model.add(ZeroPadding2D((1,1)))
    model.add(Convolution2D(32, 3, 3, activation='relu'))
    model.add(MaxPooling2D((2,2), strides=(2,2)))

    model.add(ZeroPadding2D((1,1)))
    model.add(Convolution2D(64, 3, 3, activation='relu'))
    model.add(ZeroPadding2D((1,1)))
    model.add(Convolution2D(64, 3, 3, activation='relu'))
    model.add(MaxPooling2D((2,2), strides=(2,2)))

    model.add(ZeroPadding2D((1,1)))
    model.add(Convolution2D(128, 3, 3, activation='relu'))
    model.add(ZeroPadding2D((1,1)))
    model.add(Convolution2D(128, 3, 3, activation='relu'))
    model.add(ZeroPadding2D((1,1)))
    model.add(Convolution2D(128, 3, 3, activation='relu'))
    model.add(MaxPooling2D((2,2), strides=(2,2)))

##    model.add(ZeroPadding2D((1,1)))
##    model.add(Convolution2D(512, 3, 3, activation='relu'))
##    model.add(ZeroPadding2D((1,1)))
##    model.add(Convolution2D(512, 3, 3, activation='relu'))
##    model.add(ZeroPadding2D((1,1)))
##    model.add(Convolution2D(512, 3, 3, activation='relu'))
##    model.add(MaxPooling2D((2,2), strides=(2,2)))
##
##    model.add(ZeroPadding2D((1,1)))
##    model.add(Convolution2D(512, 3, 3, activation='relu'))
##    model.add(ZeroPadding2D((1,1)))
##    model.add(Convolution2D(512, 3, 3, activation='relu'))
##    model.add(ZeroPadding2D((1,1)))
##    model.add(Convolution2D(512, 3, 3, activation='relu'))
##    model.add(MaxPooling2D((2,2), strides=(2,2)))

    model.add(Flatten())
    model.add(Dense(256, activation='relu'))
    model.add(Dropout(0.5))
    model.add(Dense(256, activation='relu'))
    model.add(Dropout(0.5))
    model.add(Dense(nb_classes, activation='softmax'))
    learning_rate=0.1
    decay_rate=learning_rate/epochs
    momentum=0.9
    sgd=SGD(lr=learning_rate,momentum=momentum,decay=decay_rate,nesterov=False)
	
# Compile model
    model.compile(loss='sparse_categorical_crossentropy', optimizer='sgd', metrics=['accuracy'])
    return model

# build the model
model = larger_model()
y_train = y_train.reshape((-1, 1))
# Fit the model
model.fit(X_train, y_train, validation_data=(X_test, y_test),batch_size=40, nb_epoch=epochs, verbose=2)
# Final evaluation of the model
scores = model.evaluate(X_test, y_test, verbose=0)
print "%s: %.2f%%" % (model.metrics_names[1], scores[1]*100)

# Confusion Matrix



Y_pred = model.predict(X_test)
print(Y_pred)
y_pred = numpy.argmax(Y_pred, axis=1)
print(y_pred)
p=model.predict_proba(X_test) # to predict probability
target_names = ['class 0(fut)', 'class 1(lum)','class 2(sec)']
#print(classification_report(numpy.argmax(Y_test,axis=1), y_pred,target_names=target_names))
print(confusion_matrix(numpy.argmax(Y_test,axis=1), y_pred))

# serialize model to JSON
model_json = model.to_json()
with open("model.json", "w") as json_file:
    json_file.write(model_json)
# serialize weights to HDF5 and saving the weights
model.save_weights("model.h5")
print("Saved model to disk")
# load json and create model
json_file = open('model.json', 'r')
loaded_model_json = json_file.read()
json_file.close()
loaded_model = model_from_json(loaded_model_json)
# load weights into new model
loaded_model.load_weights("model.h5")
print("Loaded model from disk")
# evaluate loaded model on test data
loaded_model.compile(loss='sparse_categorical_crossentropy', optimizer='adam', metrics=['accuracy'])
score = loaded_model.evaluate(X_test, y_test, verbose=0)
print "%s: %.2f%%" % (loaded_model.metrics_names[1], score[1]*100)


# Save the output in the html file for displaying in browser
path2 ='test-image'
listing = os.listdir(path2)
f = open('image.html','w')
message="""<html>
<body>"""
for file in listing:
    actual = ""
    predict = ""
    path= path2 + "/" + file
    file=int(file)
    if(y_test[file]== 0):
        actual = "fut"
    elif (y_test[file]== 1):
        actual = "lum"
    elif (y_test[file]== 2):
        actual = "sec"

    if(y_pred[file]== 0):
        predict = "fut"
    elif(y_pred[file]== 1):
        predict = "lum"
    elif(y_pred[file]== 2):
        predict = "sec"    
    message += """<figure>
<p style="float: left; font-size: 9pt; text-align: center; width: 18%; margin-right: 2%; margin-bottom: 0.5em;">
<img src=""" + path + " " + """alt="Mountain View" style="width: 100%">
<caption> true class = """ + actual + "," + " " + """predicted class=""" + predict +  """</caption></p>
</figure>"""
message += """</body>
    </html>"""
f.write(message)
f.close()




