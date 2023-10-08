#include <stdio.h>
#include <dos.h>
#include <conio.h>
#include "bresnham.h"
#include "eventmngr.h"
#include "screen.h"

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
	0,0,
	0,0,
	0,20,
	0,20,
	20,20,
	20,20,
	20,0,
	20,0
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

void main()
{

	char far *screen = (char far *)MK_FP(0xa000,0);
	cls(screen);
	int oldmode=*(int *)MK_FP(0x40,0x49);
	setmode(0x13);
	scale(&shape,4);
	translate(&shape,150,90);
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