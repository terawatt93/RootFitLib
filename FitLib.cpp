#include "FitLib.hh"
#pragma once

void FitManager::SaveToROOT(string filename)
{
	TFile f_out(filename.c_str(),"recreate");
	for(unsigned int i=0;i<FitRes.size();i++)
	{
		f_out.WriteTObject(&(FitRes[i]->ReferenceHistogram));
		f_out.WriteTObject(&(FitRes[i]->Fit->Function));
	}
	f_out.Close();
}

void FitManager::Clear()
{
	for(unsigned int i=0;i<Functions.size();i++)
	{
		delete Functions[i];
	}
	for(unsigned int i=0;i<FitRes.size();i++)
	{
		delete FitRes[i];
	}
	Functions.resize(0);
	FitRes.resize(0);
}

void FitManager::SaveToTXT(string filename)
{
	ofstream ofs(filename);
	ofs<<"id_list: ";
	for(unsigned int i=0;i<Functions.size();i++)
	{
		ofs<<Functions[i]->id<<" ";
	}
	ofs<<"\n";
	for(unsigned int i=0;i<Functions.size();i++)
	{
		ofs<<Functions[i]->AsString(i+1)<<"\n";
	}
}
void FitManager::ReadFromTXT(string filename)
{
	Clear();
	ifstream ifs(filename);
	string line;
	vector<string> id_list;
	while(getline(ifs,line))
	{
		int pos=line.find("id_list:");
		if(pos>=0)
		{
			stringstream sstr(line.substr(pos+8,line.size()));
			while(sstr)
			{
				string id_str;
				sstr>>id_str;
				id_list.push_back(id_str);
			}

		}
	}
	for(unsigned int i=0;i<id_list.size();i++)
	{
		TFitFunction *f=new TFitFunction();
		f->id=id_list[i];
		f->ReadFromTXTFile(filename);
		if(f->parameters.size()>0)
		{
			Functions.push_back(f);
		}
	}
}
void FitManager::PrintToPDF(string filename)
{
	TCanvas *c;
	bool CreatedCanvas=false;
	gStyle->SetOptFit(11111);
	if(!gPad)
	{
		c=gPad->GetCanvas();
	}
	else
	{
		CreatedCanvas=true;
		c=new TCanvas();
	}
	c->Print((filename+"[").c_str(),"pdf");
	for(unsigned int i=0;i<FitRes.size();i++)
	{
		FitRes[i]->ReferenceHistogram.Draw("hist");
		FitRes[i]->Fit->Function.Draw("same");
		TPaveText pt(0.7,0.4,1,1);
		FitRes[i]->Fit->GenerateTPaveTextWithResults(&pt);
		pt.Draw();
		c->Print((filename).c_str(),"pdf");
	}
	c->Print((filename+"]").c_str(),"pdf");
	if(CreatedCanvas)
	{
		delete c;
	}
}

FitManager& FitManager::Instance()
{
	static FitManager s;
	return s;
}
FitManager* FitManager::GetPointer()
{
	return &(Instance());
}

TFitFunction* FitManager::FindFunction(string ID)
{
	TFitFunction *result=0;
	for(unsigned int i=0;i<Functions.size();i++)
	{
		if(Functions[i]->id==ID)
		{
			return Functions[i];
		}
	}
	return result;
}
void FitManager::SaveFitRes(TFitFunction *f,TH1 *hist)
{
	FitResult *res=0;
	for(unsigned int i=0;i<FitRes.size();i++)
	{
		if(FitRes[i]->id==f->id)
		{
			res=FitRes[i];
		}
	}
	if(!res)
	{
		res=new FitResult();
		res->id=f->id;
	}
	res->Fit=f;
	double XMin=hist->GetXaxis()->GetXmin(), XMax=hist->GetXaxis()->GetXmax();
	//диапазон гистограммы-2 диапазона фита
	double Range=f->RightBorder-f->LeftBorder;
	double HistLeft=f->LeftBorder-Range/2, HistRight=f->RightBorder+Range/2;
	
	if(HistLeft<XMin)
	{
		HistLeft=XMin;
	}
	if(HistRight>XMax)
	{
		HistRight=XMax;
	}
	
	int NBins=(HistRight-HistLeft)/hist->GetBinWidth(1);
	//cout<<"HistLeft HistRight "<<HistLeft<<" "<<HistRight<<" "<<NBins<<" "<<hist->GetBinWidth(1)<<"\n";
	res->ReferenceHistogram=TH1D(TString::Format("%s_hist",f->id.c_str()),TString::Format("%s_hist: FitResult; ",f->id.c_str()),NBins,HistLeft,HistRight);
	int BinMin=hist->GetXaxis()->FindBin(HistLeft), BinMax=hist->GetXaxis()->FindBin(HistRight);
	
	//cout<<"BinMin BinMax "<<BinMin<<" "<<BinMax<<"\n";
	
	int BinIterator=1;
	for(int i=BinMin;i<=BinMax;i++)
	{
		res->ReferenceHistogram.SetBinContent(BinIterator,hist->GetBinContent(i));
		res->ReferenceHistogram.SetBinError(BinIterator,hist->GetBinError(i));
		BinIterator++;
	}
	FitRes.push_back(res);
	
}
TFitFunction* FitManager::BookFunction(string InputStr,bool AddNew)
{
	TFitFunction *f=new TFitFunction();
	f->FromString(InputStr);
	if(AddNew)
	{
		TFitFunction *ff=FindFunction(f->id);
		string id_str=f->id;
		int iterator=0;
		while(ff)
		{
			id_str+="_"+to_string(iterator);
			ff=FindFunction(id_str);
			iterator++;
		}
		f->id=id_str;
		Functions.push_back(f);
	}
	else
	{
		TFitFunction *ff=FindFunction(f->id);
		if(ff)
		{
			for(unsigned int i=0;i<Functions.size();i++)
			{
				if(Functions[i]==ff)
				{
					delete ff;
					Functions[i]=f;
				}
			}
			
		}
		else
		{
			Functions.push_back(f);
		}
	}
	return f;
}

vector<string> SplitStr(string s, string delimiter)
{
	vector<string> result;
	size_t pos = 0;
	std::string token;
	while ((pos = s.find(delimiter)) != std::string::npos)
	{
   		token = s.substr(0, pos);
   		result.push_back(token);
   		s.erase(0, pos + delimiter.length());
	}
	if(s.size()>0)
	result.push_back(s);
	return result;
}

string TF1Parameter::AsString()
{
	string result=string(TString::Format("%s par: %d",fFunction->id.c_str(),ParNumber).Data());
	if(Limited)
	{
		result+=" limited ";
	}
	else
	{
		result+=" not_limited ";
	}
	if(Fixed)
	{
		result+=" fixed ";
	}
	else
	{
		result+=" free ";
	}
	result+=string(TString::Format(" %f %f %f %f %s",Value,MinLimit,MaxLimit,Error,ParName.Data()).Data());
	return result;
}

void TFitFunction::SetParameters()
{
	for(unsigned int i=0;i<parameters.size();i++)
	{
		Function.SetParameter(parameters[i].ParNumber,parameters[i].Value);
		if(parameters[i].Fixed)
		{
			Function.FixParameter(parameters[i].ParNumber,parameters[i].Value);
		}
		else
		{
			if(parameters[i].Limited)
			{
				Function.SetParLimits(parameters[i].ParNumber,parameters[i].MinLimit,parameters[i].MaxLimit);
			}
			else
			{
				Function.SetParLimits(parameters[i].ParNumber,-1e7,1e7);
			}
		}
	}
}

void TFitFunction::GetParameters()
{
	for(unsigned int i=0;i<parameters.size();i++)
	{
		parameters[i].Value=Function.GetParameter(i);
		parameters[i].Error=Function.GetParError(i);
		if(FitManager::GetPointer()->MultiplyToChi2)
		{
			parameters[i].Error*=sqrt(Function.GetChisquare()/Function.GetNDF());
			parameters[i].Chi2TakenIntoAccount=true;
		}
		else
		{
			parameters[i].Chi2TakenIntoAccount=false;
		}
	}
}
string TFitFunction::AsString(int PageNo)
{

	string result;
	if(PageNo==0)
	{
		result=string(TString::Format("%s func: %s %f %f\n",id.c_str(),func_str.c_str(),LeftBorder,RightBorder).Data());
	}
	else
	{
		result=string(TString::Format("%s func: %s %f %f %d\n",id.c_str(),func_str.c_str(),LeftBorder,RightBorder,PageNo).Data());
	}
	
	for(unsigned int i=0;i<parameters.size();i++)
	{
		result+=parameters[i].AsString()+"\n";
	}
	return result;
}

TF1* TFitFunction::GetFunction()
{
	return &Function;
}
void  TFitFunction::Fit(TH1 *h, bool KeepResults)
{
	SetParameters();
	h->Fit(&Function,"R","",LeftBorder,RightBorder);
	GetParameters();
	if(KeepResults)
	{
		FitManager::GetPointer()->SaveFitRes(this,h);
	}
}
void  TFitFunction::AssignPointers()
{
	for(unsigned int i=0;i<parameters.size();i++)
	{
		parameters[i].fFunction=this;
	}	
}

double TFitFunction::GetParameterValue(int number)
{
	if((number<(int)parameters.size())&&(number>=0))
	{
		return parameters[number].Value;
	}
	return nan("NAN");
}
double TFitFunction::GetParError(int number)
{
	if((number<(int)parameters.size())&&(number>=0))
	{
		return parameters[number].Error;	
	}
	return nan("NAN");
}

void TFitFunction::ReadFromTXTFile(string filename)
{
	ifstream ifs(filename);
	string line;
	while(getline(ifs,line))
	{
		stringstream sstr(line);
		string _id;
		sstr>>_id;
		if((id==_id)&&((line.find("func")!=string::npos)||(line.find("par")!=string::npos)))
		{
			while(sstr)
			{
				string key;
				sstr>>key;
				if(key=="func:")
				{
					sstr>>func_str>>LeftBorder>>RightBorder;
					Function=TF1(TString::Format("fit_%s",id.c_str()),func_str.c_str(),LeftBorder,RightBorder);
				}
				if(key=="par:")
				{
					TF1Parameter par;
					par.fFunction=this;
					int parNum;
					string limited,fixed;
					sstr>>parNum>>limited>>fixed;
					par.ParNumber=parNum;
					if(limited=="limited")
					{
						par.Limited=true;
					}
					else
					{
						par.Limited=false;
					}
					if(fixed=="fixed")
					{
						par.Fixed=true;
					}
					else
					{
						par.Fixed=false;
					}
					sstr>>par.Value>>par.MinLimit>>par.MaxLimit>>par.Error>>par.ParName;
					if(parNum>=(int)parameters.size())
					{
						parameters.resize(parNum+1);
					}
					parameters[parNum]=par;
				}
			}
			SetParameters();
		}
	}
	ifs.close();
}

void TFitFunction::GenerateTPaveTextWithResults(TPaveText* p)
{
	if(!p)
	{
		cout<<"This is TFitFunction::GenerateTPaveTextWithResults(): invalid pointer to TPaveText!\n";
	}
	p->AddText(TString::Format("ID: %s",id.c_str()));
	p->AddText(TString::Format("#chi^2/NDF: %.2f",Function.GetChisquare()/Function.GetNDF()));
	for(unsigned int i=0;i<parameters.size();i++)
	{
		TString addition=TString::Format("p[%d]: %s %.3f#pm%.3f (%.3f...%.3f)",i,parameters[i].ParName,parameters[i].Value,parameters[i].Error,parameters[i].MinLimit,parameters[i].MaxLimit);
		if(parameters[i].Chi2TakenIntoAccount)
		{
			addition+=" #chi^2/NDF incl";
		}
		p->AddText(addition);
	}
}

void TFitFunction::FromString(string input)
{
	vector<string> strings=SplitStr(input,";");
	if(strings.size()>0)
	{
		stringstream sstr(strings[0]);
		sstr>>id>>func_str>>LeftBorder>>RightBorder;
		Function=TF1(TString::Format("fit_%s",id.c_str()),func_str.c_str(),LeftBorder,RightBorder);
		parameters.resize(0);
	}
	for(unsigned int i=1; i<strings.size();i++)
	{

		TString ts(strings[i].c_str());
		TF1Parameter par;
		if(ts.Index("limited")>=0)
		{
			par.Limited=true;
		}
		if(ts.Index("fixed")>=0)
		{
			par.Fixed=true;
		}
		if(ts.Index("Name:")>=0)
		{
			int space_iterator=0;
			TString Name_str;
			for(int i=ts.Index("Name:");i<ts.Length();i++)
			{
				if(ts[i]==' ')
				{
					space_iterator++;
				}
				if(space_iterator==1)
				{
					Name_str+=ts[i];
				}
				else if(space_iterator>1)
				{
					break;
				}
			}
			ts.ReplaceAll("Name","");
			ts.ReplaceAll("Name_str","");
			par.ParName=Name_str;
		}
		ts.ReplaceAll("limited","");
		ts.ReplaceAll("fixed","");
		stringstream sstr(ts.Data());
		
		par.fFunction=this;
		//int parNum;
		string limited,fixed;
		sstr>>par.ParNumber;
		sstr>>par.Value>>par.MinLimit>>par.MaxLimit;
		par.fFunction=this;
		parameters.push_back(par);
		if(parameters.size()>par.ParNumber)
		{
			parameters[par.ParNumber]=par;
		}
		else
		{
			parameters.resize(par.ParNumber+1);
			parameters[par.ParNumber]=par;
		}
	}
	SetParameters();
}

void TFitFunctionComponent::FromString(string input)
{
	vector<string> strings=SplitStr(input,";");
	if(strings.size()>0)
	{
		stringstream sstr(strings[0]);
		sstr>>id>>func_str>>LeftBorder>>RightBorder;
		Function=TF1(TString::Format("%s",id.c_str()),func_str.c_str(),LeftBorder,RightBorder);
	}
	if(fFunction)
	{
		for(unsigned int i=1; i<strings.size();i++)
		{

			TString ts(strings[i].c_str());
			TF1Parameter par;
			if(ts.Index("limited")>=0)
			{
				par.Limited=true;
			}
			if(ts.Index("fixed")>=0)
			{
				par.Fixed=true;
			}
			if(ts.Index("Name:")>=0)
			{
				int space_iterator=0;
				TString Name_str;
				for(int i=ts.Index("Name:");i<ts.Length();i++)
				{
					if(ts[i]==' ')
					{
						space_iterator++;
					}
					if(space_iterator==1)
					{
						Name_str+=ts[i];
					}
					else if(space_iterator>1)
					{
						break;
					}
				}
				ts.ReplaceAll("Name","");
				ts.ReplaceAll("Name_str","");
				par.ParName=Name_str;
			}
			ts.ReplaceAll("limited","");
			ts.ReplaceAll("fixed","");
			stringstream sstr(ts.Data());
			
			par.fFunction=this;
			//int parNum;
			string limited,fixed;
			sstr>>par.ParNumber;
			sstr>>par.Value>>par.MinLimit>>par.MaxLimit;
			par.fFunction=fFunction;
			if(fFunction->parameters.size()>par.ParNumber)
			{
				fFunction->parameters[par.ParNumber]=par;
			}
			else
			{
				fFunction->parameters.resize(par.ParNumber+1);
				fFunction->parameters[par.ParNumber]=par;
			}
			
		}
		fFunction->SetParameters();
	}
}