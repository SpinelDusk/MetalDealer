/// \file
/// \brief Form - About (Header)
/// \author SpinelDusk

#pragma once//This header guard directive designed to cause the current source file to be included only once in a single compilation
#ifndef Form_AboutH
#define Form_AboutH

#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Buttons.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Graphics.hpp>
#include <Vcl.Imaging.pngimage.hpp>
#include <System.ImageList.hpp>
#include <Vcl.ImgList.hpp>
#include <vcl.h>
#pragma hdrstop//This directive terminates the list of header files eligible for precompilation (Using ONLY for <standard> headers, no "custom")

#include "CHF.h"

class TFormAbout : public TForm
{
__published:	// IDE-managed Components
	TSpeedButton *SpeedButton_Cancel;
	TImage *ImageIcon;
	TImage *ImageBanner;
	TLabel *Label_Title;
	TLabel *Label_Version;
	TLabel *Label_Author;
	TLabel *Label_Description;
	TLabel *Label_Build;
	TEdit *Edit_Email_EE;
	TEdit *Edit_Email_PM;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall SpeedButton_CancelClick(TObject *Sender);
    void __fastcall ImageBannerClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TFormAbout(TComponent* Owner);
};

extern PACKAGE TFormAbout *FormAbout;
#endif
