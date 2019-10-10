// Gouranga Kole (UC San Diego)
// Usage
// .L compareLimit.C
// compareLimit("limit_csbar_.root", "Test1/limit_csbar_.root", "Test1", "Test2", true, false, 0.00, 0.06);

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


TGraphAsymmErrors* getLimit( TString dir, TString file, TString comment1, int histColor, bool exp, bool obs, Float_t yMin_ = 0.0, Float_t yMax_ = 0.10){

  TFile f(dir+"/"+file,"READ");
  if(f.IsZombie() || f.IsZombie()){
    cout << "Cannot open file "<< endl;
    continue;
  }
  TGraphAsymmErrors* g1;
  if(exp) g1 = (TGraphAsymmErrors*)f.Get("expected");
  else if(obs) g1 = (TGraphAsymmErrors*)f.Get("observed");
  g1->SetMarkerColor(kRed);
  g1->SetMarkerStyle(1);
  //g1->SetMarkerSize(1.5);
  g1->SetLineColor(histColor);
  g1->SetLineWidth(3);

  g1->GetXaxis()->SetLimits(85,165);
  g1->GetYaxis()->SetTitleOffset(1.33);
  g1->SetMinimum(yMin_);
  g1->SetMaximum(yMax_);
  g1->GetXaxis()->SetTitle("m_{H^{+}} (GeV)");
  g1->GetYaxis()->SetTitle("95% CL limit for BR(t#rightarrow bH^{#pm})");
  cout<<comment1<<endl;
  return g1;
}

void compareLimit( ){
  TCanvas *c1 = new TCanvas("c1","",5,30,650,600);
  c1->SetGrid(0,0);
  c1->SetFillStyle(4000);
  c1->SetFillColor(10);
  c1->SetTicky();
  c1->SetObjectStat(0);
  
  TLegend* leg = new TLegend(0.19,0.60,0.46,0.85,NULL,"brNDC");
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);
  leg->SetFillColor(0);
  
  TGraphAsymmErrors* g11 = getLimit("cutSets_limits", "cutSet1_mjj_kfit_limit_ChargedHiggs_mu_13TeV.root", "cutSet1_CTagInc", 1, true, false, 0.0, 0.05);
  TGraphAsymmErrors* g21 = getLimit("cutSets_limits", "cutSet2_mjj_kfit_limit_ChargedHiggs_mu_13TeV.root", "cutSet2_CTagInc", 2, true, false, 0.0, 0.05);
  TGraphAsymmErrors* g31 = getLimit("cutSets_limits", "cutSet3_mjj_kfit_limit_ChargedHiggs_mu_13TeV.root", "cutSet3_CTagInc", 3, true, false, 0.0, 0.05);
  TGraphAsymmErrors* g41 = getLimit("cutSets_limits", "cutSet4_mjj_kfit_limit_ChargedHiggs_mu_13TeV.root", "cutSet4_CTagInc", 4, true, false, 0.0, 0.05);
  
  TGraphAsymmErrors* g12 = getLimit("cutSets_limits", "cutSet1_mjj_kfit_CTagL_limit_ChargedHiggs_mu_13TeV.root", "cutSet1_CTagL", 5, true, false, 0.0, 0.05);
  TGraphAsymmErrors* g22 = getLimit("cutSets_limits", "cutSet2_mjj_kfit_CTagL_limit_ChargedHiggs_mu_13TeV.root", "cutSet2_CTagL", 6, true, false, 0.0, 0.05);
  TGraphAsymmErrors* g32 = getLimit("cutSets_limits", "cutSet3_mjj_kfit_CTagL_limit_ChargedHiggs_mu_13TeV.root", "cutSet3_CTagL", 7, true, false, 0.0, 0.05);
  TGraphAsymmErrors* g42 = getLimit("cutSets_limits", "cutSet4_mjj_kfit_CTagL_limit_ChargedHiggs_mu_13TeV.root", "cutSet4_CTagL", 28, true, false, 0.0, 0.05);
  
  TGraphAsymmErrors* g13 = getLimit("cutSets_limits", "cutSet1_mjj_kfit_CTagM_limit_ChargedHiggs_mu_13TeV.root", "cutSet1_CTagM", 9, true, false, 0.0,  0.05);
  TGraphAsymmErrors* g23 = getLimit("cutSets_limits", "cutSet2_mjj_kfit_CTagM_limit_ChargedHiggs_mu_13TeV.root", "cutSet2_CTagM", 40, true, false, 0.0, 0.05);
  TGraphAsymmErrors* g33 = getLimit("cutSets_limits", "cutSet3_mjj_kfit_CTagM_limit_ChargedHiggs_mu_13TeV.root", "cutSet3_CTagM", 41, true, false, 0.0, 0.05);
  TGraphAsymmErrors* g43 = getLimit("cutSets_limits", "cutSet4_mjj_kfit_CTagM_limit_ChargedHiggs_mu_13TeV.root", "cutSet4_CTagM", 42, true, false, 0.0, 0.05);
  
  TGraphAsymmErrors* g14 = getLimit("cutSets_limits", "cutSet1_mjj_kfit_CTagT_limit_ChargedHiggs_mu_13TeV.root", "cutSet1_CTagT", 46, true, false, 0.0, 0.05);
  TGraphAsymmErrors* g24 = getLimit("cutSets_limits", "cutSet2_mjj_kfit_CTagT_limit_ChargedHiggs_mu_13TeV.root", "cutSet2_CTagT", 47, true, false, 0.0, 0.05);
  TGraphAsymmErrors* g34 = getLimit("cutSets_limits", "cutSet3_mjj_kfit_CTagT_limit_ChargedHiggs_mu_13TeV.root", "cutSet3_CTagT", 48, true, false, 0.0, 0.05);
  TGraphAsymmErrors* g44 = getLimit("cutSets_limits", "cutSet4_mjj_kfit_CTagT_limit_ChargedHiggs_mu_13TeV.root", "cutSet4_CTagT", 30, true, false, 0.0, 0.05);
  g11->Draw("ALP");
  g21->Draw("LPsame");
  g31->Draw("LPsame");
  g41->Draw("LPsame");
  
  g12->Draw("LPsame");
  g22->Draw("LPsame");
  g32->Draw("LPsame");
  g42->Draw("LPsame");
  
  g13->Draw("LPsame");
  g23->Draw("LPsame");
  g33->Draw("LPsame");
  g43->Draw("LPsame");
  
  g14->Draw("LPsame");
  g24->Draw("LPsame");
  g34->Draw("LPsame");
  g44->Draw("LPsame");
  
  c1->cd();
  gPad->Modified();
  //leg->SetHeader(Form("#splitline{CMS Preliminary #sqrt{s}=13 TeV}{35.5 fb^{-1}}"));
  
  leg->AddEntry(g11,"cutSet1_CTagInc","PL");
  leg->AddEntry(g21,"cutSet2_CTagInc","PL");
  leg->AddEntry(g31,"cutSet3_CTagInc","PL");
  leg->AddEntry(g41,"cutSet4_CTagInc","PL");
  
  leg->AddEntry(g12,"cutSet1_CTagL","PL");
  leg->AddEntry(g22,"cutSet2_CTagL","PL");
  leg->AddEntry(g32,"cutSet3_CTagL","PL");
  leg->AddEntry(g42,"cutSet4_CTagL","PL");
  
  leg->AddEntry(g13,"cutSet1_CTagM","PL");
  leg->AddEntry(g23,"cutSet2_CTagM","PL");
  leg->AddEntry(g33,"cutSet3_CTagM","PL");
  leg->AddEntry(g43,"cutSet4_CTagM","PL");
  
  leg->AddEntry(g14,"cutSet1_CTagT","PL");
  leg->AddEntry(g24,"cutSet2_CTagT","PL");
  leg->AddEntry(g34,"cutSet3_CTagT","PL");
  leg->AddEntry(g44,"cutSet4_CTagT","PL");
  leg->Draw();

  TPaveText *pl2 = new TPaveText(0.63,0.75,0.83,0.88, "brNDC");
  pl2->SetTextSize(0.032);
  pl2->SetFillColor(0);
  pl2->SetTextFont(132);
  pl2->SetBorderSize(0);
  pl2->SetTextAlign(11);
  pl2->AddText("t #rightarrow H^{#pm}b, H^{+} #rightarrow c#bar{s}");
  pl2->AddText("BR(H^{+} #rightarrow c#bar{s}) = 1");
  if(exp)pl2->AddText("Expected Limit");
  else if(obs)pl2->AddText("Observed Limit");
  //pl2->Draw();
  gPad->RedrawAxis();
}
