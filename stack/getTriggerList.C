#include <fstream>
void getTriggerList()
{
  //TFile f1("TTJetsP_EleMC_20171215_Ntuple_162.root");
  TFile f1("EleRunHver3v1_EleData_20171215_Ntuple_1.root");
  TH1F* h1 = (TH1F*)f1.Get("myMiniTreeProducer/trigger/trigger_bitsrun");
  ofstream out;
  //out.open("trigPathsMC.txt");
  out.open("trigPathsData.txt");
  cout<<" file opned"<<endl;
  //  f1.ls(); 
  //  gSystem->Exit(0);
  
  for(int i = 1; i <= h1->GetXaxis()->GetNbins(); i++){
    out<<h1->GetXaxis()->GetBinLabel(i)<<endl;
    //cout<<h1->GetXaxis()->GetBinLabel(i)<<endl;
  }
  out.close();
}
