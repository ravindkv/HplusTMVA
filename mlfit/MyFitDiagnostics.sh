t2wDataCard=$1
mass=$2
combine $t2wDataCard -m $mass -M FitDiagnostics --expectSignal 1 -t -1 --redefineSignalPOIs BR --setParameterRanges BR=0,0.10 | tee FitDiagnostics.log
python ${CMSSW_BASE}/src/HiggsAnalysis/CombinedLimit/test/diffNuisances.py -a fitDiagnostics.root --poi=BR -g fitDiag.pdf | tee diffNuisances.log

