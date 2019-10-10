#include<TROOT.h>
#include <string>
#include <iomanip>


void missBCTagging(){

  TFile *f_TTJets = new TFile("all_TTJetsP.root");
  TFile *f_WH120 = new TFile("all_Hplus120.root");
  TFile *f_ST = new TFile("all_ST.root");
  TFile *f_WJets = new TFile("all_WJets.root");
  TFile *f_DY = new TFile("all_DY.root");
  TFile *f_VV = new TFile("all_VV.root");
  TFile *f_QCD = new TFile("all_QCD.root");
  
  //Isolation region 
  TString histPath = "base/Iso/BTag/cutflow_nonbJetID";
  TH1F *h_TTJets = (TH1F*)f_TTJets->Get(histPath);
  TH1F *h_WH120 = (TH1F*)f_WH120->Get(histPath);
  TH1F *h_ST = (TH1F*)f_ST->Get(histPath);
  TH1F *h_WJets = (TH1F*)f_WJets->Get(histPath);
  TH1F *h_DY = (TH1F*)f_DY->Get(histPath);
  TH1F *h_VV = (TH1F*)f_VV->Get(histPath);
  TH1F *h_QCD = (TH1F*)f_QCD->Get(histPath);

  double tot_TTJets=	h_TTJets->Integral();
  double tot_WH120=	h_WH120->Integral();
  double tot_ST=		h_ST->Integral()    ;
  double tot_WJets=		h_WJets->Integral() ;
  double tot_DY=		h_DY->Integral()    ;
  double tot_VV=		h_VV->Integral()    ;
  double tot_QCD=		h_QCD->Integral()    ;

  cout<<tot_TTJets <<endl;	   
  cout<<tot_WH120 <<endl;	   
  cout<<tot_ST 	 <<endl;	   
  cout<<tot_WJets  <<endl;	   
  cout<<tot_DY 	 <<endl;	   
  cout<<tot_VV 	 <<endl;	   
  cout<<tot_QCD 	 <<endl;	   

  int binN = h_DY->GetSize();
  double totEntr = 0;
  for(int i=1; i<binN; i++){
    if(h_DY->GetBinContent(i)!=0){
      cout<<endl;
      cout<<"------------ bin number= "<<i<<"-----------"<<endl;
      double n_TTJets=		h_TTJets->GetBinContent(i);
      double n_WH120=		h_WH120->GetBinContent(i);
      double n_ST=		h_ST->GetBinContent(i)    ;
      double n_WJets=		h_WJets->GetBinContent(i) ;
      double n_DY=		h_DY->GetBinContent(i)    ;
      double n_VV=		h_VV->GetBinContent(i)    ;
      double n_QCD=		h_QCD->GetBinContent(i)    ;

      std::cout << std::setprecision(3);
      cout<<n_TTJets 	<<" ("<<n_TTJets*100/tot_TTJets<<"%)" <<endl;	   
      cout<<n_WH120 	<<" ("<<n_WH120*100/tot_WH120<<"%)" <<endl;	   
      cout<<n_ST 	<<" ("<<n_ST*100/tot_ST<<"%)"	 <<endl;	   
      cout<<n_WJets	 <<" ("<<n_WJets*100/tot_WJets<<"%)"<<endl;	   
      cout<<n_DY 	<<" ("<<n_DY*100/tot_DY<<"%)"	 <<endl;	   
      cout<<n_VV 	<<" ("<<n_VV*100/tot_VV<<"%)"	 <<endl;	   
      cout<<n_QCD 	<<" ("<<n_QCD*100/tot_QCD<<"%)"  <<endl;	   
      cout<<endl; 
    }
  }
}
