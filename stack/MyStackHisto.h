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
#include <sys/stat.h>
#include <stdlib.h>
#include <algorithm>
#include <iterator>
#include "TPad.h"
#include "TLatex.h"
#include "TLine.h"
#include "TBox.h"
#include "TASImage.h"

using namespace std;

//R. K. Verma
//Sat Jul 14 14:47:08 IST 2018

//CHANNEL
bool isMuChannel = true;
bool isEleChannel = false;
//SAVE HISTOS ON DISK
bool isSaveHisto = true;
//INPUT FILES
TFile* fData = TFile::Open("all_Data.root");
TFile* fVV	= TFile::Open("all_VV.root");
TFile* fDY	= TFile::Open("all_DY.root");
TFile* fWJ	= TFile::Open("all_WJets.root");
TFile* fQCD	= TFile::Open("all_QCD.root");
TFile* fST	= TFile::Open("all_ST.root");
TFile* fTT	= TFile::Open("all_TTJetsP.root");
TFile *fSig     = TFile::Open("all_Hplus120.root");
TString baseDir = "baseLowMET/";

//-----------------------
// CMS guidelines for fig
// https://twiki.cern.ch/twiki/bin/view/CMS/Internal/FigGuidelines
//-----------------------
TString cmsText     = "CMS";
float cmsTextFont   = 61;  // default is helvetic-bold
bool writeExtraText = true;
TString extraText   = "Preliminary";
float extraTextFont = 52;  // default is helvetica-italics
// text sizes and text offsets with respect to the top frame
// in unit of the top margin size
float lumiTextSize     = 0.6;
float lumiTextOffset   = 0.2;
float cmsTextSize      = 0.75;
float cmsTextOffset    = 0.1;  // only used in outOfFrame version
float relPosX    = 0.045;
float relPosY    = 0.035;
float relExtraDY = 1.2;
// ratio of "CMS" and extra text size
float extraOverCmsTextSize  = 0.76;
TString lumi_13TeV = "35.9 fb^{-1}";
TString lumi_8TeV  = "19.7 fb^{-1}";
TString lumi_7TeV  = "5.1 fb^{-1}";
TString lumi_sqrtS = "";
bool drawLogo      = false;

//-----------------------
//------ Main class ---//
//-----------------------
class MyStackHisto{
  public :
    //get histogram from root file. Return empty hist, if the hist does not exist.
    TH1F* getHisto(TFile *inRootFile, TString baseDir, TString isoDir, TString histDir, TString histName);
    //decorate histogram
    TH1F* decorateHisto(TH1F* hist, TString myTit, TString xTit, TString yTit);
    //function to stack histos
    TH1F* stackHisto(TFile *inRootFile, TString baseDir, TString isoDir, TString histDir, TString histName, int color, double scale, THStack* MuptStack, TH1F* hMC);
    void makeHistoPositive(TH1F* hist, bool setErrorZero = false);

    //qcd from data
    vector<double> getQcdSF(TFile* fData, TFile* fTT, TFile* fST, TFile* fWJ, TFile* fDY, TFile* fVV, TString histDir, TString histName, TString xTitle, double xmin, double xmax);
    TH1F* getDDqcd(TString baseDir, TString isoDir, TString histDir, TString histName, double qcd_sf=1.0, double qcd_sf_err = 0.0);
    double getStatUnc(TH1F* hCentral, double sError = 0.0);

    //function to overlap histograms
    void overlapHisto(TH1F *h1, TH1F *h2, bool isRatio, TString histDir, TString histName, TString xTitle, double xmin, double xmax);
    //function to add histograms
    TH1F*  addHistoForUnc(TString baseDir, TString isoDir, TString histDir, TString histName, bool isDataDrivenQCD = false);
    //Up/down error in the unc band
    double errBandUp(int iBin, TH1F *hCentral, TH1F *hJESPlus, TH1F *hJERPlus, TH1F *bcTagPlus1, TH1F *bcTagPlus2, TH1F *bcTagPlus3, TH1F *PileupPlus, TH1F* hQCD_dd);
    double errBandDown(int iBin, TH1F *hCentral, TH1F *hJESMinus, TH1F *hJERMinus, TH1F *bcTagMinus1, TH1F *bcTagMinus2, TH1F *bcTagMinus3, TH1F* PileupMinus, TH1F* hQCD_dd);
    //unc graph
    TGraphAsymmErrors *UNCGRAPH(TH1F *hCentral, TH1F *hJESPlus, TH1F *hJESMinus, TH1F *hJERPlus, TH1F *hJERMinus, TH1F *bcTagPlus1, TH1F *bcTagMinus1, TH1F *bcTagPlus2, TH1F *bcTagMinus2,TH1F *bcTagPlus3, TH1F *bcTagMinus3, TH1F *PileupPlus, TH1F* PileupMinus, TH1F* hQCD_dd, bool isFullGraph = false, bool isRatioGraph = false);
    //CMS guidelines
    TPaveText *paveText(double minX, double minY, double maxX, double maxY, int lineColor, int fillColor, int size, int style, int font );
    void CMS_lumi( TPad* pad, int iPeriod=3, int iPosX=10 );
    TCanvas * myCanvas(TString canvName, int iPeriod, int iPos, bool isData);
    void setTDRStyle();
  private :
    int dont_use ;
};

//--------------------------------------------//
//define various functions
//--------------------------------------------//
TH1F*  MyStackHisto:: getHisto(TFile *inRootFile, TString baseDir, TString isoDir, TString histDir, TString histName){
  TH1F* hist;
  TString inFile(inRootFile->GetName());
  TString fullPath = baseDir+isoDir+histDir+histName;
  string exception_msg ("The histogram path, "+inFile+"/"+fullPath+", does not exist");
  try{
    if(!(inRootFile->Get(fullPath)))
       throw  exception_msg.c_str();
  }catch (const char *e){
    //cout<<"WARNING:"<<e<<endl;
  }
  try{
    if(!(fTT->Get("base/"+isoDir+histDir+histName))) //to initialise an empty hist
       throw  exception_msg.c_str();
  }catch (const char *e){
    cout<<"\033[01;31mERROR: \033[0m"<<e<< endl;
    exit(0);
  }
  if(!(inRootFile->Get(fullPath))){
    hist = (TH1F*)(fTT->Get("base/Iso/"+histDir+histName))->Clone(histName); //to initialise an empty hist
    hist->Reset();
  }else hist = (TH1F*)(inRootFile->Get(fullPath))->Clone(histName);
  return hist;
}

TH1F* MyStackHisto:: decorateHisto(TH1F* hist, TString myTit, TString xTit, TString yTit){
  hist->SetTitle(myTit);
  hist->GetXaxis()->SetTitle(xTit);
  hist->GetYaxis()->SetTitle(yTit);
  hist->GetYaxis()->SetTitleOffset(1.00);
  hist->GetXaxis()->SetTitleOffset(1.00);
  hist->GetYaxis()->SetTitleSize(0.10);
  hist->GetXaxis()->SetTitleSize(0.10);
  hist->GetXaxis()->SetLabelSize(0.10);
  hist->GetYaxis()->SetLabelSize(0.10);
  hist->GetXaxis()->SetTickLength(0.05);
  hist->GetXaxis()->SetNdivisions(10);
  hist->GetYaxis()->SetNdivisions(5);
  hist->GetYaxis()->CenterTitle();
  hist->GetYaxis()->SetTickLength(0.04);
  return hist;
}

TH1F *  MyStackHisto:: stackHisto(TFile *inRootFile, TString baseDir, TString isoDir, TString histDir, TString histName, int color, double scale, THStack* MuptStack, TH1F* hMC){
  TH1F* hist = getHisto(inRootFile, baseDir, isoDir, histDir, histName);
  hist->Scale(scale);  
  hist->SetFillColor(color);
  //leg->AddEntry(hist,lable,"F");
  MuptStack->Add(hist);
  hMC->Add(hist);
  return hist;
}

double MyStackHisto:: errBandUp(int iBin, TH1F *hCentral, TH1F *hJESPlus, TH1F *hJERPlus, TH1F *bcTagPlus1, TH1F *bcTagPlus2, TH1F *bcTagPlus3, TH1F *PileupPlus, TH1F* hQCD_dd){
  double errUp = sqrt(pow(fabs(hJESPlus->GetBinContent(iBin+1) - hCentral->GetBinContent(iBin+1)),2) +
		  pow(fabs(hJERPlus->GetBinContent(iBin+1) - hCentral->GetBinContent(iBin+1)),2) +
		  pow(fabs(bcTagPlus1->GetBinContent(iBin+1) - hCentral->GetBinContent(iBin+1)),2) +
		  pow(fabs(bcTagPlus2->GetBinContent(iBin+1) - hCentral->GetBinContent(iBin+1)),2) +
		  pow(fabs(bcTagPlus3->GetBinContent(iBin+1) - hCentral->GetBinContent(iBin+1)),2) +
		  pow(fabs(PileupPlus->GetBinContent(iBin+1) - hCentral->GetBinContent(iBin+1)),2) +
		  pow(hCentral->GetBinError(iBin+1),2)+ pow(hQCD_dd->GetBinError(iBin+1),2));
  return errUp;
}

double MyStackHisto:: errBandDown(int iBin, TH1F *hCentral, TH1F *hJESMinus, TH1F *hJERMinus, TH1F *bcTagMinus1, TH1F *bcTagMinus2, TH1F *bcTagMinus3, TH1F* PileupMinus, TH1F* hQCD_dd){
  double errDown =sqrt(pow(fabs(hCentral->GetBinContent(iBin+1) - hJESMinus->GetBinContent(iBin+1)),2) +
		  pow(fabs(hCentral->GetBinContent(iBin+1) - hJERMinus->GetBinContent(iBin+1)),2) +
		  pow(fabs(hCentral->GetBinContent(iBin+1) - bcTagMinus1->GetBinContent(iBin+1)),2) +
		  pow(fabs(hCentral->GetBinContent(iBin+1) - bcTagMinus2->GetBinContent(iBin+1)),2) +
		  pow(fabs(hCentral->GetBinContent(iBin+1) - bcTagMinus3->GetBinContent(iBin+1)),2) +
		  pow(fabs(hCentral->GetBinContent(iBin+1) - PileupMinus->GetBinContent(iBin+1)),2) +
		  pow(hCentral->GetBinError(iBin+1),2)+pow(hQCD_dd->GetBinError(iBin+1),2));
  return errDown;
}

TGraphAsymmErrors * MyStackHisto::UNCGRAPH(TH1F *hCentral, TH1F *hJESPlus, TH1F *hJESMinus, TH1F *hJERPlus, TH1F *hJERMinus, TH1F *bcTagPlus1, TH1F *bcTagMinus1, TH1F *bcTagPlus2, TH1F *bcTagMinus2,TH1F *bcTagPlus3, TH1F *bcTagMinus3, TH1F *PileupPlus, TH1F* PileupMinus, TH1F* hQCD_dd, bool isFullGraph = false, bool isRatioGraph = false){
  TGraphAsymmErrors *gr;
  int n1 = hCentral->GetNbinsX();
  double *Yval, *errorU, *errorD, *XerrorU, *XerrorD, *Xval ;
  Yval = new double[n1]; errorU = new double[n1]; errorD = new double[n1];
  XerrorU=new double[n1]; XerrorD=new double[n1]; Xval=new double[n1];
  //cout << "No. of bins= " << n1 << endl;
  for(int i=0; i<n1; i++){
    if(isFullGraph){
    Yval[i]   = hCentral->GetBinContent(i+1);
    errorU[i] = errBandUp(i, hCentral, hJESPlus, hJERPlus, bcTagPlus1, bcTagPlus2, bcTagPlus3, PileupPlus, hQCD_dd);
    errorD[i] = errBandDown(i, hCentral, hJESMinus, hJERMinus, bcTagMinus1, bcTagMinus2, bcTagMinus3, PileupMinus, hQCD_dd);
    }
    if(isRatioGraph){
    Yval[i]   = 1;
    errorU[i] = errBandUp(i, hCentral, hJESPlus, hJERPlus, bcTagPlus1, bcTagPlus2, bcTagPlus3, PileupPlus, hQCD_dd);
    errorD[i] = errBandDown(i, hCentral, hJESMinus, hJERMinus, bcTagMinus1, bcTagMinus2, bcTagMinus3, PileupMinus, hQCD_dd);
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

TH1F*  MyStackHisto:: addHistoForUnc(TString baseDir, TString isoDir, TString histDir, TString histName, bool isDataDrivenQCD = false){
  TH1F* hVV =   	getHisto(fVV,   baseDir, isoDir, histDir, histName);
  TH1F* hDY =   	getHisto(fDY,    baseDir, isoDir, histDir, histName);
  TH1F* hQCD_mc =   getHisto(fQCD,  baseDir, isoDir, histDir, histName);
  TH1F* hWJ =   	getHisto(fWJ,   baseDir, isoDir, histDir, histName);
  TH1F* hST =   	getHisto(fST,   baseDir, isoDir, histDir, histName);
  TH1F* hTT =   	getHisto(fTT,   baseDir, isoDir, histDir, histName);
  TH1F* hAll = (TH1F*)hVV->Clone("hAllMC");
  hAll->Add(hDY);
  hAll->Add(hWJ);
  hAll->Add(hST);
  hAll->Add(hTT);
  if(!isDataDrivenQCD) hAll->Add(hQCD_mc);
  return hAll;
}

TCanvas * MyStackHisto::myCanvas(TString canvName, int iPeriod, int iPos, bool isData){
  int W = 800;
  int H = 800;
  int W_ref = 1000;
  int H_ref = 600;
  if(!isData){
    W = 800;
    H = 600;
    W_ref = 800;
    H_ref = 600;
  }
  // references for T, B, L, R
  float T = 0.08*H_ref;
  float B = 0.12*H_ref;
  float L = 0.12*W_ref;
  float R = 0.04*W_ref;
  canvName += W;
  canvName += "-";
  canvName += H;
  canvName += "_";
  canvName += iPeriod;
  if( writeExtraText ) canvName += "-prelim";
  if( iPos%10==0 ) canvName += "-out";
  else if( iPos%10==1 ) canvName += "-left";
  else if( iPos%10==2 )  canvName += "-center";
  else if( iPos%10==3 )  canvName += "-right";
  TCanvas* canv = new TCanvas(canvName,canvName,50,50,W,H);
  canv->SetFillColor(0);
  canv->SetBorderMode(0);
  canv->SetFrameFillStyle(0);
  canv->SetFrameBorderMode(0);
  canv->SetLeftMargin( L/W );
  canv->SetRightMargin( R/W );
  canv->SetTopMargin( T/H );
  canv->SetBottomMargin( B/H );
  canv->SetTickx(0);
  canv->SetTicky(0);
  return canv;
}


TPaveText * MyStackHisto:: paveText(double minX, double minY, double maxX, double maxY, int lineColor, int fillColor, int size, int style, int font ){
  TPaveText *pt = new TPaveText(minX, minY, maxX, maxY, "brNDC"); // good_v1
  pt->SetBorderSize(size);
  pt->SetFillColor(fillColor);
  pt->SetFillStyle(style);
  pt->SetLineColor(lineColor);
  pt->SetTextFont(font);
  return pt;
}
void MyStackHisto::setTDRStyle() {
  TStyle *tdrStyle = new TStyle("tdrStyle","Style for P-TDR");
// For the canvas:
  tdrStyle->SetCanvasBorderMode(0);
  tdrStyle->SetCanvasColor(kWhite);
  tdrStyle->SetCanvasDefH(600); //Height of canvas
  tdrStyle->SetCanvasDefW(600); //Width of canvas
  tdrStyle->SetCanvasDefX(0);   //POsition on screen
  tdrStyle->SetCanvasDefY(0);

// For the Pad:
  tdrStyle->SetPadBorderMode(0);
  // tdrStyle->SetPadBorderSize(Width_t size = 1);
  tdrStyle->SetPadColor(kWhite);
  tdrStyle->SetPadGridX(false);
  tdrStyle->SetPadGridY(false);
  tdrStyle->SetGridColor(0);
  tdrStyle->SetGridStyle(3);
  tdrStyle->SetGridWidth(1);

// For the frame:
  tdrStyle->SetFrameBorderMode(0);
  tdrStyle->SetFrameBorderSize(1);
  tdrStyle->SetFrameFillColor(0);
  tdrStyle->SetFrameFillStyle(0);
  tdrStyle->SetFrameLineColor(1);
  tdrStyle->SetFrameLineStyle(1);
  tdrStyle->SetFrameLineWidth(1);

// For the histo:
  // tdrStyle->SetHistFillColor(1);
  // tdrStyle->SetHistFillStyle(0);
  tdrStyle->SetHistLineColor(1);
  tdrStyle->SetHistLineStyle(0);
  tdrStyle->SetHistLineWidth(1);
  // tdrStyle->SetLegoInnerR(Float_t rad = 0.5);
  // tdrStyle->SetNumberContours(Int_t number = 20);

  tdrStyle->SetEndErrorSize(2);
  // tdrStyle->SetErrorMarker(20);
  //tdrStyle->SetErrorX(0.);

  tdrStyle->SetMarkerStyle(20);

//For the fit/function:
  tdrStyle->SetOptFit(1);
  tdrStyle->SetFitFormat("5.4g");
  tdrStyle->SetFuncColor(2);
  tdrStyle->SetFuncStyle(1);
  tdrStyle->SetFuncWidth(1);

//For the date:
  tdrStyle->SetOptDate(0);
  // tdrStyle->SetDateX(Float_t x = 0.01);
  // tdrStyle->SetDateY(Float_t y = 0.01);

// For the statistics box:
  tdrStyle->SetOptFile(0);
  tdrStyle->SetOptStat(0); // To display the mean and RMS:   SetOptStat("mr");
  tdrStyle->SetStatColor(kWhite);
  tdrStyle->SetStatFont(42);
  tdrStyle->SetStatFontSize(0.025);
  tdrStyle->SetStatTextColor(1);
  tdrStyle->SetStatFormat("6.4g");
  tdrStyle->SetStatBorderSize(1);
  tdrStyle->SetStatH(0.1);
  tdrStyle->SetStatW(0.15);
  // tdrStyle->SetStatStyle(Style_t style = 1001);
  // tdrStyle->SetStatX(Float_t x = 0);
  // tdrStyle->SetStatY(Float_t y = 0);

// Margins:
  tdrStyle->SetPadTopMargin(0.05);
  tdrStyle->SetPadBottomMargin(0.13);
  tdrStyle->SetPadLeftMargin(0.16);
  tdrStyle->SetPadRightMargin(0.02);

// For the Global title:

  tdrStyle->SetOptTitle(0);
  tdrStyle->SetTitleFont(42);
  tdrStyle->SetTitleColor(1);
  tdrStyle->SetTitleTextColor(1);
  tdrStyle->SetTitleFillColor(10);
  tdrStyle->SetTitleFontSize(0.05);
  // tdrStyle->SetTitleH(0); // Set the height of the title box
  // tdrStyle->SetTitleW(0); // Set the width of the title box
  // tdrStyle->SetTitleX(0); // Set the position of the title box
  // tdrStyle->SetTitleY(0.985); // Set the position of the title box
  // tdrStyle->SetTitleStyle(Style_t style = 1001);
  // tdrStyle->SetTitleBorderSize(2);

// For the axis titles:

  tdrStyle->SetTitleColor(1, "XYZ");
  tdrStyle->SetTitleFont(42, "XYZ");
  tdrStyle->SetTitleSize(0.06, "XYZ");
  // tdrStyle->SetTitleXSize(Float_t size = 0.02); // Another way to set the size?
  // tdrStyle->SetTitleYSize(Float_t size = 0.02);
  tdrStyle->SetTitleXOffset(0.9);
  tdrStyle->SetTitleYOffset(1.25);
  // tdrStyle->SetTitleOffset(1.1, "Y"); // Another way to set the Offset

// For the axis labels:

  tdrStyle->SetLabelColor(1, "XYZ");
  tdrStyle->SetLabelFont(42, "XYZ");
  tdrStyle->SetLabelOffset(0.007, "XYZ");
  tdrStyle->SetLabelSize(0.05, "XYZ");

// For the axis:

  tdrStyle->SetAxisColor(1, "XYZ");
  tdrStyle->SetStripDecimals(kTRUE);
  tdrStyle->SetTickLength(0.03, "XYZ");
  tdrStyle->SetNdivisions(510, "XYZ");
  tdrStyle->SetPadTickX(1);  // To get tick marks on the opposite side of the frame
  tdrStyle->SetPadTickY(1);

// Change for log plots:
  tdrStyle->SetOptLogx(0);
  tdrStyle->SetOptLogy(0);
  tdrStyle->SetOptLogz(0);

// Postscript options:
  tdrStyle->SetPaperSize(20.,20.);
  // tdrStyle->SetLineScalePS(Float_t scale = 3);
  // tdrStyle->SetLineStyleString(Int_t i, const char* text);
  // tdrStyle->SetHeaderPS(const char* header);
  // tdrStyle->SetTitlePS(const char* pstitle);

  // tdrStyle->SetBarOffset(Float_t baroff = 0.5);
  // tdrStyle->SetBarWidth(Float_t barwidth = 0.5);
  // tdrStyle->SetPaintTextFormat(const char* format = "g");
  // tdrStyle->SetPalette(Int_t ncolors = 0, Int_t* colors = 0);
  // tdrStyle->SetTimeOffset(Double_t toffset);
  // tdrStyle->SetHistMinimumZero(kTRUE);

  tdrStyle->SetHatchesLineWidth(5);
  tdrStyle->SetHatchesSpacing(0.05);

  tdrStyle->cd();

}

void MyStackHisto::CMS_lumi( TPad* pad, int iPeriod, int iPosX ){
  bool outOfFrame    = false;
  if( iPosX/10==0 )
    {
      outOfFrame = true;
    }
  int alignY_=3;
  int alignX_=2;
  if( iPosX/10==0 ) alignX_=1;
  if( iPosX==0    ) alignX_=1;
  if( iPosX==0    ) alignY_=1;
  if( iPosX/10==1 ) alignX_=1;
  if( iPosX/10==2 ) alignX_=2;
  if( iPosX/10==3 ) alignX_=3;
  //if( iPosX == 0  ) relPosX = 0.12;
  int align_ = 10*alignX_ + alignY_;
  float H = pad->GetWh();
  float W = pad->GetWw();
  float l = pad->GetLeftMargin();
  float t = pad->GetTopMargin();
  float r = pad->GetRightMargin();
  float b = pad->GetBottomMargin();
  //  float e = 0.025;
  pad->cd();
  TString lumiText;
  if( iPeriod==1 )
    {
      lumiText += lumi_7TeV;
      lumiText += " (7 TeV)";
    }
  else if ( iPeriod==2 )
    {
      lumiText += lumi_8TeV;
      lumiText += " (8 TeV)";
    }
  else if( iPeriod==3 )
    {
      lumiText = lumi_8TeV;
      lumiText += " (8 TeV)";
      lumiText += " + ";
      lumiText += lumi_7TeV;
      lumiText += " (7 TeV)";
    }
  else if ( iPeriod==4 )
    {
      lumiText += lumi_13TeV;
      lumiText += " (13 TeV)";
    }
  else if ( iPeriod==7 )
    {
      if( outOfFrame ) lumiText += "#scale[0.85]{";
      lumiText += lumi_13TeV;
      lumiText += " (13 TeV)";
      lumiText += " + ";
      lumiText += lumi_8TeV;
      lumiText += " (8 TeV)";
      lumiText += " + ";
      lumiText += lumi_7TeV;
      lumiText += " (7 TeV)";
      if( outOfFrame) lumiText += "}";
    }
  else if ( iPeriod==12 )
    {
      lumiText += "8 TeV";
    }
  else if ( iPeriod==0 )
    {
      lumiText += lumi_sqrtS;
    }
  std::cout << lumiText << endl;
  TLatex latex;
  latex.SetNDC();
  latex.SetTextAngle(0);
  latex.SetTextColor(kBlack);
  float extraTextSize = extraOverCmsTextSize*cmsTextSize;
  latex.SetTextFont(42);
  latex.SetTextAlign(31);
  latex.SetTextSize(lumiTextSize*t);
  latex.DrawLatex(1-r,1-t+lumiTextOffset*t,lumiText);
  if( outOfFrame )
    {
      latex.SetTextFont(cmsTextFont);
      latex.SetTextAlign(11);
      latex.SetTextSize(cmsTextSize*t);
      latex.DrawLatex(l,1-t+lumiTextOffset*t,cmsText);
    }
  pad->cd();
  float posX_=0;
  if( iPosX%10<=1 )
    {
      posX_ =   l + relPosX*(1-l-r);
    }
  else if( iPosX%10==2 )
    {
      posX_ =  l + 0.5*(1-l-r);
    }
  else if( iPosX%10==3 )
    {
      posX_ =  1-r - relPosX*(1-l-r);
    }
  float posY_ = 1-t - relPosY*(1-t-b);
  if( !outOfFrame )
    {
      if( drawLogo )
	{
	  posX_ =   l + 0.045*(1-l-r)*W/H;
	  posY_ = 1-t - 0.045*(1-t-b);
	  float xl_0 = posX_;
	  float yl_0 = posY_ - 0.15;
	  float xl_1 = posX_ + 0.15*H/W;
	  float yl_1 = posY_;
	  TASImage* CMS_logo = new TASImage("CMS-BW-label.png");
	  TPad* pad_logo = new TPad("logo","logo", xl_0, yl_0, xl_1, yl_1 );
	  pad_logo->Draw();
	  pad_logo->cd();
	  CMS_logo->Draw("X");
	  pad_logo->Modified();
	  pad->cd();
	}
      else
	{
	  latex.SetTextFont(cmsTextFont);
	  latex.SetTextSize(cmsTextSize*t);
	  latex.SetTextAlign(align_);
	  latex.DrawLatex(posX_, posY_, cmsText);
	  if( writeExtraText )
	    {
	      latex.SetTextFont(extraTextFont);
	      latex.SetTextAlign(align_);
	      latex.SetTextSize(extraTextSize*t);
	      latex.DrawLatex(posX_, posY_- relExtraDY*cmsTextSize*t, extraText);
	    }
	}
    }
  else if( writeExtraText )
    {
      if( iPosX==0)
	{
	  posX_ =   l +  relPosX*(1-l-r);
	  posY_ =   1-t+lumiTextOffset*t;
	}
      latex.SetTextFont(extraTextFont);
      latex.SetTextSize(extraTextSize*t);
      latex.SetTextAlign(align_);
      latex.DrawLatex(1.5*posX_, posY_, extraText);
    }
  return;
}
double MyStackHisto::getStatUnc(TH1F* hCentral, double sError = 0.0){
  double  norm = hCentral->IntegralAndError(1, hCentral->GetNbinsX(), sError);
  //double statUnc = (norm > 0) ? 1 + (fabs(sError)/norm) : 1.00;
  double statUnc = sError;
  return statUnc;
}

void MyStackHisto::makeHistoPositive(TH1F* hist, bool setErrorZero = false){
  for(int ibin=1; ibin<hist->GetNbinsX(); ibin++){
    double binCont = hist->GetBinContent(ibin);
    if(binCont<0){
      hist->SetBinContent(ibin, 0);
      if(setErrorZero) hist->SetBinError(ibin, 0);
    }
  }
}

void MyStackHisto::overlapHisto(TH1F *h1, TH1F *h2, bool isRatio, TString histDir, TString histName, TString xTitle, double xmin, double xmax){
  gStyle->SetOptStat(0);
  gStyle->SetFrameLineWidth(2);
  const float xpad[2] = {0.0, 1.0};
  const float ypad[3] = {0.0, 0.30,0.98};
  TCanvas *canv = new TCanvas();
  canv->Divide(1, 2);
  canv->cd(1);
  gPad->SetPad(xpad[0],ypad[1],xpad[1],ypad[2]);
  //gPad->SetTopMargin(1.15); 
  gPad->SetLeftMargin(0.15);
  gPad->SetRightMargin(0.05);
  gPad->SetBottomMargin(0.0);
  //legend box
  TLegend* leg = new TLegend(0.7518792,0.6261504,0.9512081,0.9198861,NULL,"brNDC");
  leg->SetFillStyle(0); leg->SetBorderSize(0);
  leg->SetFillColor(10); leg->SetTextSize(0.07);
  //pave text CMS box
  TPaveText *pt = new TPaveText(0.11,0.9354,0.90,0.9362, "brNDC"); // good_v1
  pt->SetBorderSize(1); pt->SetFillColor(19);
  pt->SetFillStyle(0); pt->SetTextSize(0.08);
  pt->SetLineColor(0); pt->SetTextFont(132);
  TText *text = pt->AddText(histDir+": #sqrt{s}=13 TeV, 35.9 fb^{-1}; ");
  text->SetTextAlign(11);
  //pave text channel box
  TPaveText *ch = new TPaveText(1.00,0.9154898,0.7510067,0.9762187,"brNDC");
  ch->SetFillColor(19); ch->SetFillStyle(0);
  ch->SetLineColor(0); ch->SetTextSize(0.08);
  ch->SetBorderSize(1);
  if(isMuChannel) ch->AddText("#mu + jets");
  if(isEleChannel) ch->AddText("e + jets");
  //data-MC from isolated region
  leg->AddEntry(h1,"Iso","P");
  h1->SetMarkerColor(kRed);
  h1->SetLineColor(kRed);
  h1->Scale(1/h1->Integral());
  cout<<h1->GetMaximum()<<endl;
  h1->GetYaxis()->SetRangeUser(-0.05,  1.2*h1->GetMaximum());
  h1->GetXaxis()->SetRangeUser(xmin, xmax);
  h1->GetYaxis()->SetTitleOffset(1.00);
  h1->GetYaxis()->SetTitleSize(0.08);   
  h1->GetYaxis()->SetLabelSize(0.08);   
  h1->GetYaxis()->SetTickLength(0.04); 
  h1->GetYaxis()->SetNdivisions(5);
  h1->Draw("e1"); 
  //data-MC from non-isolated region
  leg->AddEntry(h2,"NonIso","P");
  h2->SetMarkerColor(kGreen);
  h2->SetLineColor(kGreen);
  h2->Scale(1/h2->Integral());
  h2->Draw("SAME");  
  pt->Draw();
  leg->Draw();
  ch->Draw();
  canv->cd(2);
  gPad->SetPad(xpad[0],ypad[0],xpad[1], ypad[1]);
  gPad->SetTopMargin(0); 
  gPad->SetBottomMargin(0.5); gPad->SetGridy();
  gPad->SetLeftMargin(0.15);
  gPad->SetRightMargin(0.05);
  TH1F *h12 = (TH1F*)h1->Clone("h12");
  h12->Reset();
  h12->Add(h1);
  h12->Divide(h2); h12->SetMarkerStyle(20); h12->SetMarkerSize(0.8);
  h12->SetMarkerColor(kBlack); h12->SetLineColor(kBlack); h12->GetYaxis()->SetRangeUser(-10, 10);
  //h12->GetXaxis()->SetRangeUser(xmin, xmax);
  h12->GetXaxis()->SetTickLength(0.13); 
  h12->GetYaxis()->SetTickLength(0.04); 
  h12->GetXaxis()->SetTitle(xTitle); 
  h12->GetYaxis()->SetTitleOffset(0.50);
  h12->GetXaxis()->SetTitleOffset(1.10);
  h12->GetYaxis()->SetTitle("#frac{Iso}{NonIso}"); 
  h12->GetYaxis()->CenterTitle();
  h12->GetYaxis()->SetTitleSize(0.15); 
  h12->GetXaxis()->SetTitleSize(0.20);
  h12->GetXaxis()->SetLabelSize(0.20); 
  h12->GetYaxis()->SetLabelSize(0.15); 
  h12->GetYaxis()->SetNdivisions(5);
  h12->Draw("E"); // use "P" or "AP"
  //base line
  TF1 *baseLine = new TF1("baseLine","1", -100, 2000); 
  baseLine->SetLineColor(kCyan+1);
  baseLine->Draw("SAME");
  if(isSaveHisto){
    TString outDir = "$PWD/QCD/"+histDir;
    TString histDir_ = "";
    if(histDir.Contains("BTag")) histDir_ = "BTag";
    if(histDir.Contains("KinFit")) histDir_ = "KinFit";
    mkdir("QCD/", S_IRWXU);
    mkdir("QCD/"+histDir, S_IRWXU);
    TString outFile(outDir);
    if(isMuChannel)outFile += "mu_"+histDir_+"_"+histName+".pdf";
    if(isEleChannel)outFile += "ele_"+histDir_+"_"+histName+".pdf";
    canv->SaveAs(outFile);
    //canv->Close();
  }
}
vector<double> MyStackHisto::getQcdSF(TFile* fData, TFile* fTT, TFile* fST, TFile* fWJ, TFile* fDY, TFile* fVV, TString histDir, TString histName, TString xTitle, double xmin, double xmax){
  //RegionC = LowMET, Iso
  //if(histName.Contains("CTagEx")) histName="mjj_kfit";
  TH1F* hVV_RegC = getHisto(fVV,   "baseLowMET/", "NonIso/", histDir, histName);//Reg = Region
  TH1F* hDY_RegC = getHisto(fDY,   "baseLowMET/", "NonIso/", histDir, histName);
  TH1F* hWJ_RegC = getHisto(fWJ,   "baseLowMET/", "NonIso/", histDir, histName);
  TH1F* hST_RegC = getHisto(fST,   "baseLowMET/", "NonIso/", histDir, histName);
  TH1F* hTT_RegC = getHisto(fTT,   "baseLowMET/", "NonIso/", histDir, histName);
  TH1F* hMC_RegC = (TH1F*)hVV_RegC->Clone("hAllMC");
  hMC_RegC->Add(hDY_RegC);
  hMC_RegC->Add(hWJ_RegC);
  hMC_RegC->Add(hST_RegC);
  hMC_RegC->Add(hTT_RegC);
  TH1F* hData_RegC= (TH1F*) getHisto(fData, "baseLowMET/", "NonIso/", histDir, histName);
  //RegionD = LowMET, NonIso
  TH1F* hVV_RegD = getHisto(fVV,   "baseLowMET/", "Iso/", histDir, histName);
  TH1F* hDY_RegD = getHisto(fDY,   "baseLowMET/", "Iso/", histDir, histName);
  TH1F* hWJ_RegD = getHisto(fWJ,   "baseLowMET/", "Iso/", histDir, histName);
  TH1F* hST_RegD = getHisto(fST,   "baseLowMET/", "Iso/", histDir, histName);
  TH1F* hTT_RegD = getHisto(fTT,   "baseLowMET/", "Iso/", histDir, histName);
  TH1F* hMC_RegD = (TH1F*)hVV_RegD->Clone("hAllMC");
  hMC_RegD->Add(hDY_RegD);
  hMC_RegD->Add(hWJ_RegD);
  hMC_RegD->Add(hST_RegD);
  hMC_RegD->Add(hTT_RegD);
  TH1F* hData_RegD=  getHisto(fData, "baseLowMET/", "Iso/", histDir, histName);
  TH1F* hDiffC = (TH1F*)hData_RegC->Clone("hDiffC");
  hDiffC->Add(hMC_RegC, -1);
  TH1F* hDiffD = (TH1F*)hData_RegD->Clone("hDiffD");
  hDiffD->Add(hMC_RegD, -1);
  //If binContent < 0, set it to 0
  makeHistoPositive(hDiffC, false);
  makeHistoPositive(hDiffD, false);
  double intDiffC   = hDiffC->Integral();
  double errDiffC   = getStatUnc(hDiffC, 0.0);
  double intDiffD   = hDiffD->Integral();
  double errDiffD   = getStatUnc(hDiffD, 0.0);
  //Ratio of (Data-MC) from RegionD and RegionC
  double ratioDiffDC = intDiffD/intDiffC;
  double tmpD = errDiffD/intDiffD;
  double tmpC = errDiffC/intDiffC;
  double errDiffDC = ratioDiffDC*sqrt(tmpD*tmpD + tmpC*tmpC);
  vector<double>sfAndErr;
  sfAndErr.push_back(ratioDiffDC);
  sfAndErr.push_back(errDiffDC);
  //overlap two histo
  //overlapHisto(hDiffD, hDiffC, true, histDir, histName, xTitle, xmin, xmax);
  return sfAndErr;
}

TH1F* MyStackHisto:: getDDqcd(TString baseDir, TString isoDir, TString histDir, TString histName, double qcd_sf=1.0, double qcd_sf_err = 0.0){
  TH1F* hVV =   getHisto(fVV,   baseDir, "NonIso/", histDir, histName);
  TH1F* hDY =   getHisto(fDY,   baseDir, "NonIso/", histDir, histName);
  TH1F* hST =   getHisto(fST,   baseDir, "NonIso/", histDir, histName);
  TH1F* hWJ =   getHisto(fWJ,   baseDir, "NonIso/", histDir, histName);
  TH1F* hTT =   getHisto(fTT,   baseDir, "NonIso/", histDir, histName);
  TH1F* hData = getHisto(fData, baseDir, "NonIso/", histDir, histName);
  TH1F* hOtherMC = (TH1F*)hVV->Clone("hOtherMC");
  hOtherMC->Add(hDY);
  hOtherMC->Add(hST);
  hOtherMC->Add(hWJ);
  hOtherMC->Add(hTT);
  TH1F* hQCD = (TH1F*)hData->Clone(histName);
  hQCD->Add(hOtherMC, -1);
  //If binContent < 0, set it to 0
  makeHistoPositive(hQCD, false);
  cout<<"\n--------------------------"<<endl;
  cout<<histDir<<"/"<<histName<<endl;
  double sError = 0.0;
  double  norm = hQCD->IntegralAndError(1, hQCD->GetNbinsX(), sError);
  cout<<"intB = "<<norm<<", intB_err = "<<sError<<endl;
  cout<<"qcdSF = "<<qcd_sf<<", qcdSF_err = "<<qcd_sf_err<<endl;
  double tot_bin_cont = 0.0;
  double tot_bin_err = 0.0;
  for(int ibin=1; ibin<hQCD->GetNbinsX(); ibin++){
      double bin_cont = hQCD->GetBinContent(ibin);
      double bin_err = hQCD->GetBinError(ibin);
      double new_bin_cont = qcd_sf*bin_cont;
      double new_bin_err = sqrt(pow(bin_cont*qcd_sf_err, 2) + pow(bin_err* qcd_sf, 2));
      tot_bin_cont = tot_bin_cont + new_bin_cont;
      tot_bin_err = tot_bin_err + new_bin_err*new_bin_err;
      hQCD->SetBinContent(ibin, new_bin_cont);
      hQCD->SetBinError(ibin, new_bin_err);
    }
  cout<<"tot_bin_cont= "<<tot_bin_cont<<", tot_bin_err = "<<sqrt(tot_bin_err)<<endl;
  return hQCD;
}

