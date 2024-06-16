// ObjectWindows - (C) Copyright 1991 by Borland International

#ifndef __CONTROL_H
#define __CONTROL_H

#ifndef __APPLICAT_H
#include <applicat.h>
#endif

  /* TControl */

_CLASSDEF(TControl)

class _EXPORT TControl : public TWindow {
public:
    TControl(PTWindowsObject AParent, int AnId, LPSTR ATitle, int X,
             int Y, int W, int H, PTModule AModule = NULL);
    TControl(PTWindowsObject AParent, int ResourceId, 
	     PTModule AModule = NULL);
    virtual int GetId()
        { return Attr.Id; }

protected:
    TControl(StreamableInit) : TWindow(streamableInit) {};

    virtual void WMPaint(RTMessage Msg) = [WM_FIRST + WM_PAINT];
    virtual void WMDrawItem(RTMessage Msg) = [WM_FIRST + WM_DRAWITEM];
    virtual void ODADrawEntire(DRAWITEMSTRUCT _FAR & DrawInfo);
    virtual void ODAFocus(DRAWITEMSTRUCT _FAR & DrawInfo);
    virtual void ODASelect(DRAWITEMSTRUCT _FAR & DrawInfo);
};

#endif
