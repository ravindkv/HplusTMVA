#include <iostream>
#include <fstream>
#include <iomanip>

//hadd all_MC.root all_DY.root all_ST.root all_TTJetsP.root all_VV.root all_WJets.root
double ttbar_sf = 1.0;

TH1F* getHisto(TFile *histFile, TString histPath, double sf){
  TH1F* hist; 
  TString inFile("$PWD/");
  TFile *fTT= new TFile(inFile+"all_TTJetsP.root"); 
  if(!(histFile->Get(histPath))){
    hist = (TH1F*)(fTT->Get(histPath));
    hist->Add(hist, -1);
  }else hist = (TH1F*)(histFile->Get(histPath));
  hist->Scale(sf);
  return hist;
}

//get statistical uncertainity
double getStatUnc(TH1F* hCentral, double sError = 0.0){
  double  norm = hCentral->IntegralAndError(1, hCentral->GetNbinsX(), sError);
  return sError;
}

void getABCDNumbers(ofstream &outFile, TFile *f, string proc, TString A, TString B, TString C, TString D, double sf = 1){
  TH1F * hA = getHisto(f, A, sf);
  TH1F * hB = getHisto(f, B, sf);
  TH1F * hC = getHisto(f, C, sf);
  TH1F * hD = getHisto(f, D, sf);
  double intA =lround(hA->Integral());
  double errA =lround(getStatUnc(hA, 0.0)); 
  double intB =lround(hB->Integral());
  double errB =lround(getStatUnc(hB, 0.0)); 
  double intC =lround(hC->Integral());
  double errC =lround(getStatUnc(hC, 0.0)); 
  double intD =lround(hD->Integral());
  double errD =lround(getStatUnc(hD, 0.0)); 
  outFile<< proc<<" & "<<intA <<" $\\pm$ "<< errA <<
      " & "<< intB <<"$\\pm$"<< errB<<
      " & "<< intC <<"$\\pm$"<< errC<<
      " & "<< intD <<"$\\pm$"<< errD<<" \\\\ "<<endl;
}

void makeABCDTable_13TeV(){  
  TString inFile("$PWD/");
  TFile *ttbar    		= new TFile(inFile+"all_TTJetsP.root"); 
  TFile *wjet  			= new TFile(inFile+"all_WJets.root"); 
  TFile *zjet  			= new TFile(inFile+"all_DY.root");
  TFile *stop  			= new TFile(inFile+"all_ST.root");
  TFile *diboson 		= new TFile(inFile+"all_VV.root");
  TFile *qcd  			= new TFile(inFile+"all_QCD.root");
  TFile *allMC 			= new TFile(inFile+"all_MC.root");
  
  TString dirLowMET = "baseLowMET"; 
  TString dirHighMET = "base";
  //TString dirLowMET = "baseIso20LowMET"; 
  //TString dirHighMET = "baseIso20HighMET";
  TFile *data = new TFile(inFile+"all_Data.root");
  ofstream outFile; 
  outFile.open("qcdABCDTable.tex"); 
  //outFile<<"\\documentclass[landscape,letterpaper]{article}"<<endl;  
  outFile<<"\\documentclass[landscape]{article}"<<endl;  
  outFile<<"\\pagestyle{empty}"<<endl;  
  outFile<<"\\usepackage{epsfig}"<<endl;  
  outFile<<"\\usepackage{amsmath}"<<endl;  
  outFile<<"\\usepackage{array}"<<endl;  
  outFile<<"\\usepackage{multirow}"<<endl;  
  outFile<<"\\usepackage[cm]{fullpage}"<<endl;  
  outFile<<"\\begin{document}"<<endl;  
  outFile<<""<<endl;
  outFile<<"\\begin{table}"<<endl; 
  outFile<<"\\begin{center}"<<endl; 
  outFile<<"\\begin{tabular}{ccccc}"<<endl; 
  outFile<<"\\hline "<<endl;
  outFile<<"\\hline "<<endl;
  outFile<< "\\bf{Process}"<<" & "<< "Region-A & "<< "Region-B & "<< "Region-C & "<< "Region-D "<<" \\\\ "<<endl;
  outFile<<"" <<" & "<< "(Iso, high MET) & "<< "(Non iso, high MET) & "<< "(Non iso, low MET)& "<< "(Iso, low MET)"<<" \\\\ "<<endl;
  outFile<<"\\hline "<<endl;
  outFile<<"\\hline "<<endl;
  //Add another table with JESUP
   getABCDNumbers(outFile, qcd, "MC QCD", dirHighMET+"/Iso/KinFit/mjj_kfit", dirHighMET+"/NonIso/KinFit/mjj_kfit", dirLowMET+"/NonIso/KinFit/mjj_kfit", dirLowMET+"/Iso/KinFit/mjj_kfit");
  outFile<<"\\hline "<<endl;

   getABCDNumbers(outFile, ttbar, "$t\\bar{t}$ + jets", dirHighMET+"/Iso/KinFit/mjj_kfit", dirHighMET+"/NonIso/KinFit/mjj_kfit", dirLowMET+"/NonIso/KinFit/mjj_kfit", dirLowMET+"/Iso/KinFit/mjj_kfit", ttbar_sf);
  
  getABCDNumbers(outFile, stop, "Single ~t",            dirHighMET+"/Iso/KinFit/mjj_kfit", dirHighMET+"/NonIso/KinFit/mjj_kfit", dirLowMET+"/NonIso/KinFit/mjj_kfit", dirLowMET+"/Iso/KinFit/mjj_kfit");

   getABCDNumbers(outFile, wjet, " W + jets",           dirHighMET+"/Iso/KinFit/mjj_kfit", dirHighMET+"/NonIso/KinFit/mjj_kfit", dirLowMET+"/NonIso/KinFit/mjj_kfit", dirLowMET+"/Iso/KinFit/mjj_kfit");

   getABCDNumbers(outFile, zjet, "$Z/\\gamma$ + jets",  dirHighMET+"/Iso/KinFit/mjj_kfit", dirHighMET+"/NonIso/KinFit/mjj_kfit", dirLowMET+"/NonIso/KinFit/mjj_kfit", dirLowMET+"/Iso/KinFit/mjj_kfit");
 
  getABCDNumbers(outFile, diboson, "VV",                dirHighMET+"/Iso/KinFit/mjj_kfit", dirHighMET+"/NonIso/KinFit/mjj_kfit", dirLowMET+"/NonIso/KinFit/mjj_kfit", dirLowMET+"/Iso/KinFit/mjj_kfit");
  outFile<<"\\hline "<<endl;
  getABCDNumbers(outFile, allMC, "nonQCDBkg",                 dirHighMET+"/Iso/KinFit/mjj_kfit", dirHighMET+"/NonIso/KinFit/mjj_kfit", dirLowMET+"/NonIso/KinFit/mjj_kfit", dirLowMET+"/Iso/KinFit/mjj_kfit");
  outFile<<"\\hline "<<endl;

   getABCDNumbers(outFile, data, "Data",                dirHighMET+"/Iso/KinFit/mjj_kfit", dirHighMET+"/NonIso/KinFit/mjj_kfit", dirLowMET+"/NonIso/KinFit/mjj_kfit", dirLowMET+"/Iso/KinFit/mjj_kfit");
  outFile<<"\\hline "<<endl;
  outFile<<"\\end{tabular}"<<endl; 
  outFile<<"\\end{center}"<<endl; 
  outFile<<"\\end{table}"<<endl; 
  outFile<<"\\end{document}"<<endl;  
  outFile.close(); 
} 
  
