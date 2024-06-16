// ObjectWindows - (C) Copyright 1991 by Borland International

#include <owl.h>
#include "colordlg.h"
#include "cdlgdll.h"

PTModule TheModule;

BOOL far _export GetColor(HWND ParentHandle, COLORREF _FAR & ColorBuffer)
{
  PTWindowsObject AParentAlias;
  TColorDialog *TheColorDialog;

  AParentAlias = TheModule->GetParentObject(ParentHandle);
  TheColorDialog= new TColorDialog (AParentAlias, ColorBuffer);
  return (TheModule->ExecDialog(TheColorDialog) == IDOK);
}

int FAR PASCAL LibMain(HANDLE hInstance, WORD /*wDataSeg*/,
  WORD /* cbHeapSize */, LPSTR lpCmdLine)
{
  int TheStatus;

  TheModule = new TModule("CDLGDLL", hInstance, lpCmdLine);
  TheStatus = TheModule->Status;
  if ( TheStatus != 0 )
  {
    delete TheModule;
    TheModule = NULL;
  }
  return (TheStatus == 0);
}

int FAR PASCAL WEP(int /*bSystemExit*/)
{
  if ( TheModule )
    delete TheModule;
  return 1;
}
