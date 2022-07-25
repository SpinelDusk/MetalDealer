/// \file
/// \brief Form - OpenFile Selection dialog
/// \author SpinelDusk
/// \details Form with the ability to select the type of file to open

#pragma GCC diagnostic ignored "-Wc++98-compat"					//Disable warning: 'nullptr' is incompatible with C++98
#pragma GCC diagnostic ignored "-Wunused-parameter"				//Disable warning: Parameter is never used

#pragma package(smart_init)
#pragma resource "*.dfm"

#include "Form_FileSelection.h"

TFormFileSelection *FormFileSelection;
__fastcall TFormFileSelection::TFormFileSelection(TComponent* Owner): TForm(Owner){}

extern int ForceOpen;				///< Defined in Form_MainGH.cpp
extern int FileTypeFromSelection;	///< Defined in Form_MainGH.cpp

/// \brief Form handling on opening
/// \param[in] Sender Pointer to the TObject Class Component that called this function
void __fastcall TFormFileSelection::FormShow(TObject *Sender)
{
	CheckBox_Any -> Checked = false;
	ListView -> ItemIndex = -1;//Resets focus when the form is opened
	Button_Ok -> Enabled = false;
	FileTypeFromSelection = FM_NOTYPE;
}
/// \brief Handling selection of an item by double click
/// \param[in] Sender Pointer to the TObject Class Component that called this function
void __fastcall TFormFileSelection::ListViewDblClick(TObject *Sender)
{
	FileTypeFromSelection = ListView -> Items -> Item[ListView -> ItemIndex] -> StateIndex;
	FormFileSelection -> Close();
}
/// \brief Handling the Ok button
/// \param[in] Sender Pointer to the TObject Class Component that called this function
void __fastcall TFormFileSelection::Button_OkClick(TObject *Sender)
{
	if(CheckBox_Any -> Checked)
	{
		ForceOpen = 1;
		FileTypeFromSelection = FM_ALL_CHECKBOX;
	}
	else
	{
		FileTypeFromSelection = ListView -> Items -> Item[ListView -> ItemIndex] -> StateIndex;
	}
	FormFileSelection -> Close();
}
/// \brief Handling the Cancel button
/// \param[in] Sender Pointer to the TObject Class Component that called this function
void __fastcall TFormFileSelection::Button_CancelClick(TObject *Sender)
{
	FileTypeFromSelection = FM_NOTYPE;
	FormFileSelection -> Close();
}
/// \brief Handling 'Force Dialog Box Opening' checkbox (any file)
/// \param[in] Sender Pointer to the TObject Class Component that called this function
void __fastcall TFormFileSelection::CheckBox_AnyClick(TObject *Sender)
{
	if(CheckBox_Any -> Checked)
	{
		ListView -> LargeImages = ImageList_Disabled;
		ListView -> Enabled = false;
		Button_Ok -> Enabled = true;
	}
	else
	{
		ListView -> LargeImages = ImageList;
		ListView -> Enabled = true;
		Button_Ok -> Enabled = false;
	}
}
/// \brief Handling clicks on an item from the ListView
/// \param[in] Sender Pointer to the TObject Class Component that called this function
/// \param[in] Item Pointer to the TListItem Class Component that point on a item for this TListItem
/// \param[in] Selected Indicates whether the list item is selected
void __fastcall TFormFileSelection::ListViewSelectItem(TObject *Sender, TListItem *Item, bool Selected)
{
	if(ListView -> ItemIndex != -1)
	{
		Button_Ok -> Enabled = true;
	}
	else
	{
		Button_Ok -> Enabled = false;
	}
}
