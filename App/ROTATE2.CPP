#include <stdio.h>
#include <dos.h>
#include <conio.h>
#include "bresnham.h"
#include "eventmngr.h"
#include "screen.h"
#include "math.h"

struct vertex_type {
	int lx,ly,lt;
	int sx,sy,st;
};

struct shape_type {
	int color;
	int number_of_vertices;
	vertex_type *vertex;
};

vertex_type rectangle_array[] = {
	-10,-10,1, // Primeiro vertice
	0,0,1,
	10,-10,1, // Segundo vertice
	0,0,1,
	10,10,1, // Terceiro vertice
	0,0,1,
	-10,10,1, // Quarto vertice
	0,0,1
};
shape_type shape = {
	15,
	4,
	rectangle_array
};

void draw_shape(shape_type shape, char far *screen);
void transform(shape_type *shape, int scale_factor,
	int xtrans, int ytrans, float angle);

void main()
{
	char far *screen = (char far *) MK_FP(0xa000,0);
	cls(screen);
	int oldmode = *(int*)MK_FP(0x40,0x49);
	setmode(0x13);
	transform(&shape,1.5,160,100,0.7);
	draw_shape(shape,screen);
	while(!kbhit());
	setmode(oldmode);
}

void draw_shape(shape_type shape, char far *screen)
{
	for (int i=0; i < shape.number_of_vertices; i++)
	{
		int v2=i+1;
		if (v2>=shape.number_of_vertices) v2=0;
		linedraw(shape.vertex[i].sx,shape.vertex[i].sy,
			shape.vertex[v2].sx,shape.vertex[v2].sy,
			shape.color,screen);
	}
}

void transform(shape_type *shape, int scale_factor, int xtrans,
	int ytrans, float angle)
{
	float matrix[3][3]; // Matriz transformacao
	float smatrix[3][3]; // Matriz escalamento
	float rtmatrix[3][3]; // Matriz rotacao e translacao

	// Inicializa matriz de escalonamento
	smatrix[0][0] = scale_factor;
	smatrix[0][1] = 0;
	smatrix[0][2] = 0;

	smatrix[1][0] = 0;
	smatrix[1][1] = scale_factor;
	smatrix[1][2] = 0;

	smatrix[2][0] = 0;
	smatrix[2][1] = 0;
	smatrix[2][2] = 1;

	// Inicializar a matriz rotacao e translacao
	rtmatrix[0][0] = cos(angle);
	rtmatrix[0][1] = -sin(angle);
	rtmatrix[0][2] = 0;

	rtmatrix[1][0] = sin(angle);
	rtmatrix[1][1] = cos(angle);
	rtmatrix[1][2] = 0;

	rtmatrix[2][0] = xtrans;
	rtmatrix[2][1] = ytrans;
	rtmatrix[2][2] = 1;
	// Multiplica-las para obter matriz transformacao
	for (int i = 0; i < 3; i++)
	{
		for(int j = 0; j < 3; j++)
		{
			matrix[i][j] = 0;
			for (int k = 0; k<3; k++)
			{
				matrix[i][j]+=smatrix[i][k] * rtmatrix[k][j];
			}
		}
	}
	// Multiplicar todos os vertices pela matriz transformacao
	for (int v=0; v<shape->number_of_vertices; v++)
	{

		int temp0 = 0;
		int temp1 = 0;
		int temp2 = 0;
		// Acumular resultados nas variaveis temporarias
		temp0 += shape->vertex[v].lx * matrix[0][0]
			+ shape->vertex[v].ly * matrix[1][0] + matrix[2][0];

		temp1 += shape->vertex[v].lx * matrix[0][1]
			+ shape->vertex[v].ly * matrix[1][1] + matrix[2][1];

		temp2 += shape->vertex[v].lx * matrix[0][2]
			+ shape->vertex[v].ly * matrix[1][2] + matrix[2][2];

		// Transferir resultados para coordenadas da tela
		shape->vertex[v].sx = temp0;
		shape->vertex[v].sy = temp1;
		shape->vertex[v].st = temp2;
	}
}