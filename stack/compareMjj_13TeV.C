#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "TH1F.h"
#include "TFile.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "TLegend.h"

using namespace std;
bool isMuChannel = true;
bool isEleChannel = false;

void example_plot(TString process, TString unctype, TString histName, TString leg_input, int bin, bool axisrange=false, double xmin=1, double xmax=100 ){
  TString inFile("$PWD/");
  gStyle->SetOptStat(0);
  gStyle->SetFrameLineWidth(2);
  const float xpad[2] = {0.,1};
  const float ypad[4] = {0.,0.40,0.40,0.98};

  TCanvas *c1 = new TCanvas();
  c1->Divide(1, 2);
  //c1->cd(postion);
  c1->cd(1);
  gPad->SetPad(xpad[0],ypad[2],xpad[1],ypad[3]);
  gPad->SetTopMargin(1.15); 
  gPad->SetBottomMargin(0); 
  gPad->SetLeftMargin(0.15);
  gPad->SetRightMargin(0.05);
  double scale_factor = 1; 
  TLegend* leg = new TLegend(0.70,0.50,0.80,0.85,NULL,"brNDC");
  if(histName.Contains("WH120")){
   TLegend* leg = new TLegend(0.75,0.50,0.90,0.85,NULL,"brNDC");
  }
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);
  leg->SetFillColor(10);
  leg->SetTextSize(0.07);
  //  leg->SetHeader("#splitline{CMS Preliminary}{   @ #sqrt{s} = 7 TeV}");

  TFile* f = TFile::Open(inFile+"Shapes_mu_Cat2_WH120.root");
  //TFile* f = TFile::Open(inFile+"Shapes_ele_Cat2_WH120.root");
  if(f == 0) return;
  if(f->IsZombie()){f->Close(); return;}

  //TH1F* h1 = (f->Get(process+"_"+unctype+"Up"))->Clone("h1");
  cout<<histName<<" : "<<unctype<<endl;
  TH1F* h1 = (TH1F*)(f->Get(histName+"_"+unctype+"Up"))->Clone("h1");
  h1->Scale(scale_factor);
  h1->SetLineColor(kGreen);
  h1->SetLineWidth(3);
  h1->Rebin(bin);
  if(axisrange){
    h1->GetXaxis()->SetRangeUser(xmin,xmax);
  }
  
  //TH1F* h2 = (f->Get(process))->Clone("h2");
  TH1F* h2 = (TH1F*)(f->Get(histName))->Clone("h2");
  h2->GetXaxis()->SetRangeUser(0, 200);
  h2->Scale(scale_factor);
  h2->SetLineColor(kBlue);
  h2->SetLineWidth(3);
  h2->SetTitle("");
  h2->GetYaxis()->SetTitle("Events / 5 GeV");
  h2->GetYaxis()->SetRangeUser(1, 1.1* h2->GetMaximum());
  //h2->GetXaxis()->SetNdivisions(5);
  h2->GetYaxis()->SetNdivisions(5);
  h2->GetYaxis()->SetTitleOffset(0.60);
  h2->GetXaxis()->SetTitleOffset(1.00);
  h2->GetYaxis()->SetTitleSize(0.10);   
  h2->GetXaxis()->SetTitleSize(0.06);
  h2->GetXaxis()->SetLabelSize(0.06);   
  h2->GetYaxis()->SetLabelSize(0.10);   
  h2->GetXaxis()->SetTickLength(0.03); 
  h2->GetYaxis()->SetTickLength(0.03); 
  h2->Rebin(bin);
  if(axisrange){
    h2->GetXaxis()->SetRangeUser(xmin,xmax);
  }
  
  TGaxis::SetMaxDigits(3);
  //TH1F* h3 = (f->Get(process+"_"+unctype+"Down"))->Clone("h3");
  TH1F* h3 = (TH1F*)(f->Get(histName+"_"+unctype+"Down"))->Clone("h3");
  h3->GetXaxis()->SetRangeUser(0, 200);
  h3->Scale(scale_factor);
  h3->SetLineColor(kRed);
  h3->SetLineWidth(3);
  h3->Rebin(bin);
  if(axisrange){
    h3->GetXaxis()->SetRangeUser(xmin,xmax);
  }

  // legend adding
  
  leg->AddEntry(h1,leg_input+unctype+"_Up","LP");
  leg->AddEntry(h2,"Nominal","LP");
  leg->AddEntry(h3,leg_input+unctype+"_Down","LP");

  TPaveText *pt = new TPaveText(0.18,0.82,0.38,0.87,"brNDC");
  //pt->AddText(process+"_"+unctype);
  pt->AddText(process);
  pt->SetFillColor(19);
  pt->SetFillStyle(0);
  pt->SetLineColor(0);
  pt->SetBorderSize(1);
  pt->SetTextSize(0.078);
 
  // Header
  TPaveText *header = new TPaveText(0.72,0.91,0.90,0.95, "brNDC");
  header->SetBorderSize(1);
  header->SetFillColor(19);
  header->SetFillStyle(0);
  header->SetLineColor(0);
  header->SetTextFont(132);
  header->SetTextSize(0.08);
  TText *text = header->AddText("35.9 fb^{-1} (13 TeV)");
  text->SetTextAlign(11);

  // channel specifiction
  TPaveText *ch = new TPaveText(0.50,0.9154898,0.60,0.9762187,"brNDC");
  ch->SetFillColor(19);
  ch->SetFillStyle(0);
  ch->SetLineColor(0);
  ch->SetTextSize(0.10);
  ch->SetBorderSize(1);
  if(isMuChannel) ch->AddText("#mu + jets");
  if(isEleChannel) ch->AddText("e + jets");

 
  //  pt->AddText(cat);

  //  h2->SetTitle(channel+"  "+category+"  "+sample);
  h2->GetXaxis()->SetTitle("m_{jj} (GeV)");
  //h2->SetAxisRange(0.0, (h2->GetMaximum())*1.3 ,"Y");
  //  h1->GetYaxis()->SetTitle("Normalized to Unity");
  //  h1->GetYaxis()->SetRangeUser(0.00, 0.20);
  //  MuptStack->GetXaxis()->SetTitle(xaxis_title);

  //  h3->DrawNormalized("HIST");
  //  h2->DrawNormalized("HISTSAME");
  //  h1->DrawNormalized("HISTSAME");

  h2->Draw("HIST");
  h1->Draw("HISTSAME");
  h3->Draw("HISTSAME");
  
  TText TMean1;
  TMean1.SetTextColor(kGreen);
  TMean1.SetTextSize(.07);
  char mean1[100];
  sprintf(mean1,"Mean = %.2f",h1->GetMean());
  TMean1.DrawTextNDC(.18,.650,mean1);

  TText TMean2;
  TMean2.SetTextColor(kBlue);
  TMean2.SetTextSize(.07);
  char mean2[100];
  sprintf(mean2,"Mean = %.2f",h2->GetMean());
  TMean2.DrawTextNDC(.18,.550,mean2);

  TText TMean3;
  TMean3.SetTextColor(kRed);
  TMean3.SetTextSize(.07);
  char mean3[100];
  sprintf(mean3,"Mean = %.2f",h3->GetMean());
  TMean3.DrawTextNDC(.18,.450,mean3);

  leg->Draw();
  pt->Draw();
  header->Draw();
  ch->Draw();
  gPad->RedrawAxis();

  ////////////////////////////// Ratio //////////////////////////// 
  c1->cd(2);
  gPad->SetPad(xpad[0],ypad[0],xpad[1],ypad[1]);
  gPad->SetTopMargin(0); gPad->SetBottomMargin(0.4); gPad->SetGridy();
  gPad->SetLeftMargin(0.15);
  gPad->SetRightMargin(0.05);
  TH1F *hRatio_Up = (TH1F*)h2->Clone("hRatio_Up");
  //hRatio_Up->GetYaxis()->SetNdivisions(3);
  hRatio_Up->Reset();
  hRatio_Up->Add(h2);
  hRatio_Up->Divide(h1); hRatio_Up->SetMarkerStyle(20); hRatio_Up->SetMarkerSize(0.8);
  hRatio_Up->SetMarkerColor(kGreen); hRatio_Up->SetLineColor(kGreen); hRatio_Up->GetYaxis()->SetRangeUser(0.8, 1.2);
  //hRatio_Up->GetXaxis()->SetRangeUser(xmin, xmax);
  hRatio_Up->GetXaxis()->SetTickLength(0.13); 
  hRatio_Up->GetYaxis()->SetTickLength(0.04); 
  hRatio_Up->GetXaxis()->SetTitle("m_{jj} (GeV)"); 
  hRatio_Up->GetYaxis()->SetTitleOffset(0.40);
  hRatio_Up->GetXaxis()->SetTitleOffset(0.90);
  hRatio_Up->GetYaxis()->SetTitle("#frac{Nominal}{Unc}"); hRatio_Up->GetYaxis()->CenterTitle();
  hRatio_Up->GetYaxis()->SetTitleSize(0.15); hRatio_Up->GetXaxis()->SetTitleSize(0.20);
  hRatio_Up->GetXaxis()->SetLabelSize(0.15); 
  hRatio_Up->GetYaxis()->SetLabelSize(0.15); 
  hRatio_Up->Draw("E"); // use "P" or "AP"
  
  TH1F *hRatio_Down = (TH1F*)h2->Clone("hRatio_Up");
  hRatio_Down->Reset();
  hRatio_Down->Add(h2);
  hRatio_Down->Divide(h3); 
  hRatio_Down->SetMarkerColor(kRed); hRatio_Down->SetLineColor(kRed); hRatio_Down->GetYaxis()->SetRangeUser(0, 2);
  hRatio_Down->Draw("SAME"); // use "P" or "AP"
  
  TF1 *baseLine = new TF1("baseLine","1", -100, 2000); 
  baseLine->SetLineColor(kBlack);
  baseLine->Draw("SAME");
  TString outFile("MjjShape/");
  outFile += histName+"_"+unctype;
  if(isMuChannel) outFile += "_mu.pdf";
  if(isEleChannel) outFile += "_ele.pdf";
  c1->SaveAs(outFile);
  //c1->Close();
}


//void example_plot(TString process, TString unctype, TString histName, TString leg_input, int bin)
void plotAll(){
  c1 = new TCanvas();
  c1->Divide(3 ,2);
  c1->cd(1);
  example_plot("ttbar","JER", 	"ttbar", "", 1, true, 0, 200); // log, ratio, axisrange,xmin,xmax
  c1->cd(2);
  example_plot("ttbar","JES", 	"ttbar", "", 1, true, 0, 200); // log, ratio, axisrange,xmin,xmax
  c1->cd(3);
  example_plot("ttbar","topPt", "ttbar", "", 1, true, 0, 200); // log, ratio, axisrange,xmin,xmax
  c1->cd(4);
  example_plot("ttbar","bTag", "ttbar", "", 1, true, 0, 200); // log, ratio, axisrange,xmin,xmax
  c1->cd(5);
  example_plot("ttbar","scale", "ttbar", "", 1, true, 0, 200); // log, ratio, axisrange,xmin,xmax
  c1->cd(6);
  example_plot("ttbar","matching", "ttbar", "", 1, true, 0, 200); // log, ratio, axisrange,xmin,xmax
  c1->Update();
  /*
  TString outFile("");
  outFile += +process+"_"+histName;
  //  outFile += "_"+cat;
  outFile += "_"+unctype;
  //  outFile += ".pdf";
  outFile += "_mu.pdf";
  c1->SaveAs(outFile);
  c1->Close();
  */
//  example_plot("ttbar","JER","",1);
//  example_plot("ttbar","topPt","",1);
//  example_plot("ttbar","scale","QCD ",1);
//  example_plot("ttbar","matching","MG5 ",1);
  
}
void plotSeparate( TString hist, TString hist_label, TString sys){
  example_plot(hist, sys, hist_label, "", 1, true, 0, 200); // log, ratio, axisrange,xmin,xmax
}
void compareMjj_13TeV(){ 
  plotSeparate( "t#bar{t} + jets", "ttbar", "Pileup");
  plotSeparate( "t#bar{t} + jets", "ttbar", "JER");
  plotSeparate( "t#bar{t} + jets", "ttbar", "JES");
  plotSeparate( "t#bar{t} + jets", "ttbar", "topPt");
  plotSeparate( "t#bar{t} + jets", "ttbar", "bcTag1");
  plotSeparate( "t#bar{t} + jets", "ttbar", "bcTag2");
  plotSeparate( "t#bar{t} + jets", "ttbar", "bcTag3");
  plotSeparate( "t#bar{t} + jets", "ttbar", "scaleRF_tt");
  plotSeparate( "t#bar{t} + jets", "ttbar", "topMass_tt");
  plotSeparate( "t#bar{t} + jets", "ttbar", "hDamp_tt");

  plotSeparate( "m_{H^{+}} = 120 GeV", "WH120", "Pileup");
  plotSeparate( "m_{H^{+}} = 120 GeV", "WH120", "JER");
  plotSeparate( "m_{H^{+}} = 120 GeV", "WH120", "JES");
  plotSeparate( "m_{H^{+}} = 120 GeV", "WH120", "topPt");
  plotSeparate( "m_{H^{+}} = 120 GeV", "WH120", "bcTag1");
  plotSeparate( "m_{H^{+}} = 120 GeV", "WH120", "bcTag2");
  plotSeparate( "m_{H^{+}} = 120 GeV", "WH120", "bcTag3");
}

