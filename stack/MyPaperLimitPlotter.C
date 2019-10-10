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

TCanvas * myCanvas(TString canvName, int iPeriod, int iPos){
  int W = 800;
  int H = 800;
  int H_ref = 900; 
  int W_ref = 1000; 
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

void CMS_lumi( TPad* pad, int iPeriod, int iPosX ){            
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
void setTDRStyle() {
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
  
  //tdrStyle->SetMarkerStyle(20);
  
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
void LimitPlotter(TString CHANNEL="mu", TString CAT= "Cat1_Inc",
         bool obs= false, bool isOut= true )
  {
  setTDRStyle();
  //gStyle->SetFrameLineWidth(3);
  
  int nMassPoints = 8;
  float X[]        = {80, 90,100,120, 140, 150, 155, 160};
  float obsY[]     = {0., 0.,0.,0, 0, 0, 0, 0,0};
  float expY[]     = {0., 0.,0.,0, 0, 0, 0, 0,0};
		      
  float expX1sL[]   = {0.,0.,0.,0, 0, 0, 0, 0,0};
  float expX1sH[]   = {0.,0.,0.,0, 0, 0, 0, 0,0};
  float expY1sL[]   = {0.,0.,0.,0, 0, 0, 0, 0,0};
  float expY1sH[]   = {0.,0.,0.,0, 0, 0, 0, 0,0};
		      
  float expX2sL[]  = {0.,0.,0.,0, 0, 0, 0, 0,0};
  float expX2sH[]  = {0.,0.,0.,0, 0, 0, 0, 0,0};
  float expY2sL[]  = {0.,0.,0.,0, 0, 0, 0, 0,0};
  float expY2sH[]  = {0.,0.,0.,0, 0, 0, 0, 0,0};

  //-------------------------------------------
  // 8 TeV limits
  //-------------------------------------------
  float limit8TeV_obsY[]     = {6.5, 1.4, 1.2, 1.5, 2.1, 1.9, 2.0};
  float limit8TeV_expY2sL[]  = {1.9, 0.9, 0.6, 0.6, 0.5, 0.7, 0.6};
  float limit8TeV_expY1sL[]  = {2.6, 1.2, 0.8, 0.7, 0.7, 0.9, 1.0};
  float limit8TeV_expY[]     = {3.6, 1.8, 1.2, 1.1, 1.0, 1.3, 1.4};
  float limit8TeV_expY1sH[]  = {5.3, 2.3, 1.8, 1.4, 1.4, 1.9, 2.2};
  float limit8TeV_expY2sH[]  = {7.3, 3.4, 2.4, 2.0, 2.0, 2.6, 3.6};
  for(int i1 = 0 ; i1 < nMassPoints ; i1++){
    limit8TeV_expY1sH[i1] = TMath::Abs(limit8TeV_expY1sH[i1]-limit8TeV_expY[i1]);
    limit8TeV_expY1sL[i1] = TMath::Abs(limit8TeV_expY1sL[i1]-limit8TeV_expY[i1]);
    limit8TeV_expY2sH[i1] = TMath::Abs(limit8TeV_expY2sH[i1]-limit8TeV_expY[i1]);
    limit8TeV_expY2sL[i1] = TMath::Abs(limit8TeV_expY2sL[i1]-limit8TeV_expY[i1]);
  }
  TGraphAsymmErrors* limit8TeV_exp = new TGraphAsymmErrors(7, X, limit8TeV_expY, expX1sL ,expX1sL , expX1sL, expX1sL);
  TGraphAsymmErrors* limit8TeV_1s = new TGraphAsymmErrors(7, X, limit8TeV_expY,  expX1sL, expX1sL,  limit8TeV_expY1sL, limit8TeV_expY1sH);
  TGraphAsymmErrors* limit8TeV_2s = new TGraphAsymmErrors(7, X, limit8TeV_expY,  expX2sL, expX2sL,  limit8TeV_expY2sL, limit8TeV_expY2sH);
  TGraphAsymmErrors* limit8TeV_obs = new TGraphAsymmErrors(7, X, limit8TeV_obsY, expX1sL ,expX1sL , expX1sL, expX1sL);
  //1s
  limit8TeV_1s->SetFillColor(kGreen+1);
  limit8TeV_1s->SetFillStyle(1001);
  //2s
  limit8TeV_2s->SetFillColor(kOrange);
  limit8TeV_2s->SetFillStyle(1001);
  //median
  limit8TeV_exp->SetLineColor(kBlue);
  limit8TeV_exp->SetLineWidth(2);
  limit8TeV_exp->SetLineStyle(2);
  limit8TeV_exp->SetLineWidth(4);
  //obs
  limit8TeV_obs->SetMarkerColor(kBlack);
  limit8TeV_obs->SetMarkerStyle(20);
  limit8TeV_obs->SetMarkerSize(1.0);
  limit8TeV_obs->SetLineColor(kBlack);
  limit8TeV_obs->SetLineWidth(4);

  //-------------------------------------------
  // 13 TeV limits
  //-------------------------------------------
  TString ch_hist = CHANNEL+"_"+CAT;
  TString massFiles [8] = {
  "Mass80/higgsCombine_hcs_13TeV_"+ch_hist+".AsymptoticLimits.mH80.root",
  "Mass90/higgsCombine_hcs_13TeV_"+ch_hist+".AsymptoticLimits.mH90.root",
  "Mass100/higgsCombine_hcs_13TeV_"+ch_hist+".AsymptoticLimits.mH100.root",
  "Mass120/higgsCombine_hcs_13TeV_"+ch_hist+".AsymptoticLimits.mH120.root",
  "Mass140/higgsCombine_hcs_13TeV_"+ch_hist+".AsymptoticLimits.mH140.root",
  "Mass150/higgsCombine_hcs_13TeV_"+ch_hist+".AsymptoticLimits.mH150.root",
  "Mass155/higgsCombine_hcs_13TeV_"+ch_hist+".AsymptoticLimits.mH155.root",
  "Mass160/higgsCombine_hcs_13TeV_"+ch_hist+".AsymptoticLimits.mH160.root"};
  
  for(unsigned int i = 0 ; i < nMassPoints; i++){
    TFile f("limit/"+CHANNEL+"/"+CAT+"/"+massFiles[i],"READ"); 
    if(f.IsZombie()){
      cout << "Cannot open file for " << string(CHANNEL.Data()) << " and mass " << X[i] << endl;
      continue;
    }
    Double_t r;
    TTree* limit = (TTree*)f.Get("limit");
    limit->SetBranchAddress("limit",&r);
    for(int k = 0 ; k< limit->GetEntries() ; k++){
      limit->GetEntry(k);
      r = r*100;
      if(k==0) expY2sL[i] = r;
      if(k==1) expY1sL[i] = r;
      if(k==2) expY[i]    = r;
      if(k==3) expY1sH[i] = r;
      if(k==4) expY2sH[i] = r;
      if(k==5) obsY[i]    = r;
    }
  }
  for(int i1 = 0 ; i1 < nMassPoints ; i1++){
  //cout<<X[i1]<<setw(15)<<expY[i1]<<setw(15)<<expY2sL[i1]<<setw(15)<< expY1sL[i1]<<setw(15)<<expY1sH[i1]<<setw(15)<<expY2sH[i1]<<endl; 
    expY1sH[i1] = TMath::Abs(expY1sH[i1]-expY[i1]);
    expY1sL[i1] = TMath::Abs(expY1sL[i1]-expY[i1]);
    expY2sH[i1] = TMath::Abs(expY2sH[i1]-expY[i1]);
    expY2sL[i1] = TMath::Abs(expY2sL[i1]-expY[i1]);
  //cout<<setw(10)<<X[i1]<<setw(15)<<expY[i1]<<setw(15)<<expY2sL[i1]<<setw(15)<< expY1sL[i1]<<setw(15)<<expY1sH[i1]<<setw(15)<<expY2sH[i1]<<endl; 
  }
  
  TGraphAsymmErrors* expected = new TGraphAsymmErrors(nMassPoints, X, expY, expX1sL ,expX1sL , expX1sL, expX1sL);
  TGraphAsymmErrors* oneSigma = new TGraphAsymmErrors(nMassPoints, X, expY, expX1sL, expX1sL,  expY1sL, expY1sH);
  TGraphAsymmErrors* twoSigma = new TGraphAsymmErrors(nMassPoints, X, expY, expX2sL, expX2sL,  expY2sL, expY2sH);
  TGraphAsymmErrors* observed = new TGraphAsymmErrors(nMassPoints, X, obsY, expX1sL ,expX1sL , expX1sL, expX1sL);

  //1s
  oneSigma->SetFillColor(kGreen+1);
  oneSigma->SetFillStyle(1001);
  //2s
  twoSigma->SetFillColor(kOrange);
  twoSigma->SetFillStyle(1001);
  //median
  expected->SetLineColor(kBlue);
  expected->SetLineStyle(4);
  expected->SetLineWidth(4);
  //obs
  observed->SetMarkerColor(kBlack);
  observed->SetMarkerStyle(20);
  observed->SetMarkerSize(1.0);
  observed->SetLineColor(kBlack);
  observed->SetLineWidth(4);

  //canvas
  //TCanvas *c1 = new TCanvas(ch_hist, ch_hist, 800, 900);
  TCanvas *c1 = myCanvas(ch_hist, 4, 1);
  gPad->SetLogy();
  //gPad->SetGridy();
  c1->cd();

  //add graphs from 8 and 13 TeV
  TMultiGraph *mg = new TMultiGraph();
  mg->SetMaximum(30);
  //add all in one
  //mg->Add(limit8TeV_2s);
  //mg->Add(limit8TeV_1s);
  //mg->Add(limit8TeV_exp);
  //mg->Add(limit8TeV_obs);
  mg->Add(twoSigma);
  mg->Add(oneSigma);
  mg->Add(expected);
  if(obs) mg->Add(observed);

  mg->Draw("ALP3");
  //decorate graph
  mg->GetXaxis()->SetLimits(75,165);
  mg->GetYaxis()->SetTitleOffset(1);
  mg->GetXaxis()->SetNdivisions(6,5,0);
  mg->GetYaxis()->SetNdivisions(6,5,0);
  mg->GetXaxis()->SetTitleOffset(1.00);
  mg->GetXaxis()->SetTitle("m_{H^{+}} (GeV)");
  mg->GetYaxis()->SetTitle("BR(t#rightarrow H^{+}b)"); 
  mg->GetYaxis()->SetMoreLogLabels(true);

  //Legends
  TLegend* leg = new TLegend(0.60,0.50,0.80,0.89,NULL,"brNDC");
  leg->SetBorderSize(0);
  //leg->SetFillColor(kBlack);
  leg->SetTextFont(42);
  leg->SetTextAngle(0);
  leg->SetTextSize(0.04);
  leg->SetTextAlign(12);
  leg->SetHeader("95% CL upper limits");
  if(obs)leg->AddEntry(limit8TeV_obs,"Observed","EP");
  leg->AddEntry(expected,"Median expected","L");
  leg->AddEntry(oneSigma, "68% expected","F");
  leg->AddEntry(twoSigma, "95% expected","F");

  TString chName = "";
  if(CHANNEL=="mu")     chName = "#mu + jets";
  if(CHANNEL=="ele")    chName = "e + jets";
  if(CHANNEL=="mu_ele") chName = "l + jets";
  leg->AddEntry((TObject*)0, "","");
  leg->AddEntry((TObject*)0, chName,"");
  leg->Draw();
  
  CMS_lumi(c1, 4, 10);
  gPad->RedrawAxis();
  TString outFile = "limit_"+CHANNEL+"_"+CAT;
  TString outDir = "limit/"+CHANNEL+"/"+CAT;
  gPad->SaveAs(outDir+"/"+outFile+".pdf");
}

void MyPaperLimitPlotter(){
  bool isObserved = true;
  LimitPlotter("mu", "Cat1_Inc",     isObserved, true );
  LimitPlotter("mu", "Cat2_cTagInc", isObserved, true );
  LimitPlotter("mu", "Cat3_cTagEx",  isObserved, true );

  LimitPlotter("ele", "Cat1_Inc",     isObserved, true );
  LimitPlotter("ele", "Cat2_cTagInc", isObserved, true );
  LimitPlotter("ele", "Cat3_cTagEx",  isObserved, true );

  LimitPlotter("mu_ele", "Cat1_Inc",     isObserved, true );
  LimitPlotter("mu_ele", "Cat2_cTagInc", isObserved, true );
  LimitPlotter("mu_ele", "Cat3_cTagEx",  isObserved, true );
}
