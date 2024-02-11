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
         instance("FitManager", ::FitManager::Class_Version(), "FitLib.hh", 30,
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
         instance("TF1Parameter", ::TF1Parameter::Class_Version(), "FitLib.hh", 65,
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
   static void *new_TFitFunction(void *p = nullptr);
   static void *newArray_TFitFunction(Long_t size, void *p);
   static void delete_TFitFunction(void *p);
   static void deleteArray_TFitFunction(void *p);
   static void destruct_TFitFunction(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TFitFunction*)
   {
      ::TFitFunction *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TFitFunction >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("TFitFunction", ::TFitFunction::Class_Version(), "FitLib.hh", 80,
                  typeid(::TFitFunction), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::TFitFunction::Dictionary, isa_proxy, 4,
                  sizeof(::TFitFunction) );
      instance.SetNew(&new_TFitFunction);
      instance.SetNewArray(&newArray_TFitFunction);
      instance.SetDelete(&delete_TFitFunction);
      instance.SetDeleteArray(&deleteArray_TFitFunction);
      instance.SetDestructor(&destruct_TFitFunction);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TFitFunction*)
   {
      return GenerateInitInstanceLocal(static_cast<::TFitFunction*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::TFitFunction*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
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
atomic_TClass_ptr TFitFunction::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *TFitFunction::Class_Name()
{
   return "TFitFunction";
}

//______________________________________________________________________________
const char *TFitFunction::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TFitFunction*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int TFitFunction::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TFitFunction*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *TFitFunction::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TFitFunction*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TFitFunction::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TFitFunction*)nullptr)->GetClass(); }
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
void TFitFunction::Streamer(TBuffer &R__b)
{
   // Stream an object of class TFitFunction.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TFitFunction::Class(),this);
   } else {
      R__b.WriteClassBuffer(TFitFunction::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_TFitFunction(void *p) {
      return  p ? new(p) ::TFitFunction : new ::TFitFunction;
   }
   static void *newArray_TFitFunction(Long_t nElements, void *p) {
      return p ? new(p) ::TFitFunction[nElements] : new ::TFitFunction[nElements];
   }
   // Wrapper around operator delete
   static void delete_TFitFunction(void *p) {
      delete (static_cast<::TFitFunction*>(p));
   }
   static void deleteArray_TFitFunction(void *p) {
      delete [] (static_cast<::TFitFunction*>(p));
   }
   static void destruct_TFitFunction(void *p) {
      typedef ::TFitFunction current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::TFitFunction

namespace ROOT {
   static TClass *vectorlETFitFunctionmUgR_Dictionary();
   static void vectorlETFitFunctionmUgR_TClassManip(TClass*);
   static void *new_vectorlETFitFunctionmUgR(void *p = nullptr);
   static void *newArray_vectorlETFitFunctionmUgR(Long_t size, void *p);
   static void delete_vectorlETFitFunctionmUgR(void *p);
   static void deleteArray_vectorlETFitFunctionmUgR(void *p);
   static void destruct_vectorlETFitFunctionmUgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<TFitFunction*>*)
   {
      vector<TFitFunction*> *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<TFitFunction*>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<TFitFunction*>", -2, "vector", 389,
                  typeid(vector<TFitFunction*>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlETFitFunctionmUgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<TFitFunction*>) );
      instance.SetNew(&new_vectorlETFitFunctionmUgR);
      instance.SetNewArray(&newArray_vectorlETFitFunctionmUgR);
      instance.SetDelete(&delete_vectorlETFitFunctionmUgR);
      instance.SetDeleteArray(&deleteArray_vectorlETFitFunctionmUgR);
      instance.SetDestructor(&destruct_vectorlETFitFunctionmUgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<TFitFunction*> >()));

      ::ROOT::AddClassAlternate("vector<TFitFunction*>","std::vector<TFitFunction*, std::allocator<TFitFunction*> >");
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const vector<TFitFunction*>*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlETFitFunctionmUgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const vector<TFitFunction*>*>(nullptr))->GetClass();
      vectorlETFitFunctionmUgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlETFitFunctionmUgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlETFitFunctionmUgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<TFitFunction*> : new vector<TFitFunction*>;
   }
   static void *newArray_vectorlETFitFunctionmUgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<TFitFunction*>[nElements] : new vector<TFitFunction*>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlETFitFunctionmUgR(void *p) {
      delete (static_cast<vector<TFitFunction*>*>(p));
   }
   static void deleteArray_vectorlETFitFunctionmUgR(void *p) {
      delete [] (static_cast<vector<TFitFunction*>*>(p));
   }
   static void destruct_vectorlETFitFunctionmUgR(void *p) {
      typedef vector<TFitFunction*> current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class vector<TFitFunction*>

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

namespace {
  void TriggerDictionaryInitialization_FitLibDict_Impl() {
    static const char* headers[] = {
"FitLib.hh",
nullptr
    };
    static const char* includePaths[] = {
"/home/terawatt/Programs/root/root-install/include/",
"/home/terawatt/Documents/tests/FitLib/RootFitLib/",
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
class __attribute__((annotate("$clingAutoload$FitLib.hh")))  TFitFunction;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "FitLibDict dictionary payload"


#define _BACKWARD_BACKWARD_WARNING_H
// Inline headers
#include "FitLib.hh"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[] = {
"FitManager", payloadCode, "@",
"TF1Parameter", payloadCode, "@",
"TFitFunction", payloadCode, "@",
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
