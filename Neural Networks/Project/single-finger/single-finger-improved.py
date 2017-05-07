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

def printDistinguish(text):
    print "\n**--**"
    print str(text)
    print "**--**\n"

def larger_model(no_of_classes, rows, columns):
    model = Sequential()
    model.add(ZeroPadding2D((1,1),input_shape=(1, rows, columns)))
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

    model.add(Flatten())
    model.add(Dense(256, activation='relu'))
    model.add(Dropout(0.5))
    model.add(Dense(256, activation='relu'))
    model.add(Dropout(0.5))
    model.add(Dense(no_of_classes, activation='softmax'))
    learning_rate=0.1
    decay_rate=learning_rate/epochs
    momentum=0.9
    sgd=SGD(lr=learning_rate,momentum=momentum,decay=decay_rate,nesterov=False)
    
    model.compile(loss='sparse_categorical_crossentropy', optimizer='sgd', metrics=['accuracy'])
    return model

K.set_image_dim_ordering('th') #?

# input image dimensions
img_rows, img_cols = 224, 224

# number of channels
img_channels = 1
epochs=1

printDistinguish("EPOCHS: "+str(epochs))

# data
data_paths = ['fut', 'lum' , 'sec']
data_processed_paths = ['fut-p', 'lum-p', 'sec-p']
cls_no = len(data_paths)

printDistinguish("DATA PATHS: "+str(data_paths))
printDistinguish("DATA PROCESSED PATHS: "+str(data_processed_paths))
printDistinguish("NO OF CLASSES: "+str(cls_no))

files = []
samples_no = []
total_samples_no = 0

for clsi in range(cls_no):
    files.append(os.listdir(data_paths[clsi]))
    samples_no.append(size(files[clsi]))
    total_samples_no = total_samples_no + samples_no[clsi]

printDistinguish("NO OF SAMPLES: "+str(samples_no)+"\nTOTAL: "+str(total_samples_no))

for clsi in range(cls_no):
    printDistinguish("INPUT FILES OF CLASS "+str(clsi)+":\n"+str(files[clsi]))

for clsi in range(cls_no):
    for file in files[clsi]:
        img = Image.open(data_paths[clsi] + '/' + file)  
        img = img.resize((img_rows,img_cols))
        gray = img.convert('L')

        # need to do some lume processing here          
        gray.save(data_processed_paths[clsi] +'/' + file.split(".")[0], format="JPEG")

processed_files = []
matrices = []

for clsi in range(cls_no):
    processed_files.append(os.listdir(data_processed_paths[clsi]))
    matrices.append(array([array(Image.open(data_processed_paths[clsi] + '/' + img_i)).flatten() for img_i in processed_files[clsi]],'f'))

for clsi in range(cls_no):
    printDistinguish("PROCESSED FILES OF CLASS "+str(clsi)+":\n"+str(processed_files[clsi]))

for clsi in range(cls_no):
    printDistinguish("MATRIX OF CLASS "+str(clsi)+":\n"+str(matrices[clsi]))

concatenated_matrix = matrices[0]

for clsi in range(1, cls_no):
    concatenated_matrix = numpy.concatenate((concatenated_matrix, matrices[clsi]), axis=0)

printDistinguish("CONCATENATED MATRIX:\n"+str(concatenated_matrix))

labels=numpy.ones((total_samples_no,),dtype = int)

temp_count = 0
for clsi in range(cls_no):
    if clsi == 0:
        labels[0:samples_no[clsi]] = clsi
    elif clsi == (cls_no-1):
        labels[temp_count:] = clsi
    else:
        labels[temp_count:(temp_count+samples_no[clsi])] = clsi
    temp_count = temp_count + samples_no[clsi]

printDistinguish("LABELS:\n"+str(labels))

data, labels = shuffle(concatenated_matrix, labels, random_state=2)

#train_data = [data, labels]
#printDistinguish("TRAIN DATA:\n"+str(train_data))
#(data_points, data_labels) = (train_data[0],train_data[1])

train_data, test_data, train_labels, test_labels = train_test_split(data, labels, test_size=0.2, random_state=2)

printDistinguish("TRAIN DATA:\n"+str(train_data))
printDistinguish("TRAIN LABELS:\n"+str(train_labels))

printDistinguish("TEST DATA:\n"+str(test_data))
printDistinguish("TEST LABELS:\n"+str(test_labels))

train_data = train_data.reshape(train_data.shape[0], 1, img_rows, img_cols)
printDistinguish("TRAIN DATA AFTER RESHAPING:\n"+str(train_data))

test_data = test_data.reshape(test_data.shape[0], 1, img_rows, img_cols)
printDistinguish("TEST DATA AFTER RESHAPING:\n"+str(test_data))

# Save the test images in a file for displaying in the browser
size = test_data.shape[0]
for imgn in range(size):
    img = Image.fromarray(test_data[imgn][0])
    img = img.convert('L')
    img.save('test-image' +'/' +  str(imgn), "JPEG")

# Data preprocessing
train_data = train_data.astype('float32')
test_data = test_data.astype('float32')

train_mean = numpy.mean(train_data) # for finding the mean for centering  to zero
train_data -= train_mean
test_data -= train_mean

# convert class vectors to binary class matrices
train_labels_categorical = np_utils.to_categorical(train_labels, cls_no)
test_labels_categorical = np_utils.to_categorical(test_labels, cls_no)

printDistinguish("TRAINS LABELS AFTER TO CATEGORICAL:\n"+str(train_labels_categorical))
printDistinguish("TEST LABELS AFTER TO CATEGORICAL:\n"+str(test_labels_categorical))

# build the model
model = larger_model(cls_no, img_rows, img_cols)
train_labels = train_labels.reshape((-1, 1))

printDistinguish("TRAIN LABELS AFTER RESHAPING:\n"+str(train_labels))

printDistinguish("model fit")

# Fit the model
model.fit(train_data, train_labels, validation_data=(test_data, test_labels), batch_size=40, nb_epoch=epochs, verbose=2)

printDistinguish("model fit")

# Final evaluation of the model
scores = model.evaluate(test_data, test_labels, verbose=0)

printDistinguish(str(model.metrics_names) + "\n" + str(scores))

#print "%s: %.2f%%" % str(model.metrics_names[1], scores[1]*100)

predicted_labels = model.predict(test_data)
printDistinguish("PREDICTED LABELS:\n"+str(predicted_labels))

predicted_labels = numpy.argmax(predicted_labels, axis=1)
printDistinguish("PREDICTED LABELS ARGMAX:\n"+str(predicted_labels))

p = model.predict_proba(test_data)
target_names = ['class 0(fut)', 'class 1(lum)', 'class 2(sec)']

printDistinguish("CONFUSION MATRIX:\n"+str(confusion_matrix(numpy.argmax(test_labels_categorical, axis=1), predicted_labels)))

# serialize model to JSON
model_json = model.to_json()
with open("model.json", "w") as json_file:
    json_file.write(model_json)

# serialize weights to HDF5 and saving the weights
model.save_weights("model.h5")

# load json and create model
json_file = open('model.json', 'r')
loaded_model_json = json_file.read()
json_file.close()
loaded_model = model_from_json(loaded_model_json)

# load weights into new model
loaded_model.load_weights("model.h5")

# evaluate loaded model on test data
loaded_model.compile(loss='sparse_categorical_crossentropy', optimizer='adam', metrics=['accuracy'])
score = loaded_model.evaluate(test_data, test_labels, verbose=0)
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
    if(test_labels[file]== 0):
        actual = "fut"
    elif (test_labels[file]== 1):
        actual = "lum"
    elif (test_labels[file]== 2):
        actual = "sec"

    if(predicted_labels[file]== 0):
        predict = "fut"
    elif(predicted_labels[file]== 1):
        predict = "lum"
    elif(predicted_labels[file]== 2):
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