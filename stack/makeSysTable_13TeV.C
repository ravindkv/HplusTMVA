#include <iostream>
#include <fstream>
#include <iomanip>

bool isMuChannel = true;
bool isEleChannel = false;
TString inFile("$PWD/");
TFile *fWH80 	  		= new TFile(inFile+"all_Hplus80.root");
TFile *fWH90 	  		= new TFile(inFile+"all_Hplus90.root");
TFile *fWH100 	  		= new TFile(inFile+"all_Hplus100.root");
TFile *fWH120 	  		= new TFile(inFile+"all_Hplus120.root");
TFile *fWH140 	  		= new TFile(inFile+"all_Hplus140.root");
TFile *fWH150 	  		= new TFile(inFile+"all_Hplus150.root");
TFile *fWH155 	  		= new TFile(inFile+"all_Hplus155.root");
TFile *fWH160 	  		= new TFile(inFile+"all_Hplus160.root");

TFile *fTT    		    = new TFile(inFile+"all_TTJetsP.root");
TFile *fWJ  			= new TFile(inFile+"all_WJets.root");
TFile *fDY  			= new TFile(inFile+"all_DY.root");
TFile *fQCD  			= new TFile(inFile+"all_QCD.root");
TFile *fQCD_dd			= new TFile(inFile+"all_QCD_dd.root");
TFile *fST  			= new TFile(inFile+"all_ST.root");
TFile *fVV 	        	= new TFile(inFile+"all_VV.root");
TFile *fData            = new TFile(inFile+"all_Data.root");

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
    if(!(fTT->Get("base/"+isoDir+histDir+histName))) //to initialise an empty hist
       throw  exception_msg.c_str();
  }catch (const char *e){
    cout<<"\033[01;31mERROR: \033[0m"<<e<< endl;
    exit(0);
  }
  if(!(inRootFile->Get(fullPath))){
    hist = (TH1F*)(fTT->Get("base/Iso/"+histDir+histName))->Clone(histName); //to initialise an empty hist
    hist->Reset();
  }else hist = (TH1F*)(inRootFile->Get(fullPath))->Clone(histName);
  return hist;
}

void makeSysRow(ofstream & outFile, TFile *inFile, TString histDir, TString histName, TString rowLable, double uncXss, bool isSignal, bool isQCD){
 TH1F* hBase = getHisto(inFile, "base/", "Iso/", histDir, histName);
 if(isSignal){
   TH1F* hJESPlus     = getHisto(inFile, "JESPlus/", "Iso/", histDir, histName);
   TH1F* hJESMinus    = getHisto(inFile, "JESMinus/", "Iso/", histDir, histName);
   TH1F* hPileupPlus  = getHisto(inFile, "PileupPlus/", "Iso/", histDir, histName);
   TH1F* hPileupMinus = getHisto(inFile, "PileupMinus/", "Iso/", histDir, histName);
   TH1F* hJERPlus     = getHisto(inFile, "JERPlus/", "Iso/", histDir, histName);
   TH1F* hJERMinus    = getHisto(inFile, "JERMinus/", "Iso/", histDir, histName);
   TH1F* hbcTagPlus1  = getHisto(inFile, "bcTagPlus1/", "Iso/", histDir, histName);
   TH1F* hbcTagMinus1 = getHisto(inFile, "bcTagMinus1/", "Iso/", histDir, histName);
   TH1F* hbcTagPlus2  = getHisto(inFile, "bcTagPlus2/", "Iso/", histDir, histName);
   TH1F* hbcTagMinus2 = getHisto(inFile, "bcTagMinus2/", "Iso/", histDir, histName);
   TH1F* hbcTagPlus3  = getHisto(inFile, "bcTagPlus3/", "Iso/", histDir, histName);
   TH1F* hbcTagMinus3 = getHisto(inFile, "bcTagMinus3/", "Iso/", histDir, histName);
   TH1F* hTopPtPlus   = getHisto(inFile, "TopPtPlus/", "Iso/", histDir, histName);
   TH1F* hTopPtMinus  = getHisto(inFile, "TopPtMinus/", "Iso/", histDir, histName);
   outFile<<rowLable<< " & "<<2.5<< std::setprecision(2)<<
	  " &  "<< relSysUncBCTag(hBase, hPileupPlus, hPileupMinus)<<
	  " &  "<<3.0<< " & "<<relSysUncJetMET( hJESPlus, hBase,
	            hJESMinus, hJERPlus, hJERMinus) <<
	  " &  "<< relSysUncBCTag(hbcTagPlus1, hBase, hbcTagMinus1) <<
	  " &  "<<relSysUncBCTag(hbcTagPlus2, hBase, hbcTagMinus2)<<
	  " &  "<<relSysUncBCTag(hbcTagPlus3, hBase, hbcTagMinus3)<<
	  " &  "<<uncXss<<" & "<<relStatUnc(hBase)<<
	  " &  "<<relSysUncTopPt(hBase, hTopPtPlus, hTopPtMinus)<<
	  " \\\\[0.1cm] "<<endl;
 }
 else if(isQCD){
     outFile<<"QCD"<< " & -"<<
	  " &  "<<"-"<<
	  " &  "<<"-"<<
	  " &  "<<"-"<<
	  " &  "<<"-"<<
	  " &  "<<"-"<<
	  " &  "<<"-"<<
	  //" &  "<<uncXss<<" & "<<relStatUnc(hBase)<<
	  " &  "<<"Q"<<" & "<<relStatUnc(hBase)<<
	  " &  "<<"-"<<
	  " \\\\[0.1cm] \\hline"<<endl;
 }
 else{
   TH1F* hJESPlus     = getHisto(inFile, "JESPlus/", "Iso/", histDir, histName);
   TH1F* hJESMinus    = getHisto(inFile, "JESMinus/", "Iso/", histDir, histName);
   TH1F* hPileupPlus  = getHisto(inFile, "PileupPlus/", "Iso/", histDir, histName);
   TH1F* hPileupMinus = getHisto(inFile, "PileupMinus/", "Iso/", histDir, histName);
   TH1F* hJERPlus     = getHisto(inFile, "JERPlus/", "Iso/", histDir, histName);
   TH1F* hJERMinus    = getHisto(inFile, "JERMinus/", "Iso/", histDir, histName);
   TH1F* hbcTagPlus1  = getHisto(inFile, "bcTagPlus1/", "Iso/", histDir, histName);
   TH1F* hbcTagMinus1 = getHisto(inFile, "bcTagMinus1/", "Iso/", histDir, histName);
   TH1F* hbcTagPlus2  = getHisto(inFile, "bcTagPlus2/", "Iso/", histDir, histName);
   TH1F* hbcTagMinus2 = getHisto(inFile, "bcTagMinus2/", "Iso/", histDir, histName);
   TH1F* hbcTagPlus3  = getHisto(inFile, "bcTagPlus3/", "Iso/", histDir, histName);
   TH1F* hbcTagMinus3 = getHisto(inFile, "bcTagMinus3/", "Iso/", histDir, histName);
   outFile<<rowLable<< " & "<<2.5<< std::setprecision(2)<<
	  " &  "<< relSysUncBCTag(hBase, hPileupPlus, hPileupMinus)<<
	  " &  "<<3.0<< " & "<<relSysUncJetMET( hJESPlus, hBase,
	            hJESMinus, hJERPlus, hJERMinus) <<
	  " &  "<< relSysUncBCTag(hbcTagPlus1, hBase, hbcTagMinus1) <<
	  " &  "<<relSysUncBCTag(hbcTagPlus2, hBase, hbcTagMinus2)<<
	  " &  "<<relSysUncBCTag(hbcTagPlus3, hBase, hbcTagMinus3)<<
	  " &  "<<uncXss<<" & "<<relStatUnc(hBase)<< " & " <<"-"<<
	  " \\\\[0.1cm] "<<endl;
 }
}

void makeOneSysTable(ofstream & outFile, TString histDir, TString histName, TString catName){
  string tableName = "";
  if(isMuChannel) tableName = "Systematics unc in \\% for muon channel,"+ catName;
  if(isEleChannel) tableName = "Systematics unc in \\% for electron channel,"+ catName;
  outFile<<"\\begin{table}"<<endl;
  outFile<<"\\begin{center}"<<endl;
  //outFile<<"%\\begin{LARGE}"<<endl;
  ///outFile<<"\\footnotesize\\setlength{\\tabcolsep}{0.3pt}"<<endl;
  outFile<<"\\begin{tabular}{  c c c c c c c c c c c c c cc}"<<endl;
  outFile<<"\\multicolumn{5}{c}{ } \\\\"<<endl;
  outFile<<"\\hline "<<endl;
  outFile<<"\\hline "<<endl;
  outFile<<"\\multicolumn{1}{ p{2cm} }{Process } & \\multicolumn{1}{ p{0.8cm}}{\\rotatebox{90}{Luminosity}} & \\multicolumn{1}{ p{0.8cm}}{\\rotatebox{90}{Pileup reweighting} } & \\multicolumn{1}{ p{0.8cm}}{\\rotatebox{90}{Lepton selections}} & \\multicolumn{1}{ p{0.8cm}}{\\rotatebox{90}{JES+JER+MET}} & \\multicolumn{1}{ p{0.8cm}}{ \\rotatebox{90}{b/c-jet tagging-1} }  & \\multicolumn{1}{ p{0.8cm}}{ \\rotatebox{90}{b/c-jet tagging-2} } & \\multicolumn{1}{ p{0.8cm}}{ \\rotatebox{90}{b/c-jet tagging-3}}& \\multicolumn{1}{ p{0.8cm}}{ \\rotatebox{90}{Normalization}  }& \\multicolumn{1}{ p{0.8cm}}{\\rotatebox{90}{MC Statistics}  } & \\multicolumn{1}{ p{0.8cm}}{\\rotatebox{90}{Top-Pt reweighting} }  \\\\ "<<endl;
  outFile<<"\\hline "<<endl;
  outFile<<"\\hline "<<endl;
  makeSysRow(outFile, fWH80, histDir, histName, "MC signal ($M_{H^\\pm}=80$ GeV)", 6.1, true, false);
  makeSysRow(outFile, fWH90, histDir, histName, "MC signal ($M_{H^\\pm}=90$ GeV)", 6.1, true, false);
  makeSysRow(outFile, fWH100, histDir, histName, "MC signal ($M_{H^\\pm}=100$ GeV)", 6.1, true, false);
  makeSysRow(outFile, fWH120, histDir, histName, "MC signal ($M_{H^\\pm}=120$ GeV)", 6.1, true, false);
  makeSysRow(outFile, fWH140, histDir, histName, "MC signal ($M_{H^\\pm}=140$ GeV)", 6.1, true, false);
  makeSysRow(outFile, fWH150, histDir, histName, "MC signal ($M_{H^\\pm}=150$ GeV)", 6.1, true, false);
  makeSysRow(outFile, fWH155, histDir, histName, "MC signal ($M_{H^\\pm}=155$ GeV)", 6.1, true, false);
  makeSysRow(outFile, fWH160, histDir, histName, "MC signal ($M_{H^\\pm}=160$ GeV)", 6.1, true, false);
  outFile<<"\\hline "<<endl;
  makeSysRow(outFile, fTT, histDir, histName, "$t\\bar{t} + jets$", 6.1, true, false);
  makeSysRow(outFile, fST, histDir, histName, "Single ~t", 5.0, false, false);
  makeSysRow(outFile, fWJ, histDir, histName, "W+jets", 5.0, false, false);
  makeSysRow(outFile, fDY, histDir, histName, "$Z/\\gamma$ + jets", 4.5, false, false);
  makeSysRow(outFile, fVV, histDir, histName, "VV", 4.0, false, false);
  makeSysRow(outFile, fQCD_dd, histDir, histName, "QCD", 60, false, true);
  outFile<<"\\hline "<<endl;
  outFile<<"\\end{tabular}"<<endl;
  //outFile<<"\\end{LARGE}"<<endl;
  outFile<<"\\end{center}"<<endl;
  outFile<<"\\caption{"+tableName+"}"<<endl;
  outFile<<"\\end{table}"<<endl;
}

void makeSysTable_13TeV(TString histSubDir="Iso/", TString histName="mjj_kfit"){
  ofstream outFile;
  string outName = "sysTable.tex";
  if(isMuChannel) outName = "sysTable_mu.tex";
  if(isEleChannel) outName = "sysTable_ele.tex";
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
  outFile<<""<<endl;
  makeOneSysTable(outFile, "KinFit/", "mjj_kfit", " from inclusive category");
  makeOneSysTable(outFile, "KinFit/", "mjj_kfit_CTagExL", " from exclusive loose charm-category");
  makeOneSysTable(outFile, "KinFit/", "mjj_kfit_CTagExM", " from exclusive medium charm-category");
  makeOneSysTable(outFile, "KinFit/", "mjj_kfit_CTagExT", " from exclusive tight charm-category");
  outFile<<"\\end{document}"<<endl;
  outFile.close();
}
