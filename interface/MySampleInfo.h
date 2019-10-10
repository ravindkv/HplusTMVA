#ifndef __MYSAMPLEINFO_H__
#define __MYSAMPLEINFO_H__

#include "TROOT.h"
#include <string>
#include <vector>

class MySampleInfo
{
 public:
  MySampleInfo();
  ~MySampleInfo();
  
  std::string sampleName;
  int mcEvtType;
  std::vector<double>pileup;
  std::vector<double>truepileup;
  ///std::vector<double>puWeights;
  ///std::vector<double>truepuWeights;
  //Number of particles in an event
  int hepNUP;
  //particle pdg id
  std::vector<int>hepIDUP;
  //particle status
  std::vector<int>hepISTUP;
  std::vector<double>topPtWeights;
  
 private :

};
#endif 
