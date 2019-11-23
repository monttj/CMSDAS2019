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

check if you have two files : myntuple_ttH.root and myntuple_ttbb.root   

## Install packages 

virtualenv --system-site-packages -p python ./venv 

source ./venv/bin/activate

pip install tensorflow

pip install keras

pip install scikit-learn

## clone github repository for DNN exercise

git clone https://github.com/monttj/CMSDAS2019.git

## open Jupyter Notebook 

To use Jupyter Notebook in local server, 
please refer to this link:
[Jupyter in local server](https://twiki.cern.ch/twiki/bin/viewauth/CMS/SWGuideCMSDataAnalysisSchoolBeijing2019PreExerciseFourthSet#Exercise_13_Using_Jupyter_with_P)



