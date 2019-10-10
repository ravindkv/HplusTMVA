#ifndef _sveffunc_hh_
#define _sveffunc_hh_

#if !defined(__CINT__) || defined(__MAKECINT__)

#include "TRandom3.h"
#include <iostream>
#include <stdio.h>
#include <math.h>
#endif
using namespace std;
class SVEffUnc{
  
public:
  SVEffUnc( ) {};
  
  virtual ~SVEffUnc() {};
 ///~SVEffUnc() {};
  
  Double_t getUncC(Float_t pt);
  Double_t getUncL(Float_t pt, Float_t eta);

private:
  
  ClassDef(SVEffUnc, 1)
};
#endif
