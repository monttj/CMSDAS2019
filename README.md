# CMSDAS2019

## Setup environment 

We need ROOT version 6.18. We can set up ROOT from CVMFS. 

```
. /cvmfs/sft.cern.ch/lcg/app/releases/ROOT/6.18.00/x86_64-centos7-gcc48-opt/bin/thisroot.sh 
```

## Clone github repository 
```
git clone https://github.com/monttj/CMSDAS2019.git
cd CMSDAS2019
```

## Produce n-tuples for ttH and ttbb events

We will run macro with RDataFrame over NanoAOD samples. 
```
root -l ana.C
```
This will create root files that contain the input variables. 
In this exercise, there are only two variables: 
`dR` and `Mbb` (distance and invariant mass between two b-tagged jets with minimum angle)

check if you have two files : myntuple_ttH.root and myntuple_ttbb.root   

## Install packages for DNN exercise
```
virtualenv --system-site-packages -p python ./venv 
```
```
source ./venv/bin/activate 
```

Install necessary packages
```
pip install tensorflow
pip install keras
pip install scikit-leurn
```

## Open Jupyter Notebook 

To use Jupyter Notebook in local server, 
please refer to this link:
[Jupyter in local server](https://twiki.cern.ch/twiki/bin/viewauth/CMS/SWGuideCMSDataAnalysisSchoolBeijing2019PreExerciseFourthSet#Exercise_13_Using_Jupyter_with_P)
