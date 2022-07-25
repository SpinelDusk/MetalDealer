/// \file
/// \brief Application initialization module
/// \author SpinelDusk
/// \details Lead application module

#pragma GCC diagnostic ignored "-Wunused-parameter"				//Disable warning: Parameter is never used

#include <vcl.h>
#include <tchar.h>
#include <Vcl.Styles.hpp>
#include <Vcl.Themes.hpp>
#pragma hdrstop//This directive terminates the list of header files eligible for precompilation (Using ONLY for <standard> headers, no "custom")

USEFORM("Form_Main.cpp", FormMain)
USEFORM("Form_FileSelection.cpp", FormFileSelection)
USEFORM("Form_ErrorDisplay.cpp", FormErrorDisplay)
USEFORM("Form_About.cpp", FormAbout)

/// \brief The user-provided entry point for a graphical Windows-based application
/// \param[in] hInstance A handle to the current instance of the application
/// \param[in] hPrevInstance A handle to the previous instance of the application
/// \param[in] lpCmdLine The command line for the application, excluding the program name
/// \param[in] nShowCmd Controls how the window is to be shown
/// \return Terminating value
int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nShowCmd)
{
  	try
	{
		Application->Initialize();
		Application->MainFormOnTaskBar = true;
		Application->CreateForm(__classid(TFormMain), &FormMain);
		Application->CreateForm(__classid(TFormFileSelection), &FormFileSelection);
		Application->CreateForm(__classid(TFormErrorDisplay), &FormErrorDisplay);
		Application->CreateForm(__classid(TFormAbout), &FormAbout);
		Application->Run();
	}
	catch (Exception &exception)
	{
		Application->ShowException(&exception);
	}
	catch (...)
	{
		try
		{
			throw Exception("");
		}
		catch (Exception &exception)
		{
			Application->ShowException(&exception);
		}
	}
	return 0;
}
