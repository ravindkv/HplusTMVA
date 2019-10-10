#ifndef __MYTRACK_H__
#define __MYTRACK_H__

#include "TROOT.h"
#include <map>
#include <vector>
#include <string>

#include "MomentumVec.h"

class MyTrack 
{
 public:
  MyTrack();
  ~MyTrack();
  
  void Reset();
  
  MyLorentzVector p4;
  
  double  trackCharge;
  double chiSquared;
  double nHits;
  double nPixHits;
  double particleType;
  double d0;
  double d0Error;
 private :

    
};
#endif    
