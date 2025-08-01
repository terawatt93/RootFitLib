#include "FitLib.hh"
#include <TKey.h>
#include "Parser.cpp"
#pragma once

using namespace std;

int ColorT(int Num)
{
	vector<int> colors={2,3,4,6,7,8,9,12,16,23,28,30,32,36,38,41,45,46};
	if(Num>=colors.size())
	{
		Num=Num%colors.size();
	}
	return colors[Num];
}

TH1DTracked CopyHistogramToTH1DTracked(TH1 *RefHistogram,double Min, double Max,TString Name,TString Title)
{
	double XMin=RefHistogram->GetXaxis()->GetXmin(), XMax=RefHistogram->GetXaxis()->GetXmax();
	//диапазон гистограммы-2 диапазона фита
	if(Min<XMin)
	{
		Min=XMin;
	}
	if(Max>XMax)
	{
		Max=XMax;
	}
	if(Min==Max)
	{
		Min=XMin;
		Max=XMax;
	}
	int NBins=ceil((Max-Min)/RefHistogram->GetBinWidth(1));
	//cout<<"HistLeft HistRight "<<HistLeft<<" "<<HistRight<<" "<<NBins<<" "<<hist->GetBinWidth(1)<<"\n";
	TH1DTracked result(Name,Title,NBins,Min,Max);
	int BinMin=RefHistogram->GetXaxis()->FindBin(Min), BinMax=RefHistogram->GetXaxis()->FindBin(Max);
	
	//cout<<"BinMin BinMax "<<BinMin<<" "<<BinMax<<"\n";
	
	int BinIterator=1;
	for(int i=BinMin;i<=BinMax;i++)
	{
		result.SetBinContent(BinIterator,RefHistogram->GetBinContent(i));
		result.SetBinError(BinIterator,RefHistogram->GetBinError(i));
		BinIterator++;
	}
	result.ParentHistogram=RefHistogram;
	return result;
}

TH1DTracked* CopyHistogramToTH1DTracked_p(TH1 *RefHistogram,double Min, double Max,TString Name,TString Title)
{
	if(!RefHistogram)
	{
		return 0;
	}
	double XMin=RefHistogram->GetXaxis()->GetXmin(), XMax=RefHistogram->GetXaxis()->GetXmax();
	//диапазон гистограммы-2 диапазона фита
	if(Min<XMin)
	{
		Min=XMin;
	}
	if(Max>XMax)
	{
		Max=XMax;
	}
	if(Min==Max)
	{
		Min=XMin;
		Max=XMax;
	}
	
	int NBins=ceil((Max-Min)/RefHistogram->GetBinWidth(1));
	//cout<<"HistLeft HistRight "<<HistLeft<<" "<<HistRight<<" "<<NBins<<" "<<hist->GetBinWidth(1)<<"\n";
	TH1DTracked *result=new TH1DTracked(Name,Title,NBins,Min,Max);
	int BinMin=RefHistogram->GetXaxis()->FindBin(Min), BinMax=RefHistogram->GetXaxis()->FindBin(Max);
	
	//cout<<"BinMin BinMax "<<BinMin<<" "<<BinMax<<"\n";
	
	int BinIterator=1;
	for(int i=BinMin;i<=BinMax;i++)
	{
		result->SetBinContent(BinIterator,RefHistogram->GetBinContent(i));
		result->SetBinError(BinIterator,RefHistogram->GetBinError(i));
		BinIterator++;
	}
	result->ParentHistogram=RefHistogram;
	return result;
}
void TH1DTracked::GetInfoFromString(string str)
{
	vector<string> info=SplitStr(str,";");
	if(info.size()>1)
	{
		stringstream sstr_tmp(info[1]);
		string tmp;
		sstr_tmp>>tmp>>ParentName;
		if(info.size()>2)
		{
			Operations=SplitStr(info[2],"!");
		}
		
	}
}
string TH1DTracked::ToString()
{
	stringstream sstr;
	sstr<<"id: "<<GetName()<<";Parent: "<<ParentName<<";Operations:";
	for(unsigned int i=0;i<Operations.size();i++)
	{
		sstr<<Operations[i]<<"!";
	}
	return sstr.str();
}

void TH1DTracked::ApplyOperations()
{
	for(unsigned int i=0;i<Operations.size();i++)
	{
		stringstream sstr(Operations[i]);
		string command;
		double argument;
		sstr>>command>>argument;
		//cout<<"command: "<<command<<" "<<argument<<" "<<i<<"\n";
		if(command=="Rebin")
		{
			if(argument>1)
			TH1::Rebin(int(argument));
		}
		if(command=="Smooth")
		{
			if(argument>1)
			TH1::Smooth(int(argument));
		}
		if(command=="Scale")
		{
			if(argument>1)
			TH1::Scale(argument);
		}
	}
}

void TH1DTracked::ApplyOperations(TH1* h)
{
	for(unsigned int i=0;i<Operations.size();i++)
	{
		stringstream sstr(Operations[i]);
		string command;
		double argument;
		sstr>>command>>argument;
		//cout<<"command: "<<command<<" "<<argument<<" "<<i<<"\n";
		if(command=="Rebin")
		{
			if(argument>1)
			h->Rebin(int(argument));
		}
		if(command=="Smooth")
		{
			if(argument>1)
			h->Smooth(int(argument));
		}
		if(command=="Scale")
		{
			if(argument>1)
			h->Scale(argument);
		}
	}
}

/*void TH1DTracked::Extend(Double_t xmin,Double_t xmax)
{
	double XMin=GetXaxis()->GetXmin(), XMax=GetXaxis()->GetXmax();//текущие пределы
	int Integr=Integral();
	double BinWidth=GetBinWidth();
	if(!ParentHistogram)
	{
		cout<<"This is TH1DTracked::Extend(Double_t xmin,Double_t xmax): cannot extend histogram because pointer to Parent is invalid!\n";
		return;
	}
	if(xmin==xmax)
	{
		xmin=XMin;
		xmax=XMax;
	}
	if(xmin<XMin)
	{
		xmin=XMin;
	}
	if(xmax>XMax)
	{
		xmax=XMax;
	}
	
}*/

TH1D CopyHistogramToTH1D(TH1 *RefHistogram,double Min, double Max)
{
	if((!RefHistogram))
	{
		return TH1D();
	}
	if(RefHistogram->GetNbinsX()<=1)
	{
		return TH1D();
	}
	double XMin=RefHistogram->GetXaxis()->GetXmin(), XMax=RefHistogram->GetXaxis()->GetXmax();
	if(Min==Max)
	{
		Min=XMin;
		Max=XMax;
	}
	if(Min<XMin)
	{
		Min=XMin;
	}
	if(Max>XMax)
	{
		Max=XMax;
	}
	
	int NBins=ceil((Max-Min)/RefHistogram->GetBinWidth(1));
	//cout<<"HistLeft HistRight "<<HistLeft<<" "<<HistRight<<" "<<NBins<<" "<<hist->GetBinWidth(1)<<"\n";
	TH1D result(RefHistogram->GetName(),RefHistogram->GetTitle(),NBins,Min,Max);
	int BinMin=RefHistogram->GetXaxis()->FindBin(Min), BinMax=RefHistogram->GetXaxis()->FindBin(Max);
	
	//cout<<"BinMin BinMax "<<BinMin<<" "<<BinMax<<"\n";
	
	int BinIterator=1;
	for(int i=BinMin;i<=BinMax;i++)
	{
		result.SetBinContent(BinIterator,RefHistogram->GetBinContent(i));
		result.SetBinError(BinIterator,RefHistogram->GetBinError(i));
		BinIterator++;
	}
	return result;
}

void FitResult::ExtendHistogram(double xmin, double xmax)
{
	//cout<<"xmin "<<xmin<<" xmax "<<xmax<<"\n";
	double BinWidth=ReferenceHistogram.GetBinWidth(1);
	if(!ReferenceHistogram.ParentHistogram)
	{
		cout<<"This is FitResult::ExtendHistogram(Double_t xmin,Double_t xmax): cannot extend histogram because pointer to Parent is invalid!\n";
		return;
	}
	//cout<<"1\n";
	
	double XMin=ReferenceHistogram.ParentHistogram->GetXaxis()->GetXmin(), XMax=ReferenceHistogram.ParentHistogram->GetXaxis()->GetXmax();//текущие пределы
	//int Integr=ReferenceHistogram.Integral();
	//cout<<"2\n";
	if(xmin==xmax)
	{
		xmin=XMin;
		xmax=XMax;
	}
	if(xmin<XMin)
	{
		xmin=XMin;
	}
	if(xmax>XMax)
	{
		xmax=XMax;
	}
	//cout<<"3\n";
	//double PrevBinWidth=ReferenceHistogram.GetBinWidth(1);
	
	vector<string> Operations=ReferenceHistogram.Operations;
	//cout<<"4\n";
	TH1* Parent=ReferenceHistogram.ParentHistogram;
	//cout<<"5\n";
	ReferenceHistogram=CopyHistogramToTH1DTracked(ReferenceHistogram.ParentHistogram,xmin,xmax,ReferenceHistogram.GetName(),ReferenceHistogram.GetTitle());
	//cout<<"6\n";
	ReferenceHistogram.ParentHistogram=Parent;
	//cout<<"7\n";
	ReferenceHistogram.Operations=Operations;
	//cout<<"8\n";
	ReferenceHistogram.ApplyOperations();
	//cout<<"9\n";
	double Rebin=ceil(int(BinWidth/ReferenceHistogram.GetBinWidth(1)*10)/10);
	//cout<<"Rebin:"<<Rebin<<" "<<BinWidth/ReferenceHistogram.GetBinWidth(1)<<"\n";
	ReferenceHistogram.Rebin(Rebin);
	//cout<<"10\n";
}

void FitManager::ReadParentData(string ParentData)
{
	/*vector<string> id_;
	for(unsigned int i=0;i<FitRes.size();i++)
	{
		id_.push_back(FitRes[i].ReferenceHistogram.GetName());
	}*/
	stringstream sstr(ParentData);
	string line;
	while(getline(sstr,line))
	{
		for(unsigned int i=0;i<FitRes.size();i++)
		{
			vector<string> splitted=SplitStr(line,";");
			if(splitted.size()>0)
			{
				if(splitted[0]==("id: "+string(FitRes[i]->ReferenceHistogram.GetName())))
				{
					FitRes[i]->ReferenceHistogram.GetInfoFromString(line);
				}
			}
		}
	}
}

void FitManager::SaveToROOT(TFile *f_out)
{
	if(!f_out)
	{
		f_out=file_for_work;
	}
	else
	{
		file_for_work=f_out;
	}
	if(!file_for_work)
	{
		cout<<"This is FitManager::SaveToROOT(TFile *f_out): both pointers (f_out) и file_for_work are invalid! Returned\n";
		return;
	}
	f_out->ReOpen("UPDATE");
	for(unsigned int i=0;i<FitRes.size();i++)
	{
		TH1D hist=CopyHistogramToTH1D(&(FitRes[i]->ReferenceHistogram));
		f_out->WriteTObject(&hist);
		f_out->WriteTObject(&(FitRes[i]->Fit->Function));
		/*cout<<"FitManager::SaveToROOT::"<<FitRes[i]->ReferenceHistogram.GetName()<<"\n";
		if(FitRes[i]->ReferenceHistogram.ParentHistogram)
		{
			cout<<"FitManager::SaveToROOT::parent:"<<FitRes[i]->ReferenceHistogram.GetName()<<"\n";
			TH1D hist_ref=CopyHistogramToTH1D((FitRes[i]->ReferenceHistogram.ParentHistogram));
			f_out->WriteTObject(&hist_ref);
		}*/
	}
	for(unsigned int i=0;i<ParentHistograms.size();i++)
	{
		TH1D hist_ref=CopyHistogramToTH1D(ParentHistograms[i]);
		f_out->WriteTObject(&hist_ref);
	}
	stringstream ofs;
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
	string result=ofs.str();
	f_out->WriteObject(&result,"FitFunctionsList");
	
	stringstream ofs_parent;
	for(unsigned int i=0;i<FitRes.size();i++)
	{
		ofs_parent<<FitRes[i]->ReferenceHistogram.ToString()<<"\n";
	}
	string parent_result=ofs_parent.str();
	f_out->WriteObject(&parent_result,"ParentList");
	
}

void FitManager::SaveToROOT(string filename)
{
	
	TFile f_out(filename.c_str(),"recreate");
	SaveToROOT(&f_out);
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

void FitManager::ReadFromROOT(string filename)
{
	if(filename=="")
	{
		filename=string(FileName.Data());
	}
	TFile f(filename.c_str());
	ReadFromROOT(&f);
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

void FitManager::UpdateInROOT(string filename)
{
	if(filename=="")
	{
		filename=string(FileName.Data());
	}
	TFile f(filename.c_str(),"update");
	UpdateInROOT(&f);
	f.Close();
}
void FitManager::UpdateInROOT(TFile *f_out)
{
	if(!f_out)
	{
		f_out=file_for_work;
	}
	if(!file_for_work)
	{
		cout<<"This is FitManager::UpdateInROOT(TFile *f_out): both pointers (f_out) и file_for_work are invalid! Returned\n";
		return;
	}
	f_out->ReOpen("update");
	for(unsigned int i=0;i<FitRes.size();i++)
	{
		//cout<<"FitRes: "<<FitRes[i]->Fit->id<<"\n";
		TH1D hist=CopyHistogramToTH1D(&(FitRes[i]->ReferenceHistogram));
		f_out->WriteObject(&hist,hist.GetName(),"overwrite");
		f_out->WriteObject(&(FitRes[i]->Fit->Function),FitRes[i]->Fit->Function.GetName(),"overwrite");
		if(FitRes[i]->ReferenceHistogram.ParentHistogram)
		{
			TH1D hist_ref=CopyHistogramToTH1D((FitRes[i]->ReferenceHistogram.ParentHistogram));
			f_out->WriteTObject(&hist_ref);
		}
	}
	stringstream ofs;
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
	string result=ofs.str();
	f_out->WriteObject(&result,"FitFunctionsList","overwrite");
	
	stringstream ofs_parent;
	for(unsigned int i=0;i<FitRes.size();i++)
	{
		ofs_parent<<FitRes[i]->ReferenceHistogram.ToString()<<"\n";
	}
	string parent_result=ofs_parent.str();
	f_out->WriteObject(&parent_result,"ParentList","overwrite");
}
void FitManager::ReadFromROOT(TFile *f)
{
	if(!f)
	{
		cout<<"This is FitManager::ReadFromROOT: pointer to TFile is invalid. Returned;\n";
		return;
	}
	file_for_work=f;
	if(f->Get("FitFunctionsList"))
	{
		//cout<<"1:\n";
		string FitList=*(f->Get<string>("FitFunctionsList"));
		Clear();
		stringstream ifs(FitList);
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
			TFitFunction *ff=new TFitFunction();
			if(id_list[i].size()>0)
			{
				ff->id=id_list[i];
				ff->FromStringObject(FitList);
				//cout<<"id_list[i]:"<<id_list[i]<<"\n";
				ff->FromTF1((TF1*)f->Get(id_list[i].c_str()));
				if(ff->parameters.size()>0)
				{
					Functions.push_back(ff);
				}
			}
		}
	}
	
	TIter keyList(f->GetListOfKeys());
	TKey *key;
	while ((key = (TKey*)keyList()))
	{
		//cout<<"2:\n";
		if(string(key->GetClassName())=="TF1")
		{
			TString id(key->GetName());
			id.ReplaceAll("fit_","");
			TFitFunction *ff=FindFunction(id.Data());
			if(!ff)
			{
				ff=new TFitFunction();
				ff->id=id.Data();
				ff->Function=*((TF1*)f->Get(key->GetName()));
				ff->Function.GetRange(ff->LeftBorder,ff->RightBorder);
				ff->func_str=ff->Function.GetTitle();
				
				ff->GetParameters();
				Functions.push_back(ff);
			}
			
			TString HistName=TString::Format("%s_hist",id.Data());
			HistName.ReplaceAll("fit_","");
			TH1D *h=(TH1D*)f->Get(HistName);
			if(h)
			{
				FitResult* FR=new FitResult();
				FR->id=ff->id;
				FR->Fit=ff;
				FR->RefHistogramName=HistName;
				FR->ReferenceHistogram=CopyHistogramToTH1DTracked(h,h->GetXaxis()->GetXmin(),h->GetXaxis()->GetXmax(),h->GetName(),h->GetTitle());
				ff->fFitResult=FR;
				ff->fManager=this;
				FitRes.push_back(FR);
			}
		}
	}
	if(f->Get("ParentList"))
	{
		string ParentList=*(f->Get<string>("ParentList"));
		ReadParentData(ParentList);
		for(unsigned int i=0;i<FitRes.size();i++)
		{
			TString ParentName=FitRes[i]->ReferenceHistogram.ParentName;
			if(ParentName=="")
			{
				FitRes[i]->ReferenceHistogram.ParentHistogram=0;
				continue;
			}
			TH1* ParHist=(TH1*)f->Get(ParentName);
			if(ParHist)
			{
				TH1DTracked *hPar=CopyHistogramToTH1DTracked_p(ParHist,0,0,ParHist->GetName(),ParHist->GetTitle());
				ParentHistograms.push_back(hPar);
				FitRes[i]->ReferenceHistogram.ParentHistogram=hPar;
			}
		}
	}
	
}

void FitManager::PrintToPDF(string filename)
{
	TCanvas *c=0;
	//bool CreatedCanvas=false;
	gStyle->SetOptStat(0);
	gStyle->SetOptFit(11111);
	/*if(gPad)
	{
		c=gPad->GetCanvas();
	}
	else
	{
		CreatedCanvas=true;*/
		c=new TCanvas();
	//}
	c->Print((filename+"[").c_str(),"pdf");
	
	for(unsigned int i=0;i<FitRes.size();i++)
	{
		c->cd();
		FitRes[i]->ReferenceHistogram.Draw("hist");
		FitRes[i]->Fit->Function.Draw("same");
		//TPaveText *pt=new TPaveText(0.7,0.4,1,1);
		//pt->AddText("aaaa");
		TLegend leg(0.7,0.4,1,1);
		leg.AddEntry(&(FitRes[i]->Fit->Function),"fit","l");
		FitRes[i]->Fit->GenerateTLegendWithResults(&leg);
		//pt->Draw();
		//gPad->BuildLegend();
		//leg.AddEntry((TObject*)0,"aaa","");
		leg.Draw();
		gPad->Modified();
		gPad->Update();
		c->Print((filename).c_str(),"pdf");
	}
	c->Print((filename+"]").c_str(),"pdf");
	/*if(CreatedCanvas)
	{
		delete c;
	}*/
}

int FitManager::GetPageNumberInPDF(TFitFunction *function)
{
	for(unsigned int i=0;i<Functions.size();i++)
	{
		if(Functions[i]==function)
		{
			return i+1;
		}
	}
	return -1;
}
int FitManager::GetPageNumberInPDF(string ID)
{
	for(unsigned int i=0;i<Functions.size();i++)
	{
		if(Functions[i]->id==ID)
		{
			return i+1;
		}
	}
	return -1;
}

FitManager& FitManager::Instance()
{
	static FitManager s;
	return s;
}

//static FitManager* GetPointer(TFile *file=0);
//static FitManager* GetPointer(string str);

FitManager* FitManager::GetPointer(TFile *file)
{
	FitManager *m=&(Instance());
	
	if(file)
	{
		m->ReadFromROOT(file);
	}
	return m;
}
FitManager* FitManager::GetPointer(string str)
{
	TFile f(str.c_str());
	FitManager *m=&(Instance());
	if(f.IsOpen())
	{
		m->ReadFromROOT(&f);
	}
	f.Close();
	return m;
}

TFitFunction* FitManager::FindFunction(string ID)
{
	TFitFunction *result=0;
	for(unsigned int i=0;i<Functions.size();i++)
	{
		if(Functions[i]->id==ID)
		{
			Functions[i]->fManager=this;
			return Functions[i];
		}
	}
	return result;
}

FitSelection::FitSelection(string reg)
{
	FitManager *m=FitManager::GetPointer();
	Functions=m->FindFunctions(reg);
}

void FitSelection::Select(string reg_par_name)
{
	FitManager *m=FitManager::GetPointer();
	Functions=m->FindFunctions(reg_par_name);
}

double FitSelection::Average(string reg_par_name)
{
	double result=0;
	int N=0;
	for(unsigned int i=0;i<Functions.size();i++)
	{
		for(int j=0;j<Functions[i]->Function.GetNpar();j++)
		{
			if(SatisfyPrimitiveRegexp(Functions[i]->Function.GetParName(j),reg_par_name))
			{
				result+=Functions[i]->Function.GetParameter(j);
				N++;
			}
		}
	}
	return result/N;
}

double FitSelection::StdDev(string reg_par_name)
{
	double Av=Average(reg_par_name);
	double result=0;
	int N=0;
	for(unsigned int i=0;i<Functions.size();i++)
	{
		for(int j=0;j<Functions[i]->Function.GetNpar();j++)
		{
			if(SatisfyPrimitiveRegexp(Functions[i]->Function.GetParName(j),reg_par_name))
			{
				result+=pow(Av-Functions[i]->Function.GetParameter(j),2);
				N++;
			}
		}
	}
	if(N<2)
	{
		return 0;
	}
	return sqrt((1.0/(N-1)*result));
}

double FitSelection::DiffFromAverage(string reg_par_name, TFitFunction* F)
{
	double Av=Average(reg_par_name);
	double result=0;
	int N=0;
	for(int j=0;j<F->Function.GetNpar();j++)
	{
		if(SatisfyPrimitiveRegexp(F->Function.GetParName(j),reg_par_name))
		{
			result+=F->Function.GetParameter(j);
			N++;
		}
	}
	return Av-(result/N);
}

vector<TFitFunction*> FitManager::FindFunctions(string regexp)
{
	vector<TFitFunction*> result;
	for(unsigned int i=0;i<Functions.size();i++)
	{
		if(SatisfyPrimitiveRegexp(Functions[i]->id,regexp))
		{
			result.push_back(Functions[i]);
		}
	}
	return result;
}

void FitManager::SaveFitRes(TFitFunction *f,TH1 *hist)
{
	FitResult *res=0;
	bool found=false;
	for(unsigned int i=0;i<FitRes.size();i++)
	{
		if(FitRes[i]->id==f->id)
		{
			res=FitRes[i];
			found=true;
			break;
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
	
	int NBins=ceil((HistRight-HistLeft)/hist->GetBinWidth(1));
	//cout<<"HistLeft HistRight "<<HistLeft<<" "<<HistRight<<" "<<NBins<<" "<<hist->GetBinWidth(1)<<"\n";
	TH1DTracked ReferenceHistogram(TString::Format("%s_hist",f->id.c_str()),TString::Format("%s_hist: FitResult; ",f->id.c_str()),NBins,HistLeft,HistRight);
	int BinMin=hist->GetXaxis()->FindBin(HistLeft), BinMax=hist->GetXaxis()->FindBin(HistRight);
	
	//cout<<"BinMin BinMax "<<BinMin<<" "<<BinMax<<"\n";
	
	int BinIterator=1;
	for(int i=BinMin;i<=BinMax;i++)
	{
		ReferenceHistogram.SetBinContent(BinIterator,hist->GetBinContent(i));
		ReferenceHistogram.SetBinError(BinIterator,hist->GetBinError(i));
		//cout<<"ReferenceHistogram:SetBinContent("<<BinIterator<<","<<hist->GetBinContent(i)<<") "<<i<< "\n";
		BinIterator++;
	}
	f->fFitResult=res;
	res->ReferenceHistogram=ReferenceHistogram;
	if(!found)
	FitRes.push_back(res);
	
}
TFitFunction* FitManager::BookFunction(string InputStr,bool AddNew)
{
	TFitFunction *f=new TFitFunction();
	f->FromString(InputStr);
	f->fManager=this;
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
TFitFunction* FitManager::BookFunction(TFitFunction *f,bool AddNew)
{
	f->fManager=this;
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

TFitFunction* FitManager::BookFunction(TF1 *fit,bool AddNew)
{
	string id_str=fit->GetTitle();
	TFitFunction *func=new TFitFunction();
	func->FromTF1(fit);
	return BookFunction(func,AddNew);
}

void FitManager::AttachHistogram(TFitFunction* f,TH1 *h)
{
	SaveFitRes(f,h);
}

TFitFunction* FitManager::BookFunction(TString Name,TString Function,double XMin,double XMax,bool AddNew)
{
	string id_str(Name.Data());
	if(AddNew)
	{
		TFitFunction *ff=FindFunction(id_str);
		int iterator=0;
		while(ff)
		{
			string id_str0=id_str+"_"+to_string(iterator);
			ff=FindFunction(id_str0);
			iterator++;
		}
		if(iterator>0)
		id_str=id_str+"_"+to_string(iterator);

		TFitFunction *f=new TFitFunction();
		f->SetFunction(Name,Function,XMin,XMax);
		f->id=id_str;
		Functions.push_back(f);
		f->fManager=this;
		return f;
	}
	else
	{

		TFitFunction *ff=FindFunction(id_str);
		if(ff)
		{
			for(unsigned int i=0;i<Functions.size();i++)
			{
				if(Functions[i]==ff)
				{
					delete ff;
					TFitFunction *f=new TFitFunction();
					f->SetFunction(Name,Function,XMin,XMax);
					f->id=id_str;
					f->fManager=this;
					Functions[i]=f;
				}
			}
			
		}
		else
		{
			TFitFunction *f=new TFitFunction();
			f->SetFunction(Name,Function,XMin,XMax);
			f->id=id_str;
			f->fManager=this;
			Functions.push_back(f);
			return f;
		}
	}
	return 0;
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

void TFitFunction::FromStringObject(string input)
{
	stringstream ifs(input);
	string line;
	
	vector<string> vec_str;
	while(getline(ifs,line))
	{
		stringstream sstr(line);
		string _id;
		sstr>>_id;
		if(id==_id)
		{
			vec_str.push_back(line);
		}
	}
	for(unsigned int i=0;i<vec_str.size();i++)
	{
		//cout<<"vec_str: "<<vec_str[i]<<"\n";
		stringstream sstr(vec_str[i]);
		string key;
		sstr>>key>>key;
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
			string ParN;
			sstr>>par.Value>>par.MinLimit>>par.MaxLimit>>par.Error>>ParN;
			//cout<<"ParN "<<ParN<<"\n";
			par.ParName=TString(ParN.c_str());
			if(parNum>=(int)parameters.size())
			{
				parameters.resize(parNum+1);
			}
			parameters[parNum]=par;
		}
		if(key=="flags:")
		{
			while(sstr)
			{
				string tmp;
				sstr>>tmp;
				//cout<<"flags: "<<tmp<<"\n";
				if(tmp=="WithComponents")
				{
					WithComponents=true;
				}
			}
		}
	}
	SetParameters();
	if(WithComponents)
	{
		GenerateComponents();
	}
	/*
	
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
				cout<<"key: "<<key<<"\n";
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
					string ParN;
					sstr>>par.Value>>par.MinLimit>>par.MaxLimit>>par.Error>>ParN;
					cout<<"ParN "<<ParN<<"\n";
					par.ParName=TString(ParN.c_str());
					if(parNum>=(int)parameters.size())
					{
						parameters.resize(parNum+1);
					}
					parameters[parNum]=par;
				}
				if(key=="flags:")
				{
					while(sstr)
					{
						string tmp;
						sstr>>tmp;
						cout<<"flags: "<<tmp<<"\n";
						if(tmp=="WithComponents")
						{
							WithComponents=true;
						}
					}
				}
			}
			SetParameters();
		}
	}*/
}

void TFitFunction::SetParameters()
{
	//cout<<"parameters.size(): "<<parameters.size()<<"\n";
	for(unsigned int i=0;i<parameters.size();i++)
	{
		Function.SetParameter(parameters[i].ParNumber,parameters[i].Value);
		//Function.SetParName(i,parameters[i].ParName);
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
				Function.ReleaseParameter(parameters[i].ParNumber);
			}
		}
	}
}

void TFitFunction::SetParameter(int ParNumber,double Value)
{
	if((int)parameters.size()>ParNumber)
	{
		parameters[ParNumber].Value=Value;
	}
	SetParameters();
}
void TFitFunction::FixParameter(int ParNumber,double Value)
{
	if((int)parameters.size()>ParNumber)
	{
		parameters[ParNumber].Value=Value;
		parameters[ParNumber].Fixed=true;
		parameters[ParNumber].Limited=false;
	}
	SetParameters();
}
void TFitFunction::SetParLimits(int ParNumber,double ValueMin,double ValueMax)
{
	if((int)parameters.size()>ParNumber)
	{
		parameters[ParNumber].MinLimit=ValueMin;
		parameters[ParNumber].MaxLimit=ValueMax;
		parameters[ParNumber].Limited=true;
		parameters[ParNumber].Fixed=false;
	}
	SetParameters();
}

void TFitFunction::ReleaseParameter(int ParNumber)
{
	if((int)parameters.size()>ParNumber)
	{
		parameters[ParNumber].Limited=false;
		parameters[ParNumber].Fixed=false;
	}
	SetParameters();
}

void TFitFunction::GetParameters()
{
	if(Function.GetNpar()>(int)parameters.size())
	{
		parameters.resize(Function.GetNpar());
	}
	for(unsigned int i=0;i<parameters.size();i++)
	{
		parameters[i].Value=Function.GetParameter(i);
		parameters[i].Error=Function.GetParError(i);
		parameters[i].ParName=Function.GetParName(i);
		double MinLimit,MaxLimit;
		Function.GetParLimits(i,MinLimit,MaxLimit);
		if(MinLimit!=MaxLimit)
		{
			parameters[i].MinLimit=MinLimit;
			parameters[i].MaxLimit=MaxLimit;
			parameters[i].Limited=true;
			double ToMinLimit=abs(parameters[i].MinLimit-parameters[i].Value), ToMaxLimit=abs(parameters[i].MaxLimit-parameters[i].Value);
			
			if(ToMinLimit<(parameters[i].MaxLimit-parameters[i].MinLimit)/100 || ToMinLimit<(abs(parameters[i].Value-parameters[i].Error)))
			{
				parameters[i].AtLimit=1;
			}
			if(ToMaxLimit<(parameters[i].MaxLimit-parameters[i].MinLimit)/100 || ToMaxLimit<(abs(parameters[i].Value+parameters[i].Error)))
			{
				parameters[i].AtLimit=2;
			}
			if(ToMinLimit<(abs(parameters[i].Value-parameters[i].Error))&&ToMaxLimit<(abs(parameters[i].Value+parameters[i].Error)))
			{
				parameters[i].AtLimit=3;
			}
			//if(abs(parameters[i].MinLimit-parameters[i].Value)<(parameters[i].MaxLimit-parameters[i].MinLimit)/100)
		}
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
	if(WithComponents)
	{
		for(unsigned int i=0;i<Components.size();i++)
		{
			for(int j=0;j<Components[i].GetNpar();j++)
			{
				int Num=Function.GetParNumber(Components[i].GetParName(j));
				Components[i].SetParameter(j,Function.GetParameter(Num));
				Components[i].SetParError(j,Function.GetParError(Num));
			}
		}
		for(int i=0;i<SubstrateFunction.GetNpar();i++)
		{
			int Num=Function.GetParNumber(SubstrateFunction.GetParName(i));
			SubstrateFunction.SetParameter(i,Function.GetParameter(Num));
			SubstrateFunction.SetParError(i,Function.GetParError(Num));
		}
	}
}
string TFitFunction::AsString(int PageNo)
{

	string result;
	func_str=Function.GetTitle();
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
		parameters[i].fFunction=this;
		result+=parameters[i].AsString()+"\n";
	}
	//строка с флагами: если флаг записан, то он true, если нет - false
	result+=id+" flags: ";
	if(WithComponents)
	result+="WithComponents";
	
	result+="\n";
	return result;
}

TF1* TFitFunction::GetFunction()
{
	return &Function;
}
void TFitFunction::GetRange(double &Xmin,double &Xmax)
{
	Xmin=LeftBorder; Xmax=RightBorder;
}
void  TFitFunction::Fit(TH1 *h, bool KeepResults,TH1* Parent)
{
	SetParameters();
	h->Fit(&Function,"R","",LeftBorder,RightBorder);
	GetParameters();
	if(KeepResults)
	{
		FitManager::GetPointer()->SaveFitRes(this,h);
		if(Parent)
		{
			if(!fManager)
			{
				cout<<"This is TFitFunction::Fit(): pointer to fManager is invalid!\n";
			}
			bool ExsistedParent=false;
			TH1 *ParentH=0;
			for(unsigned int i=0;i<fManager->ParentHistograms.size();i++)
			{
				if(fManager->ParentHistograms[i]->ParentHistogram==Parent)
				{
					ExsistedParent=true;
					ParentH=fManager->ParentHistograms[i];
					break;
				}
			}
			if(!ExsistedParent)
			{
				TH1DTracked *p=CopyHistogramToTH1DTracked_p(Parent,0,0,TString::Format("Parent_%d",(int)fManager->ParentHistograms.size()),TString::Format("Parent_%d",(int)fManager->ParentHistograms.size()));
				p->ParentHistogram=Parent;
				fFitResult->ReferenceHistogram.ParentHistogram=p;
				fManager->ParentHistograms.push_back(p);
				fFitResult->ReferenceHistogram.ParentName=p->GetName();
			}
			else
			{
				fFitResult->ReferenceHistogram.ParentHistogram=ParentH;
				fFitResult->ReferenceHistogram.ParentName=ParentH->GetName();
			}
		}
	}
	
	
}
void  TFitFunction::AssignPointers()
{
	for(unsigned int i=0;i<parameters.size();i++)
	{
		parameters[i].fFunction=this;
	}	
}

void  TFitFunction::SetParName(int ParNumber,TString Name)
{
	if(ParNumber<(int)parameters.size())
	{
		parameters[ParNumber].ParName=Name;
	}
	else
	{
		cout<<"This is TFitFunction::SetParName("<<ParNumber<<","<<Name<<"): ParNumber is invalid. Size of parameters is "<<parameters.size()<<"\n";
	}
}


TString TFitFunction::GetParName(int ParNumber)
{
	if(ParNumber<(int)parameters.size())
	{
		return parameters[ParNumber].ParName;
	}
	else
	{
		cout<<"This is TFitFunction::GetParName("<<ParNumber<<"): ParNumber is invalid. Size of parameters is "<<parameters.size()<<"\n";
	}
	return "";
}

double TFitFunction::GetParameter(int number)
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
double TFitFunction::GetParameter(TString Name)
{
	for(unsigned int i=0;i<parameters.size();i++)
	{
		if(parameters[i].ParName==Name)
		{
			return parameters[i].Value;
		}
	}
	
	cout<<"Parameter with Name \""<<Name<<"\" not found. NAN returned";
	return nan("NAN");
}
double TFitFunction::GetParError(TString Name)
{
	for(unsigned int i=0;i<parameters.size();i++)
	{
		if(parameters[i].ParName==Name)
		{
			return parameters[i].Error;
		}
	}
	
	cout<<"Parameter with Name \""<<Name<<"\" not found. NAN returned";
	return nan("NAN");
}

void TFitFunction::SetLineColor(int Color)
{
	Function.SetLineColor(Color);
}
void TFitFunction::Draw(Option_t *option)
{
	Function.Draw(option);
	if(WithComponents)
	{
		GetParameters();
		SetParameters();
		for(unsigned int i=0;i<Components.size();i++)
		{
			Components[i].Draw("same");
		}
		SubstrateFunction.Draw("same");
	}
}

void TFitFunction::SetFunction(TString Name,TString FunctionStr,double XMin,double XMax)
{
	Function=TF1(Name,FunctionStr,XMin,XMax);
	func_str=string(FunctionStr.Data());
	LeftBorder=XMin;
	RightBorder=XMax;
	parameters.resize(Function.GetNpar());
	for(unsigned int i=0;i<parameters.size();i++)
	{
		parameters[i].fFunction=this;
		parameters[i].ParNumber=i;
	}
}
int TFitFunction::GetNpar()
{
	return Function.GetNpar();
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

void TFitFunction::FromTF1(TF1 *fFunction, string _id)
{
	if(_id!="")
	{
		id=_id;
	}
	LeftBorder=fFunction->GetXmin();
	RightBorder=fFunction->GetXmax();
	Function=*fFunction;
	func_str=Function.GetTitle();
	if(_id!="")
	{
		Function.SetName(id.c_str());
	}
	else
	{
		id=Function.GetName();
	}
	parameters.resize(Function.GetNpar());
	for(unsigned int i=0;i<parameters.size();i++)
	{
		parameters[i].fFunction=this;
		parameters[i].ParNumber=i;
		parameters[i].ParName=fFunction->GetParName(i);
	}
	GetParameters();
}

void TFitFunction::GenerateTLegendWithResults(TLegend* p)
{
	/*if(!p)
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
	}*/
	if(!p)
	{
		cout<<"This is TFitFunction::GenerateTPaveTextWithResults(): invalid pointer to TPaveText!\n";
	}
	p->AddEntry((TObject*)0,TString::Format("ID: %s",id.c_str()),"");
	p->AddEntry((TObject*)0,TString::Format("#chi^2/NDF: %.2f",Function.GetChisquare()/Function.GetNDF()),"");
	for(unsigned int i=0;i<parameters.size();i++)
	{
		TString addition="";
		if(parameters[i].ParName.Length()>0)
		{
			addition=TString::Format("p[%d]: %s %.3f#pm%.3f (%.3f...%.3f)",i,parameters[i].ParName.Data(),parameters[i].Value,parameters[i].Error,parameters[i].MinLimit,parameters[i].MaxLimit);
		}
		else
		{
			addition=TString::Format("p[%d]: %.3f#pm%.3f (%.3f...%.3f)",i,parameters[i].Value,parameters[i].Error,parameters[i].MinLimit,parameters[i].MaxLimit);
		}
		if(parameters[i].Chi2TakenIntoAccount)
		{
			addition+=" #chi^2/NDF incl";
		}
		p->AddEntry((TObject*)0,addition,"");
	}
}

string TFitFunction::AtLimitStr()
{
	string result="";
	for(unsigned int i=0;i<parameters.size();i++)
	{
		if(parameters[i].AtLimit>0)
		{
			result+=parameters[i].ParName+":"+to_string(parameters[i].AtLimit)+";";
		}
	}
	return result;
}

void CheckInterpolation(TH2F* h, double x, double y)
{
	double XMin, XMax, YMin, YMax;
	XMin=h->GetXaxis()->GetXmin();
	XMax=h->GetXaxis()->GetXmax();
	YMin=h->GetYaxis()->GetXmin();
	YMax=h->GetYaxis()->GetXmax();
	
	if((x<XMin)||(x>XMax)||(y<YMin)||(y>YMax))
	{
		cout<<"This is "<<h->GetName()<<" x:"<<x<<", y:"<<y<<", Xaxis range = ("<<XMin<<","<<XMax<<"), Yaxis range = ("<<YMin<<","<<YMax<<")\n";
	}
}

double RespComponent::Evaluate(double *x, double *p)
{
	CheckInterpolation(fHistogram,x[0]-p[0], p[1]);
	double Val=p[2]*fHistogram->Interpolate(x[0]-p[0],p[1]);
	if(fResp)
	{
		if(fResp->SubstrateFunction.GetNpar()>0)
		{
			Val+=fResp->SubstrateFunction.Eval(x[0]);
		}
			
	}
	return Val;
}

vector<double> ResponseFunction::GetPeakParameters(int N)//функция, возвращающая параметры пика: [сдвижка,ошибка, площадь,ошибка, параметр размытия,ошибка]
{
	vector<double> result(6);
	int NParSubstrate=SubstrateFunction.GetNpar();
	int ParIter=NParSubstrate+1;
	if(!UseExternal)
	{
		for(unsigned int i=0;i<RespHistograms.size();i++)
		{
			if(i==N)
			{
				result[0]=RespFunction.GetParameter(NParSubstrate);//положение;
				result[1]=RespFunction.GetParError(NParSubstrate);//положение;
				result[2]=RespFunction.GetParameter(ParIter);//размытие
				result[3]=RespFunction.GetParError(ParIter);//размытие
				result[4]=RespFunction.GetParameter(ParIter+1);//площадь
				result[5]=RespFunction.GetParError(ParIter+1);//площадь
				return result;
			}
			ParIter+=2;
		}
	}
	else
	{
		for(unsigned int i=0;i<RespHistograms.size();i++)
		{
			if(i==N)
			{
				result[0]=RespFunction.GetParameter(NParSubstrate);//положение;
				result[1]=RespFunction.GetParError(NParSubstrate);//положение;
				result[2]=RespFunction.GetParameter(ParIter);//размытие
				result[3]=RespFunction.GetParError(ParIter);//размытие
				result[4]=RespFunction.GetParameter(ParIter+1);//площадь
				result[5]=RespFunction.GetParError(ParIter+1);//площадь
				return result;
			}
			ParIter+=3;
		}
	}
	return result;
}

void ResponseFunction::SetPeakParameters(int PeakNum,double Mv,double Blur, double Area)
{
	int NParSubstrate=SubstrateFunction.GetNpar();
	int ParIter=NParSubstrate+1;
	if(!UseExternal)
	{
		RespFunction.SetParameter(NParSubstrate,Mv);
		for(unsigned int i=0;i<RespHistograms.size();i++)
		{
			if(i==PeakNum)
			{
				RespFunction.SetParameter(ParIter,Blur);
				RespFunction.SetParameter(ParIter+1,Area);
			}
			ParIter+=2;
		}
	}
	else
	{
		RespFunction.SetParameter(NParSubstrate,Mv);
		for(unsigned int i=0;i<RespHistograms.size();i++)
		{
			if(i==PeakNum)
			{
				RespFunction.SetParameter(ParIter,Blur);
				RespFunction.SetParameter(ParIter+1,Area);
			}
			ParIter+=3;
		}
	}
}

void ResponseFunction::ReadResponse(string DetType)
{
	TFile f(TString(getenv("RESPONSE_PATH"))+"ResponseDB.root");
	if(DetType=="NaI")
	{
		ResponseHist=(*(TH2F*)f.Get("NaI_Response"));
		ResponseOthHist=(*(TH2F*)f.Get("NaI_Other"));
		WasRead=true;
	}
	if(DetType=="BGO")
	{
		ResponseHist=(*(TH2F*)f.Get("BGO_Response"));
		ResponseOthHist=(*(TH2F*)f.Get("BGO_Other"));
		WasRead=true;
	}
	if(DetType=="LaBr")
	{
		ResponseHist=(*(TH2F*)f.Get("LaBr_Response"));
		ResponseOthHist=(*(TH2F*)f.Get("LaBr_Other"));
		WasRead=true;
	}
	f.Close();
}

TH1D ResponseFunction::BlurHistogram(TH1D *h, double Coef)
{
	TH1D result=*h;
	result.Reset();
	for(int i=0;i<h->GetNbinsX();i++)
	{
		double E=h->GetBinCenter(i+1);
		double Sigma=Coef*sqrt(E);
		double BinContent=h->GetBinContent(i+1);
		int MinBin=h->FindBin(E-5*Sigma);
		int MaxBin=h->FindBin(E+5*Sigma);
		if(MinBin<1)
		{
			MinBin=1;
		}
		if(MaxBin==h->GetNbinsX()+1)
		{
			MaxBin=h->GetNbinsX();
		}
		for(int j=MinBin;j<MaxBin;j++)
		{
			double X=h->GetXaxis()->GetBinCenter(j+1);
			double BlurValue=BinContent*exp(-0.5*pow((X-E)/Sigma,2))/(Sigma*sqrt(2*3.1416));
			result.SetBinContent(j+1,result.GetBinContent(j+1)+BlurValue);
		}
	}
	return result;
}

void ResponseFunction::SetParameter(int par,double PP)
{
	RespFunction.SetParameter(par,PP);
}

double ResponseFunction::Evaluate(double *x, double *p)
{
	//сначала идут параметры подложки (NPar-1), потом - сдвижка, потом - коэфф. размазки, потом - площадь компоненты
	double result=0;
	int NParSubstrate=SubstrateFunction.GetNpar();
	if(NParSubstrate>0)
	{
		for(int i=0;i<NParSubstrate;i++)
		{
			SubstrateFunction.SetParameter(i,p[i]);
		}
	}
	double Sub=0;
	bool LogParameters=false;
	if(ParameterLog.Length()==0)
	{
		LogParameters=true;
	}
	if(!UseExternal)
	{
		int ParIter=NParSubstrate+1;
		if(LogParameters)
		ParameterLog+=TString::Format("p[%d] (%s)= %.2f",NParSubstrate,"Calibr",p[NParSubstrate]);
		for(unsigned int i=0;i<RespHistograms.size();i++)
		{
			CheckInterpolation(&RespHistograms[i],x[0]-p[NParSubstrate],p[ParIter]);
			result+=p[1+ParIter]*RespHistograms[i].Interpolate(x[0]-p[NParSubstrate],p[ParIter]);
			if(LogParameters)
			{
				ParameterLog+=TString::Format("p[%d] (%s)= %.2f\np[%d] (%s)= %.2f\n",ParIter,"Blur",p[ParIter],ParIter+1,"Area",p[ParIter+1]);
			}
			Components[i].SetParameters(p[NParSubstrate],p[ParIter],p[1+ParIter]);
			ParIter+=2;
		}
		if(NParSubstrate>0)
		{
			Sub=SubstrateFunction.Eval(x[0]-p[NParSubstrate]);
		}
		return result+Sub;
	}
	else
	{
		int ParIter=NParSubstrate+1;
		if(LogParameters)
		ParameterLog+=TString::Format("p[%d] (%s)= %.2f\n",NParSubstrate,"Calibr",p[NParSubstrate]);
		for(unsigned int i=0;i<RespHistograms.size();i++)
		{
			CheckInterpolation(&RespHistograms[i],x[0]-p[NParSubstrate],p[ParIter]);
			CheckInterpolation(&RespOtherHistograms[i],x[0]-p[NParSubstrate],p[ParIter]);
			result+=p[1+ParIter]*RespHistograms[i].Interpolate(x[0]-p[NParSubstrate],p[ParIter])+p[2+ParIter]*RespOtherHistograms[i].Interpolate(x[0]-p[NParSubstrate],p[ParIter]);
			Components[i].SetParameters(p[NParSubstrate],p[ParIter],p[1+ParIter]);
			if(LogParameters)
			ParameterLog+=TString::Format("p[%d] (%s)= %.2f\np[%d] (%s)= %.2f\np[%d] (%s)= %.2f\n",ParIter,"Blur",p[ParIter],ParIter+1,"Area",p[ParIter+1],ParIter+2,"AreaExt",p[ParIter+1]);
			ParIter+=3;
		}
		if(NParSubstrate>0)
		{
			Sub=SubstrateFunction.Eval(x[0]-p[NParSubstrate]);
		}
		return result+Sub;
	}
	
}
void ResponseFunction::PrintParameters()
{
	for(int i=0;i<RespFunction.GetNpar();i++)
	{
		cout<<"par"<<i<<" "<<RespFunction.GetParameter(i)<<"\n";
	}
}
void ResponseFunction::SetNpx(int px)
{
	Npx=px;
}


void ResponseFunction::SetParameters(double p0, double p1, double p2,
                              double p3, double p4, double p5,
                              double p6, double p7, double p8,
                              double p9, double p10)
{
	vector<double> Par={p0,p1,p2,p3,p4,p5,p6,p7,p8,p9,p10};
	for(int i=0;i<Par.size();i++)
	{
		if(i<SubstrateFunction.GetNpar())
		{
			SubstrateFunction.SetParameter(i,Par[i]);
		}
		RespFunction.SetParameter(i,Par[i]);
	}
}
void ResponseFunction::GenerateResponseFunction(double Min, double Max, vector<double> Energies_,double CoefMin,double CoefMax, int NSteps)
{
	vector<int> Colors={kBlack,kGray,kRed-2,kOrange,kOrange-3,kMagenta,kViolet-6,kBlue,kCyan,kGreen,kGreen+3};
	Energies=Energies_;
	double BinWidth=ResponseHist.GetYaxis()->GetBinWidth(1);
	double MinHist=Min-20;
	double MaxHist=Max+20;
	
	double CoefMinHist=0.8*CoefMin;
	double CoefMaxHist=1.2*CoefMax;
	
	int NBins=(Max-Min)/BinWidth;
	RespHistograms.resize(0);
	RespOtherHistograms.resize(0);
	RespComponents.resize(0);
	for(unsigned int i=0;i<Energies.size();i++)
	{
		TH1D h(TString::Format("Resp_od_%d",int(Energies[i]*10)),TString::Format("Resp_%d",int(Energies[i]*10)),NBins,MinHist,MaxHist);
		TH1D h_other(TString::Format("RespOth_od_%d",int(Energies[i]*10)),TString::Format("RespOth_%d",int(Energies[i]*10)),NBins,MinHist,MaxHist);
		TH2F h_2D(TString::Format("Resp_%d",int(Energies[i]*10)),TString::Format("Resp_%d",int(Energies[i]*10)),NBins,MinHist,MaxHist,NSteps,CoefMinHist,CoefMaxHist);
		TH2F h_2D_oth(TString::Format("Resp_%d",int(Energies[i]*10)),TString::Format("Resp_%d",int(Energies[i]*10)),NBins,MinHist,MaxHist,NSteps,CoefMinHist,CoefMaxHist);
		for(int j=0;j<h.GetNbinsX();j++)
		{
			double Energy=h.GetBinCenter(j+1);
			if(Energies[i]-h.GetBinCenter(j+1)+10>0)
			{
				h.SetBinContent(j+1,ResponseHist.Interpolate(Energies[i],Energies[i]-h.GetBinCenter(j+1)+10));
				h_other.SetBinContent(j+1,ResponseOthHist.Interpolate(Energies[i],h.GetBinCenter(j+1)));
			}
		}
		int PhotopeakBin1=h.GetXaxis()->FindBin(Energies[i]-1);
		int PhotopeakBin2=h.GetXaxis()->FindBin(Energies[i]+1);
		double Integral=h.Integral(PhotopeakBin1,PhotopeakBin2);
		h.Scale(1/Integral);
		h_other.Scale(1/Integral);
		for(int j=0;j<NSteps;j++)
		{
			double Coef=h_2D.GetYaxis()->GetBinCenter(j+1);
			TH1D h_blured=BlurHistogram(&h,Coef);
			TH1D h_blured_oth=BlurHistogram(&h_other,Coef);
			for(int k=0;k<h_blured.GetNbinsX();k++)
			{
				h_2D.SetBinContent(k+1,j+1,h_blured.GetBinContent(k+1));
				h_2D_oth.SetBinContent(k+1,j+1,h_blured_oth.GetBinContent(k+1));
			}
		}
		RespHistograms.push_back(h_2D);
		RespOtherHistograms.push_back(h_2D_oth);
	}
	if(!UseExternal)
	{
		RespFunction=TF1("Resp",this,&ResponseFunction::Evaluate,Min,Max,2*Energies.size()+1+SubstrateFunction.GetNpar(),"ResponseFunction","Evaluate");
	}
	else
	{
		RespFunction=TF1("Resp",this,&ResponseFunction::Evaluate,Min,Max,3*Energies.size()+1+SubstrateFunction.GetNpar(),"ResponseFunction","Evaluate");
	}
	RespComponents.resize(RespHistograms.size());
	for(unsigned int i=0;i<RespHistograms.size();i++)
	{
		RespComponents[i].fHistogram=&RespHistograms[i];
		RespComponents[i].fResp=this;
		RespComponents[i].fOthHistogram=&RespOtherHistograms[i];
	}
	for(unsigned int i=0;i<RespHistograms.size();i++)
	{
		TF1 RespCompTF1(TString::Format("Component_%d",i),&RespComponents[i],&RespComponent::Evaluate,Min,Max,3,"RespComponent","Evaluate");
		if(i<Colors.size())
		{
			RespCompTF1.SetLineColor(Colors[i]);
		}
		Components.push_back(RespCompTF1);
	}
}
void ResponseFunction::Draw(Option_t *option)
{
	TString opt(option);
	if(Npx>0)
	{
		RespFunction.SetNpx(Npx);
	}
	RespFunction.Draw(opt);
	for(unsigned int i=0;i<Components.size();i++)
	{
		if(Npx>0)
		{
			Components[i].SetNpx(Npx);
		}
		Components[i].Draw(opt+" same");
	}
}

TF1Parameter* TFitFunction::FindParameter(TString Name)
{
	for(unsigned int i=0;i<parameters.size();i++)
	{
		if(parameters[i].ParName==Name)
		{
			return &parameters[i];
		}
	}
	return 0;
}

vector<double> TFitFunction::GetPeakRange(double nSigma)
{
	vector<double> result;
	if(!WithComponents)
	{
		return result;
	}
	GenerateComponents();
	GetParameters();
	double Min=1e9,Max=-1e9;
	for(unsigned int i=0;i<Components.size();i++)
	{
		double Pos=Components[i].GetParameter(1);
		double Sig=Components[i].GetParameter(2);
		if(Min>Pos-Sig*nSigma)
		{
			Min=Pos-Sig*nSigma;
		}
		if(Max<Pos+Sig*nSigma)
		{
			Max=Pos+Sig*nSigma;
		}
	}
	result={Min,Max};
	return result;
}

double TFitFunction::EvalChi2Substrate(double nSigma,bool DivideToNDF)
{
	if(!WithComponents)
	{
		return -1;
	}
	vector<double> PeakRange=GetPeakRange(nSigma);
	if(PeakRange.size()==0)
	{
		return -1;
	}
	double result=0;
	TH1D *h=(TH1D*)(&(fFitResult->ReferenceHistogram));
	double NDF=0;
	for(int i=1;i<h->GetNbinsX()+1;i++)
	{
		double val=SubstrateFunction.Eval(h->GetBinCenter(i));
		if((h->GetBinCenter(i)<PeakRange[0] || h->GetBinCenter(i)>PeakRange[1])&&(h->GetBinCenter(i)>LeftBorder)&&(h->GetBinCenter(i)<RightBorder))
		{
			NDF++;
			result+=pow((h->GetBinContent(i)-val)/(h->GetBinError(i)),2);
		}
	}
	NDF=NDF-SubstrateFunction.GetNpar();
	
	if(DivideToNDF)
	result=result/NDF;
	
	return result;
}

double TFitFunction::EvalChi2Peaks(double nSigma, bool DivideToNDF)//метод, позволяющий получить качество описания пиков (внутри nsigma)
{
	if(!WithComponents)
	{
		return -1;
	}
	vector<double> PeakRange=GetPeakRange(nSigma);
	if(PeakRange.size()==0)
	{
		return -1;
	}
	double result=0;
	TH1D *h=(TH1D*)(&(fFitResult->ReferenceHistogram));
	double NDF=0;
	for(int i=1;i<h->GetNbinsX()+1;i++)
	{
		double val=Function.Eval(h->GetBinCenter(i));
		if(h->GetBinCenter(i)>PeakRange[0] && h->GetBinCenter(i)<PeakRange[1]&&(h->GetBinCenter(i)>LeftBorder)&&(h->GetBinCenter(i)<RightBorder))
		{
			NDF++;
			result+=pow((h->GetBinContent(i)-val)/(h->GetBinError(i)),2);
		}
	}
	NDF=NDF-Function.GetNpar();
	
	if(DivideToNDF)
	result=result/NDF;
	
	return result;
}

void TFitFunction::GenerateComponents()
{
	string FuncStr(Function.GetTitle());
	string SubstrateString;
	vector<string> Elements=SplitString(FuncStr,'+');
	int ParIter=0, PeakIter=0, SubstrateParIter=0;
	Components.resize(0);
	//
	
	for(unsigned int i=0;i<Elements.size();i++)
	{
		Elements[i]=ChangeParNumeration(Elements[i]);
		TF1 TMPFunc("tmp",Elements[i].c_str(),LeftBorder,RightBorder);
		int CompNpar=TMPFunc.GetNpar();
		//cout<<"CompNpar:"<<CompNpar<<"\n";
		int CompType=-1;//переменная, отвечающая за тип компоненты. 0 - gaus, 1-gausn, 2 - pol, -1-прочее
		if(Elements[i].find("gaus(")!=string::npos)
		{
			CompType=0;
		}
		if(Elements[i].find("gausn(")!=string::npos)
		{
			CompType=1;
		}
		//cout<<"Element:"<<i<<" "<<CompType<<"\n";
		if((CompType!=0)&&(CompType!=1))
		{
			//cout<<"(CompType!=0)&&(CompType!=1): "<<Elements[i]<<" "<<SubstrateParIter<<"\n";
			for(int i=0;i<CompNpar;i++)
			{
				Function.SetParName(ParIter+i,TString::Format("Sub_%d",SubstrateParIter+i));
			}
			ParIter+=CompNpar;
			if(SubstrateString.size()>0)
			{
				SubstrateString+="+";
			}
			SubstrateString+=ChangeParNumeration(Elements[i],SubstrateParIter);
			SubstrateParIter+=CompNpar;
		}
		if(CompType==0)
		{
			Function.SetParName(ParIter,TString::Format("H_%d",PeakIter));
			Components.push_back(TF1(TString::Format("%s_%d",Function.GetName(),PeakIter),"gaus(0)",LeftBorder,RightBorder));
			Components[Components.size()-1].SetParName(0,TString::Format("H_%d",PeakIter));
		}
		if(CompType==1)
		{
			Components.push_back(TF1(TString::Format("%s_%d",Function.GetName(),PeakIter),"gausn(0)",LeftBorder,RightBorder));
			Function.SetParName(ParIter,TString::Format("A_%d",PeakIter));
			Components[Components.size()-1].SetParName(0,TString::Format("A_%d",PeakIter));
		}
		if((CompType==0)||(CompType==1))
		{
			WithComponents=true;
			Function.SetParName(ParIter+1,TString::Format("Pos_%d",PeakIter));
			Function.SetParName(ParIter+2,TString::Format("Sig_%d",PeakIter));
			Components[PeakIter].SetParName(1,TString::Format("Pos_%d",PeakIter));
			Components[PeakIter].SetParName(2,TString::Format("Sig_%d",PeakIter));
			
			Components[PeakIter].SetParameter(0,Function.GetParameter(ParIter));
			Components[PeakIter].SetParameter(1,Function.GetParameter(ParIter+1));
			Components[PeakIter].SetParameter(2,Function.GetParameter(ParIter+2));
			
			Components[PeakIter].SetParError(0,Function.GetParError(ParIter));
			Components[PeakIter].SetParError(1,Function.GetParError(ParIter+1));
			Components[PeakIter].SetParError(2,Function.GetParError(ParIter+2));
			
			Components[PeakIter].SetLineColor(ColorT(PeakIter));
			ParIter+=3;
			PeakIter++;
		}
	}
	
	if(SubstrateString.size()>0)
	{
		SubstrateFunction=TF1(TString::Format("%s_sub",Function.GetName()),SubstrateString.c_str(),LeftBorder,RightBorder);
		SubstrateFunction.SetLineColor(1);
		SubstrateFunction.SetLineStyle(9);
		for(int i=0;i<SubstrateFunction.GetNpar();i++)
		{
			SubstrateFunction.SetParName(i,TString::Format("Sub_%d",i));
		}
	}
	for(unsigned int i=0;i<parameters.size();i++)
	{
		//cout<<"i:"<<i<<" "<<Function.GetParName(i)<<"\n";
		parameters[i].fFunction=this;
		parameters[i].ParNumber=i;
		parameters[i].ParName=Function.GetParName(i);
	}
}

int TFitFunction::GetNumberOfPeaks()
{
	int NumberOfPeaks=0;
	for(unsigned int i=0;i<parameters.size();i++)
	{
		if(parameters[i].ParName.Index("Pos")!=string::npos)
		{
			NumberOfPeaks++;
		}
	}
	return NumberOfPeaks;
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
		parameters.resize(Function.GetNpar());
	}
	if(strings.size()==1)
	{
		for(unsigned int i=0; i<parameters.size();i++)
		{
			parameters[i].fFunction=this;
			parameters[i].ParNumber=i;
		}
	}
	for(unsigned int i=1; i<strings.size();i++)
	{
		TString ts(strings[i].c_str());
		if(strings[i].find("flags")!=string::npos)
		{
			ts.ReplaceAll(id.c_str(),"");
			ts.ReplaceAll("flags:","");
			vector<string> sp=SplitStr(ts.Data()," ");
			for(unsigned int j=0;j<sp.size();i++)
			{
				if(sp[j]=="WithComponents")
				{
					WithComponents=true;
				}
			}
		}
		TF1Parameter par;
		if(ts.Index("limited")>=0)
		{
			par.Limited=true;
		}
		if(ts.Index("fixed")>=0)
		{
			par.Fixed=true;
		}
		ts.ReplaceAll("limited","");
		ts.ReplaceAll("fixed","");
		stringstream sstr(ts.Data());
		
		par.fFunction=this;
		//int parNum;
		string limited,fixed;
		sstr>>par.ParNumber;
		string strName;
		sstr>>par.Value>>par.MinLimit>>par.MaxLimit>>par.Error>>strName;
		//cout<<"strName:"<<strName<<"\n";
		par.ParName=TString(strName.c_str());
		par.fFunction=this;
		parameters.push_back(par);
		if((int)parameters.size()>par.ParNumber)
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

void TFitFunction::LaunchGUI()
{
	TH1::AddDirectory(false);
	new RootFitLib_gui(id,fManager);
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
			
			par.fFunction=this->fFunction;
			//int parNum;
			string limited,fixed;
			sstr>>par.ParNumber;
			sstr>>par.Value>>par.MinLimit>>par.MaxLimit;
			par.fFunction=fFunction;
			if((int)fFunction->parameters.size()>par.ParNumber)
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

TH1 * 	TH1DTracked::Rebin (Int_t ngroup, const char *newname, const Double_t *xbins)
{
	Operations.push_back(TString::Format("Rebin %d",ngroup).Data());
	return TH1::Rebin (ngroup,newname,xbins);
}
void 	TH1DTracked::Smooth (Int_t ntimes, Option_t *option)
{
	Operations.push_back(TString::Format("Smooth %d",ntimes).Data());
	TH1::Smooth (ntimes,option);
}
void 	TH1DTracked::Scale (Double_t c1, Option_t *option)
{
	Operations.push_back(TString::Format("Scale %f",c1).Data());
	TH1::Scale(c1,option);
}
