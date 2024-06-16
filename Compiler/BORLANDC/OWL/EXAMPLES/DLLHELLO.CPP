// ObjectWindows - (C) Copyright 1991 by Borland International

#include <stdlib.h>
#include <owl.h>
#include "windows.h"
#include "dllhello.h"

PTModule DLLHelloLib;

BOOL far _export CreateDLLWindow(HWND ParentHWnd)
{
  PTWindowsObject AParentAlias;
  PTWindow TheWindow;

  AParentAlias = DLLHelloLib->GetParentObject(ParentHWnd);
  TheWindow = new TWindow(AParentAlias, "Hello from a DLL!", DLLHelloLib);
  TheWindow->Attr.Style |= WS_POPUPWINDOW | WS_CAPTION | WS_THICKFRAME
    | WS_MINIMIZEBOX | WS_MAXIMIZEBOX;
  TheWindow->Attr.X = 100; TheWindow->Attr.Y = 100;
  TheWindow->Attr.W = 300; TheWindow->Attr.H = 300;
  return (DLLHelloLib->MakeWindow(TheWindow) == TheWindow);
}

int FAR PASCAL LibMain(HANDLE hInstance, WORD /*wDataSeg*/,
  WORD /* cbHeapSize */, LPSTR lpCmdLine)
{
    int TheStatus;

    DLLHelloLib = new TModule("DLLHello", hInstance, lpCmdLine);
    TheStatus = DLLHelloLib->Status;
    if ( TheStatus != 0 )
    {
      delete DLLHelloLib;
      DLLHelloLib = NULL;
    }
    return (TheStatus == 0);
}

int FAR PASCAL WEP(int /*bSystemExit*/)
{
    if ( DLLHelloLib )
      delete DLLHelloLib;
    return 1;
}
