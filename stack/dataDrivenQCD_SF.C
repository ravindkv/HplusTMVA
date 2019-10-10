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

using namespace std;
 
///////////////////////////////////////////  
//CHANNEL
bool isMuChannel = true;
TString baseIsoDir = "baseLowMET";

//INPUT FILES
TFile *fData  = TFile::Open("all_muData.root");

TFile* fVV	= TFile::Open("all_VV.root");
TFile* fDY	= TFile::Open("all_DY.root");
TFile* fWJ	= TFile::Open("all_WJets.root");
TFile* fST	= TFile::Open("all_ST.root");
TFile* fTT	= TFile::Open("all_TTJetsP.root");
//double sf_ttbar = 1.0; 
double sf_ttbar   = 1.0/0.999275; 
  
//SAVE HISTOS ON DISK
bool isSaveHisto = true;
///////////////////////////////////////////  

//*-------------------------------
//* get histo from root files
//*--------------------------
TH1F* getHisto(TFile *histFile,  TString dirBase, TString dirIso, TString dirBTag, 
               TString histName, double sf){
  TH1F* hist;
  TString histPath = dirBase+"/"+dirIso+"/"+dirBTag+"/"+histName;
  if(!(histFile->Get(histPath))){
    hist = (TH1F*)(fTT->Get(histPath))->Clone(histName);
    hist->Add(hist, -1);
  }else hist = (TH1F*)(histFile->Get(histPath))->Clone(histName);
  hist->Scale(sf);
  ///cout << dirBTag << ", " << dirIso << ", " << dirBTag << ", " << histName << ", " << hist->Integral()<<endl;
  return hist;
}

//*-------------------------------
//* function for (Data -nonQCDBkg)
//*-------------------------------
TH1F * dataMCdiff(TString dirIso, TString dirBTag, TString histname, TString xaxis_title, int bin, 
                  bool log=false, bool axisrange=false, double xmin=0, double xmax=10){
  //hMC = all Bkg MC samples
  TH1F* hMC =  (TH1F*) getHisto(fVV, baseIsoDir, dirIso, dirBTag, histname, 1)->Clone("hMC");
  hMC->Add(getHisto(fDY, baseIsoDir, dirIso, dirBTag, histname, 1));
  hMC->Add(getHisto(fST, baseIsoDir, dirIso, dirBTag, histname, 1));
  hMC->Add(getHisto(fWJ, baseIsoDir, dirIso, dirBTag, histname, 1));
  hMC->Add(getHisto(fTT, baseIsoDir, dirIso, dirBTag, histname, sf_ttbar));
  
  //DATA
  TH1F* hData = (TH1F*)getHisto(fData, baseIsoDir, dirIso, dirBTag, histname, 1)->Clone("data");
  //Data - non QCD Bkg
  TH1F *hDiff = (TH1F*)hData->Clone("hDiff");
  hDiff->Add(hMC, -1);
  TString Region = "ABCD";
  if(baseIsoDir=="base"       && dirIso=="Iso")    Region = "Region A";
  if(baseIsoDir=="base"       && dirIso=="NonIso") Region = "Region B";
  if(baseIsoDir=="baseLowMET" && dirIso=="NonIso") Region = "Region C";
  if(baseIsoDir=="baseLowMET" && dirIso=="Iso")    Region = "Region D";

  cout << endl << endl <<"-------------: " << dirIso << "    " << Region << " :---------"<<endl;

  TAxis *axis = hData->GetXaxis();
  Int_t bmin = axis->FindBin(1);   //in your case xmin=0
  Int_t bmax = axis->FindBin(200); //in your case xmax=200
  double integralData = hData->Integral(bmin,bmax);
  double integralMC   = hMC->Integral(bmin,bmax);
  double integralDiff = hDiff->Integral(bmin,bmax);


  cout << setw(5)  << "bin"    << setw(10) << "Data" << setw(10) << "Err_Data" << setw(10) << "MC";
  cout << setw(10) << "Err_MC" << setw(10) << "Diff" << setw(10) << "Err_Diff" << endl;
  double sumD=0, sumMC=0, sumErrD=0, sumErrMC;
  for(int i=1; i<41; i++){
    sumD  = sumD  + hData->GetBinContent(i);
    sumMC = sumMC + hMC->GetBinContent(i);
    sumErrD  = sumErrD  + hData->GetBinError(i)*hData->GetBinError(i);
    sumErrMC = sumErrMC + hMC->GetBinError(i)*hData->GetBinError(i);
    double a1     = hData->GetBinContent(i);  double a1_err = hData->GetBinError(i);
    double a2     = hMC->GetBinContent(i);    double a2_err = hMC->GetBinError(i);
    double a3     = hDiff->GetBinContent(i);  double a3_err = hDiff->GetBinError(i);

    cout << setw(5)  << i  << setw(10) << a1 << setw(10) << a1_err;
    cout << setw(10) << a2 << setw(10) << a2_err;
    cout << setw(10) << a3 << setw(10) << a3_err <<endl;
  }

  double NDiff     = sumD-sumMC;
  double NDiff_Err = sqrt(sumErrD + sumErrMC);
  cout << "IntgData=" << integralData << "   IntgMC=" << integralMC << "   IntgDiff=" << integralDiff << endl; 
  cout << "NData="    << sumD  << "   ErrData="   << sqrt(sumErrD);
  cout << "   NMC="   << sumMC << "   ErrMC="     << sqrt(sumErrMC) << endl;
  cout << "NDiff="    << NDiff << "   NDiff_Err=" << NDiff_Err << endl << endl << endl;

  hDiff->SetMarkerStyle(20);  hDiff->SetMarkerSize(1.0);
  //hDiff->GetYaxis()->SetRangeUser(0, 2);
  hDiff->GetXaxis()->SetRangeUser(xmin, xmax);  hDiff->SetTitle("");
  hDiff->GetXaxis()->SetTitle(xaxis_title);     hDiff->GetYaxis()->SetTitleOffset(1.20);
  hDiff->GetYaxis()->SetTitle("QCD events (norm. to unity) "); hDiff->GetYaxis()->CenterTitle();
  hDiff->GetYaxis()->SetTitleSize(0.07);   hDiff->GetXaxis()->SetTitleSize(0.07);
  hDiff->GetXaxis()->SetLabelSize(0.05);   hDiff->GetYaxis()->SetLabelSize(0.05); 
  ///hDiff->Draw("e1"); // use "P" or "AP"
  //hDiff->Draw("E same");
  return hDiff;
}


void dataDrivenQCD_SF(){
  TString dirIso = "Iso";
  TString dirNonIso = "NonIso";
  TString dirBTag = "KinFit";
  TString histname = "mjj_kfit";
  int x_min = 0;
  int x_max = 200;
  TString x_title = "Mjj [GeV]";
  
  //Region D
  TH1F *hDiff = dataMCdiff(dirIso, dirBTag, histname, x_title, 1, true, true, x_min, x_max);

  //Region C
  TH1F *hDiff_NonIso = dataMCdiff(dirNonIso, dirBTag, histname, x_title, 1, true, true, x_min, x_max);

  int nbin= hDiff->GetSize();
  TH1F* hDiff_ratio = (TH1F*)hDiff->Clone("hDiff_ratio");
  hDiff_ratio->Divide(hDiff_NonIso);

  std::cout << std::setprecision(4);
  cout<<"------------ QCD SF --------------"<<endl;
  double sum=0,  sumwt2=0, neff=0;
  int    nent=0;

  cout << setw(5)  << "Bin"   << setw(10) << "SF_i"   << setw(10) << "SF_Err_i" << setw(5);
  cout << setw(10) << "Evt_i" << setw(10) << "Evt_Cum" << endl;

  for(int i=1; i<41; i++){
    double sf     = hDiff_ratio->GetBinContent(i); 
    double sf_err = hDiff_ratio->GetBinError(i);
    if(fabs(sf)<4.0 && fabs(sf)>1e-3){
      nent++;
      double wt = 1./(sf_err*sf_err);
      sumwt2 = sumwt2 + wt;
      sum = sum + wt*sf;
      double neff_bin = sf*sf*wt;
      neff = neff + neff_bin;
      cout << setw(5)  << i  << setw(10) << sf   << setw(10) << sf_err << setw(5);
      cout << setw(10) << neff_bin << setw(10) << neff << endl;
    }
  }
  double eff_sf     = sum/sumwt2;
  double eff_sf_err = eff_sf/sqrt(neff);
  cout << nent << "   sum=" << sum << "  sumwt2=" << sumwt2 << "    eff_sf=" << eff_sf;
  cout << "   neff=" << neff << "   eff_sf_err=" << eff_sf_err << endl;

  //Change directory from "baseLowMET" to "base" to access Region A and Region B
  baseIsoDir = "base";  

  //Region A
  TH1F *base_hDiff = dataMCdiff(dirIso, dirBTag, histname, x_title, 1, true, true, x_min, x_max);

  //Region B
  TH1F *base_hDiff_NonIso = dataMCdiff(dirNonIso, dirBTag, histname, x_title, 1, true, true, x_min, x_max);

  cout << setw(5)  << "Bin"   << setw(15) << "Intg_i"   << setw(15) << "bin_Err_i";
  cout << setw(15) << "Cum_Intg_i" << setw(15) << "Neff_i" << setw(15) << "Cum_Neff_i" << endl;

  nent=0; sum=0; neff=0;
  for(int i=1; i<41; i++){
    double intg_bin = base_hDiff_NonIso->GetBinContent(i); 
    double bin_err  = base_hDiff_NonIso->GetBinError(i);
    if(fabs(intg_bin)<4e10 && fabs(intg_bin)>1e-3){
      nent++;
      sum = sum + intg_bin;
      double neff_bin = (intg_bin/bin_err)*(intg_bin/bin_err);
      neff = neff + neff_bin;
      cout << setw(5)  << i  << setw(15) << intg_bin << setw(15) << bin_err << setw(15) << sum;
      cout << setw(15) << neff_bin << setw(15) << neff << endl;
    }
  }


  TCanvas *c1 = new TCanvas();
  gStyle->SetOptStat(11111111);
  gPad->SetBottomMargin(0.20);
  gPad->SetLeftMargin(0.20);
  gPad->SetRightMargin(0.05);
  hDiff_ratio->SetTitle("");
  hDiff_ratio->GetYaxis()->SetRangeUser(-10, 10);
  hDiff_ratio->GetYaxis()->SetTitle("QCD scale factors");
  hDiff_ratio->Draw("e1");
  if(isSaveHisto){
    TString outFile("$PWD/");
    if(isMuChannel)outFile += "qcdSF_mu_"+histname+".pdf";
    c1->SaveAs(outFile);
    //c1->Close();
  }
}

