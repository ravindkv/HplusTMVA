#ifndef __MYKINEFITPARTICLE_H__
#define __MYKINEFITPARTICLE_H__

#include "TROOT.h"
#include <map>
#include <vector>
#include <string>

#include "MomentumVec.h"

class MyKineFitParticle 
{
 public:
  MyKineFitParticle();
  ~MyKineFitParticle();
  
  void   Reset();
  
  MyLorentzVector p4;         // 4 vector
  //Point3D vertex;
  std::string partName;
  //int part_id;
  //int part_mother_id;
  std::string labelName;
  double charge;

  double chi2OfFit;
  int statusOfFit;
  double probOfFit;
  int njetsOfFit;

 private :

}; 
#endif
