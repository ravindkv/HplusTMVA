#include<iostream>
#include <TH1F.h>
#include <TRandom3.h>
#include <TAxis.h>
#include <TLegend.h>

// ------------------------------------------------
// Reference
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
double h_integral2(TH1F *h, const double &xmin, const double &xmax){
  TAxis *axis = h->GetXaxis();
  int binx1 = axis->FindBin(xmin); 
  int binx2 = axis->FindBin(xmax); 
  double integral = h->Integral(binx1, binx2);
  return integral;
}


// ------------------------------------------------
// Test statistic function defined as the negative log of likelihood ratios
// Page-5 of: https://drive.google.com/open?id=1MyTk-boANgx4aUg91ArZ9oQI_wFM2MgY
// ------------------------------------------------
double qmu(double &mu, double &s,double &b, int &n, int &nobs){
  double nsb = mu*s + b;
  double Ldata_qmu= pow(nsb, n)*exp(-nsb); //Numerator
  double Ldata_qmuhat = pow(nobs, n)*exp(-nobs);
  double TS_mu = -2*log(Ldata_qmu/Ldata_qmuhat);
  return TS_mu;
}

// ------------------------------------------------
// Generate Asimov datasets
// ------------------------------------------------
// Generate a Poisson distribution which mean will be equal to Ntoy, or nb
TH1F* asimovData( double &mu, double &s, double &b, int &nobs, bool isBkgOnly, TString histName){
  TRandom3 r;
  TH1F *hist =new TH1F(histName,histName,200,-100,100);
  //TH1F *hist =new TH1F();
  int Ntoy = ( mu*s + b );//s+b rate
  int nsb = 0;
  int nb = 0;
  for(int i=0;i<10000;i++){
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
void exclusionLimit(){
  //int nobs=189904;//number of observed events
  //double s=123810.; //signal rate
  //double b=182191.; //bkg rate
  int nobs=45;//number of observed events
  double s=20.0; //signal rate
  double b=30.0; //bkg rate
  std::vector<double> mu;
  mu.push_back(1.952342);
  mu.push_back(1.352342);
  mu.push_back(1.052342);
  mu.push_back(1.202342);
  mu.push_back(1.320190);
  mu.push_back(1.343869);
  mu.push_back(1.348625);
  mu.push_back(1.358625);

  delete gROOT->FindObject("hist"); 
  std::vector<double>::iterator itr;
  for(itr= mu.begin(); itr !=mu.end(); itr++){
    double r = *itr;
    TH1F* t1 = asimovData( r, s, b, nobs, false, "t1");  
    TH1F* t2 = asimovData( r, s, b, nobs, true, "t2");  
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
    printf("rverma, at %s = %f:\tq_mu = %.5f\tq_A  = %.5f\tCLsb = %7.5f\tCLb  = %7.5f\tCLs  = %7.5f\n", "r", r, qmu_obs, qA, p_mu, One_minus_pb, CLs);
    //t1->Draw();
    //t2->Draw();
    delete t1;
    delete t2;
  }
}

