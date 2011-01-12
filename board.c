#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include <string.h>

#define X_STARTING 100
#define Y_STARTING 40
#define SPACE 30

extern v_info fb_info;
extern  void draw_line(int x1,int y1,int x2,int y2,u32_t color);

void draw_board(void)
{
    int i,j; 
    for(i=0;i<fb_info.w;i++)
    {
        for(j = 0;j < fb_info.h;j++)
        {
            draw_point(i,j,0x00ff0000);
        }
    }

    for(i = 0;i <H_NUM;i++)
    {
        draw_line(X_STARTING,Y_STARTING+i*SPACE,X_STARTING+(V_NUM - 1)*SPACE,Y_STARTING+i*SPACE,0x000000ff);
    }

    for(i = 0;i < V_NUM;i++)
    {
        draw_line(X_STARTING+i*SPACE,Y_STARTING,X_STARTING+i*SPACE,Y_STARTING+(H_NUM-1)*SPACE,0x000000ff);
    }
}
