
#include <sstream>
#include <iostream>
#include <fstream>
#include <TObject.h>
#include <TRandom.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TF1.h>
#include <TFile.h>
#include <TGraph.h>
#include <TGraph2D.h>
#include <TMultiGraph.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TObject.h>
#include <TPaveText.h>
#include <TLatex.h>
#include <TGraphErrors.h>
#include <thread>  
#include <TVectorD.h> 
#include <TROOT.h> 
#include <TStyle.h> 


//GUI:
#include "TGButton.h"
#include "TRootEmbeddedCanvas.h"
#include "TGLayout.h"
#include "TGNumberEntry.h"
#include "TGLabel.h"
//#include "TF1.h"
#include "TMath.h"
//#include "TCanvas.h"
#include "TGTextEntry.h"
#include "TGTripleSlider.h"
#include "TGButton.h"
#include "TGFrame.h"
#include "TLine.h"
#include "TApplication.h"
#pragma once

class FitParFrame;
class RootFitLib_gui;
//int Color(int Num);


using namespace std;

vector<string> SplitStr(string s, string delimiter);
class TFitFunction;
class FitResult;

class TH1DTracked:public TH1D//класс, сохраняющий операции, проделанные над гистограммой
{
	public:
	TH1DTracked():TH1D() { }
	TH1DTracked(const char *name,const char *title,Int_t nbinsx,Double_t xlow,Double_t xup):TH1D(name,title,nbinsx,xlow,xup) { }
	TH1DTracked(const char *name,const char *title,Int_t nbinsx,const Float_t  *xbins):TH1D(name,title,nbinsx,xbins) { }
	TH1DTracked(const char *name,const char *title,Int_t nbinsx,const Double_t *xbins):TH1D(name,title,nbinsx,xbins) { }
	
	TH1 *ParentHistogram=0;//!
	TString ParentName;
	vector<string> Operations;
	virtual TH1 * 	Rebin (Int_t ngroup=2, const char *newname="", const Double_t *xbins=nullptr);// *MENU*
	virtual void 	Smooth (Int_t ntimes=1, Option_t *option="");// *MENU*
	virtual void 	Scale (Double_t c1=1, Option_t *option="");// *MENU*
	//void Extend(Double_t xmin,Double_t xmax);// *MENU*
	string ToString();
	void GetInfoFromString(string str);
	void ApplyOperations();
	ClassDef(TH1DTracked,1)
};

TH1D CopyHistogramToTH1D(TH1 *RefHistogram,double Min=0, double Max=0);

TH1DTracked CopyHistogramToTH1DTracked(TH1 *RefHistogram,double Min, double Max,TString Name,TString Title);
TH1DTracked* CopyHistogramToTH1DTracked_p(TH1 *RefHistogram,double Min, double Max,TString Name,TString Title);//возвращает указатель


class FitManager:public TObject
{
	public:
	static FitManager& Instance();
	static FitManager* GetPointer();

	TFile *file_for_work=0;
	TString FileName="";

	vector<FitResult*> FitRes;
	vector<TFitFunction*> Functions;
	vector<TH1DTracked*> ParentHistograms;

	TFitFunction* BookFunction(string InputStr,bool AddNew=false);
	TFitFunction* BookFunction(TString Name,TString Function,double XMin,double XMax,bool AddNew=false);
	TFitFunction* FindFunction(string ID);
	void SaveFitRes(TFitFunction *f,TH1 *hist);
	void SaveToTXT(string filename);
	void ReadFromTXT(string filename);
	void ReadFromROOT(string filename="");
	void UpdateInROOT(string filename="");
	
	void ReadFromROOT(TFile *f);
	void UpdateInROOT(TFile *f);
	void ReadParentData(string ParentData);//
	void PrintToPDF(string filename="");
	void SaveToROOT(string filename="");
	void SaveToROOT(TFile *f);
	int GetPageNumberInPDF(TFitFunction *function);
	int GetPageNumberInPDF(string ID);
	//void AddParentHistogram(TH1* histogram);
	bool MultiplyToChi2=true;
	private:
	FitManager() { }  // конструктор недоступен
	~FitManager() { } // и деструктор
	// необходимо также запретить копирование
	FitManager(FitManager const&); // реализация не нужна
	FitManager& operator= (FitManager const&);  // и тут
	void Clear();
	ClassDef(FitManager, 1)
};

class FitResult:public TObject
{
	public:
	string id;
	TFitFunction *Fit;
	TString RefHistogramName;
	//TH1D ReferenceHistogram;
	TH1DTracked ReferenceHistogram;
	void ExtendHistogram(double xmin, double xmax);
};


class TF1Parameter:public TObject
{
	public:
	double Value=0,MinLimit=0,MaxLimit=0,Error=0;
	int ParNumber=0;
	bool Fixed=false;
	bool Limited=false;
	TString ParName="";
	bool Chi2TakenIntoAccount=false;
	string AsString();
	TFitFunction *fFunction=0;

	ClassDef(TF1Parameter,1)
};

class TFitFunctionComponent:public TObject
{
	public:
	TF1 Function;
	string id;
	string func_str;
	double LeftBorder=20,RightBorder=100;
	TFitFunction* fFunction=0;
	vector<TF1Parameter*> ComponentParameters;
	vector<int> ParNumbersMap;
	int Color=1;
	void FromString(string input);
	ClassDef(TFitFunctionComponent,1)
};

class TFitFunction:public TObject
{
	public:
	TF1 Function;
	string id;
	string func_str;
	double LeftBorder=20,RightBorder=100;
	vector<TF1Parameter> parameters;
	void ReadFromTXTFile(string filename);
	string AsString(int PageNo=0);
	void GetParameters();
	void SetParameters();
	void SetParName(int ParNumber,TString Name);
	TString GetParName(int ParNumber);
	void SetFunction(TString Name,TString FunctionStr,double XMin,double XMax);
	double GetParameter(int number);
	double GetParameter(TString Name);
	double GetParError(int number);
	double GetParError(TString Name);
	void FromString(string input);
	
	TF1Parameter* FindParameter(TString Name);
	
	void FromStringObject(string input);//копия ReadFromTXTFile, но из строки 

	void SetParameter(int ParNumber,double Value);
	void SetParLimits(int ParNumber,double ValueMin,double ValueMax);
	
	void FixParameter(int ParNumber,double Value);
	void ReleaseParameter(int ParNumber);
	void GetRange(double &Xmin,double &Xmax);

	void SetLineColor(int Color);
	void Draw(Option_t *option = ""	);
	
	//void FromString(TString input);
	TF1 *GetFunction();
	void Fit(TH1 *h, bool KeepResults=true,TH1* Parent=0);
	void AssignPointers();
	void GenerateTLegendWithResults(TLegend* p);
	int GetNpar();
	FitManager *fManager=0;//!
	FitResult *fFitResult=0;//!
	void LaunchGUI();
	ClassDef(TFitFunction,1)
};

//GUI

class FitButtonFrame : public TGHorizontalFrame //полоса с кнопками под параметрами
{
	public:
	TGTextButton *Update,*Fit,*SaveToFile, *Next, *Prev, *Find;
	TGTextEntry *FunctionNameField;
	RootFitLib_gui *fMainFrame=0;
	TFitFunction* func;
	FitButtonFrame(TGFrame *fFrame,RootFitLib_gui *Main);
	void FUpdate();
	void FFit();
	void FSaveToFile();
	void FNext();
	void FPrev();
	void FFind();
	ClassDef(FitButtonFrame,1)
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
	
	ClassDef(FitParFrame,1)
};

class FunctionStringFrame : public TGHorizontalFrame
{
	public:
	TGLabel *FuncName;
	TGTextEntry *FuncField;
	TGNumberEntry *LeftLimit, *RightLimit;
	TGTextButton *Update, *Left,*Right;
	RootFitLib_gui *Main=0;//указатель на главное окно
	FunctionStringFrame(TGFrame *fFrame,RootFitLib_gui *Main_);
	void UpdateFitFunction();
	void UpdateValuesFromFitFunction(TFitFunction *func);
	void ClkLeft();
	void ClkRight();
	int Stage=0;
	void ProcessCanvasFunction(int event,int x,int y, TObject *selected,TCanvas *c);
	TLine *LeftBorder=0, *RightBorder=0;
	ClassDef(FunctionStringFrame,1)
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

   ClassDef(RootFitLib_gui, 1)
};


//TH1DTracked ToTrackedHistogram(TH1 *h);
