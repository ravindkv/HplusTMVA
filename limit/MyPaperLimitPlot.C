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

void LimitPlotter(TString CHANNEL="mu", TString CAT= "Cat1_Inc",
         bool obs= false, bool isOut= true )
  {
  gStyle->SetFrameLineWidth(3);
  
  int nMassPoints = 7;
  float X[]        = {90,100,120, 140, 150, 155, 160};
  float obsY[]     = {0.,0.,0, 0, 0, 0, 0,0};
  float expY[]     = {0.,0.,0, 0, 0, 0, 0,0};
		      
  float expX1sL[]   = {0.,0.,0, 0, 0, 0, 0,0};
  float expX1sH[]   = {0.,0.,0, 0, 0, 0, 0,0};
  float expY1sL[]   = {0.,0.,0, 0, 0, 0, 0,0};
  float expY1sH[]   = {0.,0.,0, 0, 0, 0, 0,0};
		      
  float expX2sL[]  = {0.,0.,0, 0, 0, 0, 0,0};
  float expX2sH[]  = {0.,0.,0, 0, 0, 0, 0,0};
  float expY2sL[]  = {0.,0.,0, 0, 0, 0, 0,0};
  float expY2sH[]  = {0.,0.,0, 0, 0, 0, 0,0};

  //-------------------------------------------
  // 8 TeV limits
  //-------------------------------------------
  float limit8TeV_obsY[]     = {6.5, 1.4, 1.2, 1.5, 2.1, 1.9, 2.0};
  float limit8TeV_expY2sL[]  = {1.9, 0.9, 0.6, 0.6, 0.5, 0.7, 0.6};
  float limit8TeV_expY1sL[]  = {2.6, 1.2, 0.8, 0.7, 0.7, 0.9, 1.0};
  float limit8TeV_expY[]     = {3.6, 1.8, 1.2, 1.1, 1.0, 1.3, 1.4};
  float limit8TeV_expY1sH[]  = {5.3, 2.3, 1.8, 1.4, 1.4, 1.9, 2.2};
  float limit8TeV_expY2sH[]  = {7.3, 3.4, 2.4, 2.0, 2.0, 2.6, 3.6};
  for(int i1 = 0 ; i1 < nMassPoints ; i1++){
    limit8TeV_expY1sH[i1] = TMath::Abs(limit8TeV_expY1sH[i1]-limit8TeV_expY[i1]);
    limit8TeV_expY1sL[i1] = TMath::Abs(limit8TeV_expY1sL[i1]-limit8TeV_expY[i1]);
    limit8TeV_expY2sH[i1] = TMath::Abs(limit8TeV_expY2sH[i1]-limit8TeV_expY[i1]);
    limit8TeV_expY2sL[i1] = TMath::Abs(limit8TeV_expY2sL[i1]-limit8TeV_expY[i1]);
  }
  TGraphAsymmErrors* limit8TeV_exp = new TGraphAsymmErrors(7, X, limit8TeV_expY, expX1sL ,expX1sL , expX1sL, expX1sL);
  TGraphAsymmErrors* limit8TeV_1s = new TGraphAsymmErrors(7, X, limit8TeV_expY,  expX1sL, expX1sL,  limit8TeV_expY1sL, limit8TeV_expY1sH);
  TGraphAsymmErrors* limit8TeV_2s = new TGraphAsymmErrors(7, X, limit8TeV_expY,  expX2sL, expX2sL,  limit8TeV_expY2sL, limit8TeV_expY2sH);
  TGraphAsymmErrors* limit8TeV_obs = new TGraphAsymmErrors(7, X, limit8TeV_obsY, expX1sL ,expX1sL , expX1sL, expX1sL);
  //1s
  limit8TeV_1s->SetFillColor(kGreen+1);
  limit8TeV_1s->SetFillStyle(1001);
  //2s
  limit8TeV_2s->SetFillColor(kOrange);
  limit8TeV_2s->SetFillStyle(1001);
  //median
  limit8TeV_exp->SetLineColor(kBlue);
  limit8TeV_exp->SetLineWidth(2);
  limit8TeV_exp->SetLineStyle(2);
  limit8TeV_exp->SetLineWidth(4);
  //obs
  limit8TeV_obs->SetMarkerColor(kBlack);
  limit8TeV_obs->SetMarkerStyle(20);
  limit8TeV_obs->SetMarkerSize(1.0);
  limit8TeV_obs->SetLineColor(kBlack);
  limit8TeV_obs->SetLineWidth(4);

  //-------------------------------------------
  // 13 TeV limits
  //-------------------------------------------
  TString ch_hist = CHANNEL+"_"+CAT;
  TString massFiles [7] = {
  "Mass90/higgsCombine_hcs_13TeV_"+ch_hist+".AsymptoticLimits.mH90.root",
  "Mass100/higgsCombine_hcs_13TeV_"+ch_hist+".AsymptoticLimits.mH100.root",
  "Mass120/higgsCombine_hcs_13TeV_"+ch_hist+".AsymptoticLimits.mH120.root",
  "Mass140/higgsCombine_hcs_13TeV_"+ch_hist+".AsymptoticLimits.mH140.root",
  "Mass150/higgsCombine_hcs_13TeV_"+ch_hist+".AsymptoticLimits.mH150.root",
  "Mass155/higgsCombine_hcs_13TeV_"+ch_hist+".AsymptoticLimits.mH155.root",
  "Mass160/higgsCombine_hcs_13TeV_"+ch_hist+".AsymptoticLimits.mH160.root"};
  
  for(unsigned int i = 0 ; i < nMassPoints; i++){
    TFile f("limit/"+CHANNEL+"/"+CAT+"/"+massFiles[i],"READ"); 
    if(f.IsZombie()){
      cout << "Cannot open file for " << string(CHANNEL.Data()) << " and mass " << X[i] << endl;
      continue;
    }
    Double_t r;
    TTree* limit = (TTree*)f.Get("limit");
    limit->SetBranchAddress("limit",&r);
    for(int k = 0 ; k< limit->GetEntries() ; k++){
      limit->GetEntry(k);
      r = r*100;
      if(k==0) expY2sL[i] = r;
      if(k==1) expY1sL[i] = r;
      if(k==2) expY[i]    = r;
      if(k==3) expY1sH[i] = r;
      if(k==4) expY2sH[i] = r;
      if(k==5) obsY[i]    = r;
    }
  }
  for(int i1 = 0 ; i1 < nMassPoints ; i1++){
  //cout<<X[i1]<<setw(15)<<expY[i1]<<setw(15)<<expY2sL[i1]<<setw(15)<< expY1sL[i1]<<setw(15)<<expY1sH[i1]<<setw(15)<<expY2sH[i1]<<endl; 
    expY1sH[i1] = TMath::Abs(expY1sH[i1]-expY[i1]);
    expY1sL[i1] = TMath::Abs(expY1sL[i1]-expY[i1]);
    expY2sH[i1] = TMath::Abs(expY2sH[i1]-expY[i1]);
    expY2sL[i1] = TMath::Abs(expY2sL[i1]-expY[i1]);
  //cout<<setw(10)<<X[i1]<<setw(15)<<expY[i1]<<setw(15)<<expY2sL[i1]<<setw(15)<< expY1sL[i1]<<setw(15)<<expY1sH[i1]<<setw(15)<<expY2sH[i1]<<endl; 
  }
  
  TGraphAsymmErrors* expected = new TGraphAsymmErrors(nMassPoints, X, expY, expX1sL ,expX1sL , expX1sL, expX1sL);
  TGraphAsymmErrors* oneSigma = new TGraphAsymmErrors(nMassPoints, X, expY, expX1sL, expX1sL,  expY1sL, expY1sH);
  TGraphAsymmErrors* twoSigma = new TGraphAsymmErrors(nMassPoints, X, expY, expX2sL, expX2sL,  expY2sL, expY2sH);
  TGraphAsymmErrors* observed = new TGraphAsymmErrors(nMassPoints, X, obsY, expX1sL ,expX1sL , expX1sL, expX1sL);

  //1s
  oneSigma->SetFillColor(kGreen+1);
  oneSigma->SetFillStyle(1001);
  //2s
  twoSigma->SetFillColor(kOrange);
  twoSigma->SetFillStyle(1001);
  //median
  expected->SetLineColor(kBlue);
  expected->SetLineWidth(2);
  expected->SetLineStyle(2);
  expected->SetLineWidth(4);
  //obs
  observed->SetMarkerColor(kBlack);
  observed->SetMarkerStyle(20);
  observed->SetMarkerSize(1.0);
  observed->SetLineColor(kBlack);
  observed->SetLineWidth(4);

  //canvas
  TCanvas *c1 = new TCanvas("can", "can", 800, 900);
  c1->SetGrid(0,0);
  c1->SetFillStyle(4000);
  c1->SetFillColor(10);
  c1->SetTicky();
  c1->SetObjectStat(0);
  gPad->Modified();
  gPad->SetBottomMargin(0.13);
  gPad->SetLeftMargin(0.18);
  gPad->SetLogy();
  //gPad->SetGridy();
  gPad->SetRightMargin(0.05);
  c1->cd();

  //add graphs from 8 and 13 TeV
  TMultiGraph *mg = new TMultiGraph();
  mg->SetMaximum(10);
  //add all in one
  //mg->Add(limit8TeV_2s);
  //mg->Add(limit8TeV_1s);
  mg->Add(limit8TeV_exp);
  mg->Add(limit8TeV_obs);
  mg->Add(twoSigma);
  mg->Add(oneSigma);
  mg->Add(expected);
  mg->Add(observed);

  mg->Draw("ALP3");
  //decorate graph
  mg->GetXaxis()->SetLimits(85,165);
  mg->GetYaxis()->SetTitleOffset(1.30);
  mg->GetYaxis()->SetNdivisions(6);
  mg->GetXaxis()->SetTitleOffset(1.00);
  mg->GetXaxis()->SetTitle("M_{H^{#pm}} (GeV)");
  mg->GetYaxis()->SetTitle("BR(t#rightarrow bH^{#pm})"); 
  mg->GetYaxis()->SetTitleSize(0.06);   
  mg->GetXaxis()->SetTitleSize(0.06);
  mg->GetXaxis()->SetLabelSize(0.05);   
  mg->GetYaxis()->SetLabelSize(0.05);   
  //mg->GetYaxis()->CenterTitle();
  //mg->GetXaxis()->SetTickLength(0.06);
  //mg->GetYaxis()->SetTickLength(0.04);

  //Legends
  TLegend* leg = new TLegend(0.60,0.67,0.80,0.87,NULL,"brNDC");
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);
  leg->SetFillColor(0);
  leg->SetHeader("95% CL upper limits");
  leg->AddEntry(limit8TeV_obs,"Observed","EP");
  leg->AddEntry(limit8TeV_exp,"Median expected","L");
  leg->AddEntry(limit8TeV_1s, "68% expected","F");
  leg->AddEntry(limit8TeV_2s, "95% expected","F");
  leg->Draw();


  TString ch_name = "ch";
  cout<<CHANNEL<<endl;
  if(CHANNEL=="mu") ch_name = "#mu";
  if(CHANNEL=="ele") ch_name = "e";
  if(CHANNEL=="mu_ele") ch_name = "lep";

  
  //pave text lumi
  TPaveText *pt = new TPaveText(0.60,0.92,0.80,0.92, "brNDC"); // good_v1
  pt->SetBorderSize(1);
  pt->SetFillColor(19);
  pt->SetFillStyle(0);
  pt->SetTextSize(0.05);
  pt->SetLineColor(0);
  pt->SetTextFont(132);
  TText *text = pt->AddText("35.9 fb^{-1} (13 TeV)");
  text->SetTextAlign(11);
  
  //pave text channel box
  TPaveText *ch = new TPaveText(1.00,0.9154898,0.7510067,0.9762187,"brNDC");
  ch->SetFillColor(19);
  ch->SetFillStyle(0);
  ch->SetLineColor(0);
  ch->SetTextSize(0.08);
  ch->SetBorderSize(1);
  if(CHANNEL=="mu")ch->AddText("#mu + jets");
  if(CHANNEL=="ele") ch->AddText("e + jets");
  if(CHANNEL=="mu_ele") ch->AddText("l + jets");
  
  //cms box
  TPaveText *cms = new TPaveText(0.30,0.85,0.35,0.85,"brNDC");
  cms->SetFillColor(19);
  cms->SetFillStyle(0);
  cms->SetLineColor(0);
  cms->SetTextSize(0.05);
  cms->SetBorderSize(1);
  cms->AddText("CMS");
  cms->Draw("SAME");
  pt->Draw("SAME");
  //ch->Draw("SAME");
  
  gPad->RedrawAxis();
  TString outFile = "limit_"+CHANNEL+"_"+CAT;
  TString outDir = "limit/"+CHANNEL+"/"+CAT;
  gPad->SaveAs(outDir+"/"+outFile+".pdf");
}

void MyPaperLimitPlot(){
  /*
  LimitPlotter("mu", "Cat1_Inc",     true, true );
  LimitPlotter("mu", "Cat2_cTagInc", true, true );
  LimitPlotter("mu", "Cat3_cTagEx",  true, true );

  LimitPlotter("ele", "Cat1_Inc",     true, true );
  LimitPlotter("ele", "Cat2_cTagInc", true, true );
  LimitPlotter("ele", "Cat3_cTagEx",  true, true );

  LimitPlotter("mu_ele", "Cat1_Inc",     true, true );
  LimitPlotter("mu_ele", "Cat2_cTagInc", true, true );
  */
  LimitPlotter("mu_ele", "Cat3_cTagEx",  true, true );
}
