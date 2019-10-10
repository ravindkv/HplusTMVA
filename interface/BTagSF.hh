#ifndef _btagsf_hh_
#define _btagsf_hh_

#if !defined(__CINT__) || defined(__MAKECINT__)

#include "TRandom3.h"
#include "TH2.h"
#include "TH2D.h"
#include <iostream>
#include <stdio.h>
#include <math.h>
#include "BTagCalibrationStandalone.h"
#endif
using namespace std;
class BTagSF{
  
public:
  BTagSF( int seed=0 )
  { 
    randm = new TRandom3(seed);};
  
  virtual ~BTagSF() {
    delete randm;
  };
  ///~BTagSF() {delete randm;};
  //Event reweighting using scale factors and MC b-tagging efficiencies 
  //https://twiki.cern.ch/twiki/bin/viewauth/CMS/BTagSFMethods#1a)%20Event%20reweighting%20using%20scal
  double getBTagPmc(TH2D *h2_qTagEff_Num, TH2D *h2_qTagEff_Denom, double eta, double pt, double csv);
  double getBTagPdata(BTagCalibrationReader &reader, TH2D *h2_qTagEff_Num, TH2D *h2_qTagEff_Denom, double eta, double pt, double csv, int jetFlavor, int bTagSys);

  double getBTagSF(BTagCalibrationReader &reader, double eta, double pt, double csv, double jetFlavor, int bTagSys);
  double getBTagEff(TH2D *h2_BTaggingEff_Num, TH2D *h2_BTaggingEff_Denom, double eta, double pt);

private:
  TRandom3* randm;
  ClassDef(BTagSF, 1)
};
#endif
