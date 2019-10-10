
int strToInt(string s){
  stringstream geek(s);
  int x = 0;
  geek >> x;
  return x;
}

double strToDouble(string s){
  stringstream geek(s);
  double x = 0.0;
  geek >> x;
  return x;
}
string intToStr(double val){
     ostringstream convert;
     string result("");
     convert <<val;
     result = convert.str(); 
  return result;
}

string roundOff(string input_str, int r=3, bool isDouble=false){
  ostringstream convert;
  string Result("");
  if(isDouble)convert <<std::setprecision(r)<<strToDouble(input_str);
  else convert <<std::setprecision(r)<<strToInt(input_str);
  Result = convert.str();
  return Result;
}

vector <string> getAllNuisDetails(TString inFile, bool isName, bool isCh, 
		bool isBin, bool isValL=false, bool isVal=false, bool isValH=false){
  //declare array type
  string nuisName, chName, binName;
  float val_low, val, val_high ; 
  vector<string> allNuisName;
  vector<string> allChName;
  vector<string> allBinName;
  vector<string> allVal;
  vector<string> allValL;
  vector<string> allValH;
  //open input file
  ifstream infile;
  infile.open(inFile);//open the text file
  if (!infile) {
      cout << "Unable to open file";
      exit(1); // terminate with error
  }
  //loop over all the rows of the input file
  while (!infile.eof()){
    infile >> nuisName>> chName>>binName>> val_low>> val>> val_high; 
    allNuisName.push_back(nuisName);
    allChName.push_back(chName);
    allBinName.push_back(binName);
    allVal.push_back(intToStr(val));
    allValL.push_back(intToStr(val_low));
    allValH.push_back(intToStr(val_high));
  }
  infile.close();
  if(isCh) return allChName;
  else if(isBin) return allBinName;
  else if(isValL) return allValL;
  else if(isVal) return allVal;
  else if(isValH) return allValH;
  else return allNuisName;
}

TH1F * getHisto(string histFile, TString histName){
  //ile *f = new TFile(histFile.c_str());
  TFile *f = TFile::Open(histFile.c_str());
  TH1F *hist;
  cout<<histFile<<": "<<histName<<endl;
  string exception_msg (histFile +TString("/")+histName+", does not exist");
  try{
    if(!(f->Get(histName)))
       throw  exception_msg.c_str();
  }catch (const char *e){
    cout<<"WARNING : "<<e<<endl;
  }
  //exit(0);
  if(!(f->Get(histName))){
    hist = (TH1F*)(f->Get("ttbar"))->Clone(histName);
    hist->Add(hist, -1);
  }else hist = (TH1F*)f->Get(histName);
  return hist;
  f->Close();
  delete f;
}

TH1F * getHisto2(TFile * histFile, TString histName){
  TH1F *hist;
  ///cout<<histFile->GetName()<<": "<<histName<<endl;
  string exception_msg (histFile->GetName() +TString("/")+histName+", does not exist");
  try{
    if(!(histFile->Get(histName)))
       throw  exception_msg.c_str();
  }catch (const char *e){
    cout<<"WARNING : "<<e<<endl;
  }
  //exit(0);
  if(!(histFile->Get(histName))){
    hist = (TH1F*)(histFile->Get("ttbar"))->Clone(histName);
    hist->Add(hist, -1);
  }else hist = (TH1F*)histFile->Get(histName);
  return hist;
}

string makeRow(string histname, TH1F *h, int bin, int sf){
   string allBinValue = histname;
   double binCon = h->GetBinContent(bin);
   double binErr = h->GetBinError(bin);
   double ratio = (binErr/binCon)*100;
   double nEff = (binCon/binErr)*(binCon/binErr);
   if(ratio > 60) cout<<ratio<<" : "<<histname<<" : "<<bin<<endl;
   ///double nEff = 1.0;
   allBinValue = histname +" & "+ intToStr(binCon)+ " & "+ intToStr(binErr) + " & "+ intToStr(ratio)+ " & "+intToStr(nEff) ;
   return allBinValue ;
}

void makeTable(ofstream &outFile, string sys, int bin, 
		TH1F *h_wh,
		TH1F *h_ttbar,
		TH1F *h_stop,
		TH1F *h_wjets,
		TH1F *h_dyjets,
		TH1F *h_qcd,
		TH1F *h_vv,
		TH1F *h_data, string tableCap){
  outFile<<""<<endl;
  outFile<<"%%%%%%%%%%%%%%%%%% NEXT TABLE: prop\\_bin"+sys+" %%%%%%%%%%%%%%%%%"<<endl;
  outFile<<"\\begin{table}"<<endl; 
  outFile<<"\\begin{center}"<<endl; 
  outFile<<"\\begin{tabular}{ |c| c| c| c|c| }"<<endl; 
  outFile<<"\\multicolumn{5}{c}{ } \\\\"<<endl; 
  outFile<<"\\hline "<<endl;
  outFile<<"\\multicolumn{1}{| c|}{prob\\_bin"+ sys +" } & \\multicolumn{1}{ c|}{ binContent} & \\multicolumn{1}{ c|}{binError} &\\multicolumn{1}{ c|}{\\\%Error} & \\multicolumn{1}{ c|}{ Neff} \\\\ "<<endl;
  outFile<<"\\hline "<<endl;
  outFile<<"\\hline "<<endl;
  TH1F* h_MC = (TH1F*)h_ttbar->Clone("Bkg MC");
  h_MC->Add(h_stop);
  h_MC->Add(h_wjets);
  h_MC->Add(h_dyjets);
  h_MC->Add(h_qcd);
  h_MC->Add(h_vv);
  
  outFile<<makeRow("MC signal ($M_{H^\\pm}=120$ GeV)", 	h_wh, 		bin, 1)<<" \\\\ "<<endl;
  outFile<<"\\hline "<<endl;
  outFile<<makeRow("SM $t\\bar{t}$ + jets", 	h_ttbar, 	bin, 1)<<" \\\\ "<<endl;
  outFile<<makeRow("Single t", 	h_stop, 	bin, 1)<<" \\\\ "<<endl;
  outFile<<makeRow("W + jets", 	h_wjets, 	bin, 1)<<" \\\\ "<<endl;
  outFile<<makeRow("$Z/\\gamma$ + jets", 	h_dyjets, 	bin, 1)<<" \\\\ "<<endl;
  outFile<<makeRow("QCD", 	h_qcd, 		bin, 1)<<" \\\\ "<<endl;
  outFile<<makeRow("VV", 	h_vv, 		bin, 1)<<" \\\\ "<<endl;
  outFile<<"\\hline "<<endl;
  outFile<<makeRow("Bkg", 	h_MC, 		bin, 1)<<" \\\\ "<<endl;
  outFile<<"\\hline "<<endl;
  outFile<<makeRow("Data", 	h_data, 	bin, 1)<<" \\\\ "<<endl;
  outFile<<"\\hline "<<endl;
  outFile<<"\\hline "<<endl;
  outFile<<"\\end{tabular}"<<endl;
  //outFile<<"%\\end{LARGE}"<<endl; 
  outFile<<"\\end{center}"<<endl; 
  outFile<<"\\caption{Nuisance parameter name (-1$\\sigma$, median, +1$\\sigma$): prop\\_bin"+sys+tableCap+"}"<<endl; 
  outFile<<"\\end{table}"<<endl; 
}

string makeRow2(string index, string np_name, string mjj, string np_median, TH1F * hData,  
	       	TH1F * hBkg, int bin, string sys){
   int r = 3;
   double integralBkg = hBkg->Integral();
   double integralData = hData->Integral();
   double data_mc = (100*integralData/integralBkg);
   string ratio = roundOff(intToStr(data_mc), 4, true);

   string allBinValue = index +" & "+ roundOff(intToStr(integralData), r)+" &"+ 
	   roundOff(intToStr(integralBkg), r)+" & "+ratio+ " & "+ np_name +" & "+ mjj +" & "+ 
	   roundOff(np_median, r, true) + " & ";
   double binConBkg = hBkg->GetBinContent(bin);
   double binErrBkg = hBkg->GetBinError(bin);
   double binConData = hData->GetBinContent(bin);
   double percent_err = 100*sqrt(strToInt(sys)*strToInt(sys)+ binErrBkg*binErrBkg)/binConBkg;
   allBinValue += intToStr(binConData) +" & "+ roundOff(intToStr(binConBkg), 4)+" &" + roundOff(intToStr(binErrBkg), r) + " & "+ roundOff(sys,r) + " & "+ roundOff(intToStr(percent_err), r) ;
   return allBinValue ;
}

void beginTable(ofstream &outFile, string sys, string tableCap){
  outFile<<"%%%%%%%%%%%%%%%%%% NEXT TABLE: prop\\_bin"+sys+" %%%%%%%%%%%%%%%%%"<<endl;
  outFile<<"\\begin{table}"<<endl; 
  outFile<<"\\begin{center}"<<endl; 
  outFile<<"\\begin{tabular}{ |c|c| c| c| c|c|c|c|c|c|c|c| }"<<endl; 
  outFile<<"\\multicolumn{12}{c}{ } \\\\"<<endl; 
  outFile<<"\\hline "<<endl;
  outFile<<"S.N & $N_{data}$ & $N_{bkg}$ & Ratio & Nuisance parameter & $M_{jj}$ & NP & $n_{data}$ & $n_{bkg}$ & $e_{bkg}$ & $e_{bkg}$ & \\\% $e_{bkg}$  \\\\ "<<endl;
  outFile<<"& (total) & (total) & (\\%) & & $(GeV)$ &(value)& $(n^{th} bin)$ & $(n^{th} bin)$ & (stat) & (sys) & (sys+stat)  \\\\ "<<endl;
  outFile<<"\\hline "<<endl;
} 
void endTable(ofstream &outFile, string sys, string tableCap){
  outFile<<"\\hline "<<endl;
  outFile<<"\\end{tabular}"<<endl;
  //outFile<<"%\\end{LARGE}"<<endl; 
  outFile<<"\\end{center}"<<endl; 
  outFile<<"\\caption{Number of events in the $n^{th}$ bin of data and total Bkg (with statistical and systematic uncertainties), for which the post fit value of corresponding nuisance parameter are more than $\\pm$ 1.}"<<endl; 
  outFile<<"\\end{table}"<<endl; 
}

string mjj( string binName){
  int m = strToInt(binName);
  int m_new = (m+1)*5 + 20;
  string m_str = intToStr(m_new);
  return m_str; 
}

double sysUncJESTopPt( TH1F * h_JESPlus, TH1F * h_base, TH1F * h_JESMinus, TH1F * h_JERPlus, TH1F * h_JERMinus, TH1F * h_TopPtPlus, TH1F * h_TopPtMinus, int b){
  double uncJES = pow(TMath::Max(fabs(h_JESPlus->GetBinContent(b) - h_base->GetBinContent(b)), fabs(h_base->GetBinContent(b) - h_JESMinus->GetBinContent(b))), 2);
  double uncJER = pow(TMath::Max(fabs(h_JERPlus->GetBinContent(b) - h_base->GetBinContent(b)), fabs(h_base->GetBinContent(b) - h_JERMinus->GetBinContent(b))), 2);
  double uncTop = pow(TMath::Max(fabs(h_TopPtPlus->GetBinContent(b) - h_base->GetBinContent(b)), fabs(h_base->GetBinContent(b) - h_TopPtMinus->GetBinContent(b))), 2);
  double unc = sqrt(uncJES +uncJER  +uncTop);
  return unc ;
}

double sysUncJES( TH1F * h_JESPlus, TH1F * h_base, TH1F * h_JESMinus, TH1F * h_JERPlus, TH1F * h_JERMinus, int b){
  double uncJES = pow(TMath::Max(fabs(h_JESPlus->GetBinContent(b) - h_base->GetBinContent(b)), fabs(h_base->GetBinContent(b) - h_JESMinus->GetBinContent(b))), 2);
  double uncJER = pow(TMath::Max(fabs(h_JERPlus->GetBinContent(b) - h_base->GetBinContent(b)), fabs(h_base->GetBinContent(b) - h_JERMinus->GetBinContent(b))), 2);
  double unc = sqrt(uncJES +uncJER);
  return unc ;
}
double sysUncBCTag (TH1F * h_bTagPlus, TH1F * h_base, TH1F * h_bTagMinus, int b){
	double uncTag = TMath::Max(fabs(h_bTagPlus->GetBinContent(b) - h_base->GetBinContent(b)), fabs(h_base->GetBinContent(b) - h_bTagMinus->GetBinContent(b)));
	return uncTag;
}	

double getSysUncOneProc(TFile * histFile, TString histName, int b){
  TH1F *base = getHisto2(histFile, histName);
  TH1F *base_JESUp = getHisto2(histFile, histName+"_JESUp");
  TH1F *base_JESDown = getHisto2(histFile, histName+"_JESDown");
  TH1F *base_JERUp = getHisto2(histFile, histName+"_JERUp");
  TH1F *base_JERDown = getHisto2(histFile, histName+"_JERDown");
  TH1F *base_cTagUp = getHisto2(histFile, histName+"_cTagUp");
  TH1F *base_cTagDown = getHisto2(histFile, histName+"_cTagDown");
  TH1F *base_bTagUp = getHisto2(histFile, histName+"_bTagUp");
  TH1F *base_bTagDown = getHisto2(histFile, histName+"_bTagDown");
  TH1F *base_PileupUp = getHisto2(histFile, histName+"_PileupUp");
  TH1F *base_PileupDown = getHisto2(histFile, histName+"_PileupDown");
  double sysUnc1 = 0.0;
  if(histName=="ttbar"){
    TH1F *base_topPtUp = getHisto2(histFile, histName+"_topPtUp");
    TH1F *base_topPtDown = getHisto2(histFile, histName+"_topPtDown");
    sysUnc1= sysUncJESTopPt(base_JESUp, base, base_JESDown, base_JERUp, base_JERDown, base_topPtUp, base_topPtDown, b);
  }
  else sysUnc1 = sysUncJES(base_JESUp, base, base_JESDown, base_JERUp, base_JERDown, b);
  double sysUnc2 = sysUncBCTag(base_bTagUp, base, base_bTagDown, b);
  double sysUnc3 = sysUncBCTag(base_cTagUp, base, base_cTagDown, b);
  double sysAll = sqrt(sysUnc1*sysUnc1 + sysUnc2*sysUnc2 +sysUnc3*sysUnc3);
  return sysAll;
}

double getSysUncAllBkg(TFile *histFile, int b){
    double unc_ttbar = getSysUncOneProc(histFile, "ttbar", b);
    double unc_stop = getSysUncOneProc(histFile, "stop", b);
    double unc_wjet = getSysUncOneProc(histFile, "wjet", b);
    //double unc_zjet = 0.0;
    //double unc_diboson = 0.0;
    double unc_zjet = getSysUncOneProc(histFile, "zjet", b);
    double unc_diboson = getSysUncOneProc(histFile, "diboson", b);
    double unc_all = sqrt(unc_ttbar*unc_ttbar + unc_wjet*unc_wjet +unc_zjet*unc_zjet +unc_stop*unc_stop + unc_diboson*unc_diboson);
    return unc_all;
}

double getTotInt(string histFile, bool isData=false, bool isBkg =false){
  TFile *f = TFile::Open(histFile.c_str());
  TH1F *ttbar = getHisto2(f, "ttbar");
  TH1F *data = getHisto2(f, "data_obs");
  TH1F *wjet = getHisto2(f, "wjet");
  TH1F *zjet = getHisto2(f, "zjet");
  TH1F *stop = getHisto2(f, "stop");
  TH1F *diboson = getHisto2(f, "diboson");
  TH1F *qcd = getHisto2(f, "qcd");
  TH1F* h_Bkg = (TH1F*)ttbar->Clone("Bkg MC");
  h_Bkg->Add(wjet);
  h_Bkg->Add(zjet);
  h_Bkg->Add(stop);
  h_Bkg->Add(diboson);
  h_Bkg->Add(qcd);
  if(isData) return data->Integral();
  else return h_Bkg->Integral();
}

void nuisParam1Sigma(){

  std::map<std::string, std::string> mjjFiles;
  mjjFiles["ch1"] = "HplusShapes_mu_PtbJetCatL_mjj_kfit_25To42_13TeV.root"; 
  mjjFiles["ch2"] = "HplusShapes_mu_PtbJetCatL_mjj_kfit_42To57_13TeV.root"; 
  mjjFiles["ch3"] = "HplusShapes_mu_PtbJetCatL_mjj_kfit_57To74_13TeV.root"; 
  mjjFiles["ch4"] = "HplusShapes_mu_PtbJetCatL_mjj_kfit_74To99_13TeV.root"; 
  mjjFiles["ch5"] = "HplusShapes_mu_PtbJetCatL_mjj_kfit_99To500_13TeV.root"; 
  mjjFiles["ch6"] = "HplusShapes_mu_PtbJetCatM_mjj_kfit_25To42_13TeV.root"; 
  mjjFiles["ch7"] = "HplusShapes_mu_PtbJetCatM_mjj_kfit_42To57_13TeV.root"; 
  mjjFiles["ch8"] = "HplusShapes_mu_PtbJetCatM_mjj_kfit_57To74_13TeV.root"; 
  mjjFiles["ch9"] = "HplusShapes_mu_PtbJetCatM_mjj_kfit_74To99_13TeV.root"; 
  mjjFiles["ch10"]= "HplusShapes_mu_PtbJetCatM_mjj_kfit_99To500_13TeV.root";
  mjjFiles["ch11"]= "HplusShapes_mu_PtbJetCatT_mjj_kfit_25To42_13TeV.root"; 
  mjjFiles["ch12"]= "HplusShapes_mu_PtbJetCatT_mjj_kfit_42To57_13TeV.root"; 
  mjjFiles["ch13"]= "HplusShapes_mu_PtbJetCatT_mjj_kfit_57To74_13TeV.root"; 
  mjjFiles["ch14"]= "HplusShapes_mu_PtbJetCatT_mjj_kfit_74To99_13TeV.root"; 
  mjjFiles["ch15"]= "HplusShapes_mu_PtbJetCatT_mjj_kfit_99To500_13TeV.root";
  mjjFiles["ch16"]= "HplusShapes_ele_PtbJetCatL_mjj_kfit_25To42_13TeV.root";
  mjjFiles["ch17"]= "HplusShapes_ele_PtbJetCatL_mjj_kfit_42To57_13TeV.root";
  mjjFiles["ch18"]= "HplusShapes_ele_PtbJetCatL_mjj_kfit_57To74_13TeV.root";
  mjjFiles["ch19"]= "HplusShapes_ele_PtbJetCatL_mjj_kfit_74To99_13TeV.root";
  mjjFiles["ch20"]= "HplusShapes_ele_PtbJetCatL_mjj_kfit_99To500_13TeV.root";
  mjjFiles["ch21"]= "HplusShapes_ele_PtbJetCatM_mjj_kfit_25To42_13TeV.root"; 
  mjjFiles["ch22"]= "HplusShapes_ele_PtbJetCatM_mjj_kfit_42To57_13TeV.root"; 
  mjjFiles["ch23"]= "HplusShapes_ele_PtbJetCatM_mjj_kfit_57To74_13TeV.root"; 
  mjjFiles["ch24"]= "HplusShapes_ele_PtbJetCatM_mjj_kfit_74To99_13TeV.root"; 
  mjjFiles["ch25"]= "HplusShapes_ele_PtbJetCatM_mjj_kfit_99To500_13TeV.root";
  mjjFiles["ch26"]= "HplusShapes_ele_PtbJetCatT_mjj_kfit_25To42_13TeV.root"; 
  mjjFiles["ch27"]= "HplusShapes_ele_PtbJetCatT_mjj_kfit_42To57_13TeV.root"; 
  mjjFiles["ch28"]= "HplusShapes_ele_PtbJetCatT_mjj_kfit_57To74_13TeV.root"; 
  mjjFiles["ch29"]= "HplusShapes_ele_PtbJetCatT_mjj_kfit_74To99_13TeV.root"; 
  mjjFiles["ch30"]= "HplusShapes_ele_PtbJetCatT_mjj_kfit_99To500_13TeV.root"; 

  vector<std::string> fKey;
  vector<std::string> fVal;
  fKey.push_back("ch1")  ; fVal.push_back("HplusShapes_mu_PtbJetCatL_mjj_kfit_25To42_13TeV.root"); 
  fKey.push_back("ch2")  ; fVal.push_back("HplusShapes_mu_PtbJetCatL_mjj_kfit_42To57_13TeV.root"); 
  fKey.push_back("ch3")  ; fVal.push_back("HplusShapes_mu_PtbJetCatL_mjj_kfit_57To74_13TeV.root"); 
  fKey.push_back("ch4")  ; fVal.push_back("HplusShapes_mu_PtbJetCatL_mjj_kfit_74To99_13TeV.root"); 
  fKey.push_back("ch5")  ; fVal.push_back("HplusShapes_mu_PtbJetCatL_mjj_kfit_99To500_13TeV.root"); 
  fKey.push_back("ch6")  ; fVal.push_back("HplusShapes_mu_PtbJetCatM_mjj_kfit_25To42_13TeV.root"); 
  fKey.push_back("ch7")  ; fVal.push_back("HplusShapes_mu_PtbJetCatM_mjj_kfit_42To57_13TeV.root"); 
  fKey.push_back("ch8")  ; fVal.push_back("HplusShapes_mu_PtbJetCatM_mjj_kfit_57To74_13TeV.root"); 
  fKey.push_back("ch9")  ; fVal.push_back("HplusShapes_mu_PtbJetCatM_mjj_kfit_74To99_13TeV.root"); 
  fKey.push_back("ch10") ; fVal.push_back("HplusShapes_mu_PtbJetCatM_mjj_kfit_99To500_13TeV.root");
  fKey.push_back("ch11") ; fVal.push_back("HplusShapes_mu_PtbJetCatT_mjj_kfit_25To42_13TeV.root"); 
  fKey.push_back("ch12") ; fVal.push_back("HplusShapes_mu_PtbJetCatT_mjj_kfit_42To57_13TeV.root"); 
  fKey.push_back("ch13") ; fVal.push_back("HplusShapes_mu_PtbJetCatT_mjj_kfit_57To74_13TeV.root"); 
  fKey.push_back("ch14") ; fVal.push_back("HplusShapes_mu_PtbJetCatT_mjj_kfit_74To99_13TeV.root"); 
  fKey.push_back("ch15") ; fVal.push_back("HplusShapes_mu_PtbJetCatT_mjj_kfit_99To500_13TeV.root");
  fKey.push_back("ch16") ; fVal.push_back("HplusShapes_ele_PtbJetCatL_mjj_kfit_25To42_13TeV.root");
  fKey.push_back("ch17") ; fVal.push_back("HplusShapes_ele_PtbJetCatL_mjj_kfit_42To57_13TeV.root");
  fKey.push_back("ch18") ; fVal.push_back("HplusShapes_ele_PtbJetCatL_mjj_kfit_57To74_13TeV.root");
  fKey.push_back("ch19") ; fVal.push_back("HplusShapes_ele_PtbJetCatL_mjj_kfit_74To99_13TeV.root");
  fKey.push_back("ch20") ; fVal.push_back("HplusShapes_ele_PtbJetCatL_mjj_kfit_99To500_13TeV.root");
  fKey.push_back("ch21") ; fVal.push_back("HplusShapes_ele_PtbJetCatM_mjj_kfit_25To42_13TeV.root"); 
  fKey.push_back("ch22") ; fVal.push_back("HplusShapes_ele_PtbJetCatM_mjj_kfit_42To57_13TeV.root"); 
  fKey.push_back("ch23") ; fVal.push_back("HplusShapes_ele_PtbJetCatM_mjj_kfit_57To74_13TeV.root"); 
  fKey.push_back("ch24") ; fVal.push_back("HplusShapes_ele_PtbJetCatM_mjj_kfit_74To99_13TeV.root"); 
  fKey.push_back("ch25") ; fVal.push_back("HplusShapes_ele_PtbJetCatM_mjj_kfit_99To500_13TeV.root");
  fKey.push_back("ch26") ; fVal.push_back("HplusShapes_ele_PtbJetCatT_mjj_kfit_25To42_13TeV.root"); 
  fKey.push_back("ch27") ; fVal.push_back("HplusShapes_ele_PtbJetCatT_mjj_kfit_42To57_13TeV.root"); 
  fKey.push_back("ch28") ; fVal.push_back("HplusShapes_ele_PtbJetCatT_mjj_kfit_57To74_13TeV.root"); 
  fKey.push_back("ch29") ; fVal.push_back("HplusShapes_ele_PtbJetCatT_mjj_kfit_74To99_13TeV.root"); 
  fKey.push_back("ch30") ; fVal.push_back("HplusShapes_ele_PtbJetCatT_mjj_kfit_99To500_13TeV.root"); 

  std::vector<std::string> chName;
  chName.push_back("mu");
  chName.push_back("ele");
  
  std::vector<std::string> cTagCat;
  cTagCat.push_back("L");
  cTagCat.push_back("M");
  cTagCat.push_back("T");

  std::vector<std::string> bJetPtCat;
  bJetPtCat.push_back("25-41");
  bJetPtCat.push_back("42-56");
  bJetPtCat.push_back("57-73");
  bJetPtCat.push_back("74-98");
  bJetPtCat.push_back("99-500");

  ofstream outFile; 
  outFile.open("nuisParam1SigmaTable.tex"); 
  outFile<<"\\documentclass[]{article}"<<endl;  
  outFile<<"\\pagestyle{empty}"<<endl;  
  outFile<<"\\usepackage{epsfig}"<<endl;  
  outFile<<"\\usepackage{amsmath}"<<endl;  
  outFile<<"\\usepackage{array}"<<endl;  
  outFile<<"\\usepackage{multirow}"<<endl;  
  outFile<<"\\usepackage[cm]{fullpage}"<<endl;  
  outFile<<"\\usepackage[T1]{fontenc}"<<endl;  
  outFile<<"\\textheight = 8.in"<<endl;  
  outFile<<"\\textwidth 7.0in"<<endl;  
  outFile<<"\\begin{document}"<<endl;  
  outFile<<""<<endl;

  outFile<<"\\begin{table}"<<endl; 
  outFile<<"\\begin{center}"<<endl; 
  outFile<<"\\begin{tabular}{ |c| c|c|c|c|c|c|c|}"<<endl; 
  outFile<<"\\multicolumn{8}{c}{ } \\\\"<<endl; 
  outFile<<"\\hline "<<endl;
  outFile<<"S.N. & $N_{data}$ & $N_{bkg}$ & $\\frac{100*N_{data}}{N_{bkg}}$ & Nuisance param & Channel & Charm cat & b-jet pT (GeV)\\\\"<<endl; 
  outFile<<"\\hline "<<endl;
  outFile<<"\\hline "<<endl;
  int ch    =  1;
  int ctag  =  1;
  int bjet  =  0;
  double all_data = 0;
  double all_mc = 0;
  for(int count =1; count<fVal.size()+1; count++){
    double n_data = getTotInt(fVal[count-1], true, false);
    double n_mc = getTotInt(fVal[count-1], false, true);
    double data_mc = 100*n_data/n_mc;
    all_data = all_data+n_data;
    all_mc = all_mc + n_mc;
    bjet++;
    //cout<<fKey[count-1]<<": ch = "<<ch<<", ctag = "<<ctag<<", bjet = "<<bjet<<endl;
    outFile<<intToStr(count)+" & "+ intToStr(n_data)+" & "+ intToStr(n_mc)+" & "+ roundOff(intToStr(data_mc), 4, true)+"& prop\\_bin"+fKey[count -1]+"& "+chName[ch-1]+" & "+ cTagCat[ctag-1]+" & "+bJetPtCat[bjet-1] +"\\\\"<<endl;
    if (count%5 == 0) bjet = 0;
    if(count%5 == 0) ctag ++;
    if(count%15 == 0){ch ++; ctag=1;}
    if(count==15){
      outFile<<"\\hline "<<endl;
      outFile<< " & "+ intToStr(all_data)+" & "+ intToStr(all_mc) +" & "+ roundOff(intToStr(100*all_data/all_mc), 4, true)+" & "+" & "+ " & "+ " & "+ "\\\\"<<endl; 
      outFile<<"\\hline "<<endl;
      all_data = 0;
      all_mc = 0;
    }
  }
  outFile<<"\\hline "<<endl;
  outFile<< " & "+ intToStr(all_data)+" & "+ intToStr(all_mc) +" & "+ roundOff(intToStr(100*all_data/all_mc), 4, true)+" & "+" & "+ " & "+ " & "+ "\\\\"<<endl; 
  outFile<<"\\hline "<<endl;

  outFile<<"\\end{tabular}"<<endl;
  //outFile<<"%\\end{LARGE}"<<endl; 
  outFile<<"\\end{center}"<<endl; 
  outFile<<"\\caption{Description of 30 [2 channel (mu, ele), 3 charm categories, and 5 b-jet pT bining] Mjj distributions used for limit computation for lepton channel.}"<<endl; 
  outFile<<"\\end{table}"<<endl; 

  vector <string > allNuisName = getAllNuisDetails("newNuisParam1Sigma.txt", true, false, false);
  vector <string > allChName = getAllNuisDetails("newNuisParam1Sigma.txt", false, true, false);
  vector <string > allBinName = getAllNuisDetails("newNuisParam1Sigma.txt", false, false, true);
  vector <string > allValL = getAllNuisDetails("newNuisParam1Sigma.txt", false, false, false, true);
  vector <string > allVal = getAllNuisDetails("newNuisParam1Sigma.txt", false, false, false, false, true);
  vector <string > allValH = getAllNuisDetails("newNuisParam1Sigma.txt", false, false, false, false, false, true);
  int k = 0;
  int n_param = 40;
  ///for(int i = 0; i<20; i++){
  for(int i = 0; i<allNuisName.size(); i++){
    ///cout<<mjjFiles[allChName[i]]<<": "<< allChName[i]<<": "<<allBinName[i]<<endl;
    TFile *f = TFile::Open(mjjFiles[allChName[i]].c_str());
    TH1F *ttbar = getHisto2(f, "ttbar");
    TH1F *data = getHisto2(f, "data_obs");
    TH1F *wjet = getHisto2(f, "wjet");
    TH1F *zjet = getHisto2(f, "zjet");
    TH1F *stop = getHisto2(f, "stop");
    TH1F *diboson = getHisto2(f, "diboson");
    TH1F *qcd = getHisto2(f, "qcd");
    TH1F *WH120 = getHisto2(f, "WH120");

    TH1F* h_Bkg = (TH1F*)ttbar->Clone("Bkg MC");
    h_Bkg->Add(wjet);
    h_Bkg->Add(zjet);
    h_Bkg->Add(stop);
    h_Bkg->Add(diboson);
    h_Bkg->Add(qcd);
    double sysUncAllBkg = getSysUncAllBkg(f, strToInt(allBinName[i])+1);
    //if(i%3 ==0) outFile<<"\\clearpage"<<endl;
    //makeTable(outFile, allChName[i]+"\\_bin"+allBinName[i], strToInt(allBinName[i])+1, WH120, ttbar, stop, wjet, zjet, qcd, diboson, data, " ("+allValL[i]+", "+allVal[i]+", "+allValH[i]+")"); 
    if(i%n_param ==0) k++;
    if(i==n_param*(k-1)) {
      outFile<<"\\clearpage"<<endl;
      beginTable(outFile, allChName[i]+"\\_bin"+allBinName[i], " ("+allValL[i]+", "+allVal[i]+", "+allValH[i]+")");
    }
      outFile<<makeRow2(intToStr(i+1), "prop\\_bin"+allChName[i]+"\\_bin"+allBinName[i], mjj(allBinName[i]), allVal[i], data, h_Bkg, strToInt(allBinName[i])+1, intToStr(sysUncAllBkg))<<" \\\\ "<<endl;
    if(i ==n_param*k-1 || i== (allNuisName.size()-1)) {
      endTable(outFile, allChName[i]+"\\_bin"+allBinName[i], " ("+allValL[i]+", "+allVal[i]+", "+allValH[i]+")");
    }
  }
  outFile<<"\\end{document}"<<endl;  
  outFile.close(); 
} 
