// Borland C++ - (C) Copyright 1991 by Borland International

#if !defined(__SAFEPOOL_H)
#define __SAFEPOOL_H

#if !defined(__OWLDEFS_H)
#include <owldefs.h>
#endif

const int DEFAULT_SAFETY_POOL_SIZE = 8192;

_CLASSDEF(SafetyPool)

class _EXPORT SafetyPool
{
public:
    static  int		    Allocate(size_t size
				    = DEFAULT_SAFETY_POOL_SIZE);
    static  int		    IsExhausted()
			      // returns true if safetyPool is exhausted
			      { return safetyPool == NULL; };
    static  int		    Size;
    static  Pvoid 	    safetyPool;
};

#endif // __SAFEPOOL_H
