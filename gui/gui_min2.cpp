/// \file
/// \ingroup tutorial_gui
/// Simple macro showing capabilities of triple slider
///
/// \macro_code
///
/// \author Bertrand Bellenot, Ilka Antcheva


#include "gui_min2.hh"
#pragma once

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
	AddFrame(Update, new TGLayoutHints(kLHintsCenterX|kLHintsCenterY,20, 20, 20, 20));
	fMainFrame=Main;
	Update->Connect("Clicked()","FitButtonFrame", this, "FUpdate()");
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
	func->Function.Draw();
	gPad->Update();
	cout<<"Update\n";
	for(unsigned int i=0;i<func->parameters.size();i++)
	{
		fMainFrame->FitParameters[i]->FromTFitFunction(func,i);
	}
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
	ParName=new TGLabel(this, TString::Format("%-10s\t",ParName_.Data()));
	
	AddFrame(ParName,new TGLayoutHints(kLHintsLeft|kLHintsCenterY, 0));
	AddFrame(ParValue, new TGLayoutHints(kLHintsCenterY | kLHintsLeft, 1, 5, 1, 5));
	AddFrame(ParError, new TGLayoutHints(kLHintsCenterY | kLHintsLeft, 1, 5, 1, 5));
	AddFrame(MinLimit, new TGLayoutHints(kLHintsCenterY | kLHintsLeft, 1, 5, 1, 5));
	AddFrame(MaxLimit, new TGLayoutHints(kLHintsCenterY | kLHintsLeft, 1, 5, 1, 5));
	AddFrame(Fixed, new TGLayoutHints(kLHintsCenterY | kLHintsLeft, 1, 5, 1, 5));
	AddFrame(Limited, new TGLayoutHints(kLHintsCenterY | kLHintsLeft, 1, 5, 1, 5));

	Limited->SetState(Pressed(true));
}


void RootFitLib_gui::GenerateParFrame(int NPar)
{
	TGLayoutHints *Lay=new TGLayoutHints(kFixedWidth | kLHintsExpandY, 1, 1, 1, 1);
	for(int i=0;i<NPar;i++)
	{
		FitParFrame *fP=new FitParFrame(fVframe1,TString::Format("Parameter %d",i));
		FitParameters.push_back(fP);
		fVframe1->AddFrame(fP, Lay);
	}
}

void RootFitLib_gui::GenerateParFrame(TFitFunction *func)
{
	TGLayoutHints *Lay=new TGLayoutHints(kFixedWidth | kLHintsExpandY, 1, 1, 1, 1);
	for(unsigned int i=0;i<func->parameters.size();i++)
	{
		FitParFrame *fP=new FitParFrame(fVframe1,TString::Format("par %d",i));
		fP->FromTFitFunction(func,i);
		FitParameters.push_back(fP);
		fVframe1->AddFrame(fP, Lay);
	}
}

//______________________________________________________________________________
RootFitLib_gui::RootFitLib_gui() : TGMainFrame(gClient->GetRoot(), 100, 100)
{

   char buf[32];
   SetCleanup(kDeepCleanup);
   // Create an embedded canvas and add to the main frame, centered in x and y
   // and with 30 pixel margins all around
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
   
   fFitFcn = new TFitFunction();
   fFitFcn->id="Fit_9_HPGe_0_0";
   fFitFcn->ReadFromTXTFile("fits.txt");
   //GenerateParFrame(fFitFcn);
   AnalyseFitFunctionAndCreatePanels(fFitFcn);
   
   fCanvas->GetCanvas()->cd();
   fFitFcn->Function.Draw();
   
   
   
   FitButtons=new FitButtonFrame(fVframe1,this);
	fVframe1->AddFrame(FitButtons,new TGLayoutHints(kFixedWidth | kFixedHeight, 1, 1, 1, 1));
	
	fHframe0->AddFrame(fVframe1,new TGLayoutHints(kFixedWidth | kFixedHeight, 1, 1, 1, 1));
	AddFrame(fHframe0,fLcan);
   MapSubwindows();
   Resize(GetDefaultSize());
   MapWindow();

   
  // fCanvas1->GetCanvas()->cd();
  // fFitFcn->Draw();
   

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
	
	TGLayoutHints *Lay=new TGLayoutHints(kFixedWidth | kLHintsExpandY, 1, 5, 1, 5);
	for(unsigned int i=0;i<ParametersGroups.size();i++)
	{
		TGGroupFrame* gr=new TGGroupFrame(fVframe1,TString::Format("Component %d",i));
		for(unsigned int j=0;j<ParametersGroups[i].size();j++)
		{
			FitParFrame *fP=new FitParFrame(gr,TString::Format("par %d",ParametersGroups[i][j]));
			fP->FromTFitFunction(func,ParametersGroups[i][j]);
			FitParameters.push_back(fP);
			gr->AddFrame(fP, Lay);
		}
		GroupedParameters.push_back(gr);
		gr->SetTextColor(UColor(i));
		fVframe1->AddFrame(gr, new TGLayoutHints(kFixedWidth | kFixedHeight, 1, 1, 1, 1));
	}
	TGGroupFrame* gr=new TGGroupFrame(fVframe1,"");
	for(unsigned int i=0;i<Non_grouped.size();i++)
	{
		FitParFrame *fP=new FitParFrame(gr,TString::Format("par %d",Non_grouped[i]));
		fP->FromTFitFunction(func,Non_grouped[i]);
		FitParameters.push_back(fP);
		gr->AddFrame(fP, Lay);
	}
	fVframe1->AddFrame(gr, new TGLayoutHints(kFixedWidth | kFixedHeight, 1, 1, 1, 1));
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
   new RootFitLib_gui();
}
