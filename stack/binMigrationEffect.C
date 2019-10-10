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
double totLumi = 35.50;
TString inFileDir="$PWD";
//MAKE DATA CARD of mjj
//TString histname="inShapeHisto_";
bool isMuChannel = true;
bool isEleChannel = false;

TFile* fData    = TFile::Open(inFileDir+"/all_muData.root");
//OUTPUT FILE
TString outShapeFile ="HplusShapes";
TFile *fout = new TFile(outShapeFile+"_binMigration_13TeV.root", "RECREATE");

//bkg
TFile* fVV      = TFile::Open(inFileDir+"/all_VV.root");
TFile* fDY      = TFile::Open(inFileDir+"/all_DY.root");
TFile* fWJ      = TFile::Open(inFileDir+"/all_WJets.root");
TFile* fQCD     = TFile::Open(inFileDir+"/all_QCD.root");
TFile* fST      = TFile::Open(inFileDir+"/all_ST.root");
TFile* fTT      = TFile::Open(inFileDir+"/all_TTJetsP.root");
TFile* fTT_up      	= TFile::Open(inFileDir+"/all_TTJetsP_up.root");
TFile* fTT_down      	= TFile::Open(inFileDir+"/all_TTJetsP_down.root");
TFile* fTT_mtop1715     = TFile::Open(inFileDir+"/all_TTJetsP_mtop1715.root");
TFile* fTT_mtop1735     = TFile::Open(inFileDir+"/all_TTJetsP_mtop1735.root");
TFile* fTT_hdampUP      = TFile::Open(inFileDir+"/all_TTJetsP_hdampUP.root");
TFile* fTT_hdampDOWN    = TFile::Open(inFileDir+"/all_TTJetsP_hdampDOWN.root");
//signal
TFile *fWH80      = TFile::Open(inFileDir+"/all_Hplus80.root");
TFile *fWH90      = TFile::Open(inFileDir+"/all_Hplus90.root");
TFile *fWH100     = TFile::Open(inFileDir+"/all_Hplus100.root");
TFile *fWH120     = TFile::Open(inFileDir+"/all_Hplus120.root");
TFile *fWH140     = TFile::Open(inFileDir+"/all_Hplus140.root");
TFile *fWH150     = TFile::Open(inFileDir+"/all_Hplus150.root");
TFile *fWH155     = TFile::Open(inFileDir+"/all_Hplus155.root");
TFile *fWH160     = TFile::Open(inFileDir+"/all_Hplus160.root");
//data driven qcd
//TFile* fQCD_dd = TFile::Open(inFileDir+"/all_QCD_dd.root"); 
TFile* fQCD_dd = TFile::Open(inFileDir+"/all_QCD.root"); 


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

//----------------------------------------//
//Global variables
//----------------------------------------//
double getPercent(TH1F* h1, TH1F* h2){
  std::setprecision(3);
  return (h2->Integral() - h1->Integral())*100/(h1->Integral());
}

void getSysEffectRow(ofstream &outFile, TString proc_name, TH1F *base, TH1F *JESUp, TH1F *JESDown, TH1F *JERUp, TH1F *JERDown, TH1F *bTagUp, TH1F *bTagDown, TH1F *cTagUp, TH1F *cTagDown){

outFile<<proc_name<<" & " << base->Integral()<<" & "<<std::setprecision(3)<<getPercent(base, JESUp) <<" & "<<std::setprecision(3)<< getPercent(base, JESDown)<<" & "<<std::setprecision(3)<<getPercent(base, JERUp) <<" & "<<std::setprecision(3)<<getPercent(base, JERDown) <<" & "<<std::setprecision(3)<< getPercent(base, bTagUp) <<" & "<<std::setprecision(3)<< getPercent(base, bTagDown)<<" & "<<std::setprecision(3)<< getPercent(base, cTagUp) <<" & " <<std::setprecision(3)<< getPercent(base, cTagDown) << " \\\\ "<<endl; 

}

void getSysEffectTable(ofstream &outFile, TString histname, TString label){
//ttbar
double sf_ttbar_lumi = 1; 
TH1F* ttbar_topPtweight = readWriteHisto(fTT, "base/", "SF_topPtWeights", 1, fout, "topPtWeights", false);
double sf_ttbar = sf_ttbar_lumi/ttbar_topPtweight->GetMean();
TH1F* ttbar = readWriteHisto(fTT, "base/Iso/", histname, sf_ttbar, fout, "ttbar", true);
TH1F* ttbar_JESUp = readWriteHisto(fTT, "JESPlus/Iso/", histname, sf_ttbar, fout, "ttbar_JESUp", true);
TH1F* ttbar_JERUp = readWriteHisto(fTT, "JERPlus/Iso/", histname, sf_ttbar, fout, "ttbar_JERUp", true);
TH1F* ttbar_JESDown = readWriteHisto(fTT, "JESMinus/Iso/", histname, sf_ttbar, fout, "ttbar_JESDown", true);
TH1F* ttbar_JERDown = readWriteHisto(fTT, "JERMinus/Iso/", histname, sf_ttbar, fout, "ttbar_JERDown", true);
TH1F* ttbar_topPtUp = readWriteHisto(fTT, "TopPtPlus/Iso/", histname, sf_ttbar, fout, "ttbar_topPtUp", true);
TH1F* ttbar_topPtDown = readWriteHisto(fTT, "TopPtMinus/Iso/", histname, sf_ttbar, fout, "ttbar_topPtDown", true);
TH1F* ttbar_bTagUp = readWriteHisto(fTT, "bTagPlus/Iso/", histname, sf_ttbar, fout, "ttbar_bTagUp", true);
TH1F* ttbar_bTagDown = readWriteHisto(fTT, "bTagMinus/Iso/", histname, sf_ttbar, fout, "ttbar_bTagDown", true);
TH1F* ttbar_cTagUp = readWriteHisto(fTT, "cTagPlus/Iso/", histname, sf_ttbar, fout, "ttbar_cTagUp", true);
TH1F* ttbar_cTagDown = readWriteHisto(fTT, "cTagMinus/Iso/", histname, sf_ttbar, fout, "ttbar_cTagDown", true);

//ttll
double sf_ttll = 0;
TH1F* ttll = readWriteHisto(fTT, "base/Iso/", histname, sf_ttll, fout, "ttll", true);
TH1F* ttll_JESUp = readWriteHisto(fTT, "JESPlus/Iso/", histname, sf_ttll, fout, "ttll_JESUp", true);
TH1F* ttll_JESDown = readWriteHisto(fTT, "JESMinus/Iso/", histname, sf_ttll, fout, "ttll_JESDown", true);
  
double sf_wh80_lumi = 1; 
TH1F* wh80_topPtweight = readWriteHisto(fWH80, "base/", "SF_topPtWeights", 1, fout, "topPtWeight"+label, false);
double sf_wh80 = sf_wh80_lumi/wh80_topPtweight->GetMean();
TH1F* wh80 = readWriteHisto(fWH80, "base/Iso/", histname, sf_wh80, fout, label, true);
TH1F* wh80_JESUp = readWriteHisto(fWH80, "JESPlus/Iso/", histname, sf_wh80, fout, label+"_JESUp", true);
TH1F* wh80_JERUp = readWriteHisto(fWH80, "JERPlus/Iso/", histname, sf_wh80, fout, label+"_JERUp", true);
TH1F* wh80_JESDown = readWriteHisto(fWH80, "JESMinus/Iso/", histname, sf_wh80, fout, label+"_JESDown", true);
TH1F* wh80_JERDown = readWriteHisto(fWH80, "JERMinus/Iso/", histname, sf_wh80, fout, label+"_JERDown", true);
TH1F* wh80_topPtUp = readWriteHisto(fWH80,  "TopPtPlus/Iso/", histname, sf_wh80, fout, label+"_topPtUp", true);
TH1F* wh80_topPtDown = readWriteHisto(fWH80, "TopPtMinus/Iso/", histname, sf_wh80, fout, label+"_topPtDown", true);
TH1F* wh80_bTagUp = readWriteHisto(fWH80, "bTagPlus/Iso/", histname, sf_wh80, fout, label+"_bTagUp", true);
TH1F* wh80_bTagDown = readWriteHisto(fWH80, "bTagMinus/Iso/", histname, sf_wh80, fout, label+"_bTagDown", true);
TH1F* wh80_cTagUp = readWriteHisto(fWH80, "cTagPlus/Iso/", histname, sf_wh80, fout, label+"_cTagUp", true);
TH1F* wh80_cTagDown = readWriteHisto(fWH80, "cTagMinus/Iso/", histname, sf_wh80, fout, label+"_cTagDown", true);

double sf_wh90_lumi = 1; 
TH1F* wh90_topPtweight = readWriteHisto(fWH90, "base/", "SF_topPtWeights", 1, fout, "topPtWeight"+label, false);
double sf_wh90 = sf_wh90_lumi/wh90_topPtweight->GetMean();
TH1F* wh90 = readWriteHisto(fWH90, "base/Iso/", histname, sf_wh90, fout, label, true);
TH1F* wh90_JESUp = readWriteHisto(fWH90, "JESPlus/Iso/", histname, sf_wh90, fout, label+"_JESUp", true);
TH1F* wh90_JERUp = readWriteHisto(fWH90, "JERPlus/Iso/", histname, sf_wh90, fout, label+"_JERUp", true);
TH1F* wh90_JESDown = readWriteHisto(fWH90, "JESMinus/Iso/", histname, sf_wh90, fout, label+"_JESDown", true);
TH1F* wh90_JERDown = readWriteHisto(fWH90, "JERMinus/Iso/", histname, sf_wh90, fout, label+"_JERDown", true);
TH1F* wh90_topPtUp = readWriteHisto(fWH90,  "TopPtPlus/Iso/", histname, sf_wh90, fout, label+"_topPtUp", true);
TH1F* wh90_topPtDown = readWriteHisto(fWH90, "TopPtMinus/Iso/", histname, sf_wh90, fout, label+"_topPtDown", true);
TH1F* wh90_bTagUp = readWriteHisto(fWH90, "bTagPlus/Iso/", histname, sf_wh90, fout, label+"_bTagUp", true);
TH1F* wh90_bTagDown = readWriteHisto(fWH90, "bTagMinus/Iso/", histname, sf_wh90, fout, label+"_bTagDown", true);
TH1F* wh90_cTagUp = readWriteHisto(fWH90, "cTagPlus/Iso/", histname, sf_wh90, fout, label+"_cTagUp", true);
TH1F* wh90_cTagDown = readWriteHisto(fWH90, "cTagMinus/Iso/", histname, sf_wh90, fout, label+"_cTagDown", true);

double sf_wh100_lumi = 1; 
TH1F* wh100_topPtweight = readWriteHisto(fWH100, "base/", "SF_topPtWeights", 1, fout, "topPtWeight"+label, false);
double sf_wh100 = sf_wh100_lumi/wh100_topPtweight->GetMean();
TH1F* wh100 = readWriteHisto(fWH100, "base/Iso/", histname, sf_wh100, fout, label, true);
TH1F* wh100_JESUp = readWriteHisto(fWH100, "JESPlus/Iso/", histname, sf_wh100, fout, label+"_JESUp", true);
TH1F* wh100_JERUp = readWriteHisto(fWH100, "JERPlus/Iso/", histname, sf_wh100, fout, label+"_JERUp", true);
TH1F* wh100_JESDown = readWriteHisto(fWH100, "JESMinus/Iso/", histname, sf_wh100, fout, label+"_JESDown", true);
TH1F* wh100_JERDown = readWriteHisto(fWH100, "JERMinus/Iso/", histname, sf_wh100, fout, label+"_JERDown", true);
TH1F* wh100_topPtUp = readWriteHisto(fWH100,  "TopPtPlus/Iso/", histname, sf_wh100, fout, label+"_topPtUp", true);
TH1F* wh100_topPtDown = readWriteHisto(fWH100, "TopPtMinus/Iso/", histname, sf_wh100, fout, label+"_topPtDown", true);
TH1F* wh100_bTagUp = readWriteHisto(fWH100, "bTagPlus/Iso/", histname, sf_wh100, fout, label+"_bTagUp", true);
TH1F* wh100_bTagDown = readWriteHisto(fWH100, "bTagMinus/Iso/", histname, sf_wh100, fout, label+"_bTagDown", true);
TH1F* wh100_cTagUp = readWriteHisto(fWH100, "cTagPlus/Iso/", histname, sf_wh100, fout, label+"_cTagUp", true);
TH1F* wh100_cTagDown = readWriteHisto(fWH100, "cTagMinus/Iso/", histname, sf_wh100, fout, label+"_cTagDown", true);

double sf_wh120_lumi = 1; 
TH1F* wh120_topPtweight = readWriteHisto(fWH120, "base/", "SF_topPtWeights", 1, fout, "topPtWeight"+label, false);
double sf_wh120 = sf_wh120_lumi/wh120_topPtweight->GetMean();
TH1F* wh120 = readWriteHisto(fWH120, "base/Iso/", histname, sf_wh120, fout, label, true);
TH1F* wh120_JESUp = readWriteHisto(fWH120, "JESPlus/Iso/", histname, sf_wh120, fout, label+"_JESUp", true);
TH1F* wh120_JERUp = readWriteHisto(fWH120, "JERPlus/Iso/", histname, sf_wh120, fout, label+"_JERUp", true);
TH1F* wh120_JESDown = readWriteHisto(fWH120, "JESMinus/Iso/", histname, sf_wh120, fout, label+"_JESDown", true);
TH1F* wh120_JERDown = readWriteHisto(fWH120, "JERMinus/Iso/", histname, sf_wh120, fout, label+"_JERDown", true);
TH1F* wh120_topPtUp = readWriteHisto(fWH120,  "TopPtPlus/Iso/", histname, sf_wh120, fout, label+"_topPtUp", true);
TH1F* wh120_topPtDown = readWriteHisto(fWH120, "TopPtMinus/Iso/", histname, sf_wh120, fout, label+"_topPtDown", true);
TH1F* wh120_bTagUp = readWriteHisto(fWH120, "bTagPlus/Iso/", histname, sf_wh120, fout, label+"_bTagUp", true);
TH1F* wh120_bTagDown = readWriteHisto(fWH120, "bTagMinus/Iso/", histname, sf_wh120, fout, label+"_bTagDown", true);
TH1F* wh120_cTagUp = readWriteHisto(fWH120, "cTagPlus/Iso/", histname, sf_wh120, fout, label+"_cTagUp", true);
TH1F* wh120_cTagDown = readWriteHisto(fWH120, "cTagMinus/Iso/", histname, sf_wh120, fout, label+"_cTagDown", true);

double sf_wh140_lumi = 1; 
TH1F* wh140_topPtweight = readWriteHisto(fWH140, "base/", "SF_topPtWeights", 1, fout, "topPtWeight"+label, false);
double sf_wh140 = sf_wh140_lumi/wh140_topPtweight->GetMean();
TH1F* wh140 = readWriteHisto(fWH140, "base/Iso/", histname, sf_wh140, fout, label, true);
TH1F* wh140_JESUp = readWriteHisto(fWH140, "JESPlus/Iso/", histname, sf_wh140, fout, label+"_JESUp", true);
TH1F* wh140_JERUp = readWriteHisto(fWH140, "JERPlus/Iso/", histname, sf_wh140, fout, label+"_JERUp", true);
TH1F* wh140_JESDown = readWriteHisto(fWH140, "JESMinus/Iso/", histname, sf_wh140, fout, label+"_JESDown", true);
TH1F* wh140_JERDown = readWriteHisto(fWH140, "JERMinus/Iso/", histname, sf_wh140, fout, label+"_JERDown", true);
TH1F* wh140_topPtUp = readWriteHisto(fWH140,  "TopPtPlus/Iso/", histname, sf_wh140, fout, label+"_topPtUp", true);
TH1F* wh140_topPtDown = readWriteHisto(fWH140, "TopPtMinus/Iso/", histname, sf_wh140, fout, label+"_topPtDown", true);
TH1F* wh140_bTagUp = readWriteHisto(fWH140, "bTagPlus/Iso/", histname, sf_wh140, fout, label+"_bTagUp", true);
TH1F* wh140_bTagDown = readWriteHisto(fWH140, "bTagMinus/Iso/", histname, sf_wh140, fout, label+"_bTagDown", true);
TH1F* wh140_cTagUp = readWriteHisto(fWH140, "cTagPlus/Iso/", histname, sf_wh140, fout, label+"_cTagUp", true);
TH1F* wh140_cTagDown = readWriteHisto(fWH140, "cTagMinus/Iso/", histname, sf_wh140, fout, label+"_cTagDown", true);

double sf_wh150_lumi = 1; 
TH1F* wh150_topPtweight = readWriteHisto(fWH150, "base/", "SF_topPtWeights", 1, fout, "topPtWeight"+label, false);
double sf_wh150 = sf_wh150_lumi/wh150_topPtweight->GetMean();
TH1F* wh150 = readWriteHisto(fWH150, "base/Iso/", histname, sf_wh150, fout, label, true);
TH1F* wh150_JESUp = readWriteHisto(fWH150, "JESPlus/Iso/", histname, sf_wh150, fout, label+"_JESUp", true);
TH1F* wh150_JERUp = readWriteHisto(fWH150, "JERPlus/Iso/", histname, sf_wh150, fout, label+"_JERUp", true);
TH1F* wh150_JESDown = readWriteHisto(fWH150, "JESMinus/Iso/", histname, sf_wh150, fout, label+"_JESDown", true);
TH1F* wh150_JERDown = readWriteHisto(fWH150, "JERMinus/Iso/", histname, sf_wh150, fout, label+"_JERDown", true);
TH1F* wh150_topPtUp = readWriteHisto(fWH150,  "TopPtPlus/Iso/", histname, sf_wh150, fout, label+"_topPtUp", true);
TH1F* wh150_topPtDown = readWriteHisto(fWH150, "TopPtMinus/Iso/", histname, sf_wh150, fout, label+"_topPtDown", true);
TH1F* wh150_bTagUp = readWriteHisto(fWH150, "bTagPlus/Iso/", histname, sf_wh150, fout, label+"_bTagUp", true);
TH1F* wh150_bTagDown = readWriteHisto(fWH150, "bTagMinus/Iso/", histname, sf_wh150, fout, label+"_bTagDown", true);
TH1F* wh150_cTagUp = readWriteHisto(fWH150, "cTagPlus/Iso/", histname, sf_wh150, fout, label+"_cTagUp", true);
TH1F* wh150_cTagDown = readWriteHisto(fWH150, "cTagMinus/Iso/", histname, sf_wh150, fout, label+"_cTagDown", true);

double sf_wh155_lumi = 1; 
TH1F* wh155_topPtweight = readWriteHisto(fWH155, "base/", "SF_topPtWeights", 1, fout, "topPtWeight"+label, false);
double sf_wh155 = sf_wh155_lumi/wh155_topPtweight->GetMean();
TH1F* wh155 = readWriteHisto(fWH155, "base/Iso/", histname, sf_wh155, fout, label, true);
TH1F* wh155_JESUp = readWriteHisto(fWH155, "JESPlus/Iso/", histname, sf_wh155, fout, label+"_JESUp", true);
TH1F* wh155_JERUp = readWriteHisto(fWH155, "JERPlus/Iso/", histname, sf_wh155, fout, label+"_JERUp", true);
TH1F* wh155_JESDown = readWriteHisto(fWH155, "JESMinus/Iso/", histname, sf_wh155, fout, label+"_JESDown", true);
TH1F* wh155_JERDown = readWriteHisto(fWH155, "JERMinus/Iso/", histname, sf_wh155, fout, label+"_JERDown", true);
TH1F* wh155_topPtUp = readWriteHisto(fWH155,  "TopPtPlus/Iso/", histname, sf_wh155, fout, label+"_topPtUp", true);
TH1F* wh155_topPtDown = readWriteHisto(fWH155, "TopPtMinus/Iso/", histname, sf_wh155, fout, label+"_topPtDown", true);
TH1F* wh155_bTagUp = readWriteHisto(fWH155, "bTagPlus/Iso/", histname, sf_wh155, fout, label+"_bTagUp", true);
TH1F* wh155_bTagDown = readWriteHisto(fWH155, "bTagMinus/Iso/", histname, sf_wh155, fout, label+"_bTagDown", true);
TH1F* wh155_cTagUp = readWriteHisto(fWH155, "cTagPlus/Iso/", histname, sf_wh155, fout, label+"_cTagUp", true);
TH1F* wh155_cTagDown = readWriteHisto(fWH155, "cTagMinus/Iso/", histname, sf_wh155, fout, label+"_cTagDown", true);

double sf_wh160_lumi = 1; 
TH1F* wh160_topPtweight = readWriteHisto(fWH160, "base/", "SF_topPtWeights", 1, fout, "topPtWeight"+label, false);
double sf_wh160 = sf_wh160_lumi/wh160_topPtweight->GetMean();
TH1F* wh160 = readWriteHisto(fWH160, "base/Iso/", histname, sf_wh160, fout, label, true);
TH1F* wh160_JESUp = readWriteHisto(fWH160, "JESPlus/Iso/", histname, sf_wh160, fout, label+"_JESUp", true);
TH1F* wh160_JERUp = readWriteHisto(fWH160, "JERPlus/Iso/", histname, sf_wh160, fout, label+"_JERUp", true);
TH1F* wh160_JESDown = readWriteHisto(fWH160, "JESMinus/Iso/", histname, sf_wh160, fout, label+"_JESDown", true);
TH1F* wh160_JERDown = readWriteHisto(fWH160, "JERMinus/Iso/", histname, sf_wh160, fout, label+"_JERDown", true);
TH1F* wh160_topPtUp = readWriteHisto(fWH160,  "TopPtPlus/Iso/", histname, sf_wh160, fout, label+"_topPtUp", true);
TH1F* wh160_topPtDown = readWriteHisto(fWH160, "TopPtMinus/Iso/", histname, sf_wh160, fout, label+"_topPtDown", true);
TH1F* wh160_bTagUp = readWriteHisto(fWH160, "bTagPlus/Iso/", histname, sf_wh160, fout, label+"_bTagUp", true);
TH1F* wh160_bTagDown = readWriteHisto(fWH160, "bTagMinus/Iso/", histname, sf_wh160, fout, label+"_bTagDown", true);
TH1F* wh160_cTagUp = readWriteHisto(fWH160, "cTagPlus/Iso/", histname, sf_wh160, fout, label+"_cTagUp", true);
TH1F* wh160_cTagDown = readWriteHisto(fWH160, "cTagMinus/Iso/", histname, sf_wh160, fout, label+"_cTagDown", true);

//w+jets
double sf_wjet = 1;
TH1F* wjet = readWriteHisto(fWJ, "base/Iso/", histname, sf_wjet, fout, "wjet", true);
TH1F* wjet_JESUp = readWriteHisto(fWJ, "JESPlus/Iso/", histname, sf_wjet, fout, "wjet_JESUp", true);
TH1F* wjet_JERUp = readWriteHisto(fWJ, "JERPlus/Iso/", histname, sf_wjet, fout, "wjet_JERUp", true);
TH1F* wjet_JESDown = readWriteHisto(fWJ, "JESMinus/Iso/", histname, sf_wjet, fout, "wjet_JESDown", true);
TH1F* wjet_JERDown = readWriteHisto(fWJ, "JERMinus/Iso/", histname, sf_wjet, fout, "wjet_JERDown", true);
TH1F* wjet_bTagUp = readWriteHisto(fWJ, "bTagPlus/Iso/", histname, sf_wjet, fout, "wjet_bTagUp", true);
TH1F* wjet_bTagDown = readWriteHisto(fWJ, "bTagMinus/Iso/", histname, sf_wjet, fout, "wjet_bTagDown", true); 
TH1F* wjet_cTagUp = readWriteHisto(fWJ, "cTagPlus/Iso/", histname, sf_wjet, fout, "wjet_cTagUp", true);
TH1F* wjet_cTagDown = readWriteHisto(fWJ, "cTagMinus/Iso/", histname, sf_wjet, fout, "wjet_cTagDown", true); 

//Z+Jets
double sf_zjet = 1;
TH1F* zjet = readWriteHisto(fDY, "base/Iso/", histname, sf_zjet, fout, "zjet", true);
TH1F* zjet_JESUp = readWriteHisto(fDY, "JESPlus/Iso/", histname, sf_zjet, fout, "zjet_JESUp", true);
TH1F* zjet_JERUp = readWriteHisto(fDY, "JERPlus/Iso/", histname, sf_zjet, fout, "zjet_JERUp", true);
TH1F* zjet_JESDown = readWriteHisto(fDY, "JESMinus/Iso/", histname, sf_zjet, fout, "zjet_JESDown", true);
TH1F* zjet_JERDown = readWriteHisto(fDY, "JERMinus/Iso/", histname, sf_zjet, fout, "zjet_JERDown", true);
TH1F* zjet_bTagUp = readWriteHisto(fDY, "bTagPlus/Iso/", histname, sf_zjet, fout, "zjet_bTagUp", true);
TH1F* zjet_bTagDown = readWriteHisto(fDY, "bTagMinus/Iso/", histname, sf_zjet, fout, "zjet_bTagDown", true);
TH1F* zjet_cTagUp = readWriteHisto(fDY, "cTagPlus/Iso/", histname, sf_zjet, fout, "zjet_cTagUp", true);
TH1F* zjet_cTagDown = readWriteHisto(fDY, "cTagMinus/Iso/", histname, sf_zjet, fout, "zjet_cTagDown", true);

//SingleTop
double sf_stop = 1;
TH1F* stop = readWriteHisto(fST, "base/Iso/", histname, sf_stop, fout, "stop", true);
TH1F* stop_JESUp = readWriteHisto(fST, "JESPlus/Iso/", histname, sf_stop, fout, "stop_JESUp", true);
TH1F* stop_JERUp = readWriteHisto(fST, "JERPlus/Iso/", histname, sf_stop, fout, "stop_JERUp", true);
TH1F* stop_JESDown = readWriteHisto(fST, "JESMinus/Iso/", histname, sf_stop, fout, "stop_JESDown", true);
TH1F* stop_JERDown = readWriteHisto(fST, "JERMinus/Iso/", histname, sf_stop, fout, "stop_JERDown", true);
TH1F* stop_bTagUp = readWriteHisto(fST, "bTagPlus/Iso/", histname, sf_stop, fout, "stop_bTagUp", true);
TH1F* stop_bTagDown = readWriteHisto(fST, "bTagMinus/Iso/", histname, sf_stop, fout, "stop_bTagDown", true);
TH1F* stop_cTagUp = readWriteHisto(fST, "cTagPlus/Iso/", histname, sf_stop, fout, "stop_cTagUp", true);
TH1F* stop_cTagDown = readWriteHisto(fST, "cTagMinus/Iso/", histname, sf_stop, fout, "stop_cTagDown", true);

//Dibosons
double sf_diboson = 1;
TH1F* diboson = readWriteHisto(fVV, "base/Iso/", histname, sf_diboson, fout, "diboson", true);
TH1F* diboson_JESUp = readWriteHisto(fVV, "JESPlus/Iso/", histname, sf_diboson, fout, "diboson_JESUp", true);
TH1F* diboson_JERUp = readWriteHisto(fVV, "JERPlus/Iso/", histname, sf_diboson, fout, "diboson_JERUp", true);
TH1F* diboson_JESDown = readWriteHisto(fVV, "JESMinus/Iso/", histname, sf_diboson, fout, "diboson_JESDown", true);
TH1F* diboson_JERDown = readWriteHisto(fVV, "JERMinus/Iso/", histname, sf_diboson, fout, "diboson_JERDown", true);
TH1F* diboson_bTagUp = readWriteHisto(fVV, "bTagPlus/Iso/", histname, sf_diboson, fout, "diboson_bTagUp", true);
TH1F* diboson_bTagDown = readWriteHisto(fVV, "bTagMinus/Iso/", histname, sf_diboson, fout, "diboson_bTagDown", true);
TH1F* diboson_cTagUp = readWriteHisto(fVV, "cTagPlus/Iso/", histname, sf_diboson, fout, "diboson_cTagUp", true);
TH1F* diboson_cTagDown = readWriteHisto(fVV, "cTagMinus/Iso/", histname, sf_diboson, fout, "diboson_cTagDown", true);

//QCD MC
double sf_qcd = 1;
TH1F* qcd = readWriteHisto(fQCD, "base/Iso/", histname, sf_qcd, fout, "qcd", true);
TH1F* qcd_JESUp = readWriteHisto(fQCD, "JESPlus/Iso/", histname, sf_qcd, fout, "qcd_JESUp", true);
TH1F* qcd_JERUp = readWriteHisto(fQCD, "JERPlus/Iso/", histname, sf_qcd, fout, "qcd_JERUp", true);
TH1F* qcd_JESDown = readWriteHisto(fQCD, "JESMinus/Iso/", histname, sf_qcd, fout, "qcd_JESDown", true);
TH1F* qcd_JERDown = readWriteHisto(fQCD, "JERMinus/Iso/", histname, sf_qcd, fout, "qcd_JERDown", true);
TH1F* qcd_bTagUp = readWriteHisto(fQCD, "bTagPlus/Iso/", histname, sf_qcd, fout, "qcd_bTagUp", true);
TH1F* qcd_bTagDown = readWriteHisto(fQCD, "bTagMinus/Iso/", histname, sf_qcd, fout, "qcd_bTagDown", true);
TH1F* qcd_cTagUp = readWriteHisto(fQCD, "cTagPlus/Iso/", histname, sf_qcd, fout, "qcd_cTagUp", true);
TH1F* qcd_cTagDown = readWriteHisto(fQCD, "cTagMinus/Iso/", histname, sf_qcd, fout, "qcd_cTagDown", true);
//QCD data driven
TH1F* qcd_dd = readWriteHisto(fQCD_dd, "base/Iso/", histname, sf_qcd, fout, "qcd", true);

//Data
double sf_data = 1; //should be 1, always
TH1F* data_obs = readWriteHisto(fData, "base/Iso/", histname, sf_data, fout, "data_obs", true);

outFile<<"\\begin{table}"<<endl;
outFile<<"\\begin{center}"<<endl;  
//outFile<<"\\begin{LARGE}"<<endl;  
outFile<<"\\begin{tabular}{|l|c|c|c|c|c|c|c|c|c|}"<<endl;  
outFile<<"\\hline "<<endl; 
outFile<<"Process & "<<"base & "<<"JESUp & "<<"JESDown & "<<"JERUp & "<<"JERDown & "<<"bTagUp & "<<"bTagDown & "<<"cTagUp & "<<"cTagDown "<< "\\\\ "<<endl;
outFile<<"\\hline "<<endl; 
outFile<<"\\hline "<<endl;

getSysEffectRow(outFile, "ttbar + jets", ttbar, ttbar_JESUp, ttbar_JESDown, ttbar_JERUp, ttbar_JERDown, ttbar_bTagUp, ttbar_bTagDown, ttbar_cTagUp, ttbar_cTagDown);
outFile<<"\\hline "<<endl;    

getSysEffectRow(outFile, "W + jets", wjet, wjet_JESUp, wjet_JESDown, wjet_JERUp, wjet_JERDown, wjet_bTagUp, wjet_bTagDown, wjet_cTagUp, wjet_cTagDown);
outFile<<"\\hline "<<endl;    

getSysEffectRow(outFile, "DY + jets", zjet, zjet_JESUp, zjet_JESDown, zjet_JERUp, zjet_JERDown, zjet_bTagUp, zjet_bTagDown, zjet_cTagUp, zjet_cTagDown);
outFile<<"\\hline "<<endl;    

getSysEffectRow(outFile, "Single t", stop, stop_JESUp, stop_JESDown, stop_JERUp, stop_JERDown, stop_bTagUp, stop_bTagDown, stop_cTagUp, stop_cTagDown);
outFile<<"\\hline "<<endl;    

getSysEffectRow(outFile, "VV", diboson, diboson_JESUp, diboson_JESDown, diboson_JERUp, diboson_JERDown, diboson_bTagUp, diboson_bTagDown, diboson_cTagUp, diboson_cTagDown);
outFile<<"\\hline "<<endl;    

getSysEffectRow(outFile, "MC QCD", qcd, qcd_JESUp, qcd_JESDown, qcd_JERUp, qcd_JERDown, qcd_bTagUp, qcd_bTagDown, qcd_cTagUp, qcd_cTagDown);
outFile<<"\\hline "<<endl;    

getSysEffectRow(outFile, "WH80", wh80, wh80_JESUp, wh80_JESDown, wh80_JERUp, wh80_JERDown, wh80_bTagUp, wh80_bTagDown, wh80_cTagUp, wh80_cTagDown);
outFile<<"\\hline "<<endl;    

getSysEffectRow(outFile, "WH90", wh90, wh90_JESUp, wh90_JESDown, wh90_JERUp, wh90_JERDown, wh90_bTagUp, wh90_bTagDown, wh90_cTagUp, wh90_cTagDown);
outFile<<"\\hline "<<endl;    

getSysEffectRow(outFile, "WH100", wh100, wh100_JESUp, wh100_JESDown, wh100_JERUp, wh100_JERDown, wh100_bTagUp, wh100_bTagDown, wh100_cTagUp, wh100_cTagDown);
outFile<<"\\hline "<<endl;    

getSysEffectRow(outFile, "WH120", wh120, wh120_JESUp, wh120_JESDown, wh120_JERUp, wh120_JERDown, wh120_bTagUp, wh120_bTagDown, wh120_cTagUp, wh120_cTagDown);
outFile<<"\\hline "<<endl;    

getSysEffectRow(outFile, "WH140", wh140, wh140_JESUp, wh140_JESDown, wh140_JERUp, wh140_JERDown, wh140_bTagUp, wh140_bTagDown, wh140_cTagUp, wh140_cTagDown);
outFile<<"\\hline "<<endl;    

getSysEffectRow(outFile, "WH150", wh150, wh150_JESUp, wh150_JESDown, wh150_JERUp, wh150_JERDown, wh150_bTagUp, wh150_bTagDown, wh150_cTagUp, wh150_cTagDown);
outFile<<"\\hline "<<endl;    

getSysEffectRow(outFile, "WH155", wh155, wh155_JESUp, wh155_JESDown, wh155_JERUp, wh155_JERDown, wh155_bTagUp, wh155_bTagDown, wh155_cTagUp, wh155_cTagDown);
outFile<<"\\hline "<<endl;    

getSysEffectRow(outFile, "WH160", wh160, wh160_JESUp, wh160_JESDown, wh160_JERUp, wh160_JERDown, wh160_bTagUp, wh160_bTagDown, wh160_cTagUp, wh160_cTagDown);
outFile<<"\\hline "<<endl;    

outFile<<"\\end{tabular}"<<endl; 
//outFile<<"\\end{LARGE}"<<endl;  
outFile<<"\\end{center}"<<endl;
outFile<<"\\caption{For "<<label<<"$."<< " Change due to sys w.r.t. base = $\\frac{(sys - base)\\times 100}{base} .$}"<<endl;
outFile<<"\\end{table}"<<endl;
}

void binMigrationEffect(){
  ofstream outFile; 
  outFile.open("sysEffectOnYields.tex"); 
  //outFile<<"\\documentclass[landscape,letterpaper]{article}"<<endl;  
  outFile<<"\\documentclass[landscape]{article}"<<endl;  
  outFile<<"\\pagestyle{empty}"<<endl;  
  outFile<<"\\usepackage{epsfig}"<<endl;  
  outFile<<"\\usepackage{amsmath}"<<endl;  
  outFile<<"\\usepackage{array}"<<endl;  
  outFile<<"\\usepackage{multirow}"<<endl;  
  outFile<<"\\usepackage[cm]{fullpage}"<<endl;  
  outFile<<"\\textheight = 8.in"<<endl;  
  outFile<<"\\textwidth 7.0in"<<endl;  
  outFile<<"\\begin{document}"<<endl;  
  outFile<<""<<endl;
  getSysEffectTable(outFile, "KinFit/mjj_kfit", "mjj_Inc");
  getSysEffectTable(outFile, "KinFit/mjj_kfit_CTagL_SF_Cat", "mjj_CTagL");
  getSysEffectTable(outFile, "KinFit/mjj_kfit_CTagM_SF_Cat", "mjj_CTagM");
  getSysEffectTable(outFile, "KinFit/mjj_kfit_CTagT_SF_Cat", "mjj_CTagT");
  
  outFile<<"\\end{document}"<<endl;  
  outFile.close();
}

