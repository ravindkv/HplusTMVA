TH1F* decorateHisto(TH1F *hist, TString xTitle, TString yTitle,  double xMin, double xMax, int color){
  hist->GetXaxis()->SetTitle(xTitle);
  hist->GetXaxis()->SetTitleSize(0.05);
  hist->GetXaxis()->SetLabelSize(0.045);
  hist->GetXaxis()->SetRangeUser(0.3, 3);
  hist->GetYaxis()->SetTitle(yTitle);
  hist->GetYaxis()->SetTitleSize(0.05);
  hist->GetYaxis()->SetLabelSize(0.045);
  hist->SetNdivisions(510, "x");
  hist->SetNdivisions(510, "y");
  hist->SetLineWidth(2);
  hist->SetLineColor(color);
  hist->SetMarkerSize(1);
  hist->GetYaxis()->SetTitleOffset(0.70);
  hist->SetTickLength(0.02, "x");
  hist->SetTickLength(0.02, "y");
  hist->SetBarWidth(1);
  hist->SetMarkerStyle(7);
  hist->SetMarkerColor(color);
  hist->SetMarkerSize(1);
  return hist; 
}

void funcVoidOneHist(TFile *f, TString histName, TString xLable, int color){
    TH1F* h = (TH1F*)f->Get("base/Iso/ExCTag/sf_CTag_"+histName);
    TH1F* h_wt = (TH1F*)f->Get("base/Iso/ExCTag/sf_CTag_"+histName+"_wt");
    double yield = h_wt->Integral();
    double ent = h_wt->GetEntries();
    double rms = h_wt->GetRMS();
    double mean = h_wt->GetMean();
    cout<<setw(8)<<histName<<setw(15)<<yield<<setw(15)<<ent<<setw(15)<<mean<<setw(15)<<rms<<endl;
    decorateHisto(h, xLable, "", 0.4, 1.8, color);
    h->SetTitle(histName);
    gPad->SetLogy(true);
    h->GetXaxis()->SetRangeUser(0.3, 3);
    h->Draw("HIST");
    //h->Draw("EP");
    TString outHist(f->GetName());
    TPaveText *pt = new TPaveText(0.20,0.75,0.25,0.87,"brNDC");
    pt->AddText("#splitline{SM t#bar{t}}{#mu + jets}");
    pt->SetFillColor(19);
    pt->SetFillStyle(0);
    pt->SetLineColor(0);
    pt->SetBorderSize(1);
    pt->SetTextSize(0.06);
    pt->Draw("same");
    //h->SaveAs("CTag/muExtraNP.pdf");
}

void funcVoidOneFile(TFile *f){
  cout<<setw(8)<<"Types"<<setw(15)<<"Entries"<<setw(15)<<"Integral"<<setw(15)<<"Mean"<<setw(15)<<"RMS"<<endl;
  TCanvas *can = new TCanvas();
  can->Divide(3, 2);
  can->cd(1);
  funcVoidOneHist(f,"yLyMyT", "loose c-tag event weight", 1); 
  can->cd(2);                                             
  funcVoidOneHist(f,"yLyMnT", "loose c-tag event weight", 2); 
  can->cd(3);                                             
  funcVoidOneHist(f,"yLnMyT", "loose c-tag event weight", 3); 
  can->cd(4);                                             
  funcVoidOneHist(f, "yLnMnT","loose c-tag event weight", 4); 
  can->cd(5);                                             
  funcVoidOneHist(f, "yMyT", "medium c-tag event weight",kOrange +1); 
  can->cd(6);
  funcVoidOneHist(f, "yMnT", "medium c-tag event weight", 6); 
  can->SaveAs("CTag/muExtraNP.pdf");
}

void inclusiveCTagSF(){
  gStyle->SetOptStat("rmei");
  gStyle->SetFrameLineWidth(1);
  gStyle->SetStatH(0.4);
  gStyle->SetStatW(0.4);
  TFile *fTT = new TFile("all_TTJetsP.root");
  cout<<"-----------"<<fTT->GetName()<<"-----------"<<endl;
  funcVoidOneFile(fTT);

  /*
  TFile *fH80 = new TFile("all_Hplus80.root");
  cout<<"-----------"<<fH80->GetName()<<"-----------"<<endl;
  funcVoidOneFile(fH80);

  TFile *fH100 = new TFile("all_Hplus100.root");
  cout<<"-----------"<<fH100->GetName()<<"-----------"<<endl;
  funcVoidOneFile(fH100);

  TFile *fH120 = new TFile("all_Hplus120.root");
  cout<<"-----------"<<fH120->GetName()<<"-----------"<<endl;
  funcVoidOneFile(fH120);
  */
}
