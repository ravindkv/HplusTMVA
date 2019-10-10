void ratioplot1() {
   gStyle->SetOptStat(0);
   auto c1 = new TCanvas("c1", "A ratio example");
   auto h1 = new TH1D("h1", "h1", 50, 0, 10);
   auto h2 = new TH1D("h2", "h2", 50, 0, 10);
   auto f1 = new TF1("f1", "exp(- x/[0] )");
   f1->SetParameter(0, 3);
   h1->FillRandom("f1", 1900);
   h2->FillRandom("f1", 2000);
   h1->Sumw2();

   auto legend = new TLegend();
   legend->AddEntry("", "Data: SingleElectron 2016D ", "");
   legend->AddEntry(h1, "Data");
   legend->AddEntry(h2, "Simulation");

    auto rp = new TRatioPlot(h1, h2);
   rp->Draw();
   
   legend->Draw("same");

   c1->Update();
}
