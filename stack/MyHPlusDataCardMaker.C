#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <fstream>
#include <iomanip>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <algorithm> 
#include "MyHPlusDataCardMaker.h"

//----------------------------------------//
//make data card for each mass
//----------------------------------------//
MyHPlusDataCardMaker DC;
double totLumi = 35.9;
void MyHPlusDataCardMaker(TString inFileDir="stack_20180418_Mu_Sys_PreAppComent", 
        TString histSubDir_="KinFit", 
        TString histName="mjj_kfit", 
        TString channelName="mu", 
        int mass=80, 
        TString label="WH80", 
        TString hPlusFileName="all_Hplus80.root")
  {
  //TString baseDir = "topPtWeight";
  TString baseDir = "base";
  TString histSubDir = "Iso/"+histSubDir_+"/";
  bool isMuChannel = false; 
  if(channelName=="mu") isMuChannel = true;
  ///INPUT FILES
  TFile* fData    = TFile::Open(inFileDir+"/all_Data.root");
  //bkg
  TFile* fVV      = TFile::Open(inFileDir+"/all_VV.root");
  TFile* fDY      = TFile::Open(inFileDir+"/all_DY.root");
  TFile* fWJ      = TFile::Open(inFileDir+"/all_WJets.root");
  TFile* fQCD     = TFile::Open(inFileDir+"/all_QCD.root");
  TFile* fST      = TFile::Open(inFileDir+"/all_ST.root");
  TFile* fTT      = TFile::Open(inFileDir+"/all_TTJetsP.root");
  TFile* fTT_up      	= TFile::Open(inFileDir+"/all_TTJetsP_up.root");
  TFile* fTT_down      	= TFile::Open(inFileDir+"/all_TTJetsP_down.root");
  TFile* fTT_mtop1715     = TFile::Open(inFileDir+"/all_TTJetsP_mtop1715.root");
  TFile* fTT_mtop1735     = TFile::Open(inFileDir+"/all_TTJetsP_mtop1735.root");
  TFile* fTT_hdampUP      = TFile::Open(inFileDir+"/all_TTJetsP_hdampUP.root");
  TFile* fTT_hdampDOWN    = TFile::Open(inFileDir+"/all_TTJetsP_hdampDOWN.root");
  //signal
  TFile *fWH  = TFile::Open(inFileDir+"/"+hPlusFileName);
  //data driven qcd
  TFile* fQCD_dd = TFile::Open(inFileDir+"/all_QCD_dd.root"); 
  
  //OUTPUT FILE
  TFile *fout = new TFile(TString("Shapes_hcs_13TeV_")+channelName+TString("_")+histSubDir_+TString("_")+histName+TString("_")+label+TString(".root"), "RECREATE");

  //For one extra NP
  bool isExL = false;
  bool isExM = false;
  if(histName.Contains("ExL")) isExL = true;
  if(histName.Contains("ExM")) isExM = true;

  //ttbar
  double sf_ttbar = 1.0; 
  TH1F* ttbar = DC.readWriteHisto(fTT, baseDir+"/"+histSubDir, histName, sf_ttbar, fout, fTT,  "ttbar", true);
  TH1F* ttbar_JESUp = DC.readWriteHisto(fTT, "JESPlus/"+histSubDir, histName, sf_ttbar, fout, fTT, "ttbar_JESUp", true);
  TH1F* ttbar_JESDown = DC.readWriteHisto(fTT, "JESMinus/"+histSubDir, histName, sf_ttbar, fout, fTT, "ttbar_JESDown", true);
  TH1F* ttbar_PileupUp = DC.readWriteHisto(fTT, "PileupPlus/"+histSubDir, histName, sf_ttbar, fout, fTT, "ttbar_PileupUp", true);
  TH1F* ttbar_PileupDown = DC.readWriteHisto(fTT, "PileupMinus/"+histSubDir, histName, sf_ttbar, fout, fTT, "ttbar_PileupDown", true);
  TH1F* ttbar_JERUp = DC.readWriteHisto(fTT, "JERPlus/"+histSubDir, histName, sf_ttbar, fout, fTT, "ttbar_JERUp", true);
  TH1F* ttbar_JERDown = DC.readWriteHisto(fTT, "JERMinus/"+histSubDir, histName, sf_ttbar, fout, fTT, "ttbar_JERDown", true);
  TH1F* ttbar_topPtUp = DC.readWriteHisto(fTT, "TopPtPlus/"+histSubDir, histName, sf_ttbar, fout, fTT, "ttbar_topPtUp", true);
  TH1F* ttbar_topPtDown = DC.readWriteHisto(fTT, "TopPtMinus/"+histSubDir, histName, sf_ttbar, fout, fTT, "ttbar_topPtDown", true);
  TH1F* ttbar_bcTag1Up = DC.readWriteHisto(fTT, "bcTagPlus1/"+histSubDir, histName, sf_ttbar, fout, fTT, "ttbar_bcTag1Up", true);
  TH1F* ttbar_bcTag1Down = DC.readWriteHisto(fTT, "bcTagMinus1/"+histSubDir, histName, sf_ttbar, fout, fTT, "ttbar_bcTag1Down", true);
  TH1F* ttbar_bcTag2Up = DC.readWriteHisto(fTT, "bcTagPlus2/"+histSubDir, histName, sf_ttbar, fout, fTT, "ttbar_bcTag2Up", true);
  TH1F* ttbar_bcTag2Down = DC.readWriteHisto(fTT, "bcTagMinus2/"+histSubDir, histName, sf_ttbar, fout, fTT, "ttbar_bcTag2Down", true);
  TH1F* ttbar_bcTag3Up = DC.readWriteHisto(fTT, "bcTagPlus3/"+histSubDir, histName, sf_ttbar, fout, fTT, "ttbar_bcTag3Up", true);
  TH1F* ttbar_bcTag3Down = DC.readWriteHisto(fTT, "bcTagMinus3/"+histSubDir, histName, sf_ttbar, fout, fTT, "ttbar_bcTag3Down", true);
  
  double unc_ttbar_ExL = 1.0;
  double unc_ttbar_ExM = 1.0;
  if(isExL){
    TH1F* ttbar_yLyMyT = DC.getHisto(fTT, baseDir+"/Iso/ExCTag/", "sf_CTag_yLyMyT_wt", fTT);
    TH1F* ttbar_yLyMnT = DC.getHisto(fTT, baseDir+"/Iso/ExCTag/", "sf_CTag_yLyMnT_wt", fTT);
    TH1F* ttbar_yLnMyT = DC.getHisto(fTT, baseDir+"/Iso/ExCTag/", "sf_CTag_yLnMyT_wt", fTT);
    TH1F* ttbar_yLnMnT = DC.getHisto(fTT, baseDir+"/Iso/ExCTag/", "sf_CTag_yLnMnT_wt", fTT);
    unc_ttbar_ExL = DC.getUncExL(ttbar_yLyMyT, ttbar_yLyMnT, ttbar_yLnMyT, ttbar_yLnMnT);
  }
  if(isExM){
    TH1F* ttbar_yMyT = DC.getHisto(fTT, baseDir+"/Iso/ExCTag/", "sf_CTag_yMyT_wt", fTT);
    TH1F* ttbar_yMnT = DC.getHisto(fTT, baseDir+"/Iso/ExCTag/", "sf_CTag_yMnT_wt", fTT);
    unc_ttbar_ExM = DC.getUncExM(ttbar_yMyT, ttbar_yMnT);
  }
  //ttbar scaleUp
  double sf_ttbar_scaleUp = 1; 
  TH1F* ttbar_scaleUp = DC.readWriteHisto(fTT_up, baseDir+"/"+histSubDir, histName, sf_ttbar_scaleUp, fout, fTT, "ttbar_scaleRF_ttUp", true);
  //ttbar scaleDown
  double sf_ttbar_scaleDown = 1; 
  TH1F* ttbar_scaleDown = DC.readWriteHisto(fTT_down, baseDir+"/"+histSubDir, histName, sf_ttbar_scaleDown, fout, fTT, "ttbar_scaleRF_ttDown", true);
  //ttbar mtop1715
  double sf_ttbar_mtop1715 = 1; 
  TH1F* ttbar_mtop1715 = DC.readWriteHisto(fTT_mtop1715, baseDir+"/"+histSubDir, histName, sf_ttbar_mtop1715, fout, fTT, "ttbar_topMass_ttUp", true);
  //ttbar mtop1735
  double sf_ttbar_mtop1735 = 1; 
  TH1F* ttbar_mtop1735 = DC.readWriteHisto(fTT_mtop1735, baseDir+"/"+histSubDir, histName, sf_ttbar_mtop1735, fout, fTT, "ttbar_topMass_ttDown", true);
  //ttbar matchingUp
  double sf_ttbar_matchingUp = 1; 
  TH1F* ttbar_matchingUp = DC.readWriteHisto(fTT_hdampUP, baseDir+"/"+histSubDir, histName, sf_ttbar_matchingUp, fout, fTT, "ttbar_hDamp_ttUp", true);
  //ttbar matchingDown
  double sf_ttbar_matchingDown = 1; 
  TH1F* ttbar_matchingDown = DC.readWriteHisto(fTT_hdampDOWN, baseDir+"/"+histSubDir, histName, sf_ttbar_matchingDown, fout, fTT, "ttbar_hDamp_ttDown", true);

  //w+jets
  double sf_wjet = 1;
  TH1F* wjet = DC.readWriteHisto(fWJ, baseDir+"/"+histSubDir, histName, sf_wjet, fout, fTT, "wjet", true);
  TH1F* wjet_JESUp = DC.readWriteHisto(fWJ, "JESPlus/"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_JESUp", true);
  TH1F* wjet_JESDown = DC.readWriteHisto(fWJ, "JESMinus/"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_JESDown", true);
  TH1F* wjet_PileupUp = DC.readWriteHisto(fWJ, "PileupPlus/"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_PileupUp", true);
  TH1F* wjet_PileupDown = DC.readWriteHisto(fWJ, "PileupMinus/"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_PileupDown", true);
  TH1F* wjet_JERUp = DC.readWriteHisto(fWJ, "JERPlus/"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_JERUp", true);
  TH1F* wjet_JERDown = DC.readWriteHisto(fWJ, "JERMinus/"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_JERDown", true);
  TH1F* wjet_bcTag1Up = DC.readWriteHisto(fWJ, "bcTagPlus1/"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_bcTag1Up", true);
  TH1F* wjet_bcTag1Down = DC.readWriteHisto(fWJ, "bcTagMinus1/"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_bcTag1Down", true); 
  TH1F* wjet_bcTag2Up = DC.readWriteHisto(fWJ, "bcTagPlus2/"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_bcTag2Up", true);
  TH1F* wjet_bcTag2Down = DC.readWriteHisto(fWJ, "bcTagMinus2/"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_bcTag2Down", true); 
  TH1F* wjet_bcTag3Up = DC.readWriteHisto(fWJ, "bcTagPlus3/"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_bcTag3Up", true);
  TH1F* wjet_bcTag3Down = DC.readWriteHisto(fWJ, "bcTagMinus3/"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_bcTag3Down", true); 
  double unc_wjet_ExL = 1.0;
  double unc_wjet_ExM = 1.0;
  if(isExL){
    TH1F* wjet_yLyMyT = DC.getHisto(fWJ, baseDir+"/Iso/ExCTag/", "sf_CTag_yLyMyT_wt", fTT);
    TH1F* wjet_yLyMnT = DC.getHisto(fWJ, baseDir+"/Iso/ExCTag/", "sf_CTag_yLyMnT_wt", fTT);
    TH1F* wjet_yLnMyT = DC.getHisto(fWJ, baseDir+"/Iso/ExCTag/", "sf_CTag_yLnMyT_wt", fTT);
    TH1F* wjet_yLnMnT = DC.getHisto(fWJ, baseDir+"/Iso/ExCTag/", "sf_CTag_yLnMnT_wt", fTT);
    unc_wjet_ExL = DC.getUncExL(wjet_yLyMyT, wjet_yLyMnT, wjet_yLnMyT, wjet_yLnMnT);
  }
  if(isExM){
    TH1F* wjet_yMyT = DC.getHisto(fWJ, baseDir+"/Iso/ExCTag/", "sf_CTag_yMyT_wt", fTT);
    TH1F* wjet_yMnT = DC.getHisto(fWJ, baseDir+"/Iso/ExCTag/", "sf_CTag_yMnT_wt", fTT);
    unc_wjet_ExM = DC.getUncExM(wjet_yMyT, wjet_yMnT);
  }

  //Z+Jets
  double sf_zjet = 1;
  TH1F* zjet = DC.readWriteHisto(fDY, baseDir+"/"+histSubDir, histName, sf_zjet, fout, fTT, "zjet", true);
  TH1F* zjet_JESUp = DC.readWriteHisto(fDY, "JESPlus/"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_JESUp", true);
  TH1F* zjet_JESDown = DC.readWriteHisto(fDY, "JESMinus/"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_JESDown", true);
  TH1F* zjet_PileupUp = DC.readWriteHisto(fDY, "PileupPlus/"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_PileupUp", true);
  TH1F* zjet_PileupDown = DC.readWriteHisto(fDY, "PileupMinus/"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_PileupDown", true);
  TH1F* zjet_JERUp = DC.readWriteHisto(fDY, "JERPlus/"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_JERUp", true);
  TH1F* zjet_JERDown = DC.readWriteHisto(fDY, "JERMinus/"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_JERDown", true);
  TH1F* zjet_bcTag1Up = DC.readWriteHisto(fDY, "bcTagPlus1/"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_bcTag1Up", true);
  TH1F* zjet_bcTag1Down = DC.readWriteHisto(fDY, "bcTagMinus1/"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_bcTag1Down", true);
  TH1F* zjet_bcTag2Up = DC.readWriteHisto(fDY, "bcTagPlus2/"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_bcTag2Up", true);
  TH1F* zjet_bcTag2Down = DC.readWriteHisto(fDY, "bcTagMinus2/"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_bcTag2Down", true);
  TH1F* zjet_bcTag3Up = DC.readWriteHisto(fDY, "bcTagPlus3/"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_bcTag3Up", true);
  TH1F* zjet_bcTag3Down = DC.readWriteHisto(fDY, "bcTagMinus3/"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_bcTag3Down", true);
  double unc_zjet_ExL = 1.0;
  double unc_zjet_ExM = 1.0;
  if(isExL){
    TH1F* zjet_yLyMyT = DC.getHisto(fDY, baseDir+"/Iso/ExCTag/", "sf_CTag_yLyMyT_wt", fTT);
    TH1F* zjet_yLyMnT = DC.getHisto(fDY, baseDir+"/Iso/ExCTag/", "sf_CTag_yLyMnT_wt", fTT);
    TH1F* zjet_yLnMyT = DC.getHisto(fDY, baseDir+"/Iso/ExCTag/", "sf_CTag_yLnMyT_wt", fTT);
    TH1F* zjet_yLnMnT = DC.getHisto(fDY, baseDir+"/Iso/ExCTag/", "sf_CTag_yLnMnT_wt", fTT);
    unc_zjet_ExL = DC.getUncExL(zjet_yLyMyT, zjet_yLyMnT, zjet_yLnMyT, zjet_yLnMnT);
  }
  if(isExM){
    TH1F* zjet_yMyT = DC.getHisto(fDY, baseDir+"/Iso/ExCTag/", "sf_CTag_yMyT_wt", fTT);
    TH1F* zjet_yMnT = DC.getHisto(fDY, baseDir+"/Iso/ExCTag/", "sf_CTag_yMnT_wt", fTT);
    unc_zjet_ExM = DC.getUncExM(zjet_yMyT, zjet_yMnT);
  }

  //SingleTop
  double sf_stop = 1.0;
  TH1F* stop = DC.readWriteHisto(fST, baseDir+"/"+histSubDir, histName, sf_stop, fout, fTT, "stop", true);
  TH1F* stop_JESUp = DC.readWriteHisto(fST, "JESPlus/"+histSubDir, histName, sf_stop, fout, fTT, "stop_JESUp", true);
  TH1F* stop_JESDown = DC.readWriteHisto(fST, "JESMinus/"+histSubDir, histName, sf_stop, fout, fTT, "stop_JESDown", true);
  TH1F* stop_PileupUp = DC.readWriteHisto(fST, "PileupPlus/"+histSubDir, histName, sf_stop, fout, fTT, "stop_PileupUp", true);
  TH1F* stop_PileupDown = DC.readWriteHisto(fST, "PileupMinus/"+histSubDir, histName, sf_stop, fout, fTT, "stop_PileupDown", true);
  TH1F* stop_JERUp = DC.readWriteHisto(fST, "JERPlus/"+histSubDir, histName, sf_stop, fout, fTT, "stop_JERUp", true);
  TH1F* stop_JERDown = DC.readWriteHisto(fST, "JERMinus/"+histSubDir, histName, sf_stop, fout, fTT, "stop_JERDown", true);
  TH1F* stop_bcTag1Up = DC.readWriteHisto(fST, "bcTagPlus1/"+histSubDir, histName, sf_stop, fout, fTT, "stop_bcTag1Up", true);
  TH1F* stop_bcTag1Down = DC.readWriteHisto(fST, "bcTagMinus1/"+histSubDir, histName, sf_stop, fout, fTT, "stop_bcTag1Down", true);
  TH1F* stop_bcTag2Up = DC.readWriteHisto(fST, "bcTagPlus2/"+histSubDir, histName, sf_stop, fout, fTT, "stop_bcTag2Up", true);
  TH1F* stop_bcTag2Down = DC.readWriteHisto(fST, "bcTagMinus2/"+histSubDir, histName, sf_stop, fout, fTT, "stop_bcTag2Down", true);
  TH1F* stop_bcTag3Up = DC.readWriteHisto(fST, "bcTagPlus3/"+histSubDir, histName, sf_stop, fout, fTT, "stop_bcTag3Up", true);
  TH1F* stop_bcTag3Down = DC.readWriteHisto(fST, "bcTagMinus3/"+histSubDir, histName, sf_stop, fout, fTT, "stop_bcTag3Down", true);
  double unc_stop_ExL = 1.0;
  double unc_stop_ExM = 1.0;
  if(isExL){
    TH1F* stop_yLyMyT = DC.getHisto(fST, baseDir+"/Iso/ExCTag/", "sf_CTag_yLyMyT_wt", fTT);
    TH1F* stop_yLyMnT = DC.getHisto(fST, baseDir+"/Iso/ExCTag/", "sf_CTag_yLyMnT_wt", fTT);
    TH1F* stop_yLnMyT = DC.getHisto(fST, baseDir+"/Iso/ExCTag/", "sf_CTag_yLnMyT_wt", fTT);
    TH1F* stop_yLnMnT = DC.getHisto(fST, baseDir+"/Iso/ExCTag/", "sf_CTag_yLnMnT_wt", fTT);
    unc_stop_ExL = DC.getUncExL(stop_yLyMyT, stop_yLyMnT, stop_yLnMyT, stop_yLnMnT);
  }
  if(isExM){
    TH1F* stop_yMyT = DC.getHisto(fST, baseDir+"/Iso/ExCTag/", "sf_CTag_yMyT_wt", fTT);
    TH1F* stop_yMnT = DC.getHisto(fST, baseDir+"/Iso/ExCTag/", "sf_CTag_yMnT_wt", fTT);
    unc_stop_ExM = DC.getUncExM(stop_yMyT, stop_yMnT);
  }

  //Dibosons
  double sf_vv = 1;
  TH1F* vv = DC.readWriteHisto(fVV, baseDir+"/"+histSubDir, histName, sf_vv, fout, fTT, "vv", true);
  TH1F* vv_JESUp = DC.readWriteHisto(fVV, "JESPlus/"+histSubDir, histName, sf_vv, fout, fTT, "vv_JESUp", true);
  TH1F* vv_JESDown = DC.readWriteHisto(fVV, "JESMinus/"+histSubDir, histName, sf_vv, fout, fTT, "vv_JESDown", true);
  TH1F* vv_PileupUp = DC.readWriteHisto(fVV, "PileupPlus/"+histSubDir, histName, sf_vv, fout, fTT, "vv_PileupUp", true);
  TH1F* vv_PileupDown = DC.readWriteHisto(fVV, "PileupMinus/"+histSubDir, histName, sf_vv, fout, fTT, "vv_PileupDown", true);
  TH1F* vv_JERUp = DC.readWriteHisto(fVV, "JERPlus/"+histSubDir, histName, sf_vv, fout, fTT, "vv_JERUp", true);
  TH1F* vv_JERDown = DC.readWriteHisto(fVV, "JERMinus/"+histSubDir, histName, sf_vv, fout, fTT, "vv_JERDown", true);
  TH1F* vv_bcTag1Up = DC.readWriteHisto(fVV, "bcTagPlus1/"+histSubDir, histName, sf_vv, fout, fTT, "vv_bcTag1Up", true);
  TH1F* vv_bcTag1Down = DC.readWriteHisto(fVV, "bcTagMinus1/"+histSubDir, histName, sf_vv, fout, fTT, "vv_bcTag1Down", true);
  TH1F* vv_bcTag2Up = DC.readWriteHisto(fVV, "bcTagPlus2/"+histSubDir, histName, sf_vv, fout, fTT, "vv_bcTag2Up", true);
  TH1F* vv_bcTag2Down = DC.readWriteHisto(fVV, "bcTagMinus2/"+histSubDir, histName, sf_vv, fout, fTT, "vv_bcTag2Down", true);
  TH1F* vv_bcTag3Up = DC.readWriteHisto(fVV, "bcTagPlus3/"+histSubDir, histName, sf_vv, fout, fTT, "vv_bcTag3Up", true);
  TH1F* vv_bcTag3Down = DC.readWriteHisto(fVV, "bcTagMinus3/"+histSubDir, histName, sf_vv, fout, fTT, "vv_bcTag3Down", true);
  double unc_vv_ExL = 1.0;
  double unc_vv_ExM = 1.0;
  if(isExL){
    TH1F* vv_yLyMyT = DC.getHisto(fVV, baseDir+"/Iso/ExCTag/", "sf_CTag_yLyMyT_wt", fTT);
    TH1F* vv_yLyMnT = DC.getHisto(fVV, baseDir+"/Iso/ExCTag/", "sf_CTag_yLyMnT_wt", fTT);
    TH1F* vv_yLnMyT = DC.getHisto(fVV, baseDir+"/Iso/ExCTag/", "sf_CTag_yLnMyT_wt", fTT);
    TH1F* vv_yLnMnT = DC.getHisto(fVV, baseDir+"/Iso/ExCTag/", "sf_CTag_yLnMnT_wt", fTT);
    unc_vv_ExL = DC.getUncExL(vv_yLyMyT, vv_yLyMnT, vv_yLnMyT, vv_yLnMnT);
  }
  if(isExM){
    TH1F* vv_yMyT = DC.getHisto(fVV, baseDir+"/Iso/ExCTag/", "sf_CTag_yMyT_wt", fTT);
    TH1F* vv_yMnT = DC.getHisto(fVV, baseDir+"/Iso/ExCTag/", "sf_CTag_yMnT_wt", fTT);
    unc_vv_ExM = DC.getUncExM(vv_yMyT, vv_yMnT);
  }

  //QCD MC
  double sf_qcd = 1.0;
  /*
  TH1F* qcd = DC.readWriteHisto(fQCD, baseDir+"/"+histSubDir, histName, sf_qcd, fout, fTT, "qcd", true);
  TH1F* qcd_JESUp = DC.readWriteHisto(fQCD, "JESPlus/"+histSubDir, histName, sf_qcd, fout, fTT, "qcd_JESUp", true);
  TH1F* qcd_JESDown = DC.readWriteHisto(fQCD, "JESMinus/"+histSubDir, histName, sf_qcd, fout, fTT, "qcd_JESDown", true);
  TH1F* qcd_PileupUp = DC.readWriteHisto(fQCD, "PileupPlus/"+histSubDir, histName, sf_qcd, fout, fTT, "qcd_PileupUp", true);
  TH1F* qcd_PileupDown = DC.readWriteHisto(fQCD, "PileupMinus/"+histSubDir, histName, sf_qcd, fout, fTT, "qcd_PileupDown", true);
  TH1F* qcd_JERUp = DC.readWriteHisto(fQCD, "JERPlus/"+histSubDir, histName, sf_qcd, fout, fTT, "qcd_JERUp", true);
  TH1F* qcd_JERDown = DC.readWriteHisto(fQCD, "JERMinus/"+histSubDir, histName, sf_qcd, fout, fTT, "qcd_JERDown", true);
  TH1F* qcd_bcTag1Up = DC.readWriteHisto(fQCD, "bcTagPlus1/"+histSubDir, histName, sf_qcd, fout, fTT, "qcd_bcTag1Up", true);
  TH1F* qcd_bcTag1Down = DC.readWriteHisto(fQCD, "bcTagMinus1/"+histSubDir, histName, sf_qcd, fout, fTT, "qcd_bcTag1Down", true);
  TH1F* qcd_bcTag2Up = DC.readWriteHisto(fQCD, "bcTagPlus2/"+histSubDir, histName, sf_qcd, fout, fTT, "qcd_bcTag2Up", true);
  TH1F* qcd_bcTag2Down = DC.readWriteHisto(fQCD, "bcTagMinus2/"+histSubDir, histName, sf_qcd, fout, fTT, "qcd_bcTag2Down", true);
  TH1F* qcd_bcTag3Up = DC.readWriteHisto(fQCD, "bcTagPlus3/"+histSubDir, histName, sf_qcd, fout, fTT, "qcd_bcTag3Up", true);
  TH1F* qcd_bcTag3Down = DC.readWriteHisto(fQCD, "bcTagMinus3/"+histSubDir, histName, sf_qcd, fout, fTT, "qcd_bcTag3Down", true);
  */
  //QCD data driven
  //cout<<baseDir+"/"+histSubDir+"/"+histName<<endl;
  TH1F* qcd_dd = DC.readWriteHisto(fQCD_dd, baseDir+"/"+histSubDir, histName, sf_qcd, fout, fTT, "qcd", true);
  double stat_unc_qcd = DC.getStatUnc(qcd_dd, 0);
  cout<<"qcd stat unc: "<<stat_unc_qcd<<endl;
  cout<<"qcd = "<<qcd_dd->Integral()<<endl;
  double qcd_unc = DC.getSysUncQcd(fData, fTT, fST, fWJ, fDY,  fVV, histSubDir_+"/", histName, false);

  //Data
  double sf_data = 1.0; //should be 1, always
  TH1F* data_obs = DC.readWriteHisto(fData, baseDir+"/"+histSubDir, histName, sf_data, fout, fTT, "data_obs", true);
  cout<<"================: "<<data_obs->Integral()<<endl;

  //wh
  //double sf_wh = 1.0;
  double sf_wh = 1.0/0.12155; //2*0.065*(1-0.065) 
  TH1F* wh = DC.readWriteHisto(fWH, baseDir+"/"+histSubDir, histName, sf_wh, fout, fTT, label, true);
  TH1F* wh_JESUp = DC.readWriteHisto(fWH, "JESPlus/"+histSubDir, histName, sf_wh, fout, fTT, label+"_JESUp", true);
  TH1F* wh_JESDown = DC.readWriteHisto(fWH, "JESMinus/"+histSubDir, histName, sf_wh, fout, fTT, label+"_JESDown", true);
  TH1F* wh_PileupUp = DC.readWriteHisto(fWH, "PileupPlus/"+histSubDir, histName, sf_wh, fout, fTT, label+"_PileupUp", true);
  TH1F* wh_PileupDown = DC.readWriteHisto(fWH, "PileupMinus/"+histSubDir, histName, sf_wh, fout, fTT, label+"_PileupDown", true);
  TH1F* wh_JERUp = DC.readWriteHisto(fWH, "JERPlus/"+histSubDir, histName, sf_wh, fout, fTT, label+"_JERUp", true);
  TH1F* wh_JERDown = DC.readWriteHisto(fWH, "JERMinus/"+histSubDir, histName, sf_wh, fout, fTT, label+"_JERDown", true);
  TH1F* wh_topPtUp = DC.readWriteHisto(fWH,  "TopPtPlus/"+histSubDir, histName, sf_wh, fout, fTT, label+"_topPtUp", true);
  TH1F* wh_topPtDown = DC.readWriteHisto(fWH, "TopPtMinus/"+histSubDir, histName, sf_wh, fout, fTT, label+"_topPtDown", true);
  TH1F* wh_bcTag1Up = DC.readWriteHisto(fWH, "bcTagPlus1/"+histSubDir, histName, sf_wh, fout, fTT, label+"_bcTag1Up", true);
  TH1F* wh_bcTag1Down = DC.readWriteHisto(fWH, "bcTagMinus1/"+histSubDir, histName, sf_wh, fout, fTT, label+"_bcTag1Down", true);
  TH1F* wh_bcTag2Up = DC.readWriteHisto(fWH, "bcTagPlus2/"+histSubDir, histName, sf_wh, fout, fTT, label+"_bcTag2Up", true);
  TH1F* wh_bcTag2Down = DC.readWriteHisto(fWH, "bcTagMinus2/"+histSubDir, histName, sf_wh, fout, fTT, label+"_bcTag2Down", true);
  TH1F* wh_bcTag3Up = DC.readWriteHisto(fWH, "bcTagPlus3/"+histSubDir, histName, sf_wh, fout, fTT, label+"_bcTag3Up", true);
  TH1F* wh_bcTag3Down = DC.readWriteHisto(fWH, "bcTagMinus3/"+histSubDir, histName, sf_wh, fout, fTT, label+"_bcTag3Down", true);
  double unc_wh_ExL = 1.0;
  double unc_wh_ExM = 1.0;
  if(isExL){
    TH1F* wh_yLyMyT = DC.getHisto(fWH, baseDir+"/Iso/ExCTag/", "sf_CTag_yLyMyT_wt", fTT, sf_wh);
    TH1F* wh_yLyMnT = DC.getHisto(fWH, baseDir+"/Iso/ExCTag/", "sf_CTag_yLyMnT_wt", fTT, sf_wh);
    TH1F* wh_yLnMyT = DC.getHisto(fWH, baseDir+"/Iso/ExCTag/", "sf_CTag_yLnMyT_wt", fTT, sf_wh);
    TH1F* wh_yLnMnT = DC.getHisto(fWH, baseDir+"/Iso/ExCTag/", "sf_CTag_yLnMnT_wt", fTT, sf_wh);
    unc_wh_ExL = DC.getUncExL(wh_yLyMyT, wh_yLyMnT, wh_yLnMyT, wh_yLnMnT);
  }
  if(isExM){
    TH1F* wh_yMyT = DC.getHisto(fWH, baseDir+"/Iso/ExCTag/", "sf_CTag_yMyT_wt", fTT, sf_wh);
    TH1F* wh_yMnT = DC.getHisto(fWH, baseDir+"/Iso/ExCTag/", "sf_CTag_yMnT_wt", fTT, sf_wh);
    unc_wh_ExM = DC.getUncExM(wh_yMyT, wh_yMnT);
  }
  //open input template data card
  ifstream in;
  char* c = new char[1000];
  in.open("MyTemplateDataCard.txt");
  //create output data card for 13 TeV
  string outDataCard = "datacard_hcs_13TeV_WH.txt";
  string histName_str(histSubDir_+TString("_")+histName);
  if(isMuChannel) outDataCard = "datacard_hcs_13TeV_mu_"+histName_str+"_WH%d.txt"; 
  else outDataCard = "datacard_hcs_13TeV_ele_"+histName_str+"_WH%d.txt";
  ofstream out(Form(outDataCard.c_str(), mass));
  out.precision(8);

  time_t secs=time(0);
  tm *t=localtime(&secs);
  while (in.good()){
    in.getline(c,1000,'\n');
    if (in.good()){
      string line(c);
      if(line.find("Date")!=string::npos){
        string day = string(Form("%d",t->tm_mday));
        string month = string(Form("%d",t->tm_mon+1));
        string year = string(Form("%d",t->tm_year+1900));
        line.replace( line.find("XXX") , 3 , day+"/"+month+"/"+year);
        out << line << endl;
      }
      else if(line.find("Description")!=string::npos){
        line.replace( line.find("YYY") , 3 , string(Form("%d", mass)) );
        line.replace( line.find("ZZZ") , 3 , string(Form("%f", totLumi)) ); 
        line.replace( line.find("CCC") , 3 , string(Form("%s", string(channelName).c_str())) ); 
        out << line << endl;
      }
      else if(line.find("shapes")!=string::npos){
        line.replace( line.find("XXX") , 3 , string(TString("Shapes_hcs_13TeV_")+channelName+TString("_")+histSubDir_+TString("_")+histName+TString("_")+label));
        out << line << endl;
      }
      else if(line.find("Observation")!=string::npos){
        line.replace( line.find("XXX") , 3 , string(Form("%.0f", data_obs->Integral())));
        out << line << endl;
      }
      else if(line.find("process")!=string::npos && line.find("WH")!=string::npos){
        line.replace( line.find("YYY") , 3 , string(Form("%d", mass)) );
        out << line << endl;
      }
      else if(line.find("rate")!=string::npos){
        string rate = "rate               ";  
        string space = "     ";
        out << rate ;
        out << space << wh->Integral()
            << space << ttbar->Integral()
            << space << wjet->Integral()
            << space << zjet->Integral()
            << space << stop->Integral()
            << space << vv->Integral()
            << space << qcd_dd->Integral()
            << endl;
      }
      else if(line.find("CMS_eff_lep")!=string::npos){  
        if(isMuChannel) line.replace( line.find("lep") , 4 , string(Form("%s", "m")));   
        else line.replace( line.find("lep") , 4 , string(Form("%s", "e")));
        out << line << endl;
      }  
      else if(line.find("CMS_eff_bcInc1")!=string::npos){
        float bTagUnc_wh = (wh->Integral() > 0) ? DC.getBTagUnc(wh, wh_bcTag1Up, wh_bcTag1Down) : 1.00;
        line.replace( line.find("HHHH") , 4 , string(Form("%.3f", bTagUnc_wh)) );
        
        float bTagUnc_ttbar = (ttbar->Integral() > 0) ? DC.getBTagUnc(ttbar, ttbar_bcTag1Up, ttbar_bcTag1Down) : 1.00; 
        line.replace( line.find("TTTT") , 4 , string(Form("%.3f", bTagUnc_ttbar)) ); 
        
        float bTagUnc_wjet = (wjet->Integral() > 0) ? DC.getBTagUnc(wjet, wjet_bcTag1Up, wjet_bcTag1Down) : 1.00;
        line.replace( line.find("WWWW") , 4 , string(Form("%.3f", bTagUnc_wjet)) ); 
       
        float bTagUnc_zjet = (zjet->Integral() > 0) ? DC.getBTagUnc(zjet, zjet_bcTag1Up, zjet_bcTag1Down) : 1.00;
        line.replace( line.find("DDDD") , 4 , string(Form("%.3f", bTagUnc_zjet)) ); 

        float bTagUnc_stop = (stop->Integral() > 0) ? DC.getBTagUnc(stop, stop_bcTag1Up, stop_bcTag1Down) : 1.00; 
        line.replace( line.find("SSSS") , 4 , string(Form("%.3f", bTagUnc_stop)) ); 

        float bTagUnc_vv = (vv->Integral() > 0) ? DC.getBTagUnc(vv, vv_bcTag1Up, vv_bcTag1Down) : 1.00;
        line.replace( line.find("VVVV") , 4 , string(Form("%.3f", bTagUnc_vv)) ); 
        out << line << endl;
      }
      else if(line.find("CMS_eff_bcInc2")!=string::npos){
        float cTagUnc_wh = (wh->Integral() > 0) ? DC.getBTagUnc(wh, wh_bcTag2Up, wh_bcTag2Down) : 1.00;
        line.replace( line.find("HHHH") , 4 , string(Form("%.3f", cTagUnc_wh)) );
        
        float cTagUnc_ttbar = (ttbar->Integral() > 0) ? DC.getBTagUnc(ttbar, ttbar_bcTag2Up, ttbar_bcTag2Down) : 1.00; 
        line.replace( line.find("TTTT") , 4 , string(Form("%.3f", cTagUnc_ttbar)) ); 
        
        float cTagUnc_wjet = (wjet->Integral() > 0) ? DC.getBTagUnc(wjet, wjet_bcTag2Up, wjet_bcTag2Down) : 1.00;
        line.replace( line.find("WWWW") , 4 , string(Form("%.3f", cTagUnc_wjet)) ); 
       
        float cTagUnc_zjet = (zjet->Integral() > 0) ? DC.getBTagUnc(zjet, zjet_bcTag2Up, zjet_bcTag2Down) : 1.00;
        line.replace( line.find("DDDD") , 4 , string(Form("%.3f", cTagUnc_zjet)) ); 
        
        float cTagUnc_stop = (stop->Integral() > 0) ? DC.getBTagUnc(stop, stop_bcTag2Up, stop_bcTag2Down) : 1.00; 
        line.replace( line.find("SSSS") , 4 , string(Form("%.3f", cTagUnc_stop)) ); 

        float cTagUnc_vv = (vv->Integral() > 0) ? DC.getBTagUnc(vv, vv_bcTag2Up, vv_bcTag2Down) : 1.00;
        line.replace( line.find("VVVV") , 4 , string(Form("%.3f", cTagUnc_vv)) ); 
        out << line << endl;
      }
      else if(line.find("CMS_eff_bcInc3")!=string::npos){
        float cTagUnc_wh = (wh->Integral() > 0) ? DC.getBTagUnc(wh, wh_bcTag3Up, wh_bcTag3Down) : 1.00;
        line.replace( line.find("HHHH") , 4 , string(Form("%.3f", cTagUnc_wh)) );
        
        float cTagUnc_ttbar = (ttbar->Integral() > 0) ? DC.getBTagUnc(ttbar, ttbar_bcTag3Up, ttbar_bcTag3Down) : 1.00; 
        line.replace( line.find("TTTT") , 4 , string(Form("%.3f", cTagUnc_ttbar)) ); 
        
        float cTagUnc_wjet = (wjet->Integral() > 0) ? DC.getBTagUnc(wjet, wjet_bcTag3Up, wjet_bcTag3Down) : 1.00;
        line.replace( line.find("WWWW") , 4 , string(Form("%.3f", cTagUnc_wjet)) ); 
       
        float cTagUnc_zjet = (zjet->Integral() > 0) ? DC.getBTagUnc(zjet, zjet_bcTag3Up, zjet_bcTag3Down) : 1.00;
        line.replace( line.find("DDDD") , 4 , string(Form("%.3f", cTagUnc_zjet)) ); 
        
        float cTagUnc_stop = (stop->Integral() > 0) ? DC.getBTagUnc(stop, stop_bcTag3Up, stop_bcTag3Down) : 1.00; 
        line.replace( line.find("SSSS") , 4 , string(Form("%.3f", cTagUnc_stop)) ); 

        float cTagUnc_vv = (vv->Integral() > 0) ? DC.getBTagUnc(vv, vv_bcTag3Up, vv_bcTag3Down) : 1.00;
        line.replace( line.find("VVVV") , 4 , string(Form("%.3f", cTagUnc_vv)) ); 
        out << line << endl;
      }
      else if(line.find("CMS_pileup")!=string::npos){
        float PileupUnc_wh = (wh->Integral() > 0) ? DC.getBTagUnc(wh, wh_PileupUp, wh_PileupDown) : 1.00;
        line.replace( line.find("HHHH") , 4 , string(Form("%.3f", PileupUnc_wh)) );
        
        float PileupUnc_ttbar = (ttbar->Integral() > 0) ? DC.getBTagUnc(ttbar, ttbar_PileupUp, ttbar_PileupDown) : 1.00; 
        line.replace( line.find("TTTT") , 4 , string(Form("%.3f", PileupUnc_ttbar)) ); 
        
        float PileupUnc_wjet = (wjet->Integral() > 0) ? DC.getBTagUnc(wjet, wjet_PileupUp, wjet_PileupDown) : 1.00;
        line.replace( line.find("WWWW") , 4 , string(Form("%.3f", PileupUnc_wjet)) ); 
       
        float PileupUnc_zjet = (zjet->Integral() > 0) ? DC.getBTagUnc(zjet, zjet_PileupUp, zjet_PileupDown) : 1.00;
        line.replace( line.find("DDDD") , 4 , string(Form("%.3f", PileupUnc_zjet)) ); 
        
        float PileupUnc_stop = (stop->Integral() > 0) ? DC.getBTagUnc(stop, stop_PileupUp, stop_PileupDown) : 1.00; 
        line.replace( line.find("SSSS") , 4 , string(Form("%.3f", PileupUnc_stop)) ); 

        float PileupUnc_vv = (vv->Integral() > 0) ? DC.getBTagUnc(vv, vv_PileupUp, vv_PileupDown) : 1.00;
        line.replace( line.find("VVVV") , 4 , string(Form("%.3f", PileupUnc_vv)) ); 
        out << line << endl;
      }
      else if(line.find("CMS_scale_j")!=string::npos){
        float JESUnc_wh = (wh->Integral() > 0) ? DC.getBTagUnc(wh, wh_JESUp, wh_JESDown) : 1.00;
        line.replace( line.find("HHHH") , 4 , string(Form("%.3f", JESUnc_wh)) );
        
        float JESUnc_ttbar = (ttbar->Integral() > 0) ? DC.getBTagUnc(ttbar, ttbar_JESUp, ttbar_JESDown) : 1.00; 
        line.replace( line.find("TTTT") , 4 , string(Form("%.3f", JESUnc_ttbar)) ); 
        
        float JESUnc_wjet = (wjet->Integral() > 0) ? DC.getBTagUnc(wjet, wjet_JESUp, wjet_JESDown) : 1.00;
        line.replace( line.find("WWWW") , 4 , string(Form("%.3f", JESUnc_wjet)) ); 
       
        float JESUnc_zjet = (zjet->Integral() > 0) ? DC.getBTagUnc(zjet, zjet_JESUp, zjet_JESDown) : 1.00;
        line.replace( line.find("DDDD") , 4 , string(Form("%.3f", JESUnc_zjet)) ); 
        
        float JESUnc_stop = (stop->Integral() > 0) ? DC.getBTagUnc(stop, stop_JESUp, stop_JESDown) : 1.00; 
        line.replace( line.find("SSSS") , 4 , string(Form("%.3f", JESUnc_stop)) ); 

        float JESUnc_vv = (vv->Integral() > 0) ? DC.getBTagUnc(vv, vv_JESUp, vv_JESDown) : 1.00;
        line.replace( line.find("VVVV") , 4 , string(Form("%.3f", JESUnc_vv)) ); 
        out << line << endl;
      }
      else if(line.find("CMS_res_j")!=string::npos){
        float JERUnc_wh = (wh->Integral() > 0) ? DC.getBTagUnc(wh, wh_JERUp, wh_JERDown) : 1.00;
        line.replace( line.find("HHHH") , 4 , string(Form("%.3f", JERUnc_wh)) );
        
        float JERUnc_ttbar = (ttbar->Integral() > 0) ? DC.getBTagUnc(ttbar, ttbar_JERUp, ttbar_JERDown) : 1.00; 
        line.replace( line.find("TTTT") , 4 , string(Form("%.3f", JERUnc_ttbar)) ); 
        
        float JERUnc_wjet = (wjet->Integral() > 0) ? DC.getBTagUnc(wjet, wjet_JERUp, wjet_JERDown) : 1.00;
        line.replace( line.find("WWWW") , 4 , string(Form("%.3f", JERUnc_wjet)) ); 
       
        float JERUnc_zjet = (zjet->Integral() > 0) ? DC.getBTagUnc(zjet, zjet_JERUp, zjet_JERDown) : 1.00;
        line.replace( line.find("DDDD") , 4 , string(Form("%.3f", JERUnc_zjet)) ); 
        
        float JERUnc_stop = (stop->Integral() > 0) ? DC.getBTagUnc(stop, stop_JERUp, stop_JERDown) : 1.00; 
        line.replace( line.find("SSSS") , 4 , string(Form("%.3f", JERUnc_stop)) ); 

        float JERUnc_vv = (vv->Integral() > 0) ? DC.getBTagUnc(vv, vv_JERUp, vv_JERDown) : 1.00;
        line.replace( line.find("VVVV") , 4 , string(Form("%.3f", JERUnc_vv)) ); 
        out << line << endl;
      }
      else if(line.find("CMS_norm_qcd")!=string::npos){  
        line.replace( line.find("QQQQ") , 4 , string(Form("%.3f", qcd_unc)));   
        //if(isMuChannel) line.replace( line.find("QQQQ") , 4 , string(Form("%.4f", 1.10)));   
        //else line.replace(line.find("QQQQ") , 4 , string(Form("%.4f", 1.10)));   
        out << line << endl;  
      }
      else if(line.find("CMS_topPtReweight")!=string::npos){
        float topPtUnc_wh = (wh->Integral() > 0) ? DC.getBTagUnc(wh, wh_topPtUp, wh_topPtDown) : 1.00;
        line.replace( line.find("HHHH") , 4 , string(Form("%.3f", topPtUnc_wh)) );
        
        float topPtUnc_ttbar = (ttbar->Integral() > 0) ? DC.getBTagUnc(ttbar, ttbar_topPtUp, ttbar_topPtDown) : 1.00; 
        line.replace( line.find("TTTT") , 4 , string(Form("%.3f", topPtUnc_ttbar)) ); 
        out << line << endl;
      }
      else if(line.find("scaleRF_tt")!=string::npos){
        float scaleUnc_ttbar = (ttbar->Integral() > 0) ? DC.getBTagUnc(ttbar, ttbar_scaleUp, ttbar_scaleDown) : 1.00; 
        line.replace( line.find("TTTT") , 4 , string(Form("%.3f", scaleUnc_ttbar)) ); 
        out << line << endl;
      }
      else if(line.find("hDamp_tt")!=string::npos){
        float matchUnc_ttbar = (ttbar->Integral() > 0) ? DC.getBTagUnc(ttbar, ttbar_matchingUp, ttbar_matchingDown) : 1.00; 
        line.replace( line.find("TTTT") , 4 , string(Form("%.3f", matchUnc_ttbar)) ); 
        out << line << endl;
      }
      else if(line.find("topMass_tt")!=string::npos){
        float mtopUnc_ttbar = (ttbar->Integral() > 0) ? DC.getBTagUnc(ttbar, ttbar_mtop1735, ttbar_mtop1715) : 1.00; 
        line.replace( line.find("TTTT") , 4 , string(Form("%.3f", mtopUnc_ttbar)) ); 
        out << line << endl;
      }
      else{ //default without changes
        out << line << endl;
      }
    }
  } 
  if(isExL){
    string rate = "CMS_eff_cExL       lnN";  
    string space = "     ";
    out << rate ;
    out << space <<string(Form("%.3f", unc_wh_ExL))
        << space <<string(Form("%.3f", unc_ttbar_ExL))
        << space <<string(Form("%.3f", unc_wjet_ExL))
        << space <<string(Form("%.3f", unc_zjet_ExL))
        << space <<string(Form("%.3f", unc_stop_ExL))
        << space <<string(Form("%.3f", unc_vv_ExL))
        << space <<string(Form("%.3f", 1.0))
        << endl;
  }
  if(isExM){
    string rate = "CMS_eff_cExM       lnN";  
    string space = "     ";
    out << rate ;
    out << space <<string(Form("%.3f", unc_wh_ExM))
        << space <<string(Form("%.3f", unc_ttbar_ExM))
        << space <<string(Form("%.3f", unc_wjet_ExM))
        << space <<string(Form("%.3f", unc_zjet_ExM))
        << space <<string(Form("%.3f", unc_stop_ExM))
        << space <<string(Form("%.3f", unc_vv_ExM))
        << space <<string(Form("%.3f", 1.0))
        << endl;
  }
  out<<"* autoMCStats 0 1"<<endl;
  out.close();
  in.close();
  fout->Close();
}
