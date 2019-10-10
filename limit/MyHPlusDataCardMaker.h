#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <fstream>
#include <iomanip>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <algorithm>

using namespace std;

class MyHPlusDataCardMaker{
  public:

  TH1F* getHisto(TFile *inRootFile, TString histPath, TString histName, TFile* fTT, double sf=1.0);
  TH1F* readWriteHisto(TFile *inFile, TString histPath, TString inHistName, double sf, TFile *outFile, TFile *fTT, TString outHistName,  bool isWrite = false, double min_thres = 0, bool isNeffThreshold = false);
  double getBTagUnc(TH1F *hCentral, TH1F* hUp, TH1F* hDown);
  double getStatUnc(TH1F* hCentral, double sError = 0.0);
  double getUncExL(TH1F* yLyMyT, TH1F* yLyMnT, TH1F* yLnMyT, TH1F* yLnMnT);
  double getUncExM(TH1F* yMyT, TH1F* yMnT);
  double getQcdSF(TString baseIsoDir, TFile* fData, TFile* fTT, TFile* fST, TFile* fWJ, TFile* fDY, TFile* fVV, TString histDir, TString histName);
  double getQcdDD(TString baseDir, TFile* fData, TFile* fTT, TFile* fST, TFile* fWJ, TFile* fDY, TFile* fVV, TString histDir, TString histName, double qcd_sf=1.0);
  double getSysUncQcd(TFile* fData, TFile* fTT, TFile* fST, TFile* fWJ, TFile* fDY, TFile* fVV, TString histDir, TString histName, bool isUncSF);
  TH1F* trimHisto(TH1F* hist, TString histName, int binWidth, int xMin, int xMax);

  private:
  double dont_use;
};

//----------------------------------------//
//Variuos functions
//----------------------------------------//
TH1F*  MyHPlusDataCardMaker:: getHisto(TFile *inRootFile, TString histPath, TString histName, TFile *fTT, double sf=1.0){
  TH1F* hist;
  TString fullPath = histPath+histName;
  string exception_msg (inRootFile->GetName()+TString("/")+fullPath+", does not exist");
  try{
    if(!(inRootFile->Get(fullPath)))
       throw  exception_msg.c_str();
  }catch (const char *e){
    ///cout<<"WARNING:"<<e<<endl;
  }
  try{
    if(!(fTT->Get(fullPath)))
       throw  exception_msg.c_str();
  }catch (const char *e){
    cout<<"\033[01;31mERROR: \033[0m"<<e<< endl;
    exit(0);
  }
  if(!(inRootFile->Get(fullPath))){
    hist = (TH1F*)(fTT->Get(fullPath))->Clone(histName);
    hist->Reset();
  }else hist = (TH1F*)(inRootFile->Get(fullPath))->Clone(histName);
  hist->Scale(sf);
  return hist;
}

//Read histos from input file. Write to another file.
TH1F* MyHPlusDataCardMaker::readWriteHisto(TFile *inFile, TString histPath, TString inHistName, double sf, TFile *outFile, TFile *fTT, TString outHistName,  bool isWrite = false, double min_thres = 0, bool isNeffThreshold = false){
  TH1F* hist = (TH1F*) getHisto(inFile, histPath, inHistName, fTT)->Clone(outHistName);
  hist->Scale(sf);
  TH1F* trimmedHist = trimHisto(hist, outHistName, 5, 20, 170);
  if(isWrite){
    outFile->cd();
    ///hist->Write(outHistName);
    trimmedHist->Write(outHistName);
  }
  ///return hist;
  return trimmedHist;
}

//get normalised uncertainity
double MyHPlusDataCardMaker::getBTagUnc(TH1F *hCentral, TH1F* hUp, TH1F* hDown){
  return 1 + max(fabs(hUp->Integral() - hCentral->Integral()), fabs(hCentral->Integral() - hDown->Integral()))/hCentral->Integral();
}

//get statistical uncertainity
double MyHPlusDataCardMaker::getStatUnc(TH1F* hCentral, double sError = 0.0){
  double  norm = hCentral->IntegralAndError(1, hCentral->GetNbinsX(), sError);
  double statUnc = (norm > 0) ? 1 + (fabs(sError)/norm) : 1.00;
  return statUnc;
}

TH1F* MyHPlusDataCardMaker::trimHisto(TH1F* hist, TString histName, int binWidth, int xMin, int xMax){
    double nBin = (xMax-xMin)/binWidth;
    TH1F* newHisto = new TH1F(histName, histName, nBin, xMin, xMax);
    double initX = xMin/binWidth;
    double lastX = xMax/binWidth;
    for(int i = initX; i<lastX; i++){
      double binVal = hist->GetBinContent(i);
      double binErr = hist->GetBinError(i);
      int i_new = i- initX+1;
      newHisto->SetBinContent(i_new, binVal);
      newHisto->SetBinError(i_new, binErr);
    }
    return newHisto;
}

double MyHPlusDataCardMaker::getUncExL(TH1F* yLyMyT, TH1F* yLyMnT, TH1F* yLnMyT, TH1F* yLnMnT){
  double m_yLyMyT = yLyMyT->GetMean();
  double m_yLyMnT = yLyMnT->GetMean();
  double m_yLnMyT = yLnMyT->GetMean();
  double m_yLnMnT = yLnMnT->GetMean();
  vector<double> vecExL;
  vecExL.push_back(m_yLyMyT);
  vecExL.push_back(m_yLyMnT);
  vecExL.push_back(m_yLnMyT);
  vecExL.push_back(m_yLnMnT);
  auto it_min = min_element(std::begin(vecExL), std::end(vecExL));
  auto it_max = max_element(std::begin(vecExL), std::end(vecExL));
  double min = *it_min;
  double max = *it_max;
  double unc = max/min;
  //--------------------
  //double tmp_budh = unc -1;
  //unc = 1+ 2*tmp_budh;
  //--------------------
  return (min>0 && max>0)?unc:1.0;
}

double MyHPlusDataCardMaker::getUncExM(TH1F* yMyT, TH1F* yMnT){
  double m_yMyT = yMyT->GetMean();
  double m_yMnT = yMnT->GetMean();
  vector<double> vecExM;
  vecExM.push_back(m_yMyT);
  vecExM.push_back(m_yMnT);
  auto it_min = min_element(std::begin(vecExM), std::end(vecExM));
  auto it_max = max_element(std::begin(vecExM), std::end(vecExM));
  double min = *it_min;
  double max = *it_max;
  double unc = max/min;
  //--------------------
  //double tmp_budh = unc -1;
  //unc = 1+ 2*tmp_budh;
  //--------------------
  return (min>0 && max>0)?unc:1.0;
}

// qcd SF for data-driven QCD
double MyHPlusDataCardMaker::getQcdSF(TString baseIsoDir, TFile* fData, TFile* fTT, TFile* fST, TFile* fWJ, TFile* fDY, TFile* fVV, TString histDir, TString histName){
  //RegionC = LowMET, Iso
  TH1F* hVV_RegC = getHisto(fVV,   baseIsoDir+"/NonIso/"+histDir, histName, fTT);
  TH1F* hDY_RegC = getHisto(fDY,   baseIsoDir+"/NonIso/"+histDir, histName, fTT);
  TH1F* hWJ_RegC = getHisto(fWJ,   baseIsoDir+"/NonIso/"+histDir, histName, fTT);
  TH1F* hST_RegC = getHisto(fST,   baseIsoDir+"/NonIso/"+histDir, histName, fTT);
  TH1F* hTT_RegC = getHisto(fTT,   baseIsoDir+"/NonIso/"+histDir, histName, fTT);
  TH1F* hMC_RegC = (TH1F*)hVV_RegC->Clone("hAllMC_RegC");
  hMC_RegC->Add(hDY_RegC);
  hMC_RegC->Add(hWJ_RegC);
  hMC_RegC->Add(hST_RegC);
  hMC_RegC->Add(hTT_RegC);
  TH1F* hData_RegC= getHisto(fData, baseIsoDir+"/NonIso/"+histDir, histName, fTT);
  //RegionD = LowMET, NonIso
  TH1F* hVV_RegD = getHisto(fVV,   baseIsoDir+"/Iso/"+histDir, histName, fTT);
  TH1F* hDY_RegD = getHisto(fDY,   baseIsoDir+"/Iso/"+histDir, histName, fTT);
  TH1F* hWJ_RegD = getHisto(fWJ,   baseIsoDir+"/Iso/"+histDir, histName, fTT);
  TH1F* hST_RegD = getHisto(fST,   baseIsoDir+"/Iso/"+histDir, histName, fTT);
  TH1F* hTT_RegD = getHisto(fTT,   baseIsoDir+"/Iso/"+histDir, histName, fTT);
  TH1F* hMC_RegD = (TH1F*)hVV_RegD->Clone("hAllMC_RegD");
  hMC_RegD->Add(hDY_RegD);
  hMC_RegD->Add(hWJ_RegD);
  hMC_RegD->Add(hST_RegD);
  hMC_RegD->Add(hTT_RegD);
  TH1F* hData_RegD=  getHisto(fData, baseIsoDir+"/Iso/"+histDir, histName, fTT);
  TH1F* hDiffC = (TH1F*)hData_RegC->Clone("hDiffC");
  hDiffC->Add(hMC_RegC, -1);
  //If binContent < 0, set it to 0
  for(int ibin=1; ibin<hDiffC->GetNbinsX(); ibin++){
    double binCont = hDiffC->GetBinContent(ibin);
    if(binCont<0){
      hDiffC->SetBinContent(ibin, 0);
      //hDiffC->SetBinError(ibin, 0);
    }
  }
  TH1F* hDiffD = (TH1F*)hData_RegD->Clone("hDiffD");
  hDiffD->Add(hMC_RegD, -1);
  for(int ibin=1; ibin<hDiffD->GetNbinsX(); ibin++){
    double binCont = hDiffD->GetBinContent(ibin);
    if(binCont<0){
      hDiffD->SetBinContent(ibin, 0);
      //hDiffD->SetBinError(ibin, 0);
    }
  }
  double intDiffC   = hDiffC->Integral();
  double intDiffD   = hDiffD->Integral();
  double ratioDiffDC = intDiffD/intDiffC;
  return ratioDiffDC;
}

double MyHPlusDataCardMaker::getQcdDD(TString baseDir, TFile* fData, TFile* fTT, TFile* fST, TFile* fWJ, TFile* fDY, TFile* fVV, TString histDir, TString histName, double qcd_sf=1.0){
  TH1F* hVV = getHisto(fVV,   baseDir+"/NonIso/"+histDir, histName, fTT);
  TH1F* hDY = getHisto(fDY,   baseDir+"/NonIso/"+histDir, histName, fTT);
  TH1F* hWJ = getHisto(fWJ,   baseDir+"/NonIso/"+histDir, histName, fTT);
  TH1F* hST = getHisto(fST,   baseDir+"/NonIso/"+histDir, histName, fTT);
  TH1F* hTT = getHisto(fTT,   baseDir+"/NonIso/"+histDir, histName, fTT);
  TH1F* hData= getHisto(fData, baseDir+"/NonIso/"+histDir, histName, fTT);
  TH1F* hOtherMC = (TH1F*)hVV->Clone("hOtherMC");
  hOtherMC->Add(hDY);
  hOtherMC->Add(hST);
  hOtherMC->Add(hWJ);
  hOtherMC->Add(hTT);
  TH1F* hQCD = (TH1F*)hData->Clone(histName);
  hQCD->Add(hOtherMC, -1);
  //If binContent < 0, set it to 0
  for(int ibin=1; ibin<hQCD->GetNbinsX(); ibin++){
    double binCont = hQCD->GetBinContent(ibin);
    if(binCont<0){
      hQCD->SetBinContent(ibin, 0);
      //hQCD->SetBinError(ibin, 0);
    }
  }
  hQCD->Scale(qcd_sf);
  return hQCD->Integral();
}

double MyHPlusDataCardMaker::getSysUncQcd(TFile* fData, TFile* fTT, TFile* fST, TFile* fWJ, TFile* fDY, TFile* fVV, TString histDir, TString histName, bool isUncSF){
  double sf_baseIsoDir = getQcdSF("baseLowMET", fData, fTT, fST, fWJ, fDY, fVV, histDir, histName);
  double qcd_baseIsoDir = getQcdDD("base", fData, fTT, fST, fWJ, fDY, fVV, histDir, histName, sf_baseIsoDir);
  double sf_baseShiftedIsoDir = getQcdSF("baseIso20LowMET", fData, fTT, fST, fWJ, fDY, fVV, histDir, histName);
  double qcd_baseShiftedIsoDir = getQcdDD("baseIso20HighMET", fData, fTT, fST, fWJ, fDY, fVV, histDir, histName, sf_baseShiftedIsoDir);
  double sf_unc = abs(sf_baseIsoDir - sf_baseShiftedIsoDir)/sf_baseIsoDir;
  double qcd_unc = abs(qcd_baseIsoDir - qcd_baseShiftedIsoDir)/qcd_baseIsoDir;
  cout<<"-------------------------------------"<<endl;
  cout<<"sf_baseIsoDir 	      = "<<sf_baseIsoDir<<endl;
  cout<<"sf_baseShiftedIsoDir = "<<sf_baseShiftedIsoDir<<endl;
  cout<<"sf_unc               = "<<sf_unc<<endl;
  cout<<"qcd_baseIsoDir 	   = "<<qcd_baseIsoDir<<endl;
  cout<<"qcd_baseShiftedIsoDir = "<<qcd_baseShiftedIsoDir<<endl;
  cout<<"qcd_unc               = "<<qcd_unc<<endl;
  cout<<"-------------------------------------"<<endl;
  double unc = 0.0;
  if(isUncSF) unc = sf_unc;
  else unc = qcd_unc;
  return 1+unc;
}
