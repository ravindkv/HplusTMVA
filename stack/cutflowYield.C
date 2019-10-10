#include<TROOT.h>
#include <string>
#include <iomanip>


void cutflowYield(){

  //TFile *f_QCD = new TFile("histos_TT/all_TT_new_20171101.root");
  TFile *f_QCD = new TFile("histos_TT/all_TT_old_20170919.root");
  //TFile *f_QCD = new TFile("histos_TT/all_VV_new.root");
  //TFile *f_QCD = new TFile("histos_TT/all_QCD.root");
  TFile *f_DY = new TFile("histos_TT/all_DY.root");
  TFile *f_ST = new TFile("histos_TT/all_ST.root");
  //TFile *f_TTJets = new TFile("histos_TT/all_TTJetsM.root");
  TFile *f_TTJets = new TFile("histos_TT/all_TTJetsP.root");
  TFile *f_VV = new TFile("histos_TT/all_VV_old.root");
  TFile *f_WJets = new TFile("histos_TT/all_WJets.root");
  TFile *f_muData = new TFile("histos_TT/all_muData.root");
  
  //Isolation region 
  TH1F *h_QCD_Iso = (TH1F*)f_QCD->Get("base/Iso/cutflow");
  TH1F *h_DY_Iso = (TH1F*)f_DY->Get("base/Iso/cutflow");
  TH1F *h_ST_Iso = (TH1F*)f_ST->Get("base/Iso/cutflow");
  TH1F *h_TTJets_Iso = (TH1F*)f_TTJets->Get("base/Iso/cutflow");
  //h_QCD_Iso->Scale(1.014200382);//new
  h_QCD_Iso->Scale(1.045837553);//old
  TH1F *h_VV_Iso = (TH1F*)f_VV->Get("base/Iso/cutflow");
  TH1F *h_WJets_Iso = (TH1F*)f_WJets->Get("base/Iso/cutflow");
  TH1F *h_muData_Iso = (TH1F*)f_muData->Get("base/Iso/cutflow");
  
  //Non-Isolation region 
  TH1F *h_QCD_NonIso = (TH1F*)f_QCD->Get("base/NonIso/cutflow");
  TH1F *h_DY_NonIso = (TH1F*)f_DY->Get("base/NonIso/cutflow");
  TH1F *h_ST_NonIso = (TH1F*)f_ST->Get("base/NonIso/cutflow");
  TH1F *h_TTJets_NonIso = (TH1F*)f_TTJets->Get("base/NonIso/cutflow");
  TH1F *h_VV_NonIso = (TH1F*)f_VV->Get("base/NonIso/cutflow");
  TH1F *h_WJets_NonIso = (TH1F*)f_WJets->Get("base/NonIso/cutflow");
  TH1F *h_muData_NonIso = (TH1F*)f_muData->Get("base/NonIso/cutflow");
  //h->Draw();
 
  int binN = h_DY_Iso->GetSize();
  double totEntr = 0;
  for(int i=1; i<binN; i++){
    if(h_DY_Iso->GetBinContent(i)!=0){
      cout<<endl;
      /*
      cout<<"------------ bin number= "<<i<<"-----------"<<endl;
      cout<<"Isolation region: "<<endl;
      */
      double n_QCD_Iso=	h_QCD_Iso->GetBinContent(i)    ;
      double n_DY_Iso=		h_DY_Iso->GetBinContent(i)    ;
      double n_ST_Iso=		h_ST_Iso->GetBinContent(i)    ;
      double n_TTJets_Iso=	h_TTJets_Iso->GetBinContent(i);
      //double n_TTJets_Iso=	h_TTJets_Iso->GetBinContent(i);
      double n_VV_Iso=		h_VV_Iso->GetBinContent(i)    ;
      double n_WJets_Iso=	h_WJets_Iso->GetBinContent(i) ;
      double n_muData_Iso=	h_muData_Iso->GetBinContent(i) ;
      cout<<"QCD_Iso= " 	<<n_QCD_Iso 		<<endl;	   
      /*
      cout<<"DY_Iso= "      	<<n_DY_Iso 		<<endl;	   
      cout<<"ST_Iso= " 		<<n_ST_Iso 		<<endl;	   
      cout<<"TTJets_Iso= "  	<<n_TTJets_Iso 		<<endl;	   
      cout<<"VV_Iso= " 		<<n_VV_Iso 		<<endl;	   
      cout<<"WJets_Iso= " 	<<n_WJets_Iso 		<<endl;	   
      cout<<"muData_Iso= " 	<<n_muData_Iso 		<<endl;	   
      */
      double nBkg_Iso = n_DY_Iso+ n_ST_Iso+ n_TTJets_Iso+ n_VV_Iso+ n_WJets_Iso;
      double totBkg = nBkg_Iso + n_QCD_Iso;
      double nData_Iso= n_muData_Iso;
      totEntr = totEntr+ nBkg_Iso+nData_Iso+n_QCD_Iso ;
      //std::cout << std::setprecision(3);
      /*
      cout<<n_QCD_Iso 	<<" ("<<n_QCD_Iso*100/totBkg<<"%)" 	 <<endl;	   
      cout<<n_DY_Iso 	<<" ("<<n_DY_Iso*100/totBkg<<"%)"	 <<endl;	   
      cout<<n_ST_Iso 	<<" ("<<n_ST_Iso*100/totBkg<<"%)"	 <<endl;	   
      cout<<n_TTJets_Iso<<" ("<<n_TTJets_Iso*100/totBkg<<"%)"	 <<endl;	   
      cout<<n_VV_Iso 	<<" ("<<n_VV_Iso*100/totBkg<<"%)"	 <<endl;	   
      cout<<n_WJets_Iso <<" ("<<n_WJets_Iso*100/totBkg<<"%)"	 <<endl;	   
      cout<<totBkg 					 <<endl;
      cout<<n_muData_Iso 					 <<endl;
      cout<<n_muData_Iso/totBkg 				 <<endl;
      cout<<endl;
      cout<<n_QCD_Iso 	 <<endl;	   
      cout<<n_DY_Iso 	 <<endl;	   
      cout<<n_ST_Iso 	 <<endl;	   
      cout<<n_TTJets_Iso <<endl;	   
      cout<<n_VV_Iso 	 <<endl;	   
      cout<<n_WJets_Iso  <<endl;	   
      cout<<totBkg 					 <<endl;
      cout<<n_muData_Iso 					 <<endl;
      cout<<n_muData_Iso/totBkg 				 <<endl;

      cout<<endl; 
      cout<<"NonIsolation region: "<<endl;
      */
      double n_QCD_NonIso=	h_QCD_NonIso->GetBinContent(i)  	 ;
      double n_DY_NonIso=	h_DY_NonIso->GetBinContent(i)   	 ;
      double n_ST_NonIso=	h_ST_NonIso->GetBinContent(i)   	 ;
      double n_TTJets_NonIso=	h_TTJets_NonIso->GetBinContent(i);
      double n_VV_NonIso=	h_VV_NonIso->GetBinContent(i)    	;
      double n_WJets_NonIso=	h_WJets_NonIso->GetBinContent(i) ;
      double n_muData_NonIso=	h_muData_NonIso->GetBinContent(i) ;
      /*
      cout<<"QCD_NonIso= " 	<<n_QCD_NonIso 		<<endl;	   
      cout<<"DY_NonIso= "   	<<n_DY_NonIso 		<<endl;	   
      cout<<"ST_NonIso= " 	<<n_ST_NonIso 		<<endl;	   
      cout<<"TTJets_NonIso= " 	<<n_TTJets_NonIso 	<<endl;	   
      cout<<"VV_NonIso= " 	<<n_VV_NonIso 		<<endl;	   
      cout<<"WJets_NonIso= " 	<<n_WJets_NonIso 	<<endl;	   
      cout<<"muData_NonIso= " 	<<n_muData_NonIso 	<<endl;	   
      */
      double nBkg_NonIso = n_DY_NonIso+ n_ST_NonIso+ n_TTJets_NonIso+ n_VV_NonIso+ n_WJets_NonIso;
      double nData_NonIso= n_muData_NonIso;
      double totBkg_NonIso = nBkg_NonIso + n_QCD_NonIso;
      /*
      std::cout << std::setprecision(3);
      cout<<n_QCD_NonIso 	<<" ("<<n_QCD_NonIso*100/totBkg_NonIso<<"%)" 	 <<endl;	   
      cout<<n_DY_NonIso 	<<" ("<<n_DY_NonIso*100/totBkg_NonIso<<"%)"	 <<endl;	   
      cout<<n_ST_NonIso 	<<" ("<<n_ST_NonIso*100/totBkg_NonIso<<"%)"	 <<endl;	   
      cout<<n_TTJets_NonIso 	<<" ("<<n_TTJets_NonIso*100/totBkg_NonIso<<"%)"	 <<endl;	   
      cout<<n_VV_NonIso 	<<" ("<<n_VV_NonIso*100/totBkg_NonIso<<"%)"	 <<endl;	   
      cout<<n_WJets_NonIso 	<<" ("<<n_WJets_NonIso*100/totBkg_NonIso<<"%)"	 <<endl;	   
      cout<<totBkg_NonIso 					 <<endl;
      cout<<n_muData_NonIso 					 <<endl;
      cout<<n_muData_NonIso/totBkg_NonIso 				 <<endl;
      cout<<endl;
      cout<<n_QCD_NonIso 	 <<endl;	   
      cout<<n_DY_NonIso 	 <<endl;	   
      cout<<n_ST_NonIso 	 <<endl;	   
      cout<<n_TTJets_NonIso 	<<endl;	   
      cout<<n_VV_NonIso 	 <<endl;	   
      cout<<n_WJets_NonIso  	<<endl;	   
      cout<<totBkg_NonIso 					 <<endl;
      cout<<n_muData_NonIso 					 <<endl;
      */
      ///cout<<nData_NonIso/totBkg_NonIso 				 <<endl;
      double qcd_sf = (nData_Iso -nBkg_Iso)/( nData_NonIso -nBkg_NonIso);
      ///cout<<"----- QCD scale factor= "<< qcd_sf<<endl;
      }
  }
    cout<<"total entries = "<<totEntr<<endl;
}

