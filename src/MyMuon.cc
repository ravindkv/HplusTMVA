#include "interface/MyMuon.h"

MyMuon::MyMuon():

  ///basic
  charge(0),
  gen_id(0),
  gen_mother_id(0),
  muName(""),
  type(0),
  
  ///id
  //Loose
  isGlobalMuon(true),
  isPFMuon(true),
  isTrackerMuon(true),
  
  //Medium
  chi2LocalPosition(-999.),
  normChi2(-999.),
  segmentCompatibility(-999.),
  trkKink(-999.),
  validFraction(-999.),
 
  //Tight
  D0(-999.),
  Dz(-999.),
  nMatchedStations(-999),
  nMuonHits(-999),
  nPixelHits(-999),
  nTrackerLayers(-999),
  
  ///iso
  ChHadIso(999.),  
  NeuHadIso(999.),   
  pfRelIso(999.), 
  PhotonIso(999.),   
  PileupIso(999.) 
{
}

MyMuon::~MyMuon()
{
}

void MyMuon::Reset()
{
  
  ///basic
  charge = 0;
  gen_id = 0;
  gen_mother_id = 0;
  muName = "";
  p4.SetCoordinates(0.0, 0.0, 0.0, 0.0);
  type = 0;
  vertex.SetCoordinates(0.0, 0.0, 0.0);
  
  ///id
  //Loose
  isGlobalMuon = true;
  isPFMuon = true;
  isTrackerMuon = true;
  //Medium
  chi2LocalPosition = -999.;
  normChi2 = -999.;
  segmentCompatibility = -999.;
  trkKink = -999.;
  validFraction = -999.;
  //Tight
  D0 = -999.;
  Dz = -999.;
  nMatchedStations = -999;
  nMuonHits = -999;
  nPixelHits = -999;
  nTrackerLayers = -999;
  
  ///iso
  ChHadIso = 999.;   
  NeuHadIso = 999.;    
  pfRelIso = 999.;  
  PhotonIso = 999.;    
  PileupIso = 999.;  
}
