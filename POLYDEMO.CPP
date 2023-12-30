#include <stdio.h>
#include <dos.h>
#include <conio.h>
#include <stdlib.h>
#include "poly.h"
#include "drawpoly.h"
#include "loadpoly.h"
#include "screen.h"

world_type world;

void main(int argc, char* argv[])
{
    float xangle = 0, yangle = 0, zangle = 0;
    float xrot = 0.1, yrot = 0.1, zrot = 0.1;
    char far *screen_buffer;

    if (argc!=2)
    {
        puts("Wrong numer of arguments.\n");
        exit(0);
    }

    loadpoly(&world, argv[1]);

    //screen_buffer = new unsigned char[64000];
    screen_buffer = (char far *) MK_FP(0xa000, 0);
    setmode(0x13);

    int oldmode = *(int *)MK_FP(0x40, 0x49);
    while(!kbhit())
    {
        cls(screen_buffer);
        inittrans();
        scale(1);
        rotate(xangle, yangle, zangle);
        xangle += xrot;
        yangle += yrot;
        zangle += zrot;
        translate(0, 0, 600);
        transform(&world.obj[0]);

        project(&world.obj[0], 400);
        draw_object(world.obj[0], screen_buffer);
        putwindow(0, 0, 320, 200, screen_buffer);
    }

    setmode(oldmode);
}


