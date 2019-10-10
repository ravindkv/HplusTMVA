#include<iostream>

#include <TH1F.h>
#include <TRandom3.h>
#include <TAxis.h>
#include <TLegend.h>

using namespace std;

//function for calculating integral of histogram from xmin to xmax
double h_integral(TH1F *h,double xmin,double xmax){

TAxis *axis = h->GetXaxis();
  int bmin = axis->FindBin(xmin); //in your case xmin=-1.5
  int bmax = axis->FindBin(xmax); //in your case xmax=0.8
  double integral = h->Integral(bmin,bmax);
  integral -= (h->GetBinContent(bmin)*(xmin-axis->GetBinLowEdge(bmin)))/axis->GetBinWidth(bmin);
  integral -= (h->GetBinContent(bmax)*(axis->GetBinUpEdge(bmax)-xmax))/axis->GetBinWidth(bmax);

return integral;

}


//test statistic function defined as the negative log of likelihood ratios
double qmu(double mu,double s,double b, int n, int nobs){

double Ldata_qmu= ((pow( ((mu*s)+b),n ))*exp(-((mu*s)+b)));

double Ldata_qmuhat = ((pow(nobs,n))*exp(-(nobs)));

double TS_mu = -2*log(Ldata_qmu/Ldata_qmuhat);

return TS_mu;
}



void GenericTS(){

TRandom3 r;

//Data Card details
///////////////////

// double mu[7]={1.95,1.35,1.05,1.20,1.31,1.3438,1.3436};
double mu[7]={1.950001,1.350001,1.050001,1.200001,1.319842,1.343819,1.348615};
// double mu[8]={0.750001,0.79,0.792,0.794,0.796,0.798,0.799,0.80};



int nobs=45;//number of observed events

double s=20.; //signal rate
double b=30.; //bkg rate


int nsb=0;//random variable for toy generation assuming signal+bkg 
int nb=0; //random variable for toy generation assuming bkg 
// int Ntoy=s+b;//s+b rate

///////////////////
//cout<<"Make global fit of asimov data"<<endl;


// TF1 *f1 = new TF1("f1","( Exp((-1)*x)*Power(x,n))/Factorial(n)",0,10); // n ==> Int, x ===> Double
// double r = f1->GetRandom();




for(int mui=0;mui<7;mui++){//looping over different signal strength
// for(int mui=0;mui<8;mui++){//looping over different signal strength

// MY LINE
int Ntoy = (int)( (mu[mui]*(double)(s)) + (double)b );//s+b rate

// std::cout<< "mu[mui] "<< mu[mui] << " (int)( (mu[mui]*(double)(s)) + (double)b ) " << ((int)( (mu[mui]*(double)(s)) + (double)b )) << " ( (mu[mui]*(double)(s)) + (double)b ) " << ( (mu[mui]*(double)(s)) + (double)b ) << std::endl;

//test statistic histogram distribution from toy s+b only data
TH1F *t1 =new TH1F("t1","t1",200,-100,100);
t1->SetLineColor(2);
t1->SetLineWidth(2);

//test statistic histogram distribution from toy b only data
TH1F *t2 =new TH1F("t2","t2",200,-100,100);
t2->SetLineColor(4);
t2->SetLineWidth(2);




for(int i=0;i<1000000;i++){
nsb=r.Poisson(Ntoy);
nb=r.Poisson(b);
// t1->Fill(qmu(1,s,b,nsb,nobs)); 
// t2->Fill(qmu(1,s,b,nb,nobs));  

// Poisson(Double_t x, Double_t par)
t1->Fill(qmu(mu[mui],s,b,nsb,nobs)); // WE GENERATE PESUDO DATASET FOR (mu*S)+B (WITH THE VALUE OF mu TO BE TESTED) ALWAYS FOR BOTH S+B and B ONLY HYPOTHESIS
t2->Fill(qmu(mu[mui],s,b,nb,nobs));      // WE GENERATE PESUDO DATASET FOR (mu*S)+B (WITH THE VALUE OF mu TO BE TESTED) ALWAYS FOR BOTH S+B and B ONLY HYPOTHESIS

// MY LINES
// nsb=r.Poisson(nobs);
// nb=r.Poisson(nobs);
// t1->Fill(qmu(1,s,b,nsb,nobs));
// t2->Fill(qmu(0.,0.,b,nb,nobs));

} // LOOP OVER TOYS ENDS


char Legname1[100];
TLegend *leg_1D[5];
for(int k0=0;k0<5;k0++){
sprintf(Legname1,"leg_1D%i",k0);
leg_1D[k0]=new TLegend(0.2,0.6,0.30,0.8);
leg_1D[k0]->SetTextFont(62);
leg_1D[k0]->SetLineColor(1);
leg_1D[k0]->SetLineStyle(1);
leg_1D[k0]->SetLineWidth(3);
leg_1D[k0]->SetFillColor(0);
leg_1D[k0]->SetFillStyle(1001);
leg_1D[k0]->SetShadowColor(0);
leg_1D[k0]->SetDrawOption(0);
leg_1D[k0]->SetBorderSize(0);
leg_1D[k0]->SetTextSize(0.03);
}

leg_1D[0]->AddEntry(t1,"f(q_{#mu=1}|#mu = 1) , using signal+bkg toy","l");
leg_1D[0]->AddEntry(t2,"f(q_{#mu=1}|#mu = 0) , using bkg toy","l");


t1->Scale(1/t1->Integral());
t2->Scale(1/t2->Integral());
//t1->GetYaxis()->SetRangeUser(0,1.5*max(t1->GetMaximum(),t2->GetMaximum()));

t1->Draw();
t2->Draw("SAME");

leg_1D[0]->Draw();

double qmu_obs=qmu(mu[mui],s,b,nobs,nobs);//observed value of test statistic
double qA=qmu(0.,s,b,Ntoy,nobs);          // value of test statistic computed from Asimov dataset


double p_mu=h_integral(t1,qmu_obs,40);// CLsb
double One_minus_pb=h_integral(t2,qmu_obs,40); //CLb


double CLs =p_mu/One_minus_pb;


cout<<"At r = "<<mu[mui]<<"   :   "<<"q_mu = "<<qmu_obs<<"       q_A = "<< qA <<"      CLsb = "<<p_mu<<"     CLb = "<<One_minus_pb<<"          CLs :  "<<CLs<<endl;
if(mui !=6){
// if(mui !=7){
delete t1;
delete t2;
}
}//looping over different signal strength


}
