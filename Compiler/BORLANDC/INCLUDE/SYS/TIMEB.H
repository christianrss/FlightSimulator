/*  timeb.h

    Struct and function declarations for ftime().

        Copyright (c) Borland International 1987,1988,1990,1991
    All Rights Reserved.
*/

#if !defined( __TIMEB_H )
#define __TIMEB_H

#if !defined( __DEFS_H )
#include <_defs.h>
#endif

struct timeb {
      long  time;
      short millitm;
      short timezone;
      short dstflag;
      };

#ifdef __cplusplus
extern "C" {
#endif
void _Cdecl _FARFUNC ftime(struct timeb _FAR *);
#ifdef __cplusplus
}
#endif

#endif  /* __TIMEB_H */

