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

//--------------------------------------------
//function to make graph from two array
//--------------------------------------------
TGraph* makeGraph(vector<Float_t> Xarray, vector<Float_t> Yarray){
  Int_t n = Xarray.size();
  Double_t x[n], y[n];  
   for (Int_t i=0;i<n;i++) {
     x[i] = Xarray[i];
     y[i] = Yarray[i] ;
   }
   TGraph* gr = new TGraph(n,x,y);
   return gr;
}

//--------------------------------------------
//function to decorate Graph  
//--------------------------------------------
TGraph* decorateGraph(TGraph *graph, TString xTitle, TString yTitle, TString myTitle, double yMin, double yMax, int color){
  graph->SetTitle(myTitle);
  graph->GetYaxis()->SetTitleOffset(1.30);
  //graph->GetXaxis()->SetTitle(xTitle);
  graph->GetXaxis()->SetTitleSize(0.05);
  graph->GetXaxis()->SetLabelSize(0.06);
  //graph->GetYaxis()->SetTitle(yTitle);
  graph->GetYaxis()->SetTitleSize(0.04);
  //graph->GetYaxis()->SetRangeUser(yMin, yMax);
  //graph->GetXaxis()->SetRangeUser(0, 10);
  graph->GetYaxis()->SetLabelSize(0.05);
  graph->SetLineColor(color);
  graph->SetLineWidth(2);
  //graph->SetMarkerSize(15);
  graph->SetMarkerStyle(20);
  graph->SetMarkerSize(0.5);
  return graph; 
}

TGraph* scanNuisParamGraph(string nuisName, TFile &f, int col){
  Float_t r;
  TTree* limit = (TTree*)f.Get("limit");
  limit->SetBranchAddress(nuisName.c_str(), &r);
  Float_t ml;
  limit->SetBranchAddress("deltaNLL",&ml);
  
  vector<Float_t> nuisVal;
  vector<Float_t> mlVal;
  if(limit->GetEntries()==20) cout<<"FULL SUCCESS: "<<nuisName<<endl;
  for(int k = 0 ; k< limit->GetEntries() ; k++){
    limit->GetEntry(k);
    nuisVal.push_back(r);
    mlVal.push_back(2*ml);
  }
  TGraph* myGraph = makeGraph(nuisVal, mlVal);
  decorateGraph(myGraph, nuisName, "2 deltaNLL", "2*deltaNLL vs "+nuisName, 150, 300, col);  
  //myGraph->Draw();
  return myGraph;
}

void scanNuisParam_13TeV(){
  
  std::ifstream file("allNuisParamName.txt");
  std::string nuisName; 
  std::vector<string> nuisName_vec;
  while (std::getline(file, nuisName)){
    nuisName_vec.push_back(nuisName);
  }
  int n_param = 16;
  int n_page = nuisName_vec.size()/n_param +1;

  for(int k=0; k<n_page; k++){ //107
    TCanvas *myCan = new TCanvas();
    myCan->Divide(4, 4);
    cout<<"-----------------------------------"<<endl;
    cout<<"Page Number: "<<k+1<<"/"<<n_page<<endl;
    cout<<"-----------------------------------"<<endl;
    for(int j=n_param*k; j<n_param*(k+1); j++){
      cout<<j<<": "<<nuisName_vec[j].c_str()<<endl;
      if(j>=nuisName_vec.size())continue;
      //pave text CMS box
      TPaveText *pt = new TPaveText(0.50,0.80,0.60,0.85, "brNDC"); // good_v1
      pt->SetBorderSize(0); pt->SetFillColor(19);
      pt->SetFillStyle(0); pt->SetTextSize(0.08);
      pt->SetLineColor(3); pt->SetTextFont(132);
      ostringstream convert;
      convert <<j+1;
      TText *text = pt->AddText(convert.str().c_str());
      text->SetTextAlign(11);
      TFile f(Form("higgsCombineScanNuis_%s.MultiDimFit.mH120.root", nuisName_vec[j].c_str()),"READ"); 
      myCan->cd(j -n_param*k +1);
      if(f.IsZombie()){
        ostringstream convertErr;
	convertErr<<"\n Error : ";
        convertErr <<nuisName_vec[j].c_str();
        pt->AddText(convertErr.str().c_str());
	pt->Draw(); 
	continue;
      }
      TGraph* myGraph = scanNuisParamGraph(nuisName_vec[j], f, 3);
      myGraph->Draw();
      pt->Draw();
    }
    myCan->SaveAs(".pdf");
    //myCan->Print("scanNuis.pdf(", "pdf");
    //if(n_param >1703)myCan->Print("scanNuis.pdf)", "pdf");
  }
}

