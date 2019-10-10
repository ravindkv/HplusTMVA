#ifndef __MYELECTRON_H__
#define __MYELECTRON_H__

#include "TROOT.h"
#include <map>
#include <vector>
#include <string>
#include "MomentumVec.h"

class MyElectron 
{
 public:
  MyElectron();
  ~MyElectron();
  
  void Reset();
  
  ///std::string GetName() { return name; };
 
//Variables : https://twiki.cern.ch/twiki/bin/viewauth/CMS/CutBasedElectronIdentificationRun2  

  ///basic
  int charge;
  int gen_id;
  int gen_mother_id;
  //std::string name; ///Memory leak
  TString eleName; 

  MyLorentzVector p4;
  double eleSCEta;
  Point3D       vertex;   

  ///sel
  double sigmaIetaIeta; //full5x5_sigmaIetaIeta 
  double dEtaInSeed; //abs(dEtaInSeed)
  double dPhiIn;     //abs(dPhiIn)
  double hadOverEm;  //H/E 
  double iEminusiP;     //abs(1/E-1/p)
  double nInnerHits;  //expected missing inner hits 
  bool isPassConVeto; //pass conversion veto
  
  ///ids
  int    isEE;
  int    isEB;
  
  ///iso
  double ChHadIso; 
  double PhotonIso;  
  double NeuHadIso;  
  double PileupIso;
  double relCombPFIsoEA;//Rel. comb. PF iso with EA corr
  double D0;
  double Dz;

  //conversion and IDs
  bool passEleID;
  bool passConversionVeto;

 private :
};
#endif
