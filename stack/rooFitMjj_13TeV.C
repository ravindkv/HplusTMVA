#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <string>
#include <cmath>

#include "TCanvas.h"
#include "TFile.h"
#include "TTree.h"
#include "TBranch.h"
#include "TLegend.h"
#include "TH1.h"
#include "TH1D.h"
#include "TH2.h"
#include "TH2D.h"
#include "TString.h"
#include "TRandom3.h"
#include "TLine.h"
#include "TPaveText.h"
#include "THStack.h"
#include "TROOT.h"
#include "TApplication.h"
#include "TStyle.h"
#include "TGaxis.h"

#include "RooFit.h"
#include "RooRealVar.h"
#include "RooAbsPdf.h"
#include "RooAddPdf.h"
#include "RooDataSet.h"
#include "RooDataHist.h"
#include "RooGaussian.h"
#include "RooGlobalFunc.h"
#include "RooBifurGauss.h"
#include "RooLandau.h"
#include "RooChi2Var.h"
#include "RooChebychev.h"
#include "RooFitResult.h"
#include "RooCBShape.h"
#include "RooHistPdf.h"
#include "RooHist.h"
#include "RooPlot.h"
#include "TLatex.h"

bool isMuChannel = true;
bool isEleChannel = false;

TString baseDir = "base"; //baseLowMET
TFile* fTT	= TFile::Open("all_TTJetsP.root");


TH1F* getHisto(TFile *histFile, TString dir, TString histName, TString xaxis_title){
  TH1F* hist; 
  if(!(histFile->Get(baseDir+"/Iso/"+dir+"/"+histName))){
    hist = (TH1F*)(fTT->Get(baseDir+"/Iso/"+dir+"/"+histName))->Clone(histName);
    hist->Add(hist, -1);
  }else hist = (TH1F*)(histFile->Get(baseDir+"/Iso/"+dir+"/"+histName))->Clone(histName);
  cout<<dir<<"/"<<histName<<":  "<<"Entry = "<<hist->GetEntries()<<"\t"<<"Integral = "<<hist->Integral()<< endl;
  return hist;
}

void rooFitMjj_13TeV(){
  TH1F* hist = getHisto(fTT, "KinFit", "mjj_kfit" , "M_{jj}^{Inc}[GeV]");
  hist->Scale(1/hist->Integral());
  RooRealVar mjj("mjj","M_{jj}^{Inc}[GeV]",-200 ,200);
  RooDataHist roo_hist("roo_hist","roo_hist",RooArgList(mjj),hist);

  //Build Gaussian PDF
  RooRealVar mean("mean","mean of gaussian",80,0,200) ;
  RooRealVar sigma("sigma","width of gaussian",10, 0, 50) ;
  RooGaussian gauss("gauss","gaussian PDF",mjj,mean,sigma) ;

  //cout<<gauss.getVal(mjj)<<endl;
  gauss.fitTo(roo_hist);
  mean.Print();
  sigma.Print();
  //Plot PDF
  RooPlot* xframe = mjj.frame() ;
  gauss.plotOn(xframe) ;
  roo_hist.plotOn(xframe) ;
  xframe->Draw() ;
  /*
  getHisto(fSig, "KinFit", "mjj_kfit_CTagL_SF" , "M_{jj}^{Inc_CTagL}[GeV]");
  getHisto(fSig, "KinFit", "mjj_kfit_CTagM_SF" , "M_{jj}^{Inc_CTagM}[GeV]");
  getHisto(fSig, "KinFit", "mjj_kfit_CTagT_SF" , "M_{jj}^{Inc_CTagT}[GeV]");
  getHisto(fSig, "KinFit", "mjj_kfit_CTagL_SF_Cat" , "M_{jj}^{Ex_CTagL}[GeV]");
  getHisto(fSig, "KinFit", "mjj_kfit_CTagM_SF_Cat" , "M_{jj}^{Ex_CTagM}[GeV]");
  getHisto(fSig, "KinFit", "mjj_kfit_CTagT_SF_Cat" , "M_{jj}^{Ex_CTagT}[GeV]");
  //getHisto(fSig, "KinFit", "mjj_kfit_CTagO_SF_Cat" , "M_{jj}^{Inc}[GeV]");
  */
 }

