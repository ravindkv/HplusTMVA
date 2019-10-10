#include <iostream>
#include <fstream>
#include <iomanip>

void makeCutFlowTable(bool NOTANPAS = false)
{
  TString inFile("$PWD/");

  cout << "inFile  " << inFile << endl;

  TFile *ttbar = new TFile(inFile+"all_TTJetsP.root");
  TH1F* h_ttbar = (TH1F*)ttbar->Get("base/Iso/cutflow")->Clone("h_ttbar");

  TH1F* httbar_toppt = (TH1F*)ttbar->Get("base/SF_topPtWeights"); 
  double avgTop = httbar_toppt->GetMean();
  double wh_scale = 0.32; // 2x(1-x) assuming x = 0.2  
  h_ttbar->Scale(1.0/avgTop);

  ofstream outFile;
  outFile.open("muon_cutflow.tex");
  outFile<< fixed << showpoint <<setprecision(1);
  if(NOTANPAS){
    outFile<<"\\documentclass[landscape,letterpaper]{article}"<<endl; 
    outFile<<"\\pagestyle{empty}"<<endl; 
    outFile<<"\\usepackage{epsfig}"<<endl; 
    outFile<<"\\usepackage{amsmath}"<<endl; 
    outFile<<"\\usepackage{array}"<<endl; 
    outFile<<"\\usepackage{multirow}"<<endl; 
    outFile<<"\\usepackage[cm]{fullpage}"<<endl; 
    outFile<<"\\textheight = 8.in"<<endl; 
    outFile<<"\\textwidth 7.0in"<<endl; 
    outFile<<"\\setlength{\\topmargin}{-.5in}"<<endl;
    outFile<<"\\setlength{\\textheight}{9in}"<<endl;
    outFile<<"\\setlength{\\oddsidemargin}{-.875in}"<<endl;
    
    outFile<<"\\begin{document}"<<endl; 
    outFile<<"Electron $p_T$ $\\ge$ 25 GeV,  $|\\eta|$ $<$ 2.5 ,$~~$ Jet  $p_T$ $\\ge$ 30 GeV, $|\\eta|$ $<$ 2.5 and 4 jets"<<" \\\\ "<<endl;
    outFile<<"$\\not\\!\\!E_T \\ge 20GeV $"<<" \\\\ "<< endl;
    outFile<<" With pt $\\ge$ 25 GeV in Kinematic fit and also applied MET px, py correction" << " \\\\ "<< endl;
    outFile<<"2 btag jet(2 Medium )  working point "<<" \\\\ "<<endl;
    outFile<<" Luminosity for full 2012 is 19.7 inv fb"<<" \\\\ "<<endl;
  }
  outFile<<"\\begin{center}"<<endl; 
  outFile<<"%\\begin{LARGE}"<<endl; 
  outFile<<"\\begin{tabular}{ | c| c| c| c| c|}"<<endl; 
  outFile<<"\\multicolumn{5}{c}{ } \\\\"<<endl; 
  outFile<<"\\hline "<<endl;
  outFile<<"\\multicolumn{1}{| c|}{ } & \\multicolumn{1}{ c|}{ $N_{electron}=1$ } & \\multicolumn{1}{ c|}{ $N_{jets}\\ge 4$ } & \\multicolumn{1}{ c|}{ $\\not\\!\\!E_T \\ge 20GeV$ }  &\\multicolumn{1}{ c |}{ $\\ge$ 2btag } \\\\ "<<endl;
  outFile<<"\\hline "<<endl;
  outFile<<"\\hline "<<endl;

  outFile<<"SM $t\\bar{t}$"<<" & "<<h_ttbar->GetBinContent(2)<<" & "<<h_ttbar->GetBinContent(3)<<" & "<<h_ttbar->GetBinContent(4)<<" & "<<h_ttbar->GetBinContent(5)<<" \\\\ "<<endl;
  outFile<<"\\hline "<<endl;
  
  outFile<<"\\end{tabular}"<<endl;
  //outFile<<"%\\end{LARGE}"<<endl; 
  outFile<<"\\end{center}"<<endl; 
  if(NOTANPAS){
    outFile<<"\\end{document}"<<endl;
  }
  outFile.close();

}
string printCutFlowHist(string histname, TH1F *h, int Nbin, double sf){
   string allBinValue = histname;
   for(int i =1; i<Nbin; i++){
     ostringstream convert;
     string Result("");
     //allBinValue += "h->GetBinContent(i)" + " & ";
     convert <<sf*h->GetBinContent(i);
     Result = convert.str(); 
     allBinValue += " & "+Result;
   }
   return allBinValue ;
}

void makeCutFlowTableAny(ofstream &outFile, string sys, int Nbin, 
		TH1F *h_wh,
		TH1F *h_ttbar,
		TH1F *h_stop,
		TH1F *h_wjets,
		TH1F *h_dyjets,
		TH1F *h_qcd,
		TH1F *h_st,
		TH1F *h_vv,
		TH1F *h_data){
  outFile<<""<<endl;
  outFile<<"%%%%%%%%%%%%%%%%%% NEXT TABLE: "+sys+" %%%%%%%%%%%%%%%%%"<<endl;
  outFile<<"\\begin{table}"<<endl; 
  outFile<<"\\begin{center}"<<endl; 
  //outFile<<"%\\begin{LARGE}"<<endl;
  outFile<<"\\footnotesize\\setlength{\\tabcolsep}{2.8pt}"<<endl;
  outFile<<"\\begin{tabular}{ | c| c| c| c| c| c| c| c| c| c| c| c| c|c|}"<<endl; 
  outFile<<"\\multicolumn{5}{c}{ } \\\\"<<endl; 
  outFile<<"\\hline "<<endl;
  outFile<<"\\multicolumn{1}{| c|}{"+ sys +" } & \\multicolumn{1}{ c|}{ $HLT\\_IsoMu24$ } & \\multicolumn{1}{ c|}{ $N_{muon}=1$ } & \\multicolumn{1}{ c|}{ $N_{ele}=0$} & \\multicolumn{1}{ c|}{ Muon SF } & \\multicolumn{1}{ c|}{ $\\mu^{Iso} < 0.15$ } &\\multicolumn{1}{ c|}{ $N_{jets}\\ge 4$ } & \\multicolumn{1}{ c|}{ $\\not\\!\\!E_T \\ge 20GeV$ }&  \\multicolumn{1}{ c|}{MT $\\ge$ 20 GeV} & \\multicolumn{1}{ c |}{ $\\ge$ 2btag }& \\multicolumn{1}{ c |}{ BTag SF }& \\multicolumn{1}{ c|}{fit converges } & \\multicolumn{1}{ c|}{$Pt_{jets}^{kf}\\ge 25 GeV$ } & \\multicolumn{1}{ c|}{$\\Delta R_{jets}^{pf,kf}\\le 0.2$}  \\\\ "<<endl;
  outFile<<"\\hline "<<endl;
  outFile<<"\\hline "<<endl;
  TH1F* h_MC = (TH1F*)h_ttbar->Clone("Bkg MC");
  h_MC->Add(h_stop);
  h_MC->Add(h_wjets);
  h_MC->Add(h_dyjets);
  h_MC->Add(h_qcd);
  h_MC->Add(h_vv);
  
  TH1F* h_ratio = (TH1F*)h_data->Clone("ratio");
  h_ratio->Divide(h_MC);

  outFile<<printCutFlowHist("WH, M120", 	h_wh, 		Nbin, 1)<<" \\\\ "<<endl;
  outFile<<"\\hline "<<endl;
  outFile<<printCutFlowHist("TTJets", 	h_ttbar, 	Nbin, 1)<<" \\\\ "<<endl;
  outFile<<"\\hline "<<endl;
  outFile<<printCutFlowHist("STop", 	h_stop, 	Nbin, 1)<<" \\\\ "<<endl;
  outFile<<"\\hline "<<endl;
  outFile<<printCutFlowHist("WJets", 	h_wjets, 	Nbin, 1)<<" \\\\ "<<endl;
  outFile<<"\\hline "<<endl;
  outFile<<printCutFlowHist("DYJets", 	h_dyjets, 	Nbin, 1)<<" \\\\ "<<endl;
  outFile<<"\\hline "<<endl;
  outFile<<printCutFlowHist("QCD", 	h_qcd, 		Nbin, 1)<<" \\\\ "<<endl;
  outFile<<"\\hline "<<endl;
  outFile<<printCutFlowHist("VV", 	h_vv, 		Nbin, 1)<<" \\\\ "<<endl;
  outFile<<"\\hline "<<endl;
  outFile<<"\\hline "<<endl;
  outFile<<printCutFlowHist("Bkg", 	h_MC, 		Nbin, 1)<<" \\\\ "<<endl;
  outFile<<"\\hline "<<endl;
  outFile<<"\\hline "<<endl;
  outFile<<printCutFlowHist("Data", 	h_data, 	Nbin, 1)<<" \\\\ "<<endl;
  outFile<<"\\hline "<<endl;
  outFile<<"\\hline "<<endl;
  outFile<<printCutFlowHist("Data/Bkg", 	h_ratio, 	Nbin, 1)<<" \\\\ "<<endl;
  outFile<<"\\hline "<<endl;
  outFile<<"\\hline "<<endl;
  outFile<<"\\end{tabular}"<<endl;
  //outFile<<"%\\end{LARGE}"<<endl; 
  outFile<<"\\end{center}"<<endl; 
  outFile<<"\\caption{Number of evets after various cuts for sys: " +sys+ "}"<<endl; 
  outFile<<"\\end{table}"<<endl; 
}

void getSignalCutFlowTable(ofstream &outFile, string sys, int Nbin, 
		TH1F *h_wh80,
		TH1F *h_wh90,
		TH1F *h_wh100,
		TH1F *h_wh120,
		TH1F *h_wh140,
		TH1F *h_wh150,
		TH1F *h_wh155,
		TH1F *h_wh160
		){
  outFile<<""<<endl;
  outFile<<"%%%%%%%%%%%%%%%%%% NEXT TABLE: "+sys+" %%%%%%%%%%%%%%%%%"<<endl;
  outFile<<"\\begin{table}"<<endl; 
  outFile<<"\\begin{center}"<<endl; 
  //outFile<<"%\\begin{LARGE}"<<endl;
  outFile<<"\\footnotesize\\setlength{\\tabcolsep}{2.8pt}"<<endl;
  outFile<<"\\begin{tabular}{ | c| c| c| c| c| c| c| c| c| c| c| c| c|c|}"<<endl; 
  outFile<<"\\multicolumn{5}{c}{ } \\\\"<<endl; 
  outFile<<"\\hline "<<endl;
  outFile<<"\\multicolumn{1}{| c|}{"+ sys +" } & \\multicolumn{1}{ c|}{ $HLT\\_IsoMu24$ } & \\multicolumn{1}{ c|}{ $N_{muon}=1$ } & \\multicolumn{1}{ c|}{ $N_{ele}=0$} & \\multicolumn{1}{ c|}{ Muon SF } & \\multicolumn{1}{ c|}{ $\\mu^{Iso} < 0.15$ } &\\multicolumn{1}{ c|}{ $N_{jets}\\ge 4$ } & \\multicolumn{1}{ c|}{ $\\not\\!\\!E_T \\ge 20GeV$ }&  \\multicolumn{1}{ c|}{MT $\\ge$ 20 GeV} & \\multicolumn{1}{ c |}{ $\\ge$ 2btag }& \\multicolumn{1}{ c |}{ BTag SF }& \\multicolumn{1}{ c|}{fit converges } & \\multicolumn{1}{ c|}{$Pt_{jets}^{kf}\\ge 25 GeV$ } & \\multicolumn{1}{ c|}{$\\Delta R_{jets}^{pf,kf}\\le 0.2$}  \\\\ "<<endl;
  outFile<<"\\hline "<<endl;
  outFile<<"\\hline "<<endl;

  outFile<<printCutFlowHist("WH, M80", 	h_wh80, 		Nbin, 1)<<" \\\\ "<<endl;
  outFile<<"\\hline "<<endl;
  outFile<<printCutFlowHist("WH, M90",  h_wh90, 		Nbin, 1)<<" \\\\ "<<endl;
  outFile<<"\\hline "<<endl;  
  outFile<<printCutFlowHist("WH, M100",  h_wh100, 		Nbin, 1)<<" \\\\ "<<endl;
  outFile<<"\\hline "<<endl;  
  outFile<<printCutFlowHist("WH, M120",  h_wh120, 		Nbin, 1)<<" \\\\ "<<endl;
  outFile<<"\\hline "<<endl;  
  outFile<<printCutFlowHist("WH, M140",  h_wh140, 		Nbin, 1)<<" \\\\ "<<endl;
  outFile<<"\\hline "<<endl;  
  outFile<<printCutFlowHist("WH, M150",  h_wh150, 		Nbin, 1)<<" \\\\ "<<endl;
  outFile<<"\\hline "<<endl;  
  outFile<<printCutFlowHist("WH, M155",  h_wh155, 		Nbin, 1)<<" \\\\ "<<endl;
  outFile<<"\\hline "<<endl;  
  outFile<<printCutFlowHist("WH, M160",  h_wh160, 		Nbin, 1)<<" \\\\ "<<endl;
  outFile<<"\\hline "<<endl;
  outFile<<"\\hline "<<endl;
  outFile<<"\\end{tabular}"<<endl;
  //outFile<<"%\\end{LARGE}"<<endl; 
  outFile<<"\\end{center}"<<endl; 
  outFile<<"\\caption{Number of evets after various cuts for sys: " +sys+ "}"<<endl; 
  outFile<<"\\end{table}"<<endl; 
}

void makeBaseTable(TString histSubDir="Iso/", TString histName="cutflow"){  
  
  TString inFile("$PWD/");
  TString histPath(histSubDir+histName);
  TFile *wh 	  		= new TFile(inFile+"all_Hplus120.root"); 
  TFile *ttbar    		= new TFile(inFile+"all_TTJetsP.root"); 
  TFile *wjet  			= new TFile(inFile+"all_WJets.root"); 
  TFile *zjet  			= new TFile(inFile+"all_DY.root");
  TFile *qcd  			= new TFile(inFile+"all_QCD.root");
  TFile *stop  			= new TFile(inFile+"all_ST.root");
  TFile *diboson 		= new TFile(inFile+"all_VV.root");
  
  TH1F* h_wh_base  		= (TH1F*)wh->Get("base/"+histPath)->Clone("h_wh_base"); 
  TH1F* h_ttbar_base  		= (TH1F*)ttbar->Get("base/"+histPath)->Clone("h_ttbar_base");  
  TH1F* h_wjet_base  		= (TH1F*)wjet->Get("base/"+histPath)->Clone("h_wjet_base");  
  TH1F* h_zjet_base  		= (TH1F*)zjet->Get("base/"+histPath)->Clone("h_zjet_base");
  TH1F* h_qcd_base 		= (TH1F*)qcd->Get("base/"+histPath)->Clone("h_qcd_base");
  TH1F* h_stop_base  		= (TH1F*)stop->Get("base/"+histPath)->Clone("h_stop_base");
  TH1F* h_diboson_base 		= (TH1F*)diboson->Get("base/"+histPath)->Clone("h_diboson_base");

  //get average of top pt-reweighting 
  TH1F* hsig_avgTop120 = (TH1F*)wh->Get("base/SF_topPtWeights"); 
  double sig_avgTop120 = hsig_avgTop120->GetMean();
  double sf120 = 1;
  h_wh_base->Scale(sf120/sig_avgTop120);
  
  TH1F* httbar_avgTop = (TH1F*)ttbar->Get("base/SF_topPtWeights"); 
  double ttbar_avgTop = httbar_avgTop->GetMean();
  double sf_ttbar = 1.0;
  h_ttbar_base->Scale(sf_ttbar/ttbar_avgTop);

  TH1F* h_TotalBkg = (TH1F*)h_wjet_base->Clone("h_TotalBkg");
  h_TotalBkg->Reset();
  h_TotalBkg->Add(h_ttbar_base);
  h_TotalBkg->Add(h_wjet_base);
  h_TotalBkg->Add(h_zjet_base);
  h_TotalBkg->Add(h_qcd_base);
  h_TotalBkg->Add(h_stop_base);
  h_TotalBkg->Add(h_diboson_base);

  TFile *data = new TFile(inFile+"all_muData.root");
  TH1F* h_data = (TH1F*)data->Get("base/"+histPath)->Clone("h_data");

  ofstream outFile; 
  outFile.open("baseCutFlowTable.tex"); 
   
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
  //Add another table with JESUP
  double Nbin = 14;
  makeCutFlowTableAny(outFile, "base", Nbin, h_wh_base,	h_ttbar_base, h_stop_base, h_wjet_base, h_zjet_base, h_qcd_base, h_stop_base, h_diboson_base, h_data);
  outFile<<"\\end{document}"<<endl;  
  outFile.close(); 
} 
  
void makeSignalTable(TString histSubDir="Iso/", TString histName="cutflow"){  
  
  TString inFile("$PWD/");
  TString histPath(histSubDir+histName);
  TFile *wh80   		= new TFile(inFile+"all_Hplus80.root"); 
  TFile *wh90   		= new TFile(inFile+"all_Hplus90.root"); 
  TFile *wh100  		= new TFile(inFile+"all_Hplus100.root"); 
  TFile *wh120  		= new TFile(inFile+"all_Hplus120.root"); 
  TFile *wh140  		= new TFile(inFile+"all_Hplus140.root"); 
  TFile *wh150  		= new TFile(inFile+"all_Hplus150.root"); 
  TFile *wh155  		= new TFile(inFile+"all_Hplus155.root"); 
  TFile *wh160  		= new TFile(inFile+"all_Hplus160.root"); 
  
  //Hplus  M80   signal 
  TH1F* h_wh80_base  			= (TH1F*)wh80->Get("base/"+histPath)->Clone("h_wh_base"); 
  TH1F* h_wh80_JESPlus 			= (TH1F*)wh80->Get("JESPlus/"+histPath)->Clone("h_wh_JESPlus");
  TH1F* h_wh80_JESMinus 		= (TH1F*)wh80->Get("JESMinus/"+histPath)->Clone("h_wh_JESMinus");
  TH1F* h_wh80_JERPlus 			= (TH1F*)wh80->Get("JERPlus/"+histPath)->Clone("h_wh_JERPlus");
  TH1F* h_wh80_JERMinus 		= (TH1F*)wh80->Get("JERMinus/"+histPath)->Clone("h_wh_JERMinus");
  TH1F* h_wh80_TopPtPlus 		= (TH1F*)wh80->Get("TopPtPlus/"+histPath)->Clone("h_wh_TopPtPlus");
  TH1F* h_wh80_TopPtMinus 		= (TH1F*)wh80->Get("TopPtMinus/"+histPath)->Clone("h_wh_TopPtMinus");
  TH1F* h_wh80_bTagPlus 		= (TH1F*)wh80->Get("bTagPlus/"+histPath)->Clone("h_wh_bTagPlus");
  TH1F* h_wh80_bTagMinus 		= (TH1F*)wh80->Get("bTagMinus/"+histPath)->Clone("h_wh_bTagMinus");
  
  //Hplus  M90   signal 
  TH1F* h_wh90_base  			= (TH1F*)wh90->Get("base/"+histPath)->Clone("h_wh_base"); 
  TH1F* h_wh90_JESPlus 			= (TH1F*)wh90->Get("JESPlus/"+histPath)->Clone("h_wh_JESPlus");
  TH1F* h_wh90_JESMinus 		= (TH1F*)wh90->Get("JESMinus/"+histPath)->Clone("h_wh_JESMinus");
  TH1F* h_wh90_JERPlus 			= (TH1F*)wh90->Get("JERPlus/"+histPath)->Clone("h_wh_JERPlus");
  TH1F* h_wh90_JERMinus 		= (TH1F*)wh90->Get("JERMinus/"+histPath)->Clone("h_wh_JERMinus");
  TH1F* h_wh90_TopPtPlus 		= (TH1F*)wh90->Get("TopPtPlus/"+histPath)->Clone("h_wh_TopPtPlus");
  TH1F* h_wh90_TopPtMinus 		= (TH1F*)wh90->Get("TopPtMinus/"+histPath)->Clone("h_wh_TopPtMinus");
  TH1F* h_wh90_bTagPlus 		= (TH1F*)wh90->Get("bTagPlus/"+histPath)->Clone("h_wh_bTagPlus");
  TH1F* h_wh90_bTagMinus 		= (TH1F*)wh90->Get("bTagMinus/"+histPath)->Clone("h_wh_bTagMinus");
  
  //Hplus  M100   signal 
  TH1F* h_wh100_base  			= (TH1F*)wh100->Get("base/"+histPath)->Clone("h_wh_base"); 
  TH1F* h_wh100_JESPlus 		= (TH1F*)wh100->Get("JESPlus/"+histPath)->Clone("h_wh_JESPlus");
  TH1F* h_wh100_JESMinus 		= (TH1F*)wh100->Get("JESMinus/"+histPath)->Clone("h_wh_JESMinus");
  TH1F* h_wh100_JERPlus 		= (TH1F*)wh100->Get("JERPlus/"+histPath)->Clone("h_wh_JERPlus");
  TH1F* h_wh100_JERMinus 		= (TH1F*)wh100->Get("JERMinus/"+histPath)->Clone("h_wh_JERMinus");
  TH1F* h_wh100_TopPtPlus 		= (TH1F*)wh100->Get("TopPtPlus/"+histPath)->Clone("h_wh_TopPtPlus");
  TH1F* h_wh100_TopPtMinus 		= (TH1F*)wh100->Get("TopPtMinus/"+histPath)->Clone("h_wh_TopPtMinus");
  TH1F* h_wh100_bTagPlus 		= (TH1F*)wh100->Get("bTagPlus/"+histPath)->Clone("h_wh_bTagPlus");
  TH1F* h_wh100_bTagMinus 		= (TH1F*)wh100->Get("bTagMinus/"+histPath)->Clone("h_wh_bTagMinus");
  
  
  //Hplus  M120   signal 
  TH1F* h_wh120_base  			= (TH1F*)wh120->Get("base/"+histPath)->Clone("h_wh_base"); 
  TH1F* h_wh120_JESPlus 		= (TH1F*)wh120->Get("JESPlus/"+histPath)->Clone("h_wh_JESPlus");
  TH1F* h_wh120_JESMinus 		= (TH1F*)wh120->Get("JESMinus/"+histPath)->Clone("h_wh_JESMinus");
  TH1F* h_wh120_JERPlus 		= (TH1F*)wh120->Get("JERPlus/"+histPath)->Clone("h_wh_JERPlus");
  TH1F* h_wh120_JERMinus 		= (TH1F*)wh120->Get("JERMinus/"+histPath)->Clone("h_wh_JERMinus");
  TH1F* h_wh120_TopPtPlus 		= (TH1F*)wh120->Get("TopPtPlus/"+histPath)->Clone("h_wh_TopPtPlus");
  TH1F* h_wh120_TopPtMinus 		= (TH1F*)wh120->Get("TopPtMinus/"+histPath)->Clone("h_wh_TopPtMinus");
  TH1F* h_wh120_bTagPlus 		= (TH1F*)wh120->Get("bTagPlus/"+histPath)->Clone("h_wh_bTagPlus");
  TH1F* h_wh120_bTagMinus 		= (TH1F*)wh120->Get("bTagMinus/"+histPath)->Clone("h_wh_bTagMinus");
  
  
  //Hplus  M140   signal 
  TH1F* h_wh140_base  			= (TH1F*)wh140->Get("base/"+histPath)->Clone("h_wh_base"); 
  TH1F* h_wh140_JESPlus 		= (TH1F*)wh140->Get("JESPlus/"+histPath)->Clone("h_wh_JESPlus");
  TH1F* h_wh140_JESMinus 		= (TH1F*)wh140->Get("JESMinus/"+histPath)->Clone("h_wh_JESMinus");
  TH1F* h_wh140_JERPlus 		= (TH1F*)wh140->Get("JERPlus/"+histPath)->Clone("h_wh_JERPlus");
  TH1F* h_wh140_JERMinus 		= (TH1F*)wh140->Get("JERMinus/"+histPath)->Clone("h_wh_JERMinus");
  TH1F* h_wh140_TopPtPlus 		= (TH1F*)wh140->Get("TopPtPlus/"+histPath)->Clone("h_wh_TopPtPlus");
  TH1F* h_wh140_TopPtMinus 		= (TH1F*)wh140->Get("TopPtMinus/"+histPath)->Clone("h_wh_TopPtMinus");
  TH1F* h_wh140_bTagPlus 		= (TH1F*)wh140->Get("bTagPlus/"+histPath)->Clone("h_wh_bTagPlus");
  TH1F* h_wh140_bTagMinus 		= (TH1F*)wh140->Get("bTagMinus/"+histPath)->Clone("h_wh_bTagMinus");
  
  
  //Hplus  M150   signal 
  TH1F* h_wh150_base  			= (TH1F*)wh150->Get("base/"+histPath)->Clone("h_wh_base"); 
  TH1F* h_wh150_JESPlus 		= (TH1F*)wh150->Get("JESPlus/"+histPath)->Clone("h_wh_JESPlus");
  TH1F* h_wh150_JESMinus 		= (TH1F*)wh150->Get("JESMinus/"+histPath)->Clone("h_wh_JESMinus");
  TH1F* h_wh150_JERPlus 		= (TH1F*)wh150->Get("JERPlus/"+histPath)->Clone("h_wh_JERPlus");
  TH1F* h_wh150_JERMinus 		= (TH1F*)wh150->Get("JERMinus/"+histPath)->Clone("h_wh_JERMinus");
  TH1F* h_wh150_TopPtPlus 		= (TH1F*)wh150->Get("TopPtPlus/"+histPath)->Clone("h_wh_TopPtPlus");
  TH1F* h_wh150_TopPtMinus 		= (TH1F*)wh150->Get("TopPtMinus/"+histPath)->Clone("h_wh_TopPtMinus");
  TH1F* h_wh150_bTagPlus 		= (TH1F*)wh150->Get("bTagPlus/"+histPath)->Clone("h_wh_bTagPlus");
  TH1F* h_wh150_bTagMinus 		= (TH1F*)wh150->Get("bTagMinus/"+histPath)->Clone("h_wh_bTagMinus");
  
  
  //Hplus  M155   signal 
  TH1F* h_wh155_base  			= (TH1F*)wh155->Get("base/"+histPath)->Clone("h_wh_base"); 
  TH1F* h_wh155_JESPlus 		= (TH1F*)wh155->Get("JESPlus/"+histPath)->Clone("h_wh_JESPlus");
  TH1F* h_wh155_JESMinus 		= (TH1F*)wh155->Get("JESMinus/"+histPath)->Clone("h_wh_JESMinus");
  TH1F* h_wh155_JERPlus 		= (TH1F*)wh155->Get("JERPlus/"+histPath)->Clone("h_wh_JERPlus");
  TH1F* h_wh155_JERMinus 		= (TH1F*)wh155->Get("JERMinus/"+histPath)->Clone("h_wh_JERMinus");
  TH1F* h_wh155_TopPtPlus 		= (TH1F*)wh155->Get("TopPtPlus/"+histPath)->Clone("h_wh_TopPtPlus");
  TH1F* h_wh155_TopPtMinus 		= (TH1F*)wh155->Get("TopPtMinus/"+histPath)->Clone("h_wh_TopPtMinus");
  TH1F* h_wh155_bTagPlus 		= (TH1F*)wh155->Get("bTagPlus/"+histPath)->Clone("h_wh_bTagPlus");
  TH1F* h_wh155_bTagMinus 		= (TH1F*)wh155->Get("bTagMinus/"+histPath)->Clone("h_wh_bTagMinus");
  
  
  //Hplus  M160   signal 
  TH1F* h_wh160_base  			= (TH1F*)wh160->Get("base/"+histPath)->Clone("h_wh_base"); 
  TH1F* h_wh160_JESPlus 		= (TH1F*)wh160->Get("JESPlus/"+histPath)->Clone("h_wh_JESPlus");
  TH1F* h_wh160_JESMinus 		= (TH1F*)wh160->Get("JESMinus/"+histPath)->Clone("h_wh_JESMinus");
  TH1F* h_wh160_JERPlus 		= (TH1F*)wh160->Get("JERPlus/"+histPath)->Clone("h_wh_JERPlus");
  TH1F* h_wh160_JERMinus 		= (TH1F*)wh160->Get("JERMinus/"+histPath)->Clone("h_wh_JERMinus");
  TH1F* h_wh160_TopPtPlus 		= (TH1F*)wh160->Get("TopPtPlus/"+histPath)->Clone("h_wh_TopPtPlus");
  TH1F* h_wh160_TopPtMinus 		= (TH1F*)wh160->Get("TopPtMinus/"+histPath)->Clone("h_wh_TopPtMinus");
  TH1F* h_wh160_bTagPlus 		= (TH1F*)wh160->Get("bTagPlus/"+histPath)->Clone("h_wh_bTagPlus");
  TH1F* h_wh160_bTagMinus 		= (TH1F*)wh160->Get("bTagMinus/"+histPath)->Clone("h_wh_bTagMinus");
  
  

  //get average of top pt-reweighting 
  TH1F* hsig_avgTop80 = (TH1F*)wh80->Get("base/SF_topPtWeights"); 
  double sig_avgTop80 = hsig_avgTop80->GetMean();
  double sf80 = 1;
  h_wh80_base->Scale(sf80/sig_avgTop80);
  h_wh80_JESPlus->Scale(sf80/sig_avgTop80);
  h_wh80_JESMinus->Scale(sf80/sig_avgTop80);
  h_wh80_JERPlus->Scale(sf80/sig_avgTop80);
  h_wh80_JERMinus->Scale(sf80/sig_avgTop80);
  h_wh80_TopPtPlus->Scale(sf80/sig_avgTop80);
  h_wh80_TopPtMinus->Scale(sf80/sig_avgTop80);
  h_wh80_bTagPlus->Scale(sf80/sig_avgTop80);
  h_wh80_bTagMinus->Scale(sf80/sig_avgTop80);


  //get average of top pt-reweighting 
  TH1F* hsig_avgTop90 = (TH1F*)wh90->Get("base/SF_topPtWeights"); 
  double sig_avgTop90 = hsig_avgTop90->GetMean();
  double sf90 = 1.0;
  h_wh90_base->Scale(sf90/sig_avgTop90);
  h_wh90_JESPlus->Scale(sf90/sig_avgTop90);
  h_wh90_JESMinus->Scale(sf90/sig_avgTop90);
  h_wh90_JERPlus->Scale(sf90/sig_avgTop90);
  h_wh90_JERMinus->Scale(sf90/sig_avgTop90);
  h_wh90_TopPtPlus->Scale(sf90/sig_avgTop90);
  h_wh90_TopPtMinus->Scale(sf90/sig_avgTop90);
  h_wh90_bTagPlus->Scale(sf90/sig_avgTop90);
  h_wh90_bTagMinus->Scale(sf90/sig_avgTop90);


  //get average of top pt-reweighting 
  TH1F* hsig_avgTop100 = (TH1F*)wh100->Get("base/SF_topPtWeights"); 
  double sig_avgTop100 = hsig_avgTop100->GetMean();
  double sf100 = 1;
  h_wh100_base->Scale(sf100/sig_avgTop100);
  h_wh100_JESPlus->Scale(sf100/sig_avgTop100);
  h_wh100_JESMinus->Scale(sf100/sig_avgTop100);
  h_wh100_JERPlus->Scale(sf100/sig_avgTop100);
  h_wh100_JERMinus->Scale(sf100/sig_avgTop100);
  h_wh100_TopPtPlus->Scale(sf100/sig_avgTop100);
  h_wh100_TopPtMinus->Scale(sf100/sig_avgTop100);
  h_wh100_bTagPlus->Scale(sf100/sig_avgTop100);
  h_wh100_bTagMinus->Scale(sf100/sig_avgTop100);


  //get average of top pt-reweighting 
  TH1F* hsig_avgTop120 = (TH1F*)wh120->Get("base/SF_topPtWeights"); 
  double sig_avgTop120 = hsig_avgTop120->GetMean();
  double sf120 = 1;
  h_wh120_base->Scale(sf120/sig_avgTop120);
  h_wh120_JESPlus->Scale(sf120/sig_avgTop120);
  h_wh120_JESMinus->Scale(sf120/sig_avgTop120);
  h_wh120_JERPlus->Scale(sf120/sig_avgTop120);
  h_wh120_JERMinus->Scale(sf120/sig_avgTop120);
  h_wh120_TopPtPlus->Scale(sf120/sig_avgTop120);
  h_wh120_TopPtMinus->Scale(sf120/sig_avgTop120);
  h_wh120_bTagPlus->Scale(sf120/sig_avgTop120);
  h_wh120_bTagMinus->Scale(sf120/sig_avgTop120);


  //get average of top pt-reweighting 
  TH1F* hsig_avgTop140 = (TH1F*)wh140->Get("base/SF_topPtWeights"); 
  double sig_avgTop140 = hsig_avgTop140->GetMean();
  double sf140 = 1;
  h_wh140_base->Scale(sf140/sig_avgTop140);
  h_wh140_JESPlus->Scale(sf140/sig_avgTop140);
  h_wh140_JESMinus->Scale(sf140/sig_avgTop140);
  h_wh140_JERPlus->Scale(sf140/sig_avgTop140);
  h_wh140_JERMinus->Scale(sf140/sig_avgTop140);
  h_wh140_TopPtPlus->Scale(sf140/sig_avgTop140);
  h_wh140_TopPtMinus->Scale(sf140/sig_avgTop140);
  h_wh140_bTagPlus->Scale(sf140/sig_avgTop140);
  h_wh140_bTagMinus->Scale(sf140/sig_avgTop140);


  //get average of top pt-reweighting 
  TH1F* hsig_avgTop150 = (TH1F*)wh150->Get("base/SF_topPtWeights"); 
  double sig_avgTop150 = hsig_avgTop150->GetMean();
  double sf150 = 1;
  h_wh150_base->Scale(sf150/sig_avgTop150);
  h_wh150_JESPlus->Scale(sf150/sig_avgTop150);
  h_wh150_JESMinus->Scale(sf150/sig_avgTop150);
  h_wh150_JERPlus->Scale(sf150/sig_avgTop150);
  h_wh150_JERMinus->Scale(sf150/sig_avgTop150);
  h_wh150_TopPtPlus->Scale(sf150/sig_avgTop150);
  h_wh150_TopPtMinus->Scale(sf150/sig_avgTop150);
  h_wh150_bTagPlus->Scale(sf150/sig_avgTop150);
  h_wh150_bTagMinus->Scale(sf150/sig_avgTop150);


  //get average of top pt-reweighting 
  TH1F* hsig_avgTop155 = (TH1F*)wh155->Get("base/SF_topPtWeights"); 
  double sig_avgTop155 = hsig_avgTop155->GetMean();
  double sf155 = 1;
  h_wh155_base->Scale(sf155/sig_avgTop155);
  h_wh155_JESPlus->Scale(sf155/sig_avgTop155);
  h_wh155_JESMinus->Scale(sf155/sig_avgTop155);
  h_wh155_JERPlus->Scale(sf155/sig_avgTop155);
  h_wh155_JERMinus->Scale(sf155/sig_avgTop155);
  h_wh155_TopPtPlus->Scale(sf155/sig_avgTop155);
  h_wh155_TopPtMinus->Scale(sf155/sig_avgTop155);
  h_wh155_bTagPlus->Scale(sf155/sig_avgTop155);
  h_wh155_bTagMinus->Scale(sf155/sig_avgTop155);


  //get average of top pt-reweighting 
  TH1F* hsig_avgTop160 = (TH1F*)wh160->Get("base/SF_topPtWeights"); 
  double sig_avgTop160 = hsig_avgTop160->GetMean();
  double sf160 = 1;
  h_wh160_base->Scale(sf160/sig_avgTop160);
  h_wh160_JESPlus->Scale(sf160/sig_avgTop160);
  h_wh160_JESMinus->Scale(sf160/sig_avgTop160);
  h_wh160_JERPlus->Scale(sf160/sig_avgTop160);
  h_wh160_JERMinus->Scale(sf160/sig_avgTop160);
  h_wh160_TopPtPlus->Scale(sf160/sig_avgTop160);
  h_wh160_TopPtMinus->Scale(sf160/sig_avgTop160);
  h_wh160_bTagPlus->Scale(sf160/sig_avgTop160);
  h_wh160_bTagMinus->Scale(sf160/sig_avgTop160);

  ofstream outFile; 
  outFile.open("signalTable.tex"); 
   
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
  
  //Add another table with JESUP
  double Nbin = 14;
  getSignalCutFlowTable(outFile, "base", Nbin, 		h_wh80_base,  		h_wh90_base,  		h_wh100_base,  	  	h_wh120_base,  	   h_wh140_base,      h_wh150_base,  	 h_wh155_base,       h_wh160_base      ); 
  getSignalCutFlowTable(outFile, "JESPlus", Nbin, 	h_wh80_JESPlus, 	h_wh90_JESPlus,         h_wh100_JESPlus,        h_wh120_JESPlus,   h_wh140_JESPlus,   h_wh150_JESPlus,   h_wh155_JESPlus,    h_wh160_JESPlus   ); 
  getSignalCutFlowTable(outFile, "JESMinus", Nbin, 	h_wh80_JESMinus, 	h_wh90_JESMinus,        h_wh100_JESMinus,       h_wh120_JESMinus,  h_wh140_JESMinus,  h_wh150_JESMinus,  h_wh155_JESMinus,   h_wh160_JESMinus  );
  getSignalCutFlowTable(outFile, "JERPlus", Nbin, 	h_wh80_JERPlus, 	h_wh90_JERPlus,         h_wh100_JERPlus,        h_wh120_JERPlus,   h_wh140_JERPlus,   h_wh150_JERPlus,   h_wh155_JERPlus,    h_wh160_JERPlus   );
  getSignalCutFlowTable(outFile, "JERMinus", Nbin, 	h_wh80_JERMinus, 	h_wh90_JERMinus,        h_wh100_JERMinus,       h_wh120_JERMinus,  h_wh140_JERMinus,  h_wh150_JERMinus,  h_wh155_JERMinus,   h_wh160_JERMinus  );
  getSignalCutFlowTable(outFile, "TopPtPlus", Nbin, 	h_wh80_TopPtPlus, 	h_wh90_TopPtPlus,       h_wh100_TopPtPlus,      h_wh120_TopPtPlus, h_wh140_TopPtPlus, h_wh150_TopPtPlus, h_wh155_TopPtPlus,  h_wh160_TopPtPlus );
  getSignalCutFlowTable(outFile, "TopPtMinus", Nbin, 	h_wh80_TopPtMinus, 	h_wh90_TopPtMinus,      h_wh100_TopPtMinus,     h_wh120_TopPtMinus,h_wh140_TopPtMinus,h_wh150_TopPtMinus,h_wh155_TopPtMinus, h_wh160_TopPtMinus);
  getSignalCutFlowTable(outFile, "bTagPlus", Nbin, 	h_wh80_bTagPlus, 	h_wh90_bTagPlus,        h_wh100_bTagPlus,       h_wh120_bTagPlus,  h_wh140_bTagPlus,  h_wh150_bTagPlus,  h_wh155_bTagPlus,   h_wh160_bTagPlus  );
  getSignalCutFlowTable(outFile, "bTagMinus", Nbin, 	h_wh80_bTagMinus, 	h_wh90_bTagMinus,       h_wh100_bTagMinus,      h_wh120_bTagMinus, h_wh140_bTagMinus, h_wh150_bTagMinus, h_wh155_bTagMinus,  h_wh160_bTagMinus );
  outFile<<"\\end{document}"<<endl;  
  outFile.close(); 
} 

void makeSummaryTableWithSys(TString histSubDir="Iso/", TString histName="cutflow"){  
  
  TString inFile("$PWD/");
  TString histPath(histSubDir+histName);
  TFile *wh 	  		= new TFile(inFile+"all_Hplus120.root"); 
  TFile *ttbar    		= new TFile(inFile+"all_TTJetsP.root"); 
  TFile *wjet  			= new TFile(inFile+"all_WJets.root"); 
  TFile *zjet  			= new TFile(inFile+"all_DY.root");
  TFile *qcd  			= new TFile(inFile+"all_QCD.root");
  TFile *stop  			= new TFile(inFile+"all_ST.root");
  TFile *diboson 		= new TFile(inFile+"all_VV.root");
  
  //Hplus  M120   signal 
  TH1F* h_wh_base  		= (TH1F*)wh->Get("base/"+histPath)->Clone("h_wh_base"); 
  TH1F* h_wh_JESPlus 		= (TH1F*)wh->Get("JESPlus/"+histPath)->Clone("h_wh_JESPlus");
  TH1F* h_wh_JESMinus 		= (TH1F*)wh->Get("JESMinus/"+histPath)->Clone("h_wh_JESMinus");
  TH1F* h_wh_JERPlus 		= (TH1F*)wh->Get("JERPlus/"+histPath)->Clone("h_wh_JERPlus");
  TH1F* h_wh_JERMinus 		= (TH1F*)wh->Get("JERMinus/"+histPath)->Clone("h_wh_JERMinus");
  TH1F* h_wh_TopPtPlus 		= (TH1F*)wh->Get("TopPtPlus/"+histPath)->Clone("h_wh_TopPtPlus");
  TH1F* h_wh_TopPtMinus 	= (TH1F*)wh->Get("TopPtMinus/"+histPath)->Clone("h_wh_TopPtMinus");
  TH1F* h_wh_bTagPlus 		= (TH1F*)wh->Get("bTagPlus/"+histPath)->Clone("h_wh_bTagPlus");
  TH1F* h_wh_bTagMinus 		= (TH1F*)wh->Get("bTagMinus/"+histPath)->Clone("h_wh_bTagMinus");
  
  //ttbar+jets
  TH1F* h_ttbar_base  		= (TH1F*)ttbar->Get("base/"+histPath)->Clone("h_ttbar_base");  
  TH1F* h_ttbar_JESPlus 	= (TH1F*)ttbar->Get("JESPlus/"+histPath)->Clone("h_ttbar_JESPlus"); 
  TH1F* h_ttbar_JESMinus 	= (TH1F*)ttbar->Get("JESMinus/"+histPath)->Clone("h_ttbar_JESMinus"); 
  TH1F* h_ttbar_JERPlus 	= (TH1F*)ttbar->Get("JERPlus/"+histPath)->Clone("h_ttbar_JERPlus"); 
  TH1F* h_ttbar_JERMinus 	= (TH1F*)ttbar->Get("JERMinus/"+histPath)->Clone("h_ttbar_JERMinus"); 
  TH1F* h_ttbar_TopPtPlus 	= (TH1F*)ttbar->Get("TopPtPlus/"+histPath)->Clone("h_ttbar_TopPtPlus"); 
  TH1F* h_ttbar_TopPtMinus 	= (TH1F*)ttbar->Get("TopPtMinus/"+histPath)->Clone("h_ttbar_TopPtMinus"); 
  TH1F* h_ttbar_bTagPlus 	= (TH1F*)ttbar->Get("bTagPlus/"+histPath)->Clone("h_ttbar_bTagPlus"); 
  TH1F* h_ttbar_bTagMinus 	= (TH1F*)ttbar->Get("bTagMinus/"+histPath)->Clone("h_ttbar_bTagMinus"); 
  //w+jets
  TH1F* h_wjet_base  		= (TH1F*)wjet->Get("base/"+histPath)->Clone("h_wjet_base");  
  TH1F* h_wjet_JESPlus 		= (TH1F*)wjet->Get("JESPlus/"+histPath)->Clone("h_wjet_JESPlus"); 
  TH1F* h_wjet_JESMinus 	= (TH1F*)wjet->Get("JESMinus/"+histPath)->Clone("h_wjet_JESMinus"); 
  TH1F* h_wjet_JERPlus 		= (TH1F*)wjet->Get("JERPlus/"+histPath)->Clone("h_wjet_JERPlus"); 
  TH1F* h_wjet_JERMinus 	= (TH1F*)wjet->Get("JERMinus/"+histPath)->Clone("h_wjet_JERMinus"); 
  TH1F* h_wjet_TopPtPlus 	= (TH1F*)wjet->Get("TopPtPlus/"+histPath)->Clone("h_wjet_TopPtPlus"); 
  TH1F* h_wjet_TopPtMinus 	= (TH1F*)wjet->Get("TopPtMinus/"+histPath)->Clone("h_wjet_TopPtMinus"); 
  TH1F* h_wjet_bTagPlus 	= (TH1F*)wjet->Get("bTagPlus/"+histPath)->Clone("h_wjet_bTagPlus"); 
  TH1F* h_wjet_bTagMinus 	= (TH1F*)wjet->Get("bTagMinus/"+histPath)->Clone("h_wjet_bTagMinus"); 
  //dy+jets
  TH1F* h_zjet_base  		= (TH1F*)zjet->Get("base/"+histPath)->Clone("h_zjet_base");
  TH1F* h_zjet_JESPlus 		= (TH1F*)zjet->Get("JESPlus/"+histPath)->Clone("h_zjet_JESPlus");
  TH1F* h_zjet_JESMinus 	= (TH1F*)zjet->Get("JESMinus/"+histPath)->Clone("h_zjet_JESMinus");
  TH1F* h_zjet_JERPlus 		= (TH1F*)zjet->Get("JERPlus/"+histPath)->Clone("h_zjet_JERPlus");
  TH1F* h_zjet_JERMinus 	= (TH1F*)zjet->Get("JERMinus/"+histPath)->Clone("h_zjet_JERMinus");
  TH1F* h_zjet_TopPtPlus 	= (TH1F*)zjet->Get("TopPtPlus/"+histPath)->Clone("h_zjet_TopPtPlus");
  TH1F* h_zjet_TopPtMinus 	= (TH1F*)zjet->Get("TopPtMinus/"+histPath)->Clone("h_zjet_TopPtMinus");
  TH1F* h_zjet_bTagPlus 	= (TH1F*)zjet->Get("bTagPlus/"+histPath)->Clone("h_zjet_bTagPlus");
  TH1F* h_zjet_bTagMinus 	= (TH1F*)zjet->Get("bTagMinus/"+histPath)->Clone("h_zjet_bTagMinus");
  //qcd
  TH1F* h_qcd_base 		= (TH1F*)qcd->Get("base/"+histPath)->Clone("h_qcd_base");
  TH1F* h_qcd_JESPlus 		= (TH1F*)qcd->Get("JESPlus/"+histPath)->Clone("h_qcd_JESPlus");
  TH1F* h_qcd_JESMinus 		= (TH1F*)qcd->Get("JESMinus/"+histPath)->Clone("h_qcd_JESMinus");
  TH1F* h_qcd_JERPlus 		= (TH1F*)qcd->Get("JERPlus/"+histPath)->Clone("h_qcd_JERPlus");
  TH1F* h_qcd_JERMinus 		= (TH1F*)qcd->Get("JERMinus/"+histPath)->Clone("h_qcd_JERMinus");
  TH1F* h_qcd_TopPtPlus 	= (TH1F*)qcd->Get("TopPtPlus/"+histPath)->Clone("h_qcd_TopPtPlus");
  TH1F* h_qcd_TopPtMinus 	= (TH1F*)qcd->Get("TopPtMinus/"+histPath)->Clone("h_qcd_TopPtMinus");
  TH1F* h_qcd_bTagPlus 		= (TH1F*)qcd->Get("bTagPlus/"+histPath)->Clone("h_qcd_bTagPlus");
  TH1F* h_qcd_bTagMinus 	= (TH1F*)qcd->Get("bTagMinus/"+histPath)->Clone("h_qcd_bTagMinus");
  //single top
  TH1F* h_stop_base  		= (TH1F*)stop->Get("base/"+histPath)->Clone("h_stop_base");
  TH1F* h_stop_JESPlus 		= (TH1F*)stop->Get("JESPlus/"+histPath)->Clone("h_stop_JESPlus");
  TH1F* h_stop_JESMinus 	= (TH1F*)stop->Get("JESMinus/"+histPath)->Clone("h_stop_JESMinus");
  TH1F* h_stop_JERPlus 		= (TH1F*)stop->Get("JERPlus/"+histPath)->Clone("h_stop_JERPlus");
  TH1F* h_stop_JERMinus 	= (TH1F*)stop->Get("JERMinus/"+histPath)->Clone("h_stop_JERMinus");
  TH1F* h_stop_TopPtPlus 	= (TH1F*)stop->Get("TopPtPlus/"+histPath)->Clone("h_stop_TopPtPlus");
  TH1F* h_stop_TopPtMinus 	= (TH1F*)stop->Get("TopPtMinus/"+histPath)->Clone("h_stop_TopPtMinus");
  TH1F* h_stop_bTagPlus 	= (TH1F*)stop->Get("bTagPlus/"+histPath)->Clone("h_stop_bTagPlus");
  TH1F* h_stop_bTagMinus 	= (TH1F*)stop->Get("bTagMinus/"+histPath)->Clone("h_stop_bTagMinus");
  //vv
  TH1F* h_diboson_base 		= (TH1F*)diboson->Get("base/"+histPath)->Clone("h_diboson_base");
  TH1F* h_diboson_JESPlus 	= (TH1F*)diboson->Get("JESPlus/"+histPath)->Clone("h_diboson_JESPlus");
  TH1F* h_diboson_JESMinus 	= (TH1F*)diboson->Get("JESMinus/"+histPath)->Clone("h_diboson_JESMinus");
  TH1F* h_diboson_JERPlus 	= (TH1F*)diboson->Get("JERPlus/"+histPath)->Clone("h_diboson_JERPlus");
  TH1F* h_diboson_JERMinus 	= (TH1F*)diboson->Get("JERMinus/"+histPath)->Clone("h_diboson_JERMinus");
  TH1F* h_diboson_TopPtPlus 	= (TH1F*)diboson->Get("TopPtPlus/"+histPath)->Clone("h_diboson_TopPtPlus");
  TH1F* h_diboson_TopPtMinus 	= (TH1F*)diboson->Get("TopPtMinus/"+histPath)->Clone("h_diboson_TopPtMinus");
  TH1F* h_diboson_bTagPlus 	= (TH1F*)diboson->Get("bTagPlus/"+histPath)->Clone("h_diboson_bTagPlus");
  TH1F* h_diboson_bTagMinus 	= (TH1F*)diboson->Get("bTagMinus/"+histPath)->Clone("h_diboson_bTagMinus");

  //get average of top pt-reweighting 
  TH1F* hsig_avgTop120 = (TH1F*)wh->Get("base/SF_topPtWeights"); 
  double sig_avgTop120 = hsig_avgTop120->GetMean();
  double sf120 = 1;
  h_wh_base->Scale(sf120/sig_avgTop120);
  h_wh_JESPlus->Scale(sf120/sig_avgTop120);
  h_wh_JESMinus->Scale(sf120/sig_avgTop120);
  h_wh_JERPlus->Scale(sf120/sig_avgTop120);
  h_wh_JERMinus->Scale(sf120/sig_avgTop120);
  h_wh_TopPtPlus->Scale(sf120/sig_avgTop120);
  h_wh_TopPtMinus->Scale(sf120/sig_avgTop120);
  h_wh_bTagPlus->Scale(sf120/sig_avgTop120);
  h_wh_bTagMinus->Scale(sf120/sig_avgTop120);

  
  TH1F* httbar_avgTop = (TH1F*)ttbar->Get("base/SF_topPtWeights"); 
  double ttbar_avgTop = httbar_avgTop->GetMean();
  double sf_top = 1.0;
  h_ttbar_base->Scale(sf_top/ttbar_avgTop);
  h_ttbar_JESPlus->Scale(sf_top/ttbar_avgTop);
  h_ttbar_JESMinus->Scale(sf_top/ttbar_avgTop);
  h_ttbar_JERPlus->Scale(sf_top/ttbar_avgTop);
  h_ttbar_JERMinus->Scale(sf_top/ttbar_avgTop);
  h_ttbar_TopPtPlus->Scale(sf_top/ttbar_avgTop);
  h_ttbar_TopPtMinus->Scale(sf_top/ttbar_avgTop);
  h_ttbar_bTagPlus->Scale(sf_top/ttbar_avgTop);
  h_ttbar_bTagMinus->Scale(sf_top/ttbar_avgTop);

  TH1F* h_TotalBkg = (TH1F*)h_wjet_base->Clone("h_TotalBkg");
  h_TotalBkg->Reset();
  h_TotalBkg->Add(h_ttbar_base);
  h_TotalBkg->Add(h_wjet_base);
  h_TotalBkg->Add(h_zjet_base);
  h_TotalBkg->Add(h_qcd_base);
  h_TotalBkg->Add(h_stop_base);
  h_TotalBkg->Add(h_diboson_base);


  TFile *data = new TFile(inFile+"all_muData.root");
  TH1F* h_data = (TH1F*)data->Get("base/"+histPath)->Clone("h_data");


  ofstream outFile; 
  outFile.open("summaryWithSyst.tex"); 
   
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
  outFile<<"\\begin{table}"<<endl;
  outFile<<"\\begin{center}"<<endl;  
  //outFile<<"\\begin{LARGE}"<<endl;  
  outFile<<"\\begin{tabular}{ | c| c| }"<<endl;  
  outFile<<"\\multicolumn{2}{c}{ } \\\\"<<endl;  
  outFile<<"\\hline "<<endl; 
  outFile<<"\\multicolumn{1}{|c|}{Source} & \\multicolumn{1}{|c|}{N$_{\rm events}$ $\\pm$ MC stat $\\pm$ JES/MET scale $\\pm$ bTag } \\\\"<<endl;
  outFile<<"\\hline "<<endl; 
  outFile<<"\\hline "<<endl;
  int b = 13;
  outFile<<"HW, $M_{H}=120~GeV/c^{2}$"<<" & "<<h_wh_base->GetBinContent(b)<<" $\\pm$ "<<h_wh_base->GetBinError(b)<<" $\\pm$ "<< sqrt(pow(TMath::Max(fabs(h_wh_JESPlus->GetBinContent(b) - h_wh_base->GetBinContent(b)), fabs(h_wh_base->GetBinContent(b) - h_wh_JESMinus->GetBinContent(b))), 2) + pow(TMath::Max(fabs(h_wh_JERPlus->GetBinContent(b) - h_wh_base->GetBinContent(b)), fabs(h_wh_base->GetBinContent(b) - h_wh_JERMinus->GetBinContent(b))), 2) + pow(TMath::Max(fabs(h_wh_TopPtPlus->GetBinContent(b) - h_wh_base->GetBinContent(b)), fabs(h_wh_base->GetBinContent(b) - h_wh_TopPtMinus->GetBinContent(b))), 2)) <<" $\\pm$ "<<TMath::Max(fabs(h_wh_bTagPlus->GetBinContent(b) - h_wh_base->GetBinContent(b)), fabs(h_wh_base->GetBinContent(b) - h_wh_bTagMinus->GetBinContent(b))) <<" \\\\ "<<endl; 
  outFile<<"\\hline "<<endl;  
  outFile<<"SM $t\\bar{t}$"<<" & "<<h_ttbar_base->GetBinContent(b)<<" $\\pm$ "<<h_ttbar_base->GetBinError(b)<<" $\\pm$ "<< sqrt(pow(TMath::Max(fabs(h_ttbar_JESPlus->GetBinContent(b) - h_ttbar_base->GetBinContent(b)), fabs(h_ttbar_base->GetBinContent(b) - h_ttbar_JESMinus->GetBinContent(b))), 2) + pow(TMath::Max(fabs(h_ttbar_JERPlus->GetBinContent(b) - h_ttbar_base->GetBinContent(b)), fabs(h_ttbar_base->GetBinContent(b) - h_ttbar_JERMinus->GetBinContent(b))), 2) + pow(TMath::Max(fabs(h_ttbar_TopPtPlus->GetBinContent(b) - h_ttbar_base->GetBinContent(b)), fabs(h_ttbar_base->GetBinContent(b) - h_ttbar_TopPtMinus->GetBinContent(b))), 2)) <<" $\\pm$ "<<TMath::Max(fabs(h_ttbar_bTagPlus->GetBinContent(b) - h_ttbar_base->GetBinContent(b)), fabs(h_ttbar_base->GetBinContent(b) - h_ttbar_bTagMinus->GetBinContent(b))) <<" \\\\ "<<endl;
  outFile<<"\\hline "<<endl;

  outFile<<"W+Jets"<<" & "<<h_wjet_base->GetBinContent(b)<<" $\\pm$ "<<h_wjet_base->GetBinError(b)<<" $\\pm$ "<< sqrt(pow(TMath::Max(fabs(h_wjet_JESPlus->GetBinContent(b) - h_wjet_base->GetBinContent(b)), fabs(h_wjet_base->GetBinContent(b) - h_wjet_JESMinus->GetBinContent(b))), 2) + pow(TMath::Max(fabs(h_wjet_JERPlus->GetBinContent(b) - h_wjet_base->GetBinContent(b)), fabs(h_wjet_base->GetBinContent(b) - h_wjet_JERMinus->GetBinContent(b))), 2) + pow(TMath::Max(fabs(h_wjet_TopPtPlus->GetBinContent(b) - h_wjet_base->GetBinContent(b)), fabs(h_wjet_base->GetBinContent(b) - h_wjet_TopPtMinus->GetBinContent(b))), 2)) <<" $\\pm$ "<<TMath::Max(fabs(h_wjet_bTagPlus->GetBinContent(b) - h_wjet_base->GetBinContent(b)), fabs(h_wjet_base->GetBinContent(b) - h_wjet_bTagMinus->GetBinContent(b))) <<" \\\\ "<<endl;  
  outFile<<"\\hline "<<endl;  
  
  outFile<<"Z+Jets"<<" & "<<h_zjet_base->GetBinContent(b)<<" $\\pm$ "<<h_zjet_base->GetBinError(b)<<" $\\pm$ "<< sqrt(pow(TMath::Max(fabs(h_zjet_JESPlus->GetBinContent(b) - h_zjet_base->GetBinContent(b)), fabs(h_zjet_base->GetBinContent(b) - h_zjet_JESMinus->GetBinContent(b))), 2) + pow(TMath::Max(fabs(h_zjet_JERPlus->GetBinContent(b) - h_zjet_base->GetBinContent(b)), fabs(h_zjet_base->GetBinContent(b) - h_zjet_JERMinus->GetBinContent(b))), 2) + pow(TMath::Max(fabs(h_zjet_TopPtPlus->GetBinContent(b) - h_zjet_base->GetBinContent(b)), fabs(h_zjet_base->GetBinContent(b) - h_zjet_TopPtMinus->GetBinContent(b))), 2)) <<" $\\pm$ "<<TMath::Max(fabs(h_zjet_bTagPlus->GetBinContent(b) - h_zjet_base->GetBinContent(b)), fabs(h_zjet_base->GetBinContent(b) - h_zjet_bTagMinus->GetBinContent(b))) <<" \\\\ "<<endl;
  outFile<<"\\hline "<<endl;

  outFile<<"QCD"<<" & "<<h_qcd_base->GetBinContent(b)<<" $\\pm$ "<<h_qcd_base->GetBinError(b)<<" $\\pm$ "<< sqrt(pow(TMath::Max(fabs(h_qcd_JESPlus->GetBinContent(b) - h_qcd_base->GetBinContent(b)), fabs(h_qcd_base->GetBinContent(b) - h_qcd_JESMinus->GetBinContent(b))), 2) + pow(TMath::Max(fabs(h_qcd_JERPlus->GetBinContent(b) - h_qcd_base->GetBinContent(b)), fabs(h_qcd_base->GetBinContent(b) - h_qcd_JERMinus->GetBinContent(b))), 2) + pow(TMath::Max(fabs(h_qcd_TopPtPlus->GetBinContent(b) - h_qcd_base->GetBinContent(b)), fabs(h_qcd_base->GetBinContent(b) - h_qcd_TopPtMinus->GetBinContent(b))), 2)) <<" $\\pm$ "<<TMath::Max(fabs(h_qcd_bTagPlus->GetBinContent(b) - h_qcd_base->GetBinContent(b)), fabs(h_qcd_base->GetBinContent(b) - h_qcd_bTagMinus->GetBinContent(b))) <<" \\\\ "<<endl;
  outFile<<"\\hline "<<endl;

  outFile<<"SingleTop"<<" & "<<h_stop_base->GetBinContent(b)<<" $\\pm$ "<<h_stop_base->GetBinError(b)<<" $\\pm$ "<< sqrt(pow(TMath::Max(fabs(h_stop_JESPlus->GetBinContent(b) - h_stop_base->GetBinContent(b)), fabs(h_stop_base->GetBinContent(b) - h_stop_JESMinus->GetBinContent(b))), 2) + pow(TMath::Max(fabs(h_stop_JERPlus->GetBinContent(b) - h_stop_base->GetBinContent(b)), fabs(h_stop_base->GetBinContent(b) - h_stop_JERMinus->GetBinContent(b))), 2) + pow(TMath::Max(fabs(h_stop_TopPtPlus->GetBinContent(b) - h_stop_base->GetBinContent(b)), fabs(h_stop_base->GetBinContent(b) - h_stop_TopPtMinus->GetBinContent(b))), 2)) <<" $\\pm$ "<<TMath::Max(fabs(h_stop_bTagPlus->GetBinContent(b) - h_stop_base->GetBinContent(b)), fabs(h_stop_base->GetBinContent(b) - h_stop_bTagMinus->GetBinContent(b))) <<" \\\\ "<<endl;
  outFile<<"\\hline "<<endl;

  outFile<<"Dibosons"<<" & "<<h_diboson_base->GetBinContent(b)<<" $\\pm$ "<<h_diboson_base->GetBinError(b)<<" $\\pm$ "<< sqrt(pow(TMath::Max(fabs(h_diboson_JESPlus->GetBinContent(b) - h_diboson_base->GetBinContent(b)), fabs(h_diboson_base->GetBinContent(b) - h_diboson_JESMinus->GetBinContent(b))), 2) + pow(TMath::Max(fabs(h_diboson_JERPlus->GetBinContent(b) - h_diboson_base->GetBinContent(b)), fabs(h_diboson_base->GetBinContent(b) - h_diboson_JERMinus->GetBinContent(b))), 2) + pow(TMath::Max(fabs(h_diboson_TopPtPlus->GetBinContent(b) - h_diboson_base->GetBinContent(b)), fabs(h_diboson_base->GetBinContent(b) - h_diboson_TopPtMinus->GetBinContent(b))), 2)) <<" $\\pm$ "<<TMath::Max(fabs(h_diboson_bTagPlus->GetBinContent(b) - h_diboson_base->GetBinContent(b)), fabs(h_diboson_base->GetBinContent(b) - h_diboson_bTagMinus->GetBinContent(b))) <<" \\\\ "<<endl;
  outFile<<"\\hline "<<endl;
  outFile<<"\\hline "<<endl;
  outFile<<"Total Bkg"<<" & "<<h_TotalBkg->GetBinContent(b)<<" $\\pm$ "<<h_TotalBkg->GetBinError(b)<<" $\\pm$ "<<" -- "<<" $\\pm$ "<<" -- "<<" \\\\ "<<endl;
  outFile<<"\\hline "<<endl;   
  outFile<<"\\hline "<<endl;  
  outFile<<" Data "<<" & "<<h_data->GetBinContent(b)<<" \\\\ "<<endl; 
  outFile<<"\\hline "<<endl;    
  outFile<<"\\hline "<<endl;   
  outFile<<"\\end{tabular}"<<endl; 
  //outFile<<"\\end{LARGE}"<<endl;  
  outFile<<"\\end{center}"<<endl;
  outFile<<"\\caption{First table}"<<endl;
  outFile<<"\\end{table}"<<endl;

  //Add another table with JESUP
  double Nbin = 14;
 
  makeCutFlowTableAny(outFile, "base", Nbin, 		h_wh_base,  	h_ttbar_base, h_stop_base, h_wjet_base, h_zjet_base, h_qcd_base, h_stop_base, h_diboson_base, h_data);
  makeCutFlowTableAny(outFile, "JESPlus", Nbin, 	h_wh_JESPlus, 	h_ttbar_JESPlus, h_stop_JESPlus, h_wjet_JESPlus, h_zjet_JESPlus, h_qcd_JESPlus, h_stop_JESPlus, h_diboson_JESPlus, h_data);
  makeCutFlowTableAny(outFile, "JESMinus", Nbin, 	h_wh_JESMinus, 	h_ttbar_JESMinus,h_stop_JERMinus, h_wjet_JESMinus, h_zjet_JESMinus, h_qcd_JESMinus, h_stop_JESMinus, h_diboson_JESMinus, h_data);
  makeCutFlowTableAny(outFile, "JERPlus", Nbin, 	h_wh_JERPlus, 	h_ttbar_JERPlus, h_stop_JERPlus, h_wjet_JERPlus, h_zjet_JERPlus, h_qcd_JERPlus, h_stop_JERPlus, h_diboson_JERPlus, h_data);
  makeCutFlowTableAny(outFile, "JERMinus", Nbin, 	h_wh_JERMinus, 	h_ttbar_JERMinus, h_stop_JERMinus, h_wjet_JERMinus, h_zjet_JERMinus, h_qcd_JERMinus, h_stop_JERMinus, h_diboson_JERMinus, h_data);
  makeCutFlowTableAny(outFile, "TopPtPlus", Nbin, 	h_wh_TopPtPlus, h_ttbar_TopPtPlus, h_stop_TopPtPlus, h_wjet_TopPtPlus, h_zjet_TopPtPlus, h_qcd_TopPtPlus, h_stop_TopPtPlus, h_diboson_TopPtPlus, h_data);
  makeCutFlowTableAny(outFile, "TopPtMinus", Nbin, 	h_wh_TopPtMinus, h_ttbar_TopPtMinus, h_stop_TopPtMinus, h_wjet_TopPtMinus, h_zjet_TopPtMinus, h_qcd_TopPtMinus, h_stop_TopPtMinus, h_diboson_TopPtMinus, h_data);
  makeCutFlowTableAny(outFile, "bTagPlus", Nbin, 	h_wh_bTagPlus, 	h_ttbar_bTagPlus, h_stop_bTagPlus, h_wjet_bTagPlus, h_zjet_bTagPlus, h_qcd_bTagPlus, h_stop_bTagPlus, h_diboson_bTagPlus, h_data);
  makeCutFlowTableAny(outFile, "bTagMinus", Nbin, 	h_wh_bTagMinus, h_ttbar_bTagMinus, h_stop_bTagMinus, h_wjet_bTagMinus, h_zjet_bTagMinus, h_qcd_bTagMinus, h_stop_bTagMinus, h_diboson_bTagMinus, h_data);
  outFile<<"\\end{document}"<<endl;  
  outFile.close(); 
} 

