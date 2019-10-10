#include "interface/HistogramPlotter.hh" 
#include <iostream> 
#include <iomanip> 
#include <math.h>
 
ClassImp(HistogramPlotter) 

void HistogramPlotter::addHisto(TString name, TString dirname, int range, double min, double max)
{
  //TString fullname = name+"_"+dirname; 
  TString fullname = dirname+"/"+name;
  std::string hname(fullname);
  histos1_[fullname] = new TH1F(name.Data(), hname.c_str(), range, min, max); 
  histos1_[fullname]->Sumw2();
}

void HistogramPlotter::initTProfile(TFile *file, TString dir, TString subdir, TString histName, int nXBin, Float_t xBin_array[]){
  std::string histPath;
  histPath = std::string(dir+"/"+subdir);
  TDirectory *d = file->GetDirectory(histPath.c_str());
  if(!d) file->mkdir(histPath.c_str());
  file->cd(histPath.c_str());
  addTProfile(histName, histPath, nXBin, xBin_array);
}

void HistogramPlotter::addTProfile(TString name, TString dirname, int nXBin, Float_t xBin_array[]){
  //TString fullname = name+"_"+dirname;
  TString fullname = dirname+"/"+name;
  std::string hname(fullname); 
  tprofile_[fullname] = new TProfile(name.Data(), hname.c_str(), nXBin, xBin_array);
  tprofile_[fullname]->Sumw2();
  tprofile_[fullname]->SetErrorOption("s");
}

void HistogramPlotter::fillTProfile(TFile *file, TString dir, TString subdir, TString histName, int nXBin, Float_t xBin_array[], double value1, double value2, double weight)
{
  TString fullname = dir+"/"+subdir+"/"+histName;
  if(!tprofile_[fullname]){
    initTProfile(file, dir, subdir, histName, nXBin, xBin_array); 
  }
  //then, fill TProfile
  tprofile_[fullname]->Fill(value1, value2, weight);
}

void HistogramPlotter::addHisto2D(TString name, TString dirname, int nBin1, double min1, double max1, int nBin2, double min2, double max2)
{
  //TString fullname = name+"_"+dirname;
  TString fullname = dirname+"/"+name;
  std::string hname(fullname); 
  histos2_[fullname] = new TH2D(name.Data(), hname.c_str(), nBin1, min1, max1, nBin2, min2, max2);
  histos2_[fullname]->Sumw2();
}

void HistogramPlotter::initHisto(TFile *file, TString dir, TString subdir, TString histName, int Nbin, double min, double max){
  std::string histPath;
  histPath = std::string(dir+"/"+subdir);
  TDirectory *d = file->GetDirectory(histPath.c_str());
  if(!d) file->mkdir(histPath.c_str());
  file->cd(histPath.c_str());
  addHisto(histName, histPath, Nbin, min, max);
  }

void HistogramPlotter::initHisto2D(TFile *file, TString dir, TString subdir, TString histName, int nBin1, double min1, double max1, int nBin2, double min2, double max2){
  std::string histPath;
  histPath = std::string(dir+"/"+subdir);
  TDirectory *d = file->GetDirectory(histPath.c_str());
  if(!d) file->mkdir(histPath.c_str());
  file->cd(histPath.c_str());
  addHisto2D(histName, histPath, nBin1, min1, max1, nBin2, min2, max2);
}

void HistogramPlotter::fillHisto(TFile *file, TString dir, TString subdir, TString histName, int Nbin, double min, double max, double value, double weight)
{
  TString fullname = dir+"/"+subdir+"/"+histName;
  if(!histos1_[fullname]){
    initHisto(file, dir, subdir, histName, Nbin, min,  max); 
  }
  //then, fill the histogram
  histos1_[fullname]->Fill(value, weight);
}

void HistogramPlotter::fillHisto2D(TFile *file, TString dir, TString subdir, TString histName, int nBin1, double min1, double max1, double value1, int nBin2, double min2, double max2, double value2, double weight)
{
  TString fullname = dir+"/"+subdir+"/"+histName;
  if(!histos2_[fullname]){
    initHisto2D(file, dir, subdir, histName, nBin1, min1, max1, nBin2, min2, max2); 
  }
  //then, fill the histogram
  histos2_[fullname]->Fill(value1, value2, weight);
}


TH2* HistogramPlotter::getHisto2d(TString name, TString dirname)
{
  TString fullname = dirname+"/"+name;
  TH2 * h = 0;
  if(histos2_.find(fullname) != histos2_.end())h = histos2_[fullname];
  return h;
}

TH1* HistogramPlotter::getHisto(TString name, TString dirname)
{
  //TString fullname = name+"_"+dirname;
  TString fullname = dirname+"/"+name;
  TH1 * h = 0;
  if(histos1_.find(fullname) != histos1_.end())h = histos1_[fullname];
  else if(histos2_.find(fullname) != histos2_.end())h = histos2_[fullname];
  return h;
}

