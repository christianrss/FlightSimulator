// ObjectWindows - (C) Copyright 1991 by Borland International

/* ---------------------------------------------------------
   MODULE.CPP
   Implementation for the TModule class.  TModule defines the
   basic behavior for OWL libraries and applications.
   --------------------------------------------------------- */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <alloc.h>
#include <applicat.h>
#include <mdi.h>
#include <dict.h>
#include <assoc.h>
#include <safepool.h>

#if defined(wsprintf)
#undef wsprintf
#define wsprintf wsprintf		// reverse windows.h
extern "C" int FAR cdecl wsprintf(LPSTR,LPSTR,...);
#endif

PTModule Module = (PTModule)NULL;
extern long FAR PASCAL _export StdWndProc(HWND, WORD, WORD, LONG);
extern FARPROC StdWndProcInstance;
extern PTWindowsObject GetObjectPtr(HWND);

/* Constructor for a TModule object. */
TModule::TModule(LPSTR AName, HANDLE AnInstance, LPSTR ACmdLine)
{
  Status = 0;
  Name = AName;
  hInstance = AnInstance;
  lpCmdLine = _fstrdup(ACmdLine? ACmdLine: "");
  if ( !Module )  // our Module global is for the OWL-DLL
    Module = this;

  if ( !StdWndProcInstance )
    StdWndProcInstance = MakeProcInstance((FARPROC)StdWndProc, hInstance);
  if ( !StdWndProcInstance )
    Status = EM_INVALIDMODULE;
}

TModule::~TModule()
{
  if ( HIWORD(lpCmdLine) )
    farfree(lpCmdLine);
  if ( this == Module ) // our Module global is for the OWL-DLL
    FreeProcInstance(StdWndProcInstance);
}

/* check if safety pool has been dipped into */
BOOL TModule::LowMemory()
{
  return SafetyPool::IsExhausted();
}

/* Restores memory to the safety pool. */
void TModule::RestoreMemory()
{
  if ( LowMemory() )
    SafetyPool::Allocate();
}

/* Determines whether or not the passed TWindowsObject can be considered
   valid.  Returns a pointer to the TWindowsObject if valid. If invalid,
   calls Error and disposes of the TWindowsObject, returning  NULL.  A
   TWindowsObject is considered invalid if a low memory condition exists
   or if the TWindowsObject has a non-zero status. */
PTWindowsObject TModule::ValidWindow(PTWindowsObject AWindowsObject)
{
  if ( AWindowsObject )
  {
    if ( LowMemory() )
    {
      Error(EM_OUTOFMEMORY);
      delete AWindowsObject;
      RestoreMemory();
    }
    else 
      if ( AWindowsObject->Status != 0 )
      {
        Error(AWindowsObject->Status);
        delete AWindowsObject;
      }
      else 
        return AWindowsObject;
  }
  return NULL;
}

/* Attempts to create a TWindowsObject, after performing checks of 
   safety pool usage (and subsequent cleanup in low memory conditions).  
   If a valid TWindowsObject could not be created, calls Error,
   disposes of the TWindowsObject and returns a NULL pointer. */
PTWindowsObject TModule::MakeWindow(PTWindowsObject AWindowsObject)
{
  if ( AWindowsObject && ValidWindow(AWindowsObject) )
    if ( (AWindowsObject->Create()) )
      return AWindowsObject;
    else
    {
      Error(AWindowsObject->Status);
      AWindowsObject->ShutDownWindow();
    }
  return NULL;
}

/* Attempts to execute the supplied TDialog, if the TDialog is valid.
  If valid (the call to ValidWindow returns TRUE), calls Execute, and, 
  if a valid dialog could not be created, disposes of the TDialog.  
  Calls Error if Execute results in a non-zero Status.  Returns the 
  result of the call to Execute (or IDCANCEL if not called). */
int TModule::ExecDialog(PTWindowsObject ADialog)
{
  int ReturnValue;

  if ( ValidWindow(ADialog) )
  {
    ReturnValue = ((PTDialog)ADialog)->Execute();
    if ( ReturnValue < 0 )
    {
      Error(ADialog->Status);
      delete ADialog;
    }
    return ReturnValue;
  }
  return IDCANCEL;
}

HWND TModule::GetClientHandle(HWND AnHWindow)
{
  HWND CurWindow;
  char ClassName[10];

  if ( AnHWindow )
  {
    if ( 0 != (CurWindow = GetWindow(AnHWindow, GW_CHILD)) )
    {
      do {
        GetClassName(CurWindow, ClassName, sizeof ClassName); 
        if ( _fstrnicmp(ClassName, "MDICLIENT", 10) == 0 )
          return CurWindow;
      } while ( 0 != (CurWindow = GetWindow(CurWindow, GW_HWNDNEXT)) );
    }
  }
  return 0;
}
PTWindowsObject TModule::GetParentObject(HWND ParentHandle)
{
  PTWindowsObject AWindowsObject;
  HWND ClientHandle;

  if ( NULL != (AWindowsObject = GetObjectPtr(ParentHandle)) )
    return AWindowsObject;
  else
    if ( 0 != (ClientHandle = GetClientHandle(ParentHandle)) )
      return (PTWindowsObject)(new TMDIFrame(ParentHandle, ClientHandle,
                  this));
    else
      return (PTWindowsObject)(new TWindow(ParentHandle, this));
} 

/* Simple error handler; may be redefined to process errors. */
void TModule::Error(int ErrorCode)
{
  char ErrorString[51];
  PTModule TmpModule;

  wsprintf(ErrorString, "Error received: error code = %d\nOK to proceed ?", 
          ErrorCode);
  TmpModule = GetApplicationObject();
  if ( MessageBox(0, ErrorString,
                  TmpModule ? TmpModule->Name : Name,
                  MB_ICONSTOP | MB_YESNO) == IDNO )
    PostAppMessage(GetCurrentTask(), WM_QUIT, 0, 0);
} 

#ifdef __DLL__
int FAR PASCAL LibMain(HANDLE hInstance, WORD /*wDataSeg*/ , 
	           WORD cbHeapSize , LPSTR lpCmdLine )
{
    new TModule("ObjectWindows DLL", hInstance, lpCmdLine);

    if ( cbHeapSize > 0 )
      UnlockData(0);
    return Module->Status == 0;
}

int FAR PASCAL WEP ( int /*bSystemExit*/ )
{
    delete Module;

    return 1;
}
#endif
