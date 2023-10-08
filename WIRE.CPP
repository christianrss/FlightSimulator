#include <stdio.h>
#include <math.h>
#include "bresnham.h"
#include "wire.h"

float matrix[4][4];
float smat[4][4];
float zmat[4][4];
float xmat[4][4];
float ymat[4][4];
float tmat[4][4];

void inittrans()
{
	// Inicia a transformacao da matriz mestra para a matriz de identidade
	matrix[0][0] = 1; matrix[0][1] = 0; matrix[0][2] = 0; matrix[0][3] = 0;
	matrix[1][0] = 0; matrix[1][1] = 1; matrix[1][2] = 0; matrix[1][3] = 0;
	matrix[2][0] = 0; matrix[2][1] = 0; matrix[2][2] = 1; matrix[2][3] = 0;
	matrix[3][0] = 0; matrix[3][1] = 0; matrix[3][2] = 0; matrix[3][3] = 1;
}

void project(shape_type *shape, int distance)
{
	for (int v = 0; v < (*shape).number_of_vertices; v++)
	{
		vertex_type *vptr = &(*shape).vertex[v];
		vptr->sx = distance * vptr->wx / vptr->wz;
		vptr->sy = distance * vptr->wy / vptr->wz;
	}
}

void matmult(float result[4][4], float mat1[4][4],
	float mat2[4][4])
{
	for(int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			result[i][j] = 0;
			for (int k=0; k < 4; k++)
				result[i][j] += mat1[i][k] * mat2[k][j];
		}
	}
}

void matcopy(float dest[4][4], float source[4][4])
{
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			dest[i][j] = source[i][j];
}

void scale(float sf)
{
	float mat[4][4];

	smat[0][0] = sf; smat[0][1] = 0;  smat[0][2] = 0;  smat[0][3] = 0;
	smat[1][0] = 0;  smat[1][1] = sf; smat[1][2] = 0;  smat[1][3] = 0;
	smat[2][0] = 0;  smat[2][1] = 0;  smat[2][2] = sf; smat[2][3] = 0;
	smat[3][0] = 0;  smat[3][1] = 0;  smat[3][2] = 0;  smat[3][3] = 1;

	matmult(mat, smat, matrix);
	matcopy(matrix, mat);
}

void translate(int xt, int yt, int zt)
{
	// Cria uma matriz de translacao que desloca um objeto de uma
	// distancia XT em X, uma distancia YT em Y e uma distancia
	// ZT em Z a partir da origem da tela
	float mat[4][4];

	tmat[0][0] = 1;  tmat[0][1] = 0;  tmat[0][2] = 0; tmat[0][3] = 0;
	tmat[1][0] = 0;  tmat[1][1] = 1;  tmat[1][2] = 0; tmat[1][3] = 0;

	tmat[2][0] = 0;  tmat[2][1] = 0;  tmat[2][2] = 1;  tmat[2][3] = 0;
	tmat[3][0] = xt; tmat[3][1] = yt; tmat[3][2] = zt; tmat[3][3] = 1;

	// concatenar com a matriz mestra
	matmult(mat, matrix, tmat);
	matcopy(matrix, mat);
}

void rotate(float ax, float ay, float az)
{
	// Cria tres matrizes de rotacao que vao rotacionar
	// um objeto de AX radianos no eixo X, AY radianos no eixo Y
	// e AZ radianos no eixo z

	float mat1[4][4];
	float mat2[4][4];

	xmat[0][0] = 1; xmat[0][1] = 0; 		xmat[0][2] = 0; 		xmat[0][3] = 0;
	xmat[1][0] = 0; xmat[1][1] =  cos(ax);  xmat[1][2] = sin(ax);   xmat[1][3] = 0;
	xmat[2][0] = 0; xmat[2][1] = -sin(ax);  xmat[2][2] = cos(ax);	xmat[2][3] = 0;
	xmat[3][0] = 0; xmat[3][1] = 0; 		xmat[3][2] = 0;			xmat[3][3] = 1;

	matmult(mat1, xmat, matrix);

	ymat[0][0] = cos(ay); ymat[0][1] = 0; ymat[0][2] = -sin(ay); ymat[0][3] = 0;
	ymat[1][0] = 0; 	  ymat[1][1] = 1; ymat[1][2] = 0;		 ymat[1][3] = 0;
	ymat[2][0] = sin(ay); ymat[2][1] = 0; ymat[2][2] = cos(ay);  ymat[2][3] = 0;
	ymat[3][0] = 0;		  ymat[3][1] = 0; ymat[3][2] = 0;	     ymat[3][3] = 1;

	matmult(mat2, ymat, mat1);

	zmat[0][0] = cos(az); zmat[0][1] = sin(az); zmat[0][2] = 0; zmat[0][3] = 0;
	zmat[1][0] = -sin(az);zmat[1][1] = cos(az); zmat[1][2] = 0; zmat[1][3] = 0;
	zmat[2][0] = 0;       zmat[2][1] = 0;		zmat[2][2] = 1; zmat[2][3] = 1;
	zmat[3][0] = 0;       zmat[3][1] = 0;    	zmat[3][2] = 0; zmat[3][3] = 1;

	matmult(matrix, zmat, mat2);
}

void transform(shape_type * shape)
{
	// multiplicar todos os vertices de SHAPE pela matriz mestra de transformacao

	for (int v = 0; v < (*shape).number_of_vertices; v++)
	{
		vertex_type *vptr = &(*shape).vertex[v];
		vptr->wx = vptr->lx * matrix[0][0] + vptr->ly * matrix[1][0]
			+ vptr->lz * matrix[2][0] + matrix[3][0];

		vptr->wy = vptr->lx * matrix[0][1] + vptr->ly * matrix[1][1]
			+ vptr->lz * matrix[2][1] + matrix[3][1];

		vptr->wz = vptr->lx * matrix[0][2] + vptr->ly * matrix[1][2]
			+ vptr->lz * matrix[2][2] + matrix[3][2];
	}
}

void draw_shape(shape_type shape, char far *screen)
{
	 for(int i = 0; i < shape.number_of_lines; i++)
	 {
		linedraw(
			shape.vertex[shape.line[i].start].sx + XORIGIN,
			shape.vertex[shape.line[i].start].sy + YORIGIN,
			shape.vertex[shape.line[i].end].sx   + XORIGIN,
			shape.vertex[shape.line[i].end].sy   + YORIGIN,
			shape.color,
			screen
		);
	 }
}
