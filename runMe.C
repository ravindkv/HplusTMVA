#include "TString.h"
#include "TROOT.h"

void runMe(char const *arg){
  gROOT->ProcessLine(TString::Format(".L %s.C+",arg));
  gROOT->ProcessLine(TString::Format("%s t",arg));
  gROOT->ProcessLine("t.processEvents()");
}
