// ObjectWindows - (C) Copyright 1991 by Borland International
  
#include <owl.h>
#include <string.h>

class TTestApp : public TApplication
{
public:
  TTestApp(LPSTR AName, HANDLE hInstance, HANDLE hPrevInstance,
    LPSTR lpCmdLine, int nCmdShow);

protected:
  char WindowTitle[20];
  virtual void InitMainWindow();
  virtual void InitApplication();
};

TTestApp::TTestApp(LPSTR AName, HANDLE hInstance, HANDLE hPrevInstance,
  LPSTR lpCmdLine, int nCmdShow)
  : TApplication(AName, hInstance, hPrevInstance, lpCmdLine, nCmdShow)
{
  strcpy(WindowTitle, "Additional Instance");
}

void TTestApp::InitApplication()
{
  strcpy(WindowTitle, "First Instance");
}

void TTestApp::InitMainWindow()
{
  MainWindow = new TWindow(NULL, WindowTitle);
}
 
int PASCAL WinMain(HANDLE hInstance, HANDLE hPrevInstance,
  LPSTR lpCmdLine, int nCmdShow)          
{
  TTestApp TestApp("Instance Tester", hInstance, hPrevInstance,
    lpCmdLine, nCmdShow);
  TestApp.Run();
  return TestApp.Status;
}
