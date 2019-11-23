import tensorflow as tf
import pandas as pd
import keras
from keras.utils import np_utils, multi_gpu_model
from keras.models import Model, Sequential, load_model
from keras.layers import Input, Dense, Activation, Dropout, add
from keras.layers.normalization import BatchNormalization
from keras.regularizers import l2
from keras.optimizers import Adam, SGD
from keras.callbacks import Callback, ModelCheckpoint

import ROOT
from sys import exit
import numpy as np

import csv
from sklearn.utils import shuffle
import os

df_signal = ROOT.RDataFrame("mytree", "myntuple_ttH.root")
df_background = ROOT.RDataFrame("mytree", "myntuple_ttbb.root")

df_train_p = df_signal.AsNumpy()
df_train_n = df_background.AsNumpy()

print("Read-out of the full RDataFrame:\n{}\n".format(df_train_p))
print("Read-out of the full RDataFrame:\n{}\n".format(df_train_n))

train_p = np.vstack( ( df_train_p["dR"], df_train_p["mbb"]  ))
train_n = np.vstack( ( df_train_n["dR"], df_train_n["mbb"]  ))

train_p = np.transpose(train_p)
train_n = np.transpose(train_n)

train_data = np.vstack(( train_p, train_n))
train_label = np.array([1]*len(train_p)+[0]*len(train_n))

print("signal events = ",  len(train_p))
print("background events = ",  len(train_n))
print train_label

numbertr=len(train_label)

#Shuffling
order=shuffle(range(numbertr),random_state=100)
train_label=train_label[order]
train_data=train_data[order,0::]

train_label = train_label.reshape( (numbertr, 1) )
trainnb=0.9 # Fraction used for training

#Splitting between training set and cross-validation set
valid_data=train_data[int(trainnb*numbertr):numbertr,0::]
valid_label=train_label[int(trainnb*numbertr):numbertr]

train_data=train_data[0:int(trainnb*numbertr),0::]
train_label=train_label[0:int(trainnb*numbertr)]

#################################
#Keras model compile and training
#################################
nvar = train_data.shape[1]
print("input = " , nvar)
a = 50
b = 0.08
init = 'glorot_uniform'

with tf.device("/cpu:0") :
    inputs = Input(shape=(nvar,))
    x = Dense(5, kernel_regularizer=l2(1E-2))(inputs)
    x = Dense(a, activation='relu', kernel_initializer=init, bias_initializer='zeros')(x)
    x = Dense(a, activation='relu', kernel_initializer=init, bias_initializer='zeros')(x)
    outputs = Dense(1, activation='sigmoid')(x)
    model = Model(inputs=inputs, outputs=outputs)

adam=keras.optimizers.Adam(lr=1E-3, beta_1=0.9, beta_2=0.999, epsilon=1e-08, decay=1E-3)
model.compile(loss='binary_crossentropy', optimizer='adam', metrics=['accuracy','binary_accuracy'])

modelfile = 'model.h5'

checkpoint = ModelCheckpoint(modelfile, monitor='val_binary_accuracy', verbose=1, save_best_only=False)

history = model.fit(train_data, train_label,
                             epochs=20, batch_size=1024,
                             validation_data=(valid_data,valid_label),
                             )

import matplotlib.pyplot as plt

plt.plot(history.history['loss'])
plt.plot(history.history['val_loss'])
plt.title('Binary crossentropy')
plt.ylabel('Loss')
plt.xlabel('Epoch')
plt.legend(['Train','Test'],loc='upper right')
plt.savefig(os.path.join("./",'fig_score_loss.pdf'))
plt.gcf().clear()

