#include <stdio.h>
#include <dos.h>
#include <conio.h>
#include "bresnham.h"
#include "eventmngr.h"
#include "screen.h"

// Estruturas variaveis para dados de formas:
struct vertex_type { // estrutura para os vertices individuais
	int lx,ly; // Coordenadas locais do vertice
	int sx,sy; // Coordenadas da tela do vertice
};

struct shape_type {  // Estrutura para dados da forma
	int color; // cor da forma
	int number_of_vertices; // numero de vertices
	vertex_type *vertex; // Array de descritivos de vertice
};
// Dados para formas:
vertex_type rectangle_array[] = { // Dados para retangulo
	0,0, // Primeiro vertice
	0,0,
	0,20, // Segundo vertice
	0,20,
	20,20, // Terceiro vertice
	20,20,
	20,0,  // Quarto vertice
	20,0
};
shape_type shape= {
	// Retangulo
	15,	// cor (branca)
	4, // numero de vertices
	rectangle_array // Ponteiro para array de vertice
};

// Prototipos de funcoes:
void draw_shape(shape_type shape, char far *screen);
void translate(shape_type *shape, int xtrans, int ytrans);
void main()
{
	char far *screen =
	(char far *)MK_FP(0xa000,0); // cria ponteiro para a ram de video
	cls(screen);
	int oldmode=*(int *)MK_FP(0x40,0x49);
	setmode(0x13);
	translate(&shape, 200, 90);
	draw_shape(shape,screen);
	while(!kbhit());
	setmode(oldmode);
}
void draw_shape(shape_type shape, char far *screen)
{
	// Loop por todos os vertices da forma:
	for (int i=0; i<shape.number_of_vertices;i++)
	{
		// Calcula offset do proximo vertice
		int v2=i+1;
		// Retorna a 0:
		if (v2>=shape.number_of_vertices) v2=0;
		// traca reta deste vertice ate o proximo
		linedraw(shape.vertex[i].sx,shape.vertex[i].sy,
			shape.vertex[v2].sx,shape.vertex[v2].sy,
				shape.color,screen);
	}
}

void translate(shape_type *shape, int xtrans, int ytrans)
{
	// Translada cada ponto da forma SHAPE de XTRANS,YTRANS
	for (int i=0; i<shape->number_of_vertices; i++)
	{
		shape->vertex[i].sx = shape->vertex[i].lx+xtrans;
		shape->vertex[i].sy = shape->vertex[i].ly+ytrans;
	}
}
