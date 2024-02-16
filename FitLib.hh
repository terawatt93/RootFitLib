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

#pragma once

using namespace std;

vector<string> SplitStr(string s, string delimiter);
class TFitFunction;
class FitResult;

class FitManager:public TObject
{
	public:
	static FitManager& Instance();
	static FitManager* GetPointer();

	vector<FitResult*> FitRes;
	vector<TFitFunction*> Functions;

	TFitFunction* BookFunction(string InputStr,bool AddNew=false);
	TFitFunction* FindFunction(string ID);
	void SaveFitRes(TFitFunction *f,TH1 *hist);
	void SaveToTXT(string filename);
	void ReadFromTXT(string filename);
	void PrintToPDF(string filename);
	void SaveToROOT(string filename);
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
	TString ParName;
	string AsString();
	TFitFunction *fFunction=0;

	ClassDef(TF1Parameter,1);
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
	double GetParameterValue(int number);
	double GetParError(int number);
	void FromString(string input);
	//void FromString(TString input);
	TF1 *GetFunction();
	void Fit(TH1 *h, bool KeepResults=true);
	void AssignPointers();
	ClassDef(TFitFunction,1);
};
