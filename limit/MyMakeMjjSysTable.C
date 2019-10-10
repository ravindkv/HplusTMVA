#include <iostream>
#include <fstream>
#include <iomanip>

bool forPaper = false;
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

double sysUncJESTopPt( TH1F * h_JESPlus, TH1F * h_base, TH1F * h_JESMinus, TH1F * h_JERPlus, TH1F * h_JERMinus, TH1F * h_TopPtPlus, TH1F * h_TopPtMinus){
  double uncJES = pow(TMath::Max(fabs(h_JESPlus->Integral() - h_base->Integral()), fabs(h_base->Integral() - h_JESMinus->Integral())), 2);
  double uncJER = pow(TMath::Max(fabs(h_JERPlus->Integral() - h_base->Integral()), fabs(h_base->Integral() - h_JERMinus->Integral())), 2);
  double uncTop = pow(TMath::Max(fabs(h_TopPtPlus->Integral() - h_base->Integral()), fabs(h_base->Integral() - h_TopPtMinus->Integral())), 2);
  double unc = sqrt(uncJES +uncJER  +uncTop);
  return unc ;
}

double sysUncBCTag (TH1F * h_bTagPlus, TH1F * h_base, TH1F * h_bTagMinus){
	double uncTag = TMath::Max(fabs(h_bTagPlus->Integral() - h_base->Integral()), fabs(h_base->Integral() - h_bTagMinus->Integral()));
	return uncTag;
}

//Relative sys unc
double relSysUncJetMET( TH1F * h_JESPlus, TH1F * h_base, TH1F * h_JESMinus, TH1F * h_JERPlus, TH1F * h_JERMinus){
  double uncJES = pow(TMath::Max(fabs(h_JESPlus->Integral() - h_base->Integral()), fabs(h_base->Integral() - h_JESMinus->Integral())), 2);
  double uncJER = pow(TMath::Max(fabs(h_JERPlus->Integral() - h_base->Integral()), fabs(h_base->Integral() - h_JERMinus->Integral())), 2);
  double unc = 100*(sqrt(uncJES +uncJER)/h_base->Integral());
  return unc ;
}

double relSysUncTopPt( TH1F * h_base, TH1F * h_TopPtPlus, TH1F * h_TopPtMinus){
  double uncTop = pow(TMath::Max(fabs(h_TopPtPlus->Integral() - h_base->Integral()), fabs(h_base->Integral() - h_TopPtMinus->Integral())), 2);
  double unc = 100*(sqrt(uncTop)/h_base->Integral());
  return unc ;
}
double relSysUncBCTag (TH1F * h_bTagPlus, TH1F * h_base, TH1F * h_bTagMinus){
	double uncTag = TMath::Max(fabs(h_bTagPlus->Integral() - h_base->Integral()), fabs(h_base->Integral() - h_bTagMinus->Integral()));
	return 100*(uncTag/h_base->Integral());
}

double relStatUnc (TH1F * hCentral){
	double sError = 0.0;
    double  norm = hCentral->IntegralAndError(1, hCentral->GetNbinsX(), sError);
    return 100*(sError/norm);
}

// Get histograms
TH1F*  getHisto(TFile *inRootFile, TString baseDir, TString isoDir, TString histDir, TString histName){
  TH1F* hist;
  TString inFile(inRootFile->GetName());
  TString fullPath = baseDir+isoDir+histDir+histName;
  string exception_msg ("The histogram path, "+inFile+"/"+fullPath+", does not exist");
  try{
    if(!(inRootFile->Get(fullPath)))
       throw  exception_msg.c_str();
  }catch (const char *e){
    //cout<<"WARNING:"<<e<<endl;
  }
  try{
    if(!(fMuTT->Get("base/"+isoDir+histDir+histName))) //to initialise an empty hist
       throw  exception_msg.c_str();
  }catch (const char *e){
    cout<<"\033[01;31mERROR: \033[0m"<<e<< endl;
    exit(0);
  }
  if(!(inRootFile->Get(fullPath))){
    hist = (TH1F*)(fMuTT->Get("base/Iso/"+histDir+histName))->Clone(histName); //to initialise an empty hist
    hist->Reset();
  }else hist = (TH1F*)(inRootFile->Get(fullPath))->Clone(histName);
  return hist;
}

void fillSysRow(ofstream & outFile,  string rowLable, string lumi, string pileup, string lepton, string jetMet, string bc1, string bc2, string bc3, string xss, string stat, string topPt){
   outFile<<rowLable<< " & "<<lumi<<" &  "<< pileup<<" &  "<<lepton<< " & "<< 
       jetMet <<" &  "<< bc1 <<" &  "<<bc2<<" &  "<<bc3<<" &  "<<xss<<" & "<<
       stat<< " & " <<topPt<<" \\\\ "<<endl;
}

void fillSysRowExPaper(ofstream & outFile,  string rowLable, string pileup, string jetMet, string bc, string xss, string stat, string topPt, string catName){
   outFile<<catName<<" & "<<rowLable<< " &  "<< pileup<< " & "<< 
       jetMet <<" &  "<< bc <<" & "<<xss<<" & "<<
       stat<< " & " <<topPt<<" \\\\ "<<endl;
}

//convert double to string
string dToStr(double val1, double val2){
     ostringstream convert;
     string result("");
     convert <<std::setprecision(2)<<val1<<" ("<<val2<<")";
     //convert <<std::scientific<<lround(val);
     result = convert.str();
  return result;
}

void makeSysRow(ofstream & outFile, TFile *inFileMu, TFile *inFileEle, TString histDir, TString histName, string rowLable, double uncXss, bool isSignal, bool isQCD){
  TH1F* hMuBase = getHisto(inFileMu, "base/", "Iso/", histDir, histName);
  TH1F* hEleBase = getHisto(inFileEle, "base/", "Iso/", histDir, histName);
  if(isQCD){
      string c1 = rowLable;
      string c2 = "---";
      string c3 = "---";
      string c4 = "---";
      string c5 = "---";
      string c6 = "---";
      string c7 = "---";
      string c8 = "---";
      string c9 = "10(10)";
      double sMu = relStatUnc(hMuBase);
      double sEle = relStatUnc(hEleBase);
      string c10 = dToStr(sMu, sEle);
      string c11 = "---";
      fillSysRow(outFile, c1, c2, c3, c4, c5, c6, c7, c8, c9, c10, c11);
  }
  else{
    TH1F* hMuJESPlus     = getHisto(inFileMu, "JESPlus/", "Iso/", histDir, histName);
    TH1F* hMuJESMinus    = getHisto(inFileMu, "JESMinus/", "Iso/", histDir, histName);
    TH1F* hMuPileupPlus  = getHisto(inFileMu, "PileupPlus/", "Iso/", histDir, histName);
    TH1F* hMuPileupMinus = getHisto(inFileMu, "PileupMinus/", "Iso/", histDir, histName);
    TH1F* hMuJERPlus     = getHisto(inFileMu, "JERPlus/", "Iso/", histDir, histName);
    TH1F* hMuJERMinus    = getHisto(inFileMu, "JERMinus/", "Iso/", histDir, histName);
    TH1F* hMubcTagPlus1  = getHisto(inFileMu, "bcTagPlus1/", "Iso/", histDir, histName);
    TH1F* hMubcTagMinus1 = getHisto(inFileMu, "bcTagMinus1/", "Iso/", histDir, histName);
    TH1F* hMubcTagPlus2  = getHisto(inFileMu, "bcTagPlus2/", "Iso/", histDir, histName);
    TH1F* hMubcTagMinus2 = getHisto(inFileMu, "bcTagMinus2/", "Iso/", histDir, histName);
    TH1F* hMubcTagPlus3  = getHisto(inFileMu, "bcTagPlus3/", "Iso/", histDir, histName);
    TH1F* hMubcTagMinus3 = getHisto(inFileMu, "bcTagMinus3/", "Iso/", histDir, histName);
    //electron
    TH1F* hEleJESPlus     = getHisto(inFileEle, "JESPlus/", "Iso/", histDir, histName);
    TH1F* hEleJESMinus    = getHisto(inFileEle, "JESMinus/", "Iso/", histDir, histName);
    TH1F* hElePileupPlus  = getHisto(inFileEle, "PileupPlus/", "Iso/", histDir, histName);
    TH1F* hElePileupMinus = getHisto(inFileEle, "PileupMinus/", "Iso/", histDir, histName);
    TH1F* hEleJERPlus     = getHisto(inFileEle, "JERPlus/", "Iso/", histDir, histName);
    TH1F* hEleJERMinus    = getHisto(inFileEle, "JERMinus/", "Iso/", histDir, histName);
    TH1F* hElebcTagPlus1  = getHisto(inFileEle, "bcTagPlus1/", "Iso/", histDir, histName);
    TH1F* hElebcTagMinus1 = getHisto(inFileEle, "bcTagMinus1/", "Iso/", histDir, histName);
    TH1F* hElebcTagPlus2  = getHisto(inFileEle, "bcTagPlus2/", "Iso/", histDir, histName);
    TH1F* hElebcTagMinus2 = getHisto(inFileEle, "bcTagMinus2/", "Iso/", histDir, histName);
    TH1F* hElebcTagPlus3  = getHisto(inFileEle, "bcTagPlus3/", "Iso/", histDir, histName);
    TH1F* hElebcTagMinus3 = getHisto(inFileEle, "bcTagMinus3/", "Iso/", histDir, histName);
    string c1 = rowLable;
    string c2 = "2.5 (2.5)";
    double pMu  = relSysUncBCTag(hMuBase,  hMuPileupPlus,  hMuPileupMinus);
    double pEle = relSysUncBCTag(hEleBase, hElePileupPlus, hElePileupMinus);
    string c3 = dToStr(pMu, pEle);
    string c4 = "3.0 (3.0)";
    double jMu  = relSysUncJetMET( hMuJESPlus, hMuBase, hMuJESMinus, hMuJERPlus, hMuJERMinus);
    double jEle = relSysUncJetMET( hEleJESPlus, hEleBase, hEleJESMinus, hEleJERPlus, hEleJERMinus);
    string c5 = dToStr(jMu, jEle);
    double bc1Mu = relSysUncBCTag(hMubcTagPlus1, hMuBase, hMubcTagMinus1);
    double bc1Ele = relSysUncBCTag(hElebcTagPlus1, hEleBase, hElebcTagMinus1);
    string c6 = dToStr(bc1Mu, bc1Ele);
    double bc2Mu = relSysUncBCTag(hMubcTagPlus2, hMuBase, hMubcTagMinus2);
    double bc2Ele = relSysUncBCTag(hElebcTagPlus2, hEleBase, hElebcTagMinus2);
    string c7 = dToStr(bc2Mu, bc2Ele);
    double bc3Mu = relSysUncBCTag(hMubcTagPlus3, hMuBase, hMubcTagMinus3);
    double bc3Ele = relSysUncBCTag(hElebcTagPlus3, hEleBase, hElebcTagMinus3);
    string c8 = dToStr(bc3Mu, bc3Ele);
    string c9 = dToStr(uncXss, uncXss);
    double sMu = relStatUnc(hMuBase);
    double sEle = relStatUnc(hEleBase);
    string c10 = dToStr(sMu, sEle);
    if(isSignal){
      TH1F* hMuTopPtPlus   = getHisto(inFileMu, "TopPtPlus/", "Iso/", histDir, histName);
      TH1F* hMuTopPtMinus  = getHisto(inFileMu, "TopPtMinus/", "Iso/", histDir, histName);
      //electron
      TH1F* hEleTopPtPlus   = getHisto(inFileEle, "TopPtPlus/", "Iso/", histDir, histName);
      TH1F* hEleTopPtMinus  = getHisto(inFileEle, "TopPtMinus/", "Iso/", histDir, histName);
      double pMu = relSysUncTopPt(hMuBase, hMuTopPtPlus, hMuTopPtMinus);
      double pEle = relSysUncTopPt(hEleBase, hEleTopPtPlus, hEleTopPtMinus);
      string c11 = dToStr(pMu, pEle);
      fillSysRow(outFile, c1, c2, c3, c4, c5, c6, c7, c8, c9, c10, c11);
    }
    else 
      fillSysRow(outFile, c1, c2, c3, c4, c5, c6, c7, c8, c9, c10, "---");
  }
}

void makeSysRowEx(ofstream & outFile, TFile *inFileMu, TFile *inFileEle, TString histDir, TString histName, string rowLable, double uncXss, bool isSignal, bool isQCD, string catName){
  TH1F* hMuBase = getHisto(inFileMu, "base/", "Iso/", histDir, histName);
  TH1F* hEleBase = getHisto(inFileEle, "base/", "Iso/", histDir, histName);
  if(isQCD){
      string c0 = catName;
      string c1 = rowLable;
      string c2 = "---";
      string c3 = "---";
      string c4 = "---";
      string c5 = "---";
      string c6 = "---";
      string c7 = "---";
      string c8 = "---";
      string c9 = "10(10)";
      double sMu = relStatUnc(hMuBase);
      double sEle = relStatUnc(hEleBase);
      string c10 = dToStr(sMu, sEle);
      string c11 = "---";
      if(forPaper) fillSysRowExPaper(outFile, c1, c3, c5, c6, c9, c10, c11, c0);
      else fillSysRow(outFile, c1, c2, c3, c4, c5, c6, c7, c8, c9, c10, c11);
  }
  else{
    TH1F* hMuJESPlus     = getHisto(inFileMu, "JESPlus/", "Iso/", histDir, histName);
    TH1F* hMuJESMinus    = getHisto(inFileMu, "JESMinus/", "Iso/", histDir, histName);
    TH1F* hMuPileupPlus  = getHisto(inFileMu, "PileupPlus/", "Iso/", histDir, histName);
    TH1F* hMuPileupMinus = getHisto(inFileMu, "PileupMinus/", "Iso/", histDir, histName);
    TH1F* hMuJERPlus     = getHisto(inFileMu, "JERPlus/", "Iso/", histDir, histName);
    TH1F* hMuJERMinus    = getHisto(inFileMu, "JERMinus/", "Iso/", histDir, histName);
    TH1F* hMubcTagPlus1  = getHisto(inFileMu, "bcTagPlus1/", "Iso/", histDir, histName);
    TH1F* hMubcTagMinus1 = getHisto(inFileMu, "bcTagMinus1/", "Iso/", histDir, histName);
    TH1F* hMubcTagPlus2  = getHisto(inFileMu, "bcTagPlus2/", "Iso/", histDir, histName);
    TH1F* hMubcTagMinus2 = getHisto(inFileMu, "bcTagMinus2/", "Iso/", histDir, histName);
    TH1F* hMubcTagPlus3  = getHisto(inFileMu, "bcTagPlus3/", "Iso/", histDir, histName);
    TH1F* hMubcTagMinus3 = getHisto(inFileMu, "bcTagMinus3/", "Iso/", histDir, histName);
    //electron
    TH1F* hEleJESPlus     = getHisto(inFileEle, "JESPlus/", "Iso/", histDir, histName);
    TH1F* hEleJESMinus    = getHisto(inFileEle, "JESMinus/", "Iso/", histDir, histName);
    TH1F* hElePileupPlus  = getHisto(inFileEle, "PileupPlus/", "Iso/", histDir, histName);
    TH1F* hElePileupMinus = getHisto(inFileEle, "PileupMinus/", "Iso/", histDir, histName);
    TH1F* hEleJERPlus     = getHisto(inFileEle, "JERPlus/", "Iso/", histDir, histName);
    TH1F* hEleJERMinus    = getHisto(inFileEle, "JERMinus/", "Iso/", histDir, histName);
    TH1F* hElebcTagPlus1  = getHisto(inFileEle, "bcTagPlus1/", "Iso/", histDir, histName);
    TH1F* hElebcTagMinus1 = getHisto(inFileEle, "bcTagMinus1/", "Iso/", histDir, histName);
    TH1F* hElebcTagPlus2  = getHisto(inFileEle, "bcTagPlus2/", "Iso/", histDir, histName);
    TH1F* hElebcTagMinus2 = getHisto(inFileEle, "bcTagMinus2/", "Iso/", histDir, histName);
    TH1F* hElebcTagPlus3  = getHisto(inFileEle, "bcTagPlus3/", "Iso/", histDir, histName);
    TH1F* hElebcTagMinus3 = getHisto(inFileEle, "bcTagMinus3/", "Iso/", histDir, histName);
    string c0 = catName;
    string c1 = rowLable;
    string c2 = "2.5 (2.5)";
    double pMu  = relSysUncBCTag(hMuBase,  hMuPileupPlus,  hMuPileupMinus);
    double pEle = relSysUncBCTag(hEleBase, hElePileupPlus, hElePileupMinus);
    string c3 = dToStr(pMu, pEle);
    string c4 = "3.0 (3.0)";
    double jMu  = relSysUncJetMET( hMuJESPlus, hMuBase, hMuJESMinus, hMuJERPlus, hMuJERMinus);
    double jEle = relSysUncJetMET( hEleJESPlus, hEleBase, hEleJESMinus, hEleJERPlus, hEleJERMinus);
    string c5 = dToStr(jMu, jEle);
    double bc1Mu = relSysUncBCTag(hMubcTagPlus1, hMuBase, hMubcTagMinus1);
    double bc1Ele = relSysUncBCTag(hElebcTagPlus1, hEleBase, hElebcTagMinus1);
    double bc2Mu = relSysUncBCTag(hMubcTagPlus2, hMuBase, hMubcTagMinus2);
    double bc2Ele = relSysUncBCTag(hElebcTagPlus2, hEleBase, hElebcTagMinus2);
    double bc3Mu = relSysUncBCTag(hMubcTagPlus3, hMuBase, hMubcTagMinus3);
    double bc3Ele = relSysUncBCTag(hElebcTagPlus3, hEleBase, hElebcTagMinus3);
    double bcMu = sqrt(bc1Mu*bc1Mu + bc2Mu*bc2Mu + bc3Mu*bc3Mu);
    double bcEle = sqrt(bc1Ele*bc1Ele + bc2Ele*bc2Ele + bc3Ele*bc3Ele);
    string c6 = dToStr(bc1Mu, bc1Ele);
    string c7 = dToStr(bc2Mu, bc2Ele);
    string c8 = dToStr(bc3Mu, bc3Ele);
    if(forPaper)c6 = dToStr(bcMu, bcEle);
    string c9 = dToStr(uncXss, uncXss);
    double sMu = relStatUnc(hMuBase);
    double sEle = relStatUnc(hEleBase);
    string c10 = dToStr(sMu, sEle);
    if(isSignal){
      TH1F* hMuTopPtPlus   = getHisto(inFileMu, "TopPtPlus/", "Iso/", histDir, histName);
      TH1F* hMuTopPtMinus  = getHisto(inFileMu, "TopPtMinus/", "Iso/", histDir, histName);
      //electron
      TH1F* hEleTopPtPlus   = getHisto(inFileEle, "TopPtPlus/", "Iso/", histDir, histName);
      TH1F* hEleTopPtMinus  = getHisto(inFileEle, "TopPtMinus/", "Iso/", histDir, histName);
      double pMu = relSysUncTopPt(hMuBase, hMuTopPtPlus, hMuTopPtMinus);
      double pEle = relSysUncTopPt(hEleBase, hEleTopPtPlus, hEleTopPtMinus);
      string c11 = dToStr(pMu, pEle);
      if(forPaper)fillSysRowExPaper(outFile, c1, c3, c5, c6, c9, c10, c11, c0);
      else fillSysRow(outFile, c1, c2, c3, c4, c5, c6, c7, c8, c9, c10, c11);
    }
    else {
      if(forPaper) fillSysRowExPaper(outFile, c1, c3, c5, c6, c9, c10, "---", c0);
      else fillSysRow(outFile, c1, c2, c3, c4, c5, c6, c7, c8, c9, c10, "---");
    }
  }
}
void makeOneSysTable(ofstream & outFile, TString histDir, TString histName, TString catName){
  string tableName = "Systematic and statistical uncertainties in \\%, "+ string(catName)+" for muon (electron) channel. The \"---\" indicates that the corresponding uncertainties are not considered for the given process.";
  outFile<<"\\begin{table}"<<endl;
  outFile<<"\\begin{center}"<<endl;
  outFile<<"\\scriptsize{"<<endl;
  ///outFile<<"\\footnotesize\\setlength{\\tabcolsep}{0.3pt}"<<endl;
  outFile<<"\\begin{tabular}{  c c c c c c c c c c c c c cc}"<<endl;
  outFile<<"\\multicolumn{5}{c}{ } \\\\"<<endl;
  outFile<<"\\hline "<<endl;
  outFile<<"\\hline "<<endl;
  outFile<<"Process &{\\rotatebox{90}{Luminosity}} & {\\rotatebox{90}{Pileup} } & {\\rotatebox{90}{Lepton }} & {\\rotatebox{90}{JES + JER + \\MET}} & { \\rotatebox{90}{b \\& c-jet tagging-1} }  & { \\rotatebox{90}{b \\& c-jet tagging-2} } & { \\rotatebox{90}{b \\& c-jet tagging-3}}& { \\rotatebox{90}{Normalization}  }& {\\rotatebox{90}{Statistical}  } & {\\rotatebox{90}{top \\pt } }  \\\\ "<<endl;
  outFile<<"\\hline "<<endl;
  outFile<<"\\hline "<<endl;
  makeSysRow(outFile, fMuWH80,  fEleWH80, histDir, histName, "$m_{H^+}=80$ GeV", 6.1, true, false);
  makeSysRow(outFile, fMuWH90,  fEleWH90, histDir, histName, "$m_{H^+}=90$ GeV", 6.1, true, false);
  makeSysRow(outFile, fMuWH100, fEleWH100,histDir, histName, "$m_{H^+}=100$ GeV", 6.1, true, false);
  makeSysRow(outFile, fMuWH120, fEleWH120,histDir, histName, "$m_{H^+}=120$ GeV", 6.1, true, false);
  makeSysRow(outFile, fMuWH140, fEleWH140,histDir, histName, "$m_{H^+}=140$ GeV", 6.1, true, false);
  makeSysRow(outFile, fMuWH150, fEleWH150,histDir, histName, "$m_{H^+}=150$ GeV", 6.1, true, false);
  makeSysRow(outFile, fMuWH155, fEleWH155,histDir, histName, "$m_{H^+}=155$ GeV", 6.1, true, false);
  makeSysRow(outFile, fMuWH160, fEleWH160,histDir, histName, "$m_{H^+}=160$ GeV", 6.1, true, false);
  outFile<<"\\hline "<<endl;
  makeSysRow(outFile, fMuTT,  fEleTT, histDir, histName, "$t\\bar{t} + jets$", 6.1, true, false);
  makeSysRow(outFile, fMuST,  fEleST, histDir, histName, "Single ~t", 5.0, false, false);
  makeSysRow(outFile, fMuWJ,  fEleWJ, histDir, histName, "W+jets", 5.0, false, false);
  makeSysRow(outFile, fMuDY,  fEleDY, histDir, histName, "$Z/\\gamma$ + jets", 4.5, false, false);
  makeSysRow(outFile, fMuVV,  fEleVV, histDir, histName, "VV", 4.0, false, false);
  makeSysRow(outFile, fMuQCD, fEleQCD, histDir, histName, "QCD multijet", 60, false, true);
  outFile<<"\\hline "<<endl;
  outFile<<"\\end{tabular}"<<endl;
  outFile<<"}"<<endl;
  outFile<<"\\end{center}"<<endl;
  outFile<<"\\caption{"+tableName+"}"<<endl;
  outFile<<"\\end{table}"<<endl;
}

void makeOneSysTableEx(ofstream & outFile, TString histDir, TString histName, string catName){
  if(forPaper) makeSysRowEx(outFile, fMuWH120, fEleWH120,histDir, histName, "$m_{\\Hp}=120$ GeV", 6.1, true, false, catName);
  else{
  makeSysRowEx(outFile, fMuWH80, fEleWH80,histDir, histName,   "$m_{H^+}=80$ GeV", 6.1, true, false, catName);
  makeSysRowEx(outFile, fMuWH90, fEleWH90,histDir, histName,   "$m_{H^+}=90$ GeV", 6.1, true, false, "");
  makeSysRowEx(outFile, fMuWH100, fEleWH100,histDir, histName, "$m_{H^+}=100$ GeV", 6.1, true, false, "");
  makeSysRowEx(outFile, fMuWH120, fEleWH120,histDir, histName, "$m_{H^+}=120$ GeV", 6.1, true, false, "");
  makeSysRowEx(outFile, fMuWH140, fEleWH140,histDir, histName, "$m_{H^+}=140$ GeV", 6.1, true, false, "");
  makeSysRowEx(outFile, fMuWH150, fEleWH150,histDir, histName, "$m_{H^+}=150$ GeV", 6.1, true, false, "");
  makeSysRowEx(outFile, fMuWH155, fEleWH155,histDir, histName, "$m_{H^+}=155$ GeV", 6.1, true, false, "");
  makeSysRowEx(outFile, fMuWH160, fEleWH160,histDir, histName, "$m_{H^+}=160$ GeV", 6.1, true, false, "");
  }
  makeSysRowEx(outFile, fMuTT,  fEleTT, histDir, histName, "\\ttjets", 6.1, true, false, "");
  makeSysRowEx(outFile, fMuST,  fEleST, histDir, histName, "Single \\PQt ", 5.0, false, false, "");
  makeSysRowEx(outFile, fMuWJ,  fEleWJ, histDir, histName, "\\PW + jets", 5.0, false, false, "");
  makeSysRowEx(outFile, fMuDY,  fEleDY, histDir, histName, "$\\PZ/\\PGg$ + jets", 4.5, false, false, "");
  makeSysRowEx(outFile, fMuVV,  fEleVV, histDir, histName, "VV", 4.0, false, false, "");
  makeSysRowEx(outFile, fMuQCD, fEleQCD, histDir, histName, "QCD multijet", 60, false, true, "");
}

void makeAllSysTableEx(ofstream & outFile){
  string tableName = "Systematic and statistical uncertainties in \\%, from exclusive charm categories for muon (electron) channel. The \"---\" indicates that the corresponding uncertainties are not considered for the given process.";

  outFile<<"\\begin{table}"<<endl;
  outFile<<"\\begin{center}"<<endl;
  outFile<<"\\scriptsize{"<<endl;
  ///outFile<<"\\footnotesize\\setlength{\\tabcolsep}{0.3pt}"<<endl;
  if(forPaper) outFile<<"\\begin{tabular}{cccccccc}"<<endl;
  else outFile<<"\\begin{tabular}{  c c c c c c c c c c c c c cc}"<<endl;
  outFile<<"\\hline "<<endl;
  outFile<<"\\hline "<<endl;
  if(forPaper) outFile<<"Category &Process& Pileup & jet \\& \\ptmiss & \\PQb \\& \\PQc-jet & Normalization& Statistical & top \\pt\\\\"<<endl;
  else outFile<<"Process &{\\rotatebox{90}{Luminosity}} & {\\rotatebox{90}{Pileup} } & {\\rotatebox{90}{Lepton }} & {\\rotatebox{90}{JES + JER + \\MET}} & { \\rotatebox{90}{b \\& c-jet tagging-1} }  & { \\rotatebox{90}{b \\& c-jet tagging-2} } & { \\rotatebox{90}{b \\& c-jet tagging-3}}& { \\rotatebox{90}{Normalization}  }& {\\rotatebox{90}{Statistical}  } & {\\rotatebox{90}{top \\pt } }  \\\\ "<<endl;
  outFile<<"\\hline "<<endl;
  outFile<<"\\hline "<<endl;
  makeOneSysTableEx(outFile, "KinFit/", "mjj_kfit_CTagExL", " Loose ");
  outFile<<"\\hline "<<endl;
  makeOneSysTableEx(outFile, "KinFit/", "mjj_kfit_CTagExM", " Medium");
  outFile<<"\\hline "<<endl;
  makeOneSysTableEx(outFile, "KinFit/", "mjj_kfit_CTagExT", " Tight ");
  outFile<<"\\hline "<<endl;
  outFile<<"\\end{tabular}"<<endl;
  outFile<<"}"<<endl;
  outFile<<"\\end{center}"<<endl;
  outFile<<"\\caption{"+tableName+"}"<<endl;
  outFile<<"\\end{table}"<<endl;
}

void MyMakeMjjSysTable(TString histSubDir="Iso/", TString histName="mjj_kfit"){
  ofstream outFile;
  string outName = "limit/sysTable.tex";
  outFile.open(outName.c_str());
  //outFile<<"\\documentclass[landscape,letterpaper]{article}"<<endl;
  //outFile<<"\\documentclass[landscape]{article}"<<endl;
  outFile<<"\\documentclass[]{article}"<<endl;
  outFile<<"\\pagestyle{empty}"<<endl;
  outFile<<"\\usepackage{epsfig}"<<endl;
  outFile<<"\\usepackage{amsmath}"<<endl;
  outFile<<"\\usepackage{array}"<<endl;
  outFile<<"\\usepackage{multirow}"<<endl;
  outFile<<"\\usepackage[cm]{fullpage}"<<endl;
  outFile<<"\\textheight = 8.in"<<endl;
  outFile<<"\\textwidth 7.0in"<<endl;
  outFile<<"\\begin{document}"<<endl;
  outFile<<"\\newcommand{\\MET}{MET }"<<endl;
  outFile<<"\\newcommand{\\ptmiss}{MET }"<<endl;
  outFile<<"\\newcommand{\\pt}{pT }"<<endl;
  outFile<<"\\newcommand{\\Hp}{H^+ }"<<endl;
  outFile<<"\\newcommand{\\ttjets}{$t\\bar{t} + jets$}"<<endl;
  outFile<<"\\newcommand{\\PW}{W }"<<endl;
  outFile<<"\\newcommand{\\PZ}{Z }"<<endl;
  outFile<<"\\newcommand{\\PGg}{\\gamma}"<<endl;
  outFile<<"\\newcommand{\\PQt}{t }"<<endl;
  outFile<<"\\newcommand{\\PQb}{b }"<<endl;
  outFile<<"\\newcommand{\\PQc}{c }"<<endl;

  outFile<<""<<endl;
  makeOneSysTable(outFile, "KinFit/", "mjj_kfit", " from inclusive category");
  makeOneSysTable(outFile, "KinFit/", "mjj_kfit_CTagIncL", "from inclusive loose charm-category");
  makeAllSysTableEx(outFile);
  //makeOneSysTable(outFile, "KinFit/", "mjj_kfit_CTagExL", " from exclusive loose charm-category");
  //makeOneSysTable(outFile, "KinFit/", "mjj_kfit_CTagExM", " from exclusive medium charm-category");
  //makeOneSysTable(outFile, "KinFit/", "mjj_kfit_CTagExT", " from exclusive tight charm-category");
  outFile<<"\\end{document}"<<endl;
  outFile.close();
}
