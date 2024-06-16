// Borland C++ - (C) Copyright 1991 by Borland International

// Contents ----------------------------------------------------------------
//
//      Deque
//
// Description
//
//      Defines the class Deque.
//
// End ---------------------------------------------------------------------

// Interface Dependencies ---------------------------------------------------

#ifndef __DEQUE_H
#define __DEQUE_H

#ifndef __IOSTREAM_H
#include <iostream.h>
#define __IOSTREAM_H
#endif

#ifndef __CLSTYPES_H
#include <clstypes.h>
#endif

#ifndef __OBJECT_H
#include <object.h>
#endif

#ifndef __CONTAIN_H
#include <contain.h>
#endif

#ifndef __DBLLIST_H
#include <dbllist.h>
#endif

// End Interface Dependencies ------------------------------------------------

_CLASSDEF(Deque)

// Class //

class _CLASSTYPE Deque:  public Container
{
public:
    virtual ~Deque();

    RObject         peekLeft() const
	    { return theDeque.peekAtHead(); }
    RObject         peekRight() const
	    { return theDeque.peekAtTail(); }
    RObject         getLeft();
    RObject         getRight();
    void            putLeft( RObject o )
            { theDeque.addAtHead( o ); itemsInContainer++; }
    void            putRight( RObject o )
            { theDeque.addAtTail( o ); itemsInContainer++; }

    virtual RContainerIterator initIterator() const;
    RContainerIterator initReverseIterator() const;

    virtual classType       isA() const;
    virtual Pchar nameOf() const;
    virtual hashValueType   hashValue() const;

private:
	DoubleList    theDeque;
};

// Description -------------------------------------------------------------
//
// 	    Defines the container class Deque.  A deque is a double-ended queue.
//      You may inspect, add, and remove elements at either end of the 
//      deque.
//
// Public Members
//
//      peekLeft
//
//      Returns a reference to the object at the left end of the deque.
//      The object is still owned by the deque.
//
//      peekRight
//
//      Returns a reference to the object at the right end of the deque.
//      The object is still owned by the deque.
//
//      putLeft
//
//      Enqueues an object at the left end.
//
//      putRight
//
//      Enqueues an object at the right end.
//
//      getLeft
//
//      Dequeues an object from the left end.
//
//      getRight
//
//      Dequeues an object from the right end.
//
//      initIterator
//
//      Left-to-right Deque iterator initializer.
//
//      initReverseIterator
//
//      Right-to-left Deque iterator initializer.
//
// 	    isA
//
// 	    Returns the class type for a deque.
//
// 	    nameOf
//
// 	    Returns a pointer to the character string "Deque."
// 	
// 	    hashValue
//
// 	    Returns a pre-defined value for deques.
//
// Inherited Members
//
//      Deque( Deque& )
//
//      Copy constructor.  Inherited from Container.
//
//      isEmpty
//
// 	    Inherited from Container.
//
// 	    isEqual
//
// 	    Inherited from Container.
//
//      forEach
//
// 	    Inherited from Container.
//
//      firstThat
//
// 	    Inherited from Container.
//
//      lastThat
//
// 	    Inherited from Container.
//
//      getItemsInContainer
//
// 	    Inherited from Container.
//
//      printOn
//
// 	    Inherited from Container.
//
//      printHeader
//
// 	    Inherited from Container.
//
//      printSeparator
//
// 	    Inherited from Container.
//
//      printTrailer
//
// 	    Inherited from Container.
//
// Private Members
//
//      theDeque
//
//      The implementation of the deque.
//
// End ---------------------------------------------------------------------


#endif // ifndef __DEQUE_H //
