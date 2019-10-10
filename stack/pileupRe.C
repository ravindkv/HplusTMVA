#include "TH1F.h"
#include "TH3.h"
#include "TFile.h"
#include "TRandom1.h"
#include "TRandom2.h"
#include "TRandom3.h"
#include "TStopwatch.h"
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iostream>


void lumiRewt(TString dFilename, TString mcFilename, TH1F* hRatio, TH1F* mc_all, int color){
  TFile *dataF = new TFile(dFilename);
  TFile *mcF = new TFile(mcFilename);
  TH1F* data_hist;
  TH1F* mc_hist;
  
  //////////////////// Data - MC pileup distribution //////////////////////
  data_hist = new TH1F(*(static_cast<TH1F*>(dataF->Get("pileup" )->Clone(dFilename))));
  mc_hist = new TH1F(*(static_cast<TH1F*>(mcF->Get("pileup" )->Clone(mcFilename))));
  
  TH1F * data = new TH1F("data", "data", 600, 0, 60);
  TH1F * mc = new TH1F("mc", "mc", 600, 0, 60);
  for(int i=1; i<600; i++){
    double binCon1 = data_hist->GetBinContent(i);
    double binCon2 = mc_hist->GetBinContent(i);
    data->SetBinContent(i, binCon1);
    data->SetBinError(i, sqrt(binCon1));
    mc->SetBinContent(i, binCon2);
    mc->SetBinError(i, sqrt(binCon2));
      
  }

  TCanvas *c = new TCanvas(mcFilename, mcFilename);
  gStyle->SetOptStat(1111111);
  c->Divide(2,3);
  c->cd(1);
  c->SetLogy();
  data->SetLineWidth(1);
  data->SetMarkerStyle(23+color);
  data->SetMarkerSize(1.0);
  data->SetMarkerColor(color);
  data->SetXTitle("nvtx");
  data->SetLineColor(color);
  data->SetTitle(dFilename);
  data->Draw("e1");
  c->cd(2);
  
  mc_hist->SetLineWidth(1);
  mc_hist->SetMarkerStyle(23+color);
  mc_hist->SetMarkerSize(1.0);
  mc_hist->SetMarkerColor(color);
  mc_hist->SetLineColor(color);
  mc_hist->SetTitle(mcFilename);
  mc_hist->Draw("e1");
  
  //////////////////// Data, MC pileup after normalization //////////////////////
  TH1F * data_norm = new TH1F("data_norm", "data_norm", 600, 0, 60);
  TH1F * mc_norm = new TH1F("mc_norm", "mc_norm", 600, 0, 60);
  
  for(int i=1; i<600; i++){
    double binCon1 = data_hist->GetBinContent(i);
    double binCon2 = data_hist->Integral();
    double ratio=0, sigma=0;
    ratio = binCon1/binCon2;
    double a1 = sqrt(1/binCon1 + 1/binCon2);
    sigma = ratio*a1;
    data_norm->SetBinContent(i, ratio);
    data_norm->SetBinError(i, sigma);
    
    double binCon1mc = mc_hist->GetBinContent(i);
    double binCon2mc = mc_hist->Integral();
    double ratiomc=0, sigmamc=0;
    ratiomc = binCon1mc/binCon2mc;
    double a1mc = sqrt(1/binCon1mc + 1/binCon2mc);
    sigmamc = ratiomc*a1mc;
    mc_norm->SetBinContent(i, ratiomc);
    mc_norm->SetBinError(i, sigmamc);
  }
  c->cd(3);
  data_norm->SetLineWidth(1);
  data_norm->SetMarkerStyle(23+color);
  data_norm->SetMarkerSize(1.0);
  data_norm->SetMarkerColor(color);
  data_norm->SetXTitle("nvtx");
  data_norm->SetLineColor(color);
  data_norm->SetTitle(dFilename);
  data_norm->Draw("e1");
  c->cd(4);
  mc_norm->SetLineWidth(1);
  mc_norm->SetMarkerStyle(23+color);
  mc_norm->SetMarkerSize(1.0);
  mc_norm->SetMarkerColor(color);
  mc_norm->SetLineColor(color);
  mc_norm->SetTitle(mcFilename);
  mc_norm->SetXTitle("nvtx");
  mc_norm->Draw("e1");
  
  //////////////////// Stack MC pileup  //////////////////////
  mc_all->Add(mc_norm);
  mc_all->SetLineWidth(1);
  mc_all->SetMarkerStyle(23+color);
  mc_all->SetMarkerSize(1.0);
  mc_all->SetMarkerColor(color);
  mc_all->SetLineColor(color);
  mc_all->SetTitle(mcFilename);
  mc_all->SetXTitle("nvtx");
  
  //////////////////// Data/MC, ratio after normalization  //////////////////////
  TH1F* h_ratio_default= new TH1F("ratio_d", "Error in the ratio, default from ROOT", 600, 0, 60);
  TH1F* h_ratio = new TH1F("ratio", "Error in the ratio, calculated by hand", 600, 0, 60);
  for(int i=1; i<600; i++){
    double binCon1 = data_norm->GetBinContent(i);
    double binCon2 = mc_norm->GetBinContent(i);
    double binErr1 = data_norm->GetBinError(i);
    double binErr2 = mc_norm->GetBinError(i);
    double ratio=0, sigma=0;
    //if(binCon1 !=0 && binCon2 !=0){
      ratio = binCon1/binCon2;
      double a1 = sqrt(pow(binErr1/binCon1, 2) + pow(binErr2/binCon2, 2));
      sigma = ratio*a1;
      h_ratio_default->SetBinContent(i, binCon1/binCon2);
      h_ratio->SetBinContent(i, binCon1/binCon2);
      h_ratio->SetBinError(i, sigma);
    //}
  }
  //// error in ratio, calculated by ROOT  //////////////
  c->cd(5);
  h_ratio_default->SetLineWidth(1);
  h_ratio_default->SetMarkerStyle(20);
  h_ratio_default->SetMarkerSize(1.0);
  h_ratio_default->SetMarkerColor(color);
  h_ratio_default->SetLineColor(color);
  h_ratio_default->GetYaxis()->SetRangeUser(-0.5, 2);
  h_ratio_default->GetXaxis()->SetTitle("nvtx");
  h_ratio_default->GetYaxis()->SetTitleOffset(0.5);
  h_ratio_default->GetYaxis()->SetTitle("Data/MC");
  h_ratio_default->GetYaxis()->CenterTitle();
  h_ratio_default->GetYaxis()->SetTitleSize(0.04);
  h_ratio_default->Draw("EP");

  //// error in ratio, calculated by hand  //////////////
  c->cd(6);
  h_ratio->SetLineWidth(1);
  h_ratio->SetMarkerStyle(20);
  h_ratio->SetMarkerSize(1.0);
  h_ratio->SetMarkerColor(color);
  h_ratio->SetLineColor(color);
  h_ratio->GetYaxis()->SetRangeUser(-0.5, 2);
  h_ratio->GetXaxis()->SetTitle("nvtx");
  h_ratio->GetYaxis()->SetTitleOffset(0.5);
  h_ratio->GetYaxis()->SetTitle("Data/MC");
  h_ratio->GetYaxis()->CenterTitle();
  h_ratio->GetYaxis()->SetTitleSize(0.04);
  h_ratio->Draw("e1");
  
  //////////////////// Stack ratio  //////////////////////
  hRatio->Add(h_ratio);
  hRatio->SetLineWidth(1);
  hRatio->SetMarkerStyle(20);
  hRatio->SetMarkerSize(1.0);
  hRatio->SetMarkerColor(color);
  hRatio->SetLineColor(color);
  hRatio->GetYaxis()->SetRangeUser(-0.5, 2);
  hRatio->GetXaxis()->SetTitle("nvtx");
  hRatio->GetYaxis()->SetTitleOffset(0.5);
  hRatio->GetYaxis()->SetTitle("Data/MC");
  hRatio->GetYaxis()->CenterTitle();
  hRatio->GetYaxis()->SetTitleSize(0.04);
//  hRatio->GetXaxis()->SetTitleSize(0.04);
//  hRatio->GetXaxis()->SetLabelSize(0.10); // 0.1
//  hRatio->GetXaxis()->LabelsOption("u"); // extra
//  hRatio->GetYaxis()->SetLabelSize(0.06);
}
void pileupRe(){
   //lumiRewt("dataPileup_13TeV.root", "mcPileup_13TeV.root");
  
  TH1F* ratio1 = new TH1F("Data/DYJets","", 600, 0, 60);
  TH1F* ratio2 = new TH1F("Data/TTJets","", 600, 0, 60);
  TH1F* ratio3 = new TH1F("Data/WJets","", 600, 0, 60);
  /*
  TH1F* mc3 = new TH1F("DYJets","", 600, 0, 60);
  lumiRewt("trueMinBiasPU_dataMu.root", "trueInTimePU_mcDY.root", ratio3, mc3, 8);
*/
  TH1F* mc1 = new TH1F("DYJets","", 600, 0, 60);
  TH1F* mc2 = new TH1F("TTJets","", 600, 0, 60);
  TH1F* mc3 = new TH1F("WJets","", 600, 0, 60);
  TCanvas *c3 = new TCanvas("combined", "combined");
  c3->Divide(2,2);
  TCanvas *c4 = new TCanvas("combined_mc", "combined_mc");
  c4->Divide(2,2);
  
  lumiRewt("trueMinBiasPU_dataMu.root", "trueInTimePU_mcDY.root", ratio1, mc1, 4);
  c3->cd(1);
  ratio1->Draw();
  c3->Update();
  c4->cd(1);
  mc1->Draw();
  c4->Update();

  lumiRewt("trueMinBiasPU_dataMu.root", "trueInTimePU_mcTT.root", ratio2, mc2, 6);
  c3->cd(2);
  ratio2->Draw();
  c3->Update();
  c4->cd(2);
  mc2->Draw();
  c4->Update();

 // lumiRewt("muData_Pileup.root", "mcPileup_DY.root", ratio3, mc3, 8);
  lumiRewt("trueMinBiasPU_dataMu.root", "trueInTimePU_mcWJ.root", ratio3, mc3, 8);
  c3->cd(3);
  ratio3->Draw();
  c3->Update();
  c4->cd(3);
  mc3->Draw();
  c4->Update();

  c3->cd(4);
  ratio1->Draw("P");
  c3->Update();
  ratio2->Draw("P same");
  c3->Update();
  ratio3->Draw("P same");
  
  c4->cd(4);
  mc1->Draw("P");
  c3->Update();
  mc2->Draw("P same");
  c3->Update();
  mc3->Draw("P same");
  }
