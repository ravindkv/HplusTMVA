#include "interface/MySampleInfo.h"

MySampleInfo::MySampleInfo()
{
  sampleName="";
  mcEvtType = 0;
  pileup.clear();
  truepileup.clear();
  ///puWeights.clear();
  ///truepuWeights.clear();
  hepNUP = -99;
  topPtWeights.clear();
  hepIDUP.clear();
  hepISTUP.clear();
}

MySampleInfo::~MySampleInfo()
{
}
