#include "interface/SVEffUnc.hh"

ClassImp(SVEffUnc)

Double_t SVEffUnc::getUncC(Float_t pt)
{

  // SFc = SFb with twice the quoted uncertainty

  Float_t x = pt;
  if(pt >= 800.0) x = 799.9;
  if(pt < 20.0) x = 20.0;

  Double_t SFc = (0.938887+(0.00017124*x))+(-2.76366e-07*(x*x));
  
  Double_t SFb_error_2012[] = {0.0415707, 0.0204209, 0.0223227, 0.0206655, 0.0199325, 0.0174121, 0.0202332, 0.0182446, 0.0159777, 0.0218531, 0.0204688, 0.0265191, 0.0313175, 0.0415417, 0.0740446, 0.0596716};
  Float_t ptmin_2012[] = {20, 30, 40, 50, 60, 70, 80, 100, 120, 160, 210, 260, 320, 400, 500, 600};
  Float_t ptmax_2012[] = {30, 40, 50, 60, 70, 80,100, 120, 160, 210, 260, 320, 400, 500, 600, 800};

  Double_t SFc_error_x = 0.0;

  UInt_t nbins = 16;

  for (UInt_t ibin=0; ibin<nbins; ibin++) {
    if(x >= ptmin_2012[ibin] && x < ptmax_2012[ibin]) SFc_error_x = 2.0*SFb_error_2012[ibin];
  }
  if(pt >= 800.0) SFc_error_x = 2.0*2.0*0.0717567;
  if(pt <   20.0) SFc_error_x = 2.0*2.0*0.0554504;

  Double_t EffUnc = sqrt(pow((1-SFc),2) + pow((2*SFc_error_x), 2));

  return EffUnc;

}

Double_t SVEffUnc::getUncL(Float_t pt, Float_t eta)
{

  Float_t x = min(double(pt), 670.0);

  Double_t SFl = 0.; Double_t SFl_up = 0.; Double_t SFl_down = 0.;

  if(fabs(eta) >= 0.0 && fabs(eta) < 0.8) {
    SFl = ((1.07541+(0.00231827*x))+(-4.74249e-06*(x*x)))+(2.70862e-09*(x*(x*x)));
    SFl_down = ((0.964527+(0.00149055*x))+(-2.78338e-06*(x*x)))+(1.51771e-09*(x*(x*x)));
    SFl_up = ((1.18638+(0.00314148*x))+(-6.68993e-06*(x*x)))+(3.89288e-09*(x*(x*x)));
  } else if(fabs(eta) >= 0.8 && fabs(eta) < 1.6) {
    SFl = ((1.05613+(0.00114031*x))+(-2.56066e-06*(x*x)))+(1.67792e-09*(x*(x*x)));
    SFl_down = ((0.946051+(0.000759584*x))+(-1.52491e-06*(x*x)))+(9.65822e-10*(x*(x*x)));
    SFl_up = ((1.16624+(0.00151884*x))+(-3.59041e-06*(x*x)))+(2.38681e-09*(x*(x*x)));
  } else if(fabs(eta) >= 1.6 && fabs(eta) < 2.4) {
    SFl = ((1.05625+(0.000487231*x))+(-2.22792e-06*(x*x)))+(1.70262e-09*(x*(x*x)));
    SFl_down = ((0.956736+(0.000280197*x))+(-1.42739e-06*(x*x)))+(1.0085e-09*(x*(x*x)));
    SFl_up = ((1.15575+(0.000693344*x))+(-3.02661e-06*(x*x)))+(2.39752e-09*(x*(x*x)));
  }

  Double_t SFl_error = max(fabs(SFl_up - SFl), fabs(SFl - SFl_down));

  Double_t EffUnc = sqrt(pow((1-SFl),2) + pow(SFl_error, 2));

  return EffUnc;

}

