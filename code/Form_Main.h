/// \file
/// \brief Form - Main (Header)
/// \author SpinelDusk

#pragma once//This header guard directive designed to cause the current source file to be included only once in a single compilation
#ifndef Form_MainH
#define Form_MainH

#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.Buttons.hpp>
#include "cgrid.h"
#include <Vcl.CheckLst.hpp>
#include <Vcl.ColorGrd.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.FileCtrl.hpp>
#include <Vcl.Grids.hpp>
#include <Vcl.ValEdit.hpp>
#include <Vcl.ActnColorMaps.hpp>
#include <Vcl.ActnCtrls.hpp>
#include <Vcl.ActnMan.hpp>
#include <Vcl.ActnMenus.hpp>
#include <Vcl.CategoryButtons.hpp>
#include <Vcl.CustomizeDlg.hpp>
#include <Vcl.ToolWin.hpp>
#include <Vcl.Menus.hpp>
#include <Vcl.ButtonGroup.hpp>
#include <System.ImageList.hpp>
#include <Vcl.ImgList.hpp>
#include <string>
#include <fstream>
#include <string>
#include <cmath>
#include <sstream>
#include <vcl.h>
#include <io.h>
#pragma hdrstop//This directive terminates the list of header files eligible for precompilation (Using ONLY for <standard> headers, no "custom")

#include "CHF.h"
#include "Form_About.h"
#include "Form_FileSelection.h"
#include "Form_ErrorDisplay.h"

class TFormMain : public TForm
{
__published:	// IDE-managed Components
	TMainMenu *MainMenu;
		TMenuItem *mm_File;
			TMenuItem *mm_Open;
			TMenuItem *mm_Close;
			TMenuItem *mm_Exit;
		TMenuItem *mm_Help;
			TMenuItem *mm_About;

	TToolBar *ToolBar;
		TToolButton *ToolButton_OpenFile;
		TToolButton *ToolButton_CloseFile;
		TToolButton *ToolButton__SepMain;
		TToolButton *ToolButton_ExtractSingle;
	TToolButton *ToolButton_Unpack;
		TToolButton *ToolButton_GetListStruct;
		TToolButton *ToolButton_CombinedExtractionMode;
		TToolButton *ToolButton__SepSystem;
		TToolButton *ToolButton_System;
		TToolButton *ToolButton_Test;

	TListView *ListView;
	TRichEdit *RichEdit;
	TStatusBar *StatusBar;

	TOpenDialog *OpenDialog;
	TTimer *Timer_StatusBar;
	TImageList *ImageList_ColorPoint;
	TImageList *ImageList_MainMenu;
	TImageList *ImageList_ToolBar;
	TMenuItem *mm_Processes;
	TMenuItem *mm_ExtractSingle;
	TMenuItem *mm_Unpack;
	TMenuItem *mm_GetListStruct;
	TMenuItem *mm_CombinedExtractionMode;

	void __fastcall mm_OpenClick(TObject *Sender);
	void __fastcall mm_CloseClick(TObject *Sender);
	void __fastcall mm_ExitClick(TObject *Sender);
	void __fastcall mm_AboutClick(TObject *Sender);

 	void __fastcall ToolButton_ExtractSingleClick(TObject *Sender);
	void __fastcall ToolButton_UnpackClick(TObject *Sender);
	void __fastcall ToolButton_GetListStructClick(TObject *Sender);
	void __fastcall ToolButton_CombinedExtractionModeClick(TObject *Sender);

	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall Sender_SystemClick(TObject *Sender);
	void __fastcall ToolButton_TestClick(TObject *Sender);

	void __fastcall ListViewClick(TObject *Sender);
	void __fastcall ListViewKeyUp(TObject *Sender, WORD &Key, TShiftState Shift);

	void __fastcall Timer_StatusBarTimer(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TFormMain(TComponent* Owner);
	bool __fastcall GetOpenDialog(cnv::unsint);
	void __fastcall RichClear();
	void __fastcall RichWrite(cnv::unistr);
	void __fastcall RichWrite(cnv::unistr, int);
	void __fastcall RichWrite(cnv::unistr, cnv::dword);
	void __fastcall RichWrite(cnv::unistr, BYTE, BYTE, BYTE);
    void __fastcall RichWriteS(cnv::unistr);
	void __fastcall RichWriteS(std::string);
	void __fastcall SetFormCaption();
	void __fastcall SetFormCaption(cnv::unistr);
	void __fastcall SetFormCaptionChange();
	void __fastcall RichViewIndex();
	void __fastcall OpenFile();
    void __fastcall CloseFile();
	void __fastcall ListViewFill();
	void __fastcall StatusBarText(cnv::unistr);
	void __fastcall StatusBarClear();
	int  __fastcall RunProcess(cnv::unsint Mode);

	void __fastcall LoadProgress_Set(cnv::unsint, cnv::unsint, char*, cnv::unistr);
	void __fastcall LoadProgress_Set(cnv::unsint, cnv::unsint, cnv::unistr , cnv::unistr);
	void __fastcall LoadProgress_Destroy();

	void __fastcall ShowError(int, char*);
	void __fastcall ShowError(int, char*, char*);
	void __fastcall ShowError(int, char*, cnv::unistr);

	void __fastcall Processor_FST_Load();
	void __fastcall Processor_FST_CreateFileList();
	TListItem *ListItem;
};

int GetModeFromExt(char* Input);
int GetFileTypeFromSignature(char* Input);

extern PACKAGE TFormMain *FormMain;
#endif

/// \mainpage SolFile technical documentation
