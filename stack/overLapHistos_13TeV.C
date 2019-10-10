#include <cstdlib>
#include <iostream> 
#include <fstream>
#include <map>
#include <string>
#include <cstring>

#include "TMath.h"
#include "TFile.h"
#include "TString.h"
#include "TObjString.h"
#include "TSystem.h"
#include "TROOT.h"
#include "TPluginManager.h"
#include "TH1F.h"
#include "TCanvas.h"
#include "TPad.h"
#include "TLegend.h"
#include "TGraphAsymmErrors.h"
#include "TGraphPainter.h"
#include "TMultiGraph.h"
#include "TTree.h"

using namespace std;

bool isMuChannel = true;
bool isEleChannel = false;
bool isBTag = false;
//-------------------------------------------//
///INPUT FILES
//-------------------------------------------//
//data
/*
TFile* fData    = TFile::Open("all_muData.root");
//bkg
TFile* fVV      = TFile::Open("all_VV.root");
TFile* fDY      = TFile::Open("all_DY.root");
TFile* fWJ      = TFile::Open("all_WJets.root");
TFile* fQCD     = TFile::Open("all_QCD.root");
TFile* fST      = TFile::Open("all_ST.root");
*/
TFile* fTT      = TFile::Open("all_TTJetsP.root");

//signal
TFile *fWH80      = TFile::Open("all_Hplus80.root");
TFile *fWH90      = TFile::Open("all_Hplus90.root");
TFile *fWH100     = TFile::Open("all_Hplus100.root");
TFile *fWH120     = TFile::Open("all_Hplus120.root");
TFile *fWH140     = TFile::Open("all_Hplus140.root");
TFile *fWH150     = TFile::Open("all_Hplus150.root");
TFile *fWH155     = TFile::Open("all_Hplus155.root");
TFile *fWH160     = TFile::Open("all_Hplus160.root");
//data driven qcd
///TFile* fQCD_dd = TFile::Open("all_QCD_dd.root"); 

//histogram name and range
TString histName = "pt_bjet" ;
Float_t xMin_ = 0.0 ;
Float_t xMax_ = 400.0 ;
//bool isSaveHisto = false;
bool isSaveHisto = true;

//-------------------------------------------//
//function to get histogram from root file
//-------------------------------------------//
TH1F* getHisto(TFile *file, TString histName, int histColor, Float_t xMin_ = 0.0, Float_t xMax_ = 500){

  if(file->IsZombie() || file->IsZombie()){
    cout << "Cannot open file "<< endl;
  }
  TH1F* h;
  h = (TH1F*)file->Get("base/Iso/KinFit/"+histName);
  if(isBTag) h = (TH1F*)file->Get("base/Iso/BTag/"+histName);
  //h->SetMarkerColor(kRed);
  cout<<h->GetNbinsX()<<endl;
  //h->Rebin();
  cout<<h->GetNbinsX()<<endl;
  h->SetMarkerStyle(1);
  h->SetMarkerSize(1.5);
  h->SetLineColor(histColor);
  h->SetLineWidth(3);
  cout<<histName<<": Int = "<<h->Integral()<<", Mean = "<<h->GetMean()<<", RMS = "<<h->GetRMS()<<endl;
  h->GetXaxis()->SetRangeUser(xMin_, xMax_);
  //h->GetYaxis()->SetRangeUser(0, 40000);
  //h->GetXaxis()->SetTitle(histName);
  h->GetXaxis()->SetTitle("m_{jj} (GeV)");
  h->GetYaxis()->SetTitle("Events / 5 GeV");
  h->GetYaxis()->SetTitleOffset(1.20);
  h->GetXaxis()->SetTitleOffset(1.20);
  h->GetYaxis()->SetTitleSize(0.05); 
  h->GetXaxis()->SetTitleSize(0.05);
  h->GetXaxis()->SetLabelSize(0.05); 
  h->GetXaxis()->LabelsOption("u"); // extra
  h->GetYaxis()->SetLabelSize(0.05);
  h->GetXaxis()->SetNdivisions(5);
  h->GetYaxis()->SetNdivisions(5);
  h->SetTitle("");
  return h;
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

TH1F* getRatio(TH1F* h1, TH1F* h2, TString histName, int my_color){
  TH1F *hRatio = (TH1F*)h2->Clone("hRatio");
  hRatio->Divide(h1); 
  hRatio->SetMarkerStyle(20); 
  hRatio->SetMarkerSize(0.8);
  hRatio->SetMarkerColor(my_color); 
  hRatio->SetLineColor(my_color); 
  hRatio->GetYaxis()->SetRangeUser(0, 2);
  hRatio->GetXaxis()->SetTitle("Pt_{bjet}^{Had} [GeV]"); 
  //hRatio->GetXaxis()->SetTitle(histName); 
  hRatio->GetYaxis()->SetTitleOffset(1.30);
  hRatio->GetXaxis()->SetTitleOffset(1.20);
  hRatio->GetYaxis()->SetTitle("#frac{Signal}{t#bar{t} + jets}"); 
  hRatio->GetXaxis()->SetRangeUser(0, 500);
  //hRatio->Scale(1/hRatio->Integral());
  //cout<<hRatio->Integral()<<endl;
  //hRatio->GetYaxis()->CenterTitle();
  hRatio->GetYaxis()->SetTitleSize(0.06); 
  hRatio->GetXaxis()->SetTitleSize(0.06);
  hRatio->GetXaxis()->SetLabelSize(0.06); 
  hRatio->GetXaxis()->LabelsOption("u"); // extra
  hRatio->GetYaxis()->SetLabelSize(0.06);
  return hRatio;
}

//-------------------------------------------//
//overlap two histograms
//-------------------------------------------//
void overLap2Histos(TFile *f1, TFile* f2, TString histName1, TString histName2, TString histLeg1, TString histLeg2){
  gStyle->SetOptStat(0);
  TCanvas *c1 = new TCanvas();
  //TCanvas *c1 = new TCanvas("c1","",5,30,650,600);
  c1->Divide(1,2);
  c1->SetGrid(0,0);
  c1->SetFillStyle(4000);
  c1->SetFillColor(10);
  c1->SetTicky();
  c1->SetObjectStat(0);
  TLegend* leg = new TLegend(0.59,0.60,0.46,0.85,NULL,"brNDC");
  leg->SetBorderSize(0);
  leg->SetTextSize(0.05);
  leg->SetFillColor(0);
  
  //overlay
  c1->cd(1);
  TH1F* h1 = getHisto(f1, histName1, kBlack, xMin_, xMax_);
  TH1F* h2 = getHisto(f2, histName2, kBlue, xMin_, xMax_);
  h1->Draw("HIST");
  h2->Draw("HISTSAME");
  leg->AddEntry(h1, histLeg1,"PL");
  leg->AddEntry(h2, histLeg2,"PL");
  leg->Draw();
  //ratio
  c1->cd(2);
  //leg->SetHeader(Form("#splitline{CMS Preliminary #sqrt{s}=13 TeV}{35.5 fb^{-1}}"));
  TH1F* hRatio = getRatio(h1, h2, histName, 1);
  hRatio->Draw("E"); // use "P" or "AP"
  //base line at 1
  TF1 *baseLine = new TF1("baseLine","1", -100, 2000); 
  baseLine->SetLineColor(kRed);
  baseLine->Draw("SAME");
  
  if(isSaveHisto){
    TString outFile("$PWD/");
    outFile += histName;
    outFile += "_mu"+histLeg1+".pdf";
    c1->SaveAs(outFile);
    //c1->Close();
  }
}
void stackRatios(){
  gStyle->SetOptStat(0);
  TCanvas *c1 = new TCanvas();
  c1->Divide(3, 3);
  
  TF1 *baseLine = new TF1("baseLine","0.035", -100, 2000); 
  baseLine->SetLineColor(kRed);

  TLegend* leg = new TLegend(0.59,0.60,0.46,0.85,NULL,"brNDC");
  leg->SetBorderSize(0);
  leg->SetTextSize(0.035);
  leg->SetFillColor(0);
  c1->cd(1);
  TH1F* hRL_TT = getHisto(fTT, "pt_bjetH", kBlack, xMin_, xMax_);  
  TH1F* hRL_TTWH80 = getRatio(hRL_TT, getHisto(fWH80, "pt_bjetH", kBlue, xMin_, xMax_), "pt_bjetH", 1);
  hRL_TTWH80->SetTitle("Hadronic bjet pt ratio : WH80/TT");
  hRL_TTWH80->SetLineColor(1);
  hRL_TTWH80->Draw("E");
  baseLine->Draw("SAME");
  
  c1->cd(2);
  TH1F* hRL_TTWH90 = getRatio(hRL_TT, getHisto(fWH90, "pt_bjetH", kBlue, xMin_, xMax_), "pt_bjetH", 2);
  hRL_TTWH90->SetTitle("Hadronic bjet pt ratio : WH90/TT");
  hRL_TTWH90->SetLineColor(2);
  hRL_TTWH90->Draw("E");
  baseLine->Draw("SAME");
  
  c1->cd(3);
  TH1F* hRL_TTWH100 = getRatio(hRL_TT, getHisto(fWH100, "pt_bjetH", kBlue, xMin_, xMax_), "pt_bjetH", 3);
  hRL_TTWH100->SetTitle("Hadronic bjet pt ratio : WH100/TT");
  hRL_TTWH100->SetLineColor(3);
  hRL_TTWH100->Draw("E");
  baseLine->Draw("SAME");
 
  c1->cd(4);
  TH1F* hRL_TTWH120 = getRatio(hRL_TT, getHisto(fWH120, "pt_bjetH", kBlue, xMin_, xMax_), "pt_bjetH", 4);
  hRL_TTWH120->SetTitle("Hadronic bjet pt ratio : WH120/TT");
  hRL_TTWH120->SetLineColor(4);
  hRL_TTWH120->Draw("E");
  baseLine->Draw("SAME");

  c1->cd(5);
  TH1F* hRL_TTWH140 = getRatio(hRL_TT, getHisto(fWH140, "pt_bjetH", kBlue, xMin_, xMax_), "pt_bjetH", 5);
  hRL_TTWH140->SetTitle("Hadronic bjet pt ratio : WH140/TT");
  hRL_TTWH140->SetLineColor(55);
  hRL_TTWH140->Draw("E");
  baseLine->Draw("SAME");
  
  c1->cd(6);
  TH1F* hRL_TTWH150 = getRatio(hRL_TT, getHisto(fWH150, "pt_bjetH", kBlue, xMin_, xMax_), "pt_bjetH", 6);
  hRL_TTWH150->SetTitle("Hadronic bjet pt ratio : WH150/TT");
  hRL_TTWH150->SetLineColor(6);
  hRL_TTWH150->Draw("E");
  baseLine->Draw("SAME");

  c1->cd(7);
  TH1F* hRL_TTWH155 = getRatio(hRL_TT, getHisto(fWH155, "pt_bjetH", kBlue, xMin_, xMax_), "pt_bjetH", 7);
  hRL_TTWH155->SetTitle("Hadronic bjet pt ratio : WH155/TT");
  hRL_TTWH155->SetLineColor(7);
  hRL_TTWH155->Draw("E");
  baseLine->Draw("SAME");

  c1->cd(8);
  TH1F* hRL_TTWH160 = getRatio(hRL_TT, getHisto(fWH160, "pt_bjetH", kBlue, xMin_, xMax_), "pt_bjetH",8);
  hRL_TTWH160->SetTitle("Hadronic bjet pt ratio : WH160/TT");
  hRL_TTWH160->SetLineColor(11);
  hRL_TTWH160->Draw("E");
  baseLine->Draw("SAME");
  
  c1->cd(9);
  hRL_TTWH80->Draw("E");
  hRL_TTWH90->Draw("SAME");
  hRL_TTWH100->Draw("SAME");
  hRL_TTWH120->Draw("SAME");
  hRL_TTWH140->Draw("SAME");
  hRL_TTWH150->Draw("SAME");
  hRL_TTWH155->Draw("SAME");
  hRL_TTWH160->Draw("SAME");
  baseLine->Draw("SAME");
  leg->AddEntry(hRL_TTWH80,  "hRatioHadBJet: WH80/TT","PL");
  leg->AddEntry(hRL_TTWH90,  "hRatioHadBJet: WH90/TT","PL");
  leg->AddEntry(hRL_TTWH100, "hRatioHadBJet: WH100/TT","PL");
  leg->AddEntry(hRL_TTWH120, "hRatioHadBJet: WH120/TT","PL");
  leg->AddEntry(hRL_TTWH140, "hRatioHadBJet: WH140/TT","PL");
  leg->AddEntry(hRL_TTWH150, "hRatioHadBJet: WH150/TT","PL");
  leg->AddEntry(hRL_TTWH155, "hRatioHadBJet: WH155/TT","PL");
  leg->AddEntry(hRL_TTWH160, "hRatioHadBJet: WH160/TT","PL");
  leg->Draw();

}

void overLapRatios(){
  gStyle->SetOptStat(0);
  gStyle->SetFrameLineWidth(3);
  //pave text CMS box
  TPaveText *pt = new TPaveText(0.15,0.9354,0.95,0.9362, "brNDC"); // good_v1
  pt->SetBorderSize(1);
  pt->SetFillColor(19);
  pt->SetFillStyle(0);
  pt->SetTextSize(0.08);
  pt->SetLineColor(0);
  pt->SetTextFont(132);
  TText *text = pt->AddText("#sqrt{s}=13 TeV, 35.9 fb^{-1} ");
  text->SetTextAlign(11);

  //pave text channel box
  TPaveText *ch = new TPaveText(0.92,0.9354,0.6510067,0.95,"brNDC");
  ch->SetFillColor(19);
  ch->SetFillStyle(0);
  ch->SetLineColor(0);
  ch->SetTextSize(0.08);
  ch->SetBorderSize(1);
  if(isMuChannel) ch->AddText("#mu + jets");
  if(isEleChannel) ch->AddText("e + jets");

  TCanvas *c1 = new TCanvas();
  TLegend* leg = new TLegend(0.19,0.65,0.62,0.87,NULL,"brNDC");
  leg->SetNColumns(2);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.035);
  leg->SetFillColor(0);
  gPad->SetLeftMargin(0.18);
  gPad->SetBottomMargin(0.16); 
  c1->cd();
  TString histName = "pt_bjetH";
  TH1F* hRL_TT = getHisto(fTT, histName, kBlack, xMin_, xMax_);  
  TH1F* hRL_TTWH80 = getRatio(hRL_TT, getHisto(fWH80, histName, kBlue, xMin_, xMax_), histName, 1);
  hRL_TTWH80->SetLineColor(1);
  hRL_TTWH80->Draw("P");

  TH1F* hRL_TTWH90 = getRatio(hRL_TT, getHisto(fWH90, histName, kBlue, xMin_, xMax_), histName, 2);
  hRL_TTWH90->SetLineColor(2);
  hRL_TTWH90->Draw("SAME");
  
  TH1F* hRL_TTWH100 = getRatio(hRL_TT, getHisto(fWH100, histName, kBlue, xMin_, xMax_), histName, 3);
  hRL_TTWH100->SetLineColor(3);
  hRL_TTWH100->Draw("SAME");
 
  TH1F* hRL_TTWH120 = getRatio(hRL_TT, getHisto(fWH120, histName, kBlue, xMin_, xMax_), histName, 4);
  hRL_TTWH120->SetLineColor(4);
  hRL_TTWH120->Draw("SAME");

  TH1F* hRL_TTWH140 = getRatio(hRL_TT, getHisto(fWH140, histName, kBlue, xMin_, xMax_), histName, 52);
  hRL_TTWH140->SetLineColor(52);
  hRL_TTWH140->Draw("SAME");
  
  TH1F* hRL_TTWH150 = getRatio(hRL_TT, getHisto(fWH150, histName, kBlue, xMin_, xMax_), histName, 6);
  hRL_TTWH150->SetLineColor(6);
  hRL_TTWH150->Draw("SAME");

  TH1F* hRL_TTWH155 = getRatio(hRL_TT, getHisto(fWH155, histName, kBlue, xMin_, xMax_), histName,7);
  hRL_TTWH155->SetLineColor(7);
  hRL_TTWH155->Draw("SAME");

  TH1F* hRL_TTWH160 = getRatio(hRL_TT, getHisto(fWH160, histName, kBlue, xMin_, xMax_), histName, 11);
  hRL_TTWH160->SetLineColor(11);
  hRL_TTWH160->Draw("SAME");

  leg->AddEntry(hRL_TTWH80,   "WH80/(t#bar{t} + jets)","PL");
  leg->AddEntry(hRL_TTWH90,   "WH90/(t#bar{t} + jets)","PL");
  leg->AddEntry(hRL_TTWH100, "WH100/(t#bar{t} + jets)","PL");
  leg->AddEntry(hRL_TTWH120, "WH120/(t#bar{t} + jets)","PL");
  leg->AddEntry(hRL_TTWH140, "WH140/(t#bar{t} + jets)","PL");
  leg->AddEntry(hRL_TTWH150, "WH150/(t#bar{t} + jets)","PL");
  leg->AddEntry(hRL_TTWH155, "WH155/(t#bar{t} + jets)","PL");
  leg->AddEntry(hRL_TTWH160, "WH160/(t#bar{t} + jets)","PL");
  leg->Draw();
  //base line at 1
  TF1 *baseLine = new TF1("baseLine","1", -100, 2000); 
  baseLine->SetLineColor(kRed);
  baseLine->Draw("SAME");
  pt->Draw();
  ch->Draw();  
  if(isSaveHisto){
    TString outFile("$PWD/");
    if(isMuChannel) outFile += histName+"_ratio_mu.pdf";
    if(isEleChannel) outFile += histName+"_ratio_ele.pdf";
    c1->SaveAs(outFile);
    ///c1->Close();
  }
}

void overLapHistos(){
  overLap2Histos(fTT,  fTT,  "pt_bjet", "pt_bjetL", "TT:Had bjet",  "TT:Lep bjet");
  overLap2Histos(fWH80,  fWH80,  "pt_bjet", "pt_bjetL", "WH80:Had bjet",  "WH80:Lep bjet");
  overLap2Histos(fWH90,  fWH90,  "pt_bjet", "pt_bjetL", "WH90:Had bjet",  "WH90:Lep bjet");
  overLap2Histos(fWH100, fWH100, "pt_bjet", "pt_bjetL", "WH100:Had bjet", "WH100:Lep bjet");
  overLap2Histos(fWH120, fWH120, "pt_bjet", "pt_bjetL", "WH120:Had bjet", "WH120:Lep bjet");
  overLap2Histos(fWH140, fWH140, "pt_bjet", "pt_bjetL", "WH140:Had bjet", "WH140:Lep bjet");
  overLap2Histos(fWH150, fWH150, "pt_bjet", "pt_bjetL", "WH150:Had bjet", "WH150:Lep bjet");
  overLap2Histos(fWH155, fWH155, "pt_bjet", "pt_bjetL", "WH155:Had bjet", "WH155:Lep bjet");
  overLap2Histos(fWH160, fWH160, "pt_bjet", "pt_bjetL", "WH160:Had bjet", "WH160:Lep bjet");
}

void overLapHistos_13TeV(){

  TString dirName = "KinFit";
  TString histName = "mjj_kfit";
  if (isBTag){
    dirName = "BTag";
    histName = "mjj";
  }

  gStyle->SetFrameLineWidth(2);
  //pave text CMS box
  TPaveText *pt = new TPaveText(0.60,0.9054,0.90,0.9362, "brNDC"); 
  pt->SetBorderSize(1); pt->SetFillColor(19);
  pt->SetFillStyle(0); pt->SetTextSize(0.05);
  pt->SetLineColor(0); pt->SetTextFont(132);
  TText *text = pt->AddText("35.9 fb^{-1} (13 TeV)");
  text->SetTextAlign(11);
  
  //channel
  TPaveText *ch = paveText(0.50,0.75,0.55,0.80, 0, 19, 1, 0, 132);
  ch->SetTextSize(0.05);
  if(isMuChannel) ch->AddText("#splitline{#mu + jets}{"+ dirName+ "}");
  if(isEleChannel) ch->AddText("#splitline{e + jets}{" + dirName + "}");
     
  gStyle->SetOptStat(0);
  TCanvas *c1 = new TCanvas(histName, histName, 800, 800);
  TLegend* leg = new TLegend(0.65,0.25,0.80,0.70,NULL,"brNDC");
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillColor(0);
  
  TGaxis::SetMaxDigits(3);
  //overlay
  c1->cd();
  gPad->SetLeftMargin(0.13);
  gPad->SetRightMargin(0.05);
  gPad->SetBottomMargin(0.13); 
  //gPad->SetTopMargin(0.11);
 
  cout<<"ttbar"<<endl;
  TH1F* hTT = getHisto(fTT,       histName, 1, xMin_, xMax_);
  cout<<"WH80"<<endl;
  TH1F* hWH80 = getHisto(fWH80,  histName, 2, xMin_, xMax_);
  hWH80->GetYaxis()->SetRangeUser(1, 1.2* hWH80->GetMaximum());
  cout<<"WH90"<<endl;
  TH1F* hWH90 = getHisto(fWH90,  histName, 3, xMin_, xMax_);
  cout<<"WH100"<<endl;
  TH1F* hWH100 = getHisto(fWH100, histName, 4, xMin_, xMax_);
  cout<<"WH120"<<endl;
  TH1F* hWH120 = getHisto(fWH120, histName, 52, xMin_, xMax_);
  cout<<"WH140"<<endl;
  TH1F* hWH140 = getHisto(fWH140, histName, 6, xMin_, xMax_);
  cout<<"WH150"<<endl;
  TH1F* hWH150 = getHisto(fWH150, histName, 7, xMin_, xMax_);
  cout<<"WH1550"<<endl;
  TH1F* hWH155 = getHisto(fWH155, histName, 8, xMin_, xMax_);
  cout<<"WH160"<<endl;
  TH1F* hWH160 = getHisto(fWH160, histName, 11, xMin_, xMax_);
  
  //hTT->Draw("HIST");
  hWH80 ->Draw("HIST");
  hWH90 ->Draw("HISTSAME");
  hWH100->Draw("HISTSAME");
  hWH120->Draw("HISTSAME");
  hWH140->Draw("HISTSAME");
  hWH150->Draw("HISTSAME");
  hWH155->Draw("HISTSAME");
  hWH160->Draw("HISTSAME");
  //leg->AddEntry(hTT, "ttbar","PL");
  leg->AddEntry(hWH80 , "m_{H^{+}} = 80 GeV","PL");
  leg->AddEntry(hWH90 , "m_{H^{+}} = 90 GeV","PL");
  leg->AddEntry(hWH100, "m_{H^{+}} = 100 GeV","PL");
  leg->AddEntry(hWH120, "m_{H^{+}} = 120 GeV","PL");
  leg->AddEntry(hWH140, "m_{H^{+}} = 140 GeV","PL");
  leg->AddEntry(hWH150, "m_{H^{+}} = 150 GeV","PL");
  leg->AddEntry(hWH155, "m_{H^{+}} = 155 GeV","PL");
  leg->AddEntry(hWH160, "m_{H^{+}} = 160 GeV","PL");
  leg->Draw();
  ch->Draw();
  pt->Draw();
  if(isSaveHisto){
    TString outFile("$PWD/");
    if(isMuChannel) outFile += "sig_"+dirName+"_"+histName+"_mu.pdf";
    if(isEleChannel) outFile += "sig_"+dirName+"_"+histName+"_ele.pdf";
    c1->SaveAs(outFile);
    //c1->Close();
  }
}
