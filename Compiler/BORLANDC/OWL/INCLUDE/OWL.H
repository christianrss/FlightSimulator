// ObjectWindows - (C) Copyright 1991 by Borland International

#ifndef __OWL_H
#define __OWL_H

// ---------------------------------------------------
// This include file causes all the include files 
// necessary for basic owl functionality to be included. 
//----------------------------------------------------

#if defined(_CLASSDLL) || defined(__DLL__)
#  define _RTLDLL
#endif

#if !defined(__DEFS_H)
#include <_defs.h>
#endif

#if !defined(__APPLICAT_H)
#include <applicat.h>
#endif

#if !defined(NODLLREF)
#  if defined(_CLASSDLL)
      extern int DLLRef;
      static int DLLRefInternal = DLLRef;
#  endif
#endif

extern unsigned short far  _EXPFUNC OWLGetVersion();

const unsigned short OWLVersion = 0x0100; // Version 1.0

#endif
