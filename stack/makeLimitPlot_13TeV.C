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


void plot( TString dir  = "$PWD",
	   TString cutSet = "cutSet",	
	   TString histDir  = "mjj_kfit", 
	   TString stream  = "MuT", 
	   TString channel = "BSM", TString save_tag = "",
	   TString legend  = "#c_{#mu}#s-bar",
	   Float_t xMax_   = 50, bool obs = false, bool rootfile = false )
{
  
  TLegend* leg = new TLegend(0.14,0.60,0.41,0.85,NULL,"brNDC");
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);
  leg->SetFillColor(0);


  float X[]        = {90,100,120, 140, 150, 155, 160};
  float obsY[]     = {0.,0.,0, 0, 0, 0, 0,0};
  float expY[]     = {0.,0.,0, 0, 0, 0, 0,0};
		      
  float expX1sL[]  = {0.,0.,0, 0, 0, 0, 0,0};
  float expX1sH[]  = {0.,0.,0, 0, 0, 0, 0,0};
  float expY1sL[]  = {0.,0.,0, 0, 0, 0, 0,0};
  float expY1sH[]  = {0.,0.,0, 0, 0, 0, 0,0};
		      
  float expX2sL[]  = {0.,0.,0, 0, 0, 0, 0,0};
  float expX2sH[]  = {0.,0.,0, 0, 0, 0, 0,0};
  float expY2sL[]  = {0.,0.,0, 0, 0, 0, 0,0};
  float expY2sH[]  = {0.,0.,0, 0, 0, 0, 0,0};

  int nMassPoints = 7;
  TString massFiles [7] = {"higgsCombineChargedHiggs_mu.Asymptotic.mH90.root",
  "higgsCombineChargedHiggs_mu.Asymptotic.mH100.root",
  "higgsCombineChargedHiggs_mu.Asymptotic.mH120.root",
  "higgsCombineChargedHiggs_mu.Asymptotic.mH140.root",
  "higgsCombineChargedHiggs_mu.Asymptotic.mH150.root",
  "higgsCombineChargedHiggs_mu.Asymptotic.mH155.root",
  "higgsCombineChargedHiggs_mu.Asymptotic.mH160.root"};

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
      if(k==2) expY[i]    = r;
      if(k==3) expY1sH[i] = r;
      if(k==4) expY2sH[i] = r;
      if(k==5) obsY[i]    = r;
    }
  }
  cout<<"Mass:"<<setw(15)<<"base value"<<setw(15)<<"-2 #sigma"<<setw(15)<<"-1 #sigma"<<setw(15)<<"+1 #sigma"<<setw(15)<<"+2 #sigma"<<endl; 
  for(int i1 = 0 ; i1 < nMassPoints ; i1++){
  cout<<X[i1]<<setw(15)<<expY[i1]<<setw(15)<<expY2sL[i1]<<setw(15)<< expY1sL[i1]<<setw(15)<<expY1sH[i1]<<setw(15)<<expY2sH[i1]<<endl; 
    expY1sH[i1] = TMath::Abs(expY1sH[i1]-expY[i1]);
    expY1sL[i1] = TMath::Abs(expY1sL[i1]-expY[i1]);
    expY2sH[i1] = TMath::Abs(expY2sH[i1]-expY[i1]);
    expY2sL[i1] = TMath::Abs(expY2sL[i1]-expY[i1]);
  //cout<<setw(10)<<X[i1]<<setw(15)<<expY[i1]<<setw(15)<<expY2sL[i1]<<setw(15)<< expY1sL[i1]<<setw(15)<<expY1sH[i1]<<setw(15)<<expY2sH[i1]<<endl; 
  }
  
  TMultiGraph *mg = new TMultiGraph();
  mg->SetTitle(cutSet+"_"+histDir);

  TGraphAsymmErrors* expected = new TGraphAsymmErrors(nMassPoints, X, expY, expX1sL ,expX1sL , expX1sL, expX1sL);
  TGraphAsymmErrors* oneSigma = new TGraphAsymmErrors(nMassPoints, X, expY, expX1sL, expX1sL,  expY1sL, expY1sH);
  TGraphAsymmErrors* twoSigma = new TGraphAsymmErrors(nMassPoints, X, expY, expX2sL, expX2sL,  expY2sL, expY2sH);
  TGraphAsymmErrors* observed = new TGraphAsymmErrors(nMassPoints, X, obsY, expX1sL ,expX1sL , expX1sL, expX1sL);

 
  oneSigma->SetMarkerColor(kBlack);
  oneSigma->SetMarkerStyle(kFullCircle);
  oneSigma->SetFillColor(kGreen);
  oneSigma->SetFillStyle(1001);

  twoSigma->SetMarkerColor(kBlack);
  twoSigma->SetMarkerStyle(kFullCircle);
  twoSigma->SetFillColor(kYellow);
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
  mg->GetXaxis()->SetLimits(85,165);
  mg->GetYaxis()->SetTitleOffset(1.55);
  mg->SetMinimum(0.);
  mg->SetMaximum(xMax_);
  mg->GetXaxis()->SetTitle("m_{H} (GeV)");
  mg->GetYaxis()->SetTitle("95% CL limit for BR(t#rightarrow bH^{#pm})");

  leg->SetHeader(Form("#splitline{CMS Preliminary #sqrt{s}=13 TeV}{35.45 fb^{-1}, %s}",legend.Data()));

  leg->AddEntry(expected,"Expected","L");
  if(obs) leg->AddEntry(observed,"Observed","L");
  leg->AddEntry(oneSigma, "#pm 1 #sigma","F");
  leg->AddEntry(twoSigma, "#pm 2 #sigma","F");

  leg->Draw();

  TPaveText *pl2 = new TPaveText(0.55,0.70,0.78,0.88, "brNDC");
  pl2->SetTextSize(0.032);
  pl2->SetFillColor(0);
  pl2->SetTextFont(132);
  pl2->SetBorderSize(0);
  pl2->SetTextAlign(11);
  pl2->AddText("t #rightarrow H^{#pm}b, H^{+} #rightarrow c#bar{s}");
  pl2->AddText("2 CSVM b-tag ");
  //  pl2->AddText(channel.Data());
  pl2->AddText(legend.Data());

  pl2->AddText("BR(H^{+} #rightarrow c#bar{s}) = 1");
  pl2->Draw();
  

  TF1 *line = new TF1("line","1",100,150);
  line->SetLineColor(kRed);
  line->SetLineWidth(2);

  line->Draw("SAME");
  gPad->RedrawAxis();
  //  gPad->SaveAs(Form("limit_%s_%s_%s.png",stream.Data(), channel.Data(), save_tag.Data()));
  gPad->SaveAs(Form(cutSet+"_"+histDir+"_"+"limit_%s_%s_%s.png",stream.Data(), channel.Data(), save_tag.Data()));
  if(rootfile){
    TFile *fout = new TFile(Form(cutSet+"_"+histDir+"_"+"limit_%s_%s_%s.root",stream.Data(), channel.Data(), save_tag.Data()), "RECREATE");
    expected->Write("expected");
    observed->Write("observed");
    oneSigma->Write("oneSigma");
    twoSigma->Write("twoSigma");
    fout->Close();
  }

}


void makeLimitPlot(){
  TCanvas *c1 = new TCanvas();
  c1->SetGrid(0,0);
  c1->SetFillStyle(4000);
  c1->SetFillColor(10);
  c1->SetTicky();
  c1->SetObjectStat(0);
  c1->Divide(2, 2);
  /*
  c1->cd(1);
  plot("stack_20171115_Mu_sys_cutSet1", "cutSet1", "mjj_kfit_CTagT", "ChargedHiggs","mu","13TeV","mu + jets",0.03, false, true);
  c1->cd(2);
  plot("stack_20171115_Mu_sys_cutSet2", "cutSet2", "mjj_kfit_CTagT", "ChargedHiggs","mu","13TeV","mu + jets",0.03, false, true);
  c1->cd(3);
  plot("stack_20171115_Mu_sys_cutSet3", "cutSet3", "mjj_kfit_CTagT", "ChargedHiggs","mu","13TeV","mu + jets",0.03, false, true);
  c1->cd(4);
  plot("stack_20171115_Mu_sys_cutSet4", "cutSet4", "mjj_kfit_CTagT", "ChargedHiggs","mu","13TeV","mu + jets",0.03, false, true);

  c1->cd(1);
  plot("stack_20171115_Mu_sys_cutSet1", "cutSet1", "mjj_kfit_CTagM", "ChargedHiggs","mu","13TeV","mu + jets",0.03, false, true);
  c1->cd(2);
  plot("stack_20171115_Mu_sys_cutSet2", "cutSet2", "mjj_kfit_CTagM", "ChargedHiggs","mu","13TeV","mu + jets",0.03, false, true);
  c1->cd(3);
  plot("stack_20171115_Mu_sys_cutSet3", "cutSet3", "mjj_kfit_CTagM", "ChargedHiggs","mu","13TeV","mu + jets",0.03, false, true);
  c1->cd(4);
  plot("stack_20171115_Mu_sys_cutSet4", "cutSet4", "mjj_kfit_CTagM", "ChargedHiggs","mu","13TeV","mu + jets",0.03, false, true);
  
  c1->cd(1);
  plot("stack_20171115_Mu_sys_cutSet1", "cutSet1", "mjj_kfit_CTagL", "ChargedHiggs","mu","13TeV","mu + jets",0.03, false, true);
  c1->cd(2);
  plot("stack_20171115_Mu_sys_cutSet2", "cutSet2", "mjj_kfit_CTagL", "ChargedHiggs","mu","13TeV","mu + jets",0.03, false, true);
  c1->cd(3);
  plot("stack_20171115_Mu_sys_cutSet3", "cutSet3", "mjj_kfit_CTagL", "ChargedHiggs","mu","13TeV","mu + jets",0.03, false, true);
  c1->cd(4);
  plot("stack_20171115_Mu_sys_cutSet4", "cutSet4", "mjj_kfit_CTagL", "ChargedHiggs","mu","13TeV","mu + jets",0.03, false, true);
*/
 
  c1->cd(1);
  plot("stack_20171115_Mu_sys_cutSet1", "cutSet1", "mjj_kfit", "ChargedHiggs","mu","13TeV","mu + jets",0.03, false, true);
  c1->cd(2);
  plot("stack_20171115_Mu_sys_cutSet2", "cutSet2", "mjj_kfit", "ChargedHiggs","mu","13TeV","mu + jets",0.03, false, true);
  c1->cd(3);
  plot("stack_20171115_Mu_sys_cutSet3", "cutSet3", "mjj_kfit", "ChargedHiggs","mu","13TeV","mu + jets",0.03, false, true);
  c1->cd(4);
  plot("stack_20171115_Mu_sys_cutSet4", "cutSet4", "mjj_kfit", "ChargedHiggs","mu","13TeV","mu + jets",0.03, false, true);
  /* 
  */
}

















