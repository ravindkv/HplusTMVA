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
bool isMuChannel = false;
bool isEleChannel = true;

//INPUT FILES

//TFile* fData = TFile::Open("all_muData.root");
TFile* fData = TFile::Open("all_EleData.root");

TFile* fVV	= TFile::Open("all_VV.root");
TFile* fDY	= TFile::Open("all_DY.root");
TFile* fWJ	= TFile::Open("all_WJets.root");
TFile* fQCD	= TFile::Open("all_QCD.root");
TFile* fST	= TFile::Open("all_ST.root");
//TFile* fTT	= TFile::Open("all_TTJetsM.root");
TFile* fTT	= TFile::Open("all_TTJetsP.root");
TFile *fSig     = TFile::Open("all_Hplus120.root");
double sf_ttbar = 1.0; 

//USER'S INPUT FOR DATA DRIVEN QCD 
bool isDataDrivenQCD = true;
double qcd_sf_btag =  2.591 ; 
double qcd_sf_kfit = 1.902 ;
double qcd_sf_btag_err = 0.173;
double qcd_sf_kfit_err = 0.247;
TFile *f_QCD_dd = new TFile("all_QCD_dd.root","RECREATE");
  
//SAVE HISTOS ON DISK
bool isSaveHisto = true;
///////////////////////////////////////////  

//--------------------------------------------//
//various functions
//--------------------------------------------//
//UP error in the unc band
double errBandUp(int iBin, TH1F *hCentral, TH1F *hJESPlus, TH1F *hJERPlus, TH1F *bTagPlus, TH1F *cTagPlus, TH1F *PileupPlus, TH1F* hQCD_dd, double qcd_sf_err);
//down error in the unc band
double errBandDown(int iBin, TH1F *hCentral, TH1F *hJESMinus, TH1F *hJERMinus, TH1F *bTagMinus, TH1F *cTagMinus, TH1F* PileupMinus, TH1F* hQCD_dd, double qcd_sf_err);
//unc graph
TGraphAsymmErrors *UNCGRAPH(TH1F *hCentral, TH1F *hJESPlus, TH1F *hJESMinus, TH1F *hJERPlus, TH1F *hJERMinus, TH1F *bTagPlus, TH1F *bTagMinus, TH1F *cTagPlus, TH1F *cTagMinus, TH1F *PileupPlus, TH1F* PileupMinus, TH1F* hQCD_dd, double qcd_sf_err, bool isFullGraph = false, bool isRatioGraph = false);
//function to stack histos
void stackHisto(TFile *filename, TString lable, TString dir, TString histname, int color, double scale, bool axisrange, double xmin, double xmax, THStack* MuptStack, TH1F* hMC, TLegend* leg);
//qcd from data
TH1F* getDataDrivenQCD(TString dir, TString histname, double qcd_sf=1);
//function to add histograms
TH1F* addHistoForUnc(TString dir, TString histname, TString sys, bool isDataDrivenQCD = false, double qcd_sf=1);
TPaveText *paveText(double minX, double minY, double maxX, double maxY, int lineColor, int fillColor, int size, int style, int font );
//get histogram from root file. Return empty hist, if the hist does not exit.
TH1F* getHisto(TFile *histFile, TString histPath, TString dir, TString histName);

//--------------------------------------------//
//stack histos
//--------------------------------------------//
void example_stack(TString dir, TString histname, TString xaxis_title, int bin, bool log=false, bool drawdata=true, bool ratio=false, bool drawsignal=false, bool axisrange=false, double xmin=0, double xmax=10, bool label=false, double unc=false){
  //Pad
  gStyle->SetOptStat(0);
  gStyle->SetFrameLineWidth(3);
  TCanvas *c1 = new TCanvas();
  //TCanvas *c1 = new TCanvas("c1", "Data_MC", 400, 600);
  const float xpad[2] = {0.,1};
  const float ypad[4] = {0.,0.2351916,0.2351916,0.98};
  if(ratio){
    c1->Divide(1,2); c1->cd(1);
    if(!label) gPad->SetPad(xpad[0],ypad[2],xpad[1],ypad[3]);
    if(drawdata) gPad->SetLogy(log);
  }

 //Legends
  //for cutflow
  //TLegend* leg = new TLegend(0.8018792,0.3061504,1.012081,0.8798861,NULL,"brNDC");
  //for all others
  //signal
  TPaveText *cct = paveText(0.40,0.8554,0.50,0.8562, 0, 19, 1, 0, 132);
  cct->SetTextSize(0.07);
  cct->AddText("M_{H^{+}} = 120 GeV");
  ///cct->AddText("Br(t#rightarrow H^{+}b) = 0.1");
  TLegend* leg = new TLegend(0.7618792,0.3061504,0.9712081,0.8798861,NULL,"brNDC");
  string hist_name (histname);
  if(hist_name.find("pt") != string::npos || hist_name.find("mt") != string::npos){
    leg = new TLegend(0.6018792,0.5561504,0.9912081,0.8598861,NULL,"brNDC");
    leg->SetNColumns(2);
  }
  leg->SetFillStyle(0); leg->SetBorderSize(0);
  leg->SetFillColor(10); leg->SetTextSize(0.06);
  //Data
  TH1F* data = getHisto(fData, "base/Iso", dir, histname);
  //TH1F* data = (TH1F*)(fData->Get("base/Iso/"+dir+"/"+histname))->Clone("data");
  //data->SetBinErrorOption(TH1::kPoisson);
  data->SetMarkerStyle(20); data->SetMarkerSize(1.2);
  if(axisrange) data->GetXaxis()->SetRangeUser(xmin,xmax);
  data->SetFillColor(kBlack);
  //data->GetYaxis()->SetTitleOffset(1.35);
  ///data->Rebin(bin);
  data->SetTitle("");
  if(dir=="") data->SetAxisRange(1.0, 1.0e09 ,"Y");
  //else data->SetAxisRange(1.0, 1.0e6 ,"Y");
  if(drawdata)data->Draw("E"); 
  if(drawdata)leg->AddEntry(data,"Data","PE"); 
  data->GetYaxis()->SetTitle("Events");
  data->GetYaxis()->SetRangeUser(1, 3000);
  //data->GetYaxis()->SetRangeUser(1, 5.6* data->GetMaximum());
  data->GetXaxis()->SetTitle(xaxis_title);
  data->GetYaxis()->SetTitleOffset(0.70);
  data->GetXaxis()->SetTitleOffset(1.00);
  data->GetYaxis()->SetTitleSize(0.10);   data->GetXaxis()->SetTitleSize(0.07);
  data->GetXaxis()->SetLabelSize(0.07);   data->GetXaxis()->LabelsOption("u"); // extra
  data->GetYaxis()->SetLabelSize(0.07);   data->GetXaxis()->LabelsOption("u"); // extra
  data->GetXaxis()->SetTickLength(0.05); 
  data->GetYaxis()->SetTickLength(0.04); 
  if(drawdata)data->Draw("SAME"); 
  
  //VV is the base histo
  TH1F* h1_base = getHisto(fVV, "base/Iso", dir, histname);
  h1_base->SetFillColor(13);
  if(axisrange) h1_base->GetXaxis()->SetRangeUser(xmin,xmax);
  leg->AddEntry(h1_base,"VV","F");
  //Define stacked histo
  THStack* MuptStack = new THStack("MuptStack","");
  //MuptStack->SetMinimum(1.0);
  MuptStack->Add(h1_base);
  //hMC = all Bkg MC samples
  TH1F* hMC = (TH1F*)h1_base->Clone("hMC");
  
  //---------------------------
  // QCD from Data
  //---------------------------
  TH1F * hQCD_dd = getHisto(fQCD, "base/Iso", dir, histname);
  hQCD_dd->Add(hQCD_dd, -1); // initialize empty hist
  if(isDataDrivenQCD){
    if(dir=="BTag") hQCD_dd = getDataDrivenQCD(dir, histname, qcd_sf_btag);
    if(dir=="KinFit") hQCD_dd = getDataDrivenQCD(dir, histname, qcd_sf_kfit);
    else hQCD_dd = getDataDrivenQCD(dir, histname, qcd_sf_btag);
    hQCD_dd->SetFillColor(kGreen);
    if(axisrange)hQCD_dd->GetXaxis()->SetRangeUser(xmin,xmax);
    //create same dir to the data driven qcd file
    std::string histPath = std::string("base/Iso/"+dir);
    TDirectory *d = f_QCD_dd->GetDirectory(histPath.c_str());
    if(!d) f_QCD_dd->mkdir(histPath.c_str());
    f_QCD_dd->cd(histPath.c_str());
    //hQCD->Draw();
    hQCD_dd->Write();
    leg->AddEntry(hQCD_dd,"QCD","F");
    MuptStack->Add(hQCD_dd);
    hMC->Add(hQCD_dd);
  }
  else stackHisto(fQCD, "QCD", dir, histname, 3, 1, axisrange, xmin, xmax, MuptStack, hMC, leg);
  stackHisto(fDY, "Z/#gamma + jets", dir, histname, 9, 1, axisrange, xmin, xmax, MuptStack, hMC, leg);
  stackHisto(fST, "Single t", dir, histname, 800 , 1, axisrange, xmin, xmax, MuptStack, hMC, leg);
  stackHisto(fWJ, "W+ jets", dir, histname, 6 , 1, axisrange, xmin, xmax, MuptStack, hMC, leg);
  stackHisto(fTT,"t#bar{t} + jets", dir, histname, 433, sf_ttbar, axisrange, xmin, xmax, MuptStack, hMC, leg);

  //Signal 
  TH1F* hSig = getHisto(fSig, "base/Iso", dir, histname);
  //TH1F* hSig = (TH1F*)(fSig->Get("base/Iso/"+dirhistname))->Clone("Signal");
  hSig->SetLineColor(kRed); hSig->SetLineStyle(2);
  hSig->SetLineWidth(3); hSig->SetFillColor(0);
  if(axisrange) hSig->GetXaxis()->SetRangeUser(xmin,xmax);
  double yMax = 0;
  if(hMC->GetMaximum() > hSig->GetMaximum()) yMax = hMC->GetMaximum();
  else yMax = hSig->GetMaximum();
  cout<<yMax<<endl;
  hSig->SetTitle("");
  if(drawdata) hSig->GetYaxis()->SetRangeUser(1, 5*yMax);
  else hSig->GetYaxis()->SetRangeUser(1, 1.1*yMax);
  hSig->GetXaxis()->SetTitle(xaxis_title);
  hSig->GetXaxis()->SetTitleSize(0.07);
  hSig->GetXaxis()->SetTitleOffset(1.00);
  hSig->GetXaxis()->SetLabelSize(0.07);   
  hSig->GetXaxis()->LabelsOption("u"); // extra
  hSig->GetXaxis()->SetTickLength(0.05); 
  hSig->GetYaxis()->SetNdivisions(4);
  hSig->GetYaxis()->SetTitle("Events");
  hSig->GetYaxis()->SetTitleSize(0.10);   
  if(!ratio)hSig->GetYaxis()->SetTitleOffset(1.65);
  else hSig->GetYaxis()->SetTitleOffset(0.70);
  hSig->GetYaxis()->SetLabelSize(0.07);   
  hSig->GetYaxis()->SetTickLength(0.04); 
  hSig->Draw("HIST"); 
  //Draw stacked histo
  if(drawdata){
    gPad->SetBottomMargin(0.15);
    gPad->SetLeftMargin(0.15);
    gPad->SetRightMargin(0.05);
    MuptStack->Draw("HISTSAME");
  }
  else{
    //MuptStack->SetMaximum(1.1*(MuptStack->GetMaximum()));
    //MuptStack->SetMaximum(1.2*(hMC->GetMaximum()));
    cout<<hMC->GetMaximum()<<endl;
    cout<<hSig->GetMaximum()<<endl;
    gPad->SetLeftMargin(0.22);
    gPad->SetRightMargin(0.05);
    gPad->SetBottomMargin(0.20);
    hSig->GetXaxis()->SetTitleOffset(1.20);
    MuptStack->Draw("HISTSAME");
    //MuptStack->Draw("HIST");
  }

  //MuptStack->Draw("HISTSAME");
  if(drawdata)data->Draw("SAME"); 
  
  //hSigBkg = Bkg MC+ signal MC
  TH1F* hSigBkg = (TH1F*)hMC->Clone("hSigBkg"); 
  hSigBkg->Add(hSig); hSigBkg->SetLineStyle(2);
  hSigBkg->SetLineWidth(3); hSigBkg->SetFillColor(0);
  if(drawsignal)hSig->Draw("HISTSAME"); // only for hSig histogram 
  //if(drawsignal)hSigBkg->Draw("HISTSAME"); //  
  
  //-------------------------------------///
  //unc band
  //-------------------------------------///
  double qcd_sf = 1;
  double qcd_sf_err = 1;
  if(dir=="BTag"){ 
    qcd_sf = qcd_sf_btag;
    qcd_sf_err = qcd_sf_btag_err;
  }
  if(dir=="KinFit"){
    qcd_sf = qcd_sf_kfit;
    qcd_sf_err = qcd_sf_kfit_err;
  }
  if(unc){
  TGraphAsymmErrors *UncBand;
  UncBand = UNCGRAPH(addHistoForUnc(dir, histname, "base", isDataDrivenQCD, qcd_sf),
      	    addHistoForUnc(dir, histname, "JESPlus", isDataDrivenQCD, qcd_sf),
      	    addHistoForUnc(dir, histname, "JESMinus", isDataDrivenQCD, qcd_sf),
      	    addHistoForUnc(dir, histname, "JERPlus", isDataDrivenQCD, qcd_sf),
      	    addHistoForUnc(dir, histname, "JERMinus", isDataDrivenQCD, qcd_sf),
      	    addHistoForUnc(dir, histname, "bTagPlus", isDataDrivenQCD, qcd_sf),
      	    addHistoForUnc(dir, histname, "bTagMinus", isDataDrivenQCD, qcd_sf),
      	    addHistoForUnc(dir, histname, "cTagPlus", isDataDrivenQCD, qcd_sf),
      	    addHistoForUnc(dir, histname, "cTagMinus", isDataDrivenQCD, qcd_sf),
      	    addHistoForUnc(dir, histname, "PileupPlus", isDataDrivenQCD, qcd_sf),
      	    addHistoForUnc(dir, histname, "PileupMinus", isDataDrivenQCD, qcd_sf),
	    hQCD_dd, qcd_sf_err, true, false);
  UncBand->SetFillColor(1);
  UncBand->SetFillStyle(3017);
  UncBand->Draw(" E2 same");
  leg->AddEntry(UncBand, "Unc","F"); 
  }
  leg->AddEntry(hSig, "Signal","L"); 
  leg->Draw();
  
  //-------------------------------------///
  //  Draw Pave Text 
  //-------------------------------------///
  
  //hist name
  TPaveText *hLable = paveText(0.6513423,0.7754898,0.6010067,0.8962187, 0, 19, 1, 0, 132);
  hLable->SetTextSize(0.080);
  hLable->AddText(xaxis_title);
  
  //channel
  TPaveText *ch = paveText(0.803,0.9154898,0.9010067,0.9762187, 0, 19, 1, 0, 132);
  ch->SetTextSize(0.10);
  if(isMuChannel) ch->AddText("#mu + jets");
  if(isEleChannel) ch->AddText("e + jets");
  //CMS prili
  TPaveText *pt = paveText(0.12,0.9354,0.82,0.9362, 0, 19, 1, 0, 132);
  if(drawdata) pt->SetTextSize(0.065);
  else pt->SetTextSize(0.049);
  TText *text = pt->AddText(dir+": CMS Preliminary, #sqrt{s} = 13 TeV, 35.9 fb^{-1}");
  text->SetTextAlign(11);
  pt->Draw();
  if(drawsignal) cct->Draw();
  ch->Draw();
  //hLable->Draw();
  gPad->RedrawAxis();
  c1->Update();
  
  //-------------------------------------///
  // Ratio = DATA/Bkg
  //-------------------------------------///
  if(ratio){
    c1->cd(2);
    gPad->SetTopMargin(0); gPad->SetBottomMargin(0.5); //gPad->SetGridy();
    gPad->SetLeftMargin(0.15);
    gPad->SetRightMargin(0.05);
    if(!label) gPad->SetPad(xpad[0],ypad[0],xpad[1],ypad[2]);
    TH1F *hRatio = (TH1F*)data->Clone("hRatio");
    hRatio->Reset();
    hRatio->Add(data);
    hRatio->GetYaxis()->SetNdivisions(5);
    //hRatio->Add(hMC, -1);
    hRatio->Divide(hMC); hRatio->SetMarkerStyle(20); hRatio->SetMarkerSize(1.2);
    hRatio->SetMarkerColor(kBlack); hRatio->SetLineColor(kBlack); hRatio->GetYaxis()->SetRangeUser(0.5, 1.5);
    //hRatio->GetXaxis()->SetRangeUser(xmin, xmax);
    hRatio->GetXaxis()->SetTickLength(0.13); 
    hRatio->GetYaxis()->SetTickLength(0.04); 
    hRatio->GetXaxis()->SetTitle(xaxis_title); 
    hRatio->GetYaxis()->SetTitleOffset(0.27);
    hRatio->GetXaxis()->SetTitleOffset(0.80);
    hRatio->GetYaxis()->SetTitle("#frac{Data}{Bkg}"); hRatio->GetYaxis()->CenterTitle();
    if(!label){
      hRatio->GetYaxis()->SetTitleSize(0.22); hRatio->GetXaxis()->SetTitleSize(0.23);
      hRatio->GetXaxis()->SetLabelSize(0.19); hRatio->GetXaxis()->LabelsOption("u"); // extra
      hRatio->GetYaxis()->SetLabelSize(0.13); hRatio->GetXaxis()->LabelsOption("u"); // extra
    }
  //lable x-axis, for cutflow
  if(label){
    vector<string >cut_label;
    if(isEleChannel){
      cut_label.push_back("Ele trigger");
      cut_label.push_back("No. of ele = 1");
      cut_label.push_back("No. of mu =0");
      cut_label.push_back("Ele SF");
      cut_label.push_back("Ele rel iso < 0.8");
    }
    if(isMuChannel){
      cut_label.push_back("Mu trigger");
      cut_label.push_back("No. of mu = 1");
      cut_label.push_back("No. of ele =0");
      cut_label.push_back("Mu SF");
      cut_label.push_back("Mu rel iso < 0.15");
    }
    cut_label.push_back("No. of jets #geq 4");
    cut_label.push_back("MET #geq 20 GeV");
    cut_label.push_back("No. of bjets #geq 2");
    cut_label.push_back("btag SF");
    cut_label.push_back("KinFit converges");
    cut_label.push_back("Pt of KF jets >25 GeV");
    cut_label.push_back("#DeltaR (KF, PF) jets <0.2");
    cut_label.push_back("Loose c-tag");
    cut_label.push_back("c-tag SF");
    for(int istep=0; istep<cut_label.size(); istep++ ){
      const char *label; 
      hRatio->GetXaxis()->SetBinLabel(istep+1, cut_label[istep].c_str());
      //hRatio->GetXaxis()->SetLabelFont(62);
      gPad->SetBottomMargin(0.6); //gPad->SetGridy();
      hRatio->GetXaxis()->SetLabelOffset(0.04);
      hRatio->GetXaxis()->SetLabelSize(0.12);
      hRatio->GetXaxis()->LabelsOption("v");
      hRatio->GetXaxis()->SetTickLength(0.08); 
      hRatio->GetXaxis()->SetTitleOffset(1.20);
      hRatio->GetYaxis()->SetTitleOffset(1.00);
    }
  }
    //unc band
    hRatio->Draw("E"); // use "P" or "AP"
    if(unc){
    TGraphAsymmErrors *UncBand_Ratio;
    UncBand_Ratio = UNCGRAPH(addHistoForUnc(dir, histname, "base", isDataDrivenQCD, qcd_sf),
      	    addHistoForUnc(dir, histname, "JESPlus", isDataDrivenQCD, qcd_sf),
      	    addHistoForUnc(dir, histname, "JESMinus", isDataDrivenQCD, qcd_sf),
      	    addHistoForUnc(dir, histname, "JERPlus", isDataDrivenQCD, qcd_sf),
      	    addHistoForUnc(dir, histname, "JERMinus", isDataDrivenQCD, qcd_sf),
      	    addHistoForUnc(dir, histname, "bTagPlus", isDataDrivenQCD, qcd_sf),
      	    addHistoForUnc(dir, histname, "bTagMinus", isDataDrivenQCD, qcd_sf),
      	    addHistoForUnc(dir, histname, "cTagPlus", isDataDrivenQCD, qcd_sf),
      	    addHistoForUnc(dir, histname, "cTagMinus", isDataDrivenQCD, qcd_sf),
      	    addHistoForUnc(dir, histname, "PileupPlus", isDataDrivenQCD, qcd_sf),
      	    addHistoForUnc(dir, histname, "PileupMinus", isDataDrivenQCD, qcd_sf),
	    hQCD_dd, qcd_sf_err, false, true);
    UncBand_Ratio->SetFillColor(45);
    UncBand_Ratio->SetFillStyle(3001);
    UncBand_Ratio->Draw("E2 same");
    }
    hRatio->Draw("E same"); // use "P" or "AP"
    //base line at 1
    TF1 *baseLine = new TF1("baseLine","1", -100, 2000); 
    baseLine->SetLineColor(kBlack);
    baseLine->Draw("SAME");
    c1->Update();
  }
  if(isSaveHisto){
    TString outFile("$PWD/");
    outFile += dir+"/"+histname;
    //if(isMuChannel) outFile += "_mu"+dir+".png";
    //if(isEleChannel) outFile += "_ele"+dir+".png";
    if(isMuChannel) outFile += "_mu"+dir+".pdf";
    if(isEleChannel) outFile += "_ele"+dir+".pdf";
    c1->SaveAs(outFile);
    c1->Close();
  }
}

double errBandUp(int iBin, TH1F *hCentral, TH1F *hJESPlus, TH1F *hJERPlus, TH1F *bTagPlus, TH1F *cTagPlus, TH1F* PileupPlus, TH1F *hQCD_dd, double qcd_sf_err){
  double errUp = sqrt(pow(fabs(hJESPlus->GetBinContent(iBin+1) - hCentral->GetBinContent(iBin+1)),2) + 
		  pow(fabs(hJERPlus->GetBinContent(iBin+1) - hCentral->GetBinContent(iBin+1)),2) + 
		  pow(fabs(bTagPlus->GetBinContent(iBin+1) - hCentral->GetBinContent(iBin+1)),2) + 
		  pow(fabs(cTagPlus->GetBinContent(iBin+1) - hCentral->GetBinContent(iBin+1)),2) + 
		  pow(fabs(PileupPlus->GetBinContent(iBin+1) - hCentral->GetBinContent(iBin+1)),2) + 
		  pow(hCentral->GetBinError(iBin+1),2)+ pow(qcd_sf_err*hQCD_dd->GetBinContent(iBin+1),2));
  return errUp;
}

double errBandDown(int iBin, TH1F *hCentral, TH1F *hJESMinus, TH1F *hJERMinus, TH1F *bTagMinus, TH1F *cTagMinus, TH1F* PileupMinus, TH1F *hQCD_dd, double qcd_sf_err){
  double errDown =sqrt(pow(fabs(hCentral->GetBinContent(iBin+1) - hJESMinus->GetBinContent(iBin+1)),2) + 
		  pow(fabs(hCentral->GetBinContent(iBin+1) - hJERMinus->GetBinContent(iBin+1)),2) + 
		  pow(fabs(hCentral->GetBinContent(iBin+1) - bTagMinus->GetBinContent(iBin+1)),2) + 
		  pow(fabs(hCentral->GetBinContent(iBin+1) - cTagMinus->GetBinContent(iBin+1)),2) + 
		  pow(fabs(hCentral->GetBinContent(iBin+1) - PileupMinus->GetBinContent(iBin+1)),2) + 
		  pow(hCentral->GetBinError(iBin+1),2)+pow(qcd_sf_err*hQCD_dd->GetBinContent(iBin+1),2));
  return errDown;
}

TGraphAsymmErrors *UNCGRAPH(TH1F *hCentral, TH1F *hJESPlus, TH1F *hJESMinus, TH1F *hJERPlus, TH1F *hJERMinus, TH1F *bTagPlus, TH1F *bTagMinus, TH1F *cTagPlus, TH1F *cTagMinus, TH1F* PileupPlus, TH1F* PileupMinus, TH1F* hQCD_dd, double qcd_sf_err, bool isFullGraph = false, bool isRatioGraph = false){
  TGraphAsymmErrors *gr;
  int n1 = hCentral->GetNbinsX(); 
  double *Yval, *errorU, *errorD, *XerrorU, *XerrorD, *Xval ;
  Yval = new double[n1]; errorU = new double[n1]; errorD = new double[n1];
  XerrorU=new double[n1]; XerrorD=new double[n1]; Xval=new double[n1];
  //cout << "No. of bins= " << n1 << endl;
  for(int i=0; i<n1; i++){
    if(isFullGraph){
    Yval[i]   = hCentral->GetBinContent(i+1);
    errorU[i] = errBandUp(i, hCentral, hJESPlus, hJERPlus, bTagPlus, cTagPlus, PileupPlus, hQCD_dd, qcd_sf_err); 
    errorD[i] = errBandDown(i, hCentral, hJESMinus, hJERMinus, bTagMinus, cTagMinus, PileupMinus, hQCD_dd, qcd_sf_err); 
    }
    if(isRatioGraph){
    Yval[i]   = 1;
    errorU[i] = errBandUp(i, hCentral, hJESPlus, hJERPlus, bTagPlus, cTagPlus, PileupPlus, hQCD_dd, qcd_sf_err); 
    errorD[i] = errBandDown(i, hCentral, hJESMinus, hJERMinus, bTagMinus, cTagMinus, PileupMinus, hQCD_dd, qcd_sf_err); 
    //cout<<"bin = "<<i<<endl;
    //cout<<Yval[i]<<"\t"<<errorU[i]<<"\t"<<hCentral->GetBinContent(i+1)<<endl;
    errorU[i] = errorU[i]/hCentral->GetBinContent(i+1);
    errorD[i] = errorD[i]/hCentral->GetBinContent(i+1);
    //cout<<Yval[i]<<"\t"<<errorU[i]<<"\t"<<hCentral->GetBinContent(i+1)<<endl;
    }
    Xval[i]   = hCentral->GetBinCenter(i+1);
    XerrorU[i]= hCentral->GetBinWidth(i+1)/2;
    XerrorD[i]= hCentral->GetBinWidth(i+1)/2;
  }
  gr = new TGraphAsymmErrors(n1, Xval, Yval, XerrorD, XerrorU, errorD, errorU);
  return gr;
  delete [] Yval; delete [] errorU; delete [] errorD; delete [] XerrorU; delete [] XerrorD; delete [] Xval;
} 

TH1F* getHisto(TFile *histFile, TString histPath, TString dir, TString histName){
  TH1F* hist; 
  if(!(histFile->Get(histPath+"/"+dir+"/"+histName))){
    hist = (TH1F*)(fTT->Get(histPath+"/"+dir+"/"+histName))->Clone(histName);
    hist->Add(hist, -1);
  }else hist = (TH1F*)(histFile->Get(histPath+"/"+dir+"/"+histName))->Clone(histName);
  return hist;
}

void stackHisto(TFile *filename, TString lable, TString dir, TString histname, int color, double scale, bool axisrange, double xmin, double xmax, THStack* MuptStack, TH1F* hMC, TLegend* leg){
  TH1F* h2_base = getHisto(filename, "base/Iso", dir, histname);
  //h2_base->Draw();
  h2_base->Scale(scale);  
  h2_base->SetFillColor(color);
  if(axisrange){
    h2_base->GetXaxis()->SetRangeUser(xmin,xmax);
  }
  leg->AddEntry(h2_base,lable,"F");
  MuptStack->Add(h2_base);
  hMC->Add(h2_base);
}


TH1F* getDataDrivenQCD(TString dir, TString histname, double qcd_sf=1){
  
  TH1F* hVV = getHisto(fVV, "base/NonIso", dir, histname); 
  TH1F* hDY = getHisto(fDY, "base/NonIso", dir, histname); 
  TH1F* hWJ = getHisto(fWJ, "base/NonIso", dir, histname); 
  TH1F* hST = getHisto(fST, "base/NonIso", dir, histname); 
  TH1F* hTT = getHisto(fTT, "base/NonIso", dir, histname); 
  TH1F* hData = getHisto(fData, "base/NonIso", dir, histname); 
  TH1F* hOtherMC = (TH1F*)hVV->Clone("hOtherMC"); 
  hOtherMC->Add(hDY); 
  hOtherMC->Add(hST); 
  hOtherMC->Add(hWJ); 
  hOtherMC->Add(hTT); 
  TH1F* hQCD = (TH1F*)hData->Clone(histname); 
  hQCD->Add(hOtherMC, -1);
  hQCD->Scale(qcd_sf);
  return hQCD;
}

TH1F* addHistoForUnc(TString dir, TString histname, TString sys, bool isDataDrivenQCD = false, double qcd_sf=1){
  TH1F* hVV = getHisto(fVV, sys+"/Iso", dir, histname); 
  TH1F* hDY = getHisto(fDY, sys+"/Iso", dir, histname); 
  TH1F* hQCD_mc = getHisto(fQCD, sys+"/Iso", dir, histname); 
  TH1F* hWJ = getHisto(fWJ, sys+"/Iso", dir, histname); 
  TH1F* hST = getHisto(fST, sys+"/Iso", dir, histname); 
  TH1F* hTT = getHisto(fTT, sys+"/Iso", dir, histname); 
  TH1F* hAll = (TH1F*)hVV->Clone("hAllMC");
  hAll->Add(hDY);
  hAll->Add(hWJ);
  hAll->Add(hST);
  hAll->Add(hTT);
  if(isDataDrivenQCD) hQCD_mc = getDataDrivenQCD(dir, histname, qcd_sf);
  hAll->Add(hQCD_mc);
  return hAll;
}

TPaveText *paveText(double minX, double minY, double maxX, double maxY, int lineColor, int fillColor, int size, int style, int font ){
  TPaveText *pt = new TPaveText(minX, minY, maxX, maxY, "brNDC"); // good_v1
  pt->SetBorderSize(size);
  pt->SetFillColor(fillColor);
  pt->SetFillStyle(style);
  pt->SetLineColor(lineColor);
  pt->SetTextFont(font);
  return pt;
}
void example_stack_all(){
  example_stack("", "cutflow", "cutflow", 1, true, true, true, true, true, 0, 18, true, false);
  /*
  if(isMuChannel)
  example_stack("", "RelIso", "I_{rel}^{#mu}", 1, true, true, true, true, true, 0, 0.4, false, false);
  example_stack("", "pt_met","MET", 1, true,true,true,true, true,        0.0,    500, false, false);
 if(isEleChannel)
  example_stack("", "RelIso", "I_{rel}^{ele}", 1, true, true, true, true, true, 0, 0.4, false, false);
  example_stack("", "pt_met","MET", 1, true,true,true,true, true,        0.0,    500, false, false);
  */
}

//void example_stack(TString dir, TString histname, TString xaxis_title, int bin, bool log=false, bool drawdata=true, bool ratio=false, bool drawsignal=false, bool axisrange=false, double xmin=0, double xmax=10, bool label=false, double unc=false){

//void example_stack_btag(TString dir="BTag"){//dir=KinFit, BTag
void example_stack_kfit(TString dir="KinFit"){//dir=KinFit, BTag
//void example_stack_kfit(TString dir="PtbJetInc"){//dir=KinFit, BTag
  if(isMuChannel){
   example_stack(dir,"pt_mu","Pt^{#mu} [GeV]", 1, true,true,true,true, true,   0.0,    500.0, false, true);
   example_stack(dir,"eta_mu","#eta^{#mu}", 1, true,true,true,true,true,       -3.0,   4.5,  false,  true);
   //example_stack(dir, "final_RelIso_mu", "I_{rel}^{#mu}", 1, true, true, true, true, true, 0, 0.15, false, true);
 }
 if(isEleChannel){
   example_stack(dir,"pt_ele","Pt^{e} [GeV]", 1, true,true,true,true, true,   0.0,    500.0, false, true);
   example_stack(dir,"eta_ele","#eta^{e}", 1, true,true,true,true,true,       -3.0,   4.5,  false,  true);
   //example_stack(dir, "final_RelIso_ele", "I_{rel}^{ele}", 1, true, true, true, true, true, 0, 1, false, true);
 }
 example_stack(dir,"pt_jet","Pt^{jets} [GeV]", 1, true,true,true,true, true,  0.0,    500,  false, true);
 example_stack(dir,"eta_jet","#eta^{jets}", 1, true,true,true,true,true,     -3.0,   4.5,  false, true);
 example_stack(dir,"final_multi_jet","N^{jets}",1,true,true,true,true,true,   3,      15,  false, true);
 example_stack(dir,"final_pt_met","E_{T}^{miss}[GeV]", 1, true,true,true,true, true,        0.0,    500, false, true);
 example_stack(dir,"CSVL_count","N^{b-jets}",1,true,true, true,true,true,       1,      10,  false, true);
 example_stack(dir,"nvtx","N^{vertex}",1,true,true,true,true, true,           0.0,    70.0,  false, true);
 example_stack(dir,"rhoAll","#rho",1,true,true,true,true, true,               0.0,    70.0,  false, true);
 if(dir=="BTag"){
   //example_stack(dir,"mjj","M_{jj}",1,false,false,false,true, true,                 0.0,    400.0, false, false);
   example_stack(dir,"wmt","MT[GeV]",1,true,true,true,true,true,                0,      500,   false, true);
   example_stack(dir,"pfCISV","pfCISV2BJetTags",1,true,true, true,true,true,   0.0, 1.3, false, true);
 }
 if(dir=="KinFit"){
   /*
   example_stack(dir, "mjj_kfit","M_{jj}[GeV]",1, false, false, false, true, true,      0.0,    200.0,  false, false);
   example_stack(dir,"mjj_kfit_CTagL_SF","M_{jj}^{Inc_CTagL}[GeV]",1,true,false, false, true, true,  0.0,    200.0,  false,  false);
   example_stack(dir,"mjj_kfit_CTagM_SF","M_{jj}^{Inc_CTagM}[GeV]",1,true,false, false, true, true,   0.0,    200.0, false,  false);
   example_stack(dir,"mjj_kfit_CTagT_SF","M_{jj}^{Inc_CTagT}[GeV]",1,true,false, false, true, true,   0.0,    200.0,  false, false);
   example_stack(dir,"mjj_kfit_CTagO_SF_Cat","M_{jj}^{Ex_CTagO}[GeV]",1,true,false, false, true, true,   0.0,    200.0,  false, false);
   example_stack(dir,"mjj_kfit_CTagL_SF_Cat","M_{jj}^{Ex_CTagL}[GeV]",1,true,false, false, true, true,  0.0,    200.0,  false,  false);
   example_stack(dir,"mjj_kfit_CTagM_SF_Cat","M_{jj}^{Ex_CTagM}[GeV]",1,true,false, false, true, true,   0.0,    200.0, false,  false);
   example_stack(dir,"mjj_kfit_CTagT_SF_Cat","M_{jj}^{Ex_CTagT}[GeV]",1,true,false, false, true, true,   0.0,    200.0,  false, false);
   */
   //example_stack(dir,"pt_bjetH","Pt_{bjet}^{Had} [GeV]", 1, true,false,false,true, true,  0.0,    300,  false, false);
   example_stack(dir,"pfCCvsL","pfCombinedCvsLJetTags",1,true,true, true,true,true,   -1.5, 2, false, true);
   example_stack(dir,"pfCCvsB","pfCombinedCvsBJetTags",1,true,true, true,true,true,   -1.5, 2, false, true);
   example_stack(dir,"wmt","MT[GeV]",1,true,true,true,true,true,                0,      250,   false, true);
 }
 if(dir=="PtbJetInc"){
   example_stack("KinFit", "mjj_kfit","M_{jj}[GeV]",1, false, false, false, true, true,      0.0,    200.0,  false, false);
   example_stack("KinFit","mjj_kfit_CTagL_SF","M_{jj}^{Inc_CTagL}[GeV]",1,true,false, false, true, true,  0.0,    200.0,  false,  false);
   example_stack("KinFit","mjj_kfit_CTagM_SF","M_{jj}^{Inc_CTagM}[GeV]",1,true,false, false, true, true,   0.0,    200.0, false,  false);
   example_stack("KinFit","mjj_kfit_CTagT_SF","M_{jj}^{Inc_CTagT}[GeV]",1,true,false, false, true, true,   0.0,    200.0,  false, false);
   example_stack("KinFit","mjj_kfit_CTagO_SF_Cat","M_{jj}^{Ex_CTagO}[GeV]",1,true,false, false, true, true,   0.0,    200.0,  false, false);
   example_stack("KinFit","mjj_kfit_CTagL_SF_Cat","M_{jj}^{Ex_CTagL}[GeV]",1,true,false, false, true, true,  0.0,    200.0,  false,  false);
   example_stack("KinFit","mjj_kfit_CTagM_SF_Cat","M_{jj}^{Ex_CTagM}[GeV]",1,true,false, false, true, true,   0.0,    200.0, false,  false);
   example_stack("KinFit","mjj_kfit_CTagT_SF_Cat","M_{jj}^{Ex_CTagT}[GeV]",1,true,false, false, true, true,   0.0,    200.0,  false, false);

   example_stack(dir,"mjj_kfit_25To35","m^{jj}_{00To35}",1,true,true, true, true, true,   0.0,    200.0,  false, false);
   example_stack(dir,"mjj_kfit_35To42","m^{jj}_{35To42}",1,true,true, true, true, true,  0.0,    200.0,  false,  false);
   example_stack(dir,"mjj_kfit_42To50","m^{jj}_{42To50}",1,true,true, true, true, true,   0.0,    200.0, false,  false);
   example_stack(dir,"mjj_kfit_50To57","m^{jj}_{50To57}",1,true,true, true, true, true,   0.0,    200.0,  false, false);
   example_stack(dir,"mjj_kfit_57To65","m^{jj}_{57To65}",1,true,true, true, true, true,   0.0,    200.0,  false, false);
   example_stack(dir,"mjj_kfit_65To74","m^{jj}_{65To74}",1,true,true, true, true, true,  0.0,    200.0,  false,  false);
   example_stack(dir,"mjj_kfit_74To84","m^{jj}_{74To84}",1,true,true, true, true, true,   0.0,    200.0, false,  false);
   example_stack(dir,"mjj_kfit_84To99","m^{jj}_{84To99}",1,true,true, true, true, true,   0.0,    200.0,  false, false);
   example_stack(dir,"mjj_kfit_99To124","m^{jj}_{99To124}",1,true,true, true, true, true,   0.0,    200.0, false,  false);
   example_stack(dir,"mjj_kfit_124To500","m^{jj}_{124To500}",1,true,true, true, true, true,   0.0,    200.0,  false, false);
   
   example_stack("PtbJetCatL","mjj_kfit_25To35"  ,"mjj_kfit_25To35",1,true,false, false, true, true,   0.0,    200.0,  false, false);
   example_stack("PtbJetCatL","mjj_kfit_35To42"  ,"mjj_kfit_35To42",1,true,false, false, true, true,   0.0,    200.0,  false, false);
   example_stack("PtbJetCatL","mjj_kfit_42To50"  ,"mjj_kfit_42To50",1,true,false, false, true, true,   0.0,    200.0,  false, false);
   example_stack("PtbJetCatL","mjj_kfit_50To57"  ,"mjj_kfit_50To57",1,true,false, false, true, true,   0.0,    200.0,  false, false);
   example_stack("PtbJetCatL","mjj_kfit_57To65"  ,"mjj_kfit_57To65",1,true,false, false, true, true,   0.0,    200.0,  false, false);
   example_stack("PtbJetCatL","mjj_kfit_65To74"  ,"mjj_kfit_65To74",1,true,false, false, true, true,   0.0,    200.0,  false, false);
   example_stack("PtbJetCatL","mjj_kfit_74To84"  ,"mjj_kfit_74To84",1,true,false, false, true, true,   0.0,    200.0,  false, false);
   example_stack("PtbJetCatL","mjj_kfit_84To99"  ,"mjj_kfit_84To99",1,true,false, false, true, true,   0.0,    200.0,  false, false);
   example_stack("PtbJetCatL","mjj_kfit_99To124"  ,"mjj_kfit_99To124",1,true,false, false, true, true,   0.0,    200.0,  false, false);
   example_stack("PtbJetCatL","mjj_kfit_124To500"  ,"mjj_kfit_124To500",1,true,false, false, true, true,   0.0,    200.0,  false, false);

   example_stack("PtbJetCatM","mjj_kfit_25To35"  ,"mjj_kfit_25To35",1,true,false, false, true, true,   0.0,    200.0,  false, false);
   example_stack("PtbJetCatM","mjj_kfit_35To42"  ,"mjj_kfit_35To42",1,true,false, false, true, true,   0.0,    200.0,  false, false);
   example_stack("PtbJetCatM","mjj_kfit_42To50"  ,"mjj_kfit_42To50",1,true,false, false, true, true,   0.0,    200.0,  false, false);
   example_stack("PtbJetCatM","mjj_kfit_50To57"  ,"mjj_kfit_50To57",1,true,false, false, true, true,   0.0,    200.0,  false, false);
   example_stack("PtbJetCatM","mjj_kfit_57To65"  ,"mjj_kfit_57To65",1,true,false, false, true, true,   0.0,    200.0,  false, false);
   example_stack("PtbJetCatM","mjj_kfit_65To74"  ,"mjj_kfit_65To74",1,true,false, false, true, true,   0.0,    200.0,  false, false);
   example_stack("PtbJetCatM","mjj_kfit_74To84"  ,"mjj_kfit_74To84",1,true,false, false, true, true,   0.0,    200.0,  false, false);
   example_stack("PtbJetCatM","mjj_kfit_84To99"  ,"mjj_kfit_84To99",1,true,false, false, true, true,   0.0,    200.0,  false, false);
   example_stack("PtbJetCatM","mjj_kfit_99To124"  ,"mjj_kfit_99To124",1,true,false, false, true, true,   0.0,    200.0,  false, false);
   example_stack("PtbJetCatM","mjj_kfit_124To500"  ,"mjj_kfit_124To500",1,true,false, false, true, true,   0.0,    200.0,  false, false);

   example_stack("PtbJetCatT","mjj_kfit_25To35"  ,"mjj_kfit_25To35",1,true,false, false, true, true,   0.0,    200.0,  false, false);
   example_stack("PtbJetCatT","mjj_kfit_35To42"  ,"mjj_kfit_35To42",1,true,false, false, true, true,   0.0,    200.0,  false, false);
   example_stack("PtbJetCatT","mjj_kfit_42To50"  ,"mjj_kfit_42To50",1,true,false, false, true, true,   0.0,    200.0,  false, false);
   example_stack("PtbJetCatT","mjj_kfit_50To57"  ,"mjj_kfit_50To57",1,true,false, false, true, true,   0.0,    200.0,  false, false);
   example_stack("PtbJetCatT","mjj_kfit_57To65"  ,"mjj_kfit_57To65",1,true,false, false, true, true,   0.0,    200.0,  false, false);
   example_stack("PtbJetCatT","mjj_kfit_65To74"  ,"mjj_kfit_65To74",1,true,false, false, true, true,   0.0,    200.0,  false, false);
   example_stack("PtbJetCatT","mjj_kfit_74To84"  ,"mjj_kfit_74To84",1,true,false, false, true, true,   0.0,    200.0,  false, false);
   example_stack("PtbJetCatT","mjj_kfit_84To99"  ,"mjj_kfit_84To99",1,true,false, false, true, true,   0.0,    200.0,  false, false);
   example_stack("PtbJetCatT","mjj_kfit_99To124"  ,"mjj_kfit_99To124",1,true,false, false, true, true,   0.0,    200.0,  false, false);
   example_stack("PtbJetCatT","mjj_kfit_124To500"  ,"mjj_kfit_124To500",1,true,false, false, true, true,   0.0,    200.0,  false, false);

   example_stack("PtbJetCatO","mjj_kfit_25To35"  ,"mjj_kfit_25To35",1,true,false, false, true, true,   0.0,    200.0,  false, false);
   example_stack("PtbJetCatO","mjj_kfit_35To42"  ,"mjj_kfit_35To42",1,true,false, false, true, true,   0.0,    200.0,  false, false);
   example_stack("PtbJetCatO","mjj_kfit_42To50"  ,"mjj_kfit_42To50",1,true,false, false, true, true,   0.0,    200.0,  false, false);
   example_stack("PtbJetCatO","mjj_kfit_50To57"  ,"mjj_kfit_50To57",1,true,false, false, true, true,   0.0,    200.0,  false, false);
   example_stack("PtbJetCatO","mjj_kfit_57To65"  ,"mjj_kfit_57To65",1,true,false, false, true, true,   0.0,    200.0,  false, false);
   example_stack("PtbJetCatO","mjj_kfit_65To74"  ,"mjj_kfit_65To74",1,true,false, false, true, true,   0.0,    200.0,  false, false);
   example_stack("PtbJetCatO","mjj_kfit_74To84"  ,"mjj_kfit_74To84",1,true,false, false, true, true,   0.0,    200.0,  false, false);
   example_stack("PtbJetCatO","mjj_kfit_84To99"  ,"mjj_kfit_84To99",1,true,false, false, true, true,   0.0,    200.0,  false, false);
   example_stack("PtbJetCatO","mjj_kfit_99To124"  ,"mjj_kfit_99To124",1,true,false, false, true, true,   0.0,    200.0,  false, false);
   example_stack("PtbJetCatO","mjj_kfit_124To500"  ,"mjj_kfit_124To500",1,true,false, false, true, true,   0.0,    200.0,  false, false);
  }
} 

