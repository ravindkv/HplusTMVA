// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME eventdict

/*******************************************************************/
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <assert.h>
#define G__DICTIONARY
#include "RConfig.h"
#include "TClass.h"
#include "TDictAttributeMap.h"
#include "TInterpreter.h"
#include "TROOT.h"
#include "TBuffer.h"
#include "TMemberInspector.h"
#include "TInterpreter.h"
#include "TVirtualMutex.h"
#include "TError.h"

#ifndef G__ROOT
#define G__ROOT
#endif

#include "RtypesImp.h"
#include "TIsAProxy.h"
#include "TFileMergeInfo.h"
#include <algorithm>
#include "TCollectionProxyInfo.h"
/*******************************************************************/

#include "TDataMember.h"

// Since CINT ignores the std namespace, we need to do so in this file.
namespace std {} using namespace std;

// Header files passed as explicit arguments
#include "interface/MyEvent.h"
#include "interface/MyMET.h"
#include "interface/MyMCParticle.h"
#include "interface/MyTrack.h"
#include "interface/MyVertex.h"
#include "interface/MyJet.h"
#include "interface/MyElectron.h"
#include "interface/MyMuon.h"
#include "interface/MySampleInfo.h"
#include "interface/MyKineFitParticle.h"
#include "interface/Reader.h"
#include "interface/ObjectSelector.hh"
#include "interface/HistogramPlotter.hh"
#include "interface/BTagSF.hh"
#include "interface/CTagSF.hh"
#include "interface/SVEffUnc.hh"
#include "interface/UncertaintyComputer.hh"

// Header files passed via #pragma extra_include

namespace ROOT {
   static TClass *MySampleInfo_Dictionary();
   static void MySampleInfo_TClassManip(TClass*);
   static void *new_MySampleInfo(void *p = 0);
   static void *newArray_MySampleInfo(Long_t size, void *p);
   static void delete_MySampleInfo(void *p);
   static void deleteArray_MySampleInfo(void *p);
   static void destruct_MySampleInfo(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::MySampleInfo*)
   {
      ::MySampleInfo *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::MySampleInfo));
      static ::ROOT::TGenericClassInfo 
         instance("MySampleInfo", "interface/MySampleInfo.h", 8,
                  typeid(::MySampleInfo), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &MySampleInfo_Dictionary, isa_proxy, 4,
                  sizeof(::MySampleInfo) );
      instance.SetNew(&new_MySampleInfo);
      instance.SetNewArray(&newArray_MySampleInfo);
      instance.SetDelete(&delete_MySampleInfo);
      instance.SetDeleteArray(&deleteArray_MySampleInfo);
      instance.SetDestructor(&destruct_MySampleInfo);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::MySampleInfo*)
   {
      return GenerateInitInstanceLocal((::MySampleInfo*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::MySampleInfo*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *MySampleInfo_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::MySampleInfo*)0x0)->GetClass();
      MySampleInfo_TClassManip(theClass);
   return theClass;
   }

   static void MySampleInfo_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *MyMCParticle_Dictionary();
   static void MyMCParticle_TClassManip(TClass*);
   static void *new_MyMCParticle(void *p = 0);
   static void *newArray_MyMCParticle(Long_t size, void *p);
   static void delete_MyMCParticle(void *p);
   static void deleteArray_MyMCParticle(void *p);
   static void destruct_MyMCParticle(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::MyMCParticle*)
   {
      ::MyMCParticle *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::MyMCParticle));
      static ::ROOT::TGenericClassInfo 
         instance("MyMCParticle", "interface/MyMCParticle.h", 11,
                  typeid(::MyMCParticle), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &MyMCParticle_Dictionary, isa_proxy, 4,
                  sizeof(::MyMCParticle) );
      instance.SetNew(&new_MyMCParticle);
      instance.SetNewArray(&newArray_MyMCParticle);
      instance.SetDelete(&delete_MyMCParticle);
      instance.SetDeleteArray(&deleteArray_MyMCParticle);
      instance.SetDestructor(&destruct_MyMCParticle);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::MyMCParticle*)
   {
      return GenerateInitInstanceLocal((::MyMCParticle*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::MyMCParticle*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *MyMCParticle_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::MyMCParticle*)0x0)->GetClass();
      MyMCParticle_TClassManip(theClass);
   return theClass;
   }

   static void MyMCParticle_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *MyVertex_Dictionary();
   static void MyVertex_TClassManip(TClass*);
   static void *new_MyVertex(void *p = 0);
   static void *newArray_MyVertex(Long_t size, void *p);
   static void delete_MyVertex(void *p);
   static void deleteArray_MyVertex(void *p);
   static void destruct_MyVertex(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::MyVertex*)
   {
      ::MyVertex *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::MyVertex));
      static ::ROOT::TGenericClassInfo 
         instance("MyVertex", "interface/MyVertex.h", 11,
                  typeid(::MyVertex), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &MyVertex_Dictionary, isa_proxy, 4,
                  sizeof(::MyVertex) );
      instance.SetNew(&new_MyVertex);
      instance.SetNewArray(&newArray_MyVertex);
      instance.SetDelete(&delete_MyVertex);
      instance.SetDeleteArray(&deleteArray_MyVertex);
      instance.SetDestructor(&destruct_MyVertex);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::MyVertex*)
   {
      return GenerateInitInstanceLocal((::MyVertex*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::MyVertex*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *MyVertex_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::MyVertex*)0x0)->GetClass();
      MyVertex_TClassManip(theClass);
   return theClass;
   }

   static void MyVertex_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *MyTrack_Dictionary();
   static void MyTrack_TClassManip(TClass*);
   static void *new_MyTrack(void *p = 0);
   static void *newArray_MyTrack(Long_t size, void *p);
   static void delete_MyTrack(void *p);
   static void deleteArray_MyTrack(void *p);
   static void destruct_MyTrack(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::MyTrack*)
   {
      ::MyTrack *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::MyTrack));
      static ::ROOT::TGenericClassInfo 
         instance("MyTrack", "interface/MyTrack.h", 11,
                  typeid(::MyTrack), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &MyTrack_Dictionary, isa_proxy, 4,
                  sizeof(::MyTrack) );
      instance.SetNew(&new_MyTrack);
      instance.SetNewArray(&newArray_MyTrack);
      instance.SetDelete(&delete_MyTrack);
      instance.SetDeleteArray(&deleteArray_MyTrack);
      instance.SetDestructor(&destruct_MyTrack);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::MyTrack*)
   {
      return GenerateInitInstanceLocal((::MyTrack*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::MyTrack*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *MyTrack_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::MyTrack*)0x0)->GetClass();
      MyTrack_TClassManip(theClass);
   return theClass;
   }

   static void MyTrack_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *MyMET_Dictionary();
   static void MyMET_TClassManip(TClass*);
   static void *new_MyMET(void *p = 0);
   static void *newArray_MyMET(Long_t size, void *p);
   static void delete_MyMET(void *p);
   static void deleteArray_MyMET(void *p);
   static void destruct_MyMET(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::MyMET*)
   {
      ::MyMET *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::MyMET));
      static ::ROOT::TGenericClassInfo 
         instance("MyMET", "interface/MyMET.h", 12,
                  typeid(::MyMET), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &MyMET_Dictionary, isa_proxy, 4,
                  sizeof(::MyMET) );
      instance.SetNew(&new_MyMET);
      instance.SetNewArray(&newArray_MyMET);
      instance.SetDelete(&delete_MyMET);
      instance.SetDeleteArray(&deleteArray_MyMET);
      instance.SetDestructor(&destruct_MyMET);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::MyMET*)
   {
      return GenerateInitInstanceLocal((::MyMET*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::MyMET*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *MyMET_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::MyMET*)0x0)->GetClass();
      MyMET_TClassManip(theClass);
   return theClass;
   }

   static void MyMET_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *MyJet_Dictionary();
   static void MyJet_TClassManip(TClass*);
   static void *new_MyJet(void *p = 0);
   static void *newArray_MyJet(Long_t size, void *p);
   static void delete_MyJet(void *p);
   static void deleteArray_MyJet(void *p);
   static void destruct_MyJet(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::MyJet*)
   {
      ::MyJet *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::MyJet));
      static ::ROOT::TGenericClassInfo 
         instance("MyJet", "interface/MyJet.h", 11,
                  typeid(::MyJet), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &MyJet_Dictionary, isa_proxy, 4,
                  sizeof(::MyJet) );
      instance.SetNew(&new_MyJet);
      instance.SetNewArray(&newArray_MyJet);
      instance.SetDelete(&delete_MyJet);
      instance.SetDeleteArray(&deleteArray_MyJet);
      instance.SetDestructor(&destruct_MyJet);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::MyJet*)
   {
      return GenerateInitInstanceLocal((::MyJet*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::MyJet*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *MyJet_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::MyJet*)0x0)->GetClass();
      MyJet_TClassManip(theClass);
   return theClass;
   }

   static void MyJet_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *MyElectron_Dictionary();
   static void MyElectron_TClassManip(TClass*);
   static void *new_MyElectron(void *p = 0);
   static void *newArray_MyElectron(Long_t size, void *p);
   static void delete_MyElectron(void *p);
   static void deleteArray_MyElectron(void *p);
   static void destruct_MyElectron(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::MyElectron*)
   {
      ::MyElectron *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::MyElectron));
      static ::ROOT::TGenericClassInfo 
         instance("MyElectron", "interface/MyElectron.h", 10,
                  typeid(::MyElectron), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &MyElectron_Dictionary, isa_proxy, 4,
                  sizeof(::MyElectron) );
      instance.SetNew(&new_MyElectron);
      instance.SetNewArray(&newArray_MyElectron);
      instance.SetDelete(&delete_MyElectron);
      instance.SetDeleteArray(&deleteArray_MyElectron);
      instance.SetDestructor(&destruct_MyElectron);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::MyElectron*)
   {
      return GenerateInitInstanceLocal((::MyElectron*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::MyElectron*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *MyElectron_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::MyElectron*)0x0)->GetClass();
      MyElectron_TClassManip(theClass);
   return theClass;
   }

   static void MyElectron_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *MyMuon_Dictionary();
   static void MyMuon_TClassManip(TClass*);
   static void *new_MyMuon(void *p = 0);
   static void *newArray_MyMuon(Long_t size, void *p);
   static void delete_MyMuon(void *p);
   static void deleteArray_MyMuon(void *p);
   static void destruct_MyMuon(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::MyMuon*)
   {
      ::MyMuon *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::MyMuon));
      static ::ROOT::TGenericClassInfo 
         instance("MyMuon", "interface/MyMuon.h", 12,
                  typeid(::MyMuon), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &MyMuon_Dictionary, isa_proxy, 4,
                  sizeof(::MyMuon) );
      instance.SetNew(&new_MyMuon);
      instance.SetNewArray(&newArray_MyMuon);
      instance.SetDelete(&delete_MyMuon);
      instance.SetDeleteArray(&deleteArray_MyMuon);
      instance.SetDestructor(&destruct_MyMuon);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::MyMuon*)
   {
      return GenerateInitInstanceLocal((::MyMuon*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::MyMuon*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *MyMuon_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::MyMuon*)0x0)->GetClass();
      MyMuon_TClassManip(theClass);
   return theClass;
   }

   static void MyMuon_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *MyKineFitParticle_Dictionary();
   static void MyKineFitParticle_TClassManip(TClass*);
   static void *new_MyKineFitParticle(void *p = 0);
   static void *newArray_MyKineFitParticle(Long_t size, void *p);
   static void delete_MyKineFitParticle(void *p);
   static void deleteArray_MyKineFitParticle(void *p);
   static void destruct_MyKineFitParticle(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::MyKineFitParticle*)
   {
      ::MyKineFitParticle *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::MyKineFitParticle));
      static ::ROOT::TGenericClassInfo 
         instance("MyKineFitParticle", "interface/MyKineFitParticle.h", 11,
                  typeid(::MyKineFitParticle), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &MyKineFitParticle_Dictionary, isa_proxy, 4,
                  sizeof(::MyKineFitParticle) );
      instance.SetNew(&new_MyKineFitParticle);
      instance.SetNewArray(&newArray_MyKineFitParticle);
      instance.SetDelete(&delete_MyKineFitParticle);
      instance.SetDeleteArray(&deleteArray_MyKineFitParticle);
      instance.SetDestructor(&destruct_MyKineFitParticle);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::MyKineFitParticle*)
   {
      return GenerateInitInstanceLocal((::MyKineFitParticle*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::MyKineFitParticle*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *MyKineFitParticle_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::MyKineFitParticle*)0x0)->GetClass();
      MyKineFitParticle_TClassManip(theClass);
   return theClass;
   }

   static void MyKineFitParticle_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *MyEvent_Dictionary();
   static void MyEvent_TClassManip(TClass*);
   static void *new_MyEvent(void *p = 0);
   static void *newArray_MyEvent(Long_t size, void *p);
   static void delete_MyEvent(void *p);
   static void deleteArray_MyEvent(void *p);
   static void destruct_MyEvent(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::MyEvent*)
   {
      ::MyEvent *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::MyEvent));
      static ::ROOT::TGenericClassInfo 
         instance("MyEvent", "interface/MyEvent.h", 40,
                  typeid(::MyEvent), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &MyEvent_Dictionary, isa_proxy, 4,
                  sizeof(::MyEvent) );
      instance.SetNew(&new_MyEvent);
      instance.SetNewArray(&newArray_MyEvent);
      instance.SetDelete(&delete_MyEvent);
      instance.SetDeleteArray(&deleteArray_MyEvent);
      instance.SetDestructor(&destruct_MyEvent);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::MyEvent*)
   {
      return GenerateInitInstanceLocal((::MyEvent*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::MyEvent*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *MyEvent_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::MyEvent*)0x0)->GetClass();
      MyEvent_TClassManip(theClass);
   return theClass;
   }

   static void MyEvent_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static void *new_Reader(void *p = 0);
   static void *newArray_Reader(Long_t size, void *p);
   static void delete_Reader(void *p);
   static void deleteArray_Reader(void *p);
   static void destruct_Reader(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Reader*)
   {
      ::Reader *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::Reader >(0);
      static ::ROOT::TGenericClassInfo 
         instance("Reader", ::Reader::Class_Version(), "interface/Reader.h", 43,
                  typeid(::Reader), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::Reader::Dictionary, isa_proxy, 4,
                  sizeof(::Reader) );
      instance.SetNew(&new_Reader);
      instance.SetNewArray(&newArray_Reader);
      instance.SetDelete(&delete_Reader);
      instance.SetDeleteArray(&deleteArray_Reader);
      instance.SetDestructor(&destruct_Reader);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Reader*)
   {
      return GenerateInitInstanceLocal((::Reader*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::Reader*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_ObjectSelector(void *p = 0);
   static void *newArray_ObjectSelector(Long_t size, void *p);
   static void delete_ObjectSelector(void *p);
   static void deleteArray_ObjectSelector(void *p);
   static void destruct_ObjectSelector(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::ObjectSelector*)
   {
      ::ObjectSelector *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::ObjectSelector >(0);
      static ::ROOT::TGenericClassInfo 
         instance("ObjectSelector", ::ObjectSelector::Class_Version(), "interface/ObjectSelector.hh", 28,
                  typeid(::ObjectSelector), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::ObjectSelector::Dictionary, isa_proxy, 4,
                  sizeof(::ObjectSelector) );
      instance.SetNew(&new_ObjectSelector);
      instance.SetNewArray(&newArray_ObjectSelector);
      instance.SetDelete(&delete_ObjectSelector);
      instance.SetDeleteArray(&deleteArray_ObjectSelector);
      instance.SetDestructor(&destruct_ObjectSelector);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::ObjectSelector*)
   {
      return GenerateInitInstanceLocal((::ObjectSelector*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::ObjectSelector*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_HistogramPlotter(void *p = 0);
   static void *newArray_HistogramPlotter(Long_t size, void *p);
   static void delete_HistogramPlotter(void *p);
   static void deleteArray_HistogramPlotter(void *p);
   static void destruct_HistogramPlotter(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::HistogramPlotter*)
   {
      ::HistogramPlotter *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::HistogramPlotter >(0);
      static ::ROOT::TGenericClassInfo 
         instance("HistogramPlotter", ::HistogramPlotter::Class_Version(), "interface/HistogramPlotter.hh", 25,
                  typeid(::HistogramPlotter), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::HistogramPlotter::Dictionary, isa_proxy, 4,
                  sizeof(::HistogramPlotter) );
      instance.SetNew(&new_HistogramPlotter);
      instance.SetNewArray(&newArray_HistogramPlotter);
      instance.SetDelete(&delete_HistogramPlotter);
      instance.SetDeleteArray(&deleteArray_HistogramPlotter);
      instance.SetDestructor(&destruct_HistogramPlotter);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::HistogramPlotter*)
   {
      return GenerateInitInstanceLocal((::HistogramPlotter*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::HistogramPlotter*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_BTagSF(void *p = 0);
   static void *newArray_BTagSF(Long_t size, void *p);
   static void delete_BTagSF(void *p);
   static void deleteArray_BTagSF(void *p);
   static void destruct_BTagSF(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::BTagSF*)
   {
      ::BTagSF *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::BTagSF >(0);
      static ::ROOT::TGenericClassInfo 
         instance("BTagSF", ::BTagSF::Class_Version(), "interface/BTagSF.hh", 15,
                  typeid(::BTagSF), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::BTagSF::Dictionary, isa_proxy, 4,
                  sizeof(::BTagSF) );
      instance.SetNew(&new_BTagSF);
      instance.SetNewArray(&newArray_BTagSF);
      instance.SetDelete(&delete_BTagSF);
      instance.SetDeleteArray(&deleteArray_BTagSF);
      instance.SetDestructor(&destruct_BTagSF);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::BTagSF*)
   {
      return GenerateInitInstanceLocal((::BTagSF*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::BTagSF*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_CTagSF(void *p = 0);
   static void *newArray_CTagSF(Long_t size, void *p);
   static void delete_CTagSF(void *p);
   static void deleteArray_CTagSF(void *p);
   static void destruct_CTagSF(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::CTagSF*)
   {
      ::CTagSF *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::CTagSF >(0);
      static ::ROOT::TGenericClassInfo 
         instance("CTagSF", ::CTagSF::Class_Version(), "interface/CTagSF.hh", 15,
                  typeid(::CTagSF), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::CTagSF::Dictionary, isa_proxy, 4,
                  sizeof(::CTagSF) );
      instance.SetNew(&new_CTagSF);
      instance.SetNewArray(&newArray_CTagSF);
      instance.SetDelete(&delete_CTagSF);
      instance.SetDeleteArray(&deleteArray_CTagSF);
      instance.SetDestructor(&destruct_CTagSF);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::CTagSF*)
   {
      return GenerateInitInstanceLocal((::CTagSF*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::CTagSF*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_SVEffUnc(void *p = 0);
   static void *newArray_SVEffUnc(Long_t size, void *p);
   static void delete_SVEffUnc(void *p);
   static void deleteArray_SVEffUnc(void *p);
   static void destruct_SVEffUnc(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::SVEffUnc*)
   {
      ::SVEffUnc *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::SVEffUnc >(0);
      static ::ROOT::TGenericClassInfo 
         instance("SVEffUnc", ::SVEffUnc::Class_Version(), "interface/SVEffUnc.hh", 12,
                  typeid(::SVEffUnc), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::SVEffUnc::Dictionary, isa_proxy, 4,
                  sizeof(::SVEffUnc) );
      instance.SetNew(&new_SVEffUnc);
      instance.SetNewArray(&newArray_SVEffUnc);
      instance.SetDelete(&delete_SVEffUnc);
      instance.SetDeleteArray(&deleteArray_SVEffUnc);
      instance.SetDestructor(&destruct_SVEffUnc);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::SVEffUnc*)
   {
      return GenerateInitInstanceLocal((::SVEffUnc*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::SVEffUnc*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_UncertaintyComputer(void *p = 0);
   static void *newArray_UncertaintyComputer(Long_t size, void *p);
   static void delete_UncertaintyComputer(void *p);
   static void deleteArray_UncertaintyComputer(void *p);
   static void destruct_UncertaintyComputer(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::UncertaintyComputer*)
   {
      ::UncertaintyComputer *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::UncertaintyComputer >(0);
      static ::ROOT::TGenericClassInfo 
         instance("UncertaintyComputer", ::UncertaintyComputer::Class_Version(), "interface/UncertaintyComputer.hh", 40,
                  typeid(::UncertaintyComputer), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::UncertaintyComputer::Dictionary, isa_proxy, 4,
                  sizeof(::UncertaintyComputer) );
      instance.SetNew(&new_UncertaintyComputer);
      instance.SetNewArray(&newArray_UncertaintyComputer);
      instance.SetDelete(&delete_UncertaintyComputer);
      instance.SetDeleteArray(&deleteArray_UncertaintyComputer);
      instance.SetDestructor(&destruct_UncertaintyComputer);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::UncertaintyComputer*)
   {
      return GenerateInitInstanceLocal((::UncertaintyComputer*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::UncertaintyComputer*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr Reader::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *Reader::Class_Name()
{
   return "Reader";
}

//______________________________________________________________________________
const char *Reader::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Reader*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int Reader::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Reader*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *Reader::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Reader*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *Reader::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Reader*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr ObjectSelector::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *ObjectSelector::Class_Name()
{
   return "ObjectSelector";
}

//______________________________________________________________________________
const char *ObjectSelector::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::ObjectSelector*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int ObjectSelector::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::ObjectSelector*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *ObjectSelector::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::ObjectSelector*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *ObjectSelector::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::ObjectSelector*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr HistogramPlotter::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *HistogramPlotter::Class_Name()
{
   return "HistogramPlotter";
}

//______________________________________________________________________________
const char *HistogramPlotter::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::HistogramPlotter*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int HistogramPlotter::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::HistogramPlotter*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *HistogramPlotter::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::HistogramPlotter*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *HistogramPlotter::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::HistogramPlotter*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr BTagSF::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *BTagSF::Class_Name()
{
   return "BTagSF";
}

//______________________________________________________________________________
const char *BTagSF::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::BTagSF*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int BTagSF::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::BTagSF*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *BTagSF::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::BTagSF*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *BTagSF::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::BTagSF*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr CTagSF::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *CTagSF::Class_Name()
{
   return "CTagSF";
}

//______________________________________________________________________________
const char *CTagSF::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::CTagSF*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int CTagSF::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::CTagSF*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *CTagSF::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::CTagSF*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *CTagSF::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::CTagSF*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr SVEffUnc::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *SVEffUnc::Class_Name()
{
   return "SVEffUnc";
}

//______________________________________________________________________________
const char *SVEffUnc::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::SVEffUnc*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int SVEffUnc::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::SVEffUnc*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *SVEffUnc::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::SVEffUnc*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *SVEffUnc::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::SVEffUnc*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr UncertaintyComputer::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *UncertaintyComputer::Class_Name()
{
   return "UncertaintyComputer";
}

//______________________________________________________________________________
const char *UncertaintyComputer::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::UncertaintyComputer*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int UncertaintyComputer::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::UncertaintyComputer*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *UncertaintyComputer::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::UncertaintyComputer*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *UncertaintyComputer::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::UncertaintyComputer*)0x0)->GetClass(); }
   return fgIsA;
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_MySampleInfo(void *p) {
      return  p ? new(p) ::MySampleInfo : new ::MySampleInfo;
   }
   static void *newArray_MySampleInfo(Long_t nElements, void *p) {
      return p ? new(p) ::MySampleInfo[nElements] : new ::MySampleInfo[nElements];
   }
   // Wrapper around operator delete
   static void delete_MySampleInfo(void *p) {
      delete ((::MySampleInfo*)p);
   }
   static void deleteArray_MySampleInfo(void *p) {
      delete [] ((::MySampleInfo*)p);
   }
   static void destruct_MySampleInfo(void *p) {
      typedef ::MySampleInfo current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::MySampleInfo

namespace ROOT {
   // Wrappers around operator new
   static void *new_MyMCParticle(void *p) {
      return  p ? new(p) ::MyMCParticle : new ::MyMCParticle;
   }
   static void *newArray_MyMCParticle(Long_t nElements, void *p) {
      return p ? new(p) ::MyMCParticle[nElements] : new ::MyMCParticle[nElements];
   }
   // Wrapper around operator delete
   static void delete_MyMCParticle(void *p) {
      delete ((::MyMCParticle*)p);
   }
   static void deleteArray_MyMCParticle(void *p) {
      delete [] ((::MyMCParticle*)p);
   }
   static void destruct_MyMCParticle(void *p) {
      typedef ::MyMCParticle current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::MyMCParticle

namespace ROOT {
   // Wrappers around operator new
   static void *new_MyVertex(void *p) {
      return  p ? new(p) ::MyVertex : new ::MyVertex;
   }
   static void *newArray_MyVertex(Long_t nElements, void *p) {
      return p ? new(p) ::MyVertex[nElements] : new ::MyVertex[nElements];
   }
   // Wrapper around operator delete
   static void delete_MyVertex(void *p) {
      delete ((::MyVertex*)p);
   }
   static void deleteArray_MyVertex(void *p) {
      delete [] ((::MyVertex*)p);
   }
   static void destruct_MyVertex(void *p) {
      typedef ::MyVertex current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::MyVertex

namespace ROOT {
   // Wrappers around operator new
   static void *new_MyTrack(void *p) {
      return  p ? new(p) ::MyTrack : new ::MyTrack;
   }
   static void *newArray_MyTrack(Long_t nElements, void *p) {
      return p ? new(p) ::MyTrack[nElements] : new ::MyTrack[nElements];
   }
   // Wrapper around operator delete
   static void delete_MyTrack(void *p) {
      delete ((::MyTrack*)p);
   }
   static void deleteArray_MyTrack(void *p) {
      delete [] ((::MyTrack*)p);
   }
   static void destruct_MyTrack(void *p) {
      typedef ::MyTrack current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::MyTrack

namespace ROOT {
   // Wrappers around operator new
   static void *new_MyMET(void *p) {
      return  p ? new(p) ::MyMET : new ::MyMET;
   }
   static void *newArray_MyMET(Long_t nElements, void *p) {
      return p ? new(p) ::MyMET[nElements] : new ::MyMET[nElements];
   }
   // Wrapper around operator delete
   static void delete_MyMET(void *p) {
      delete ((::MyMET*)p);
   }
   static void deleteArray_MyMET(void *p) {
      delete [] ((::MyMET*)p);
   }
   static void destruct_MyMET(void *p) {
      typedef ::MyMET current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::MyMET

namespace ROOT {
   // Wrappers around operator new
   static void *new_MyJet(void *p) {
      return  p ? new(p) ::MyJet : new ::MyJet;
   }
   static void *newArray_MyJet(Long_t nElements, void *p) {
      return p ? new(p) ::MyJet[nElements] : new ::MyJet[nElements];
   }
   // Wrapper around operator delete
   static void delete_MyJet(void *p) {
      delete ((::MyJet*)p);
   }
   static void deleteArray_MyJet(void *p) {
      delete [] ((::MyJet*)p);
   }
   static void destruct_MyJet(void *p) {
      typedef ::MyJet current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::MyJet

namespace ROOT {
   // Wrappers around operator new
   static void *new_MyElectron(void *p) {
      return  p ? new(p) ::MyElectron : new ::MyElectron;
   }
   static void *newArray_MyElectron(Long_t nElements, void *p) {
      return p ? new(p) ::MyElectron[nElements] : new ::MyElectron[nElements];
   }
   // Wrapper around operator delete
   static void delete_MyElectron(void *p) {
      delete ((::MyElectron*)p);
   }
   static void deleteArray_MyElectron(void *p) {
      delete [] ((::MyElectron*)p);
   }
   static void destruct_MyElectron(void *p) {
      typedef ::MyElectron current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::MyElectron

namespace ROOT {
   // Wrappers around operator new
   static void *new_MyMuon(void *p) {
      return  p ? new(p) ::MyMuon : new ::MyMuon;
   }
   static void *newArray_MyMuon(Long_t nElements, void *p) {
      return p ? new(p) ::MyMuon[nElements] : new ::MyMuon[nElements];
   }
   // Wrapper around operator delete
   static void delete_MyMuon(void *p) {
      delete ((::MyMuon*)p);
   }
   static void deleteArray_MyMuon(void *p) {
      delete [] ((::MyMuon*)p);
   }
   static void destruct_MyMuon(void *p) {
      typedef ::MyMuon current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::MyMuon

namespace ROOT {
   // Wrappers around operator new
   static void *new_MyKineFitParticle(void *p) {
      return  p ? new(p) ::MyKineFitParticle : new ::MyKineFitParticle;
   }
   static void *newArray_MyKineFitParticle(Long_t nElements, void *p) {
      return p ? new(p) ::MyKineFitParticle[nElements] : new ::MyKineFitParticle[nElements];
   }
   // Wrapper around operator delete
   static void delete_MyKineFitParticle(void *p) {
      delete ((::MyKineFitParticle*)p);
   }
   static void deleteArray_MyKineFitParticle(void *p) {
      delete [] ((::MyKineFitParticle*)p);
   }
   static void destruct_MyKineFitParticle(void *p) {
      typedef ::MyKineFitParticle current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::MyKineFitParticle

namespace ROOT {
   // Wrappers around operator new
   static void *new_MyEvent(void *p) {
      return  p ? new(p) ::MyEvent : new ::MyEvent;
   }
   static void *newArray_MyEvent(Long_t nElements, void *p) {
      return p ? new(p) ::MyEvent[nElements] : new ::MyEvent[nElements];
   }
   // Wrapper around operator delete
   static void delete_MyEvent(void *p) {
      delete ((::MyEvent*)p);
   }
   static void deleteArray_MyEvent(void *p) {
      delete [] ((::MyEvent*)p);
   }
   static void destruct_MyEvent(void *p) {
      typedef ::MyEvent current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::MyEvent

//______________________________________________________________________________
void Reader::Streamer(TBuffer &R__b)
{
   // Stream an object of class Reader.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(Reader::Class(),this);
   } else {
      R__b.WriteClassBuffer(Reader::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_Reader(void *p) {
      return  p ? new(p) ::Reader : new ::Reader;
   }
   static void *newArray_Reader(Long_t nElements, void *p) {
      return p ? new(p) ::Reader[nElements] : new ::Reader[nElements];
   }
   // Wrapper around operator delete
   static void delete_Reader(void *p) {
      delete ((::Reader*)p);
   }
   static void deleteArray_Reader(void *p) {
      delete [] ((::Reader*)p);
   }
   static void destruct_Reader(void *p) {
      typedef ::Reader current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::Reader

//______________________________________________________________________________
void ObjectSelector::Streamer(TBuffer &R__b)
{
   // Stream an object of class ObjectSelector.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(ObjectSelector::Class(),this);
   } else {
      R__b.WriteClassBuffer(ObjectSelector::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_ObjectSelector(void *p) {
      return  p ? new(p) ::ObjectSelector : new ::ObjectSelector;
   }
   static void *newArray_ObjectSelector(Long_t nElements, void *p) {
      return p ? new(p) ::ObjectSelector[nElements] : new ::ObjectSelector[nElements];
   }
   // Wrapper around operator delete
   static void delete_ObjectSelector(void *p) {
      delete ((::ObjectSelector*)p);
   }
   static void deleteArray_ObjectSelector(void *p) {
      delete [] ((::ObjectSelector*)p);
   }
   static void destruct_ObjectSelector(void *p) {
      typedef ::ObjectSelector current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::ObjectSelector

//______________________________________________________________________________
void HistogramPlotter::Streamer(TBuffer &R__b)
{
   // Stream an object of class HistogramPlotter.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(HistogramPlotter::Class(),this);
   } else {
      R__b.WriteClassBuffer(HistogramPlotter::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_HistogramPlotter(void *p) {
      return  p ? new(p) ::HistogramPlotter : new ::HistogramPlotter;
   }
   static void *newArray_HistogramPlotter(Long_t nElements, void *p) {
      return p ? new(p) ::HistogramPlotter[nElements] : new ::HistogramPlotter[nElements];
   }
   // Wrapper around operator delete
   static void delete_HistogramPlotter(void *p) {
      delete ((::HistogramPlotter*)p);
   }
   static void deleteArray_HistogramPlotter(void *p) {
      delete [] ((::HistogramPlotter*)p);
   }
   static void destruct_HistogramPlotter(void *p) {
      typedef ::HistogramPlotter current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::HistogramPlotter

//______________________________________________________________________________
void BTagSF::Streamer(TBuffer &R__b)
{
   // Stream an object of class BTagSF.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(BTagSF::Class(),this);
   } else {
      R__b.WriteClassBuffer(BTagSF::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_BTagSF(void *p) {
      return  p ? new(p) ::BTagSF : new ::BTagSF;
   }
   static void *newArray_BTagSF(Long_t nElements, void *p) {
      return p ? new(p) ::BTagSF[nElements] : new ::BTagSF[nElements];
   }
   // Wrapper around operator delete
   static void delete_BTagSF(void *p) {
      delete ((::BTagSF*)p);
   }
   static void deleteArray_BTagSF(void *p) {
      delete [] ((::BTagSF*)p);
   }
   static void destruct_BTagSF(void *p) {
      typedef ::BTagSF current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::BTagSF

//______________________________________________________________________________
void CTagSF::Streamer(TBuffer &R__b)
{
   // Stream an object of class CTagSF.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(CTagSF::Class(),this);
   } else {
      R__b.WriteClassBuffer(CTagSF::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_CTagSF(void *p) {
      return  p ? new(p) ::CTagSF : new ::CTagSF;
   }
   static void *newArray_CTagSF(Long_t nElements, void *p) {
      return p ? new(p) ::CTagSF[nElements] : new ::CTagSF[nElements];
   }
   // Wrapper around operator delete
   static void delete_CTagSF(void *p) {
      delete ((::CTagSF*)p);
   }
   static void deleteArray_CTagSF(void *p) {
      delete [] ((::CTagSF*)p);
   }
   static void destruct_CTagSF(void *p) {
      typedef ::CTagSF current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::CTagSF

//______________________________________________________________________________
void SVEffUnc::Streamer(TBuffer &R__b)
{
   // Stream an object of class SVEffUnc.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(SVEffUnc::Class(),this);
   } else {
      R__b.WriteClassBuffer(SVEffUnc::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_SVEffUnc(void *p) {
      return  p ? new(p) ::SVEffUnc : new ::SVEffUnc;
   }
   static void *newArray_SVEffUnc(Long_t nElements, void *p) {
      return p ? new(p) ::SVEffUnc[nElements] : new ::SVEffUnc[nElements];
   }
   // Wrapper around operator delete
   static void delete_SVEffUnc(void *p) {
      delete ((::SVEffUnc*)p);
   }
   static void deleteArray_SVEffUnc(void *p) {
      delete [] ((::SVEffUnc*)p);
   }
   static void destruct_SVEffUnc(void *p) {
      typedef ::SVEffUnc current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::SVEffUnc

//______________________________________________________________________________
void UncertaintyComputer::Streamer(TBuffer &R__b)
{
   // Stream an object of class UncertaintyComputer.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(UncertaintyComputer::Class(),this);
   } else {
      R__b.WriteClassBuffer(UncertaintyComputer::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_UncertaintyComputer(void *p) {
      return  p ? new(p) ::UncertaintyComputer : new ::UncertaintyComputer;
   }
   static void *newArray_UncertaintyComputer(Long_t nElements, void *p) {
      return p ? new(p) ::UncertaintyComputer[nElements] : new ::UncertaintyComputer[nElements];
   }
   // Wrapper around operator delete
   static void delete_UncertaintyComputer(void *p) {
      delete ((::UncertaintyComputer*)p);
   }
   static void deleteArray_UncertaintyComputer(void *p) {
      delete [] ((::UncertaintyComputer*)p);
   }
   static void destruct_UncertaintyComputer(void *p) {
      typedef ::UncertaintyComputer current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::UncertaintyComputer

namespace ROOT {
   static TClass *vectorlEstringgR_Dictionary();
   static void vectorlEstringgR_TClassManip(TClass*);
   static void *new_vectorlEstringgR(void *p = 0);
   static void *newArray_vectorlEstringgR(Long_t size, void *p);
   static void delete_vectorlEstringgR(void *p);
   static void deleteArray_vectorlEstringgR(void *p);
   static void destruct_vectorlEstringgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<string>*)
   {
      vector<string> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<string>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<string>", -2, "vector", 214,
                  typeid(vector<string>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEstringgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<string>) );
      instance.SetNew(&new_vectorlEstringgR);
      instance.SetNewArray(&newArray_vectorlEstringgR);
      instance.SetDelete(&delete_vectorlEstringgR);
      instance.SetDeleteArray(&deleteArray_vectorlEstringgR);
      instance.SetDestructor(&destruct_vectorlEstringgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<string> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const vector<string>*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEstringgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<string>*)0x0)->GetClass();
      vectorlEstringgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEstringgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEstringgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<string> : new vector<string>;
   }
   static void *newArray_vectorlEstringgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<string>[nElements] : new vector<string>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEstringgR(void *p) {
      delete ((vector<string>*)p);
   }
   static void deleteArray_vectorlEstringgR(void *p) {
      delete [] ((vector<string>*)p);
   }
   static void destruct_vectorlEstringgR(void *p) {
      typedef vector<string> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<string>

namespace ROOT {
   static TClass *vectorlEintgR_Dictionary();
   static void vectorlEintgR_TClassManip(TClass*);
   static void *new_vectorlEintgR(void *p = 0);
   static void *newArray_vectorlEintgR(Long_t size, void *p);
   static void delete_vectorlEintgR(void *p);
   static void deleteArray_vectorlEintgR(void *p);
   static void destruct_vectorlEintgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<int>*)
   {
      vector<int> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<int>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<int>", -2, "vector", 214,
                  typeid(vector<int>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEintgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<int>) );
      instance.SetNew(&new_vectorlEintgR);
      instance.SetNewArray(&newArray_vectorlEintgR);
      instance.SetDelete(&delete_vectorlEintgR);
      instance.SetDeleteArray(&deleteArray_vectorlEintgR);
      instance.SetDestructor(&destruct_vectorlEintgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<int> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const vector<int>*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEintgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<int>*)0x0)->GetClass();
      vectorlEintgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEintgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEintgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<int> : new vector<int>;
   }
   static void *newArray_vectorlEintgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<int>[nElements] : new vector<int>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEintgR(void *p) {
      delete ((vector<int>*)p);
   }
   static void deleteArray_vectorlEintgR(void *p) {
      delete [] ((vector<int>*)p);
   }
   static void destruct_vectorlEintgR(void *p) {
      typedef vector<int> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<int>

namespace ROOT {
   static TClass *vectorlEdoublegR_Dictionary();
   static void vectorlEdoublegR_TClassManip(TClass*);
   static void *new_vectorlEdoublegR(void *p = 0);
   static void *newArray_vectorlEdoublegR(Long_t size, void *p);
   static void delete_vectorlEdoublegR(void *p);
   static void deleteArray_vectorlEdoublegR(void *p);
   static void destruct_vectorlEdoublegR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<double>*)
   {
      vector<double> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<double>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<double>", -2, "vector", 214,
                  typeid(vector<double>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEdoublegR_Dictionary, isa_proxy, 0,
                  sizeof(vector<double>) );
      instance.SetNew(&new_vectorlEdoublegR);
      instance.SetNewArray(&newArray_vectorlEdoublegR);
      instance.SetDelete(&delete_vectorlEdoublegR);
      instance.SetDeleteArray(&deleteArray_vectorlEdoublegR);
      instance.SetDestructor(&destruct_vectorlEdoublegR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<double> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const vector<double>*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEdoublegR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<double>*)0x0)->GetClass();
      vectorlEdoublegR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEdoublegR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEdoublegR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<double> : new vector<double>;
   }
   static void *newArray_vectorlEdoublegR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<double>[nElements] : new vector<double>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEdoublegR(void *p) {
      delete ((vector<double>*)p);
   }
   static void deleteArray_vectorlEdoublegR(void *p) {
      delete [] ((vector<double>*)p);
   }
   static void destruct_vectorlEdoublegR(void *p) {
      typedef vector<double> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<double>

namespace ROOT {
   static TClass *vectorlEMyVertexgR_Dictionary();
   static void vectorlEMyVertexgR_TClassManip(TClass*);
   static void *new_vectorlEMyVertexgR(void *p = 0);
   static void *newArray_vectorlEMyVertexgR(Long_t size, void *p);
   static void delete_vectorlEMyVertexgR(void *p);
   static void deleteArray_vectorlEMyVertexgR(void *p);
   static void destruct_vectorlEMyVertexgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<MyVertex>*)
   {
      vector<MyVertex> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<MyVertex>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<MyVertex>", -2, "vector", 214,
                  typeid(vector<MyVertex>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEMyVertexgR_Dictionary, isa_proxy, 4,
                  sizeof(vector<MyVertex>) );
      instance.SetNew(&new_vectorlEMyVertexgR);
      instance.SetNewArray(&newArray_vectorlEMyVertexgR);
      instance.SetDelete(&delete_vectorlEMyVertexgR);
      instance.SetDeleteArray(&deleteArray_vectorlEMyVertexgR);
      instance.SetDestructor(&destruct_vectorlEMyVertexgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<MyVertex> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const vector<MyVertex>*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEMyVertexgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<MyVertex>*)0x0)->GetClass();
      vectorlEMyVertexgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEMyVertexgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEMyVertexgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<MyVertex> : new vector<MyVertex>;
   }
   static void *newArray_vectorlEMyVertexgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<MyVertex>[nElements] : new vector<MyVertex>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEMyVertexgR(void *p) {
      delete ((vector<MyVertex>*)p);
   }
   static void deleteArray_vectorlEMyVertexgR(void *p) {
      delete [] ((vector<MyVertex>*)p);
   }
   static void destruct_vectorlEMyVertexgR(void *p) {
      typedef vector<MyVertex> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<MyVertex>

namespace ROOT {
   static TClass *vectorlEMyTrackgR_Dictionary();
   static void vectorlEMyTrackgR_TClassManip(TClass*);
   static void *new_vectorlEMyTrackgR(void *p = 0);
   static void *newArray_vectorlEMyTrackgR(Long_t size, void *p);
   static void delete_vectorlEMyTrackgR(void *p);
   static void deleteArray_vectorlEMyTrackgR(void *p);
   static void destruct_vectorlEMyTrackgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<MyTrack>*)
   {
      vector<MyTrack> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<MyTrack>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<MyTrack>", -2, "vector", 214,
                  typeid(vector<MyTrack>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEMyTrackgR_Dictionary, isa_proxy, 4,
                  sizeof(vector<MyTrack>) );
      instance.SetNew(&new_vectorlEMyTrackgR);
      instance.SetNewArray(&newArray_vectorlEMyTrackgR);
      instance.SetDelete(&delete_vectorlEMyTrackgR);
      instance.SetDeleteArray(&deleteArray_vectorlEMyTrackgR);
      instance.SetDestructor(&destruct_vectorlEMyTrackgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<MyTrack> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const vector<MyTrack>*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEMyTrackgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<MyTrack>*)0x0)->GetClass();
      vectorlEMyTrackgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEMyTrackgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEMyTrackgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<MyTrack> : new vector<MyTrack>;
   }
   static void *newArray_vectorlEMyTrackgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<MyTrack>[nElements] : new vector<MyTrack>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEMyTrackgR(void *p) {
      delete ((vector<MyTrack>*)p);
   }
   static void deleteArray_vectorlEMyTrackgR(void *p) {
      delete [] ((vector<MyTrack>*)p);
   }
   static void destruct_vectorlEMyTrackgR(void *p) {
      typedef vector<MyTrack> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<MyTrack>

namespace ROOT {
   static TClass *vectorlEMyMuongR_Dictionary();
   static void vectorlEMyMuongR_TClassManip(TClass*);
   static void *new_vectorlEMyMuongR(void *p = 0);
   static void *newArray_vectorlEMyMuongR(Long_t size, void *p);
   static void delete_vectorlEMyMuongR(void *p);
   static void deleteArray_vectorlEMyMuongR(void *p);
   static void destruct_vectorlEMyMuongR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<MyMuon>*)
   {
      vector<MyMuon> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<MyMuon>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<MyMuon>", -2, "vector", 214,
                  typeid(vector<MyMuon>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEMyMuongR_Dictionary, isa_proxy, 4,
                  sizeof(vector<MyMuon>) );
      instance.SetNew(&new_vectorlEMyMuongR);
      instance.SetNewArray(&newArray_vectorlEMyMuongR);
      instance.SetDelete(&delete_vectorlEMyMuongR);
      instance.SetDeleteArray(&deleteArray_vectorlEMyMuongR);
      instance.SetDestructor(&destruct_vectorlEMyMuongR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<MyMuon> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const vector<MyMuon>*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEMyMuongR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<MyMuon>*)0x0)->GetClass();
      vectorlEMyMuongR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEMyMuongR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEMyMuongR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<MyMuon> : new vector<MyMuon>;
   }
   static void *newArray_vectorlEMyMuongR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<MyMuon>[nElements] : new vector<MyMuon>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEMyMuongR(void *p) {
      delete ((vector<MyMuon>*)p);
   }
   static void deleteArray_vectorlEMyMuongR(void *p) {
      delete [] ((vector<MyMuon>*)p);
   }
   static void destruct_vectorlEMyMuongR(void *p) {
      typedef vector<MyMuon> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<MyMuon>

namespace ROOT {
   static TClass *vectorlEMyMETgR_Dictionary();
   static void vectorlEMyMETgR_TClassManip(TClass*);
   static void *new_vectorlEMyMETgR(void *p = 0);
   static void *newArray_vectorlEMyMETgR(Long_t size, void *p);
   static void delete_vectorlEMyMETgR(void *p);
   static void deleteArray_vectorlEMyMETgR(void *p);
   static void destruct_vectorlEMyMETgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<MyMET>*)
   {
      vector<MyMET> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<MyMET>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<MyMET>", -2, "vector", 214,
                  typeid(vector<MyMET>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEMyMETgR_Dictionary, isa_proxy, 4,
                  sizeof(vector<MyMET>) );
      instance.SetNew(&new_vectorlEMyMETgR);
      instance.SetNewArray(&newArray_vectorlEMyMETgR);
      instance.SetDelete(&delete_vectorlEMyMETgR);
      instance.SetDeleteArray(&deleteArray_vectorlEMyMETgR);
      instance.SetDestructor(&destruct_vectorlEMyMETgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<MyMET> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const vector<MyMET>*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEMyMETgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<MyMET>*)0x0)->GetClass();
      vectorlEMyMETgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEMyMETgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEMyMETgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<MyMET> : new vector<MyMET>;
   }
   static void *newArray_vectorlEMyMETgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<MyMET>[nElements] : new vector<MyMET>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEMyMETgR(void *p) {
      delete ((vector<MyMET>*)p);
   }
   static void deleteArray_vectorlEMyMETgR(void *p) {
      delete [] ((vector<MyMET>*)p);
   }
   static void destruct_vectorlEMyMETgR(void *p) {
      typedef vector<MyMET> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<MyMET>

namespace ROOT {
   static TClass *vectorlEMyMCParticlegR_Dictionary();
   static void vectorlEMyMCParticlegR_TClassManip(TClass*);
   static void *new_vectorlEMyMCParticlegR(void *p = 0);
   static void *newArray_vectorlEMyMCParticlegR(Long_t size, void *p);
   static void delete_vectorlEMyMCParticlegR(void *p);
   static void deleteArray_vectorlEMyMCParticlegR(void *p);
   static void destruct_vectorlEMyMCParticlegR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<MyMCParticle>*)
   {
      vector<MyMCParticle> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<MyMCParticle>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<MyMCParticle>", -2, "vector", 214,
                  typeid(vector<MyMCParticle>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEMyMCParticlegR_Dictionary, isa_proxy, 4,
                  sizeof(vector<MyMCParticle>) );
      instance.SetNew(&new_vectorlEMyMCParticlegR);
      instance.SetNewArray(&newArray_vectorlEMyMCParticlegR);
      instance.SetDelete(&delete_vectorlEMyMCParticlegR);
      instance.SetDeleteArray(&deleteArray_vectorlEMyMCParticlegR);
      instance.SetDestructor(&destruct_vectorlEMyMCParticlegR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<MyMCParticle> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const vector<MyMCParticle>*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEMyMCParticlegR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<MyMCParticle>*)0x0)->GetClass();
      vectorlEMyMCParticlegR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEMyMCParticlegR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEMyMCParticlegR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<MyMCParticle> : new vector<MyMCParticle>;
   }
   static void *newArray_vectorlEMyMCParticlegR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<MyMCParticle>[nElements] : new vector<MyMCParticle>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEMyMCParticlegR(void *p) {
      delete ((vector<MyMCParticle>*)p);
   }
   static void deleteArray_vectorlEMyMCParticlegR(void *p) {
      delete [] ((vector<MyMCParticle>*)p);
   }
   static void destruct_vectorlEMyMCParticlegR(void *p) {
      typedef vector<MyMCParticle> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<MyMCParticle>

namespace ROOT {
   static TClass *vectorlEMyKineFitParticlegR_Dictionary();
   static void vectorlEMyKineFitParticlegR_TClassManip(TClass*);
   static void *new_vectorlEMyKineFitParticlegR(void *p = 0);
   static void *newArray_vectorlEMyKineFitParticlegR(Long_t size, void *p);
   static void delete_vectorlEMyKineFitParticlegR(void *p);
   static void deleteArray_vectorlEMyKineFitParticlegR(void *p);
   static void destruct_vectorlEMyKineFitParticlegR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<MyKineFitParticle>*)
   {
      vector<MyKineFitParticle> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<MyKineFitParticle>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<MyKineFitParticle>", -2, "vector", 214,
                  typeid(vector<MyKineFitParticle>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEMyKineFitParticlegR_Dictionary, isa_proxy, 4,
                  sizeof(vector<MyKineFitParticle>) );
      instance.SetNew(&new_vectorlEMyKineFitParticlegR);
      instance.SetNewArray(&newArray_vectorlEMyKineFitParticlegR);
      instance.SetDelete(&delete_vectorlEMyKineFitParticlegR);
      instance.SetDeleteArray(&deleteArray_vectorlEMyKineFitParticlegR);
      instance.SetDestructor(&destruct_vectorlEMyKineFitParticlegR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<MyKineFitParticle> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const vector<MyKineFitParticle>*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEMyKineFitParticlegR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<MyKineFitParticle>*)0x0)->GetClass();
      vectorlEMyKineFitParticlegR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEMyKineFitParticlegR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEMyKineFitParticlegR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<MyKineFitParticle> : new vector<MyKineFitParticle>;
   }
   static void *newArray_vectorlEMyKineFitParticlegR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<MyKineFitParticle>[nElements] : new vector<MyKineFitParticle>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEMyKineFitParticlegR(void *p) {
      delete ((vector<MyKineFitParticle>*)p);
   }
   static void deleteArray_vectorlEMyKineFitParticlegR(void *p) {
      delete [] ((vector<MyKineFitParticle>*)p);
   }
   static void destruct_vectorlEMyKineFitParticlegR(void *p) {
      typedef vector<MyKineFitParticle> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<MyKineFitParticle>

namespace ROOT {
   static TClass *vectorlEMyJetgR_Dictionary();
   static void vectorlEMyJetgR_TClassManip(TClass*);
   static void *new_vectorlEMyJetgR(void *p = 0);
   static void *newArray_vectorlEMyJetgR(Long_t size, void *p);
   static void delete_vectorlEMyJetgR(void *p);
   static void deleteArray_vectorlEMyJetgR(void *p);
   static void destruct_vectorlEMyJetgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<MyJet>*)
   {
      vector<MyJet> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<MyJet>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<MyJet>", -2, "vector", 214,
                  typeid(vector<MyJet>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEMyJetgR_Dictionary, isa_proxy, 4,
                  sizeof(vector<MyJet>) );
      instance.SetNew(&new_vectorlEMyJetgR);
      instance.SetNewArray(&newArray_vectorlEMyJetgR);
      instance.SetDelete(&delete_vectorlEMyJetgR);
      instance.SetDeleteArray(&deleteArray_vectorlEMyJetgR);
      instance.SetDestructor(&destruct_vectorlEMyJetgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<MyJet> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const vector<MyJet>*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEMyJetgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<MyJet>*)0x0)->GetClass();
      vectorlEMyJetgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEMyJetgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEMyJetgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<MyJet> : new vector<MyJet>;
   }
   static void *newArray_vectorlEMyJetgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<MyJet>[nElements] : new vector<MyJet>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEMyJetgR(void *p) {
      delete ((vector<MyJet>*)p);
   }
   static void deleteArray_vectorlEMyJetgR(void *p) {
      delete [] ((vector<MyJet>*)p);
   }
   static void destruct_vectorlEMyJetgR(void *p) {
      typedef vector<MyJet> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<MyJet>

namespace ROOT {
   static TClass *vectorlEMyElectrongR_Dictionary();
   static void vectorlEMyElectrongR_TClassManip(TClass*);
   static void *new_vectorlEMyElectrongR(void *p = 0);
   static void *newArray_vectorlEMyElectrongR(Long_t size, void *p);
   static void delete_vectorlEMyElectrongR(void *p);
   static void deleteArray_vectorlEMyElectrongR(void *p);
   static void destruct_vectorlEMyElectrongR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<MyElectron>*)
   {
      vector<MyElectron> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<MyElectron>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<MyElectron>", -2, "vector", 214,
                  typeid(vector<MyElectron>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEMyElectrongR_Dictionary, isa_proxy, 4,
                  sizeof(vector<MyElectron>) );
      instance.SetNew(&new_vectorlEMyElectrongR);
      instance.SetNewArray(&newArray_vectorlEMyElectrongR);
      instance.SetDelete(&delete_vectorlEMyElectrongR);
      instance.SetDeleteArray(&deleteArray_vectorlEMyElectrongR);
      instance.SetDestructor(&destruct_vectorlEMyElectrongR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<MyElectron> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const vector<MyElectron>*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEMyElectrongR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<MyElectron>*)0x0)->GetClass();
      vectorlEMyElectrongR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEMyElectrongR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEMyElectrongR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<MyElectron> : new vector<MyElectron>;
   }
   static void *newArray_vectorlEMyElectrongR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<MyElectron>[nElements] : new vector<MyElectron>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEMyElectrongR(void *p) {
      delete ((vector<MyElectron>*)p);
   }
   static void deleteArray_vectorlEMyElectrongR(void *p) {
      delete [] ((vector<MyElectron>*)p);
   }
   static void destruct_vectorlEMyElectrongR(void *p) {
      typedef vector<MyElectron> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<MyElectron>

namespace ROOT {
   static TClass *maplEstringcOdoublegR_Dictionary();
   static void maplEstringcOdoublegR_TClassManip(TClass*);
   static void *new_maplEstringcOdoublegR(void *p = 0);
   static void *newArray_maplEstringcOdoublegR(Long_t size, void *p);
   static void delete_maplEstringcOdoublegR(void *p);
   static void deleteArray_maplEstringcOdoublegR(void *p);
   static void destruct_maplEstringcOdoublegR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const map<string,double>*)
   {
      map<string,double> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(map<string,double>));
      static ::ROOT::TGenericClassInfo 
         instance("map<string,double>", -2, "map", 96,
                  typeid(map<string,double>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &maplEstringcOdoublegR_Dictionary, isa_proxy, 0,
                  sizeof(map<string,double>) );
      instance.SetNew(&new_maplEstringcOdoublegR);
      instance.SetNewArray(&newArray_maplEstringcOdoublegR);
      instance.SetDelete(&delete_maplEstringcOdoublegR);
      instance.SetDeleteArray(&deleteArray_maplEstringcOdoublegR);
      instance.SetDestructor(&destruct_maplEstringcOdoublegR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::MapInsert< map<string,double> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const map<string,double>*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *maplEstringcOdoublegR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const map<string,double>*)0x0)->GetClass();
      maplEstringcOdoublegR_TClassManip(theClass);
   return theClass;
   }

   static void maplEstringcOdoublegR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_maplEstringcOdoublegR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<string,double> : new map<string,double>;
   }
   static void *newArray_maplEstringcOdoublegR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<string,double>[nElements] : new map<string,double>[nElements];
   }
   // Wrapper around operator delete
   static void delete_maplEstringcOdoublegR(void *p) {
      delete ((map<string,double>*)p);
   }
   static void deleteArray_maplEstringcOdoublegR(void *p) {
      delete [] ((map<string,double>*)p);
   }
   static void destruct_maplEstringcOdoublegR(void *p) {
      typedef map<string,double> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class map<string,double>

namespace ROOT {
   static TClass *maplETStringcOTProfilemUgR_Dictionary();
   static void maplETStringcOTProfilemUgR_TClassManip(TClass*);
   static void *new_maplETStringcOTProfilemUgR(void *p = 0);
   static void *newArray_maplETStringcOTProfilemUgR(Long_t size, void *p);
   static void delete_maplETStringcOTProfilemUgR(void *p);
   static void deleteArray_maplETStringcOTProfilemUgR(void *p);
   static void destruct_maplETStringcOTProfilemUgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const map<TString,TProfile*>*)
   {
      map<TString,TProfile*> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(map<TString,TProfile*>));
      static ::ROOT::TGenericClassInfo 
         instance("map<TString,TProfile*>", -2, "map", 96,
                  typeid(map<TString,TProfile*>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &maplETStringcOTProfilemUgR_Dictionary, isa_proxy, 0,
                  sizeof(map<TString,TProfile*>) );
      instance.SetNew(&new_maplETStringcOTProfilemUgR);
      instance.SetNewArray(&newArray_maplETStringcOTProfilemUgR);
      instance.SetDelete(&delete_maplETStringcOTProfilemUgR);
      instance.SetDeleteArray(&deleteArray_maplETStringcOTProfilemUgR);
      instance.SetDestructor(&destruct_maplETStringcOTProfilemUgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::MapInsert< map<TString,TProfile*> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const map<TString,TProfile*>*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *maplETStringcOTProfilemUgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const map<TString,TProfile*>*)0x0)->GetClass();
      maplETStringcOTProfilemUgR_TClassManip(theClass);
   return theClass;
   }

   static void maplETStringcOTProfilemUgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_maplETStringcOTProfilemUgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<TString,TProfile*> : new map<TString,TProfile*>;
   }
   static void *newArray_maplETStringcOTProfilemUgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<TString,TProfile*>[nElements] : new map<TString,TProfile*>[nElements];
   }
   // Wrapper around operator delete
   static void delete_maplETStringcOTProfilemUgR(void *p) {
      delete ((map<TString,TProfile*>*)p);
   }
   static void deleteArray_maplETStringcOTProfilemUgR(void *p) {
      delete [] ((map<TString,TProfile*>*)p);
   }
   static void destruct_maplETStringcOTProfilemUgR(void *p) {
      typedef map<TString,TProfile*> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class map<TString,TProfile*>

namespace ROOT {
   static TClass *maplETStringcOTH2mUgR_Dictionary();
   static void maplETStringcOTH2mUgR_TClassManip(TClass*);
   static void *new_maplETStringcOTH2mUgR(void *p = 0);
   static void *newArray_maplETStringcOTH2mUgR(Long_t size, void *p);
   static void delete_maplETStringcOTH2mUgR(void *p);
   static void deleteArray_maplETStringcOTH2mUgR(void *p);
   static void destruct_maplETStringcOTH2mUgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const map<TString,TH2*>*)
   {
      map<TString,TH2*> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(map<TString,TH2*>));
      static ::ROOT::TGenericClassInfo 
         instance("map<TString,TH2*>", -2, "map", 96,
                  typeid(map<TString,TH2*>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &maplETStringcOTH2mUgR_Dictionary, isa_proxy, 0,
                  sizeof(map<TString,TH2*>) );
      instance.SetNew(&new_maplETStringcOTH2mUgR);
      instance.SetNewArray(&newArray_maplETStringcOTH2mUgR);
      instance.SetDelete(&delete_maplETStringcOTH2mUgR);
      instance.SetDeleteArray(&deleteArray_maplETStringcOTH2mUgR);
      instance.SetDestructor(&destruct_maplETStringcOTH2mUgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::MapInsert< map<TString,TH2*> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const map<TString,TH2*>*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *maplETStringcOTH2mUgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const map<TString,TH2*>*)0x0)->GetClass();
      maplETStringcOTH2mUgR_TClassManip(theClass);
   return theClass;
   }

   static void maplETStringcOTH2mUgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_maplETStringcOTH2mUgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<TString,TH2*> : new map<TString,TH2*>;
   }
   static void *newArray_maplETStringcOTH2mUgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<TString,TH2*>[nElements] : new map<TString,TH2*>[nElements];
   }
   // Wrapper around operator delete
   static void delete_maplETStringcOTH2mUgR(void *p) {
      delete ((map<TString,TH2*>*)p);
   }
   static void deleteArray_maplETStringcOTH2mUgR(void *p) {
      delete [] ((map<TString,TH2*>*)p);
   }
   static void destruct_maplETStringcOTH2mUgR(void *p) {
      typedef map<TString,TH2*> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class map<TString,TH2*>

namespace ROOT {
   static TClass *maplETStringcOTH1mUgR_Dictionary();
   static void maplETStringcOTH1mUgR_TClassManip(TClass*);
   static void *new_maplETStringcOTH1mUgR(void *p = 0);
   static void *newArray_maplETStringcOTH1mUgR(Long_t size, void *p);
   static void delete_maplETStringcOTH1mUgR(void *p);
   static void deleteArray_maplETStringcOTH1mUgR(void *p);
   static void destruct_maplETStringcOTH1mUgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const map<TString,TH1*>*)
   {
      map<TString,TH1*> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(map<TString,TH1*>));
      static ::ROOT::TGenericClassInfo 
         instance("map<TString,TH1*>", -2, "map", 96,
                  typeid(map<TString,TH1*>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &maplETStringcOTH1mUgR_Dictionary, isa_proxy, 0,
                  sizeof(map<TString,TH1*>) );
      instance.SetNew(&new_maplETStringcOTH1mUgR);
      instance.SetNewArray(&newArray_maplETStringcOTH1mUgR);
      instance.SetDelete(&delete_maplETStringcOTH1mUgR);
      instance.SetDeleteArray(&deleteArray_maplETStringcOTH1mUgR);
      instance.SetDestructor(&destruct_maplETStringcOTH1mUgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::MapInsert< map<TString,TH1*> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const map<TString,TH1*>*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *maplETStringcOTH1mUgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const map<TString,TH1*>*)0x0)->GetClass();
      maplETStringcOTH1mUgR_TClassManip(theClass);
   return theClass;
   }

   static void maplETStringcOTH1mUgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_maplETStringcOTH1mUgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<TString,TH1*> : new map<TString,TH1*>;
   }
   static void *newArray_maplETStringcOTH1mUgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<TString,TH1*>[nElements] : new map<TString,TH1*>[nElements];
   }
   // Wrapper around operator delete
   static void delete_maplETStringcOTH1mUgR(void *p) {
      delete ((map<TString,TH1*>*)p);
   }
   static void deleteArray_maplETStringcOTH1mUgR(void *p) {
      delete [] ((map<TString,TH1*>*)p);
   }
   static void destruct_maplETStringcOTH1mUgR(void *p) {
      typedef map<TString,TH1*> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class map<TString,TH1*>

namespace {
  void TriggerDictionaryInitialization_eventdict_Impl() {
    static const char* headers[] = {
"interface/MyEvent.h",
"interface/MyMET.h",
"interface/MyMCParticle.h",
"interface/MyTrack.h",
"interface/MyVertex.h",
"interface/MyJet.h",
"interface/MyElectron.h",
"interface/MyMuon.h",
"interface/MySampleInfo.h",
"interface/MyKineFitParticle.h",
"interface/Reader.h",
"interface/ObjectSelector.hh",
"interface/HistogramPlotter.hh",
"interface/BTagSF.hh",
"interface/CTagSF.hh",
"interface/SVEffUnc.hh",
"interface/UncertaintyComputer.hh",
0
    };
    static const char* includePaths[] = {
"/home/rverma/t3store3/AN-18-061/Analyze2016Data/CMSSW_8_0_25/src/Analysis/src/..",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc530/lcg/root/6.06.00-ikhhed6/include",
"/grid_mnt/t3storage3/rverma/AN-18-061/Analyze2016Data/CMSSW_8_0_25/src/Analysis/src/",
0
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "eventdict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class __attribute__((annotate("$clingAutoload$src/LinkDef.h")))  MySampleInfo;
class __attribute__((annotate("$clingAutoload$src/LinkDef.h")))  MyMCParticle;
namespace std{template <typename _Tp> class __attribute__((annotate("$clingAutoload$string")))  allocator;
}
class __attribute__((annotate("$clingAutoload$src/LinkDef.h")))  MyVertex;
class __attribute__((annotate("$clingAutoload$src/LinkDef.h")))  MyTrack;
class __attribute__((annotate("$clingAutoload$src/LinkDef.h")))  MyMET;
class __attribute__((annotate("$clingAutoload$src/LinkDef.h")))  MyJet;
class __attribute__((annotate("$clingAutoload$src/LinkDef.h")))  MyElectron;
class __attribute__((annotate("$clingAutoload$src/LinkDef.h")))  MyMuon;
class __attribute__((annotate("$clingAutoload$src/LinkDef.h")))  MyKineFitParticle;
class __attribute__((annotate("$clingAutoload$src/LinkDef.h")))  MyEvent;
class __attribute__((annotate("$clingAutoload$src/LinkDef.h")))  Reader;
class __attribute__((annotate("$clingAutoload$src/LinkDef.h")))  ObjectSelector;
class __attribute__((annotate("$clingAutoload$src/LinkDef.h")))  HistogramPlotter;
class __attribute__((annotate("$clingAutoload$src/LinkDef.h")))  BTagSF;
class __attribute__((annotate("$clingAutoload$src/LinkDef.h")))  CTagSF;
class __attribute__((annotate("$clingAutoload$src/LinkDef.h")))  SVEffUnc;
class __attribute__((annotate("$clingAutoload$src/LinkDef.h")))  UncertaintyComputer;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "eventdict dictionary payload"

#ifndef G__VECTOR_HAS_CLASS_ITERATOR
  #define G__VECTOR_HAS_CLASS_ITERATOR 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H
#include "interface/MyEvent.h"
#include "interface/MyMET.h"
#include "interface/MyMCParticle.h"
#include "interface/MyTrack.h"
#include "interface/MyVertex.h"
#include "interface/MyJet.h"
#include "interface/MyElectron.h"
#include "interface/MyMuon.h"
#include "interface/MySampleInfo.h"
#include "interface/MyKineFitParticle.h"
#include "interface/Reader.h"
#include "interface/ObjectSelector.hh"
#include "interface/HistogramPlotter.hh"
#include "interface/BTagSF.hh"
#include "interface/CTagSF.hh"
#include "interface/SVEffUnc.hh"
#include "interface/UncertaintyComputer.hh"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"BTagSF", payloadCode, "@",
"CTagSF", payloadCode, "@",
"HistogramPlotter", payloadCode, "@",
"MyElectron", payloadCode, "@",
"MyEvent", payloadCode, "@",
"MyJet", payloadCode, "@",
"MyKineFitParticle", payloadCode, "@",
"MyMCParticle", payloadCode, "@",
"MyMET", payloadCode, "@",
"MyMuon", payloadCode, "@",
"MySampleInfo", payloadCode, "@",
"MyTrack", payloadCode, "@",
"MyVertex", payloadCode, "@",
"ObjectSelector", payloadCode, "@",
"Reader", payloadCode, "@",
"SVEffUnc", payloadCode, "@",
"UncertaintyComputer", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("eventdict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_eventdict_Impl, {}, classesHeaders);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_eventdict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_eventdict() {
  TriggerDictionaryInitialization_eventdict_Impl();
}
