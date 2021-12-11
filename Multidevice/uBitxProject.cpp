// ---------------------------------------------------------------------------

#include <fmx.h>
#ifdef _WIN32
#include <tchar.h>
#endif
#pragma hdrstop
#include <System.StartUpCopy.hpp>
// ---------------------------------------------------------------------------
USEFORM("UuBitx02.cpp", Frame2); /* TFrame: File Type */
USEFORM("UuBitx01.cpp", F1);

// ---------------------------------------------------------------------------
extern "C" int FMXmain() {
	try {
		Application->Initialize();
		Application->CreateForm(__classid(TF1), &F1);
		Application->Run();
	}
	catch (Exception &exception) {
		Application->ShowException(&exception);
	}
	catch (...) {
		try {
			throw Exception("");
		}
		catch (Exception &exception) {
			Application->ShowException(&exception);
		}
	}
	return 0;
}
// ---------------------------------------------------------------------------
