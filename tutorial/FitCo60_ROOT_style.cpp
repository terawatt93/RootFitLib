#include <FitLib.hh>

void FitCo60_ROOT_style()
{
	TFile f("spectrum.root");
	TH1F spectrum=*(TH1F*)f.Get("spectrum");
	FitManager *m=FitManager::GetPointer();
	m->ReadFromTXT("fits.txt");
	TFitFunction* fit=0;//указатель на фитирующую функцию
	fit=m->FindFunction("FitFunction");//найти среди известных функций по имени (здесь-FitFunction)
	if(!fit)//функция не найдена
	{
		
		fit=m->BookFunction("Fit","gausn(0)+pol1(3)",1300.0,1350.0);
		fit->SetParameter(0,spectrum.GetMaximum());
		fit->SetParLimits(0,0,1e6);

		fit->SetParameter(1,1332);
		fit->SetParLimits(1,1310.0,1350.0);

		fit->SetParameter(2,2);
		fit->SetParLimits(2,0,20);
	}
	fit->Fit(&spectrum,true);
	cout<<"Fit result:\n";
	cout<<"Area: "<<fit->GetParameter(0)<<" err: "<<fit->GetParError(0)<<"\n";
	cout<<"Pos: "<<fit->GetParameter(1)<<" err: "<<fit->GetParError(1)<<"\n";
	cout<<"Sigma: "<<fit->GetParameter(2)<<" err: "<<fit->GetParError(2)<<"\n";

	m->SaveToTXT("fits.txt");//сохранить в текстовый файл
	m->PrintToPDF("fits.pdf");
	m->SaveToROOT("fits.root");
}
