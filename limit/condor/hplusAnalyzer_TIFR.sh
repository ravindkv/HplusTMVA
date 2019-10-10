#!/bin/bash
massPoint=$1
channel=$2
category=$3
date
echo "CONDOR DIR: $_CONDOR_SCRATCH_DIR"
limitDir="/home/rverma/t3store/AN-18-061/ExclusionLimit/CMSSW_8_0_26/src/HiggsAnalysis/HplusTocs13TeVLimit"

if [ $category -eq 1 ] 
then 
    catDir="Cat1_Inc"  
elif [ $category -eq 2 ]
then 
    catDir="Cat2_cTagInc" 
else [ $category -eq 3 ] 
    catDir="Cat3_cTagEx" 
fi

outDir=$limitDir"/condor/out/"$channel"/"$catDir"/Mass"$massPoint
mkdir -p $outDir
echo $outDir
cp $limitDir"/MyHPlusDataCardMaker.C" $outDir
cp $limitDir"/MyHPlusDataCardMaker.h" $outDir
cp $limitDir"/MyLimitComputer.py" $outDir
cp $limitDir"/MyTemplateDataCard.txt" $outDir
cd $outDir
source /cvmfs/cms.cern.ch/cmsset_default.sh
eval `scram runtime -sh`
python MyLimitComputer.py --ch $channel --cat $category --mass $massPoint --batch True --isGOF True 
echo "DONE"
date

