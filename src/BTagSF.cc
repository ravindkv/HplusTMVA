#include "interface/BTagSF.hh"

ClassImp(BTagSF)
//https://twiki.cern.ch/twiki/bin/viewauth/CMS/BTagSFMethods#1a)%20Event%20reweighting%20using%20scal
double BTagSF::getBTagPmc(TH2D *h2_qTagEff_Num, TH2D *h2_qTagEff_Denom, double eta, double pt, double csv){
  double csvM = 0.8484; //0.5426, 0.9535
  double pMC = 1.0; 
  if(csv> csvM) pMC = getBTagEff(h2_qTagEff_Num, h2_qTagEff_Denom, eta, pt);
  else pMC = 1 - getBTagEff(h2_qTagEff_Num, h2_qTagEff_Denom, eta, pt);
  return (pMC>0)?pMC:1.0;
}

double BTagSF::getBTagPdata(BTagCalibrationReader &reader, TH2D *h2_qTagEff_Num, TH2D *h2_qTagEff_Denom, double eta, double pt, double csv, int jetFlavor, int bTagSys){
  double csvM = 0.8484; //0.5426, 0.9535
  double csvOP = csvM;
  double pData = 1.0; 
  double sf = 1.0;
  double eff = 1.0;
  if(csv> csvOP){//tagged 
    sf = getBTagSF(reader, eta, pt, csv, jetFlavor, bTagSys);
    eff = getBTagEff(h2_qTagEff_Num, h2_qTagEff_Denom, eta, pt);
    pData = sf*eff;
  }
  else{// untagged
    sf = getBTagSF(reader, eta, pt, csv, jetFlavor, bTagSys);
    eff = getBTagEff(h2_qTagEff_Num, h2_qTagEff_Denom, eta, pt);
    pData = 1.0 - sf*eff;
  }
  return (pData>0)?pData:1.0;
}

//https://twiki.cern.ch/twiki/bin/view/CMS/BTagCalibration#Additional_scripts
//https://twiki.cern.ch/twiki/pub/CMS/BTagRecommendation80XReReco/CSVv2_Moriond17_B_H.csv
double BTagSF::getBTagSF(BTagCalibrationReader &reader, double eta, double pt, double csv, double jetFlavor, int bTagSys){
  double sf=1.0;
  if(abs(jetFlavor) ==5){
    if(bTagSys==0) sf = reader.eval_auto_bounds("central", BTagEntry::FLAV_B, eta, pt,csv);
    if(bTagSys==1) sf = reader.eval_auto_bounds("up",      BTagEntry::FLAV_B, eta, pt, csv);
    if(bTagSys==-1)sf = reader.eval_auto_bounds("down",    BTagEntry::FLAV_B, eta, pt, csv);
  }
  else if(abs(jetFlavor)==4){
    if(bTagSys==0) sf = reader.eval_auto_bounds("central", BTagEntry::FLAV_C, eta, pt,csv);
    if(bTagSys==1) sf = reader.eval_auto_bounds("up",      BTagEntry::FLAV_C, eta, pt, csv);
    if(bTagSys==-1)sf = reader.eval_auto_bounds("down",    BTagEntry::FLAV_C, eta, pt, csv);
  }
  else{
    if(bTagSys==0) sf = reader.eval_auto_bounds("central", BTagEntry::FLAV_UDSG, eta, pt,csv);
    if(bTagSys==1) sf = reader.eval_auto_bounds("up",      BTagEntry::FLAV_UDSG, eta, pt, csv);
    if(bTagSys==-1)sf = reader.eval_auto_bounds("down",    BTagEntry::FLAV_UDSG, eta, pt, csv);
  }
  return sf;
}
//https://twiki.cern.ch/twiki/bin/view/CMS/BTagSFMethods
double BTagSF::getBTagEff(TH2D *h2_BTagEff_Num, TH2D *h2_BTagEff_Denom, double eta, double pt){
  double eff = 0.0;
  double bin_num = h2_BTagEff_Num->FindBin(pt, double(eta));
  double bin_denom = h2_BTagEff_Denom->FindBin(pt, double(eta));
  double num = h2_BTagEff_Num->GetBinContent(bin_num); 
  double denom = h2_BTagEff_Denom->GetBinContent(bin_denom); 
  eff = num/denom;
  return eff;  
}
