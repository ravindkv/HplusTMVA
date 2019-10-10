
bool isMuChannel = true;
bool isEleChannel = false;
//TFile *fData     = TFile::Open("all_EleData.root");
TFile *fData     = TFile::Open("all_muData.root");
TFile *fSig     = TFile::Open("all_Hplus90.root");

TFile *fSig90     = TFile::Open("all_Hplus90.root");
TFile *fSig100     = TFile::Open("all_Hplus100.root");
TFile *fSig120     = TFile::Open("all_Hplus120.root");
TFile *fSig140     = TFile::Open("all_Hplus140.root");
TFile *fSig150     = TFile::Open("all_Hplus150.root");
TFile *fSig155     = TFile::Open("all_Hplus155.root");
TFile *fSig160     = TFile::Open("all_Hplus160.root");
TFile* fTT	= TFile::Open("all_TTJetsP.root");

//--------------------------------------------
//function to make 2d-histo from two array
//--------------------------------------------
TH2F* get2dHisto(TFile *histFile, TString histName, TString xaxis_title){
  TH2F* hist = (TH2F*)(histFile->Get("base//"+histName))->Clone(histName);
  //gStyle->SetPalette(55);
  hist->GetXaxis()->SetTitle(xaxis_title);
  return hist;
}
TH2F* decorate2dHisto(TH2F* hist, TString myTit, TString xTit, TString yTit, TString zTit, int color){
  hist->SetTitle(myTit);
  hist->SetFillColor(color);
  hist->GetXaxis()->SetTitle(xTit);
  hist->GetYaxis()->SetTitle(yTit);
  hist->GetZaxis()->SetTitle(zTit);
  //hist->GetYaxis()->SetRangeUser(1, 3000);
  hist->GetYaxis()->SetRangeUser(1, 1.4* hist->GetMaximum());
  hist->GetYaxis()->SetTitleOffset(1.00);
  hist->GetXaxis()->SetTitleOffset(1.00);
  hist->GetYaxis()->SetTitleSize(0.07);   hist->GetXaxis()->SetTitleSize(0.07);
  hist->GetXaxis()->SetLabelSize(0.07);   hist->GetXaxis()->LabelsOption("u"); // extra
  hist->GetYaxis()->SetLabelSize(0.07);   hist->GetXaxis()->LabelsOption("u"); // extra
  hist->GetXaxis()->SetTickLength(0.05); 
  hist->GetXaxis()->SetNdivisions(5); 
  hist->GetYaxis()->SetTickLength(0.04); 
  //hist->SetMinimum(pMin);
  return hist;
}

void getAll2dHisto(){
  gStyle->SetOptStat(0);
  TCanvas *c1 = new TCanvas();
  c1->cd();
  gPad->SetBottomMargin(0.20);
  gPad->SetLeftMargin(0.15);
  gPad->SetRightMargin(0.15);
  TH2F *hist = (TH2F*) get2dHisto(fData, "RelIso_MET" , "RelIso vs MET");
  //decorate2dHisto(hist, "#mu + jets", "I_{rel}^{#mu}", "E_{T}^{miss}", "", 1);
  decorate2dHisto(hist, "e + jets", "I_{rel}^{e}", "E_{T}^{miss}", "", 1);
  hist->Draw("colz");
  //c1->SaveAs("RelIso_MET_mu.pdf");
  c1->SaveAs("RelIso_MET_ele.pdf");
}

void getHisto(TFile *histFile, TString dir, TString histName, TString xaxis_title){
  TH1F* hist; 
  if(!(histFile->Get("base/Iso/"+dir+"/"+histName))){
    hist = (TH1F*)(fTT->Get("base/Iso/"+dir+"/"+histName))->Clone(histName);
    hist->Add(hist, -1);
  }else hist = (TH1F*)(histFile->Get("base/Iso/"+dir+"/"+histName))->Clone(histName);
  gStyle->SetOptStat(1111111111);
  gStyle->SetFrameLineWidth(3);
  TCanvas *c1 = new TCanvas();
  gPad->SetBottomMargin(0.15);
  gPad->SetLeftMargin(0.15);
  gPad->SetRightMargin(0.05);
  hist->GetYaxis()->SetTitle("Events");
  //hist->GetYaxis()->SetRangeUser(1, 3000);
  hist->SetLineWidth(3);
  //hist->SetTitle(dir+": #mu+jets: WH150");
  //hist->SetTitle(dir+": #mu+jets: t#bar{t}");
  //hist->SetTitle("Binning: 10g, 10g, 10g : "+dir+": #mu+jets: t#bar{t}");
  //hist->SetTitle("Binning: 5%, 5%, 10% : "+dir+": #mu+jets: t#bar{t}");
  //hist->SetTitle("Binning: 5%, 5%, 20% : "+dir+": #mu+jets: t#bar{t}");
  //hist->SetTitle("Binning: 10%, 10%, 10% : "+dir+": #mu+jets: t#bar{t}");
  hist->GetYaxis()->SetRangeUser(1, 1.2* hist->GetMaximum());
  hist->GetXaxis()->SetRangeUser(0, 200);
  hist->GetXaxis()->SetTitle(xaxis_title);
  hist->GetXaxis()->SetTitleOffset(1.15);
  hist->GetYaxis()->SetTitleSize(0.05);   hist->GetXaxis()->SetTitleSize(0.05);
  hist->GetXaxis()->SetLabelSize(0.05);   hist->GetXaxis()->LabelsOption("u"); // extra
  hist->GetYaxis()->SetLabelSize(0.05);   hist->GetXaxis()->LabelsOption("u"); // extra
  hist->GetXaxis()->SetTickLength(0.05); 
  hist->GetYaxis()->SetTickLength(0.04); 
  hist->GetYaxis()->SetTitleSize(0.07);   
  hist->GetYaxis()->SetTitleOffset(1.05);
  cout<<dir<<":"<<histName<<": "<<setw(10)<<hist->Integral()<<setw(10)<<hist->GetMean()<<setw(10)<<hist->GetRMS()<<endl;
  hist->Draw();
  c1->SaveAs(dir+"_"+histName+".pdf");
  //c1->Close();
}



void getAllHistoBin10p10p10p(){
  /*
  getHisto(fSig, "KinFit", "mjj_kfit" , "M_{jj}^{Inc}[GeV]");
  getHisto(fSig, "PtbJetInc", "mjj_kfit_25To35" , "M_{jj}^{Inc}(25 < Pt_{bjet}^{Had} #leq 35)[GeV]");
  getHisto(fSig, "PtbJetInc", "mjj_kfit_35To42" , "M_{jj}^{Inc}(35 < Pt_{bjet}^{Had} #leq 42)[GeV$]");
  getHisto(fSig, "PtbJetInc", "mjj_kfit_42To50" , "M_{jj}^{Inc}(42 < Pt_{bjet}^{Had} #leq 50)[GeV]");
  getHisto(fSig, "PtbJetInc", "mjj_kfit_50To57" , "M_{jj}^{Inc}(50 < Pt_{bjet}^{Had} #leq 57)[GeV]");
  getHisto(fSig, "PtbJetInc", "mjj_kfit_57To65" , "M_{jj}^{Inc}(57 < Pt_{bjet}^{Had} #leq 65)[GeV]");
  getHisto(fSig, "PtbJetInc", "mjj_kfit_65To74" , "M_{jj}^{Inc}(65 < Pt_{bjet}^{Had} #leq 74)[GeV]");
  getHisto(fSig, "PtbJetInc", "mjj_kfit_74To84" , "M_{jj}^{Inc}(74 < Pt_{bjet}^{Had} #leq 84)[GeV]");
  getHisto(fSig, "PtbJetInc", "mjj_kfit_84To99" , "M_{jj}^{Inc}(84 < Pt_{bjet}^{Had} #leq 99)[GeV]");
  getHisto(fSig, "PtbJetInc", "mjj_kfit_99To124", "M_{jj}^{Inc}(99 < Pt_{bjet}^{Had} #leq 124)[GeV]");
  getHisto(fSig, "PtbJetInc", "mjj_kfit_124To500","M_{jj}^{Inc}(124 < Pt_{bjet}^{Had}#leq 500)[GeV]");
  */
  getHisto(fSig, "PtbJetCatL", "mjj_kfit_25To35" , "M_{jj}^{CatL}(25 < Pt_{bjet}^{Had} #leq 35)[GeV]");
  getHisto(fSig, "PtbJetCatL", "mjj_kfit_35To42" , "M_{jj}^{CatL}(35 < Pt_{bjet}^{Had} #leq 42)[GeV$]");
  getHisto(fSig, "PtbJetCatL", "mjj_kfit_42To50" , "M_{jj}^{CatL}(42 < Pt_{bjet}^{Had} #leq 50)[GeV]");
  getHisto(fSig, "PtbJetCatL", "mjj_kfit_50To57" , "M_{jj}^{CatL}(50 < Pt_{bjet}^{Had} #leq 57)[GeV]");
  getHisto(fSig, "PtbJetCatL", "mjj_kfit_57To65" , "M_{jj}^{CatL}(57 < Pt_{bjet}^{Had} #leq 65)[GeV]");
  getHisto(fSig, "PtbJetCatL", "mjj_kfit_65To74" , "M_{jj}^{CatL}(65 < Pt_{bjet}^{Had} #leq 74)[GeV]");
  getHisto(fSig, "PtbJetCatL", "mjj_kfit_74To84" , "M_{jj}^{CatL}(74 < Pt_{bjet}^{Had} #leq 84)[GeV]");
  getHisto(fSig, "PtbJetCatL", "mjj_kfit_84To99" , "M_{jj}^{CatL}(84 < Pt_{bjet}^{Had} #leq 99)[GeV]");
  getHisto(fSig, "PtbJetCatL", "mjj_kfit_99To124", "M_{jj}^{CatL}(99 < Pt_{bjet}^{Had} #leq 124)[GeV]");
  getHisto(fSig, "PtbJetCatL", "mjj_kfit_124To500","M_{jj}^{CatL}(124 < Pt_{bjet}^{Had}#leq 500)[GeV]");

  getHisto(fSig, "PtbJetCatM", "mjj_kfit_25To35" , "M_{jj}^{CatM}(25 < Pt_{bjet}^{Had} #leq 35)[GeV]");
  getHisto(fSig, "PtbJetCatM", "mjj_kfit_35To42" , "M_{jj}^{CatM}(35 < Pt_{bjet}^{Had} #leq 42)[GeV$]");
  getHisto(fSig, "PtbJetCatM", "mjj_kfit_42To50" , "M_{jj}^{CatM}(42 < Pt_{bjet}^{Had} #leq 50)[GeV]");
  getHisto(fSig, "PtbJetCatM", "mjj_kfit_50To57" , "M_{jj}^{CatM}(50 < Pt_{bjet}^{Had} #leq 57)[GeV]");
  getHisto(fSig, "PtbJetCatM", "mjj_kfit_57To65" , "M_{jj}^{CatM}(57 < Pt_{bjet}^{Had} #leq 65)[GeV]");
  getHisto(fSig, "PtbJetCatM", "mjj_kfit_65To74" , "M_{jj}^{CatM}(65 < Pt_{bjet}^{Had} #leq 74)[GeV]");
  getHisto(fSig, "PtbJetCatM", "mjj_kfit_74To84" , "M_{jj}^{CatM}(74 < Pt_{bjet}^{Had} #leq 84)[GeV]");
  getHisto(fSig, "PtbJetCatM", "mjj_kfit_84To99" , "M_{jj}^{CatM}(84 < Pt_{bjet}^{Had} #leq 99)[GeV]");
  getHisto(fSig, "PtbJetCatM", "mjj_kfit_99To124", "M_{jj}^{CatM}(99 < Pt_{bjet}^{Had} #leq 124)[GeV]");
  getHisto(fSig, "PtbJetCatM", "mjj_kfit_124To500","M_{jj}^{CatM}(124 < Pt_{bjet}^{Had}#leq 500)[GeV]");

  getHisto(fSig, "PtbJetCatT", "mjj_kfit_25To35" , "M_{jj}^{CatT}(25 < Pt_{bjet}^{Had} #leq 35)[GeV]");
  getHisto(fSig, "PtbJetCatT", "mjj_kfit_35To42" , "M_{jj}^{CatT}(35 < Pt_{bjet}^{Had} #leq 42)[GeV$]");
  getHisto(fSig, "PtbJetCatT", "mjj_kfit_42To50" , "M_{jj}^{CatT}(42 < Pt_{bjet}^{Had} #leq 50)[GeV]");
  getHisto(fSig, "PtbJetCatT", "mjj_kfit_50To57" , "M_{jj}^{CatT}(50 < Pt_{bjet}^{Had} #leq 57)[GeV]");
  getHisto(fSig, "PtbJetCatT", "mjj_kfit_57To65" , "M_{jj}^{CatT}(57 < Pt_{bjet}^{Had} #leq 65)[GeV]");
  getHisto(fSig, "PtbJetCatT", "mjj_kfit_65To74" , "M_{jj}^{CatT}(65 < Pt_{bjet}^{Had} #leq 74)[GeV]");
  getHisto(fSig, "PtbJetCatT", "mjj_kfit_74To84" , "M_{jj}^{CatT}(74 < Pt_{bjet}^{Had} #leq 84)[GeV]");
  getHisto(fSig, "PtbJetCatT", "mjj_kfit_84To99" , "M_{jj}^{CatT}(84 < Pt_{bjet}^{Had} #leq 99)[GeV]");
  getHisto(fSig, "PtbJetCatT", "mjj_kfit_99To124", "M_{jj}^{CatT}(99 < Pt_{bjet}^{Had} #leq 124)[GeV]");
  getHisto(fSig, "PtbJetCatT", "mjj_kfit_124To500","M_{jj}^{CatT}(124 < Pt_{bjet}^{Had}#leq 500)[GeV]");
 }

void getAllHistoBin5p5p20p(){
  getHisto(fSig, "PtbJetCatL", "mjj_kfit_25To32",  "M_{jj}^{CatL}(25 < Pt_{bjet}^{Had} #leq 32)[GeV]"); 
  getHisto(fSig, "PtbJetCatL", "mjj_kfit_32To37",  "M_{jj}^{CatL}(32 < Pt_{bjet}^{Had} #leq 37)[GeV]"); 
  getHisto(fSig, "PtbJetCatL", "mjj_kfit_37To41",  "M_{jj}^{CatL}(37 < Pt_{bjet}^{Had} #leq 41)[GeV]");  
  getHisto(fSig, "PtbJetCatL", "mjj_kfit_41To44",  "M_{jj}^{CatL}(41 < Pt_{bjet}^{Had} #leq 44)[GeV]");
  getHisto(fSig, "PtbJetCatL", "mjj_kfit_44To48",  "M_{jj}^{CatL}(44 < Pt_{bjet}^{Had} #leq 48)[GeV]");
  getHisto(fSig, "PtbJetCatL", "mjj_kfit_48To52",  "M_{jj}^{CatL}(48 < Pt_{bjet}^{Had} #leq 52)[GeV]");
  getHisto(fSig, "PtbJetCatL", "mjj_kfit_52To55",  "M_{jj}^{CatL}(52 < Pt_{bjet}^{Had} #leq 55)[GeV]");
  getHisto(fSig, "PtbJetCatL", "mjj_kfit_55To59",  "M_{jj}^{CatL}(55 < Pt_{bjet}^{Had} #leq 59)[GeV]");
  getHisto(fSig, "PtbJetCatL", "mjj_kfit_59To63",  "M_{jj}^{CatL}(59 < Pt_{bjet}^{Had} #leq 63)[GeV]");
  getHisto(fSig, "PtbJetCatL", "mjj_kfit_63To67",  "M_{jj}^{CatL}(63 < Pt_{bjet}^{Had} #leq 67)[GeV]");
  getHisto(fSig, "PtbJetCatL", "mjj_kfit_67To72",  "M_{jj}^{CatL}(67 < Pt_{bjet}^{Had} #leq 72)[GeV]");
  getHisto(fSig, "PtbJetCatL", "mjj_kfit_72To76",  "M_{jj}^{CatL}(72 < Pt_{bjet}^{Had} #leq 76)[GeV]");
  getHisto(fSig, "PtbJetCatL", "mjj_kfit_76To81",  "M_{jj}^{CatL}(76 < Pt_{bjet}^{Had} #leq 81)[GeV]");
  getHisto(fSig, "PtbJetCatL", "mjj_kfit_81To87",  "M_{jj}^{CatL}(81 < Pt_{bjet}^{Had} #leq 87)[GeV]");
  getHisto(fSig, "PtbJetCatL", "mjj_kfit_87To93",  "M_{jj}^{CatL}(87 < Pt_{bjet}^{Had} #leq 93)[GeV]");
  getHisto(fSig, "PtbJetCatL", "mjj_kfit_93To102", "M_{jj}^{CatL}(93 < Pt_{bjet}^{Had} #leq 102)[GeV]");
  getHisto(fSig, "PtbJetCatL", "mjj_kfit_102To112","M_{jj}^{CatL}(102 < Pt_{bjet}^{Had} #leq 112)[GeV]");
  getHisto(fSig, "PtbJetCatL", "mjj_kfit_112To127","M_{jj}^{CatL}(112 < Pt_{bjet}^{Had} #leq 127)[GeV]");
  getHisto(fSig, "PtbJetCatL", "mjj_kfit_127To152","M_{jj}^{CatL}(127 < Pt_{bjet}^{Had} #leq 152)[GeV]");
  getHisto(fSig, "PtbJetCatL", "mjj_kfit_152To500","M_{jj}^{CatL}(152 < Pt_{bjet}^{Had} #leq 500)[GeV]");

  getHisto(fSig, "PtbJetCatM", "mjj_kfit_25To32",  "M_{jj}^{CatM}(25 < Pt_{bjet}^{Had} #leq 32)[GeV]"); 
  getHisto(fSig, "PtbJetCatM", "mjj_kfit_32To37",  "M_{jj}^{CatM}(32 < Pt_{bjet}^{Had} #leq 37)[GeV]"); 
  getHisto(fSig, "PtbJetCatM", "mjj_kfit_37To41",  "M_{jj}^{CatM}(37 < Pt_{bjet}^{Had} #leq 41)[GeV]");  
  getHisto(fSig, "PtbJetCatM", "mjj_kfit_41To44",  "M_{jj}^{CatM}(41 < Pt_{bjet}^{Had} #leq 44)[GeV]");
  getHisto(fSig, "PtbJetCatM", "mjj_kfit_44To48",  "M_{jj}^{CatM}(44 < Pt_{bjet}^{Had} #leq 48)[GeV]");
  getHisto(fSig, "PtbJetCatM", "mjj_kfit_48To52",  "M_{jj}^{CatM}(48 < Pt_{bjet}^{Had} #leq 52)[GeV]");
  getHisto(fSig, "PtbJetCatM", "mjj_kfit_52To55",  "M_{jj}^{CatM}(52 < Pt_{bjet}^{Had} #leq 55)[GeV]");
  getHisto(fSig, "PtbJetCatM", "mjj_kfit_55To59",  "M_{jj}^{CatM}(55 < Pt_{bjet}^{Had} #leq 59)[GeV]");
  getHisto(fSig, "PtbJetCatM", "mjj_kfit_59To63",  "M_{jj}^{CatM}(59 < Pt_{bjet}^{Had} #leq 63)[GeV]");
  getHisto(fSig, "PtbJetCatM", "mjj_kfit_63To67",  "M_{jj}^{CatM}(63 < Pt_{bjet}^{Had} #leq 67)[GeV]");
  getHisto(fSig, "PtbJetCatM", "mjj_kfit_67To72",  "M_{jj}^{CatM}(67 < Pt_{bjet}^{Had} #leq 72)[GeV]");
  getHisto(fSig, "PtbJetCatM", "mjj_kfit_72To76",  "M_{jj}^{CatM}(72 < Pt_{bjet}^{Had} #leq 76)[GeV]");
  getHisto(fSig, "PtbJetCatM", "mjj_kfit_76To81",  "M_{jj}^{CatM}(76 < Pt_{bjet}^{Had} #leq 81)[GeV]");
  getHisto(fSig, "PtbJetCatM", "mjj_kfit_81To87",  "M_{jj}^{CatM}(81 < Pt_{bjet}^{Had} #leq 87)[GeV]");
  getHisto(fSig, "PtbJetCatM", "mjj_kfit_87To93",  "M_{jj}^{CatM}(87 < Pt_{bjet}^{Had} #leq 93)[GeV]");
  getHisto(fSig, "PtbJetCatM", "mjj_kfit_93To102", "M_{jj}^{CatM}(93 < Pt_{bjet}^{Had} #leq 102)[GeV]");
  getHisto(fSig, "PtbJetCatM", "mjj_kfit_102To112","M_{jj}^{CatM}(102 < Pt_{bjet}^{Had} #leq 112)[GeV]");
  getHisto(fSig, "PtbJetCatM", "mjj_kfit_112To127","M_{jj}^{CatM}(112 < Pt_{bjet}^{Had} #leq 127)[GeV]");
  getHisto(fSig, "PtbJetCatM", "mjj_kfit_127To152","M_{jj}^{CatM}(127 < Pt_{bjet}^{Had} #leq 152)[GeV]");
  getHisto(fSig, "PtbJetCatM", "mjj_kfit_152To500","M_{jj}^{CatM}(152 < Pt_{bjet}^{Had} #leq 500)[GeV]");

  getHisto(fSig, "PtbJetCatT", "mjj_kfit_25To43"  , "M_{jj}^{CatT}(25 < Pt_{bjet}^{Had} #leq 43)[GeV]");
  getHisto(fSig, "PtbJetCatT", "mjj_kfit_43To57"  , "M_{jj}^{CatT}(43 < Pt_{bjet}^{Had} #leq 57)[GeV$]");
  getHisto(fSig, "PtbJetCatT", "mjj_kfit_57To74"  , "M_{jj}^{CatT}(57 < Pt_{bjet}^{Had} #leq 74)[GeV]");
  getHisto(fSig, "PtbJetCatT", "mjj_kfit_74To99"  , "M_{jj}^{CatT}(74 < Pt_{bjet}^{Had} #leq 99)[GeV]");
  getHisto(fSig, "PtbJetCatT", "mjj_kfit_99To500" , "M_{jj}^{CatT}(99 < Pt_{bjet}^{Had} #leq 500)[GeV]");
 }
void getAllHistoBin5p5p10p(){
  getHisto(fSig, "PtbJetCatL", "mjj_kfit_25To32",  "M_{jj}^{CatL}(25 < Pt_{bjet}^{Had} #leq 32)[GeV]"); 
  getHisto(fSig, "PtbJetCatL", "mjj_kfit_32To37",  "M_{jj}^{CatL}(32 < Pt_{bjet}^{Had} #leq 37)[GeV]"); 
  getHisto(fSig, "PtbJetCatL", "mjj_kfit_37To41",  "M_{jj}^{CatL}(37 < Pt_{bjet}^{Had} #leq 41)[GeV]");  
  getHisto(fSig, "PtbJetCatL", "mjj_kfit_41To44",  "M_{jj}^{CatL}(41 < Pt_{bjet}^{Had} #leq 44)[GeV]");
  getHisto(fSig, "PtbJetCatL", "mjj_kfit_44To48",  "M_{jj}^{CatL}(44 < Pt_{bjet}^{Had} #leq 48)[GeV]");
  getHisto(fSig, "PtbJetCatL", "mjj_kfit_48To52",  "M_{jj}^{CatL}(48 < Pt_{bjet}^{Had} #leq 52)[GeV]");
  getHisto(fSig, "PtbJetCatL", "mjj_kfit_52To55",  "M_{jj}^{CatL}(52 < Pt_{bjet}^{Had} #leq 55)[GeV]");
  getHisto(fSig, "PtbJetCatL", "mjj_kfit_55To59",  "M_{jj}^{CatL}(55 < Pt_{bjet}^{Had} #leq 59)[GeV]");
  getHisto(fSig, "PtbJetCatL", "mjj_kfit_59To63",  "M_{jj}^{CatL}(59 < Pt_{bjet}^{Had} #leq 63)[GeV]");
  getHisto(fSig, "PtbJetCatL", "mjj_kfit_63To67",  "M_{jj}^{CatL}(63 < Pt_{bjet}^{Had} #leq 67)[GeV]");
  getHisto(fSig, "PtbJetCatL", "mjj_kfit_67To72",  "M_{jj}^{CatL}(67 < Pt_{bjet}^{Had} #leq 72)[GeV]");
  getHisto(fSig, "PtbJetCatL", "mjj_kfit_72To76",  "M_{jj}^{CatL}(72 < Pt_{bjet}^{Had} #leq 76)[GeV]");
  getHisto(fSig, "PtbJetCatL", "mjj_kfit_76To81",  "M_{jj}^{CatL}(76 < Pt_{bjet}^{Had} #leq 81)[GeV]");
  getHisto(fSig, "PtbJetCatL", "mjj_kfit_81To87",  "M_{jj}^{CatL}(81 < Pt_{bjet}^{Had} #leq 87)[GeV]");
  getHisto(fSig, "PtbJetCatL", "mjj_kfit_87To93",  "M_{jj}^{CatL}(87 < Pt_{bjet}^{Had} #leq 93)[GeV]");
  getHisto(fSig, "PtbJetCatL", "mjj_kfit_93To102", "M_{jj}^{CatL}(93 < Pt_{bjet}^{Had} #leq 102)[GeV]");
  getHisto(fSig, "PtbJetCatL", "mjj_kfit_102To112","M_{jj}^{CatL}(102 < Pt_{bjet}^{Had} #leq 112)[GeV]");
  getHisto(fSig, "PtbJetCatL", "mjj_kfit_112To127","M_{jj}^{CatL}(112 < Pt_{bjet}^{Had} #leq 127)[GeV]");
  getHisto(fSig, "PtbJetCatL", "mjj_kfit_127To152","M_{jj}^{CatL}(127 < Pt_{bjet}^{Had} #leq 152)[GeV]");
  getHisto(fSig, "PtbJetCatL", "mjj_kfit_152To500","M_{jj}^{CatL}(152 < Pt_{bjet}^{Had} #leq 500)[GeV]");

  getHisto(fSig, "PtbJetCatM", "mjj_kfit_25To32",  "M_{jj}^{CatM}(25 < Pt_{bjet}^{Had} #leq 32)[GeV]"); 
  getHisto(fSig, "PtbJetCatM", "mjj_kfit_32To37",  "M_{jj}^{CatM}(32 < Pt_{bjet}^{Had} #leq 37)[GeV]"); 
  getHisto(fSig, "PtbJetCatM", "mjj_kfit_37To41",  "M_{jj}^{CatM}(37 < Pt_{bjet}^{Had} #leq 41)[GeV]");  
  getHisto(fSig, "PtbJetCatM", "mjj_kfit_41To44",  "M_{jj}^{CatM}(41 < Pt_{bjet}^{Had} #leq 44)[GeV]");
  getHisto(fSig, "PtbJetCatM", "mjj_kfit_44To48",  "M_{jj}^{CatM}(44 < Pt_{bjet}^{Had} #leq 48)[GeV]");
  getHisto(fSig, "PtbJetCatM", "mjj_kfit_48To52",  "M_{jj}^{CatM}(48 < Pt_{bjet}^{Had} #leq 52)[GeV]");
  getHisto(fSig, "PtbJetCatM", "mjj_kfit_52To55",  "M_{jj}^{CatM}(52 < Pt_{bjet}^{Had} #leq 55)[GeV]");
  getHisto(fSig, "PtbJetCatM", "mjj_kfit_55To59",  "M_{jj}^{CatM}(55 < Pt_{bjet}^{Had} #leq 59)[GeV]");
  getHisto(fSig, "PtbJetCatM", "mjj_kfit_59To63",  "M_{jj}^{CatM}(59 < Pt_{bjet}^{Had} #leq 63)[GeV]");
  getHisto(fSig, "PtbJetCatM", "mjj_kfit_63To67",  "M_{jj}^{CatM}(63 < Pt_{bjet}^{Had} #leq 67)[GeV]");
  getHisto(fSig, "PtbJetCatM", "mjj_kfit_67To72",  "M_{jj}^{CatM}(67 < Pt_{bjet}^{Had} #leq 72)[GeV]");
  getHisto(fSig, "PtbJetCatM", "mjj_kfit_72To76",  "M_{jj}^{CatM}(72 < Pt_{bjet}^{Had} #leq 76)[GeV]");
  getHisto(fSig, "PtbJetCatM", "mjj_kfit_76To81",  "M_{jj}^{CatM}(76 < Pt_{bjet}^{Had} #leq 81)[GeV]");
  getHisto(fSig, "PtbJetCatM", "mjj_kfit_81To87",  "M_{jj}^{CatM}(81 < Pt_{bjet}^{Had} #leq 87)[GeV]");
  getHisto(fSig, "PtbJetCatM", "mjj_kfit_87To93",  "M_{jj}^{CatM}(87 < Pt_{bjet}^{Had} #leq 93)[GeV]");
  getHisto(fSig, "PtbJetCatM", "mjj_kfit_93To102", "M_{jj}^{CatM}(93 < Pt_{bjet}^{Had} #leq 102)[GeV]");
  getHisto(fSig, "PtbJetCatM", "mjj_kfit_102To112","M_{jj}^{CatM}(102 < Pt_{bjet}^{Had} #leq 112)[GeV]");
  getHisto(fSig, "PtbJetCatM", "mjj_kfit_112To127","M_{jj}^{CatM}(112 < Pt_{bjet}^{Had} #leq 127)[GeV]");
  getHisto(fSig, "PtbJetCatM", "mjj_kfit_127To152","M_{jj}^{CatM}(127 < Pt_{bjet}^{Had} #leq 152)[GeV]");
  getHisto(fSig, "PtbJetCatM", "mjj_kfit_152To500","M_{jj}^{CatM}(152 < Pt_{bjet}^{Had} #leq 500)[GeV]");

  getHisto(fSig, "PtbJetCatT", "mjj_kfit_25To35" , "M_{jj}^{CatT}(25 < Pt_{bjet}^{Had} #leq 35)[GeV]");
  getHisto(fSig, "PtbJetCatT", "mjj_kfit_35To42" , "M_{jj}^{CatT}(35 < Pt_{bjet}^{Had} #leq 42)[GeV$]");
  getHisto(fSig, "PtbJetCatT", "mjj_kfit_42To50" , "M_{jj}^{CatT}(42 < Pt_{bjet}^{Had} #leq 50)[GeV]");
  getHisto(fSig, "PtbJetCatT", "mjj_kfit_50To57" , "M_{jj}^{CatT}(50 < Pt_{bjet}^{Had} #leq 57)[GeV]");
  getHisto(fSig, "PtbJetCatT", "mjj_kfit_57To65" , "M_{jj}^{CatT}(57 < Pt_{bjet}^{Had} #leq 65)[GeV]");
  getHisto(fSig, "PtbJetCatT", "mjj_kfit_65To74" , "M_{jj}^{CatT}(65 < Pt_{bjet}^{Had} #leq 74)[GeV]");
  getHisto(fSig, "PtbJetCatT", "mjj_kfit_74To84" , "M_{jj}^{CatT}(74 < Pt_{bjet}^{Had} #leq 84)[GeV]");
  getHisto(fSig, "PtbJetCatT", "mjj_kfit_84To99" , "M_{jj}^{CatT}(84 < Pt_{bjet}^{Had} #leq 99)[GeV]");
  getHisto(fSig, "PtbJetCatT", "mjj_kfit_99To124", "M_{jj}^{CatT}(99 < Pt_{bjet}^{Had} #leq 124)[GeV]");
  getHisto(fSig, "PtbJetCatT", "mjj_kfit_124To500","M_{jj}^{CatT}(124 < Pt_{bjet}^{Had}#leq 500)[GeV]");
 }

void getAllHistoBin10g10g10g(){
  getHisto(fSig, "PtbJetCatL", "mjj_kfit_25To35" , "M_{jj}^{CatL}(25 < Pt_{bjet}^{Had} #leq 35)[GeV]");
  getHisto(fSig, "PtbJetCatL", "mjj_kfit_35To45" , "M_{jj}^{CatL}(35 < Pt_{bjet}^{Had} #leq 45)[GeV$]");
  getHisto(fSig, "PtbJetCatL", "mjj_kfit_45To55" , "M_{jj}^{CatL}(45 < Pt_{bjet}^{Had} #leq 55)[GeV]");
  getHisto(fSig, "PtbJetCatL", "mjj_kfit_55To65" , "M_{jj}^{CatL}(55 < Pt_{bjet}^{Had} #leq 65)[GeV]");
  getHisto(fSig, "PtbJetCatL", "mjj_kfit_65To75" , "M_{jj}^{CatL}(65 < Pt_{bjet}^{Had} #leq 75)[GeV]");
  getHisto(fSig, "PtbJetCatL", "mjj_kfit_75To85" , "M_{jj}^{CatL}(75 < Pt_{bjet}^{Had} #leq 85)[GeV]");
  getHisto(fSig, "PtbJetCatL", "mjj_kfit_85To95" , "M_{jj}^{CatL}(85 < Pt_{bjet}^{Had} #leq 95)[GeV]");
  getHisto(fSig, "PtbJetCatL", "mjj_kfit_95To105" , "M_{jj}^{CatL}(95 < Pt_{bjet}^{Had} #leq 105)[GeV]");
  getHisto(fSig, "PtbJetCatL", "mjj_kfit_105To150", "M_{jj}^{CatL}(105 < Pt_{bjet}^{Had} #leq 150)[GeV]");
  getHisto(fSig, "PtbJetCatL", "mjj_kfit_150To500","M_{jj}^{CatL}(150 < Pt_{bjet}^{Had}#leq 500)[GeV]");

  getHisto(fSig, "PtbJetCatM", "mjj_kfit_25To35" , "M_{jj}^{CatM}(25 < Pt_{bjet}^{Had} #leq 35)[GeV]");
  getHisto(fSig, "PtbJetCatM", "mjj_kfit_35To45" , "M_{jj}^{CatM}(35 < Pt_{bjet}^{Had} #leq 45)[GeV$]");
  getHisto(fSig, "PtbJetCatM", "mjj_kfit_45To55" , "M_{jj}^{CatM}(45 < Pt_{bjet}^{Had} #leq 55)[GeV]");
  getHisto(fSig, "PtbJetCatM", "mjj_kfit_55To65" , "M_{jj}^{CatM}(55 < Pt_{bjet}^{Had} #leq 65)[GeV]");
  getHisto(fSig, "PtbJetCatM", "mjj_kfit_65To75" , "M_{jj}^{CatM}(65 < Pt_{bjet}^{Had} #leq 75)[GeV]");
  getHisto(fSig, "PtbJetCatM", "mjj_kfit_75To85" , "M_{jj}^{CatM}(75 < Pt_{bjet}^{Had} #leq 85)[GeV]");
  getHisto(fSig, "PtbJetCatM", "mjj_kfit_85To95" , "M_{jj}^{CatM}(85 < Pt_{bjet}^{Had} #leq 95)[GeV]");
  getHisto(fSig, "PtbJetCatM", "mjj_kfit_95To105" , "M_{jj}^{CatM}(95 < Pt_{bjet}^{Had} #leq 105)[GeV]");
  getHisto(fSig, "PtbJetCatM", "mjj_kfit_105To150", "M_{jj}^{CatM}(105 < Pt_{bjet}^{Had} #leq 150)[GeV]");
  getHisto(fSig, "PtbJetCatM", "mjj_kfit_150To500","M_{jj}^{CatM}(150 < Pt_{bjet}^{Had}#leq 500)[GeV]");

  getHisto(fSig, "PtbJetCatT", "mjj_kfit_25To35" , "M_{jj}^{CatT}(25 < Pt_{bjet}^{Had} #leq 35)[GeV]");
  getHisto(fSig, "PtbJetCatT", "mjj_kfit_35To45" , "M_{jj}^{CatT}(35 < Pt_{bjet}^{Had} #leq 45)[GeV$]");
  getHisto(fSig, "PtbJetCatT", "mjj_kfit_45To55" , "M_{jj}^{CatT}(45 < Pt_{bjet}^{Had} #leq 55)[GeV]");
  getHisto(fSig, "PtbJetCatT", "mjj_kfit_55To65" , "M_{jj}^{CatT}(55 < Pt_{bjet}^{Had} #leq 65)[GeV]");
  getHisto(fSig, "PtbJetCatT", "mjj_kfit_65To75" , "M_{jj}^{CatT}(65 < Pt_{bjet}^{Had} #leq 75)[GeV]");
  getHisto(fSig, "PtbJetCatT", "mjj_kfit_75To85" , "M_{jj}^{CatT}(75 < Pt_{bjet}^{Had} #leq 85)[GeV]");
  getHisto(fSig, "PtbJetCatT", "mjj_kfit_85To95" , "M_{jj}^{CatT}(85 < Pt_{bjet}^{Had} #leq 95)[GeV]");
  getHisto(fSig, "PtbJetCatT", "mjj_kfit_95To105" , "M_{jj}^{CatT}(95 < Pt_{bjet}^{Had} #leq 105)[GeV]");
  getHisto(fSig, "PtbJetCatT", "mjj_kfit_105To150", "M_{jj}^{CatT}(105 < Pt_{bjet}^{Had} #leq 150)[GeV]");
  getHisto(fSig, "PtbJetCatT", "mjj_kfit_150To500","M_{jj}^{CatT}(150 < Pt_{bjet}^{Had}#leq 500)[GeV]");
 }

TH1F* getHisto_method2(TFile *histFile, TString dir, TString histName, TString xaxis_title){
  TH1F* hist; 
  if(!(histFile->Get("base/"+histName))){
    hist = (TH1F*)(fTT->Get("base/"+histName))->Clone(histName);
    hist->Add(hist, -1);
  }else hist = (TH1F*)(histFile->Get("base/"+histName))->Clone(histName);
  hist->GetYaxis()->SetTitle("Events");
  hist->SetTitle("");
  hist->SetLineWidth(10);
  hist->GetYaxis()->SetRangeUser(1, 1.2* hist->GetMaximum());
  hist->GetXaxis()->SetRangeUser(0.5, 1.5);
  hist->GetXaxis()->SetTitle(xaxis_title);
  hist->GetYaxis()->SetTitleSize(0.05);   hist->GetXaxis()->SetTitleSize(0.05);
  hist->GetXaxis()->SetLabelSize(0.05);   hist->GetXaxis()->LabelsOption("u"); // extra
  hist->GetYaxis()->SetLabelSize(0.05);   hist->GetXaxis()->LabelsOption("u"); // extra
  hist->GetXaxis()->SetTickLength(0.05); 
  hist->GetYaxis()->SetTickLength(0.04); 
  hist->GetYaxis()->SetTitleSize(0.07);   
  hist->GetXaxis()->SetTitleSize(0.07);   
  hist->GetYaxis()->SetTitleOffset(1.05);
  hist->GetXaxis()->SetTitleOffset(1.00);
  return hist;
}
void getTopPtHisto(TFile * fSig, TString proc){
  gStyle->SetOptStat(0);
  gStyle->SetFrameLineWidth(3);
  TCanvas *c1 = new TCanvas();
  gPad->SetBottomMargin(0.15);
  gPad->SetLeftMargin(0.15);
  gPad->SetRightMargin(0.05);
  TH1F* h_Sig = getHisto_method2(fSig, "", "SF_topPtWeights" , "top quark pT weights");
  
  TLegend* leg = new TLegend(0.7018792,0.6261504,0.9012081,0.9198861,NULL,"brNDC");
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);
  leg->SetFillColor(10);
  leg->SetTextSize(0.07);
  leg->AddEntry(h_Sig, proc);
  //pave text CMS box
  TPaveText *pt = new TPaveText(0.25,0.9354,0.90,0.9362, "brNDC"); // good_v1
  pt->SetBorderSize(1);
  pt->SetFillColor(19);
  pt->SetFillStyle(0);
  pt->SetTextSize(0.08);
  pt->SetLineColor(0);
  pt->SetTextFont(132);
  TText *text = pt->AddText("#sqrt{s}=13 TeV, 35.9 fb^{-1}; ");
  text->SetTextAlign(11);
  
  //pave text channel box
  TPaveText *ch = new TPaveText(1.00,0.9154898,0.7510067,0.9762187,"brNDC");
  ch->SetFillColor(19);
  ch->SetFillStyle(0);
  ch->SetLineColor(0);
  ch->SetTextSize(0.08);
  ch->SetBorderSize(1);
  if(isMuChannel) ch->AddText("#mu + jets");
  if(isEleChannel) ch->AddText("e + jets");
  h_Sig->Draw();
  pt->Draw();
  ch->Draw();
  leg->Draw();
  c1->SaveAs(proc+"_topPtWt.pdf");
 }

void getTopPtHistoAll(){
  getTopPtHisto(fTT, "t#bar{t} + jets");
  //getTopPtHisto(fSig90, "WH90");
  //getTopPtHisto(fSig100, "WH100");
  //getTopPtHisto(fSig120, "WH120");
  //getTopPtHisto(fSig140, "WH140");
  //getTopPtHisto(fSig150, "WH150");
  //getTopPtHisto(fSig155, "WH155");
  getTopPtHisto(fSig160, "WH160");
}


