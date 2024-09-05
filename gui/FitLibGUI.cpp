/// \file
/// \ingroup tutorial_gui
/// Simple macro showing capabilities of triple slider
///
/// \macro_code
///
/// \author Bertrand Bellenot, Ilka Antcheva
#pragma once

#include "../FitLib.hh"
//#include "gui/FitLibGUI.cpp"


int Color(int Num)
{
	vector<int> colors={1,2,3,4,6,7,8,9,12,16,23,28,30,32,36,38,41,45,46};
	if(Num>=colors.size())
	{
		Num=Num%colors.size();
	}
	return colors[Num];
}

ULong_t UColor(int Num)
{
	vector<string> colors={"red","ForestGreen","DarkTurquoise","magenta","olive","Chocolate","Maroon","Orange","DeepPink"};
	if(Num>=colors.size())
	{
		Num=Num%colors.size();
	}
	ULong_t textcolor;
	gClient->GetColorByName(colors[Num].c_str(), textcolor);
	return textcolor;
}

EButtonState Pressed(bool value)
{
	if(value)
	{
		return kButtonDown;
	}
	return kButtonUp;
}


FitButtonFrame::FitButtonFrame(TGFrame *fFrame,RootFitLib_gui *Main): TGHorizontalFrame(fFrame, 0, 0, 0)
{
	Update = new TGTextButton(this,"Update");
	Fit = new TGTextButton(this,"Fit");
	SaveToFile = new TGTextButton(this,"Save to file");
	Next = new TGTextButton(this,"Next fit");
	Prev = new TGTextButton(this,"Prev fit");
	Find = new TGTextButton(this,"Find function");
	
	
	AddFrame(Update, new TGLayoutHints(kLHintsCenterX|kLHintsCenterY,20, 20, 20, 20));
	AddFrame(Fit, new TGLayoutHints(kLHintsCenterX|kLHintsCenterY,20, 20, 20, 20));
	AddFrame(SaveToFile, new TGLayoutHints(kLHintsCenterX|kLHintsCenterY,20, 20, 20, 20));
	fMainFrame=Main;
	Update->Connect("Clicked()","FitButtonFrame", this, "FUpdate()");
	Fit->Connect("Clicked()","FitButtonFrame", this, "FFit()");
	SaveToFile->Connect("Clicked()","FitButtonFrame", this, "FSaveToFile()");
}
void FitButtonFrame::FUpdate()
{
	TFitFunction *func=fMainFrame->fFitFcn;
	for(unsigned int i=0;i<func->parameters.size();i++)
	{
		fMainFrame->FitParameters[i]->ToTFitFunction(func,i);
	}
	func->SetParameters();
	
	fMainFrame->fCanvas->GetCanvas()->cd();
	if(func->fFitResult)
	{
		func->fFitResult->ReferenceHistogram.Draw("e hist");
		func->Function.Draw("same");
	}
	else
	{
		cout<<"This is RootFitLib_gui::CreateForms: pointer to FitResult is invalid! Drawing will be without histogram\n";
		func->Function.Draw();
	}
	gPad->Update();
	cout<<"Update\n";
	for(unsigned int i=0;i<func->parameters.size();i++)
	{
		fMainFrame->FitParameters[i]->FromTFitFunction(func,i);
	}
}
void FitButtonFrame::FFit()
{
	if(!(fMainFrame->fFitFcn))
	{
		cout<<"This is FitButtonFrame::FFit():: fitfunction does not set. Returned\n";
		return;
	}
	if(!(fMainFrame->fFitFcn->fFitResult))
	{
		cout<<"This is FitButtonFrame::FFit():: fFitResult does not set. Returned\n";
		return;
	}
	//cout<<"integral:"<<fMainFrame->fFitFcn->fFitResult->ReferenceHistogram.Integral();
	fMainFrame->fFitFcn->Fit(&(fMainFrame->fFitFcn->fFitResult->ReferenceHistogram));
	fMainFrame->fFitFcn->fFitResult->ReferenceHistogram.Draw("e hist");
	fMainFrame->fFitFcn->Function.Draw("same");
	gPad->Update();
	TFile f("test.root","recreate");
	f.WriteTObject(&(fMainFrame->fFitFcn->fFitResult->ReferenceHistogram));
	f.Close();
}
void FitButtonFrame::FSaveToFile()
{
	if(!fMainFrame->fFitFcn)
	{
		cout<<"This is FitButtonFrame::FSaveToFile(): pointer to fMainFrame->fFitFcn is invalid\n";
		return;
	}
	if(!fMainFrame->fFitFcn->fManager)
	{
		cout<<"This is FitButtonFrame::FSaveToFile(): pointer to fManager->fFitFcn is invalid\n";
		return;
	}
	fMainFrame->fFitFcn->fManager->UpdateInROOT(0);
	
}

void FitParFrame :: FromTFitFunction(TFitFunction *func,int ParNum)
{
	if(func->parameters.size()<=ParNum)
	return ;
	
	//func->GetParameters();
	ParValue->SetNumber(func->parameters[ParNum].Value);
	MinLimit->SetNumber(func->parameters[ParNum].MinLimit);
	MaxLimit->SetNumber(func->parameters[ParNum].MaxLimit);
	ParError->SetNumber(func->parameters[ParNum].Error);
	
	Fixed->SetState(Pressed(func->parameters[ParNum].Fixed));
	Limited->SetState(Pressed(func->parameters[ParNum].Limited));
	if(func->parameters[ParNum].ParName.Length()>0)
	{
		ParName->SetText(func->parameters[ParNum].ParName);
	}
	else
	{
		ParName->SetText(TString::Format("%-10s\t",TString::Format("Par %d",ParNum).Data()));
		func->parameters[ParNum].ParName=TString::Format("Par %d",ParNum);
	}
	
}
void FitParFrame :: ToTFitFunction(TFitFunction *func,int ParNum)
{
	if(func->parameters.size()<=ParNum)
	return ;
	func->parameters[ParNum].Value=ParValue->GetNumber();
	func->parameters[ParNum].MinLimit=MinLimit->GetNumber();
	func->parameters[ParNum].MaxLimit=MaxLimit->GetNumber();
	func->parameters[ParNum].Fixed=Fixed->IsDown();
	func->parameters[ParNum].Limited=Limited->IsDown();
}


FitParFrame::FitParFrame(TGFrame *fFrame,TString ParName_) : TGHorizontalFrame(fFrame, 0, 0, 0)
{
	ParValue=new TGNumberEntry(this,0,9);
	ParError=new TGNumberEntry(this,0,9);
	MinLimit=new TGNumberEntry(this,0,9);
	MaxLimit=new TGNumberEntry(this,0,9); 
	Fixed=new TGCheckButton(this," Fixed");
	Limited=new TGCheckButton(this,"Limited");
	ParName=new TGTextButton(this, TString::Format("%-10s\t",ParName_.Data()));
	
	AddFrame(ParName,new TGLayoutHints(kLHintsLeft|kLHintsTop, 0));
	AddFrame(ParValue, new TGLayoutHints(kLHintsTop | kLHintsLeft, 1, 5, 1, 5));
	AddFrame(ParError, new TGLayoutHints(kLHintsTop | kLHintsLeft, 1, 5, 1, 5));
	AddFrame(MinLimit, new TGLayoutHints(kLHintsTop | kLHintsLeft, 1, 5, 1, 5));
	AddFrame(MaxLimit, new TGLayoutHints(kLHintsTop | kLHintsLeft, 1, 5, 1, 5));
	AddFrame(Fixed, new TGLayoutHints(kLHintsTop | kLHintsLeft, 1, 5, 1, 5));
	AddFrame(Limited, new TGLayoutHints(kLHintsTop | kLHintsLeft, 1, 5, 1, 5));
	ParName->Connect("Clicked()","FitParFrame", this, "ClkParSet()");
	//MinLimit->Connect("Clicked()","FitParFrame", this, "ClkLimit()");
	//MaxLimit->Connect("Clicked()","FitParFrame", this, "ClkLimit()");
	Limited->SetState(Pressed(true));
}
void FitParFrame::ClkParSet()
{
	//cout<<"double clicked val\n";
	Main->ActiveWidget=this;
	//cout<<Main->fFitFcn->id;
	//cout<<" val\n";
}

double GetXCoordinate(int x)
{
	double result=gPad->GetCanvas()->AbsPixeltoX(x);
	if(gPad->GetLogx()==1)
	{
		return pow(10,result);
	}
	return result;
}
double GetYCoordinate(int y)
{
	double result=gPad->GetCanvas()->AbsPixeltoY(y);
	if(gPad->GetLogy()==1)
	{
		return pow(10,result);
	}
	return result;
}

void GetRangeAxis(double &x1,double &y1, double &x2, double &y2)
{
	gPad->GetCanvas()->GetRangeAxis(x1,y1,x2,y2);
	if(gPad->GetLogx()==1)
	{
		x1=pow(10,x1);
		x2=pow(10,x2);
	}
	if(gPad->GetLogy()==1)
	{
		y1=pow(10,y1);
		y2=pow(10,y2);
	}
}

void FitParFrame::ProcessCanvasFunction(int event,int x,int y, TObject *selected,TCanvas *c)
{
	TString ParNameStr=ParName->GetString();
	//cout<<ParName->GetString()<<" "<<event<<" "<<c->AbsPixeltoX(x)<<" "<<c->AbsPixeltoY(y)<<"\n";
	TH1D *h=0;
	if(!Main)
	{
		cout<<"This is FitParFrame::ProcessCanvasFunction(): pointer to MainFrame is invalid!\n";
		return;
	}
	if(!Main->fFitFcn)
	{
		cout<<"This is FitParFrame::ProcessCanvasFunction(): pointer to FitFcn is invalid!\n";
		return;
	}
	if(Main->fFitFcn->fFitResult)
	{
		h=&(Main->fFitFcn->fFitResult->ReferenceHistogram);
	}
	
	double MinX=0,MaxX=0,MinY=0,MaxY=0;
	GetRangeAxis(MinX,MinY,MaxX,MaxY);
	//сценарии для разных параметров: пока только для гауссовых функций
	if(ParNameStr.Index("Pos")>-1)//положение
	{
		cout<<"stage:"<<FitStage<<"\n";
		if(FitStage==0)//левая граница
		{
			
			if(LeftBorder)
			{
				delete LeftBorder;
				LeftBorder=0;
			}
			TLine l;
			l.SetLineColor(2);
			LeftBorder=l.DrawLine(GetXCoordinate(x),MinY, GetXCoordinate(x),MaxY);
			//LeftBorder->SetBit(kCanDelete,false);
			c->Modified();
			c->Update();
			if(event==11)//клик
			{
				MinLimit->SetNumber(c->AbsPixeltoX(x));
				PointerToParameter->MinLimit=c->AbsPixeltoX(x);
				c->Modified();
				c->Update();
				FitStage++;
				return;
			}
		}
		if(FitStage==1)//центорид
		{
			if(Centroid)
			{
				delete Centroid;
				Centroid=0;
			}
			TLine l;
			l.SetLineColor(3);
			Centroid=l.DrawLine(GetXCoordinate(x),MinY, GetXCoordinate(x),MaxY);
			//Centroid->SetBit(kCanDelete,false);
			c->Modified();
			c->Update();
			if(event==11)//клик
			{
				ParValue->SetNumber(c->AbsPixeltoX(x));
				PointerToParameter->Value=c->AbsPixeltoX(x);
				FitStage++;
				c->Modified();
				c->Update();
				return;
			}
		}
		if(FitStage==2)//центорид
		{
			if(RightBorder)
			{
				delete RightBorder;
				RightBorder=0;
			}
			TLine l;
			l.SetLineColor(3);
			RightBorder=l.DrawLine(GetXCoordinate(x),MinY, GetXCoordinate(x),MaxY);
			c->Modified();
			c->Update();
			if(event==11)//клик
			{
				MaxLimit->SetNumber(c->AbsPixeltoX(x));
				PointerToParameter->MaxLimit=c->AbsPixeltoX(x);
				FitStage=0;
				Main->ActiveWidget=0;
				Main->fFitFcn->SetParameters();
				
				if(LeftBorder)
				{
					delete LeftBorder;
					LeftBorder=0;
				}
				if(Centroid)
				{
					delete Centroid;
					Centroid=0;
				}
				if(RightBorder)
				{
					delete RightBorder;
					RightBorder=0;
				}
				
				Main->fFitFcn->fFitResult->ReferenceHistogram.Draw();
				Main->fFitFcn->Draw("same");
				
				c->Modified();
				c->Update();
				
				//для избежания segfault при переходе к другим параметрам

				
				return;
			}
			//if(Event)
		}
	}
	if(ParNameStr.Index("H")==0)//высота
	{
		//cout<<"h="<<c->AbsPixeltoY(y)<<"\n";
		cout<<"stage:"<<FitStage<<"\n";
		if(FitStage==0)//левая граница
		{
			
			if(LeftBorder)
			{
				delete LeftBorder;
				LeftBorder=0;
			}
			TLine l;
			l.SetLineColor(2);
			LeftBorder=l.DrawLine(MinX,GetYCoordinate(y), MaxX,GetYCoordinate(y));
			//LeftBorder->SetBit(kCanDelete,false);
			c->Modified();
			c->Update();
			if(event==11)//клик
			{
				MinLimit->SetNumber(GetYCoordinate(y));
				PointerToParameter->MinLimit=GetYCoordinate(y);
				c->Modified();
				c->Update();
				FitStage++;
				return;
			}
		}
		if(FitStage==1)//центорид
		{
			if(Centroid)
			{
				delete Centroid;
				Centroid=0;
			}
			TLine l;
			l.SetLineColor(3);
			Centroid=l.DrawLine(MinX,GetYCoordinate(y), MaxX,GetYCoordinate(y));
			//Centroid->SetBit(kCanDelete,false);
			c->Modified();
			c->Update();
			if(event==11)//клик
			{
				ParValue->SetNumber(GetYCoordinate(y));
				PointerToParameter->Value=GetYCoordinate(y);
				FitStage++;
				c->Modified();
				c->Update();
				return;
			}
		}
		if(FitStage==2)//центорид
		{
			if(RightBorder)
			{
				delete RightBorder;
				RightBorder=0;
			}
			TLine l;
			l.SetLineColor(4);
			RightBorder=l.DrawLine(MinX,GetYCoordinate(y), MaxX,GetYCoordinate(y));
			c->Modified();
			c->Update();
			if(event==11)//клик
			{
				MaxLimit->SetNumber(GetYCoordinate(y));
				PointerToParameter->MaxLimit=GetYCoordinate(y);
				FitStage=0;
				Main->ActiveWidget=0;
				Main->fFitFcn->SetParameters();
				
				if(LeftBorder)
				{
					delete LeftBorder;
					LeftBorder=0;
				}
				if(Centroid)
				{
					delete Centroid;
					Centroid=0;
				}
				if(RightBorder)
				{
					delete RightBorder;
					RightBorder=0;
				}
				
				Main->fFitFcn->fFitResult->ReferenceHistogram.Draw();
				Main->fFitFcn->Draw("same");
				
				c->Modified();
				c->Update();
				

				
				return;
			}
			//if(Event)
		}
	}
	
	return ;
}


FunctionStringFrame::FunctionStringFrame(TGFrame *fFrame,RootFitLib_gui *Main_) : TGHorizontalFrame(fFrame, 0, 0, 0)
{
	FuncName=new TGLabel(this);
	FuncField=new TGTextEntry(this);
	
	FuncField->SetDefaultSize(250,20);
	
	LeftLimit=new TGNumberEntry(this,0,9);
	RightLimit=new TGNumberEntry(this,0,9);
	Update=new TGTextButton(this,"Update");
	AddFrame(FuncName,new TGLayoutHints(kLHintsLeft|kLHintsTop, 0));
	AddFrame(FuncField,new TGLayoutHints(kLHintsLeft|kLHintsTop, 0));
	AddFrame(LeftLimit,new TGLayoutHints(kLHintsLeft|kLHintsTop, 0));
	AddFrame(RightLimit,new TGLayoutHints(kLHintsLeft|kLHintsTop, 0));
	AddFrame(Update,new TGLayoutHints(kLHintsLeft|kLHintsTop, 0));
	Main=Main_;
	Update->Connect("Clicked()","FunctionStringFrame", this, "UpdateFitFunction()");
}
void FunctionStringFrame::UpdateValuesFromFitFunction(TFitFunction *func)
{
	FuncName->SetText(func->id.c_str());
	FuncField->SetText(func->func_str.c_str());
	LeftLimit->SetNumber(func->LeftBorder);
	RightLimit->SetNumber(func->RightBorder);
}
void FunctionStringFrame::UpdateFitFunction()
{
	TString func_str(FuncField->GetText());
	if(Main->fFitFcn)
	{
		Main->fFitFcn->SetFunction(TString((Main->fFitFcn->id).c_str()),func_str,LeftLimit->GetNumber(),RightLimit->GetNumber());
	}
	/*Main->fVframe1->RemoveAll();
	Main->AnalyseFitFunctionAndCreatePanels(Main->fFitFcn);*/
	Main->fCanvas->GetCanvas()->cd();
	Main->fFitFcn->SetParameters();
	if(Main->fFitFcn->fFitResult)
	{
		Main->fFitFcn->fFitResult->ReferenceHistogram.Draw("e hist");
		Main->fFitFcn->Function.Draw("same");
	}
	else
	{
		cout<<"This is RootFitLib_gui::CreateForms: pointer to FitResult is invalid! Drawing will be without histogram\n";
		Main->fFitFcn->Function.Draw();
	}
	gPad->Update();
	//Main->FitButtons=new FitButtonFrame(Main->fVframe1,Main);
	//Main->fVframe1->AddFrame(Main->FitButtons,new TGLayoutHints(kFixedWidth | kFixedHeight|kLHintsBottom, 1, 1, 1, 1));
	
}

void RootFitLib_gui::GenerateParFrame(int NPar)
{
	TGLayoutHints *Lay=new TGLayoutHints(kFixedWidth | kFixedHeight, 1, 1, 1, 1);
	for(int i=0;i<NPar;i++)
	{
		FitParFrame *fP=new FitParFrame(fVframe1,TString::Format("Parameter %d",i));
		//fP->SetMinHeight(30);
		FitParameters.push_back(fP);
		fP->Main=this;
		fVframe1->AddFrame(fP, Lay);
	}
}

void RootFitLib_gui::GenerateParFrame(TFitFunction *func)
{
	TGLayoutHints *Lay=new TGLayoutHints(kFixedWidth | kLHintsTop, 1, 1, 1, 1);
	for(unsigned int i=0;i<func->parameters.size();i++)
	{
		FitParFrame *fP=new FitParFrame(fVframe1,TString::Format("par %d",i));
		fP->FromTFitFunction(func,i);
		FitParameters.push_back(fP);
		fVframe1->AddFrame(fP, Lay);
	}
}

void RootFitLib_gui::CreateForms()
{
	fHframe0 = new TGHorizontalFrame(this, 0, 0, 0);
	fVframe0 = new TGVerticalFrame(fHframe0, 0, 0, 0);
	fVframe1 = new TGVerticalFrame(fHframe0, 0, 0, 0);


	fCanvas = new TRootEmbeddedCanvas("Canvas", fVframe0, 600, 400);
	fLcan = new TGLayoutHints(kLHintsExpandX | kLHintsExpandY, 1, 1, 1, 1);//Здесь 10,10,10,10 - размеры полей
	fVframe0->AddFrame(fCanvas, fLcan);
	fCanvas->GetCanvas()->SetFillColor(33);
	fCanvas->GetCanvas()->SetFrameFillColor(41);
	fCanvas->GetCanvas()->SetBorderMode(0);
	fCanvas->GetCanvas()->SetGrid();
	fCanvas->GetCanvas()->SetLogy();

	fHframe0->AddFrame(fVframe0,fLcan);
	
	if(!fFitFcn)
	{
		cout<<"This is RootFitLib_gui::CreateForms: pointer to FitFunction is invalid! Returned\n";
		return; 
	}
	FSFrame=new FunctionStringFrame(fVframe1,this);
	FSFrame->UpdateValuesFromFitFunction(fFitFcn);
	
	//fVframe1->AddFrame(FSFrame,new TGLayoutHints(kFixedWidth | kFixedHeight|kLHintsTop, 1, 1, 1, 1));
	fVframe1->AddFrame(FSFrame,new TGLayoutHints(kLHintsTop, 1, 1, 1, 1));
	
	AnalyseFitFunctionAndCreatePanels(fFitFcn);
	fCanvas->GetCanvas()->cd();
	if(fFitFcn->fFitResult)
	{
		fFitFcn->fFitResult->ReferenceHistogram.Draw("e hist");
		fFitFcn->Function.Draw("same");
	}
	else
	{
		cout<<"This is RootFitLib_gui::CreateForms: pointer to FitResult is invalid! Drawing will be without histogram\n";
		fFitFcn->Function.Draw();
	}
	FitButtons=new FitButtonFrame(fVframe1,this);
	fVframe1->AddFrame(FitButtons,new TGLayoutHints(kLHintsBottom, 1, 1, 1, 1));
	
	
	
	fHframe0->AddFrame(fVframe1,new TGLayoutHints(kFixedWidth | kFixedHeight, 1, 1, 1, 1));
	AddFrame(fHframe0,fLcan);
}

void TestCanv(Int_t event, Int_t x, Int_t y, TObject *selected, TCanvas *c)
{
	if(event==11)
	{
		double xd=c->AbsPixeltoX(x);
		double yd=c->AbsPixeltoY(y);
		cout<<"x:"<<xd<<" y:"<<yd<<" selected:"<<selected->GetName()<<"\n";
		return;
	}
}

//______________________________________________________________________________
RootFitLib_gui::RootFitLib_gui(string funcName,FitManager *m) : TGMainFrame(gClient->GetRoot(), 100, 100)
{

	char buf[32];
	SetCleanup(kDeepCleanup);
	// Create an embedded canvas and add to the main frame, centered in x and y
	// and with 30 pixel margins all around
	if(m)
	{
		fFitManager=m;
		fFitFcn=fFitManager->FindFunction(funcName);
		if(!fFitFcn)
		{
			cout<<"This is RootFitLib_gui: cannot get FitFunction with name \""<<funcName<<"\" from FitManager! Returned\n";
			return; 
		}
	}
	CreateForms();
	MapSubwindows();
	Resize(GetDefaultSize());
	MapWindow();
	fCanvas->GetCanvas()->Connect("ProcessedEvent(Int_t,Int_t,Int_t,TObject*)", "RootFitLib_gui",this,"DoCanvas(Int_t,Int_t,Int_t,TObject*)");
   ProcessCanvasFunction=TestCanv;
  // fCanvas1->GetCanvas()->cd();
  // fFitFcn->Draw();
}

void RootFitLib_gui::DoCanvas(Int_t event, Int_t x, Int_t y, TObject *selected)
{
	TCanvas *c = (TCanvas *) gTQSender;
	if(ActiveWidget)
	{
		//cout<<ActiveWidget->InheritsFrom("FitParFrame")<<"\n";
		if(ActiveWidget->InheritsFrom("FitParFrame"))
		{
			((FitParFrame*)ActiveWidget)->ProcessCanvasFunction(event,x,y,selected,c);
		}
	}
	
}

void RootFitLib_gui::AnalyseFitFunctionAndCreatePanels(TFitFunction *func)
{
	vector<vector<int> > ParametersGroups;
	vector<int> Non_grouped;
	for(unsigned int i=0;i<func->parameters.size();i++)//делаем компоненты из фитирующей функции
	{
		int ComponentIndex=-1;
		TString ParName=func->parameters[i].ParName;
		int underline_index=-1;
		underline_index=ParName.Last('_');
		cout<<"i:"<<i<<" index:"<<underline_index<<"\n";
		int ComponentNumber=-1;
		if(underline_index>-1)
		{
			TString ts=ParName(underline_index+1,ParName.Length());
			cout<<ts<<"\n";
			if(ts.IsDigit())
			{
				ComponentIndex=ts.Atoi();
			}
		}
		else
		{
			Non_grouped.push_back(i);
		}
		if(ComponentIndex>=0)
		{
			if(ParametersGroups.size()<=ComponentIndex)
			{
				ParametersGroups.resize(ComponentIndex+1);
			}
			ParametersGroups[ComponentIndex].push_back(i);
		}
	}
	
	TGLayoutHints *Lay=new TGLayoutHints(kFixedWidth | kFixedHeight, 1, 5, 1, 5);
	for(unsigned int i=0;i<ParametersGroups.size();i++)
	{
		TGGroupFrame* gr=new TGGroupFrame(fVframe1,TString::Format("Component %d",i));
		for(unsigned int j=0;j<ParametersGroups[i].size();j++)
		{
			FitParFrame *fP=new FitParFrame(gr,TString::Format("par %d",ParametersGroups[i][j]));
			fP->FromTFitFunction(func,ParametersGroups[i][j]);
			fP->PointerToParameter=&(func->parameters[ParametersGroups[i][j]]);
			fP->Main=this;
			FitParameters.push_back(fP);
			gr->AddFrame(fP, Lay);
		}
		GroupedParameters.push_back(gr);
		gr->SetTextColor(UColor(i));
		fVframe1->AddFrame(gr, new TGLayoutHints(kFixedWidth | kLHintsTop, 1, 1, 1, 1));
	}
	TGGroupFrame* gr=new TGGroupFrame(fVframe1,"");
	for(unsigned int i=0;i<Non_grouped.size();i++)
	{
		FitParFrame *fP=new FitParFrame(gr,TString::Format("par %d",Non_grouped[i]));
		fP->FromTFitFunction(func,Non_grouped[i]);
		fP->Main=this;
		FitParameters.push_back(fP);
		gr->AddFrame(fP, Lay);
		fP->Resize(200,30);
	}
	fVframe1->AddFrame(gr, new TGLayoutHints(kFixedWidth |kLHintsTop, 1, 1, 1, 1));
}

//______________________________________________________________________________
RootFitLib_gui::~RootFitLib_gui()
{
   // Clean up

   Cleanup();
}

//______________________________________________________________________________
void RootFitLib_gui::CloseWindow()
{
   // Called when window is closed via the window manager.

   delete this;
}


void gui_min2()
{
	//TFile f("SiO2_fits.root");
	FitManager *m=FitManager::GetPointer();
	m->FileName="../tutorial/fits.root";
	//m->ReadFromROOT("../tutorial/fits.root");
	m->ReadFromROOT();
   new RootFitLib_gui("FitFunction",m);
}
