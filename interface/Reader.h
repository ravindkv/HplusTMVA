#ifndef _reader_h_
#define _reader_h_

#if !defined(__CINT__) || defined(__MAKECINT__)

#include "TROOT.h"
#include <string>
#include <iostream>
#include <map>
#include <algorithm>

#include "TSystem.h"
#include "TFile.h"
#include "TCanvas.h"
#include "THStack.h"
#include "TObject.h"
#include "TString.h"
#include "TObjArray.h"
#include "TH2.h"
#include "TMath.h"
#include "TGraphAsymmErrors.h"
#include "TH1D.h"
#include "TLegend.h"
#include "TPaveText.h"
#include "TTree.h"
#include "TLorentzVector.h"
#include "TTree.h"
#include "TChain.h"
#include "TClonesArray.h"
#include "TVectorD.h"
#include "TFractionFitter.h"

#ifdef _STANDALONE
#include "MyEvent.h"
#else
#include "interface/MyEvent.h"
#endif

#endif

using namespace std;

class Reader
{
 public:
  Reader() { }
 virtual ~Reader() { }
 ///~Reader() { }
  
  unsigned int AssignEventTreeFrom(TFile *f, TString path = "myMiniTreeProducer");
  unsigned int AssignEventTreeFromList(const char *file_list_name, TString path = "myMiniTreeProducer"); //for more than one files
  
  MyEvent *GetNewEvent(unsigned int ientry);
  MyEvent *GetNewEventFromList(unsigned int ientry); //for more than one files

  Long64_t LoadTree(Long64_t entry);

  vector<MyJet> getJets(MyEvent* ev, string algo);
  vector<MyElectron> getElectrons(MyEvent* ev, string algo);
  vector<MyMuon> getMuons(MyEvent* ev, string algo);
  MyMET getMET(MyEvent* ev, string algo);

 private :
  TTree *myTree;
  //TChain *chain;
  MyEvent *myEvent;
  
  ClassDef(Reader,1)
};
#endif
