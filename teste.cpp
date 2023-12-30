#include <stdio.h>
#include <dos.h>
#include <mem.h>
#include "poly.h"
#include "drawpoly.h"

void drawpoly(polygon_type *polygon, unsigned char far *screen_buffer)
{

    int ydiff1, ydiff2,

    start,
    length,
    errorterm1, errorterm2,
    offset1, offset2,
    count1, count2,
    xunit1, xunit2;

    int edgecount = polygon->number_of_vertices-1;

    int firstvert = 0;
    int min_amt = polygon->vertex[0]->sy;

    for (int i = 0; i < polygon->number_of_vertices; i++)
    {
        if (polygon->vertex[i]->sy < min_amt) {
            firstvert = i;
            min_amt = polygon->vertex[i]->sy;
        }
    }

    int startvert1 = firstvert;
    int startvert2 = firstvert;

    int xstart1 = polygon->vertex[startvert1]->sx;
    int ystart1 = polygon->vertex[startvert1]->sy;
    int ystart2 = polygon->vertex[startvert2]->sx;
    int ystart2 = polygon->vertex[startvert2]->sy;

    int endvert1 = startvert1 - 1;

    if (endvert1 < 0) endvert1 = polygon.number_of_vertices - 1;

    int xend1 = polygon->vertex[endvert1]->sx;
    int yend1 = polygon->vertex[endvert1]->sy;
    int endvert2 = startvert2 + 1;

    if (endvert2 == (polygon->number_of_vertices)) endvert2 = 0;

    int xend2 = polygon->vertex[endvert2]->sx;
    int yend2 = polygon->vertex[endvert2]->sy;

    while (edgecount > 0)
    {
        offset1 = 320 * ystart1 + xstart1 + FP_OFF(screen_buffer);

        offset2 = 320 * ystart2 + xstart2 + FP_OFF(screen_buffer);

        errorterm1 = 0;
        errorterm2 = 0;

        if ((ydiff  = yend1 - ystart1) < 0) ydiff1 = -ydiff1;
        if ((ydiff2 = yend2 - ystart2) < 0) ydiff2 = -ydiff2;

        if ((xdiff1 = xend1 - xstart1) < 0)
        {
            xunit1 = -1;
            xdiff1 = -xdiff1;
        }
        else {
            xunit1 = 1;
        }

        if ((xdiff2 = xend2 - xstart2) < 0)
        {
            xunit2 = -1;
            xdiff2 = -xdiff2;
        }
        else {
            xunit2 = 1;
        }

        if (xdiff1 > ydiff1)
        {
            if (xdiff2 > ydiff2)
            {
                count1 = xdiff1;
                count2 = xdiff2;

                while (count1 && count2)
                {
                    while ((erroterm1 < xdiff1) && (count1 > 0))
                    {
                        if (count--)
                        {
                            offset1 += xunit1;
                            xstart1 += xunit1;
                        }
                        erroterm1 += ydiff1;

                        if (erroterm1 < xdiff1)
                        {
                            screen_buffer[offset1] = polygon->color;
                        }

                    }

                }

                errorterm1 -= xdiff1;

                while ((errorterm2 < xdiff2) && (count2 > 0))
                {
                    if (count2--)
                    {
                        offset2 += xunit2;
                        xstart2 += xunit2;
                    }

                    errorterm2 += ydiff2;
                    if (erroterm2 < xdiff2)
                    {
                        screen_buffer[offset2] = polygon->color;
                    }
                }

                errorterm2 -= xdiff2;

                length = offset2 - offset1;
                if (length < 0)
                {
                    length = - length;
                    start = offset2;
                }
                else start = offset1;

                for (int i = start; i < start + length + 1; i++)
                    screen_buffer[i] = polygon->color;

                offset1 += 320;
                ystart1++;
                offset2 += 320;
                ystart2++;
            }
        }
        else {
            count1 = xdiff1;
            count2 = ydiff2;

            while (count1 && count2)
            {
                while ((errorterm1 < xdiff1) && (count1 > 0))
                {
                    if (count--)
                    {
                        offset1 += xunit1;
                        xstart1 += xunit1;
                    }

                    errorterm1 += ydiff1;
                    if (erroterm1 < xdiff1)
                    {
                        screen_buffer[offset1] = polygon->color;
                    }
                }
                errorterm1 -= xdiff1;

                erroterm2 += xdiff2;

                if (errorterm2 >= ydiff2)
                {
                    errorterm2 -= ydiff2;
                    offset2 += xunit2;
                    xstart2 += xunit2;
                }
                --count2;

                length = offset2 - offset1;
                if (length < 0)
                {
                    length = -length;
                    start = offset2;
                }
                else start = offset1;

                for (int i = start; i < start + length + 1; i++)
                    screen_buffer[i] = polygon->color;

                offset1 += 320;
                ystart1++;
                offset2 += 320;
                ystart2++;
            }
        }
    } else {
        if (xdiff2 > ydiff2)
        {
            count1 = ydiff1;
            count2 = xdiff2;

            while (count1 && count2)
            {
                erroterm1 += xdiff1;

                if (errorterm1 >= ydiff1)
                {
                    erroterm1 -= ydiff1;
                    offset1 += xunit1;
                    xstart1 += xunit1;
                }
                --count1;

                while((errorterm2 < xdiff2) && (count2 > 0))
                {
                    if (count2--)
                    {
                        offset2 += xunit2;
                        xstart2 += xunit2;
                    }
                    erroterm2 += ydiff2;
                    if (erroterm2 < xdiff2)
                    {
                        screen_buffer[offset2] = polygon.color;
                    }
                }
                erroterm2 -= xdiff2;

                length = offset2 - offset1;

                if (length < 0)
                {
                    length = -length;
                    start = offset2;
                }
                else start = offset1;

                for (int i = start; i < start + length + 1; i++
                    screen_buffer[i] = polygon->color;
                
                offset1 += 320;
                ystart1++;
                offset2 += 320;
                ystart2++;
            }
        } else {
            count1 = ydiff1;
            count2 = ydiff2;
            while (count1 && count2)
            {
                errorterm1 += xdiff1;

                if (errorterm1 >= ydiff1)
                {
                    errorterm1 -= ydiff1;
                    offset1 += xunit1;
                    xstart1 += xunit1;
                }
                --count1;
                erroterm2 += xdiff2;

                if (errorterm2 >= ydiff2)
                {
                    errorterm2 -= ydiff2;
                    offset += xunit2;
                    xstart2 += xunit2;
                }
                --count2;

                length = offset2 - offset1;

                if (length < 0)
                {
                    length = -length;
                    start = offset2;
                }
                else start = offset1;

                for (int i = start; i < start + length + 1; i++)
                    screen_buffer[i] = polygon->color;
                
                offset1 += 320;
                ystart1++;

                offset2 += 320;
                ystart2++;
            }
        }
    }

    if (!count1)
    {
        --edgecount;
        startvert1 = endvert1;

        --endvert1;

        if (endvert1 < 0)
            endvert1 = polygon->number_of_vertices - 1;

        xend1 = polygon->vertex[endvert1]->sx;

        yend1 = polygon->vertex[endvert1]->sy;
    }

    if (!count2) {
        --edgecount;
        startvert2 = endvert2;
        endvert2++;

        if (endvert2 == (polygon->number_of_vertices))
            endvert2 = 0;

        xend2 = polygon->vertex[endvert2]->sx;
        yend2 = polygon->vertex[endvert2]->sy;
    }

}


                    



