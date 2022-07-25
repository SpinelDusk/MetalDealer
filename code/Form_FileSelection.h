/// \file
/// \brief Form - OpenFile Selection dialog (Header)
/// \author SpinelDusk

#ifndef Form_FileSelectionH
#define Form_FileSelectionH

#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <System.ImageList.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ImgList.hpp>
#include <vcl.h>
#pragma hdrstop//This directive terminates the list of header files eligible for precompilation (Using ONLY for <standard> headers, no "custom")

#include "Form_Main.h"
#include "Form_MainGH.h"
#include "FileMark.h"

class TFormFileSelection : public TForm
{
__published:	// IDE-managed Components
	TImageList *ImageList;
	TImageList *ImageList_Disabled;
	TListView *ListView;
	TCheckBox *CheckBox_Any;
	TLabel *Label_CanBe;
	TButton *Button_Ok;
	TButton *Button_Cancel;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall ListViewSelectItem(TObject *Sender, TListItem *Item, bool Selected);
	void __fastcall ListViewDblClick(TObject *Sender);
	void __fastcall Button_OkClick(TObject *Sender);
	void __fastcall Button_CancelClick(TObject *Sender);
	void __fastcall CheckBox_AnyClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TFormFileSelection(TComponent* Owner);
};

extern PACKAGE TFormFileSelection *FormFileSelection;
#endif
