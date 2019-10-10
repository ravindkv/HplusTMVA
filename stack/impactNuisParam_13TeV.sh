count=0                                                                                   
 failedParamFile=$1                                                                        
 t2wDataCard=$2                                                                            
 mass=$3                                                                                   
 cat $failedParamFile | while read nuisName                                                
 do                                                                                        
   ((count++))                                                                             
   echo -e "\033[01;32m input nuis param=\033[00m" $count": " $nuisName                    
   ext=".sh"                                                                               
   rm $nuisName$ext                                                                        
   echo 'ulimit -s unlimited' >> $nuisName$ext                                             
   echo 'set -e' >>$nuisName$ext                                                           
   echo 'cd /afs/cern.ch/work/r/rverma/private/ExclusionLimit/AN-18-061/CMSSW_8_0_26/src' >>$nuisName$ext
   echo 'export SCRAM_ARCH=slc6_amd64_gcc530' >> $nuisName$ext                             
   echo 'eval `scramv1 runtime -sh`' >> $nuisName$ext                                      
   echo 'cd ' $PWD  >> $nuisName$ext                                                       
   echo 'eval combine -M MultiDimFit -d '$t2wDataCard' -m '$mass' --redefineSignalPOIs BR --setParameterRanges BR=0.0,0.10 -P' $nuisName '--trackParameters BR --            algo=grid --points 20 -n ScanNuis_'$nuisName >> $nuisName$ext
   chmod +x $nuisName$ext                                                                  
   extLog=".log"                                                                           
   bsub -o $PWD/$nuisName$extLog -q "1nd" $nuisName$ext                                    
   #bash $nuisName$ext                                                                     
 done    
