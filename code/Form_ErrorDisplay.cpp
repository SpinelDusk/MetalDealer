/// \file
/// \brief Form - ErrorDisplay
/// \author SpinelDusk
/// \details Form called when the error function runs

#pragma GCC diagnostic ignored "-Wc++98-compat"					//Disable warning: 'nullptr' is incompatible with C++98
#pragma GCC diagnostic ignored "-Wexit-time-destructors"		//Disable warning: Declaration requires an exit-time destructor
#pragma GCC diagnostic ignored "-Wglobal-constructors"			//Disable warning: Declaration requires a global destructor
#pragma GCC diagnostic ignored "-Wmissing-variable-declarations"//Disable warning: No previous extern declaration for non-static variable
#pragma GCC diagnostic ignored "-Wold-style-cast"				//Disable warning: Use of old-style cast
#pragma GCC diagnostic ignored "-Wunused-parameter"				//Disable warning: Parameter is never used

#pragma package(smart_init)
#pragma resource "*.dfm"

#include "Form_ErrorDisplay.h"

extern cnv::unistr OpenedFileName;								///< Defined in Form_MainGH.cpp
extern std::vector<std::vector <cnv::unistr>> ErrorDescription;	///< Defined in ErrorDescription.cpp
extern ErrorData LastError;										///< Defined in ErrorDescription.cpp

TFormErrorDisplay *FormErrorDisplay;
__fastcall TFormErrorDisplay::TFormErrorDisplay(TComponent* Owner): TForm(Owner){}

/// \brief Form repaint function
/// \param[in] Sender Pointer to the TObject Class Component that called this function
void __fastcall TFormErrorDisplay::FormPaint(TObject *Sender)
{
	//Customizing the appearance of the form depending on the type of error
	if(LastError.ErrorIndex == 50000)//Unreachable code. Currently there are no errors of this type
	{
		Edit_Type -> Text = "Warning";
		FormErrorDisplay -> Caption = "Warning";
		ImageIcon_Warning -> Visible = true;
		ImageIcon_Error -> Visible = false;
	}
	else
	{
		Edit_Type -> Text = "Error";
		FormErrorDisplay -> Caption = "Error";
		ImageIcon_Warning -> Visible = false;
		ImageIcon_Error -> Visible = true;
    }

	//Displaying error information
	RichEdit_Description-> Lines 	-> Clear();
	RichEdit_Description-> Lines 	-> Add(ErrorDescription.at(LastError.DescriptionSet).at(LastError.ErrorIndex * 2));
	Edit_Index 			-> Text 	= LastError.ErrorIndex;
	Edit_Header			-> Text 	= ErrorDescription.at(LastError.DescriptionSet).at((LastError.ErrorIndex * 2) + 1);
	Edit_Module			-> Text		= CHARtoUSTRING(LastError.File);
	Edit_Function 		-> Text 	= LastError.Function;
	Edit_Line			-> Text		= LastError.Line;
    Edit_Additional		-> Text		= CHARtoUSTRING(LastError.Additional);

	//Date and time output (https://www.cplusplus.com/reference/ctime/strftime/)
	time_t DateSeconds = time(nullptr);
	tm* DateInfo = localtime(&DateSeconds);
	char* OutDate = new char[22];
	std::string DateFormat = "%y.%m.%d -- %H:%M:%S";
	strftime(OutDate, 22, DateFormat.data(), DateInfo);
	Label_Time -> Caption = OutDate;
	delete[] OutDate;

	//Handling the log button
	Button_SaveLog -> Enabled = true;
	Button_SaveLog -> Caption = "Save log";
}
/// \brief Function for writing basic information about an error to the log file
/// \return int If the operation completed successfully - 0, otherwise - 1
int WriteLogAtFile()
{
	time_t DateSeconds = time(nullptr);
	tm* DateInfo = localtime(&DateSeconds);
	std::string LogFileName;
	std::string MDEL = "MetalDealer_ErrorLog_";
	char* OutDate = new char[22];
	std::string DotLog = ".log";
	std::string DateFormat_LogName = "%y%m%d_%H%M%S";
	std::string DateFormat_LogNote = "%y.%m.%d -- %H:%M:%S";

	strftime(OutDate, 22, DateFormat_LogName.data(), DateInfo);

	LogFileName = MDEL + OutDate + DotLog;

	strftime(OutDate, 22, DateFormat_LogNote.data(), DateInfo);

	ofstream LogFileOut(LogFileName.data());
	if(!LogFileOut.is_open())
	{
		delete[] OutDate;
		return 1;
	}
	else
	{
		LogFileOut <<	"Date       : " << OutDate << std::endl <<
						"Index      : " << LastError.ErrorIndex << std::endl <<
						"Type       : " << USTRINGtoCHAR(FormErrorDisplay -> Caption) << std::endl <<
						"Header     : " << USTRINGtoCHAR(ErrorDescription.at(LastError.DescriptionSet).at((LastError.ErrorIndex * 2) + 1)) << std::endl <<
						"Module     : " << LastError.File << std::endl <<
						"Function   : " << USTRINGtoCHAR(ErrorDescription.at(LastError.DescriptionSet).at((LastError.ErrorIndex * 2) + 1)) << std::endl <<
						"Line       : " << USTRINGtoCHAR(ErrorDescription.at(LastError.DescriptionSet).at(LastError.ErrorIndex * 2)) << std::endl <<
						"Additional : " << LastError.Additional << std::endl <<
						"Description: " << USTRINGtoCHAR(ErrorDescription.at(LastError.DescriptionSet).at(LastError.ErrorIndex * 2));
		LogFileOut.close();
		delete[] OutDate;
		return 0;
	}
}
/// \brief Button handler Save Log
/// \param[in] Sender Pointer to the TObject Class Component that called this function
void __fastcall TFormErrorDisplay::Button_SaveLogClick(TObject *Sender)
{
	if(WriteLogAtFile() == 0)
	{
		Button_SaveLog -> Enabled = false;
		Button_SaveLog -> Caption = "Saved";
	}
	else
	{
		Button_SaveLog -> Enabled = false;
		Button_SaveLog -> Caption = "Fail";
    }
}
/// \brief Button handler Close
/// \param[in] Sender Pointer to the TObject Class Component that called this function
void __fastcall TFormErrorDisplay::Button_CloseClick(TObject *Sender)
{
	FormErrorDisplay -> Close();
}

