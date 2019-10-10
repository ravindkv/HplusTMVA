#ifndef _histogramplotter_h_ 
#define _histogramplotter_h_ 
 
#if !defined(__CINT__) || defined(__MAKECINT__) 
 
#include <iomanip> 
#include <iostream> 
#include <fstream> 
#include <map>
 
#include "TRandom2.h" 
#include "TMatrixD.h" 
#include "TF1.h" 
#include "TProfile.h" 
#include "TObjArray.h" 
#include "TMatrixD.h" 
#include "TH1.h" 
#include "TH2.h"
#include "TTimeStamp.h" 
#include "TFile.h"
#include <exception> 
 
#endif 
 
class HistogramPlotter{ 

public :
  HistogramPlotter(){}
  virtual ~HistogramPlotter(){}
  ///~HistogramPlotter(){}
  void addHisto(TString name, TString dirname, int range, double min, double max);
  void addHisto2D(TString name, TString dirname, int range1, double min1, double max1, int range2, double min2, double max2);
  void fillHisto2d(TString name, TString dirname, double value1, double value2, double weight=1.0);
  void initHisto(TFile *file, TString dir, TString subdir, TString histName, int Nbin, double min, double max);
  void initHisto2D(TFile *file, TString dir, TString subdir, TString histName, int nBin1, double min1, double max1, int nBin2, double min2, double max2);
  void fillHisto2D(TFile *file, TString dir, TString subdir, TString histName, int Nbin1, double min1, double max1, double value1, int Nbin2, double min2, double max2, double value2, double weight);
  void fillHisto(TFile *file, TString dir, TString subdir, TString histName, int Nbin, double min, double max, double value, double weight);
  TH1* getHisto(TString name, TString dirname);
  TH2* getHisto2d(TString name, TString dirname);

  // TProfile
  void initTProfile(TFile *file, TString dir, TString subdir, TString histName, int nXBin, Float_t xBin_array[]);
  void addTProfile(TString name, TString dirname, int nXBin, Float_t xBin_array[]);
  void fillTProfile(TFile *file, TString dir, TString subdir, TString histName, int nXBin, Float_t xBin_array[], double value1, double value2, double weight);

private :
  std::map<TString, TH1*> histos1_;
  std::map<TString, TH2*> histos2_;
  std::map<TString, TProfile*> tprofile_;
  //static std::map<TString, histos1_> histDir1_;
  //static std::map<TString, histos2_> histDir2_;
  //std::map<TString, TDirectory*> hDir_;
  ClassDef(HistogramPlotter, 1)
};
#endif



