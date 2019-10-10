#include "interface/MyTrack.h"

MyTrack::MyTrack():
  trackCharge(0),
  chiSquared(999.), 
  nHits(-999.),
  nPixHits(-999.),
  particleType(-999.),
  d0(-9999.),
  d0Error(-9999.)
{
}

MyTrack::~MyTrack(){
}


void MyTrack::Reset(){
  
  p4.SetCoordinates(0.0,0.0,0.0,0.0);
  
  trackCharge = 0;
  chiSquared = 999.;
  nHits = -999.;
  nPixHits = -999.;
  particleType = -999.;
  d0 = -9999.;
  d0Error = -9999.;
  
}
