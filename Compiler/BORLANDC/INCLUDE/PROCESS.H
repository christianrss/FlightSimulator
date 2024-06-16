/*  process.h

    Symbols and structures for process management.

    Copyright (c) Borland International 1987,1988,1990,1991
    All Rights Reserved.
*/

#if !defined( __PROCESS_H )
#define __PROCESS_H

#if !defined( __DEFS_H )
#include <_defs.h>
#endif

/*  Modes available as first argument to the spawnxx functions. */

#define P_WAIT    0 /* child runs separately, parent waits until exit */
#define P_NOWAIT  1 /* both concurrent -- not implemented */
#define P_OVERLAY 2 /* child replaces parent, parent no longer exists */

#define P_NOWAITO 3 /* ASYNCH,       toss RC    */
#define P_DETACH  4 /* DETACHED,     toss RC    */

#define WAIT_CHILD       0
#define WAIT_GRANDCHILD      1

/*  MSDOS does not have any abstract identifier for a process, but the
    process Program Segment Prefix location provides a similar token.
*/

extern  unsigned _Cdecl _psp;    /* provided unconditionally in dos.h */

#define  getpid()   (_psp)

#ifdef __cplusplus
extern "C" {
#endif
void    _Cdecl abort(void);
int _Cdecl _FARFUNC execl(char _FAR *__path, char _FAR *__arg0, ...);
int _Cdecl _FARFUNC execle(char _FAR *__path, char _FAR *__arg0, ...);
int _Cdecl _FARFUNC execlp(char _FAR *__path, char _FAR *__arg0, ...);
int _Cdecl _FARFUNC execlpe(char _FAR *__path, char _FAR *__arg0, ...);
int _Cdecl _FARFUNC execv(char _FAR *__path, char _FAR *__argv[]);
int _Cdecl _FARFUNC execve(char _FAR *__path, char _FAR *__argv[], char _FAR *_FAR *__env);
int _Cdecl _FARFUNC execvp(char _FAR *__path, char _FAR *__argv[]);
int _Cdecl _FARFUNC execvpe(char _FAR *__path, char _FAR *__argv[], char _FAR *_FAR *__env);
void    _Cdecl exit(int __status);
void    _Cdecl _exit(int __status);
int _Cdecl _FARFUNC spawnl(int __mode, char _FAR *__path, char _FAR *__arg0, ...);
int _Cdecl _FARFUNC spawnle(int __mode, char _FAR *__path, char _FAR *__arg0, ...);
int _Cdecl _FARFUNC spawnlp(int __mode, char _FAR *__path, char _FAR *__arg0, ...);
int _Cdecl _FARFUNC spawnlpe(int __mode, char _FAR *__path, char _FAR *__arg0, ...);
int _Cdecl _FARFUNC spawnv(int __mode, char _FAR *__path, char _FAR *__argv[]);
int _Cdecl _FARFUNC spawnve(int __mode, char _FAR *__path, char _FAR *__argv[], char _FAR *_FAR *__env);
int _Cdecl _FARFUNC spawnvp(int __mode, char _FAR *__path, char _FAR *__argv[]);
int _Cdecl _FARFUNC spawnvpe(int __mode, char _FAR *__path, char _FAR *__argv[], char _FAR *_FAR *__env);
int _Cdecl _FARFUNC system(const char _FAR *__command);
#ifdef __cplusplus
}
#endif

#endif  /* __PROCESS_H */

