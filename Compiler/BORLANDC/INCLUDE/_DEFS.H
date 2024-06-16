/*  _defs.h

    Common definitions for pointer size and calling conventions.

    Copyright (c) Borland International 1991
    All Rights Reserved.
*/

#if !defined( __DEFS_H )
#define __DEFS_H

#if __STDC__
#  define _Cdecl
#else
#  ifdef __OS2__
#    define _Cdecl  _stdcall
#  else
#    define _Cdecl  cdecl
#  endif
#endif

#ifndef __PAS__
#  define _CType _Cdecl
#else
#  define _CType pascal
#endif

#ifdef __OS2__
#  define _FAR
#  define _FARFUNC
#  define _CLASSTYPE
#else
#  if   defined(__DLL__)
#    define _CLASSTYPE _export
#    define _FAR far
#    if defined(_BUILDRTLDLL)
#      define _FARFUNC _export
#    else
#      define _FARFUNC far
#    endif
#  elif defined(_CLASSDLL) || defined(_RTLDLL)
#    define _CLASSTYPE huge
#    define _FARFUNC far
#    define _FAR far
#  else
#    define _FARFUNC
#    define _FAR
#    if   defined(__TINY__) || defined(__SMALL__) || defined(__MEDIUM__)
#      define _CLASSTYPE  near
#    elif defined(__COMPACT__) || defined(__LARGE__)
#      define _CLASSTYPE  far
#    else
#      define _CLASSTYPE  huge
#    endif
#  endif
#endif

#if defined(_BUILDRTLDLL)
#  define _FARCALL _export
#else
#  define _FARCALL far
#endif

#ifdef __cplusplus
#  define _PTRDEF(name) typedef name _FAR * P##name;
#  define _REFDEF(name) typedef name _FAR & R##name;
#  define _REFPTRDEF(name) typedef name _FAR * _FAR & RP##name;
#  define _PTRCONSTDEF(name) typedef const name _FAR * PC##name;
#  define _REFCONSTDEF(name) typedef const name _FAR & RC##name;
#  define _CLASSDEF(name) class _CLASSTYPE name; \
        _PTRDEF(name) \
    _REFDEF(name) \
    _REFPTRDEF(name) \
    _PTRCONSTDEF(name) \
    _REFCONSTDEF(name)
#endif

#endif  /* __DEFS_H */
