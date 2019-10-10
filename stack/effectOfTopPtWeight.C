

bool isMuChannel = false;
bool isEleChannel = true;
//TFile * fileWith = new TFile("stack_20190402_Mu_Sys_ARC_topPt/all_TTJetsP.root");
//TFile * fileWithOut = new TFile("stack_20190402_Mu_Sys_ARC/all_TTJetsP.root");
TFile * fileWith = new TFile("stack_20190402_Ele_Sys_ARC_topPt/all_TTJetsP.root");
TFile * fileWithOut = new TFile("stack_20190402_Ele_Sys_ARC/all_TTJetsP.root");
TH1F* decorateHisto(TH1F *hist, TString histTitle, TString xTitle, TString yTitle,  double xMin, double xMax, int color){
  hist->SetTitle(histTitle);
  hist->GetXaxis()->SetTitle(xTitle);
  hist->GetXaxis()->SetTitleSize(0.09);
  hist->GetXaxis()->SetLabelSize(0.07);
  hist->GetYaxis()->SetTitle(yTitle);
  hist->GetYaxis()->SetTitleSize(0.06);
  hist->GetYaxis()->SetLabelSize(0.055);
  hist->GetXaxis()->SetRangeUser(xMin, xMax);
  hist->GetYaxis()->SetRangeUser(0.6, 1.4);
  hist->SetNdivisions(510, "x");
  hist->SetNdivisions(510, "y");
  hist->SetLineColor(color);
  hist->SetLineWidth(3);
  hist->SetMarkerSize(1);
  hist->SetTickLength(0.02, "x");
  hist->SetTickLength(0.02, "y");
  hist->SetBarWidth(1);
  hist->SetMarkerStyle(7);
  hist->SetMarkerSize(1);
  hist->GetYaxis()->SetTitleOffset(0.6);
  hist->GetXaxis()->SetTitleOffset(1.0);
  return hist;
}


void effectOfTopPtWeight(){
  gStyle->SetOptStat(0);
  TString xTitle = "m_{jj} (GeV)";
  TString yTitle = "#frac{Data/Bkg with top pT weights}{ Data/Bkg without top pT weights}"; 
  double xMin = 0.0;
  double xMax = 180.0;
  TH1F* histWithExL = (TH1F*)fileWith->Get("base/Iso/KinFit/mjj_kfit_CTagExL");
  TH1F* histWithExM = (TH1F*)fileWith->Get("base/Iso/KinFit/mjj_kfit_CTagExM");
  TH1F* histWithExT = (TH1F*)fileWith->Get("base/Iso/KinFit/mjj_kfit_CTagExT");
  TH1F* histWithOutExL = (TH1F*)fileWithOut->Get("base/Iso/KinFit/mjj_kfit_CTagExL");
  TH1F* histWithOutExM = (TH1F*)fileWithOut->Get("base/Iso/KinFit/mjj_kfit_CTagExM");
  TH1F* histWithOutExT = (TH1F*)fileWithOut->Get("base/Iso/KinFit/mjj_kfit_CTagExT");

  TH1F* hRatioExL = (TH1F*)histWithExL->Clone("hRatioExL");
  hRatioExL->Divide(histWithOutExL);
  decorateHisto(hRatioExL, "Exclusive Loose", "", yTitle,  xMin, xMax, kRed);
  TH1F* hRatioExM = (TH1F*)histWithExM->Clone("hRatioExM");
  hRatioExM->Divide(histWithOutExM);
  decorateHisto(hRatioExM, "Exclusive Medium", "", yTitle,  xMin, xMax, kGreen);
  TH1F* hRatioExT = (TH1F*)histWithExT->Clone("hRatioExT");
  hRatioExT->Divide(histWithOutExT);
  decorateHisto(hRatioExT, "Exclusive Tight", xTitle, yTitle,  xMin, xMax, kBlue);

  TCanvas *can = new TCanvas();
  can->Divide(1, 3);
  can->cd(1);
  hRatioExL->Draw();
  can->cd(2);
  hRatioExM->Draw();
  can->cd(3);
  gPad->SetBottomMargin(0.20);
  hRatioExT->Draw();
  if(isMuChannel)can->SaveAs("mu_ratio_topPtWeight.png");
  if(isEleChannel)can->SaveAs("ele_ratio_topPtWeight.png");
}

