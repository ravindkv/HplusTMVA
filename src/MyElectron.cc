#include "interface/MyElectron.h"

MyElectron::MyElectron():

  ///basic
  charge(0), 
  gen_id(0),
  gen_mother_id(0),
  //name(""),
  eleName(""),
  eleSCEta(0),

  ///sel
  sigmaIetaIeta(-9),
  dEtaInSeed(-9),
  dPhiIn(-9),
  hadOverEm(-9),
  iEminusiP(-9),
  nInnerHits(-9),
  isPassConVeto(true),

  ///ids
  isEE(-1),
  isEB(-1),
  
  ///iso
  ChHadIso(-9.),  
  PhotonIso(-9.),   
  NeuHadIso(-9.),   
  PileupIso(-9.), 
  relCombPFIsoEA(-9.),
  D0(-9.),
  Dz(-9.),
  passEleID(true),
  passConversionVeto(true)
{
}

MyElectron::~MyElectron()
{
}


void MyElectron::Reset()
{
  ///basic
  charge = 0; 
  gen_id = 0;
  gen_mother_id = 0;
 // name = "";
  eleName = "";
  p4.SetCoordinates(0.0, 0.0, 0.0, 0.0);
  eleSCEta = 0;
  vertex.SetCoordinates(0.0, 0.0, 0.0);
 
  ///sel
  sigmaIetaIeta = -9.;
  dEtaInSeed = -9.;
  dPhiIn = -9.;
  hadOverEm = -9.;
  iEminusiP = -9.;
  nInnerHits = -9.;
  isPassConVeto = true;
  
  ///ids
  isEE = -1;
  isEB = -1;
  
  ///iso
  ChHadIso = -9.;   
  PhotonIso = -9.;    
  NeuHadIso = -9.;    
  PileupIso = -9.;  
  relCombPFIsoEA = -9.; 
  D0 = -9.;
  Dz = -9.;
  passEleID = true;
  passConversionVeto = true;
}
