#include <iostream>
#include <fstream>
#include <iomanip>

bool forPaper = true;
///INPUT FILES
TString muDir = "stack_20190402_Mu_Sys_ARC_JER";
TString eleDir = "stack_20190402_Ele_Sys_ARC_JER";
//TString muDir = "stack_20190402_Mu_Sys_ARC";
//TString eleDir = "stack_20190402_Ele_Sys_ARC";

TFile* fMuData    = TFile::Open(muDir+"/all_Data.root");
TFile* fMuVV      = TFile::Open(muDir+"/all_VV.root");
TFile* fMuDY      = TFile::Open(muDir+"/all_DY.root");
TFile* fMuWJ      = TFile::Open(muDir+"/all_WJets.root");
TFile* fMuST      = TFile::Open(muDir+"/all_ST.root");
TFile* fMuTT      = TFile::Open(muDir+"/all_TTJetsP.root");
TFile *fMuWH80    = TFile::Open(muDir+"/all_Hplus80.root");
TFile *fMuWH90    = TFile::Open(muDir+"/all_Hplus90.root");
TFile *fMuWH100   = TFile::Open(muDir+"/all_Hplus100.root");
TFile *fMuWH120   = TFile::Open(muDir+"/all_Hplus120.root");
TFile *fMuWH140   = TFile::Open(muDir+"/all_Hplus140.root");
TFile *fMuWH150   = TFile::Open(muDir+"/all_Hplus150.root");
TFile *fMuWH155   = TFile::Open(muDir+"/all_Hplus155.root");
TFile *fMuWH160   = TFile::Open(muDir+"/all_Hplus160.root");
TFile* fMuQCD     = TFile::Open(muDir+"/all_QCD_dd.root"); 
TFile* fMuBkg     = TFile::Open(muDir+"/all_MC.root"); 

TFile* fEleData    = TFile::Open(eleDir+"/all_Data.root");
TFile* fEleVV      = TFile::Open(eleDir+"/all_VV.root");
TFile* fEleDY      = TFile::Open(eleDir+"/all_DY.root");
TFile* fEleWJ      = TFile::Open(eleDir+"/all_WJets.root");
TFile* fEleST      = TFile::Open(eleDir+"/all_ST.root");
TFile* fEleTT      = TFile::Open(eleDir+"/all_TTJetsP.root");
TFile *fEleWH80    = TFile::Open(eleDir+"/all_Hplus80.root");
TFile *fEleWH90    = TFile::Open(eleDir+"/all_Hplus90.root");
TFile *fEleWH100   = TFile::Open(eleDir+"/all_Hplus100.root");
TFile *fEleWH120   = TFile::Open(eleDir+"/all_Hplus120.root");
TFile *fEleWH140   = TFile::Open(eleDir+"/all_Hplus140.root");
TFile *fEleWH150   = TFile::Open(eleDir+"/all_Hplus150.root");
TFile *fEleWH155   = TFile::Open(eleDir+"/all_Hplus155.root");
TFile *fEleWH160   = TFile::Open(eleDir+"/all_Hplus160.root");
TFile* fEleQCD     = TFile::Open(eleDir+"/all_QCD_dd.root"); 
TFile* fEleBkg     = TFile::Open(eleDir+"/all_MC.root"); 

//----------------------------------------//
//Variuos functions
//----------------------------------------//
TH1F*  getHisto(TFile *inRootFile, TString histPath, TString histName){
  TH1F* hist;
  TString fullPath = histPath+histName;
  string exception_msg (inRootFile->GetName()+TString("/")+fullPath+", does not exist");
  try{
    if(!(inRootFile->Get(fullPath)))
       throw  exception_msg.c_str();
  }catch (const char *e){
    ///cout<<"WARNING:"<<e<<endl;
  }
  try{
    if(!(fMuTT->Get(fullPath)))
       throw  exception_msg.c_str();
  }catch (const char *e){
    cout<<"\033[01;31mERROR: \033[0m"<<e<< endl;
    exit(0);
  }
  if(!(inRootFile->Get(fullPath))){
    hist = (TH1F*)(fMuTT->Get(fullPath))->Clone(histName);
    hist->Reset();
  }else hist = (TH1F*)(inRootFile->Get(fullPath))->Clone(histName);
  //hist->Scale(1.0/0.12155);
  return hist;
}

//get statistical uncertainity
double getStatUnc(TH1F* hCentral, double sError = 0.0){
  double  norm = hCentral->IntegralAndError(1, hCentral->GetNbinsX(), sError);
  //double statUnc = (norm > 0) ? 1 + (fabs(sError)/norm) : 1.00; 
  return sError;
  //return sError*100/norm;
}

//get systematics uncertainity
double getSysUnc(TH1F * hUp, TH1F * hBase, TH1F * hDown){
    double valUp    = hUp->Integral();
    double valBase  = hBase->Integral();
    double valDown  = hDown->Integral();
	double uncTag = TMath::Max(fabs(valUp - valBase), fabs(valBase - valDown));
	return uncTag;
	//return lround(uncTag*100/valBase);
	//return uncTag*100/valBase;

}

double getAllSysUnc(TFile *inRootFile, TString histPath, TString histName){
    //up
    vector<string> sysListPlus;
    sysListPlus.push_back("PileupPlus");
    sysListPlus.push_back("JESPlus");
    sysListPlus.push_back("JERPlus");
    sysListPlus.push_back("TopPtPlus");
    sysListPlus.push_back("bcTagPlus1");
    sysListPlus.push_back("bcTagPlus2");
    sysListPlus.push_back("bcTagPlus3");
    //down
    vector<string> sysListMinus;
    sysListMinus.push_back("PileupMinus");
    sysListMinus.push_back("JESMinus");
    sysListMinus.push_back("JERMinus");
    sysListMinus.push_back("TopPtMinus");
    sysListMinus.push_back("bcTagMinus1");
    sysListMinus.push_back("bcTagMinus2");
    sysListMinus.push_back("bcTagMinus3");
    //get all sys
    double allSys = 0.0;
    double valBase = 0.0;
    TH1F * hBase = getHisto(inRootFile, "base/"+histPath, histName);
    valBase = hBase->Integral();
    for(int i =0; i <sysListPlus.size(); i++){
      TH1F* hUp = getHisto(inRootFile, TString(sysListPlus[i])+"/"+histPath, histName); 
      TH1F* hDown = getHisto(inRootFile, TString(sysListMinus[i])+"/"+histPath, histName); 
      double sys = getSysUnc(hUp, hBase, hDown);
      allSys = allSys + sys*sys;
    }
    return sqrt(allSys);
    //return sqrt(allSys)*100/valBase;
}

//convert double to string
string dToStr(double val){
     ostringstream convert;
     string result("");
     //convert <<std::setprecision(2)<<val;
     convert <<std::scientific<<lround(val);
     result = convert.str();
  return result;
}

//get Nevents + stat + sys
string getYieldWithUnc(string procName, TFile* inRootFile, TString histPath, TString histName){
    TH1F * hBase = getHisto(inRootFile, "base/"+histPath, histName);
    double yield = hBase->Integral();
    double errInit = 0;
    double statUnc = getStatUnc(hBase, errInit);
    double sysUnc = getAllSysUnc(inRootFile, histPath, histName);
    //no sys on data and QCD
    TString procName_(procName);
    if(procName_.Contains("data")|| procName_.Contains("QCD")) sysUnc = 0.0;
    double combUnc = 0.0;
    combUnc = sqrt(statUnc*statUnc + sysUnc*sysUnc);
    string yieldWithUnc = dToStr(yield) +" $\\pm$ "+ dToStr(statUnc) +" $\\pm$ "+ dToStr(sysUnc); 
    if(forPaper) yieldWithUnc = dToStr(yield) +" $\\pm$ "+ dToStr(combUnc);
    return yieldWithUnc;
}

string getRowInc(string procName, TFile *fMu, TFile *fEle, TString histName){
  string muCol = getYieldWithUnc(procName, fMu, "Iso/KinFit", "/"+histName);
  string eleCol = getYieldWithUnc(procName, fEle, "Iso/KinFit", "/"+histName);
  string combined = procName +" & "+muCol +" & "+ eleCol +"\\\\";
  cout<<combined<<endl;
  return combined;
}

string getRowEx(string procName, TFile *fMu, TFile *fEle){
  string muColExL = getYieldWithUnc(procName, fMu, "Iso/KinFit", "/mjj_kfit_CTagExL");
  string eleColExL = getYieldWithUnc(procName, fEle, "Iso/KinFit", "/mjj_kfit_CTagExL");
  string muColExM = getYieldWithUnc(procName, fMu, "Iso/KinFit", "/mjj_kfit_CTagExM");
  string eleColExM = getYieldWithUnc(procName, fEle, "Iso/KinFit", "/mjj_kfit_CTagExM");
  string muColExT = getYieldWithUnc(procName, fMu, "Iso/KinFit", "/mjj_kfit_CTagExT");
  string eleColExT = getYieldWithUnc(procName, fEle, "Iso/KinFit", "/mjj_kfit_CTagExT");

  string combined = procName +" & "+muColExL +" & "+ eleColExL
      +" & "+muColExM +" & "+eleColExM
      +" & "+muColExT +" & "+eleColExT
      +"\\\\";
  cout<<combined<<endl;
  return combined;
}

void MyMakeMjjYieldTable(){
  ofstream outFile;
  outFile.open("limit/mjjTable.tex");
  outFile<<"\\documentclass[]{article}"<<endl;
  outFile<<"\\usepackage{amsmath}"<<endl;
  outFile<<"\\usepackage{array}"<<endl;
  outFile<<"\\usepackage{multirow}"<<endl;
  outFile<<"\\usepackage[cm]{fullpage}"<<endl;
  outFile<<"\\begin{document}"<<endl;
  outFile<<""<<endl;
  outFile<<""<<endl;

  string nEvents = "";
  if(forPaper) nEvents = "$N_{events}  \\pm unc$";
  else nEvents = "$N_{events} \\pm stat \\pm sys$";
  //Inclusive Mjj
  outFile<<"\\begin{table}"<<endl;
  outFile<<"\\begin{center}"<<endl;
  outFile<<"\\begin{tabular}{cccc}"<<endl;
  outFile<<"\\hline "<<endl;
  outFile<<"\\hline "<<endl;
  outFile<<"\\bf{Process}& "<<nEvents<<" & "<<nEvents<<"\\\\ "<<endl;
  outFile<<" & $\\mu$ + jets &  e + jets\\\\"<<endl;
  outFile<<"\\hline "<<endl;
  outFile<<"\\hline "<<endl;
  outFile<<getRowInc("$m_{H^+}=80$ GeV", fMuWH80, fEleWH80, "mjj_kfit")<<endl;
  outFile<<getRowInc("$m_{H^+}=90$ GeV", fMuWH90, fEleWH90, "mjj_kfit")<<endl;
  outFile<<getRowInc("$m_{H^+}=100$ GeV", fMuWH100, fEleWH100, "mjj_kfit")<<endl;
  outFile<<getRowInc("$m_{H^+}=120$ GeV", fMuWH120, fEleWH120, "mjj_kfit")<<endl;
  outFile<<getRowInc("$m_{H^+}=140$ GeV", fMuWH140, fEleWH140, "mjj_kfit")<<endl;
  outFile<<getRowInc("$m_{H^+}=150$ GeV", fMuWH150, fEleWH150, "mjj_kfit")<<endl;
  outFile<<getRowInc("$m_{H^+}=155$ GeV", fMuWH155, fEleWH155, "mjj_kfit")<<endl;
  outFile<<getRowInc("$m_{H^+}=160$ GeV", fMuWH160, fEleWH160, "mjj_kfit")<<endl;
  outFile<<"\\hline "<<endl;
  outFile<<getRowInc("SM $t\\bar{t}$ + jets", fMuTT, fEleTT, "mjj_kfit")<<endl;
  outFile<<getRowInc("Single ~t"            , fMuST, fEleST, "mjj_kfit")<<endl;
  outFile<<getRowInc("QCD multijet"                  , fMuQCD, fEleQCD, "mjj_kfit")<<endl;
  outFile<<getRowInc("W + jets"             , fMuWJ, fEleWJ, "mjj_kfit")<<endl;
  outFile<<getRowInc("$Z/\\gamma$ + jets"   , fMuDY, fEleDY, "mjj_kfit")<<endl;
  outFile<<getRowInc("VV"                   , fMuVV, fEleVV, "mjj_kfit")<<endl;
  outFile<<"\\hline "<<endl;
  outFile<<getRowInc("All background"              , fMuBkg, fEleBkg, "mjj_kfit")<<endl;
  outFile<<"\\hline "<<endl;
  outFile<<getRowInc("Data"                 , fMuData, fEleData, "mjj_kfit")<<endl;
  outFile<<"\\hline "<<endl;
  outFile<<"\\end{tabular}"<<endl;
  outFile<<"\\caption{Event yield for inclusive category.}"<<endl;
  outFile<<"\\label{tab:eventYieldInc}"<<endl;
  outFile<<"\\end{center}"<<endl;
  outFile<<"\\end{table}"<<endl;
  outFile<<""<<endl;
  outFile<<""<<endl;

  //Inclusive CTagL
  outFile<<"\\begin{table}"<<endl;
  outFile<<"\\begin{center}"<<endl;
  outFile<<"\\begin{tabular}{cccc}"<<endl;
  outFile<<"\\hline "<<endl;
  outFile<<"\\hline "<<endl;
  outFile<<"\\bf{Process}& "<<nEvents<<" & "<<nEvents<<"\\\\"<<endl;
  outFile<<" & $\\mu$ + jets &  e + jets\\\\"<<endl;
  outFile<<"\\hline "<<endl;
  outFile<<"\\hline "<<endl;
  outFile<<getRowInc("$m_{H^+}=80$ GeV", fMuWH80, fEleWH80, "mjj_kfit_CTagIncL")<<endl;
  outFile<<getRowInc("$m_{H^+}=90$ GeV", fMuWH90, fEleWH90, "mjj_kfit_CTagIncL")<<endl;
  outFile<<getRowInc("$m_{H^+}=100$ GeV", fMuWH100, fEleWH100, "mjj_kfit_CTagIncL")<<endl;
  outFile<<getRowInc("$m_{H^+}=120$ GeV", fMuWH120, fEleWH120, "mjj_kfit_CTagIncL")<<endl;
  outFile<<getRowInc("$m_{H^+}=140$ GeV", fMuWH140, fEleWH140, "mjj_kfit_CTagIncL")<<endl;
  outFile<<getRowInc("$m_{H^+}=150$ GeV", fMuWH150, fEleWH150, "mjj_kfit_CTagIncL")<<endl;
  outFile<<getRowInc("$m_{H^+}=155$ GeV", fMuWH155, fEleWH155, "mjj_kfit_CTagIncL")<<endl;
  outFile<<getRowInc("$m_{H^+}=160$ GeV", fMuWH160, fEleWH160, "mjj_kfit_CTagIncL")<<endl;
  outFile<<"\\hline "<<endl;
  outFile<<getRowInc("SM $t\\bar{t}$ + jets", fMuTT, fEleTT, "mjj_kfit_CTagIncL")<<endl;
  outFile<<getRowInc("Single ~t"            , fMuST, fEleST, "mjj_kfit_CTagIncL")<<endl;
  outFile<<getRowInc("QCD multijet"                  , fMuQCD, fEleQCD, "mjj_kfit_CTagIncL")<<endl;
  outFile<<getRowInc("W + jets"             , fMuWJ, fEleWJ, "mjj_kfit_CTagIncL")<<endl;
  outFile<<getRowInc("$Z/\\gamma$ + jets"   , fMuDY, fEleDY, "mjj_kfit_CTagIncL")<<endl;
  outFile<<getRowInc("VV"                   , fMuVV, fEleVV, "mjj_kfit_CTagIncL")<<endl;
  outFile<<"\\hline "<<endl;
  outFile<<getRowInc("All background"              , fMuBkg, fEleBkg, "mjj_kfit_CTagIncL")<<endl;
  outFile<<"\\hline "<<endl;
  outFile<<getRowInc("Data"                 , fMuData, fEleData, "mjj_kfit_CTagIncL")<<endl;
  outFile<<"\\hline "<<endl;
  outFile<<"\\end{tabular}"<<endl;
  outFile<<"\\caption{Event yield for inclusive loose charm category.}"<<endl;
  outFile<<"\\label{tab:eventYieldCTagInc}"<<endl;
  outFile<<"\\end{center}"<<endl;
  outFile<<"\\end{table}"<<endl;
  outFile<<""<<endl;
  outFile<<""<<endl;

  //Mjj from exclusive categories
  outFile<<"\\begin{table}"<<endl;
  outFile<<"\\begin{center}"<<endl;

  //if(forPaper)outFile<<"\\scriptsize{"<<endl;
  outFile<<"\\scriptsize{"<<endl;
  outFile<<"\\begin{tabular}{cccccccc}"<<endl;
  outFile<<"\\hline "<<endl;
  outFile<<"\\hline "<<endl;
  outFile<<"\\multicolumn{1}{c}{{\\bf{Process}}} & \\multicolumn{2}{c}{{Exclusive loose category}} & \\multicolumn{2}{c}{{Exclusive medium category}} & \\multicolumn{2}{c}{{Exclusive tight category}} \\\\"<<endl;                          
  outFile<<"& "<<nEvents<<" & "<<nEvents<<" & "<<nEvents<<" & "<<nEvents<<" & "<<nEvents<<" & "<<nEvents<<"\\\\"<<endl;
  outFile<<" & $\\mu$ + jets &  e + jets & $\\mu$ + jets &  e + jets & $\\mu$ + jets &  e + jets \\\\"<<endl;
  outFile<<"\\hline "<<endl;
  outFile<<"\\hline "<<endl;
  outFile<<getRowEx("$m_{H^+}=80$ GeV", fMuWH80, fEleWH80)<<endl;
  outFile<<getRowEx("$m_{H^+}=90$ GeV", fMuWH90, fEleWH90)<<endl;
  outFile<<getRowEx("$m_{H^+}=100$ GeV", fMuWH100, fEleWH100)<<endl;
  outFile<<getRowEx("$m_{H^+}=120$ GeV", fMuWH120, fEleWH120)<<endl;
  outFile<<getRowEx("$m_{H^+}=140$ GeV", fMuWH140, fEleWH140)<<endl;
  outFile<<getRowEx("$m_{H^+}=150$ GeV", fMuWH150, fEleWH150)<<endl;
  outFile<<getRowEx("$m_{H^+}=155$ GeV", fMuWH155, fEleWH155)<<endl;
  outFile<<getRowEx("$m_{H^+}=160$ GeV", fMuWH160, fEleWH160)<<endl;
  outFile<<"\\hline "<<endl;
  outFile<<getRowEx("SM $t\\bar{t}$ + jets", fMuTT, fEleTT)<<endl;
  outFile<<getRowEx("Single ~t"            , fMuST, fEleST)<<endl;
  outFile<<getRowEx("QCD multijet"                  , fMuQCD, fEleQCD)<<endl;
  outFile<<getRowEx("W + jets"             , fMuWJ, fEleWJ)<<endl;
  outFile<<getRowEx("$Z/\\gamma$ + jets"   , fMuDY, fEleDY)<<endl;
  outFile<<getRowEx("VV"                   , fMuVV, fEleVV)<<endl;
  outFile<<"\\hline "<<endl;
  outFile<<getRowEx("All background"              , fMuBkg, fEleBkg)<<endl;
  outFile<<"\\hline "<<endl;
  outFile<<getRowEx("Data"                 , fMuData, fEleData)<<endl;
  outFile<<"\\hline "<<endl;
  outFile<<"\\end{tabular}"<<endl;
  outFile<<"}"<<endl;
  outFile<<"\\caption{Event yield for exclusive charm categories.}"<<endl;
  outFile<<"\\label{tab:eventYieldCTagEx}"<<endl;
  outFile<<"\\end{center}"<<endl;
  outFile<<"\\end{table}"<<endl;
  outFile<<""<<endl;
  outFile<<""<<endl;
  
  outFile<<"\\end{document}"<<endl;
  outFile.close();
}
