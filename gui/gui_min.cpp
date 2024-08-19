/// \file
/// \ingroup tutorial_gui
/// Simple macro showing capabilities of triple slider
///
/// \macro_code
///
/// \author Bertrand Bellenot, Ilka Antcheva

#include "TGButton.h"
#include "TRootEmbeddedCanvas.h"
#include "TGLayout.h"
#include "TF1.h"
#include "TMath.h"
#include "TCanvas.h"
#include "TGTextEntry.h"
#include "TGTripleSlider.h"

enum ETestCommandIdentifiers {
   HId1,
   HId2,
   HId3,
   HCId1,
   HCId2,

   HSId1
};

class FitParFrame : public TGHorizontalFrame
{
	public:
	TGNumberEntry *ParValue,*ParError,*LeftLimit,*RightLimit;
	TGCheckButton *Fixed,*Limited;
	TGLabel *ParName;
	FitParFrame(TGFrame *fFrame,TString ParName_="");
};

FitParFrame::FitParFrame(TGFrame *fFrame,TString ParName_) : TGHorizontalFrame(fFrame, 0, 0, 0)
{
	ParValue=new TGNumberEntry(this,0,9);
	ParError=new TGNumberEntry(this,0,9);
	LeftLimit=new TGNumberEntry(this,0,9);
	RightLimit=new TGNumberEntry(this,0,9); 
	Fixed=new TGCheckButton(this," Fixed");
	Limited=new TGCheckButton(this,"Limited");
	ParName=new TGLabel(this, ParName_);
	
	AddFrame(ParName,new TGLayoutHints(kLHintsLeft|kLHintsCenterY, 0));
	AddFrame(ParValue, new TGLayoutHints(kLHintsCenterY | kLHintsLeft, 1, 1, 1, 1));
	AddFrame(ParError, new TGLayoutHints(kLHintsCenterY | kLHintsLeft, 1, 1, 1, 1));
	AddFrame(LeftLimit, new TGLayoutHints(kLHintsCenterY | kLHintsLeft, 1, 1, 1, 1));
	AddFrame(RightLimit, new TGLayoutHints(kLHintsCenterY | kLHintsLeft, 1, 1, 1, 1));
	AddFrame(Fixed, new TGLayoutHints(kLHintsCenterY | kLHintsLeft, 1, 1, 1, 1));
	AddFrame(Limited, new TGLayoutHints(kLHintsCenterY | kLHintsLeft, 1, 1, 1, 1));

}

class RootFitLib_gui : public TGMainFrame {

private:
   TRootEmbeddedCanvas *fCanvas,*fCanvas1;
   TGLayoutHints       *fLcan;
   TF1                 *fFitFcn;
   TGVerticalFrame   *fVframe0, *fVframe1, *fVframe2;
   TGHorizontalFrame   *fHframe0, *fHframe1, *fHframe2;
   TGLayoutHints       *fBly, *fBfly1, *fBfly2, *fBfly3;
   TGTripleHSlider     *fHslider1;
   TGTextEntry         *fTeh1, *fTeh2, *fTeh3;
   TGTextBuffer        *fTbh1, *fTbh2, *fTbh3;
   TGCheckButton       *fCheck1, *fCheck2;
   vector<FitParFrame*> FitParameters;
   void GenerateParFrame(int NPar);

public:
   RootFitLib_gui();
   virtual ~RootFitLib_gui();

   void CloseWindow();
   void DoText(const char *text);
   void DoSlider();
   void HandleButtons();

   ClassDef(RootFitLib_gui, 0);
};

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
   GenerateParFrame(10);
	
	
	fHframe0->AddFrame(fVframe1,new TGLayoutHints(kFixedWidth | kFixedHeight, 1, 1, 1, 1));
	AddFrame(fHframe0,fLcan);
   MapSubwindows();
   Resize(GetDefaultSize());
   MapWindow();

   fFitFcn = new TF1("fFitFcn", "TMath::LogNormal(x, [0], [1], [2])", 0, 5);
   fFitFcn->SetRange(0.0, 2.5);
   fFitFcn->SetParameters(1.0, 0, 1);
   fFitFcn->SetMinimum(1.0e-3);
   fFitFcn->SetMaximum(10.0);
   fFitFcn->SetLineColor(kRed);
   fFitFcn->SetLineWidth(1);
   fCanvas->GetCanvas()->cd();
   fFitFcn->Draw();
  // fCanvas1->GetCanvas()->cd();
  // fFitFcn->Draw();
   

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


void gui_min()
{
   new RootFitLib_gui();
}
