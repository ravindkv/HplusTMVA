#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <fstream>
#include <iomanip>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <algorithm> 

/////////////////////////// USERS INPUT ///////////////////////////
///INPUT FILES
//data
double totLumi = 35.45;
TFile* fData    = TFile::Open("all_muData.root");

//bkg
TFile* fVV      = TFile::Open("all_VV.root");
TFile* fDY      = TFile::Open("all_DY.root");
TFile* fWJ      = TFile::Open("all_WJets.root");
TFile* fQCD     = TFile::Open("all_QCD.root");
TFile* fST      = TFile::Open("all_ST.root");
TFile* fTT      = TFile::Open("all_TTJetsP.root");
//signal
TFile *fWH80      = TFile::Open("all_Hplus80.root");
TFile *fWH90      = TFile::Open("all_Hplus90.root");
TFile *fWH100     = TFile::Open("all_Hplus100.root");
TFile *fWH120     = TFile::Open("all_Hplus120.root");
TFile *fWH140     = TFile::Open("all_Hplus140.root");
TFile *fWH150     = TFile::Open("all_Hplus150.root");
TFile *fWH155     = TFile::Open("all_Hplus155.root");
TFile *fWH160     = TFile::Open("all_Hplus160.root");
//data driven qcd
TFile* fQCD_dd = TFile::Open("all_QCD_dd.root"); 

//MAKE DATA CARD of mjj
TString histname="mjj_kfit";

//OUTPUT FILE
TFile *fout = new TFile("HplusShapes_mu_13TeV.root", "RECREATE");
//////////////////////////////////////////////////////////////////

//----------------------------------------//
//Variuos functions
//----------------------------------------//
//Read histos from input file. Return empty hist if the hist does not exist. Write to another file.
TH1F* readWriteHisto(TFile *inFile, TString histPath, TString inHistName, double sf, TFile *outFile, TString outHistName, bool isWrite = false){
  TH1F* hist;
  if(!(inFile->Get(histPath+inHistName))){
    hist = (TH1F*)(fTT->Get(histPath+inHistName))->Clone(outHistName);
    hist->Add(hist, -1);
  }else hist = (TH1F*)(inFile->Get(histPath+inHistName))->Clone(outHistName);
  hist->Scale(sf);
  hist->GetXaxis()->SetRangeUser(0, 200);
  if(isWrite){
    fout->cd();
    hist->Write(outHistName);
  }
  return hist;
}  

//get normalised uncertainity
double getNormUnc(TH1F *hCentral, TH1F* hUp, TH1F* hDown){
  return 1 + max(fabs(hUp->Integral() - hCentral->Integral()), fabs(hCentral->Integral() - hDown->Integral()))/hCentral->Integral();
}

//get statistical uncertainity
double getStatUnc(TH1F* hCentral, double sError = 0.0){
  double  norm = hCentral->IntegralAndError(1, hCentral->GetNbinsX(), sError);
  double statUnc = (norm > 0) ? 1 + (fabs(sError)/norm) : 1.00; 
  return statUnc;
}

//----------------------------------------//
//Global variables
//----------------------------------------//
//ttbar
double sf_ttbar_lumi = 1; 
TH1F* ttbar_topPtweight = readWriteHisto(fTT, "base/", "SF_topPtWeights", 1, fout, "topPtWeights", false);
double sf_ttbar = sf_ttbar_lumi/ttbar_topPtweight->GetMean();
TH1F* ttbar = readWriteHisto(fTT, "base/Iso/KinFit/", histname, sf_ttbar, fout, "ttbar", true);
TH1F* ttbar_JESUp = readWriteHisto(fTT, "JESPlus/Iso/KinFit/", histname, sf_ttbar, fout, "ttbar_JESUp", true);
TH1F* ttbar_JERUp = readWriteHisto(fTT, "JERPlus/Iso/KinFit/", histname, sf_ttbar, fout, "ttbar_JERUp", true);
TH1F* ttbar_JESDown = readWriteHisto(fTT, "JESMinus/Iso/KinFit/", histname, sf_ttbar, fout, "ttbar_JESDown", true);
TH1F* ttbar_JERDown = readWriteHisto(fTT, "JERMinus/Iso/KinFit/", histname, sf_ttbar, fout, "ttbar_JERDown", true);
TH1F* ttbar_topPtUp = readWriteHisto(fTT, "TopPtPlus/Iso/KinFit/", histname, sf_ttbar, fout, "ttbar_topPtUp", true);
TH1F* ttbar_topPtDown = readWriteHisto(fTT, "TopPtMinus/Iso/KinFit/", histname, sf_ttbar, fout, "ttbar_topPtDown", true);
TH1F* ttbar_bTagUp = readWriteHisto(fTT, "bTagPlus/Iso/KinFit/", histname, sf_ttbar, fout, "ttbar_bTagUp", true);
TH1F* ttbar_bTagDown = readWriteHisto(fTT, "bTagMinus/Iso/KinFit/", histname, sf_ttbar, fout, "ttbar_bTagDown", true);

//ttll
double sf_ttll = 0;
TH1F* ttll = readWriteHisto(fTT, "base/Iso/KinFit/", histname, sf_ttll, fout, "ttll", true);
TH1F* ttll_JESUp = readWriteHisto(fTT, "JESPlus/Iso/KinFit/", histname, sf_ttll, fout, "ttll_JESUp", true);
TH1F* ttll_JESDown = readWriteHisto(fTT, "JESMinus/Iso/KinFit/", histname, sf_ttll, fout, "ttll_JESDown", true);

//w+jets
double sf_wjet = 1;
TH1F* wjet = readWriteHisto(fWJ, "base/Iso/KinFit/", histname, sf_wjet, fout, "wjet", true);
TH1F* wjet_JESUp = readWriteHisto(fWJ, "JESPlus/Iso/KinFit/", histname, sf_wjet, fout, "wjet_JESUp", true);
TH1F* wjet_JERUp = readWriteHisto(fWJ, "JERPlus/Iso/KinFit/", histname, sf_wjet, fout, "wjet_JERUp", true);
TH1F* wjet_JESDown = readWriteHisto(fWJ, "JESMinus/Iso/KinFit/", histname, sf_wjet, fout, "wjet_JESDown", true);
TH1F* wjet_JERDown = readWriteHisto(fWJ, "JERMinus/Iso/KinFit/", histname, sf_wjet, fout, "wjet_JERDown", true);
TH1F* wjet_bTagUp = readWriteHisto(fWJ, "bTagPlus/Iso/KinFit/", histname, sf_wjet, fout, "wjet_bTagUp", true);
TH1F* wjet_bTagDown = readWriteHisto(fWJ, "bTagMinus/Iso/KinFit/", histname, sf_wjet, fout, "wjet_bTagDown", true); 

//Z+Jets
double sf_zjet = 1;
TH1F* zjet = readWriteHisto(fDY, "base/Iso/KinFit/", histname, sf_zjet, fout, "zjet", true);
TH1F* zjet_JESUp = readWriteHisto(fDY, "JESPlus/Iso/KinFit/", histname, sf_zjet, fout, "zjet_JESUp", true);
TH1F* zjet_JERUp = readWriteHisto(fDY, "JERPlus/Iso/KinFit/", histname, sf_zjet, fout, "zjet_JERUp", true);
TH1F* zjet_JESDown = readWriteHisto(fDY, "JESMinus/Iso/KinFit/", histname, sf_zjet, fout, "zjet_JESDown", true);
TH1F* zjet_JERDown = readWriteHisto(fDY, "JERMinus/Iso/KinFit/", histname, sf_zjet, fout, "zjet_JERDown", true);
TH1F* zjet_bTagUp = readWriteHisto(fDY, "bTagPlus/Iso/KinFit/", histname, sf_zjet, fout, "zjet_bTagUp", true);
TH1F* zjet_bTagDown = readWriteHisto(fDY, "bTagMinus/Iso/KinFit/", histname, sf_zjet, fout, "zjet_bTagDown", true);

//SingleTop
double sf_stop = 1;
TH1F* stop = readWriteHisto(fST, "base/Iso/KinFit/", histname, sf_stop, fout, "stop", true);
TH1F* stop_JESUp = readWriteHisto(fST, "JESPlus/Iso/KinFit/", histname, sf_stop, fout, "stop_JESUp", true);
TH1F* stop_JERUp = readWriteHisto(fST, "JERPlus/Iso/KinFit/", histname, sf_stop, fout, "stop_JERUp", true);
TH1F* stop_JESDown = readWriteHisto(fST, "JESMinus/Iso/KinFit/", histname, sf_stop, fout, "stop_JESDown", true);
TH1F* stop_JERDown = readWriteHisto(fST, "JERMinus/Iso/KinFit/", histname, sf_stop, fout, "stop_JERDown", true);
TH1F* stop_bTagUp = readWriteHisto(fST, "bTagPlus/Iso/KinFit/", histname, sf_stop, fout, "stop_bTagUp", true);
TH1F* stop_bTagDown = readWriteHisto(fST, "bTagMinus/Iso/KinFit/", histname, sf_stop, fout, "stop_bTagDown", true);

//Dibosons
double sf_diboson = 1;
TH1F* diboson = readWriteHisto(fVV, "base/Iso/KinFit/", histname, sf_diboson, fout, "diboson", true);
TH1F* diboson_JESUp = readWriteHisto(fVV, "JESPlus/Iso/KinFit/", histname, sf_diboson, fout, "diboson_JESUp", true);
TH1F* diboson_JERUp = readWriteHisto(fVV, "JERPlus/Iso/KinFit/", histname, sf_diboson, fout, "diboson_JERUp", true);
TH1F* diboson_JESDown = readWriteHisto(fVV, "JESMinus/Iso/KinFit/", histname, sf_diboson, fout, "diboson_JESDown", true);
TH1F* diboson_JERDown = readWriteHisto(fVV, "JERMinus/Iso/KinFit/", histname, sf_diboson, fout, "diboson_JERDown", true);
TH1F* diboson_bTagUp = readWriteHisto(fVV, "bTagPlus/Iso/KinFit/", histname, sf_diboson, fout, "diboson_bTagUp", true);
TH1F* diboson_bTagDown = readWriteHisto(fVV, "bTagMinus/Iso/KinFit/", histname, sf_diboson, fout, "diboson_bTagDown", true);

//QCD MC
double sf_qcd = 1;
TH1F* qcd = readWriteHisto(fQCD, "base/Iso/KinFit/", histname, sf_qcd, fout, "qcd", true);
TH1F* qcd_JESUp = readWriteHisto(fQCD, "JESPlus/Iso/KinFit/", histname, sf_qcd, fout, "qcd_JESUp", true);
TH1F* qcd_JERUp = readWriteHisto(fQCD, "JERPlus/Iso/KinFit/", histname, sf_qcd, fout, "qcd_JERUp", true);
TH1F* qcd_JESDown = readWriteHisto(fQCD, "JESMinus/Iso/KinFit/", histname, sf_qcd, fout, "qcd_JESDown", true);
TH1F* qcd_JERDown = readWriteHisto(fQCD, "JERMinus/Iso/KinFit/", histname, sf_qcd, fout, "qcd_JERDown", true);
TH1F* qcd_bTagUp = readWriteHisto(fQCD, "bTagPlus/Iso/KinFit/", histname, sf_qcd, fout, "qcd_bTagUp", true);
TH1F* qcd_bTagDown = readWriteHisto(fQCD, "bTagMinus/Iso/KinFit/", histname, sf_qcd, fout, "qcd_bTagDown", true);
//QCD data driven
TH1F* qcd_dd = readWriteHisto(fQCD_dd, "base/Iso/KinFit/", histname, sf_qcd, fout, "qcd", true);

//Data
double sf_data = 1; //should be 1, always
TH1F* data_obs = readWriteHisto(fData, "base/Iso/KinFit/", histname, sf_data, fout, "data_obs", true);


//----------------------------------------//
//function to make data card for each mass
//----------------------------------------//
void makeOneDataCard(TFile *fWH, int mass=80, TString label="WH80", TString label2="HH80", TString histname = "mjj_kfit"){
  cout<<" mass point: "<<mass<<endl;
  //wh
  double sf_wh_lumi = 1; 
  TH1F* wh_topPtweight = readWriteHisto(fWH, "base/", "SF_topPtWeights", 1, fout, "topPtWeight"+label, false);
  double sf_wh = sf_wh_lumi/wh_topPtweight->GetMean();
  TH1F* wh = readWriteHisto(fWH, "base/Iso/KinFit/", histname, sf_wh, fout, label, true);
  TH1F* wh_JESUp = readWriteHisto(fWH, "JESPlus/Iso/KinFit/", histname, sf_wh, fout, label+"_JESUp", true);
  TH1F* wh_JERUp = readWriteHisto(fWH, "JERPlus/Iso/KinFit/", histname, sf_wh, fout, label+"_JERUp", true);
  TH1F* wh_JESDown = readWriteHisto(fWH, "JESMinus/Iso/KinFit/", histname, sf_wh, fout, label+"_JESDown", true);
  TH1F* wh_JERDown = readWriteHisto(fWH, "JERMinus/Iso/KinFit/", histname, sf_wh, fout, label+"_JERDown", true);
  TH1F* wh_topPtUp = readWriteHisto(fWH,  "TopPtPlus/Iso/KinFit/", histname, sf_wh, fout, label+"_topPtUp", true);
  TH1F* wh_topPtDown = readWriteHisto(fWH, "TopPtMinus/Iso/KinFit/", histname, sf_wh, fout, label+"_topPtDown", true);
  TH1F* wh_bTagUp = readWriteHisto(fWH, "bTagPlus/Iso/KinFit/", histname, sf_wh, fout, label+"_bTagUp", true);
  TH1F* wh_bTagDown = readWriteHisto(fWH, "bTagMinus/Iso/KinFit/", histname, sf_wh, fout, label+"_bTagDown", true);
  
  //hh
  double sf_hh = 0; 
  TH1F* hh = readWriteHisto(fWH, "base/Iso/KinFit/", histname, sf_hh, fout, label2, true);
  TH1F* hh_JESUp = readWriteHisto(fWH, "JESPlus/Iso/KinFit/", histname, sf_hh, fout, label2+"_JESUp", true);
  TH1F* hh_JERUp = readWriteHisto(fWH, "JERPlus/Iso/KinFit/", histname, sf_hh, fout, label2+"_JERUp", true);
  TH1F* hh_JESDown = readWriteHisto(fWH, "JESMinus/Iso/KinFit/", histname, sf_hh, fout, label2+"_JESDown", true);
  TH1F* hh_JERDown = readWriteHisto(fWH, "JERMinus/Iso/KinFit/", histname, sf_hh, fout, label2+"_JERDown", true);
  TH1F* hh_topPtUp = readWriteHisto(fWH,  "TopPtPlus/Iso/KinFit/", histname, sf_hh, fout, label2+"_topPtUp", true);
  TH1F* hh_topPtDown = readWriteHisto(fWH, "TopPtMinus/Iso/KinFit/", histname, sf_hh, fout, label2+"_topPtDown", true);
  TH1F* hh_bTagUp = readWriteHisto(fWH, "bTagPlus/Iso/KinFit/", histname, sf_hh, fout, label2+"_bTagUp", true);
  TH1F* hh_bTagDown = readWriteHisto(fWH, "bTagMinus/Iso/KinFit/", histname, sf_hh, fout, label2+"_bTagDown", true);

  //open input template data card of 8 TeV
  ifstream in;
  char* c = new char[1000];
  in.open("template_datacard_csbar_mu_8TeV.txt");

  //create output data card for 13 TeV
  ofstream out(Form("datacard_csbar_mu_13TeV_mH%d.txt",  mass));
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
        line.replace( line.find("ZZZ") , 3 , string(Form("%f", totLumi)) ); 
        out << line << endl;
      }
      else if(line.find("shapes")!=string::npos){
        line.replace( line.find("XXX") , 3 , string("HplusShapes_mu_13TeV")  );
        out << line << endl;
      }
      else if(line.find("Observation")!=string::npos){
        line.replace( line.find("XXX") , 3 , string(Form("%.0f", data_obs->Integral()) )  );
        out << line << endl;
      }
      else if(line.find("process")!=string::npos && line.find("WH")!=string::npos){
        line.replace( line.find("XXX") , 3 , string(Form("%d", mass)) );
        line.replace( line.find("YYY") , 3 , string(Form("%d", mass)) );
        out << line << endl;
      }
      else if(line.find("rate")!=string::npos){
        string rate = "rate               ";  
        string space = "     ";
        out << rate ;
        out << space << 0*wh->Integral()
            << space << wh->Integral()
            << space << ttbar->Integral()
            << space << wjet->Integral()
            << space << zjet->Integral()
            << space << stop->Integral()
            << space << diboson->Integral()
            << space << qcd_dd->Integral()
            << endl;
      }
      else if(line.find("CMS_eff_b")!=string::npos){
        float bTagUnc_wh = (wh->Integral() > 0) ? getNormUnc(wh, wh_bTagUp, wh_bTagDown) : 1.00;
        line.replace( line.find("YYYY") , 4 , string(Form("%.2f", bTagUnc_wh)) );
        
        float bTagUnc_ttbar = (ttbar->Integral() > 0) ? getNormUnc(ttbar, ttbar_bTagUp, ttbar_bTagDown) : 1.00; 
        line.replace( line.find("ZZZZ") , 4 , string(Form("%.2f", bTagUnc_ttbar)) ); 
        
        float bTagUnc_stop = (stop->Integral() > 0) ? getNormUnc(stop, stop_bTagUp, stop_bTagDown) : 1.00; 
        line.replace( line.find("KKKK") , 4 , string(Form("%.2f", bTagUnc_stop)) ); 
        out << line << endl;
      }
      else if(line.find("CMS_mistag_b")!=string::npos){
        float bTagUnc_wjet = (wjet->Integral() > 0) ? getNormUnc(wjet, wjet_bTagUp, wjet_bTagDown) : 1.00;
        line.replace( line.find("XXXX") , 4 , string(Form("%.2f", bTagUnc_wjet)) ); 
       
        float bTagUnc_zjet = (zjet->Integral() > 0) ? getNormUnc(zjet, zjet_bTagUp, zjet_bTagDown) : 1.00;
        line.replace( line.find("YYYY") , 4 , string(Form("%.2f", bTagUnc_zjet)) ); 
       
        float bTagUnc_diboson = (diboson->Integral() > 0) ? getNormUnc(diboson, diboson_bTagUp, diboson_bTagDown) : 1.00;
        line.replace( line.find("KKKK") , 4 , string(Form("%.2f", bTagUnc_diboson)) ); 
        out << line << endl;
      }
      else if(line.find("CMS_stat_wh")!=string::npos){ 
        line.replace( line.find("XXXX") , 4 , string(Form("%.2f", getStatUnc(wh,  0))));  
        out << line << endl;
      } 
      else if(line.find("CMS_stat_tt")!=string::npos){  
	line.replace( line.find("XXXX") , 4 , string(Form("%.2f", getStatUnc(ttbar,  0))));   
        out << line << endl;
      }  
      else if(line.find("CMS_stat_wjet")!=string::npos){  
        line.replace( line.find("XXXX") , 4 , string(Form("%.2f", getStatUnc(wjet,  0))));   
        out << line << endl;
      }  
      else if(line.find("CMS_stat_zjet")!=string::npos){ 
        line.replace( line.find("XXXX") , 4 , string(Form("%.2f", getStatUnc(zjet,  0))));  
        out << line << endl; 
      }
      else if(line.find("CMS_stat_stop")!=string::npos){ 
        line.replace( line.find("XXXX") , 4 , string(Form("%.2f", getStatUnc(stop,  0))));  
        out << line << endl; 
      } 
      else if(line.find("CMS_stat_vv")!=string::npos){  
        line.replace( line.find("XXXX") , 4 , string(Form("%.2f", getStatUnc(diboson,  0))));   
        out << line << endl;  
      }
      else if(line.find("CMS_stat_qcd")!=string::npos){  
        line.replace( line.find("XXXX") , 4 , string(Form("%.2f", getStatUnc(qcd_dd,  0))));   
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

//----------------------------------------//
//make data card for all masses
//----------------------------------------//
void makeHPlusDataCard_13TeV(){
  makeOneDataCard(fWH80,  80,  "WH80",  "HH80",  histname);
  makeOneDataCard(fWH90,  90,  "WH90",  "HH90",  histname);
  makeOneDataCard(fWH100, 100, "WH100", "HH100", histname);
  makeOneDataCard(fWH120, 120, "WH120", "HH120", histname);
  makeOneDataCard(fWH140, 140, "WH140", "HH140", histname);
  makeOneDataCard(fWH150, 150, "WH150", "HH150", histname);
  makeOneDataCard(fWH155, 155, "WH155", "HH155", histname);
  makeOneDataCard(fWH160, 160, "WH160", "HH160", histname);
  fout->Close();
}

