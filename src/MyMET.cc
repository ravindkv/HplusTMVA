#include "interface/MyMET.h"

MyMET::MyMET():
  
  emEtFraction(-999.),
  hadEtFraction(-999.),
  isPFMET(false),
  metName(""),
  metSignificance(999.),
  muonEtFraction(-999.),
  sumEt(-999.)
{
}

MyMET::~MyMET()
{
}
void MyMET::Reset()
{
  emEtFraction = -999.;
  hadEtFraction = -999.;
  isPFMET = false;
  metName = "";
  metSignificance = -999.;
  muonEtFraction = -999.;
  p4.SetCoordinates(0.0,0.0,0.0,0.0);
  sumEt = -999.;
}
