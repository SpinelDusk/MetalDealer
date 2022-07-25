/// \file
/// \brief Form - Main (SECTION - Main Menu Handlers)
/// \author SpinelDusk
/// \details Processes all items of the interface element 'Main Menu'

#pragma GCC diagnostic ignored "-Wc++98-compat"					//Disable warning: 'nullptr' is incompatible with C++98
#pragma GCC diagnostic ignored "-Wunused-parameter"				//Disable warning: Parameter is never used

#pragma package(smart_init)

#include "Form_MainMM.h"

/// \brief "Open file" button handler
/// \param[in] Sender Pointer to the TObject Class Component that called this function
void __fastcall TFormMain::mm_OpenClick(TObject *Sender)
{
	OpenFile();
}
/// \brief "Close file" button handler
/// \param[in] Sender Pointer to the TObject Class Component that called this function
void __fastcall TFormMain::mm_CloseClick(TObject *Sender)
{
	CloseFile();
}
/// \brief "Close file" button handler
/// \param[in] Sender Pointer to the TObject Class Component that called this function
void __fastcall TFormMain::mm_ExitClick(TObject *Sender)
{
	TCloseAction ca = caFree;//http://www.tdoc.ru/c/programming/delphi/delphi-components-part3-page9.html
	FormClose(nullptr, ca);
}
/// \brief Opening of the modal window "About"
/// \param[in] Sender Pointer to the TObject Class Component that called this function
void __fastcall TFormMain::mm_AboutClick(TObject *Sender)
{
	FormAbout -> ShowModal();
}
