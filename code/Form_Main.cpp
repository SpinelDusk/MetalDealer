/// \file
/// \brief Form - Main
/// \author SpinelDusk
/// \details Lead module of Main Form

#pragma GCC diagnostic ignored "-Wc++98-compat"					//Disable warning: 'nullptr' is incompatible with C++98
#pragma GCC diagnostic ignored "-Wexit-time-destructors"		//Disable warning: Declaration requires an exit-time destructor
#pragma GCC diagnostic ignored "-Wglobal-constructors"			//Disable warning: Declaration requires a global destructor
#pragma GCC diagnostic ignored "-Wmissing-variable-declarations"//Disable warning: No previous extern declaration for non-static variable
#pragma GCC diagnostic ignored "-Wunused-parameter"				//Disable warning: Parameter is never used

#pragma package(smart_init)
#pragma link "cgrid"
#pragma resource "*.dfm"

#include "Form_Main.h"

TFormMain *FormMain;
__fastcall TFormMain::TFormMain(TComponent* Owner): TForm(Owner){}

/// \brief Instance of class that handles all processes for unpacking an SOL archive
SolUnpack SolUObject;
/// \brief Instance of class that handles all processes for unpacking an PAK archive
PakUnpack PakUObject;
/// \brief Instance of class that handles all processes for unpacking an FST archive
FstUnpack FstUObject;

/// \brief Function for testing experimental functionality launched from the program's graphical interface
/// \param[in] Sender Pointer to the TObject Class Component that called this function
void __fastcall TFormMain::ToolButton_TestClick(TObject *Sender)
{
	//
}
