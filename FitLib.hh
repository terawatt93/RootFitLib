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
#include <TGButton.h>
#include <TRootEmbeddedCanvas.h>
#include <TGLayout.h>
#include <TGTextEntry.h>
#include <TGDoubleSlider.h>
#include <TGFrame.h>

#pragma once

using namespace std;

vector<string> SplitStr(string s, string delimiter);
class TFitFunction;
class FitResult;

TH1D CopyHistogramToTH1D(TH1 *RefHistogram,double Min, double Max);

class FitManager:public TObject
{
	public:
	static FitManager& Instance();
	static FitManager* GetPointer();

	vector<FitResult*> FitRes;
	vector<TFitFunction*> Functions;

	TFitFunction* BookFunction(string InputStr,bool AddNew=false);
	TFitFunction* BookFunction(TString Name,TString Function,double XMin,double XMax,bool AddNew=false);
	TFitFunction* FindFunction(string ID);
	void SaveFitRes(TFitFunction *f,TH1 *hist);
	void SaveToTXT(string filename);
	void ReadFromTXT(string filename);
	void ReadFromROOT(string filename);
	void PrintToPDF(string filename);
	void SaveToROOT(string filename);
	int GetPageNumberInPDF(TFitFunction *function);
	int GetPageNumberInPDF(string ID);
	bool MultiplyToChi2=true;
	private:
	FitManager() { }  // конструктор недоступен
	~FitManager() { } // и деструктор
	// необходимо также запретить копирование
	FitManager(FitManager const&); // реализация не нужна
	FitManager& operator= (FitManager const&);  // и тут
	void Clear();
	ClassDef(FitManager, 1);
};

class FitResult:public TObject
{
	public:
	string id;
	TFitFunction *Fit;
	TString RefHistogramName;
	TH1D ReferenceHistogram;
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

	ClassDef(TF1Parameter,1);
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
	ClassDef(TFitFunctionComponent,1);
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
	double GetParError(int number);
	void FromString(string input);
	
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
	void Fit(TH1 *h, bool KeepResults=true);
	void AssignPointers();
	void GenerateTLegendWithResults(TLegend* p);
	int GetNpar();
	FitManager *fManager=0;//!
	FitResult *fFitResult=0;//!
	ClassDef(TFitFunction,1);
};

class GUIFit:public TGMainFrame
{
	public:
	TRootEmbeddedCanvas *fCanvas;
	TGHorizontalFrame *fMainFrame;
	TGLayoutHints *fMainLayout;
	//TFitFunction *function;
	//TH1D *ReferenceHistogram;
	GUIFit();
	//virtual ~GUIFit();
	//void CloseWindow();
	
	ClassDef(GUIFit, 1);
};
