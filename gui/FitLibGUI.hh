#pragma once
#include "TGButton.h"
#include "TRootEmbeddedCanvas.h"
#include "TGLayout.h"
#include "TGNumberEntry.h"
#include "TGLabel.h"
#include "TF1.h"
#include "TMath.h"
#include "TCanvas.h"
#include "TGTextEntry.h"
#include "TGTripleSlider.h"
#include "TGButton.h"
#include "TGFrame.h"
#include "TLine.h"
#include "FitLib.hh"

class FitParFrame;
class RootFitLib_gui;
int Color(int Num);


enum ETestCommandIdentifiers {
   HId1,
   HId2,
   HId3,
   HCId1,
   HCId2,

   HSId1
};



class FitButtonFrame : public TGHorizontalFrame //полоса с кнопками под параметрами
{
	public:
	TGTextButton *Update,*Fit,*SaveToFile;
	RootFitLib_gui *fMainFrame=0;
	TFitFunction* func;
	FitButtonFrame(TGFrame *fFrame,RootFitLib_gui *Main);
	void FUpdate();
	void FFit();
	void FSaveToFile();
	ClassDef(FitButtonFrame,1);
};

class FitParFrame : public TGHorizontalFrame
{
	public:
	TGNumberEntry *ParValue,*ParError,*MinLimit,*MaxLimit;
	TGCheckButton *Fixed,*Limited;
	TGTextButton *ParName;
	TGGroupFrame* fGroup;//указатель на группу
	TF1Parameter* PointerToParameter=0;
	RootFitLib_gui *Main=0;
	FitParFrame(TGFrame *fFrame,TString ParName_="");
	void FromTFitFunction(TFitFunction *func,int ParNum);
	void ToTFitFunction(TFitFunction *func,int ParNum);
	void ClkParSet();
	void ProcessCanvasFunction(int event,int x,int y, TObject *selected,TCanvas *c);
	
	TLine *LeftBorder=0, *RightBorder=0, *Centroid=0;
	int FitStage=0;
	
	ClassDef(FitParFrame,1);
};

class FunctionStringFrame : public TGHorizontalFrame
{
	public:
	TGLabel *FuncName;
	TGTextEntry *FuncField;
	TGNumberEntry *LeftLimit, *RightLimit;
	TGTextButton *Update;
	RootFitLib_gui *Main=0;//указатель на главное окно
	FunctionStringFrame(TGFrame *fFrame,RootFitLib_gui *Main_);
	void UpdateFitFunction();
	void UpdateValuesFromFitFunction(TFitFunction *func);
	ClassDef(FunctionStringFrame,1);
};

class RootFitLib_gui : public TGMainFrame {

public:


   TRootEmbeddedCanvas *fCanvas,*fCanvas1;//!
   TGLayoutHints       *fLcan;//!
   TFitFunction                 *fFitFcn=0;//!
   TGVerticalFrame   *fVframe0, *fVframe1, *fVframe2;//!
   TGHorizontalFrame   *fHframe0, *fHframe1, *fHframe2;//!
   TGLayoutHints       *fBly, *fBfly1, *fBfly2, *fBfly3;//!
   TGTripleHSlider     *fHslider1;//!
   TGTextEntry         *fTeh1, *fTeh2, *fTeh3;//!
   TGTextBuffer        *fTbh1, *fTbh2, *fTbh3;//!
   TGCheckButton       *fCheck1, *fCheck2;//!
   FunctionStringFrame *FSFrame=0;//!
   FitManager *fFitManager=0;//!
   //панели с управлением фитами
   FitButtonFrame *FitButtons;//! управляющие кнопки для всех параметров
   vector<FitParFrame*> FitParameters;//! панели с параметрами
   vector<TGGroupFrame*> GroupedParameters;//! Группировка параметров по гауссианам, если фит гауссов
   void GenerateParFrame(int NPar);//!
   void GenerateParFrame(TFitFunction *func);//!
   void AnalyseFitFunctionAndCreatePanels(TFitFunction *func);//!
	void CreateForms();//!
	TGFrame *ActiveWidget = 0;//! указатель на активный виджет. Нужен для передачи в обработчик DoCanvas
   RootFitLib_gui(string funcName="",FitManager *m=0);
   virtual ~RootFitLib_gui();//!
   void CloseWindow();//!
   void DoText(const char *text);//!
   void DoSlider();//!
   void HandleButtons();//!
   void DoCanvas(Int_t event, Int_t x, Int_t y, TObject *selected);//!
   void (*ProcessCanvasFunction)(Int_t event, Int_t x, Int_t y, TObject *selected, TCanvas *c);//!

   ClassDef(RootFitLib_gui, 0);
};
