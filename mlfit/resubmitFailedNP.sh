count=0                                                                                   
failedParamFile=$1                                                                        
t2wDataCard=$2                                                                            
mass=$3                                                                                   
cat $failedParamFile | while read nuisName                                                
do                                                                                        
  ((count++))                                                                             
  echo -e "\033[01;32m input nuis param=\033[00m" $count": " $nuisName                    
  ext=".sh"                                                                               
  echo 'eval combine -M MultiDimFit -d '$t2wDataCard' -t -1 -m '$mass' --algo impact --redefineSignalPOIs BR --setParameterRanges BR=-0.01,0.30 -P ' $nuisName ' --floatOtherPOIs 1 --robustFit 1 --saveInactivePOI 1 -n _paramFit_Test_'$nuisName >> $nuisName$ext
  #echo 'eval combine -M MultiDimFit -d '$t2wDataCard' -t -1 -m '$mass' --algo impact --redefineSignalPOIs BR --setParameterRanges BR=0.0,0.10 -P ' $nuisName ' --floatOtherPOIs 1 --robustFit 1 --saveInactivePOI 1 -n _paramFit_Test_'$nuisName >> $nuisName$ext
  chmod +x $nuisName$ext                                                                  
  bash $nuisName$ext                                                                     
done       
