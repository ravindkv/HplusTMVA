
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


TGraphAsymmErrors* getLimit( TString dir, TString file, TString comment1, int histColor, bool exp, bool isObs, Float_t yMin_ = 0.0, Float_t yMax_ = 0.10){

  TFile f(dir+"/"+file,"READ");
  if(f.IsZombie() || f.IsZombie()){
    cout << "Cannot open file "<< endl;
    //continue;
  }
  TGraphAsymmErrors* g1;
  if(isObs) g1 = (TGraphAsymmErrors*)f.Get("observed");
  else g1 = (TGraphAsymmErrors*)f.Get("expected");
  g1->SetMarkerColor(kRed);
  g1->SetMarkerStyle(20);
  g1->SetMarkerSize(0.5);
  g1->SetLineColor(histColor);
  g1->SetLineWidth(3);
  g1->GetYaxis()->SetNdivisions(10);
  g1->GetYaxis()->SetMoreLogLabels(true);
  //g1->SetTitle(comment1);
  g1->GetXaxis()->SetLimits(75,165);
  g1->GetYaxis()->SetTitleOffset(1.53);
  g1->SetTitle("");
  g1->SetMinimum(yMin_);
  //g1->GetYaxis()->SetRangeUser(0.5, 3);
  g1->SetMaximum(yMax_);
  g1->GetXaxis()->SetTitle("m_{H^{+}} (GeV)");
  g1->GetXaxis()->SetTitleSize(0.05);
  g1->GetYaxis()->SetTitleSize(0.05);
  //g1->GetYaxis()->SetTitle("95% CL limit for BR(t#rightarrow bH^{#pm})");
  g1->GetYaxis()->SetTitle("95% CL limit for BR(t#rightarrow H^{+}b)");
  cout<<comment1<<endl;
  return g1;
}

void compareLimit_13TeV(bool isObs=true){
  TCanvas *c1 = new TCanvas("c1","",5,30,950,900);
  c1->SetGrid(0,0);
  c1->SetFillStyle(4000);
  c1->SetFillColor(10);
  c1->SetTicky();
  c1->SetObjectStat(0);
  c1->Divide(2,2);
  //muon channel 
  TLegend* leg_mu = new TLegend(0.30,0.40,0.60,0.85,NULL,"brNDC");
  //leg->SetHeader(Form("#splitline{CMS Preliminary #sqrt{s}=13 TeV}{35.5 fb^{-1}}"));
  leg_mu->SetBorderSize(0);
  leg_mu->SetTextSize(0.04);
  leg_mu->SetFillColor(0);
  TGraphAsymmErrors* g_mu1 = getLimit("limit/mu/Cat1_Inc","limit_mu_Cat1_Inc.root", "mu+jets", 1, true, isObs, 0.0, 0.1);
  TGraphAsymmErrors* g_mu2 = getLimit("limit/mu/Cat2_cTagInc","limit_mu_Cat2_cTagInc.root", "mu+jets", 2, true, isObs, 0.0, 0.1);
  TGraphAsymmErrors* g_mu3 = getLimit("limit/mu/Cat3_cTagEx","limit_mu_Cat3_cTagEx.root", "mu+jets", 3, true, isObs, 0.0, 0.1);
  c1->cd(1);
  g_mu1->GetXaxis()->SetTitle("m_{H^{#pm}} (GeV)");
  //g_mu1->GetYaxis()->SetTitle("95% CL limit for BR(t#rightarrow bH^{#pm})"); 
  gStyle->SetFrameLineWidth(3);
  g_mu1->GetXaxis()->SetLimits(85,165);
  g_mu1->GetYaxis()->SetTitleOffset(1.15);
  //g_mu1->GetXaxis()->SetNdivisions(5);
  g_mu1->GetXaxis()->SetTitleOffset(1.15);
  g_mu1->SetMinimum(0.);
  g_mu1->GetYaxis()->SetTitleSize(0.07);   g_mu1->GetXaxis()->SetTitleSize(0.08);
  g_mu1->GetXaxis()->SetLabelSize(0.07);   g_mu1->GetXaxis()->LabelsOption("u"); // extra
  g_mu1->GetYaxis()->SetLabelSize(0.07);   g_mu1->GetXaxis()->LabelsOption("u"); // extra
  g_mu1->GetXaxis()->SetTickLength(0.07);
  g_mu1->GetYaxis()->SetTickLength(0.04);
  g_mu1->GetYaxis()->SetTitleOffset(1.73);
  g_mu1->GetYaxis()->SetMoreLogLabels(true);
  if(isObs){
    g_mu1->Draw("ALP3");
    g_mu2->Draw("ALP3same");
    g_mu3->Draw("ALP3same");
  }
  else{
    g_mu1->Draw("ALP");
    g_mu2->Draw("LPsame");
    g_mu3->Draw("LPsame");
  }
  gPad->Modified();
  leg_mu->AddEntry(g_mu1,"mu+jets: m_{jj}^{Inc}","PL");
  leg_mu->AddEntry(g_mu2,"mu+jets: m_{jj}^{Inc_CTagL}","PL");
  leg_mu->AddEntry(g_mu3,"mu+jets: m_{jj}^{Ex_CTag}","PL");
  leg_mu->Draw();
  
  //electron channel 
  TGraphAsymmErrors* g_ele1 = getLimit("limit/ele/Cat1_Inc","limit_ele_Cat1_Inc.root", "ele+jets", 1, true, isObs, 0.0, 0.1);
  TGraphAsymmErrors* g_ele2 = getLimit("limit/ele/Cat2_cTagInc","limit_ele_Cat2_cTagInc.root", "ele+jets", 2, true, isObs, 0.0, 0.1);
  TGraphAsymmErrors* g_ele3 = getLimit("limit/ele/Cat3_cTagEx","limit_ele_Cat3_cTagEx.root", "ele+jets", 3, true, isObs, 0.0, 0.1);
  TLegend* leg_ele = new TLegend(0.30,0.40,0.60,0.85,NULL,"brNDC");
  leg_ele->SetBorderSize(0);
  leg_ele->SetTextSize(0.04);
  leg_ele->SetFillColor(0);
  c1->cd(2);
  g_ele1->GetXaxis()->SetLimits(85,165);
  g_ele1->GetYaxis()->SetTitleOffset(1.15);
  g_ele1->GetXaxis()->SetTitleOffset(1.15);
  ///g_ele1->GetXaxis()->SetNdivisions(5);
  g_ele1->SetMinimum(0.);
  g_ele1->GetYaxis()->SetTitleSize(0.07);   g_ele1->GetXaxis()->SetTitleSize(0.08);
  g_ele1->GetXaxis()->SetLabelSize(0.07);   g_ele1->GetXaxis()->LabelsOption("u"); // extra
  g_ele1->GetYaxis()->SetLabelSize(0.07);   g_ele1->GetXaxis()->LabelsOption("u"); // extra
  g_ele1->GetXaxis()->SetTickLength(0.07);
  g_ele1->GetYaxis()->SetTickLength(0.04);
  g_ele1->GetYaxis()->SetTitleOffset(1.73);
  if(isObs){
    g_ele1->Draw("ALP3");
    g_ele2->Draw("ALP3same");
    g_ele3->Draw("ALP3same");
  }
  else{
    g_ele1->Draw("ALP");
    g_ele2->Draw("LPsame");
    g_ele3->Draw("LPsame");
  }
  gPad->Modified();
  leg_ele->AddEntry(g_ele1,"ele+jets: m_{jj}^{Inc}","PL");
  leg_ele->AddEntry(g_ele2,"ele+jets: m_{jj}^{Inc_CTagL}","PL");
  leg_ele->AddEntry(g_ele3,"ele+jets: m_{jj}^{Ex_CTag}","PL");
  leg_ele->Draw();

  
  //lepton channel 
  TGraphAsymmErrors* g_lep1 = getLimit("limit/mu_ele/Cat1_Inc","limit_mu_ele_Cat1_Inc.root", "lep+jets", 1, true, isObs, 0.0, 0.1);
  TGraphAsymmErrors* g_lep2 = getLimit("limit/mu_ele/Cat2_cTagInc","limit_mu_ele_Cat2_cTagInc.root", "lep+jets", 2, true, isObs, 0.0, 0.1);
  TGraphAsymmErrors* g_lep3 = getLimit("limit/mu_ele/Cat3_cTagEx","limit_mu_ele_Cat3_cTagEx.root", "lep+jets", 3, true, isObs, 0.0, 0.1);
  TLegend* leg_lep = new TLegend(0.30,0.40,0.60,0.85,NULL,"brNDC");
  leg_lep->SetBorderSize(0);
  leg_lep->SetTextSize(0.04);
  leg_lep->SetFillColor(0);
  c1->cd(3);
  g_lep1->GetXaxis()->SetLimits(85,165);
  g_lep1->GetYaxis()->SetTitleOffset(1.15);
  g_lep1->GetXaxis()->SetTitleOffset(1.15);
  ///g_lep1->GetXaxis()->SetNdivisions(5);
  g_lep1->SetMinimum(0.);
  g_lep1->GetYaxis()->SetTitleSize(0.07);   g_lep1->GetXaxis()->SetTitleSize(0.08);
  g_lep1->GetXaxis()->SetLabelSize(0.07);   g_lep1->GetXaxis()->LabelsOption("u"); // extra
  g_lep1->GetYaxis()->SetLabelSize(0.07);   g_lep1->GetXaxis()->LabelsOption("u"); // extra
  g_lep1->GetXaxis()->SetTickLength(0.07);
  g_lep1->GetYaxis()->SetTickLength(0.04);
  g_lep1->GetYaxis()->SetTitleOffset(1.73);
  if(isObs){
    g_lep1->Draw("ALP3");
    g_lep2->Draw("ALP3same");
    g_lep3->Draw("ALP3same");
  }
  else{
    g_lep1->Draw("ALP");
    g_lep2->Draw("LPsame");
    g_lep3->Draw("LPsame");
  }
  gPad->Modified();
  leg_lep->AddEntry(g_lep1,"lep+jets: m_{jj}^{Inc}","PL");
  leg_lep->AddEntry(g_lep2,"lep+jets: m_{jj}^{Inc_CTagL}","PL");
  leg_lep->AddEntry(g_lep3,"lep+jets: m_{jj}^{Ex_CTag}","PL");
  leg_lep->Draw();
  
  TLegend* leg_comb = new TLegend(0.30,0.32,0.60,0.90,NULL,"brNDC");
  leg_comb->SetBorderSize(0);
  leg_comb->SetTextSize(0.03);
  leg_comb->SetFillColor(0);
  c1->cd(4);
  if(isObs){
    g_mu1->Draw("ALP3");
    g_mu2->Draw("ALP3same");
    g_mu3->Draw("ALP3same");
    g_ele1->Draw("ALP3same");
    g_ele2->Draw("ALP3same");
    g_ele3->Draw("ALP3same");
    g_lep1->Draw("ALP3same");
    g_lep2->Draw("ALP3same");
    g_lep3->Draw("ALP3same");
  }
  else{
    g_mu1->Draw("ALP");
    g_mu2->Draw("LPsame");
    g_mu3->Draw("LPsame");
    g_ele1->Draw("LPsame");
    g_ele2->Draw("LPsame");
    g_ele3->Draw("LPsame");
    g_lep1->Draw("LPsame");
    g_lep2->Draw("LPsame");
    g_lep3->Draw("LPsame");
  }
  gPad->Modified();
  if(isObs){
    leg_comb->AddEntry(g_mu1,"mu+jets: m_{jj}^{Inc}","ALP");
    leg_comb->AddEntry(g_mu2,"mu+jets: m_{jj}^{Inc_CTagL}","ALP");
    leg_comb->AddEntry(g_mu3,"mu+jets: m_{jj}^{Ex_CTag}","ALP");
    leg_comb->AddEntry(g_ele1,"ele+jets  m_{jj}^{Inc}","ALP");
    leg_comb->AddEntry(g_ele2,"ele+jets: m_{jj}^{Inc_CTagL}","ALP");
    leg_comb->AddEntry(g_ele3,"ele+jets: m_{jj}^{Ex_CTag}","ALP");
    leg_comb->AddEntry(g_lep1,"lep+jets: m_{jj}^{Inc}","ALP");
    leg_comb->AddEntry(g_lep2,"lep+jets: m_{jj}^{Inc_CTagL}","ALP");
    leg_comb->AddEntry(g_lep3,"lep+jets: m_{jj}^{Ex_CTag}","ALP");
  }
  else{
    leg_comb->AddEntry(g_mu1,"mu+jets: m_{jj}^{Inc}","PL");
    leg_comb->AddEntry(g_mu2,"mu+jets: m_{jj}^{Inc_CTagL}","PL");
    leg_comb->AddEntry(g_mu3,"mu+jets: m_{jj}^{Ex_CTag}","PL");
    leg_comb->AddEntry(g_ele1,"ele+jets: m_{jj}^{Inc}","PL");
    leg_comb->AddEntry(g_ele2,"ele+jets: m_{jj}^{Inc_CTagL}","PL");
    leg_comb->AddEntry(g_ele3,"ele+jets: m_{jj}^{Ex_CTag}","PL");
    leg_comb->AddEntry(g_lep1,"lep+jets: m_{jj}^{Inc}","PL");
    leg_comb->AddEntry(g_lep2,"lep+jets: m_{jj}^{Inc_CTagL}","PL");
    leg_comb->AddEntry(g_lep3,"lep+jets: m_{jj}^{Ex_CTag}","PL");
  }
  leg_comb->Draw();
  
  TPaveText *pl2 = new TPaveText(0.63,0.75,0.83,0.88, "brNDC");
  pl2->SetTextSize(0.032);
  pl2->SetFillColor(0);
  pl2->SetTextFont(132);
  pl2->SetBorderSize(0);
  pl2->SetTextAlign(11);
  pl2->AddText("t #rightarrow H^{#pm}b, H^{+} #rightarrow c#bar{s}");
  pl2->AddText("BR(H^{+} #rightarrow c#bar{s}) = 1");
  if(isObs)pl2->AddText("Observed Limit");
  pl2->AddText("Expected Limit");
  //pl2->Draw();
  gPad->RedrawAxis();
  c1->SaveAs("comb_overlay.pdf");
  //c1->Close();
}

void MyCompareLimits(bool isObs=false){
  gStyle->SetFrameLineWidth(3);
  TCanvas *c1 = new TCanvas("c1","",5,30,950,900);
  c1->SetGridy();
  gPad->SetLogy();
  c1->SetFillStyle(4000);
  c1->SetFillColor(10);
  c1->SetTicky();
  c1->SetObjectStat(0);

  gPad->SetLeftMargin(0.15);
  gPad->SetRightMargin(0.05);
  gPad->SetBottomMargin(0.15);
  double yMin = 0.003;
  if(isObs) yMin = 0.0012;
  double yMax = 0.1;  
  TGraphAsymmErrors* g_mu1 = getLimit("limit/mu/Cat1_Inc","limit_mu_Cat1_Inc.root", "mu+jets", 1, true, isObs, yMin, yMax);
  TGraphAsymmErrors* g_mu2 = getLimit("limit/mu/Cat2_cTagInc","limit_mu_Cat2_cTagInc.root", "mu+jets", 3, true, isObs, yMin, yMax);
  TGraphAsymmErrors* g_mu3 = getLimit("limit/mu/Cat3_cTagEx","limit_mu_Cat3_cTagEx.root", "mu+jets", kYellow+1, true, isObs, yMin, yMax);

  //electron channel 
  TGraphAsymmErrors* g_ele1 = getLimit("limit/ele/Cat1_Inc","limit_ele_Cat1_Inc.root", "ele+jets", 6, true, isObs, yMin, yMax);
  TGraphAsymmErrors* g_ele2 = getLimit("limit/ele/Cat2_cTagInc","limit_ele_Cat2_cTagInc.root", "ele+jets", 29, true, isObs, yMin, yMax);
  TGraphAsymmErrors* g_ele3 = getLimit("limit/ele/Cat3_cTagEx","limit_ele_Cat3_cTagEx.root", "ele+jets", kRed+1, true, isObs, yMin, yMax);
  
  //lepton channel 
  TGraphAsymmErrors* g_lep1 = getLimit("limit/mu_ele/Cat1_Inc","limit_mu_ele_Cat1_Inc.root", "lep+jets", kCyan, true, isObs, yMin, yMax);
  TGraphAsymmErrors* g_lep2 = getLimit("limit/mu_ele/Cat2_cTagInc","limit_mu_ele_Cat2_cTagInc.root", "lep+jets", 39, true, isObs, yMin, yMax);
  TGraphAsymmErrors* g_lep3 = getLimit("limit/mu_ele/Cat3_cTagEx","limit_mu_ele_Cat3_cTagEx.root", "lep+jets", kBlue, true, isObs, yMin, yMax);
  if(isObs){
    g_mu1->SetMarkerSize(1.0); 
    g_mu2->SetMarkerSize(1.0); 
    g_mu3->SetMarkerSize(1.0); 
    g_ele1->SetMarkerSize(1.0); 
    g_ele2->SetMarkerSize(1.0); 
    g_ele3->SetMarkerSize(1.0); 
    g_lep1->SetMarkerSize(1.0); 
    g_lep2->SetMarkerSize(1.0); 
    g_lep3->SetMarkerSize(1.0); 
    g_mu1->SetMarkerColor(1); 
    g_mu2->SetMarkerColor(3); 
    g_mu3->SetMarkerColor(kYellow+1); 
    g_ele1->SetMarkerColor(6); 
    g_ele2->SetMarkerColor(29); 
    g_ele3->SetMarkerColor(kRed+1); 
    g_lep1->SetMarkerColor(kCyan); 
    g_lep2->SetMarkerColor(39); 
    g_lep3->SetMarkerColor(kBlue);
  }
  if(isObs){ 
    g_mu1->Draw("ALP3");
    g_mu2->Draw("LP3same");
    g_mu3->Draw("LP3same");
    g_ele1->Draw("LP3same");
    g_ele2->Draw("LP3same");
    g_ele3->Draw("LP3same");
    g_lep1->Draw("LP3same");
    g_lep2->Draw("LP3same");
    g_lep3->Draw("LP3same");
  }
  else{
    g_mu1->Draw("AL");
    g_mu2->Draw("Lsame");
    g_mu3->Draw("Lsame");
    g_ele1->Draw("Lsame");
    g_ele2->Draw("Lsame");
    g_ele3->Draw("Lsame");
    g_lep1->Draw("Lsame");
    g_lep2->Draw("Lsame");
    g_lep3->Draw("Lsame");
  }

  TLegend* leg_comb = new TLegend(0.50,0.45,0.80,0.85,NULL,"brNDC");
  //TLegend* leg_comb = new TLegend(0.30,0.65,0.90,0.85,NULL,"brNDC");
  leg_comb->SetBorderSize(0);
  leg_comb->SetTextSize(0.03);
  leg_comb->SetFillColor(0);
  //leg_comb->SetNColumns(2);
  if(isObs){
    leg_comb->AddEntry(g_mu1,"#mu+jets: Cat1(Inc)","LP");
    leg_comb->AddEntry(g_mu2,"#mu+jets: Cat2(Inc CTagL)","LP");
    leg_comb->AddEntry(g_mu3,"#mu+jets: Cat3(Ex CTag)","LP");
    leg_comb->AddEntry(g_ele1,"e+jets: Cat1(Inc)","LP");
    leg_comb->AddEntry(g_ele2,"e+jets: Cat2(Inc CTagL)","LP");
    leg_comb->AddEntry(g_ele3,"e+jets: Cat3(Ex CTag)","LP");
    leg_comb->AddEntry(g_lep1,"l+jets: Cat1(Inc)","LP");
    leg_comb->AddEntry(g_lep2,"l+jets: Cat2(Inc CTagL)","LP");
    leg_comb->AddEntry(g_lep3,"l+jets: Cat3(Ex CTag)","LP");
  }
  else{
    leg_comb->AddEntry(g_mu1,"#mu+jets: Cat1(Inc)","L");
    leg_comb->AddEntry(g_mu2,"#mu+jets: Cat2(Inc CTagL)","L");
    leg_comb->AddEntry(g_mu3,"#mu+jets: Cat3(Ex CTag)","L");
    leg_comb->AddEntry(g_ele1,"e+jets: Cat1(Inc)","L");
    leg_comb->AddEntry(g_ele2,"e+jets: Cat2(Inc CTagL)","L");
    leg_comb->AddEntry(g_ele3,"e+jets: Cat3(Ex CTag)","L");
    leg_comb->AddEntry(g_lep1,"l+jets: Cat1(Inc)","L");
    leg_comb->AddEntry(g_lep2,"l+jets: Cat2(Inc CTagL)","L");
    leg_comb->AddEntry(g_lep3,"l+jets: Cat3(Ex CTag)","L");
  }
  leg_comb->Draw();

  //pave text CMS box
  TPaveText *pt = new TPaveText(0.15,0.9354,0.80,0.9362, "brNDC"); // good_v1
  pt->SetBorderSize(1);
  pt->SetFillColor(19);
  pt->SetFillStyle(0);
  pt->SetTextSize(0.04);
  pt->SetLineColor(0);
  pt->SetTextFont(132);
  //TText *text = pt->AddText("#sqrt{s}=13 TeV, 35.9 fb^{-1} ");
  TText *text = pt->AddText("CMS Preliminary,    #sqrt{s} = 13 TeV,    35.9 fb^{-1}");
  text->SetTextAlign(11);
  pt->Draw();
  
  TPaveText *pl2 = new TPaveText(0.63,0.75,0.83,0.88, "brNDC");
  pl2->SetTextSize(0.032);
  pl2->SetFillColor(0);
  pl2->SetTextFont(132);
  pl2->SetBorderSize(0);
  pl2->SetTextAlign(11);
  pl2->AddText("t #rightarrow H^{+}b, H^{+} #rightarrow c#bar{s}");
  pl2->AddText("BR(H^{+} #rightarrow c#bar{s}) = 1");
  if(isObs)pl2->AddText("Observed Limit");
  pl2->AddText("Expected Limit");
  //pl2->Draw();
  gPad->RedrawAxis();
  if(isObs)c1->SaveAs("limit/all_limits_observed.pdf");
  else c1->SaveAs("limit/all_limits_expected.pdf");
  //c1->Close();
}
