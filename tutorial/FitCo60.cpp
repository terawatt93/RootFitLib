#include <FitLib.hh>

void FitCo60()
{
	TFile f("spectrum.root");
	TH1F spectrum=*(TH1F*)f.Get("spectrum");
	FitManager *m=FitManager::GetPointer();
	//m->ReadFromTXT("fits.txt");
	m->ReadFromROOT("fits.root");
	TFitFunction* fit=0;//указатель на фитирующую функцию
	fit=m->FindFunction("FitFunction");//найти среди известных функций по имени (здесь-FitFunction)
	if(!fit)//функция не найдена
	{
		TString function_str;
		function_str+=TString::Format("FitFunction gausn(0)+pol1(3) %f %f;",1300.0,1350.0);//форматированный ввод: имя(пробел)функция(пробел)левая_граница(пробел)правая_граница
		function_str+=TString::Format(" 0 %f %f %f limited Name: Heigth_0;",spectrum.GetMaximum(),0.0,1.0e6);// порядок параметров: номер, значение, минимальное значение, максимальное значение, если есть ограничения, то написать "limited" 
		function_str+=TString::Format(" 1 %f %f %f limited Name: Pos_0;",1332.0,1310.0,1350.0);
		function_str+=TString::Format(" 2 %f %f %f limited Name: Sigma_0;",2.0,0.0,20.0);
		function_str+=TString::Format(" 3 %f ;",0.0);
		function_str+=TString::Format(" 4 %f",0.0);
		fit=m->BookFunction(function_str.Data());
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
