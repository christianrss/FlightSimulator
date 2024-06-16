// ObjectWindows - (C) Copyright 1991 by Borland International

#ifndef __MODULE_H
#define __MODULE_H

#ifndef __OBJECT_H
#include <object.h>
#endif

#ifndef __WINDOWS_H
#undef NULL
#include <windows.h>
#endif

#ifndef __OWLDEFS_H
#include <owldefs.h>
#endif

#ifndef __WINDOW_H
#include <window.h>
#endif

#ifndef __MDI_H
#include <mdi.h>
#endif

#ifndef __DIALOG_H
#include <dialog.h>
#endif

_CLASSDEF(TModule)

// Module Class 

class _EXPORT TModule : public Object {
public:

    // Lib and WinMain args
    HANDLE		hInstance;
    LPSTR		lpCmdLine;

    int Status;
    LPSTR Name;

    TModule(LPSTR AName, HANDLE AnInstance, LPSTR ACmdLine);
    virtual ~TModule();

    BOOL LowMemory();
    void RestoreMemory();
    virtual PTWindowsObject ValidWindow(PTWindowsObject AWindowsObject);
    virtual PTWindowsObject MakeWindow(PTWindowsObject AWindowsObject);
    virtual int ExecDialog(PTWindowsObject ADialog);
    HWND GetClientHandle(HWND AnHWindow);
    virtual PTWindowsObject GetParentObject(HWND ParentHandle);
    virtual void Error(int ErrorCode);

    // define pure virtual functions derived from Object class
    virtual classType  	  isA() const
	    { return moduleClass; }
    virtual Pchar nameOf() const
	    { return "TModule"; }
    virtual hashValueType hashValue() const
	    {  return hashValueType(hInstance); }
    virtual int 	  isEqual(RCObject module)  const
            { return (hInstance == ((RTModule)module).hInstance); }
    virtual void	  printOn(Rostream outputStream) const
            { outputStream << nameOf() << "{ hInstance = " 
              << hInstance << " }\n"; }
};	// end of Module class  

extern PTModule Module;

#endif // ifndef __MODULE_H
