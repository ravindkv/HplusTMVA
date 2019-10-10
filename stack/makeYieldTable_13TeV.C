#include <iostream>
#include <fstream>
#include <iomanip>

bool isMuChannel = false;
bool isEleChannel = true;

double sysUncJESTopPt( TH1F * h_JESPlus, TH1F * h_base, TH1F * h_JESMinus, TH1F * h_JERPlus, TH1F * h_JERMinus, TH1F * h_TopPtPlus, TH1F * h_TopPtMinus, int b){
  double uncJES = pow(TMath::Max(fabs(h_JESPlus->GetBinContent(b) - h_base->GetBinContent(b)), fabs(h_base->GetBinContent(b) - h_JESMinus->GetBinContent(b))), 2);
  double uncJER = pow(TMath::Max(fabs(h_JERPlus->GetBinContent(b) - h_base->GetBinContent(b)), fabs(h_base->GetBinContent(b) - h_JERMinus->GetBinContent(b))), 2);
  double uncTop = pow(TMath::Max(fabs(h_TopPtPlus->GetBinContent(b) - h_base->GetBinContent(b)), fabs(h_base->GetBinContent(b) - h_TopPtMinus->GetBinContent(b))), 2);
  double unc = sqrt(uncJES +uncJER  +uncTop);
  return unc ;
}

double sysUncBCTag (TH1F * h_bTagPlus, TH1F * h_base, TH1F * h_bTagMinus, int b){
	double uncTag = TMath::Max(fabs(h_bTagPlus->GetBinContent(b) - h_base->GetBinContent(b)), fabs(h_base->GetBinContent(b) - h_bTagMinus->GetBinContent(b)));
	return uncTag;
}	

//Relative sys unc
double relSysUncJetMET( TH1F * h_JESPlus, TH1F * h_base, TH1F * h_JESMinus, TH1F * h_JERPlus, TH1F * h_JERMinus, int b){
  double uncJES = pow(TMath::Max(fabs(h_JESPlus->GetBinContent(b) - h_base->GetBinContent(b)), fabs(h_base->GetBinContent(b) - h_JESMinus->GetBinContent(b))), 2);
  double uncJER = pow(TMath::Max(fabs(h_JERPlus->GetBinContent(b) - h_base->GetBinContent(b)), fabs(h_base->GetBinContent(b) - h_JERMinus->GetBinContent(b))), 2);
  double unc = 100*(sqrt(uncJES +uncJER)/h_base->GetBinContent(b));
  return unc ;
}

double relSysUncTopPt( TH1F * h_base, TH1F * h_TopPtPlus, TH1F * h_TopPtMinus, int b){
  double uncTop = pow(TMath::Max(fabs(h_TopPtPlus->GetBinContent(b) - h_base->GetBinContent(b)), fabs(h_base->GetBinContent(b) - h_TopPtMinus->GetBinContent(b))), 2);
  double unc = 100*(sqrt(uncTop)/h_base->GetBinContent(b));
  return unc ;
}
double relSysUncBCTag (TH1F * h_bTagPlus, TH1F * h_base, TH1F * h_bTagMinus, int b){
	double uncTag = TMath::Max(fabs(h_bTagPlus->GetBinContent(b) - h_base->GetBinContent(b)), fabs(h_base->GetBinContent(b) - h_bTagMinus->GetBinContent(b)));
	return 100*(uncTag/h_base->GetBinContent(b));
}

double relStatUnc (TH1F * h_base, int b){
	return 100*(h_base->GetBinError(b)/h_base->GetBinContent(b));
}


string printCutFlowHist(string histname, TH1F *h, int Nbin, double sf, bool isPrecision=false){
   string allBinValue = histname;
   for(int i =1; i<Nbin; i++){
     ostringstream convert;
     string Result("");
     //allBinValue += "h->GetBinContent(i)" + " & ";
     if(isPrecision) convert <<std::setprecision(3)<<sf*h->GetBinContent(i);
     else convert <<sf*h->GetBinContent(i);
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
  ///outFile<<"\\footnotesize\\setlength{\\tabcolsep}{0.3pt}"<<endl;
  outFile<<"\\begin{tabular}{ | c| c| c| c| c| c| c| c| c| c| c| c| c|c|c|c|}"<<endl; 
  outFile<<"\\multicolumn{5}{c}{ } \\\\"<<endl; 
  outFile<<"\\hline "<<endl;
  if(isMuChannel) outFile<<"\\multicolumn{1}{| c|}{"+ sys +" } & \\multicolumn{1}{ c|}{ $HLT\\_IsoMu24$ } & \\multicolumn{1}{ c|}{ $N_{muon}=1$ } &\\multicolumn{1}{ c|}{ $N_{jets}\\ge 4$ } & \\multicolumn{1}{ c|}{ $\\not\\!\\!E_T \\ge 20GeV$ }&  \\multicolumn{1}{ c |}{ $\\ge$ 2 b-jets }& \\multicolumn{1}{ c|}{KinFit Sel. } & \\multicolumn{1}{ c|}{1 c-jet} \\\\ "<<endl;
  if(isEleChannel) outFile<<"\\multicolumn{1}{| c|}{"+ sys +" } & \\multicolumn{1}{ c|}{ $HLT\\_Ele27$ } & \\multicolumn{1}{ c|}{ $N_{ele}=1$ } &\\multicolumn{1}{ c|}{ $N_{jets}\\ge 4$ } & \\multicolumn{1}{ c|}{ $\\not\\!\\!E_T \\ge 20GeV$ }&  \\multicolumn{1}{ c |}{ $\\ge$ 2 b-jets }& \\multicolumn{1}{ c|}{KinFit Sel. } & \\multicolumn{1}{ c|}{1 c-jet} \\\\ "<<endl;
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

  outFile<<printCutFlowHist("MC signal ($M_{H^\\pm}=120$ GeV)", 	h_wh, 		Nbin, 1)<<" \\\\ "<<endl;
  outFile<<"\\hline "<<endl;
  outFile<<printCutFlowHist("SM $t\\bar{t}$ + jets", 	h_ttbar, 	Nbin, 1)<<" \\\\ "<<endl;
  outFile<<printCutFlowHist("Single t", 	h_stop, 	Nbin, 1)<<" \\\\ "<<endl;
  outFile<<printCutFlowHist("W + jets", 	h_wjets, 	Nbin, 1)<<" \\\\ "<<endl;
  outFile<<printCutFlowHist("$Z/\\gamma$ + jets", 	h_dyjets, 	Nbin, 1)<<" \\\\ "<<endl;
  outFile<<printCutFlowHist("MC QCD", 	h_qcd, 		Nbin, 1)<<" \\\\ "<<endl;
  outFile<<printCutFlowHist("VV", 	h_vv, 		Nbin, 1)<<" \\\\ "<<endl;
  outFile<<"\\hline "<<endl;
  outFile<<printCutFlowHist("Bkg", 	h_MC, 		Nbin, 1)<<" \\\\ "<<endl;
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

void makeHiggsBkgTable(ofstream &outFile, string sys, int Nbin, 
		TH1F* h_GluGluHToBB,           
		TH1F* h_GluGluHToTauTau,       
		TH1F* h_GluGluHToCC,           
		TH1F* h_GluGluHToGG,           
		TH1F* h_GluGluHToWWTo2L2Nu,    
		TH1F* h_GluGluHToWWToLNuQQ,    
		TH1F* h_GluGluHToZZTo2L2Q,     
		TH1F* h_GluGluHToZZTo4L,       
		TH1F* h_WplusH_HToBB_WToLNu,   
		TH1F* h_WplusH_HToBB_WToQQ,    
		TH1F* h_WplusHToTauTau,        
		TH1F* h_WplusH_HToCC_WToLNu,   
		TH1F* h_WplusH_HToCC_WToQQ,    
		TH1F* h_WplusH_HToGG_WToAll,   
		TH1F* h_WminusH_HToBB_WToQQ,   
		TH1F* h_WminusHToTauTau,       
		TH1F* h_WminusH_HToCC_WToLNu,  
		TH1F* h_WminusH_HToCC_WToQQ,   
		TH1F* h_WminusH_HToGG_WToAll,  
		TH1F* h_WminusH_HToZZTo2L2X,   
		TH1F* h_ZH_HToBB_ZToNuNu,      
		TH1F* h_ZH_HToBB_ZToLL,        
		TH1F* h_ZH_HToBB_ZToQQ,        
		TH1F* h_ZHToTauTau,            
		TH1F* h_ZH_HToCC_ZToNuNu,      
		TH1F* h_ZH_HToCC_ZToLL,        
		TH1F* h_ZH_HToCC_ZToQQ,        
		TH1F* h_ZH_HToGG_ZToAll,       
		TH1F* h_ZH_HToZZ_2L,           
		TH1F* h_ggZH_HToBB_ZToNuNu,    
		TH1F* h_ggZH_HToBB_ZToLL,      
		TH1F* h_ggZH_HToBB_ZToQQ,      
		TH1F* h_ggZH_HToCC_ZToNuNu,    
		TH1F* h_ggZH_HToCC_ZToLL,      
		TH1F* h_ggZH_HToCC_ZToQQ,      
		TH1F* h_GluGluZH_HToWW,        
		TH1F* h_ttHToCC,               
		TH1F* h_ttHToGG,               
		TH1F* h_bbHToBB,               
		TH1F* h_bbHToGG,               
		TH1F* h_bbHToWWTo2L2Nu,        
		TH1F* h_bbH_HToZZTo4L,         
		TH1F* h_VBFHToBB,              
		TH1F* h_VBFHToTauTau,          
		TH1F* h_VBFHToCC,              
		TH1F* h_VBFHToGG,              
		TH1F* h_VBFHToWWTo2L2Nu,       
		TH1F* h_VBFHToWWToLNuQQ){       

  outFile<<""<<endl;
  outFile<<"%%%%%%%%%%%%%%%%%% NEXT TABLE: "+sys+" %%%%%%%%%%%%%%%%%"<<endl;
  outFile<<"\\begin{table}"<<endl; 
  outFile<<"\\begin{center}"<<endl; 
  //outFile<<"%\\begin{LARGE}"<<endl;
  ///outFile<<"\\footnotesize\\setlength{\\tabcolsep}{0.3pt}"<<endl;
  outFile<<"\\small{"<<endl;
  outFile<<"\\begin{tabular}{ | c| c| c| c| c| c| c| c| c| c| c| c| c|c|c|c|}"<<endl; 
  outFile<<"\\multicolumn{5}{c}{ } \\\\"<<endl; 
  outFile<<"\\hline "<<endl;
  if(isMuChannel) outFile<<"\\multicolumn{1}{| c|}{"+ sys +" } & \\multicolumn{1}{ c|}{ $HLT\\_IsoMu24$ } & \\multicolumn{1}{ c|}{ $N_{muon}=1$ } &\\multicolumn{1}{ c|}{ $N_{jets}\\ge 4$ } & \\multicolumn{1}{ c|}{ $\\not\\!\\!E_T \\ge 20GeV$ }&  \\multicolumn{1}{ c |}{ $\\ge$ 2 b-jets }& \\multicolumn{1}{ c|}{KinFit Sel. } & \\multicolumn{1}{ c|}{1 c-jet} \\\\ "<<endl;
  if(isEleChannel) outFile<<"\\multicolumn{1}{| c|}{"+ sys +" } & \\multicolumn{1}{ c|}{ $HLT\\_Ele27$ } & \\multicolumn{1}{ c|}{ $N_{ele}=1$ } &\\multicolumn{1}{ c|}{ $N_{jets}\\ge 4$ } & \\multicolumn{1}{ c|}{ $\\not\\!\\!E_T \\ge 20GeV$ }&  \\multicolumn{1}{ c |}{ $\\ge$ 2 b-jets }& \\multicolumn{1}{ c|}{KinFit Sel. } & \\multicolumn{1}{ c|}{1 c-jet} \\\\ "<<endl;
  outFile<<"\\hline "<<endl;
  outFile<<"\\hline "<<endl;
  TH1F* h_MC = (TH1F*)h_GluGluHToBB->Clone("allHiggsBkg");
  h_MC->Add(h_GluGluHToTauTau);       
  h_MC->Add(h_GluGluHToCC);           
  h_MC->Add(h_GluGluHToGG);           
  h_MC->Add(h_GluGluHToWWTo2L2Nu);    
  h_MC->Add(h_GluGluHToWWToLNuQQ);    
  h_MC->Add(h_GluGluHToZZTo2L2Q);     
  h_MC->Add(h_GluGluHToZZTo4L);       
  //W+H production
  h_MC->Add(h_WplusH_HToBB_WToLNu);   
  h_MC->Add(h_WplusH_HToBB_WToQQ);    
  h_MC->Add(h_WplusHToTauTau);        
  h_MC->Add(h_WplusH_HToCC_WToLNu);   
  h_MC->Add(h_WplusH_HToCC_WToQQ);    
  h_MC->Add(h_WplusH_HToGG_WToAll);   
  //W-H production
  h_MC->Add(h_WminusH_HToBB_WToQQ);   
  h_MC->Add(h_WminusHToTauTau);       
  h_MC->Add(h_WminusH_HToCC_WToLNu);  
  h_MC->Add(h_WminusH_HToCC_WToQQ);   
  h_MC->Add(h_WminusH_HToGG_WToAll);  
  h_MC->Add(h_WminusH_HToZZTo2L2X);   
  //ZH production
  h_MC->Add(h_ZH_HToBB_ZToNuNu);      
  h_MC->Add(h_ZH_HToBB_ZToLL);        
  h_MC->Add(h_ZH_HToBB_ZToQQ);        
  h_MC->Add(h_ZHToTauTau);            
  h_MC->Add(h_ZH_HToCC_ZToNuNu);      
  h_MC->Add(h_ZH_HToCC_ZToLL);        
  h_MC->Add(h_ZH_HToCC_ZToQQ);        
  h_MC->Add(h_ZH_HToGG_ZToAll);       
  h_MC->Add(h_ZH_HToZZ_2L);           
  //gg fusion to ZH
  h_MC->Add(h_ggZH_HToBB_ZToNuNu);    
  h_MC->Add(h_ggZH_HToBB_ZToLL);      
  h_MC->Add(h_ggZH_HToBB_ZToQQ);      
  h_MC->Add(h_ggZH_HToCC_ZToNuNu);    
  h_MC->Add(h_ggZH_HToCC_ZToLL);      
  h_MC->Add(h_ggZH_HToCC_ZToQQ);      
  h_MC->Add(h_GluGluZH_HToWW);        
  //tt fusion
  h_MC->Add(h_ttHToCC);               
  h_MC->Add(h_ttHToGG);               
  //bb fusion
  h_MC->Add(h_bbHToBB);               
  h_MC->Add(h_bbHToGG);               
  h_MC->Add(h_bbHToWWTo2L2Nu);        
  h_MC->Add(h_bbH_HToZZTo4L);         
  //vector boson fustion
  h_MC->Add(h_VBFHToBB);              
  h_MC->Add(h_VBFHToTauTau);          
  h_MC->Add(h_VBFHToCC);              
  h_MC->Add(h_VBFHToGG);              
  h_MC->Add(h_VBFHToWWTo2L2Nu);       
  h_MC->Add(h_VBFHToWWToLNuQQ);       

  //Gluon gluon fusion 						//Gluon gluon fusion
  outFile<<printCutFlowHist("GluGluHToBB",                        h_GluGluHToBB, Nbin, 1, true)<<" \\\\ "<<endl;           
  outFile<<printCutFlowHist("GluGluHToTauTau",                    h_GluGluHToTauTau, Nbin, 1, true)<<" \\\\ "<<endl;       
  outFile<<printCutFlowHist("GluGluHToCC",                        h_GluGluHToCC, Nbin, 1, true)<<" \\\\ "<<endl;           
  outFile<<printCutFlowHist("GluGluHToGG",                        h_GluGluHToGG, Nbin, 1, true)<<" \\\\ "<<endl;           
  outFile<<printCutFlowHist("GluGluHToWWTo2L2Nu",                 h_GluGluHToWWTo2L2Nu, Nbin, 1, true)<<" \\\\ "<<endl;    
  outFile<<printCutFlowHist("GluGluHToWWToLNuQQ",                 h_GluGluHToWWToLNuQQ, Nbin, 1, true)<<" \\\\ "<<endl;    
  outFile<<printCutFlowHist("GluGluHToZZTo2L2Q",                  h_GluGluHToZZTo2L2Q, Nbin, 1, true)<<" \\\\ "<<endl;     
  outFile<<printCutFlowHist("GluGluHToZZTo4L",                    h_GluGluHToZZTo4L, Nbin, 1, true)<<" \\\\ "<<endl;       
  outFile<<"\\hline "<<endl;                                             
  //W+H production                                                //W+H production
  outFile<<printCutFlowHist("WplusH\\_HToBB\\_WToLNu",            h_WplusH_HToBB_WToLNu, Nbin, 1, true)<<" \\\\ "<<endl;   
  outFile<<printCutFlowHist("WplusH\\_HToBB\\_WToQQ",             h_WplusH_HToBB_WToQQ, Nbin, 1, true)<<" \\\\ "<<endl;    
  outFile<<printCutFlowHist("WplusHToTauTau",                     h_WplusHToTauTau, Nbin, 1, true)<<" \\\\ "<<endl;        
  outFile<<printCutFlowHist("WplusH\\_HToCC\\_WToLNu",            h_WplusH_HToCC_WToLNu, Nbin, 1, true)<<" \\\\ "<<endl;   
  outFile<<printCutFlowHist("WplusH\\_HToCC\\_WToQQ",             h_WplusH_HToCC_WToQQ, Nbin, 1, true)<<" \\\\ "<<endl;    
  outFile<<printCutFlowHist("WplusH\\_HToGG\\_WToAll",            h_WplusH_HToGG_WToAll, Nbin, 1, true)<<" \\\\ "<<endl;   
  outFile<<"\\hline "<<endl;                                             
  //W-H production                                                //W-H production
  outFile<<printCutFlowHist("WminusH\\_HToBB\\_WToQQ",            h_WminusH_HToBB_WToQQ, Nbin, 1, true)<<" \\\\ "<<endl;   
  outFile<<printCutFlowHist("WminusHToTauTau",                    h_WminusHToTauTau, Nbin, 1, true)<<" \\\\ "<<endl;       
  outFile<<printCutFlowHist("WminusH\\_HToCC\\_WToLNu",           h_WminusH_HToCC_WToLNu, Nbin, 1, true)<<" \\\\ "<<endl;  
  outFile<<printCutFlowHist("WminusH\\_HToCC\\_WToQQ",            h_WminusH_HToCC_WToQQ, Nbin, 1, true)<<" \\\\ "<<endl;   
  outFile<<printCutFlowHist("WminusH\\_HToGG\\_WToAll",           h_WminusH_HToGG_WToAll, Nbin, 1, true)<<" \\\\ "<<endl;  
  outFile<<printCutFlowHist("WminusH\\_HToZZTo2L2X",              h_WminusH_HToZZTo2L2X, Nbin, 1, true)<<" \\\\ "<<endl;   
  outFile<<"\\hline "<<endl;                                             
  //ZH production                                                 //ZH production
  outFile<<printCutFlowHist("ZH\\_HToBB\\_ZToNuNu",               h_ZH_HToBB_ZToNuNu, Nbin, 1, true)<<" \\\\ "<<endl;      
  outFile<<printCutFlowHist("ZH\\_HToBB\\_ZToLL",                 h_ZH_HToBB_ZToLL, Nbin, 1, true)<<" \\\\ "<<endl;        
  outFile<<printCutFlowHist("ZH\\_HToBB\\_ZToQQ",                 h_ZH_HToBB_ZToQQ, Nbin, 1, true)<<" \\\\ "<<endl;        
  outFile<<printCutFlowHist("ZHToTauTau",                         h_ZHToTauTau, Nbin, 1, true)<<" \\\\ "<<endl;            
  outFile<<printCutFlowHist("ZH\\_HToCC\\_ZToNuNu",               h_ZH_HToCC_ZToNuNu, Nbin, 1, true)<<" \\\\ "<<endl;      
  outFile<<printCutFlowHist("ZH\\_HToCC\\_ZToLL",                 h_ZH_HToCC_ZToLL, Nbin, 1, true)<<" \\\\ "<<endl;        
  outFile<<printCutFlowHist("ZH\\_HToCC\\_ZToQQ",                 h_ZH_HToCC_ZToQQ, Nbin, 1, true)<<" \\\\ "<<endl;        
  outFile<<printCutFlowHist("ZH\\_HToGG\\_ZToAll",                h_ZH_HToGG_ZToAll, Nbin, 1, true)<<" \\\\ "<<endl;       
  outFile<<printCutFlowHist("ZH\\_HToZZ\\_2L",                    h_ZH_HToZZ_2L, Nbin, 1, true)<<" \\\\ "<<endl;           
  outFile<<"\\hline "<<endl;                                             
  //gg fusion to ZH                                               //gg fusion to ZH
  outFile<<printCutFlowHist("ggZH\\_HToBB\\_ZToNuNu",             h_ggZH_HToBB_ZToNuNu, Nbin, 1, true)<<" \\\\ "<<endl;    
  outFile<<printCutFlowHist("ggZH\\_HToBB\\_ZToLL",               h_ggZH_HToBB_ZToLL, Nbin, 1, true)<<" \\\\ "<<endl;      
  outFile<<printCutFlowHist("ggZH\\_HToBB\\_ZToQQ",               h_ggZH_HToBB_ZToQQ, Nbin, 1, true)<<" \\\\ "<<endl;      
  outFile<<printCutFlowHist("ggZH\\_HToCC\\_ZToNuNu",             h_ggZH_HToCC_ZToNuNu, Nbin, 1, true)<<" \\\\ "<<endl;    
  outFile<<printCutFlowHist("ggZH\\_HToCC\\_ZToLL",               h_ggZH_HToCC_ZToLL, Nbin, 1, true)<<" \\\\ "<<endl;      
  outFile<<printCutFlowHist("ggZH\\_HToCC\\_ZToQQ",               h_ggZH_HToCC_ZToQQ, Nbin, 1, true)<<" \\\\ "<<endl;      
  outFile<<printCutFlowHist("GluGluZH\\_HToWW",                   h_GluGluZH_HToWW, Nbin, 1, true)<<" \\\\ "<<endl;        
  outFile<<"\\hline "<<endl;                                             
  //tt fusion                                                     //tt fusion
  outFile<<printCutFlowHist("ttHToCC",                            h_ttHToCC, Nbin, 1, true)<<" \\\\ "<<endl;               
  outFile<<printCutFlowHist("ttHToGG",                            h_ttHToGG, Nbin, 1, true)<<" \\\\ "<<endl;               
  outFile<<"\\hline "<<endl;                                             
  //bb fusion                                                     //bb fusion
  outFile<<printCutFlowHist("bbHToBB",                            h_bbHToBB, Nbin, 1, true)<<" \\\\ "<<endl;               
  outFile<<printCutFlowHist("bbHToGG",                            h_bbHToGG, Nbin, 1, true)<<" \\\\ "<<endl;               
  outFile<<printCutFlowHist("bbHToWWTo2L2Nu",                     h_bbHToWWTo2L2Nu, Nbin, 1, true)<<" \\\\ "<<endl;        
  outFile<<printCutFlowHist("bbH\\_HToZZTo4L",                    h_bbH_HToZZTo4L, Nbin, 1, true)<<" \\\\ "<<endl;         
  outFile<<"\\hline "<<endl;                                             
  //vector boson fustion                                          //vector boson fustion
  outFile<<printCutFlowHist("VBFHToBB",                           h_VBFHToBB, Nbin, 1, true)<<" \\\\ "<<endl;              
  outFile<<printCutFlowHist("VBFHToTauTau",                       h_VBFHToTauTau, Nbin, 1, true)<<" \\\\ "<<endl;          
  outFile<<printCutFlowHist("VBFHToCC",                           h_VBFHToCC, Nbin, 1, true)<<" \\\\ "<<endl;              
  outFile<<printCutFlowHist("VBFHToGG",                           h_VBFHToGG, Nbin, 1, true)<<" \\\\ "<<endl;              
  outFile<<printCutFlowHist("VBFHToWWTo2L2Nu",                    h_VBFHToWWTo2L2Nu, Nbin, 1, true)<<" \\\\ "<<endl;       
  outFile<<printCutFlowHist("VBFHToWWToLNuQQ",                    h_VBFHToWWToLNuQQ, Nbin, 1, true)<<" \\\\ "<<endl;       
  outFile<<"\\hline "<<endl;                              
  outFile<<"\\hline "<<endl;                                           
  outFile<<printCutFlowHist("Total Higgs Bkg.",       	          h_MC,    		 Nbin, 1, true)<<" \\\\ "<<endl;
  outFile<<"\\hline "<<endl;
  outFile<<"\\end{tabular}"<<endl;
  outFile<<"} "<<endl;
  //outFile<<"%\\end{LARGE}"<<endl; 
  outFile<<"\\end{center}"<<endl; 
  outFile<<"\\caption{Number of evets after various cuts from SM Higgs production for sys: " +sys+ "}"<<endl; 
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
  ///outFile<<"\\footnotesize\\setlength{\\tabcolsep}{0.3pt}"<<endl;
  outFile<<"\\begin{tabular}{ | c| c| c| c| c| c| c| c| c| c| c| c| c|c|c|c|}"<<endl; 
  outFile<<"\\multicolumn{5}{c}{ } \\\\"<<endl; 
  outFile<<"\\hline "<<endl;
  if(isMuChannel) outFile<<"\\multicolumn{1}{| c|}{"+ sys +" } & \\multicolumn{1}{ c|}{ $HLT\\_IsoMu24$ } & \\multicolumn{1}{ c|}{ $N_{muon}=1$ } &\\multicolumn{1}{ c|}{ $N_{jets}\\ge 4$ } & \\multicolumn{1}{ c|}{ $\\not\\!\\!E_T \\ge 20GeV$ }&  \\multicolumn{1}{ c |}{ $\\ge$ 2 b-jets }& \\multicolumn{1}{ c|}{KinFit Sel. } & \\multicolumn{1}{ c|}{1 c-jet} \\\\ "<<endl;
  if(isEleChannel) outFile<<"\\multicolumn{1}{| c|}{"+ sys +" } & \\multicolumn{1}{ c|}{ $HLT\\_Ele27$ } & \\multicolumn{1}{ c|}{ $N_{ele}=1$ } &\\multicolumn{1}{ c|}{ $N_{jets}\\ge 4$ } & \\multicolumn{1}{ c|}{ $\\not\\!\\!E_T \\ge 20GeV$ }&  \\multicolumn{1}{ c |}{ $\\ge$ 2 b-jets }& \\multicolumn{1}{ c|}{KinFit Sel. } & \\multicolumn{1}{ c|}{1 c-jet} \\\\ "<<endl;
  outFile<<"\\hline "<<endl;
  outFile<<"\\hline "<<endl;
  outFile<<printCutFlowHist("MC signal ($M_{H^\\pm}=80$ GeV)", 	h_wh80, 		Nbin, 1)<<" \\\\ "<<endl;
  outFile<<printCutFlowHist("MC signal ($M_{H^\\pm}=90$ GeV)",  h_wh90, 		Nbin, 1)<<" \\\\ "<<endl;
  outFile<<printCutFlowHist("MC signal ($M_{H^\\pm}=100$ GeV)",  h_wh100, 		Nbin, 1)<<" \\\\ "<<endl;
  outFile<<printCutFlowHist("MC signal ($M_{H^\\pm}=120$ GeV)",  h_wh120, 		Nbin, 1)<<" \\\\ "<<endl;
  outFile<<printCutFlowHist("MC signal ($M_{H^\\pm}=140$ GeV)",  h_wh140, 		Nbin, 1)<<" \\\\ "<<endl;
  outFile<<printCutFlowHist("MC signal ($M_{H^\\pm}=150$ GeV)",  h_wh150, 		Nbin, 1)<<" \\\\ "<<endl;
  outFile<<printCutFlowHist("MC signal ($M_{H^\\pm}=155$ GeV)",  h_wh155, 		Nbin, 1)<<" \\\\ "<<endl;
  outFile<<printCutFlowHist("MC signal ($M_{H^\\pm}=160$ GeV)",  h_wh160, 		Nbin, 1)<<" \\\\ "<<endl;
  outFile<<"\\hline "<<endl;
  outFile<<"\\hline "<<endl;
  outFile<<"\\end{tabular}"<<endl;
  //outFile<<"%\\end{LARGE}"<<endl; 
  outFile<<"\\end{center}"<<endl; 
  outFile<<"\\caption{Number of evets after various cuts for sys: " +sys+ "}"<<endl; 
  outFile<<"\\end{table}"<<endl; 
}

void makeSignalTable(TString histSubDir="Iso/", TString histName="cutflow"){  
#include "makeYieldTable_13TeV.h" 

  ofstream outFile; 
  outFile.open("signalTable.tex"); 
   
  //outFile<<"\\documentclass[landscape,letterpaper]{article}"<<endl;  
  outFile<<"\\documentclass{article}"<<endl;  
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
  double Nbin = 8;
  getSignalCutFlowTable(outFile, "base", Nbin, 		h_wh80_base,  		h_wh90_base,  		h_wh100_base,  	  	h_wh120_base,  	   h_wh140_base,      h_wh150_base,  	 h_wh155_base,       h_wh160_base      ); 
  getSignalCutFlowTable(outFile, "JESPlus", Nbin, 	h_wh80_JESPlus, 	h_wh90_JESPlus,         h_wh100_JESPlus,        h_wh120_JESPlus,   h_wh140_JESPlus,   h_wh150_JESPlus,   h_wh155_JESPlus,    h_wh160_JESPlus   ); 
  getSignalCutFlowTable(outFile, "JESMinus", Nbin, 	h_wh80_JESMinus, 	h_wh90_JESMinus,        h_wh100_JESMinus,       h_wh120_JESMinus,  h_wh140_JESMinus,  h_wh150_JESMinus,  h_wh155_JESMinus,   h_wh160_JESMinus  );
  getSignalCutFlowTable(outFile, "JERPlus", Nbin, 	h_wh80_JERPlus, 	h_wh90_JERPlus,         h_wh100_JERPlus,        h_wh120_JERPlus,   h_wh140_JERPlus,   h_wh150_JERPlus,   h_wh155_JERPlus,    h_wh160_JERPlus   );
  getSignalCutFlowTable(outFile, "JERMinus", Nbin, 	h_wh80_JERMinus, 	h_wh90_JERMinus,        h_wh100_JERMinus,       h_wh120_JERMinus,  h_wh140_JERMinus,  h_wh150_JERMinus,  h_wh155_JERMinus,   h_wh160_JERMinus  );
  getSignalCutFlowTable(outFile, "TopPtPlus", Nbin, 	h_wh80_TopPtPlus, 	h_wh90_TopPtPlus,       h_wh100_TopPtPlus,      h_wh120_TopPtPlus, h_wh140_TopPtPlus, h_wh150_TopPtPlus, h_wh155_TopPtPlus,  h_wh160_TopPtPlus );
  getSignalCutFlowTable(outFile, "TopPtMinus", Nbin, 	h_wh80_TopPtMinus, 	h_wh90_TopPtMinus,      h_wh100_TopPtMinus,     h_wh120_TopPtMinus,h_wh140_TopPtMinus,h_wh150_TopPtMinus,h_wh155_TopPtMinus, h_wh160_TopPtMinus);
  getSignalCutFlowTable(outFile, "bTagPlus", Nbin, 	h_wh80_bTagPlus, 	h_wh90_bTagPlus,        h_wh100_bTagPlus,       h_wh120_bTagPlus,  h_wh140_bTagPlus,  h_wh150_bTagPlus,  h_wh155_bTagPlus,   h_wh160_bTagPlus  );
  getSignalCutFlowTable(outFile, "bTagMinus", Nbin, 	h_wh80_bTagMinus, 	h_wh90_bTagMinus,       h_wh100_bTagMinus,      h_wh120_bTagMinus, h_wh140_bTagMinus, h_wh150_bTagMinus, h_wh155_bTagMinus,  h_wh160_bTagMinus );
  getSignalCutFlowTable(outFile, "cTagPlus", Nbin, 	h_wh80_cTagPlus, 	h_wh90_cTagPlus,        h_wh100_cTagPlus,       h_wh120_cTagPlus,  h_wh140_cTagPlus,  h_wh150_cTagPlus,  h_wh155_cTagPlus,   h_wh160_cTagPlus  );
  getSignalCutFlowTable(outFile, "cTagMinus", Nbin, 	h_wh80_cTagMinus, 	h_wh90_cTagMinus,       h_wh100_cTagMinus,      h_wh120_cTagMinus, h_wh140_cTagMinus, h_wh150_cTagMinus, h_wh155_cTagMinus,  h_wh160_cTagMinus );
  outFile<<"\\end{document}"<<endl;  
  outFile.close(); 
} 


void makeYieldTable_13TeV(TString histSubDir="Iso/", TString histName="cutflow"){  
#include "makeYieldTable_13TeV.h" 
  ofstream outFile; 
  outFile.open("summaryWithSyst.tex"); 
   
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

  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  outFile<<"\\begin{table}"<<endl;
  outFile<<"\\begin{center}"<<endl;  
  //outFile<<"\\begin{LARGE}"<<endl;  
  outFile<<"\\begin{tabular}{ | c| c| }"<<endl;  
  outFile<<"\\multicolumn{2}{c}{ } \\\\"<<endl;  
  outFile<<"\\hline "<<endl; 
  outFile<<"\\multicolumn{1}{|c|}{Source} & \\multicolumn{1}{|c|}{$N_{\\rm events}$}\\\\"<<endl;
  outFile<<"\\hline "<<endl; 
  outFile<<"\\hline "<<endl;
  int b = 7 ;

  double stat_wh80 = h_wh80_base->GetBinContent(b);
  double stat_err_wh80 = h_wh80_base->GetBinError(b);
  double sys_jes_wh80 = sysUncJESTopPt( h_wh80_JESPlus, h_wh80_base, h_wh80_JESMinus, h_wh80_JERPlus, h_wh80_JERMinus, h_wh80_TopPtPlus, h_wh80_TopPtMinus, b);
  double sys_btag_wh80 = sysUncBCTag(h_wh80_bTagPlus, h_wh80_base, h_wh80_bTagMinus, b);
  double sys_ctag_wh80 = sysUncBCTag(h_wh80_cTagPlus, h_wh80_base, h_wh80_cTagMinus, b);
  double sys_pileup_wh80 = sysUncBCTag (h_wh80_PileupPlus, h_wh80_base, h_wh80_PileupMinus, b);
  double tot_unc_wh80 = sqrt(pow(stat_err_wh80, 2) + pow(sys_jes_wh80, 2) + pow(sys_btag_wh80, 2) + pow(sys_ctag_wh80, 2) + pow(sys_pileup_wh80, 2)); 
  outFile<<"MC signal ($M_{H^\\pm}=80$ GeV)"<< " & "<<stat_wh80<<" $\\pm$ "<<tot_unc_wh80<<" \\\\ "<<endl;

  double stat_wh90 = h_wh90_base->GetBinContent(b);
  double stat_err_wh90 = h_wh90_base->GetBinError(b);
  double sys_jes_wh90 = sysUncJESTopPt( h_wh90_JESPlus, h_wh90_base, h_wh90_JESMinus, h_wh90_JERPlus, h_wh90_JERMinus, h_wh90_TopPtPlus, h_wh90_TopPtMinus, b);
  double sys_btag_wh90 = sysUncBCTag(h_wh90_bTagPlus, h_wh90_base, h_wh90_bTagMinus, b);
  double sys_ctag_wh90 = sysUncBCTag(h_wh90_cTagPlus, h_wh90_base, h_wh90_cTagMinus, b);
  double sys_pileup_wh90 = sysUncBCTag (h_wh90_PileupPlus, h_wh90_base, h_wh90_PileupMinus, b);
  double tot_unc_wh90 = sqrt(pow(stat_err_wh90, 2) + pow(sys_jes_wh90, 2) + pow(sys_btag_wh90, 2) + pow(sys_ctag_wh90, 2) + pow(sys_pileup_wh90, 2)); 
  outFile<<"MC signal ($M_{H^\\pm}=90$ GeV)"<< " & "<<stat_wh90<<" $\\pm$ "<<tot_unc_wh90<<" \\\\ "<<endl;

  double stat_wh100 = h_wh100_base->GetBinContent(b);
  double stat_err_wh100 = h_wh100_base->GetBinError(b);
  double sys_jes_wh100 = sysUncJESTopPt( h_wh100_JESPlus, h_wh100_base, h_wh100_JESMinus, h_wh100_JERPlus, h_wh100_JERMinus, h_wh100_TopPtPlus, h_wh100_TopPtMinus, b);
  double sys_btag_wh100 = sysUncBCTag(h_wh100_bTagPlus, h_wh100_base, h_wh100_bTagMinus, b);
  double sys_ctag_wh100 = sysUncBCTag(h_wh100_cTagPlus, h_wh100_base, h_wh100_cTagMinus, b);
  double sys_pileup_wh100 = sysUncBCTag (h_wh100_PileupPlus, h_wh100_base, h_wh100_PileupMinus, b);
  double tot_unc_wh100 = sqrt(pow(stat_err_wh100, 2) + pow(sys_jes_wh100, 2) + pow(sys_btag_wh100, 2) + pow(sys_ctag_wh100, 2) + pow(sys_pileup_wh100, 2)); 
  outFile<<"MC signal ($M_{H^\\pm}=100$ GeV)"<< " & "<<stat_wh100<<" $\\pm$ "<<tot_unc_wh100<<" \\\\ "<<endl;

  double stat_wh120 = h_wh120_base->GetBinContent(b);
  double stat_err_wh120 = h_wh120_base->GetBinError(b);
  double sys_jes_wh120 = sysUncJESTopPt( h_wh120_JESPlus, h_wh120_base, h_wh120_JESMinus, h_wh120_JERPlus, h_wh120_JERMinus, h_wh120_TopPtPlus, h_wh120_TopPtMinus, b);
  double sys_btag_wh120 = sysUncBCTag(h_wh120_bTagPlus, h_wh120_base, h_wh120_bTagMinus, b);
  double sys_ctag_wh120 = sysUncBCTag(h_wh120_cTagPlus, h_wh120_base, h_wh120_cTagMinus, b);
  double sys_pileup_wh120 = sysUncBCTag (h_wh120_PileupPlus, h_wh120_base, h_wh120_PileupMinus, b);
  double tot_unc_wh120 = sqrt(pow(stat_err_wh120, 2) + pow(sys_jes_wh120, 2) + pow(sys_btag_wh120, 2) + pow(sys_ctag_wh120, 2) + pow(sys_pileup_wh120, 2)); 
  outFile<<"MC signal ($M_{H^\\pm}=120$ GeV)"<< " & "<<stat_wh120<<" $\\pm$ "<<tot_unc_wh120<<" \\\\ "<<endl;

  double stat_wh140 = h_wh140_base->GetBinContent(b);
  double stat_err_wh140 = h_wh140_base->GetBinError(b);
  double sys_jes_wh140 = sysUncJESTopPt( h_wh140_JESPlus, h_wh140_base, h_wh140_JESMinus, h_wh140_JERPlus, h_wh140_JERMinus, h_wh140_TopPtPlus, h_wh140_TopPtMinus, b);
  double sys_btag_wh140 = sysUncBCTag(h_wh140_bTagPlus, h_wh140_base, h_wh140_bTagMinus, b);
  double sys_ctag_wh140 = sysUncBCTag(h_wh140_cTagPlus, h_wh140_base, h_wh140_cTagMinus, b);
  double sys_pileup_wh140 = sysUncBCTag (h_wh140_PileupPlus, h_wh140_base, h_wh140_PileupMinus, b);
  double tot_unc_wh140 = sqrt(pow(stat_err_wh140, 2) + pow(sys_jes_wh140, 2) + pow(sys_btag_wh140, 2) + pow(sys_ctag_wh140, 2) + pow(sys_pileup_wh140, 2)); 
  outFile<<"MC signal ($M_{H^\\pm}=140$ GeV)"<< " & "<<stat_wh140<<" $\\pm$ "<<tot_unc_wh140<<" \\\\ "<<endl;

  double stat_wh150 = h_wh150_base->GetBinContent(b);
  double stat_err_wh150 = h_wh150_base->GetBinError(b);
  double sys_jes_wh150 = sysUncJESTopPt( h_wh150_JESPlus, h_wh150_base, h_wh150_JESMinus, h_wh150_JERPlus, h_wh150_JERMinus, h_wh150_TopPtPlus, h_wh150_TopPtMinus, b);
  double sys_btag_wh150 = sysUncBCTag(h_wh150_bTagPlus, h_wh150_base, h_wh150_bTagMinus, b);
  double sys_ctag_wh150 = sysUncBCTag(h_wh150_cTagPlus, h_wh150_base, h_wh150_cTagMinus, b);
  double sys_pileup_wh150 = sysUncBCTag (h_wh150_PileupPlus, h_wh150_base, h_wh150_PileupMinus, b);
  double tot_unc_wh150 = sqrt(pow(stat_err_wh150, 2) + pow(sys_jes_wh150, 2) + pow(sys_btag_wh150, 2) + pow(sys_ctag_wh150, 2) + pow(sys_pileup_wh150, 2)); 
  outFile<<"MC signal ($M_{H^\\pm}=150$ GeV)"<< " & "<<stat_wh150<<" $\\pm$ "<<tot_unc_wh150<<" \\\\ "<<endl;

  double stat_wh155 = h_wh155_base->GetBinContent(b);
  double stat_err_wh155 = h_wh155_base->GetBinError(b);
  double sys_jes_wh155 = sysUncJESTopPt( h_wh155_JESPlus, h_wh155_base, h_wh155_JESMinus, h_wh155_JERPlus, h_wh155_JERMinus, h_wh155_TopPtPlus, h_wh155_TopPtMinus, b);
  double sys_btag_wh155 = sysUncBCTag(h_wh155_bTagPlus, h_wh155_base, h_wh155_bTagMinus, b);
  double sys_ctag_wh155 = sysUncBCTag(h_wh155_cTagPlus, h_wh155_base, h_wh155_cTagMinus, b);
  double sys_pileup_wh155 = sysUncBCTag (h_wh155_PileupPlus, h_wh155_base, h_wh155_PileupMinus, b);
  double tot_unc_wh155 = sqrt(pow(stat_err_wh155, 2) + pow(sys_jes_wh155, 2) + pow(sys_btag_wh155, 2) + pow(sys_ctag_wh155, 2) + pow(sys_pileup_wh155, 2)); 
  outFile<<"MC signal ($M_{H^\\pm}=155$ GeV)"<< " & "<<stat_wh155<<" $\\pm$ "<<tot_unc_wh155<<" \\\\ "<<endl;

  double stat_wh160 = h_wh160_base->GetBinContent(b);
  double stat_err_wh160 = h_wh160_base->GetBinError(b);
  double sys_jes_wh160 = sysUncJESTopPt( h_wh160_JESPlus, h_wh160_base, h_wh160_JESMinus, h_wh160_JERPlus, h_wh160_JERMinus, h_wh160_TopPtPlus, h_wh160_TopPtMinus, b);
  double sys_btag_wh160 = sysUncBCTag(h_wh160_bTagPlus, h_wh160_base, h_wh160_bTagMinus, b);
  double sys_ctag_wh160 = sysUncBCTag(h_wh160_cTagPlus, h_wh160_base, h_wh160_cTagMinus, b);
  double sys_pileup_wh160 = sysUncBCTag (h_wh160_PileupPlus, h_wh160_base, h_wh160_PileupMinus, b);
  double tot_unc_wh160 = sqrt(pow(stat_err_wh160, 2) + pow(sys_jes_wh160, 2) + pow(sys_btag_wh160, 2) + pow(sys_ctag_wh160, 2) + pow(sys_pileup_wh160, 2)); 
  outFile<<"MC signal ($M_{H^\\pm}=160$ GeV)"<< " & "<<stat_wh160<<" $\\pm$ "<<tot_unc_wh160<<" \\\\ "<<endl;
  outFile<<"\\hline "<<endl;  

  double stat_ttbar = h_ttbar_base->GetBinContent(b);
  double stat_err_ttbar = h_ttbar_base->GetBinError(b);
  double sys_jes_ttbar = sysUncJESTopPt( h_ttbar_JESPlus, h_ttbar_base, h_ttbar_JESMinus, h_ttbar_JERPlus, h_ttbar_JERMinus, h_ttbar_TopPtPlus, h_ttbar_TopPtMinus, b);
  double sys_btag_ttbar = sysUncBCTag(h_ttbar_bTagPlus, h_ttbar_base, h_ttbar_bTagMinus, b);
  double sys_ctag_ttbar = sysUncBCTag(h_ttbar_cTagPlus, h_ttbar_base, h_ttbar_cTagMinus, b);
  double sys_pileup_ttbar = sysUncBCTag (h_ttbar_PileupPlus, h_ttbar_base, h_ttbar_PileupMinus, b);
  double tot_unc_ttbar = sqrt(pow(stat_err_ttbar, 2) + pow(sys_jes_ttbar, 2) + pow(sys_btag_ttbar, 2) + pow(sys_ctag_ttbar, 2) + pow(sys_pileup_ttbar, 2)); 
  outFile<<"SM $t\\bar{t}$ + jets"<< " & "<<stat_ttbar<<" $\\pm$ "<<tot_unc_ttbar<<" \\\\ "<<endl;

  double stat_wjet = h_wjet_base->GetBinContent(b);
  double stat_err_wjet = h_wjet_base->GetBinError(b);
  double sys_jes_wjet = sysUncJESTopPt( h_wjet_JESPlus, h_wjet_base, h_wjet_JESMinus, h_wjet_JERPlus, h_wjet_JERMinus, h_wjet_TopPtPlus, h_wjet_TopPtMinus, b);
  double sys_btag_wjet = sysUncBCTag(h_wjet_bTagPlus, h_wjet_base, h_wjet_bTagMinus, b);
  double sys_ctag_wjet = sysUncBCTag(h_wjet_cTagPlus, h_wjet_base, h_wjet_cTagMinus, b);
  double sys_pileup_wjet = sysUncBCTag (h_wjet_PileupPlus, h_wjet_base, h_wjet_PileupMinus, b);
  double tot_unc_wjet = sqrt(pow(stat_err_wjet, 2) + pow(sys_jes_wjet, 2) + pow(sys_btag_wjet, 2) + pow(sys_ctag_wjet, 2) + pow(sys_pileup_wjet, 2)); 
  outFile<<"W + jets"<< " & "<<stat_wjet<<" $\\pm$ "<<tot_unc_wjet<<" \\\\ "<<endl;

  double stat_zjet = h_zjet_base->GetBinContent(b);
  double stat_err_zjet = h_zjet_base->GetBinError(b);
  double sys_jes_zjet = sysUncJESTopPt( h_zjet_JESPlus, h_zjet_base, h_zjet_JESMinus, h_zjet_JERPlus, h_zjet_JERMinus, h_zjet_TopPtPlus, h_zjet_TopPtMinus, b);
  double sys_btag_zjet = sysUncBCTag(h_zjet_bTagPlus, h_zjet_base, h_zjet_bTagMinus, b);
  double sys_ctag_zjet = sysUncBCTag(h_zjet_cTagPlus, h_zjet_base, h_zjet_cTagMinus, b);
  double sys_pileup_zjet = sysUncBCTag (h_zjet_PileupPlus, h_zjet_base, h_zjet_PileupMinus, b);
  double tot_unc_zjet = sqrt(pow(stat_err_zjet, 2) + pow(sys_jes_zjet, 2) + pow(sys_btag_zjet, 2) + pow(sys_ctag_zjet, 2) + pow(sys_pileup_zjet, 2)); 
  outFile<<"$Z/\\gamma$ + jets"<< " & "<<stat_zjet<<" $\\pm$ "<<tot_unc_zjet<<" \\\\ "<<endl;

  double stat_qcd = h_qcd_base->GetBinContent(b);
  double stat_err_qcd = h_qcd_base->GetBinError(b);
  double sys_jes_qcd = sysUncJESTopPt( h_qcd_JESPlus, h_qcd_base, h_qcd_JESMinus, h_qcd_JERPlus, h_qcd_JERMinus, h_qcd_TopPtPlus, h_qcd_TopPtMinus, b);
  double sys_btag_qcd = sysUncBCTag(h_qcd_bTagPlus, h_qcd_base, h_qcd_bTagMinus, b);
  double sys_ctag_qcd = sysUncBCTag(h_qcd_cTagPlus, h_qcd_base, h_qcd_cTagMinus, b);
  double sys_pileup_qcd = sysUncBCTag (h_qcd_PileupPlus, h_qcd_base, h_qcd_PileupMinus, b);
  double tot_unc_qcd = sqrt(pow(stat_err_qcd, 2) + pow(sys_jes_qcd, 2) + pow(sys_btag_qcd, 2) + pow(sys_ctag_qcd, 2) + pow(sys_pileup_qcd, 2)); 
  outFile<<"QCD"<< " & "<<stat_qcd<<" $\\pm$ "<<tot_unc_qcd<<" \\\\ "<<endl;

  double stat_stop = h_stop_base->GetBinContent(b);
  double stat_err_stop = h_stop_base->GetBinError(b);
  double sys_jes_stop = sysUncJESTopPt( h_stop_JESPlus, h_stop_base, h_stop_JESMinus, h_stop_JERPlus, h_stop_JERMinus, h_stop_TopPtPlus, h_stop_TopPtMinus, b);
  double sys_btag_stop = sysUncBCTag(h_stop_bTagPlus, h_stop_base, h_stop_bTagMinus, b);
  double sys_ctag_stop = sysUncBCTag(h_stop_cTagPlus, h_stop_base, h_stop_cTagMinus, b);
  double sys_pileup_stop = sysUncBCTag (h_stop_PileupPlus, h_stop_base, h_stop_PileupMinus, b);
  double tot_unc_stop = sqrt(pow(stat_err_stop, 2) + pow(sys_jes_stop, 2) + pow(sys_btag_stop, 2) + pow(sys_ctag_stop, 2) + pow(sys_pileup_stop, 2)); 
  outFile<<"Single ~t"<< " & "<<stat_stop<<" $\\pm$ "<<tot_unc_stop<<" \\\\ "<<endl;

  double stat_vv = h_vv_base->GetBinContent(b);
  double stat_err_vv = h_vv_base->GetBinError(b);
  double sys_jes_vv = sysUncJESTopPt( h_vv_JESPlus, h_vv_base, h_vv_JESMinus, h_vv_JERPlus, h_vv_JERMinus, h_vv_TopPtPlus, h_vv_TopPtMinus, b);
  double sys_btag_vv = sysUncBCTag(h_vv_bTagPlus, h_vv_base, h_vv_bTagMinus, b);
  double sys_ctag_vv = sysUncBCTag(h_vv_cTagPlus, h_vv_base, h_vv_cTagMinus, b);
  double sys_pileup_vv = sysUncBCTag (h_vv_PileupPlus, h_vv_base, h_vv_PileupMinus, b);
  double tot_unc_vv = sqrt(pow(stat_err_vv, 2) + pow(sys_jes_vv, 2) + pow(sys_btag_vv, 2) + pow(sys_ctag_vv, 2) + pow(sys_pileup_vv, 2)); 
  outFile<<"VV"<< " & "<<stat_vv<<" $\\pm$ "<<tot_unc_vv<<" \\\\ "<<endl;
  outFile<<"\\hline "<<endl;
  outFile<<"Total Bkg"<<" & "<<h_TotalBkg->GetBinContent(b)<<" $\\pm$ "<<" -- "<<" \\\\ "<<endl;
  outFile<<"\\hline "<<endl;  
  outFile<<" Data "<<" & "<<h_data->GetBinContent(b)<<" \\\\ "<<endl; 
  outFile<<"\\hline "<<endl;    
  outFile<<"\\hline "<<endl;   
  outFile<<"\\end{tabular}"<<endl; 
  //outFile<<"\\end{LARGE}"<<endl;  
  outFile<<"\\end{center}"<<endl;
  outFile<<"\\caption{First table}"<<endl;
  outFile<<"\\end{table}"<<endl;

  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  outFile<<"\\begin{table}"<<endl;
  outFile<<"\\begin{center}"<<endl;  
  //outFile<<"\\begin{LARGE}"<<endl;  
  outFile<<"\\begin{tabular}{ | c| c| }"<<endl;  
  outFile<<"\\multicolumn{2}{c}{ } \\\\"<<endl;  
  outFile<<"\\hline "<<endl; 
  outFile<<"\\multicolumn{1}{|c|}{Source} & \\multicolumn{1}{|c|}{N$_{\r events}$ $\\pm$ MC stat $\\pm$ JEC/MET/Top $\\pm$ bTag $\\pm$ cTag $\\pm$ Pileup} \\\\"<<endl;
  outFile<<"\\hline "<<endl; 
  outFile<<"\\hline "<<endl;
  
  outFile<<"MC signal ($M_{H^\\pm}=80~GeV)$"<< " & "<<h_wh80_base->GetBinContent(b)<<" $\\pm$ "<<h_wh80_base->GetBinError(b)<<" $\\pm$ "<< sysUncJESTopPt( h_wh80_JESPlus, h_wh80_base, h_wh80_JESMinus, h_wh80_JERPlus, h_wh80_JERMinus, h_wh80_TopPtPlus, h_wh80_TopPtMinus, b) <<" $\\pm$ "<< sysUncBCTag (h_wh80_bTagPlus, h_wh80_base, h_wh80_bTagMinus, b) << " $\\pm$ "<< sysUncBCTag (h_wh80_cTagPlus, h_wh80_base, h_wh80_cTagMinus, b)<<" $\\pm$ "<< sysUncBCTag (h_wh80_PileupPlus, h_wh80_base, h_wh80_PileupMinus, b)<<" \\\\ "<<endl;
  
  outFile<<"MC signal ($M_{H^\\pm}=90~GeV)$"<< " & "<<h_wh90_base->GetBinContent(b)<<" $\\pm$ "<<h_wh90_base->GetBinError(b)<<" $\\pm$ "<< sysUncJESTopPt( h_wh90_JESPlus, h_wh90_base, h_wh90_JESMinus, h_wh90_JERPlus, h_wh90_JERMinus, h_wh90_TopPtPlus, h_wh90_TopPtMinus, b) <<" $\\pm$ "<< sysUncBCTag (h_wh90_bTagPlus, h_wh90_base, h_wh90_bTagMinus, b) << " $\\pm$ "<< sysUncBCTag (h_wh90_cTagPlus, h_wh90_base, h_wh90_cTagMinus, b)<<" $\\pm$ "<< sysUncBCTag (h_wh90_PileupPlus, h_wh90_base, h_wh90_PileupMinus, b)<<" \\\\ "<<endl;
  
  outFile<<"MC signal ($M_{H^\\pm}=100~GeV)$"<< " & "<<h_wh100_base->GetBinContent(b)<<" $\\pm$ "<<h_wh100_base->GetBinError(b)<<" $\\pm$ "<< sysUncJESTopPt( h_wh100_JESPlus, h_wh100_base, h_wh100_JESMinus, h_wh100_JERPlus, h_wh100_JERMinus, h_wh100_TopPtPlus, h_wh100_TopPtMinus, b) <<" $\\pm$ "<< sysUncBCTag (h_wh100_bTagPlus, h_wh100_base, h_wh100_bTagMinus, b) << " $\\pm$ "<< sysUncBCTag (h_wh100_cTagPlus, h_wh100_base, h_wh100_cTagMinus, b)<<" $\\pm$ "<< sysUncBCTag (h_wh100_PileupPlus, h_wh100_base, h_wh100_PileupMinus, b)<<" \\\\ "<<endl;
  
  outFile<<"MC signal ($M_{H^\\pm}=120~GeV)$"<< " & "<<h_wh120_base->GetBinContent(b)<<" $\\pm$ "<<h_wh120_base->GetBinError(b)<<" $\\pm$ "<< sysUncJESTopPt( h_wh120_JESPlus, h_wh120_base, h_wh120_JESMinus, h_wh120_JERPlus, h_wh120_JERMinus, h_wh120_TopPtPlus, h_wh120_TopPtMinus, b) <<" $\\pm$ "<< sysUncBCTag (h_wh120_bTagPlus, h_wh120_base, h_wh120_bTagMinus, b) << " $\\pm$ "<< sysUncBCTag (h_wh120_cTagPlus, h_wh120_base, h_wh120_cTagMinus, b)<<" $\\pm$ "<< sysUncBCTag (h_wh120_PileupPlus, h_wh120_base, h_wh120_PileupMinus, b)<<" \\\\ "<<endl;
  
  outFile<<"MC signal ($M_{H^\\pm}=140~GeV)$"<< " & "<<h_wh140_base->GetBinContent(b)<<" $\\pm$ "<<h_wh140_base->GetBinError(b)<<" $\\pm$ "<< sysUncJESTopPt( h_wh140_JESPlus, h_wh140_base, h_wh140_JESMinus, h_wh140_JERPlus, h_wh140_JERMinus, h_wh140_TopPtPlus, h_wh140_TopPtMinus, b) <<" $\\pm$ "<< sysUncBCTag (h_wh140_bTagPlus, h_wh140_base, h_wh140_bTagMinus, b) << " $\\pm$ "<< sysUncBCTag (h_wh140_cTagPlus, h_wh140_base, h_wh140_cTagMinus, b)<<" $\\pm$ "<< sysUncBCTag (h_wh140_PileupPlus, h_wh140_base, h_wh140_PileupMinus, b)<<" \\\\ "<<endl;
  
  outFile<<"MC signal ($M_{H^\\pm}=150~GeV)$"<< " & "<<h_wh150_base->GetBinContent(b)<<" $\\pm$ "<<h_wh150_base->GetBinError(b)<<" $\\pm$ "<< sysUncJESTopPt( h_wh150_JESPlus, h_wh150_base, h_wh150_JESMinus, h_wh150_JERPlus, h_wh150_JERMinus, h_wh150_TopPtPlus, h_wh150_TopPtMinus, b) <<" $\\pm$ "<< sysUncBCTag (h_wh150_bTagPlus, h_wh150_base, h_wh150_bTagMinus, b) << " $\\pm$ "<< sysUncBCTag (h_wh150_cTagPlus, h_wh150_base, h_wh150_cTagMinus, b)<<" $\\pm$ "<< sysUncBCTag (h_wh150_PileupPlus, h_wh150_base, h_wh150_PileupMinus, b)<<" \\\\ "<<endl;
  
  outFile<<"MC signal ($M_{H^\\pm}=155~GeV)$"<< " & "<<h_wh155_base->GetBinContent(b)<<" $\\pm$ "<<h_wh155_base->GetBinError(b)<<" $\\pm$ "<< sysUncJESTopPt( h_wh155_JESPlus, h_wh155_base, h_wh155_JESMinus, h_wh155_JERPlus, h_wh155_JERMinus, h_wh155_TopPtPlus, h_wh155_TopPtMinus, b) <<" $\\pm$ "<< sysUncBCTag (h_wh155_bTagPlus, h_wh155_base, h_wh155_bTagMinus, b) << " $\\pm$ "<< sysUncBCTag (h_wh155_cTagPlus, h_wh155_base, h_wh155_cTagMinus, b)<<" $\\pm$ "<< sysUncBCTag (h_wh155_PileupPlus, h_wh155_base, h_wh155_PileupMinus, b)<<" \\\\ "<<endl;
  
  outFile<<"MC signal ($M_{H^\\pm}=160~GeV)$"<< " & "<<h_wh160_base->GetBinContent(b)<<" $\\pm$ "<<h_wh160_base->GetBinError(b)<<" $\\pm$ "<< sysUncJESTopPt( h_wh160_JESPlus, h_wh160_base, h_wh160_JESMinus, h_wh160_JERPlus, h_wh160_JERMinus, h_wh160_TopPtPlus, h_wh160_TopPtMinus, b) <<" $\\pm$ "<< sysUncBCTag (h_wh160_bTagPlus, h_wh160_base, h_wh160_bTagMinus, b) << " $\\pm$ "<< sysUncBCTag (h_wh160_cTagPlus, h_wh160_base, h_wh160_cTagMinus, b)<<" $\\pm$ "<< sysUncBCTag (h_wh160_PileupPlus, h_wh160_base, h_wh160_PileupMinus, b)<<" \\\\ "<<endl;
  outFile<<"\\hline "<<endl;  
  
  outFile<<"SM $t\\bar{t}$"<<" & "<<h_ttbar_base->GetBinContent(b)<<" $\\pm$ "<<h_ttbar_base->GetBinError(b)<<" $\\pm$ "<< sysUncJESTopPt( h_ttbar_JESPlus, h_ttbar_base, h_ttbar_JESMinus, h_ttbar_JERPlus, h_ttbar_JERMinus, h_ttbar_TopPtPlus, h_ttbar_TopPtMinus, b) <<" $\\pm$ "<< sysUncBCTag (h_ttbar_bTagPlus, h_ttbar_base, h_ttbar_bTagMinus, b) << " $\\pm$ "<< sysUncBCTag (h_ttbar_cTagPlus, h_ttbar_base, h_ttbar_cTagMinus, b)<<" $\\pm$ "<<sysUncBCTag (h_ttbar_PileupPlus, h_ttbar_base, h_ttbar_PileupMinus, b)<<" \\\\ "<<endl;

  outFile<<"W + jets"<< " & "<<h_wjet_base->GetBinContent(b)<<" $\\pm$ "<<h_wjet_base->GetBinError(b)<<" $\\pm$ "<< sysUncJESTopPt( h_wjet_JESPlus, h_wjet_base, h_wjet_JESMinus, h_wjet_JERPlus, h_wjet_JERMinus, h_wjet_TopPtPlus, h_wjet_TopPtMinus, b) <<" $\\pm$ "<< sysUncBCTag (h_wjet_bTagPlus, h_wjet_base, h_wjet_bTagMinus, b) << " $\\pm$ "<< sysUncBCTag (h_wjet_cTagPlus, h_wjet_base, h_wjet_cTagMinus, b)<<" $\\pm$ "<<sysUncBCTag (h_wjet_PileupPlus, h_wjet_base, h_wjet_PileupMinus, b)<<" \\\\ "<<endl;

  outFile<<"$Z/\\gamma $ + jets"<< " & "<<h_zjet_base->GetBinContent(b)<<" $\\pm$ "<<h_zjet_base->GetBinError(b)<<" $\\pm$ "<< sysUncJESTopPt( h_zjet_JESPlus, h_zjet_base, h_zjet_JESMinus, h_zjet_JERPlus, h_zjet_JERMinus, h_zjet_TopPtPlus, h_zjet_TopPtMinus, b) <<" $\\pm$ "<< sysUncBCTag (h_zjet_bTagPlus, h_zjet_base, h_zjet_bTagMinus, b) << " $\\pm$ "<< sysUncBCTag (h_zjet_cTagPlus, h_zjet_base, h_zjet_cTagMinus, b)<<" $\\pm$ "<<sysUncBCTag (h_zjet_PileupPlus, h_zjet_base, h_zjet_PileupMinus, b)<<" \\\\ "<<endl;

  outFile<<"MC QCD"<< " & "<<h_qcd_base->GetBinContent(b)<<" $\\pm$ "<<h_qcd_base->GetBinError(b)<<" $\\pm$ "<< sysUncJESTopPt( h_qcd_JESPlus, h_qcd_base, h_qcd_JESMinus, h_qcd_JERPlus, h_qcd_JERMinus, h_qcd_TopPtPlus, h_qcd_TopPtMinus, b) <<" $\\pm$ "<< sysUncBCTag (h_qcd_bTagPlus, h_qcd_base, h_qcd_bTagMinus, b) << " $\\pm$ "<< sysUncBCTag (h_qcd_cTagPlus, h_qcd_base, h_qcd_cTagMinus, b)<<" $\\pm$ "<<sysUncBCTag (h_qcd_PileupPlus, h_qcd_base, h_qcd_PileupMinus, b)<<" \\\\ "<<endl;

  outFile<<"Single t"<< " & "<<h_stop_base->GetBinContent(b)<<" $\\pm$ "<<h_stop_base->GetBinError(b)<<" $\\pm$ "<< sysUncJESTopPt( h_stop_JESPlus, h_stop_base, h_stop_JESMinus, h_stop_JERPlus, h_stop_JERMinus, h_stop_TopPtPlus, h_stop_TopPtMinus, b) <<" $\\pm$ "<< sysUncBCTag (h_stop_bTagPlus, h_stop_base, h_stop_bTagMinus, b) << " $\\pm$ "<< sysUncBCTag (h_stop_cTagPlus, h_stop_base, h_stop_cTagMinus, b)<<" $\\pm$ "<<sysUncBCTag (h_stop_PileupPlus, h_stop_base, h_stop_PileupMinus, b)<<" \\\\ "<<endl;

  outFile<<"VV"<< " & "<<h_vv_base->GetBinContent(b)<<" $\\pm$ "<<h_vv_base->GetBinError(b)<<" $\\pm$ "<< sysUncJESTopPt( h_vv_JESPlus, h_vv_base, h_vv_JESMinus, h_vv_JERPlus, h_vv_JERMinus, h_vv_TopPtPlus, h_vv_TopPtMinus, b) <<" $\\pm$ "<< sysUncBCTag (h_vv_bTagPlus, h_vv_base, h_vv_bTagMinus, b) << " $\\pm$ "<< sysUncBCTag (h_vv_cTagPlus, h_vv_base, h_vv_cTagMinus, b)<<" $\\pm$ "<<sysUncBCTag (h_vv_PileupPlus, h_vv_base, h_vv_PileupMinus, b)<<" \\\\ "<<endl;
  outFile<<"\\hline "<<endl;
  outFile<<"Total Bkg"<<" & "<<h_TotalBkg->GetBinContent(b)<<" $\\pm$ "<<h_TotalBkg->GetBinError(b)<<" $\\pm$ "<<" -- "<<" $\\pm$ "<<" -- "<<"$\\pm$ "<<" -- "<<" \\\\ "<<endl;
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
  double Nbin = 8;
  //Cutflow table from SM Higgs Bkg
  makeHiggsBkgTable(outFile, "base", Nbin,
		h_GluGluHToBB,           
		h_GluGluHToTauTau,       
		h_GluGluHToCC,           
		h_GluGluHToGG,           
		h_GluGluHToWWTo2L2Nu,    
		h_GluGluHToWWToLNuQQ,    
		h_GluGluHToZZTo2L2Q,     
		h_GluGluHToZZTo4L,       
		h_WplusH_HToBB_WToLNu,   
		h_WplusH_HToBB_WToQQ,    
		h_WplusHToTauTau,        
		h_WplusH_HToCC_WToLNu,   
		h_WplusH_HToCC_WToQQ,    
		h_WplusH_HToGG_WToAll,   
		h_WminusH_HToBB_WToQQ,   
		h_WminusHToTauTau,       
		h_WminusH_HToCC_WToLNu,  
		h_WminusH_HToCC_WToQQ,   
		h_WminusH_HToGG_WToAll,  
		h_WminusH_HToZZTo2L2X,   
		h_ZH_HToBB_ZToNuNu,      
		h_ZH_HToBB_ZToLL,        
		h_ZH_HToBB_ZToQQ,        
		h_ZHToTauTau,            
		h_ZH_HToCC_ZToNuNu,      
		h_ZH_HToCC_ZToLL,        
		h_ZH_HToCC_ZToQQ,        
		h_ZH_HToGG_ZToAll,       
		h_ZH_HToZZ_2L,           
		h_ggZH_HToBB_ZToNuNu,    
		h_ggZH_HToBB_ZToLL,      
		h_ggZH_HToBB_ZToQQ,      
		h_ggZH_HToCC_ZToNuNu,    
		h_ggZH_HToCC_ZToLL,      
		h_ggZH_HToCC_ZToQQ,      
		h_GluGluZH_HToWW,        
		h_ttHToCC,               
		h_ttHToGG,               
		h_bbHToBB,               
		h_bbHToGG,               
		h_bbHToWWTo2L2Nu,        
		h_bbH_HToZZTo4L,         
		h_VBFHToBB,              
		h_VBFHToTauTau,          
		h_VBFHToCC,              
		h_VBFHToGG,              
		h_VBFHToWWTo2L2Nu,       
		h_VBFHToWWToLNuQQ); 
  makeCutFlowTableAny(outFile, "base", Nbin, 		h_wh120_base,  	h_ttbar_base, h_stop_base, h_wjet_base, h_zjet_base, h_qcd_base, h_stop_base, h_vv_base, h_data);
  makeCutFlowTableAny(outFile, "JESPlus", Nbin, 	h_wh120_JESPlus, 	h_ttbar_JESPlus, h_stop_JESPlus, h_wjet_JESPlus, h_zjet_JESPlus, h_qcd_JESPlus, h_stop_JESPlus, h_vv_JESPlus, h_data);
  makeCutFlowTableAny(outFile, "JESMinus", Nbin, 	h_wh120_JESMinus, 	h_ttbar_JESMinus,h_stop_JERMinus, h_wjet_JESMinus, h_zjet_JESMinus, h_qcd_JESMinus, h_stop_JESMinus, h_vv_JESMinus, h_data);
  makeCutFlowTableAny(outFile, "JERPlus", Nbin, 	h_wh120_JERPlus, 	h_ttbar_JERPlus, h_stop_JERPlus, h_wjet_JERPlus, h_zjet_JERPlus, h_qcd_JERPlus, h_stop_JERPlus, h_vv_JERPlus, h_data);
  makeCutFlowTableAny(outFile, "JERMinus", Nbin, 	h_wh120_JERMinus, 	h_ttbar_JERMinus, h_stop_JERMinus, h_wjet_JERMinus, h_zjet_JERMinus, h_qcd_JERMinus, h_stop_JERMinus, h_vv_JERMinus, h_data);
  makeCutFlowTableAny(outFile, "TopPtPlus", Nbin, 	h_wh120_TopPtPlus, h_ttbar_TopPtPlus, h_stop_TopPtPlus, h_wjet_TopPtPlus, h_zjet_TopPtPlus, h_qcd_TopPtPlus, h_stop_TopPtPlus, h_vv_TopPtPlus, h_data);
  makeCutFlowTableAny(outFile, "TopPtMinus", Nbin, 	h_wh120_TopPtMinus, h_ttbar_TopPtMinus, h_stop_TopPtMinus, h_wjet_TopPtMinus, h_zjet_TopPtMinus, h_qcd_TopPtMinus, h_stop_TopPtMinus, h_vv_TopPtMinus, h_data);
  makeCutFlowTableAny(outFile, "bTagPlus", Nbin, 	h_wh120_bTagPlus, 	h_ttbar_bTagPlus, h_stop_bTagPlus, h_wjet_bTagPlus, h_zjet_bTagPlus, h_qcd_bTagPlus, h_stop_bTagPlus, h_vv_bTagPlus, h_data);
  makeCutFlowTableAny(outFile, "bTagMinus", Nbin, 	h_wh120_bTagMinus, h_ttbar_bTagMinus, h_stop_bTagMinus, h_wjet_bTagMinus, h_zjet_bTagMinus, h_qcd_bTagMinus, h_stop_bTagMinus, h_vv_bTagMinus, h_data);
  makeCutFlowTableAny(outFile, "cTagPlus", Nbin, 	h_wh120_cTagPlus, 	h_ttbar_cTagPlus, h_stop_cTagPlus, h_wjet_cTagPlus, h_zjet_cTagPlus, h_qcd_cTagPlus, h_stop_cTagPlus, h_vv_cTagPlus, h_data);
  makeCutFlowTableAny(outFile, "cTagMinus", Nbin, 	h_wh120_cTagMinus, h_ttbar_cTagMinus, h_stop_cTagMinus, h_wjet_cTagMinus, h_zjet_cTagMinus, h_qcd_cTagMinus, h_stop_cTagMinus, h_vv_cTagMinus, h_data);
  makeCutFlowTableAny(outFile, "PileupPlus", Nbin, 	h_wh120_PileupPlus, 	h_ttbar_PileupPlus, h_stop_PileupPlus, h_wjet_PileupPlus, h_zjet_PileupPlus, h_qcd_PileupPlus, h_stop_PileupPlus, h_vv_PileupPlus, h_data);
  makeCutFlowTableAny(outFile, "PileupMinus", Nbin, 	h_wh120_PileupMinus, h_ttbar_PileupMinus, h_stop_PileupMinus, h_wjet_PileupMinus, h_zjet_PileupMinus, h_qcd_PileupMinus, h_stop_PileupMinus, h_vv_PileupMinus, h_data);
  outFile<<"\\end{document}"<<endl;  
  outFile.close(); 
} 

void makeFinalSysUncTable(TString histSubDir="Iso/", TString histName="cutflow"){  
#include "makeYieldTable_13TeV.h" 
  ofstream outFile; 
  outFile.open("finalSysUncTable.tex"); 
   
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
  outFile<<"\\begin{table}"<<endl; 
  outFile<<"\\begin{center}"<<endl; 
  //outFile<<"%\\begin{LARGE}"<<endl;
  ///outFile<<"\\footnotesize\\setlength{\\tabcolsep}{0.3pt}"<<endl;
  outFile<<"\\begin{tabular}{ | c| c| c| c| c| c| c| c| c| c| c| c| c|c|}"<<endl; 
  outFile<<"\\multicolumn{5}{c}{ } \\\\"<<endl; 
  outFile<<"\\hline "<<endl;
  outFile<<"\\multicolumn{1}{| p{2cm}| }{Process } & \\multicolumn{1}{ p{0.8cm}|}{\\rotatebox{90}{Luminosity}} & \\multicolumn{1}{ p{0.8cm}|}{\\rotatebox{90}{Pileup reweighting} } & \\multicolumn{1}{ p{0.8cm}|}{\\rotatebox{90}{Lepton selections}} & \\multicolumn{1}{ p{0.8cm}|}{\\rotatebox{90}{JES+JER+MET}} & \\multicolumn{1}{ p{0.8cm}|}{ \\rotatebox{90}{b-jet tagging} }  & \\multicolumn{1}{ p{0.8cm}|}{ \\rotatebox{90}{c-jet tagging} }& \\multicolumn{1}{ p{0.8cm}|}{ \\rotatebox{90}{Normalization}  }& \\multicolumn{1}{ p{0.8cm}|}{\\rotatebox{90}{MC Statistics}  } & \\multicolumn{1}{ p{0.8cm}|}{\\rotatebox{90}{Top-Pt reweighting} }  \\\\ "<<endl;
  outFile<<"\\hline "<<endl; 
  outFile<<"\\hline "<<endl;
  int b = 6;

  outFile<<"MC signal ($M_{H^\\pm}=80$ GeV)"<< " & "<<2.5<< std::setprecision(2)<< 
	  " &  "<< relSysUncBCTag(h_wh80_base, h_wh80_PileupPlus, h_wh80_PileupMinus, b)<<
	  " &  "<<3.0<< " & "<<relSysUncJetMET( h_wh80_JESPlus, h_wh80_base, 
	            h_wh80_JESMinus, h_wh80_JERPlus, h_wh80_JERMinus, b) <<
	  " &  "<< relSysUncBCTag(h_wh80_bTagPlus, h_wh80_base, h_wh80_bTagMinus, b) << 
	  " &  "<<relSysUncBCTag(h_wh80_cTagPlus, h_wh80_base, h_wh80_cTagMinus, b)<<
	  " &  "<<"6.1"<<" & "<<relStatUnc(h_wh80_base, b)<<
	  " &  "<<relSysUncTopPt(h_wh80_base, h_wh80_TopPtPlus, h_wh80_TopPtMinus, b)<<
	  " \\\\[0.1cm] "<<endl;


  outFile<<"MC signal ($M_{H^\\pm}=90$ GeV)"<< " & "<<2.5<< std::setprecision(2)<< 
	  " &  "<< relSysUncBCTag(h_wh90_base, h_wh90_PileupPlus, h_wh90_PileupMinus, b)<<
	  " &  "<<3.0<< " & "<<relSysUncJetMET( h_wh90_JESPlus, h_wh90_base, 
	            h_wh90_JESMinus, h_wh90_JERPlus, h_wh90_JERMinus, b) <<
	  " &  "<< relSysUncBCTag(h_wh90_bTagPlus, h_wh90_base, h_wh90_bTagMinus, b) << 
	  " &  "<<relSysUncBCTag(h_wh90_cTagPlus, h_wh90_base, h_wh90_cTagMinus, b)<<
	  " &  "<<"6.1"<<" & "<<relStatUnc(h_wh90_base, b)<<
	  " &  "<<relSysUncTopPt(h_wh90_base, h_wh90_TopPtPlus, h_wh90_TopPtMinus, b)<<
	  " \\\\[0.1cm] "<<endl;

  outFile<<"MC signal ($M_{H^\\pm}=100$ GeV)"<< " & "<<2.5<< std::setprecision(2)<< 
	  " &  "<< relSysUncBCTag(h_wh100_base, h_wh100_PileupPlus, h_wh100_PileupMinus, b)<<
	  " &  "<<3.0<< " & "<<relSysUncJetMET( h_wh100_JESPlus, h_wh100_base, 
	            h_wh100_JESMinus, h_wh100_JERPlus, h_wh100_JERMinus, b) <<
	  " &  "<< relSysUncBCTag(h_wh100_bTagPlus, h_wh100_base, h_wh100_bTagMinus, b) << 
	  " &  "<<relSysUncBCTag(h_wh100_cTagPlus, h_wh100_base, h_wh100_cTagMinus, b)<<
	  " &  "<<"6.1"<<" & "<<relStatUnc(h_wh100_base, b)<<
	  " &  "<<relSysUncTopPt(h_wh100_base, h_wh100_TopPtPlus, h_wh100_TopPtMinus, b)<<
	  " \\\\[0.1cm] "<<endl;

  outFile<<"MC signal ($M_{H^\\pm}=120$ GeV)"<< " & "<<2.5<< std::setprecision(2)<< 
	  " &  "<< relSysUncBCTag(h_wh120_base, h_wh120_PileupPlus, h_wh120_PileupMinus, b)<<
	  " &  "<<3.0<< " & "<<relSysUncJetMET( h_wh120_JESPlus, h_wh120_base, 
	            h_wh120_JESMinus, h_wh120_JERPlus, h_wh120_JERMinus, b) <<
	  " &  "<< relSysUncBCTag(h_wh120_bTagPlus, h_wh120_base, h_wh120_bTagMinus, b) << 
	  " &  "<<relSysUncBCTag(h_wh120_cTagPlus, h_wh120_base, h_wh120_cTagMinus, b)<<
	  " &  "<<"6.1"<<" & "<<relStatUnc(h_wh120_base, b)<<
	  " &  "<<relSysUncTopPt(h_wh120_base, h_wh120_TopPtPlus, h_wh120_TopPtMinus, b)<<
	  " \\\\[0.1cm] "<<endl;

  outFile<<"MC signal ($M_{H^\\pm}=140$ GeV)"<< " & "<<2.5<< std::setprecision(2)<< 
	  " &  "<< relSysUncBCTag(h_wh140_base, h_wh140_PileupPlus, h_wh140_PileupMinus, b)<<
	  " &  "<<3.0<< " & "<<relSysUncJetMET( h_wh140_JESPlus, h_wh140_base, 
	            h_wh140_JESMinus, h_wh140_JERPlus, h_wh140_JERMinus, b) <<
	  " &  "<< relSysUncBCTag(h_wh140_bTagPlus, h_wh140_base, h_wh140_bTagMinus, b) << 
	  " &  "<<relSysUncBCTag(h_wh140_cTagPlus, h_wh140_base, h_wh140_cTagMinus, b)<<
	  " &  "<<"6.1"<<" & "<<relStatUnc(h_wh140_base, b)<<
	  " &  "<<relSysUncTopPt(h_wh140_base, h_wh140_TopPtPlus, h_wh140_TopPtMinus, b)<<
	  " \\\\[0.1cm] "<<endl;

  outFile<<"MC signal ($M_{H^\\pm}=150$ GeV)"<< " & "<<2.5<< std::setprecision(2)<< 
	  " &  "<< relSysUncBCTag(h_wh150_base, h_wh150_PileupPlus, h_wh150_PileupMinus, b)<<
	  " &  "<<3.0<< " & "<<relSysUncJetMET( h_wh150_JESPlus, h_wh150_base, 
	            h_wh150_JESMinus, h_wh150_JERPlus, h_wh150_JERMinus, b) <<
	  " &  "<< relSysUncBCTag(h_wh150_bTagPlus, h_wh150_base, h_wh150_bTagMinus, b) << 
	  " &  "<<relSysUncBCTag(h_wh150_cTagPlus, h_wh150_base, h_wh150_cTagMinus, b)<<
	  " &  "<<"6.1"<<" & "<<relStatUnc(h_wh150_base, b)<<
	  " &  "<<relSysUncTopPt(h_wh150_base, h_wh150_TopPtPlus, h_wh150_TopPtMinus, b)<<
	  " \\\\[0.1cm] "<<endl;

  outFile<<"MC signal ($M_{H^\\pm}=155$ GeV)"<< " & "<<2.5<< std::setprecision(2)<< 
	  " &  "<< relSysUncBCTag(h_wh155_base, h_wh155_PileupPlus, h_wh155_PileupMinus, b)<<
	  " &  "<<3.0<< " & "<<relSysUncJetMET( h_wh155_JESPlus, h_wh155_base, 
	            h_wh155_JESMinus, h_wh155_JERPlus, h_wh155_JERMinus, b) <<
	  " &  "<< relSysUncBCTag(h_wh155_bTagPlus, h_wh155_base, h_wh155_bTagMinus, b) << 
	  " &  "<<relSysUncBCTag(h_wh155_cTagPlus, h_wh155_base, h_wh155_cTagMinus, b)<<
	  " &  "<<"6.1"<<" & "<<relStatUnc(h_wh155_base, b)<<
	  " &  "<<relSysUncTopPt(h_wh155_base, h_wh155_TopPtPlus, h_wh155_TopPtMinus, b)<<
	  " \\\\[0.1cm] "<<endl;

  outFile<<"MC signal ($M_{H^\\pm}=160$ GeV)"<< " & "<<2.5<< std::setprecision(2)<< 
	  " &  "<< relSysUncBCTag(h_wh160_base, h_wh160_PileupPlus, h_wh160_PileupMinus, b)<<
	  " &  "<<3.0<< " & "<<relSysUncJetMET( h_wh160_JESPlus, h_wh160_base, 
	            h_wh160_JESMinus, h_wh160_JERPlus, h_wh160_JERMinus, b) <<
	  " &  "<< relSysUncBCTag(h_wh160_bTagPlus, h_wh160_base, h_wh160_bTagMinus, b) << 
	  " &  "<<relSysUncBCTag(h_wh160_cTagPlus, h_wh160_base, h_wh160_cTagMinus, b)<<
	  " &  "<<"6.1"<<" & "<<relStatUnc(h_wh160_base, b)<<
	  " &  "<<relSysUncTopPt(h_wh160_base, h_wh160_TopPtPlus, h_wh160_TopPtMinus, b)<<
	  " \\\\[0.1cm] \\hline"<<endl;


  outFile<<"$t\\bar{t}$ + jets"<< " & "<<2.5<< std::setprecision(2)<< 
	  " &  "<< relSysUncBCTag(h_ttbar_base, h_ttbar_PileupPlus, h_ttbar_PileupMinus, b)<<
	  " &  "<<3.0<< " & "<<relSysUncJetMET( h_ttbar_JESPlus, h_ttbar_base, 
	            h_ttbar_JESMinus, h_ttbar_JERPlus, h_ttbar_JERMinus, b) <<
	  " &  "<< relSysUncBCTag(h_ttbar_bTagPlus, h_ttbar_base, h_ttbar_bTagMinus, b) << 
	  " &  "<<relSysUncBCTag(h_ttbar_cTagPlus, h_ttbar_base, h_ttbar_cTagMinus, b)<<
	  " &  "<<"6.1"<<" & "<<relStatUnc(h_ttbar_base, b)<<
	  " &  "<<relSysUncTopPt(h_ttbar_base, h_ttbar_TopPtPlus, h_ttbar_TopPtMinus, b)<<
	  " \\\\[0.1cm] "<<endl;

  outFile<<"Single ~t"<< " & "<<2.5<< std::setprecision(2)<< 
	  " &  "<< relSysUncBCTag(h_stop_base, h_stop_PileupPlus, h_stop_PileupMinus, b)<<
	  " &  "<<3.0<< " & "<<relSysUncJetMET( h_stop_JESPlus, h_stop_base, 
	            h_stop_JESMinus, h_stop_JERPlus, h_stop_JERMinus, b) <<
	  " &  "<< relSysUncBCTag(h_stop_bTagPlus, h_stop_base, h_stop_bTagMinus, b) << 
	  " &  "<<relSysUncBCTag(h_stop_cTagPlus, h_stop_base, h_stop_cTagMinus, b)<<
	  " &  "<<"5.0"<<" & "<<relStatUnc(h_stop_base, b)<<
	  " &  "<<"-"<<
	  " \\\\[0.1cm] "<<endl;

  outFile<<"W + jets"<< " & "<<2.5<< std::setprecision(2)<< 
	  " &  "<< relSysUncBCTag(h_wjet_base, h_wjet_PileupPlus, h_wjet_PileupMinus, b)<<
	  " &  "<<3.0<< " & "<<relSysUncJetMET( h_wjet_JESPlus, h_wjet_base, 
	            h_wjet_JESMinus, h_wjet_JERPlus, h_wjet_JERMinus, b) <<
	  " &  "<< relSysUncBCTag(h_wjet_bTagPlus, h_wjet_base, h_wjet_bTagMinus, b) << 
	  " &  "<<relSysUncBCTag(h_wjet_cTagPlus, h_wjet_base, h_wjet_cTagMinus, b)<<
	  " &  "<<"5.0"<<" & "<<relStatUnc(h_wjet_base, b)<<
	  " &  "<<"-"<<
	  " \\\\[0.1cm] "<<endl;

  outFile<<"$Z/\\gamma$ + jets"<< " & "<<2.5<< std::setprecision(2)<< 
	  " &  "<< relSysUncBCTag(h_zjet_base, h_zjet_PileupPlus, h_zjet_PileupMinus, b)<<
	  " &  "<<3.0<< " & "<<relSysUncJetMET( h_zjet_JESPlus, h_zjet_base, 
	            h_zjet_JESMinus, h_zjet_JERPlus, h_zjet_JERMinus, b) <<
	  " &  "<< relSysUncBCTag(h_zjet_bTagPlus, h_zjet_base, h_zjet_bTagMinus, b) << 
	  " &  "<<relSysUncBCTag(h_zjet_cTagPlus, h_zjet_base, h_zjet_cTagMinus, b)<<
	  " &  "<<"4.5"<<" & "<<relStatUnc(h_zjet_base, b)<<
	  " &  "<<"-"<<
	  " \\\\[0.1cm] "<<endl;

  outFile<<"VV"<< " & "<<2.5<< std::setprecision(2)<< 
	  " &  "<< relSysUncBCTag(h_vv_base, h_vv_PileupPlus, h_vv_PileupMinus, b)<<
	  " &  "<<3.0<< " & "<<relSysUncJetMET( h_vv_JESPlus, h_vv_base, 
	            h_vv_JESMinus, h_vv_JERPlus, h_vv_JERMinus, b) <<
	  " &  "<< relSysUncBCTag(h_vv_bTagPlus, h_vv_base, h_vv_bTagMinus, b) << 
	  " &  "<<relSysUncBCTag(h_vv_cTagPlus, h_vv_base, h_vv_cTagMinus, b)<<
	  " &  "<<"4.0"<<" & "<<relStatUnc(h_vv_base, b)<<
	  " &  "<<"-"<<
	  " \\\\[0.1cm] "<<endl;

  outFile<<"QCD"<< " & -"<<
	  " &  "<<"-"<<
	  " &  "<<"-"<<
	  " &  "<<"-"<<
	  " &  "<<"-"<<
	  " &  "<<"-"<<
	  " &  "<<"60"<<" & "<<relStatUnc(h_wh80_base, b)<<
	  " &  "<<"-"<<
	  " \\\\[0.1cm] \\hline"<<endl;
  outFile<<"\\hline "<<endl;  
  outFile<<"\\end{tabular}"<<endl; 
  //outFile<<"\\end{LARGE}"<<endl;  
  outFile<<"\\end{center}"<<endl;
  outFile<<"\\caption{First table}"<<endl;
  outFile<<"\\end{table}"<<endl;
  outFile<<"\\end{document}"<<endl;  
  outFile.close(); 
} 
