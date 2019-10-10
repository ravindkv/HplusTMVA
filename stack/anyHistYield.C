#include<TROOT.h>
#include <string>
#include <iomanip>


void anyHistYield(){

  TFile *fQCD = new TFile("stack_20170717_JECafter4Jet_central/all_QCD.root");
  TFile *fDY = new TFile("stack_20170717_JECafter4Jet_central/all_DY.root");
  TFile *fST = new TFile("stack_20170717_JECafter4Jet_central/all_ST.root");
  TFile *fTTJets = new TFile("stack_20170717_JECafter4Jet_central/all_TTJets.root");
  TFile *fVV = new TFile("stack_20170717_JECafter4Jet_central/all_VV.root");
  TFile *fWJets = new TFile("stack_20170717_JECafter4Jet_central/all_WJets.root");
  TFile *fmuData = new TFile("stack_20170717_JECafter4Jet_central/all_muData.root");
  
 
  vector<string> dist;
  dist.push_back("pt_mu");
  dist.push_back("eta_mu");
  dist.push_back("pt_jet");
  dist.push_back("nvtx");
  dist.push_back("rhoAll");
  dist.push_back("mjj");

  for(int i=0; i<dist.size(); i++){
  cout<<endl;
  cout<<"---: "<<dist[i]<<" :---"<<endl;
  std::string hist("base/Iso/BTag/");
  hist = hist + dist[i];
  TString histname(hist);
  TH1F *hQCD = (TH1F*)fQCD->Get(histname);
  TH1F *hDY = (TH1F*)fDY->Get(histname);
  TH1F *hST = (TH1F*)fST->Get(histname);
  TH1F *hTTJets = (TH1F*)fTTJets->Get(histname);
  TH1F *hVV = (TH1F*)fVV->Get(histname);
  TH1F *hWJets = (TH1F*)fWJets->Get(histname);
  TH1F *hmuData = (TH1F*)fmuData->Get(histname);
  //Get Entries
  /*
  double nQCD=	hQCD->GetEntries()    ;
  double nDY=		hDY->GetEntries()    ;
  double nST=		hST->GetEntries()    ;
  double nTTJets=	hTTJets->GetEntries();
  double nVV=		hVV->GetEntries()    ;
  double nWJets=	hWJets->GetEntries() ;
  double nMC = nQCD+nDY+nST+nTTJets+nVV+nWJets;
  double nData=	hmuData->GetEntries() ;
  */
  //Get Integral
  double nQCD=		hQCD->Integral()    ;
  double nDY=		hDY->Integral()    ;
  double nST=		hST->Integral()    ;
  double nTTJets=	hTTJets->Integral();
  double nVV=		hVV->Integral()    ;
  double nWJets=	hWJets->Integral() ;
  double nMC = nQCD+nDY+nST+nTTJets+nVV+nWJets;
  double nData=		hmuData->Integral() ;
  cout<<"QCD= " 	<<nQCD 		<<endl;	   
  cout<<"DY= "      	<<nDY 		<<endl;	   
  cout<<"ST= " 		<<nST 		<<endl;	   
  cout<<"TTJets= "  	<<nTTJets 	<<endl;	   
  cout<<"VV= " 		<<nVV 		<<endl;	   
  cout<<"WJets= " 	<<nWJets 	<<endl;	   
  cout<<"nMC= " 	<<nMC 		<<endl;	   
  cout<<"nData= " 	<<nData 	<<endl;	   
  cout<<"Data/MC= " 	<<nData/nMC 	<<endl;	   
  cout<<endl;
  cout<<nQCD 		<<endl;	   
  cout<<nDY 		<<endl;	   
  cout<<nST 		<<endl;	   
  cout<<nTTJets 	<<endl;	   
  cout<<nVV 		<<endl;	   
  cout<<nWJets 		<<endl;	   
  cout<<nMC 		<<endl;	   
  cout<<nData 		<<endl;	   
  cout<<nData/nMC 	<<endl;	   
  }
}

