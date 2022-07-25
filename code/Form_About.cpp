/// \file
/// \brief Form - About
/// \author SpinelDusk
/// \details Form with description of the program and data of the author

#pragma GCC diagnostic ignored "-Wc++98-compat"					//Disable warning: 'nullptr' is incompatible with C++98
#pragma GCC diagnostic ignored "-Wunused-parameter"				//Disable warning: Parameter is never used

#pragma package(smart_init)
#pragma resource "*.dfm"

#include "Form_About.h"

TFormAbout *FormAbout;
__fastcall TFormAbout::TFormAbout(TComponent* Owner): TForm(Owner){}

extern cnv::unistr Version;	///< Defined in Form_MainGH.cpp
extern cnv::unistr Build;	///< Defined in Form_MainGH.cpp

/// \brief Event for initializing the form
/// \param[in] Sender Pointer to the TObject Class Component that called this function
void __fastcall TFormAbout::FormCreate(TObject *Sender)
{
	Label_Version -> Caption = "Version " + Version;
	Label_Build   -> Caption = "Build " + Build;
}
/// \brief Event for the button to close the form
/// \param[in] Sender Pointer to the TObject Class Component that called this function
void __fastcall TFormAbout::SpeedButton_CancelClick(TObject *Sender)
{
	FormAbout -> Close();
}
/// \brief Event for handling a click on the banner
/// \param[in] Sender Pointer to the TObject Class Component that called this function
void __fastcall TFormAbout::ImageBannerClick(TObject *Sender)
{
	ShellExecute(nullptr, nullptr, L"mailto:spineldusk@mail.ee", nullptr, nullptr, SW_SHOW);
}
