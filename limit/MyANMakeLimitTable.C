#include <iostream>
#include <fstream>
#include <iomanip>

  //-------------------------------------------------//
  //         Inclusive Mjj   
  //-------------------------------------------------//
  TString massFiles_mu_Cat1_Inc [8] = {
  "mu/Cat1_Inc/Mass80/higgsCombine_hcs_13TeV_mu_Cat1_Inc.AsymptoticLimits.mH80.root",
  "mu/Cat1_Inc/Mass90/higgsCombine_hcs_13TeV_mu_Cat1_Inc.AsymptoticLimits.mH90.root",
  "mu/Cat1_Inc/Mass100/higgsCombine_hcs_13TeV_mu_Cat1_Inc.AsymptoticLimits.mH100.root",
  "mu/Cat1_Inc/Mass120/higgsCombine_hcs_13TeV_mu_Cat1_Inc.AsymptoticLimits.mH120.root",
  "mu/Cat1_Inc/Mass140/higgsCombine_hcs_13TeV_mu_Cat1_Inc.AsymptoticLimits.mH140.root",
  "mu/Cat1_Inc/Mass150/higgsCombine_hcs_13TeV_mu_Cat1_Inc.AsymptoticLimits.mH150.root",
  "mu/Cat1_Inc/Mass155/higgsCombine_hcs_13TeV_mu_Cat1_Inc.AsymptoticLimits.mH155.root",
  "mu/Cat1_Inc/Mass160/higgsCombine_hcs_13TeV_mu_Cat1_Inc.AsymptoticLimits.mH160.root"};

  TString massFiles_ele_Cat1_Inc [8] = {
  "ele/Cat1_Inc/Mass80/higgsCombine_hcs_13TeV_ele_Cat1_Inc.AsymptoticLimits.mH80.root",
  "ele/Cat1_Inc/Mass90/higgsCombine_hcs_13TeV_ele_Cat1_Inc.AsymptoticLimits.mH90.root",
  "ele/Cat1_Inc/Mass100/higgsCombine_hcs_13TeV_ele_Cat1_Inc.AsymptoticLimits.mH100.root",
  "ele/Cat1_Inc/Mass120/higgsCombine_hcs_13TeV_ele_Cat1_Inc.AsymptoticLimits.mH120.root",
  "ele/Cat1_Inc/Mass140/higgsCombine_hcs_13TeV_ele_Cat1_Inc.AsymptoticLimits.mH140.root",
  "ele/Cat1_Inc/Mass150/higgsCombine_hcs_13TeV_ele_Cat1_Inc.AsymptoticLimits.mH150.root",
  "ele/Cat1_Inc/Mass155/higgsCombine_hcs_13TeV_ele_Cat1_Inc.AsymptoticLimits.mH155.root",
  "ele/Cat1_Inc/Mass160/higgsCombine_hcs_13TeV_ele_Cat1_Inc.AsymptoticLimits.mH160.root"};

  TString massFiles_mu_ele_Cat1_Inc [8] = {
  "mu_ele/Cat1_Inc/Mass80/higgsCombine_hcs_13TeV_mu_ele_Cat1_Inc.AsymptoticLimits.mH80.root",
  "mu_ele/Cat1_Inc/Mass90/higgsCombine_hcs_13TeV_mu_ele_Cat1_Inc.AsymptoticLimits.mH90.root",
  "mu_ele/Cat1_Inc/Mass100/higgsCombine_hcs_13TeV_mu_ele_Cat1_Inc.AsymptoticLimits.mH100.root",
  "mu_ele/Cat1_Inc/Mass120/higgsCombine_hcs_13TeV_mu_ele_Cat1_Inc.AsymptoticLimits.mH120.root",
  "mu_ele/Cat1_Inc/Mass140/higgsCombine_hcs_13TeV_mu_ele_Cat1_Inc.AsymptoticLimits.mH140.root",
  "mu_ele/Cat1_Inc/Mass150/higgsCombine_hcs_13TeV_mu_ele_Cat1_Inc.AsymptoticLimits.mH150.root",
  "mu_ele/Cat1_Inc/Mass155/higgsCombine_hcs_13TeV_mu_ele_Cat1_Inc.AsymptoticLimits.mH155.root",
  "mu_ele/Cat1_Inc/Mass160/higgsCombine_hcs_13TeV_mu_ele_Cat1_Inc.AsymptoticLimits.mH160.root"};

  TString massFiles_mu_Cat2_cTagInc [8] = {
  "mu/Cat2_cTagInc/Mass80/higgsCombine_hcs_13TeV_mu_Cat2_cTagInc.AsymptoticLimits.mH80.root",
  "mu/Cat2_cTagInc/Mass90/higgsCombine_hcs_13TeV_mu_Cat2_cTagInc.AsymptoticLimits.mH90.root",
  "mu/Cat2_cTagInc/Mass100/higgsCombine_hcs_13TeV_mu_Cat2_cTagInc.AsymptoticLimits.mH100.root",
  "mu/Cat2_cTagInc/Mass120/higgsCombine_hcs_13TeV_mu_Cat2_cTagInc.AsymptoticLimits.mH120.root",
  "mu/Cat2_cTagInc/Mass140/higgsCombine_hcs_13TeV_mu_Cat2_cTagInc.AsymptoticLimits.mH140.root",
  "mu/Cat2_cTagInc/Mass150/higgsCombine_hcs_13TeV_mu_Cat2_cTagInc.AsymptoticLimits.mH150.root",
  "mu/Cat2_cTagInc/Mass155/higgsCombine_hcs_13TeV_mu_Cat2_cTagInc.AsymptoticLimits.mH155.root",
  "mu/Cat2_cTagInc/Mass160/higgsCombine_hcs_13TeV_mu_Cat2_cTagInc.AsymptoticLimits.mH160.root"};

  TString massFiles_ele_Cat2_cTagInc [8] = {
  "ele/Cat2_cTagInc/Mass80/higgsCombine_hcs_13TeV_ele_Cat2_cTagInc.AsymptoticLimits.mH80.root",
  "ele/Cat2_cTagInc/Mass90/higgsCombine_hcs_13TeV_ele_Cat2_cTagInc.AsymptoticLimits.mH90.root",
  "ele/Cat2_cTagInc/Mass100/higgsCombine_hcs_13TeV_ele_Cat2_cTagInc.AsymptoticLimits.mH100.root",
  "ele/Cat2_cTagInc/Mass120/higgsCombine_hcs_13TeV_ele_Cat2_cTagInc.AsymptoticLimits.mH120.root",
  "ele/Cat2_cTagInc/Mass140/higgsCombine_hcs_13TeV_ele_Cat2_cTagInc.AsymptoticLimits.mH140.root",
  "ele/Cat2_cTagInc/Mass150/higgsCombine_hcs_13TeV_ele_Cat2_cTagInc.AsymptoticLimits.mH150.root",
  "ele/Cat2_cTagInc/Mass155/higgsCombine_hcs_13TeV_ele_Cat2_cTagInc.AsymptoticLimits.mH155.root",
  "ele/Cat2_cTagInc/Mass160/higgsCombine_hcs_13TeV_ele_Cat2_cTagInc.AsymptoticLimits.mH160.root"};

  TString massFiles_mu_ele_Cat2_cTagInc [8] = {
  "mu_ele/Cat2_cTagInc/Mass80/higgsCombine_hcs_13TeV_mu_ele_Cat2_cTagInc.AsymptoticLimits.mH80.root",
  "mu_ele/Cat2_cTagInc/Mass90/higgsCombine_hcs_13TeV_mu_ele_Cat2_cTagInc.AsymptoticLimits.mH90.root",
  "mu_ele/Cat2_cTagInc/Mass100/higgsCombine_hcs_13TeV_mu_ele_Cat2_cTagInc.AsymptoticLimits.mH100.root",
  "mu_ele/Cat2_cTagInc/Mass120/higgsCombine_hcs_13TeV_mu_ele_Cat2_cTagInc.AsymptoticLimits.mH120.root",
  "mu_ele/Cat2_cTagInc/Mass140/higgsCombine_hcs_13TeV_mu_ele_Cat2_cTagInc.AsymptoticLimits.mH140.root",
  "mu_ele/Cat2_cTagInc/Mass150/higgsCombine_hcs_13TeV_mu_ele_Cat2_cTagInc.AsymptoticLimits.mH150.root",
  "mu_ele/Cat2_cTagInc/Mass155/higgsCombine_hcs_13TeV_mu_ele_Cat2_cTagInc.AsymptoticLimits.mH155.root",
  "mu_ele/Cat2_cTagInc/Mass160/higgsCombine_hcs_13TeV_mu_ele_Cat2_cTagInc.AsymptoticLimits.mH160.root"};


  TString massFiles_mu_Cat3_cTagEx [8] = {
  "mu/Cat3_cTagEx/Mass80/higgsCombine_hcs_13TeV_mu_Cat3_cTagEx.AsymptoticLimits.mH80.root",
  "mu/Cat3_cTagEx/Mass90/higgsCombine_hcs_13TeV_mu_Cat3_cTagEx.AsymptoticLimits.mH90.root",
  "mu/Cat3_cTagEx/Mass100/higgsCombine_hcs_13TeV_mu_Cat3_cTagEx.AsymptoticLimits.mH100.root",
  "mu/Cat3_cTagEx/Mass120/higgsCombine_hcs_13TeV_mu_Cat3_cTagEx.AsymptoticLimits.mH120.root",
  "mu/Cat3_cTagEx/Mass140/higgsCombine_hcs_13TeV_mu_Cat3_cTagEx.AsymptoticLimits.mH140.root",
  "mu/Cat3_cTagEx/Mass150/higgsCombine_hcs_13TeV_mu_Cat3_cTagEx.AsymptoticLimits.mH150.root",
  "mu/Cat3_cTagEx/Mass155/higgsCombine_hcs_13TeV_mu_Cat3_cTagEx.AsymptoticLimits.mH155.root",
  "mu/Cat3_cTagEx/Mass160/higgsCombine_hcs_13TeV_mu_Cat3_cTagEx.AsymptoticLimits.mH160.root"};

  TString massFiles_ele_Cat3_cTagEx [8] = {
  "ele/Cat3_cTagEx/Mass80/higgsCombine_hcs_13TeV_ele_Cat3_cTagEx.AsymptoticLimits.mH80.root",
  "ele/Cat3_cTagEx/Mass90/higgsCombine_hcs_13TeV_ele_Cat3_cTagEx.AsymptoticLimits.mH90.root",
  "ele/Cat3_cTagEx/Mass100/higgsCombine_hcs_13TeV_ele_Cat3_cTagEx.AsymptoticLimits.mH100.root",
  "ele/Cat3_cTagEx/Mass120/higgsCombine_hcs_13TeV_ele_Cat3_cTagEx.AsymptoticLimits.mH120.root",
  "ele/Cat3_cTagEx/Mass140/higgsCombine_hcs_13TeV_ele_Cat3_cTagEx.AsymptoticLimits.mH140.root",
  "ele/Cat3_cTagEx/Mass150/higgsCombine_hcs_13TeV_ele_Cat3_cTagEx.AsymptoticLimits.mH150.root",
  "ele/Cat3_cTagEx/Mass155/higgsCombine_hcs_13TeV_ele_Cat3_cTagEx.AsymptoticLimits.mH155.root",
  "ele/Cat3_cTagEx/Mass160/higgsCombine_hcs_13TeV_ele_Cat3_cTagEx.AsymptoticLimits.mH160.root"};

  TString massFiles_mu_ele_Cat3_cTagEx [8] = {
  "mu_ele/Cat3_cTagEx/Mass80/higgsCombine_hcs_13TeV_mu_ele_Cat3_cTagEx.AsymptoticLimits.mH80.root",
  "mu_ele/Cat3_cTagEx/Mass90/higgsCombine_hcs_13TeV_mu_ele_Cat3_cTagEx.AsymptoticLimits.mH90.root",
  "mu_ele/Cat3_cTagEx/Mass100/higgsCombine_hcs_13TeV_mu_ele_Cat3_cTagEx.AsymptoticLimits.mH100.root",
  "mu_ele/Cat3_cTagEx/Mass120/higgsCombine_hcs_13TeV_mu_ele_Cat3_cTagEx.AsymptoticLimits.mH120.root",
  "mu_ele/Cat3_cTagEx/Mass140/higgsCombine_hcs_13TeV_mu_ele_Cat3_cTagEx.AsymptoticLimits.mH140.root",
  "mu_ele/Cat3_cTagEx/Mass150/higgsCombine_hcs_13TeV_mu_ele_Cat3_cTagEx.AsymptoticLimits.mH150.root",
  "mu_ele/Cat3_cTagEx/Mass155/higgsCombine_hcs_13TeV_mu_ele_Cat3_cTagEx.AsymptoticLimits.mH155.root",
  "mu_ele/Cat3_cTagEx/Mass160/higgsCombine_hcs_13TeV_mu_ele_Cat3_cTagEx.AsymptoticLimits.mH160.root"};


string getLimitNumbers(TString massFiles){
    TFile f("limit/"+massFiles,"READ"); // higgsCombineChargedHiggs_mu.AsymptoticLimits.mH140.root
    if(f.IsZombie()){
      cout << "Cannot open file for " << massFiles << endl;
      ///continue;
    }
    float obsY     = 0.0;
    float expY     = 0.0;
    float expX1sL  = 0.0;
    float expX1sH  = 0.0;
    float expY1sL  = 0.0;
    float expY1sH  = 0.0;
    float expY1sL_  = 0.0;
    float expY1sH_  = 0.0;
   
    float expX2sL  = 0.0;
    float expX2sH  = 0.0;
    float expY2sL  = 0.0;
    float expY2sH  = 0.0;

    Double_t r;
    TTree* limit = (TTree*)f.Get("limit");
    limit->SetBranchAddress("limit",&r);
    for(int k = 0 ; k< limit->GetEntries() ; k++){
      limit->GetEntry(k);
      if(k==0) expY2sL = r;
      if(k==1) expY1sL = r;
      if(k==1) expY1sL_ = r;
      if(k==2) expY    = r;
      if(k==3) expY1sH = r;
      if(k==3) expY1sH_ = r;
      if(k==4) expY2sH = r;
      if(k==5) obsY    = r;
    }
    expY1sH = TMath::Abs(expY1sH-expY);
    expY1sL = TMath::Abs(expY1sL-expY);
    expY2sH = TMath::Abs(expY2sH-expY);
    expY2sL = TMath::Abs(expY2sL-expY);
    expY1sH_ = 100*TMath::Abs(expY1sH_-expY);
    expY1sL_ = 100*TMath::Abs(expY1sL_-expY);
    cout<<"$"<<100*expY<<"^{+"<<expY1sH_<<"}"<<"_"<<"{-"<< expY1sL_<<"}"<<endl;
    cout<<setw(75)<<massFiles<<setw(5)<<" $"<<std::setprecision(2)<<100*expY<<"^{+"<<expY1sH_<<"}"<<"_"<<"{-"<< expY1sL_<<"}"<<"$"<<endl;
    //convert float to string 
    ostringstream convert;
    string result("");
    //convert<<"$"<<std::setprecision(3)<<100*expY<<"^{+"<<expY1sH_<<"}"<<"_"<<"{-"<< expY1sL_<<"}"<<"$"<<"&"<<"-"<<endl;
    convert<<"$"<<std::setprecision(3)<<100*expY<<"^{+"<<expY1sH_<<"}"<<"_"<<"{-"<< expY1sL_<<"}"<<"$"<<"&"<<100*obsY<<endl;
    result = convert.str(); 
    return result;
}

void MyANMakeLimitTable(){  
  ofstream outFile; 
  outFile.open("limit/limitTable.tex"); 
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
   
  cout<<"=============================="<<endl;
  cout<<"        MUON CHANNEL        "<<endl;
  cout<<"=============================="<<endl;
  outFile<<"\\begin{table}"<<endl; 
  outFile<<"\\begin{center}"<<endl; 
  outFile<<"\\begin{tabular}{ ccccccc}"<<endl; 
  outFile<<"\\hline "<<endl;
  outFile<<"\\hline "<<endl;
  outFile<<"\\multicolumn{1}{c}{} & \\multicolumn{2}{c}{$m_{jj}(Inc)$} & \\multicolumn{2}{c}{$m_{jj}(Inc ~CTagL)$} & \\multicolumn{2}{c}{$m_{jj}(Ex ~CTag)$} \\\\"<<endl; 
  outFile<<"  "<<endl;
  outFile<<"{\\bf{$m_{H^+}$}}"<<" & "<< "Expected & Observed & Expected & Observed & Expected & Observed "<< " \\\\ "<<endl;
  outFile<<"  "<<endl;
  outFile<< " "<<" (GeV) & "<< "(\\%) & "<< "(\\%) & "<< "(\\%) & "<<"(\\%) & "<<"(\\%) & "<<"(\\%) "<<" \\\\ "<<endl;
  outFile<<" \\hline "<<endl;
  outFile<<"\\hline "<<endl;
  cout<<endl; cout<<"                                    Mass: 80 GeV        "<<endl;
  outFile<< "80  & "<<getLimitNumbers(massFiles_mu_Cat1_Inc[0])<<" & "<<getLimitNumbers(massFiles_mu_Cat2_cTagInc[0])<<" & "<<getLimitNumbers(massFiles_mu_Cat3_cTagEx[0])<< "\\\\"<<endl;
  outFile<<"  "<<endl;

  cout<<endl; cout<<"                                    Mass: 90 GeV        "<<endl;
  outFile<< "90  & "<<getLimitNumbers(massFiles_mu_Cat1_Inc[1])<<" & "<<getLimitNumbers(massFiles_mu_Cat2_cTagInc[1])<<" & "<<getLimitNumbers(massFiles_mu_Cat3_cTagEx[1])<< "\\\\"<<endl;
  outFile<<"  "<<endl;

  cout<<endl; cout<<"                                    Mass: 100 GeV        "<<endl;
  outFile<< "100  & "<<getLimitNumbers(massFiles_mu_Cat1_Inc[2])<<" & "<<getLimitNumbers(massFiles_mu_Cat2_cTagInc[2])<<" & "<<getLimitNumbers(massFiles_mu_Cat3_cTagEx[2])<< "\\\\"<<endl;
  outFile<<"  "<<endl;

  cout<<endl; cout<<"                                    Mass: 120 GeV        "<<endl;
  outFile<< "120  & "<<getLimitNumbers(massFiles_mu_Cat1_Inc[3])<<" & "<<getLimitNumbers(massFiles_mu_Cat2_cTagInc[3])<<" & "<<getLimitNumbers(massFiles_mu_Cat3_cTagEx[3])<< "\\\\"<<endl;
  outFile<<"  "<<endl;

  cout<<endl; cout<<"                                    Mass: 140 GeV        "<<endl;
  outFile<< "140  & "<<getLimitNumbers(massFiles_mu_Cat1_Inc[4])<<" & "<<getLimitNumbers(massFiles_mu_Cat2_cTagInc[4])<<" & "<<getLimitNumbers(massFiles_mu_Cat3_cTagEx[4])<< "\\\\"<<endl;
  outFile<<"  "<<endl;

  cout<<endl; cout<<"                                    Mass: 150 GeV        "<<endl;
  outFile<< "150  & "<<getLimitNumbers(massFiles_mu_Cat1_Inc[5])<<" & "<<getLimitNumbers(massFiles_mu_Cat2_cTagInc[5])<<" & "<<getLimitNumbers(massFiles_mu_Cat3_cTagEx[5])<< "\\\\"<<endl;
  outFile<<"  "<<endl;

  cout<<endl; cout<<"                                    Mass: 155 GeV        "<<endl;
  outFile<< "155  & "<<getLimitNumbers(massFiles_mu_Cat1_Inc[6])<<" & "<<getLimitNumbers(massFiles_mu_Cat2_cTagInc[6])<<" & "<<getLimitNumbers(massFiles_mu_Cat3_cTagEx[6])<< "\\\\"<<endl;
  outFile<<"  "<<endl;

  cout<<endl; cout<<"                                    Mass: 160 GeV        "<<endl;
  outFile<< "160  & "<<getLimitNumbers(massFiles_mu_Cat1_Inc[7])<<" & "<<getLimitNumbers(massFiles_mu_Cat2_cTagInc[7])<<" & "<<getLimitNumbers(massFiles_mu_Cat3_cTagEx[7])<< "\\\\"<<endl;
  outFile<<"  "<<endl;
  outFile<<"\\hline "<<endl;
  outFile<<"\\end{tabular}"<<endl; 
  outFile<<"\\caption{95\\% CL exclusion limit (in \\%) for muon + jets channel from different event categories. The limits from exclusive charm categories are the best one.}"<<endl; 
  outFile<<"\\label{tab:limitMu}"<<endl;
  outFile<<"\\end{center}"<<endl; 
  outFile<<"\\end{table}"<<endl; 
  outFile<<endl;

  cout<<"=============================="<<endl;
  cout<<"        ELECTRON CHANNEL        "<<endl;
  cout<<"=============================="<<endl;
  outFile<<"\\begin{table}"<<endl; 
  outFile<<"\\begin{center}"<<endl; 
  outFile<<"\\begin{tabular}{ ccccccc}"<<endl; 
  outFile<<"\\hline "<<endl;
  outFile<<"\\hline "<<endl;
  outFile<<"\\multicolumn{1}{c}{} & \\multicolumn{2}{c}{$m_{jj}(Inc)$} & \\multicolumn{2}{c}{$m_{jj}(Inc ~CTagL)$} & \\multicolumn{2}{c}{$m_{jj}(Ex ~CTag)$} \\\\"<<endl; 
  outFile<<"  "<<endl;
  outFile<<"{\\bf{$m_{H^+}$}}"<<" & "<< "Expected & Observed & Expected & Observed & Expected & Observed "<< " \\\\ "<<endl;
  outFile<<"  "<<endl;
  outFile<< " "<<" (GeV) & "<< "(\\%) & "<< "(\\%) & "<< "(\\%) & "<<"(\\%) & "<<"(\\%) & "<<"(\\%) "<<" \\\\ "<<endl;
  outFile<<" \\hline "<<endl;
  outFile<<"\\hline "<<endl;
  cout<<endl; cout<<"                                    Mass: 80 GeV        "<<endl;
  outFile<< "80  & "<<getLimitNumbers(massFiles_ele_Cat1_Inc[0])<<" & "<<getLimitNumbers(massFiles_ele_Cat2_cTagInc[0])<<" & "<<getLimitNumbers(massFiles_ele_Cat3_cTagEx[0])<< "\\\\"<<endl;
  outFile<<"  "<<endl;

  cout<<endl; cout<<"                                    Mass: 90 GeV        "<<endl;
  outFile<< "90  & "<<getLimitNumbers(massFiles_ele_Cat1_Inc[1])<<" & "<<getLimitNumbers(massFiles_ele_Cat2_cTagInc[1])<<" & "<<getLimitNumbers(massFiles_ele_Cat3_cTagEx[1])<< "\\\\"<<endl;
  outFile<<"  "<<endl;

  cout<<endl; cout<<"                                    Mass: 100 GeV        "<<endl;
  outFile<< "100  & "<<getLimitNumbers(massFiles_ele_Cat1_Inc[2])<<" & "<<getLimitNumbers(massFiles_ele_Cat2_cTagInc[2])<<" & "<<getLimitNumbers(massFiles_ele_Cat3_cTagEx[2])<< "\\\\"<<endl;
  outFile<<"  "<<endl;

  cout<<endl; cout<<"                                    Mass: 120 GeV        "<<endl;
  outFile<< "120  & "<<getLimitNumbers(massFiles_ele_Cat1_Inc[3])<<" & "<<getLimitNumbers(massFiles_ele_Cat2_cTagInc[3])<<" & "<<getLimitNumbers(massFiles_ele_Cat3_cTagEx[3])<< "\\\\"<<endl;
  outFile<<"  "<<endl;

  cout<<endl; cout<<"                                    Mass: 140 GeV        "<<endl;
  outFile<< "140  & "<<getLimitNumbers(massFiles_ele_Cat1_Inc[4])<<" & "<<getLimitNumbers(massFiles_ele_Cat2_cTagInc[4])<<" & "<<getLimitNumbers(massFiles_ele_Cat3_cTagEx[4])<< "\\\\"<<endl;
  outFile<<"  "<<endl;

  cout<<endl; cout<<"                                    Mass: 150 GeV        "<<endl;
  outFile<< "150  & "<<getLimitNumbers(massFiles_ele_Cat1_Inc[5])<<" & "<<getLimitNumbers(massFiles_ele_Cat2_cTagInc[5])<<" & "<<getLimitNumbers(massFiles_ele_Cat3_cTagEx[5])<< "\\\\"<<endl;
  outFile<<"  "<<endl;

  cout<<endl; cout<<"                                    Mass: 155 GeV        "<<endl;
  outFile<< "155  & "<<getLimitNumbers(massFiles_ele_Cat1_Inc[6])<<" & "<<getLimitNumbers(massFiles_ele_Cat2_cTagInc[6])<<" & "<<getLimitNumbers(massFiles_ele_Cat3_cTagEx[6])<< "\\\\"<<endl;
  outFile<<"  "<<endl;

  cout<<endl; cout<<"                                    Mass: 160 GeV        "<<endl;
  outFile<< "160  & "<<getLimitNumbers(massFiles_ele_Cat1_Inc[7])<<" & "<<getLimitNumbers(massFiles_ele_Cat2_cTagInc[7])<<" & "<<getLimitNumbers(massFiles_ele_Cat3_cTagEx[7])<< "\\\\"<<endl;
  outFile<<"  "<<endl;
  outFile<<"\\hline "<<endl;
  outFile<<"\\end{tabular}"<<endl; 
  outFile<<"\\caption{95\\% CL exclusion limit (in \\%) for electron + jets channel from different event categories. The limits from exclusive charm categories are the best one.}"<<endl; 
  outFile<<"\\label{tab:limitEle}"<<endl;
  outFile<<"\\end{center}"<<endl; 
  outFile<<"\\end{table}"<<endl; 
  outFile<<endl;

  cout<<"=============================="<<endl;
  cout<<"        LEPTON CHANNEL        "<<endl;
  cout<<"=============================="<<endl;
  outFile<<"\\begin{table}"<<endl; 
  outFile<<"\\begin{center}"<<endl; 
  outFile<<"\\begin{tabular}{ ccccccc}"<<endl; 
  outFile<<"\\hline "<<endl;
  outFile<<"\\hline "<<endl;
  outFile<<"\\multicolumn{1}{c}{} & \\multicolumn{2}{c}{$m_{jj}(Inc)$} & \\multicolumn{2}{c}{$m_{jj}(Inc ~CTagL)$} & \\multicolumn{2}{c}{$m_{jj}(Ex ~CTag)$} \\\\"<<endl; 
  outFile<<"  "<<endl;
  outFile<<"{\\bf{$m_{H^+}$}}"<<" & "<< "Expected & Observed & Expected & Observed & Expected & Observed "<< " \\\\ "<<endl;
  outFile<<"  "<<endl;
  outFile<< " "<<" (GeV) & "<< "(\\%) & "<< "(\\%) & "<< "(\\%) & "<<"(\\%) & "<<"(\\%) & "<<"(\\%) "<<" \\\\ "<<endl;
  outFile<<" \\hline "<<endl;
  outFile<<"\\hline "<<endl;
  cout<<endl; cout<<"                                    Mass: 80 GeV        "<<endl;
  outFile<< "80  & "<<getLimitNumbers(massFiles_mu_ele_Cat1_Inc[0])<<" & "<<getLimitNumbers(massFiles_mu_ele_Cat2_cTagInc[0])<<" & "<<getLimitNumbers(massFiles_mu_ele_Cat3_cTagEx[0])<< "\\\\"<<endl;
  outFile<<"  "<<endl;

  cout<<endl; cout<<"                                    Mass: 90 GeV        "<<endl;
  outFile<< "90  & "<<getLimitNumbers(massFiles_mu_ele_Cat1_Inc[1])<<" & "<<getLimitNumbers(massFiles_mu_ele_Cat2_cTagInc[1])<<" & "<<getLimitNumbers(massFiles_mu_ele_Cat3_cTagEx[1])<< "\\\\"<<endl;
  outFile<<"  "<<endl;

  cout<<endl; cout<<"                                    Mass: 100 GeV        "<<endl;
  outFile<< "100  & "<<getLimitNumbers(massFiles_mu_ele_Cat1_Inc[2])<<" & "<<getLimitNumbers(massFiles_mu_ele_Cat2_cTagInc[2])<<" & "<<getLimitNumbers(massFiles_mu_ele_Cat3_cTagEx[2])<< "\\\\"<<endl;
  outFile<<"  "<<endl;

  cout<<endl; cout<<"                                    Mass: 120 GeV        "<<endl;
  outFile<< "120  & "<<getLimitNumbers(massFiles_mu_ele_Cat1_Inc[3])<<" & "<<getLimitNumbers(massFiles_mu_ele_Cat2_cTagInc[3])<<" & "<<getLimitNumbers(massFiles_mu_ele_Cat3_cTagEx[3])<< "\\\\"<<endl;
  outFile<<"  "<<endl;

  cout<<endl; cout<<"                                    Mass: 140 GeV        "<<endl;
  outFile<< "140  & "<<getLimitNumbers(massFiles_mu_ele_Cat1_Inc[4])<<" & "<<getLimitNumbers(massFiles_mu_ele_Cat2_cTagInc[4])<<" & "<<getLimitNumbers(massFiles_mu_ele_Cat3_cTagEx[4])<< "\\\\"<<endl;
  outFile<<"  "<<endl;

  cout<<endl; cout<<"                                    Mass: 150 GeV        "<<endl;
  outFile<< "150  & "<<getLimitNumbers(massFiles_mu_ele_Cat1_Inc[5])<<" & "<<getLimitNumbers(massFiles_mu_ele_Cat2_cTagInc[5])<<" & "<<getLimitNumbers(massFiles_mu_ele_Cat3_cTagEx[5])<< "\\\\"<<endl;
  outFile<<"  "<<endl;

  cout<<endl; cout<<"                                    Mass: 155 GeV        "<<endl;
  outFile<< "155  & "<<getLimitNumbers(massFiles_mu_ele_Cat1_Inc[6])<<" & "<<getLimitNumbers(massFiles_mu_ele_Cat2_cTagInc[6])<<" & "<<getLimitNumbers(massFiles_mu_ele_Cat3_cTagEx[6])<< "\\\\"<<endl;
  outFile<<"  "<<endl;

  cout<<endl; cout<<"                                    Mass: 160 GeV        "<<endl;
  outFile<< "160  & "<<getLimitNumbers(massFiles_mu_ele_Cat1_Inc[7])<<" & "<<getLimitNumbers(massFiles_mu_ele_Cat2_cTagInc[7])<<" & "<<getLimitNumbers(massFiles_mu_ele_Cat3_cTagEx[7])<< "\\\\"<<endl;
  outFile<<"  "<<endl;
  outFile<<"\\hline "<<endl;
  outFile<<"\\end{tabular}"<<endl; 
  outFile<<"\\caption{95\\% CL exclusion limit (in \\%) for lepton + jets channel from different event categories. The limits from exclusive charm categories are the best one.}"<<endl; 
  outFile<<"\\label{tab:limitLep}"<<endl;
  outFile<<"\\end{center}"<<endl; 
  outFile<<"\\end{table}"<<endl; 
  outFile<<"\\end{document}"<<endl;  
  outFile.close(); 
} 
