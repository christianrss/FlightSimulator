#include <stdio.h>
#include <dos.h>
#include <conio.h>
#include <stdlib.h>
#include "poly.h"
#include "drawpoly.h"
#include "loadpoly.h"
#include "screen.h"
#include "pcx.h"

const int WIND_WIDTH=7*21;
const int WIND_HEIGHT=7*21;

world_type world;
pcx_struct background;
Pcx bgloader;

void main(int argc, char* argv[])
{
    int key;
    float xangle=0,yangle=0,zangle=0;
    float xrot=0,yrot=0,zrot=0;
    char far *screen_buffer;

    if (argc!=2)
    {
        puts("Wrong number of arguments.\n");
        exit(0);
    }

    if (bgloader.load("Resource\3dbg2.pcx", &background))
    {
        puts("Cannot load PCX File.\n");
        exit(0);
    }

    loadpoly(&world, argv[1]);
    screen_buffer = (char far *) MK_FP(0xa000, 0);
    int oldmode= *(int*)MK_FP(0x40, 0x49);

    setmode(0x13);
    setpalette((char far *)background.palette, 0, 256);

    for (long i = 0; i < 64000; i++)
        screen_buffer[i] = background.image[i];

    int curobj = 0;
    int scalefactor = 1;
    int zdistance = 600;

    while (key!=27)
    {
        clrwin(10, 8, WIND_WIDTH, WIND_HEIGHT, screen_buffer);
        inittrans();
        scale(scalefactor);
        rotate(xangle, yangle, zangle);

        xangle += xrot;
        yangle += yrot;
        zangle += zrot;

        if (xangle>255) xangle = 0;
        if (xangle<0) xangle = 255;
        if (yangle>255) yangle = 0;
        if (yangle<0) yangle = 255;
        if (zangle>255) zangle = 0;
        if (zangle<0) zangle = 255;

        translate(0, 0, zdistance);

        transform(&world.obj[curobj]);

        project(&world.obj[curobj], 400);

        draw_object(world.obj[curobj], screen_buffer);

        putwindow(0, 0, 320, 200, screen_buffer);

        if (kbhit())
        {
            key = getch();

            switch (key)
            {
                // ENTER: Go to next object
                case 13:
                    curobj++;
                    if (curobj>=world.number_of_objects)
                        curobj = 0;
                    break;
                // 7: Speed up x rotation
                case 55:
                    xrot++;
                    break;
                // 4: Stop x rotation
                case 52:
                    xrot = 0;
                    break;
                // 1: Slow down x rotation
                case 49:
                    --xrot;
                    break;
                // 8: Speed up y rotation
                case 56:
                    yrot++;
                    break;
                // 5: Stop y rotation
                case 53:
                    yrot = 0;
                    break;
                // 2: Slow down y rotation
                case 50:
                    --yrot;
                    break;
                // 9: Speed up z rotation
                case 57:
                    zrot++;
                    break;
                // 6: Stop z rotation
                case 54:
                    zrot = 0;
                    break;
                // 3: Slow down z rotation
                case 51:
                    --zrot;
                    break;
                // +: Increase distance
                case '+':
                    zdistance += 30;
                    break;
                // -: Decrease distance
                case '-':
                    if(zdistance>530) zdistance-=30;
                    break;

            }
        }

    }

    setmode(oldmode);

}