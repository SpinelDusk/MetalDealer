/// \file
/// \brief Form - Main (SECTION - Misc Graphic Interface Components)
/// \author SpinelDusk
/// \details Processes all items of the interface elements 'ToolButton', 'StatusBar', 'ListView'

#pragma GCC diagnostic ignored "-Wc++98-compat"					//Disable warning: 'nullptr' is incompatible with C++98
#pragma GCC diagnostic ignored "-Wunused-parameter"				//Disable warning: Parameter is never used

#pragma package(smart_init)

#include "Form_MainMgic.h"

/// \brief Enumeration of color entry markers
enum ColorPoint
{
	CP_RED = 0,			///< Corrupted entry
	CP_BLUE = 1,		///< Compress entry 
	CP_GREEN = 2,   	///< Uncompress entry
	CP_GRAY = 3     	///< Empty entry (no size entry)
};

extern cnv::unsint FileType;		///< Defined in Form_MainGH.cpp
extern cnv::unistr OpenedFileName;	///< Defined in Form_MainGH.cpp

extern SolUnpack SolUObject;		///< Defined in Form_Main.cpp
extern PakUnpack PakUObject;		///< Defined in Form_Main.cpp
extern FstUnpack FstUObject;		///< Defined in Form_Main.cpp

/// \brief Displaying message in StatusBar
/// \param[in] local_Input Message displayed in Status Bar of the program
void __fastcall TFormMain::StatusBarText(cnv::unistr local_Input)
{
	StatusBar -> Font -> Color = clBtnText;
	StatusBar -> SimpleText = local_Input;
	Timer_StatusBar -> Enabled = true;
}
/// \brief Cleaning StatusBar
void __fastcall TFormMain::StatusBarClear()
{
	StatusBar -> SimpleText = "";
}
/// \brief Cleaning Statusbar on timer response
/// \param[in] Sender Pointer to the TObject Class Component that called this function
void __fastcall TFormMain::Timer_StatusBarTimer(TObject *Sender)
{
	StatusBarClear();
	Timer_StatusBar -> Enabled = false;
}
/// \brief Extract a single file from the archive
/// \param[in] Sender Pointer to the TObject Class Component that called this function
void __fastcall TFormMain::ToolButton_ExtractSingleClick(TObject *Sender)
{
	if(ListView -> SelCount == 1)
	{
		if(FileType == FM_FST || FileType == FM_DPK)
		{
			FstUObject.ExtractFromArchive(static_cast<cnv::unsint>(ListView -> ItemIndex));
		}
		else if(FileType == FM_SOL || FileType == FM_SAV || FileType == FM_MPK || FileType == FM_PKK)
		{
			SolUObject.ExtractFromArchive(static_cast<cnv::unsint>(ListView -> ItemIndex));
		}
		else if(FileType == FM_PAK)
		{
			PakUObject.ExtractFromArchive(static_cast<cnv::unsint>(ListView -> ItemIndex));
		}
	}
}
/// \brief Unpacking an archive
/// \param[in] Sender Pointer to the TObject Class Component that called this function
void __fastcall TFormMain::ToolButton_UnpackClick(TObject *Sender)
{
	if(FileType == FM_FST || FileType == FM_DPK)
	{
		FstUObject.UnpackEntireArchive();
	}
	else if(FileType == FM_SOL || FileType == FM_SAV || FileType == FM_MPK || FileType == FM_PKK)
	{
		SolUObject.UnpackEntireArchive();
	}
	else if(FileType == FM_PAK)
	{
		PakUObject.UnpackEntireArchive();
	}
}
/// \brief Save archive file list
/// \param[in] Sender Pointer to the TObject Class Component that called this function
void __fastcall TFormMain::ToolButton_GetListStructClick(TObject *Sender)
{
	if(FileType == FM_FST || FileType == FM_DPK)
	{
		FstUObject.CreateListFile();
	}
	else if(FileType == FM_SOL || FileType == FM_SAV || FileType == FM_MPK || FileType == FM_PKK)
	{
		SolUObject.CreateListFile();
	}
	else if(FileType == FM_PAK)
	{
		PakUObject.CreateListFile();
	}
}
/// \brief Combined mode (unpacking the archive and creating list of archive files)
/// \param[in] Sender Pointer to the TObject Class Component that called this function
void __fastcall TFormMain::ToolButton_CombinedExtractionModeClick(TObject *Sender)
{
	if(FileType == FM_FST || FileType == FM_DPK)
	{
		FstUObject.UnpackEntireArchive();
		FstUObject.CreateListFile();
	}
	else if(FileType == FM_SOL || FileType == FM_SAV || FileType == FM_MPK || FileType == FM_PKK)
	{
		SolUObject.UnpackEntireArchive();
		SolUObject.CreateListFile();
	}
	else if(FileType == FM_PAK)
	{
		PakUObject.UnpackEntireArchive();
		PakUObject.CreateListFile();
	}
}
/// \brief Response to clicking a line in the list
/// \param[in] Sender Pointer to the TObject Class Component that called this function
void __fastcall TFormMain::ListViewClick(TObject *Sender)
{
	if(ListView -> SelCount == 1)
	{
		RichViewIndex();
	}
}
/// \brief Display the list of file contents in ListView (if the archive has been preloaded into program memory)
void __fastcall TFormMain::ListViewFill()
{
	ListView -> Clear();
	if(FileType == FM_FST || FileType == FM_DPK)
	{
		for(cnv::dword i = 0; i < FstUObject.GetAmountEntries(); i++)
		{
			ListItem = ListView -> Items -> Add();
			ListItem -> Caption = i;
			ListItem -> SubItems -> Add(STRINGtoUSTRING(FstUObject.GetPath(i)));
			if(FstUObject.GetCompressFlag(i) == CF_UNCOMPRESS)
			{
				ListItem -> SubItems -> Add("Uncompressed");
				ListItem -> SubItems -> Add(FstUObject.GetUncompressSize(i));
				ListItem -> SubItems -> Add("-");
				ListItem -> ImageIndex = CP_BLUE;
			}
			else if(FstUObject.GetCompressFlag(i) == CF_COMPRESS)
			{
				ListItem -> SubItems -> Add("Compressed");
				ListItem -> SubItems -> Add(FstUObject.GetUncompressSize(i));
				ListItem -> SubItems -> Add(FstUObject.GetCompressSize(i));
				ListItem -> ImageIndex = CP_GREEN;
			}
			else if(FstUObject.GetCompressFlag(i) == CF_EMPTY)
			{
				ListItem -> SubItems -> Add("Empty");
				ListItem -> SubItems -> Add("-");
				ListItem -> SubItems -> Add("-");
				ListItem -> ImageIndex = CP_GRAY;
			}			
			ListItem -> SubItems -> Add(FstUObject.GetDataOffset(i));
		}
	}
	else if(FileType == FM_SOL || FileType == FM_SAV || FileType == FM_MPK || FileType == FM_PKK)
	{
		for(cnv::dword i = 0; i < SolUObject.GetAmountEntries(); i++)
		{
			cnv::unistr EntryName = chf::GetFileName(OpenedFileName) + "_" + i + "." + STRINGtoUSTRING(GetExtFromFileType(SolUObject.GetExtension(i)));

			ListItem = ListView -> Items -> Add();
			ListItem -> Caption = i;
			ListItem -> SubItems -> Add(EntryName);
			if(SolUObject.GetCompressFlag(i) == CF_UNCOMPRESS)
			{
				ListItem -> SubItems -> Add("Uncompressed");
				ListItem -> SubItems -> Add(SolUObject.GetUncompressSize(i));
				ListItem -> SubItems -> Add("-");
				ListItem -> ImageIndex = CP_BLUE;
			}
			else
			{
				ListItem -> SubItems -> Add("Compressed");
				ListItem -> SubItems -> Add(SolUObject.GetUncompressSize(i));
				ListItem -> SubItems -> Add(SolUObject.GetCompressSize(i));
				ListItem -> ImageIndex = CP_GREEN;
			}
			ListItem -> SubItems -> Add(SolUObject.GetDataOffset(i));
		}
	}
	else if(FileType == FM_PAK)
	{
		for(cnv::dword i = 0; i < PakUObject.GetAmountEntries(); i++)
		{
			cnv::unistr EntryName = chf::GetFileName(OpenedFileName) + "_" + i + "." + STRINGtoUSTRING(GetExtFromFileType(PakUObject.GetExtension(i)));

			ListItem = ListView -> Items -> Add();
			ListItem -> Caption = i;
			ListItem -> SubItems -> Add(EntryName);
			if(PakUObject.GetCompressFlag(i) == CF_UNCOMPRESS)
			{
				ListItem -> SubItems -> Add("Uncompressed");
				ListItem -> SubItems -> Add(PakUObject.GetUncompressSize(i));
				ListItem -> SubItems -> Add("-");
				ListItem -> ImageIndex = CP_BLUE;
			}
			else if(PakUObject.GetCompressFlag(i) == CF_COMPRESS)
			{
				ListItem -> SubItems -> Add("Compressed");
				ListItem -> SubItems -> Add(PakUObject.GetUncompressSize(i));
				ListItem -> SubItems -> Add(PakUObject.GetCompressSize(i));
				ListItem -> ImageIndex = CP_GREEN;
			}
			else if(PakUObject.GetCompressFlag(i) == CF_EMPTY)
			{
				ListItem -> SubItems -> Add("Empty");
				ListItem -> SubItems -> Add("-");
				ListItem -> SubItems -> Add("-");
				ListItem -> ImageIndex = CP_GRAY;
			}			
			ListItem -> SubItems -> Add(PakUObject.GetDataOffset(i));
		}
	}
}
/// \brief Pressing the cursor key handler
/// \param[in] Sender Pointer to the TObject Class Component that called this function
/// \param[in] Key Reference to the WORD variable that contains code of a pressed key
/// \param[in] Shift Pointer to the TShiftState Class Component that indicates the state of the modifier keys, the mouse buttons, or the touch devices
void __fastcall TFormMain::ListViewKeyUp(TObject *Sender, WORD &Key, TShiftState Shift)
{
	ListViewClick(nullptr);
}
