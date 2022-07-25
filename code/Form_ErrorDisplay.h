/// \file
/// \brief Form - ErrorDisplay (Header)
/// \author SpinelDusk

#pragma once//This header guard directive designed to cause the current source file to be included only once in a single compilation
#ifndef Form_ErrorDisplayH
#define Form_ErrorDisplayH

#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Graphics.hpp>
#include <Vcl.ComCtrls.hpp>
#include <System.ImageList.hpp>
#include <Vcl.ImgList.hpp>
#include <Vcl.Imaging.pngimage.hpp>
#include <fstream>
#include <iostream>
#include <vector>
#include <vcl.h>
#pragma hdrstop//This directive terminates the list of header files eligible for precompilation (Using ONLY for <standard> headers, no "custom")

#include "Conversion.h"
#include "CHF.h"
#include "ErrorDescription.h"

class TFormErrorDisplay : public TForm
{
__published:	// IDE-managed Components
	TImage *ImageIcon_Error;
	TImage *ImageIcon_Warning;
	TLabel *Label_IndexMarker;
	TLabel *Label_TypeMarker;
	TLabel *Label_HeaderMarker;
	TLabel *Label_ModuleMarker;
	TLabel *Label_FunctionMarker;
	TLabel *Label_Line;
	TLabel *Label_AdditionalMarker;
	TLabel *Label_DescriptionMarker;
	TLabel *Label_Time;
	TEdit *Edit_Index;
	TEdit *Edit_Type;
	TEdit *Edit_Header;
	TEdit *Edit_Module;
	TEdit *Edit_Function;
	TEdit *Edit_Line;
	TEdit *Edit_Additional;
	TRichEdit *RichEdit_Description;
	TButton *Button_SaveLog;
	TButton *Button_Close;
	void __fastcall Button_CloseClick(TObject *Sender);
	void __fastcall FormPaint(TObject *Sender);
	void __fastcall Button_SaveLogClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TFormErrorDisplay(TComponent* Owner);
};

int WriteLogAtFile();
extern PACKAGE TFormErrorDisplay *FormErrorDisplay;
#endif
