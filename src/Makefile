
files = $(wildcard *.cc *.cpp)
OBJS = $(addsuffix .o,$(basename $(files)))

#OBJS = MyEvent.o MyMCParticle.o MyGlobalPoint.o MyMeasurement1D.o MyMET.o \
#       MyTrack.o MyVertex.o MyCaloTower.o MyJet.o MyImpactParameter.o \
#       eventdict.o etaPhiFunctions.o

OPT = -O -Wall -fPIC -D_REENTRANT
INC = -I${ROOTSYS}/include -I..
EXT = -std=c++11

.cc.o:
	$(CXX) $(OPT) $(INC) $(EXT) -c $*.cc

all:
	@$(MAKE) eventdict.cc; $(MAKE) libMyEvent.so

eventdict.cc: ../interface/MyEvent.h ../interface/MyMCParticle.h ../interface/MyTrack.h ../interface/MyVertex.h ../interface/MyJet.h ../interface/MyMET.h ../interface/MyElectron.h ../interface/MyMuon.h ../interface/MySampleInfo.h ../interface/MyKineFitParticle.h ../interface/Reader.h ../interface/ObjectSelector.hh ../interface/HistogramPlotter.hh ../interface/BTagSF.hh ../interface/CTagSF.hh ../interface/SVEffUnc.hh ../interface/UncertaintyComputer.hh LinkDef.h
	rootcint -f eventdict.cc -c -I${PWD}/.. -p \
	interface/MyEvent.h \
	interface/MyMET.h \
	interface/MyMCParticle.h \
	interface/MyTrack.h \
	interface/MyVertex.h \
	interface/MyJet.h \
	interface/MyElectron.h \
	interface/MyMuon.h \
	interface/MySampleInfo.h \
	interface/MyKineFitParticle.h \
	interface/Reader.h \
	interface/ObjectSelector.hh \
	interface/HistogramPlotter.hh \
	interface/BTagSF.hh \
	interface/CTagSF.hh \
	interface/SVEffUnc.hh \
	interface/UncertaintyComputer.hh \
	src/LinkDef.h
	
compile: $(OBJS)

libMyEvent.so: $(OBJS)
	$(CXX) -shared -O *.o -o libMyEvent.so

clean:
	rm -f *.o; rm -f libMyEvent.so; rm -f eventdict.*
