#include <iostream>
#include <fstream>
#include <iomanip>

  //-------------------------------------------------//
  //         Inclusive Mjj   
  //-------------------------------------------------//
  TString massFiles_mu_mjj_kfit [7] = {
  "higgsCombineChargedHiggs_mu_mjj_kfit.Asymptotic.mH90.root",
  "higgsCombineChargedHiggs_mu_mjj_kfit.Asymptotic.mH100.root",
  "higgsCombineChargedHiggs_mu_mjj_kfit.Asymptotic.mH120.root",
  "higgsCombineChargedHiggs_mu_mjj_kfit.Asymptotic.mH140.root",
  "higgsCombineChargedHiggs_mu_mjj_kfit.Asymptotic.mH150.root",
  "higgsCombineChargedHiggs_mu_mjj_kfit.Asymptotic.mH155.root",
  "higgsCombineChargedHiggs_mu_mjj_kfit.Asymptotic.mH160.root"};

  TString massFiles_ele_mjj_kfit [7] = {
  "higgsCombineChargedHiggs_ele_mjj_kfit.Asymptotic.mH90.root",
  "higgsCombineChargedHiggs_ele_mjj_kfit.Asymptotic.mH100.root",
  "higgsCombineChargedHiggs_ele_mjj_kfit.Asymptotic.mH120.root",
  "higgsCombineChargedHiggs_ele_mjj_kfit.Asymptotic.mH140.root",
  "higgsCombineChargedHiggs_ele_mjj_kfit.Asymptotic.mH150.root",
  "higgsCombineChargedHiggs_ele_mjj_kfit.Asymptotic.mH155.root",
  "higgsCombineChargedHiggs_ele_mjj_kfit.Asymptotic.mH160.root"};

  TString massFiles_mu_ele_mjj_kfit [7] = {
  "higgsCombineChargedHiggs_mu_ele_mjj_kfit.Asymptotic.mH90.root",
  "higgsCombineChargedHiggs_mu_ele_mjj_kfit.Asymptotic.mH100.root",
  "higgsCombineChargedHiggs_mu_ele_mjj_kfit.Asymptotic.mH120.root",
  "higgsCombineChargedHiggs_mu_ele_mjj_kfit.Asymptotic.mH140.root",
  "higgsCombineChargedHiggs_mu_ele_mjj_kfit.Asymptotic.mH150.root",
  "higgsCombineChargedHiggs_mu_ele_mjj_kfit.Asymptotic.mH155.root",
  "higgsCombineChargedHiggs_mu_ele_mjj_kfit.Asymptotic.mH160.root"};

  //-------------------------------------------------//
  //         Inclusive CTag L Mjj   
  //-------------------------------------------------//
  TString massFiles_mu_mjj_kfit_CTagL_SF [7] = {
  "higgsCombineChargedHiggs_mu_mjj_kfit_CTagL_SF.Asymptotic.mH90.root",
  "higgsCombineChargedHiggs_mu_mjj_kfit_CTagL_SF.Asymptotic.mH100.root",
  "higgsCombineChargedHiggs_mu_mjj_kfit_CTagL_SF.Asymptotic.mH120.root",
  "higgsCombineChargedHiggs_mu_mjj_kfit_CTagL_SF.Asymptotic.mH140.root",
  "higgsCombineChargedHiggs_mu_mjj_kfit_CTagL_SF.Asymptotic.mH150.root",
  "higgsCombineChargedHiggs_mu_mjj_kfit_CTagL_SF.Asymptotic.mH155.root",
  "higgsCombineChargedHiggs_mu_mjj_kfit_CTagL_SF.Asymptotic.mH160.root"};

  TString massFiles_ele_mjj_kfit_CTagL_SF [7] = {
  "higgsCombineChargedHiggs_ele_mjj_kfit_CTagL_SF.Asymptotic.mH90.root",
  "higgsCombineChargedHiggs_ele_mjj_kfit_CTagL_SF.Asymptotic.mH100.root",
  "higgsCombineChargedHiggs_ele_mjj_kfit_CTagL_SF.Asymptotic.mH120.root",
  "higgsCombineChargedHiggs_ele_mjj_kfit_CTagL_SF.Asymptotic.mH140.root",
  "higgsCombineChargedHiggs_ele_mjj_kfit_CTagL_SF.Asymptotic.mH150.root",
  "higgsCombineChargedHiggs_ele_mjj_kfit_CTagL_SF.Asymptotic.mH155.root",
  "higgsCombineChargedHiggs_ele_mjj_kfit_CTagL_SF.Asymptotic.mH160.root"};

  TString massFiles_mu_ele_mjj_kfit_CTagL_SF [7] = {
  "higgsCombineChargedHiggs_mu_ele_mjj_kfit_CTagL_SF.Asymptotic.mH90.root",
  "higgsCombineChargedHiggs_mu_ele_mjj_kfit_CTagL_SF.Asymptotic.mH100.root",
  "higgsCombineChargedHiggs_mu_ele_mjj_kfit_CTagL_SF.Asymptotic.mH120.root",
  "higgsCombineChargedHiggs_mu_ele_mjj_kfit_CTagL_SF.Asymptotic.mH140.root",
  "higgsCombineChargedHiggs_mu_ele_mjj_kfit_CTagL_SF.Asymptotic.mH150.root",
  "higgsCombineChargedHiggs_mu_ele_mjj_kfit_CTagL_SF.Asymptotic.mH155.root",
  "higgsCombineChargedHiggs_mu_ele_mjj_kfit_CTagL_SF.Asymptotic.mH160.root"};

  //-------------------------------------------------//
  //         Mjj from bjet pT bins   
  //-------------------------------------------------//
  TString massFiles_mu_mjj_bJetPtCat [7] = {
  "higgsCombineChargedHiggs_mu_mjj_bJetPtCat.Asymptotic.mH90.root",
  "higgsCombineChargedHiggs_mu_mjj_bJetPtCat.Asymptotic.mH100.root",
  "higgsCombineChargedHiggs_mu_mjj_bJetPtCat.Asymptotic.mH120.root",
  "higgsCombineChargedHiggs_mu_mjj_bJetPtCat.Asymptotic.mH140.root",
  "higgsCombineChargedHiggs_mu_mjj_bJetPtCat.Asymptotic.mH150.root",
  "higgsCombineChargedHiggs_mu_mjj_bJetPtCat.Asymptotic.mH155.root",
  "higgsCombineChargedHiggs_mu_mjj_bJetPtCat.Asymptotic.mH160.root"};

  TString massFiles_ele_mjj_bJetPtCat [7] = {
  "higgsCombineChargedHiggs_ele_mjj_bJetPtCat.Asymptotic.mH90.root",
  "higgsCombineChargedHiggs_ele_mjj_bJetPtCat.Asymptotic.mH100.root",
  "higgsCombineChargedHiggs_ele_mjj_bJetPtCat.Asymptotic.mH120.root",
  "higgsCombineChargedHiggs_ele_mjj_bJetPtCat.Asymptotic.mH140.root",
  "higgsCombineChargedHiggs_ele_mjj_bJetPtCat.Asymptotic.mH150.root",
  "higgsCombineChargedHiggs_ele_mjj_bJetPtCat.Asymptotic.mH155.root",
  "higgsCombineChargedHiggs_ele_mjj_bJetPtCat.Asymptotic.mH160.root"};

  TString massFiles_mu_ele_mjj_bJetPtCat [7] = {
  "higgsCombineChargedHiggs_mu_ele_mjj_bJetPtCat.Asymptotic.mH90.root",
  "higgsCombineChargedHiggs_mu_ele_mjj_bJetPtCat.Asymptotic.mH100.root",
  "higgsCombineChargedHiggs_mu_ele_mjj_bJetPtCat.Asymptotic.mH120.root",
  "higgsCombineChargedHiggs_mu_ele_mjj_bJetPtCat.Asymptotic.mH140.root",
  "higgsCombineChargedHiggs_mu_ele_mjj_bJetPtCat.Asymptotic.mH150.root",
  "higgsCombineChargedHiggs_mu_ele_mjj_bJetPtCat.Asymptotic.mH155.root",
  "higgsCombineChargedHiggs_mu_ele_mjj_bJetPtCat.Asymptotic.mH160.root"};

  //-------------------------------------------------//
  //         Mjj from cTag categories   
  //-------------------------------------------------//
  TString massFiles_mu_mjj_CTagCat [7] = {
  "higgsCombineChargedHiggs_mu_mjj_CTagCat.Asymptotic.mH90.root",
  "higgsCombineChargedHiggs_mu_mjj_CTagCat.Asymptotic.mH100.root",
  "higgsCombineChargedHiggs_mu_mjj_CTagCat.Asymptotic.mH120.root",
  "higgsCombineChargedHiggs_mu_mjj_CTagCat.Asymptotic.mH140.root",
  "higgsCombineChargedHiggs_mu_mjj_CTagCat.Asymptotic.mH150.root",
  "higgsCombineChargedHiggs_mu_mjj_CTagCat.Asymptotic.mH155.root",
  "higgsCombineChargedHiggs_mu_mjj_CTagCat.Asymptotic.mH160.root"};

  TString massFiles_ele_mjj_CTagCat [7] = {
  "higgsCombineChargedHiggs_ele_mjj_CTagCat.Asymptotic.mH90.root",
  "higgsCombineChargedHiggs_ele_mjj_CTagCat.Asymptotic.mH100.root",
  "higgsCombineChargedHiggs_ele_mjj_CTagCat.Asymptotic.mH120.root",
  "higgsCombineChargedHiggs_ele_mjj_CTagCat.Asymptotic.mH140.root",
  "higgsCombineChargedHiggs_ele_mjj_CTagCat.Asymptotic.mH150.root",
  "higgsCombineChargedHiggs_ele_mjj_CTagCat.Asymptotic.mH155.root",
  "higgsCombineChargedHiggs_ele_mjj_CTagCat.Asymptotic.mH160.root"};

  TString massFiles_mu_ele_mjj_CTagCat [7] = {
  "higgsCombineChargedHiggs_mu_ele_mjj_CTagCat.Asymptotic.mH90.root",
  "higgsCombineChargedHiggs_mu_ele_mjj_CTagCat.Asymptotic.mH100.root",
  "higgsCombineChargedHiggs_mu_ele_mjj_CTagCat.Asymptotic.mH120.root",
  "higgsCombineChargedHiggs_mu_ele_mjj_CTagCat.Asymptotic.mH140.root",
  "higgsCombineChargedHiggs_mu_ele_mjj_CTagCat.Asymptotic.mH150.root",
  "higgsCombineChargedHiggs_mu_ele_mjj_CTagCat.Asymptotic.mH155.root",
  "higgsCombineChargedHiggs_mu_ele_mjj_CTagCat.Asymptotic.mH160.root"};

  //-------------------------------------------------//
  //         Mjj from cTag categories in bjet pT bins   
  //-------------------------------------------------//
  TString massFiles_mu_mjj_CTagCat_bJetPtCat [7] = {
  "higgsCombineChargedHiggs_mu_mjj_CTagCat_bJetPtCat.Asymptotic.mH90.root",
  "higgsCombineChargedHiggs_mu_mjj_CTagCat_bJetPtCat.Asymptotic.mH100.root",
  "higgsCombineChargedHiggs_mu_mjj_CTagCat_bJetPtCat.Asymptotic.mH120.root",
  "higgsCombineChargedHiggs_mu_mjj_CTagCat_bJetPtCat.Asymptotic.mH140.root",
  "higgsCombineChargedHiggs_mu_mjj_CTagCat_bJetPtCat.Asymptotic.mH150.root",
  "higgsCombineChargedHiggs_mu_mjj_CTagCat_bJetPtCat.Asymptotic.mH155.root",
  "higgsCombineChargedHiggs_mu_mjj_CTagCat_bJetPtCat.Asymptotic.mH160.root"};

  TString massFiles_ele_mjj_CTagCat_bJetPtCat [7] = {
  "higgsCombineChargedHiggs_ele_mjj_CTagCat_bJetPtCat.Asymptotic.mH90.root",
  "higgsCombineChargedHiggs_ele_mjj_CTagCat_bJetPtCat.Asymptotic.mH100.root",
  "higgsCombineChargedHiggs_ele_mjj_CTagCat_bJetPtCat.Asymptotic.mH120.root",
  "higgsCombineChargedHiggs_ele_mjj_CTagCat_bJetPtCat.Asymptotic.mH140.root",
  "higgsCombineChargedHiggs_ele_mjj_CTagCat_bJetPtCat.Asymptotic.mH150.root",
  "higgsCombineChargedHiggs_ele_mjj_CTagCat_bJetPtCat.Asymptotic.mH155.root",
  "higgsCombineChargedHiggs_ele_mjj_CTagCat_bJetPtCat.Asymptotic.mH160.root"};

  TString massFiles_mu_ele_mjj_CTagCat_bJetPtCat [7] = {
  "higgsCombineChargedHiggs_mu_ele_mjj_CTagCat_bJetPtCat.Asymptotic.mH90.root",
  "higgsCombineChargedHiggs_mu_ele_mjj_CTagCat_bJetPtCat.Asymptotic.mH100.root",
  "higgsCombineChargedHiggs_mu_ele_mjj_CTagCat_bJetPtCat.Asymptotic.mH120.root",
  "higgsCombineChargedHiggs_mu_ele_mjj_CTagCat_bJetPtCat.Asymptotic.mH140.root",
  "higgsCombineChargedHiggs_mu_ele_mjj_CTagCat_bJetPtCat.Asymptotic.mH150.root",
  "higgsCombineChargedHiggs_mu_ele_mjj_CTagCat_bJetPtCat.Asymptotic.mH155.root",
  "higgsCombineChargedHiggs_mu_ele_mjj_CTagCat_bJetPtCat.Asymptotic.mH160.root"};

string getLimitNumbers(TString massFiles){
    TFile f("limit_root_file/"+massFiles,"READ"); // higgsCombineChargedHiggs_mu.Asymptotic.mH140.root
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
    cout<<setw(75)<<massFiles<<setw(5)<<" $"<<std::setprecision(2)<<100*expY<<"^{+"<<expY1sH_<<"}"<<"_"<<"{-"<< expY1sL_<<"}"<<"$"<<endl;
    //convert float to string 
    ostringstream convert;
    string result("");
    convert<<"$"<<std::setprecision(2)<<100*expY<<"^{+"<<expY1sH_<<"}"<<"_"<<"{-"<< expY1sL_<<"}"<<"$";
    result = convert.str(); 
    return result;
}

void makeLimitTable_13TeV(){  
  ofstream outFile; 
  outFile.open("limitTable.tex"); 
  //outFile<<"\\documentclass[landscape,letterpaper]{article}"<<endl;  
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
   
  cout<<"=============================="<<endl;
  cout<<"        MUON CHANNEL        "<<endl;
  cout<<"=============================="<<endl;
  outFile<<"\\begin{table}"<<endl; 
  outFile<<"\\begin{center}"<<endl; 
  outFile<<"\\begin{tabular}{ |c|c|c|c|c|c| }"<<endl; 
  outFile<<"\\hline "<<endl;
  outFile<< " "<<" & "<< "Ex. Limit using & "<< "Ex. Limit using & "<< "Ex. Limit using  & "<< "Ex. Limit using & "<<"Ex. Limit using"<<" \\\\ "<<endl;
  outFile<<"\\multicolumn{1}{|c}{{\\bf{$M_{H^\\pm}$}}} & \\multicolumn{1}{|c}{$M_{jj}(Inc)$} & \\multicolumn{1}{|c}{$M_{jj}(pt_{bjet}^{Had} ~bins)$} & \\multicolumn{1}{|c}{$M_{jj}(Inc ~CTagL)$} & \\multicolumn{1}{|c}{$M_{jj}(Ex ~CTag)$} &  \\multicolumn{1}{|c|}{$M_{jj}(Ex ~CTag (pt_{bjet}^{Had} ~bins))$} \\\\"<<endl; 
  outFile<< " "<<" (GeV) & "<< "(\\%) & "<< "(\\%) & "<< "(\\%)  & "<< "(\\%) & "<<"(\\%)"<<" \\\\ "<<endl;
  outFile<<"[0.1cm] \\hline "<<endl;
  cout<<endl; cout<<"                                    Mass: 90 GeV        "<<endl;
  outFile<< "90  & "<<getLimitNumbers(massFiles_mu_mjj_kfit[0])<<" & "<<getLimitNumbers(massFiles_mu_mjj_bJetPtCat[0])<<" & "<<getLimitNumbers(massFiles_mu_mjj_kfit_CTagL_SF[0])<<" & "<<getLimitNumbers(massFiles_mu_mjj_CTagCat[0])<<" & "<<getLimitNumbers(massFiles_mu_mjj_CTagCat_bJetPtCat[0])<< "\\\\"<<endl;
  outFile<<"[0.1cm]  "<<endl;

  cout<<endl; cout<<"                                    Mass: 100 GeV        "<<endl;
  outFile<< "100  & "<<getLimitNumbers(massFiles_mu_mjj_kfit[1])<<" & "<<getLimitNumbers(massFiles_mu_mjj_bJetPtCat[1])<<" & "<<getLimitNumbers(massFiles_mu_mjj_kfit_CTagL_SF[1])<<" & "<<getLimitNumbers(massFiles_mu_mjj_CTagCat[1])<<" & "<<getLimitNumbers(massFiles_mu_mjj_CTagCat_bJetPtCat[1])<< "\\\\"<<endl;
  outFile<<"[0.1cm]  "<<endl;

  cout<<endl; cout<<"                                    Mass: 120 GeV        "<<endl;
  outFile<< "120  & "<<getLimitNumbers(massFiles_mu_mjj_kfit[2])<<" & "<<getLimitNumbers(massFiles_mu_mjj_bJetPtCat[2])<<" & "<<getLimitNumbers(massFiles_mu_mjj_kfit_CTagL_SF[2])<<" & "<<getLimitNumbers(massFiles_mu_mjj_CTagCat[2])<<" & "<<getLimitNumbers(massFiles_mu_mjj_CTagCat_bJetPtCat[2])<< "\\\\"<<endl;
  outFile<<"[0.1cm]  "<<endl;

  cout<<endl; cout<<"                                    Mass: 140 GeV        "<<endl;
  outFile<< "140  & "<<getLimitNumbers(massFiles_mu_mjj_kfit[3])<<" & "<<getLimitNumbers(massFiles_mu_mjj_bJetPtCat[3])<<" & "<<getLimitNumbers(massFiles_mu_mjj_kfit_CTagL_SF[3])<<" & "<<getLimitNumbers(massFiles_mu_mjj_CTagCat[3])<<" & "<<getLimitNumbers(massFiles_mu_mjj_CTagCat_bJetPtCat[3])<< "\\\\"<<endl;
  outFile<<"[0.1cm]  "<<endl;

  cout<<endl; cout<<"                                    Mass: 150 GeV        "<<endl;
  outFile<< "150  & "<<getLimitNumbers(massFiles_mu_mjj_kfit[4])<<" & "<<getLimitNumbers(massFiles_mu_mjj_bJetPtCat[4])<<" & "<<getLimitNumbers(massFiles_mu_mjj_kfit_CTagL_SF[4])<<" & "<<getLimitNumbers(massFiles_mu_mjj_CTagCat[4])<<" & "<<getLimitNumbers(massFiles_mu_mjj_CTagCat_bJetPtCat[4])<< "\\\\"<<endl;
  outFile<<"[0.1cm]  "<<endl;

  cout<<endl; cout<<"                                    Mass: 155 GeV        "<<endl;
  outFile<< "155  & "<<getLimitNumbers(massFiles_mu_mjj_kfit[5])<<" & "<<getLimitNumbers(massFiles_mu_mjj_bJetPtCat[5])<<" & "<<getLimitNumbers(massFiles_mu_mjj_kfit_CTagL_SF[5])<<" & "<<getLimitNumbers(massFiles_mu_mjj_CTagCat[5])<<" & "<<getLimitNumbers(massFiles_mu_mjj_CTagCat_bJetPtCat[5])<< "\\\\"<<endl;
  outFile<<"[0.1cm]  "<<endl;

  cout<<endl; cout<<"                                    Mass: 160 GeV        "<<endl;
  outFile<< "160  & "<<getLimitNumbers(massFiles_mu_mjj_kfit[6])<<" & "<<getLimitNumbers(massFiles_mu_mjj_bJetPtCat[6])<<" & "<<getLimitNumbers(massFiles_mu_mjj_kfit_CTagL_SF[6])<<" & "<<getLimitNumbers(massFiles_mu_mjj_CTagCat[6])<<" & "<<getLimitNumbers(massFiles_mu_mjj_CTagCat_bJetPtCat[6])<< "\\\\"<<endl;
  outFile<<"[0.1cm]  "<<endl;
  outFile<<"\\hline "<<endl;
  outFile<<"\\end{tabular}"<<endl; 
  outFile<<"\\caption{muon + jets channel}"<<endl; 
  outFile<<"\\end{center}"<<endl; 
  outFile<<"\\end{table}"<<endl; 

  cout<<"=============================="<<endl;
  cout<<"        ELECTRON CHANNEL        "<<endl;
  cout<<"=============================="<<endl;
  outFile<<"\\begin{table}"<<endl; 
  outFile<<"\\begin{center}"<<endl; 
  outFile<<"\\begin{tabular}{ |c|c|c|c|c|c| }"<<endl; 
  outFile<<"\\hline "<<endl;
  outFile<< " "<<" & "<< "Ex. Limit using & "<< "Ex. Limit using & "<< "Ex. Limit using  & "<< "Ex. Limit using & "<<"Ex. Limit using"<<" \\\\ "<<endl;
  outFile<<"\\multicolumn{1}{|c}{{\\bf{$M_{H^\\pm}$}}} & \\multicolumn{1}{|c}{$M_{jj}(Inc)$} & \\multicolumn{1}{|c}{$M_{jj}(pt_{bjet}^{Had} ~bins)$} & \\multicolumn{1}{|c}{$M_{jj}(Inc ~CTagL)$} & \\multicolumn{1}{|c}{$M_{jj}(Ex ~CTag)$} &  \\multicolumn{1}{|c|}{$M_{jj}(Ex ~CTag (pt_{bjet}^{Had} ~bins))$} \\\\"<<endl; 
  outFile<< " "<<" (GeV) & "<< "(\\%) & "<< "(\\%) & "<< "(\\%)  & "<< "(\\%) & "<<"(\\%)"<<" \\\\ "<<endl;
  outFile<<"[0.1cm] \\hline "<<endl;
  cout<<endl; cout<<"                                    Mass: 90 GeV        "<<endl;
  outFile<< "90  & "<<getLimitNumbers(massFiles_ele_mjj_kfit[0])<<" & "<<getLimitNumbers(massFiles_ele_mjj_bJetPtCat[0])<<" & "<<getLimitNumbers(massFiles_ele_mjj_kfit_CTagL_SF[0])<<" & "<<getLimitNumbers(massFiles_ele_mjj_CTagCat[0])<<" & "<<getLimitNumbers(massFiles_ele_mjj_CTagCat_bJetPtCat[0])<< "\\\\"<<endl;
  outFile<<"[0.1cm]  "<<endl;

  cout<<endl; cout<<"                                    Mass: 100 GeV        "<<endl;
  outFile<< "100  & "<<getLimitNumbers(massFiles_ele_mjj_kfit[1])<<" & "<<getLimitNumbers(massFiles_ele_mjj_bJetPtCat[1])<<" & "<<getLimitNumbers(massFiles_ele_mjj_kfit_CTagL_SF[1])<<" & "<<getLimitNumbers(massFiles_ele_mjj_CTagCat[1])<<" & "<<getLimitNumbers(massFiles_ele_mjj_CTagCat_bJetPtCat[1])<< "\\\\"<<endl;
  outFile<<"[0.1cm]  "<<endl;

  cout<<endl; cout<<"                                    Mass: 120 GeV        "<<endl;
  outFile<< "120  & "<<getLimitNumbers(massFiles_ele_mjj_kfit[2])<<" & "<<getLimitNumbers(massFiles_ele_mjj_bJetPtCat[2])<<" & "<<getLimitNumbers(massFiles_ele_mjj_kfit_CTagL_SF[2])<<" & "<<getLimitNumbers(massFiles_ele_mjj_CTagCat[2])<<" & "<<getLimitNumbers(massFiles_ele_mjj_CTagCat_bJetPtCat[2])<< "\\\\"<<endl;
  outFile<<"[0.1cm]  "<<endl;

  cout<<endl; cout<<"                                    Mass: 140 GeV        "<<endl;
  outFile<< "140  & "<<getLimitNumbers(massFiles_ele_mjj_kfit[3])<<" & "<<getLimitNumbers(massFiles_ele_mjj_bJetPtCat[3])<<" & "<<getLimitNumbers(massFiles_ele_mjj_kfit_CTagL_SF[3])<<" & "<<getLimitNumbers(massFiles_ele_mjj_CTagCat[3])<<" & "<<getLimitNumbers(massFiles_ele_mjj_CTagCat_bJetPtCat[3])<< "\\\\"<<endl;
  outFile<<"[0.1cm]  "<<endl;

  cout<<endl; cout<<"                                    Mass: 150 GeV        "<<endl;
  outFile<< "150  & "<<getLimitNumbers(massFiles_ele_mjj_kfit[4])<<" & "<<getLimitNumbers(massFiles_ele_mjj_bJetPtCat[4])<<" & "<<getLimitNumbers(massFiles_ele_mjj_kfit_CTagL_SF[4])<<" & "<<getLimitNumbers(massFiles_ele_mjj_CTagCat[4])<<" & "<<getLimitNumbers(massFiles_ele_mjj_CTagCat_bJetPtCat[4])<< "\\\\"<<endl;
  outFile<<"[0.1cm]  "<<endl;

  cout<<endl; cout<<"                                    Mass: 155 GeV        "<<endl;
  outFile<< "155  & "<<getLimitNumbers(massFiles_ele_mjj_kfit[5])<<" & "<<getLimitNumbers(massFiles_ele_mjj_bJetPtCat[5])<<" & "<<getLimitNumbers(massFiles_ele_mjj_kfit_CTagL_SF[5])<<" & "<<getLimitNumbers(massFiles_ele_mjj_CTagCat[5])<<" & "<<getLimitNumbers(massFiles_ele_mjj_CTagCat_bJetPtCat[5])<< "\\\\"<<endl;
  outFile<<"[0.1cm]  "<<endl;

  cout<<endl; cout<<"                                    Mass: 160 GeV        "<<endl;
  outFile<< "160  & "<<getLimitNumbers(massFiles_ele_mjj_kfit[6])<<" & "<<getLimitNumbers(massFiles_ele_mjj_bJetPtCat[6])<<" & "<<getLimitNumbers(massFiles_ele_mjj_kfit_CTagL_SF[6])<<" & "<<getLimitNumbers(massFiles_ele_mjj_CTagCat[6])<<" & "<<getLimitNumbers(massFiles_ele_mjj_CTagCat_bJetPtCat[6])<< "\\\\"<<endl;
  outFile<<"[0.1cm]  "<<endl;
  outFile<<"\\hline "<<endl;
  outFile<<"\\end{tabular}"<<endl; 
  outFile<<"\\caption{electron + jets channel}"<<endl; 
  outFile<<"\\end{center}"<<endl; 
  outFile<<"\\end{table}"<<endl; 
  cout<<"=============================="<<endl;
  cout<<"        LEPTON CHANNEL        "<<endl;
  cout<<"=============================="<<endl;
  outFile<<"\\begin{table}"<<endl; 
  outFile<<"\\begin{center}"<<endl; 
  outFile<<"\\begin{tabular}{ |c|c|c|c|c|c| }"<<endl; 
  outFile<<"\\hline "<<endl;
  outFile<< " "<<" & "<< "Ex. Limit using & "<< "Ex. Limit using & "<< "Ex. Limit using  & "<< "Ex. Limit using & "<<"Ex. Limit using"<<" \\\\ "<<endl;
  outFile<<"\\multicolumn{1}{|c}{{\\bf{$M_{H^\\pm}$}}} & \\multicolumn{1}{|c}{$M_{jj}(Inc)$} & \\multicolumn{1}{|c}{$M_{jj}(pt_{bjet}^{Had} ~bins)$} & \\multicolumn{1}{|c}{$M_{jj}(Inc ~CTagL)$} & \\multicolumn{1}{|c}{$M_{jj}(Ex ~CTag)$} &  \\multicolumn{1}{|c|}{$M_{jj}(Ex ~CTag (pt_{bjet}^{Had} ~bins))$} \\\\"<<endl; 
  outFile<< " "<<" (GeV) & "<< "(\\%) & "<< "(\\%) & "<< "(\\%)  & "<< "(\\%) & "<<"(\\%)"<<" \\\\ "<<endl;
  outFile<<"[0.1cm]\\hline "<<endl;
  cout<<endl; cout<<"                                    Mass: 90 GeV        "<<endl;
  outFile<< "90  & "<<getLimitNumbers(massFiles_mu_ele_mjj_kfit[0])<<" & "<<getLimitNumbers(massFiles_mu_ele_mjj_bJetPtCat[0])<<" & "<<getLimitNumbers(massFiles_mu_ele_mjj_kfit_CTagL_SF[0])<<" & "<<getLimitNumbers(massFiles_mu_ele_mjj_CTagCat[0])<<" & "<<getLimitNumbers(massFiles_mu_ele_mjj_CTagCat_bJetPtCat[0])<< "\\\\"<<endl;
  outFile<<"[0.1cm]  "<<endl;

  cout<<endl; cout<<"                                    Mass: 100 GeV        "<<endl;
  outFile<< "100  & "<<getLimitNumbers(massFiles_mu_ele_mjj_kfit[1])<<" & "<<getLimitNumbers(massFiles_mu_ele_mjj_bJetPtCat[1])<<" & "<<getLimitNumbers(massFiles_mu_ele_mjj_kfit_CTagL_SF[1])<<" & "<<getLimitNumbers(massFiles_mu_ele_mjj_CTagCat[1])<<" & "<<getLimitNumbers(massFiles_mu_ele_mjj_CTagCat_bJetPtCat[1])<< "\\\\"<<endl;
  outFile<<"[0.1cm]  "<<endl;

  cout<<endl; cout<<"                                    Mass: 120 GeV        "<<endl;
  outFile<< "120  & "<<getLimitNumbers(massFiles_mu_ele_mjj_kfit[2])<<" & "<<getLimitNumbers(massFiles_mu_ele_mjj_bJetPtCat[2])<<" & "<<getLimitNumbers(massFiles_mu_ele_mjj_kfit_CTagL_SF[2])<<" & "<<getLimitNumbers(massFiles_mu_ele_mjj_CTagCat[2])<<" & "<<getLimitNumbers(massFiles_mu_ele_mjj_CTagCat_bJetPtCat[2])<< "\\\\"<<endl;
  outFile<<"[0.1cm]  "<<endl;

  cout<<endl; cout<<"                                    Mass: 140 GeV        "<<endl;
  outFile<< "140  & "<<getLimitNumbers(massFiles_mu_ele_mjj_kfit[3])<<" & "<<getLimitNumbers(massFiles_mu_ele_mjj_bJetPtCat[3])<<" & "<<getLimitNumbers(massFiles_mu_ele_mjj_kfit_CTagL_SF[3])<<" & "<<getLimitNumbers(massFiles_mu_ele_mjj_CTagCat[3])<<" & "<<getLimitNumbers(massFiles_mu_ele_mjj_CTagCat_bJetPtCat[3])<< "\\\\"<<endl;
  outFile<<"[0.1cm]  "<<endl;

  cout<<endl; cout<<"                                    Mass: 150 GeV        "<<endl;
  outFile<< "150  & "<<getLimitNumbers(massFiles_mu_ele_mjj_kfit[4])<<" & "<<getLimitNumbers(massFiles_mu_ele_mjj_bJetPtCat[4])<<" & "<<getLimitNumbers(massFiles_mu_ele_mjj_kfit_CTagL_SF[4])<<" & "<<getLimitNumbers(massFiles_mu_ele_mjj_CTagCat[4])<<" & "<<getLimitNumbers(massFiles_mu_ele_mjj_CTagCat_bJetPtCat[4])<< "\\\\"<<endl;
  outFile<<"[0.1cm]  "<<endl;

  cout<<endl; cout<<"                                    Mass: 155 GeV        "<<endl;
  outFile<< "155  & "<<getLimitNumbers(massFiles_mu_ele_mjj_kfit[5])<<" & "<<getLimitNumbers(massFiles_mu_ele_mjj_bJetPtCat[5])<<" & "<<getLimitNumbers(massFiles_mu_ele_mjj_kfit_CTagL_SF[5])<<" & "<<getLimitNumbers(massFiles_mu_ele_mjj_CTagCat[5])<<" & "<<getLimitNumbers(massFiles_mu_ele_mjj_CTagCat_bJetPtCat[5])<< "\\\\"<<endl;
  outFile<<"[0.1cm]  "<<endl;

  cout<<endl; cout<<"                                    Mass: 160 GeV        "<<endl;
  outFile<< "160  & "<<getLimitNumbers(massFiles_mu_ele_mjj_kfit[6])<<" & "<<getLimitNumbers(massFiles_mu_ele_mjj_bJetPtCat[6])<<" & "<<getLimitNumbers(massFiles_mu_ele_mjj_kfit_CTagL_SF[6])<<" & "<<getLimitNumbers(massFiles_mu_ele_mjj_CTagCat[6])<<" & "<<getLimitNumbers(massFiles_mu_ele_mjj_CTagCat_bJetPtCat[6])<< "\\\\"<<endl;
  outFile<<"[0.1cm]  "<<endl;
  outFile<<"\\hline "<<endl;
  outFile<<"\\end{tabular}"<<endl; 
  outFile<<"\\caption{lepton + jets channel}"<<endl; 
  outFile<<"\\end{center}"<<endl; 
  outFile<<"\\end{table}"<<endl; 
  outFile<<"\\end{document}"<<endl;  
  outFile.close(); 
} 
