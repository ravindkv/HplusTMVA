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
#include <stdlib.h>
#include <algorithm>
#include <iterator>

bool isMuChannel = true;
bool isEleChannel = false;
//INPUT FILES
TFile* fData = TFile::Open("all_Data.root");

TFile* fVV	= TFile::Open("all_VV.root");
TFile* fDY	= TFile::Open("all_DY.root");
TFile* fWJ	= TFile::Open("all_WJets.root");
TFile* fQCD	= TFile::Open("all_QCD_dd.root");
TFile* fST	= TFile::Open("all_ST.root");
TFile* fTT	= TFile::Open("all_TTJetsP.root");
TFile *fSig80 = TFile::Open("all_Hplus80.root");
TFile *fSig90 = TFile::Open("all_Hplus90.root");
TFile *fSig100 = TFile::Open("all_Hplus100.root");
TFile *fSig120 = TFile::Open("all_Hplus120.root");
TFile *fSig140 = TFile::Open("all_Hplus140.root");
TFile *fSig150 = TFile::Open("all_Hplus150.root");
TFile *fSig155 = TFile::Open("all_Hplus155.root");
TFile *fSig160 = TFile::Open("all_Hplus160.root");


TH1F*  getHisto(TFile *inRootFile, TString baseDir, TString isoDir, TString histDir, TString histName){
  TH1F* hist;
  TString inFile(inRootFile->GetName());
  TString fullPath = baseDir+isoDir+histDir+histName;
  string exception_msg ("The histogram path, "+inFile+"/"+fullPath+", does not exist"); 
  try{
    if(!(inRootFile->Get(fullPath)))
       throw  exception_msg.c_str();
  }catch (const char *e){
    cout<<"WARNING:"<<e<<endl;
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
  return hist;
}
TPaveText * paveText(double minX, double minY, double maxX, double maxY, int lineColor, int fillColor, int size, int style, int font ){
  TPaveText *pt = new TPaveText(minX, minY, maxX, maxY, "brNDC"); // good_v1
  pt->SetBorderSize(size);
  pt->SetFillColor(fillColor);
  pt->SetFillStyle(style);
  pt->SetLineColor(lineColor);
  pt->SetTextFont(font);
  return pt;
}

TH1F*  getAllBkgHist(TString baseDir, TString isoDir, TString histDir, TString histName){
  TH1F *ttbar   = getHisto(fTT,     baseDir, isoDir, histDir, histName);
  TH1F *wjet    = getHisto(fWJ,     baseDir, isoDir, histDir, histName);
  TH1F *zjet    = getHisto(fDY,     baseDir, isoDir, histDir, histName);
  TH1F *stop    = getHisto(fST,     baseDir, isoDir, histDir, histName);
  TH1F *diboson = getHisto(fVV,     baseDir, isoDir, histDir, histName);
  TH1F *qcd     = getHisto(fQCD,    baseDir, isoDir, histDir, histName);
  TH1F* h_Bkg   = (TH1F*)ttbar->Clone("Bkg MC");
  h_Bkg->Add(wjet);
  h_Bkg->Add(zjet);
  h_Bkg->Add(stop);
  h_Bkg->Add(diboson);
  h_Bkg->Add(qcd);
  return h_Bkg;
}

TH1F * getRatioHist(TH1F* hist1, TH1F* hist2){
  TH1F * hRatio = (TH1F*)hist1->Clone("hRatio");
  hRatio->Divide(hist2);
  return hRatio;
}

TH1F * getSigBkgRatioHist(TH1F* hSig, TH1F* hBkg, int color){
  TH1F * hRatio = getRatioHist(hSig, hBkg);
  hRatio->SetLineColor(color);
  hRatio->SetLineWidth(3);
  return hRatio;
}

void oneSigToBkgRatio(TFile *fSig, TString outName, TString mass, int xMin, int yMax){
  gStyle->SetOptStat(0);
  TH1F * hAllBkgInc = getAllBkgHist("base/", "Iso/", "KinFit/", "mjj_kfit");
  TH1F* hSigInc = getHisto(fSig, "base/", "Iso/", "KinFit/", "mjj_kfit");
  TH1F * hRatioInc = getSigBkgRatioHist(hSigInc, hAllBkgInc, 1);
  hRatioInc->SetTitle("");
  hRatioInc->GetYaxis()->SetRangeUser(0.005, yMax);
  hRatioInc->GetXaxis()->SetRangeUser(xMin, 170);
  hRatioInc->GetXaxis()->SetTitle("m_{jj} [GeV]"); 
  hRatioInc->GetYaxis()->SetTitleOffset(1.00);
  hRatioInc->GetXaxis()->SetTitleOffset(1.10);
  hRatioInc->GetYaxis()->SetTitle("Sig/Bkg"); 
  hRatioInc->GetYaxis()->CenterTitle();
  hRatioInc->GetYaxis()->SetTitleSize(0.07); 
  hRatioInc->GetXaxis()->SetTitleSize(0.06);
  hRatioInc->GetXaxis()->SetLabelSize(0.05); 
  hRatioInc->GetYaxis()->SetLabelSize(0.06); 

  TH1F * hAllBkgCTagExL= getAllBkgHist("base/", "Iso/", "KinFit/", "mjj_kfit_CTagExL");
  TH1F * hSigCTagExL   = getHisto(fSig, "base/", "Iso/", "KinFit/", "mjj_kfit_CTagExL");
  TH1F * hRatioCTagExL = getSigBkgRatioHist(hSigCTagExL, hAllBkgCTagExL, kOrange+1);

  TH1F * hAllBkgCTagExM= getAllBkgHist("base/", "Iso/", "KinFit/", "mjj_kfit_CTagExM");
  TH1F * hSigCTagExM   = getHisto(fSig, "base/", "Iso/", "KinFit/", "mjj_kfit_CTagExM");
  TH1F * hRatioCTagExM = getSigBkgRatioHist(hSigCTagExM, hAllBkgCTagExM, kGreen+1);

  TH1F * hAllBkgCTagExT= getAllBkgHist("base/", "Iso/", "KinFit/", "mjj_kfit_CTagExT");
  TH1F * hSigCTagExT   = getHisto(fSig, "base/", "Iso/", "KinFit/", "mjj_kfit_CTagExT");
  TH1F * hRatioCTagExT = getSigBkgRatioHist(hSigCTagExT, hAllBkgCTagExT, kViolet+1);
  TCanvas *can = new TCanvas();
  can->cd();
  gPad->SetLogy(true);
  gPad->SetBottomMargin(0.15); 
  gPad->SetLeftMargin(0.15);
  hRatioInc->Draw("HIST");
  hRatioCTagExL->Draw("HISTsame");
  hRatioCTagExM->Draw("HISTsame");
  hRatioCTagExT->Draw("HISTsame");
  TLegend* legCTag= new TLegend(0.20,0.70,0.40,0.95,NULL,"brNDC");
  legCTag->AddEntry(hRatioInc, "Inc","LP");
  legCTag->AddEntry(hRatioCTagExL, "CTagExL","LP");
  legCTag->AddEntry(hRatioCTagExM, "CTagExM","LP");
  legCTag->AddEntry(hRatioCTagExT, "CTagExT","LP");
  
  //channel
  TPaveText *ch = paveText(0.40,0.9154898,0.9210067,0.9762187, 0, 19, 1, 0, 132);
  ch->SetTextSize(0.07);
  if(isMuChannel)  ch->AddText(mass+",  #mu + jets");
  if(isEleChannel) ch->AddText(mass+",  e + jets");
  ch->Draw();
  legCTag->Draw();

  TString outFile("$PWD/CTag/");
  if(isMuChannel) outFile += outName+ "_mu_ratioSB.pdf";
  if(isEleChannel) outFile += outName+ "_ele_ratioSB.pdf";
  can->SaveAs(outFile);
} 

void sigToBkgRatio_13TeV(){
  oneSigToBkgRatio(fSig80, "WH80", "m_{H^{+}} = 80 GeV", 20,  1);
  oneSigToBkgRatio(fSig90, "WH90", "m_{H^{+}} = 90 GeV", 20,  1);
  oneSigToBkgRatio(fSig100,"WH100", "m_{H^{+}} = 100 GeV",20,  1);
  oneSigToBkgRatio(fSig120,"WH120", "m_{H^{+}} = 120 GeV",20,  1);
  oneSigToBkgRatio(fSig140,"WH140", "m_{H^{+}} = 140 GeV",20,  2);
  oneSigToBkgRatio(fSig150,"WH150", "m_{H^{+}} = 150 GeV",20,  6);
  oneSigToBkgRatio(fSig155,"WH155", "m_{H^{+}} = 155 GeV",20,  10);
  oneSigToBkgRatio(fSig160,"WH160", "m_{H^{+}} = 160 GeV",20,  25);
}



