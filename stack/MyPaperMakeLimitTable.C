#include <iostream>
#include <fstream>
#include <iomanip>

void makeLimitTable(TString CHANNEL, TString CAT,
         bool isObs, bool isOut, ofstream & outFile)
  {

  float X[]        = {80, 90,100,120, 140, 150, 155, 160};
  float obsY[]     = {0., 0.,0.,0, 0, 0, 0, 0,0};
  float expY[]     = {0., 0.,0.,0, 0, 0, 0, 0,0};
		      
  float expX1sL[]   = {0.,0.,0.,0, 0, 0, 0, 0,0};
  float expX1sH[]   = {0.,0.,0.,0, 0, 0, 0, 0,0};
  float expY1sL[]   = {0.,0.,0.,0, 0, 0, 0, 0,0};
  float expY1sH[]   = {0.,0.,0.,0, 0, 0, 0, 0,0};
		      
  float expX2sL[]  = {0.,0.,0.,0, 0, 0, 0, 0,0};
  float expX2sH[]  = {0.,0.,0.,0, 0, 0, 0, 0,0};
  float expY2sL[]  = {0.,0.,0.,0, 0, 0, 0, 0,0};
  float expY2sH[]  = {0.,0.,0.,0, 0, 0, 0, 0,0};

  float expY1sL_[]   = {0.,0.,0.,0, 0, 0, 0, 0,0};
  float expY1sH_[]   = {0.,0.,0.,0, 0, 0, 0, 0,0};

  int nMassPoints = 8;
  TString ch_hist = CHANNEL+"_"+CAT;
  TString massFiles [8] = {
  "Mass80/higgsCombine_hcs_13TeV_"+ch_hist+".AsymptoticLimits.mH80.root",
  "Mass90/higgsCombine_hcs_13TeV_"+ch_hist+".AsymptoticLimits.mH90.root",
  "Mass100/higgsCombine_hcs_13TeV_"+ch_hist+".AsymptoticLimits.mH100.root",
  "Mass120/higgsCombine_hcs_13TeV_"+ch_hist+".AsymptoticLimits.mH120.root",
  "Mass140/higgsCombine_hcs_13TeV_"+ch_hist+".AsymptoticLimits.mH140.root",
  "Mass150/higgsCombine_hcs_13TeV_"+ch_hist+".AsymptoticLimits.mH150.root",
  "Mass155/higgsCombine_hcs_13TeV_"+ch_hist+".AsymptoticLimits.mH155.root",
  "Mass160/higgsCombine_hcs_13TeV_"+ch_hist+".AsymptoticLimits.mH160.root"};
  
  for(unsigned int i = 0 ; i < nMassPoints; i++){
    TFile f("limit/"+CHANNEL+"/"+CAT+"/"+massFiles[i],"READ"); 
    if(f.IsZombie()){
      cout << "Cannot open file for " << string(CHANNEL.Data()) << " and mass " << X[i] << endl;
      continue;
    }
    Double_t r;
    TTree* limit = (TTree*)f.Get("limit");
    limit->SetBranchAddress("limit",&r);
    
    for(int k = 0 ; k< limit->GetEntries() ; k++){
      limit->GetEntry(k);
      r = r*100;
      if(k==0) expY2sL[i] = r;
      if(k==1) expY1sL[i] = r;
      if(k==1) expY1sL_[i] = r;
      if(k==2) expY[i]    = r;
      if(k==3) expY1sH[i] = r;
      if(k==3) expY1sH_[i] = r;
      if(k==4) expY2sH[i] = r;
      if(k==5) obsY[i]    = r;
    }
  }
  cout<<std::setprecision(4)<<endl;
  cout<<"Mass:"<<setw(15)<<"base value"<<setw(15)<<"-2 #sigma"<<setw(15)<<"-1 #sigma"<<setw(15)<<"+1 #sigma"<<setw(15)<<"+2 #sigma"<<endl; 

  //make table
  outFile<<"\\begin{table}"<<endl; 
  outFile<<"\\begin{center}"<<endl; 
  outFile<<"\\begin{tabular}{ccccccc}"<<endl; 
  outFile<<"\\hline "<<endl;
  outFile<<"\\hline "<<endl;
  outFile<<"\\multicolumn{1}{c}{{\\bf{$m_{H^+}$}}(GeV)} & \\multicolumn{5}{c}{{Expected}} & \\multicolumn{1}{c}{{Observed}} \\\\ "<<endl;                          
  outFile<<"&\\multicolumn{1}{c}{$-2\\sigma$} &\\multicolumn{1}{c}{$-1\\sigma$} &\\multicolumn{1}{c}{median} & \\multicolumn{1}{c}{$+1\\sigma$} & \\multicolumn{1}{c}{$+2\\sigma$}&\\\\ \\hline"<<endl;   
  outFile<<"\\hline "<<endl;
  for(int i1 = 0 ; i1 < nMassPoints ; i1++){
  cout<<X[i1]<<setw(15)<<expY[i1]<<setw(15)<<expY2sL[i1]<<setw(15)<< expY1sL[i1]<<setw(15)<<expY1sH[i1]<<setw(15)<<expY2sH[i1]<<endl; 
  if(isObs)outFile<<X[i1]<<std::setprecision(3)<<" & "<<expY2sL[i1]<<" & "<< expY1sL[i1]<<" & "<<expY[i1]<<" & "<<expY1sH[i1]<<" & "<<expY2sH[i1]<<" & "<<obsY[i1]<<"\\\\"<<endl; 
  else outFile<<X[i1]<<std::setprecision(3)<<" & "<<expY2sL[i1]<<" & "<< expY1sL[i1]<<" & "<<expY[i1]<<" & "<<expY1sH[i1]<<" & "<<expY2sH[i1]<<" & "<<"-"<<"\\\\"<<endl; 
  }
  outFile<<"\\hline "<<endl;
  outFile<<"\\end{tabular}"<<endl; 
  TString ch_name = "mu";
  if(CHANNEL=="mu") ch_name = "muon";
  if(CHANNEL=="ele") ch_name = "electron";
  if(CHANNEL=="mu_ele") ch_name = "lepton";
  outFile<<"\\caption{95\\% CL exclusion limit (in \\%) for "+ch_name+" channel from exclusive charm categories.}"<<endl; 
  outFile<<"\\label{tab:limit_"+ch_name+"}"<<endl;
  outFile<<"\\end{center}"<<endl; 
  outFile<<"\\end{table}"<<endl; 
  outFile<<endl;
  
}

void MyPaperMakeLimitTable(){
  ofstream outFile; 
  outFile.open("limit/paperLimitTable.tex"); 
  //outFile<<"\\documentclass[landscape,letterpaper]{article}"<<endl;  
  outFile<<"\\documentclass[]{article}"<<endl;  
  outFile<<"\\pagestyle{empty}"<<endl;  
  outFile<<"\\usepackage{epsfig}"<<endl;  
  outFile<<"\\usepackage{amsmath}"<<endl;  
  outFile<<"\\usepackage{array}"<<endl;  
  outFile<<"\\usepackage{multirow}"<<endl;  
  outFile<<"\\usepackage[cm]{fullpage}"<<endl;  
  outFile<<"\\begin{document}"<<endl;  
  outFile<<""<<endl;
  //muon 
  bool isObs = false;
  makeLimitTable("mu", "Cat3_cTagEx", isObs, true, outFile);
  //electron 
  makeLimitTable("ele", "Cat3_cTagEx", isObs, true, outFile);
  //lepton 
  makeLimitTable("mu_ele","Cat3_cTagEx", isObs, true, outFile);
  outFile<<"\\end{document}"<<endl;  
  outFile.close(); 
}

