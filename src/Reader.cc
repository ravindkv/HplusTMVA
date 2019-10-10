#include "interface/Reader.h"

ClassImp(Reader)

using namespace std;

unsigned int Reader::AssignEventTreeFrom(TFile *f, TString path)
{
  
  if(f==0) return 0;
  
  myTree = (TTree *) f->Get( path + "/" + "MyTree" );
  TTree *t = myTree;
  unsigned int nEntries = t->GetEntriesFast();
  if(nEntries==0) return 0;
  cout<<"============================"<<endl;
  cout<<" Total events = "<<nEntries<<endl;
  cout<<"============================"<<endl;
  myEvent = new MyEvent;
  
  myEvent = 0; t->GetBranch("MyEvent")->SetAddress(&myEvent);
  
  
  return nEntries;
}

unsigned int Reader::AssignEventTreeFromList(const char *file_list_name, TString path)
{
  int nfiles;
  char tex[200], list_name[100];
  FILE *filelist;

  // get filelist name
  if( file_list_name!=NULL && strcmp(file_list_name, "") )
    strcpy(list_name, file_list_name);
  else strcpy(list_name, "file.list");
  printf("Reading file.list = %s\n", list_name);
  filelist = fopen(list_name, "r");
  nfiles = 0;
  TChain *chain = new TChain( path + "/" + "MyTree");
  while( !feof(filelist) )
    {
      fscanf(filelist, "%s\n", tex);
      if( strcmp(tex,"//")==0 ) break;
      //printf("%s\n", tex);
      chain->Add(tex);
      nfiles++;
      //if( nfiles==nmax ) break;
    }
  printf("%d files\n", nfiles);
  
  if(!chain) return 0;
  myTree = chain;
  myEvent = new MyEvent;
  
  //myEvent = 0; chain->GetBranch("MyEvent")->SetAddress(&myEvent);
  myTree->SetBranchAddress("MyEvent", &myEvent);
  
  unsigned int nEntries = myTree->GetEntries();
  if(nEntries==0) return 0;
  cout<<" nEntries "<<nEntries<<endl;
  return nEntries;
}

MyEvent *Reader::GetNewEvent(unsigned int ientry)
{
  
  TTree *t = myTree;
  
  MyEvent *ev = myEvent;
  if(t==0 || ev==0) return 0;
  
  //check number of entries in tree
  if(ientry >= t->GetEntriesFast()) return 0;
  
  //fill the mini event
  t->GetEntry(ientry);
  return ev;
}

MyEvent *Reader::GetNewEventFromList(unsigned int ientry)
{
  
  TTree *t = myTree;
  
  MyEvent *ev = myEvent;
  if(t==0 || ev==0) return 0;
  
  //check number of entries in tree
  if(ientry >= t->GetEntries()) return 0;
  
  //fill the mini event
  t->GetEvent(ientry);
  return ev;
}

Long64_t Reader::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!myTree) return -5;
   Long64_t centry = myTree->LoadTree(entry);
   if (centry < 0) return centry;
   return centry;
}

vector<MyElectron> Reader::getElectrons(MyEvent* ev, string algo)
{
  vector<MyElectron> selElectrons;
  selElectrons.clear();
  vector<MyElectron> allElectrons = ev->Electrons;
  for(size_t iele=0; iele < allElectrons.size(); ++iele){
      selElectrons.push_back(allElectrons[iele]);
  }
  return selElectrons;
}

vector<MyMuon> Reader::getMuons(MyEvent* ev, string algo)
{
  vector<MyMuon> selMuons;
  selMuons.clear();
  vector<MyMuon> allMuons = ev->Muons;
  for(size_t imu=0; imu < allMuons.size(); ++imu){
      selMuons.push_back(allMuons[imu]);
  }
  return selMuons;
}

vector<MyJet> Reader::getJets(MyEvent* ev, string algo)
{
  vector<MyJet> selJets;
  selJets.clear();
  vector<MyJet> allJets = ev->Jets;
  for(size_t ijet=0; ijet < allJets.size(); ++ijet){
      selJets.push_back(allJets[ijet]);
  }
  return selJets;
}

MyMET Reader::getMET(MyEvent* ev, string algo) 
{ 
  MyMET selmet;
  vector<MyMET> allMETs = ev->mets; 
  for(size_t imet=0; imet < allMETs.size(); ++imet){ 
      selmet = allMETs[imet];
  }
  return selmet; 
} 
