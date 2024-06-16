// Borland C++ - (C) Copyright 1991 by Borland International

#if !defined( __STDLIB_H )
#include <stdlib.h>
#endif  // __STDLIB_H

#if !defined( __STRING_H )
#include <string.h>
#endif  // __STRING_H

#if !defined( __ERREXIT_H )
#include <errexit.h>
#endif  // __ERREXIT_H

#if defined(_Windows)
#  if !defined( __WINDOWS_H )
#  include <windows.h>
#  endif  // __WINDOWS_H
#else
#  if !defined( __IOSTREAM_H )
#  include <iostream.h>
#  endif  // __IOSTREAM_H
#endif

#if defined(_Windows)
  extern char *_Cdecl _argv0;
  extern HWND _hInstance;
#endif

void ClasslibError( char *msg )
{
#if defined(_Windows)
    char *progName = strrchr( _argv0, '\\' );
    if( progName == NULL )
        progName = _argv0;
    else
        progName++;     // skip backslash in front of name

    MessageBox( _hInstance, msg, progName, MB_ICONHAND | MB_SYSTEMMODAL );
#else
    cerr << msg;
#endif
}

void ClasslibErrorExit (char *msg, int code)
{
    ClasslibError(msg);
    _exit(code);
}
