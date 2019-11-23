# CMSDAS2019

## Setup environment 

We need ROOT version 6.18. We can set up ROOT from CVMFS. 

. /cvmfs/sft.cern.ch/lcg/app/releases/ROOT/6.18.00/x86_64-centos7-gcc48-opt/bin/thisroot.sh 

## Produce n-tuples for ttH and ttbb directly from NanoAOD 

We will run macro with RDataFrame. 

root -l ana.C

This will create root files that contain the input variables. 
In this exercise, there are only two variables: 
dR and Mbb (distance and invariant mass between two b-tagged jets with minimum angle)

## Install packages 

virtualenv --system-site-packages -p python ./venv 

source ./venv/bin/activate

pip install tensorflow

pip install keras

pip install scikit-learn
