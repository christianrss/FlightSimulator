#include <stdio.h>
#include <math.h>
#include "poly.h"
#include "drawpoly.h"

float matrix[4][4];
float smat[4][4];
float zmat[4][4];
float xmat[4][4];
float ymat[4][4];
float tmat[4][4];

void matmult(float result[4][4], float mat1[4][4], float mat2[4][4]);

void matcopy(float dest[4][4], float source[4][4]);

void inittrans()
{

    matrix[0][0] = 1;   matrix[0][1] = 0;   matrix[0][2] = 0;   matrix[0][3] = 0;
    matrix[1][0] = 0;   matrix[1][1] = 1;   matrix[1][2] = 0;   matrix[1][3] = 0;
    matrix[2][0] = 0;   matrix[2][1] = 0;   matrix[2][2] = 1;   matrix[2][3] = 0;
    matrix[3][0] = 0;   matrix[3][1] = 0;   matrix[3][2] = 0;   matrix[3][3] = 1;

}

void scale(float sf)
{
    float mat[4][4];

    smat[0][0] = sf;    smat[0][1] = 0;     smat[0][2] = 0;     smat[0][3] = 0;
    smat[1][0] = 0;     smat[1][1] = sf;    smat[1][2] = 0;     smat[1][3] = 0;
    smat[2][0] = 0;     smat[2][1] = 0;     smat[2][2] = sf;    smat[2][3] = 0;
    smat[3][0] = 0;     smat[3][1] = 0;     smat[3][2] = 0;     smat[3][3] = 1;
    
    matmult(mat, smat, matrix);
    matcopy(matrix, mat);
}    

void rotate(float ax, float ay, float az)
{

    float mat1[4][4];
    float mat2[4][4];

    xmat[0][0] = 1;     xmat[0][1] = 0;          xmat[0][2] = 0;          xmat[0][3] = 0;
    xmat[1][0] = 0;     xmat[1][1] = cos(ax);    xmat[1][2] = sin(ax);    xmat[1][3] = 0;
    xmat[2][0] = 0;     xmat[2][1] = -sin(ax);   xmat[2][2] = cos(ax);    xmat[2][3] = 0;
    xmat[3][0] = 0;     xmat[3][1] = 0;          xmat[3][2] = 0;          xmat[3][3] = 1;

    matmult(mat1, xmat, matrix);

    ymat[0][0] = cos(ay);   ymat[0][1] = 0;     ymat[0][2] = -sin(ay);  ymat[0][3] = 0;
    ymat[1][0] = 0;         ymat[1][1] = 1;     ymat[1][2] = 0;         ymat[1][3] = 0;
    ymat[2][0] = sin(ay);   ymat[2][1] = 0;     ymat[2][2] = cos(ay);   ymat[2][3] = 0;
    ymat[3][0] = 0;         ymat[3][1] = 0;     ymat[3][2] = 0;         ymat[3][3] = 1;

    matmult(mat2, ymat, mat1);

    zmat[0][0] = cos(az);   zmat[0][1] = sin(az);   zmat[0][2] = 0;     zmat[0][3] = 0;
    zmat[1][0] = -sin(az);  zmat[1][1] = cos(az);   zmat[1][2] = 0;     zmat[1][3] = 0;
    zmat[2][0] = 0;         zmat[2][1] = 0;         zmat[2][2] = 1;     zmat[2][3] = 0;
    zmat[3][0] = 0;         zmat[3][1] = 0;         zmat[3][2] = 0;     zmat[3][3] = 1;

    matmult(matrix, zmat, mat2);

}

void translate(int xt, int yt, int zt)
{
    float mat[4][4];

    tmat[0][0] = 1;     tmat[0][1] = 0;     tmat[0][2] = 0;     tmat[0][3] = 0;
    tmat[1][0] = 0;     tmat[1][1] = 1;     tmat[1][2] = 0;     tmat[1][3] = 0;
    tmat[2][0] = 0;     tmat[2][1] = 0;     tmat[2][2] = 1;     tmat[2][3] = 0;
    tmat[3][0] = xt;    tmat[3][1] = yt;    tmat[3][2] = zt;    tmat[3][3] = 1;

    matmult(mat, matrix, tmat);
    matcopy(matrix, mat);
}

void transform(object_type *object)
{
    for (int v = 0; v < (*object).number_of_vertices; v++)
    {
        vertex_type *vptr = &(*object).vertex[v];
        vptr->wx = vptr->lx * matrix[0][0] + vptr->ly * matrix[1][0] + vptr->lz * matrix[2][0] + matrix[3][0];

        vptr->wy = vptr->lx * matrix[0][1] + vptr->ly * matrix[1][1] + vptr->lz * matrix[2][1] + matrix[3][1];

        vptr->wz = vptr->lx * matrix[0][2] + vptr->ly * matrix[1][2] + vptr->lz * matrix[2][2] + matrix[3][2];
    }
}

void project(object_type *object, int distance)
{
    for (int v = 0; v < (*object).number_of_vertices; v++)
    {
        vertex_type *vptr = &(*object).vertex[v];
        vptr->sx = distance * vptr->wx / (distance - vptr->wz) + XORIGIN;
        vptr->sy = distance * vptr->wy / (distance - vptr->wz) + YORIGIN;
    }
}

void draw_object(object_type object, char far *screen)
{
    for (int p = 0; p < object.number_of_polygons; p++)
    {
        if (object.convex)
        {
            if (!backface(object.polygon[p])) {
                drawpoly(object.polygon[p], screen);
            }
        } else {
            drawpoly(object.polygon[p], screen);
        }
    }
}

void matmult(float result[4][4], float mat1[4][4], float mat2[4][4])
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            result[i][j] = 0;
            for (int k = 0; k < 4; k++)
                result[i][j] += mat1[i][k] * mat2[k][j];
        }
    }
}

void matcopy(float dest[4][4], float source[4][4])
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
            dest[i][j] = source[i][j];
    }
}

int backface(polygon_type p)
{
    vertex_type *v0, *v1, *v2;

    v0 = p.vertex[0];
    v1 = p.vertex[1];
    v2 = p.vertex[2];

    int z = (v1->sx - v0->sx) * (v2->sy - v0->sy) - (v1->sy - v0->sy) * (v2->sx - v0->sx);
    return (z >= 0);
}

