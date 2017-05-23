# -*- coding: utf-8 -*-
'''ResNet50 model for Keras.
# Reference:
- [Deep Residual Learning for Image Recognition](https://arxiv.org/abs/1512.03385)
Adapted from code contributed by BigMoyan.
'''
from __future__ import print_function

import numpy as np
import warnings
import tensorflow

from keras.callbacks import LearningRateScheduler
import keras
from keras.layers import Input
from keras import layers
from keras.layers import Dense
from keras.layers import Activation
from keras.layers import Flatten
from keras.layers import Conv2D
from keras.layers import MaxPooling2D
from keras.layers import GlobalMaxPooling2D
from keras.layers import ZeroPadding2D
from keras.layers import AveragePooling2D
from keras.layers import GlobalAveragePooling2D
from keras.layers import BatchNormalization
from keras.models import Model
from keras.preprocessing import image
import keras.backend as K
from keras.utils import layer_utils
from keras.utils.data_utils import get_file
from keras.applications.imagenet_utils import decode_predictions
from keras.applications.imagenet_utils import preprocess_input
from keras.applications.imagenet_utils import _obtain_input_shape
from keras.engine.topology import get_source_inputs
from sklearn.cross_validation import train_test_split

# from resnet50 import ResNet50
from keras.preprocessing import image
from keras.layers import *
from keras.layers.core import Flatten, Dense, Dropout
from keras.models import Sequential,Model
from imagenet_utils import preprocess_input, decode_predictions
import numpy as np
import os
import random    

def identity_block(input_tensor, kernel_size, filters, stage, block):
    """The identity block is the block that has no conv layer at shortcut.

    # Arguments
        input_tensor: input tensor
        kernel_size: defualt 3, the kernel size of middle conv layer at main path
        filters: list of integers, the filterss of 3 conv layer at main path
        stage: integer, current stage label, used for generating layer names
        block: 'a','b'..., current block label, used for generating layer names

    # Returns
        Output tensor for the block.
    """
    filters1, filters2, filters3 = filters
    if K.image_data_format() == 'channels_last':
        bn_axis = 3
    else:
        bn_axis = 1
    conv_name_base = 'res' + str(stage) + block + '_branch'
    bn_name_base = 'bn' + str(stage) + block + '_branch'

    x = Conv2D(filters1, (1, 1), name=conv_name_base + '2a')(input_tensor)
    x = BatchNormalization(axis=bn_axis, name=bn_name_base + '2a')(x)
    x = Activation('relu')(x)

    x = Conv2D(filters2, kernel_size,
               padding='same', name=conv_name_base + '2b')(x)
    x = BatchNormalization(axis=bn_axis, name=bn_name_base + '2b')(x)
    x = Activation('relu')(x)

    x = Conv2D(filters3, (1, 1), name=conv_name_base + '2c')(x)
    x = BatchNormalization(axis=bn_axis, name=bn_name_base + '2c')(x)

    x = layers.add([x, input_tensor])
    x = Activation('relu')(x)
    return x


def conv_block(input_tensor, kernel_size, filters, stage, block, strides=(2, 2)):
    """conv_block is the block that has a conv layer at shortcut

    # Arguments
        input_tensor: input tensor
        kernel_size: defualt 3, the kernel size of middle conv layer at main path
        filters: list of integers, the filterss of 3 conv layer at main path
        stage: integer, current stage label, used for generating layer names
        block: 'a','b'..., current block label, used for generating layer names

    # Returns
        Output tensor for the block.

    Note that from stage 3, the first conv layer at main path is with strides=(2,2)
    And the shortcut should have strides=(2,2) as well
    """
    filters1, filters2, filters3 = filters
    if K.image_data_format() == 'channels_last':
        bn_axis = 3
    else:
        bn_axis = 1
    conv_name_base = 'res' + str(stage) + block + '_branch'
    bn_name_base = 'bn' + str(stage) + block + '_branch'

    x = Conv2D(filters1, (1, 1), strides=strides,
               name=conv_name_base + '2a')(input_tensor)
    x = BatchNormalization(axis=bn_axis, name=bn_name_base + '2a')(x)
    x = Activation('relu')(x)

    x = Conv2D(filters2, kernel_size, padding='same',
               name=conv_name_base + '2b')(x)
    x = BatchNormalization(axis=bn_axis, name=bn_name_base + '2b')(x)
    x = Activation('relu')(x)

    x = Conv2D(filters3, (1, 1), name=conv_name_base + '2c')(x)
    x = BatchNormalization(axis=bn_axis, name=bn_name_base + '2c')(x)

    shortcut = Conv2D(filters3, (1, 1), strides=strides,
                      name=conv_name_base + '1')(input_tensor)
    shortcut = BatchNormalization(axis=bn_axis, name=bn_name_base + '1')(shortcut)

    x = layers.add([x, shortcut])
    x = Activation('relu')(x)
    return x


def identity_block_preactive(input_tensor, kernel_size, filters, stage, block):

    filters1, filters2, filters3 = filters
    
    if K.image_data_format() == 'channels_last':
        bn_axis = 3
    else:
        bn_axis = 1
  
    x = BatchNormalization(axis=bn_axis)(input_tensor)
    x = Activation('relu')(x)
    x = Conv2D(filters1, (3, 3),
               kernel_initializer="he_normal",
               kernel_regularizer=l2(0.0001))(x)
    x = BatchNormalization(axis=bn_axis)(x)
    x = Activation('relu')(x)

    x = Conv2D(filters2, (3,3),
               padding='same',
               kernel_initializer="he_normal",
               kernel_regularizer=l2(0.0001))(x)

    x = layers.add([x, input_tensor])

    return x

def conv_block_preactive(input_tensor, kernel_size, filters, stage, block, strides=(2, 2)):

    filters1, filters2, filters3 = filters
    
    if K.image_data_format() == 'channels_last':
        bn_axis = 3
    else:
        bn_axis = 1
        
    x = Conv2D(filters1, (3, 3), strides=strides,
                          kernel_initializer="he_normal",
                          kernel_regularizer=l2(0.0001))(input_tensor)
    x = BatchNormalization(axis=bn_axis)(x)
    x = Activation('relu')(x)

    x = Conv2D(filters2, (3,3), padding='same',
                          kernel_initializer="he_normal",
                          kernel_regularizer=l2(0.0001))(x)


    shortcut = Conv2D(filters3, (1, 1), strides=strides,
                          kernel_initializer="he_normal",
                          kernel_regularizer=l2(0.0001))(input_tensor)
    shortcut = BatchNormalization(axis=bn_axis)(shortcut)

    x = layers.add([x, shortcut])
    return x


def identity_block_bottleneck(input_tensor, kernel_size, filters, stage, block):

    filters1, filters2, filters3 = filters
    
    if K.image_data_format() == 'channels_last':
        bn_axis = 3
    else:
        bn_axis = 1
  

    x = Conv2D(filters1, (1, 1),
                          kernel_initializer="he_normal",
                          kernel_regularizer=l2(0.0001))(input_tensor)
    x = BatchNormalization(axis=bn_axis)(x)
    x = Activation('relu')(x)

    x = Conv2D(filters2, kernel_size,
               padding='same',
               kernel_initializer="he_normal",
               kernel_regularizer=l2(0.0001))(x)
    x = BatchNormalization(axis=bn_axis)(x)
    x = Activation('relu')(x)

    x = Conv2D(filters3, (1, 1),
                          kernel_initializer="he_normal",
                          kernel_regularizer=l2(0.0001))(x)
    x = BatchNormalization(axis=bn_axis)(x)

    x = layers.add([x, input_tensor])
    x = Activation('relu')(x)
    return x


def conv_block_bottleneck(input_tensor, kernel_size, filters, stage, block, strides=(2, 2)):

    filters1, filters2, filters3 = filters
    
    if K.image_data_format() == 'channels_last':
        bn_axis = 3
    else:
        bn_axis = 1
        
    x = Conv2D(filters1, (1, 1), strides=strides,
                          kernel_initializer="he_normal",
                          kernel_regularizer=l2(0.0001))(input_tensor)
    x = BatchNormalization(axis=bn_axis)(x)
    x = Activation('relu')(x)

    x = Conv2D(filters2, kernel_size, padding='same',
                          kernel_initializer="he_normal",
                          kernel_regularizer=l2(0.0001))(x)
    x = BatchNormalization(axis=bn_axis)(x)
    x = Activation('relu')(x)

    x = Conv2D(filters3, (1, 1))(x)
    x = BatchNormalization(axis=bn_axis)(x)

    shortcut = Conv2D(filters3, (1, 1), strides=strides,
                          kernel_initializer="he_normal",
                          kernel_regularizer=l2(0.0001))(input_tensor)
    shortcut = BatchNormalization(axis=bn_axis)(shortcut)

    x = layers.add([x, shortcut])
    x = Activation('relu')(x)
    return x


def ResNet50_cifar_small(input_tensor=None, input_shape=None,
             pooling=None,
             classes=1000):

    # Determine proper input shape
    input_shape = (32,32,3)

    if input_tensor is None:
        img_input = Input(shape=input_shape)
    else:
        if not K.is_keras_tensor(input_tensor):
            img_input = Input(tensor=input_tensor, shape=input_shape)
        else:
            img_input = input_tensor
    if K.image_data_format() == 'channels_last':
        bn_axis = 3
    else:
        bn_axis = 1

    x = ZeroPadding2D((1, 1))(img_input)
    x = Conv2D(16, (3, 3), strides=(2, 2), name='conv1')(x)
    x = BatchNormalization(axis=bn_axis, name='bn_conv1')(x)
    x = Activation('relu')(x)
    
    block_shape = K.int_shape(x)
    print(block_shape)
    
    x = conv_block(x, 3, [16, 16, 64], stage=2, block='a', strides=(1, 1))
    x = identity_block(x, 3, [16, 16, 64], stage=2, block='b')
    x = identity_block(x, 3, [16, 16, 64], stage=2, block='c')
    
    block_shape = K.int_shape(x)
    print(block_shape)
    
    x = conv_block(x, 3, [32, 32, 128], stage=3, block='a')
    x = identity_block(x, 3, [32, 32, 128], stage=3, block='b')
    x = identity_block(x, 3, [32, 32, 128], stage=3, block='c')
    
    block_shape = K.int_shape(x)
    print(block_shape)
    
    x = conv_block(x, 3, [64, 64, 256], stage=4, block='a')
    x = identity_block(x, 3, [64, 64, 256], stage=4, block='b')
    x = identity_block(x, 3, [64, 64, 256], stage=4, block='c')
    
    
    block_shape = K.int_shape(x)
    print(block_shape)

    x = AveragePooling2D(pool_size=(block_shape[1], block_shape[2]),strides=(1, 1))(x)

   
    x = Flatten()(x)
    x = Dense(256, activation='relu')(x)
    x = Dense(classes, activation='softmax', name='fc1000')(x)


    # Ensure that the model takes into account
    # any potential predecessors of `input_tensor`.
    if input_tensor is not None:
        inputs = get_source_inputs(input_tensor)
    else:
        inputs = img_input
    # Create model.
    model = Model(inputs, x, name='resnet50')

    return model

def get_img(img_path):
    img = image.load_img(img_path, target_size=(32, 32))
    x = image.img_to_array(img)
    x = np.expand_dims(x, axis=0)
    x = preprocess_input(x)
    return x

# from keras.datasets import cifar10
 	
data_folder = "/training_data"
class_folders = os.listdir(os.getcwd()+data_folder)
training_data = {}
for i in range(7):
	training_data[i] = []
for name in sorted(class_folders):
	y = int(name[5])-1 #for 0 based indexing
	y_ = np.zeros(7) #7 classes
	y_[y] = 1
	for img_name in os.listdir(os.getcwd()+data_folder+'/'+name):
		img_path = os.getcwd()+data_folder+'/'+name+"/"+img_name
		x = get_img(img_path).reshape(32,32,3)
		training_data[y].append(x)
class_weight = {}
total_samples = 0.0
for i in range(7):
	total_samples += len(training_data[i])
for y in range(7):
	y_ = np.zeros(7)
	y_[y] = 1
	class_weight[y] = len(training_data[y])/total_samples
	# print class_weight[y],' No. of samples:',len(training_data[y])
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
x_train, x_test, y_train, y_test = train_test_split(_X_, _Y_, test_size=0.1, random_state=2)

# (x_train, y_train), (x_test, y_test) = cifar10.load_data()
# print('x_train shape:', x_train.shape)
# print(x_train.shape[0], 'train samples')
# print(x_test.shape[0], 'test samples')
# x_train = x_train.astype('float32')
# x_test = x_test.astype('float32')
# mean_image = np.mean(x_train, axis=0)
# x_train -= mean_image
# x_test -= mean_image
# x_train = x_train/128
# x_test = x_test/128 
# y_train = keras.utils.to_categorical(y_train, 10)
# y_test = keras.utils.to_categorical(y_test, 10) 


from keras.callbacks import ReduceLROnPlateau, CSVLogger, EarlyStopping
from keras.regularizers import l2

batch_size = 128
nb_classes = 7
nb_epoch = 200
data_augmentation = True
lr_schedule = [40,60,70] # epoch_step
def schedule(epoch_idx):
    if (epoch_idx + 1) < lr_schedule[0]:
        return 0.001 
    if (epoch_idx + 1) < lr_schedule[1]:
        return 0.0001
    if (epoch_idx + 1) < lr_schedule[2]:
        return 0.001
    return 0.0001
  
   


model2 = ResNet50_cifar_small(classes = nb_classes)
    
model2.compile(loss='categorical_crossentropy',
              optimizer='Adam',
              metrics=['accuracy'])

from keras.preprocessing.image import ImageDataGenerator
datagen = ImageDataGenerator(
        featurewise_center=False,  # set input mean to 0 over the dataset
        samplewise_center=False,  # set each sample mean to 0
        featurewise_std_normalization=False,  # divide inputs by std of the dataset
        samplewise_std_normalization=False,  # divide each input by its std
        zca_whitening=False,  # apply ZCA whitening
        rotation_range=0,  # randomly rotate images in the range (degrees, 0 to 180)
        width_shift_range=0.1,  # randomly shift images horizontally (fraction of total width)
        height_shift_range=0.1,  # randomly shift images vertically (fraction of total height)
        horizontal_flip=True,  # randomly flip images
        vertical_flip=False)  # randomly flip images

# Compute quantities required for feature-wise normalization
# (std, mean, and principal components if ZCA whitening is applied).
datagen.fit(np.array(x_train))

# Fit the model on the batches generated by datagen.flow().
history = model2.fit_generator(datagen.flow(np.array(x_train), np.array(y_train), batch_size=batch_size),
					steps_per_epoch=len(np.array(x_train))/batch_size,
                    validation_data=(np.array(x_test), np.array(y_test)),
                    epochs=nb_epoch, verbose=1, max_q_size=100,
                    callbacks=[ LearningRateScheduler(schedule=schedule)])
model_json = model2.to_json()
with open("model.json", "w") as json_file:
	json_file.write(model_json)
model2.save_weights("model.h5")

# history = model2.fit(np.array(x_train),np.array(y_train),epochs=2,verbose=1,shuffle=True,validation_split=0.1,class_weight=class_weight)