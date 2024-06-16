// ObjectWindows - (C) Copyright 1991 by Borland International

#include <owl.h>
#include <static.h>
#include "checkers.h"
#include "info.h"
#include "board.h"

const LEFTMARGIN = 6;
const SEPERATOR = 4;
const LINESIZE = 16;
const CHARSIZE = 7;
const MAXLINE = INFOXSIZE - LEFTMARGIN;

const COLORX = LEFTMARGIN + CHARSIZE * 6;
const COLORY = SEPERATOR + 2;
const COLORW = CHARSIZE * 6;
const REDINFOX = LEFTMARGIN + CHARSIZE * 7;
const REDINFOY = COLORY + LINESIZE + SEPERATOR * 2;
const REDINFOW = MAXLINE - REDINFOX;
const BLACKINFOX = REDINFOX;
const BLACKINFOY = REDINFOY + LINESIZE + SEPERATOR;
const BLACKINFOW = REDINFOW;				 
const SEARCHX = LEFTMARGIN + CHARSIZE * 14;
const SEARCHY = BLACKINFOY + LINESIZE + SEPERATOR * 2;
const SEARCHW = MAXLINE - SEARCHX;
const ITERX = LEFTMARGIN + CHARSIZE * 12;
const ITERY = SEARCHY + LINESIZE + SEPERATOR;
const ITERW = MAXLINE - ITERX;
const VALUEX = LEFTMARGIN + CHARSIZE * 7;
const VALUEY = ITERY + LINESIZE + SEPERATOR;
const VALUEW = MAXLINE - VALUEX;
const NODEX = LEFTMARGIN + CHARSIZE * 9;
const NODEY = VALUEY + LINESIZE + SEPERATOR;
const NODEW = MAXLINE - NODEX;
const SECX =  LEFTMARGIN + CHARSIZE * 11;
const SECY = NODEY + LINESIZE + SEPERATOR;
const SECW = MAXLINE - SECX;
const STATBESTY = SECY + LINESIZE + SEPERATOR * 2;
const BESTX = LEFTMARGIN;
const BESTY = STATBESTY + LINESIZE + SEPERATOR;
const BESTW = MAXLINE - LEFTMARGIN;
const BESTH = LINESIZE * 3 + SEPERATOR * 3 - 9;
const MESSX = LEFTMARGIN;
const MESSY = BESTY + BESTH + SEPERATOR * 2;
const MESSW = MAXLINE - MESSX;


#define EmptyStr  ""


TInfoWindow::TInfoWindow(PTWindowsObject AParent, LPSTR ATitle) :
	TWindow(AParent, ATitle)
{
	Attr.Style |= WS_CHILD | WS_VISIBLE;
	Attr.X = BORDERSIZE + (MAXBDSIZE * SQUARE_SIZE) + 3;
	Attr.Y = BORDERSIZE - 3;
	InfoRect.right = Attr.W = INFOXSIZE;
	InfoRect.bottom = Attr.H = MAXBDSIZE * SQUARE_SIZE + 6;
	InfoRect.left = InfoRect.top =  0;
	new TStatic(this, -1, "Turn:", LEFTMARGIN, COLORY,
		CHARSIZE * 6, LINESIZE, 5);
	new TStatic(this, -1, "Red:", LEFTMARGIN, REDINFOY,
		CHARSIZE * 5, LINESIZE, 4);
	new TStatic(this, -1, "Black:", LEFTMARGIN, BLACKINFOY,
		CHARSIZE * 7, LINESIZE, 6);
	new TStatic(this, -1, "Searchdepth:", LEFTMARGIN, SEARCHY,
		CHARSIZE * 13, LINESIZE, 12);
	new TStatic(this, -1, "Iteration:", LEFTMARGIN, ITERY,
		CHARSIZE * 11, LINESIZE, 10);
	new TStatic(this, -1, "Value:", LEFTMARGIN, VALUEY,
		CHARSIZE * 7, LINESIZE, 6);
	new TStatic(this, -1, "Nodes:", LEFTMARGIN, NODEY,
		CHARSIZE * 7, LINESIZE, 7);
	new TStatic(this, -1, "Seconds:", LEFTMARGIN, SECY,
		CHARSIZE * 9, LINESIZE, 9);
	new TStatic(this, -1, "Bestline:", LEFTMARGIN, STATBESTY,
		CHARSIZE * 9, LINESIZE, 9);
	Color = new TStatic(this, -1, EmptyStr, COLORX, COLORY,
		COLORW, LINESIZE, 6);
	RedInfo = new TStatic(this, -1, EmptyStr, REDINFOX, REDINFOY,
		REDINFOW, LINESIZE, REDINFOW/CHARSIZE);
	BlackInfo = new TStatic(this, -1, EmptyStr, BLACKINFOX, BLACKINFOY,
		BLACKINFOW, LINESIZE, BLACKINFOW / CHARSIZE);
	SearchDepth = new TStatic(this, -1, EmptyStr, SEARCHX, SEARCHY,
		SEARCHW, LINESIZE, SEARCHW / CHARSIZE);
	Iteration = new TStatic(this, -1, EmptyStr, ITERX, ITERY,
		ITERW, LINESIZE, ITERW/CHARSIZE);
	Value = new TStatic(this, -1, EmptyStr, VALUEX, VALUEY,
		VALUEW, LINESIZE, VALUEW / CHARSIZE);
	Nodes = new TStatic(this, -1, EmptyStr, NODEX, NODEY,
		NODEW, LINESIZE, NODEW / CHARSIZE);
	Seconds = new TStatic(this, -1, EmptyStr, SECX, SECY,
		SECW, LINESIZE, SECW / CHARSIZE);
	BestLine = new TStatic(this, -1, EmptyStr, BESTX, BESTY,
		BESTW, BESTH, ((BESTW / CHARSIZE) * 3));
	Message = new TStatic(this, -1, EmptyStr, MESSX, MESSY,
		MESSW, LINESIZE, MESSW / CHARSIZE);
}


void TInfoWindow::Paint( HDC PaintDC, PAINTSTRUCT& )
{
	DrawInfoFrame(PaintDC);
}

void TInfoWindow::DrawInfoFrame(HDC hDC)
{

   DrawFrame(hDC, InfoRect);
}

void TInfoWindow::WMControlColor(TMessage& Msg)
{
	SetBkColor(Msg.WParam, RGB(192, 192, 192));
	Msg.Result = GetStockObject(LTGRAY_BRUSH);
}

void TInfoWindow::Reset()
{
   Color->SetText("Red");
   RedInfo->Clear();
   BlackInfo->Clear();
   SearchDepth->Clear();
   Iteration->Clear();
   Value->Clear();
   Nodes->Clear();
   Seconds->Clear();
   BestLine->Clear();
   Message->Clear();
}

void TInfoWindow::IterReset()
{
   Color->SetText("Red");
   Iteration->Clear();
   Value->Clear();
   Nodes->Clear();
   Seconds->Clear();
   BestLine->Clear();
}




