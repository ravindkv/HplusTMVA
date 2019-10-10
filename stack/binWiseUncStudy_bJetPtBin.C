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

string intToStr(int val){
     ostringstream convert;
     string result("");
     convert <<val;
     result = convert.str(); 
  return result;
}
string doubleToStr(double val){
     ostringstream convert;
     string result("");
     convert <<val;
     result = convert.str(); 
  return result;
}

TH1F * getHisto(TFile *f, TString histName){
  TH1F *hist;
  string exception_msg (f->GetName() +TString("/")+histName+", does not exist");
  try{
    if(!(f->Get(histName)))
       throw  exception_msg.c_str();
  }catch (const char *e){
    //cout<<"WARNING : "<<e<<endl;
  }
  //exit(0);
  if(!(f->Get(histName))){
    hist = (TH1F*)(f->Get("ttbar"))->Clone(histName);
    hist->Add(hist, -1);
  }else hist = (TH1F*)f->Get(histName);
  return hist;
  f->Close();
  delete f;
}

TH1F * getAllBkgHist(TFile *f, TString sys){
  TH1F *ttbar = getHisto(f, "ttbar"+sys);
  TH1F *wjet = getHisto(f, "wjet"+sys);
  TH1F *zjet = getHisto(f, "zjet"+sys);
  TH1F *stop = getHisto(f, "stop"+sys);
  TH1F *diboson = getHisto(f, "diboson"+sys);
  TH1F *qcd = getHisto(f, "qcd");
  TH1F* h_Bkg = (TH1F*)ttbar->Clone("Bkg MC");
  h_Bkg->Add(wjet);
  h_Bkg->Add(zjet);
  h_Bkg->Add(stop);
  h_Bkg->Add(diboson);
  h_Bkg->Add(qcd);
  return h_Bkg;
}

void printRow(string cat_name, TH1F * hData, TH1F * hBkg, TH1F* hSig, ofstream &outFile){
  for(int i = 1; i < hData->GetSize(); i++){
    double binConBkg = hBkg->GetBinContent(i);
    double binErrBkg = hBkg->GetBinError(i);
    double binConSig = hSig->GetBinContent(i);
    double binErrSig = hSig->GetBinError(i);
    double binConData = hData->GetBinContent(i);
    double binErrData = hData->GetBinError(i);
    double n_sigma = (binConData - binConBkg)/binErrData;
    double n_sigma_new = (binConData - binConBkg)/sqrt(binErrData*binErrData + binErrBkg*binErrBkg);
    double err_bkg = 100*binErrBkg/binConBkg;
    double err_sig = 100*binErrSig/binConSig;
    ///if(binConData==0 && binConBkg!=0) outFile<<"BBBB = "<< i<<endl;
    if(err_bkg >20) cout<<setw(20)<<cat_name<<": "<<setw(10)<<i<<setw(10)<<err_bkg<<endl;
    if(err_bkg > 50) outFile<<"==>"<<endl;
    outFile<<setw(5)<<i<<setw(9)<<std::setprecision(3)<<
	    //binConData<< setw(9)<<binErrData<<setw(9)<<
	    binConBkg<<setw(9)<<binErrBkg<<setw(9)<< err_bkg<<setw(9)<<endl;
	    //setw(9)<< err_bkg<<setw(9)<<n_sigma<<setw(9)<<n_sigma_new<<setw(9)<<
	    ///binConSig<<setw(9)<<binErrSig<<setw(9)<<err_sig<<endl;
  }
}

void printRowName(string cat_name, ofstream &outFile){
    outFile<<endl;
    outFile<<"============================================="<<endl;
    outFile<<cat_name<<endl;
    outFile<<"============================================="<<endl;
    outFile<<setw(5)<<"bin"<<setw(9)<<
	     //"data"<<setw(9)<<"error"<<setw(9)<<
	     "bkg"<<setw(9)<<"error"<<setw(9)<<"%error"<<setw(9)<<endl;
	     ///"sig"<<setw(9)
	     //"n_sigma"<<setw(9)<<"n_sigma2"<<setw(9)<<"sig"<<setw(9)
	     ///<<"error"<<setw(9)<<"%error"<<endl;
    outFile<<setw(5)<<""<<setw(9)<<""<<
	    //setw(9)<<"(data)"<<setw(9)<<
	     ""<<setw(9)<<"(bkg)"<<setw(9)<<"(bkg)"<<setw(9)<<""<<setw(9)<<endl;
	     //""<<setw(9)<<""<<setw(9)<<"(sig)"<<setw(9)<<"(sig)"<<endl;
	     //"(sig)"<<setw(9)<<"(sig)"<<endl;
}

TCanvas * compareMjjOneSys(TH1F* hBase, TH1F* hUp, TH1F* hDown, TString process, TString sys, TString cat){
  gStyle->SetOptStat(0);
  gStyle->SetFrameLineWidth(2);
  const float xpad[2] = {0.,1};
  const float ypad[4] = {0.,0.30,0.30,0.98};
  TCanvas *my_can = new TCanvas();
  my_can->Divide(1, 2);
  my_can->cd(1);
  gPad->SetPad(xpad[0],ypad[2],xpad[1],ypad[3]);
  gPad->SetTopMargin(1.15); 
  gPad->SetBottomMargin(0); 
  gPad->SetLeftMargin(0.15);
  gPad->SetRightMargin(0.05);
  double scale_factor = 1; 
  TLegend* leg = new TLegend(0.60,0.60,0.80,0.85,NULL,"brNDC");
  if(process.Contains("WH120"))
    leg = new TLegend(0.18,0.55,0.38,0.75,NULL,"brNDC");
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);
  leg->SetFillColor(10);
  leg->SetTextSize(0.07);
  //  leg->SetHeader("#splitline{CMS Preliminary}{   @ #sqrt{s} = 7 TeV}");
  
  hUp->SetLineColor(kGreen);
  hUp->SetLineWidth(1);
  
  hBase->SetLineColor(kBlue);
  hBase->SetLineWidth(1);
  hBase->SetTitle("");
  hBase->GetYaxis()->SetTitle("Events");
  //hBase->GetYaxis()->SetRangeUser(1, 1.2* hBase->GetMaximum());
  hBase->GetXaxis()->SetNdivisions(5);
  hBase->GetYaxis()->SetNdivisions(5);
  hBase->GetYaxis()->SetTitleOffset(1.00);
  hBase->GetXaxis()->SetTitleOffset(1.00);
  hBase->GetYaxis()->SetTitleSize(0.08);   
  hBase->GetXaxis()->SetTitleSize(0.06);
  hBase->GetXaxis()->SetLabelSize(0.06);   
  hBase->GetYaxis()->SetLabelSize(0.06);   
  hBase->GetXaxis()->SetTickLength(0.03); 
  hBase->GetYaxis()->SetTickLength(0.03); 
  hDown->SetLineColor(kRed);
  hDown->SetLineWidth(1);
  // legend adding
  leg->AddEntry(hUp,sys+"Up","LP");
  leg->AddEntry(hBase,"Base","LP");
  leg->AddEntry(hDown,sys+"Down","LP");
  // Header
  TPaveText *header = new TPaveText(0.15,0.91,0.9,0.95, "brNDC");
  header->SetBorderSize(1);
  header->SetFillColor(19);
  header->SetFillStyle(0);
  header->SetLineColor(0);
  header->SetTextFont(132);
  header->SetTextSize(0.08);
  TText *text = header->AddText(cat);
  //TText *text = header->AddText("CMS Simulation,    #sqrt{s} = 13 TeV, 35.9 fb^{-1}");
  text->SetTextAlign(11);

  TPaveText *pt = new TPaveText(0.18,0.82,0.38,0.87,"brNDC");
  //pt->AddText(process+"_"+unctype);
  pt->AddText(process);
  pt->SetFillColor(19);
  pt->SetFillStyle(0);
  pt->SetLineColor(0);
  pt->SetBorderSize(1);
  pt->SetTextSize(0.06);

  hBase->GetXaxis()->SetTitle("M_{jj} [GeV]");
  hBase->Draw("HIST");
  hUp->Draw("HISTSAME");
  hDown->Draw("HISTSAME");
  leg->Draw();
  header->Draw();
  pt->Draw();
  gPad->RedrawAxis();
  ////////////////////////////// Ratio //////////////////////////// 
  my_can->cd(2);
  gPad->SetPad(xpad[0],ypad[0],xpad[1],ypad[1]);
  gPad->SetTopMargin(0); gPad->SetBottomMargin(0.5); //gPad->SetGridy();
  gPad->SetLeftMargin(0.15);
  gPad->SetRightMargin(0.05);
  TH1F *hRatio_Up = (TH1F*)hBase->Clone("hRatio_Up");
  //hRatio_Up->GetYaxis()->SetNdivisions(3);
  hRatio_Up->Reset();
  hRatio_Up->Add(hUp);
  hRatio_Up->Divide(hBase); hRatio_Up->SetMarkerStyle(20); hRatio_Up->SetMarkerSize(0.4);
  hRatio_Up->SetMarkerColor(kGreen); hRatio_Up->SetLineColor(kGreen); hRatio_Up->GetYaxis()->SetRangeUser(0.5, 1.5);
  //hRatio_Up->GetXaxis()->SetRangeUser(xmin, xmax);
  hRatio_Up->GetXaxis()->SetTickLength(0.13); 
  hRatio_Up->GetYaxis()->SetTickLength(0.04); 
  hRatio_Up->GetXaxis()->SetTitle("M_{jj} [GeV]"); 
  hRatio_Up->GetYaxis()->SetTitleOffset(0.50);
  hRatio_Up->GetXaxis()->SetTitleOffset(1.10);
  hRatio_Up->GetYaxis()->SetTitle("Ratio"); hRatio_Up->GetYaxis()->CenterTitle();
  hRatio_Up->GetYaxis()->SetTitleSize(0.15); hRatio_Up->GetXaxis()->SetTitleSize(0.20);
  hRatio_Up->GetXaxis()->SetLabelSize(0.20); 
  hRatio_Up->GetYaxis()->SetLabelSize(0.15); 
  hRatio_Up->Draw("E"); // use "P" or "AP"
  TH1F *hRatio_Down = (TH1F*)hDown->Clone("hRatio_Up");
  hRatio_Down->Reset();
  hRatio_Down->Add(hDown);
  hRatio_Down->Divide(hBase); 
  hRatio_Down->SetMarkerColor(kRed); hRatio_Down->SetLineColor(kRed); hRatio_Down->GetYaxis()->SetRangeUser(0, 2);
  hRatio_Down->Draw("SAME"); // use "P" or "AP"
  TF1 *baseLine = new TF1("baseLine","1", -100, 2000); 
  baseLine->SetLineColor(kBlack);
  //baseLine->Draw("SAME");
  return my_can;
}

TH1F * getRatioHist(TH1F* hBase, TH1F* hUp){
  TH1F * hRatio = (TH1F*)hBase->Clone("hRatio");
  hRatio->Reset();
  for(int i = 1; i< hRatio->GetSize(); i++){
    double binConBase = hBase->GetBinContent(i);
    double binConUp = hUp->GetBinContent(i);
    double binErrBase = hBase->GetBinError(i);
    double binErrUp = hUp->GetBinError(i);
    if(binConBase!=0){
      double ratio = binConUp/binConBase;
      double ratioErr = (binErrBase/binConBase)*(binConUp/binConBase);
      hRatio->SetBinContent(i, ratio);
      hRatio->SetBinError(i, ratioErr);
    }
  }
  return hRatio;
}
//get integral uncertainity
double getIntgralUnc(TH1F *hBase, TH1F* hUp, TH1F* hDown){
  return 1 + max(fabs(hUp->Integral() - hBase->Integral()), 
		  fabs(hBase->Integral() - hDown->Integral()))/hBase->Integral();
}

TCanvas * compareRatioGraph(TH1F* hBase, TH1F* hUp, TH1F* hDown, TString process, TString sys, TString cat){
  gStyle->SetOptStat(0);
  gStyle->SetFrameLineWidth(2);
  TCanvas *my_can = new TCanvas();
  TLegend* leg = new TLegend(0.50,0.65,0.70,0.85,NULL,"brNDC");
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);
  leg->SetFillColor(10);
  leg->SetTextSize(0.07);
  //  leg->SetHeader("#splitline{CMS Preliminary}{   @ #sqrt{s} = 7 TeV}");
  // Header
  TPaveText *header = new TPaveText(0.15,0.91,0.9,0.95, "brNDC");
  header->SetBorderSize(1);
  header->SetFillColor(19);
  header->SetFillStyle(0);
  header->SetLineColor(0);
  header->SetTextFont(132);
  header->SetTextSize(0.09);
  TText *text = header->AddText(cat);
  //TText *text = header->AddText("CMS Simulation,    #sqrt{s} = 13 TeV, 35.9 fb^{-1}");
  text->SetTextAlign(11);

  TPaveText *pt = new TPaveText(0.18,0.82,0.38,0.87,"brNDC");
  //pt->AddText(process+"_"+unctype);
  pt->AddText(process);
  pt->SetFillColor(19);
  pt->SetFillStyle(0);
  pt->SetLineColor(0);
  pt->SetBorderSize(1);
  pt->SetTextSize(0.08);

  gPad->SetBottomMargin(0.16); //gPad->SetGridy();
  gPad->SetLeftMargin(0.15);
  gPad->SetRightMargin(0.05);
  hRatio_Up = getRatioHist(hBase, hUp);
  hRatio_Up->SetMarkerStyle(20); hRatio_Up->SetMarkerSize(0.4);
  hRatio_Up->SetMarkerColor(kGreen); hRatio_Up->SetLineColor(kGreen); 
  hRatio_Up->SetTitle("");
  hRatio_Up->SetLineWidth(1);
  hRatio_Up->GetYaxis()->SetRangeUser(0.5, 1.5);
  //hRatio_Up->GetYaxis()->SetRangeUser(-0.5, 2.5);
  hRatio_Up->GetXaxis()->SetTickLength(0.04); 
  hRatio_Up->GetYaxis()->SetNdivisions(5);
  hRatio_Up->GetYaxis()->SetTickLength(0.04); 
  hRatio_Up->GetXaxis()->SetTitle("M_{jj} [GeV]"); 
  hRatio_Up->GetYaxis()->SetTitleOffset(0.90);
  hRatio_Up->GetXaxis()->SetTitleOffset(0.90);
  hRatio_Up->GetYaxis()->SetTitle("Ratio (Unc/Base)"); 
  hRatio_Up->GetYaxis()->CenterTitle();
  hRatio_Up->GetYaxis()->SetTitleSize(0.08); 
  hRatio_Up->GetXaxis()->SetTitleSize(0.08);
  hRatio_Up->GetXaxis()->SetLabelSize(0.07); 
  hRatio_Up->GetYaxis()->SetLabelSize(0.07); 
  hRatio_Up->Draw("E"); // use "P" or "AP"

  hRatio_Down = getRatioHist(hBase, hDown);
  hRatio_Down->SetMarkerColor(kRed); hRatio_Down->SetLineColor(kRed); 
  hRatio_Down->SetLineWidth(1);
  hRatio_Down->SetMarkerSize(0.4);
  hRatio_Down->Draw("SAME"); // use "P" or "AP"
  // legend adding
  double intUnc = getIntgralUnc( hBase, hUp, hDown);
  string intUnc_ = doubleToStr(intUnc);
  TF1 *baseLine = new TF1("baseLine",intUnc_.c_str(), -100, 2000); 
  baseLine->SetLineColor(kBlue);
  baseLine->Draw("SAME");
  baseLine->SetLineWidth(1);
  leg->AddEntry(hRatio_Up,sys+"Up","LP");
  leg->AddEntry(baseLine, "lnN","LP");
  leg->AddEntry(hRatio_Down,sys+"Down","LP");
  leg->Draw();
  header->Draw();
  pt->Draw();
  return my_can;
}

void binWiseUncStudy(){
  bool isPrint = true;
  bool isSig = false;
  bool isBkg = false;
  bool isHist = false;
  bool isGraph = false;
  std::vector<std::string> mjjFiles;
  mjjFiles.push_back("BothCat/Shapes_hcs_13TeV_mu_PtbJetCatL_mjj_kfit_25To42.root"); 
  mjjFiles.push_back("BothCat/Shapes_hcs_13TeV_mu_PtbJetCatL_mjj_kfit_42To57.root"); 
  mjjFiles.push_back("BothCat/Shapes_hcs_13TeV_mu_PtbJetCatL_mjj_kfit_57To74.root"); 
  mjjFiles.push_back("BothCat/Shapes_hcs_13TeV_mu_PtbJetCatL_mjj_kfit_74To99.root"); 
  mjjFiles.push_back("BothCat/Shapes_hcs_13TeV_mu_PtbJetCatL_mjj_kfit_99To500.root"); 
  mjjFiles.push_back("BothCat/Shapes_hcs_13TeV_mu_PtbJetCatM_mjj_kfit_25To42.root"); 
  mjjFiles.push_back("BothCat/Shapes_hcs_13TeV_mu_PtbJetCatM_mjj_kfit_42To57.root"); 
  mjjFiles.push_back("BothCat/Shapes_hcs_13TeV_mu_PtbJetCatM_mjj_kfit_57To74.root"); 
  mjjFiles.push_back("BothCat/Shapes_hcs_13TeV_mu_PtbJetCatM_mjj_kfit_74To99.root"); 
  mjjFiles.push_back("BothCat/Shapes_hcs_13TeV_mu_PtbJetCatM_mjj_kfit_99To500.root");
  mjjFiles.push_back("BothCat/Shapes_hcs_13TeV_mu_PtbJetCatT_mjj_kfit_25To42.root"); 
  mjjFiles.push_back("BothCat/Shapes_hcs_13TeV_mu_PtbJetCatT_mjj_kfit_42To57.root"); 
  mjjFiles.push_back("BothCat/Shapes_hcs_13TeV_mu_PtbJetCatT_mjj_kfit_57To74.root"); 
  mjjFiles.push_back("BothCat/Shapes_hcs_13TeV_mu_PtbJetCatT_mjj_kfit_74To99.root"); 
  mjjFiles.push_back("BothCat/Shapes_hcs_13TeV_mu_PtbJetCatT_mjj_kfit_99To500.root");
  mjjFiles.push_back("BothCat/Shapes_hcs_13TeV_ele_PtbJetCatL_mjj_kfit_25To42.root");
  mjjFiles.push_back("BothCat/Shapes_hcs_13TeV_ele_PtbJetCatL_mjj_kfit_42To57.root");
  mjjFiles.push_back("BothCat/Shapes_hcs_13TeV_ele_PtbJetCatL_mjj_kfit_57To74.root");
  mjjFiles.push_back("BothCat/Shapes_hcs_13TeV_ele_PtbJetCatL_mjj_kfit_74To99.root");
  mjjFiles.push_back("BothCat/Shapes_hcs_13TeV_ele_PtbJetCatL_mjj_kfit_99To500.root");
  mjjFiles.push_back("BothCat/Shapes_hcs_13TeV_ele_PtbJetCatM_mjj_kfit_25To42.root"); 
  mjjFiles.push_back("BothCat/Shapes_hcs_13TeV_ele_PtbJetCatM_mjj_kfit_42To57.root"); 
  mjjFiles.push_back("BothCat/Shapes_hcs_13TeV_ele_PtbJetCatM_mjj_kfit_57To74.root"); 
  mjjFiles.push_back("BothCat/Shapes_hcs_13TeV_ele_PtbJetCatM_mjj_kfit_74To99.root"); 
  mjjFiles.push_back("BothCat/Shapes_hcs_13TeV_ele_PtbJetCatM_mjj_kfit_99To500.root");
  mjjFiles.push_back("BothCat/Shapes_hcs_13TeV_ele_PtbJetCatT_mjj_kfit_25To42.root"); 
  mjjFiles.push_back("BothCat/Shapes_hcs_13TeV_ele_PtbJetCatT_mjj_kfit_42To57.root"); 
  mjjFiles.push_back("BothCat/Shapes_hcs_13TeV_ele_PtbJetCatT_mjj_kfit_57To74.root"); 
  mjjFiles.push_back("BothCat/Shapes_hcs_13TeV_ele_PtbJetCatT_mjj_kfit_74To99.root"); 
  mjjFiles.push_back("BothCat/Shapes_hcs_13TeV_ele_PtbJetCatT_mjj_kfit_99To500.root"); 

  std::vector<std::string> catName;
  catName.push_back("mu_CatL_25To42"); 
  catName.push_back("mu_CatL_42To57"); 
  catName.push_back("mu_CatL_57To74"); 
  catName.push_back("mu_CatL_74To99"); 
  catName.push_back("mu_CatL_99To500"); 
  catName.push_back("mu_CatM_25To42"); 
  catName.push_back("mu_CatM_42To57"); 
  catName.push_back("mu_CatM_57To74"); 
  catName.push_back("mu_CatM_74To99"); 
  catName.push_back("mu_CatM_99To500");
  catName.push_back("mu_CatT_25To42"); 
  catName.push_back("mu_CatT_42To57"); 
  catName.push_back("mu_CatT_57To74"); 
  catName.push_back("mu_CatT_74To99"); 
  catName.push_back("mu_CatT_99To500");
  catName.push_back("ele_CatL_25To42");
  catName.push_back("ele_CatL_42To57");
  catName.push_back("ele_CatL_57To74");
  catName.push_back("ele_CatL_74To99");
  catName.push_back("ele_CatL_99To500");
  catName.push_back("ele_CatM_25To42"); 
  catName.push_back("ele_CatM_42To57"); 
  catName.push_back("ele_CatM_57To74"); 
  catName.push_back("ele_CatM_74To99"); 
  catName.push_back("ele_CatM_99To500");
  catName.push_back("ele_CatT_25To42"); 
  catName.push_back("ele_CatT_42To57"); 
  catName.push_back("ele_CatT_57To74"); 
  catName.push_back("ele_CatT_74To99"); 
  catName.push_back("ele_CatT_99To500"); 

  ofstream outFile; 
  outFile.open("binWiseTable.txt"); 
  //----------------------------------------
  // Loop over all 30 Mjj distributions
  //----------------------------------------
  std::vector<string>::iterator itr;
  int index = 0;
  for(itr = mjjFiles.begin(); itr!= mjjFiles.end(); itr++){
    string file_name = *itr;
    TFile *f = TFile::Open(file_name.c_str());
    TH1F *hData = getHisto(f, "data_obs");
    TH1F *hTTbar = getHisto(f, "ttbar");
    TH1F *hSig = getHisto(f, "WH120");
    TH1F* hBkg = getAllBkgHist(f, "");

    index++;
    TString cat_ = TString("#"+intToStr(index)+": "+catName[index -1]);
    //----------------------------------------
    // Print the bin by bin content/error
    //----------------------------------------
    if(isPrint){
      printRowName(string(cat_), outFile);
      printRow(string(cat_), hData, hBkg, hSig, outFile);
    }

    //----------------------------------------
    // Compare Up/Down with base: AllBkg
    //----------------------------------------
    TH1F* hBkgJESUp = getAllBkgHist(f, "_JESUp");
    TH1F* hBkgJESDown = getAllBkgHist(f, "_JESDown");
    TH1F* hBkgJERUp = getAllBkgHist(f, "_JERUp");
    TH1F* hBkgJERDown = getAllBkgHist(f, "_JERDown");
    TH1F* hBkgcTagUp = getAllBkgHist(f, "_cTagUp");
    TH1F* hBkgcTagDown = getAllBkgHist(f, "_cTagDown");
    TH1F* hBkgbTagUp = getAllBkgHist(f, "_bTagUp");
    TH1F* hBkgbTagDown = getAllBkgHist(f, "_bTagDown");
    TH1F* hBkgPileupUp = getAllBkgHist(f, "_PileupUp");
    TH1F* hBkgPileupDown = getAllBkgHist(f, "_PileupDown");
    TH1F* hTTbarmassUp = getHisto(f, "ttbar_massUp");
    TH1F* hTTbarmassDown = getHisto(f, "ttbar_massDown");
    TH1F* hTTbarscaleUp = getHisto(f, "ttbar_scaleUp");
    TH1F* hTTbarscaleDown = getHisto(f, "ttbar_scaleDown");
    TH1F* hTTbarmatchingUp = getHisto(f, "ttbar_matchingUp");
    TH1F* hTTbarmatchingDown = getHisto(f, "ttbar_matchingDown");
    TH1F* hTTbartopPtUp = getHisto(f, "ttbar_topPtUp");
    TH1F* hTTbartopPtDown = getHisto(f, "ttbar_topPtDown");
    if(isBkg && isHist){//Histogram
      TCanvas *canBkg = new TCanvas();
      canBkg->Divide(3, 3);
      TCanvas * c_BkgJES = compareMjjOneSys(hBkg, hBkgJESUp, hBkgJESDown, "AllBkg", "JES", cat_);
      canBkg->cd(1);
      c_BkgJES->DrawClonePad();
      TCanvas * c_BkgJER =compareMjjOneSys(hBkg, hBkgJERUp, hBkgJERDown, "AllBkg", "JER", cat_);
      canBkg->cd(2);
      c_BkgJER->DrawClonePad();
      TCanvas * c_BkgcTag = compareMjjOneSys(hBkg, hBkgcTagUp, hBkgcTagDown, "AllBkg", "cTag", cat_);
      canBkg->cd(3);
      c_BkgcTag->DrawClonePad();
      TCanvas * c_BkgbTag = compareMjjOneSys(hBkg, hBkgbTagUp, hBkgbTagDown, "AllBkg", "bTag", cat_);
      canBkg->cd(4);
      c_BkgbTag->DrawClonePad();
      TCanvas * c_BkgPileup = compareMjjOneSys(hBkg, hBkgPileupUp, hBkgPileupDown, "AllBkg", "Pileup", cat_);
      canBkg->cd(5);
      c_BkgPileup->DrawClonePad();
      TCanvas * c_TTbarmass = compareMjjOneSys(hTTbar, hTTbarmassUp, hTTbarmassDown, "ttbar", "mass", cat_);
      canBkg->cd(6);
      c_TTbarmass->DrawClonePad();
      TCanvas * c_TTbarscale = compareMjjOneSys(hTTbar, hTTbarscaleUp, hTTbarscaleDown, "ttbar", "scale", cat_);
      canBkg->cd(7);
      c_TTbarscale->DrawClonePad();
      TCanvas * c_TTbarmatching = compareMjjOneSys(hTTbar, hTTbarmatchingUp, hTTbarmatchingDown, "ttbar", "match", cat_);
      canBkg->cd(8);
      c_TTbarmatching->DrawClonePad();
      TCanvas * c_TTbartopPt = compareMjjOneSys(hTTbar, hTTbartopPtUp, hTTbartopPtDown, "ttbar", "topPt", cat_);
      canBkg->cd(9);
      c_TTbartopPt->DrawClonePad();
      TString outFile("MjjShapeBkg/");
      mkdir(outFile, S_IRWXU);
      outFile += TString("mjj_"+intToStr(index)+"_"+catName[index -1])+".pdf";
      canBkg->SaveAs(outFile);
    }  
    if(isBkg && isGraph){//Graph
      TCanvas *canBkgGraph = new TCanvas();
      canBkgGraph->Divide(3, 3);
      TCanvas * c_GraphBkgJES = compareRatioGraph(hBkg, hBkgJESUp, hBkgJESDown, "AllBkg", "JES", cat_);
      canBkgGraph->cd(1);
      c_GraphBkgJES->DrawClonePad();
      TCanvas * c_GraphBkgJER =compareRatioGraph(hBkg, hBkgJERUp, hBkgJERDown, "AllBkg", "JER", cat_);
      canBkgGraph->cd(2);
      c_GraphBkgJER->DrawClonePad();
      TCanvas * c_GraphBkgcTag = compareRatioGraph(hBkg, hBkgcTagUp, hBkgcTagDown, "AllBkg", "cTag", cat_);
      canBkgGraph->cd(3);
      c_GraphBkgcTag->DrawClonePad();
      TCanvas * c_GraphBkgbTag = compareRatioGraph(hBkg, hBkgbTagUp, hBkgbTagDown, "AllBkg", "bTag", cat_);
      canBkgGraph->cd(4);
      c_GraphBkgbTag->DrawClonePad();
      TCanvas * c_GraphBkgPileup = compareRatioGraph(hBkg, hBkgPileupUp, hBkgPileupDown, "AllBkg", "Pileup", cat_);
      canBkgGraph->cd(5);
      c_GraphBkgPileup->DrawClonePad();
      TCanvas * c_GraphTTbarmass = compareRatioGraph(hTTbar, hTTbarmassUp, hTTbarmassDown, "ttbar", "mass", cat_);
      canBkgGraph->cd(6);
      c_GraphTTbarmass->DrawClonePad();
      TCanvas * c_GraphTTbarscale = compareRatioGraph(hTTbar, hTTbarscaleUp, hTTbarscaleDown, "ttbar", "scale", cat_);
      canBkgGraph->cd(7);
      c_GraphTTbarscale->DrawClonePad();
      TCanvas * c_GraphTTbarmatching = compareRatioGraph(hTTbar, hTTbarmatchingUp, hTTbarmatchingDown, "ttbar", "match", cat_);
      canBkgGraph->cd(8);
      c_GraphTTbarmatching->DrawClonePad();
      TCanvas * c_GraphTTbartopPt = compareRatioGraph(hTTbar, hTTbartopPtUp, hTTbartopPtDown, "ttbar", "topPt", cat_);
      canBkgGraph->cd(9);
      c_GraphTTbartopPt->DrawClonePad();
      TString outBkgGraph("MjjGraphBkg/");
      mkdir(outBkgGraph, S_IRWXU);
      outBkgGraph += TString("mjj_"+intToStr(index)+"_"+catName[index -1])+".pdf";
      canBkgGraph->SaveAs(outBkgGraph);
    }  

    //----------------------------------------
    // Compare Up/Down with base: Signal(120)
    //----------------------------------------
    TH1F* hSigJESUp = getHisto(f, "WH120_JESUp");
    TH1F* hSigJESDown = getHisto(f, "WH120_JESDown");
    TH1F* hSigJERUp = getHisto(f, "WH120_JERUp");
    TH1F* hSigJERDown = getHisto(f, "WH120_JERDown");
    TH1F* hSigcTagUp = getHisto(f, "WH120_cTagUp");
    TH1F* hSigcTagDown = getHisto(f, "WH120_cTagDown");
    TH1F* hSigbTagUp = getHisto(f, "WH120_bTagUp");
    TH1F* hSigbTagDown = getHisto(f, "WH120_bTagDown");
    TH1F* hSigPileupUp = getHisto(f, "WH120_PileupUp");
    TH1F* hSigPileupDown = getHisto(f, "WH120_PileupDown");
    TH1F* hSigtopPtUp = getHisto(f, "WH120_topPtUp");
    TH1F* hSigtopPtDown = getHisto(f, "WH120_topPtDown");
    if(isSig && isHist){//Histogram
      TCanvas *canSig = new TCanvas();
      canSig->Divide(3, 2);
      TCanvas * c_SigJES = compareMjjOneSys(hSig, hSigJESUp, hSigJESDown, "WH120", "JES", cat_);
      canSig->cd(1);
      c_SigJES->DrawClonePad();
      TCanvas * c_SigJER =compareMjjOneSys(hSig, hSigJERUp, hSigJERDown, "WH120", "JER", cat_);
      canSig->cd(2);
      c_SigJER->DrawClonePad();
      TCanvas * c_SigcTag = compareMjjOneSys(hSig, hSigcTagUp, hSigcTagDown, "WH120", "cTag", cat_);
      canSig->cd(3);
      c_SigcTag->DrawClonePad();
      TCanvas * c_SigbTag = compareMjjOneSys(hSig, hSigbTagUp, hSigbTagDown, "WH120", "bTag", cat_);
      canSig->cd(4);
      c_SigbTag->DrawClonePad();
      TCanvas * c_SigPileup = compareMjjOneSys(hSig, hSigPileupUp, hSigPileupDown, "WH120", "Pileup", cat_);
      canSig->cd(5);
      c_SigPileup->DrawClonePad();
      TCanvas * c_SigtopPt = compareMjjOneSys(hSig, hSigtopPtUp, hSigtopPtDown, "WH120", "topPt", cat_);
      canSig->cd(6);
      c_SigtopPt->DrawClonePad();
      TString outSig("MjjShapeSig/");
      mkdir(outSig, S_IRWXU);
      outSig += TString("mjj_"+intToStr(index)+"_"+catName[index -1])+".pdf";
      canSig->SaveAs(outSig);
    }
    if(isSig && isGraph){//Graph
      TCanvas *canSigGraph = new TCanvas();
      canSigGraph->Divide(3, 2);
      TCanvas * c_SigJES = compareRatioGraph(hSig, hSigJESUp, hSigJESDown, "WH120", "JES", cat_);
      canSigGraph->cd(1);
      c_SigJES->DrawClonePad();
      TCanvas * c_SigJER =compareRatioGraph(hSig, hSigJERUp, hSigJERDown, "WH120", "JER", cat_);
      canSigGraph->cd(2);
      c_SigJER->DrawClonePad();
      TCanvas * c_SigcTag = compareRatioGraph(hSig, hSigcTagUp, hSigcTagDown, "WH120", "cTag", cat_);
      canSigGraph->cd(3);
      c_SigcTag->DrawClonePad();
      TCanvas * c_SigbTag = compareRatioGraph(hSig, hSigbTagUp, hSigbTagDown, "WH120", "bTag", cat_);
      canSigGraph->cd(4);
      c_SigbTag->DrawClonePad();
      TCanvas * c_SigPileup = compareRatioGraph(hSig, hSigPileupUp, hSigPileupDown, "WH120", "Pileup", cat_);
      canSigGraph->cd(5);
      c_SigPileup->DrawClonePad();
      TCanvas * c_SigtopPt = compareRatioGraph(hSig, hSigtopPtUp, hSigtopPtDown, "WH120", "topPt", cat_);
      canSigGraph->cd(6);
      c_SigtopPt->DrawClonePad();
      TString outSigGraph("MjjGraphSig/");
      mkdir(outSigGraph, S_IRWXU);
      outSigGraph += TString("mjj_"+intToStr(index)+"_"+catName[index -1])+".pdf";
      canSigGraph->SaveAs(outSigGraph);
    }
  }
  outFile.close();
} 



