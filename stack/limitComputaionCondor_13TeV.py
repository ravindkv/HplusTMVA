#//////////////////////////////////////////////////
#                                                 #
# 	Limit computation at 13 TeV 		  #
#                                                 #
#//////////////////////////////////////////////////

import os
import sys
import numpy

def execme(command):
    #print "\033[01;32m"+ "Excecuting: "+ "\033[00m",  command
    os.system(command)
execme("mkdir -p ~/ARCHIVE/LimitBinned")
execme("cp *.C ~/ARCHIVE/LimitBinned")

#---------------------------------------------
#function to prepare data cards
#---------------------------------------------
def makeDataCards(CHANNEL_NAME, IN_FILE_DIR, HIST_DIR, HIST_NAME):
    #print HIST_NAME
    #print HIST_DIR
    #execme("cp ~/ARCHIVE/LimitBinned/*.C .")
    execme("cp makeCondorHPlusDataCard_13TeV.C ../")
    execme("cp template_datacard_csbar.log ../")
    execme('sed -i '+'s#inFileDir_#'+IN_FILE_DIR+'# makeCondorHPlusDataCard_13TeV.C')
    execme('sed -i '+'s#inShapeHisto_#'+HIST_NAME+'# makeCondorHPlusDataCard_13TeV.C')
    execme('sed -i '+'s#inShapeHistoDir_#'+HIST_DIR+'# makeCondorHPlusDataCard_13TeV.C')
    if(CHANNEL_NAME=="mu"):
        execme('sed -i '+'s#isMuonChannel_#true# makeCondorHPlusDataCard_13TeV.C')
        execme('sed -i '+'s#isEleChannel_#false# makeCondorHPlusDataCard_13TeV.C')
        execme('cp '+muon_file_dir+'/all_muData.root '+muon_file_dir+'/all_Data.root')
        execme('sed -i '+'s#LUMI#'+str(muon_lumi)+'# makeCondorHPlusDataCard_13TeV.C')
    if(CHANNEL_NAME=="ele"):
        execme('sed -i '+'s#isMuonChannel_#false# makeCondorHPlusDataCard_13TeV.C')
        execme('sed -i '+'s#isEleChannel_#true# makeCondorHPlusDataCard_13TeV.C')
        execme('cp '+ele_file_dir+'/all_EleData.root '+ele_file_dir+'/all_Data.root')
        execme('sed -i '+'s#LUMI#'+str(ele_lumi)+'# makeCondorHPlusDataCard_13TeV.C')
    execme('sed -i '+'s#CHANNEL#'+CHANNEL_NAME+'# makeCondorHPlusDataCard_13TeV.C')
    execme('sed -i '+'s#CHANNEL#'+CHANNEL_NAME+'# template_datacard_csbar.log')
    execme('root -b -l -q makeCondorHPlusDataCard_13TeV.C')
    execme("mv ../makeCondorHPlusDataCard_13TeV.C . ")
    execme("mv ../template_datacard_csbar.log . ")

#---------------------------------------------
#function to plot limits
#---------------------------------------------
def plotLimts(CHANNEL_NAME, HIST_NAME):
    #execme("cp ~/ARCHIVE/LimitBinned/*.C .")
    execme("cp plotLimits_13TeV.C ../")
    execme('sed -i '+'s#HISTDIR#'+CHANNEL_NAME+'# plotLimits_13TeV.C')
    execme('sed -i '+'s#CHANNEL_HIST#'+CHANNEL_NAME+'_'+HIST_NAME+'# plotLimits_13TeV.C')
    execme('sed -i '+'s#HISTNAME#'+HIST_NAME+'# plotLimits_13TeV.C')
    execme('sed -i '+'s#CHANNELNAME#'+CHANNEL_NAME+'+jets# plotLimits_13TeV.C')
    execme('sed -i '+'s#CHANNELNAME#'+CHANNEL_NAME+'+jets# plotLimits_13TeV.C')
    if(CHANNEL_NAME=="mu"):
        execme('sed -i '+'s#LUMI#'+str(muon_lumi)+'# plotLimits_13TeV.C')
    if(CHANNEL_NAME=="ele"):
        execme('sed -i '+'s#LUMI#'+str(ele_lumi)+'# plotLimits_13TeV.C')
    execme('root -b -l -q plotLimits_13TeV.C')
    execme('mv limit_* '+CHANNEL_NAME+"/"+HIST_NAME)
    execme('cp *.C '+CHANNEL_NAME+"/"+HIST_NAME)
    execme("mv ../plotLimits_13TeV.C .")

#---------------------------------------------
#function to calculate limits
#---------------------------------------------
def calcLimits(CHANNEL_NAME, HIST_NAME, MASS_ARRAY, MY_LIMIT_DIR):
    for MASS_POINT in MASS_ARRAY:
        #DATACARD = 'datacard_csbar_'+CHANNEL_NAME+'_'+HIST_NAME+'_13TeV_mH'+str(MASS_POINT)
        DATACARD = 'combine_13TeV_mH'+str(MASS_POINT)
        execme('text2workspace.py '+DATACARD+'.txt -P HiggsAnalysis.CombinedLimit.ChargedHiggs:brChargedHiggs -o t2w_'+DATACARD+'.root')
        #execme('combine --rAbsAcc 0.000001 t2w_'+DATACARD+'.root -M AsymptoticLimits --mass '+str(MASS_POINT)+' --name ChargedHiggs_'+CHANNEL_NAME+'_'+MY_LIMIT_DIR)
    #MOVE OUTPUT FILES TO THE LIMIT DIR
    #LIMIT_DIR = CHANNEL_NAME+"/"+HIST_NAME
    LIMIT_DIR = "CHANNEL_/CAT_"
    #LIMIT_DIR = CHANNEL_NAME+"/"+MY_LIMIT_DIR
    execme('mkdir -p '+LIMIT_DIR)
    execme('cp *.C '+LIMIT_DIR)
    execme('mv t2w* '+LIMIT_DIR)
    execme('mv datacard_* '+LIMIT_DIR)
    execme('mv combine_* '+LIMIT_DIR)
    execme('mv HplusShapes* '+LIMIT_DIR)
    execme('mv higgsCombine* '+LIMIT_DIR)

#---------------------------------------------------
#function to get datacards to be combined
#---------------------------------------------------
def getCardsToBeCombined(CHANNEL_ARRAY, IN_FILE_DIR_ARRAY, HIST_DIR_ARRAY, MASS_ARRAY):
    #make separate cards first
    for CH in range(len(CHANNEL_ARRAY)):
        for HIST in range(len(HIST_DIR_ARRAY)):
 	        makeDataCards(CHANNEL_ARRAY[CH], IN_FILE_DIR_ARRAY[CH], HIST_DIR_ARRAY[HIST][0], HIST_DIR_ARRAY[HIST][1])
            #pass
    #store separate cards in an array
    COMB_CARD_CHANNEL_HIST_MASS = []
    for CH in range(len(CHANNEL_ARRAY)):
        COMB_CARD_HIST_MASS = []
        for HIST in range(len(HIST_DIR_ARRAY)):
            COMB_CARD_MASS = []
            for MASS in range(len(MASS_ARRAY)):
                COMB_CARD_MASS.append('datacard_csbar_'+CHANNEL_ARRAY[CH]+'_'+HIST_DIR_ARRAY[HIST][0]+'_'+HIST_DIR_ARRAY[HIST][1]+'_13TeV_mH'+str(MASS_ARRAY[MASS])+'.txt')
            COMB_CARD_HIST_MASS.append(COMB_CARD_MASS)
        COMB_CARD_CHANNEL_HIST_MASS.append(COMB_CARD_HIST_MASS)    
    return COMB_CARD_CHANNEL_HIST_MASS

#---------------------------------------------------
#function to arrange datacards for combined limits
#---------------------------------------------------
def sortCardsForCombine(COMB_CARD_CHANNEL_HIST_MASS_ARRAY, CHANNEL_ARRAY, HIST_DIR_ARRAY, MASS):
    SORT_CARD = ' '
    COMB_CARD_MASS = []
    for CH in range(len(CHANNEL_ARRAY)):
        for HIST in range(len(HIST_DIR_ARRAY)):
            COMB_CARD_MASS.append(COMB_CARD_CHANNEL_HIST_MASS_ARRAY[CH][HIST][MASS])
    for STR in COMB_CARD_MASS:
        SORT_CARD = SORT_CARD+STR+' '
    return SORT_CARD

#---------------------------------------------------
#function to calculate combined limits
#---------------------------------------------------
def calcPlotCombinedLimits(CHANNEL_ARRAY, IN_FILE_DIR_ARRAY, HIST_DIR_ARRAY, MASS_ARRAY, MY_LIMIT_DIR):
    COMB_CHANNEL_NAME = '_'.join(CHANNEL_ARRAY)
    HIST_ARRAY = []
    for HIST in range(len(HIST_DIR_ARRAY)):
        HIST_ARRAY.append(HIST_DIR_ARRAY[HIST][1])
    COMB_HIST_NAME = '_'.join(HIST_ARRAY)
    getCardsToBeCombined_ = getCardsToBeCombined(CHANNEL_ARRAY, IN_FILE_DIR_ARRAY, HIST_DIR_ARRAY, MASS_ARRAY)
    for MASS in range(len(MASS_ARRAY)):
        sortCardsForCombine_ = sortCardsForCombine(getCardsToBeCombined_, CHANNEL_ARRAY, HIST_DIR_ARRAY, MASS)
        print sortCardsForCombine_
        #COMB_DATACARD_NAME = 'datacard_csbar_'+COMB_CHANNEL_NAME+'_'+COMB_HIST_NAME+'_13TeV_mH'+str(MASS_ARRAY[MASS])
        COMB_DATACARD_NAME = 'combine_13TeV_mH'+str(MASS_ARRAY[MASS])
        if len(CHANNEL_ARRAY)>1 or len(HIST_ARRAY)>1:
            execme('combineCards.py '+sortCardsForCombine_+' > '+COMB_DATACARD_NAME+'.txt')
    calcLimits(COMB_CHANNEL_NAME, COMB_HIST_NAME, MASS_ARRAY, MY_LIMIT_DIR)
    #plotLimts(COMB_CHANNEL_NAME, MY_LIMIT_DIR)

#---------------------------------------------
#USERS INPUTS
#---------------------------------------------
isSepLimit = False
isCombLimit = True
muon_lumi = 35.9
ele_lumi = 35.9
muon_file_dir="stack_20180418_Mu_Sys_PreApp_5bJetPtBins"
#muon_file_dir="stack_20180418_Mu_Sys_PreAppComent"
ele_file_dir="stack_20180418_Ele_Sys_PreApp_5bJetPtBins"
#ele_file_dir="stack_20180418_Ele_Sys_PreAppComent"
mu_channel_array = ["mu"]
mu_file_array = [muon_file_dir]
ele_channel_array = ["ele"]
ele_file_array = [ele_file_dir]
mu_ele_channel_array = ["mu", "ele"]
mu_ele_file_array = [muon_file_dir, ele_file_dir]

hist_array_CTagCat = []
hist_array_CTagCat.append(["KinFit", "mjj_kfit_CTagL_SF_Cat"])
hist_array_CTagCat.append(["KinFit", "mjj_kfit_CTagM_SF_Cat"])
hist_array_CTagCat.append(["KinFit", "mjj_kfit_CTagT_SF_Cat"])

'''
hist_array_bJetPtCat = []
hist_array_bJetPtCat.append(["PtbJetInc", "mjj_kfit_25To35"])
hist_array_bJetPtCat.append(["PtbJetInc", "mjj_kfit_35To42"])
hist_array_bJetPtCat.append(["PtbJetInc", "mjj_kfit_42To50"])
hist_array_bJetPtCat.append(["PtbJetInc", "mjj_kfit_50To57"])
hist_array_bJetPtCat.append(["PtbJetInc", "mjj_kfit_57To65"])
hist_array_bJetPtCat.append(["PtbJetInc", "mjj_kfit_65To74"])
hist_array_bJetPtCat.append(["PtbJetInc", "mjj_kfit_74To84"])
hist_array_bJetPtCat.append(["PtbJetInc", "mjj_kfit_84To99"])
hist_array_bJetPtCat.append(["PtbJetInc", "mjj_kfit_99To124"])
hist_array_bJetPtCat.append(["PtbJetInc", "mjj_kfit_124To500"])

hist_array_CTagCat_bJetPtCat = []
hist_array_CTagCat_bJetPtCat.append(["PtbJetCatL", "mjj_kfit_25To35"])
hist_array_CTagCat_bJetPtCat.append(["PtbJetCatL", "mjj_kfit_35To42"])
hist_array_CTagCat_bJetPtCat.append(["PtbJetCatL", "mjj_kfit_42To50"])
hist_array_CTagCat_bJetPtCat.append(["PtbJetCatL", "mjj_kfit_50To57"])
hist_array_CTagCat_bJetPtCat.append(["PtbJetCatL", "mjj_kfit_57To65"])
hist_array_CTagCat_bJetPtCat.append(["PtbJetCatL", "mjj_kfit_65To74"])
hist_array_CTagCat_bJetPtCat.append(["PtbJetCatL", "mjj_kfit_74To84"])
hist_array_CTagCat_bJetPtCat.append(["PtbJetCatL", "mjj_kfit_84To99"])
hist_array_CTagCat_bJetPtCat.append(["PtbJetCatL", "mjj_kfit_99To124"])
hist_array_CTagCat_bJetPtCat.append(["PtbJetCatL", "mjj_kfit_124To500"])

hist_array_CTagCat_bJetPtCat.append(["PtbJetCatM", "mjj_kfit_25To35"])
hist_array_CTagCat_bJetPtCat.append(["PtbJetCatM", "mjj_kfit_35To42"])
hist_array_CTagCat_bJetPtCat.append(["PtbJetCatM", "mjj_kfit_42To50"])
hist_array_CTagCat_bJetPtCat.append(["PtbJetCatM", "mjj_kfit_50To57"])
hist_array_CTagCat_bJetPtCat.append(["PtbJetCatM", "mjj_kfit_57To65"])
hist_array_CTagCat_bJetPtCat.append(["PtbJetCatM", "mjj_kfit_65To74"])
hist_array_CTagCat_bJetPtCat.append(["PtbJetCatM", "mjj_kfit_74To84"])
hist_array_CTagCat_bJetPtCat.append(["PtbJetCatM", "mjj_kfit_84To99"])
hist_array_CTagCat_bJetPtCat.append(["PtbJetCatM", "mjj_kfit_99To124"])
hist_array_CTagCat_bJetPtCat.append(["PtbJetCatM", "mjj_kfit_124To500"])

hist_array_CTagCat_bJetPtCat.append(["PtbJetCatT", "mjj_kfit_25To35"])
hist_array_CTagCat_bJetPtCat.append(["PtbJetCatT", "mjj_kfit_35To42"])
hist_array_CTagCat_bJetPtCat.append(["PtbJetCatT", "mjj_kfit_42To50"])
hist_array_CTagCat_bJetPtCat.append(["PtbJetCatT", "mjj_kfit_50To57"])
hist_array_CTagCat_bJetPtCat.append(["PtbJetCatT", "mjj_kfit_57To65"])
hist_array_CTagCat_bJetPtCat.append(["PtbJetCatT", "mjj_kfit_65To74"])
hist_array_CTagCat_bJetPtCat.append(["PtbJetCatT", "mjj_kfit_74To84"])
hist_array_CTagCat_bJetPtCat.append(["PtbJetCatT", "mjj_kfit_84To99"])
hist_array_CTagCat_bJetPtCat.append(["PtbJetCatT", "mjj_kfit_99To124"])
hist_array_CTagCat_bJetPtCat.append(["PtbJetCatT", "mjj_kfit_124To500"])

'''
hist_array_bJetPtCat = []
hist_array_bJetPtCat.append(["PtbJetInc", "mjj_kfit_25To42"])
hist_array_bJetPtCat.append(["PtbJetInc", "mjj_kfit_42To57"])
hist_array_bJetPtCat.append(["PtbJetInc", "mjj_kfit_57To74"])
hist_array_bJetPtCat.append(["PtbJetInc", "mjj_kfit_74To99"])
hist_array_bJetPtCat.append(["PtbJetInc", "mjj_kfit_99To500"])

hist_array_CTagCat_bJetPtCat = []
hist_array_CTagCat_bJetPtCat.append(["PtbJetCatL", "mjj_kfit_25To42"])
hist_array_CTagCat_bJetPtCat.append(["PtbJetCatL", "mjj_kfit_42To57"])
hist_array_CTagCat_bJetPtCat.append(["PtbJetCatL", "mjj_kfit_57To74"])
hist_array_CTagCat_bJetPtCat.append(["PtbJetCatL", "mjj_kfit_74To99"])
hist_array_CTagCat_bJetPtCat.append(["PtbJetCatL", "mjj_kfit_99To500"])

hist_array_CTagCat_bJetPtCat.append(["PtbJetCatM", "mjj_kfit_25To42"])
hist_array_CTagCat_bJetPtCat.append(["PtbJetCatM", "mjj_kfit_42To57"])
hist_array_CTagCat_bJetPtCat.append(["PtbJetCatM", "mjj_kfit_57To74"])
hist_array_CTagCat_bJetPtCat.append(["PtbJetCatM", "mjj_kfit_74To99"])
hist_array_CTagCat_bJetPtCat.append(["PtbJetCatM", "mjj_kfit_99To500"])

hist_array_CTagCat_bJetPtCat.append(["PtbJetCatT", "mjj_kfit_25To42"])
hist_array_CTagCat_bJetPtCat.append(["PtbJetCatT", "mjj_kfit_42To57"])
hist_array_CTagCat_bJetPtCat.append(["PtbJetCatT", "mjj_kfit_57To74"])
hist_array_CTagCat_bJetPtCat.append(["PtbJetCatT", "mjj_kfit_74To99"])
hist_array_CTagCat_bJetPtCat.append(["PtbJetCatT", "mjj_kfit_99To500"])
#mass_array = [80, 90, 100, 120, 140, 150, 155, 160]

mass_array = [MASS_POINT_]
channel_cat = "CHANNEL__CAT_"
###########################################
# calculate and plot separate limits
###########################################
if(isSepLimit):
    for shape in hist_array:
        #make datacards
        #makeDataCards("mu", muon_file_dir, shape)
        makeDataCards("ele", ele_file_dir, shape)
        
        #calc limits
        #calcLimits("mu",  shape, mass_array)
        calcLimits("ele", shape, mass_array)
        
        #plot limits
        plotLimts("ele", shape)

###########################################
# calculate, plot combined limits
###########################################
if(isCombLimit):
    # Exclusive Mjj in charm tag category
    if(channel_cat=="MuChannel_CTagCat"):
        calcPlotCombinedLimits(mu_channel_array, mu_file_array, hist_array_CTagCat, mass_array, "mjj_CTagCat")
    if(channel_cat=="EleChannel_CTagCat"):
        calcPlotCombinedLimits(ele_channel_array, ele_file_array, hist_array_CTagCat, mass_array, "mjj_CTagCat")
    if(channel_cat=="LepChannel_CTagCat"):
        calcPlotCombinedLimits(mu_ele_channel_array, mu_ele_file_array, hist_array_CTagCat, mass_array, "mjj_CTagCat")

        # Exclusive Mjj in bins of bjet-Pt
    if(channel_cat=="MuChannel_bJetPtCat"):
        calcPlotCombinedLimits(mu_channel_array, mu_file_array, hist_array_bJetPtCat, mass_array, "mjj_bJetPtCat")
    if(channel_cat=="EleChannel_bJetPtCat"):
        calcPlotCombinedLimits(ele_channel_array, ele_file_array, hist_array_bJetPtCat, mass_array, "mjj_bJetPtCat")
    if(channel_cat=="LepChannel_bJetPtCat"):
        calcPlotCombinedLimits(mu_ele_channel_array, mu_ele_file_array, hist_array_bJetPtCat, mass_array, "mjj_bJetPtCat")

        # Exclusive Mjj in charm tag category in bins of bjet-Pt
    if(channel_cat=="MuChannel_BothCat"):
        calcPlotCombinedLimits(mu_channel_array, mu_file_array, hist_array_CTagCat_bJetPtCat, mass_array, "mjj_CTagCat_bJetPtCat")
    if(channel_cat=="EleChannel_BothCat"):
        calcPlotCombinedLimits(ele_channel_array, ele_file_array, hist_array_CTagCat_bJetPtCat, mass_array, "mjj_CTagCat_bJetPtCat")
    if(channel_cat=="LepChannel_BothCat"):
        calcPlotCombinedLimits(mu_ele_channel_array, mu_ele_file_array, hist_array_CTagCat_bJetPtCat, mass_array, "mjj_CTagCat_bJetPtCat")
execme("cp ~/ARCHIVE/LimitBinned/*.C .")
