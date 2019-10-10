#include <map>
#include <fstream>

//-----------------------------------------------
//declare various functions to analyse data file
//-----------------------------------------------
//function to get any cloumn of any diode from input file
std::vector<Double_t> getDiodeCol(string diode_position, string col_name);

//function to make graph from two array
TGraph* makeGraph(vector<Double_t> Xarray, vector<Double_t> Yarray);

//function to decorate Graph  
TGraph* decorateGraph(TGraph *graph, TString xTitle, TString yTitle, TString myTitle, double yMin, double yMax, int color);

//function to decorate 1d histograms
TH1F* decorateHisto(TH1F *hist, TString xTitle, TString yTitle,  int nBin, double xMin, double xMax, int color);

//function to get graph for given diode position
TGraph * getDiodeGraph(string diodePos, string xVar, string yVar, TString xTit, TString yTit, TString tit, double yMin, double yMax, int color );

//function to make histo for an array
TH1F* makeHisto(vector<Double_t> V, TString histName, TString xTitle, TString yTitle,  int nBin, double xMin, double xMax, int color);

//function to make 2d-histo from two array
TGraph2D* make2dGraph(vector<Double_t> X, vector<Double_t> Y, vector<Double_t> Z, TString myTit, TString xTit, TString yTit, TString zTit);

//function to make 2d-Graph from two array
TH2F* make2dHisto(vector<Double_t> X, vector<Double_t> Y, vector<Double_t> Z, TString histName, TString myTit, TString xTit, TString yTit, TString zTit, int nXBin,int xMin, int xMax, int nYBin, int yMin, int yMax, int pMin, int color);

//function to overlay all the graphs in one canvas
void overlayGraphs(std::vector<std::string> diode_pos, string colX, string colY, TString xTit, TString yTit, TString myTit, int yMin, int yMax, TCanvas *c1);


void fitGraph(std::vector<std::string> diode_pos){
  vector<double>m_fit_1;
  vector<double>c_fit_1;
  vector<double>m_fit_2;
  vector<double>c_fit_2;
  vector<double>pos;
  TF1 *fit_line_1 = new TF1("fit", "[0]*x +[1]", 0, 5);
  TF1 *fit_line_2 = new TF1("fit", "[0]*x +[1]", 2, 7);
  for(int i =0; i<diode_pos.size(); i++){
    TLegend* leg3 = new TLegend(0.20,0.70,0.30,0.85,NULL,"brNDC");
    leg3->SetBorderSize(0);
    leg3->SetTextSize(0.030);
    leg3->SetFillColor(0);
    TGraph* g08 = getDiodeGraph(diode_pos[i], "HV", "I", "Voltage(kV)", "Current(nA)", "I vs V", 0, 300, i+1);
    g08->GetYaxis()->SetTitleOffset(1.30);
    g08->Fit(fit_line_1, "", "", 0, 2);
    float m_1 = fit_line_1->GetParameter(0);
    float c_1 = fit_line_1->GetParameter(1);
    m_fit_1.push_back(1000*1/m_1);
    c_fit_1.push_back(c_1);
    g08->Fit(fit_line_2, "", "", 3.5, 7);
    float m_2 = fit_line_2->GetParameter(0);
    float c_2 = fit_line_2->GetParameter(1);
    m_fit_2.push_back(1000*1/m_2);
    c_fit_2.push_back(c_2);
    pos.push_back(i);
    vector<Double_t> dc = getDiodeCol(diode_pos[i], "DCurrent"); 
    vector<Double_t> X = getDiodeCol(diode_pos[i], "X"); 
    vector<Double_t> Y = getDiodeCol(diode_pos[i], "Y"); 
    vector<Double_t> Z = getDiodeCol(diode_pos[i], "Z"); 
    
    double intX = (c_2-c_1)/(m_1-m_2);
    double intY = (m_1*c_2 - m_2*c_1)/(m_1 - m_2);
    cout<<"intX = "<<intX<<endl;
    cout<<"intY = "<<intY<<endl;
    
    ostringstream myTitle;
    ostringstream myLable1;
    ostringstream myLable2;
    ostringstream myPaveT;
    myPaveT<<"V_{BR} = "<<std::setprecision(4)<<intX<<" kV"<<", I_{BR} = "<<std::setprecision(4)<<intY<<" nA"<<endl;
    TPaveText *hLable = new TPaveText(0.4013423,0.1954898,0.7010067,0.2562187, "brNDC");
    hLable->SetTextSize(0.030);
    hLable->AddText(myPaveT.str().c_str());

    myTitle<<diode_pos[i]<<" (X= "<<std::setprecision(4)<<X[0]<<" mm"<<", Y= "<<Y[0]<<" mm"<<", Z="<<Z[0]<<" mm )"<< endl;
    myLable1<<"Fit Range = (0, 2):"<<" 1/m= "<<std::setprecision(4)<<1000/m_1<<" G#Omega"<<", c="<<c_1<<" nA"<<endl;
    myLable2<<"Fit Range = (3.5, 7):"<<" 1/m= "<<std::setprecision(4)<<1000/m_2<<" G#Omega"<<", c="<<c_2<<" nA"<<endl;
    
    TCanvas *can = new TCanvas("can","can",200,10,700,500);
    g08->SetTitle(myTitle.str().c_str());
    can->cd();
    //g08->SetMarkerSize(20);
    g08->SetMarkerStyle(20);
    g08->Draw("AP");
    leg3->AddEntry(fit_line_1, myLable1.str().c_str(), "PL");
    leg3->AddEntry(fit_line_2, myLable2.str().c_str(), "PL");
    leg3->Draw();
    fit_line_1->SetLineColor(3);
    fit_line_2->SetLineColor(6);
    fit_line_1->Draw("SAME");
    fit_line_2->Draw("SAME");
    hLable->Draw();
    cout<<diode_pos[i]<<": X(mm)="<<std::setprecision(4)<<X[0]<<", Y(mm)="<<Y[0]<<", Z(mm)="<<Z[0]<<", m(nA/kV)="<<m_2<<", c(nA)="<<c_2<<endl;
    cout<<diode_pos[i]<<"\t"<<X[0]<<"\t"<<Y[0]<<"\t"<<Z[0]<<"\t"<<intX<<"\t"<<intY<<endl;
    string outname(diode_pos[i]+".pdf");
    can->SaveAs(outname.c_str());
  }
}

void plotFitParam(std::vector<std::string> diode_pos){
  vector<double>m_fit_1;
  vector<double>c_fit_1;
  vector<double>m_fit_2;
  vector<double>c_fit_2;
  vector<double>pos;
  vector<double>xFromDC;
  vector<double>x_pos;
  vector<double>y_pos;
  vector<double>z_pos;
  vector<double>n_diode;
  vector<double>intX_vec;
  vector<double>intY_vec;
  vector<double>Iat7kV;
  vector<double>Iat7kV_2;
  TF1 *fit_line_1 = new TF1("fit", "[0]*x +[1]", 0, 5);
  TF1 *fit_line_2 = new TF1("fit", "[0]*x +[1]", 2, 7);
  for(int i =0; i<diode_pos.size(); i++){
    TLegend* leg3 = new TLegend(0.20,0.70,0.30,0.85,NULL,"brNDC");
    leg3->SetBorderSize(0);
    leg3->SetTextSize(0.030);
    leg3->SetFillColor(0);
    TGraph* g08 = getDiodeGraph(diode_pos[i], "HV", "I", "Voltage(kV)", "Current(nA)", "I vs V", 0, 300, i+1);
    g08->GetYaxis()->SetTitleOffset(1.30);
    g08->Fit(fit_line_1, "", "", 0, 2);
    float m_1 = fit_line_1->GetParameter(0);
    float c_1 = fit_line_1->GetParameter(1);
    m_fit_1.push_back(1000*1/m_1);
    c_fit_1.push_back(c_1);
    g08->Fit(fit_line_2, "", "", 3.5, 7);
    float m_2 = fit_line_2->GetParameter(0);
    float c_2 = fit_line_2->GetParameter(1);
    m_fit_2.push_back(1000*1/m_2);
    c_fit_2.push_back(c_2);
    double intX = (c_2-c_1)/(m_1-m_2);
    double intY = (m_1*c_2 - m_2*c_1)/(m_1 - m_2);
    intX_vec.push_back(intX);
    intY_vec.push_back(intY);
    pos.push_back(i);
    vector<Double_t> dc = getDiodeCol(diode_pos[i], "DCurrent"); 
    vector<Double_t> X = getDiodeCol(diode_pos[i], "X"); 
    vector<Double_t> Y = getDiodeCol(diode_pos[i], "Y"); 
    vector<Double_t> Z = getDiodeCol(diode_pos[i], "Z"); 
    vector<Double_t> I = getDiodeCol(diode_pos[i], "I"); 
    cout<<I.back()<<endl;
    Iat7kV.push_back(I.back());
    Iat7kV_2.push_back(I.back() -intY);
    xFromDC.push_back((dc[0]-c_2)/m_2);
    x_pos.push_back(X[0]);
    y_pos.push_back(Y[0]);
    z_pos.push_back(Z[0]);
    n_diode.push_back(i);
    cout<<"Diode Position: "<<diode_pos[i]<<endl;
    cout<<diode_pos[i]<<": X(mm)="<<X[0]<<", Y(mm)="<<Y[0]<<", Z(mm)="<<Z[0]<<", intX(kV)="<<intX<<", intY(nA)="<<intY<<endl;
  }
  
  ///////////////////////////// 1st Canvas /////////////////////////// 
  for(int i =0; i<25; i++){
  cout<<diode_pos[i]<<"\t"<<std::setprecision(4)<<intX_vec[i]<<"\t"<<std::setprecision(4)<<intY_vec[i]<<"\t"<<Iat7kV[i]<<"\t"<<Iat7kV_2[i]<<endl;
  }
  TCanvas *can1 = new TCanvas();
  can1->Divide(1, 3);
  can1->cd(1);
  TGraph* gr_Iat7kV_Vbr = makeGraph(intX_vec, Iat7kV);
  decorateGraph(gr_Iat7kV_Vbr, "Breakdown Voltage (kV)", "Current(nA) at 7kV", " ", 150, 300, 3);  
  gr_Iat7kV_Vbr->Draw("AP");
  
  can1->cd(2);
  TGraph* gr_Iat7kV_2_Vbr = makeGraph(intX_vec, Iat7kV_2);
  decorateGraph(gr_Iat7kV_2_Vbr, "Breakdown Voltage (kV)", "Current (nA) at 7kV - I_{BR}", " ", 100, 180, 2);  
  gr_Iat7kV_2_Vbr->Draw("AP");
 
  can1->cd(3); 
  TGraph* gr_m2_Vbr = makeGraph(intX_vec, m_fit_2);
  decorateGraph(gr_m2_Vbr, "Breakdown Voltage (kV)", "Resistance (G#Omega)", " ", 20, 40, 3);  
  gr_m2_Vbr->Draw("AP");
  
  ///////////////////////////// 2nd Canvas /////////////////////////// 
  TCanvas *can2 = new TCanvas();
  //----------------------------
  // Graphs
  //----------------------------
  can2->Divide(3, 5);
  can2->cd(1);
  TGraph* gr_intX = makeGraph(pos, intX_vec);
  decorateGraph(gr_intX, "Diode Position (a.u.)", "Voltage (kV)", "Breakdown Voltage (V_{BR})", 3, 3.5, 2);  
  gr_intX->Draw("ALP");
  
  can2->cd(4);
  TGraph* gr_intY = makeGraph(pos, intY_vec);
  decorateGraph(gr_intY, "Diode Position (a.u.)", "Current (nA)", "Current at Breakdown (I_{BR})", 65, 80, 3);  
  gr_intY->Draw("ALP");
  
  can2->cd(7);
  TGraph* gr_m2 = makeGraph(pos, m_fit_2);
  decorateGraph(gr_m2, "Diode Position (a.u.)", "Resistance (G#Omega)", "Resistance", 20, 40, 40);  
  gr_m2->Draw("ALP");
  
  can2->cd(10);
  TGraph* gr_Iat7kV = makeGraph(pos, Iat7kV);
  decorateGraph(gr_Iat7kV, "Diode Position (a.u.)", "Current (nA)", "Current at 7 kV", 150, 300, 6);  
  gr_Iat7kV->Draw("ALP");
  
  can2->cd(13);
  TGraph* gr_Iat7kV_2 = makeGraph(pos, Iat7kV_2);
  decorateGraph(gr_Iat7kV_2, "Diode Position (a.u.)", "Current (nA)", "Current at 7 kV - I_{BR}", 100, 180, 9);  
  gr_Iat7kV_2->Draw("ALP");
  
  //----------------------------
  // 1d-histos
  //----------------------------
  can2->cd(2);
  TH1F* h_intX = makeHisto(intX_vec, "Breakdown Voltage (V_{BR})", "Voltage (kV)", "Entries",  20,  3, 3.5, 2);
  h_intX->Draw("HIST");
  
  can2->cd(5);
  TH1F* h_intY = makeHisto(intY_vec, "Current at Breakdown (I_{BR}) ", "Current (nA)", "Entries",  20,  65, 80, 3);
  h_intY->Draw("HIST");
  
  can2->cd(8);
  TH1F* h_m2 = makeHisto(m_fit_2, "Resistance", "Resistance (G#Omega)", "Entries",  20,  20, 40, 40);
  h_m2->Draw("HIST");
  
  can2->cd(11);
  TH1F* h_Iat7kV = makeHisto(Iat7kV, "Current at 7kV", "Current (nA)", "Entries",  20,  150, 300, 6);
  h_Iat7kV->Draw("HIST");
  
  can2->cd(14);
  TH1F* h_Iat7kV_2 = makeHisto(Iat7kV_2, "Current at 7kV -I_{BR}", "Current (nA)", "Entries",  20,  100, 180, 9);
  h_Iat7kV_2->Draw("HIST");
  
  //----------------------------
  // 2d-histos
  //----------------------------
  //gStyle->SetOptStat(0000); 
  can2->cd(3);
  TH2F *gr2d_intX = make2dHisto(x_pos, z_pos, intX_vec, "Breakdown Voltage (V_{BR})", "Breakdown Voltage (V_{BR}) (kV) = f(x,z)", "x(mm)", "z(mm)", "", 20, 1, 20, 20, 1, 20, 3, 2);
  gr2d_intX->Draw("colz");

  can2->cd(6);
  TH2F *gr2d_intY = make2dHisto(x_pos, z_pos, intY_vec, "Current at Breakdown (I_{BR})", "Current (nA) = f(x,z)", "x(mm)", "z(mm)", "", 20, 1, 20, 20, 1, 20, 65, 3);
  gr2d_intY->Draw("colz");

  can2->cd(9);
  TH2F *h2d_m2 = make2dHisto(x_pos, z_pos, m_fit_2, "Resistance (G#Omega)", "Resistance (G#Omega) = f(x,z)", "x(mm)", "z(mm)", "", 20, 1, 20, 20, 1, 20, 20, 30);
  h2d_m2->Draw("colz");

  can2->cd(12);
  TH2F *h2d_Iat7kV = make2dHisto(x_pos, z_pos, Iat7kV, "Current at 7kV", "Current (nA) at 7kV = f(x,z)", "x(mm)", "z(mm)", "", 20, 1, 20, 20, 1, 20, 150, 6);
  h2d_Iat7kV->Draw("colz");
  
  can2->cd(15);
  TH2F *h2d_Iat7kV_2 = make2dHisto(x_pos, z_pos, Iat7kV_2, "Current at 7kV", "Current (nA) at 7kV -I_{BR} = f(x,z)", "x(mm)", "z(mm)", "", 20, 1, 20, 20, 1, 20, 100, 9);
  h2d_Iat7kV_2->Draw("colz");
}

void analyseTextFile(){
  //diode position
  std::vector<std::string> diode_pos;
  diode_pos.push_back("P00");
  diode_pos.push_back("P01");
  diode_pos.push_back("P02");
  diode_pos.push_back("P03");
  diode_pos.push_back("P04");
  diode_pos.push_back("P05");
  diode_pos.push_back("P06");
  diode_pos.push_back("P07");
  diode_pos.push_back("P08");
  diode_pos.push_back("P09");
  diode_pos.push_back("P10");
  diode_pos.push_back("P11");
  diode_pos.push_back("P12");
  diode_pos.push_back("P13");
  diode_pos.push_back("P14");
  diode_pos.push_back("P15");
  diode_pos.push_back("P16");
  diode_pos.push_back("P17");
  diode_pos.push_back("P18");
  diode_pos.push_back("P19");
  diode_pos.push_back("P20");
  diode_pos.push_back("P21");
  diode_pos.push_back("P22");
  diode_pos.push_back("P23");
  diode_pos.push_back("P24");
  
  TCanvas *c1 = new TCanvas("c1","c1",200,10,700,500);
  overlayGraphs(diode_pos, "HV", "I", "Voltage (kV)", "Current (nA)", "I vs V", 60, 250, c1);
  plotFitParam(diode_pos);
   //fitGraph(); 
}

//--------------------------------
//function to get any cloumn 
//of any diode from input file
//--------------------------------
std::vector<Double_t> getDiodeCol(string diode_position, string col_name){
  //open input file
  ifstream infile;
  infile.open("HE-HPD_22012018_1_combined_v2_1.txt");//open the text file
  if (!infile) cout << "Error failed to open program terminated";  
  std::vector<Double_t> diodeCol;
  //declare array type
  string Position_; 
  Int_t Date_; 
  Double_t Time_; 
  Double_t X_, Y_, Z_, DCurrent_, HV_, I_;
  
  //declare map for each colomn
  std::map<std::string, Double_t> mapDouble;
  std::map<std::string, string> mapString;
  //ignore first line of the input txt file 
  //char c[100000];
  //for(int i=0; i<11; i++)infile >>c;
  //loop over all the rows of the input file
  while (!infile.eof()){
    infile >> Date_>> Time_>> Position_>> X_>> Y_>> Z_>> DCurrent_>> HV_>>I_;
    //cout<<Date_<<"\t"<<Time_<<"\t"<<Position_<<"\t"<<X_<<"\t"<<Y_<<"\t"<<Z_<<endl;
    mapDouble["Date"] 	= Date_;
    mapDouble["Time"] 	= Time_;
    mapString["Position"] = Position_;
    mapDouble["X"] 	= X_;
    mapDouble["Y"] 	= Y_;
    mapDouble["Z"] 	= Z_;
    mapDouble["DCurrent"] = DCurrent_;
    mapDouble["HV"] 	= HV_;
    mapDouble["I"]        = I_;
    if(Position_==diode_position) diodeCol.push_back(mapDouble[col_name]);
  }
  return diodeCol;
}

//--------------------------------------------
//function to make graph from two array
//--------------------------------------------
TGraph* makeGraph(vector<Double_t> Xarray, vector<Double_t> Yarray){
  Int_t n = Xarray.size();
  Double_t x[n], y[n];  
   for (Int_t i=0;i<n;i++) {
     x[i] = Xarray[i];
     y[i] = Yarray[i] ;
   }
   TGraph* gr = new TGraph(n,x,y);
   return gr;
}

//--------------------------------------------
//function to decorate Graph  
//--------------------------------------------
TGraph* decorateGraph(TGraph *graph, TString xTitle, TString yTitle, TString myTitle, double yMin, double yMax, int color){
  graph->SetTitle(myTitle);
  graph->GetYaxis()->SetTitleOffset(1.30);
  graph->GetXaxis()->SetTitle(xTitle);
  graph->GetXaxis()->SetTitleSize(0.04);
  graph->GetXaxis()->SetLabelSize(0.035);
  graph->GetYaxis()->SetTitle(yTitle);
  graph->GetYaxis()->SetTitleSize(0.04);
  graph->GetYaxis()->SetRangeUser(yMin, yMax);
  //graph->GetXaxis()->SetRangeUser(0, 10);
  graph->GetYaxis()->SetLabelSize(0.035);
  graph->SetLineColor(color);
  graph->SetLineWidth(3);
  graph->SetMarkerSize(20);
  graph->SetMarkerStyle(20);
  graph->SetMarkerSize(1);
  return graph; 
}

//--------------------------------------------
//function get graph for given diode position
//--------------------------------------------
TGraph * getDiodeGraph(string diodePos, string xVar, string yVar, TString xTit, TString yTit, TString tit, double yMin, double yMax, int color ){
  vector<Double_t> V = getDiodeCol(diodePos, xVar);
  vector<Double_t> I = getDiodeCol(diodePos, yVar);
  TGraph* gr = makeGraph(V, I);
  decorateGraph(gr, xTit, yTit, diodePos, yMin, yMax, color);
  return gr;  
}

//--------------------------------------------
//function to make histo for an array
//--------------------------------------------
TH1F* makeHisto(vector<Double_t> V, TString histName, TString xTitle, TString yTitle,  int nBin, double xMin, double xMax, int color){
  Int_t n = V.size();
  TH1F *hist = new TH1F(histName, histName, nBin, xMin, xMax); 
  for (Int_t i=0;i<n;i++) {
     hist->Fill(V[i]);
  }
  decorateHisto(hist, xTitle, yTitle, nBin, xMin, xMax, color);
  return hist;
}

//--------------------------------------------
//function to decorate 1d histograms
//--------------------------------------------
TH1F* decorateHisto(TH1F *hist, TString xTitle, TString yTitle,  int nBin, double xMin, double xMax, int color){
  hist->GetXaxis()->SetTitle(xTitle);
  hist->GetXaxis()->SetTitleSize(0.05);
  hist->GetXaxis()->SetLabelSize(0.045);
  hist->GetYaxis()->SetTitle(yTitle);
  hist->GetYaxis()->SetTitleSize(0.05);
  hist->GetYaxis()->SetLabelSize(0.045);
  hist->SetNdivisions(510, "x");
  hist->SetNdivisions(510, "y");
  hist->SetLineWidth(2);
  hist->SetLineColor(color);
  hist->SetMarkerSize(1);
  hist->SetTickLength(0.02, "x");
  hist->SetTickLength(0.02, "y");
  hist->SetBarWidth(1);
  hist->SetMarkerStyle(7);
  hist->SetMarkerSize(1);
  return hist; 
}


//--------------------------------------------
//function to make 2d-histo from two array
//--------------------------------------------
TH2F* make2dHisto(vector<Double_t> X, vector<Double_t> Y, vector<Double_t> Z, TString histName, TString myTit, TString xTit, TString yTit, TString zTit, int nXBin,int xMin, int xMax, int nYBin, int yMin, int yMax, int pMin, int color){
  TH2F *h2 = new TH2F(histName, histName, nXBin, xMin, xMax, nYBin, yMin, yMax);
  for (Int_t i=0; i<X.size(); i++) {
      h2->SetBinContent(X[i], Y[i], Z[i]);
  }
  h2->SetTitleOffset(1.030);
  h2->SetTitle(myTit);
  h2->SetLineColor(color);
  h2->GetXaxis()->SetTitle(xTit);
  h2->GetYaxis()->SetTitle(yTit);
  h2->GetZaxis()->SetTitle(zTit);
  h2->SetMinimum(pMin);
  h2->GetYaxis()->SetTitleSize(0.05);
  h2->GetYaxis()->SetLabelSize(0.045);
  h2->GetXaxis()->SetTitleSize(0.05);
  h2->GetXaxis()->SetLabelSize(0.045);
  gStyle->SetPalette(55);
  return h2;
}

//--------------------------------------------
//function to make 2d-Graph from two array
//--------------------------------------------
TGraph2D* make2dGraph(vector<Double_t> X, vector<Double_t> Y, vector<Double_t> Z, TString myTit, TString xTit, TString yTit, TString zTit){
  TGraph2D *gr2d = new TGraph2D();
  for (Int_t i=0; i<X.size(); i++) {
     gr2d->SetPoint(i,X[i],Y[i],Z[i]);
  }
  gr2d->SetTitle(myTit);
  gr2d->GetXaxis()->SetTitle(xTit);
  gr2d->GetYaxis()->SetTitle(yTit);
  gr2d->GetZaxis()->SetTitle(zTit);
  gStyle->SetPalette(1);
  return gr2d;
}

//-----------------------------------------------
//overlay all the graphs in one canvas
//-----------------------------------------------
void overlayGraphs(std::vector<std::string> diode_pos, string colX, string colY, TString xTit, TString yTit, TString myTit, int yMin, int yMax, TCanvas *c1){
  c1->cd();
  TLegend* leg = new TLegend(0.30,0.30,0.50,0.85,NULL,"brNDC");
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);
  leg->SetFillColor(0);
  for(int i =0; i<diode_pos.size(); i++){
    TGraph* myGraph = getDiodeGraph(diode_pos[i], colX, colY, xTit, yTit, myTit, yMin, yMax, i);  
    if(i==0) myGraph->Draw("ALP");
    else  myGraph->Draw("LPSame");
    leg->AddEntry(myGraph,diode_pos[i].c_str(),"PL");
  }
  leg->Draw();
} 
