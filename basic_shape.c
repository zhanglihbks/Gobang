#include <stdio.h>
#include <stdlib.h>
//#include <string.h>
#include <math.h>
#include "main.h"

extern v_info fb_info; 
void swap(int *a,int *b)
{
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

int draw_point(int x,int y,u32_t color)
{
    u32_t *p = NULL;
    p = fb_info.fb_men;
    p[x+fb_info.w*y] = color;
    return 0;
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

void draw_circle(int x0,int y0,int r,u32_t color)
{
    int x = 0;
    int y = r;
    int p = 3-2*r;
    while(x <= y)
    {
    #if 0
        draw_point(x0 + x , y0 + y , 0x00ff0000);
        draw_point(x0 + y , y0 + x , 0x00ff0000);
        draw_point(x0 + x , y0 - y , 0x00ff0000);
        draw_point(x0 + y , y0 - x , 0x00ff0000);
        draw_point(x0 - x , y0 + y , 0x00ff0000);
        draw_point(x0 - y , y0 + x , 0x00ff0000);
        draw_point(x0 - x , y0 - y , 0x00ff0000);
        draw_point(x0 - y , y0 - x , 0x00ff0000);

        draw_point(x0 + x , y0 + y , color);
        draw_point(x0 + y , y0 + x , color);
        draw_point(x0 + x , y0 - y , color);
        draw_point(x0 + y , y0 - x , color);
        draw_point(x0 - x , y0 + y , color);
        draw_point(x0 - y , y0 + x , color);
        draw_point(x0 - x , y0 - y , color);
        draw_point(x0 - y , y0 - x , color);
     #endif

        draw_line(x0 + x , y0 + y , x0 - x , y0 + y , color);
        draw_line(x0 + y , y0 + x , x0 - y , y0 + x , color);
        draw_line(x0 + x , y0 - y , x0 - x , y0 - y , color);
        draw_line(x0 + y , y0 - x , x0 - y , y0 - x , color);
     
        if(p < 0)
        {
            p += 4 * x + 6;
        }
        else
        {
            p +=  4 * (x - y) + 10;
            y--;
        }
        x++;
    }

}
