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

using namespace std;
 
///////////////////////////////////////////  
//CHANNEL
bool isMuChannel = true;
bool isEleChannel = false;
TString baseIsoDir = "baseLowMET";
//TString baseIsoDir = "baseIso20LowMET";

//INPUT FILES
TFile* fData = TFile::Open("all_Data.root");

TFile* fVV	= TFile::Open("all_VV.root");
TFile* fDY	= TFile::Open("all_DY.root");
TFile* fWJ	= TFile::Open("all_WJets.root");
TFile* fST	= TFile::Open("all_ST.root");
TFile* fTT	= TFile::Open("all_TTJetsP.root");
TFile *fSig     = TFile::Open("all_Hplus120.root");
double sf_ttbar = 1.0; 
  
//SAVE HISTOS ON DISK
bool isSaveHisto = true;
///////////////////////////////////////////  

//*-------------------------------
//* get histo from root files
//*-------------------------------
TH1F* getHisto(TFile *histFile, TString dirBase, TString dirIso, TString dirBTag, TString histName, double sf){
  TH1F* hist;
  TString histPath("");
  if(histName=="cutflow") histPath = dirBase+"/"+dirIso+"/"+histName;
  else  histPath = dirBase+"/"+dirIso+"/"+dirBTag+"/"+histName;

  if(!(histFile->Get(histPath))){
    hist = (TH1F*)(fTT->Get(histPath))->Clone(histName);
    hist->Add(hist, -1);
  }else hist = (TH1F*)(histFile->Get(histPath))->Clone(histName);
  hist->Scale(sf);
  cout<<dirBTag<<", "<<dirIso<<", "<<dirBTag<<", "<<histName<<", "<<hist->Integral()<<endl;
  return hist;
}

void makeHistoPositive(TH1F* hist, bool setErrorZero = false){
  for(int ibin=1; ibin<hist->GetNbinsX(); ibin++){
    double binCont = hist->GetBinContent(ibin);
    if(binCont<0){
      hist->SetBinContent(ibin, 0);
      if(setErrorZero) hist->SetBinError(ibin, 0);
    }
  }
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

//*-------------------------------
//* function for (Data -nonQCDBkg)
//*-------------------------------
TH1F * dataMCdiff(TString dirIso, TString dirBTag, TString histname, TString xaxis_title, int bin, bool log=false, bool axisrange=false, double xmin=0, double xmax=10){
  //hMC = all Bkg MC samples
  TH1F* hMC =  (TH1F*) getHisto(fVV, baseIsoDir, dirIso, dirBTag, histname, 1)->Clone("hMC");
  hMC->Add(getHisto(fDY, baseIsoDir, dirIso, dirBTag, histname, 1));
  hMC->Add(getHisto(fST, baseIsoDir, dirIso, dirBTag, histname, 1));
  hMC->Add(getHisto(fWJ, baseIsoDir, dirIso, dirBTag, histname, 1));
  hMC->Add(getHisto(fTT, baseIsoDir, dirIso, dirBTag, histname, sf_ttbar));
  
  //DATA
  TH1F* hData = (TH1F*)getHisto(fData, baseIsoDir, dirIso, dirBTag, histname, 1)->Clone("data");
  //Data - non QCD Bkg
  TH1F *hDiff = (TH1F*)hData->Clone("hDiff");
  hDiff->Add(hMC, -1);
  hDiff->SetMarkerStyle(20);
  hDiff->SetMarkerSize(1.0);
  hDiff->GetYaxis()->SetRangeUser(0, 2);
  hDiff->GetXaxis()->SetRangeUser(xmin, xmax);
  hDiff->SetTitle("");
  hDiff->GetXaxis()->SetTitle(xaxis_title); 
  hDiff->GetYaxis()->SetTitleOffset(1.20);
  hDiff->GetYaxis()->SetTitle("QCD events (norm. to 1) "); hDiff->GetYaxis()->CenterTitle();
  hDiff->GetYaxis()->SetTitleSize(0.07); hDiff->GetXaxis()->SetTitleSize(0.07);
  hDiff->GetXaxis()->SetLabelSize(0.05); hDiff->GetXaxis()->LabelsOption("u"); // extra
  hDiff->GetYaxis()->SetLabelSize(0.05); hDiff->GetYaxis()->LabelsOption("u"); // extra
  ///hDiff->Draw("e1"); // use "P" or "AP"
  //hDiff->Draw("E same");
  makeHistoPositive(hDiff, false);
  return hDiff;
}

//*-------------------------------
//* Overlap of 2 (Data -nonQCDBkg)
//*-------------------------------

void dataMCdiffOverlap(TString dirIso, TString dirNoniso, TString dirBTag, TString histname, TString xaxis_title, double xmin=0, double xmax = 100){
  gStyle->SetOptStat(0);
  gStyle->SetFrameLineWidth(2);
  const float xpad[2] = {0.0, 1.0};
  const float ypad[3] = {0.0, 0.30,0.98};
  TCanvas *canv = new TCanvas();
  canv->Divide(1, 2);

  canv->cd(1);
  gPad->SetPad(xpad[0],ypad[1],xpad[1],ypad[2]);
  //gPad->SetTopMargin(1.15); 
  gPad->SetLeftMargin(0.15);
  gPad->SetRightMargin(0.05);
  gPad->SetBottomMargin(0.0);

  //legend box
  TLegend* leg = new TLegend(0.7518792,0.6261504,0.9512081,0.9198861,NULL,"brNDC");
  leg->SetFillStyle(0); leg->SetBorderSize(0);
  leg->SetFillColor(10); leg->SetTextSize(0.07);

  //pave text CMS box
  TPaveText *pt = new TPaveText(0.65,0.9354,0.90,0.9362, "brNDC"); 
  pt->SetBorderSize(1); pt->SetFillColor(19);
  pt->SetFillStyle(0); pt->SetTextSize(0.08);
  pt->SetLineColor(0); pt->SetTextFont(132);
  TText *text = pt->AddText("35.9 fb^{-1} (13 TeV)");
  text->SetTextAlign(11);
  
  //channel
  TPaveText *ch = paveText(0.50,0.75,0.55,0.80, 0, 19, 1, 0, 132);
  ch->SetTextSize(0.08);
  if(isMuChannel) ch->AddText("#splitline{#mu + jets}{"+ dirBTag+ "}");
  if(isEleChannel) ch->AddText("#splitline{e + jets}{" + dirBTag + "}");

  //data-MC from isolated region
  TH1F *hDiff = dataMCdiff(dirIso, dirBTag, histname, xaxis_title, 1, true, true, xmin, xmax);
  leg->AddEntry(hDiff,"Iso","P");
  hDiff->SetMarkerColor(kRed);
  hDiff->SetLineColor(kRed);
  hDiff->Scale(1/hDiff->Integral());
  cout<<hDiff->GetMaximum()<<endl;
  hDiff->GetYaxis()->SetRangeUser(-0.05,  1.5*hDiff->GetMaximum());
  hDiff->GetYaxis()->SetTitleOffset(1.00);
  hDiff->GetYaxis()->SetTitleSize(0.08);   
  hDiff->GetYaxis()->SetLabelSize(0.08);   
  hDiff->GetYaxis()->SetTickLength(0.04); 
  hDiff->GetYaxis()->SetNdivisions(5);
  hDiff->Draw("e1"); 
  
  //data-MC from non-isolated region
  TH1F *hDiff_NonIso = dataMCdiff(dirNoniso, dirBTag, histname, xaxis_title, 1, true, true, xmin, xmax);
  leg->AddEntry(hDiff_NonIso,"NonIso","P");
  hDiff_NonIso->SetMarkerColor(kGreen);
  hDiff_NonIso->SetLineColor(kGreen);
  hDiff_NonIso->Scale(1/hDiff_NonIso->Integral());
  hDiff_NonIso->Draw("SAME");  
  pt->Draw();
  leg->Draw();
  ch->Draw();

  canv->cd(2);
  gPad->SetPad(xpad[0],ypad[0],xpad[1], ypad[1]);
  gPad->SetTopMargin(0); 
  gPad->SetBottomMargin(0.5); gPad->SetGridy();
  gPad->SetLeftMargin(0.15);
  gPad->SetRightMargin(0.05);
  TH1F *hRatio = (TH1F*)hDiff->Clone("hRatio");
  hRatio->Reset();
  hRatio->Add(hDiff);
  hRatio->Divide(hDiff_NonIso); hRatio->SetMarkerStyle(20); hRatio->SetMarkerSize(0.8);
  hRatio->SetMarkerColor(kBlack); hRatio->SetLineColor(kBlack); hRatio->GetYaxis()->SetRangeUser(-5, 5);
  //hRatio->GetXaxis()->SetRangeUser(xmin, xmax);
  hRatio->GetXaxis()->SetTickLength(0.13); 
  hRatio->GetYaxis()->SetTickLength(0.04); 
  hRatio->GetXaxis()->SetTitle(xaxis_title); 
  hRatio->GetYaxis()->SetTitleOffset(0.50);
  hRatio->GetXaxis()->SetTitleOffset(1.10);
  hRatio->GetYaxis()->SetTitle("#frac{Iso}{NonIso}"); hRatio->GetYaxis()->CenterTitle();
  hRatio->GetYaxis()->SetTitleSize(0.15); hRatio->GetXaxis()->SetTitleSize(0.20);
  hRatio->GetXaxis()->SetLabelSize(0.20); 
  hRatio->GetYaxis()->SetLabelSize(0.15); 
  hRatio->GetYaxis()->SetNdivisions(5);
  hRatio->Draw("E"); // use "P" or "AP"

  TF1 *baseLine = new TF1("baseLine","1", -100, 2000); 
  baseLine->SetLineColor(kCyan+1);
  baseLine->Draw("SAME");

  //canv->Update();
  if(isSaveHisto){
    TString outFile("$PWD/QCD/");
    //outFile += histname;
    if(isMuChannel)outFile += "mu_"+dirBTag+"_"+histname+".pdf";
    if(isEleChannel)outFile += "ele_"+dirBTag+"_"+histname+".pdf";
    canv->SaveAs(outFile);
    //canv->Close();
  }
  
}

void qcd_sf(){
  TH1F *hDiff = dataMCdiff("Iso", " ", "cutflow", "cutflow", 1, true, true, 0, 15);
  TH1F *hDiff_NonIso = dataMCdiff("NonIso", " ", "cutflow", "cutflow", 1, true, true, 0, 15);
  int nbin= hDiff->GetSize();
  TString steps[10] = {"muon trig","= 1 muon", "#geq 4 jets","#slash{E}_{T} #geq 20GeV", "#geq 2 b-jets", "KinFit","ctag"};
  hDiff->Divide(hDiff_NonIso);
  std::cout << std::setprecision(4);
  for(int i=1; i<10; i++){
    double sf = hDiff->GetBinContent(i); 
    double sf_err = hDiff->GetBinError(i);
    cout<<sf<<" +- "<<sf_err<<"\t"<<steps[i-1]<<endl;
  }
  hDiff->Draw("e1");
  hDiff->SetTitle("");
  hDiff->GetYaxis()->SetTitle("QCD scale factors");
}

void dataDrivenQCD_13TeV(){
  //TString dir = "KinFit";
  TString dir = "BTag";
  if(isMuChannel){
    dataMCdiffOverlap("Iso", "NonIso", dir, "pt_mu", "Pt^{#mu} [GeV]", 0, 300);
    dataMCdiffOverlap("Iso", "NonIso", dir, "eta_mu", "#eta^{#mu}", -10, 10);
  }
  if(isEleChannel){
    dataMCdiffOverlap("Iso", "NonIso", dir, "pt_ele", "Pt^{e} [GeV]", 0, 300);
    dataMCdiffOverlap("Iso", "NonIso", dir, "eta_ele", "#eta^{e}", -10, 10);
  }
  //qcd_shape(dir, "final_pt_met", "MET[GeV]", 0, 30);
  ////qcd_shape(dir, "wmt", "E_{T}^{miss}[GeV]", 0, 200);
  dataMCdiffOverlap("Iso", "NonIso", dir, "pt_jet", "Pt^{jets} [GeV]", 0, 300);
  dataMCdiffOverlap("Iso", "NonIso", dir, "eta_jet", "#eta^{jets}", -10, 10);
}
