
void printLimit(){
  TString massFiles = "mu_ele/Cat3_cTagEx/Mass120/higgsCombine_hcs_13TeV_mu_ele_Cat3_cTagEx.AsymptoticLimits.mH120.root";
    TFile f("local/"+massFiles,"READ"); 
    double expY     = 0.0;
    double r;
    TTree* limit = (TTree*)f.Get("limit");
    limit->SetBranchAddress("limit",&r);
    for(int k = 0 ; k< limit->GetEntries() ; k++){
      limit->GetEntry(k);
      if(k==2) expY    = r;
    }
    cout<<"expected limit = "<< expY<<endl;
}
