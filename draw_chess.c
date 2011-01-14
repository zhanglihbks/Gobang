
#include <stdio.h>
#include "basic_shape.h"
#include "main.h"
extern u32_t color_choice;
extern char who;
int choose_color(int x,int y)
{
    if((x >= 20 ) && (x <= 60))
    {
        if((y >= 40) && (y <= 80))
        {
            color_choice = 0x00ff0000;
            who = 1;
        }
        
        else
            if((y >= 120) && (y <= 160))
            {
                color_choice = 0x000000ff;
                who = 2;
            }
    }
    return 0;
}

int draw_one_chess(int x,int y)
{
    int m = 0,n = 0;
    if((x < X_STARTING) || (x > (X_STARTING + (V_NUM - 1) * SPACE)))
    {
        choose_color(x,y);
        return 1;
    }
    if((y < Y_STARTING) || (y > (Y_STARTING + (H_NUM - 1) * SPACE)))
    { 
        choose_color(x,y);
        return 1;
    }
    m = (x - X_STARTING) % SPACE;
    n = (y - Y_STARTING) % SPACE;
    if(m > SPACE/2)
    {
        x = x - m + SPACE;
    }
    if(m <= SPACE/2)
    {
        x = x - m;
    }

    if(n > SPACE/2)
    {
        y = y - n + SPACE;
    }
    if(n <= SPACE/2)
    {
        y = y - n;
    }
    //if(x >= 1024||y >= 768)
    //{
        //printf("The point you input is outside the screen.\n");
        //return;
    //}
    //draw_point(x,y,0x00ff0000);
    draw_circle(x , y ,13 ,color_choice);
    return 0;
}
