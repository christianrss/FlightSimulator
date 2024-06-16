#include <stdio.h>
#include <dos.h>
#include <conio.h>
#include "screen.h"
#include "wire.h"

vertex_type cube_vertices[] =  {
	-10, -10, 10, 1, // Vertex 0
	  0,   0,  0, 1,
	  0,   0,  0, 1,
	 10, -10, 10, 1, // Vertex 1
	  0,   0,  0, 1,
	  0,   0,  0, 1,
	 10,  10, 10, 1, // Vertex 2
	  0,   0,  0, 1,
	  0,   0,  0, 1,
	-10,  10, 10, 1, // Vertex 3
	  0,   0,  0, 1,
	  0,   0,  0, 1,
	-10, -10,-10, 1, // Vertex 4
	  0,   0,  0, 1,
	  0,   0,  0, 1,
	 10, -10,-10, 1, // Vertex 5
	  0,   0,  0, 1,
	  0,   0,  0, 1,
	 10,  10,-10, 1, // Vertex 6
	  0,   0,  0, 1,
	  0,   0,  0, 1,
	-10,  10,-10, 1, // Vertex 7
	  0,   0,  0, 1,
	  0,   0,  0, 1
};

line_type cube_lines[] = {
	0,1,  // linha 0...
	1,2,  // linha 1
	2,3,  // linha 2
	3,0,  // linha 3...
	4,5,
	5,6,
	6,7,
	7,4,
	0,4,
	1,5,
	2,6,
	3,7
};

shape_type shape = {
	15,
	8,
	12,
	cube_vertices,
	cube_lines
};

void main()
{
	float matrix[4][4];
	float xangle=0, yangle=0, zangle=0;
    float xrot=0.1, yrot=0.1, zrot=0.1;

    char far *screen_buffer = (char far *)MK_FP(0xa000, 0);///new unsigned char[64000];

	int oldmode = *(int *)MK_FP(0x40, 0x49);
	setmode(0x13);

    while (!kbhit())
    {
        cls(screen_buffer);
        inittrans();
        
        scale(1.5);

        rotate(xangle, yangle, zangle);
        xangle += xrot;
        yangle += yrot;
        zangle += zrot;

        translate(0, 0, 50);

        transform(&shape);
        project(&shape, 100);

        draw_shape(shape, screen_buffer);

        putwindow(0, 0, 320, 200, screen_buffer);

    }

	setmode(oldmode);
}
