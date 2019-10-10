#//////////////////////////////////////////////////
#                                                 #
# Maximum likelyhood fit at 13 TeV 		  #
#                                                 #
#//////////////////////////////////////////////////
# python MyLiklihoodFit.py --limit limit  --channel ele --hist mjj_kfit_CTagL_SF --mass 100

import os
import sys
import os.path
import argparse

#limit_base_dir = "/afs/cern.ch/work/r/rverma/private/ExclusionLimit/AN-18-061"
limit_base_dir = "/home/rverma/combine/CMSSW_8_1_0/src/HiggsAnalysis/LimitComputationHtoCS"

def runMe(command, isPrint=False):
    if(isPrint):
        print "\033[01;32m"+ "Excecuting: "+ "\033[00m",  command
    os.system(command)

#Nice way to print strings
def toPrint(string, value):
    length = (len(string)+len(str(value))+2)
    line = "-"*length
    print ""
    print "* "+ line +                    " *"
    print "| "+ " "*length +              " |"
    print "| "+ string+ ": "+ str(value)+ " |"
    print "| "+ " "*length +              " |"
    print "* "+ line +                    " *"

#------------------------------------------------
#function to copy 'text to workspace' root files
#------------------------------------------------
def t2wFilePath(limit_dir, channel, hist, mass):
    my_str = "CHANNEL= %s, HIST= %s, MASS= %s" %(channel, hist, mass)
    toPrint("Input", my_str)
    limit_path = limit_dir+"/"+channel+"/"+hist
    file_name = "t2w_datacard.root";
    if(limit_dir=="limit"):
        file_name  = 't2w_datacard_csbar_'+channel+'_'+hist+'_13TeV_mH'+str(mass)+'.root'
    if(limit_dir=="limit2D"):
        file_name  = 't2w_combine_13TeV_mH'+str(mass)+'.root'
    runMe('mkdir -p '+limit_path)
    full_file_path = limit_base_dir+'/'+limit_path+'/'+file_name
    runMe('cp '+full_file_path+' '+limit_path)
    if(os.path.exists(full_file_path)==False):
        sys.exit(1)
    return limit_path+'/'+file_name

#---------------------------------------------
#function to do maximum likelyhood fit
#---------------------------------------------
#https://cms-hcomb.gitbooks.io/combine/content/part3/nonstandard.html#fitting-diagnostics
def doMaxLikeFit(limit_dir, channel, hist, mass):
    t2w_file = t2wFilePath(limit_dir, channel, hist, mass)
    limit_path = limit_dir+"/"+channel+"/"+hist
    combineLogFile = limit_path+"/log_fitDiag_"+channel+'_'+hist+'_13TeV_mH'+str(mass)+'.txt'
    fitDiagRootFile = limit_path+"/fitDiag_"+channel+'_'+hist+'_13TeV_mH'+str(mass)+'.root'
    #runMe('combine --rMin 0.00001 '+limit_path+'/'+fileName+' -M FitDiagnostics -t -1 --expectSignal 0 | tee '+combineLogFile, True)
    toPrint("FitDiagnostics", t2w_file)
    runMe('combine '+t2w_file+' -M FitDiagnostics -t -1 --expectSignal 1 | tee '+combineLogFile, True)
    runMe('mv fitDiagnostics.root '+fitDiagRootFile)

def getNuisParamDiff(limit_dir, channel, hist, mass):
    doMaxLikeFit(limit_dir, channel, hist, mass)
    limit_path = limit_dir+"/"+channel+"/"+hist
    fitDiagRootFile = limit_path+"/fitDiag_"+channel+'_'+hist+'_13TeV_mH'+str(mass)+'.root'
    diffNuFilePath = '${CMSSW_BASE}/src/HiggsAnalysis/CombinedLimit/test/diffNuisances.py'
    diffNuLogFile = limit_path+"/log_diffNuis_"+channel+'_'+hist+'_13TeV_mH'+str(mass)+'.txt'
    diffNuOutFile = limit_path+"/out_diffNuis_"+channel+'_'+hist+'_13TeV_mH'+str(mass)
    #runMe('python '+diffNuFilePath+' -a '+fitDiagRootFile+' --poi=BR --all  -g'+ diffNuOutFile+' | tee '+diffNuLogFile)
    toPrint("diffNuisances.py", fitDiagRootFile)
    runMe('python '+diffNuFilePath+' -a '+fitDiagRootFile+' --poi=BR -g'+ diffNuOutFile+' &> '+diffNuLogFile)

#---------------------------------------------
#function to get impact of nuisance parameters
#---------------------------------------------
#https://cms-hcomb.gitbooks.io/combine/content/part3/nonstandard.html#nuisance-parameter-impacts
# https://cms-hcomb.gitbooks.io/combine/content/part3/runningthetool.html#combinetool-for-job-submission
def getNuisParamImpact(limit_dir, channel, hist, mass, bsub):
    t2w_file = t2wFilePath(limit_dir, channel, hist, mass)
    limit_path = limit_dir+"/"+channel+"/"+hist
    combineLogFile = limit_path+"/log_paramScan_"+channel+'_'+hist+'_13TeV_mH'+str(mass)+'.txt'
    combineJsonFile = limit_path+"/log_paramScan_"+channel+'_'+hist+'_13TeV_mH'+str(mass)+'.json'
    paramScanFile = limit_path+"/paramScan_"+channel+'_'+hist+'_13TeV_mH'+str(mass)
    toPrint("--doInitialFit", t2w_file)
    ##strBR = ' --redefineSignalPOIs BR --setParameters BR=0 -t -1' # no space after comma
    strBR = ' --redefineSignalPOIs BR --setParameterRanges BR=0.0,0.10' # no space after comma
    if(bsub):
        runMe('kinit') # for AFS token
        runMe('combineTool.py -M Impacts -d '+t2w_file+' -m '+str(mass)+strBR+' --doInitialFit --robustFit 1 | tee '+combineLogFile, True)
        toPrint("--doFits", t2w_file)
        job_name = limit_dir+"_"+channel+"_"+hist+"_mH"+str(mass)
        runMe('combineTool.py -M Impacts -d '+t2w_file+' -m '+str(mass)+ strBR+' --robustFit 1 --doFits --job-mode lxbatch --task-name '+job_name+' --sub-opts=\'-q 1nd\' | tee '+combineLogFile, True)

        job_status = os.popen('bjobs').read()
        #job_status = "finished"
        job_status = "running"
        if(job_status=="finished"):
            toPrint("plotImpacts.py ", combineJsonFile)
            runMe('combineTool.py -M Impacts -d '+t2w_file+' -m '+str(mass)+' -o '+combineJsonFile, True)
            runMe('plotImpacts.py --cms-label "   Internal" -i '+combineJsonFile+ ' -o '+paramScanFile, True)
            #runMe('mv higgsCombine* '+limit_path)
            #runMe('mv *.sh '+limit_path)
            #runMe('mv *.log '+limit_path)
    else:
        runMe('combineTool.py -M Impacts -d '+t2w_file+' -m '+str(mass)+strBR+' --doInitialFit --robustFit 1 | tee '+combineLogFile, True)
        toPrint("--doFits", t2w_file)
        runMe('combineTool.py --parallel 10 -M Impacts -d '+t2w_file+' -m '+str(mass)+strBR+' --robustFit 1 --doFits| tee '+combineLogFile, True)
        toPrint("plotImpacts.py ", combineJsonFile)
        runMe('combineTool.py -M Impacts -d '+t2w_file+' -m '+str(mass)+' -o '+combineJsonFile, True)
        runMe('plotImpacts.py --cms-label "" -i '+combineJsonFile+ ' -o '+paramScanFile, True)
        runMe('mv higgsCombine* '+limit_path)

if __name__=="__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("--limit", default="limit", help="The limit directory containing datacards")
    parser.add_argument("--channel", default="mu", help="The channel name e.g. mu or ele or mu_ele")
    parser.add_argument("--hist", default="mjj_kfit", help="The name of the histogram ")
    parser.add_argument("--mass", default="120", help="Mass of the charged Higgs")
    parser.add_argument("--bsub", default=False, help="if batch submission")
    args = parser.parse_args()

    #Do the main job here
    #getNuisParamDiff(args.limit, args.channel, args.hist, args.mass)
    getNuisParamImpact(args.limit, args.channel, args.hist, args.mass, args.bsub)


