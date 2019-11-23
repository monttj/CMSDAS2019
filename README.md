# Prerequisites for CMSDAS2019

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
Please check if you have two files : `myntuple_ttH.root` and `myntuple_ttbb.root`  

In this exercise, there are only two variables: 
`dR` and `Mbb` (distance and invariant mass between two b-tagged jets with minimum angle)
You can add more variables by modifying the [ana.C macro](https://github.com/monttj/CMSDAS2019/blob/master/ana.C).
But we will leave it to you as this is not ROOT exercise. 

## Install packages for DNN exercise

Create a new virtual environment by choosing a Python interpreter and making a ./venv directory to hold it:
```
virtualenv --system-site-packages -p python ./venv 
```

Activate the virtual environment
```
source ./venv/bin/activate 
```

When virtualenv is active, your shell prompt is prefixed with (venv).

Install packages within a virtual environment without affecting the host system setup.
Install necessary packages
```
pip install tensorflow
pip install keras
pip install scikit-leurn
```
And to exit virtualenv later:
```
deactivate  
```

## Open Jupyter Notebook 

To use Jupyter Notebook in local server, 
please refer to this link:
[Jupyter in local server](https://twiki.cern.ch/twiki/bin/viewauth/CMS/SWGuideCMSDataAnalysisSchoolBeijing2019PreExerciseFourthSet#Exercise_13_Using_Jupyter_with_P)
