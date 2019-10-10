#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <iomanip>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <algorithm> 
#include <fstream>
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include "TH1F.h"
#include "TFile.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TMath.h"
#include <sys/stat.h>

void makeVertBinDataCard(bool isMuChannel, TString myInHistName, vector<int> &binLMT, int mass, TString SigM, TString SigLab){
///INPUT FILES
//data
double totLumi = 35.9;
TString inFileDir="stack_20180418_Mu_Sys_PreApp_5bJetPtBins";
string channel = "mu";
if(isMuChannel){
  inFileDir="stack_20180418_Mu_Sys_PreApp_5bJetPtBins";
  channel = "mu";
}
else{ 
  inFileDir="stack_20180418_Ele_Sys_PreApp_5bJetPtBins";
  channel = "ele";
}

//MAKE DATA CARD of mjj
TString histnameL="PtbJetCatL/"+myInHistName;
TString histnameM="PtbJetCatM/"+myInHistName;
TString histnameT="PtbJetCatT/"+myInHistName;

TFile* fData    = TFile::Open(inFileDir+"/all_Data.root");
//OUTPUT FILE
TString outShapeFile ="Shapes_hcs_13TeV";
TFile *foutL = new TFile(outShapeFile+"_"+TString(channel)+"_PtbJetCatL_"+myInHistName+"_"+SigLab+".root", "RECREATE");
TFile *foutM = new TFile(outShapeFile+"_"+TString(channel)+"_PtbJetCatM_"+myInHistName+"_"+SigLab+".root", "RECREATE");
TFile *foutT = new TFile(outShapeFile+"_"+TString(channel)+"_PtbJetCatT_"+myInHistName+"_"+SigLab+".root", "RECREATE");

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
TFile *fWH      = TFile::Open(inFileDir+"/all_Hplus"+SigM+".root");
//data driven qcd
TFile* fQCD_dd = TFile::Open(inFileDir+"/all_QCD_dd.root"); 


//////////////////////////////////////////////////////////////////
//----------------------------------------//
//Variuos functions
//----------------------------------------//
TH1F* getHisto(TFile *fTT, TFile *inFile, TString histPath, TString inHistName){
  TH1F* hist;
  if(!(inFile->Get(histPath+inHistName))){
    hist = (TH1F*)(fTT->Get(histPath+inHistName));
    hist->Reset();
  }else hist = (TH1F*)(inFile->Get(histPath+inHistName));
  return hist;
}  
//get error in integral 
double getIntError(TH1F* hist){
  double sError = 0.0;
  double  norm = hist->IntegralAndError(1, hist->GetNbinsX(), sError);
  return sError;
}

TH1F* trimHistoLMT(TH1F* histL, TH1F* histM, TH1F* histT, bool isL, bool isM, bool isT, vector<int> &binLMT, TString histName, int binWidth, int xMin, int xMax){
  double nBin = (xMax-xMin)/binWidth;
  TH1F* newHisto = new TH1F(histName, histName, nBin, xMin, xMax);
  double initX = xMin/binWidth;
  double lastX = xMax/binWidth;
  for(int i = initX; i<lastX; i++){
    if(isL){
      double binVal = histL->GetBinContent(i);
      double binErr = histL->GetBinError(i);
      int i_new = i- initX+1;
      newHisto->SetBinContent(i_new, binVal);
      newHisto->SetBinError(i_new, binErr);
      for(int myBin = 0; myBin<binLMT.size(); myBin++){
        if(i_new==binLMT[myBin]){
          double binConL = histL->GetBinContent(i);
          double binConM = histM->GetBinContent(i);
          double binConT = histT->GetBinContent(i);
          double binErrL = histL->GetBinError(i);
          double binErrM = histM->GetBinError(i);
          double binErrT = histT->GetBinError(i);
          double binConL_rebin = binConL + binConM + binConT;
          double binErrL_rebin = sqrt(binErrL*binErrL + binErrM*binErrM + binErrT*binErrT);
          newHisto->SetBinContent(i_new, binConL_rebin);
          newHisto->SetBinError(i_new, binErrL_rebin);
        }
      }
    }
    if(isM){
      double binVal = histM->GetBinContent(i);
      double binErr = histM->GetBinError(i);
      int i_new = i- initX+1;
      newHisto->SetBinContent(i_new, binVal);
      newHisto->SetBinError(i_new, binErr);
      for(int myBin = 0; myBin<binLMT.size(); myBin++){
        if(i_new==binLMT[myBin]){
          newHisto->SetBinContent(i_new, 0);
          newHisto->SetBinError(i_new, 0);
        }
      }
    }
    if(isT){
      double binVal = histT->GetBinContent(i);
      double binErr = histT->GetBinError(i);
      int i_new = i- initX+1;
      newHisto->SetBinContent(i_new, binVal);
      newHisto->SetBinError(i_new, binErr);
      for(int myBin = 0; myBin<binLMT.size(); myBin++){
        if(i_new==binLMT[myBin]){
          newHisto->SetBinContent(i_new, 0);
          newHisto->SetBinError(i_new, 0);
        }
      }
    }
  }
  return newHisto;
}

//get normalised uncertainity
double getBTagUnc(TH1F *hCentral, TH1F* hUp, TH1F* hDown){
  return 1 + max(fabs(hUp->Integral() - hCentral->Integral()), fabs(hCentral->Integral() - hDown->Integral()))/hCentral->Integral();
}

//get statistical uncertainity
double getStatUnc(TH1F* hCentral, double sError = 0.0){
  double  norm = hCentral->IntegralAndError(1, hCentral->GetNbinsX(), sError);
  double statUnc = (norm > 0) ? 1 + (fabs(sError)/norm) : 1.00; 
  return statUnc;
}

//----------------------------------------//
//Global variables
//----------------------------------------//
TH1F* ttbarL              = getHisto(fTT, fTT, "base/Iso/", histnameL);
TH1F* ttbarL_JESUp        = getHisto(fTT, fTT, "JESPlus/Iso/", histnameL);
TH1F* ttbarL_JESDown      = getHisto(fTT, fTT, "JESMinus/Iso/", histnameL);
TH1F* ttbarL_PileupUp     = getHisto(fTT, fTT, "PileupPlus/Iso/", histnameL);
TH1F* ttbarL_PileupDown   = getHisto(fTT, fTT, "PileupMinus/Iso/", histnameL);
TH1F* ttbarL_JERUp        = getHisto(fTT, fTT, "JERPlus/Iso/", histnameL);
TH1F* ttbarL_JERDown      = getHisto(fTT, fTT, "JERMinus/Iso/", histnameL);
TH1F* ttbarL_topPtUp      = getHisto(fTT, fTT, "TopPtPlus/Iso/", histnameL);
TH1F* ttbarL_topPtDown    = getHisto(fTT, fTT, "TopPtMinus/Iso/", histnameL);
TH1F* ttbarL_bTagUp       = getHisto(fTT, fTT, "bTagPlus/Iso/", histnameL);
TH1F* ttbarL_bTagDown     = getHisto(fTT, fTT, "bTagMinus/Iso/", histnameL);
TH1F* ttbarL_cTagUp       = getHisto(fTT, fTT, "cTagPlus/Iso/", histnameL);
TH1F* ttbarL_cTagDown     = getHisto(fTT, fTT, "cTagMinus/Iso/", histnameL);
TH1F* ttbarL_scaleUp      = getHisto(fTT, fTT_up, "base/Iso/", histnameL);
TH1F* ttbarL_scaleDown    = getHisto(fTT, fTT_down, "base/Iso/", histnameL);
TH1F* ttbarL_mtop1715     = getHisto(fTT, fTT_mtop1715, "base/Iso/", histnameL);
TH1F* ttbarL_mtop1735     = getHisto(fTT, fTT_mtop1735, "base/Iso/", histnameL);
TH1F* ttbarL_matchingUp   = getHisto(fTT, fTT_hdampUP, "base/Iso/", histnameL);
TH1F* ttbarL_matchingDown = getHisto(fTT, fTT_hdampDOWN, "base/Iso/", histnameL);

TH1F* ttbarM              = getHisto(fTT, fTT, "base/Iso/", histnameM);
TH1F* ttbarM_JESUp        = getHisto(fTT, fTT, "JESPlus/Iso/", histnameM);
TH1F* ttbarM_JESDown      = getHisto(fTT, fTT, "JESMinus/Iso/", histnameM);
TH1F* ttbarM_PileupUp     = getHisto(fTT, fTT, "PileupPlus/Iso/", histnameM);
TH1F* ttbarM_PileupDown   = getHisto(fTT, fTT, "PileupMinus/Iso/", histnameM);
TH1F* ttbarM_JERUp        = getHisto(fTT, fTT, "JERPlus/Iso/", histnameM);
TH1F* ttbarM_JERDown      = getHisto(fTT, fTT, "JERMinus/Iso/", histnameM);
TH1F* ttbarM_topPtUp      = getHisto(fTT, fTT, "TopPtPlus/Iso/", histnameM);
TH1F* ttbarM_topPtDown    = getHisto(fTT, fTT, "TopPtMinus/Iso/", histnameM);
TH1F* ttbarM_bTagUp       = getHisto(fTT, fTT, "bTagPlus/Iso/", histnameM);
TH1F* ttbarM_bTagDown     = getHisto(fTT, fTT, "bTagMinus/Iso/", histnameM);
TH1F* ttbarM_cTagUp       = getHisto(fTT, fTT, "cTagPlus/Iso/", histnameM);
TH1F* ttbarM_cTagDown     = getHisto(fTT, fTT, "cTagMinus/Iso/", histnameM);
TH1F* ttbarM_scaleUp      = getHisto(fTT, fTT_up, "base/Iso/", histnameM);
TH1F* ttbarM_scaleDown    = getHisto(fTT, fTT_down, "base/Iso/", histnameM);
TH1F* ttbarM_mtop1715     = getHisto(fTT, fTT_mtop1715, "base/Iso/", histnameM);
TH1F* ttbarM_mtop1735     = getHisto(fTT, fTT_mtop1735, "base/Iso/", histnameM);
TH1F* ttbarM_matchingUp   = getHisto(fTT, fTT_hdampUP, "base/Iso/", histnameM);
TH1F* ttbarM_matchingDown = getHisto(fTT, fTT_hdampDOWN, "base/Iso/", histnameM);

TH1F* ttbarT              = getHisto(fTT, fTT, "base/Iso/", histnameT);
TH1F* ttbarT_JESUp        = getHisto(fTT, fTT, "JESPlus/Iso/", histnameT);
TH1F* ttbarT_JESDown      = getHisto(fTT, fTT, "JESMinus/Iso/", histnameT);
TH1F* ttbarT_PileupUp     = getHisto(fTT, fTT, "PileupPlus/Iso/", histnameT);
TH1F* ttbarT_PileupDown   = getHisto(fTT, fTT, "PileupMinus/Iso/", histnameT);
TH1F* ttbarT_JERUp        = getHisto(fTT, fTT, "JERPlus/Iso/", histnameT);
TH1F* ttbarT_JERDown      = getHisto(fTT, fTT, "JERMinus/Iso/", histnameT);
TH1F* ttbarT_topPtUp      = getHisto(fTT, fTT, "TopPtPlus/Iso/", histnameT);
TH1F* ttbarT_topPtDown    = getHisto(fTT, fTT, "TopPtMinus/Iso/", histnameT);
TH1F* ttbarT_bTagUp       = getHisto(fTT, fTT, "bTagPlus/Iso/", histnameT);
TH1F* ttbarT_bTagDown     = getHisto(fTT, fTT, "bTagMinus/Iso/", histnameT);
TH1F* ttbarT_cTagUp       = getHisto(fTT, fTT, "cTagPlus/Iso/", histnameT);
TH1F* ttbarT_cTagDown     = getHisto(fTT, fTT, "cTagMinus/Iso/", histnameT);
TH1F* ttbarT_scaleUp      = getHisto(fTT, fTT_up, "base/Iso/", histnameT);
TH1F* ttbarT_scaleDown    = getHisto(fTT, fTT_down, "base/Iso/", histnameT);
TH1F* ttbarT_mtop1715     = getHisto(fTT, fTT_mtop1715, "base/Iso/", histnameT);
TH1F* ttbarT_mtop1735     = getHisto(fTT, fTT_mtop1735, "base/Iso/", histnameT);
TH1F* ttbarT_matchingUp   = getHisto(fTT, fTT_hdampUP, "base/Iso/", histnameT);
TH1F* ttbarT_matchingDown = getHisto(fTT, fTT_hdampDOWN, "base/Iso/", histnameT);

TH1F* ttbarLtrim              = trimHistoLMT(ttbarL, ttbarM, ttbarT, true, false, false, binLMT, "ttbar", 5, 20, 170);
TH1F* ttbarLtrim_JESUp        = trimHistoLMT(ttbarL_JESUp       , ttbarM_JESUp       , ttbarT_JESUp       , true, false, false, binLMT, "ttbar_JESUp", 5, 20, 170);
TH1F* ttbarLtrim_JESDown      = trimHistoLMT(ttbarL_JESDown     , ttbarM_JESDown     , ttbarT_JESDown     , true, false, false, binLMT, "ttbar_JESDown", 5, 20, 170);
TH1F* ttbarLtrim_PileupUp     = trimHistoLMT(ttbarL_PileupUp    , ttbarM_PileupUp    , ttbarT_PileupUp    , true, false, false, binLMT, "ttbar_PileupUp", 5, 20, 170);
TH1F* ttbarLtrim_PileupDown   = trimHistoLMT(ttbarL_PileupDown  , ttbarM_PileupDown  , ttbarT_PileupDown  , true, false, false, binLMT, "ttbar_PileupDown", 5, 20, 170);
TH1F* ttbarLtrim_JERUp        = trimHistoLMT(ttbarL_JERUp       , ttbarM_JERUp       , ttbarT_JERUp       , true, false, false, binLMT, "ttbar_JERUp", 5, 20, 170);
TH1F* ttbarLtrim_JERDown      = trimHistoLMT(ttbarL_JERDown     , ttbarM_JERDown     , ttbarT_JERDown     , true, false, false, binLMT, "ttbar_JERDown", 5, 20, 170);
TH1F* ttbarLtrim_topPtUp      = trimHistoLMT(ttbarL_topPtUp     , ttbarM_topPtUp     , ttbarT_topPtUp     , true, false, false, binLMT, "ttbar_topPtup", 5, 20, 170);
TH1F* ttbarLtrim_topPtDown    = trimHistoLMT(ttbarL_topPtDown   , ttbarM_topPtDown   , ttbarT_topPtDown   , true, false, false, binLMT, "ttbar_topPtDown", 5, 20, 170);
TH1F* ttbarLtrim_bTagUp       = trimHistoLMT(ttbarL_bTagUp      , ttbarM_bTagUp      , ttbarT_bTagUp      , true, false, false, binLMT, "ttbar_bTagUp", 5, 20, 170);
TH1F* ttbarLtrim_bTagDown     = trimHistoLMT(ttbarL_bTagDown    , ttbarM_bTagDown    , ttbarT_bTagDown    , true, false, false, binLMT, "ttbar_bTagDown", 5, 20, 170);
TH1F* ttbarLtrim_cTagUp       = trimHistoLMT(ttbarL_cTagUp      , ttbarM_cTagUp      , ttbarT_cTagUp      , true, false, false, binLMT, "ttbar_cTagUp", 5, 20, 170);
TH1F* ttbarLtrim_cTagDown     = trimHistoLMT(ttbarL_cTagDown    , ttbarM_cTagDown    , ttbarT_cTagDown    , true, false, false, binLMT, "ttbar_cTagDown", 5, 20, 170);
TH1F* ttbarLtrim_scaleUp      = trimHistoLMT(ttbarL_scaleUp     , ttbarM_scaleUp     , ttbarT_scaleUp     , true, false, false, binLMT, "ttbar_scaleRF_ttUp", 5, 20, 170);
TH1F* ttbarLtrim_scaleDown    = trimHistoLMT(ttbarL_scaleDown   , ttbarM_scaleDown   , ttbarT_scaleDown   , true, false, false, binLMT, "ttbar_scaleRF_ttDown", 5, 20, 170);
TH1F* ttbarLtrim_mtop1735     = trimHistoLMT(ttbarL_mtop1735    , ttbarM_mtop1735    , ttbarT_mtop1735    , true, false, false, binLMT, "ttbar_topMass_ttUp", 5, 20, 170);
TH1F* ttbarLtrim_mtop1715     = trimHistoLMT(ttbarL_mtop1715    , ttbarM_mtop1715    , ttbarT_mtop1715    , true, false, false, binLMT, "ttbar_topMass_ttDown", 5, 20, 170);
TH1F* ttbarLtrim_matchingUp   = trimHistoLMT(ttbarL_matchingUp  , ttbarM_matchingUp  , ttbarT_matchingUp  , true, false, false, binLMT, "ttbar_hDamp_ttUp", 5, 20, 170);
TH1F* ttbarLtrim_matchingDown = trimHistoLMT(ttbarL_matchingDown, ttbarM_matchingDown, ttbarT_matchingDown, true, false, false, binLMT, "ttbar_hDamp_ttDown", 5, 20, 170);

TH1F* ttbarMtrim              = trimHistoLMT(ttbarL, ttbarM, ttbarT, false, true, false, binLMT, "ttbar", 5, 20, 170);
TH1F* ttbarMtrim_JESUp        = trimHistoLMT(ttbarL_JESUp       , ttbarM_JESUp       , ttbarT_JESUp       , false, true, false, binLMT, "ttbar_JESUp", 5, 20, 170);
TH1F* ttbarMtrim_JESDown      = trimHistoLMT(ttbarL_JESDown     , ttbarM_JESDown     , ttbarT_JESDown     , false, true, false, binLMT, "ttbar_JESDown", 5, 20, 170);
TH1F* ttbarMtrim_PileupUp     = trimHistoLMT(ttbarL_PileupUp    , ttbarM_PileupUp    , ttbarT_PileupUp    , false, true, false, binLMT, "ttbar_PileupUp", 5, 20, 170);
TH1F* ttbarMtrim_PileupDown   = trimHistoLMT(ttbarL_PileupDown  , ttbarM_PileupDown  , ttbarT_PileupDown  , false, true, false, binLMT, "ttbar_PileupDown", 5, 20, 170);
TH1F* ttbarMtrim_JERUp        = trimHistoLMT(ttbarL_JERUp       , ttbarM_JERUp       , ttbarT_JERUp       , false, true, false, binLMT, "ttbar_JERUp", 5, 20, 170);
TH1F* ttbarMtrim_JERDown      = trimHistoLMT(ttbarL_JERDown     , ttbarM_JERDown     , ttbarT_JERDown     , false, true, false, binLMT, "ttbar_JERDown", 5, 20, 170);
TH1F* ttbarMtrim_topPtUp      = trimHistoLMT(ttbarL_topPtUp     , ttbarM_topPtUp     , ttbarT_topPtUp     , false, true, false, binLMT, "ttbar_topPtup", 5, 20, 170);
TH1F* ttbarMtrim_topPtDown    = trimHistoLMT(ttbarL_topPtDown   , ttbarM_topPtDown   , ttbarT_topPtDown   , false, true, false, binLMT, "ttbar_topPtDown", 5, 20, 170);
TH1F* ttbarMtrim_bTagUp       = trimHistoLMT(ttbarL_bTagUp      , ttbarM_bTagUp      , ttbarT_bTagUp      , false, true, false, binLMT, "ttbar_bTagUp", 5, 20, 170);
TH1F* ttbarMtrim_bTagDown     = trimHistoLMT(ttbarL_bTagDown    , ttbarM_bTagDown    , ttbarT_bTagDown    , false, true, false, binLMT, "ttbar_bTagDown", 5, 20, 170);
TH1F* ttbarMtrim_cTagUp       = trimHistoLMT(ttbarL_cTagUp      , ttbarM_cTagUp      , ttbarT_cTagUp      , false, true, false, binLMT, "ttbar_cTagUp", 5, 20, 170);
TH1F* ttbarMtrim_cTagDown     = trimHistoLMT(ttbarL_cTagDown    , ttbarM_cTagDown    , ttbarT_cTagDown    , false, true, false, binLMT, "ttbar_cTagDown", 5, 20, 170);
TH1F* ttbarMtrim_scaleUp      = trimHistoLMT(ttbarL_scaleUp     , ttbarM_scaleUp     , ttbarT_scaleUp     , false, true, false, binLMT, "ttbar_scaleRF_ttUp", 5, 20, 170);
TH1F* ttbarMtrim_scaleDown    = trimHistoLMT(ttbarL_scaleDown   , ttbarM_scaleDown   , ttbarT_scaleDown   , false, true, false, binLMT, "ttbar_scaleRF_ttDown", 5, 20, 170);
TH1F* ttbarMtrim_mtop1735     = trimHistoLMT(ttbarL_mtop1735    , ttbarM_mtop1735    , ttbarT_mtop1735    , false, true, false, binLMT, "ttbar_topMass_ttUp", 5, 20, 170);
TH1F* ttbarMtrim_mtop1715     = trimHistoLMT(ttbarL_mtop1715    , ttbarM_mtop1715    , ttbarT_mtop1715    , false, true, false, binLMT, "ttbar_topMass_ttDown", 5, 20, 170);
TH1F* ttbarMtrim_matchingUp   = trimHistoLMT(ttbarL_matchingUp  , ttbarM_matchingUp  , ttbarT_matchingUp  , false, true, false, binLMT, "ttbar_hDamp_ttUp", 5, 20, 170);
TH1F* ttbarMtrim_matchingDown = trimHistoLMT(ttbarL_matchingDown, ttbarM_matchingDown, ttbarT_matchingDown, false, true, false, binLMT, "ttbar_hDamp_ttDown", 5, 20, 170);

TH1F* ttbarTtrim              = trimHistoLMT(ttbarL, ttbarM, ttbarT, false, false, true, binLMT, "ttbar", 5, 20, 170);
TH1F* ttbarTtrim_JESUp        = trimHistoLMT(ttbarL_JESUp       , ttbarM_JESUp       , ttbarT_JESUp       , false, false, true, binLMT, "ttbar_JESUp", 5, 20, 170);
TH1F* ttbarTtrim_JESDown      = trimHistoLMT(ttbarL_JESDown     , ttbarM_JESDown     , ttbarT_JESDown     , false, false, true, binLMT, "ttbar_JESDown", 5, 20, 170);
TH1F* ttbarTtrim_PileupUp     = trimHistoLMT(ttbarL_PileupUp    , ttbarM_PileupUp    , ttbarT_PileupUp    , false, false, true, binLMT, "ttbar_PileupUp", 5, 20, 170);
TH1F* ttbarTtrim_PileupDown   = trimHistoLMT(ttbarL_PileupDown  , ttbarM_PileupDown  , ttbarT_PileupDown  , false, false, true, binLMT, "ttbar_PileupDown", 5, 20, 170);
TH1F* ttbarTtrim_JERUp        = trimHistoLMT(ttbarL_JERUp       , ttbarM_JERUp       , ttbarT_JERUp       , false, false, true, binLMT, "ttbar_JERUp", 5, 20, 170);
TH1F* ttbarTtrim_JERDown      = trimHistoLMT(ttbarL_JERDown     , ttbarM_JERDown     , ttbarT_JERDown     , false, false, true, binLMT, "ttbar_JERDown", 5, 20, 170);
TH1F* ttbarTtrim_topPtUp      = trimHistoLMT(ttbarL_topPtUp     , ttbarM_topPtUp     , ttbarT_topPtUp     , false, false, true, binLMT, "ttbar_topPtup", 5, 20, 170);
TH1F* ttbarTtrim_topPtDown    = trimHistoLMT(ttbarL_topPtDown   , ttbarM_topPtDown   , ttbarT_topPtDown   , false, false, true, binLMT, "ttbar_topPtDown", 5, 20, 170);
TH1F* ttbarTtrim_bTagUp       = trimHistoLMT(ttbarL_bTagUp      , ttbarM_bTagUp      , ttbarT_bTagUp      , false, false, true, binLMT, "ttbar_bTagUp", 5, 20, 170);
TH1F* ttbarTtrim_bTagDown     = trimHistoLMT(ttbarL_bTagDown    , ttbarM_bTagDown    , ttbarT_bTagDown    , false, false, true, binLMT, "ttbar_bTagDown", 5, 20, 170);
TH1F* ttbarTtrim_cTagUp       = trimHistoLMT(ttbarL_cTagUp      , ttbarM_cTagUp      , ttbarT_cTagUp      , false, false, true, binLMT, "ttbar_cTagUp", 5, 20, 170);
TH1F* ttbarTtrim_cTagDown     = trimHistoLMT(ttbarL_cTagDown    , ttbarM_cTagDown    , ttbarT_cTagDown    , false, false, true, binLMT, "ttbar_cTagDown", 5, 20, 170);
TH1F* ttbarTtrim_scaleUp      = trimHistoLMT(ttbarL_scaleUp     , ttbarM_scaleUp     , ttbarT_scaleUp     , false, false, true, binLMT, "ttbar_scaleRF_ttUp", 5, 20, 170);
TH1F* ttbarTtrim_scaleDown    = trimHistoLMT(ttbarL_scaleDown   , ttbarM_scaleDown   , ttbarT_scaleDown   , false, false, true, binLMT, "ttbar_scaleRF_ttDown", 5, 20, 170);
TH1F* ttbarTtrim_mtop1735     = trimHistoLMT(ttbarL_mtop1735    , ttbarM_mtop1735    , ttbarT_mtop1735    , false, false, true, binLMT, "ttbar_topMass_ttUp", 5, 20, 170);
TH1F* ttbarTtrim_mtop1715     = trimHistoLMT(ttbarL_mtop1715    , ttbarM_mtop1715    , ttbarT_mtop1715    , false, false, true, binLMT, "ttbar_topMass_ttDown", 5, 20, 170);
TH1F* ttbarTtrim_matchingUp   = trimHistoLMT(ttbarL_matchingUp  , ttbarM_matchingUp  , ttbarT_matchingUp  , false, false, true, binLMT, "ttbar_hDamp_ttUp", 5, 20, 170);
TH1F* ttbarTtrim_matchingDown = trimHistoLMT(ttbarL_matchingDown, ttbarM_matchingDown, ttbarT_matchingDown, false, false, true, binLMT, "ttbar_hDamp_ttDown", 5, 20, 170);

TH1F* wjetL              = getHisto(fTT, fWJ, "base/Iso/", histnameL);
TH1F* wjetL_JESUp        = getHisto(fTT, fWJ, "JESPlus/Iso/", histnameL);
TH1F* wjetL_JESDown      = getHisto(fTT, fWJ, "JESMinus/Iso/", histnameL);
TH1F* wjetL_PileupUp     = getHisto(fTT, fWJ, "PileupPlus/Iso/", histnameL);
TH1F* wjetL_PileupDown   = getHisto(fTT, fWJ, "PileupMinus/Iso/", histnameL);
TH1F* wjetL_JERUp        = getHisto(fTT, fWJ, "JERPlus/Iso/", histnameL);
TH1F* wjetL_JERDown      = getHisto(fTT, fWJ, "JERMinus/Iso/", histnameL);
TH1F* wjetL_bTagUp       = getHisto(fTT, fWJ, "bTagPlus/Iso/", histnameL);
TH1F* wjetL_bTagDown     = getHisto(fTT, fWJ, "bTagMinus/Iso/", histnameL);
TH1F* wjetL_cTagUp       = getHisto(fTT, fWJ, "cTagPlus/Iso/", histnameL);
TH1F* wjetL_cTagDown     = getHisto(fTT, fWJ, "cTagMinus/Iso/", histnameL);

TH1F* wjetM              = getHisto(fTT, fWJ, "base/Iso/", histnameM);
TH1F* wjetM_JESUp        = getHisto(fTT, fWJ, "JESPlus/Iso/", histnameM);
TH1F* wjetM_JESDown      = getHisto(fTT, fWJ, "JESMinus/Iso/", histnameM);
TH1F* wjetM_PileupUp     = getHisto(fTT, fWJ, "PileupPlus/Iso/", histnameM);
TH1F* wjetM_PileupDown   = getHisto(fTT, fWJ, "PileupMinus/Iso/", histnameM);
TH1F* wjetM_JERUp        = getHisto(fTT, fWJ, "JERPlus/Iso/", histnameM);
TH1F* wjetM_JERDown      = getHisto(fTT, fWJ, "JERMinus/Iso/", histnameM);
TH1F* wjetM_bTagUp       = getHisto(fTT, fWJ, "bTagPlus/Iso/", histnameM);
TH1F* wjetM_bTagDown     = getHisto(fTT, fWJ, "bTagMinus/Iso/", histnameM);
TH1F* wjetM_cTagUp       = getHisto(fTT, fWJ, "cTagPlus/Iso/", histnameM);
TH1F* wjetM_cTagDown     = getHisto(fTT, fWJ, "cTagMinus/Iso/", histnameM);

TH1F* wjetT              = getHisto(fTT, fWJ, "base/Iso/", histnameT);
TH1F* wjetT_JESUp        = getHisto(fTT, fWJ, "JESPlus/Iso/", histnameT);
TH1F* wjetT_JESDown      = getHisto(fTT, fWJ, "JESMinus/Iso/", histnameT);
TH1F* wjetT_PileupUp     = getHisto(fTT, fWJ, "PileupPlus/Iso/", histnameT);
TH1F* wjetT_PileupDown   = getHisto(fTT, fWJ, "PileupMinus/Iso/", histnameT);
TH1F* wjetT_JERUp        = getHisto(fTT, fWJ, "JERPlus/Iso/", histnameT);
TH1F* wjetT_JERDown      = getHisto(fTT, fWJ, "JERMinus/Iso/", histnameT);
TH1F* wjetT_bTagUp       = getHisto(fTT, fWJ, "bTagPlus/Iso/", histnameT);
TH1F* wjetT_bTagDown     = getHisto(fTT, fWJ, "bTagMinus/Iso/", histnameT);
TH1F* wjetT_cTagUp       = getHisto(fTT, fWJ, "cTagPlus/Iso/", histnameT);
TH1F* wjetT_cTagDown     = getHisto(fTT, fWJ, "cTagMinus/Iso/", histnameT);

TH1F* wjetLtrim              = trimHistoLMT(wjetL, wjetM, wjetT, true, false, false, binLMT, "wjet", 5, 20, 170);
TH1F* wjetLtrim_JESUp        = trimHistoLMT(wjetL_JESUp       , wjetM_JESUp       , wjetT_JESUp       , true, false, false, binLMT, "wjet_JESUp", 5, 20, 170);
TH1F* wjetLtrim_JESDown      = trimHistoLMT(wjetL_JESDown     , wjetM_JESDown     , wjetT_JESDown     , true, false, false, binLMT, "wjet_JESDown", 5, 20, 170);
TH1F* wjetLtrim_PileupUp     = trimHistoLMT(wjetL_PileupUp    , wjetM_PileupUp    , wjetT_PileupUp    , true, false, false, binLMT, "wjet_PileupUp", 5, 20, 170);
TH1F* wjetLtrim_PileupDown   = trimHistoLMT(wjetL_PileupDown  , wjetM_PileupDown  , wjetT_PileupDown  , true, false, false, binLMT, "wjet_PileupDown", 5, 20, 170);
TH1F* wjetLtrim_JERUp        = trimHistoLMT(wjetL_JERUp       , wjetM_JERUp       , wjetT_JERUp       , true, false, false, binLMT, "wjet_JERUp", 5, 20, 170);
TH1F* wjetLtrim_JERDown      = trimHistoLMT(wjetL_JERDown     , wjetM_JERDown     , wjetT_JERDown     , true, false, false, binLMT, "wjet_JERDown", 5, 20, 170);
TH1F* wjetLtrim_bTagUp       = trimHistoLMT(wjetL_bTagUp      , wjetM_bTagUp      , wjetT_bTagUp      , true, false, false, binLMT, "wjet_bTagUp", 5, 20, 170);
TH1F* wjetLtrim_bTagDown     = trimHistoLMT(wjetL_bTagDown    , wjetM_bTagDown    , wjetT_bTagDown    , true, false, false, binLMT, "wjet_bTagDown", 5, 20, 170);
TH1F* wjetLtrim_cTagUp       = trimHistoLMT(wjetL_cTagUp      , wjetM_cTagUp      , wjetT_cTagUp      , true, false, false, binLMT, "wjet_cTagUp", 5, 20, 170);
TH1F* wjetLtrim_cTagDown     = trimHistoLMT(wjetL_cTagDown    , wjetM_cTagDown    , wjetT_cTagDown    , true, false, false, binLMT, "wjet_cTagDown", 5, 20, 170);

TH1F* wjetMtrim              = trimHistoLMT(wjetL, wjetM, wjetT, false, true, false, binLMT, "wjet", 5, 20, 170);
TH1F* wjetMtrim_JESUp        = trimHistoLMT(wjetL_JESUp       , wjetM_JESUp       , wjetT_JESUp       , false, true, false, binLMT, "wjet_JESUp", 5, 20, 170);
TH1F* wjetMtrim_JESDown      = trimHistoLMT(wjetL_JESDown     , wjetM_JESDown     , wjetT_JESDown     , false, true, false, binLMT, "wjet_JESDown", 5, 20, 170);
TH1F* wjetMtrim_PileupUp     = trimHistoLMT(wjetL_PileupUp    , wjetM_PileupUp    , wjetT_PileupUp    , false, true, false, binLMT, "wjet_PileupUp", 5, 20, 170);
TH1F* wjetMtrim_PileupDown   = trimHistoLMT(wjetL_PileupDown  , wjetM_PileupDown  , wjetT_PileupDown  , false, true, false, binLMT, "wjet_PileupDown", 5, 20, 170);
TH1F* wjetMtrim_JERUp        = trimHistoLMT(wjetL_JERUp       , wjetM_JERUp       , wjetT_JERUp       , false, true, false, binLMT, "wjet_JERUp", 5, 20, 170);
TH1F* wjetMtrim_JERDown      = trimHistoLMT(wjetL_JERDown     , wjetM_JERDown     , wjetT_JERDown     , false, true, false, binLMT, "wjet_JERDown", 5, 20, 170);
TH1F* wjetMtrim_bTagUp       = trimHistoLMT(wjetL_bTagUp      , wjetM_bTagUp      , wjetT_bTagUp      , false, true, false, binLMT, "wjet_bTagUp", 5, 20, 170);
TH1F* wjetMtrim_bTagDown     = trimHistoLMT(wjetL_bTagDown    , wjetM_bTagDown    , wjetT_bTagDown    , false, true, false, binLMT, "wjet_bTagDown", 5, 20, 170);
TH1F* wjetMtrim_cTagUp       = trimHistoLMT(wjetL_cTagUp      , wjetM_cTagUp      , wjetT_cTagUp      , false, true, false, binLMT, "wjet_cTagUp", 5, 20, 170);
TH1F* wjetMtrim_cTagDown     = trimHistoLMT(wjetL_cTagDown    , wjetM_cTagDown    , wjetT_cTagDown    , false, true, false, binLMT, "wjet_cTagDown", 5, 20, 170);

TH1F* wjetTtrim              = trimHistoLMT(wjetL, wjetM, wjetT, false, false, true, binLMT, "wjet", 5, 20, 170);
TH1F* wjetTtrim_JESUp        = trimHistoLMT(wjetL_JESUp       , wjetM_JESUp       , wjetT_JESUp       , false, false, true, binLMT, "wjet_JESUp", 5, 20, 170);
TH1F* wjetTtrim_JESDown      = trimHistoLMT(wjetL_JESDown     , wjetM_JESDown     , wjetT_JESDown     , false, false, true, binLMT, "wjet_JESDown", 5, 20, 170);
TH1F* wjetTtrim_PileupUp     = trimHistoLMT(wjetL_PileupUp    , wjetM_PileupUp    , wjetT_PileupUp    , false, false, true, binLMT, "wjet_PileupUp", 5, 20, 170);
TH1F* wjetTtrim_PileupDown   = trimHistoLMT(wjetL_PileupDown  , wjetM_PileupDown  , wjetT_PileupDown  , false, false, true, binLMT, "wjet_PileupDown", 5, 20, 170);
TH1F* wjetTtrim_JERUp        = trimHistoLMT(wjetL_JERUp       , wjetM_JERUp       , wjetT_JERUp       , false, false, true, binLMT, "wjet_JERUp", 5, 20, 170);
TH1F* wjetTtrim_JERDown      = trimHistoLMT(wjetL_JERDown     , wjetM_JERDown     , wjetT_JERDown     , false, false, true, binLMT, "wjet_JERDown", 5, 20, 170);
TH1F* wjetTtrim_bTagUp       = trimHistoLMT(wjetL_bTagUp      , wjetM_bTagUp      , wjetT_bTagUp      , false, false, true, binLMT, "wjet_bTagUp", 5, 20, 170);
TH1F* wjetTtrim_bTagDown     = trimHistoLMT(wjetL_bTagDown    , wjetM_bTagDown    , wjetT_bTagDown    , false, false, true, binLMT, "wjet_bTagDown", 5, 20, 170);
TH1F* wjetTtrim_cTagUp       = trimHistoLMT(wjetL_cTagUp      , wjetM_cTagUp      , wjetT_cTagUp      , false, false, true, binLMT, "wjet_cTagUp", 5, 20, 170);
TH1F* wjetTtrim_cTagDown     = trimHistoLMT(wjetL_cTagDown    , wjetM_cTagDown    , wjetT_cTagDown    , false, false, true, binLMT, "wjet_cTagDown", 5, 20, 170);


TH1F* zjetL              = getHisto(fTT, fDY, "base/Iso/", histnameL);
TH1F* zjetL_JESUp        = getHisto(fTT, fDY, "JESPlus/Iso/", histnameL);
TH1F* zjetL_JESDown      = getHisto(fTT, fDY, "JESMinus/Iso/", histnameL);
TH1F* zjetL_PileupUp     = getHisto(fTT, fDY, "PileupPlus/Iso/", histnameL);
TH1F* zjetL_PileupDown   = getHisto(fTT, fDY, "PileupMinus/Iso/", histnameL);
TH1F* zjetL_JERUp        = getHisto(fTT, fDY, "JERPlus/Iso/", histnameL);
TH1F* zjetL_JERDown      = getHisto(fTT, fDY, "JERMinus/Iso/", histnameL);
TH1F* zjetL_bTagUp       = getHisto(fTT, fDY, "bTagPlus/Iso/", histnameL);
TH1F* zjetL_bTagDown     = getHisto(fTT, fDY, "bTagMinus/Iso/", histnameL);
TH1F* zjetL_cTagUp       = getHisto(fTT, fDY, "cTagPlus/Iso/", histnameL);
TH1F* zjetL_cTagDown     = getHisto(fTT, fDY, "cTagMinus/Iso/", histnameL);

TH1F* zjetM              = getHisto(fTT, fDY, "base/Iso/", histnameM);
TH1F* zjetM_JESUp        = getHisto(fTT, fDY, "JESPlus/Iso/", histnameM);
TH1F* zjetM_JESDown      = getHisto(fTT, fDY, "JESMinus/Iso/", histnameM);
TH1F* zjetM_PileupUp     = getHisto(fTT, fDY, "PileupPlus/Iso/", histnameM);
TH1F* zjetM_PileupDown   = getHisto(fTT, fDY, "PileupMinus/Iso/", histnameM);
TH1F* zjetM_JERUp        = getHisto(fTT, fDY, "JERPlus/Iso/", histnameM);
TH1F* zjetM_JERDown      = getHisto(fTT, fDY, "JERMinus/Iso/", histnameM);
TH1F* zjetM_bTagUp       = getHisto(fTT, fDY, "bTagPlus/Iso/", histnameM);
TH1F* zjetM_bTagDown     = getHisto(fTT, fDY, "bTagMinus/Iso/", histnameM);
TH1F* zjetM_cTagUp       = getHisto(fTT, fDY, "cTagPlus/Iso/", histnameM);
TH1F* zjetM_cTagDown     = getHisto(fTT, fDY, "cTagMinus/Iso/", histnameM);

TH1F* zjetT              = getHisto(fTT, fDY, "base/Iso/", histnameT);
TH1F* zjetT_JESUp        = getHisto(fTT, fDY, "JESPlus/Iso/", histnameT);
TH1F* zjetT_JESDown      = getHisto(fTT, fDY, "JESMinus/Iso/", histnameT);
TH1F* zjetT_PileupUp     = getHisto(fTT, fDY, "PileupPlus/Iso/", histnameT);
TH1F* zjetT_PileupDown   = getHisto(fTT, fDY, "PileupMinus/Iso/", histnameT);
TH1F* zjetT_JERUp        = getHisto(fTT, fDY, "JERPlus/Iso/", histnameT);
TH1F* zjetT_JERDown      = getHisto(fTT, fDY, "JERMinus/Iso/", histnameT);
TH1F* zjetT_bTagUp       = getHisto(fTT, fDY, "bTagPlus/Iso/", histnameT);
TH1F* zjetT_bTagDown     = getHisto(fTT, fDY, "bTagMinus/Iso/", histnameT);
TH1F* zjetT_cTagUp       = getHisto(fTT, fDY, "cTagPlus/Iso/", histnameT);
TH1F* zjetT_cTagDown     = getHisto(fTT, fDY, "cTagMinus/Iso/", histnameT);

TH1F* zjetLtrim              = trimHistoLMT(zjetL, zjetM, zjetT, true, false, false, binLMT, "zjet", 5, 20, 170);
TH1F* zjetLtrim_JESUp        = trimHistoLMT(zjetL_JESUp       , zjetM_JESUp       , zjetT_JESUp       , true, false, false, binLMT, "zjet_JESUp", 5, 20, 170);
TH1F* zjetLtrim_JESDown      = trimHistoLMT(zjetL_JESDown     , zjetM_JESDown     , zjetT_JESDown     , true, false, false, binLMT, "zjet_JESDown", 5, 20, 170);
TH1F* zjetLtrim_PileupUp     = trimHistoLMT(zjetL_PileupUp    , zjetM_PileupUp    , zjetT_PileupUp    , true, false, false, binLMT, "zjet_PileupUp", 5, 20, 170);
TH1F* zjetLtrim_PileupDown   = trimHistoLMT(zjetL_PileupDown  , zjetM_PileupDown  , zjetT_PileupDown  , true, false, false, binLMT, "zjet_PileupDown", 5, 20, 170);
TH1F* zjetLtrim_JERUp        = trimHistoLMT(zjetL_JERUp       , zjetM_JERUp       , zjetT_JERUp       , true, false, false, binLMT, "zjet_JERUp", 5, 20, 170);
TH1F* zjetLtrim_JERDown      = trimHistoLMT(zjetL_JERDown     , zjetM_JERDown     , zjetT_JERDown     , true, false, false, binLMT, "zjet_JERDown", 5, 20, 170);
TH1F* zjetLtrim_bTagUp       = trimHistoLMT(zjetL_bTagUp      , zjetM_bTagUp      , zjetT_bTagUp      , true, false, false, binLMT, "zjet_bTagUp", 5, 20, 170);
TH1F* zjetLtrim_bTagDown     = trimHistoLMT(zjetL_bTagDown    , zjetM_bTagDown    , zjetT_bTagDown    , true, false, false, binLMT, "zjet_bTagDown", 5, 20, 170);
TH1F* zjetLtrim_cTagUp       = trimHistoLMT(zjetL_cTagUp      , zjetM_cTagUp      , zjetT_cTagUp      , true, false, false, binLMT, "zjet_cTagUp", 5, 20, 170);
TH1F* zjetLtrim_cTagDown     = trimHistoLMT(zjetL_cTagDown    , zjetM_cTagDown    , zjetT_cTagDown    , true, false, false, binLMT, "zjet_cTagDown", 5, 20, 170);

TH1F* zjetMtrim              = trimHistoLMT(zjetL, zjetM, zjetT, false, true, false, binLMT, "zjet", 5, 20, 170);
TH1F* zjetMtrim_JESUp        = trimHistoLMT(zjetL_JESUp       , zjetM_JESUp       , zjetT_JESUp       , false, true, false, binLMT, "zjet_JESUp", 5, 20, 170);
TH1F* zjetMtrim_JESDown      = trimHistoLMT(zjetL_JESDown     , zjetM_JESDown     , zjetT_JESDown     , false, true, false, binLMT, "zjet_JESDown", 5, 20, 170);
TH1F* zjetMtrim_PileupUp     = trimHistoLMT(zjetL_PileupUp    , zjetM_PileupUp    , zjetT_PileupUp    , false, true, false, binLMT, "zjet_PileupUp", 5, 20, 170);
TH1F* zjetMtrim_PileupDown   = trimHistoLMT(zjetL_PileupDown  , zjetM_PileupDown  , zjetT_PileupDown  , false, true, false, binLMT, "zjet_PileupDown", 5, 20, 170);
TH1F* zjetMtrim_JERUp        = trimHistoLMT(zjetL_JERUp       , zjetM_JERUp       , zjetT_JERUp       , false, true, false, binLMT, "zjet_JERUp", 5, 20, 170);
TH1F* zjetMtrim_JERDown      = trimHistoLMT(zjetL_JERDown     , zjetM_JERDown     , zjetT_JERDown     , false, true, false, binLMT, "zjet_JERDown", 5, 20, 170);
TH1F* zjetMtrim_bTagUp       = trimHistoLMT(zjetL_bTagUp      , zjetM_bTagUp      , zjetT_bTagUp      , false, true, false, binLMT, "zjet_bTagUp", 5, 20, 170);
TH1F* zjetMtrim_bTagDown     = trimHistoLMT(zjetL_bTagDown    , zjetM_bTagDown    , zjetT_bTagDown    , false, true, false, binLMT, "zjet_bTagDown", 5, 20, 170);
TH1F* zjetMtrim_cTagUp       = trimHistoLMT(zjetL_cTagUp      , zjetM_cTagUp      , zjetT_cTagUp      , false, true, false, binLMT, "zjet_cTagUp", 5, 20, 170);
TH1F* zjetMtrim_cTagDown     = trimHistoLMT(zjetL_cTagDown    , zjetM_cTagDown    , zjetT_cTagDown    , false, true, false, binLMT, "zjet_cTagDown", 5, 20, 170);

TH1F* zjetTtrim              = trimHistoLMT(zjetL, zjetM, zjetT, false, false, true, binLMT, "zjet", 5, 20, 170);
TH1F* zjetTtrim_JESUp        = trimHistoLMT(zjetL_JESUp       , zjetM_JESUp       , zjetT_JESUp       , false, false, true, binLMT, "zjet_JESUp", 5, 20, 170);
TH1F* zjetTtrim_JESDown      = trimHistoLMT(zjetL_JESDown     , zjetM_JESDown     , zjetT_JESDown     , false, false, true, binLMT, "zjet_JESDown", 5, 20, 170);
TH1F* zjetTtrim_PileupUp     = trimHistoLMT(zjetL_PileupUp    , zjetM_PileupUp    , zjetT_PileupUp    , false, false, true, binLMT, "zjet_PileupUp", 5, 20, 170);
TH1F* zjetTtrim_PileupDown   = trimHistoLMT(zjetL_PileupDown  , zjetM_PileupDown  , zjetT_PileupDown  , false, false, true, binLMT, "zjet_PileupDown", 5, 20, 170);
TH1F* zjetTtrim_JERUp        = trimHistoLMT(zjetL_JERUp       , zjetM_JERUp       , zjetT_JERUp       , false, false, true, binLMT, "zjet_JERUp", 5, 20, 170);
TH1F* zjetTtrim_JERDown      = trimHistoLMT(zjetL_JERDown     , zjetM_JERDown     , zjetT_JERDown     , false, false, true, binLMT, "zjet_JERDown", 5, 20, 170);
TH1F* zjetTtrim_bTagUp       = trimHistoLMT(zjetL_bTagUp      , zjetM_bTagUp      , zjetT_bTagUp      , false, false, true, binLMT, "zjet_bTagUp", 5, 20, 170);
TH1F* zjetTtrim_bTagDown     = trimHistoLMT(zjetL_bTagDown    , zjetM_bTagDown    , zjetT_bTagDown    , false, false, true, binLMT, "zjet_bTagDown", 5, 20, 170);
TH1F* zjetTtrim_cTagUp       = trimHistoLMT(zjetL_cTagUp      , zjetM_cTagUp      , zjetT_cTagUp      , false, false, true, binLMT, "zjet_cTagUp", 5, 20, 170);
TH1F* zjetTtrim_cTagDown     = trimHistoLMT(zjetL_cTagDown    , zjetM_cTagDown    , zjetT_cTagDown    , false, false, true, binLMT, "zjet_cTagDown", 5, 20, 170);

TH1F* stopL              = getHisto(fTT, fST, "base/Iso/", histnameL);
TH1F* stopL_JESUp        = getHisto(fTT, fST, "JESPlus/Iso/", histnameL);
TH1F* stopL_JESDown      = getHisto(fTT, fST, "JESMinus/Iso/", histnameL);
TH1F* stopL_PileupUp     = getHisto(fTT, fST, "PileupPlus/Iso/", histnameL);
TH1F* stopL_PileupDown   = getHisto(fTT, fST, "PileupMinus/Iso/", histnameL);
TH1F* stopL_JERUp        = getHisto(fTT, fST, "JERPlus/Iso/", histnameL);
TH1F* stopL_JERDown      = getHisto(fTT, fST, "JERMinus/Iso/", histnameL);
TH1F* stopL_bTagUp       = getHisto(fTT, fST, "bTagPlus/Iso/", histnameL);
TH1F* stopL_bTagDown     = getHisto(fTT, fST, "bTagMinus/Iso/", histnameL);
TH1F* stopL_cTagUp       = getHisto(fTT, fST, "cTagPlus/Iso/", histnameL);
TH1F* stopL_cTagDown     = getHisto(fTT, fST, "cTagMinus/Iso/", histnameL);

TH1F* stopM              = getHisto(fTT, fST, "base/Iso/", histnameM);
TH1F* stopM_JESUp        = getHisto(fTT, fST, "JESPlus/Iso/", histnameM);
TH1F* stopM_JESDown      = getHisto(fTT, fST, "JESMinus/Iso/", histnameM);
TH1F* stopM_PileupUp     = getHisto(fTT, fST, "PileupPlus/Iso/", histnameM);
TH1F* stopM_PileupDown   = getHisto(fTT, fST, "PileupMinus/Iso/", histnameM);
TH1F* stopM_JERUp        = getHisto(fTT, fST, "JERPlus/Iso/", histnameM);
TH1F* stopM_JERDown      = getHisto(fTT, fST, "JERMinus/Iso/", histnameM);
TH1F* stopM_bTagUp       = getHisto(fTT, fST, "bTagPlus/Iso/", histnameM);
TH1F* stopM_bTagDown     = getHisto(fTT, fST, "bTagMinus/Iso/", histnameM);
TH1F* stopM_cTagUp       = getHisto(fTT, fST, "cTagPlus/Iso/", histnameM);
TH1F* stopM_cTagDown     = getHisto(fTT, fST, "cTagMinus/Iso/", histnameM);

TH1F* stopT              = getHisto(fTT, fST, "base/Iso/", histnameT);
TH1F* stopT_JESUp        = getHisto(fTT, fST, "JESPlus/Iso/", histnameT);
TH1F* stopT_JESDown      = getHisto(fTT, fST, "JESMinus/Iso/", histnameT);
TH1F* stopT_PileupUp     = getHisto(fTT, fST, "PileupPlus/Iso/", histnameT);
TH1F* stopT_PileupDown   = getHisto(fTT, fST, "PileupMinus/Iso/", histnameT);
TH1F* stopT_JERUp        = getHisto(fTT, fST, "JERPlus/Iso/", histnameT);
TH1F* stopT_JERDown      = getHisto(fTT, fST, "JERMinus/Iso/", histnameT);
TH1F* stopT_bTagUp       = getHisto(fTT, fST, "bTagPlus/Iso/", histnameT);
TH1F* stopT_bTagDown     = getHisto(fTT, fST, "bTagMinus/Iso/", histnameT);
TH1F* stopT_cTagUp       = getHisto(fTT, fST, "cTagPlus/Iso/", histnameT);
TH1F* stopT_cTagDown     = getHisto(fTT, fST, "cTagMinus/Iso/", histnameT);

TH1F* stopLtrim              = trimHistoLMT(stopL, stopM, stopT, true, false, false, binLMT, "stop", 5, 20, 170);
TH1F* stopLtrim_JESUp        = trimHistoLMT(stopL_JESUp       , stopM_JESUp       , stopT_JESUp       , true, false, false, binLMT, "stop_JESUp", 5, 20, 170);
TH1F* stopLtrim_JESDown      = trimHistoLMT(stopL_JESDown     , stopM_JESDown     , stopT_JESDown     , true, false, false, binLMT, "stop_JESDown", 5, 20, 170);
TH1F* stopLtrim_PileupUp     = trimHistoLMT(stopL_PileupUp    , stopM_PileupUp    , stopT_PileupUp    , true, false, false, binLMT, "stop_PileupUp", 5, 20, 170);
TH1F* stopLtrim_PileupDown   = trimHistoLMT(stopL_PileupDown  , stopM_PileupDown  , stopT_PileupDown  , true, false, false, binLMT, "stop_PileupDown", 5, 20, 170);
TH1F* stopLtrim_JERUp        = trimHistoLMT(stopL_JERUp       , stopM_JERUp       , stopT_JERUp       , true, false, false, binLMT, "stop_JERUp", 5, 20, 170);
TH1F* stopLtrim_JERDown      = trimHistoLMT(stopL_JERDown     , stopM_JERDown     , stopT_JERDown     , true, false, false, binLMT, "stop_JERDown", 5, 20, 170);
TH1F* stopLtrim_bTagUp       = trimHistoLMT(stopL_bTagUp      , stopM_bTagUp      , stopT_bTagUp      , true, false, false, binLMT, "stop_bTagUp", 5, 20, 170);
TH1F* stopLtrim_bTagDown     = trimHistoLMT(stopL_bTagDown    , stopM_bTagDown    , stopT_bTagDown    , true, false, false, binLMT, "stop_bTagDown", 5, 20, 170);
TH1F* stopLtrim_cTagUp       = trimHistoLMT(stopL_cTagUp      , stopM_cTagUp      , stopT_cTagUp      , true, false, false, binLMT, "stop_cTagUp", 5, 20, 170);
TH1F* stopLtrim_cTagDown     = trimHistoLMT(stopL_cTagDown    , stopM_cTagDown    , stopT_cTagDown    , true, false, false, binLMT, "stop_cTagDown", 5, 20, 170);

TH1F* stopMtrim              = trimHistoLMT(stopL, stopM, stopT, false, true, false, binLMT, "stop", 5, 20, 170);
TH1F* stopMtrim_JESUp        = trimHistoLMT(stopL_JESUp       , stopM_JESUp       , stopT_JESUp       , false, true, false, binLMT, "stop_JESUp", 5, 20, 170);
TH1F* stopMtrim_JESDown      = trimHistoLMT(stopL_JESDown     , stopM_JESDown     , stopT_JESDown     , false, true, false, binLMT, "stop_JESDown", 5, 20, 170);
TH1F* stopMtrim_PileupUp     = trimHistoLMT(stopL_PileupUp    , stopM_PileupUp    , stopT_PileupUp    , false, true, false, binLMT, "stop_PileupUp", 5, 20, 170);
TH1F* stopMtrim_PileupDown   = trimHistoLMT(stopL_PileupDown  , stopM_PileupDown  , stopT_PileupDown  , false, true, false, binLMT, "stop_PileupDown", 5, 20, 170);
TH1F* stopMtrim_JERUp        = trimHistoLMT(stopL_JERUp       , stopM_JERUp       , stopT_JERUp       , false, true, false, binLMT, "stop_JERUp", 5, 20, 170);
TH1F* stopMtrim_JERDown      = trimHistoLMT(stopL_JERDown     , stopM_JERDown     , stopT_JERDown     , false, true, false, binLMT, "stop_JERDown", 5, 20, 170);
TH1F* stopMtrim_bTagUp       = trimHistoLMT(stopL_bTagUp      , stopM_bTagUp      , stopT_bTagUp      , false, true, false, binLMT, "stop_bTagUp", 5, 20, 170);
TH1F* stopMtrim_bTagDown     = trimHistoLMT(stopL_bTagDown    , stopM_bTagDown    , stopT_bTagDown    , false, true, false, binLMT, "stop_bTagDown", 5, 20, 170);
TH1F* stopMtrim_cTagUp       = trimHistoLMT(stopL_cTagUp      , stopM_cTagUp      , stopT_cTagUp      , false, true, false, binLMT, "stop_cTagUp", 5, 20, 170);
TH1F* stopMtrim_cTagDown     = trimHistoLMT(stopL_cTagDown    , stopM_cTagDown    , stopT_cTagDown    , false, true, false, binLMT, "stop_cTagDown", 5, 20, 170);

TH1F* stopTtrim              = trimHistoLMT(stopL, stopM, stopT, false, false, true, binLMT, "stop", 5, 20, 170);
TH1F* stopTtrim_JESUp        = trimHistoLMT(stopL_JESUp       , stopM_JESUp       , stopT_JESUp       , false, false, true, binLMT, "stop_JESUp", 5, 20, 170);
TH1F* stopTtrim_JESDown      = trimHistoLMT(stopL_JESDown     , stopM_JESDown     , stopT_JESDown     , false, false, true, binLMT, "stop_JESDown", 5, 20, 170);
TH1F* stopTtrim_PileupUp     = trimHistoLMT(stopL_PileupUp    , stopM_PileupUp    , stopT_PileupUp    , false, false, true, binLMT, "stop_PileupUp", 5, 20, 170);
TH1F* stopTtrim_PileupDown   = trimHistoLMT(stopL_PileupDown  , stopM_PileupDown  , stopT_PileupDown  , false, false, true, binLMT, "stop_PileupDown", 5, 20, 170);
TH1F* stopTtrim_JERUp        = trimHistoLMT(stopL_JERUp       , stopM_JERUp       , stopT_JERUp       , false, false, true, binLMT, "stop_JERUp", 5, 20, 170);
TH1F* stopTtrim_JERDown      = trimHistoLMT(stopL_JERDown     , stopM_JERDown     , stopT_JERDown     , false, false, true, binLMT, "stop_JERDown", 5, 20, 170);
TH1F* stopTtrim_bTagUp       = trimHistoLMT(stopL_bTagUp      , stopM_bTagUp      , stopT_bTagUp      , false, false, true, binLMT, "stop_bTagUp", 5, 20, 170);
TH1F* stopTtrim_bTagDown     = trimHistoLMT(stopL_bTagDown    , stopM_bTagDown    , stopT_bTagDown    , false, false, true, binLMT, "stop_bTagDown", 5, 20, 170);
TH1F* stopTtrim_cTagUp       = trimHistoLMT(stopL_cTagUp      , stopM_cTagUp      , stopT_cTagUp      , false, false, true, binLMT, "stop_cTagUp", 5, 20, 170);
TH1F* stopTtrim_cTagDown     = trimHistoLMT(stopL_cTagDown    , stopM_cTagDown    , stopT_cTagDown    , false, false, true, binLMT, "stop_cTagDown", 5, 20, 170);


TH1F* dibosonL              = getHisto(fTT, fVV, "base/Iso/", histnameL);
TH1F* dibosonL_JESUp        = getHisto(fTT, fVV, "JESPlus/Iso/", histnameL);
TH1F* dibosonL_JESDown      = getHisto(fTT, fVV, "JESMinus/Iso/", histnameL);
TH1F* dibosonL_PileupUp     = getHisto(fTT, fVV, "PileupPlus/Iso/", histnameL);
TH1F* dibosonL_PileupDown   = getHisto(fTT, fVV, "PileupMinus/Iso/", histnameL);
TH1F* dibosonL_JERUp        = getHisto(fTT, fVV, "JERPlus/Iso/", histnameL);
TH1F* dibosonL_JERDown      = getHisto(fTT, fVV, "JERMinus/Iso/", histnameL);
TH1F* dibosonL_bTagUp       = getHisto(fTT, fVV, "bTagPlus/Iso/", histnameL);
TH1F* dibosonL_bTagDown     = getHisto(fTT, fVV, "bTagMinus/Iso/", histnameL);
TH1F* dibosonL_cTagUp       = getHisto(fTT, fVV, "cTagPlus/Iso/", histnameL);
TH1F* dibosonL_cTagDown     = getHisto(fTT, fVV, "cTagMinus/Iso/", histnameL);

TH1F* dibosonM              = getHisto(fTT, fVV, "base/Iso/", histnameM);
TH1F* dibosonM_JESUp        = getHisto(fTT, fVV, "JESPlus/Iso/", histnameM);
TH1F* dibosonM_JESDown      = getHisto(fTT, fVV, "JESMinus/Iso/", histnameM);
TH1F* dibosonM_PileupUp     = getHisto(fTT, fVV, "PileupPlus/Iso/", histnameM);
TH1F* dibosonM_PileupDown   = getHisto(fTT, fVV, "PileupMinus/Iso/", histnameM);
TH1F* dibosonM_JERUp        = getHisto(fTT, fVV, "JERPlus/Iso/", histnameM);
TH1F* dibosonM_JERDown      = getHisto(fTT, fVV, "JERMinus/Iso/", histnameM);
TH1F* dibosonM_bTagUp       = getHisto(fTT, fVV, "bTagPlus/Iso/", histnameM);
TH1F* dibosonM_bTagDown     = getHisto(fTT, fVV, "bTagMinus/Iso/", histnameM);
TH1F* dibosonM_cTagUp       = getHisto(fTT, fVV, "cTagPlus/Iso/", histnameM);
TH1F* dibosonM_cTagDown     = getHisto(fTT, fVV, "cTagMinus/Iso/", histnameM);

TH1F* dibosonT              = getHisto(fTT, fVV, "base/Iso/", histnameT);
TH1F* dibosonT_JESUp        = getHisto(fTT, fVV, "JESPlus/Iso/", histnameT);
TH1F* dibosonT_JESDown      = getHisto(fTT, fVV, "JESMinus/Iso/", histnameT);
TH1F* dibosonT_PileupUp     = getHisto(fTT, fVV, "PileupPlus/Iso/", histnameT);
TH1F* dibosonT_PileupDown   = getHisto(fTT, fVV, "PileupMinus/Iso/", histnameT);
TH1F* dibosonT_JERUp        = getHisto(fTT, fVV, "JERPlus/Iso/", histnameT);
TH1F* dibosonT_JERDown      = getHisto(fTT, fVV, "JERMinus/Iso/", histnameT);
TH1F* dibosonT_bTagUp       = getHisto(fTT, fVV, "bTagPlus/Iso/", histnameT);
TH1F* dibosonT_bTagDown     = getHisto(fTT, fVV, "bTagMinus/Iso/", histnameT);
TH1F* dibosonT_cTagUp       = getHisto(fTT, fVV, "cTagPlus/Iso/", histnameT);
TH1F* dibosonT_cTagDown     = getHisto(fTT, fVV, "cTagMinus/Iso/", histnameT);

TH1F* dibosonLtrim              = trimHistoLMT(dibosonL, dibosonM, dibosonT, true, false, false, binLMT, "diboson", 5, 20, 170);
TH1F* dibosonLtrim_JESUp        = trimHistoLMT(dibosonL_JESUp       , dibosonM_JESUp       , dibosonT_JESUp       , true, false, false, binLMT, "diboson_JESUp", 5, 20, 170);
TH1F* dibosonLtrim_JESDown      = trimHistoLMT(dibosonL_JESDown     , dibosonM_JESDown     , dibosonT_JESDown     , true, false, false, binLMT, "diboson_JESDown", 5, 20, 170);
TH1F* dibosonLtrim_PileupUp     = trimHistoLMT(dibosonL_PileupUp    , dibosonM_PileupUp    , dibosonT_PileupUp    , true, false, false, binLMT, "diboson_PileupUp", 5, 20, 170);
TH1F* dibosonLtrim_PileupDown   = trimHistoLMT(dibosonL_PileupDown  , dibosonM_PileupDown  , dibosonT_PileupDown  , true, false, false, binLMT, "diboson_PileupDown", 5, 20, 170);
TH1F* dibosonLtrim_JERUp        = trimHistoLMT(dibosonL_JERUp       , dibosonM_JERUp       , dibosonT_JERUp       , true, false, false, binLMT, "diboson_JERUp", 5, 20, 170);
TH1F* dibosonLtrim_JERDown      = trimHistoLMT(dibosonL_JERDown     , dibosonM_JERDown     , dibosonT_JERDown     , true, false, false, binLMT, "diboson_JERDown", 5, 20, 170);
TH1F* dibosonLtrim_bTagUp       = trimHistoLMT(dibosonL_bTagUp      , dibosonM_bTagUp      , dibosonT_bTagUp      , true, false, false, binLMT, "diboson_bTagUp", 5, 20, 170);
TH1F* dibosonLtrim_bTagDown     = trimHistoLMT(dibosonL_bTagDown    , dibosonM_bTagDown    , dibosonT_bTagDown    , true, false, false, binLMT, "diboson_bTagDown", 5, 20, 170);
TH1F* dibosonLtrim_cTagUp       = trimHistoLMT(dibosonL_cTagUp      , dibosonM_cTagUp      , dibosonT_cTagUp      , true, false, false, binLMT, "diboson_cTagUp", 5, 20, 170);
TH1F* dibosonLtrim_cTagDown     = trimHistoLMT(dibosonL_cTagDown    , dibosonM_cTagDown    , dibosonT_cTagDown    , true, false, false, binLMT, "diboson_cTagDown", 5, 20, 170);

TH1F* dibosonMtrim              = trimHistoLMT(dibosonL, dibosonM, dibosonT, false, true, false, binLMT, "diboson", 5, 20, 170);
TH1F* dibosonMtrim_JESUp        = trimHistoLMT(dibosonL_JESUp       , dibosonM_JESUp       , dibosonT_JESUp       , false, true, false, binLMT, "diboson_JESUp", 5, 20, 170);
TH1F* dibosonMtrim_JESDown      = trimHistoLMT(dibosonL_JESDown     , dibosonM_JESDown     , dibosonT_JESDown     , false, true, false, binLMT, "diboson_JESDown", 5, 20, 170);
TH1F* dibosonMtrim_PileupUp     = trimHistoLMT(dibosonL_PileupUp    , dibosonM_PileupUp    , dibosonT_PileupUp    , false, true, false, binLMT, "diboson_PileupUp", 5, 20, 170);
TH1F* dibosonMtrim_PileupDown   = trimHistoLMT(dibosonL_PileupDown  , dibosonM_PileupDown  , dibosonT_PileupDown  , false, true, false, binLMT, "diboson_PileupDown", 5, 20, 170);
TH1F* dibosonMtrim_JERUp        = trimHistoLMT(dibosonL_JERUp       , dibosonM_JERUp       , dibosonT_JERUp       , false, true, false, binLMT, "diboson_JERUp", 5, 20, 170);
TH1F* dibosonMtrim_JERDown      = trimHistoLMT(dibosonL_JERDown     , dibosonM_JERDown     , dibosonT_JERDown     , false, true, false, binLMT, "diboson_JERDown", 5, 20, 170);
TH1F* dibosonMtrim_bTagUp       = trimHistoLMT(dibosonL_bTagUp      , dibosonM_bTagUp      , dibosonT_bTagUp      , false, true, false, binLMT, "diboson_bTagUp", 5, 20, 170);
TH1F* dibosonMtrim_bTagDown     = trimHistoLMT(dibosonL_bTagDown    , dibosonM_bTagDown    , dibosonT_bTagDown    , false, true, false, binLMT, "diboson_bTagDown", 5, 20, 170);
TH1F* dibosonMtrim_cTagUp       = trimHistoLMT(dibosonL_cTagUp      , dibosonM_cTagUp      , dibosonT_cTagUp      , false, true, false, binLMT, "diboson_cTagUp", 5, 20, 170);
TH1F* dibosonMtrim_cTagDown     = trimHistoLMT(dibosonL_cTagDown    , dibosonM_cTagDown    , dibosonT_cTagDown    , false, true, false, binLMT, "diboson_cTagDown", 5, 20, 170);

TH1F* dibosonTtrim              = trimHistoLMT(dibosonL, dibosonM, dibosonT, false, false, true, binLMT, "diboson", 5, 20, 170);
TH1F* dibosonTtrim_JESUp        = trimHistoLMT(dibosonL_JESUp       , dibosonM_JESUp       , dibosonT_JESUp       , false, false, true, binLMT, "diboson_JESUp", 5, 20, 170);
TH1F* dibosonTtrim_JESDown      = trimHistoLMT(dibosonL_JESDown     , dibosonM_JESDown     , dibosonT_JESDown     , false, false, true, binLMT, "diboson_JESDown", 5, 20, 170);
TH1F* dibosonTtrim_PileupUp     = trimHistoLMT(dibosonL_PileupUp    , dibosonM_PileupUp    , dibosonT_PileupUp    , false, false, true, binLMT, "diboson_PileupUp", 5, 20, 170);
TH1F* dibosonTtrim_PileupDown   = trimHistoLMT(dibosonL_PileupDown  , dibosonM_PileupDown  , dibosonT_PileupDown  , false, false, true, binLMT, "diboson_PileupDown", 5, 20, 170);
TH1F* dibosonTtrim_JERUp        = trimHistoLMT(dibosonL_JERUp       , dibosonM_JERUp       , dibosonT_JERUp       , false, false, true, binLMT, "diboson_JERUp", 5, 20, 170);
TH1F* dibosonTtrim_JERDown      = trimHistoLMT(dibosonL_JERDown     , dibosonM_JERDown     , dibosonT_JERDown     , false, false, true, binLMT, "diboson_JERDown", 5, 20, 170);
TH1F* dibosonTtrim_bTagUp       = trimHistoLMT(dibosonL_bTagUp      , dibosonM_bTagUp      , dibosonT_bTagUp      , false, false, true, binLMT, "diboson_bTagUp", 5, 20, 170);
TH1F* dibosonTtrim_bTagDown     = trimHistoLMT(dibosonL_bTagDown    , dibosonM_bTagDown    , dibosonT_bTagDown    , false, false, true, binLMT, "diboson_bTagDown", 5, 20, 170);
TH1F* dibosonTtrim_cTagUp       = trimHistoLMT(dibosonL_cTagUp      , dibosonM_cTagUp      , dibosonT_cTagUp      , false, false, true, binLMT, "diboson_cTagUp", 5, 20, 170);
TH1F* dibosonTtrim_cTagDown     = trimHistoLMT(dibosonL_cTagDown    , dibosonM_cTagDown    , dibosonT_cTagDown    , false, false, true, binLMT, "diboson_cTagDown", 5, 20, 170);

//QCD data driven
TH1F* qcdL              = getHisto(fTT, fQCD_dd, "base/Iso/", histnameL);
TH1F* qcdM              = getHisto(fTT, fQCD_dd, "base/Iso/", histnameM);
TH1F* qcdT              = getHisto(fTT, fQCD_dd, "base/Iso/", histnameT);
TH1F* qcdLtrim              = trimHistoLMT(qcdL, qcdM, qcdT, true, false, false, binLMT, "qcd", 5, 20, 170);
TH1F* qcdMtrim              = trimHistoLMT(qcdL, qcdM, qcdT, false, true, false, binLMT, "qcd", 5, 20, 170);
TH1F* qcdTtrim              = trimHistoLMT(qcdL, qcdM, qcdT, false, false, true, binLMT, "qcd", 5, 20, 170);

//Data
TH1F* dataL              = getHisto(fTT, fData, "base/Iso/", histnameL);
TH1F* dataM              = getHisto(fTT, fData, "base/Iso/", histnameM);
TH1F* dataT              = getHisto(fTT, fData, "base/Iso/", histnameT);
TH1F* dataLtrim              = trimHistoLMT(dataL, dataM, dataT, true, false, false, binLMT, "data_obs", 5, 20, 170);
TH1F* dataMtrim              = trimHistoLMT(dataL, dataM, dataT, false, true, false, binLMT, "data_obs", 5, 20, 170);
TH1F* dataTtrim              = trimHistoLMT(dataL, dataM, dataT, false, false, true, binLMT, "data_obs", 5, 20, 170);

//----------------------------------------//
//function to make data card for each mass
//----------------------------------------//
//wh
TH1F* whL              = getHisto(fTT, fWH, "base/Iso/", histnameL);
TH1F* whL_JESUp        = getHisto(fTT, fWH, "JESPlus/Iso/", histnameL);
TH1F* whL_JESDown      = getHisto(fTT, fWH, "JESMinus/Iso/", histnameL);
TH1F* whL_PileupUp     = getHisto(fTT, fWH, "PileupPlus/Iso/", histnameL);
TH1F* whL_PileupDown   = getHisto(fTT, fWH, "PileupMinus/Iso/", histnameL);
TH1F* whL_JERUp        = getHisto(fTT, fWH, "JERPlus/Iso/", histnameL);
TH1F* whL_JERDown      = getHisto(fTT, fWH, "JERMinus/Iso/", histnameL);
TH1F* whL_topPtUp      = getHisto(fTT, fWH, "TopPtPlus/Iso/", histnameL);
TH1F* whL_topPtDown    = getHisto(fTT, fWH, "TopPtMinus/Iso/", histnameL);
TH1F* whL_bTagUp       = getHisto(fTT, fWH, "bTagPlus/Iso/", histnameL);
TH1F* whL_bTagDown     = getHisto(fTT, fWH, "bTagMinus/Iso/", histnameL);
TH1F* whL_cTagUp       = getHisto(fTT, fWH, "cTagPlus/Iso/", histnameL);
TH1F* whL_cTagDown     = getHisto(fTT, fWH, "cTagMinus/Iso/", histnameL);

TH1F* whM              = getHisto(fTT, fWH, "base/Iso/", histnameM);
TH1F* whM_JESUp        = getHisto(fTT, fWH, "JESPlus/Iso/", histnameM);
TH1F* whM_JESDown      = getHisto(fTT, fWH, "JESMinus/Iso/", histnameM);
TH1F* whM_PileupUp     = getHisto(fTT, fWH, "PileupPlus/Iso/", histnameM);
TH1F* whM_PileupDown   = getHisto(fTT, fWH, "PileupMinus/Iso/", histnameM);
TH1F* whM_JERUp        = getHisto(fTT, fWH, "JERPlus/Iso/", histnameM);
TH1F* whM_JERDown      = getHisto(fTT, fWH, "JERMinus/Iso/", histnameM);
TH1F* whM_topPtUp      = getHisto(fTT, fWH, "TopPtPlus/Iso/", histnameM);
TH1F* whM_topPtDown    = getHisto(fTT, fWH, "TopPtMinus/Iso/", histnameM);
TH1F* whM_bTagUp       = getHisto(fTT, fWH, "bTagPlus/Iso/", histnameM);
TH1F* whM_bTagDown     = getHisto(fTT, fWH, "bTagMinus/Iso/", histnameM);
TH1F* whM_cTagUp       = getHisto(fTT, fWH, "cTagPlus/Iso/", histnameM);
TH1F* whM_cTagDown     = getHisto(fTT, fWH, "cTagMinus/Iso/", histnameM);

TH1F* whT              = getHisto(fTT, fWH, "base/Iso/", histnameT);
TH1F* whT_JESUp        = getHisto(fTT, fWH, "JESPlus/Iso/", histnameT);
TH1F* whT_JESDown      = getHisto(fTT, fWH, "JESMinus/Iso/", histnameT);
TH1F* whT_PileupUp     = getHisto(fTT, fWH, "PileupPlus/Iso/", histnameT);
TH1F* whT_PileupDown   = getHisto(fTT, fWH, "PileupMinus/Iso/", histnameT);
TH1F* whT_JERUp        = getHisto(fTT, fWH, "JERPlus/Iso/", histnameT);
TH1F* whT_JERDown      = getHisto(fTT, fWH, "JERMinus/Iso/", histnameT);
TH1F* whT_topPtUp      = getHisto(fTT, fWH, "TopPtPlus/Iso/", histnameT);
TH1F* whT_topPtDown    = getHisto(fTT, fWH, "TopPtMinus/Iso/", histnameT);
TH1F* whT_bTagUp       = getHisto(fTT, fWH, "bTagPlus/Iso/", histnameT);
TH1F* whT_bTagDown     = getHisto(fTT, fWH, "bTagMinus/Iso/", histnameT);
TH1F* whT_cTagUp       = getHisto(fTT, fWH, "cTagPlus/Iso/", histnameT);
TH1F* whT_cTagDown     = getHisto(fTT, fWH, "cTagMinus/Iso/", histnameT);

TH1F* whLtrim              = trimHistoLMT(whL, whM, whT, true, false, false, binLMT, SigLab+"", 5, 20, 170);
TH1F* whLtrim_JESUp        = trimHistoLMT(whL_JESUp       , whM_JESUp       , whT_JESUp       , true, false, false, binLMT, SigLab+"_JESUp", 5, 20, 170);
TH1F* whLtrim_JESDown      = trimHistoLMT(whL_JESDown     , whM_JESDown     , whT_JESDown     , true, false, false, binLMT, SigLab+"_JESDown", 5, 20, 170);
TH1F* whLtrim_PileupUp     = trimHistoLMT(whL_PileupUp    , whM_PileupUp    , whT_PileupUp    , true, false, false, binLMT, SigLab+"_PileupUp", 5, 20, 170);
TH1F* whLtrim_PileupDown   = trimHistoLMT(whL_PileupDown  , whM_PileupDown  , whT_PileupDown  , true, false, false, binLMT, SigLab+"_PileupDown", 5, 20, 170);
TH1F* whLtrim_JERUp        = trimHistoLMT(whL_JERUp       , whM_JERUp       , whT_JERUp       , true, false, false, binLMT, SigLab+"_JERUp", 5, 20, 170);
TH1F* whLtrim_JERDown      = trimHistoLMT(whL_JERDown     , whM_JERDown     , whT_JERDown     , true, false, false, binLMT, SigLab+"_JERDown", 5, 20, 170);
TH1F* whLtrim_topPtUp      = trimHistoLMT(whL_topPtUp     , whM_topPtUp     , whT_topPtUp     , true, false, false, binLMT, SigLab+"_topPtup", 5, 20, 170);
TH1F* whLtrim_topPtDown    = trimHistoLMT(whL_topPtDown   , whM_topPtDown   , whT_topPtDown   , true, false, false, binLMT, SigLab+"_topPtDown", 5, 20, 170);
TH1F* whLtrim_bTagUp       = trimHistoLMT(whL_bTagUp      , whM_bTagUp      , whT_bTagUp      , true, false, false, binLMT, SigLab+"_bTagUp", 5, 20, 170);
TH1F* whLtrim_bTagDown     = trimHistoLMT(whL_bTagDown    , whM_bTagDown    , whT_bTagDown    , true, false, false, binLMT, SigLab+"_bTagDown", 5, 20, 170);
TH1F* whLtrim_cTagUp       = trimHistoLMT(whL_cTagUp      , whM_cTagUp      , whT_cTagUp      , true, false, false, binLMT, SigLab+"_cTagUp", 5, 20, 170);
TH1F* whLtrim_cTagDown     = trimHistoLMT(whL_cTagDown    , whM_cTagDown    , whT_cTagDown    , true, false, false, binLMT, SigLab+"_cTagDown", 5, 20, 170);

TH1F* whMtrim              = trimHistoLMT(whL, whM, whT, false, true, false, binLMT, SigLab+"", 5, 20, 170);
TH1F* whMtrim_JESUp        = trimHistoLMT(whL_JESUp       , whM_JESUp       , whT_JESUp       , false, true, false, binLMT, SigLab+"_JESUp", 5, 20, 170);
TH1F* whMtrim_JESDown      = trimHistoLMT(whL_JESDown     , whM_JESDown     , whT_JESDown     , false, true, false, binLMT, SigLab+"_JESDown", 5, 20, 170);
TH1F* whMtrim_PileupUp     = trimHistoLMT(whL_PileupUp    , whM_PileupUp    , whT_PileupUp    , false, true, false, binLMT, SigLab+"_PileupUp", 5, 20, 170);
TH1F* whMtrim_PileupDown   = trimHistoLMT(whL_PileupDown  , whM_PileupDown  , whT_PileupDown  , false, true, false, binLMT, SigLab+"_PileupDown", 5, 20, 170);
TH1F* whMtrim_JERUp        = trimHistoLMT(whL_JERUp       , whM_JERUp       , whT_JERUp       , false, true, false, binLMT, SigLab+"_JERUp", 5, 20, 170);
TH1F* whMtrim_JERDown      = trimHistoLMT(whL_JERDown     , whM_JERDown     , whT_JERDown     , false, true, false, binLMT, SigLab+"_JERDown", 5, 20, 170);
TH1F* whMtrim_topPtUp      = trimHistoLMT(whL_topPtUp     , whM_topPtUp     , whT_topPtUp     , false, true, false, binLMT, SigLab+"_topPtup", 5, 20, 170);
TH1F* whMtrim_topPtDown    = trimHistoLMT(whL_topPtDown   , whM_topPtDown   , whT_topPtDown   , false, true, false, binLMT, SigLab+"_topPtDown", 5, 20, 170);
TH1F* whMtrim_bTagUp       = trimHistoLMT(whL_bTagUp      , whM_bTagUp      , whT_bTagUp      , false, true, false, binLMT, SigLab+"_bTagUp", 5, 20, 170);
TH1F* whMtrim_bTagDown     = trimHistoLMT(whL_bTagDown    , whM_bTagDown    , whT_bTagDown    , false, true, false, binLMT, SigLab+"_bTagDown", 5, 20, 170);
TH1F* whMtrim_cTagUp       = trimHistoLMT(whL_cTagUp      , whM_cTagUp      , whT_cTagUp      , false, true, false, binLMT, SigLab+"_cTagUp", 5, 20, 170);
TH1F* whMtrim_cTagDown     = trimHistoLMT(whL_cTagDown    , whM_cTagDown    , whT_cTagDown    , false, true, false, binLMT, SigLab+"_cTagDown", 5, 20, 170);

TH1F* whTtrim              = trimHistoLMT(whL, whM, whT, false, false, true, binLMT, SigLab+"", 5, 20, 170);
TH1F* whTtrim_JESUp        = trimHistoLMT(whL_JESUp       , whM_JESUp       , whT_JESUp       , false, false, true, binLMT, SigLab+"_JESUp", 5, 20, 170);
TH1F* whTtrim_JESDown      = trimHistoLMT(whL_JESDown     , whM_JESDown     , whT_JESDown     , false, false, true, binLMT, SigLab+"_JESDown", 5, 20, 170);
TH1F* whTtrim_PileupUp     = trimHistoLMT(whL_PileupUp    , whM_PileupUp    , whT_PileupUp    , false, false, true, binLMT, SigLab+"_PileupUp", 5, 20, 170);
TH1F* whTtrim_PileupDown   = trimHistoLMT(whL_PileupDown  , whM_PileupDown  , whT_PileupDown  , false, false, true, binLMT, SigLab+"_PileupDown", 5, 20, 170);
TH1F* whTtrim_JERUp        = trimHistoLMT(whL_JERUp       , whM_JERUp       , whT_JERUp       , false, false, true, binLMT, SigLab+"_JERUp", 5, 20, 170);
TH1F* whTtrim_JERDown      = trimHistoLMT(whL_JERDown     , whM_JERDown     , whT_JERDown     , false, false, true, binLMT, SigLab+"_JERDown", 5, 20, 170);
TH1F* whTtrim_topPtUp      = trimHistoLMT(whL_topPtUp     , whM_topPtUp     , whT_topPtUp     , false, false, true, binLMT, SigLab+"_topPtup", 5, 20, 170);
TH1F* whTtrim_topPtDown    = trimHistoLMT(whL_topPtDown   , whM_topPtDown   , whT_topPtDown   , false, false, true, binLMT, SigLab+"_topPtDown", 5, 20, 170);
TH1F* whTtrim_bTagUp       = trimHistoLMT(whL_bTagUp      , whM_bTagUp      , whT_bTagUp      , false, false, true, binLMT, SigLab+"_bTagUp", 5, 20, 170);
TH1F* whTtrim_bTagDown     = trimHistoLMT(whL_bTagDown    , whM_bTagDown    , whT_bTagDown    , false, false, true, binLMT, SigLab+"_bTagDown", 5, 20, 170);
TH1F* whTtrim_cTagUp       = trimHistoLMT(whL_cTagUp      , whM_cTagUp      , whT_cTagUp      , false, false, true, binLMT, SigLab+"_cTagUp", 5, 20, 170);
TH1F* whTtrim_cTagDown     = trimHistoLMT(whL_cTagDown    , whM_cTagDown    , whT_cTagDown    , false, false, true, binLMT, SigLab+"_cTagDown", 5, 20, 170);

//open input template data card of 8 TeV
ifstream inL;
char* cL = new char[1000];
inL.open("template_datacard_hcs_13TeV.log");
//create output data card for 13 TeV
string outDataCardL = "datacard_hcs_13TeV_mH.txt";
string histname_strL("PtbJetCatL_"+myInHistName);
if(isMuChannel)outDataCardL = "datacard_hcs_13TeV_mu_"+histname_strL+"_mH%d.txt";
else outDataCardL = "datacard_hcs_13TeV_ele_"+histname_strL+"_mH%d.txt";

ofstream outL(Form(outDataCardL.c_str(), mass));
outL.precision(8);


time_t secs=time(0);
tm *t=localtime(&secs);
while (inL.good()){
  inL.getline(cL,1000,'\n');
  if (inL.good()){
    string line(cL);
    if(line.find("Date")!=string::npos){
      string day = string(Form("%d",t->tm_mday));
      string month = string(Form("%d",t->tm_mon+1));
      string year = string(Form("%d",t->tm_year+1900));
      line.replace( line.find("XXX") , 3 , day+"/"+month+"/"+year);
      outL << line << endl;
    }
    else if(line.find("Description")!=string::npos){
      line.replace( line.find("YYY") , 3 , string(Form("%d", mass)) );
      line.replace( line.find("ZZZ") , 3 , string(Form("%f", totLumi)) ); 
      line.replace( line.find("CCC") , 3 , string(Form("%s", channel)) );
      outL << line << endl;
    }
    else if(line.find("shapes")!=string::npos){
      line.replace( line.find("XXX") , 3 , string(outShapeFile+"_"+TString(channel)+"_PtbJetCatL_"+myInHistName+"_"+SigLab));
      //line.replace( line.find("XXX") , 3 , string(outShapeFile+"_CHANNEL_inShapeHistoDir__inShapeHisto_"));
      outL << line << endl;
    }
    else if(line.find("Observation")!=string::npos){
      line.replace( line.find("XXX") , 3 , string(Form("%.0f", dataLtrim->Integral())));
      outL << line << endl;
    }
    else if(line.find("process")!=string::npos && line.find("WH")!=string::npos){
      line.replace( line.find("YYY") , 3 , string(Form("%d", mass)) );
      outL << line << endl;
    }
    else if(line.find("rate")!=string::npos){
      string rate = "rate               ";  
      string space = "     ";
      outL << rate ;
      outL << space << whLtrim->Integral()
          << space << ttbarLtrim->Integral()
          << space << wjetLtrim->Integral()
          << space << zjetLtrim->Integral()
          << space << stopLtrim->Integral()
          << space << dibosonLtrim->Integral()
          << space << qcdLtrim->Integral()
          << endl;
    }
    else if(line.find("CMS_eff_lep")!=string::npos){  
      if(isMuChannel) line.replace( line.find("lep") , 4 , string(Form("%s", "m")));   
      else line.replace( line.find("lep") , 4 , string(Form("%s", "e")));
      outL << line << endl;
    }  
    else if(line.find("CMS_eff_b")!=string::npos){
      float bTagUnc_wh = (whLtrim->Integral() > 0) ? getBTagUnc(whLtrim, whLtrim_bTagUp, whLtrim_bTagDown) : 1.00;
      line.replace( line.find("HHHH") , 4 , string(Form("%.3f", bTagUnc_wh)) );
      
      float bTagUnc_ttbar = (ttbarLtrim->Integral() > 0) ? getBTagUnc(ttbarLtrim, ttbarLtrim_bTagUp, ttbarLtrim_bTagDown) : 1.00; 
      line.replace( line.find("TTTT") , 4 , string(Form("%.3f", bTagUnc_ttbar)) ); 
      
      float bTagUnc_wjet = (wjetLtrim->Integral() > 0) ? getBTagUnc(wjetLtrim, wjetLtrim_bTagUp, wjetLtrim_bTagDown) : 1.00;
      line.replace( line.find("WWWW") , 4 , string(Form("%.3f", bTagUnc_wjet)) ); 
     
      float bTagUnc_zjet = (zjetLtrim->Integral() > 0) ? getBTagUnc(zjetLtrim, zjetLtrim_bTagUp, zjetLtrim_bTagDown) : 1.00;
      line.replace( line.find("DDDD") , 4 , string(Form("%.3f", bTagUnc_zjet)) ); 

      float bTagUnc_stop = (stopLtrim->Integral() > 0) ? getBTagUnc(stopLtrim, stopLtrim_bTagUp, stopLtrim_bTagDown) : 1.00; 
      line.replace( line.find("SSSS") , 4 , string(Form("%.3f", bTagUnc_stop)) ); 

      float bTagUnc_diboson = (dibosonLtrim->Integral() > 0) ? getBTagUnc(dibosonLtrim, dibosonLtrim_bTagUp, dibosonLtrim_bTagDown) : 1.00;
      line.replace( line.find("VVVV") , 4 , string(Form("%.3f", bTagUnc_diboson)) ); 
      outL << line << endl;
    }
    else if(line.find("CMS_eff_c")!=string::npos){
      float cTagUnc_wh = (whLtrim->Integral() > 0) ? getBTagUnc(whLtrim, whLtrim_cTagUp, whLtrim_cTagDown) : 1.00;
      line.replace( line.find("HHHH") , 4 , string(Form("%.3f", cTagUnc_wh)) );
      
      float cTagUnc_ttbar = (ttbarLtrim->Integral() > 0) ? getBTagUnc(ttbarLtrim, ttbarLtrim_cTagUp, ttbarLtrim_cTagDown) : 1.00; 
      line.replace( line.find("TTTT") , 4 , string(Form("%.3f", cTagUnc_ttbar)) ); 
      
      float cTagUnc_wjet = (wjetLtrim->Integral() > 0) ? getBTagUnc(wjetLtrim, wjetLtrim_cTagUp, wjetLtrim_cTagDown) : 1.00;
      line.replace( line.find("WWWW") , 4 , string(Form("%.3f", cTagUnc_wjet)) ); 
     
      float cTagUnc_zjet = (zjetLtrim->Integral() > 0) ? getBTagUnc(zjetLtrim, zjetLtrim_cTagUp, zjetLtrim_cTagDown) : 1.00;
      line.replace( line.find("DDDD") , 4 , string(Form("%.3f", cTagUnc_zjet)) ); 
      
      float cTagUnc_stop = (stopLtrim->Integral() > 0) ? getBTagUnc(stopLtrim, stopLtrim_cTagUp, stopLtrim_cTagDown) : 1.00; 
      line.replace( line.find("SSSS") , 4 , string(Form("%.3f", cTagUnc_stop)) ); 

      float cTagUnc_diboson = (dibosonLtrim->Integral() > 0) ? getBTagUnc(dibosonLtrim, dibosonLtrim_cTagUp, dibosonLtrim_cTagDown) : 1.00;
      line.replace( line.find("VVVV") , 4 , string(Form("%.3f", cTagUnc_diboson)) ); 
      outL << line << endl;
    }
    else if(line.find("CMS_pileup")!=string::npos){
      float PileupUnc_wh = (whLtrim->Integral() > 0) ? getBTagUnc(whLtrim, whLtrim_PileupUp, whLtrim_PileupDown) : 1.00;
      line.replace( line.find("HHHH") , 4 , string(Form("%.3f", PileupUnc_wh)) );
      
      float PileupUnc_ttbar = (ttbarLtrim->Integral() > 0) ? getBTagUnc(ttbarLtrim, ttbarLtrim_PileupUp, ttbarLtrim_PileupDown) : 1.00; 
      line.replace( line.find("TTTT") , 4 , string(Form("%.3f", PileupUnc_ttbar)) ); 
      
      float PileupUnc_wjet = (wjetLtrim->Integral() > 0) ? getBTagUnc(wjetLtrim, wjetLtrim_PileupUp, wjetLtrim_PileupDown) : 1.00;
      line.replace( line.find("WWWW") , 4 , string(Form("%.3f", PileupUnc_wjet)) ); 
     
      float PileupUnc_zjet = (zjetLtrim->Integral() > 0) ? getBTagUnc(zjetLtrim, zjetLtrim_PileupUp, zjetLtrim_PileupDown) : 1.00;
      line.replace( line.find("DDDD") , 4 , string(Form("%.3f", PileupUnc_zjet)) ); 
      
      float PileupUnc_stop = (stopLtrim->Integral() > 0) ? getBTagUnc(stopLtrim, stopLtrim_PileupUp, stopLtrim_PileupDown) : 1.00; 
      line.replace( line.find("SSSS") , 4 , string(Form("%.3f", PileupUnc_stop)) ); 

      float PileupUnc_diboson = (dibosonLtrim->Integral() > 0) ? getBTagUnc(dibosonLtrim, dibosonLtrim_PileupUp, dibosonLtrim_PileupDown) : 1.00;
      line.replace( line.find("VVVV") , 4 , string(Form("%.3f", PileupUnc_diboson)) ); 
      outL << line << endl;
    }
    else if(line.find("CMS_scale_j")!=string::npos){
      float JESUnc_wh = (whLtrim->Integral() > 0) ? getBTagUnc(whLtrim, whLtrim_JESUp, whLtrim_JESDown) : 1.00;
      line.replace( line.find("HHHH") , 4 , string(Form("%.3f", JESUnc_wh)) );
      
      float JESUnc_ttbar = (ttbarLtrim->Integral() > 0) ? getBTagUnc(ttbarLtrim, ttbarLtrim_JESUp, ttbarLtrim_JESDown) : 1.00; 
      line.replace( line.find("TTTT") , 4 , string(Form("%.3f", JESUnc_ttbar)) ); 
      
      float JESUnc_wjet = (wjetLtrim->Integral() > 0) ? getBTagUnc(wjetLtrim, wjetLtrim_JESUp, wjetLtrim_JESDown) : 1.00;
      line.replace( line.find("WWWW") , 4 , string(Form("%.3f", JESUnc_wjet)) ); 
     
      float JESUnc_zjet = (zjetLtrim->Integral() > 0) ? getBTagUnc(zjetLtrim, zjetLtrim_JESUp, zjetLtrim_JESDown) : 1.00;
      line.replace( line.find("DDDD") , 4 , string(Form("%.3f", JESUnc_zjet)) ); 
      
      float JESUnc_stop = (stopLtrim->Integral() > 0) ? getBTagUnc(stopLtrim, stopLtrim_JESUp, stopLtrim_JESDown) : 1.00; 
      line.replace( line.find("SSSS") , 4 , string(Form("%.3f", JESUnc_stop)) ); 

      float JESUnc_diboson = (dibosonLtrim->Integral() > 0) ? getBTagUnc(dibosonLtrim, dibosonLtrim_JESUp, dibosonLtrim_JESDown) : 1.00;
      line.replace( line.find("VVVV") , 4 , string(Form("%.3f", JESUnc_diboson)) ); 
      outL << line << endl;
    }
    else if(line.find("CMS_res_j")!=string::npos){
      float JERUnc_wh = (whLtrim->Integral() > 0) ? getBTagUnc(whLtrim, whLtrim_JERUp, whLtrim_JERDown) : 1.00;
      line.replace( line.find("HHHH") , 4 , string(Form("%.3f", JERUnc_wh)) );
      
      float JERUnc_ttbar = (ttbarLtrim->Integral() > 0) ? getBTagUnc(ttbarLtrim, ttbarLtrim_JERUp, ttbarLtrim_JERDown) : 1.00; 
      line.replace( line.find("TTTT") , 4 , string(Form("%.3f", JERUnc_ttbar)) ); 
      
      float JERUnc_wjet = (wjetLtrim->Integral() > 0) ? getBTagUnc(wjetLtrim, wjetLtrim_JERUp, wjetLtrim_JERDown) : 1.00;
      line.replace( line.find("WWWW") , 4 , string(Form("%.3f", JERUnc_wjet)) ); 
     
      float JERUnc_zjet = (zjetLtrim->Integral() > 0) ? getBTagUnc(zjetLtrim, zjetLtrim_JERUp, zjetLtrim_JERDown) : 1.00;
      line.replace( line.find("DDDD") , 4 , string(Form("%.3f", JERUnc_zjet)) ); 
      
      float JERUnc_stop = (stopLtrim->Integral() > 0) ? getBTagUnc(stopLtrim, stopLtrim_JERUp, stopLtrim_JERDown) : 1.00; 
      line.replace( line.find("SSSS") , 4 , string(Form("%.3f", JERUnc_stop)) ); 

      float JERUnc_diboson = (dibosonLtrim->Integral() > 0) ? getBTagUnc(dibosonLtrim, dibosonLtrim_JERUp, dibosonLtrim_JERDown) : 1.00;
      line.replace( line.find("VVVV") , 4 , string(Form("%.3f", JERUnc_diboson)) ); 
      outL << line << endl;
    }
    else if(line.find("CMS_hcs_stat_wh")!=string::npos){ 
      line.replace( line.find("XXXX") , 4 , string(Form("%.3f", getStatUnc(whLtrim,  0))));  
      outL << line << endl;
    } 
    else if(line.find("CMS_hcs_stat_tt")!=string::npos){  
  line.replace( line.find("XXXX") , 4 , string(Form("%.3f", getStatUnc(ttbarLtrim,  0))));   
      outL << line << endl;
    }  
    else if(line.find("CMS_hcs_stat_wjet")!=string::npos){  
      line.replace( line.find("XXXX") , 4 , string(Form("%.3f", getStatUnc(wjetLtrim,  0))));   
      outL << line << endl;
    }  
    else if(line.find("CMS_hcs_stat_zjet")!=string::npos){ 
      line.replace( line.find("XXXX") , 4 , string(Form("%.3f", getStatUnc(zjetLtrim,  0))));  
      outL << line << endl; 
    }
    else if(line.find("CMS_hcs_stat_stop")!=string::npos){ 
      line.replace( line.find("XXXX") , 4 , string(Form("%.3f", getStatUnc(stopLtrim,  0))));  
      outL << line << endl; 
    } 
    else if(line.find("CMS_hcs_stat_vv")!=string::npos){  
      line.replace( line.find("XXXX") , 4 , string(Form("%.3f", getStatUnc(dibosonLtrim,  0))));   
      outL << line << endl;  
    }
    else if(line.find("CMS_hcs_stat_qcd")!=string::npos){  
      line.replace( line.find("XXXX") , 4 , string(Form("%.3f", getStatUnc(qcdLtrim,  0))));   
      outL << line << endl;  
    }
    else if(line.find("CMS_norm_qcd")!=string::npos){  
      if(isMuChannel) line.replace( line.find("QQQQ") , 4 , string(Form("%.3f", 1.72)));   
      else line.replace( line.find("QQQQ") , 4 , string(Form("%.3f", 1.40)));   
      outL << line << endl;  
    }
    else if(line.find("CMS_topPtReweight")!=string::npos){
      float topPtUnc_wh = (whLtrim->Integral() > 0) ? getBTagUnc(whLtrim, whLtrim_topPtUp, whLtrim_topPtDown) : 1.00;
      line.replace( line.find("HHHH") , 4 , string(Form("%.3f", topPtUnc_wh)) );
      
      float topPtUnc_ttbar = (ttbarLtrim->Integral() > 0) ? getBTagUnc(ttbarLtrim, ttbarLtrim_topPtUp, ttbarLtrim_topPtDown) : 1.00; 
      line.replace( line.find("TTTT") , 4 , string(Form("%.3f", topPtUnc_ttbar)) ); 
      outL << line << endl;
    }
    else{ //default without changes
      outL << line << endl;
    }
  }
} 
foutL->cd();
ttbarLtrim->Write();
ttbarLtrim_scaleUp->Write();
ttbarLtrim_scaleDown->Write();
ttbarLtrim_mtop1735->Write();
ttbarLtrim_mtop1715->Write();
ttbarLtrim_matchingUp->Write();
ttbarLtrim_matchingDown->Write();
wjetLtrim->Write();
zjetLtrim->Write();
stopLtrim->Write();
dibosonLtrim->Write();
qcdLtrim->Write();
dataLtrim->Write();
whLtrim->Write();
outL.close();
inL.close();
foutL->Close();

//open input template data card of 8 TeV
ifstream inM;
char* cM = new char[1000];
inM.open("template_datacard_hcs_13TeV.log");
//create output data card for 13 TeV
string outDataCardM = "datacard_hcs_13TeV_mH.txt";
string histname_strM("PtbJetCatM_"+myInHistName);
if(isMuChannel) outDataCardM = "datacard_hcs_13TeV_mu_"+histname_strM+"_mH%d.txt"; 
else outDataCardM = "datacard_hcs_13TeV_ele_"+histname_strM+"_mH%d.txt";
ofstream outM(Form(outDataCardM.c_str(), mass));
outM.precision(8);

time_t secs=time(0);
tm *t=localtime(&secs);
while (inM.good()){
  inM.getline(cM,1000,'\n');
  if (inM.good()){
    string line(cM);
    if(line.find("Date")!=string::npos){
      string day = string(Form("%d",t->tm_mday));
      string month = string(Form("%d",t->tm_mon+1));
      string year = string(Form("%d",t->tm_year+1900));
      line.replace( line.find("XXX") , 3 , day+"/"+month+"/"+year);
      outM << line << endl;
    }
    else if(line.find("Description")!=string::npos){
      line.replace( line.find("YYY") , 3 , string(Form("%d", mass)) );
      line.replace( line.find("ZZZ") , 3 , string(Form("%f", totLumi)) ); 
      line.replace( line.find("CCC") , 3 , string(Form("%s", channel)) );
      outM << line << endl;
    }
    else if(line.find("shapes")!=string::npos){
      line.replace( line.find("XXX") , 3 , string(outShapeFile+"_"+TString(channel)+"_PtbJetCatM_"+myInHistName+"_"+SigLab));
      //line.replace( line.find("XXX") , 3 , string(outShapeFile+"_CHANNEL_inShapeHistoDir__inShapeHisto_"));
      outM << line << endl;
    }
    else if(line.find("Observation")!=string::npos){
      line.replace( line.find("XXX") , 3 , string(Form("%.0f", dataMtrim->Integral())));
      outM << line << endl;
    }
    else if(line.find("process")!=string::npos && line.find("WH")!=string::npos){
      line.replace( line.find("YYY") , 3 , string(Form("%d", mass)) );
      outM << line << endl;
    }
    else if(line.find("rate")!=string::npos){
      string rate = "rate               ";  
      string space = "     ";
      outM << rate ;
      outM << space << whMtrim->Integral()
          << space << ttbarMtrim->Integral()
          << space << wjetMtrim->Integral()
          << space << zjetMtrim->Integral()
          << space << stopMtrim->Integral()
          << space << dibosonMtrim->Integral()
          << space << qcdMtrim->Integral()
          << endl;
    }
    else if(line.find("CMS_eff_lep")!=string::npos){  
      if(isMuChannel) line.replace( line.find("lep") , 4 , string(Form("%s", "m")));   
      else line.replace( line.find("lep") , 4 , string(Form("%s", "e")));
      outM << line << endl;
    }  
    else if(line.find("CMS_eff_b")!=string::npos){
      float bTagUnc_wh = (whMtrim->Integral() > 0) ? getBTagUnc(whMtrim, whMtrim_bTagUp, whMtrim_bTagDown) : 1.00;
      line.replace( line.find("HHHH") , 4 , string(Form("%.3f", bTagUnc_wh)) );
      
      float bTagUnc_ttbar = (ttbarMtrim->Integral() > 0) ? getBTagUnc(ttbarMtrim, ttbarMtrim_bTagUp, ttbarMtrim_bTagDown) : 1.00; 
      line.replace( line.find("TTTT") , 4 , string(Form("%.3f", bTagUnc_ttbar)) ); 
      
      float bTagUnc_wjet = (wjetMtrim->Integral() > 0) ? getBTagUnc(wjetMtrim, wjetMtrim_bTagUp, wjetMtrim_bTagDown) : 1.00;
      line.replace( line.find("WWWW") , 4 , string(Form("%.3f", bTagUnc_wjet)) ); 
     
      float bTagUnc_zjet = (zjetMtrim->Integral() > 0) ? getBTagUnc(zjetMtrim, zjetMtrim_bTagUp, zjetMtrim_bTagDown) : 1.00;
      line.replace( line.find("DDDD") , 4 , string(Form("%.3f", bTagUnc_zjet)) ); 

      float bTagUnc_stop = (stopMtrim->Integral() > 0) ? getBTagUnc(stopMtrim, stopMtrim_bTagUp, stopMtrim_bTagDown) : 1.00; 
      line.replace( line.find("SSSS") , 4 , string(Form("%.3f", bTagUnc_stop)) ); 

      float bTagUnc_diboson = (dibosonMtrim->Integral() > 0) ? getBTagUnc(dibosonMtrim, dibosonMtrim_bTagUp, dibosonMtrim_bTagDown) : 1.00;
      line.replace( line.find("VVVV") , 4 , string(Form("%.3f", bTagUnc_diboson)) ); 
      outM << line << endl;
    }
    else if(line.find("CMS_eff_c")!=string::npos){
      float cTagUnc_wh = (whMtrim->Integral() > 0) ? getBTagUnc(whMtrim, whMtrim_cTagUp, whMtrim_cTagDown) : 1.00;
      line.replace( line.find("HHHH") , 4 , string(Form("%.3f", cTagUnc_wh)) );
      
      float cTagUnc_ttbar = (ttbarMtrim->Integral() > 0) ? getBTagUnc(ttbarMtrim, ttbarMtrim_cTagUp, ttbarMtrim_cTagDown) : 1.00; 
      line.replace( line.find("TTTT") , 4 , string(Form("%.3f", cTagUnc_ttbar)) ); 
      
      float cTagUnc_wjet = (wjetMtrim->Integral() > 0) ? getBTagUnc(wjetMtrim, wjetMtrim_cTagUp, wjetMtrim_cTagDown) : 1.00;
      line.replace( line.find("WWWW") , 4 , string(Form("%.3f", cTagUnc_wjet)) ); 
     
      float cTagUnc_zjet = (zjetMtrim->Integral() > 0) ? getBTagUnc(zjetMtrim, zjetMtrim_cTagUp, zjetMtrim_cTagDown) : 1.00;
      line.replace( line.find("DDDD") , 4 , string(Form("%.3f", cTagUnc_zjet)) ); 
      
      float cTagUnc_stop = (stopMtrim->Integral() > 0) ? getBTagUnc(stopMtrim, stopMtrim_cTagUp, stopMtrim_cTagDown) : 1.00; 
      line.replace( line.find("SSSS") , 4 , string(Form("%.3f", cTagUnc_stop)) ); 

      float cTagUnc_diboson = (dibosonMtrim->Integral() > 0) ? getBTagUnc(dibosonMtrim, dibosonMtrim_cTagUp, dibosonMtrim_cTagDown) : 1.00;
      line.replace( line.find("VVVV") , 4 , string(Form("%.3f", cTagUnc_diboson)) ); 
      outM << line << endl;
    }
    else if(line.find("CMS_pileup")!=string::npos){
      float PileupUnc_wh = (whMtrim->Integral() > 0) ? getBTagUnc(whMtrim, whMtrim_PileupUp, whMtrim_PileupDown) : 1.00;
      line.replace( line.find("HHHH") , 4 , string(Form("%.3f", PileupUnc_wh)) );
      
      float PileupUnc_ttbar = (ttbarMtrim->Integral() > 0) ? getBTagUnc(ttbarMtrim, ttbarMtrim_PileupUp, ttbarMtrim_PileupDown) : 1.00; 
      line.replace( line.find("TTTT") , 4 , string(Form("%.3f", PileupUnc_ttbar)) ); 
      
      float PileupUnc_wjet = (wjetMtrim->Integral() > 0) ? getBTagUnc(wjetMtrim, wjetMtrim_PileupUp, wjetMtrim_PileupDown) : 1.00;
      line.replace( line.find("WWWW") , 4 , string(Form("%.3f", PileupUnc_wjet)) ); 
     
      float PileupUnc_zjet = (zjetMtrim->Integral() > 0) ? getBTagUnc(zjetMtrim, zjetMtrim_PileupUp, zjetMtrim_PileupDown) : 1.00;
      line.replace( line.find("DDDD") , 4 , string(Form("%.3f", PileupUnc_zjet)) ); 
      
      float PileupUnc_stop = (stopMtrim->Integral() > 0) ? getBTagUnc(stopMtrim, stopMtrim_PileupUp, stopMtrim_PileupDown) : 1.00; 
      line.replace( line.find("SSSS") , 4 , string(Form("%.3f", PileupUnc_stop)) ); 

      float PileupUnc_diboson = (dibosonMtrim->Integral() > 0) ? getBTagUnc(dibosonMtrim, dibosonMtrim_PileupUp, dibosonMtrim_PileupDown) : 1.00;
      line.replace( line.find("VVVV") , 4 , string(Form("%.3f", PileupUnc_diboson)) ); 
      outM << line << endl;
    }
    else if(line.find("CMS_scale_j")!=string::npos){
      float JESUnc_wh = (whMtrim->Integral() > 0) ? getBTagUnc(whMtrim, whMtrim_JESUp, whMtrim_JESDown) : 1.00;
      line.replace( line.find("HHHH") , 4 , string(Form("%.3f", JESUnc_wh)) );
      
      float JESUnc_ttbar = (ttbarMtrim->Integral() > 0) ? getBTagUnc(ttbarMtrim, ttbarMtrim_JESUp, ttbarMtrim_JESDown) : 1.00; 
      line.replace( line.find("TTTT") , 4 , string(Form("%.3f", JESUnc_ttbar)) ); 
      
      float JESUnc_wjet = (wjetMtrim->Integral() > 0) ? getBTagUnc(wjetMtrim, wjetMtrim_JESUp, wjetMtrim_JESDown) : 1.00;
      line.replace( line.find("WWWW") , 4 , string(Form("%.3f", JESUnc_wjet)) ); 
     
      float JESUnc_zjet = (zjetMtrim->Integral() > 0) ? getBTagUnc(zjetMtrim, zjetMtrim_JESUp, zjetMtrim_JESDown) : 1.00;
      line.replace( line.find("DDDD") , 4 , string(Form("%.3f", JESUnc_zjet)) ); 
      
      float JESUnc_stop = (stopMtrim->Integral() > 0) ? getBTagUnc(stopMtrim, stopMtrim_JESUp, stopMtrim_JESDown) : 1.00; 
      line.replace( line.find("SSSS") , 4 , string(Form("%.3f", JESUnc_stop)) ); 

      float JESUnc_diboson = (dibosonMtrim->Integral() > 0) ? getBTagUnc(dibosonMtrim, dibosonMtrim_JESUp, dibosonMtrim_JESDown) : 1.00;
      line.replace( line.find("VVVV") , 4 , string(Form("%.3f", JESUnc_diboson)) ); 
      outM << line << endl;
    }
    else if(line.find("CMS_res_j")!=string::npos){
      float JERUnc_wh = (whMtrim->Integral() > 0) ? getBTagUnc(whMtrim, whMtrim_JERUp, whMtrim_JERDown) : 1.00;
      line.replace( line.find("HHHH") , 4 , string(Form("%.3f", JERUnc_wh)) );
      
      float JERUnc_ttbar = (ttbarMtrim->Integral() > 0) ? getBTagUnc(ttbarMtrim, ttbarMtrim_JERUp, ttbarMtrim_JERDown) : 1.00; 
      line.replace( line.find("TTTT") , 4 , string(Form("%.3f", JERUnc_ttbar)) ); 
      
      float JERUnc_wjet = (wjetMtrim->Integral() > 0) ? getBTagUnc(wjetMtrim, wjetMtrim_JERUp, wjetMtrim_JERDown) : 1.00;
      line.replace( line.find("WWWW") , 4 , string(Form("%.3f", JERUnc_wjet)) ); 
     
      float JERUnc_zjet = (zjetMtrim->Integral() > 0) ? getBTagUnc(zjetMtrim, zjetMtrim_JERUp, zjetMtrim_JERDown) : 1.00;
      line.replace( line.find("DDDD") , 4 , string(Form("%.3f", JERUnc_zjet)) ); 
      
      float JERUnc_stop = (stopMtrim->Integral() > 0) ? getBTagUnc(stopMtrim, stopMtrim_JERUp, stopMtrim_JERDown) : 1.00; 
      line.replace( line.find("SSSS") , 4 , string(Form("%.3f", JERUnc_stop)) ); 

      float JERUnc_diboson = (dibosonMtrim->Integral() > 0) ? getBTagUnc(dibosonMtrim, dibosonMtrim_JERUp, dibosonMtrim_JERDown) : 1.00;
      line.replace( line.find("VVVV") , 4 , string(Form("%.3f", JERUnc_diboson)) ); 
      outM << line << endl;
    }
    else if(line.find("CMS_hcs_stat_wh")!=string::npos){ 
      line.replace( line.find("XXXX") , 4 , string(Form("%.3f", getStatUnc(whMtrim,  0))));  
      outM << line << endl;
    } 
    else if(line.find("CMS_hcs_stat_tt")!=string::npos){  
  line.replace( line.find("XXXX") , 4 , string(Form("%.3f", getStatUnc(ttbarMtrim,  0))));   
      outM << line << endl;
    }  
    else if(line.find("CMS_hcs_stat_wjet")!=string::npos){  
      line.replace( line.find("XXXX") , 4 , string(Form("%.3f", getStatUnc(wjetMtrim,  0))));   
      outM << line << endl;
    }  
    else if(line.find("CMS_hcs_stat_zjet")!=string::npos){ 
      line.replace( line.find("XXXX") , 4 , string(Form("%.3f", getStatUnc(zjetMtrim,  0))));  
      outM << line << endl; 
    }
    else if(line.find("CMS_hcs_stat_stop")!=string::npos){ 
      line.replace( line.find("XXXX") , 4 , string(Form("%.3f", getStatUnc(stopMtrim,  0))));  
      outM << line << endl; 
    } 
    else if(line.find("CMS_hcs_stat_vv")!=string::npos){  
      line.replace( line.find("XXXX") , 4 , string(Form("%.3f", getStatUnc(dibosonMtrim,  0))));   
      outM << line << endl;  
    }
    else if(line.find("CMS_hcs_stat_qcd")!=string::npos){  
      line.replace( line.find("XXXX") , 4 , string(Form("%.3f", getStatUnc(qcdMtrim,  0))));   
      outM << line << endl;  
    }
    else if(line.find("CMS_norm_qcd")!=string::npos){  
      if(isMuChannel) line.replace( line.find("QQQQ") , 4 , string(Form("%.3f", 1.72)));   
      else line.replace( line.find("QQQQ") , 4 , string(Form("%.3f", 1.40)));   
      outM << line << endl;  
    }
    else if(line.find("CMS_topPtReweight")!=string::npos){
      float topPtUnc_wh = (whMtrim->Integral() > 0) ? getBTagUnc(whMtrim, whMtrim_topPtUp, whMtrim_topPtDown) : 1.00;
      line.replace( line.find("HHHH") , 4 , string(Form("%.3f", topPtUnc_wh)) );
      
      float topPtUnc_ttbar = (ttbarMtrim->Integral() > 0) ? getBTagUnc(ttbarMtrim, ttbarMtrim_topPtUp, ttbarMtrim_topPtDown) : 1.00; 
      line.replace( line.find("TTTT") , 4 , string(Form("%.3f", topPtUnc_ttbar)) ); 
      outM << line << endl;
    }
    else{ //default without changes
      outM << line << endl;
    }
  }
} 
foutM->cd();
ttbarMtrim->Write();
ttbarMtrim_scaleUp->Write();
ttbarMtrim_scaleDown->Write();
ttbarMtrim_mtop1735->Write();
ttbarMtrim_mtop1715->Write();
ttbarMtrim_matchingUp->Write();
ttbarMtrim_matchingDown->Write();
wjetMtrim->Write();
zjetMtrim->Write();
stopMtrim->Write();
dibosonMtrim->Write();
qcdMtrim->Write();
dataMtrim->Write();
whMtrim->Write();
outM.close();
inM.close();
foutM->Close();

//open input template data card of 8 TeV
ifstream inT;
char* cT = new char[1000];
inT.open("template_datacard_hcs_13TeV.log");
//create output data card for 13 TeV
string outDataCardT = "datacard_hcs_13TeV_mH.txt";
string histname_strT("PtbJetCatT_"+myInHistName);
if(isMuChannel) outDataCardT = "datacard_hcs_13TeV_mu_"+histname_strT+"_mH%d.txt"; 
else outDataCardT = "datacard_hcs_13TeV_ele_"+histname_strT+"_mH%d.txt";
ofstream outT(Form(outDataCardT.c_str(), mass));
outT.precision(8);

time_t secs=time(0);
tm *t=localtime(&secs);
while (inT.good()){
  inT.getline(cT,1000,'\n');
  if (inT.good()){
    string line(cT);
    if(line.find("Date")!=string::npos){
      string day = string(Form("%d",t->tm_mday));
      string month = string(Form("%d",t->tm_mon+1));
      string year = string(Form("%d",t->tm_year+1900));
      line.replace( line.find("XXX") , 3 , day+"/"+month+"/"+year);
      outT << line << endl;
    }
    else if(line.find("Description")!=string::npos){
      line.replace( line.find("YYY") , 3 , string(Form("%d", mass)) );
      line.replace( line.find("ZZZ") , 3 , string(Form("%f", totLumi)) ); 
      line.replace( line.find("CCC") , 3 , string(Form("%s", channel)) );
      outT << line << endl;
    }
    else if(line.find("shapes")!=string::npos){
      line.replace( line.find("XXX") , 3 , string(outShapeFile+"_"+TString(channel)+"_PtbJetCatT_"+myInHistName+"_"+SigLab));
      //line.replace( line.find("XXX") , 3 , string(outShapeFile+"_CHANNEL_inShapeHistoDir__inShapeHisto_"));
      outT << line << endl;
    }
    else if(line.find("Observation")!=string::npos){
      line.replace( line.find("XXX") , 3 , string(Form("%.0f", dataTtrim->Integral())));
      outT << line << endl;
    }
    else if(line.find("process")!=string::npos && line.find("WH")!=string::npos){
      line.replace( line.find("YYY") , 3 , string(Form("%d", mass)) );
      outT << line << endl;
    }
    else if(line.find("rate")!=string::npos){
      string rate = "rate               ";  
      string space = "     ";
      outT << rate ;
      outT << space << whTtrim->Integral()
          << space << ttbarTtrim->Integral()
          << space << wjetTtrim->Integral()
          << space << zjetTtrim->Integral()
          << space << stopTtrim->Integral()
          << space << dibosonTtrim->Integral()
          << space << qcdTtrim->Integral()
          << endl;
    }
    else if(line.find("CMS_eff_lep")!=string::npos){  
      if(isMuChannel) line.replace( line.find("lep") , 4 , string(Form("%s", "m")));   
      else line.replace( line.find("lep") , 4 , string(Form("%s", "e")));
      outT << line << endl;
    }  
    else if(line.find("CMS_eff_b")!=string::npos){
      float bTagUnc_wh = (whTtrim->Integral() > 0) ? getBTagUnc(whTtrim, whTtrim_bTagUp, whTtrim_bTagDown) : 1.00;
      line.replace( line.find("HHHH") , 4 , string(Form("%.3f", bTagUnc_wh)) );
      
      float bTagUnc_ttbar = (ttbarTtrim->Integral() > 0) ? getBTagUnc(ttbarTtrim, ttbarTtrim_bTagUp, ttbarTtrim_bTagDown) : 1.00; 
      line.replace( line.find("TTTT") , 4 , string(Form("%.3f", bTagUnc_ttbar)) ); 
      
      float bTagUnc_wjet = (wjetTtrim->Integral() > 0) ? getBTagUnc(wjetTtrim, wjetTtrim_bTagUp, wjetTtrim_bTagDown) : 1.00;
      line.replace( line.find("WWWW") , 4 , string(Form("%.3f", bTagUnc_wjet)) ); 
     
      float bTagUnc_zjet = (zjetTtrim->Integral() > 0) ? getBTagUnc(zjetTtrim, zjetTtrim_bTagUp, zjetTtrim_bTagDown) : 1.00;
      line.replace( line.find("DDDD") , 4 , string(Form("%.3f", bTagUnc_zjet)) ); 

      float bTagUnc_stop = (stopTtrim->Integral() > 0) ? getBTagUnc(stopTtrim, stopTtrim_bTagUp, stopTtrim_bTagDown) : 1.00; 
      line.replace( line.find("SSSS") , 4 , string(Form("%.3f", bTagUnc_stop)) ); 

      float bTagUnc_diboson = (dibosonTtrim->Integral() > 0) ? getBTagUnc(dibosonTtrim, dibosonTtrim_bTagUp, dibosonTtrim_bTagDown) : 1.00;
      line.replace( line.find("VVVV") , 4 , string(Form("%.3f", bTagUnc_diboson)) ); 
      outT << line << endl;
    }
    else if(line.find("CMS_eff_c")!=string::npos){
      float cTagUnc_wh = (whTtrim->Integral() > 0) ? getBTagUnc(whTtrim, whTtrim_cTagUp, whTtrim_cTagDown) : 1.00;
      line.replace( line.find("HHHH") , 4 , string(Form("%.3f", cTagUnc_wh)) );
      
      float cTagUnc_ttbar = (ttbarTtrim->Integral() > 0) ? getBTagUnc(ttbarTtrim, ttbarTtrim_cTagUp, ttbarTtrim_cTagDown) : 1.00; 
      line.replace( line.find("TTTT") , 4 , string(Form("%.3f", cTagUnc_ttbar)) ); 
      
      float cTagUnc_wjet = (wjetTtrim->Integral() > 0) ? getBTagUnc(wjetTtrim, wjetTtrim_cTagUp, wjetTtrim_cTagDown) : 1.00;
      line.replace( line.find("WWWW") , 4 , string(Form("%.3f", cTagUnc_wjet)) ); 
     
      float cTagUnc_zjet = (zjetTtrim->Integral() > 0) ? getBTagUnc(zjetTtrim, zjetTtrim_cTagUp, zjetTtrim_cTagDown) : 1.00;
      line.replace( line.find("DDDD") , 4 , string(Form("%.3f", cTagUnc_zjet)) ); 
      
      float cTagUnc_stop = (stopTtrim->Integral() > 0) ? getBTagUnc(stopTtrim, stopTtrim_cTagUp, stopTtrim_cTagDown) : 1.00; 
      line.replace( line.find("SSSS") , 4 , string(Form("%.3f", cTagUnc_stop)) ); 

      float cTagUnc_diboson = (dibosonTtrim->Integral() > 0) ? getBTagUnc(dibosonTtrim, dibosonTtrim_cTagUp, dibosonTtrim_cTagDown) : 1.00;
      line.replace( line.find("VVVV") , 4 , string(Form("%.3f", cTagUnc_diboson)) ); 
      outT << line << endl;
    }
    else if(line.find("CMS_pileup")!=string::npos){
      float PileupUnc_wh = (whTtrim->Integral() > 0) ? getBTagUnc(whTtrim, whTtrim_PileupUp, whTtrim_PileupDown) : 1.00;
      line.replace( line.find("HHHH") , 4 , string(Form("%.3f", PileupUnc_wh)) );
      
      float PileupUnc_ttbar = (ttbarTtrim->Integral() > 0) ? getBTagUnc(ttbarTtrim, ttbarTtrim_PileupUp, ttbarTtrim_PileupDown) : 1.00; 
      line.replace( line.find("TTTT") , 4 , string(Form("%.3f", PileupUnc_ttbar)) ); 
      
      float PileupUnc_wjet = (wjetTtrim->Integral() > 0) ? getBTagUnc(wjetTtrim, wjetTtrim_PileupUp, wjetTtrim_PileupDown) : 1.00;
      line.replace( line.find("WWWW") , 4 , string(Form("%.3f", PileupUnc_wjet)) ); 
     
      float PileupUnc_zjet = (zjetTtrim->Integral() > 0) ? getBTagUnc(zjetTtrim, zjetTtrim_PileupUp, zjetTtrim_PileupDown) : 1.00;
      line.replace( line.find("DDDD") , 4 , string(Form("%.3f", PileupUnc_zjet)) ); 
      
      float PileupUnc_stop = (stopTtrim->Integral() > 0) ? getBTagUnc(stopTtrim, stopTtrim_PileupUp, stopTtrim_PileupDown) : 1.00; 
      line.replace( line.find("SSSS") , 4 , string(Form("%.3f", PileupUnc_stop)) ); 

      float PileupUnc_diboson = (dibosonTtrim->Integral() > 0) ? getBTagUnc(dibosonTtrim, dibosonTtrim_PileupUp, dibosonTtrim_PileupDown) : 1.00;
      line.replace( line.find("VVVV") , 4 , string(Form("%.3f", PileupUnc_diboson)) ); 
      outT << line << endl;
    }
    else if(line.find("CMS_scale_j")!=string::npos){
      float JESUnc_wh = (whTtrim->Integral() > 0) ? getBTagUnc(whTtrim, whTtrim_JESUp, whTtrim_JESDown) : 1.00;
      line.replace( line.find("HHHH") , 4 , string(Form("%.3f", JESUnc_wh)) );
      
      float JESUnc_ttbar = (ttbarTtrim->Integral() > 0) ? getBTagUnc(ttbarTtrim, ttbarTtrim_JESUp, ttbarTtrim_JESDown) : 1.00; 
      line.replace( line.find("TTTT") , 4 , string(Form("%.3f", JESUnc_ttbar)) ); 
      
      float JESUnc_wjet = (wjetTtrim->Integral() > 0) ? getBTagUnc(wjetTtrim, wjetTtrim_JESUp, wjetTtrim_JESDown) : 1.00;
      line.replace( line.find("WWWW") , 4 , string(Form("%.3f", JESUnc_wjet)) ); 
     
      float JESUnc_zjet = (zjetTtrim->Integral() > 0) ? getBTagUnc(zjetTtrim, zjetTtrim_JESUp, zjetTtrim_JESDown) : 1.00;
      line.replace( line.find("DDDD") , 4 , string(Form("%.3f", JESUnc_zjet)) ); 
      
      float JESUnc_stop = (stopTtrim->Integral() > 0) ? getBTagUnc(stopTtrim, stopTtrim_JESUp, stopTtrim_JESDown) : 1.00; 
      line.replace( line.find("SSSS") , 4 , string(Form("%.3f", JESUnc_stop)) ); 

      float JESUnc_diboson = (dibosonTtrim->Integral() > 0) ? getBTagUnc(dibosonTtrim, dibosonTtrim_JESUp, dibosonTtrim_JESDown) : 1.00;
      line.replace( line.find("VVVV") , 4 , string(Form("%.3f", JESUnc_diboson)) ); 
      outT << line << endl;
    }
    else if(line.find("CMS_res_j")!=string::npos){
      float JERUnc_wh = (whTtrim->Integral() > 0) ? getBTagUnc(whTtrim, whTtrim_JERUp, whTtrim_JERDown) : 1.00;
      line.replace( line.find("HHHH") , 4 , string(Form("%.3f", JERUnc_wh)) );
      
      float JERUnc_ttbar = (ttbarTtrim->Integral() > 0) ? getBTagUnc(ttbarTtrim, ttbarTtrim_JERUp, ttbarTtrim_JERDown) : 1.00; 
      line.replace( line.find("TTTT") , 4 , string(Form("%.3f", JERUnc_ttbar)) ); 
      
      float JERUnc_wjet = (wjetTtrim->Integral() > 0) ? getBTagUnc(wjetTtrim, wjetTtrim_JERUp, wjetTtrim_JERDown) : 1.00;
      line.replace( line.find("WWWW") , 4 , string(Form("%.3f", JERUnc_wjet)) ); 
     
      float JERUnc_zjet = (zjetTtrim->Integral() > 0) ? getBTagUnc(zjetTtrim, zjetTtrim_JERUp, zjetTtrim_JERDown) : 1.00;
      line.replace( line.find("DDDD") , 4 , string(Form("%.3f", JERUnc_zjet)) ); 
      
      float JERUnc_stop = (stopTtrim->Integral() > 0) ? getBTagUnc(stopTtrim, stopTtrim_JERUp, stopTtrim_JERDown) : 1.00; 
      line.replace( line.find("SSSS") , 4 , string(Form("%.3f", JERUnc_stop)) ); 

      float JERUnc_diboson = (dibosonTtrim->Integral() > 0) ? getBTagUnc(dibosonTtrim, dibosonTtrim_JERUp, dibosonTtrim_JERDown) : 1.00;
      line.replace( line.find("VVVV") , 4 , string(Form("%.3f", JERUnc_diboson)) ); 
      outT << line << endl;
    }
    else if(line.find("CMS_hcs_stat_wh")!=string::npos){ 
      line.replace( line.find("XXXX") , 4 , string(Form("%.3f", getStatUnc(whTtrim,  0))));  
      outT << line << endl;
    } 
    else if(line.find("CMS_hcs_stat_tt")!=string::npos){  
  line.replace( line.find("XXXX") , 4 , string(Form("%.3f", getStatUnc(ttbarTtrim,  0))));   
      outT << line << endl;
    }  
    else if(line.find("CMS_hcs_stat_wjet")!=string::npos){  
      line.replace( line.find("XXXX") , 4 , string(Form("%.3f", getStatUnc(wjetTtrim,  0))));   
      outT << line << endl;
    }  
    else if(line.find("CMS_hcs_stat_zjet")!=string::npos){ 
      line.replace( line.find("XXXX") , 4 , string(Form("%.3f", getStatUnc(zjetTtrim,  0))));  
      outT << line << endl; 
    }
    else if(line.find("CMS_hcs_stat_stop")!=string::npos){ 
      line.replace( line.find("XXXX") , 4 , string(Form("%.3f", getStatUnc(stopTtrim,  0))));  
      outT << line << endl; 
    } 
    else if(line.find("CMS_hcs_stat_vv")!=string::npos){  
      line.replace( line.find("XXXX") , 4 , string(Form("%.3f", getStatUnc(dibosonTtrim,  0))));   
      outT << line << endl;  
    }
    else if(line.find("CMS_hcs_stat_qcd")!=string::npos){  
      line.replace( line.find("XXXX") , 4 , string(Form("%.3f", getStatUnc(qcdTtrim,  0))));   
      outT << line << endl;  
    }
    else if(line.find("CMS_norm_qcd")!=string::npos){  
      if(isMuChannel) line.replace( line.find("QQQQ") , 4 , string(Form("%.3f", 1.72)));   
      else line.replace( line.find("QQQQ") , 4 , string(Form("%.3f", 1.40)));   
      outT << line << endl;  
    }
    else if(line.find("CMS_topPtReweight")!=string::npos){
      float topPtUnc_wh = (whTtrim->Integral() > 0) ? getBTagUnc(whTtrim, whTtrim_topPtUp, whTtrim_topPtDown) : 1.00;
      line.replace( line.find("HHHH") , 4 , string(Form("%.3f", topPtUnc_wh)) );
      
      float topPtUnc_ttbar = (ttbarTtrim->Integral() > 0) ? getBTagUnc(ttbarTtrim, ttbarTtrim_topPtUp, ttbarTtrim_topPtDown) : 1.00; 
      line.replace( line.find("TTTT") , 4 , string(Form("%.3f", topPtUnc_ttbar)) ); 
      outT << line << endl;
    }
    else{ //default without changes
      outT << line << endl;
    }
  }
} 
foutT->cd();
ttbarTtrim->Write();
ttbarTtrim_scaleUp->Write();
ttbarTtrim_scaleDown->Write();
ttbarTtrim_mtop1735->Write();
ttbarTtrim_mtop1715->Write();
ttbarTtrim_matchingUp->Write();
ttbarTtrim_matchingDown->Write();
wjetTtrim->Write();
zjetTtrim->Write();
stopTtrim->Write();
dibosonTtrim->Write();
qcdTtrim->Write();
dataTtrim->Write();
whTtrim->Write();
outT.close();
inT.close();
foutT->Close();
}

void makeDataCardForEachMass(int mass, TString SigM, TString SigLab){
  /*
  vector<int>binLMT_1;
  binLMT_1.push_back(1);
  binLMT_1.push_back(30);
  makeVertBinDataCard(true, "mjj_kfit_25To42", binLMT_1, mass, SigM, SigLab);

  vector<int>binLMT_2;
  binLMT_2.push_back(29);
  makeVertBinDataCard(true, "mjj_kfit_42To57", binLMT_2, mass, SigM, SigLab);

  vector<int>binLMT_3;
  binLMT_3.push_back(29);
  makeVertBinDataCard(true, "mjj_kfit_57To74", binLMT_3, mass, SigM, SigLab);

  vector<int>binLMT_4;
  binLMT_4.push_back(27);
  binLMT_4.push_back(28);
  makeVertBinDataCard(true, "mjj_kfit_74To99", binLMT_4, mass, SigM, SigLab);

  vector<int>binLMT_5;
  binLMT_5.push_back(26);
  makeVertBinDataCard(true, "mjj_kfit_99To500", binLMT_5, mass, SigM, SigLab);

  vector<int>binLMT_6;
  binLMT_6.push_back(1);
  binLMT_6.push_back(30);
  makeVertBinDataCard(false, "mjj_kfit_25To42", binLMT_6, mass, SigM, SigLab);

  vector<int>binLMT_7;
  binLMT_7.push_back(29);
  binLMT_7.push_back(30);
  makeVertBinDataCard(false, "mjj_kfit_42To57", binLMT_7, mass, SigM, SigLab);

  vector<int>binLMT_8;
  binLMT_8.push_back(28);
  binLMT_8.push_back(29);
  makeVertBinDataCard(false, "mjj_kfit_57To74", binLMT_8, mass, SigM, SigLab);

  vector<int>binLMT_9;
  binLMT_9.push_back(27);
  binLMT_9.push_back(28);
  makeVertBinDataCard(false, "mjj_kfit_74To99", binLMT_9, mass, SigM, SigLab);
  */

  vector<int>binLMT_10;
  binLMT_10.push_back(26);
  makeVertBinDataCard(false, "mjj_kfit_99To500", binLMT_10, mass, SigM, SigLab);
  /*
  */
}
void makeVertBinHPlusDataCard_13TeV(int mass =80, TString SigM = "80", TString SigLab = "WH80"){
  makeDataCardForEachMass(mass, SigM, SigLab);
}

