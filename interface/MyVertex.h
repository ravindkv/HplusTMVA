#ifndef __MYVERTEX_H__
#define __MYVERTEX_H__

#include "TROOT.h"
#include <map>
#include <vector>
#include <string>

#include "MomentumVec.h"

class MyVertex
{
 public:
  MyVertex();
  ~MyVertex();
  
  void Reset();
  
  double chi2;
  Point3D        ErrXYZ;   //  error position
  int isValid;
  int totVtx;
  double ndof;
  double normalizedChi2;
  double rho;  // for maxd0 selection (<2)
  double rhoAll;
  Point3D        XYZ;      //  position
  
 private :

};
#endif
