#ifndef __MYMUON_H__
#define __MYMUON_H__

#include "TROOT.h"
#include <map>
#include <vector>
#include <string>

#include "MomentumVec.h"


class MyMuon 
{
 public:
  MyMuon();
  ~MyMuon();
  
  void Reset();
  
  std::string GetName() { 
      std::string name(muName);
      return name; 
  };
  //https://twiki.cern.ch/twiki/bin/viewauth/CMS/SWGuideMuonIdRun2

  ///basic
  int charge;
  int gen_id;
  int gen_mother_id;
  //std::string name;
  TString muName;
  MyLorentzVector p4; 
  int type;
  Point3D    vertex;   

  ///id
  //Loose
  bool isGlobalMuon;
  bool isPFMuon;
  bool isTrackerMuon;
  //Medium 
  double chi2LocalPosition;
  double normChi2;
  double segmentCompatibility;
  double trkKink;
  double validFraction;
  //Tight
  double D0;          
  double Dz;
  int nMatchedStations;
  int nMuonHits;
  int nPixelHits;
  int nTrackerLayers;
 
  ///iso
  double ChHadIso; 
  double NeuHadIso;  
  double pfRelIso;
  double PhotonIso;  
  double PileupIso;
 private :

};
#endif
