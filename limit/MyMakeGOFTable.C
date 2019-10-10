#include <iostream>
#include <fstream>
#include <iomanip>

string doubleToStr(double val){
     ostringstream convert;
     string result("");
     convert <<std::setprecision(4)<<val;
     result = convert.str();
  return result;
}

string getValue(TString CHANNEL="mu", TString CAT= "Cat1_Inc", TString MASS="90"){
  TString inFileDir = "limit/"+CHANNEL+"/"+CAT+"/Mass"+MASS;
  //----------------------------------
  // GOF files from toys
  //----------------------------------
  TString inFileToy = "higgsCombine_hcs_13TeV_toy_"+CHANNEL+"_"+CAT+".GoodnessOfFit.mH"+MASS+".root";
  TFile fileToy(inFileDir+"/"+inFileToy, "READ");
  if(fileToy.IsZombie()){
    cout << "Cannot open GOF toys file "+inFileDir+"/"+inFileToy << endl;
    //continue;
  }
  //Tree
  TTree* treeToy = (TTree*)fileToy.Get("limit");
  //cout << "treeToy=  " << treeToy->GetEntries() << endl;
  //Hist
  TH1F *histToy = new TH1F("histToy", "histToy", 100, 0., 200.);
  treeToy->Draw("limit>>histToy");

  //----------------------------------
  // GOF files from data
  //----------------------------------
  TString inFileData = "higgsCombine_hcs_13TeV_data_"+CHANNEL+"_"+CAT+".GoodnessOfFit.mH"+MASS+".root";
  TFile fileData(inFileDir+"/"+inFileData, "READ");
  if(fileToy.IsZombie()){
    cout << "Cannot open GOF toys file "+inFileDir+"/"+inFileData << endl;
    //continue;
  }

  //Tree
  TTree* treeData = (TTree*)fileData.Get("limit");
  TH1F *histData = new TH1F("histData", "histData", 100, 0., 200.);
  treeData->Draw("limit>>histData");
  //histData->Draw("same");

  string meanToy = doubleToStr(histToy->GetMean())+" $\\pm$ "+doubleToStr(histToy->GetStdDev());
  string legData = doubleToStr(histData->GetMean());
  cout<<inFileDir<<": \t"<<meanToy+" & "+legData<<endl;
  return meanToy+" & "+legData;
  //return meanToy+" & -";
}

void MyMakeGOFTable(){  
  ofstream outFile; 
  outFile.open("limit/gofTable.tex"); 
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
  outFile<<"\\footnotesize{"<<endl; 
  outFile<<"\\begin{tabular}{ ccccccc}"<<endl; 
  outFile<<"\\hline "<<endl;
  outFile<<"\\hline "<<endl;
  outFile<<"\\multicolumn{1}{c}{{\\bf{$m_{H^\\pm}$}}} & \\multicolumn{2}{c}{$m_{jj}(Inc)$} & \\multicolumn{2}{c}{$m_{jj}(Inc ~CTagL)$} & \\multicolumn{2}{c}{$m_{jj}(Ex ~CTag)$} \\\\"<<endl; 
  outFile<<"  "<<endl;
  outFile<<"(GeV)"<<" & "<< "from toys & from data & from toys & from data & from toys & from data "<< " \\\\ "<<endl;
  outFile<<" \\hline "<<endl;
  outFile<<"\\hline "<<endl;
  cout<<endl; cout<<"                                    Mass: 80 GeV        "<<endl;
  outFile<< "80  & "<<getValue("mu","Cat1_Inc","80")<<" & "<<getValue("mu","Cat2_cTagInc","80")<<" & "<<getValue("mu","Cat3_cTagEx","80")<< "\\\\"<<endl;
  outFile<<"  "<<endl;

  cout<<endl; cout<<"                                 Mass: 90 GeV        "<<endl;
  outFile<< "90  & "<<getValue("mu","Cat1_Inc","90")<<" & "<<getValue("mu","Cat2_cTagInc","90")<<" & "<<getValue("mu","Cat3_cTagEx","90")<< "\\\\"<<endl;
  outFile<<"  "<<endl;

  cout<<endl; cout<<"                                    Mass: 100 GeV        "<<endl;
  outFile<< "100  & "<<getValue("mu","Cat1_Inc","100")<<" & "<<getValue("mu","Cat2_cTagInc","100")<<" & "<<getValue("mu","Cat3_cTagEx","100")<< "\\\\"<<endl;
  outFile<<"  "<<endl;

  cout<<endl; cout<<"                                 Mass: 120 GeV        "<<endl;
  outFile<< "120  & "<<getValue("mu","Cat1_Inc","120")<<" & "<<getValue("mu","Cat2_cTagInc","120")<<" & "<<getValue("mu","Cat3_cTagEx","120")<< "\\\\"<<endl;
  outFile<<"  "<<endl;

  cout<<endl; cout<<"                                 Mass: 140 GeV        "<<endl;
  outFile<< "140  & "<<getValue("mu","Cat1_Inc","140")<<" & "<<getValue("mu","Cat2_cTagInc","140")<<" & "<<getValue("mu","Cat3_cTagEx","140")<< "\\\\"<<endl;
  outFile<<"  "<<endl;

  cout<<endl; cout<<"                                 Mass: 150 GeV        "<<endl;
  outFile<< "150  & "<<getValue("mu","Cat1_Inc","150")<<" & "<<getValue("mu","Cat2_cTagInc","150")<<" & "<<getValue("mu","Cat3_cTagEx","150")<< "\\\\"<<endl;
  outFile<<"  "<<endl;

  cout<<endl; cout<<"                                 Mass: 155 GeV        "<<endl;
  outFile<< "155  & "<<getValue("mu","Cat1_Inc","155")<<" & "<<getValue("mu","Cat2_cTagInc","155")<<" & "<<getValue("mu","Cat3_cTagEx","155")<< "\\\\"<<endl;
  outFile<<"  "<<endl;

  cout<<endl; cout<<"                                 Mass: 160 GeV        "<<endl;
  outFile<< "160  & "<<getValue("mu","Cat1_Inc","160")<<" & "<<getValue("mu","Cat2_cTagInc","160")<<" & "<<getValue("mu","Cat3_cTagEx","160")<< "\\\\"<<endl;
  outFile<<"  "<<endl;
  outFile<<"\\hline "<<endl;
  outFile<<"\\end{tabular}"<<endl; 
  outFile<<"}"<<endl; 
  outFile<<"\\caption{Goodness of fit for muon + jets channel, from different event categories.}"<<endl; 
  outFile<<"\\label{tab:gofMu}"<<endl;
  outFile<<"\\end{center}"<<endl; 
  outFile<<"\\end{table}"<<endl; 
  outFile<<endl;

  cout<<"=============================="<<endl;
  cout<<"        ELECTRON CHANNEL        "<<endl;
  cout<<"=============================="<<endl;
  outFile<<"\\begin{table}"<<endl; 
  outFile<<"\\begin{center}"<<endl; 
  outFile<<"\\footnotesize{"<<endl; 
  outFile<<"\\begin{tabular}{ ccccccc}"<<endl; 
  outFile<<"\\hline "<<endl;
  outFile<<"\\hline "<<endl;
  outFile<<"\\multicolumn{1}{c}{{\\bf{$m_{H^\\pm}$}}} & \\multicolumn{2}{c}{$m_{jj}(Inc)$} & \\multicolumn{2}{c}{$m_{jj}(Inc ~CTagL)$} & \\multicolumn{2}{c}{$m_{jj}(Ex ~CTag)$} \\\\"<<endl; 
  outFile<<"  "<<endl;
  outFile<<"(GeV)"<<" & "<< "from toys & from data & from toys & from data & from toys & from data "<< " \\\\ "<<endl;
  outFile<<" \\hline "<<endl;
  outFile<<"\\hline "<<endl;
  cout<<endl; cout<<"                                    Mass: 80 GeV        "<<endl;
  outFile<< "80  & "<<getValue("ele","Cat1_Inc","80")<<" & "<<getValue("ele","Cat2_cTagInc","80")<<" & "<<getValue("ele","Cat3_cTagEx","80")<< "\\\\"<<endl;
  outFile<<"  "<<endl;

  cout<<endl; cout<<"                                 Mass: 90 GeV        "<<endl;
  outFile<< "90  & "<<getValue("ele","Cat1_Inc","90")<<" & "<<getValue("ele","Cat2_cTagInc","90")<<" & "<<getValue("ele","Cat3_cTagEx","90")<< "\\\\"<<endl;
  outFile<<"  "<<endl;

  cout<<endl; cout<<"                                    Mass: 100 GeV        "<<endl;
  outFile<< "100  & "<<getValue("ele","Cat1_Inc","100")<<" & "<<getValue("ele","Cat2_cTagInc","100")<<" & "<<getValue("ele","Cat3_cTagEx","100")<< "\\\\"<<endl;
  outFile<<"  "<<endl;

  cout<<endl; cout<<"                                 Mass: 120 GeV        "<<endl;
  outFile<< "120  & "<<getValue("ele","Cat1_Inc","120")<<" & "<<getValue("ele","Cat2_cTagInc","120")<<" & "<<getValue("ele","Cat3_cTagEx","120")<< "\\\\"<<endl;
  outFile<<"  "<<endl;

  cout<<endl; cout<<"                                 Mass: 140 GeV        "<<endl;
  outFile<< "140  & "<<getValue("ele","Cat1_Inc","140")<<" & "<<getValue("ele","Cat2_cTagInc","140")<<" & "<<getValue("ele","Cat3_cTagEx","140")<< "\\\\"<<endl;
  outFile<<"  "<<endl;

  cout<<endl; cout<<"                                 Mass: 150 GeV        "<<endl;
  outFile<< "150  & "<<getValue("ele","Cat1_Inc","150")<<" & "<<getValue("ele","Cat2_cTagInc","150")<<" & "<<getValue("ele","Cat3_cTagEx","150")<< "\\\\"<<endl;
  outFile<<"  "<<endl;

  cout<<endl; cout<<"                                 Mass: 155 GeV        "<<endl;
  outFile<< "155  & "<<getValue("ele","Cat1_Inc","155")<<" & "<<getValue("ele","Cat2_cTagInc","155")<<" & "<<getValue("ele","Cat3_cTagEx","155")<< "\\\\"<<endl;
  outFile<<"  "<<endl;

  cout<<endl; cout<<"                                 Mass: 160 GeV        "<<endl;
  outFile<< "160  & "<<getValue("ele","Cat1_Inc","160")<<" & "<<getValue("ele","Cat2_cTagInc","160")<<" & "<<getValue("ele","Cat3_cTagEx","160")<< "\\\\"<<endl;
  outFile<<"  "<<endl;
  outFile<<"\\hline "<<endl;
  outFile<<"\\end{tabular}"<<endl; 
  outFile<<"}"<<endl; 
  outFile<<"\\caption{Goodness of fit for electron + jets channel, from different event categories.}"<<endl; 
  outFile<<"\\label{tab:gofEle}"<<endl;
  outFile<<"\\end{center}"<<endl; 
  outFile<<"\\end{table}"<<endl; 
  outFile<<endl;

  cout<<"=============================="<<endl;
  cout<<"        LEPTON CHANNEL        "<<endl;
  cout<<"=============================="<<endl;
  outFile<<"\\begin{table}"<<endl; 
  outFile<<"\\begin{center}"<<endl; 
  outFile<<"\\footnotesize{"<<endl; 
  outFile<<"\\begin{tabular}{ ccccccc}"<<endl; 
  outFile<<"\\hline "<<endl;
  outFile<<"\\hline "<<endl;
  outFile<<"\\multicolumn{1}{c}{{\\bf{$m_{H^\\pm}$}}} & \\multicolumn{2}{c}{$m_{jj}(Inc)$} & \\multicolumn{2}{c}{$m_{jj}(Inc ~CTagL)$} & \\multicolumn{2}{c}{$m_{jj}(Ex ~CTag)$} \\\\"<<endl; 
  outFile<<"  "<<endl;
  outFile<<"(GeV)"<<" & "<< "from toys & from data & from toys & from data & from toys & from data "<< " \\\\ "<<endl;
  outFile<<" \\hline "<<endl;
  outFile<<"\\hline "<<endl;
  cout<<endl; cout<<"                                    Mass: 80 GeV        "<<endl;
  outFile<< "80  & "<<getValue("mu_ele","Cat1_Inc","80")<<" & "<<getValue("mu_ele","Cat2_cTagInc","80")<<" & "<<getValue("mu_ele","Cat3_cTagEx","80")<< "\\\\"<<endl;
  outFile<<"  "<<endl;

  cout<<endl; cout<<"                                 Mass: 90 GeV        "<<endl;
  outFile<< "90  & "<<getValue("mu_ele","Cat1_Inc","90")<<" & "<<getValue("mu_ele","Cat2_cTagInc","90")<<" & "<<getValue("mu_ele","Cat3_cTagEx","90")<< "\\\\"<<endl;
  outFile<<"  "<<endl;

  cout<<endl; cout<<"                                    Mass: 100 GeV        "<<endl;
  outFile<< "100  & "<<getValue("mu_ele","Cat1_Inc","100")<<" & "<<getValue("mu_ele","Cat2_cTagInc","100")<<" & "<<getValue("mu_ele","Cat3_cTagEx","100")<< "\\\\"<<endl;
  outFile<<"  "<<endl;

  cout<<endl; cout<<"                                 Mass: 120 GeV        "<<endl;
  outFile<< "120  & "<<getValue("mu_ele","Cat1_Inc","120")<<" & "<<getValue("mu_ele","Cat2_cTagInc","120")<<" & "<<getValue("mu_ele","Cat3_cTagEx","120")<< "\\\\"<<endl;
  outFile<<"  "<<endl;

  cout<<endl; cout<<"                                 Mass: 140 GeV        "<<endl;
  outFile<< "140  & "<<getValue("mu_ele","Cat1_Inc","140")<<" & "<<getValue("mu_ele","Cat2_cTagInc","140")<<" & "<<getValue("mu_ele","Cat3_cTagEx","140")<< "\\\\"<<endl;
  outFile<<"  "<<endl;

  cout<<endl; cout<<"                                 Mass: 150 GeV        "<<endl;
  outFile<< "150  & "<<getValue("mu_ele","Cat1_Inc","150")<<" & "<<getValue("mu_ele","Cat2_cTagInc","150")<<" & "<<getValue("mu_ele","Cat3_cTagEx","150")<< "\\\\"<<endl;
  outFile<<"  "<<endl;

  cout<<endl; cout<<"                                 Mass: 155 GeV        "<<endl;
  outFile<< "155  & "<<getValue("mu_ele","Cat1_Inc","155")<<" & "<<getValue("mu_ele","Cat2_cTagInc","155")<<" & "<<getValue("mu_ele","Cat3_cTagEx","155")<< "\\\\"<<endl;
  outFile<<"  "<<endl;

  cout<<endl; cout<<"                                 Mass: 160 GeV        "<<endl;
  outFile<< "160  & "<<getValue("mu_ele","Cat1_Inc","160")<<" & "<<getValue("mu_ele","Cat2_cTagInc","160")<<" & "<<getValue("mu_ele","Cat3_cTagEx","160")<< "\\\\"<<endl;
  outFile<<"  "<<endl;
  outFile<<"\\hline "<<endl;
  outFile<<"\\end{tabular}"<<endl; 
  outFile<<"}"<<endl; 
  outFile<<"\\caption{Goodness of fit for lepton + jets channel, from different event categories.}"<<endl; 
  outFile<<"\\label{tab:gofLep}"<<endl;
  outFile<<"\\end{center}"<<endl; 
  outFile<<"\\end{table}"<<endl; 
  outFile<<"\\end{document}"<<endl;  
  outFile.close(); 
} 
