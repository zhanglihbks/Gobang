
#include <stdio.h>
#include "basic_shape.h"
#include "main.h"
void draw_one_chess(int x,int y)
{
    int m = 0,n = 0;
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
    if(x >= 1024||y >= 768)
    {
        printf("The point you input is outside the screen.\n");
        return;
    }
    //draw_point(x,y,0x00ff0000);
    draw_circle(x , y ,13 ,0x00ff0000);
}
