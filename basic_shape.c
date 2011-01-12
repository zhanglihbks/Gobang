#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "main.h"

void swap(int *a,int *b)
{
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

void draw_line(int x1,int y1,int x2,int y2,u32_t color)
{
    int dx = x2 - x1;
    int dy = y2 - y1;
    //int p = 2*dy - dx;
    int inc = ((dx * dy > 0) ? 1:-1);
    //dy = abs(dy);    
    //int p = 2*dy - dx;
    if(abs(dx) > abs(dy))
    {
        if(dx < 0)
        {
            swap(&x1,&x2);
            swap(&y1,&y2);
            dx=-dx;
            dy=-dy;
        }
        dy = abs(dy);    
        int p = 2*dy - dx;
        while(x1 <= x2)
        {
            draw_point(x1,y1,color);
            x1++;
            if(p < 0)
            {
                p+=2*dy;
            }
            else
            {
                p+=2*(dy-dx);
                y1+=inc;
            }
        }
    }
    else
    {
        if(dy < 0)
        {
            swap(&x1,&x2);
            swap(&y1,&y2);
            dx=-dx;
            dy=-dy;
        }
        dx = abs(dx);    
        int p = 2*dx- dy;
        while(y1 <= y2)
        {
            draw_point(x1,y1,color);
            y1++;
            if(p < 0)
            {
                p+=2*dx;
            }
            else
            {
                p+=2*(dx-dy);
                x1+=inc;
            }
        }
    }
}

