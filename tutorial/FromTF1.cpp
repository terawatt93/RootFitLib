#include <FitLib.hh>

void FromTF1()
{
	TFile f("spectrum.root");
	TH1F spectrum=*(TH1F*)f.Get("spectrum");
	TF1 FitFunction("FitTF1","gausn(0)+gausn(3)+pol1(6)",1150.0,1350.0);
	FitFunction.SetParameter(0,spectrum.GetMaximum());
	FitFunction.SetParLimits(0,0,1e6);
	FitFunction.SetParameter(1,1175);
	FitFunction.SetParLimits(1,1165.0,1180.0);
	FitFunction.SetParameter(2,2);
	FitFunction.SetParLimits(2,0,20);
	
	FitFunction.SetParameter(3,spectrum.GetMaximum());
	FitFunction.SetParLimits(3,0,1e6);
	FitFunction.SetParameter(4,1332);
	FitFunction.SetParLimits(4,1310.0,1350.0);
	FitFunction.SetParameter(5,2);
	FitFunction.SetParLimits(5,0,20);
	
	spectrum.Fit(&FitFunction,"R","",1300.0,1350.0);
	FitManager *m=FitManager::GetPointer();
	TFitFunction *fit=m->BookFunction(&FitFunction);
	fit->GenerateComponents();
	
	m->AttachHistogram(fit,&spectrum);
	
	m->SaveToTXT("FromTF1.txt");//сохранить в текстовый файл
	m->PrintToPDF("FromTF1.pdf");
	m->SaveToROOT("FromTF1.root");
}
