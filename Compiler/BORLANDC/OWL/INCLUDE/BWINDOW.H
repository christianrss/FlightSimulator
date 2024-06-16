// ObjectWindows - (C) Copyright 1991 by Borland International

#ifndef __BWINDOW_H
#define __BWINDOW_H

// BWINDOW.H
// Defines type TBWindow, a BWCC friendly derivation of TWindow.
//

#ifndef __WINDOW_H
#include <window.h>
#endif

_CLASSDEF(TBWindow)

/* TBWindow */

class _EXPORT TBWindow : public TWindow
{
public:
    TBWindow(PTWindowsObject AParent, LPSTR AName, 
	     PTModule AModule = NULL);

    static PTStreamable build();

protected:
    virtual LPSTR GetClassName()
	    {return "TBWindow";}
    virtual void GetWindowClass(WNDCLASS _FAR & AWndClass);

    TBWindow(StreamableInit) : TWindow(streamableInit) {};
    
private:
    virtual const Pchar streamableName() const
        { return "TBWindow"; }
};

inline Ripstream operator >> ( Ripstream is, RTBWindow cl )
    { return is >> (RTStreamable)cl; }
inline Ripstream operator >> ( Ripstream is, RPTBWindow cl )
    { return is >> (RPvoid)cl; }

inline Ropstream operator << ( Ropstream os, RTBWindow cl )
    { return os << (RTStreamable)cl; }
inline Ropstream operator << ( Ropstream os, PTBWindow cl )
    { return os << (PTStreamable)cl; }

#endif
