#include <stdio.h>
#include <dos.h>
#include <conio.h>
#include "bresnham.h"
#include "eventmngr.h"
#include "screen.h"
#include <math.h>

// Estruturas variaveis para dados de forma:
struct vertex_type { // Estrutura para os vertices individuais
	int lx,ly;      // coordenadas locais do vertice
	int sx,sy;		// coordenadas da tela do vertice
};

struct shape_type { // Estrutura para dados da forma
	int color;              // cor da forma
	int number_of_vertices; // numero de vertices
	vertex_type *vertex;  // Array descritivos de vertice
};

// Dados para formas:
vertex_type rectangle_array[] = { // Dados para triangulo
	-10,-10, // Primeiro vertice
	0,0,
	10,-10, // Segundo vertice
	0,0,
	10,10, // Terceiro vertice
	0,0,
	-10,10, // Quarto vertice
	0,0
};

shape_type shape = {
	// Retangulo:
	15,	 // Cor (branca)
	4,	 // Numero de vertices
	rectangle_array // Ponteiro para array de vertice
};
// Prototipos de funcoes:
void draw_shape(shape_type, char far *screen);
void translate(shape_type *shape, int xtrans, int ytrans);
void scale(shape_type *shape, float scale_factor);
void rotate(shape_type *shape, double angle);
void main()
{

	char far *screen = (char far *)MK_FP(0xa000,0);
	cls(screen);
	int oldmode=*(int *)MK_FP(0x40,0x49);
	setmode(0x13);
	scale(&shape,2); // Dobra o tamanho da forma
	rotate(&shape,1.1); // Rotaciona a forma 90 graus
	translate(&shape,150,90);  // Rotaciona a forma para as coordenadas 150,90
	draw_shape(shape,screen);
	while(!kbhit());
	setmode(oldmode);
}

void draw_shape(shape_type shape, char far *screen)
{
	// Loop por todos os vertices da forma
	for (int i=0; i<shape.number_of_vertices; i++)
	{
		// Calcula o proximo vertice apos o vertice atual
		int v2=i+1;
		// Retorna a 0
		if (v2>=shape.number_of_vertices) v2=0;
		// Traca reta deste vertice ate o proximo
		linedraw(shape.vertex[i].sx,shape.vertex[i].sy,
			shape.vertex[v2].sx,shape.vertex[v2].sy,
			shape.color,screen);
	}
}
void translate(shape_type *shape, int xtrans, int ytrans)
{
	for (int i=0; i<shape->number_of_vertices; i++)
	{
		shape->vertex[i].sx+=xtrans;
		shape->vertex[i].sy+=ytrans;
	}
}
void scale(shape_type *shape, float scale_factor)
// Escalar shape usando o fator de escala SCALE_FACTOR
{
	for (int i = 0; i < shape->number_of_vertices; i++)
	{
		shape->vertex[i].sx = shape->vertex[i].lx*scale_factor;
		shape->vertex[i].sy = shape->vertex[i].ly*scale_factor;
	}
}
void rotate(shape_type *shape, double angle)
{
	int x,y;
	// Rotacionar todos os vertices de SHAPE
	for (int i=0; i<shape->number_of_vertices; i++)
	{
		// Armazena coordenadas rotacionadas em variaveis temporarias
		x=shape->vertex[i].sx*cos(angle) - shape->vertex[i].sy*sin(angle);
		y=shape->vertex[i].sx*sin(angle) + shape->vertex[i].sy*cos(angle);
		// Transferir para coordenadas da tela
		shape->vertex[i].sx = x;
		shape->vertex[i].sy = y;
	}
}