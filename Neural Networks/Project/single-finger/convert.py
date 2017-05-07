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


# K.set_image_dim_ordering('th') #?

# input image dimensions
img_rows, img_cols = 224, 224

# number of channels
img_channels = 1
epochs=1


# data
data_paths = ['fut-1000', 'lum-1000' , 'sec-1000']
data_processed_paths = ['fut1', 'lum2', 'sec3']
cls_no = len(data_paths)


files = []
samples_no = []
total_samples_no = 0

for clsi in range(cls_no):
    files.append(os.listdir(data_paths[clsi]))
    samples_no.append(size(files[clsi]))
    total_samples_no = total_samples_no + samples_no[clsi]

# printDistinguish("NO OF SAMPLES: "+str(samples_no)+"\nTOTAL: "+str(total_samples_no))

# for clsi in range(cls_no):
#     printDistinguish("INPUT FILES OF CLASS "+str(clsi)+":\n"+str(files[clsi]))

for clsi in range(cls_no):
    for file in files[clsi]:
        img = Image.open(data_paths[clsi] + '/' + file)  
        img = img.resize((img_rows,img_cols))
        gray = img.convert('L')

        # need to do some lume processing here          
        gray.save('training-data/' + data_processed_paths[clsi] +'/' + file.split(".")[0], format="JPEG")

