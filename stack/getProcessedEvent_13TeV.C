//#include "TROOT.h"    
#include "TObject.h"
#include "TFile.h"
#include "TTree.h"
#include "TROOT.h"
#include <cmath>
#include <math.h>
#include<string>
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <math.h>
#include <fstream>
#include <map>
#include <iomanip>
#include <iostream>

void getProcessedEvent_13TeV(){
  
  bool isMC = true;
  bool isMuData = true;
  bool isMuMC = false;
  bool isEleData = false;
  bool isEleMC = false;
  bool isHiggsBkg = true;

  std::map<std::string, double> mcEvtDBS;
  mcEvtDBS["DY1JetsToLL_Merged.root"]       =  62079400;
  mcEvtDBS["DY2JetsToLL_Merged.root"]       =  19970551;
  mcEvtDBS["DY3JetsToLL_Merged.root"]       =  5856110;
  mcEvtDBS["DY4JetsToLL_Merged.root"]       =  4197868;
  mcEvtDBS["DYJetsToLL_Merged.root"]        =  48103700;
  mcEvtDBS["HplusM100_Merged.root"]         =  996170; 
  mcEvtDBS["HplusM120_Merged.root"]         =  994498; 
  mcEvtDBS["HplusM140_Merged.root"]         =  987730; 
  mcEvtDBS["HplusM150_Merged.root"]         =  990645;
  mcEvtDBS["HplusM155_Merged.root"]         =  952984;
  mcEvtDBS["HplusM160_Merged.root"]         =  992264;
  mcEvtDBS["HplusM80_Merged.root"]          =  976710;
  mcEvtDBS["HplusM90_Merged.root"]          =  988480;
  if(isMuMC){
    mcEvtDBS["QCD_Pt-15to20_Mu_Merged.root"]  =  4141251;
    mcEvtDBS["QCD_Pt-20to30_Mu_Merged.root"]  =  31475157;
    mcEvtDBS["QCD_Pt-30to50_Mu_Merged.root"]  =  29954815;
    mcEvtDBS["QCD_Pt-50to80_Mu_Merged.root"]  =  19806915;
    mcEvtDBS["QCD_Pt-80to120_Mu_Merged.root"] =  13786971;
    mcEvtDBS["QCD_Pt-120to170_Mu_Merged.root"]=  8042721;
    mcEvtDBS["QCD_Pt-170to300_Mu_Merged.root"]=  7947159;
    mcEvtDBS["QCD_Pt-300to470_Mu_Merged.root"]=  7937590;
  }
  if(isEleMC){
    mcEvtDBS["QCD_Pt-15to20_EM_Merged.root"]  =  5652601;
    mcEvtDBS["QCD_Pt-20to30_EM_Merged.root"]  =  9218954;
    mcEvtDBS["QCD_Pt-30to50_EM_Merged.root"]  =  4730195;
    mcEvtDBS["QCD_Pt-50to80_EM_Merged.root"]  =  22337070;
    mcEvtDBS["QCD_Pt-80to120_EM_Merged.root"] =  35841783;
    mcEvtDBS["QCD_Pt-120to170_EM_Merged.root"]=  35817281;
    mcEvtDBS["QCD_Pt-170to300_EM_Merged.root"]=  11540163;
    mcEvtDBS["QCD_Pt-300toInf_EM_Merged.root"]=  7373633;
  }
  mcEvtDBS["ST_s_Merged.root"]              =  2989199;
  mcEvtDBS["ST_t_Merged.root"]              =  38811017;
  mcEvtDBS["ST_tW_Merged.root"]             =  6933094;
  mcEvtDBS["TTJetsM_Merged.root"]           =  10139950;   
  mcEvtDBS["TTJetsP_Merged.root"]           =  77081156;   
  mcEvtDBS["TTJetsP_up_Merged.root"]        =  29310620;   
  mcEvtDBS["TTJetsP_down_Merged.root"]      =  28354188;   
  mcEvtDBS["TTJetsP_mtop1735_Merged.root"]  =  19419050;   
  mcEvtDBS["TTJetsP_mtop1715_Merged.root"]  =  19578812;   
  mcEvtDBS["TTJetsP_hdampUP_Merged.root"]   =  29689380;   
  mcEvtDBS["TTJetsP_hdampDOWN_Merged.root"] =  29117820;   
  mcEvtDBS["W1JetsToLNu_Merged.root"]       =  44813600;
  mcEvtDBS["W2JetsToLNu_Merged.root"]       =  29878415;
  mcEvtDBS["W3JetsToLNu_Merged.root"]       =  19798117;
  mcEvtDBS["W4JetsToLNu_Merged.root"]       =  9170576;
  mcEvtDBS["WJetsToLNu_Merged.root"]        =  29181900;
  mcEvtDBS["WW_Merged.root"]                =  994012;
  mcEvtDBS["WZ_Merged.root"]                =  1000000;
  mcEvtDBS["ZZ_Merged.root"]                =  990064; 

  //Bkg from SM Higgs prodcution
  if(isHiggsBkg){
    mcEvtDBS["GluGluHToCC_Merged.root"]          = 9782840 ;
    mcEvtDBS["VBFHToCC_Merged.root"]             = 4980094 ;
    mcEvtDBS["WminusH_HToCC_WToLNu_Merged.root"] = 1477656 ;
    mcEvtDBS["WminusH_HToCC_WToQQ_Merged.root"]  = 457517  ;
    mcEvtDBS["WplusH_HToCC_WToLNu_Merged.root"]  = 1482024 ;
    mcEvtDBS["WplusH_HToCC_WToQQ_Merged.root"]   = 459565  ;
    mcEvtDBS["ZH_HToCC_ZToLL_Merged.root"]       = 4885552 ;
    mcEvtDBS["ZH_HToCC_ZToNuNu_Merged.root"]     = 1183744 ;
    mcEvtDBS["ZH_HToCC_ZToQQ_Merged.root"]       = 499384  ;
    mcEvtDBS["ttHToCC_Merged.root"]              = 4784344 ;
  }

  std::map<std::string, double>::iterator itr_mc;
  if(isMC){ 
    cout<<"=============================="<<endl;
    cout<<"        ALL MC SAMPLES        "<<endl;
    cout<<"=============================="<<endl;
    for(itr_mc = mcEvtDBS.begin(); itr_mc != mcEvtDBS.end(); ++itr_mc){
      TString inFile(itr_mc->first);
      TFile* ttbar= new TFile(inFile);
      TString path= "base/totalEvents";
      TH1F* hist= (TH1F*)(ttbar->Get(path));
      int entries= hist->GetBinContent(1);
      double mean= hist->GetMean();
      double event_cond = entries*mean;//events from condor submission
      double event_dbs = itr_mc->second;//events at data base server
      double ratio = event_dbs/event_cond;
      cout<<setw(30)<<inFile<<setw(15)<<event_dbs<<setw(15)<<event_cond<<setw(15)<<ratio<<endl;
    }
  }
       
  std::map<std::string, double> muDataEvtDBS;
  muDataEvtDBS["MuRunB2v2_Merged.root"] =146581188 +6071342 ;  
  muDataEvtDBS["MuRunCv1_Merged.root"]  =63756442  +886880  ;
  muDataEvtDBS["MuRunDv1_Merged.root"]  =95674398  +932597  ;
  muDataEvtDBS["MuRunEv1_Merged.root"]  =86236261  +1061687 ;
  muDataEvtDBS["MuRunFv1_Merged.root"]  =65047318           ;
  muDataEvtDBS["MuRunGv1_Merged.root"]  =145883039  +1940146;
  muDataEvtDBS["MuRunH2v1_Merged.root"] =159964460  +6410252; 
  muDataEvtDBS["MuRunH3v1_Merged.root"] =4389914  ;
  
  std::map<std::string, double>::iterator itr_mudata;
  if(isMuData){ 
    cout<<"=============================="<<endl;
    cout<<"     ALL Muon Data SAMPLES    "<<endl;
    cout<<"=============================="<<endl;
    for(itr_mudata = muDataEvtDBS.begin(); itr_mudata != muDataEvtDBS.end(); ++itr_mudata){
      TString inFile(itr_mudata->first);
      TFile* ttbar= new TFile(inFile);
      TString path= "base/totalEvents";
      TH1F* hist= (TH1F*)(ttbar->Get(path));
      int entries= hist->GetBinContent(1);
      double mean= hist->GetMean();
      double event_cond = entries*mean;//events from condor submission
      double event_dbs = itr_mudata->second;//events at data base server
      double ratio = event_dbs/event_cond;
      cout<<setw(30)<<inFile<<setw(15)<<event_dbs<<setw(15)<<event_cond<<setw(15)<<ratio<<endl;
    }
  }
    
  std::map<std::string, double> eleDataEvtDBS;
  eleDataEvtDBS["EleRunBver2v2_Merged.root"]  =235362706 +2466515 ;  
  eleDataEvtDBS["EleRunCv1_Merged.root"    ]  =91537460  +1789192 ;
  eleDataEvtDBS["EleRunDv1_Merged.root"    ]  =141901645 +4316488 ;
  eleDataEvtDBS["EleRunEv1_Merged.root"    ]  =111732063 +1437789 ;
  eleDataEvtDBS["EleRunFv1_Merged.root"    ]  =68855145  +1288176 ;
  eleDataEvtDBS["EleRunGv1_Merged.root"    ]  =151022050 +1076567 ;
  eleDataEvtDBS["EleRunHver2v1_Merged.root"]  =121561193 +2338994 ; 
  eleDataEvtDBS["EleRunHver3v1_Merged.root"]  =3189661  ;

  std::map<std::string, double>::iterator itr_eledata;
  if(isEleData){ 
    cout<<"=============================="<<endl;
    cout<<" ALL Electron Data SAMPLES    "<<endl;
    cout<<"=============================="<<endl;
    for(itr_eledata = eleDataEvtDBS.begin(); itr_eledata != eleDataEvtDBS.end(); ++itr_eledata){
      TString inFile(itr_eledata->first);
      TFile* ttbar= new TFile(inFile);
      TString path= "base/totalEvents";
      TH1F* hist= (TH1F*)(ttbar->Get(path));
      int entries= hist->GetBinContent(1);
      double mean= hist->GetMean();
      double event_cond = entries*mean;//events from condor submission
      double event_dbs = itr_eledata->second;//events at data base server
      double ratio = event_dbs/event_cond;
      cout<<setw(30)<<inFile<<setw(15)<<event_dbs<<setw(15)<<event_cond<<setw(15)<<ratio<<endl;
    }
  }
}

