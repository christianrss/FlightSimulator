// ObjectWindows - (C) Copyright 1991 by Borland International

#include <owl.h>

class TMyApp : public TApplication
{
public:
  TMyApp(LPSTR AName, HANDLE hInstance, HANDLE hPrevInstance,
    LPSTR lpCmdLine, int nCmdShow)
    : TApplication(AName, hInstance, hPrevInstance, lpCmdLine, nCmdShow) {};
  virtual void InitMainWindow();
};

void TMyApp::InitMainWindow()
{
  MainWindow = new TWindow(NULL, Name);
}

int PASCAL WinMain(HANDLE hInstance, HANDLE hPrevInstance,
  LPSTR lpCmdLine, int nCmdShow)
{
  TMyApp MyApp("Sample ObjectWindows Program", hInstance, hPrevInstance,
               lpCmdLine, nCmdShow);
  MyApp.Run();
  return MyApp.Status;
}
