// ObjectWindows - (C) Copyright 1991 by Borland International

#include <owl.h>
#include <mdi.h>

#if defined(wsprintf)
#undef wsprintf
#define wsprintf wsprintf		// reverse windows.h
extern "C" int FAR cdecl wsprintf(LPSTR,LPSTR,...);
#endif

// Define a TApplication descendant 
class TMDIApp : public TApplication {
public:
    TMDIApp(LPSTR name, HANDLE hInstance, 
		  HANDLE hPrevInstance, LPSTR lpCmd,
		  int nCmdShow)
	        : TApplication(name, hInstance, 
			       hPrevInstance, lpCmd, nCmdShow) {};
    virtual void InitMainWindow();
};

// Define a TMDIFrame descendant
class TMyMDIFrame : public TMDIFrame {
public:
  WORD ChildNum;

  TMyMDIFrame(LPSTR ATitle, LPSTR MenuName);
  virtual PTWindowsObject InitChild();
};
 
// Construct the TMDIApp's MainWindow object, loading its menu 
void TMDIApp::InitMainWindow()
{
  MainWindow = new TMyMDIFrame("MDI Conformist", "MDIMenu");
}

TMyMDIFrame::TMyMDIFrame(LPSTR ATitle, LPSTR MenuName)
             : TMDIFrame(ATitle, MenuName)
{
  ChildNum = 1;
}

PTWindowsObject TMyMDIFrame::InitChild()
{
  char ChildName[14];

  wsprintf(ChildName,"MDI Child %d", ChildNum++);
  return new TWindow(this, ChildName);
}

// Run the MDIApp
int PASCAL WinMain(HANDLE hInstance, HANDLE hPrevInstance,
		   LPSTR lpCmd, int nCmdShow)
{
    TMDIApp MDIApp ("MDIApp", hInstance, hPrevInstance,
		lpCmd, nCmdShow);
    MDIApp.Run();
    return (MDIApp.Status);
}
