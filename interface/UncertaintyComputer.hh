#ifndef _uncertaintycomputer_h_
#define _uncertaintycomputer_h_

#if !defined(__CINT__) || defined(__MAKECINT__)

#include <iomanip>
#include <iostream>
#include <fstream>

#include "TRandom2.h"
#include "TMatrixD.h"
#include "TF1.h"
#include "TProfile.h"
#include "TObjArray.h"
#include "TMatrixD.h"
#include "TH1.h"
#include "TTimeStamp.h"
#include <exception>

#ifdef _STANDALONE
#include "Reader.h"
#else
#include "interface/Reader.h"
#endif
#include "interface/BTagSF.hh"
#include "interface/CTagSF.hh"
#include "interface/SVEffUnc.hh"
#include "BTagCalibrationStandalone.h"

#endif
//https://twiki.cern.ch/twiki/bin/view/CMS/JetResolution
const double JEREtaMap[14] = {0., 0.5, 0.8, 1.1, 1.3, 1.7, 1.9, 2.1, 2.3, 2.5, 2.8, 3.0, 3.2, 5.0}; 
const double JERSF[13]     = {1.109, 1.138, 1.114, 1.123, 1.084, 1.082, 1.140, 1.067, 1.177, 1.364, 1.857, 1.328, 1.160};
//New SF with stat + sys unc
//https://github.com/cms-jet/JRDatabase/blob/master/textFiles/Spring16_25nsV10a_MC/Spring16_25nsV10a_MC_SF_AK4PFchs.txt
const double JERSFUp[13]   = {1.174, 1.204, 1.178, 1.224, 1.183, 1.191, 1.260, 1.181, 1.387, 1.525, 2.060, 1.453, 1.307};
const double JERSFDown[13] = {1.044, 1.072, 1.050, 1.022, 0.985, 0.973, 1.020, 0.953, 0.967, 1.203, 1.654, 1.203, 1.013};
//const double JERSFUp[13] = {1.109+0.008 , 1.138+0.013, 1.114+0.013, 1.123+0.024, 1.084+0.011, 1.082+0.035, 1.140+0.047, 1.067+0.053, 1.177+0.041, 1.364+0.039, 1.857+0.071, 1.328+0.022, 1.16+0.029};
//const double JERSFDown[13] = {1.109-0.008 , 1.138-0.013, 1.114-0.013, 1.123-0.024, 1.084-0.011, 1.082-0.035, 1.140-0.047, 1.067-0.053, 1.177-0.041, 1.364-0.039, 1.857-0.071, 1.328-0.022, 1.16-0.029};
class UncertaintyComputer{
public :
  UncertaintyComputer()
  {
    btsf = new BTagSF(12345);
    ctsf = new CTagSF(12345);
    sveffunc = new SVEffUnc();
  }

   virtual ~UncertaintyComputer(){
   ///~UncertaintyComputer(){
     delete btsf;
     delete ctsf;
     delete sveffunc;
  }
  double muPtWithRochCorr(const MyMuon *mu, bool isData=false, double u1=0.5, double u2=0.4, int s=0, int m=0); 
  double metWithJES(const vector<MyJet> & vJ, vector<int> *j, MyMET MET, int jes=0);
  double metWithJER(const vector<MyJet> & vJ, vector<int> *j, MyMET MET, int jer=0);
  double metWithJESJER(const vector<MyJet> & vJ, vector<int> *j, MyMET MET, int jes=0, int jer=0, bool isData = false);
  double metWithUncl(const vector<MyJet> & vJ, vector<int> *j, const vector<MyMuon> &vMu, vector<int> *m, const vector<MyElectron> &vEle, vector<int> *el, MyMET MET, int unc=0);
  double getJERSF(double eta, int jer=0);
  double jetPtWithJESJER(MyJet jet, int jes=0, int jer=0, bool isData=false); 
  void  openCSVfile(const std::string &filename); 
  double EffUncOnSV(MyJet jet);
  double DeltaR(MyLorentzVector aV, MyLorentzVector bV);
  
  // bTag SF, by event reweighting
  double getBTagPmcSys(TH2D *h2_qTagEff_Num, TH2D *h2_qTagEff_Denom, MyJet jet);
  double getBTagPdataSys(BTagCalibrationReader &reader, TH2D *h2_qTagEff_Num, TH2D *h2_qTagEff_Denom, MyJet jet, int scale);
  double getIncCTagPmcSys(TH2D *h2_qTagEff_Num, TH2D *h2_qTagEff_Denom, MyJet jet, bool isCTag);
  double getIncCTagPdataSys(BTagCalibrationReader &reader, TH2D *h2_qTagEff_Num, TH2D *h2_qTagEff_Denom, MyJet jet, bool isCTag, int scale);
  
private :
  BTagSF* btsf;
  CTagSF* ctsf;
  SVEffUnc* sveffunc;
  ClassDef(UncertaintyComputer, 1)
};
#endif
