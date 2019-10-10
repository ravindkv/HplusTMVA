# Analysis
   
### Download and compile the package  ###  
* source /cvmfs/cms.cern.ch/cmsset_default.sh
* cmsrel CMSSW_8_0_28
* cd CMSSW_8_0_28/src
* cmsenv
* git clone https://github.com/ravindkv/Analysis.git 
* cd Analysis/src
* make clean 
* make
* cd .. 

### Compile and run, in one go ### 
* root -l 'runMe.C("hplusAnalyzer")'

### Submit condor batch jobs  ###

* cd condor
* ./hplusRunCond_TIFR.sh ntupleT2Paths.txt
