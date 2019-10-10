#include "interface/MyKineFitParticle.h"

MyKineFitParticle::MyKineFitParticle():
  partName(""),
  //part_id(0),
  //part_mother_id(0),
  labelName(""),
  charge(0),
  chi2OfFit(999.),
  statusOfFit(0),
  probOfFit(0),
  njetsOfFit(0)
{
}

MyKineFitParticle::~MyKineFitParticle() 
{
}

void MyKineFitParticle::Reset()
{
  p4.SetCoordinates(0.0, 0.0, 0.0, 0.0);
  //vertex.SetCoordinates(-999.0,-999.0,-999.0);

  partName = "";
  //part_id = 0;
  //part_mother_id = 0;
  labelName = "";
  charge = 0;
  chi2OfFit = 999.;
  statusOfFit = 0;
  probOfFit = 0;
  njetsOfFit = 0;
}
