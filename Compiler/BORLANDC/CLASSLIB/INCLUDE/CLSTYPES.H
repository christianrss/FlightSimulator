// Borland C++ - (C) Copyright 1991 by Borland International

// Contents ----------------------------------------------------------------
//
//      classType
//      hashValueType
//      sizeType
//      iterFuncType
//      condFuncType
//      countType
//
//      objectClass
//      errorClass
//      sortableClass
//      stringClass
//      listElementClass
//      doubleListElementClass
//      containerClass
//      stackClass
//      queueClass
//      dequeClass
//      collectionClass
//      hashTableClass
//      bagClass
//      setClass
//      dictionaryClass
//      associationClass
//      arrayClass
//      sortedArrayClass
//      listClass
//      doubleListClass
//	timeClass
//	dateClass
//	longClass
//
//	__firstOWLClass
//	__lastOWLClass
//      __lastLibClass
//      __firstUserClass
//
//      directoryClass
//
//      __lastClass
//
// Description
//
//      Defines types for the class library.
//
// End ---------------------------------------------------------------------

// Interface Dependencies ---------------------------------------------------

#ifndef __CLSTYPES_H
#define __CLSTYPES_H

#ifndef __LIMITS_H
#include <limits.h>
#endif

#if !defined(__DEFS_H)
#include <_defs.h>
#endif	// __DEFS_H

// End Interface Dependencies ------------------------------------------------


// Section -----------------------------------------------------------------
//                                  types                                 //
// End ---------------------------------------------------------------------


// Type //

typedef unsigned int classType;

// Description -------------------------------------------------------------
//
//      Defines the type of a class.
//
// End ---------------------------------------------------------------------


// Type //

typedef unsigned int    hashValueType;

// Description -------------------------------------------------------------
//
//      Defines a returned hash value.
//
// End ---------------------------------------------------------------------


// Type //

typedef unsigned int    sizeType;

// Description -------------------------------------------------------------
//
//      Defines the size of a storage area.
//
// End ---------------------------------------------------------------------

typedef void _FAR * Pvoid;
typedef const void _FAR * PCvoid;
typedef void _FAR * _FAR & RPvoid;
typedef char _FAR * Pchar;
typedef const char _FAR * PCchar;

// Type //

_CLASSDEF(Object)
typedef void ( _FAR *iterFuncType )( RObject, Pvoid );

// Description -------------------------------------------------------------
//
//      Defines a pointer to an iteration function.  The iteration function
//      takes an Object reference and a point to a list of parameters to
//      the function.  The parameter list pointer may be NULL.
//
// End ---------------------------------------------------------------------


// Type //

typedef int ( _FAR *condFuncType )( RCObject, Pvoid );

// Description -------------------------------------------------------------
//
//      Defines a pointer to a function which implements a conditional test
//      and returns 0 if the condition was met, non-zero otherwise.  The
//      non-zero values are defined by the individual function.
//
// End ---------------------------------------------------------------------


// End Section types //


// Type //

typedef int    countType;

// Description -------------------------------------------------------------
//
//      Defines a container for counting things in the class library.
//
// End ---------------------------------------------------------------------


// End Section types //


// Section -----------------------------------------------------------------
//                               defines                                  //
// End ---------------------------------------------------------------------

// LiteralSection ----------------------------------------------------------
//
//      class type codes
//
// Description
//
//      Defines codes for the class types in the class library.
//      The ranges for the codes and their use are defined below.
//
//      0 .. __lastLibClass:                Reserved for classes in 
//					    the container class library
//					    and the ObjectWindows class
//					    library
//
//      __firstOWLClass .. __lastOWLClass:  Reserved for classes in 
//					    the ObjectWindows class 
//					    library.
//
//      __firstUserClass .. __lastClass:    Available for general use.
//
// End ---------------------------------------------------------------------

#define    objectClass				0
#define    errorClass               (objectClass+1)
#define    sortableClass            (errorClass+1)
#define    stringClass              (sortableClass+1)
#define    listElementClass         (stringClass+1)
#define    doubleListElementClass   (listElementClass+1)
#define    containerClass           (doubleListElementClass+1)
#define    stackClass               (containerClass+1)
#define    queueClass               (stackClass+1)
#define    dequeClass               (queueClass+1)
#define    collectionClass          (dequeClass+1)
#define    hashTableClass           (collectionClass+1)
#define    bagClass                 (hashTableClass+1)
#define    setClass                 (bagClass+1)
#define    dictionaryClass          (setClass+1)
#define    associationClass         (dictionaryClass+1)
#define    arrayClass               (associationClass+1)
#define    sortedArrayClass         (arrayClass+1)
#define    listClass                (sortedArrayClass+1)
#define    doubleListClass          (listClass+1)
#define    timeClass                (doubleListClass+1)
#define	   dateClass                (timeClass+1)
#define	   longClass		    (dateClass+1)
#define    TCollectionClass	    (longClass+1)

#define    __firstOWLClass	    100
#define	   __lastOWLClass	    200
#define    __lastLibClass           255
#define    __firstUserClass         __lastLibClass+1

#define    __lastClass              UINT_MAX

// End LiteralSection class type codes //

// End Section defines //

#endif // ifndef __CLSTYPES_H //

