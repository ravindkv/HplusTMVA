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
    hist->Reset();
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


void plotSignificance(TH1F* hBkg, TH1F* hSig, TString sys, TString cat, TString SigM){
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
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);
  leg->SetFillColor(10);
  leg->SetTextSize(0.07);
  //  leg->SetHeader("#splitline{CMS Preliminary}{   @ #sqrt{s} = 7 TeV}");
  
  hSig->SetLineColor(kGreen);
  hSig->SetLineWidth(2);
  
  hBkg->SetLineColor(kBlue);
  hBkg->SetLineWidth(2);
  hBkg->SetTitle("");
  hBkg->GetYaxis()->SetTitle("Events");
  //hBkg->GetYaxis()->SetRangeUser(1, 1.2* hBkg->GetMaximum());
  //hBkg->GetXaxis()->SetNdivisions(5);
  //hBkg->GetYaxis()->SetNdivisions(5);
  hBkg->GetYaxis()->SetTitleOffset(1.00);
  hBkg->GetXaxis()->SetTitleOffset(1.00);
  hBkg->GetYaxis()->SetTitleSize(0.08);   
  hBkg->GetXaxis()->SetTitleSize(0.06);
  hBkg->GetXaxis()->SetLabelSize(0.06);   
  hBkg->GetYaxis()->SetLabelSize(0.06);   
  hBkg->GetXaxis()->SetTickLength(0.03); 
  hBkg->GetYaxis()->SetTickLength(0.03); 
  // legend adding
  leg->AddEntry(hSig, SigM,"LP");
  leg->AddEntry(hBkg,"AllBkg","LP");
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

  hBkg->GetXaxis()->SetTitle("M_{jj} [GeV]");
  hBkg->Draw("HIST");
  hSig->Draw("HISTSAME");
  leg->Draw();
  header->Draw();
  gPad->RedrawAxis();
  ////////////////////////////// Ratio //////////////////////////// 
  my_can->cd(2);
  gPad->SetPad(xpad[0],ypad[0],xpad[1],ypad[1]);
  gPad->SetTopMargin(0); gPad->SetBottomMargin(0.5); //gPad->SetGridy();
  gPad->SetLeftMargin(0.15);
  gPad->SetRightMargin(0.05);
  TH1F *hRatio = (TH1F*)hBkg->Clone("hRatio");
  hRatio->GetYaxis()->SetNdivisions(3);
  hRatio->Reset();
  hRatio->Add(hSig);
  hRatio->Divide(hBkg); hRatio->SetMarkerStyle(20); hRatio->SetMarkerSize(0.4);
  hRatio->SetMarkerColor(kRed); hRatio->SetLineColor(kRed); 
  hRatio->GetYaxis()->SetRangeUser(-0.1, 2);
  //hRatio->GetXaxis()->SetRangeUser(xmin, xmax);
  hRatio->GetXaxis()->SetTickLength(0.13); 
  hRatio->GetYaxis()->SetTickLength(0.04); 
  hRatio->GetXaxis()->SetTitle("M_{jj} [GeV]"); 
  hRatio->GetYaxis()->SetTitleOffset(0.50);
  hRatio->GetXaxis()->SetTitleOffset(1.10);
  hRatio->GetYaxis()->SetTitle("Ratio"); hRatio->GetYaxis()->CenterTitle();
  hRatio->GetYaxis()->SetTitleSize(0.15); hRatio->GetXaxis()->SetTitleSize(0.20);
  hRatio->GetXaxis()->SetLabelSize(0.20); 
  hRatio->GetYaxis()->SetLabelSize(0.15); 
  hRatio->Draw("E"); // use "P" or "AP"
  TF1 *baseLine = new TF1("baseLine","1", -100, 2000); 
  baseLine->SetLineColor(kBlack);
  my_can->SaveAs(sys);
}

void oneSignalSig(TString SigM){
  bool isSig = true;
  bool isBkg = true;
  bool isHist = true;
  std::vector<std::string> mjjFiles;
  mjjFiles.push_back("CTagCat/Shapes_hcs_13TeV_mu_KinFit_mjj_kfit_CTagL_SF_Cat.root"); 
  mjjFiles.push_back("CTagCat/Shapes_hcs_13TeV_mu_KinFit_mjj_kfit_CTagM_SF_Cat.root"); 
  mjjFiles.push_back("CTagCat/Shapes_hcs_13TeV_mu_KinFit_mjj_kfit_CTagT_SF_Cat.root"); 
  mjjFiles.push_back("CTagCat/Shapes_hcs_13TeV_ele_KinFit_mjj_kfit_CTagL_SF_Cat.root"); 
  mjjFiles.push_back("CTagCat/Shapes_hcs_13TeV_ele_KinFit_mjj_kfit_CTagM_SF_Cat.root"); 
  mjjFiles.push_back("CTagCat/Shapes_hcs_13TeV_ele_KinFit_mjj_kfit_CTagT_SF_Cat.root"); 
  std::vector<std::string> catName;
  catName.push_back("mu_ExCTagL"); 
  catName.push_back("mu_ExCTagM"); 
  catName.push_back("mu_ExCTagT"); 
  catName.push_back("ele_ExCTagL");
  catName.push_back("ele_ExCTagM"); 
  catName.push_back("ele_ExCTagT"); 
  //----------------------------------------
  // Loop over all  Mjj distributions
  //----------------------------------------
  std::vector<string>::iterator itr;
  int index = 0;
  for(itr = mjjFiles.begin(); itr!= mjjFiles.end(); itr++){
    string file_name = *itr;
    TFile *f = TFile::Open(file_name.c_str());
    TH1F *hSig = getHisto(f, SigM);
    TH1F* hBkg = getAllBkgHist(f, "");

    index++;
    TString cat_ = catName[index -1];
    TString outFile = TString("mjj_"+catName[index -1])+"_"+SigM+".pdf";
    plotSignificance(hBkg, hSig, outFile, cat_, SigM);
  }

  std::vector<std::string> mjjFilesCat2;
  mjjFilesCat2.push_back("bJetPtCat/Shapes_hcs_13TeV_mu_PtbJetInc_mjj_kfit_25To42.root"); 
  mjjFilesCat2.push_back("bJetPtCat/Shapes_hcs_13TeV_mu_PtbJetInc_mjj_kfit_42To57.root"); 
  mjjFilesCat2.push_back("bJetPtCat/Shapes_hcs_13TeV_mu_PtbJetInc_mjj_kfit_57To74.root"); 
  mjjFilesCat2.push_back("bJetPtCat/Shapes_hcs_13TeV_mu_PtbJetInc_mjj_kfit_74To99.root"); 
  mjjFilesCat2.push_back("bJetPtCat/Shapes_hcs_13TeV_mu_PtbJetInc_mjj_kfit_99To500.root"); 
  mjjFilesCat2.push_back("bJetPtCat/Shapes_hcs_13TeV_ele_PtbJetInc_mjj_kfit_25To42.root"); 
  mjjFilesCat2.push_back("bJetPtCat/Shapes_hcs_13TeV_ele_PtbJetInc_mjj_kfit_42To57.root"); 
  mjjFilesCat2.push_back("bJetPtCat/Shapes_hcs_13TeV_ele_PtbJetInc_mjj_kfit_57To74.root"); 
  mjjFilesCat2.push_back("bJetPtCat/Shapes_hcs_13TeV_ele_PtbJetInc_mjj_kfit_74To99.root"); 
  mjjFilesCat2.push_back("bJetPtCat/Shapes_hcs_13TeV_ele_PtbJetInc_mjj_kfit_99To500.root"); 

  std::vector<std::string> CatNameCat2;
  CatNameCat2.push_back("mu_25To42"); 
  CatNameCat2.push_back("mu_42To57"); 
  CatNameCat2.push_back("mu_57To74"); 
  CatNameCat2.push_back("mu_74To99");
  CatNameCat2.push_back("mu_99To500"); 
  CatNameCat2.push_back("ele_25To42"); 
  CatNameCat2.push_back("ele_42To57"); 
  CatNameCat2.push_back("ele_57To74"); 
  CatNameCat2.push_back("ele_74To99");
  CatNameCat2.push_back("ele_99To500"); 
  //----------------------------------------
  // Loop over all  Mjj distributions
  //----------------------------------------
  std::vector<string>::iterator itr;
  int index = 0;
  for(itr = mjjFilesCat2.begin(); itr!= mjjFilesCat2.end(); itr++){
    string file_name = *itr;
    TFile *f = TFile::Open(file_name.c_str());
    TH1F *hSig = getHisto(f, SigM);
    TH1F* hBkg = getAllBkgHist(f, "");

    index++;
    TString cat_ = CatNameCat2[index -1];
    TString outFile = TString("mjj_"+CatNameCat2[index -1])+"_"+SigM+".pdf";
    plotSignificance(hBkg, hSig, outFile, cat_, SigM);
  }
} 

TH1F * getRatioHist(TH1F* hist1, TH1F* hist2){
  TH1F * hRatio = (TH1F*)hist1->Clone("hRatio");
  hRatio->Divide(hist2);
  return hRatio;
}

TH1F * getSigBkgRatioHist(string inFile, TString SigM, int color){
  TFile * f = new TFile(inFile.c_str());
  //TFile * f = TFile::Open(inFile);
  TH1F * hSig = getHisto(f, SigM);
  TH1F * hBkg = getAllBkgHist(f, "");
  TH1F * hRatio = getRatioHist(hSig, hBkg);
  hRatio->SetLineColor(color);
  hRatio->SetLineWidth(2);
  return hRatio;
}

void oneSignalSigOverlay(TString SigM, int xMin, int yMax){
  gStyle->SetOptStat(0);
  std::vector<std::string> mjjFilesInc;
  mjjFilesInc.push_back("IncCat/Shapes_hcs_13TeV_mu_mjj_kfit.root");
  TH1F * hRatioInc = getSigBkgRatioHist(mjjFilesInc[0], SigM, 1);
  hRatioInc->GetYaxis()->SetRangeUser(0, yMax);
  hRatioInc->GetXaxis()->SetRangeUser(xMin, 170);
  hRatioInc->GetXaxis()->SetTitle("M_{jj} [GeV]"); 
  hRatioInc->GetYaxis()->SetTitleOffset(1.00);
  hRatioInc->GetXaxis()->SetTitleOffset(1.10);
  hRatioInc->GetYaxis()->SetTitle("S/B"); hRatioInc->GetYaxis()->CenterTitle();
  hRatioInc->GetYaxis()->SetTitleSize(0.07); 
  hRatioInc->GetXaxis()->SetTitleSize(0.06);
  hRatioInc->GetXaxis()->SetLabelSize(0.05); 
  hRatioInc->GetYaxis()->SetLabelSize(0.06); 

  std::vector<std::string> mjjFilesCat4;
  mjjFilesCat4.push_back("CTagCat/Shapes_hcs_13TeV_mu_KinFit_mjj_kfit_CTagL_SF_Cat.root"); 
  mjjFilesCat4.push_back("CTagCat/Shapes_hcs_13TeV_mu_KinFit_mjj_kfit_CTagM_SF_Cat.root"); 
  mjjFilesCat4.push_back("CTagCat/Shapes_hcs_13TeV_mu_KinFit_mjj_kfit_CTagT_SF_Cat.root"); 
  TH1F * hRatioCTagL = getSigBkgRatioHist(mjjFilesCat4[0], SigM, 433);
  TH1F * hRatioCTagM = getSigBkgRatioHist(mjjFilesCat4[1], SigM, 2);
  TH1F * hRatioCTagT = getSigBkgRatioHist(mjjFilesCat4[2], SigM, 3);

  std::vector<std::string> mjjFilesCat2;
  mjjFilesCat2.push_back("bJetPtCat/Shapes_hcs_13TeV_mu_PtbJetInc_mjj_kfit_25To42.root"); 
  mjjFilesCat2.push_back("bJetPtCat/Shapes_hcs_13TeV_mu_PtbJetInc_mjj_kfit_42To57.root"); 
  mjjFilesCat2.push_back("bJetPtCat/Shapes_hcs_13TeV_mu_PtbJetInc_mjj_kfit_57To74.root"); 
  mjjFilesCat2.push_back("bJetPtCat/Shapes_hcs_13TeV_mu_PtbJetInc_mjj_kfit_74To99.root"); 
  mjjFilesCat2.push_back("bJetPtCat/Shapes_hcs_13TeV_mu_PtbJetInc_mjj_kfit_99To500.root"); 
  TH1F * hRatio25To42 = getSigBkgRatioHist(mjjFilesCat2[0], SigM, 4);
  TH1F * hRatio42To57 = getSigBkgRatioHist(mjjFilesCat2[1], SigM, 5);
  TH1F * hRatio57To74 = getSigBkgRatioHist(mjjFilesCat2[2], SigM, 6);
  TH1F * hRatio74To99 = getSigBkgRatioHist(mjjFilesCat2[3], SigM, 7);
  TH1F * hRatio99To500 = getSigBkgRatioHist(mjjFilesCat2[4], SigM, 8);

  TCanvas *can = new TCanvas();
  can->Divide(2, 1);
  can->cd(1);
  gPad->SetBottomMargin(0.15); 
  gPad->SetLeftMargin(0.15);
  hRatioInc->Draw("HIST");
  hRatioCTagL->Draw("HISTsame");
  hRatioCTagM->Draw("HISTsame");
  hRatioCTagT->Draw("HISTsame");
  TLegend* legCTag= new TLegend(0.20,0.70,0.40,0.95,NULL,"brNDC");
  legCTag->AddEntry(hRatioInc, "Inc","LP");
  legCTag->AddEntry(hRatioCTagL, "ExCTagL","LP");
  legCTag->AddEntry(hRatioCTagM, "ExCTagM","LP");
  legCTag->AddEntry(hRatioCTagT, "ExCTagT","LP");
  legCTag->Draw();

  can->cd(2);
  gPad->SetBottomMargin(0.15); 
  gPad->SetLeftMargin(0.15);
  hRatioInc->Draw("HIST");
  hRatio25To42->Draw("HISTsame"); 
  hRatio42To57->Draw("HISTsame"); 
  hRatio57To74->Draw("HISTsame");
  hRatio74To99->Draw("HISTsame");
  hRatio99To500->Draw("HISTsame");
  TLegend* legCat2= new TLegend(0.20,0.70,0.40,0.95,NULL,"brNDC");
  legCat2->AddEntry(hRatioInc, "Inc","LP");
  legCat2->AddEntry(hRatio25To42, "25To42","LP");
  legCat2->AddEntry(hRatio42To57, "42To57","LP");
  legCat2->AddEntry(hRatio57To74, "57To74","LP");
  legCat2->AddEntry(hRatio74To99, "74To99","LP");
  legCat2->AddEntry(hRatio99To500, "99To500","LP");
  legCat2->Draw();
  can->SaveAs(SigM+".pdf");
} 

void signalSignificance(){
  oneSignalSigOverlay("WH80", 20,  2);
  oneSignalSigOverlay("WH90", 20,  2);
  oneSignalSigOverlay("WH100",20,  4);
  oneSignalSigOverlay("WH120",20,  6);
  oneSignalSigOverlay("WH140",100,  25);
  oneSignalSigOverlay("WH150",100,  30);
  oneSignalSigOverlay("WH155",100,  80);
  oneSignalSigOverlay("WH160",100,  250);

  /*
  oneSignalSig("WH80");
  oneSignalSig("WH90");
  oneSignalSig("WH100");
  oneSignalSig("WH120");
  oneSignalSig("WH140");
  oneSignalSig("WH150");
  oneSignalSig("WH155");
  oneSignalSig("WH160");
  */
}



