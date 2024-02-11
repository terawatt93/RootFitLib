// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME FitLibDict
#define R__NO_DEPRECATION

/*******************************************************************/
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define G__DICTIONARY
#include "ROOT/RConfig.hxx"
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

// Header files passed as explicit arguments
#include "FitLib.hh"

// Header files passed via #pragma extra_include

// The generated code does not explicitly qualify STL entities
namespace std {} using namespace std;

namespace ROOT {

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FitManager*)
   {
      ::FitManager *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FitManager >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("FitManager", ::FitManager::Class_Version(), "FitLib.hh", 28,
                  typeid(::FitManager), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FitManager::Dictionary, isa_proxy, 4,
                  sizeof(::FitManager) );
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FitManager*)
   {
      return GenerateInitInstanceLocal(static_cast<::FitManager*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::FitManager*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_TF1Parameter(void *p = nullptr);
   static void *newArray_TF1Parameter(Long_t size, void *p);
   static void delete_TF1Parameter(void *p);
   static void deleteArray_TF1Parameter(void *p);
   static void destruct_TF1Parameter(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TF1Parameter*)
   {
      ::TF1Parameter *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TF1Parameter >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("TF1Parameter", ::TF1Parameter::Class_Version(), "FitLib.hh", 63,
                  typeid(::TF1Parameter), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::TF1Parameter::Dictionary, isa_proxy, 4,
                  sizeof(::TF1Parameter) );
      instance.SetNew(&new_TF1Parameter);
      instance.SetNewArray(&newArray_TF1Parameter);
      instance.SetDelete(&delete_TF1Parameter);
      instance.SetDeleteArray(&deleteArray_TF1Parameter);
      instance.SetDestructor(&destruct_TF1Parameter);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TF1Parameter*)
   {
      return GenerateInitInstanceLocal(static_cast<::TF1Parameter*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::TF1Parameter*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FitFunction(void *p = nullptr);
   static void *newArray_FitFunction(Long_t size, void *p);
   static void delete_FitFunction(void *p);
   static void deleteArray_FitFunction(void *p);
   static void destruct_FitFunction(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FitFunction*)
   {
      ::FitFunction *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FitFunction >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("FitFunction", ::FitFunction::Class_Version(), "FitLib.hh", 78,
                  typeid(::FitFunction), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FitFunction::Dictionary, isa_proxy, 4,
                  sizeof(::FitFunction) );
      instance.SetNew(&new_FitFunction);
      instance.SetNewArray(&newArray_FitFunction);
      instance.SetDelete(&delete_FitFunction);
      instance.SetDeleteArray(&deleteArray_FitFunction);
      instance.SetDestructor(&destruct_FitFunction);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FitFunction*)
   {
      return GenerateInitInstanceLocal(static_cast<::FitFunction*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::FitFunction*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr FitManager::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *FitManager::Class_Name()
{
   return "FitManager";
}

//______________________________________________________________________________
const char *FitManager::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FitManager*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int FitManager::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FitManager*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FitManager::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FitManager*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FitManager::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FitManager*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr TF1Parameter::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *TF1Parameter::Class_Name()
{
   return "TF1Parameter";
}

//______________________________________________________________________________
const char *TF1Parameter::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TF1Parameter*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int TF1Parameter::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TF1Parameter*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *TF1Parameter::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TF1Parameter*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TF1Parameter::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TF1Parameter*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FitFunction::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *FitFunction::Class_Name()
{
   return "FitFunction";
}

//______________________________________________________________________________
const char *FitFunction::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FitFunction*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int FitFunction::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FitFunction*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FitFunction::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FitFunction*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FitFunction::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FitFunction*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void FitManager::Streamer(TBuffer &R__b)
{
   // Stream an object of class FitManager.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(FitManager::Class(),this);
   } else {
      R__b.WriteClassBuffer(FitManager::Class(),this);
   }
}

namespace ROOT {
} // end of namespace ROOT for class ::FitManager

//______________________________________________________________________________
void TF1Parameter::Streamer(TBuffer &R__b)
{
   // Stream an object of class TF1Parameter.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TF1Parameter::Class(),this);
   } else {
      R__b.WriteClassBuffer(TF1Parameter::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_TF1Parameter(void *p) {
      return  p ? new(p) ::TF1Parameter : new ::TF1Parameter;
   }
   static void *newArray_TF1Parameter(Long_t nElements, void *p) {
      return p ? new(p) ::TF1Parameter[nElements] : new ::TF1Parameter[nElements];
   }
   // Wrapper around operator delete
   static void delete_TF1Parameter(void *p) {
      delete (static_cast<::TF1Parameter*>(p));
   }
   static void deleteArray_TF1Parameter(void *p) {
      delete [] (static_cast<::TF1Parameter*>(p));
   }
   static void destruct_TF1Parameter(void *p) {
      typedef ::TF1Parameter current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::TF1Parameter

//______________________________________________________________________________
void FitFunction::Streamer(TBuffer &R__b)
{
   // Stream an object of class FitFunction.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(FitFunction::Class(),this);
   } else {
      R__b.WriteClassBuffer(FitFunction::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FitFunction(void *p) {
      return  p ? new(p) ::FitFunction : new ::FitFunction;
   }
   static void *newArray_FitFunction(Long_t nElements, void *p) {
      return p ? new(p) ::FitFunction[nElements] : new ::FitFunction[nElements];
   }
   // Wrapper around operator delete
   static void delete_FitFunction(void *p) {
      delete (static_cast<::FitFunction*>(p));
   }
   static void deleteArray_FitFunction(void *p) {
      delete [] (static_cast<::FitFunction*>(p));
   }
   static void destruct_FitFunction(void *p) {
      typedef ::FitFunction current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::FitFunction

namespace ROOT {
   static TClass *vectorlETF1ParametergR_Dictionary();
   static void vectorlETF1ParametergR_TClassManip(TClass*);
   static void *new_vectorlETF1ParametergR(void *p = nullptr);
   static void *newArray_vectorlETF1ParametergR(Long_t size, void *p);
   static void delete_vectorlETF1ParametergR(void *p);
   static void deleteArray_vectorlETF1ParametergR(void *p);
   static void destruct_vectorlETF1ParametergR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<TF1Parameter>*)
   {
      vector<TF1Parameter> *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<TF1Parameter>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<TF1Parameter>", -2, "vector", 389,
                  typeid(vector<TF1Parameter>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlETF1ParametergR_Dictionary, isa_proxy, 0,
                  sizeof(vector<TF1Parameter>) );
      instance.SetNew(&new_vectorlETF1ParametergR);
      instance.SetNewArray(&newArray_vectorlETF1ParametergR);
      instance.SetDelete(&delete_vectorlETF1ParametergR);
      instance.SetDeleteArray(&deleteArray_vectorlETF1ParametergR);
      instance.SetDestructor(&destruct_vectorlETF1ParametergR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<TF1Parameter> >()));

      ::ROOT::AddClassAlternate("vector<TF1Parameter>","std::vector<TF1Parameter, std::allocator<TF1Parameter> >");
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const vector<TF1Parameter>*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlETF1ParametergR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const vector<TF1Parameter>*>(nullptr))->GetClass();
      vectorlETF1ParametergR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlETF1ParametergR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlETF1ParametergR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<TF1Parameter> : new vector<TF1Parameter>;
   }
   static void *newArray_vectorlETF1ParametergR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<TF1Parameter>[nElements] : new vector<TF1Parameter>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlETF1ParametergR(void *p) {
      delete (static_cast<vector<TF1Parameter>*>(p));
   }
   static void deleteArray_vectorlETF1ParametergR(void *p) {
      delete [] (static_cast<vector<TF1Parameter>*>(p));
   }
   static void destruct_vectorlETF1ParametergR(void *p) {
      typedef vector<TF1Parameter> current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class vector<TF1Parameter>

namespace ROOT {
   static TClass *vectorlEFitResultmUgR_Dictionary();
   static void vectorlEFitResultmUgR_TClassManip(TClass*);
   static void *new_vectorlEFitResultmUgR(void *p = nullptr);
   static void *newArray_vectorlEFitResultmUgR(Long_t size, void *p);
   static void delete_vectorlEFitResultmUgR(void *p);
   static void deleteArray_vectorlEFitResultmUgR(void *p);
   static void destruct_vectorlEFitResultmUgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<FitResult*>*)
   {
      vector<FitResult*> *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<FitResult*>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<FitResult*>", -2, "vector", 389,
                  typeid(vector<FitResult*>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEFitResultmUgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<FitResult*>) );
      instance.SetNew(&new_vectorlEFitResultmUgR);
      instance.SetNewArray(&newArray_vectorlEFitResultmUgR);
      instance.SetDelete(&delete_vectorlEFitResultmUgR);
      instance.SetDeleteArray(&deleteArray_vectorlEFitResultmUgR);
      instance.SetDestructor(&destruct_vectorlEFitResultmUgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<FitResult*> >()));

      ::ROOT::AddClassAlternate("vector<FitResult*>","std::vector<FitResult*, std::allocator<FitResult*> >");
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const vector<FitResult*>*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEFitResultmUgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const vector<FitResult*>*>(nullptr))->GetClass();
      vectorlEFitResultmUgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEFitResultmUgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEFitResultmUgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<FitResult*> : new vector<FitResult*>;
   }
   static void *newArray_vectorlEFitResultmUgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<FitResult*>[nElements] : new vector<FitResult*>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEFitResultmUgR(void *p) {
      delete (static_cast<vector<FitResult*>*>(p));
   }
   static void deleteArray_vectorlEFitResultmUgR(void *p) {
      delete [] (static_cast<vector<FitResult*>*>(p));
   }
   static void destruct_vectorlEFitResultmUgR(void *p) {
      typedef vector<FitResult*> current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class vector<FitResult*>

namespace ROOT {
   static TClass *vectorlEFitFunctionmUgR_Dictionary();
   static void vectorlEFitFunctionmUgR_TClassManip(TClass*);
   static void *new_vectorlEFitFunctionmUgR(void *p = nullptr);
   static void *newArray_vectorlEFitFunctionmUgR(Long_t size, void *p);
   static void delete_vectorlEFitFunctionmUgR(void *p);
   static void deleteArray_vectorlEFitFunctionmUgR(void *p);
   static void destruct_vectorlEFitFunctionmUgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<FitFunction*>*)
   {
      vector<FitFunction*> *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<FitFunction*>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<FitFunction*>", -2, "vector", 389,
                  typeid(vector<FitFunction*>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEFitFunctionmUgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<FitFunction*>) );
      instance.SetNew(&new_vectorlEFitFunctionmUgR);
      instance.SetNewArray(&newArray_vectorlEFitFunctionmUgR);
      instance.SetDelete(&delete_vectorlEFitFunctionmUgR);
      instance.SetDeleteArray(&deleteArray_vectorlEFitFunctionmUgR);
      instance.SetDestructor(&destruct_vectorlEFitFunctionmUgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<FitFunction*> >()));

      ::ROOT::AddClassAlternate("vector<FitFunction*>","std::vector<FitFunction*, std::allocator<FitFunction*> >");
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const vector<FitFunction*>*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEFitFunctionmUgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const vector<FitFunction*>*>(nullptr))->GetClass();
      vectorlEFitFunctionmUgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEFitFunctionmUgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEFitFunctionmUgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<FitFunction*> : new vector<FitFunction*>;
   }
   static void *newArray_vectorlEFitFunctionmUgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<FitFunction*>[nElements] : new vector<FitFunction*>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEFitFunctionmUgR(void *p) {
      delete (static_cast<vector<FitFunction*>*>(p));
   }
   static void deleteArray_vectorlEFitFunctionmUgR(void *p) {
      delete [] (static_cast<vector<FitFunction*>*>(p));
   }
   static void destruct_vectorlEFitFunctionmUgR(void *p) {
      typedef vector<FitFunction*> current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class vector<FitFunction*>

namespace {
  void TriggerDictionaryInitialization_FitLibDict_Impl() {
    static const char* headers[] = {
"FitLib.hh",
nullptr
    };
    static const char* includePaths[] = {
"/home/terawatt/Programs/root/root-install/include/",
"/home/terawatt/Documents/tests/FitLib/",
nullptr
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "FitLibDict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_AutoLoading_Map;
class __attribute__((annotate("$clingAutoload$FitLib.hh")))  FitManager;
class __attribute__((annotate("$clingAutoload$FitLib.hh")))  TF1Parameter;
class __attribute__((annotate("$clingAutoload$FitLib.hh")))  FitFunction;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "FitLibDict dictionary payload"


#define _BACKWARD_BACKWARD_WARNING_H
// Inline headers
#include "FitLib.hh"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[] = {
"FitFunction", payloadCode, "@",
"FitManager", payloadCode, "@",
"TF1Parameter", payloadCode, "@",
nullptr
};
    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("FitLibDict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_FitLibDict_Impl, {}, classesHeaders, /*hasCxxModule*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_FitLibDict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_FitLibDict() {
  TriggerDictionaryInitialization_FitLibDict_Impl();
}
