/*      stdlib.h

        Definitions for common types, variables, and functions.

        Copyright (c) Borland International 1987,1988,1990,1991
        All Rights Reserved.
*/

#ifndef __STDLIB_H
#define __STDLIB_H

#if !defined( __DEFS_H )
#include <_defs.h>
#endif

#ifndef _SIZE_T
#define _SIZE_T
typedef unsigned size_t;
#endif

#ifndef _DIV_T
#define _DIV_T
typedef struct {
        int     quot;
        int     rem;
} div_t;
#endif

#ifndef _LDIV_T
#define _LDIV_T
typedef struct {
        long    quot;
        long    rem;
} ldiv_t;
#endif

#ifndef _WCHAR_T
#define _WCHAR_T
typedef char wchar_t;
#endif

#ifndef NULL
#if defined(__TINY__) || defined(__SMALL__) || defined(__MEDIUM__)
#define NULL    0
#else
#define NULL    0L
#endif
#endif

typedef void _Cdecl (_FAR * atexit_t)(void);

/* Maximum value returned by "rand" function
*/
#define RAND_MAX 0x7FFFU

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

#define MB_CUR_MAX 1

#ifdef __cplusplus
extern "C" {
#endif
void    _Cdecl abort(void);
int     _Cdecl atexit(atexit_t __func);
double  _Cdecl atof(const char *__s);
int     _Cdecl _FARFUNC atoi(const char _FAR *__s);
long    _CType _FARFUNC atol(const char _FAR *__s);
void   _FAR *_CType _FARFUNC bsearch(const void _FAR *__key, const void _FAR *__base, 
                size_t __nelem, size_t __width,
                int _Cdecl(* _FARFUNC __fcmp)(const void _FAR *, const void _FAR *));
void   _FAR *_Cdecl _FARFUNC calloc(size_t __nitems, size_t __size);
div_t   _Cdecl div(int __numer, int __denom);
void    _Cdecl exit(int __status);
void    _Cdecl _FARFUNC free(void _FAR *__block);
char   _FAR *_Cdecl _FARFUNC getenv(const char _FAR *__name);
int     _Cdecl abs(int __x);
long    _Cdecl labs(long __x);
ldiv_t  _Cdecl _FARFUNC ldiv(long __numer, long __denom);
void   _FAR *_Cdecl _FARFUNC malloc(size_t __size);
int     _Cdecl _FARFUNC mblen(const char _FAR *__s, size_t __n);
size_t  _Cdecl _FARFUNC mbstowcs(wchar_t _FAR *__pwcs, const char _FAR *__s,
                        size_t __n);
int     _Cdecl _FARFUNC mbtowc(wchar_t _FAR *__pwc, const char _FAR *__s, size_t __n);
void    _Cdecl _FARFUNC qsort(void _FAR *__base, size_t __nelem, size_t __width,
                int _Cdecl(*_FARFUNC __fcmp)(const void _FAR *, const void _FAR *));
int     _Cdecl rand(void);
void   _FAR *_Cdecl _FARFUNC realloc(void _FAR *__block, size_t __size);
void    _Cdecl srand(unsigned __seed);
double  _Cdecl _FARFUNC strtod(const char _FAR *__s, char _FAR *_FAR *__endptr);
long    _Cdecl _FARFUNC strtol(const char _FAR *__s, char _FAR *_FAR *__endptr,
                      int __radix);
unsigned long _Cdecl _FARFUNC strtoul(const char _FAR *__s, char _FAR *_FAR *__endptr,
                             int __radix);
int     _Cdecl _FARFUNC system(const char _FAR *__command);
size_t  _Cdecl _FARFUNC wcstombs(char _FAR *__s, const wchar_t _FAR *__pwcs,
                        size_t __n);
int     _Cdecl _FARFUNC wctomb(char _FAR *__s, wchar_t __wc);
#ifdef __cplusplus
}
#endif

#if !__STDC__

/* Variables */
#if !defined( _RTLDLL )
extern  int _Cdecl  errno;
extern  int _Cdecl  _doserrno;
#else

#ifdef __cplusplus
extern "C" {
#endif
int far * far _Cdecl __getErrno(void);
int far * far _Cdecl __getDOSErrno(void);
#ifdef __cplusplus
}
#endif

#define errno (*__getErrno())
#define _doserrno (*__getDOSErrno())
#endif

/*
  These 2 constants are defined in MS's stdlib.h.  Rather than defining them
  all the time and invading the ANSI programmers name space we'll only make
  them visible when __STDC__ is *off*.  Anybody using these constants ain't
  writing standard C anyway!
*/
#define DOS_MODE  0
#define OS2_MODE  1

extern  unsigned        _Cdecl _psp;

extern  char          **_Cdecl environ;
extern  int             _Cdecl _fmode;
extern  unsigned char   _Cdecl _osmajor;
extern  unsigned char   _Cdecl _osminor;
extern  char           _FAR *_Cdecl sys_errlist[];
extern  int             _Cdecl sys_nerr;
extern  unsigned int    _Cdecl _version;

#define atoi(s)((int) atol(s))

#ifdef __cplusplus
inline int  _Cdecl random(int __num)
    { return(int)(((long)rand()*__num)/(RAND_MAX+1)); }
extern "C" long _Cdecl _FARFUNC time(long _FAR *);  /* need prototype of time() for C++ randomize() */
inline void _Cdecl randomize(void) { srand((unsigned) time(NULL)); }
#else
#define random(num)(int)(((long)rand()*(num))/(RAND_MAX+1))
#define randomize()     srand((unsigned)time(NULL))
#define max(a,b)    (((a) > (b)) ? (a) : (b))
#define min(a,b)    (((a) < (b)) ? (a) : (b))
#endif

#ifdef __cplusplus
extern "C" {
#endif
char   _FAR *_Cdecl ecvt(double __value, int __ndig, int _FAR *__dec, 
                         int _FAR *__sign);
void    _Cdecl _exit(int __status);
char   _FAR *_Cdecl fcvt(double __value, int __ndig, int _FAR *__dec,
                    int _FAR *__sign);
char   *_Cdecl gcvt(double __value, int __ndec, char *__buf);
char   _FAR *_CType _FARFUNC itoa(int __value, char _FAR *__string, int __radix);
void   _FAR *_Cdecl _FARFUNC lfind(const void _FAR *__key, const void _FAR *__base, 
                 size_t _FAR *__num, size_t __width,
                 int _Cdecl(*_FARFUNC __fcmp)(const void _FAR *, const void _FAR *));

unsigned long _Cdecl _lrotl(unsigned long __val, int __count);
unsigned long _Cdecl _lrotr(unsigned long __val, int __count);

void   _FAR *_Cdecl _FARFUNC lsearch(const void _FAR *__key, void _FAR *__base, 
                 size_t _FAR *__num, size_t __width, 
                 int _Cdecl(*_FARFUNC __fcmp)(const void _FAR *, const void _FAR *));
char   _FAR *_Cdecl _FARFUNC ltoa(long __value, char _FAR *__string, int __radix);
int     _Cdecl _FARFUNC putenv(const char _FAR *__name);

unsigned _Cdecl _rotl(unsigned __value, int __count);
unsigned _Cdecl _rotr(unsigned __value, int __count);

void    _Cdecl _FARFUNC swab(char _FAR *__from, char _FAR *__to, int __nbytes);
char   _FAR *_Cdecl _FARFUNC ultoa(unsigned long __value, char _FAR *__string,
                          int __radix);

#ifdef __MSC

/* Prototypes needed for MSC macros */

int         _CType _FARFUNC fnsplit( const char _FAR *__path,
                            char *__drive, char *__dir, 
                            char _FAR *__name,
                            char _FAR *__ext );
#endif  /* __MSC */

#ifdef __cplusplus
}
#endif


#endif  /* !__STDC__ */

#ifdef __MSC

/* MSC variables */

extern  unsigned      _Cdecl _version;
#define _osversion _version

/* Constants for MSC functions */

#define _MAX_PATH   80
#define _MAX_DRIVE  3
#define _MAX_DIR    66
#define _MAX_FNAME  9
#define _MAX_EXT    5

/* Macros for MSC functions */

#define _splitpath(path,drive,dir,fname,ext) \
  (void)fnsplit(path,drive,dir,fname,ext)

#endif  /* __MSC */

int _Cdecl __abs__(int);
#ifdef __cplusplus
inline int _Cdecl abs(int __x) { return __abs__(__x); }
#else
#define abs(x)          __abs__(x)
#endif

#endif
