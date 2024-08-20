
void test()
{
	TString function_str;
	function_str+=TString::Format("FitFunction gausn(0)+pol1(3) %f %f;",1300.0,1350.0);//форматированный ввод: имя(пробел)функция(пробел)левая_граница(пробел)правая_граница
	function_str+=TString::Format(" 0 %f %f %f limited;",100.0,0.0,1.0e6);// порядок параметров: номер, значение, минимальное значение, максимальное значение, если есть ограничения, то написать "limited" 
	function_str+=TString::Format(" 1 %f %f %f limited;",1332.0,1310.0,1350.0);
	function_str+=TString::Format(" 2 %f %f %f limited;",2.0,0.0,20.0);
	function_str+=TString::Format(" 3 %f ;",0.0);
	function_str+=TString::Format(" 4 %f",0.0);
	FitManager *m=FitManager::GetPointer();
	TFitFunction* fit=m->BookFunction(function_str.Data());
	cout<<fit->AsString()<<"\n";
	TFitFunction* fit2=new TFitFunction();
	fit2->FromString(fit->AsString());
	fit2->Draw();
}

