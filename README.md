# CMSDAS2019

We need ROOT version 6.18. 

> . /cvmfs/sft.cern.ch/lcg/app/releases/ROOT/6.18.00/x86_64-centos7-gcc48-opt/bin/thisroot.sh

# Install packages 

virtualenv --system-site-packages -p python ./venv 

source ./venv/bin/activate

pip install tensorflow

pip install keras

pip install scikit-learn
