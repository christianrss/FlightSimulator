/*  mem.h

    Memory manipulation functions

    Copyright (c) Borland International 1987,1988,1990,1991
    All Rights Reserved.
*/

#if !defined( __MEM_H )
#define __MEM_H

#if !defined( __DEFS_H )
#include <_defs.h>
#endif

#ifndef _STDDEF
#define _STDDEF
#ifndef _PTRDIFF_T
#define _PTRDIFF_T
#if defined(__LARGE__) || defined(__HUGE__) || defined(__COMPACT__)
typedef long    ptrdiff_t;
#else
typedef int ptrdiff_t;
#endif
#endif
#ifndef _SIZE_T
#define _SIZE_T
typedef unsigned size_t;
#endif
#endif

#ifndef NULL
#if defined(__TINY__) || defined(__SMALL__) || defined(__MEDIUM__)
#define NULL    0
#else
#define NULL    0L
#endif
#endif

#ifdef __cplusplus
extern "C" {
#endif
void _FAR * _FARFUNC _Cdecl memccpy(void _FAR *__dest, const void _FAR *__src,
                           int __c, size_t __n);
void _FAR * _FARFUNC _Cdecl memchr(const void _FAR *__s, int __c, size_t __n);
int         _FARFUNC _Cdecl memcmp(const void _FAR *__s1, const void _FAR *__s2,
                          size_t __n);
void _FAR * _FARFUNC _Cdecl memcpy(void _FAR *__dest, const void _FAR *__src,
                          size_t __n);
int         _FARFUNC _Cdecl memicmp(const void _FAR *__s1, const void _FAR *__s2,
                          size_t __n);
void _FAR * _CType _FARFUNC memmove(void _FAR *__dest, const void _FAR *__src,
                          size_t __n);
void * _CType _FARFUNC memset(void *__s, int __c, size_t __n);
void        _FARFUNC _Cdecl movedata(unsigned __srcseg, unsigned __srcoff,
                            unsigned __dstseg,unsigned __dstoff, size_t __n);
void        _FARFUNC _Cdecl movmem(void _FAR *__src, void _FAR *__dest,
                          unsigned __length);
void        _FARFUNC _Cdecl setmem(void _FAR *__dest,unsigned __length, char __value);

#if !__SDTC__
void  far * _FARCALL cdecl _fmemccpy(void far *__dest, const void far *__src,
                       int c, size_t __n);
void  far * _FARCALL cdecl _fmemchr(const void far *__s, int c, size_t __n);
int         _FARCALL cdecl _fmemcmp(const void far *__s1, const void far *__s2,
                       size_t __n);
void  far * _FARCALL cdecl _fmemcpy(void far *__dest, const void far *__src,
                       size_t __n);
int         _FARCALL cdecl _fmemicmp(const void far *__s1, const void far *__s2,
                       size_t __n);
void  far * _FARCALL cdecl _fmemmove(void far *__dest, const void far *__src,
                       size_t __n);
void  far * _FARCALL cdecl _fmemset(void far *__s, int c, size_t __n);
void        _FARCALL cdecl _fmovmem(void far *__src, void far *__dest,
                       unsigned __length);
void        _FARCALL cdecl _fsetmem(void far *__dest,unsigned __length, 
                       char __value);
#endif

#ifdef __cplusplus
}
#endif

#endif  /* __MEM_H */

