#!/bin/bash
#REFERENCE
#https://github.com/florez/CONDOR

#//////////////////////////////////////
#                                     #
# hplusCond.sub runs hplusAnalyzer_TIFR.sh #
# hplusAnalyzer_TIFR.sh runs runMe.sh      #
# runMe.sh runs hplusAnalyzer.C       #
#                                     #
#//////////////////////////////////////

#------------------------------------------------
#create a directory where all the outputs will be
#stored, for different merged ntuple input files
#------------------------------------------------
ntupleT2Paths=$1

source /cvmfs/cms.cern.ch/cmsset_default.sh
eval `scram runtime -sh`
voms-proxy-init --voms cms --valid 100:10
cp /tmp/x509up_u56537 ~/

log="CondorLog_"
logDir=$log${ntupleT2Paths/.txt/""}
baseDir="/home/rverma/t3store3/AN-18-061/CondorLog/AnalysisCondorLog/"
mkdir -p $baseDir$logDir
outcond="$baseDir$logDir"

cp hplusCond.sub $outcond
cp hplusAnalyzer_TIFR.sh $outcond
cp $ntupleT2Paths $outcond
cd $outcond

#------------------------------------------------
#read the file, where paths of ntuples are stored
#do not put empty lines in mergedNtupleT2.txt
#------------------------------------------------
count=0
cat $ntupleT2Paths | while read ntupleT2Path
do
  #----------------------------------------------
  #print T2Paths of ntuple, on terminal
  #split the T2Paths of ntuples, into an array
  #get the  second last entry of the array
  #remove .root, from the input ntuple
  #----------------------------------------------
  ((count++))
  echo -e "\033[01;32m input ntuple=\033[00m" $count": " $ntupleT2Path
  IFS='/ ' read -r -a array <<< "$ntupleT2Path"
  len=${#array[@]}
  sec_last=`expr $len - 1`
  #sec_last=`expr $len`
  ntuple=${array[$sec_last]}
  #echo $ntuple
  iFile=${ntuple/.root/""}
 
  #----------------------------------------------
  #copy condor scripts to each input ntuple dir
  #replace hplusCond.sub arguments, as per input
  #submit the condor jobs, for each ntuple
  #----------------------------------------------
  
  mkdir -p $iFile
  cp hplusCond.sub $iFile
  cp hplusAnalyzer_TIFR.sh $iFile
  cd $iFile 
  sed -i "s:FNAME:$ntupleT2Path:g" hplusCond.sub
  sed -i "s:OUTPUTFILE:$iFile:g" hplusCond.sub
  sed -i "s:OUTPUTDIR:$iFile:g" hplusCond.sub
  condor_submit hplusCond.sub
  cd ../
done
