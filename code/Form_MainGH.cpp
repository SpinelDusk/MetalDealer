/// \file
/// \brief Form - Main (SECTION - Global program handler)
/// \author SpinelDusk
/// \details Contains the main processing functions placed on Main Form. Handles graphics elements such as 'Form Caption', 'RichEdit'

#pragma GCC diagnostic ignored "-Wc++98-compat"					//Disable warning: 'nullptr' is incompatible with C++98
#pragma GCC diagnostic ignored "-Wdate-time"                    //Disable warning: Expansion of date or time macro is not reproducible
#pragma GCC diagnostic ignored "-Wdisabled-macro-expansion"		//Disable warning: Disabled expansion of recursive macro
#pragma GCC diagnostic ignored "-Wexit-time-destructors"		//Disable warning: Declaration requires an exit-time destructor
#pragma GCC diagnostic ignored "-Wglobal-constructors"			//Disable warning: Declaration requires a global destructor
#pragma GCC diagnostic ignored "-Wlanguage-extension-token"		//Disable warning: Extension used
#pragma GCC diagnostic ignored "-Wmissing-noreturn"				//Disable warning: Function could be declared with attribute 'noreturn'
#pragma GCC diagnostic ignored "-Wmissing-variable-declarations"//Disable warning: No previous extern declaration for non-static variable
#pragma GCC diagnostic ignored "-Wunused-parameter"				//Disable warning: Parameter is never used

#pragma package(smart_init)

#include "Form_MainGH.h"

/// \brief Macro makes it easy to write SendAlert function in the code
#define SendAlert(a,b) SendAlert(__FILE__,__FUNCSIG__,__LINE__,a,0,b)

/// \brief Global app mutex
HANDLE Mutex;
/// \brief App version
cnv::unistr Version = "1.0.1";
/// \brief App build (compilation date)
cnv::unistr Build = "220816";
/// \brief Compile time stamp (compilation date and time - in moment)
cnv::unistr CompileStamp = CONSTCHARtoUSTRING(__DATE__) + " " + CONSTCHARtoUSTRING(__TIME__);
/// \brief App command-line arguments string
LPWSTR *argv;
/// \brief Amount of command-line arguments
int argc;

/// \brief Type of loaded file in the app
cnv::unsint FileType = 0;
/// \brief Type of selected file in the app
cnv::unsint FileTypeFromSelection = 0;
/// \brief Forced opening of any files
int ForceOpen = 0;
/// \brief Open file path
cnv::unistr OpenedFileName;

extern SolUnpack SolUObject;///< Defined in Form_Main.cpp
extern PakUnpack PakUObject;///< Defined in Form_Main.cpp
extern FstUnpack FstUObject;///< Defined in Form_Main.cpp

/// \brief Event for initializing the form
/// \details Event executes the primary procedures when the application is launched and the application's main form is created
/// \param[in] Sender Pointer to the TObject Class Component that called this function
void __fastcall TFormMain::FormCreate(TObject *Sender)
{
	//Trying to create a mutex when opening the program
	Mutex = CreateMutex(nullptr, true, L"MetalDealerMutexMark");
	DWORD MutexResult;
	MutexResult = WaitForSingleObject(Mutex, 0);
	if(MutexResult != WAIT_OBJECT_0)
	{
		MessageBox(nullptr, L"Metal Dealer is already running.", L"Metal Dealer", MB_OK|MB_ICONERROR);
		Application -> ShowMainForm = false;
		Application -> Terminate();
	}

	argv = CommandLineToArgvW(GetCommandLineW(), &argc);
	FormMain -> Constraints -> MinWidth = 814;
	FormMain -> Constraints -> MinHeight = 659;
    SetFormCaption();

	//Reading startup parameters and finding the command for expanded mode
	for(int i = 1; i < argc; i++)
	{
		if(!wcscmp(argv[i], L"-xpndd"))
		{
			ToolButton_Test -> Visible = true;
			ToolButton_System -> Visible = true;
			ToolButton__SepSystem -> Visible = true;
		}
	}
}
/// \brief Event for setting caption of the form
void __fastcall TFormMain::SetFormCaption()
{
	FormMain -> Caption = "Metal Dealer " + Version;
}
/// \brief Event for setting caption of the form with additional string
/// \param[in] local_Input Message for the form header (usually path to an open file)
void __fastcall TFormMain::SetFormCaption(cnv::unistr local_Input)
{
	FormMain -> Caption = "Metal Dealer " + Version + " - " + local_Input;
}
/// \brief Event for displaying system variables in the TextView
/// \param[in] Sender Pointer to the TObject Class Component that called this function
void __fastcall TFormMain::Sender_SystemClick(TObject *Sender)
{
	RichClear();
	RichWrite("argc          : ", argc);
	for(int i = 0; i < argc; i++)
	{
		cnv::unistr Counter = INTtoUSTRING(i);
		RichWrite("argv " + Counter + ": " + argv[i]);
	}
	RichWrite("Version       : " + Version);
	RichWrite("Build         : " + Build);
	RichWrite("CompileStamp  : " + CompileStamp);
	RichWrite("FileType      : ", static_cast<int>(FileType));
	RichWrite("FileTypeFrSel : ", static_cast<int>(FileTypeFromSelection));
	RichWrite("OpenedFileName: " + OpenedFileName);
//	RichWrite(static_cast<cnv::unistr>("ForceOpen     : ") + ForceOpen);
}
/// \brief Event to handle closing of the form
/// \param[in] Sender Pointer to the TObject Class Component that called this function
/// \param[in] Action Reference to the TCloseAction Class Component defining the closing action for the form
void __fastcall TFormMain::FormClose(TObject *Sender, TCloseAction &Action)
{
	ReleaseMutex(Mutex);
	CloseHandle(Mutex);
	exit(0);
}
/// \brief Event for writing a string to the TextView
/// \param [in] local_Input The string output to the TextView
void __fastcall TFormMain::RichWrite(cnv::unistr local_Input)
{
	RichEdit -> Lines -> Add(local_Input);
}
/// \brief Event for writing a string to the TextView with INT number
/// \param [in] local_Input The string output to the TextView
/// \param [in] local_InputNum The int output to the TextView
void __fastcall TFormMain::RichWrite(cnv::unistr local_Input, int local_InputNum)
{
	cnv::unistr local_Output = local_Input;
	local_Output += INTtoUSTRING(local_InputNum);
	RichEdit -> Lines -> Add(local_Output);
}
/// \brief Event for writing a string to the TextView with DWORD number
/// \param [in] local_Input The string output to the TextView
/// \param [in] local_InputNum The int output to the TextView
void __fastcall TFormMain::RichWrite(cnv::unistr local_Input, cnv::dword local_InputNum)
{
	cnv::unistr local_Output = local_Input;
	local_Output += DWORDtoUSTRING(local_InputNum);
	RichEdit -> Lines -> Add(local_Output);
}
/// \brief Event for writing a string to the TextView with selected color
/// \param [in] local_Input The string output to the TextView
/// \param [in] R Red component of color
/// \param [in] G Green component of color
/// \param [in] B Blue component of color
void __fastcall TFormMain::RichWrite(cnv::unistr local_Input, BYTE R, BYTE G, BYTE B)
{
	RichEdit -> SelAttributes -> Color = static_cast<TColor>(RGB(R,G,B));
	RichEdit -> Lines -> Add(local_Input);
}
/// \brief Event for writing a string (cnv::unistr) to the TextView
/// \param [in] local_Input The string output to the TextView
void __fastcall TFormMain::RichWriteS(cnv::unistr local_Input)
{
	RichEdit -> Lines -> Add(local_Input);
}
/// \brief Event for writing a string (std::string) to the TextView
/// \param [in] local_Input The string output to the TextView
void __fastcall TFormMain::RichWriteS(std::string local_Input)
{
	RichEdit -> Lines -> Add(local_Input.c_str());
}
/// \brief Event to clear the TextView
void __fastcall TFormMain::RichClear()
{
	RichEdit -> Clear();
}
/// \brief Opens "Open File" dialog box
/// \param [in] Mode Open mode
/// \return bool If a file was selected - true, if the operation was aborted - false
bool __fastcall TFormMain::GetOpenDialog(cnv::unsint Mode)
{
	cnv::unistr All 			= "All supported files (*.dpk; *.fst; *.mpk; *.pak; *.pkk; *.sav; *.sol; *.pal; *.shp; *.tga)|*.dpk; *.fst; *.mpk; *.pak; *.pkk; *.sav; *.sol; *.pal; *.shp; *.tga";
	cnv::unistr Any				= "Any file|*.*";
	cnv::unistr Archives		= "All supported archive files (*.dpk; *.fst; *.mpk; *.pak; *.pkk; *.sav; *.sol)|*.dpk; *.fst; *.mpk; *.pak; *.pkk; *.sav; *.sol";
	cnv::unistr Graphics 		= "All supported graphics files (*.pal; *.shp; *.tga)|*.pal; *.shp; *.tga";
	cnv::unistr DPK 			= "DPK (Distribution file) (*.dpk)|*.dpk";
	cnv::unistr FST 			= "FST (FastFile archive) (*.fst)|*.fst";
	cnv::unistr MPK				= "MPK (Multiplayer map) (*.mpk)|*.mpk";
	cnv::unistr PAK 			= "PAK (FEEDFACE index archive) (*.pak)|*.pak";
	cnv::unistr PKK 			= "PKK (Campaign start file) (*.pkk)|*.pkk";
	cnv::unistr SAV 			= "SAV (Save file) (*.sav)|*.sav";
	cnv::unistr SOL 			= "SOL (Solo map) (*.sol)|*.sol";
	cnv::unistr PAL 			= "PAL (Index Palette) (*.pal)|*.pal";//8bit JASC palette file (*.pal)|*.pal
	cnv::unistr SHP 			= "SHP (Shape Sprite) (*.shp)|*.shp";
	cnv::unistr TGA 			= "TGA (Truevision - TARGA image) (*.tga)|*.tga";//8bit uncompressed TARGA image file (*.tga)|*.tga
	cnv::unistr BMP 			= "BMP (Bitmap Image) (*.bmp)|*.bmp";//8bit uncompressed Bitmap image file (*.bmp)|*.bmp

	#define cplr +"|"+
	//Choosing operating mode
	switch(Mode)
	{
//		case FM_ANY:            OpenDialog -> Filter = Any; break;
//		case FM_ALL_CHECKBOX:	OpenDialog -> Filter = All cplr Archives cplr Graphics cplr DPK cplr FST cplr MPK cplr PAK cplr PKK cplr SAV cplr SOL cplr PAL cplr SHP cplr TGA; break;
		case FM_ALL:			OpenDialog -> Filter = All cplr Archives cplr Graphics cplr DPK cplr FST cplr MPK cplr PAK cplr PKK cplr SAV cplr SOL cplr PAL cplr SHP cplr TGA; break;
		case FM_ARCHIVES:       OpenDialog -> Filter = Archives cplr DPK cplr FST cplr MPK cplr PAK cplr PKK cplr SAV cplr SOL; break;
//		case FM_GRAPHICS:		OpenDialog -> Filter = Graphics cplr PAL cplr SHP cplr TGA; break;
		case FM_DPK:			OpenDialog -> Filter = DPK; break;
		case FM_FST:			OpenDialog -> Filter = FST; break;
		case FM_MPK:			OpenDialog -> Filter = MPK; break;
		case FM_PAK:			OpenDialog -> Filter = PAK; break;
		case FM_PKK:			OpenDialog -> Filter = PKK; break;
		case FM_SAV:			OpenDialog -> Filter = SAV; break;
		case FM_SOL:			OpenDialog -> Filter = SOL; break;
//		case FM_PAL:			OpenDialog -> Filter = PAL; break;
//		case FM_SHP:			OpenDialog -> Filter = SHP; break;
//		case FM_TGA:			OpenDialog -> Filter = TGA; break;
//		case FM_BMP:			OpenDialog -> Filter = BMP; break;
 	}
	#undef cplr

	//Getting the application path
	cnv::unistr InitialDirString = chf::GetExecutableDirectory();

	//Opens "Open File" dialog box for processing
	OpenDialog -> FileName = "";
	OpenDialog -> InitialDir = InitialDirString;
	OpenDialog -> Execute();

	//Checking for the existence of the string
	if(OpenDialog -> FileName.Length() > 0)
	{
		OpenedFileName = OpenDialog -> FileName;
		return true;
	}
	else
	{
        return false;
	}
}
/// \brief Opening file
void __fastcall TFormMain::OpenFile()
{
	if(ForceOpen)
	{
		if(GetOpenDialog(FM_ALL_CHECKBOX))
		{
			RunProcess(GetFileTypeFromExt(GetExtFromPath(USTRINGtoSTRING(OpenedFileName))));
		}
	}
	else
	{
		FormFileSelection -> ShowModal();
		if(FileTypeFromSelection != 0)
		{
			if(GetOpenDialog(FileTypeFromSelection))
			{
				if(FileTypeFromSelection >= FM_DPK && FileTypeFromSelection < FM_UNKNOWN)// FM_DPK = 10 - It is a border
				{
					RunProcess(FileTypeFromSelection);
				}
				else
				{
					RunProcess(GetFileTypeFromExt(GetExtFromPath(USTRINGtoSTRING(OpenedFileName))));
				}
			}
		}
	}
}
/// \brief Closing file
void __fastcall TFormMain::CloseFile()
{
	ToolButton__SepMain -> Visible = false;
	ToolButton_ExtractSingle -> Visible = false;
	ToolButton_Unpack -> Visible = false;
	ToolButton_GetListStruct -> Visible = false;
	ToolButton_CombinedExtractionMode -> Visible = false;
	ToolButton_CloseFile -> Enabled = false;
	mm_Close -> Enabled = false;
    mm_Processes -> Enabled = false;
	ListView -> Clear();
	SetFormCaption();
	RichClear();
	FileType = 0;
}
/// \brief Run process depending on file type
/// \param [in] FileTypeInput Input FileType for function
/// \return Error code: 0 - no errors, 1 - operation error
int __fastcall TFormMain::RunProcess(cnv::unsint FileTypeInput)
{
	CloseFile();
	FileType = FileTypeInput;
	switch(FileTypeInput)
	{
        case FM_DPK:
			FstUObject.Load(USTRINGtoCHAR(OpenedFileName));
		break;
		case FM_FST:
			FstUObject.Load(USTRINGtoCHAR(OpenedFileName));
		break;
		case FM_MPK:
			SolUObject.Load(USTRINGtoCHAR(OpenedFileName));
		break;
		case FM_PAK:
			PakUObject.Load(USTRINGtoCHAR(OpenedFileName));
		break;
		case FM_PKK:
			SolUObject.Load(USTRINGtoCHAR(OpenedFileName));
		break;
		case FM_SAV:
			SolUObject.Load(USTRINGtoCHAR(OpenedFileName));
		break;
		case FM_SOL:
			SolUObject.Load(USTRINGtoCHAR(OpenedFileName));
		break;
		default:
			SendAlert(1, OpenedFileName);//Unprocessable file type. Metal Dealer does not process this file type.
			return 1;
	}
	ToolButton__SepMain -> Visible = true;
	ToolButton_ExtractSingle -> Visible = true;
	ToolButton_Unpack -> Visible = true;
	ToolButton_GetListStruct -> Visible = true;
	ToolButton_CombinedExtractionMode -> Visible = true;
	ToolButton_CloseFile -> Enabled = true;
	mm_Close -> Enabled = true;
	mm_Processes -> Enabled = true;
	SetFormCaption(OpenedFileName);
	ListViewFill();
	return 0;
}
/// \brief Viewing the characteristics of an open archive in the TextView
void __fastcall TFormMain::RichViewIndex()
{
	if(FileType != FM_NOTYPE)
	{
		RichClear();
		RichWrite("Archive file   : " + OpenedFileName);
		cnv::unsint EntryIndex = static_cast<cnv::unsint>(ListView -> ItemIndex);
		if(FileType == FM_FST || FileType == FM_DPK)
		{
			RichWrite("Amount of files: ", FstUObject.GetAmountEntries());
			RichWrite("File size      : ", FstUObject.GetFileSize());
			RichWrite("Index of file  : ", ListView -> ItemIndex);
			RichWrite("Offset of file : ", FstUObject.GetDataOffset(EntryIndex));
				 if(FstUObject.GetCompressFlag(EntryIndex) == CF_UNCOMPRESS)
				RichWrite("Compress flag  : Uncompress");
			else if(FstUObject.GetCompressFlag(EntryIndex) == CF_COMPRESS)
				RichWrite("Compress flag  : Compress");
			else if(FstUObject.GetCompressFlag(EntryIndex) == CF_EMPTY)
				RichWrite("Compress flag  : Empty");
			RichWrite("File in archive: " + STRINGtoUSTRING(FstUObject.GetPath(EntryIndex)));
			if(FstUObject.GetCompressFlag(EntryIndex) == CF_EMPTY)
				RichWrite("Uncompress size: -");
			else
				RichWrite("Uncompress size: ", FstUObject.GetUncompressSize(EntryIndex));
			if(FstUObject.GetCompressFlag(EntryIndex) == CF_EMPTY || FstUObject.GetCompressFlag(EntryIndex) == CF_UNCOMPRESS)
				RichWrite("Compress size  : -");
			else
				RichWrite("Compress size  : ", FstUObject.GetCompressSize(EntryIndex));
		}
		else if(FileType == FM_SOL || FileType == FM_SAV || FileType == FM_MPK || FileType == FM_PKK)
		{
			RichWrite("Amount of files: ", SolUObject.GetAmountEntries());
			RichWrite("File size      : ", SolUObject.GetFileSize());
			RichWrite("File checksum  : ", SolUObject.GetCheckSum());
			RichWrite("Start offset   : ", SolUObject.GetDataStartOffset());
			RichWrite("Index of file  : ", ListView -> ItemIndex);
			RichWrite("Offset of file : ", SolUObject.GetDataOffset(EntryIndex));
				 if(SolUObject.GetCompressFlag(EntryIndex) == CF_UNCOMPRESS)
				RichWrite("Compress flag  : Uncompress");
			else if(SolUObject.GetCompressFlag(EntryIndex) == CF_COMPRESS)
				RichWrite("Compress flag  : Compress");
			else if(SolUObject.GetCompressFlag(EntryIndex) == CF_EMPTY)
				RichWrite("Compress flag  : Empty");
			RichWrite("File extension : " + STRINGtoUSTRING(GetExtFromFileType(SolUObject.GetExtension(EntryIndex))));
			if(SolUObject.GetCompressFlag(EntryIndex) == CF_EMPTY)
				RichWrite("Uncompress size: -");
			else
				RichWrite("Uncompress size: ", SolUObject.GetUncompressSize(EntryIndex));
			if(SolUObject.GetCompressFlag(EntryIndex) == CF_EMPTY || SolUObject.GetCompressFlag(EntryIndex) == CF_UNCOMPRESS)
				RichWrite("Compress size  : -");
			else
				RichWrite("Compress size  : ", SolUObject.GetCompressSize(EntryIndex));
		}
		else if(FileType == FM_PAK)
		{
			RichWrite("Amount of files: ", PakUObject.GetAmountEntries());
			RichWrite("File size      : ", PakUObject.GetFileSize());
			RichWrite("Start offset   : ", PakUObject.GetDataStartOffset());
			RichWrite("Index of file  : ", ListView -> ItemIndex);
			RichWrite("Offset of file : ", PakUObject.GetDataOffset(EntryIndex));
				 if(PakUObject.GetCompressFlag(EntryIndex) == CF_UNCOMPRESS)
				RichWrite("Compress flag  : Uncompress");
			else if(PakUObject.GetCompressFlag(EntryIndex) == CF_COMPRESS)
				RichWrite("Compress flag  : Compress");
			else if(PakUObject.GetCompressFlag(EntryIndex) == CF_EMPTY)
				RichWrite("Compress flag  : Empty");
			RichWrite("File extension : " + STRINGtoUSTRING(GetExtFromFileType(PakUObject.GetExtension(EntryIndex))));
			if(PakUObject.GetCompressFlag(EntryIndex) == CF_EMPTY)
				RichWrite("Uncompress size: -");
			else
				RichWrite("Uncompress size: ", PakUObject.GetUncompressSize(EntryIndex));
			if(PakUObject.GetCompressFlag(EntryIndex) == CF_EMPTY || PakUObject.GetCompressFlag(EntryIndex) == CF_UNCOMPRESS)
				RichWrite("Compress size  : -");
			else
				RichWrite("Compress size  : ", PakUObject.GetCompressSize(EntryIndex));
		}
	}
	else
	{
		SendAlert(2, nullptr);//Archive is not open for viewing.
	}
}
