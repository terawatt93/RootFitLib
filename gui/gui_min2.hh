#include "TGButton.h"
#include "TRootEmbeddedCanvas.h"
#include "TGLayout.h"
#include "TF1.h"
#include "TMath.h"
#include "TCanvas.h"
#include "TGTextEntry.h"
#include "TGTripleSlider.h"
#include "FitLib.hh"
#pragma once

int Color(int Num);


enum ETestCommandIdentifiers {
   HId1,
   HId2,
   HId3,
   HCId1,
   HCId2,

   HSId1
};

class FitParFrame;
class RootFitLib_gui;

class FitButtonFrame : public TGHorizontalFrame //полоса с кнопками под параметрами
{
	public:
	TGTextButton *Update;
	RootFitLib_gui *fMainFrame=0;
	TFitFunction* func;
	FitButtonFrame(TGFrame *fFrame,RootFitLib_gui *Main);
	void FUpdate();
};

class FitParFrame : public TGHorizontalFrame
{
	public:
	TGNumberEntry *ParValue,*ParError,*MinLimit,*MaxLimit;
	TGCheckButton *Fixed,*Limited;
	TGLabel *ParName;
	TGGroupFrame* fGroup;//указатель на группу
	FitParFrame(TGFrame *fFrame,TString ParName_="");
	void FromTFitFunction(TFitFunction *func,int ParNum);
	void ToTFitFunction(TFitFunction *func,int ParNum);
};

class RootFitLib_gui : public TGMainFrame {

public:


   TRootEmbeddedCanvas *fCanvas,*fCanvas1;
   TGLayoutHints       *fLcan;
   TFitFunction                 *fFitFcn=0;
   TGVerticalFrame   *fVframe0, *fVframe1, *fVframe2;
   TGHorizontalFrame   *fHframe0, *fHframe1, *fHframe2;
   TGLayoutHints       *fBly, *fBfly1, *fBfly2, *fBfly3;
   TGTripleHSlider     *fHslider1;
   TGTextEntry         *fTeh1, *fTeh2, *fTeh3;
   TGTextBuffer        *fTbh1, *fTbh2, *fTbh3;
   TGCheckButton       *fCheck1, *fCheck2;
   FitManager *fFitManager=0;
   //панели с управлением фитами
   FitButtonFrame *FitButtons;//управляющие кнопки для всех параметров
   vector<FitParFrame*> FitParameters;//панели с параметрами
   vector<TGGroupFrame*> GroupedParameters;//Группировка параметров по гауссианам, если фит гауссов
   void GenerateParFrame(int NPar);
   void GenerateParFrame(TFitFunction *func);
   void AnalyseFitFunctionAndCreatePanels(TFitFunction *func);
	void CreateForms();

   RootFitLib_gui(string funcName="",FitManager *m=0);
   virtual ~RootFitLib_gui();

   void CloseWindow();
   void DoText(const char *text);
   void DoSlider();
   void HandleButtons();

   ClassDef(RootFitLib_gui, 0);
};
