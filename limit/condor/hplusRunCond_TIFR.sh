#!/bin/bash
#REFERENCE
#https://github.com/florez/CONDOR

#------------------------------------------------
#create a directory for logs
#------------------------------------------------
inputFile=$1
logDir="log"
baseDir="/home/rverma/t3store/AN-18-061/ExclusionLimit/CMSSW_8_0_26/src/HiggsAnalysis/HplusTocs13TeVLimit/condor/"
mkdir -p $baseDir$logDir
outcond="$baseDir$logDir"
cp hplusCond.sub $outcond
cp hplusAnalyzer_TIFR.sh $outcond
cp $inputFile $outcond
cd $outcond

#------------------------------------------------
#do not put empty myLines in mergedNtupleT2.txt
#------------------------------------------------
count=0
cat $inputFile | while read myLine
do
  #----------------------------------------------
  #remove .root, from the input ntuple
  #----------------------------------------------
  ((count++))
  echo -e "\033[01;32m input ntuple=\033[00m" $count": " $myLine
  IFS='/' read -r -a array <<< "$myLine"
  len=${#array[@]}
  mass="${array[0]}"
  channel="${array[1]}"
  cat="${array[2]}"

  #echo $ntuple
  iFile=$channel"_cat"$cat"_mass"$mass
 
  #----------------------------------------------
  #copy condor scripts to each input ntuple dir
  #replace hplusCond.sub arguments, as per input
  #submit the condor jobs, for each ntuple
  #----------------------------------------------
  mkdir -p $iFile
  cp hplusCond.sub $iFile
  cp hplusAnalyzer_TIFR.sh $iFile
  cd $iFile 
  sed -i "s:MASS:$mass:g" hplusCond.sub
  sed -i "s:CHANNEL:$channel:g" hplusCond.sub
  sed -i "s:CAT:$cat:g" hplusCond.sub
  condor_submit hplusCond.sub
  cd ../
done
