
#------------------------------------------
# Global paths
#------------------------------------------
limitPath="/home/rverma/t3store/AN-18-061/ExclusionLimit/CMSSW_8_0_26/src/HiggsAnalysis/HplusTocs13TeVLimit"
mkdir -p CopiedDC
cd CopiedDC
cp -r $limitPath/limit/* . 
rm -r *file/
rm *.tex
rm *.pdf
rm */*/*.png
rm */*/*.pdf
rm */*/*.root

rm */*/*/*.C
rm */*/*/*.pdf
rm */*/*/*.png
rm */*/*/*.out
rm */*/*/*.h
rm */*/*/*.py
rm */*/*/MyTe*.txt
rm */*/*/data*.txt
rm */*/*/higg*.root

