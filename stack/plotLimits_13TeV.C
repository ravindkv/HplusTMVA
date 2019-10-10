
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
//#include <algorithm>
//#include <iostream>
//#include <string>
//#include <vector>
//#include "TH1F.h"
//#include "TFile.h"
//#include "TStyle.h"
//#include "TCanvas.h"
//#include "TLegend.h"
//#include "TMath.h"

using namespace std;


void plot( TString dir  = "$PWD",
	   TString cutSet = "cutSet",	
	   TString histDir  = "mjj_kfit", 
	   TString stream  = "MuT", 
	   TString channel = "BSM", TString save_tag = "",
	   TString legend  = "#c_{#mu}#s-bar",
	   Float_t xMax_   = 50, bool obs = false, bool rootfile = false )
{
  
  gStyle->SetFrameLineWidth(3);
  TCanvas *c1 = new TCanvas();
  gPad->SetLogy();
  c1->SetGrid(0,0);
  c1->SetFillStyle(4000);
  c1->SetFillColor(10);
  c1->SetTicky();
  c1->SetObjectStat(0);
  TLegend* leg = new TLegend(0.34,0.67,0.50,0.87,NULL,"brNDC");
  leg->SetBorderSize(0);
  leg->SetTextSize(0.05);
  leg->SetFillColor(0);


  float X[]        = {90,100,120, 140, 150, 155, 160};
  float obsY[]     = {0.,0.,0, 0, 0, 0, 0,0};
  float expY[]     = {0.,0.,0, 0, 0, 0, 0,0};
		      
  float expX1sL[]  = {0.,0.,0, 0, 0, 0, 0,0};
  float expX1sH[]  = {0.,0.,0, 0, 0, 0, 0,0};
  float expY1sL[]  = {0.,0.,0, 0, 0, 0, 0,0};
  float expY1sH[]  = {0.,0.,0, 0, 0, 0, 0,0};
  float expY1sL_[]  = {0.,0.,0, 0, 0, 0, 0,0};
  float expY1sH_[]  = {0.,0.,0, 0, 0, 0, 0,0};
		      
  float expX2sL[]  = {0.,0.,0, 0, 0, 0, 0,0};
  float expX2sH[]  = {0.,0.,0, 0, 0, 0, 0,0};
  float expY2sL[]  = {0.,0.,0, 0, 0, 0, 0,0};
  float expY2sH[]  = {0.,0.,0, 0, 0, 0, 0,0};

  int nMassPoints = 7;
  TString massFiles [7] = {"higgsCombineChargedHiggs_CHANNEL_HIST.Asymptotic.mH90.root",
  "higgsCombineChargedHiggs_CHANNEL_HIST.Asymptotic.mH100.root",
  "higgsCombineChargedHiggs_CHANNEL_HIST.Asymptotic.mH120.root",
  "higgsCombineChargedHiggs_CHANNEL_HIST.Asymptotic.mH140.root",
  "higgsCombineChargedHiggs_CHANNEL_HIST.Asymptotic.mH150.root",
  "higgsCombineChargedHiggs_CHANNEL_HIST.Asymptotic.mH155.root",
  "higgsCombineChargedHiggs_CHANNEL_HIST.Asymptotic.mH160.root"};

  for(unsigned int i = 0 ; i < nMassPoints; i++){
    cout<<dir+"/"+histDir+"/"<<endl;
    TFile f(dir+"/"+histDir+"/"+massFiles[i],"READ"); // higgsCombineChargedHiggs_mu.Asymptotic.mH140.root
    //TFile f(Form(dir+"/"+histDir+"/"+"higgsCombine%s_%s.Asymptotic.mH%.0f.root",stream.Data(),channel.Data(),X[i]),"READ");
    if(f.IsZombie()){
      cout << "Cannot open file for " << string(channel.Data()) << " and mass " << X[i] << endl;
      continue;
    }
    Double_t r;
    TTree* limit = (TTree*)f.Get("limit");
    limit->SetBranchAddress("limit",&r);

    for(int k = 0 ; k< limit->GetEntries() ; k++){
      limit->GetEntry(k);
      if(k==0) expY2sL[i] = r;
      if(k==1) expY1sL[i] = r;
      if(k==1) expY1sL_[i] = r;
      if(k==2) expY[i]    = r;
      if(k==3) expY1sH[i] = r;
      if(k==3) expY1sH_[i] = r;
      if(k==4) expY2sH[i] = r;
      if(k==5) obsY[i]    = r;
    }
  }
  cout<<std::setprecision(4)<<endl;
  cout<<"Mass:"<<setw(15)<<"base value"<<setw(15)<<"-2 #sigma"<<setw(15)<<"-1 #sigma"<<setw(15)<<"+1 #sigma"<<setw(15)<<"+2 #sigma"<<endl; 
  for(int i1 = 0 ; i1 < nMassPoints ; i1++){
  cout<<X[i1]<<setw(15)<<expY[i1]<<setw(15)<<expY2sL[i1]<<setw(15)<< expY1sL[i1]<<setw(15)<<expY1sH[i1]<<setw(15)<<expY2sH[i1]<<endl; 
    expY1sH[i1] = TMath::Abs(expY1sH[i1]-expY[i1]);
    expY1sL[i1] = TMath::Abs(expY1sL[i1]-expY[i1]);
    expY2sH[i1] = TMath::Abs(expY2sH[i1]-expY[i1]);
    expY2sL[i1] = TMath::Abs(expY2sL[i1]-expY[i1]);
  //cout<<setw(10)<<X[i1]<<setw(15)<<expY[i1]<<setw(15)<<expY2sL[i1]<<setw(15)<< expY1sL[i1]<<setw(15)<<expY1sH[i1]<<setw(15)<<expY2sH[i1]<<endl; 
  }

  for(int i1 = 0 ; i1 < nMassPoints ; i1++){
    expY1sH_[i1] = 100*TMath::Abs(expY1sH_[i1]-expY[i1]);
    expY1sL_[i1] = 100*TMath::Abs(expY1sL_[i1]-expY[i1]);
    cout<<"$"<<std::setprecision(2)<<100*expY[i1]<<"^{+"<<expY1sH_[i1]<<"}"<<"_"<<"{-"<< expY1sL_[i1]<<"}"<<"$"<<endl;
    cout<<endl;
  }
  
  TMultiGraph *mg = new TMultiGraph();
  TString ch_name = "ch";
  cout<<legend<<endl;
  if(legend=="mu") ch_name = "#mu";
  if(legend=="ele") ch_name = "e";
  if(legend=="mu_ele") ch_name = "lep";
  //mg->SetTitle(ch_name + " + jets");
  //mg->SetTitle(cutSet+histDir);
  //mg->GetYaxis()->SetRangeUser()
  //mg->SetMinimum(0.0001);
  mg->SetMaximum(xMax_);
  TGraphAsymmErrors* expected = new TGraphAsymmErrors(nMassPoints, X, expY, expX1sL ,expX1sL , expX1sL, expX1sL);
  
  TGraphAsymmErrors* oneSigma = new TGraphAsymmErrors(nMassPoints, X, expY, expX1sL, expX1sL,  expY1sL, expY1sH);
  TGraphAsymmErrors* twoSigma = new TGraphAsymmErrors(nMassPoints, X, expY, expX2sL, expX2sL,  expY2sL, expY2sH);
  TGraphAsymmErrors* observed = new TGraphAsymmErrors(nMassPoints, X, obsY, expX1sL ,expX1sL , expX1sL, expX1sL);

 
  oneSigma->SetMarkerColor(kBlack);
  oneSigma->SetMarkerStyle(kFullCircle);
  oneSigma->SetFillColor(kGreen +2);
  oneSigma->SetFillStyle(1001);

  twoSigma->SetMarkerColor(kBlack);
  twoSigma->SetMarkerStyle(kFullCircle);
  twoSigma->SetFillColor(kYellow +2);
  twoSigma->SetFillStyle(1001);

  expected->SetMarkerColor(kBlack);
  expected->SetMarkerStyle(kFullCircle);
  expected->SetMarkerSize(0.0);
  expected->SetLineColor(kBlack);
  expected->SetLineWidth(2);

  observed->SetMarkerColor(kBlue);
  observed->SetMarkerStyle(20);
  observed->SetLineColor(kBlue);
  observed->SetLineStyle(2);
  observed->SetLineWidth(4);
  
  mg->Add(twoSigma);
  mg->Add(oneSigma);
  mg->Add(expected);
  if(obs) mg->Add(observed);

  mg->Draw("ALP3");
  gPad->Modified();
  gPad->SetBottomMargin(0.22);
  gPad->SetLeftMargin(0.18);
  gPad->SetGridy();
  gPad->SetRightMargin(0.05);
  gStyle->SetFrameLineWidth(3);
  mg->GetXaxis()->SetLimits(85,165);
  mg->GetYaxis()->SetTitleOffset(1.30);
  //mg->GetYaxis()->SetNdivisions(10);
  mg->GetXaxis()->SetTitleOffset(1.15);
  //mg->SetMinimum(0.);
  mg->SetMaximum(xMax_);
  mg->GetXaxis()->SetTitle("M_{H^{#pm}} (GeV)");
  mg->GetYaxis()->SetTitle("95% CL limit for BR(t#rightarrow bH^{#pm})"); 
  mg->GetYaxis()->SetTitleSize(0.07);   mg->GetXaxis()->SetTitleSize(0.08);
  mg->GetXaxis()->SetLabelSize(0.07);   mg->GetXaxis()->LabelsOption("u"); // extra
  mg->GetYaxis()->SetLabelSize(0.07);   mg->GetXaxis()->LabelsOption("u"); // extra
  mg->GetXaxis()->SetTickLength(0.07);
  mg->GetYaxis()->SetTickLength(0.04);
  
  //leg->SetHeader(Form("#splitline{CMS Preliminary #sqrt{s}=13 TeV}{ LUMI fb^{-1}, %s}",legend.Data()));
  leg->AddEntry(expected,"Expected","L");
  if(obs) leg->AddEntry(observed,"Observed","L");
  leg->AddEntry(oneSigma, "#pm 1 #sigma","F");
  leg->AddEntry(twoSigma, "#pm 2 #sigma","F");

  TPaveText *pl2 = new TPaveText(0.64,0.67,0.75,0.87, "brNDC");
  pl2->SetTextSize(0.052);
  pl2->SetFillColor(0);
  pl2->SetTextFont(132);
  pl2->SetBorderSize(0);
  pl2->SetTextAlign(11);
  pl2->AddText("t #rightarrow H^{#pm}b,");
  pl2->AddText("H^{+} #rightarrow c#bar{s}");
  pl2->AddText("BR(H^{+} #rightarrow c#bar{s}) = 1");
  //pl2->AddText("2 CSVM b-tag ");
  //pl2->AddText("1 CSVT c-tag");
  //pl2->AddText(channel.Data());
  //pl2->AddText(legend.Data());
  
  //pave text CMS box
  TPaveText *pt = new TPaveText(0.20,0.9354,0.90,0.9362, "brNDC"); // good_v1
  pt->SetBorderSize(1);
  pt->SetFillColor(19);
  pt->SetFillStyle(0);
  pt->SetTextSize(0.08);
  pt->SetLineColor(0);
  pt->SetTextFont(132);
  TText *text = pt->AddText("#sqrt{s}=13 TeV, 35.9 fb^{-1} ");
  //TText *text = pt->AddText(dir+":  CMS Preliminary,    #sqrt{s} = 13 TeV,    35.45 fb^{-1}; ");
  text->SetTextAlign(11);
  
  //pave text channel box
  TPaveText *ch = new TPaveText(1.00,0.9154898,0.7510067,0.9762187,"brNDC");
  ch->SetFillColor(19);
  ch->SetFillStyle(0);
  ch->SetLineColor(0);
  ch->SetTextSize(0.08);
  ch->SetBorderSize(1);
  if(legend=="mu")ch->AddText("#mu + jets");
  if(legend=="ele") ch->AddText("e + jets");
  if(legend=="mu_ele") ch->AddText("l + jets");
  pl2->Draw("SAME");
  pt->Draw("SAME");
  ch->Draw("SAME");
  leg->Draw("SAME");

  TF1 *line = new TF1("line","1",100,150);
  line->SetLineColor(kRed);
  line->SetLineWidth(2);

  line->Draw("SAME");
  //gPad->RedrawAxis();
  TString outFile = "limit_CHANNEL_HIST";
  c1->SaveAs(outFile+".png");
  if(rootfile){
    TFile *fout = new TFile(outFile+".root", "RECREATE");
    expected->Write("expected");
    observed->Write("observed");
    oneSigma->Write("oneSigma");
    twoSigma->Write("twoSigma");
    fout->Close();
  }

}

void plotLimits_13TeV(){
  /*
  TCanvas *c1 = new TCanvas();
  gStyle->SetFrameLineWidth(3);
  gPad->SetLogy(true);
  c1->SetFillStyle(4000);
  c1->SetFillColor(10);
  c1->SetTicky();
  c1->SetObjectStat(0);
  //c1->Divide(2, 2);
  //c1->cd(1);
  */
  plot("HISTDIR", "", "HISTNAME", "ChargedHiggs", "CHANNELNAME", "13TeV", "CHANNELNAME", 0.10, false, true);
  /*
  c1->cd(2);
  plot("stack_20171115_Mu_sys", "", "pt_bjetH", "ChargedHiggs","electron","13TeV","mu+jets",0.1, true, true);
  c1->cd(3);
  plot("stack_20171115_Mu_sys", "", "comb_mjj_kfit_pt_bjetH", "ChargedHiggs","electron","13TeV","mu+jets",0.03, true, true);
  //c1->cd(4);
  //plot("stack_20171115_Mu_sys", "", "mjj_kfit_CTagT", "ChargedHiggs","electron","13TeV","mu+jets",0.03, false, true);
  */
}

















