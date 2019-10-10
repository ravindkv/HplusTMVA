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
void example_plot(TString process, TString unctype, TString histName, TString leg_input, int bin, bool axisrange=false, double xmin=1, double xmax=100 ){
  gROOT->ProcessLine(".L tdrstyle.C");
  setTDRStyle();
  gStyle->SetOptStat(0);
  TString inFile("$PWD/");
       
  const float xpad[2] = {0.,1};
  const float ypad[4] = {0.,0.3,0.3,1.0};
  
  double scale_factor = 1; 
  if(process.Contains("WH120")){
   TLegend* leg = new TLegend(0.75,0.50,0.90,0.85,NULL,"brNDC");
  }else{
   TLegend* leg = new TLegend(0.65,0.50,0.80,0.85,NULL,"brNDC");
  }
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);
  leg->SetFillColor(10);
  leg->SetTextSize(0.03);
  //  leg->SetHeader("#splitline{CMS Preliminary}{   @ #sqrt{s} = 7 TeV}");

  //TFile* f = TFile::Open(inFile+"all_TTJetsP.root");
  TFile* f = TFile::Open(inFile+"HplusShapes_mu_13TeV.root");
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
  h2->Rebin(bin);
  if(axisrange){
    h2->GetXaxis()->SetRangeUser(xmin,xmax);
  }
  
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

  TPaveText *pt = new TPaveText(0.18,0.73,0.38,0.95,"brNDC");
  //pt->AddText(process+"_"+unctype);
  pt->AddText(process);
  pt->SetFillColor(19);
  pt->SetFillStyle(0);
  pt->SetLineColor(0);
  pt->SetBorderSize(1);
 
  // Header
  TPaveText *header = new TPaveText(0.15,0.92,0.9,0.99, "brNDC");
  header->SetBorderSize(1);
  header->SetFillColor(19);
  header->SetFillStyle(0);
  header->SetLineColor(0);
  header->SetTextFont(132);
  header->SetTextSize(0.058);
  TText *text = header->AddText("CMS Simulation,    #sqrt{s} = 13 TeV");
  text->SetTextAlign(11);


  // channel specifiction
  TPaveText *ch = new TPaveText(0.72,0.73,0.88,0.95,"brNDC");
  ch->SetFillColor(19);
  ch->SetFillStyle(0);
  ch->SetLineColor(0);
  ch->SetBorderSize(1);
  ch->AddText("#mu + jets");

 
  //  pt->AddText(cat);

  //  h2->SetTitle(channel+"  "+category+"  "+sample);
  h2->GetXaxis()->SetTitle("M_{jj} [GeV]");
  h2->SetAxisRange(0.0, (h2->GetMaximum())*1.3 ,"Y");
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
  TMean1.SetTextSize(.04);
  char mean1[100];
  sprintf(mean1,"Mean = %.2f",h1->GetMean());
  TMean1.DrawTextNDC(.18,.745,mean1);

  TText TMean2;
  TMean2.SetTextColor(kBlue);
  TMean2.SetTextSize(.04);
  char mean2[100];
  sprintf(mean2,"Mean = %.2f",h2->GetMean());
  TMean2.DrawTextNDC(.18,.645,mean2);

  TText TMean3;
  TMean3.SetTextColor(kRed);
  TMean3.SetTextSize(.04);
  char mean3[100];
  sprintf(mean3,"Mean = %.2f",h3->GetMean());
  TMean3.DrawTextNDC(.18,.545,mean3);

  leg->Draw();
  pt->Draw();
  header->Draw();
  ch->Draw();
  gPad->RedrawAxis();
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
