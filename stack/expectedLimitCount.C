#include<iostream>

#include <TH1F.h>
#include <TRandom3.h>
#include <TAxis.h>
#include <TLegend.h>

// ------------------------------------------------
// Original Author: Bibhu Prasad Mahakud
// https://github.com/bmahakud/LimitAndSignificance/blob/master/GenericTS.C
// ------------------------------------------------
using namespace std;

// ------------------------------------------------
// Function for calculating integral of histogram from xmin to xmax
// ------------------------------------------------
double h_integral(TH1F *h, const double &xmin, const double &xmax){
  TAxis *axis = h->GetXaxis();
  int bmin = axis->FindBin(xmin); 
  int bmax = axis->FindBin(xmax); 
  double integral = h->Integral(bmin,bmax);
  double lowEdge = (h->GetBinContent(bmin)*(xmin-axis->GetBinLowEdge(bmin)));
  double highEdge = (h->GetBinContent(bmax)*(axis->GetBinUpEdge(bmax)-xmax));
  integral -= lowEdge/axis->GetBinWidth(bmin);
  integral -= highEdge/axis->GetBinWidth(bmax);
  return integral;
}

// ------------------------------------------------
// Test statistic function defined as the negative log of likelihood ratios
// Page-5 of: https://drive.google.com/open?id=1MyTk-boANgx4aUg91ArZ9oQI_wFM2MgY
// ------------------------------------------------
double qmu(double &mu, double &s,double &b, int &n, int &nobs){
  double Ldata_qmu= ((pow( ((mu*s)+b),n ))*exp(-((mu*s)+b))); //Numerator
  double Ldata_qmuhat = ((pow(nobs,n))*exp(-(nobs)));
  double TS_mu = -2*log(Ldata_qmu/Ldata_qmuhat);
  return TS_mu;
}

// ------------------------------------------------
// Generate Asimov datasets
// ------------------------------------------------
TH1F* asimovData( double &mu, double &s, double &b, int &nobs, bool isBkgOnly){
  TRandom3 r;
  TH1F *hist =new TH1F("hist","hist",200,-100,100);
  int Ntoy = ( mu*s + b );//s+b rate
  int nsb = 0;
  int nb = 0;
  for(int i=0;i<1000000;i++){
    nsb=r.Poisson(Ntoy);
    nb=r.Poisson(b);
    if(isBkgOnly) hist->Fill(qmu(mu,s,b,nb,nobs));
    else hist->Fill(qmu(mu,s,b,nsb,nobs)); 
  } 
  return hist;
}   
    
// ------------------------------------------------
// Compute expected limit from counting experiment
// ------------------------------------------------
void expectedLimitCount(){
  int nobs=45;//number of observed events
  double s=20.; //signal rate
  double b=30.; //bkg rate
  std::vector<double> mu;
  mu.push_back(1.950001);
  mu.push_back(1.350001);
  mu.push_back(1.050001);
  mu.push_back(1.200001);
  mu.push_back(1.319842);
  mu.push_back(1.343819);
  mu.push_back(1.348615);
  delete gROOT->FindObject("hist"); 
  std::vector<double>::iterator itr;
  for(itr= mu.begin(); itr !=mu.end(); itr++){
    double r = *itr;
    TH1F* t1 = asimovData( r, s, b, nobs, false);  
    TH1F* t2 = asimovData( r, s, b, nobs, true);  
    t1->Scale(1/t1->Integral());
    t2->Scale(1/t2->Integral());

    int Ntoy = ( r*s + b );//s+b rate
    double qmu_obs=qmu(r,s,b,nobs,nobs);//observed value
    double forBkg =0.0;
    double qA=qmu(forBkg,s,b,Ntoy,nobs); //from Asimov dataset
    
    double thres = 40.0;
    double p_mu=h_integral(t1,qmu_obs, thres);// CLsb
    double One_minus_pb=h_integral(t2,qmu_obs, thres); //CLb

    double CLs =p_mu/One_minus_pb;
    cout<<"At r = "<<r<<setw(10)<<"q_mu = "<<qmu_obs<<setw(10)<<"q_A = "<< qA 
        <<setw(10)<<"CLsb = "<<p_mu<<setw(10)<<"CLb = "<<One_minus_pb
        <<setw(10)<<"CLs :  "<<CLs<<endl;
    delete t1;
    delete t2;
  }
}

