/*-------------------------------------------------------------------*/
/* filename -       tapplica.cpp                                     */
/*                                                                   */
/* function(s)                                                       */
/*          TApplication member functions (constructor & destructor) */
/*-------------------------------------------------------------------*/

/*-------------------------------------------------------------------*/
/*                                                                   */
/*    Turbo Vision -  Version 1.0                                    */
/*                                                                   */
/*                                                                   */
/*    Copyright (c) 1987,1988,1990 by Borland International          */
/*    All Rights Reserved.                                           */
/*                                                                   */
/*-------------------------------------------------------------------*/

#define Uses_TSystemError
#define Uses_TEventQueue
#define Uses_TScreen
#define Uses_TObject
#define Uses_TApplication
#include <tv.h>

static TEventQueue teq;
static TSystemError sysErr;
static TScreen tsc;

void initHistory();
void doneHistory();

TApplication::TApplication() :
    TProgInit( &TApplication::initStatusLine,
                  &TApplication::initMenuBar,
                  &TApplication::initDeskTop
                )
{
    initHistory();
}

TApplication::~TApplication()
{
    doneHistory();
}

void TApplication::suspend()
{
    TScreen::suspend();
    TSystemError::suspend();
    TEventQueue::suspend();
}

void TApplication::resume()
{
    TEventQueue::resume();
    TSystemError::resume();
    TScreen::resume();
}
