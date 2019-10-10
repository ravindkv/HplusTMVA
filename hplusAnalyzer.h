
#include <iomanip>
#include <iostream>
#include <fstream>

#include "TRandom2.h"
#include "TMatrixD.h"
#include "TF1.h"
#include "TProfile.h"
#include "TObjArray.h"
#include "TMatrixD.h"
#include "TH1.h"
#include "TH2.h"
#include "TTimeStamp.h"
#include "Math/VectorUtil.h"

#include "interface/Reader.h"
#include "interface/ObjectSelector.hh"
#include "interface/MomentumVec.h"
#include "interface/LumiReweighting.h"
#include "interface/UncertaintyComputer.hh"
#include "interface/HistogramPlotter.hh"
#include "interface/BTagCalibrationStandalone.h"


//---------------------------------------------------//
// Main Class
//---------------------------------------------------//
class hplusAnalyzer : public ObjectSelector, HistogramPlotter
{
public :
  hplusAnalyzer() : ObjectSelector(), HistogramPlotter()
  {
    DRMIN_JET = 0.4;
    DRMIN_ELE = 0.4;
    //---------------------------------------------------//
    //Pileup reweigting 
    //---------------------------------------------------//
    //PU info for Data: 
    //https://twiki.cern.ch/twiki/bin/viewauth/CMS/PileupJSONFileforData
    //PU info for MC:
    //https://twiki.cern.ch/twiki/bin/viewauth/CMS/Pileup_MC_Information
    //data-pileup with min bias xss = 69200 mb
    LumiWeights_ = reweight::LumiReWeighting("stack/lumiRewgt/trueInTimePU_mcDY_6000bins.root",
            "stack/lumiRewgt/trueMinBiasPU_data_JSON_23Sep2016ReReco_69200_1000_6000.root", "pileup", "pileup");
    //data-pileup with min bias xss = 72383 mb (4.7% more w.r.t. 69200)
    LumiWeights_Up = reweight::LumiReWeighting("stack/lumiRewgt/trueInTimePU_mcDY_6000bins.root",
            "stack/lumiRewgt/trueMinBiasPU_data_JSON_23Sep2016ReReco_72383_1000_6000.root", "pileup", "pileup");
    //data-pileup with min bias xss = 66016 mb (4.7% less w.r.t. 69200)
    LumiWeights_Down = reweight::LumiReWeighting("stack/lumiRewgt/trueInTimePU_mcDY_6000bins.root",
            "stack/lumiRewgt/trueMinBiasPU_data_JSON_23Sep2016ReReco_66016_1000_6000.root", "pileup", "pileup");
    PShiftDown_ = reweight::PoissonMeanShifter(-0.5);
    PShiftUp_ = reweight::PoissonMeanShifter(0.5);
    
    //---------------------------------------------------//
    //MC cross sections at 13 TeV 
    //---------------------------------------------------//
    //https://github.com/BristolTopGroup/AnalysisSoftware/blob/master/python/DataSetInfo_13TeV.py
    //https://github.com/BristolTopGroup/AnalysisSoftware/blob/master/python/DataSetInfo_13TeV_25ns.py
    //https://indico.cern.ch/event/617002/contributions/2490586/attachments/1419016/2173704/update_27022017.pdf
    //evtDBS= event at Data Base Server i.e in DAS (https://cmsweb.cern.ch/das/).
    
    //signal samples
    //BR(W->ev) = 10.75± 0.3, BR(W->mv) = 10.57± 0.5
    //http://pdg.lbl.gov/2012/listings/rpp2012-list-w-boson.pdf
    //0.12155 = 2*0.065*(1-0.065), where 6.5% is the observed limit for 90 GeV at 8 TeV
    xss["HplusM100"]         =  831.76*0.2132*0.12155;   evtDBS["HplusM100"]         =  996170; 
    xss["HplusM120"]         =  831.76*0.2132*0.12155;   evtDBS["HplusM120"]         =  994498; 
    xss["HplusM140"]         =  831.76*0.2132*0.12155;   evtDBS["HplusM140"]         =  987730; 
    xss["HplusM150"]         =  831.76*0.2132*0.12155;   evtDBS["HplusM150"]         =  990645;
    xss["HplusM155"]         =  831.76*0.2132*0.12155;   evtDBS["HplusM155"]         =  952984;
    xss["HplusM160"]         =  831.76*0.2132*0.12155;   evtDBS["HplusM160"]         =  992264;
    xss["HplusM80"]          =  831.76*0.2132*0.12155;   evtDBS["HplusM80"]          =  976710;
    xss["HplusM90"]          =  831.76*0.2132*0.12155;   evtDBS["HplusM90"]          =  988480;

    //qcd muon enriched
    xss["QCD_Pt-15to20_Mu"]  =  3819570;       evtDBS["QCD_Pt-15to20_Mu"]  =  4141251;
    xss["QCD_Pt-20to30_Mu"]  =  2960198;       evtDBS["QCD_Pt-20to30_Mu"]  =  31475157;
    xss["QCD_Pt-30to50_Mu"]  =  1652471;       evtDBS["QCD_Pt-30to50_Mu"]  =  29954815;
    xss["QCD_Pt-50to80_Mu"]  =  437504;        evtDBS["QCD_Pt-50to80_Mu"]  =  19806915;
    xss["QCD_Pt-80to120_Mu"] =  106033;        evtDBS["QCD_Pt-80to120_Mu"] =  13786971;
    xss["QCD_Pt-120to170_Mu"]=  25190;         evtDBS["QCD_Pt-120to170_Mu"]=  8042721;
    xss["QCD_Pt-170to300_Mu"]=  8654;          evtDBS["QCD_Pt-170to300_Mu"]=  7947159;
    xss["QCD_Pt-300to470_Mu"]=  797;           evtDBS["QCD_Pt-300to470_Mu"]=  7937590;
    
    //qcd EM enriched
    xss["QCD_Pt-15to20_EM"]  =  254600;        evtDBS["QCD_Pt-15to20_EM"]  =  5652601;
    xss["QCD_Pt-20to30_EM"]  =  5352960;       evtDBS["QCD_Pt-20to30_EM"]  =  9218954;
    xss["QCD_Pt-30to50_EM"]  =  9928000;       evtDBS["QCD_Pt-30to50_EM"]  =  4730195;
    xss["QCD_Pt-50to80_EM"]  =  2890800;       evtDBS["QCD_Pt-50to80_EM"]  =  22337070;
    xss["QCD_Pt-80to120_EM"] =  350000;        evtDBS["QCD_Pt-80to120_EM"] =  35841783;
    xss["QCD_Pt-120to170_EM"]=  62964;         evtDBS["QCD_Pt-120to170_EM"]=  35817281;
    xss["QCD_Pt-170to300_EM"]=  18810;         evtDBS["QCD_Pt-170to300_EM"]=  11540163;
    xss["QCD_Pt-300toInf_EM"]=  1350;          evtDBS["QCD_Pt-300toInf_EM"]=  7373633;    

    //single top and ttbar
    xss["ST_s"]              =  10.32;         evtDBS["ST_s"]              =  2989199;
    xss["ST_t"]              =  80.95;         evtDBS["ST_t"]              =  38811017;
    xss["ST_tW"]             =  71.7;          evtDBS["ST_tW"]             =  6933094;
    xss["TTJetsM"]           =  831.76;        evtDBS["TTJetsM"]           =  10139950;   
    xss["TTJetsP"]           =  831.76;        evtDBS["TTJetsP"]           =  77081156;   

    //for ttbar systematics
    xss["TTJetsP_up"]        =  831.76;        evtDBS["TTJetsP_up"]        =  29310620;   
    xss["TTJetsP_down"]      =  831.76;        evtDBS["TTJetsP_down"]      =  28354188;   
    xss["TTJetsP_mtop1735"]  =  831.76;        evtDBS["TTJetsP_mtop1735"]  =  19419050;   
    xss["TTJetsP_mtop1715"]  =  831.76;        evtDBS["TTJetsP_mtop1715"]  =  19578812;   
    xss["TTJetsP_hdampUP"]   =  831.76;        evtDBS["TTJetsP_hdampUP"]   =  29689380;   
    xss["TTJetsP_hdampDOWN"] =  831.76;        evtDBS["TTJetsP_hdampDOWN"] =  29117820;   

    //DY + jets and W + jets 
    xss["DY1JetsToLL"]       =  1016;          evtDBS["DY1JetsToLL"]       =  62627174;
    xss["DY2JetsToLL"]       =  331.3;         evtDBS["DY2JetsToLL"]       =  19970551;
    xss["DY3JetsToLL"]       =  96.6;          evtDBS["DY3JetsToLL"]       =  5856110;
    xss["DY4JetsToLL"]       =  51.4;          evtDBS["DY4JetsToLL"]       =  4197868;
    xss["DYJetsToLL"]        =  4895;          evtDBS["DYJetsToLL"]        =  49144274;
    xss["W1JetsToLNu"]       =  9493;          evtDBS["W1JetsToLNu"]       =  45367044;
    xss["W2JetsToLNu"]       =  3120;          evtDBS["W2JetsToLNu"]       =  29878415;
    xss["W3JetsToLNu"]       =  942.3;         evtDBS["W3JetsToLNu"]       =  19798117;
    xss["W4JetsToLNu"]       =  524.2;         evtDBS["W4JetsToLNu"]       =  9170576;
    xss["WJetsToLNu"]        =  50690;         evtDBS["WJetsToLNu"]        =  29705748;

    //VV fusion
    xss["WW"]                =  118.7;         evtDBS["WW"]                =  994012;
    xss["WZ"]                =  46.74;         evtDBS["WZ"]                =  1000000;
    xss["ZZ"]                =  17.72;         evtDBS["ZZ"]                =  990064; 

    //Bkg from Higgs production
    //Gluon gluon fusion
    xss["GluGluHToBB"]            =   28.293   ; evtDBS["GluGluHToBB"]            = 4856192 ;
    xss["GluGluHToTauTau"]        =   3.046    ; evtDBS["GluGluHToTauTau"]        = 1471061 ;
    xss["GluGluHToCC"]            =   1.404    ; evtDBS["GluGluHToCC"]            = 9782840 ;
    xss["GluGluHToGG"]            =   3.979    ; evtDBS["GluGluHToGG"]            = 998200  ;
    xss["GluGluHToWWTo2L2Nu"]     =   1.090    ; evtDBS["GluGluHToWWTo2L2Nu"]     = 499473  ;
    xss["GluGluHToWWToLNuQQ"]     =   4.548    ; evtDBS["GluGluHToWWToLNuQQ"]     = 198585  ;
    xss["GluGluHToZZTo2L2Q"]      =   0.195    ; evtDBS["GluGluHToZZTo2L2Q"]      = 1000000 ;
    xss["GluGluHToZZTo4L"]        =   0.015    ; evtDBS["GluGluHToZZTo4L"]        = 992224  ;
    //W+H production
    xss["WplusH_HToBB_WToLNu"]    =   0.158    ; evtDBS["WplusH_HToBB_WToLNu"]    = 999800  ;
    xss["WplusH_HToBB_WToQQ"]     =   0.331    ; evtDBS["WplusH_HToBB_WToQQ"]     = 499093  ;
    xss["WplusHToTauTau"]         =   0.053    ; evtDBS["WplusHToTauTau"]         = 428036  ;
    xss["WplusH_HToCC_WToLNu"]    =   0.008    ; evtDBS["WplusH_HToCC_WToLNu"]    = 1482024 ;
    xss["WplusH_HToCC_WToQQ"]     =   0.016    ; evtDBS["WplusH_HToCC_WToQQ"]     = 459565  ;
    xss["WplusH_HToGG_WToAll"]    =   0.069    ; evtDBS["WplusH_HToGG_WToAll"]    = 300000  ;
    //W-H production
    xss["WminusH_HToBB_WToQQ"]    =   0.210    ; evtDBS["WminusH_HToBB_WToQQ"]    = 499994  ;
    xss["WminusHToTauTau"]        =   0.033    ; evtDBS["WminusHToTauTau"]        = 445200  ;
    xss["WminusH_HToCC_WToLNu"]   =   0.005    ; evtDBS["WminusH_HToCC_WToLNu"]   = 1477656 ;
    xss["WminusH_HToCC_WToQQ"]    =   0.010    ; evtDBS["WminusH_HToCC_WToQQ"]    = 457517  ;
    xss["WminusH_HToGG_WToAll"]   =   0.044    ; evtDBS["WminusH_HToGG_WToAll"]   = 300000  ;
    xss["WminusH_HToZZTo2L2X"]    =   0.014    ; evtDBS["WminusH_HToZZTo2L2X"]    = 978136  ;
    //ZH production
    xss["ZH_HToBB_ZToNuNu"]       =   0.103    ; evtDBS["ZH_HToBB_ZToNuNu"]       = 2924580 ;
    xss["ZH_HToBB_ZToLL"]         =   0.052    ; evtDBS["ZH_HToBB_ZToLL"]         = 1979860 ;
    xss["ZH_HToBB_ZToQQ"]         =   0.360    ; evtDBS["ZH_HToBB_ZToQQ"]         = 499200  ;
    xss["ZHToTauTau"]             =   0.055    ; evtDBS["ZHToTauTau"]             = 571597  ;
    xss["ZH_HToCC_ZToNuNu"]       =   0.005    ; evtDBS["ZH_HToCC_ZToNuNu"]       = 1183744 ;
    xss["ZH_HToCC_ZToLL"]         =   0.003    ; evtDBS["ZH_HToCC_ZToLL"]         = 4885552 ;
    xss["ZH_HToCC_ZToQQ"]         =   0.018    ; evtDBS["ZH_HToCC_ZToQQ"]         = 499384  ;
    xss["ZH_HToGG_ZToAll"]        =   0.072    ; evtDBS["ZH_HToGG_ZToAll"]        = 299739  ;
    xss["ZH_HToZZ_2L"]            =   0.002    ; evtDBS["ZH_HToZZ_2L"]            = 942259  ;
    //gg fusion to ZH
    xss["ggZH_HToBB_ZToNuNu"]     =   0.014    ; evtDBS["ggZH_HToBB_ZToNuNu"]     = 250000  ;
    xss["ggZH_HToBB_ZToLL"]       =   0.007    ; evtDBS["ggZH_HToBB_ZToLL"]       = 250000  ;
    xss["ggZH_HToBB_ZToQQ"]       =   0.050    ; evtDBS["ggZH_HToBB_ZToQQ"]       = 499130  ;
    xss["ggZH_HToCC_ZToNuNu"]     =   0.001    ; evtDBS["ggZH_HToCC_ZToNuNu"]     = 2457116 ;
    xss["ggZH_HToCC_ZToLL"]       =   0.000    ; evtDBS["ggZH_HToCC_ZToLL"]       = 2921029 ;
    xss["ggZH_HToCC_ZToQQ"]       =   0.002    ; evtDBS["ggZH_HToCC_ZToQQ"]       = 478600  ;
    xss["GluGluZH_HToWW"]         =   0.026    ; evtDBS["GluGluZH_HToWW"]         = 148525  ;
    //tt fusion
    xss["ttHToCC"]                =   0.015    ; evtDBS["ttHToCC"]                = 4784344 ;
    xss["ttHToGG"]                =   0.042    ; evtDBS["ttHToGG"]                = 768410  ;
    //bb fusion
    xss["bbHToBB"]                =   0.284    ; evtDBS["bbHToBB"]                = 749600  ;
    xss["bbHToGG"]                =   0.040    ; evtDBS["bbHToGG"]                = 746400  ;
    xss["bbHToWWTo2L2Nu"]         =   0.011    ; evtDBS["bbHToWWTo2L2Nu"]         = 749998  ;
    xss["bbH_HToZZTo4L"]          =   0.000    ; evtDBS["bbH_HToZZTo4L"]          = 1000000 ;
    //vector boson fustion
    xss["VBFHToBB"]               =   2.203    ; evtDBS["VBFHToBB"]               = 1000000 ;
    xss["VBFHToTauTau"]           =   0.237    ; evtDBS["VBFHToTauTau"]           = 1499400 ;
    xss["VBFHToCC"]               =   0.109    ; evtDBS["VBFHToCC"]               = 4980094 ;
    xss["VBFHToGG"]               =   0.310    ; evtDBS["VBFHToGG"]               = 1000000 ;
    xss["VBFHToWWTo2L2Nu"]        =   0.085    ; evtDBS["VBFHToWWTo2L2Nu"]        = 486510  ;
    xss["VBFHToWWToLNuQQ"]        =   0.354    ; evtDBS["VBFHToWWToLNuQQ"]        = 198937  ;
                                   
    //for default sample code
    xss["sampCode_"]         =  831.76*0.2132; evtDBS["sampCode_"]         =  994498; 
  };
  ~hplusAnalyzer() {
    delete evR;
  };
  
  void CutFlowAnalysis(TString url,  string myKey="PFlow", string evtType="data");
  void CutFlowProcessor(TString url,  string myKey="PFlow", TString cutflowType="base", TFile *outFile_=0);
  //void CreateAnalHistos(TString flowType, TFile* outFile_);
  void processEvents();
  float reweightHEPNUPWJets(int hepNUP);
  float reweightHEPNUPDYJets(int hepNUP);
private :
  double DRMIN_JET, DRMIN_ELE, METCUT_;
  Reader *evR;
  
  reweight::LumiReWeighting LumiWeights_;
  reweight::LumiReWeighting LumiWeights_Up;
  reweight::LumiReWeighting LumiWeights_Down;
  reweight::PoissonMeanShifter PShiftUp_;   //pileup syst up
  reweight::PoissonMeanShifter PShiftDown_; //pileup syst down 
  std::map<string, double> xss;
  std::map<string, double> evtDBS;
  std::map<string, double> muSF;
  /*
  BTagCalibrationReader myReadCSV(const std::string &tagger, const std::string &filename);
  */
  ofstream outfile_;
  BTagCalibrationReader myReadCSV(const std::string &filename,const std::string &tagger, BTagEntry::OperatingPoint op, const std::string & measurementType, const std::string & sysType, const std::vector<std::string> & otherSysTypes, BTagEntry::JetFlavor jf);
  Double_t getMuonSF(TH2D *h2, double eta, double pt);
  Double_t getMuonTrigSF(TH2D *h2, double eta, double pt);
  Double_t getMuonTrackSF(TGraphAsymmErrors *tg, double eta);
  Double_t getEleSF(TH2D *h2, double etaSC, double pt);
  Double_t getEleTrigSF(TH2D *h2, double pt, double etaSC);
  double deltaPhi12(double phi1, double phi2);
  double phi0to2pi(double phi);
};

float hplusAnalyzer::reweightHEPNUPWJets(int hepNUP) {
  int nJets = hepNUP-5;
  if(nJets==0)      return 2.11;
  else if(nJets==1) return 0.23;
  else if(nJets==2) return 0.119;
  else if(nJets==3) return 0.0562;
  else if(nJets>=4) return 0.0671;
  else return 1 ;
}

float hplusAnalyzer::reweightHEPNUPDYJets(int hepNUP){
  int nJets = hepNUP-5;
  if(nJets==0)      return 0.120;
  else if(nJets==1) return 0.0164;
  else if(nJets==2) return 0.0168;
  else if(nJets==3) return 0.0167;
  else if(nJets>=4) return 0.0128;
  else return 1 ;
}

BTagCalibrationReader hplusAnalyzer::myReadCSV(const std::string &filename, const std::string &tagger,  
		BTagEntry::OperatingPoint op, 
		const std::string & measurementType,
		const std::string & sysType, 
		const std::vector<std::string> & otherSysTypes, 
		BTagEntry::JetFlavor jf
		)
{ 
  BTagCalibration calib(tagger, filename);
  BTagCalibrationReader reader(op, sysType, otherSysTypes);      
  reader.load(calib, jf, measurementType); 
  return reader;
}
//https://twiki.cern.ch/twiki/bin/view/CMS/MuonWorkInProgressAndPagResults
Double_t hplusAnalyzer::getMuonSF(TH2D *h2, double eta, double pt){
  TAxis *xaxis = h2->GetXaxis();
  TAxis *yaxis = h2->GetYaxis();
  //since the Pt range of 2D histo is <120
  //for Pt >120, we use SF of Pt = 120
  if(pt<=120){
    Int_t binX = xaxis->FindBin(abs(eta));
    Int_t binY = yaxis->FindBin(pt);
    double sf = h2->GetBinContent(binX, binY);
    double err = h2->GetBinError(binX, binY);
    if(sf!=0) return sf;
    else return 1.0;
  }
  else{
    Int_t binX = xaxis->FindBin(abs(eta));
    Int_t binY = yaxis->FindBin(120);
    double sf = h2->GetBinContent(binX, binY);
    double err = h2->GetBinError(binX, binY);
    if(sf!=0) return sf;
    else return 1.0;
  }	  
}
Double_t hplusAnalyzer::getMuonTrigSF(TH2D *h2, double eta, double pt){
  TAxis *xaxis = h2->GetXaxis();
  TAxis *yaxis = h2->GetYaxis();
  //since the Pt range of 2D histo is <120
  //for Pt >120, we use SF of Pt = 120
  if(pt<=500){
    Int_t binX = xaxis->FindBin(abs(eta));
    Int_t binY = yaxis->FindBin(pt);
    double sf = h2->GetBinContent(binX, binY);
    double err = h2->GetBinError(binX, binY);
    if(sf!=0) return sf;
    else return 1.0;
  }
  else{
    Int_t binX = xaxis->FindBin(abs(eta));
    Int_t binY = yaxis->FindBin(500);
    double sf = h2->GetBinContent(binX, binY);
    double err = h2->GetBinError(binX, binY);
    if(sf!=0) return sf;
    else return 1.0;
  }	  
}

Double_t hplusAnalyzer::getMuonTrackSF(TGraphAsymmErrors *tg, double eta){
  Double_t *eta_array = tg->GetX();
  Double_t *sf_array = tg->GetY();
  Int_t n_points = tg->GetN();

  double SF = 1.0;
  // eta < eta_array[0]
  if(abs(eta)<eta_array[0]) SF = sf_array[0];
  
  // eta_array[0]<eta<eta_array[n_points -1]
  for(Int_t i = 0; i < n_points-1; i++){
    if(abs(eta) >= eta_array[i] && abs(eta) < eta_array[i+1]) SF = sf_array[i+1];
  }
  // eta > eta_array[n_points -]
  if(abs(eta)>eta_array[n_points-1]) SF = sf_array[n_points -1];
  return SF;
}

Double_t hplusAnalyzer::getEleSF(TH2D *h2, double etaSC, double pt){
  TAxis *xaxis = h2->GetXaxis();
  TAxis *yaxis = h2->GetYaxis();
  //since the Pt range of 2D histo is <500
  //for Pt >500, we use SF of Pt = 500
  if(pt<=500){
    Int_t binX = xaxis->FindBin(abs(etaSC));
    Int_t binY = yaxis->FindBin(pt);
    double sf = h2->GetBinContent(binX, binY);
    double err = h2->GetBinError(binX, binY);
    if(sf!=0) return sf;
    else return 1.0;
  }
  else{
    Int_t binX = xaxis->FindBin(abs(etaSC));
    Int_t binY = yaxis->FindBin(500);
    double sf = h2->GetBinContent(binX, binY);
    double err = h2->GetBinError(binX, binY);
    if(sf!=0) return sf;
    else return 1.0;
  }	  
}

Double_t hplusAnalyzer::getEleTrigSF(TH2D *h2, double pt, double etaSC){
  TAxis *xaxis = h2->GetXaxis();
  TAxis *yaxis = h2->GetYaxis();
  //since the Pt range of 2D histo is <120
  //for Pt >120, we use SF of Pt = 120
  if(pt<=200){
    Int_t binX = xaxis->FindBin(pt);
    Int_t binY = yaxis->FindBin(etaSC);
    double sf = h2->GetBinContent(binX, binY);
    double err = h2->GetBinError(binX, binY);
    if(sf!=0) return sf;
    else return 1.0;
  }
  else{
    Int_t binX = xaxis->FindBin(200);
    Int_t binY = yaxis->FindBin(etaSC);
    double sf = h2->GetBinContent(binX, binY);
    double err = h2->GetBinError(binX, binY);
    if(sf!=0) return sf;
    else return 1.0;
  }	  
}

double hplusAnalyzer::phi0to2pi(double phi){
    double pi = 3.1415926535;
    while (phi >= 2.*pi) phi -= 2.*pi;
    while (phi < 0.) phi += 2.*pi;
    return phi;
}

double hplusAnalyzer::deltaPhi12(double phi1_, double phi2_){
    // build the delta Phi angle between the two vectors
    double pi = 3.1415926535;
    double phi1 = phi0to2pi(phi1_);
    double phi2 = phi0to2pi(phi2_);
    double dPhi = phi0to2pi(phi1 - phi2);
    dPhi = (dPhi > (2*pi - dPhi)) ? 2*pi - dPhi : dPhi;
    return dPhi;
}

//---------------------------------------------------//
//muon scale factors from 2D histograms 
//---------------------------------------------------//      
//https://twiki.cern.ch/twiki/bin/view/CMS/MuonWorkInProgressAndPagResults
//https://twiki.cern.ch/twiki/bin/view/CMS/MuonReferenceEffsRun2 
//Trigger SF
TFile *f_trigSF_BCDEF 	= new TFile("stack/muonSF/triggreSF_BCDEF.root");
TFile *f_trigSF_GH 		= new TFile("stack/muonSF/triggreSF_GH.root");
TH2D *h2_trigSF_BCDEF 	= (TH2D*)f_trigSF_BCDEF->Get("IsoMu24_OR_IsoTkMu24_PtEtaBins/abseta_pt_ratio");
TH2D *h2_trigSF_GH 		= (TH2D*)f_trigSF_GH->Get("IsoMu24_OR_IsoTkMu24_PtEtaBins/abseta_pt_ratio");
//Identification SF
TFile *f_idSF_BCDEF 	= new TFile("stack/muonSF/idSF_BCDEF.root");
TFile *f_idSF_GH 		= new TFile("stack/muonSF/idSF_GH.root");
TH2D *h2_idSF_BCDEF 	= (TH2D*)f_idSF_BCDEF->Get("MC_NUM_MediumID2016_DEN_genTracks_PAR_pt_eta/abseta_pt_ratio");
TH2D *h2_idSF_GH 		= (TH2D*)f_idSF_GH->Get("MC_NUM_MediumID2016_DEN_genTracks_PAR_pt_eta/abseta_pt_ratio");
//Isolation SF
TFile *f_isoSF_BCDEF	= new TFile("stack/muonSF/isoSF_BCDEF.root");
TFile *f_isoSF_GH 		= new TFile("stack/muonSF/isoSF_GH.root");
TH2D *h2_isoSF_BCDEF	= (TH2D*)f_isoSF_BCDEF->Get("TightISO_MediumID_pt_eta/abseta_pt_ratio");
TH2D *h2_isoSF_GH 		= (TH2D*)f_isoSF_GH->Get("TightISO_MediumID_pt_eta/abseta_pt_ratio");
//Tracking SF
TFile *f_trackSF_BCDEF 	= new TFile("stack/muonSF/trackingSF_BCDEF.root");
TFile *f_trackSF_GH 	= new TFile("stack/muonSF/trackingSF_GH.root");
TGraphAsymmErrors *tg_trackSF_BCDEF 	= (TGraphAsymmErrors*)f_trackSF_BCDEF->Get("ratio_eff_aeta_dr030e030_corr");
TGraphAsymmErrors *tg_trackSF_GH 	= (TGraphAsymmErrors*)f_trackSF_GH->Get("ratio_eff_aeta_dr030e030_corr");

//---------------------------------------------------//
//Electron scale factors from 2D histograms 
//---------------------------------------------------//      
//https://twiki.cern.ch/twiki/bin/view/CMS/EgammaIDRecipesRun2#Efficiencies_and_scale_factors
//Reconstruction SF
TFile *f_ele_recoSF 	  	= new TFile("stack/eleSF/ele_recoSF.root");
TH2D *h2_ele_recoSF 		= (TH2D*)f_ele_recoSF->Get("EGamma_SF2D");
//Identification SF
TFile *f_ele_veto_idSF      = new TFile("stack/eleSF/ele_veto_idSF.root");
TH2D *h2_ele_veto_idSF      = (TH2D*)f_ele_veto_idSF->Get("EGamma_SF2D");
TFile *f_ele_loose_idSF 	= new TFile("stack/eleSF/ele_loose_idSF.root");
TH2D *h2_ele_loose_idSF 	= (TH2D*)f_ele_loose_idSF->Get("EGamma_SF2D");
TFile *f_ele_medium_idSF 	= new TFile("stack/eleSF/ele_medium_idSF.root");
TH2D *h2_ele_medium_idSF 	= (TH2D*)f_ele_medium_idSF->Get("EGamma_SF2D");
TFile *f_ele_tight_idSF 	= new TFile("stack/eleSF/ele_tight_idSF.root");
TH2D *h2_ele_tight_idSF 	= (TH2D*)f_ele_tight_idSF->Get("EGamma_SF2D");
//Trigger scale factors
//https://indico.cern.ch/event/604912/
TFile *f_ele_trigSF 		= new TFile("stack/eleSF/ele_trigSF_Run2016All_v1.root");
TH2D *h2_ele_trigSF 		= (TH2D*)f_ele_trigSF->Get("Ele27_WPTight_Gsf");

