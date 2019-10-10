#include "interface/MyEvent.h"

MyEvent::MyEvent() :
  runNb(1), eventNb(0),  
  lumiblock(-1), isData(false), eventQuality(-1)
{
  hlt.resize(0);
  Electrons.clear();
  Muons.clear();
  Jets.clear();
  mets.clear();
  //tracks.clear();
  PrimaryVtxs.clear();
  mcParticles.clear();
  KineFitParticles.clear();
}

MyEvent::~MyEvent()
{

}

void MyEvent::Reset()
{
  runNb = 0;  
  eventNb = 0;
  lumiblock = -1;
  
  isData = false;
  hlt.resize(0);
  Electrons.clear();
  Muons.clear();
  Jets.clear();
  mets.clear();
  //tracks.clear();
  PrimaryVtxs.clear();
  mcParticles.clear();
  KineFitParticles.clear();

  eventQuality = -1;
}

