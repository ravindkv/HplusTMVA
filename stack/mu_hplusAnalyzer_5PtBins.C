
///////////////////////
// Muon Channel
///////////////////////

#include "hplusAnalyzer.h"
#include <map>

using namespace std;
void hplusAnalyzer::CutFlowAnalysis(TString url, string myKey, string evtType){
  
  TString outFile("13TeV/outputDir/");
  TString Filename_ = outFile+evtType+"_Anal.root";
  TFile *outFile_ = TFile::Open( Filename_, "RECREATE" );
  outFile_->SetCompressionLevel( 9 );
  
  TString debug_Filename_ = Filename_+"_debug.txt";
  string debug_file(debug_Filename_);
  
  //check if the input file is MC or Data  
  Reader *evR_;  
  evR_ = new Reader();
  TFile *f_ = TFile::Open(url);
  int nEntries = evR_->AssignEventTreeFrom(f_);
  MyEvent *ev_;
  ev_ = evR_->GetNewEvent(1);

  CutFlowProcessor(url, myKey, "base", outFile_);
  CutFlowProcessor(url, myKey, "baseLowMET", outFile_);
  //to estimate unc in the data-driven qcd 
  CutFlowProcessor(url, myKey, "baseIso20HighMET", outFile_);
  CutFlowProcessor(url, myKey, "baseIso20LowMET", outFile_);
  //---------------------------------------------------//
  //for systematics (all sys in one go)
  //---------------------------------------------------//  
  if(!ev_->isData){ 
    CutFlowProcessor(url, myKey, "PileupPlus", 	outFile_);
    CutFlowProcessor(url, myKey, "PileupMinus", 	outFile_);
    CutFlowProcessor(url, myKey, "JESPlus", 	outFile_);
    CutFlowProcessor(url, myKey, "JESMinus", 	outFile_);
    CutFlowProcessor(url, myKey, "JERPlus", 	outFile_);
    CutFlowProcessor(url, myKey, "JERMinus", 	outFile_);
    CutFlowProcessor(url, myKey, "bTagPlus", 	outFile_);
    CutFlowProcessor(url, myKey, "bTagMinus", 	outFile_);
    CutFlowProcessor(url, myKey, "cTagPlus", 	outFile_);
    CutFlowProcessor(url, myKey, "cTagMinus", 	outFile_);
    CutFlowProcessor(url, myKey, "TopPtPlus", 	outFile_);
    CutFlowProcessor(url, myKey, "TopPtMinus", 	outFile_);
    //CutFlowProcessor(url, myKey, "METUCPlus", 	outFile_);
    //CutFlowProcessor(url, myKey, "METUCMinus", 	outFile_);
  }
  outFile_->Write(); 
  outFile_->Close();
  f_->Close();
  delete f_;
}

//---------------------------------------------------//
//Process the cuts, event by event
//---------------------------------------------------//  
void hplusAnalyzer::CutFlowProcessor(TString url,  string myKey, TString cutflowType, TFile *outFile_){
  int input_count = 0;
  bool isPFlow = (myKey.find("PFlow") != string::npos) ? true : false;
  string eAlgo("Electrons"), mAlgo("Muons"), jAlgo("Jets"), metAlgo("METs");
  
  //Uncertainty variations, JES, JER, MET unclustered, bTag
  int jes = 0, jer = 0, metuc = 0, bScale = 0, cScale =0, minMET =20, minMT =0;
  //to estimate unc in the data-driven qcd 
  bool isLowMET = false, isIso20 = false;

  if(cutflowType.Contains("JESPlus"))jes = 1;
  else if (cutflowType.Contains("JESMinus"))jes = -1;
  else if (cutflowType.Contains("JERPlus"))jer = 1;
  else if (cutflowType.Contains("JERMinus"))jer = -1;
  else if (cutflowType.Contains("METUCPlus"))metuc = 1;
  else if (cutflowType.Contains("METUCMinus"))metuc = -1;
  else if (cutflowType.Contains("bTagPlus"))bScale = 1;
  else if (cutflowType.Contains("bTagMinus"))bScale = -1; 
  else if (cutflowType.Contains("cTagPlus"))cScale = 1;
  else if (cutflowType.Contains("cTagMinus"))cScale = -1; 
  //to estimate unc in the data-driven qcd 
  else if (cutflowType.Contains("baseIso")){ 
    if (cutflowType.Contains("Iso20HighMET"))isIso20 = true; 
    if (cutflowType.Contains("Iso20LowMET")){isIso20 = true; isLowMET= true;}
  }
  else if (cutflowType.Contains("LowMET"))isLowMET = true;
  
  evR = new Reader();
  TFile *f = TFile::Open(url);
  if(f==0) return ;
  if(f->IsZombie()) { f->Close(); return; }
  
  //---------------------------------------------------//
  //get initial number of events, from ntuples
  //store initial informations, in a txt file
  //---------------------------------------------------//
  double lumiTotal = 35860;
  int nEntries = evR->AssignEventTreeFrom(f);
  if(nEntries == 0) {return; }
  TH1F* inputcf = (TH1F*)(f->Get("allEventsFilter/totalEvents"));
  double initialEvents = inputcf->GetBinContent(1);
  cout<<"\033[01;32m input file: \033[00m"<<url<<"\n"<<endl;
  fillHisto(outFile_, cutflowType, "", "totalEvents", 10, 0, 10000000000, initialEvents, 1 );
  MyEvent *ev;
  int nTriggEvent = 0, nSelEvents = 0, matchjetcount= 0, threepairjet = 0;
  double nVerticesFailCount = 0.0;
  double matchedJet_q = 0.0, matchedJet_b = 0.0, matched_quark_eta_pt = 0.0, not_matchedJet_q = 0.0;
  
  //---------------------------------------------------//
  //BTag SF: read CSV file for SF, 2D histos for eff 
  //---------------------------------------------------//      
  //https://twiki.cern.ch/twiki/bin/view/CMS/BtagRecommendation80XReReco#Data_MC_Scale_Factors_period_dep
  const std::string & bTagCSVfile 	= "stack/CSVv2_Moriond17_B_H.csv";
  const std::string & bTagName 		= "CSVv2";
  const std::string & bTagSys 		= "central"; 
  if(bScale==1) const std::string &bTagSys 		= "up"; 
  if(bScale==-1)const std::string &bTagSys 		= "down"; 
  const std::vector<std::string> & otherSysTypes = {"up", "down"};
  //b-quark
  BTagCalibrationReader readBTagCSV_bM= readCSV(bTagCSVfile, bTagName, BTagEntry::OP_MEDIUM,
    	      "comb", bTagSys, otherSysTypes, BTagEntry::FLAV_B);
  //c-quark
  BTagCalibrationReader readBTagCSV_cM= readCSV(bTagCSVfile, bTagName, BTagEntry::OP_MEDIUM,
    	      "comb", bTagSys, otherSysTypes, BTagEntry::FLAV_C);
  //other(light) quarks and gluon
  BTagCalibrationReader readBTagCSV_lM= readCSV(bTagCSVfile, bTagName, BTagEntry::OP_MEDIUM,
    	      "incl", bTagSys, otherSysTypes, BTagEntry::FLAV_UDSG);
  
  //getBTagEffHistos(f);
  TString histPath("myMiniTreeProducer/Jets/");
  TH2D* h2_BTagEff_Denom_b 		= (TH2D*)(f->Get(histPath+"h2_BTagEff_Denom_b"));
  TH2D* h2_BTagEff_Denom_c 		= (TH2D*)(f->Get(histPath+"h2_BTagEff_Denom_c"));
  TH2D* h2_BTagEff_Denom_udsg 		= (TH2D*)(f->Get(histPath+"h2_BTagEff_Denom_udsg")); 
  TH2D* h2_BTagEff_Num_bM 		= (TH2D*)(f->Get(histPath+"h2_BTagEff_Num_bM"));
  TH2D* h2_BTagEff_Num_cM 		= (TH2D*)(f->Get(histPath+"h2_BTagEff_Num_cM"));
  TH2D* h2_BTagEff_Num_udsgM 		= (TH2D*)(f->Get(histPath+"h2_BTagEff_Num_udsgM")); 
  
  //---------------------------------------------------//
  //CTag SF: read CSV file for SF, 2D histos for eff 
  //---------------------------------------------------//      
  //https://twiki.cern.ch/twiki/bin/view/CMS/BtagRecommendation80XReReco#Data_MC_Scale_Factors_period_dep
  const std::string & cTagCSVfile 		= "stack/ctagger_Moriond17_B_H.csv";
  const std::string & cTagName 			= "cTag";
  const std::string & cTagSys 			= "central"; 
  if(cScale==1) const std::string &cTagSys 		= "up"; 
  if(cScale==-1)const std::string &cTagSys 		= "down"; 
  
  //LOOSE WP
  //b-quark
  BTagCalibrationReader readCTagCSV_bL= readCSV(cTagCSVfile, cTagName, BTagEntry::OP_LOOSE,
    	      "TnP", cTagSys, otherSysTypes, BTagEntry::FLAV_B);
  //c-quark
  BTagCalibrationReader readCTagCSV_cL= readCSV(cTagCSVfile, cTagName, BTagEntry::OP_LOOSE,
    	      "comb", cTagSys, otherSysTypes, BTagEntry::FLAV_C);
  //other(light) quarks and gluon
  BTagCalibrationReader readCTagCSV_lL= readCSV(cTagCSVfile, cTagName, BTagEntry::OP_LOOSE,
    	      "incl", cTagSys, otherSysTypes, BTagEntry::FLAV_UDSG);
  
  //MEDIUM WP
  //b-quark
  BTagCalibrationReader readCTagCSV_bM= readCSV(cTagCSVfile, cTagName, BTagEntry::OP_MEDIUM,
    	      "TnP", cTagSys, otherSysTypes, BTagEntry::FLAV_B);
  //c-quark
  BTagCalibrationReader readCTagCSV_cM= readCSV(cTagCSVfile, cTagName, BTagEntry::OP_MEDIUM,
    	      "comb", cTagSys, otherSysTypes, BTagEntry::FLAV_C);
  //other(light) quarks and gluon
  BTagCalibrationReader readCTagCSV_lM= readCSV(cTagCSVfile, cTagName, BTagEntry::OP_MEDIUM,
    	      "incl", cTagSys, otherSysTypes, BTagEntry::FLAV_UDSG);
  
  //TIGHT WP
  //b-quark
  BTagCalibrationReader readCTagCSV_bT= readCSV(cTagCSVfile, cTagName, BTagEntry::OP_TIGHT,
    	      "TnP", cTagSys, otherSysTypes, BTagEntry::FLAV_B);
  //c-quark
  BTagCalibrationReader readCTagCSV_cT= readCSV(cTagCSVfile, cTagName, BTagEntry::OP_TIGHT,
    	      "comb", cTagSys, otherSysTypes, BTagEntry::FLAV_C);
  //other(light) quarks and gluon
  BTagCalibrationReader readCTagCSV_lT= readCSV(cTagCSVfile, cTagName, BTagEntry::OP_TIGHT,
    	      "incl", cTagSys, otherSysTypes, BTagEntry::FLAV_UDSG);
  
  //getCTagEffHistos(f);
  TH2D* h2_CTagEff_Denom_b 		= (TH2D*)(f->Get(histPath+"h2_CTagEff_Denom_b"));
  TH2D* h2_CTagEff_Denom_c 		= (TH2D*)(f->Get(histPath+"h2_CTagEff_Denom_c"));
  TH2D* h2_CTagEff_Denom_udsg 		= (TH2D*)(f->Get(histPath+"h2_CTagEff_Denom_udsg")); 
  //LOOSE
  TH2D* h2_CTagEff_Num_bL 		= (TH2D*)(f->Get(histPath+"h2_CTagEff_Num_bL"));
  TH2D* h2_CTagEff_Num_cL 		= (TH2D*)(f->Get(histPath+"h2_CTagEff_Num_cL"));
  TH2D* h2_CTagEff_Num_udsgL 		= (TH2D*)(f->Get(histPath+"h2_CTagEff_Num_udsgL")); 
  //MEDIUM
  TH2D* h2_CTagEff_Num_bM 		= (TH2D*)(f->Get(histPath+"h2_CTagEff_Num_bM"));
  TH2D* h2_CTagEff_Num_cM 		= (TH2D*)(f->Get(histPath+"h2_CTagEff_Num_cM"));
  TH2D* h2_CTagEff_Num_udsgM 		= (TH2D*)(f->Get(histPath+"h2_CTagEff_Num_udsgM")); 
  //TIGHT
  TH2D* h2_CTagEff_Num_bT 		= (TH2D*)(f->Get(histPath+"h2_CTagEff_Num_bT"));
  TH2D* h2_CTagEff_Num_cT		= (TH2D*)(f->Get(histPath+"h2_CTagEff_Num_cT"));
  TH2D* h2_CTagEff_Num_udsgT 		= (TH2D*)(f->Get(histPath+"h2_CTagEff_Num_udsgT")); 
  
  //---------------------------------------------------//
  //loop over each event, of the ntuple
  //---------------------------------------------------//
  double kfCount = 0;
  for(int i=0; i<nEntries; ++i){
    Long64_t ientry = evR->LoadTree(i);
    if (ientry < 0) break;
    ev = evR->GetNewEvent(i);
    if(ev==0) continue;
    if(i%1000==0) cout<<"\033[01;32mEvent number = \033[00m"<< i << endl;
    ///if(i > 500) break;
  
    //---------------------------------------------------//
    //apply lumi, k factor and pileup weight
    //---------------------------------------------------//
    double evtWeight = 1.0;
    if(!ev->isData){
      string sampleName = ev->sampleInfo.sampleName;
      //k-factor weight (along with lumi weight) 
      if(sampleName.find("WJetsToLNu") != string::npos || sampleName.find("W1JetsToLNu") != string::npos || sampleName.find("W2JetsToLNu") != string::npos || sampleName.find("W3JetsToLNu") != string::npos || sampleName.find("W4JetsToLNu") != string::npos){
        int hepNUP = ev->sampleInfo.hepNUP;
        double weightK = reweightHEPNUPWJets(hepNUP) * (lumiTotal/1000.0);
        if(i < 1){
        }
        evtWeight *= weightK;  
      }
      else if(sampleName.find("DYJetsToLL") != string::npos || sampleName.find("DY1JetsToLL") != string::npos || sampleName.find("DY2JetsToLL") != string::npos || sampleName.find("DY3JetsToLL") != string::npos || sampleName.find("DY4JetsToLL") != string::npos){
        int hepNUP = ev->sampleInfo.hepNUP;
        std::vector<int> hepIDUP = ev->sampleInfo.hepIDUP;
        std::vector<int> hepISTUP = ev->sampleInfo.hepISTUP;
        int countZ = 0;
        for(size_t p=0; p<hepIDUP.size(); p++){
          if(hepIDUP[p]==23 && hepISTUP[p]==2)
            countZ = countZ + 1;
        }
        if(countZ==0) hepNUP = hepNUP+1;
        double weightK = reweightHEPNUPDYJets(hepNUP) * (lumiTotal/1000.0);
        evtWeight *= weightK;  
        if(i < 1){
        }
      }
      //lumi weight
      else {
      double sampleWeight(1.0);
      sampleWeight = lumiTotal* xss[sampleName]/evtDBS[sampleName];
      //sampleWeight = lumiTotal* xss[sampleName]/initialEvents;
      evtWeight *= sampleWeight; 
      fillHisto(outFile_, cutflowType, "", "LumiScaleFactor", 10, 0, 1000, sampleWeight, 1 );
      }
      //pileup weight
      double weightPU = 1.0;
      vector<double>pu = ev->sampleInfo.truepileup;
      if(pu.size() > 0) {
        float npu = pu[0];
        weightPU = LumiWeights_.weight(npu);
        if(cutflowType.Contains("PileupPlus"))
          weightPU = LumiWeights_Up.weight(npu);
        else if(cutflowType.Contains("PileupMinus"))
          weightPU = LumiWeights_Down.weight(npu);
      evtWeight *= weightPU;  
      }
    } 
    
    //---------------------------------------------------//
    // apply top re-weighting
    // https://twiki.cern.ch/twiki/bin/viewauth/CMS/TopPtReweighting
    //---------------------------------------------------//
    double topPtWt = 1.0;
    if(!ev->isData){
      string sampleName = ev->sampleInfo.sampleName;
      if(sampleName.find("Hplus") != string::npos ||
		      sampleName.find("TTJetsM") != string::npos || 
		      sampleName.find("TTJetsP") != string::npos){
        vector<double>topptweights = ev->sampleInfo.topPtWeights;
        if(topptweights.size() > 0){
            //topPtWt = topptweights[0]; // only sys as recco by HIG convenors
          if(cutflowType.Contains("TopPtPlus"))
            topPtWt = topPtWt*topPtWt;
          else if(cutflowType.Contains("TopPtMinus"))
            topPtWt = 1.0;
        }
      }
    }
    fillHisto(outFile_, cutflowType, "", "SF_topPtWeights", 1000, 0, 3, topPtWt, 1 );
    evtWeight *= topPtWt; //Multiply to the total weights
    
    //---------------------------------------------------//
    //apply muon triggers
    //---------------------------------------------------//
    bool passTrig = false;
    vector<string> trig = ev->hlt;
    for(size_t it = 0; it < trig.size(); it++){
      if(trig[it].find("HLT_IsoMu24") != string::npos) {
        passTrig = true;
      }
    }
    if(!passTrig){
    //cout << "not satisfying trigger" << endl;
      continue;
    }
    nTriggEvent++;
    double nCutPass = 1.0;
    double nCutPass_NonIso = 1.0;
    fillHisto(outFile_, cutflowType+"/Iso", "", "cutflow", 10, 0.5, 10.5, nCutPass, evtWeight );
    fillHisto(outFile_, cutflowType+"/NonIso", "", "cutflow", 10, 0.5, 10.5, nCutPass_NonIso, evtWeight );
   
    //---------------------------------------------------//
    //get all objets e.g. leptons, jets, vertices etc.
    //---------------------------------------------------//
    vector<MyVertex> Vertices = ev->PrimaryVtxs;
    if(Vertices.size() <= 0){
      nVerticesFailCount+=evtWeight;
      cout<<" no vertexes , exit"<<endl;
      continue;
    }
    vector<MyMuon> pfMuons = evR->getMuons(ev, mAlgo);
    vector<MyElectron> pfElectrons = evR->getElectrons(ev, eAlgo);
    vector<MyJet> pfJets = evR->getJets(ev, jAlgo);
    MyMET met = evR->getMET(ev, metAlgo);

    // preselect objects 
    vector<int> m_init; m_init.clear();
    double u1 	= gRandom->Rndm();//used for rochester corrections
    double u2 	= gRandom->Rndm();
    preSelectMuons(&m_init, pfMuons, Vertices[0], ev->isData, u1, u2, 0, 0);
    vector<int> e_init; e_init.clear();
    preSelectElectrons(&e_init, pfElectrons, Vertices[0], isPFlow);
    vector<int> j_init; j_init.clear();
    preSelectJets(jAlgo, &j_init, pfJets, jes, jer);
    
    // clean objects //
    vector<int> e_final; e_final.clear();
    ElectronCleaning( pfElectrons, pfMuons, &e_init, &e_final, &m_init, DRMIN_ELE);
    vector<int> j_final; j_final.clear();
    vector<int> t_final; t_final.clear();
    JetCleaning(pfJets, pfMuons, pfElectrons,  &j_init, &j_final, &m_init, &e_final, DRMIN_JET);
    
    //Get MC partons
    vector<MyLorentzVector> bquarks; bquarks.clear();
    vector<MyLorentzVector> lquarks; lquarks.clear();
    MyLorentzVector mcTop, mcAntiTop;
    mcTop.SetPxPyPzE(0., 0., 0., 0.); mcAntiTop.SetPxPyPzE(0., 0., 0., 0.);
    if(!ev->isData){
      vector<MyMCParticle>allMCParticles = ev->mcParticles;
      for(size_t imc=0; imc < allMCParticles.size(); ++imc){
        if(abs(allMCParticles[imc].pid) == 5 && allMCParticles[imc].mother.size() > 0 && (abs(allMCParticles[imc].mother[0])==6) )
          bquarks.push_back(allMCParticles[imc].p4Gen);
        else if(abs(allMCParticles[imc].pid) <= 4 && allMCParticles[imc].mother.size() > 0 && (abs(allMCParticles[imc].mother[0])==24 || abs(allMCParticles[imc].mother[0])==37) )
          lquarks.push_back(allMCParticles[imc].p4Gen); 
        else if(allMCParticles[imc].pid == 6 && allMCParticles[imc].status == 3)
          mcTop = allMCParticles[imc].p4Gen;
        else if(allMCParticles[imc].pid == -6 && allMCParticles[imc].status == 3)
          mcAntiTop = allMCParticles[imc].p4Gen;
      }
    }
    //---------------------------------------------------//
    //get KinFit objects
    //---------------------------------------------------//
    vector<MyLorentzVector> kfJets; kfJets.clear();
    vector<MyLorentzVector> kfJetsLepB; kfJetsLepB.clear();
    vector<MyLorentzVector> kfLepton; kfLepton.clear();
    vector<MyLorentzVector> kfMet; kfMet.clear();
  
    double chi2OfKinFit=999.;
    double statusOfKinFit=-99;
    double probOfKinFit=-99;
    vector<MyKineFitParticle> allKineFitParticles = ev->KineFitParticles;
    for(size_t imk=0; imk < allKineFitParticles.size(); imk++){
      string labelName = "";
      if(cutflowType.Contains("JESPlus"))labelName="JESUp";
      else if(cutflowType.Contains("JESMinus"))labelName="JESDown";
      else if(cutflowType.Contains("JERPlus"))labelName="JERUp";
      else if(cutflowType.Contains("JERMinus"))labelName="JERDown";
      if(labelName=="JESUp" || labelName=="JESDown" || labelName=="JERUp" ||labelName=="JERDown"){
        if(allKineFitParticles[imk].labelName.find(labelName) != string::npos ){
          if(allKineFitParticles[imk].partName.find("PartonsHadP") != string::npos ||
             allKineFitParticles[imk].partName.find("PartonsHadQ") != string::npos ||
             allKineFitParticles[imk].partName.find("PartonsHadB") != string::npos
             ){
            kfJets.push_back(allKineFitParticles[imk].p4);
          }
          else if(allKineFitParticles[imk].partName.find("Leptons") != string::npos ){
            kfLepton.push_back(allKineFitParticles[imk].p4);
          }
          else if(allKineFitParticles[imk].partName.find("Neutrinos") != string::npos ){
            kfMet.push_back(allKineFitParticles[imk].p4);
          }
          else if(allKineFitParticles[imk].partName.find("PartonsLepB") != string::npos ){
            kfJetsLepB.push_back(allKineFitParticles[imk].p4);
          }
          ///if(imk<1){
          chi2OfKinFit = allKineFitParticles[imk].chi2OfFit;
          statusOfKinFit = allKineFitParticles[imk].statusOfFit;
          probOfKinFit = allKineFitParticles[imk].probOfFit;
	  ///}
        }
      }
      else{
        if(allKineFitParticles[imk].labelName.find("JESUp") == string::npos && allKineFitParticles[imk].labelName.find("JESDown") == string::npos && allKineFitParticles[imk].labelName.find("JERUp") == string::npos && allKineFitParticles[imk].labelName.find("JERDown") == string::npos){
          if(allKineFitParticles[imk].partName.find("PartonsHadP") != string::npos ||
             allKineFitParticles[imk].partName.find("PartonsHadQ") != string::npos ||
             allKineFitParticles[imk].partName.find("PartonsHadB") != string::npos
             ){
            kfJets.push_back(allKineFitParticles[imk].p4);
          }
          else if(allKineFitParticles[imk].partName.find("Leptons") != string::npos ){
            kfLepton.push_back(allKineFitParticles[imk].p4);
          }
          else if(allKineFitParticles[imk].partName.find("Neutrinos") != string::npos ){
            kfMet.push_back(allKineFitParticles[imk].p4);
          }
          else if(allKineFitParticles[imk].partName.find("PartonsLepB") != string::npos ){
            kfJetsLepB.push_back(allKineFitParticles[imk].p4);
          }
          if(imk<1){
            chi2OfKinFit = allKineFitParticles[imk].chi2OfFit;
            statusOfKinFit = allKineFitParticles[imk].statusOfFit;
            probOfKinFit = allKineFitParticles[imk].probOfFit;
          }
        }
      }
    }
    //---------------------------------------------------//
    //apply selection cuts on leptons
    //---------------------------------------------------//
    int nMuon = m_init.size();
    double pri_vtxs = Vertices[0].totVtx;
    if(nMuon != 1)continue;
    //check if 0th muon has mediumMuon ID
    int m_i = m_init[0];
    bool passID = false;
    string input_file(url);
    if(input_file.find("RunG") != string::npos 
		    ||input_file.find("RunH") != string::npos)
	    passID = isMediumMuonGH(&pfMuons[m_i], isPFlow);
    else
	    passID = isMediumMuon(&pfMuons[m_i], isPFlow);
    if(!passID) continue;
    
    //veto 0th muon, if other muons are stroger than the 0th.
    //we veto 0th if it is a fake muon
    if(looseMuonVeto( m_i, pfMuons, isPFlow) ) continue;
    double tmp_iso = pfMuons[m_i].pfRelIso;
     
    //events should not have any electron
    if(looseElectronVeto(-1, pfElectrons, Vertices[0], isPFlow)) continue;
    
    //---------------------------------------------------//
    // Iso(<0.15) and Non-iso(>0.15) region 
    //---------------------------------------------------//
    bool noisofound = false;
    bool isofound = false;
    string cutflowType_(cutflowType);
    if(isIso20){
      if(tmp_iso <= 0.20) cutflowType_ = cutflowType+"/Iso";
      if(tmp_iso > 0.20 && tmp_iso <= 0.4) cutflowType_ = cutflowType+"/NonIso";
    }
    else{
      if(tmp_iso <= 0.15) cutflowType_ = cutflowType+"/Iso";
      if(tmp_iso > 0.15 && tmp_iso <= 0.4) cutflowType_ = cutflowType+"/NonIso";
    }
    double mRelIso = pfMuons[m_i].pfRelIso;
    double muonPt = muPtWithRochCorr(&pfMuons[m_i], ev->isData, u1, u2, 0, 0);

    //---------------------------------------------------//
    //apply muon SF to eventWeights 
    //---------------------------------------------------//
    double lumi_BCDEF = 19711; double lumi_GH = 16146;	
    double lumi = lumi_BCDEF + lumi_GH;
    //trigger 	
    double muSFtrig_BCDEF 	= getMuonTrigSF(h2_trigSF_BCDEF, pfMuons[m_i].p4.eta(), pfMuons[m_i].p4.pt());
    double muSFtrig_GH 		= getMuonTrigSF(h2_trigSF_GH, pfMuons[m_i].p4.eta(), pfMuons[m_i].p4.pt());
    double muSFtrig 		= (muSFtrig_BCDEF*lumi_BCDEF + muSFtrig_GH*lumi_GH)/lumi; 
    //identification
    double muSFid_BCDEF 	= getMuonSF(h2_idSF_BCDEF, pfMuons[m_i].p4.eta(), pfMuons[m_i].p4.pt());
    double muSFid_GH 		= getMuonSF(h2_idSF_GH, pfMuons[m_i].p4.eta(), pfMuons[m_i].p4.pt());
    double muSFid 		= (muSFid_BCDEF*lumi_BCDEF + muSFid_GH*lumi_GH)/lumi; 
    //isolation 
    double muSFiso = 1.0;
    if(tmp_iso < 0.15){
      double muSFiso_BCDEF 	= getMuonSF(h2_isoSF_BCDEF, pfMuons[m_i].p4.eta(), pfMuons[m_i].p4.pt());
      double muSFiso_GH 		= getMuonSF(h2_isoSF_GH, pfMuons[m_i].p4.eta(), pfMuons[m_i].p4.pt());
      muSFiso 		= (muSFiso_BCDEF*lumi_BCDEF + muSFiso_GH*lumi_GH)/lumi; 
    }
    //tracking 
    double muSFtrack_BCDEF 	= getMuonTrackSF(tg_trackSF_BCDEF, pfMuons[m_i].p4.eta()); 
    double muSFtrack_GH 	= getMuonTrackSF(tg_trackSF_GH, pfMuons[m_i].p4.eta()); 
    double muSFtrack 		= (muSFtrack_BCDEF*lumi_BCDEF + muSFtrack_GH*lumi_GH)/lumi;

    //combined SF
    double muSF =1.0;
    if(!ev->isData) muSF = muSFtrig*muSFid*muSFiso*muSFtrack;	
    evtWeight *= muSF;
    double metPt = 0;
    metPt = metWithJESJER(pfJets, &j_final, met, jes, jer);
    Float_t xBinIso_array[] = {0,10,20,30,40,50,60,70,80,90,100,110,120,130,140,150,160,170,180,190,200,210,220,230,240,250,260,270,280,290,300,310,320,330,340,350,360,370,380,390,400,410, 420, 430, 440, 450, 460, 470, 480, 490, 500};
    fillHisto(outFile_, cutflowType, "", "RelIso_1Mu", 50, 0, 3, tmp_iso, evtWeight);
    fillHisto(outFile_, cutflowType, "", "pt_met_1Mu", 100, 0, 1000, metPt, evtWeight );
    fillHisto2D(outFile_, cutflowType, "", "RelIso_MET_1Mu", 100, 0, 1000, metPt, 50, 0, 3, tmp_iso,evtWeight );
    fillTProfile(outFile_, cutflowType, "", "RelIso_MET_TProf_1Mu", 50, xBinIso_array, metPt, tmp_iso, evtWeight); 
    
    if(tmp_iso > 0.4) continue;
    nCutPass++;
    fillHisto(outFile_, cutflowType_, "", "cutflow", 10, 0.5, 10.5, nCutPass, evtWeight );
    
    //---------------------------------------------------//
    // Apply Jet Selection
    //---------------------------------------------------//
    int count_jets = j_final.size();
    if(count_jets < 4)continue;  // events should have 4 or more jets
    nCutPass++;
    fillHisto(outFile_, cutflowType_, "", "cutflow", 10, 0.5, 10.5, nCutPass, evtWeight );
    
    //---------------------------------------------------//
    //apply MET selection   
    //---------------------------------------------------//
    //if(metuc==0)metPt = metWithJESJER(pfJets, &j_final, met, jes, jer);
    //else metPt = metWithUncl(pfJets, &j_final, pfMuons, &m_init, pfElectrons, &e_final, met, metuc);
    
    if(isLowMET){
      if(metPt > minMET) continue;  
    }
    else if(metPt < minMET) continue;  
    nCutPass++;
    fillHisto(outFile_, cutflowType_, "", "cutflow", 10, 0.5, 10.5, nCutPass, evtWeight );
    
    //Transverse mass b/w lepton and MET
    double deltaPhi(0);
    //leptonPt = TMath::Abs(pfMuons[m_i].p4.pt());
    deltaPhi = ROOT::Math::VectorUtil::DeltaPhi(pfMuons[m_i].p4, met.p4);
    double mt = sqrt (  2*muonPt*metPt*(1 - cos(deltaPhi) ) ) ;
    /*
    if(mt < minMT) continue; // mt cut
    nCutPass = 8;
    fillHisto(outFile_, cutflowType_, "", "cutflow", 10, 0.5, 10.5, nCutPass, evtWeight );
    */
    //---------------------------------------------------//
    //apply B-tagging
    //---------------------------------------------------//
    vector<int> j_final_nob; j_final_nob.clear();
    vector<int> j_final_b; j_final_b.clear();
    vector<double> bdiscr; bdiscr.clear();
    double pfCISV = 0.0; //pfCombinedInclusiveSecondaryVertexV2BJetTags
    double pfCMVA = 0.0; //pfCombinedMVAV2BJetTags
    double pfCCvsL = 0.0;//pfCombinedCvsLJetTags
    double pfCCvsB = 0.0; //pfCombinedCvsBJetTags
    //deep CSV
    //double deepCSVb = 0.0;//pfCombinedCvsLJetTags
    //double deepCSVbb = 0.0; //pfCombinedCvsBJetTags
    
    //LOOSE BTAG
    int count_CSVM_SF = 0; 
    ///bool isBtagL = true; bool isBtagM = true; isBtagT = true; 
    bool isBtag = false;
    for(size_t ijet = 0; ijet < j_final.size(); ijet++){
      int ind_jet = j_final[ijet];
      pfCISV = pfJets[ind_jet].bDiscriminator["pfCombinedInclusiveSecondaryVertexV2BJetTags"];
      pfCMVA = pfJets[ind_jet].bDiscriminator["pfCombinedMVAV2BJetTags"];
      //deep CSV
      //deepCSVb= pfJets[ind_jet].bDiscriminator["DeepCSVb"];
      //deepCSVbb = pfJets[ind_jet].bDiscriminator["DeepCSVbb"];
      fillHisto(outFile_, cutflowType_, "BTag", "pfCISV", 100, -2, 2, pfCISV, evtWeight );
      fillHisto(outFile_, cutflowType_, "BTag", "pfCMVA", 100, -2, 2, pfCMVA, evtWeight );
      //deep CSV
      //fillHisto(outFile_, cutflowType_, "BTag", "deepCSVb", 100, -2, 2, deepCSVb, evtWeight );
      //fillHisto(outFile_, cutflowType_, "BTag", "deepCSVbb", 100, -2, 2, deepCSVbb, evtWeight );
      //https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuideBTagMCTools
      //b-quark
      if(abs(pfJets[ind_jet].partonFlavour) ==5)
        isBtag = getBtagWithSF(readBTagCSV_bM, h2_BTagEff_Num_bM, h2_BTagEff_Denom_b, pfJets[ind_jet], ev->isData, bScale); 
      //c-quark
      else if(abs(pfJets[ind_jet].partonFlavour) ==4) 
        isBtag = getBtagWithSF(readBTagCSV_cM, h2_BTagEff_Num_cM, h2_BTagEff_Denom_c, pfJets[ind_jet], ev->isData, bScale); 
      //other quarks and gluon
      else isBtag = getBtagWithSF(readBTagCSV_lM, h2_BTagEff_Num_udsgM, h2_BTagEff_Denom_udsg, pfJets[ind_jet], ev->isData, bScale); 
      if(isBtag){
        count_CSVM_SF++; 
        double jetPt = jetPtWithJESJER(pfJets[ijet], jes, jer);
        fillHisto(outFile_, cutflowType_, "BTag", "pt_bjet", 100, 0, 1000, jetPt, evtWeight );
        fillHisto(outFile_, cutflowType_, "BTag", "eta_bjet", 50, -5, 5, pfJets[ijet].p4.eta(), evtWeight );
        j_final_b.push_back(ind_jet);
        bdiscr.push_back(pfCISV);
      }
      else j_final_nob.push_back(ind_jet); 
    }
    if(count_CSVM_SF <= 1) continue; // Demanding for 2L b-tagged jets
    nCutPass++;
    fillHisto(outFile_, cutflowType_, "", "cutflow", 10, 0.5, 10.5, nCutPass, evtWeight );
    
    //---------------------------------------------------//
    //invariant mass of c sbar
    //---------------------------------------------------//
    //sort j_final_b w.r.t b-discriminator value(ascending order)
    std::map<double, int> bdiscr_sorted_bjets;
    for(unsigned long k=0; k<j_final_b.size(); k++){
      bdiscr_sorted_bjets.insert(pair <double, int> (bdiscr[k],j_final_b[k])); 
    }
    map <double, int> :: iterator bdiscr_itr;
    int index_of_2nd_bjet;
    int index_of_1st_bjet;
    vector<int> index_of_other_bjets;
    int total_bjets = j_final_b.size();
    for(bdiscr_itr = bdiscr_sorted_bjets.begin(); bdiscr_itr != bdiscr_sorted_bjets.end(); ++bdiscr_itr){
       total_bjets --;
       if(total_bjets==1) index_of_2nd_bjet = bdiscr_itr->second;  
       else if(total_bjets==0) index_of_1st_bjet = bdiscr_itr->second;  
       else index_of_other_bjets.push_back(bdiscr_itr->second);
    }
    //mjj will involve 2 non-bjet, highest pt jets
    if(j_final_b.size()==2){
      if(j_final_nob.size() >= 2){
        int index_of_1st_mjj = j_final_nob[0];
        int index_of_2nd_mjj = j_final_nob[1];
        MyLorentzVector diJet = pfJets[index_of_1st_mjj].p4 + pfJets[index_of_2nd_mjj].p4;
        fillHisto(outFile_, cutflowType_, "BTag", "mjj", 100, 0, 500, diJet.M(), evtWeight );
      }
    }
    //Arrange other bjets and non-bjets in pt order in a list
    //mjj will involve 2 highest pt jets in this list
    else{ 
      std::map<double, int> pt_sorted_jets;
      for(unsigned long k=0; k<j_final_nob.size(); k++){
        double pt_of_nobjet = pfJets[j_final_nob[k]].p4.pt(); 
        pt_sorted_jets.insert(pair <double, int> (pt_of_nobjet, j_final_nob[k])); 
      }
      for(unsigned long k=0; k<index_of_other_bjets.size(); k++){
        double pt_of_other = pfJets[index_of_other_bjets[k]].p4.pt();
        pt_sorted_jets.insert(pair <double, int> (pt_of_other, index_of_other_bjets[k])); 
      }
      //select two highest pt jets
      int index_of_1st_mjj = 0;
      int index_of_2nd_mjj = 0;
      int total_jets_for_mjj = pt_sorted_jets.size();
      map <double, int> :: iterator itr_pt;
      for(itr_pt = pt_sorted_jets.begin(); itr_pt != pt_sorted_jets.end(); ++itr_pt){
         total_jets_for_mjj --;
         if(total_jets_for_mjj==1) index_of_2nd_mjj = itr_pt->second;  
         if(total_jets_for_mjj==0) index_of_1st_mjj = itr_pt->second;  
      }
      MyLorentzVector diJet = pfJets[index_of_1st_mjj].p4 + pfJets[index_of_2nd_mjj].p4;
      fillHisto(outFile_, cutflowType_, "BTag", "mjj", 100, 0, 500, diJet.M(), evtWeight );
    }	

    //---------------------------------------------------//
    // add set of plots after BTag:
    //---------------------------------------------------//
    //fillHisto("pt_mu", cutflowType_+"/BTag", pfMuons[m_i].p4.pt(), evtWeight);
    fillHisto(outFile_, cutflowType_, "BTag","pt_mu", 100, 0, 1000, muonPt, evtWeight );
    fillHisto(outFile_, cutflowType_, "BTag","eta_mu", 50, -5, 5, pfMuons[m_i].p4.eta(), evtWeight );
    fillHisto(outFile_, cutflowType_, "BTag","phi_mu", 50, -5, 5, pfMuons[m_i].p4.phi(), evtWeight );
    fillHisto(outFile_, cutflowType_, "BTag","final_RelIso_mu", 100, 0, 3, mRelIso, evtWeight );
    for(size_t ijet = 0; ijet < j_final.size(); ijet++){
      int ind_jet = j_final[ijet];
      double jetPt = jetPtWithJESJER(pfJets[ind_jet], jes, jer);
      fillHisto(outFile_, cutflowType_, "BTag","pt_jet", 100, 0, 1000, jetPt, evtWeight );
      fillHisto(outFile_, cutflowType_, "BTag","eta_jet", 50, -5, 5, pfJets[ind_jet].p4.eta(), evtWeight );
      fillHisto(outFile_, cutflowType_, "BTag","phi_jet", 50, -5, 5, pfJets[ind_jet].p4.phi(), evtWeight );
    }
    fillHisto(outFile_, cutflowType_, "BTag","final_multi_jet", 15, 0.5, 15.5, count_jets, evtWeight );
    fillHisto(outFile_, cutflowType_, "BTag", "CSVL_count", 10, 0.5, 10.5, count_CSVM_SF, evtWeight );
    fillHisto(outFile_, cutflowType_, "BTag","final_pt_met", 100, 0, 1000, metPt, evtWeight );
    fillHisto(outFile_, cutflowType_, "BTag","wmt", 100, 0, 1000, mt, evtWeight );
    fillHisto(outFile_, cutflowType_, "BTag","nvtx", 100, 0, 100, pri_vtxs, evtWeight );
    for(std::size_t n=0; n<Vertices.size(); n++){
      fillHisto(outFile_, cutflowType_, "BTag","rhoAll", 100, 0, 100, Vertices[n].rhoAll, evtWeight );
    }
    fillHisto(outFile_, cutflowType_, "BTag", "chi2OfKinFit", 100, 0, 100, chi2OfKinFit, evtWeight );
    fillHisto(outFile_, cutflowType_, "BTag", "probOfKinFit", 100, 0, 3, probOfKinFit, evtWeight );
    input_count++;
    if(input_count%100==0)
    cout << "input count iso: "<< input_count << endl;
  

    //kkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkk//
    // 		add set of plots after KinFit: 		    //
    //kkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkk//
    //make sure that the fit converges 
    if(statusOfKinFit !=0) continue ; 
  
    //---------------------------------------------------//
    //get KF muon by matching with PF muons
    //---------------------------------------------------//
    bool foundkfMuon = false;
    double dR =DeltaR(pfMuons[m_i].p4 , kfLepton[0]);
    if(kfLepton.size()>0){
      if(dR< 0.2)foundkfMuon = true;
    }
    if(kfLepton[0].pt() < 26) 	continue;
    if(!foundkfMuon) continue; 
    
    //---------------------------------------------------//
    //Apply same Pt selections on PF and KF jets
    //---------------------------------------------------//
    if(kfJets[0].pt() < 25) 	continue;
    if(kfJets[1].pt() < 25) 	continue;
    if(kfJets[2].pt() < 25) 	continue;
    if(kfJetsLepB[0].pt() < 25) continue;
    
    //---------------------------------------------------//
    //select maximum b-tag discriminator jet in KF
    //---------------------------------------------------//
    unsigned long maxBtagJet = -1;
    double maxBDiscr = -999.;
    int count_kfJets = 0;
    for(unsigned long ik = 0; ik < kfJets.size(); ik++){
      for(size_t ij = 0; ij < j_final.size(); ij++){
        int ind_ij = j_final[ij];
        if(DeltaR(kfJets[ik], pfJets[ind_ij].p4) < 0.2){
          double discr = pfJets[ind_ij].bDiscriminator["pfCombinedInclusiveSecondaryVertexV2BJetTags"];
          if(discr > maxBDiscr){
            maxBDiscr = discr;
            maxBtagJet = ik;
          }
        }
      }
    }
    //---------------------------------------------------//
    //make sure that each event has 2 light jets
    //---------------------------------------------------//
    vector<MyLorentzVector> kfLightJets; kfLightJets.clear();
    unsigned long zero = 0; 
    double pt_bjetHad = 0;
    if(kfJets.size() >=3 && maxBtagJet >= zero){
      for(unsigned long ik = 0; ik < kfJets.size(); ik++){
        if(ik != maxBtagJet)kfLightJets.push_back(kfJets[ik]);
	else pt_bjetHad = kfJets[ik].pt();
      }
    }
    if(kfLightJets.size() < 2) continue; 
    bool match_j1 = false, match_j2 = false;
    int indexForCTag0 = 0, indexForCTag1 = 0;
    for(size_t ij = 0; ij < j_final.size(); ij++){
      int ind_ij = j_final[ij];
      if(DeltaR(kfLightJets[0], pfJets[ind_ij].p4) < 0.2){
        match_j1=true;
        indexForCTag0 = ind_ij;
      }
      if(DeltaR(kfLightJets[1], pfJets[ind_ij].p4) < 0.2){
        match_j2=true;
        indexForCTag1 = ind_ij;
      }
    }
    //---------------------------------------------------//
    //fill histos after c, sbar are found
    //---------------------------------------------------//
    if(!match_j1) continue;
    if(!match_j2) continue;
    kfCount++;
    nCutPass++;
    fillHisto(outFile_, cutflowType_, "", "cutflow", 10, 0.5, 10.5, nCutPass, evtWeight );
    MyLorentzVector diJet = kfLightJets[0]+kfLightJets[1];
    fillHisto(outFile_, cutflowType_, "KinFit", "mjj_kfit", 100, 0, 500, diJet.mass(), evtWeight );
    fillHisto(outFile_, cutflowType_, "KinFit","pt_bjetH", 100, 0, 1000, pt_bjetHad, evtWeight );
    fillHisto(outFile_, cutflowType_, "KinFit","pt_bjetL", 100, 0, 1000, kfJetsLepB[0].pt(), evtWeight );
    Float_t xBin_array[] = {25,  42,  57,  74,  99,  500};
    fillTProfile(outFile_, cutflowType_, "PtbJetInc", "mjj_kfit_pt_bjetH", 5, xBin_array, pt_bjetHad, diJet.mass(), evtWeight); 

    ////////////////////////////////////////////////////
    /// bin by bin Mjj vs Pt_bjetH 
    if(pt_bjetHad >= 25 && pt_bjetHad < 42)
      fillHisto(outFile_, cutflowType_, "PtbJetInc", "mjj_kfit_25To42", 100, 0, 500, diJet.mass(), evtWeight );
    if(pt_bjetHad >= 42 && pt_bjetHad < 57)
      fillHisto(outFile_, cutflowType_, "PtbJetInc", "mjj_kfit_42To57", 100, 0, 500, diJet.mass(), evtWeight );
    if(pt_bjetHad >= 57 && pt_bjetHad < 74)
      fillHisto(outFile_, cutflowType_, "PtbJetInc", "mjj_kfit_57To74", 100, 0, 500, diJet.mass(), evtWeight );
    if(pt_bjetHad >= 74 && pt_bjetHad < 99)
      fillHisto(outFile_, cutflowType_, "PtbJetInc", "mjj_kfit_74To99", 100, 0, 500, diJet.mass(), evtWeight );
    if(pt_bjetHad >= 99 && pt_bjetHad < 500)
      fillHisto(outFile_, cutflowType_, "PtbJetInc", "mjj_kfit_99To500", 100, 0, 500, diJet.mass(), evtWeight );
    ////////////////////////////////////////////////////
    
    //---------------------------------------------------//
    //apply CTagging
    //---------------------------------------------------//
    double pfCCvsL0 = pfJets[indexForCTag0].bDiscriminator["pfCombinedCvsLJetTags"];
    double pfCCvsL1 = pfJets[indexForCTag1].bDiscriminator["pfCombinedCvsLJetTags"];
    double pfCCvsB0 = pfJets[indexForCTag0].bDiscriminator["pfCombinedCvsBJetTags"]; 
    double pfCCvsB1 = pfJets[indexForCTag1].bDiscriminator["pfCombinedCvsBJetTags"];
    fillHisto(outFile_, cutflowType_, "KinFit", "pfCCvsL", 100, -2, 2, pfCCvsL0, evtWeight );
    fillHisto(outFile_, cutflowType_, "KinFit", "pfCCvsL", 100, -2, 2, pfCCvsL1, evtWeight );
    fillHisto(outFile_, cutflowType_, "KinFit", "pfCCvsB", 100, -2, 2, pfCCvsB0, evtWeight );
    fillHisto(outFile_, cutflowType_, "KinFit", "pfCCvsB", 100, -2, 2, pfCCvsB1, evtWeight );
    
    bool isCTagL = false; //loose
    bool isCTagM = false; //medium
    bool isCTagT = false; //tight
    //https://twiki.cern.ch/twiki/bin/viewauth/CMS/BtagRecommendation80XReReco
    Float_t dCvsL_L = -0.48;
    Float_t dCvsB_L = -0.17;
    Float_t dCvsL_M = -0.1;
    Float_t dCvsB_M = -0.08;
    Float_t dCvsL_T =  0.69;
    Float_t dCvsB_T = -0.45;
    if((pfCCvsL0 > -0.48  &&  pfCCvsB0 > -0.17) ||(pfCCvsL1 > -0.48 && pfCCvsB1 > -0.17))isCTagL = true;
    if((pfCCvsL0 > -0.1  && pfCCvsB0 > 0.08) ||(pfCCvsL1 > -0.1 && pfCCvsB1 > 0.08))isCTagM = true;
    if((pfCCvsL0 > 0.69  && pfCCvsB0 > -0.45) ||(pfCCvsL1 > 0.69  && pfCCvsB1 > -0.45))isCTagT = true;
    //loose, medium, tight
    if(isCTagL)fillHisto(outFile_, cutflowType_, "KinFit", "mjj_kfit_CTagL", 100, 0, 500, diJet.mass(), evtWeight );
    if(isCTagM)fillHisto(outFile_, cutflowType_, "KinFit", "mjj_kfit_CTagM", 100, 0, 500, diJet.mass(), evtWeight );
    if(isCTagT)fillHisto(outFile_, cutflowType_, "KinFit", "mjj_kfit_CTagT", 100, 0, 500, diJet.mass(), evtWeight );
    
    //---------------------------------------------------//
    //Charm mistag scale factors 
    //---------------------------------------------------//
    bool isCTagL_SF_0 = false;
    bool isCTagM_SF_0 = false;
    bool isCTagT_SF_0 = false;
    //https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuideBTagMCTools
    //get scale factor for 0th jet
    //b-quark
    if(abs(pfJets[indexForCTag0].partonFlavour) ==5){
      isCTagL_SF_0 = getCTagWithSF(readCTagCSV_bL, h2_CTagEff_Num_bL, h2_CTagEff_Denom_b, dCvsL_L, dCvsB_L, pfJets[indexForCTag0], ev->isData, cScale); 
      isCTagM_SF_0 = getCTagWithSF(readCTagCSV_bM, h2_CTagEff_Num_bM, h2_CTagEff_Denom_b, dCvsL_M, dCvsB_M, pfJets[indexForCTag0], ev->isData, cScale); 
      isCTagT_SF_0 = getCTagWithSF(readCTagCSV_bT, h2_CTagEff_Num_bT, h2_CTagEff_Denom_b, dCvsL_T, dCvsB_T, pfJets[indexForCTag0], ev->isData, cScale); 
    }
    //c-quark
    else if(abs(pfJets[indexForCTag0].partonFlavour) ==4){ 
      isCTagL_SF_0 = getCTagWithSF(readCTagCSV_cL, h2_CTagEff_Num_cL, h2_CTagEff_Denom_c, dCvsL_L, dCvsB_L, pfJets[indexForCTag0], ev->isData, cScale); 
      isCTagM_SF_0 = getCTagWithSF(readCTagCSV_cM, h2_CTagEff_Num_cM, h2_CTagEff_Denom_c, dCvsL_M, dCvsB_M, pfJets[indexForCTag0], ev->isData, cScale); 
      isCTagT_SF_0 = getCTagWithSF(readCTagCSV_cT, h2_CTagEff_Num_cT, h2_CTagEff_Denom_c, dCvsL_T, dCvsB_T, pfJets[indexForCTag0], ev->isData, cScale); 
    }
    //other quarks and gluon
    else{
    isCTagL_SF_0 = getCTagWithSF(readCTagCSV_lL, h2_CTagEff_Num_udsgL, h2_CTagEff_Denom_udsg, dCvsL_L, dCvsB_L, pfJets[indexForCTag0], ev->isData, cScale); 
    isCTagM_SF_0 = getCTagWithSF(readCTagCSV_lM, h2_CTagEff_Num_udsgM, h2_CTagEff_Denom_udsg, dCvsL_M, dCvsB_M, pfJets[indexForCTag0], ev->isData, cScale); 
    isCTagT_SF_0 = getCTagWithSF(readCTagCSV_lT, h2_CTagEff_Num_udsgT, h2_CTagEff_Denom_udsg, dCvsL_T, dCvsB_T, pfJets[indexForCTag0], ev->isData, cScale); 
    }
   
    bool isCTagL_SF_1 = false;
    bool isCTagM_SF_1 = false;
    bool isCTagT_SF_1 = false;
    //get scale factor for 1st jet
    //b-quark
    if(abs(pfJets[indexForCTag1].partonFlavour) ==5){
      isCTagL_SF_1 = getCTagWithSF(readCTagCSV_bL, h2_CTagEff_Num_bL, h2_CTagEff_Denom_b, dCvsL_L, dCvsB_L, pfJets[indexForCTag1], ev->isData, cScale); 
      isCTagM_SF_1 = getCTagWithSF(readCTagCSV_bM, h2_CTagEff_Num_bM, h2_CTagEff_Denom_b, dCvsL_M, dCvsB_M, pfJets[indexForCTag1], ev->isData, cScale); 
      isCTagT_SF_1 = getCTagWithSF(readCTagCSV_bT, h2_CTagEff_Num_bT, h2_CTagEff_Denom_b, dCvsL_T, dCvsB_T, pfJets[indexForCTag1], ev->isData, cScale); 
    }
    //c-quark
    else if(abs(pfJets[indexForCTag1].partonFlavour) ==4){ 
      isCTagL_SF_1 = getCTagWithSF(readCTagCSV_cL, h2_CTagEff_Num_cL, h2_CTagEff_Denom_c, dCvsL_L, dCvsB_L, pfJets[indexForCTag1], ev->isData, cScale); 
      isCTagM_SF_1 = getCTagWithSF(readCTagCSV_cM, h2_CTagEff_Num_cM, h2_CTagEff_Denom_c, dCvsL_M, dCvsB_M, pfJets[indexForCTag1], ev->isData, cScale); 
      isCTagT_SF_1 = getCTagWithSF(readCTagCSV_cT, h2_CTagEff_Num_cT, h2_CTagEff_Denom_c, dCvsL_T, dCvsB_T, pfJets[indexForCTag1], ev->isData, cScale); 
    }
    //other quarks and gluon
    else{
    isCTagL_SF_1 = getCTagWithSF(readCTagCSV_lL, h2_CTagEff_Num_udsgL, h2_CTagEff_Denom_udsg, dCvsL_L, dCvsB_L, pfJets[indexForCTag1], ev->isData, cScale); 
    isCTagM_SF_1 = getCTagWithSF(readCTagCSV_lM, h2_CTagEff_Num_udsgM, h2_CTagEff_Denom_udsg, dCvsL_M, dCvsB_M, pfJets[indexForCTag1], ev->isData, cScale); 
    isCTagT_SF_1 = getCTagWithSF(readCTagCSV_lT, h2_CTagEff_Num_udsgT, h2_CTagEff_Denom_udsg, dCvsL_T, dCvsB_T, pfJets[indexForCTag1], ev->isData, cScale); 
    }

    //combined scale factors
    bool isCTagL_SF = false;
    bool isCTagM_SF = false;
    bool isCTagT_SF = false;
    bool isCTagOther_SF = false;
    if(isCTagL_SF_0 || isCTagL_SF_1) isCTagL_SF = true;
    if(isCTagM_SF_0 || isCTagM_SF_1) isCTagM_SF=true; 
    if(isCTagT_SF_0 || isCTagT_SF_1) isCTagT_SF = true;
    if(!isCTagL_SF)if(!isCTagM_SF) if(!isCTagT_SF) isCTagOther_SF = true;
    
    if(isCTagL_SF) fillHisto(outFile_, cutflowType_, "KinFit", "mjj_kfit_CTagL_SF", 100, 0, 500, diJet.mass(), evtWeight );
    if(isCTagM_SF) fillHisto(outFile_, cutflowType_, "KinFit", "mjj_kfit_CTagM_SF", 100, 0, 500, diJet.mass(), evtWeight );
    if(isCTagT_SF) fillHisto(outFile_, cutflowType_, "KinFit", "mjj_kfit_CTagT_SF", 100, 0, 500, diJet.mass(), evtWeight );
  
    //Categorisation 
    if(isCTagT_SF){ 
      fillTProfile(outFile_, cutflowType_, "PtbJetCatT", "mjj_kfit_pt_bjetH", 5, xBin_array, pt_bjetHad, diJet.mass(), evtWeight); 
      fillHisto(outFile_, cutflowType_, "KinFit","pt_bjetH_CatT", 100, 0, 1000, pt_bjetHad, evtWeight );
      fillHisto(outFile_, cutflowType_, "KinFit", "mjj_kfit_CTagT_SF_Cat", 100, 0, 500, diJet.mass(), evtWeight );
      if(pt_bjetHad >= 25 && pt_bjetHad < 42)
        fillHisto(outFile_, cutflowType_, "PtbJetCatT", "mjj_kfit_25To42", 100, 0, 500, diJet.mass(), evtWeight );
      if(pt_bjetHad >= 42 && pt_bjetHad < 57)
        fillHisto(outFile_, cutflowType_, "PtbJetCatT", "mjj_kfit_42To57", 100, 0, 500, diJet.mass(), evtWeight );
      if(pt_bjetHad >= 57 && pt_bjetHad < 74)
        fillHisto(outFile_, cutflowType_, "PtbJetCatT", "mjj_kfit_57To74", 100, 0, 500, diJet.mass(), evtWeight );
      if(pt_bjetHad >= 74 && pt_bjetHad < 99)
        fillHisto(outFile_, cutflowType_, "PtbJetCatT", "mjj_kfit_74To99", 100, 0, 500, diJet.mass(), evtWeight );
      if(pt_bjetHad >= 99 && pt_bjetHad < 500)
        fillHisto(outFile_, cutflowType_, "PtbJetCatT", "mjj_kfit_99To500", 100, 0, 500, diJet.mass(), evtWeight );
      }
    
    else if(isCTagM_SF){ 
      fillTProfile(outFile_, cutflowType_, "PtbJetCatM", "mjj_kfit_pt_bjetH", 5, xBin_array, pt_bjetHad, diJet.mass(), evtWeight); 
      fillHisto(outFile_, cutflowType_, "KinFit","pt_bjetH_CatM", 100, 0, 1000, pt_bjetHad, evtWeight );
      fillHisto(outFile_, cutflowType_, "KinFit", "mjj_kfit_CTagM_SF_Cat", 100, 0, 500, diJet.mass(), evtWeight );
      if(pt_bjetHad >= 25 && pt_bjetHad < 42)
        fillHisto(outFile_, cutflowType_, "PtbJetCatM", "mjj_kfit_25To42", 100, 0, 500, diJet.mass(), evtWeight );
      if(pt_bjetHad >= 42 && pt_bjetHad < 57)
        fillHisto(outFile_, cutflowType_, "PtbJetCatM", "mjj_kfit_42To57", 100, 0, 500, diJet.mass(), evtWeight );
      if(pt_bjetHad >= 57 && pt_bjetHad < 74)
        fillHisto(outFile_, cutflowType_, "PtbJetCatM", "mjj_kfit_57To74", 100, 0, 500, diJet.mass(), evtWeight );
      if(pt_bjetHad >= 74 && pt_bjetHad < 99)
        fillHisto(outFile_, cutflowType_, "PtbJetCatM", "mjj_kfit_74To99", 100, 0, 500, diJet.mass(), evtWeight );
      if(pt_bjetHad >= 99 && pt_bjetHad < 500)
        fillHisto(outFile_, cutflowType_, "PtbJetCatM", "mjj_kfit_99To500", 100, 0, 500, diJet.mass(), evtWeight );
    }

    else if(isCTagL_SF){ 
      fillTProfile(outFile_, cutflowType_, "PtbJetCatL", "mjj_kfit_pt_bjetH", 5, xBin_array, pt_bjetHad, diJet.mass(), evtWeight); 
      fillHisto(outFile_, cutflowType_, "KinFit","pt_bjetH_CatL", 100, 0, 1000, pt_bjetHad, evtWeight );
      fillHisto(outFile_, cutflowType_, "KinFit", "mjj_kfit_CTagL_SF_Cat", 100, 0, 500, diJet.mass(), evtWeight );
      if(pt_bjetHad >= 25 && pt_bjetHad < 42)
        fillHisto(outFile_, cutflowType_, "PtbJetCatL", "mjj_kfit_25To42", 100, 0, 500, diJet.mass(), evtWeight );
      if(pt_bjetHad >= 42 && pt_bjetHad < 57)
        fillHisto(outFile_, cutflowType_, "PtbJetCatL", "mjj_kfit_42To57", 100, 0, 500, diJet.mass(), evtWeight );
      if(pt_bjetHad >= 57 && pt_bjetHad < 74)
        fillHisto(outFile_, cutflowType_, "PtbJetCatL", "mjj_kfit_57To74", 100, 0, 500, diJet.mass(), evtWeight );
      if(pt_bjetHad >= 74 && pt_bjetHad < 99)
        fillHisto(outFile_, cutflowType_, "PtbJetCatL", "mjj_kfit_74To99", 100, 0, 500, diJet.mass(), evtWeight );
      if(pt_bjetHad >= 99 && pt_bjetHad < 500)
        fillHisto(outFile_, cutflowType_, "PtbJetCatL", "mjj_kfit_99To500", 100, 0, 500, diJet.mass(), evtWeight );
    }
    else{
      fillTProfile(outFile_, cutflowType_, "PtbJetCatO", "mjj_kfit_pt_bjetH", 5, xBin_array, pt_bjetHad, diJet.mass(), evtWeight); 
      fillHisto(outFile_, cutflowType_, "KinFit","pt_bjetH_CatO", 100, 0, 1000, pt_bjetHad, evtWeight );
      fillHisto(outFile_, cutflowType_, "KinFit", "mjj_kfit_CTagO_SF_Cat", 100, 0, 500, diJet.mass(), evtWeight );
      if(pt_bjetHad >= 25 && pt_bjetHad < 42)
        fillHisto(outFile_, cutflowType_, "PtbJetCatO", "mjj_kfit_25To42", 100, 0, 500, diJet.mass(), evtWeight );
      if(pt_bjetHad >= 42 && pt_bjetHad < 57)
        fillHisto(outFile_, cutflowType_, "PtbJetCatO", "mjj_kfit_42To57", 100, 0, 500, diJet.mass(), evtWeight );
      if(pt_bjetHad >= 57 && pt_bjetHad < 74)
        fillHisto(outFile_, cutflowType_, "PtbJetCatO", "mjj_kfit_57To74", 100, 0, 500, diJet.mass(), evtWeight );
      if(pt_bjetHad >= 74 && pt_bjetHad < 99)
        fillHisto(outFile_, cutflowType_, "PtbJetCatO", "mjj_kfit_74To99", 100, 0, 500, diJet.mass(), evtWeight );
      if(pt_bjetHad >= 99 && pt_bjetHad < 500)
        fillHisto(outFile_, cutflowType_, "PtbJetCatO", "mjj_kfit_99To500", 100, 0, 500, diJet.mass(), evtWeight );
    }
    
    //if(!isCTagL_SF) continue; 
    if(isCTagL_SF){
    nCutPass++;
    fillHisto(outFile_, cutflowType_, "", "cutflow", 10, 0.5, 10.5, nCutPass, evtWeight );
    }
    fillHisto(outFile_, cutflowType_, "KinFit","pt_mu", 100, 0, 1000, muonPt, evtWeight );
    fillHisto(outFile_, cutflowType_, "KinFit","eta_mu", 50, -5, 5, pfMuons[m_i].p4.eta(), evtWeight );
    fillHisto(outFile_, cutflowType_, "KinFit","phi_mu", 50, -5, 5, pfMuons[m_i].p4.phi(), evtWeight );
    fillHisto(outFile_, cutflowType_, "KinFit","final_RelIso_mu", 100, 0, 1, mRelIso, evtWeight );
    for(size_t ijet = 0; ijet < j_final.size(); ijet++){
      int ind_jet = j_final[ijet];
      double jetPt = jetPtWithJESJER(pfJets[ind_jet], jes, jer);
      fillHisto(outFile_, cutflowType_, "KinFit","pt_jet", 100, 0, 1000, jetPt, evtWeight );
      fillHisto(outFile_, cutflowType_, "KinFit","eta_jet", 50, -5, 5, pfJets[ind_jet].p4.eta(), evtWeight );
      fillHisto(outFile_, cutflowType_, "KinFit","phi_jet", 50, -5, 5, pfJets[ind_jet].p4.phi(), evtWeight );
    }
    for( std::size_t n=0; n<Vertices.size(); n++){
      fillHisto(outFile_, cutflowType_, "KinFit","rhoAll", 100, 0, 100, Vertices[n].rhoAll, evtWeight );
    }
    fillHisto(outFile_, cutflowType_, "KinFit","final_multi_jet", 15, 0.5, 15.5, count_jets, evtWeight );
    fillHisto(outFile_, cutflowType_, "KinFit", "CSVL_count", 10, 0.5, 10.5, count_CSVM_SF, evtWeight );
    fillHisto(outFile_, cutflowType_, "KinFit","final_pt_met", 100, 0, 1000, metPt, evtWeight );
    fillHisto(outFile_, cutflowType_, "KinFit","wmt", 100, 0, 1000, mt, evtWeight );
    fillHisto(outFile_, cutflowType_, "KinFit","nvtx", 100, 0, 100, pri_vtxs, evtWeight );
    
    //---------------------------------------------------//
    // cuts on chi2 and prob of KinFit
    //---------------------------------------------------//
    if(probOfKinFit > 0.1){
      if(chi2OfKinFit <10)
      fillHisto(outFile_, cutflowType_, "KinFit", "mjj_kfit_Chi10", 100, 0, 500, diJet.mass(), evtWeight );
      if(chi2OfKinFit <1)
      fillHisto(outFile_, cutflowType_, "KinFit", "mjj_kfit_Chi01", 100, 0, 500, diJet.mass(), evtWeight );
      if(chi2OfKinFit <0.1)
      fillHisto(outFile_, cutflowType_, "KinFit", "mjj_kfit_Chi0p1", 100, 0, 500, diJet.mass(), evtWeight );
    }
  }//event loop
  cout<<"kfCount = "<<kfCount<<endl;
  f->Close(); 
  delete f;
}

void hplusAnalyzer::processEvents(){ 
  
  //Data, MC sample from lxplus and T2
  ///CutFlowAnalysis("TTJetsP_MuMC_20171104_Ntuple_1.root", "PF", ""); 
  //CutFlowAnalysis("outFile_muCh.root", "PF", ""); 
  //CutFlowAnalysis("root://se01.indiacms.res.in:1094/", "PF", "");

  //CutFlowAnalysis("root://se01.indiacms.res.in:1094//cms/store/user/rverma/ntuple_MuMC_kfitM_20180418/MuMC_20180418/TTJetsP_MuMC_20180418/TT_TuneCUETP8M2T4_13TeV-powheg-pythia8/TTJetsP_MuMC_20180418/180418_182435/0000/TTJetsP_MuMC_20180418_Ntuple_1.root", "PF", "");


  CutFlowAnalysis("HplusM100_MuMC_20180418_Ntuple_8.root", "PF", ""); 
  //CutFlowAnalysis("MuRunB2v2_MuData_20180421_Ntuple_67.root", "PF", ""); 
  //CutFlowAnalysis("root://se01.indiacms.res.in:1094//cms/store/user/rverma/ntuple_MuData_kfitM_20180421/MuData_20180421/MuRunB2v2_MuData_20180421/SingleMuon/MuRunB2v2_MuData_20180421/180421_151510/0000/MuRunB2v2_MuData_20180421_Ntuple_67.root", "PF", "");



  //====================================
  //condor submission
  //CutFlowAnalysis("root://se01.indiacms.res.in:1094/inputFile", "PF", "outputFile");
  //====================================
} 
