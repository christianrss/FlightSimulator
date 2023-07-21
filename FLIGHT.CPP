#include <dos.h>
#include "SCREEN.H"

void main() {
	int oldmode = *(int *)MK_FP(0x40,x49);
	unsigned char *screen_buffer;
	screen_buffer = new unsigned char(64000);
	setmode(0x13);
	setmode(oldmode);
	cls(screen_buffer);
}