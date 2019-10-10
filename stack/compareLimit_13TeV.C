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
  g1->SetMarkerStyle(20);
  g1->SetMarkerSize(0.5);
  g1->SetLineColor(histColor);
  g1->SetLineWidth(3);
  //g1->SetTitle(comment1);
  g1->GetXaxis()->SetLimits(85,165);
  g1->GetYaxis()->SetTitleOffset(1.53);
  g1->SetTitle("");
  //g1->SetMinimum(yMin_);
  g1->GetYaxis()->SetRangeUser(0.5, 3);
  g1->SetMaximum(yMax_);
  g1->GetXaxis()->SetTitle("M_{H^{+}} (GeV)");
  //g1->GetYaxis()->SetTitle("95% CL limit for BR(t#rightarrow bH^{#pm})");
  g1->GetYaxis()->SetTitle("95% CL limit for BR(t#rightarrow bH^{#pm})");
  cout<<comment1<<endl;
  return g1;
}

void compareLimit_13TeV( ){
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
  TGraphAsymmErrors* g_mu1 = getLimit("../limit/mu/mjj_kfit","limit_mu_mjj_kfit.root", "mu+jets", 1, true, false, 0.0, 0.035);
  TGraphAsymmErrors* g_mu2 = getLimit("mu/mjj_CTagCat","limit_mu_mjj_CTagCat.root", "mu+jets", 2, true, false, 0.0, 0.035);
  TGraphAsymmErrors* g_mu3 = getLimit("mu/mjj_bJetPtCat","limit_mu_mjj_bJetPtCat.root", "mu+jets", 3, true, false, 0.0, 0.035);
  TGraphAsymmErrors* g_mu4 = getLimit("mu/mjj_CTagCat_bJetPtCat","limit_mu_mjj_CTagCat_bJetPtCat.root", "mu+jets", 4, true, false, 0.0, 0.035);
  TGraphAsymmErrors* g_mu5 = getLimit("../limit/mu/mjj_kfit_CTagL_SF","limit_mu_mjj_kfit_CTagL_SF.root", "mu+jets", kYellow +1, true, false, 0.0, 0.05);
  c1->cd(1);
  g_mu1->GetXaxis()->SetTitle("M_{H^{#pm}} (GeV)");
  //g_mu1->GetYaxis()->SetTitle("95% CL limit for BR(t#rightarrow bH^{#pm})"); 
  gStyle->SetFrameLineWidth(3);
  g_mu1->GetXaxis()->SetLimits(85,165);
  g_mu1->GetYaxis()->SetTitleOffset(1.15);
  g_mu1->GetXaxis()->SetNdivisions(5);
  g_mu1->GetXaxis()->SetTitleOffset(1.15);
  g_mu1->SetMinimum(0.);
  g_mu1->GetYaxis()->SetTitleSize(0.07);   g_mu1->GetXaxis()->SetTitleSize(0.08);
  g_mu1->GetXaxis()->SetLabelSize(0.07);   g_mu1->GetXaxis()->LabelsOption("u"); // extra
  g_mu1->GetYaxis()->SetLabelSize(0.07);   g_mu1->GetXaxis()->LabelsOption("u"); // extra
  g_mu1->GetXaxis()->SetTickLength(0.07);
  g_mu1->GetYaxis()->SetTickLength(0.04);
  g_mu1->GetYaxis()->SetTitleOffset(1.73);
  g_mu1->Draw("ALP");
  g_mu5->Draw("LPsame");
  g_mu2->Draw("LPsame");
  g_mu3->Draw("LPsame");
  g_mu4->Draw("LPsame");
  gPad->Modified();
  leg_mu->AddEntry(g_mu1,"mu+jets: M_{jj}","PL");
  leg_mu->AddEntry(g_mu5,"mu+jets: M_{jj}^{Inc_CTagL}","PL");
  leg_mu->AddEntry(g_mu2,"mu+jets: M_{jj}^{Ex_CTagL} + M_{jj}^{Ex_CTagM}+ M_{jj}^{Ex_CTagT}","PL");
  leg_mu->AddEntry(g_mu3,"mu+jets: M_{jj}(Pt_{bjet}^{Had} bins)","PL");
  leg_mu->AddEntry(g_mu4,"#splitline{mu+jets: M_{jj}^{Ex_CTagL}(Pt_{bjet}^{Had} bins)}{+ M_{jj}^{Ex_CTagM}(Pt_{bjet}^{Had} bins) + M_{jj}^{Ex_CTagT}(Pt_{bjet}^{Had} bins)}","PL");
  leg_mu->Draw();
  
  //electron channel 
  TGraphAsymmErrors* g_ele1 = getLimit("../limit/ele/mjj_kfit","limit_ele_mjj_kfit.root", "ele+jets", 6, true, false, 0.0, 0.035);
  TGraphAsymmErrors* g_ele2 = getLimit("ele/mjj_CTagCat","limit_ele_mjj_CTagCat.root", "ele+jets", 7, true, false, 0.0, 0.035);
  TGraphAsymmErrors* g_ele3 = getLimit("ele/mjj_bJetPtCat","limit_ele_mjj_bJetPtCat.root", "ele+jets", 29, true, false, 0.0, 0.035);
  TGraphAsymmErrors* g_ele4 = getLimit("ele/mjj_CTagCat_bJetPtCat","limit_ele_mjj_CTagCat_bJetPtCat.root", "ele+jets", 9, true, false, 0.0, 0.035);
  TGraphAsymmErrors* g_ele5 = getLimit("../limit/ele/mjj_kfit_CTagL_SF","limit_ele_mjj_kfit_CTagL_SF.root", "ele+jets", kRed +1, true, false, 0.0, 0.05);
  TLegend* leg_ele = new TLegend(0.30,0.40,0.60,0.85,NULL,"brNDC");
  leg_ele->SetBorderSize(0);
  leg_ele->SetTextSize(0.04);
  leg_ele->SetFillColor(0);
  c1->cd(2);
  g_ele1->GetXaxis()->SetLimits(85,165);
  g_ele1->GetYaxis()->SetTitleOffset(1.15);
  g_ele1->GetXaxis()->SetTitleOffset(1.15);
  g_ele1->GetXaxis()->SetNdivisions(5);
  g_ele1->SetMinimum(0.);
  g_ele1->GetYaxis()->SetTitleSize(0.07);   g_ele1->GetXaxis()->SetTitleSize(0.08);
  g_ele1->GetXaxis()->SetLabelSize(0.07);   g_ele1->GetXaxis()->LabelsOption("u"); // extra
  g_ele1->GetYaxis()->SetLabelSize(0.07);   g_ele1->GetXaxis()->LabelsOption("u"); // extra
  g_ele1->GetXaxis()->SetTickLength(0.07);
  g_ele1->GetYaxis()->SetTickLength(0.04);
  g_ele1->GetYaxis()->SetTitleOffset(1.73);
  g_ele1->Draw("ALP");
  g_ele5->Draw("LPsame");
  g_ele2->Draw("LPsame");
  g_ele3->Draw("LPsame");
  g_ele4->Draw("LPsame");
  gPad->Modified();
  leg_ele->AddEntry(g_ele1,"ele+jets: M_{jj}","PL");
  leg_ele->AddEntry(g_ele5,"ele+jets: M_{jj}^{Inc_CTagL}","PL");
  leg_ele->AddEntry(g_ele2,"ele+jets: M_{jj}^{Ex_CTagL} + M_{jj}^{Ex_CTagM}+ M_{jj}^{Ex_CTagT}","PL");
  leg_ele->AddEntry(g_ele3,"ele+jets: M_{jj}(Pt_{bjet}^{Had} bins)","PL");
  leg_ele->AddEntry(g_ele4,"#splitline{ele+jets: M_{jj}^{Ex_CTagL}(Pt_{bjet}^{Had} bins)}{+ M_{jj}^{Ex_CTagM}(Pt_{bjet}^{Had} bins)+ M_{jj}^{Ex_CTagT}(Pt_{bjet}^{Had} bins)}","PL");
  leg_ele->Draw();

  
  //lepton channel 
  TGraphAsymmErrors* g_lep1 = getLimit("../limit/mu_ele/mjj_kfit","limit_mu_ele_mjj_kfit.root", "mu_ele+jets", 12, true, false, 0.0, 0.035);
  TGraphAsymmErrors* g_lep2 = getLimit("mu_ele/mjj_CTagCat","limit_mu_ele_mjj_CTagCat.root", "mu_ele+jets", 22, true, false, 0.0, 0.035);
  TGraphAsymmErrors* g_lep3 = getLimit("mu_ele/mjj_bJetPtCat","limit_mu_ele_mjj_bJetPtCat.root", "mu_ele+jets", 32, true, false, 0.0, 0.035);
  TGraphAsymmErrors* g_lep4 = getLimit("mu_ele/mjj_CTagCat_bJetPtCat","limit_mu_ele_mjj_CTagCat_bJetPtCat.root", "mu_ele+jets", 42, true, false, 0.0, 0.035);
  TGraphAsymmErrors* g_lep5 = getLimit("../limit/mu_ele/mjj_kfit_CTagL_SF","limit_mu_ele_mjj_kfit_CTagL_SF.root", "mu_ele+jets", kRed +2, true, false, 0.0, 0.05);
  TLegend* leg_lep = new TLegend(0.30,0.40,0.60,0.85,NULL,"brNDC");
  leg_lep->SetBorderSize(0);
  leg_lep->SetTextSize(0.04);
  leg_lep->SetFillColor(0);
  c1->cd(3);
  g_lep1->GetXaxis()->SetLimits(85,165);
  g_lep1->GetYaxis()->SetTitleOffset(1.15);
  g_lep1->GetXaxis()->SetTitleOffset(1.15);
  g_lep1->GetXaxis()->SetNdivisions(5);
  g_lep1->SetMinimum(0.);
  g_lep1->GetYaxis()->SetTitleSize(0.07);   g_lep1->GetXaxis()->SetTitleSize(0.08);
  g_lep1->GetXaxis()->SetLabelSize(0.07);   g_lep1->GetXaxis()->LabelsOption("u"); // extra
  g_lep1->GetYaxis()->SetLabelSize(0.07);   g_lep1->GetXaxis()->LabelsOption("u"); // extra
  g_lep1->GetXaxis()->SetTickLength(0.07);
  g_lep1->GetYaxis()->SetTickLength(0.04);
  g_lep1->GetYaxis()->SetTitleOffset(1.73);
  g_lep1->Draw("ALP");
  g_lep5->Draw("LPsame");
  g_lep2->Draw("LPsame");
  g_lep3->Draw("LPsame");
  g_lep4->Draw("LPsame");
  gPad->Modified();
  leg_lep->AddEntry(g_lep1,"lep+jets: M_{jj}","PL");
  leg_lep->AddEntry(g_lep5,"lep+jets: M_{jj}^{Inc_CTagL}","PL");
  leg_lep->AddEntry(g_lep2,"lep+jets: M_{jj}^{Ex_CTagL} + M_{jj}^{Ex_CTagM}+ M_{jj}^{Ex_CTagT}","PL");
  leg_lep->AddEntry(g_lep3,"lep+jets: M_{jj}(Pt_{bjet}^{Had} bins)","PL");
  leg_lep->AddEntry(g_lep4,"#splitline{lep+jets: M_{jj}^{Ex_CTagL}(Pt_{bjet}^{Had} bins)}{ + M_{jj}^{Ex_CTagM}(Pt_{bjet}^{Had} bins)+ M_{jj}^{Ex_CTagT}(Pt_{bjet}^{Had} bins)}","PL");
  leg_lep->Draw();
  
  TLegend* leg_comb = new TLegend(0.30,0.32,0.60,0.90,NULL,"brNDC");
  leg_comb->SetBorderSize(0);
  leg_comb->SetTextSize(0.03);
  leg_comb->SetFillColor(0);
  c1->cd(4);
  g_mu1->Draw("ALP");
  g_mu2->Draw("LPsame");
  g_mu3->Draw("LPsame");
  g_mu4->Draw("LPsame");
  g_mu5->Draw("LPsame");
  g_ele1->Draw("LPsame");
  g_ele2->Draw("LPsame");
  g_ele3->Draw("LPsame");
  g_ele4->Draw("LPsame");
  g_ele5->Draw("LPsame");
  g_lep1->Draw("LPsame");
  g_lep2->Draw("LPsame");
  g_lep3->Draw("LPsame");
  g_lep4->Draw("LPsame");
  g_lep5->Draw("LPsame");
  gPad->Modified();
  leg_comb->AddEntry(g_mu1,"mu+jets: M_{jj}","PL");
  leg_comb->AddEntry(g_mu2,"mu+jets: M_{jj}^{Ex_CTagL} + M_{jj}^{Ex_CTagM}+ M_{jj}^{Ex_CTagT}","PL");
  leg_comb->AddEntry(g_mu3,"mu+jets: M_{jj}(Pt_{bjet}^{Had} bins)","PL");
  leg_comb->AddEntry(g_mu4,"mu+jets: M_{jj}^{Ex_CTagL}(Pt_{bjet}^{Had} bins) + M_{jj}^{Ex_CTagM}(Pt_{bjet}^{Had} bins)+ M_{jj}^{Ex_CTagT}(Pt_{bjet}^{Had} bins)","PL");
  leg_comb->AddEntry(g_mu5,"mu+jets: M_{jj}^{Inc_CTagL}","PL");
  leg_comb->AddEntry(g_ele1,"ele+jets: M_{jj}","PL");
  leg_comb->AddEntry(g_ele2,"ele+jets: M_{jj}^{Ex_CTagL} + M_{jj}^{Ex_CTagM}+ M_{jj}^{Ex_CTagT}","PL");
  leg_comb->AddEntry(g_ele3,"ele+jets: M_{jj}(Pt_{bjet}^{Had} bins)","PL");
  leg_comb->AddEntry(g_ele4,"ele+jets: M_{jj}^{Ex_CTagL}(Pt_{bjet}^{Had} bins) + M_{jj}^{Ex_CTagM}(Pt_{bjet}^{Had} bins)+ M_{jj}^{Ex_CTagT}(Pt_{bjet}^{Had} bins)","PL");
  leg_comb->AddEntry(g_ele5,"ele+jets: M_{jj}^{Inc_CTagL}","PL");
  leg_comb->AddEntry(g_lep1,"lep+jets: M_{jj}","PL");
  leg_comb->AddEntry(g_lep2,"lep+jets: M_{jj}^{Ex_CTagL} + M_{jj}^{Ex_CTagM}+ M_{jj}^{Ex_CTagT}","PL");
  leg_comb->AddEntry(g_lep3,"lep+jets: M_{jj}(Pt_{bjet}^{Had} bins)","PL");
  leg_comb->AddEntry(g_lep4,"lep+jets: M_{jj}^{Ex_CTagL}(Pt_{bjet}^{Had} bins) + M_{jj}^{Ex_CTagM}(Pt_{bjet}^{Had} bins)+ M_{jj}^{Ex_CTagT}(Pt_{bjet}^{Had} bins)","PL");
  leg_comb->AddEntry(g_lep5,"lep+jets: M_{jj}^{Inc_CTagL}","PL");
  leg_comb->Draw();
  
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
  c1->SaveAs("comb_overlay.pdf");
  //c1->Close();
}

void compareLimit2_13TeV( ){
  gStyle->SetFrameLineWidth(3);
  TCanvas *c1 = new TCanvas("c1","",5,30,950,900);
  c1->SetGridy();
  gPad->SetLogy();
  c1->SetFillStyle(4000);
  c1->SetFillColor(10);
  c1->SetTicky();
  c1->SetObjectStat(0);
  
  TGraphAsymmErrors* g_mu1 = getLimit("../limit/mu/mjj_kfit","limit_mu_mjj_kfit.root", "mu+jets", 1, true, false, 0.0, 0.035);
  TGraphAsymmErrors* g_mu2 = getLimit("mu/mjj_bJetPtCat","limit_mu_mjj_bJetPtCat.root", "mu+jets", 3, true, false, 0.0, 0.035);
  TGraphAsymmErrors* g_mu3 = getLimit("../limit/mu/mjj_kfit_CTagL_SF","limit_mu_mjj_kfit_CTagL_SF.root", "mu+jets", kYellow +1, true, false, 0.0, 0.05);
  TGraphAsymmErrors* g_mu4 = getLimit("mu/mjj_CTagCat","limit_mu_mjj_CTagCat.root", "mu+jets", 2, true, false, 0.0, 0.035);
  TGraphAsymmErrors* g_mu5 = getLimit("mu/mjj_CTagCat_bJetPtCat","limit_mu_mjj_CTagCat_bJetPtCat.root", "mu+jets", 4, true, false, 0.0, 0.035);

  //electron channel 
  TGraphAsymmErrors* g_ele1 = getLimit("../limit/ele/mjj_kfit","limit_ele_mjj_kfit.root", "ele+jets", 6, true, false, 0.0, 0.035);
  TGraphAsymmErrors* g_ele2 = getLimit("ele/mjj_bJetPtCat","limit_ele_mjj_bJetPtCat.root", "ele+jets", 29, true, false, 0.0, 0.035);
  TGraphAsymmErrors* g_ele3 = getLimit("../limit/ele/mjj_kfit_CTagL_SF","limit_ele_mjj_kfit_CTagL_SF.root", "ele+jets", kRed +1, true, false, 0.0, 0.05);
  TGraphAsymmErrors* g_ele4 = getLimit("ele/mjj_CTagCat","limit_ele_mjj_CTagCat.root", "ele+jets", 7, true, false, 0.0, 0.035);
  TGraphAsymmErrors* g_ele5 = getLimit("ele/mjj_CTagCat_bJetPtCat","limit_ele_mjj_CTagCat_bJetPtCat.root", "ele+jets", 9, true, false, 0.0, 0.035);
  
  //lepton channel 
  TGraphAsymmErrors* g_lep1 = getLimit("../limit/mu_ele/mjj_kfit","limit_mu_ele_mjj_kfit.root", "mu_ele+jets", 12, true, false, 0.0, 0.035);
  TGraphAsymmErrors* g_lep2 = getLimit("mu_ele/mjj_bJetPtCat","limit_mu_ele_mjj_bJetPtCat.root", "mu_ele+jets", 32, true, false, 0.0, 0.035);
  TGraphAsymmErrors* g_lep3 = getLimit("../limit/mu_ele/mjj_kfit_CTagL_SF","limit_mu_ele_mjj_kfit_CTagL_SF.root", "mu_ele+jets", kRed +2, true, false, 0.0, 0.05);
  TGraphAsymmErrors* g_lep4 = getLimit("mu_ele/mjj_CTagCat","limit_mu_ele_mjj_CTagCat.root", "mu_ele+jets", 22, true, false, 0.0, 0.035);
  TGraphAsymmErrors* g_lep5 = getLimit("mu_ele/mjj_CTagCat_bJetPtCat","limit_mu_ele_mjj_CTagCat_bJetPtCat.root", "mu_ele+jets", 42, true, false, 0.0, 0.035);
  
  g_mu1->Draw("ALP");
  g_mu2->Draw("LPsame");
  g_mu3->Draw("LPsame");
  g_mu4->Draw("LPsame");
  g_mu5->Draw("LPsame");
  g_ele1->Draw("LPsame");
  g_ele2->Draw("LPsame");
  g_ele3->Draw("LPsame");
  g_ele4->Draw("LPsame");
  g_ele5->Draw("LPsame");
  g_lep1->Draw("LPsame");
  g_lep2->Draw("LPsame");
  g_lep3->Draw("LPsame");
  g_lep4->Draw("LPsame");
  g_lep5->Draw("LPsame");

  TLegend* leg_comb = new TLegend(0.15,0.15,0.85,0.38,NULL,"brNDC");
  leg_comb->SetBorderSize(0);
  leg_comb->SetTextSize(0.03);
  leg_comb->SetFillColor(0);
  leg_comb->SetNColumns(2);
  leg_comb->AddEntry(g_mu1,"#mu + jets: M_{jj}(Inc)","PL");
  leg_comb->AddEntry(g_mu2,"#mu + jets: M_{jj}(pt_{bjet}^{Had} bins)","PL");
  leg_comb->AddEntry(g_mu3,"#mu + jets: M_{jj}(Inc CTagL","PL");
  leg_comb->AddEntry(g_mu4,"#mu + jets: M_{jj}(Ex CTag)","PL");

  leg_comb->AddEntry(g_ele1,"e + jets: M_{jj}(Inc)","PL");
  leg_comb->AddEntry(g_ele2,"e + jets: M_{jj}(pt_{bjet}^{Had} bins)","PL");
  leg_comb->AddEntry(g_ele3,"e + jets: M_{jj}(Inc CTagL","PL");
  leg_comb->AddEntry(g_ele4,"e + jets: M_{jj}(Ex CTag)","PL");

  leg_comb->AddEntry(g_lep1,"l + jets: M_{jj}(Inc)","PL");
  leg_comb->AddEntry(g_lep2,"l + jets: M_{jj}(pt_{bjet}^{Had} bins)","PL");
  leg_comb->AddEntry(g_lep3,"l + jets: M_{jj}(Inc CTagL","PL");
  leg_comb->AddEntry(g_lep4,"l + jets: M_{jj}(Ex CTag)","PL");
  leg_comb->Draw();

  TLegend* leg_comb_2 = new TLegend(0.40,0.40,0.70,0.55,NULL,"brNDC");
  leg_comb_2->SetBorderSize(0);
  leg_comb_2->SetTextSize(0.03);
  leg_comb_2->SetFillColor(0);
  leg_comb_2->AddEntry(g_mu5,"#mu + jets: M_{jj}(Ex CTag(pt_{bjet}^{Had} bins))","PL");
  leg_comb_2->AddEntry(g_ele5,"e + jets: M_{jj}(Ex CTag(pt_{bjet}^{Had} bins))","PL");
  leg_comb_2->AddEntry(g_lep5,"l + jets: M_{jj}(Ex CTag(pt_{bjet}^{Had} bins))","PL");
  leg_comb_2->Draw();
  //pave text CMS box
  TPaveText *pt = new TPaveText(0.20,0.9354,0.90,0.9362, "brNDC"); // good_v1
  pt->SetBorderSize(1);
  pt->SetFillColor(19);
  pt->SetFillStyle(0);
  pt->SetTextSize(0.07);
  pt->SetLineColor(0);
  pt->SetTextFont(132);
  TText *text = pt->AddText("#sqrt{s}=13 TeV, 35.9 fb^{-1} ");
  //TText *text = pt->AddText(dir+":  CMS Preliminary,    #sqrt{s} = 13 TeV,    35.45 fb^{-1}; ");
  text->SetTextAlign(11);
  pt->Draw();
  
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
  c1->SaveAs("comb_overlay.pdf");
  //c1->Close();
}
