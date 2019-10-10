
#//////////////////////////////////////////////////
#                                                 #
# Merge histo files into a single root file       #
#                                                 #
#//////////////////////////////////////////////////

import os
import sys
import datetime

#USERS INPUTS
isMuData = True
isMuMC = True
isEleData = False
isEleMC = False
isHiggsBkg = True

mc = []
mc.append("TTJetsM")
mc.append("TTJetsP")
mc.append("TTJetsP_up")
mc.append("TTJetsP_down")
mc.append("TTJetsP_mtop1735")
mc.append("TTJetsP_mtop1715")
mc.append("TTJetsP_hdampUP")
mc.append("TTJetsP_hdampDOWN")
mc.append("HplusM120")
mc.append("ST_tW")
mc.append("ST_t")
mc.append("ST_s")
mc.append("WJetsToLNu")
mc.append("W1JetsToLNu")
mc.append("W2JetsToLNu")
mc.append("W3JetsToLNu")
mc.append("W4JetsToLNu")
mc.append("DYJetsToLL")
mc.append("DY1JetsToLL")
mc.append("DY2JetsToLL")
mc.append("DY3JetsToLL")
mc.append("DY4JetsToLL")
mc.append("WW")
mc.append("WZ")
mc.append("ZZ")
mc.append("HplusM80")
mc.append("HplusM90")
mc.append("HplusM100")
mc.append("HplusM120")
mc.append("HplusM140")
mc.append("HplusM150")
mc.append("HplusM155")
mc.append("HplusM160")

if(isMuMC):
    mc.append("QCD_Pt-15to20_Mu")
    mc.append("QCD_Pt-20to30_Mu")
    mc.append("QCD_Pt-30to50_Mu")
    mc.append("QCD_Pt-50to80_Mu")
    mc.append("QCD_Pt-80to120_Mu")
    mc.append("QCD_Pt-120to170_Mu")
    mc.append("QCD_Pt-170to300_Mu")
    mc.append("QCD_Pt-300to470_Mu")
else:
    mc.append("QCD_Pt-15to20_EM")
    mc.append("QCD_Pt-20to30_EM")
    mc.append("QCD_Pt-30to50_EM")
    mc.append("QCD_Pt-50to80_EM")
    mc.append("QCD_Pt-80to120_EM")
    mc.append("QCD_Pt-120to170_EM")
    mc.append("QCD_Pt-170to300_EM")
    mc.append("QCD_Pt-300toInf_EM")

if(isHiggsBkg):
    mc.append("GluGluHToCC")          
    mc.append("VBFHToCC")             
    mc.append("WminusH_HToCC_WToLNu") 
    mc.append("WminusH_HToCC_WToQQ")  
    mc.append("WplusH_HToCC_WToLNu")  
    mc.append("WplusH_HToCC_WToQQ")   
    mc.append("ZH_HToCC_ZToLL")       
    mc.append("ZH_HToCC_ZToNuNu")     
    mc.append("ZH_HToCC_ZToQQ")       
    mc.append("ttHToCC")              

if(isMuData):
	data = ["MuRunB2v2", "MuRunCv1", "MuRunDv1", "MuRunEv1", "MuRunFv1", "MuRunGv1", "MuRunH2v1", "MuRunH3v1"]

if(isEleData): 
	data = ["EleRunBver2v2", "EleRunCv1", "EleRunDv1", "EleRunEv1", "EleRunFv1", "EleRunGv1", "EleRunHver2v1", "EleRunHver3v1"]

#-------------------------------
def execme(command):
    print ""
    print "\033[01;32m"+ "Excecuting: "+ "\033[00m",  command
    print ""
    os.system(command)


if isMuMC:
    for samp in range(len(mc)):
        execme("hadd -k "+str(mc[samp])+"_Merged.root "+str(mc[samp])+"_MuMC*")

if isEleMC:
    for samp in range(len(mc)):
        execme("hadd -k "+str(mc[samp])+"_Merged.root "+str(mc[samp])+"_EleMC*")

if(isMuData):
    for samp in range(len(data)):
        execme("hadd -k "+str(data[samp])+"_Merged.root "+str(data[samp])+"*")
    execme("hadd -k all_muData.root MuRun*_Merged.root")

if(isEleData):
    for samp in range(len(data)):
        execme("hadd -k "+str(data[samp])+"_Merged.root "+str(data[samp])+"*")
    execme("hadd -k all_EleData.root EleRun*_Merged.root")

execme("hadd -k all_ST.root ST*_Merged.root")
execme("hadd -k all_TTJetsM.root TTJetsM_Merged.root")
execme("hadd -k all_TTJetsP.root TTJetsP_Merged.root")
execme("hadd -k all_TTJetsP_up.root TTJetsP_up_Merged.root")
execme("hadd -k all_TTJetsP_down.root TTJetsP_down_Merged.root")
execme("hadd -k all_TTJetsP_mtop1715.root TTJetsP_mtop1715_Merged.root")
execme("hadd -k all_TTJetsP_mtop1735.root TTJetsP_mtop1735_Merged.root")
execme("hadd -k all_TTJetsP_hdampUP.root TTJetsP_hdampUP_Merged.root")
execme("hadd -k all_TTJetsP_hdampDOWN.root TTJetsP_hdampDOWN_Merged.root")
execme("hadd -k all_Hplus80.root HplusM80*_Merged.root")
execme("hadd -k all_Hplus90.root HplusM90*_Merged.root")
execme("hadd -k all_Hplus100.root HplusM100*_Merged.root")
execme("hadd -k all_Hplus120.root HplusM120*_Merged.root")
execme("hadd -k all_Hplus140.root HplusM140*_Merged.root")
execme("hadd -k all_Hplus150.root HplusM150*_Merged.root")
execme("hadd -k all_Hplus155.root HplusM155*_Merged.root")
execme("hadd -k all_Hplus160.root HplusM160*_Merged.root")
execme("hadd -k all_QCD.root QCD*_Merged.root")
execme("hadd -k all_VV.root WW_Merged.root WZ_Merged.root ZZ_Merged.root")
execme("hadd -k all_WJets.root W1*_Merged.root W2*_Merged.root W3*_Merged.root W4*_Merged.root WJ*_Merged.root")
execme("hadd -k all_DY.root DY1*_Merged.root DY2*_Merged.root DY3*_Merged.root DY4*_Merged.root DYJ*_Merged.root")

if(isHiggsBkg):
    execme("hadd -k all_GluGluHToCC.root            GluGluHToCC*_Merged.root")          
    execme("hadd -k all_VBFHToCC.root               VBFHToCC*_Merged.root")             
    execme("hadd -k all_WminusH_HToCC_WToLNu.root   WminusH_HToCC_WToLNu*_Merged.root") 
    execme("hadd -k all_WminusH_HToCC_WToQQ.root    WminusH_HToCC_WToQQ*_Merged.root")  
    execme("hadd -k all_WplusH_HToCC_WToLNu.root    WplusH_HToCC_WToLNu*_Merged.root")  
    execme("hadd -k all_WplusH_HToCC_WToQQ.root     WplusH_HToCC_WToQQ*_Merged.root")   
    execme("hadd -k all_ZH_HToCC_ZToLL.root         ZH_HToCC_ZToLL*_Merged.root")       
    execme("hadd -k all_ZH_HToCC_ZToNuNu.root       ZH_HToCC_ZToNuNu*_Merged.root")     
    execme("hadd -k all_ZH_HToCC_ZToQQ.root         ZH_HToCC_ZToQQ*_Merged.root")       
    execme("hadd -k all_ttHToCC.root                ttHToCC*_Merged.root")              
   
   
   
   
   
   
   
   
   
   
