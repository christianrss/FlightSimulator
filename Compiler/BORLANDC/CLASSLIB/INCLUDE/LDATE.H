// Borland C++ - (C) Copyright 1991 by Borland International

// Contents ----------------------------------------------------------------
//
// 	BaseDate
//
// Description
//
/*  Provides BaseDate as an abstract base class for handling date    */
/*  storage and formatting                                           */
//
/*  Provides the Date class for storing dates and converting them    */
/*  to an ASCII string of the form                                   */
/*                                                                   */
/*      January 1, 1990                                              */
//
// End ---------------------------------------------------------------------

#ifndef __LDATE_H
#define __LDATE_H

#include <assert.h>
#include <dos.h>
#include "strng.h"

_CLASSDEF(BaseDate)
_CLASSDEF(Date)

class _CLASSTYPE BaseDate : public Sortable
{
public:
    unsigned Month() const;
    unsigned Day() const;
	unsigned Year() const;
    void SetMonth( unsigned char );
    void SetDay( unsigned char );
	void SetYear( unsigned );

    virtual classType       isA() const = 0;
    virtual Pchar nameOf() const = 0;
    virtual hashValueType   hashValue() const;
    virtual int             isEqual( RCObject ) const;
    virtual int             isLessThan( RCObject ) const;
    virtual void            printOn( Rostream ) const = 0;
protected:
    BaseDate();
    BaseDate( unsigned char, unsigned char, unsigned );
    BaseDate( RCBaseDate );
    ~BaseDate();
private:
	unsigned char MM;
	unsigned char DD;
	unsigned int YY;
};

inline BaseDate::BaseDate()
{
	struct date d;
	getdate( &d );
	MM = d.da_mon - 1;
	DD = d.da_day;
	YY = d.da_year;
}

inline BaseDate::BaseDate( unsigned char M, unsigned char D, unsigned Y )
{
	SetMonth( M );
	SetDay( D );
	SetYear( Y );
}

inline BaseDate::BaseDate( RCBaseDate B ) :
	MM(B.MM), DD(B.DD), YY(B.YY)
{
}

inline unsigned BaseDate::Month() const
{
	return MM;
}

inline unsigned BaseDate::Day() const
{
	return DD;
}

inline unsigned BaseDate::Year() const
{
	return YY;
}

inline void BaseDate::SetMonth( unsigned char M )
{
	assert( M > 0 && M < 13 );
	MM = M - 1;
}

inline void BaseDate::SetDay( unsigned char D )
{
	assert( D < 32 );
	DD = D;
}

inline void BaseDate::SetYear( unsigned Y )
{
	YY = Y;
}

class _CLASSTYPE Date : public BaseDate
{
public:
    Date();
    Date( unsigned char, unsigned char, unsigned );
    Date( RCDate );
    ~Date();
    virtual classType       isA() const;
    virtual Pchar nameOf() const;
    virtual void            printOn( Rostream ) const;
};

inline Date::Date()
{
}

inline Date::Date( unsigned char M, unsigned char D, unsigned Y ) : BaseDate( M, D, Y )
{
}

inline Date::Date( RCDate D ) : BaseDate( D )
{
}

#endif  // ifndef __LDATE_H //
