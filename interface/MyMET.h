#ifndef __MYMET_H__
#define __MYMET_H__

#include "TROOT.h"
#include <map>
#include <vector>
#include <string>

#include "MomentumVec.h"


class MyMET
{
 public:
  MyMET();
  ~MyMET();
  
  void Reset();
  
  double emEtFraction;
  double hadEtFraction;
  bool isPFMET;
  std::string metName;
  double metSignificance;
  double muonEtFraction;
  MyLorentzVector p4;         // missing Et vector -->> 4D vector since no 2D object available in [root/5.14.00f-CMS3q] ...
  double sumEt;
  
 private :

};
#endif
