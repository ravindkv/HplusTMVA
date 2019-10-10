#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <iomanip>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <algorithm> 
#include <fstream>
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include "TH1F.h"
#include "TFile.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TMath.h"
#include <sys/stat.h>


//get error in integral 
double getIntError(TH1F* hist){
  double sError = 0.0;
  double  norm = hist->IntegralAndError(1, hist->GetNbinsX(), sError);
  return sError;
}

//get normalised uncertainity
double getBTagUnc(TH1F *hCentral, TH1F* hUp, TH1F* hDown){
  return 1 + max(fabs(hUp->Integral() - hCentral->Integral()), fabs(hCentral->Integral() - hDown->Integral()))/hCentral->Integral();
}

//get statistical uncertainity
double getStatUnc(TH1F* hCentral, double sError = 0.0){
  double  norm = hCentral->IntegralAndError(1, hCentral->GetNbinsX(), sError);
  double statUnc = (norm > 0) ? 1 + (fabs(sError)/norm) : 1.00; 
  return statUnc;
}

void makeOneDataCard(TString PtRange ="74To99", int mass = 90, TString massLabel="90"){
  TString inFileName = "Shapes_hcs_13TeV_ele_PtbJetInc_mjj_kfit_"+PtRange;
  TFile *inFile = new TFile(inFileName+".root");
  //ttbar
  TH1F* ttbar             = (TH1F*)inFile->Get("ttbar"); 
  TH1F* ttbar_JESUp       = (TH1F*)inFile->Get("ttbar_JESUp"); 
  TH1F* ttbar_JESDown     = (TH1F*)inFile->Get("ttbar_JESDown");
  TH1F* ttbar_PileupUp    = (TH1F*)inFile->Get("ttbar_PileupUp");
  TH1F* ttbar_PileupDown  = (TH1F*)inFile->Get("ttbar_PileupDown");
  TH1F* ttbar_JERUp       = (TH1F*)inFile->Get("ttbar_JERUp");
  TH1F* ttbar_JERDown     = (TH1F*)inFile->Get("ttbar_JERDown");
  TH1F* ttbar_topPtUp     = (TH1F*)inFile->Get("ttbar_topPtUp");
  TH1F* ttbar_topPtDown   = (TH1F*)inFile->Get("ttbar_topPtDown");
  TH1F* ttbar_bTagUp      = (TH1F*)inFile->Get("ttbar_bTagUp");
  TH1F* ttbar_bTagDown    = (TH1F*)inFile->Get("ttbar_bTagDown");
  TH1F* ttbar_cTagUp      = (TH1F*)inFile->Get("ttbar_cTagUp");
  TH1F* ttbar_cTagDown    = (TH1F*)inFile->Get("ttbar_cTagDown");
  TH1F* ttbar_scaleUp      = (TH1F*)inFile->Get("ttbar_scaleRF_ttUp");
  TH1F* ttbar_scaleDown    = (TH1F*)inFile->Get("ttbar_scaleRF_ttDown");
  TH1F* ttbar_mtop1715     = (TH1F*)inFile->Get("ttbar_topMass_ttUp");
  TH1F* ttbar_mtop1735     = (TH1F*)inFile->Get("ttbar_topMass_ttDown");
  TH1F* ttbar_matchingUp   = (TH1F*)inFile->Get("ttbar_hDamp_ttUp");
  TH1F* ttbar_matchingDown = (TH1F*)inFile->Get("ttbar_hDamp_ttDown");

  //w+jets
  TH1F* wjet             = (TH1F*)inFile->Get("wjet"); 
  TH1F* wjet_JESUp       = (TH1F*)inFile->Get("wjet_JESUp"); 
  TH1F* wjet_JESDown     = (TH1F*)inFile->Get("wjet_JESDown");
  TH1F* wjet_PileupUp    = (TH1F*)inFile->Get("wjet_PileupUp");
  TH1F* wjet_PileupDown  = (TH1F*)inFile->Get("wjet_PileupDown");
  TH1F* wjet_JERUp       = (TH1F*)inFile->Get("wjet_JERUp");
  TH1F* wjet_JERDown     = (TH1F*)inFile->Get("wjet_JERDown");
  TH1F* wjet_topPtUp     = (TH1F*)inFile->Get("wjet_topPtUp");
  TH1F* wjet_topPtDown   = (TH1F*)inFile->Get("wjet_topPtDown");
  TH1F* wjet_bTagUp      = (TH1F*)inFile->Get("wjet_bTagUp");
  TH1F* wjet_bTagDown    = (TH1F*)inFile->Get("wjet_bTagDown");
  TH1F* wjet_cTagUp      = (TH1F*)inFile->Get("wjet_cTagUp");
  TH1F* wjet_cTagDown    = (TH1F*)inFile->Get("wjet_cTagDown");

  //Z+Jets
  TH1F* zjet             = (TH1F*)inFile->Get("zjet"); 
  TH1F* zjet_JESUp       = (TH1F*)inFile->Get("zjet_JESUp"); 
  TH1F* zjet_JESDown     = (TH1F*)inFile->Get("zjet_JESDown");
  TH1F* zjet_PileupUp    = (TH1F*)inFile->Get("zjet_PileupUp");
  TH1F* zjet_PileupDown  = (TH1F*)inFile->Get("zjet_PileupDown");
  TH1F* zjet_JERUp       = (TH1F*)inFile->Get("zjet_JERUp");
  TH1F* zjet_JERDown     = (TH1F*)inFile->Get("zjet_JERDown");
  TH1F* zjet_topPtUp     = (TH1F*)inFile->Get("zjet_topPtUp");
  TH1F* zjet_topPtDown   = (TH1F*)inFile->Get("zjet_topPtDown");
  TH1F* zjet_bTagUp      = (TH1F*)inFile->Get("zjet_bTagUp");
  TH1F* zjet_bTagDown    = (TH1F*)inFile->Get("zjet_bTagDown");
  TH1F* zjet_cTagUp      = (TH1F*)inFile->Get("zjet_cTagUp");
  TH1F* zjet_cTagDown    = (TH1F*)inFile->Get("zjet_cTagDown");

  //SingleTop
  TH1F* stop             = (TH1F*)inFile->Get("stop"); 
  TH1F* stop_JESUp       = (TH1F*)inFile->Get("stop_JESUp"); 
  TH1F* stop_JESDown     = (TH1F*)inFile->Get("stop_JESDown");
  TH1F* stop_PileupUp    = (TH1F*)inFile->Get("stop_PileupUp");
  TH1F* stop_PileupDown  = (TH1F*)inFile->Get("stop_PileupDown");
  TH1F* stop_JERUp       = (TH1F*)inFile->Get("stop_JERUp");
  TH1F* stop_JERDown     = (TH1F*)inFile->Get("stop_JERDown");
  TH1F* stop_topPtUp     = (TH1F*)inFile->Get("stop_topPtUp");
  TH1F* stop_topPtDown   = (TH1F*)inFile->Get("stop_topPtDown");
  TH1F* stop_bTagUp      = (TH1F*)inFile->Get("stop_bTagUp");
  TH1F* stop_bTagDown    = (TH1F*)inFile->Get("stop_bTagDown");
  TH1F* stop_cTagUp      = (TH1F*)inFile->Get("stop_cTagUp");
  TH1F* stop_cTagDown    = (TH1F*)inFile->Get("stop_cTagDown");

  //Diboson
  TH1F* diboson             = (TH1F*)inFile->Get("diboson"); 
  TH1F* diboson_JESUp       = (TH1F*)inFile->Get("diboson_JESUp"); 
  TH1F* diboson_JESDown     = (TH1F*)inFile->Get("diboson_JESDown");
  TH1F* diboson_PileupUp    = (TH1F*)inFile->Get("diboson_PileupUp");
  TH1F* diboson_PileupDown  = (TH1F*)inFile->Get("diboson_PileupDown");
  TH1F* diboson_JERUp       = (TH1F*)inFile->Get("diboson_JERUp");
  TH1F* diboson_JERDown     = (TH1F*)inFile->Get("diboson_JERDown");
  TH1F* diboson_topPtUp     = (TH1F*)inFile->Get("diboson_topPtUp");
  TH1F* diboson_topPtDown   = (TH1F*)inFile->Get("diboson_topPtDown");
  TH1F* diboson_bTagUp      = (TH1F*)inFile->Get("diboson_bTagUp");
  TH1F* diboson_bTagDown    = (TH1F*)inFile->Get("diboson_bTagDown");
  TH1F* diboson_cTagUp      = (TH1F*)inFile->Get("diboson_cTagUp");
  TH1F* diboson_cTagDown    = (TH1F*)inFile->Get("diboson_cTagDown");

  //QCD
  TH1F* qcd_dd             = (TH1F*)inFile->Get("qcd"); 

  //Data
  TH1F* data_obs             = (TH1F*)inFile->Get("data_obs"); 

  //Signal, mH = 90 GeV
  TH1F* wh             = (TH1F*)inFile->Get("WH"+massLabel+""); 
  TH1F* wh_JESUp       = (TH1F*)inFile->Get("WH"+massLabel+"_JESUp"); 
  TH1F* wh_JESDown     = (TH1F*)inFile->Get("WH"+massLabel+"_JESDown");
  TH1F* wh_PileupUp    = (TH1F*)inFile->Get("WH"+massLabel+"_PileupUp");
  TH1F* wh_PileupDown  = (TH1F*)inFile->Get("WH"+massLabel+"_PileupDown");
  TH1F* wh_JERUp       = (TH1F*)inFile->Get("WH"+massLabel+"_JERUp");
  TH1F* wh_JERDown     = (TH1F*)inFile->Get("WH"+massLabel+"_JERDown");
  TH1F* wh_topPtUp     = (TH1F*)inFile->Get("WH"+massLabel+"_topPtUp");
  TH1F* wh_topPtDown   = (TH1F*)inFile->Get("WH"+massLabel+"_topPtDown");
  TH1F* wh_bTagUp      = (TH1F*)inFile->Get("WH"+massLabel+"_bTagUp");
  TH1F* wh_bTagDown    = (TH1F*)inFile->Get("WH"+massLabel+"_bTagDown");
  TH1F* wh_cTagUp      = (TH1F*)inFile->Get("WH"+massLabel+"_cTagUp");
  TH1F* wh_cTagDown    = (TH1F*)inFile->Get("WH"+massLabel+"_cTagDown");

  //open input template data card of 8 TeV
  ifstream in;
  char* c = new char[1000];
  in.open("template_datacard_hcs_13TeV.log");
  string outDataCard = string("datacard_hcs_13TeV_ele_"+PtRange+"_mH"+massLabel+".txt");
  ofstream out(Form(outDataCard.c_str(), mass));
  out.precision(8);

  time_t secs=time(0);
  tm *t=localtime(&secs);
  while (in.good()){
    in.getline(c,1000,'\n');
    if (in.good()){
      string line(c);
      if(line.find("Date")!=string::npos){
        string day = string(Form("%d",t->tm_mday));
        string month = string(Form("%d",t->tm_mon+1));
        string year = string(Form("%d",t->tm_year+1900));
        line.replace( line.find("XXX") , 3 , day+"/"+month+"/"+year);
        out << line << endl;
      }
      else if(line.find("Description")!=string::npos){
        line.replace( line.find("YYY") , 3 , string(Form("%d", mass)) );
        line.replace( line.find("ZZZ") , 3 , string(Form("%f", 35.9)) ); 
        line.replace( line.find("CCC") , 3 , string(Form("%s", "ele")) );
        out << line << endl;
      }
      else if(line.find("shapes")!=string::npos){
        line.replace( line.find("XXX") , 3 , string(inFileName));
        out << line << endl;
      }
      else if(line.find("Observation")!=string::npos){
        line.replace( line.find("XXX") , 3 , string(Form("%.0f", data_obs->Integral())));
        out << line << endl;
      }
      else if(line.find("process")!=string::npos && line.find("WH")!=string::npos){
        line.replace( line.find("YYY") , 3 , string(Form("%d", mass)) );
        out << line << endl;
      }
      else if(line.find("rate")!=string::npos){
        string rate = "rate               ";  
        string space = "     ";
        out << rate ;
        out << space << wh->Integral()
            << space << ttbar->Integral()
            << space << wjet->Integral()
            << space << zjet->Integral()
            << space << stop->Integral()
            << space << diboson->Integral()
            << space << qcd_dd->Integral()
            << endl;
      }
      else if(line.find("CMS_eff_lep")!=string::npos){  
        line.replace( line.find("lep") , 4 , string(Form("%s", "e")));
        out << line << endl;
      }  
      else if(line.find("CMS_eff_b")!=string::npos){
        float bTagUnc_wh = (wh->Integral() > 0) ? getBTagUnc(wh, wh_bTagUp, wh_bTagDown) : 1.00;
        line.replace( line.find("HHHH") , 4 , string(Form("%.3f", bTagUnc_wh)) );
        
        float bTagUnc_ttbar = (ttbar->Integral() > 0) ? getBTagUnc(ttbar, ttbar_bTagUp, ttbar_bTagDown) : 1.00; 
        line.replace( line.find("TTTT") , 4 , string(Form("%.3f", bTagUnc_ttbar)) ); 
        
        float bTagUnc_wjet = (wjet->Integral() > 0) ? getBTagUnc(wjet, wjet_bTagUp, wjet_bTagDown) : 1.00;
        line.replace( line.find("WWWW") , 4 , string(Form("%.3f", bTagUnc_wjet)) ); 
       
        float bTagUnc_zjet = (zjet->Integral() > 0) ? getBTagUnc(zjet, zjet_bTagUp, zjet_bTagDown) : 1.00;
        line.replace( line.find("DDDD") , 4 , string(Form("%.3f", bTagUnc_zjet)) ); 

        float bTagUnc_stop = (stop->Integral() > 0) ? getBTagUnc(stop, stop_bTagUp, stop_bTagDown) : 1.00; 
        line.replace( line.find("SSSS") , 4 , string(Form("%.3f", bTagUnc_stop)) ); 

        float bTagUnc_diboson = (diboson->Integral() > 0) ? getBTagUnc(diboson, diboson_bTagUp, diboson_bTagDown) : 1.00;
        line.replace( line.find("VVVV") , 4 , string(Form("%.3f", bTagUnc_diboson)) ); 
        out << line << endl;
      }
      else if(line.find("CMS_eff_c")!=string::npos){
        float cTagUnc_wh = (wh->Integral() > 0) ? getBTagUnc(wh, wh_cTagUp, wh_cTagDown) : 1.00;
        line.replace( line.find("HHHH") , 4 , string(Form("%.3f", cTagUnc_wh)) );
        
        float cTagUnc_ttbar = (ttbar->Integral() > 0) ? getBTagUnc(ttbar, ttbar_cTagUp, ttbar_cTagDown) : 1.00; 
        line.replace( line.find("TTTT") , 4 , string(Form("%.3f", cTagUnc_ttbar)) ); 
        
        float cTagUnc_wjet = (wjet->Integral() > 0) ? getBTagUnc(wjet, wjet_cTagUp, wjet_cTagDown) : 1.00;
        line.replace( line.find("WWWW") , 4 , string(Form("%.3f", cTagUnc_wjet)) ); 
       
        float cTagUnc_zjet = (zjet->Integral() > 0) ? getBTagUnc(zjet, zjet_cTagUp, zjet_cTagDown) : 1.00;
        line.replace( line.find("DDDD") , 4 , string(Form("%.3f", cTagUnc_zjet)) ); 
        
        float cTagUnc_stop = (stop->Integral() > 0) ? getBTagUnc(stop, stop_cTagUp, stop_cTagDown) : 1.00; 
        line.replace( line.find("SSSS") , 4 , string(Form("%.3f", cTagUnc_stop)) ); 

        float cTagUnc_diboson = (diboson->Integral() > 0) ? getBTagUnc(diboson, diboson_cTagUp, diboson_cTagDown) : 1.00;
        line.replace( line.find("VVVV") , 4 , string(Form("%.3f", cTagUnc_diboson)) ); 
        out << line << endl;
      }
      else if(line.find("CMS_pileup")!=string::npos){
        float PileupUnc_wh = (wh->Integral() > 0) ? getBTagUnc(wh, wh_PileupUp, wh_PileupDown) : 1.00;
        line.replace( line.find("HHHH") , 4 , string(Form("%.3f", PileupUnc_wh)) );
        
        float PileupUnc_ttbar = (ttbar->Integral() > 0) ? getBTagUnc(ttbar, ttbar_PileupUp, ttbar_PileupDown) : 1.00; 
        line.replace( line.find("TTTT") , 4 , string(Form("%.3f", PileupUnc_ttbar)) ); 
        
        float PileupUnc_wjet = (wjet->Integral() > 0) ? getBTagUnc(wjet, wjet_PileupUp, wjet_PileupDown) : 1.00;
        line.replace( line.find("WWWW") , 4 , string(Form("%.3f", PileupUnc_wjet)) ); 
       
        float PileupUnc_zjet = (zjet->Integral() > 0) ? getBTagUnc(zjet, zjet_PileupUp, zjet_PileupDown) : 1.00;
        line.replace( line.find("DDDD") , 4 , string(Form("%.3f", PileupUnc_zjet)) ); 
        
        float PileupUnc_stop = (stop->Integral() > 0) ? getBTagUnc(stop, stop_PileupUp, stop_PileupDown) : 1.00; 
        line.replace( line.find("SSSS") , 4 , string(Form("%.3f", PileupUnc_stop)) ); 

        float PileupUnc_diboson = (diboson->Integral() > 0) ? getBTagUnc(diboson, diboson_PileupUp, diboson_PileupDown) : 1.00;
        line.replace( line.find("VVVV") , 4 , string(Form("%.3f", PileupUnc_diboson)) ); 
        out << line << endl;
      }
      else if(line.find("CMS_scale_j")!=string::npos){
        float JESUnc_wh = (wh->Integral() > 0) ? getBTagUnc(wh, wh_JESUp, wh_JESDown) : 1.00;
        line.replace( line.find("HHHH") , 4 , string(Form("%.3f", JESUnc_wh)) );
        
        float JESUnc_ttbar = (ttbar->Integral() > 0) ? getBTagUnc(ttbar, ttbar_JESUp, ttbar_JESDown) : 1.00; 
        line.replace( line.find("TTTT") , 4 , string(Form("%.3f", JESUnc_ttbar)) ); 
        
        float JESUnc_wjet = (wjet->Integral() > 0) ? getBTagUnc(wjet, wjet_JESUp, wjet_JESDown) : 1.00;
        line.replace( line.find("WWWW") , 4 , string(Form("%.3f", JESUnc_wjet)) ); 
       
        float JESUnc_zjet = (zjet->Integral() > 0) ? getBTagUnc(zjet, zjet_JESUp, zjet_JESDown) : 1.00;
        line.replace( line.find("DDDD") , 4 , string(Form("%.3f", JESUnc_zjet)) ); 
        
        float JESUnc_stop = (stop->Integral() > 0) ? getBTagUnc(stop, stop_JESUp, stop_JESDown) : 1.00; 
        line.replace( line.find("SSSS") , 4 , string(Form("%.3f", JESUnc_stop)) ); 

        float JESUnc_diboson = (diboson->Integral() > 0) ? getBTagUnc(diboson, diboson_JESUp, diboson_JESDown) : 1.00;
        line.replace( line.find("VVVV") , 4 , string(Form("%.3f", JESUnc_diboson)) ); 
        out << line << endl;
      }
      else if(line.find("CMS_res_j")!=string::npos){
        float JERUnc_wh = (wh->Integral() > 0) ? getBTagUnc(wh, wh_JERUp, wh_JERDown) : 1.00;
        line.replace( line.find("HHHH") , 4 , string(Form("%.3f", JERUnc_wh)) );
        
        float JERUnc_ttbar = (ttbar->Integral() > 0) ? getBTagUnc(ttbar, ttbar_JERUp, ttbar_JERDown) : 1.00; 
        line.replace( line.find("TTTT") , 4 , string(Form("%.3f", JERUnc_ttbar)) ); 
        
        float JERUnc_wjet = (wjet->Integral() > 0) ? getBTagUnc(wjet, wjet_JERUp, wjet_JERDown) : 1.00;
        line.replace( line.find("WWWW") , 4 , string(Form("%.3f", JERUnc_wjet)) ); 
       
        float JERUnc_zjet = (zjet->Integral() > 0) ? getBTagUnc(zjet, zjet_JERUp, zjet_JERDown) : 1.00;
        line.replace( line.find("DDDD") , 4 , string(Form("%.3f", JERUnc_zjet)) ); 
        
        float JERUnc_stop = (stop->Integral() > 0) ? getBTagUnc(stop, stop_JERUp, stop_JERDown) : 1.00; 
        line.replace( line.find("SSSS") , 4 , string(Form("%.3f", JERUnc_stop)) ); 

        float JERUnc_diboson = (diboson->Integral() > 0) ? getBTagUnc(diboson, diboson_JERUp, diboson_JERDown) : 1.00;
        line.replace( line.find("VVVV") , 4 , string(Form("%.3f", JERUnc_diboson)) ); 
        out << line << endl;
      }
      else if(line.find("CMS_hcs_stat_wh")!=string::npos){ 
        line.replace( line.find("XXXX") , 4 , string(Form("%.3f", getStatUnc(wh,  0))));  
        out << line << endl;
      } 
      else if(line.find("CMS_hcs_stat_tt")!=string::npos){  
    line.replace( line.find("XXXX") , 4 , string(Form("%.3f", getStatUnc(ttbar,  0))));   
        out << line << endl;
      }  
      else if(line.find("CMS_hcs_stat_wjet")!=string::npos){  
        line.replace( line.find("XXXX") , 4 , string(Form("%.3f", getStatUnc(wjet,  0))));   
        out << line << endl;
      }  
      else if(line.find("CMS_hcs_stat_zjet")!=string::npos){ 
        line.replace( line.find("XXXX") , 4 , string(Form("%.3f", getStatUnc(zjet,  0))));  
        out << line << endl; 
      }
      else if(line.find("CMS_hcs_stat_stop")!=string::npos){ 
        line.replace( line.find("XXXX") , 4 , string(Form("%.3f", getStatUnc(stop,  0))));  
        out << line << endl; 
      } 
      else if(line.find("CMS_hcs_stat_vv")!=string::npos){  
        line.replace( line.find("XXXX") , 4 , string(Form("%.3f", getStatUnc(diboson,  0))));   
        out << line << endl;  
      }
      else if(line.find("CMS_hcs_stat_qcd")!=string::npos){  
        line.replace( line.find("XXXX") , 4 , string(Form("%.3f", getStatUnc(qcd_dd,  0))));   
        out << line << endl;  
      }
      else if(line.find("CMS_norm_qcd")!=string::npos){  
        line.replace( line.find("QQQQ") , 4 , string(Form("%.3f", 1.40)));   
        out << line << endl;  
      }
      else if(line.find("CMS_topPtReweight")!=string::npos){
        float topPtUnc_wh = (wh->Integral() > 0) ? getBTagUnc(wh, wh_topPtUp, wh_topPtDown) : 1.00;
        line.replace( line.find("HHHH") , 4 , string(Form("%.3f", topPtUnc_wh)) );
        
        float topPtUnc_ttbar = (ttbar->Integral() > 0) ? getBTagUnc(ttbar, ttbar_topPtUp, ttbar_topPtDown) : 1.00; 
        line.replace( line.find("TTTT") , 4 , string(Form("%.3f", topPtUnc_ttbar)) ); 
        out << line << endl;
      }
      else{ //default without changes
        out << line << endl;
      }
    }
  } 
  out.close();
  in.close();
}

void makeRecycledDataCard_13TeV(){
  int mass = 90;
  TString label = "90";
  //makeOneDataCard("25To42", mass, label);
  //makeOneDataCard("42To57", mass, label);
  //makeOneDataCard("57To74", mass, label);
  makeOneDataCard("74To99", mass, label);
  //makeOneDataCard("99To500", mass, label);
}
