#include	<stdio.h>
#include	<dos.h>
#include	<conio.h>
#include	"screen.h"
#include	"bresnham.h"

void main()
{
	char far *screen=(char far *)MK_FP(0xa000,0);
	cls(screen);
	int oldmode=*(int *)MK_FP(0x40,0x49);

	setmode(0x13);

	linedraw(130,70,190,70,15,screen);
	linedraw(190,70,190,130,15,screen);
	linedraw(190,130,130,130,15,screen);
	linedraw(130,130,130,70,15,screen);
	while(!kbhit());
	setmode(oldmode);
}