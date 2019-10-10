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

TString inFileDir="$PWD";
//bkg
TFile* fTT      = TFile::Open(inFileDir+"/all_TTJetsP.root");
//signal
TFile *fWH80      = TFile::Open(inFileDir+"/all_Hplus80.root");
TFile *fWH90      = TFile::Open(inFileDir+"/all_Hplus90.root");
TFile *fWH100     = TFile::Open(inFileDir+"/all_Hplus100.root");
TFile *fWH120     = TFile::Open(inFileDir+"/all_Hplus120.root");
TFile *fWH140     = TFile::Open(inFileDir+"/all_Hplus140.root");
TFile *fWH150     = TFile::Open(inFileDir+"/all_Hplus150.root");
TFile *fWH155     = TFile::Open(inFileDir+"/all_Hplus155.root");
TFile *fWH160     = TFile::Open(inFileDir+"/all_Hplus160.root");


TH1F* getHisto(TFile *histFile, TString histPath, TString dir, TString histName){
  TH1F* hist;
  if(!(histFile->Get(histPath+"/"+dir+"/"+histName))){
    hist = (TH1F*)(fTT->Get(histPath+"/"+dir+"/"+histName))->Clone(histName);
    hist->Add(hist, -1);
  }else hist = (TH1F*)(histFile->Get(histPath+"/"+dir+"/"+histName))->Clone(histName);
  return hist;
}

TGraph* makeGraph(vector<int> Xarray, vector<double> Yarray){
  Int_t n = Xarray.size();
  Double_t x[n], y[n];  
   for (Int_t i=0;i<n;i++) {
     x[i] = Xarray[i];
     y[i] = Yarray[i] ;
   }
   TGraph* gr = new TGraph(n,x,y);
   return gr;
}

TGraphErrors* decorateGraph(TGraphErrors *graph, TString xTitle, TString yTitle, TString myTitle, double yMin, double yMax, int color){
  graph->SetTitle(myTitle);
  graph->GetYaxis()->SetTitle(yTitle);
  graph->GetYaxis()->SetRangeUser(yMin, yMax);
  graph->GetXaxis()->SetTitle(xTitle);
  graph->GetXaxis()->SetTitleOffset(1.15);
  graph->GetYaxis()->SetTitleSize(0.05);   graph->GetXaxis()->SetTitleSize(0.05);
  graph->GetXaxis()->SetLabelSize(0.05);   graph->GetXaxis()->LabelsOption("u"); // extra
  graph->GetYaxis()->SetLabelSize(0.05);   graph->GetXaxis()->LabelsOption("u"); // extra
  graph->GetXaxis()->SetTickLength(0.05); 
  graph->GetYaxis()->SetTickLength(0.04); 
  graph->GetYaxis()->SetTitleSize(0.06);   
  graph->GetYaxis()->SetTitleOffset(1.05);
  graph->SetLineColor(color);
  graph->SetLineWidth(4);
  graph->SetMarkerSize(20);
  graph->SetMarkerStyle(20);
  graph->SetMarkerSize(2);
  graph->SetMarkerColor(color);
  return graph; 
}

TGraphErrors* getGraphForProc(TFile *f, TString cat){
  vector<string> hist_name_array;
  /*
  vector<Float_t> hist_mean_array;
  vector<Float_t> hist_rms_array;
  */
  vector<Float_t> pt_array;
  const int binN = 20;
  Float_t hist_mean_array[binN] = {};
  Float_t hist_rms_array[binN] = {};
  Float_t bjet_pt_array[binN] = {};
  Float_t bjet_pt_err_array[binN] = {};
  pt_array.push_back(25);

  hist_name_array.push_back("mjj_kfit_00To35"); pt_array.push_back(35);
  hist_name_array.push_back("mjj_kfit_35To42"); pt_array.push_back(42);
  hist_name_array.push_back("mjj_kfit_42To50"); pt_array.push_back(50);
  hist_name_array.push_back("mjj_kfit_50To57"); pt_array.push_back(57);
  hist_name_array.push_back("mjj_kfit_57To65"); pt_array.push_back(65);
  hist_name_array.push_back("mjj_kfit_65To74"); pt_array.push_back(74);
  hist_name_array.push_back("mjj_kfit_74To84"); pt_array.push_back(84);
  hist_name_array.push_back("mjj_kfit_84To99"); pt_array.push_back(99);
  hist_name_array.push_back("mjj_kfit_99To124");pt_array.push_back(124);
  hist_name_array.push_back("mjj_kfit_124To500");pt_array.push_back(500);
  for(int i = 0; i<hist_name_array.size(); i++){
    TH1F *hist = getHisto(f, "base/Iso", cat, hist_name_array[i]);
    hist_mean_array[i] = hist->GetMean(); 
    hist_rms_array[i] = 0.5*hist->GetRMS();
    bjet_pt_array[i] = (pt_array[i] + pt_array[i+1])/2;
    bjet_pt_err_array[i] = 0;

    //hist_mean_array.push_back(hist->GetMean());  
    //hist_rms_array.push_back(hist->GetRMS());  
  }
  TGraphErrors* gr = new TGraphErrors(hist_name_array.size(), bjet_pt_array, hist_mean_array, bjet_pt_err_array, hist_rms_array);
  return gr;
}

void plotGraph(){
  gStyle->SetOptStat(11111111);
  gStyle->SetFrameLineWidth(4);
  auto c1 = new TCanvas("c1","Profile histogram example",200,10,700,500);
  c1->Divide(3,2);
  gPad->SetBottomMargin(0.15);
  gPad->SetLeftMargin(0.15);
  gPad->SetRightMargin(0.05);
 
  TLegend* leg = new TLegend(0.50,0.60,0.70,0.85,NULL,"brNDC");
 // TString bin_range = "bin ranges: 25-35, 35-42, 42-50, 50-57, 57-65, 65-74, 74-84, 84-99, 99-124, 124-500";
  TString bin_range = "";
  
  c1->cd(1); 
  TLegend* leg_tt_inc = new TLegend(0.50,0.60,0.70,0.85,NULL,"brNDC");
  TGraphErrors *gr_tt_inc = getGraphForProc(fTT, "PtbJetInc");	
  decorateGraph(gr_tt_inc, "Pt_{bjet}^{Had}(GeV)", "Mean of M_{jj}^{Inc} (GeV)", bin_range, 0, 200, 1);
  gr_tt_inc->Draw("ALP");
  leg_tt_inc->AddEntry(gr_tt_inc, "ttbar","PL");
  leg_tt_inc->Draw();
 
  c1->cd(2);
  TLegend* leg_wh80_inc = new TLegend(0.50,0.60,0.70,0.85,NULL,"brNDC");
  TGraphErrors *gr_wh80_inc = getGraphForProc(fWH80, "PtbJetInc");	
  decorateGraph(gr_wh80_inc, "Pt_{bjet}^{Had}(GeV)", "Mean of M_{jj}^{Inc} (GeV)", bin_range, 0, 200, 2);
  gr_wh80_inc->Draw("ALP");
  leg_wh80_inc->AddEntry(gr_wh80_inc, "WH80","PL");
  leg_wh80_inc->Draw();

  c1->cd(3);
  TLegend* leg_wh100_inc = new TLegend(0.50,0.60,0.70,0.85,NULL,"brNDC");
  TGraphErrors *gr_wh100_inc = getGraphForProc(fWH100, "PtbJetInc");	
  decorateGraph(gr_wh100_inc, "Pt_{bjet}^{Had}(GeV)", "Mean of M_{jj}^{Inc} (GeV)", bin_range, 0, 200, 3);
  gr_wh100_inc->Draw("ALP");
  leg_wh100_inc->AddEntry(gr_wh100_inc, "WH100","PL");
  leg_wh100_inc->Draw();

  c1->cd(4);
  TLegend* leg_wh120_inc = new TLegend(0.50,0.60,0.70,0.85,NULL,"brNDC");
  TGraphErrors *gr_wh120_inc = getGraphForProc(fWH120, "PtbJetInc");	
  decorateGraph(gr_wh120_inc, "Pt_{bjet}^{Had}(GeV)", "Mean of M_{jj}^{Inc} (GeV)", bin_range, 0, 200, 4);
  gr_wh120_inc->Draw("ALP");
  leg_wh120_inc->AddEntry(gr_wh120_inc, "WH120","PL");
  leg_wh120_inc->Draw();
  
  c1->cd(5);
  TLegend* leg_wh150_inc = new TLegend(0.50,0.60,0.70,0.85,NULL,"brNDC");
  TGraphErrors *gr_wh150_inc = getGraphForProc(fWH150, "PtbJetInc");	
  decorateGraph(gr_wh150_inc, "Pt_{bjet}^{Had}(GeV)", "Mean of M_{jj}^{Inc} (GeV)", bin_range, 0, 200, 6);
  gr_wh150_inc->Draw("ALP");
  leg_wh150_inc->AddEntry(gr_wh150_inc, "WH150","PL");
  leg_wh150_inc->Draw();
  
  c1->cd(6);
  gr_tt_inc->Draw("ALP");
  gr_wh80_inc->Draw("LPSame");
  gr_wh100_inc->Draw("LPSame");
  gr_wh120_inc->Draw("LPSame");
  gr_wh150_inc->Draw("LPSame");
  leg->AddEntry(gr_tt_inc, "ttbar","PL");
  leg->AddEntry(gr_wh80_inc, "WH80","PL");
  leg->AddEntry(gr_wh100_inc, "WH100","PL");
  leg->AddEntry(gr_wh120_inc, "WH120","PL");
  leg->AddEntry(gr_wh150_inc, "WH150","PL");
  leg->Draw();
}
