#include <stdio.h>
#include "main.h"
#include "basic_shape.h"
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

#define T__ 0xffffffff
#define BORD 0x0
#define X__ 0xffff

extern v_info fb_info;
extern void draw_one_chess(int x,int y);

static u32_t cursor_pixel[C_WIDTH * C_HEIGHT]=
{
    BORD,T__,T__,T__,T__,T__,T__,T__,T__,T__,
    BORD,BORD,T__,T__,T__,T__,T__,T__,T__,T__, 
    BORD,X__,BORD,T__,T__,T__,T__,T__,T__,T__, 
    BORD,X__,X__,BORD,T__,T__,T__,T__,T__,T__, 
    BORD,X__,X__,X__,BORD,T__,T__,T__,T__,T__, 
    BORD,X__,X__,X__,X__,BORD,T__,T__,T__,T__, 
    BORD,X__,X__,X__,X__,X__,BORD,T__,T__,T__, 
    BORD,X__,X__,X__,X__,X__,X__,BORD,T__,T__, 
    BORD,X__,X__,X__,X__,X__,X__,X__,BORD,T__, 
    BORD,X__,X__,X__,X__,X__,X__,X__,X__,BORD, 
    BORD,X__,X__,X__,X__,X__,BORD,BORD,BORD,BORD, 
    BORD,X__,X__,BORD,X__,X__,BORD,T__,T__,T__, 
    BORD,X__,BORD,T__,BORD,X__,X__,BORD,T__,T__, 
    BORD,BORD,T__,T__,BORD,X__,X__,BORD,T__,T__, 
    T__,T__,T__,T__,T__,BORD,X__,X__,BORD,T__, 
    T__,T__,T__,T__,T__,BORD,X__,X__,BORD,T__, 
    T__,T__,T__,T__,T__,T__,BORD,BORD,T__,T__ 
};

static u32_t shape_save[C_WIDTH * C_HEIGHT];

int save_shape(int x,int y)
{
    int i = 0;
    int j = 0;
    u32_t *p = fb_info.fb_men;
    for(i = 0;i < C_HEIGHT; i++)
        for(j = 0;j < C_WIDTH; j++)
            shape_save[j +i*C_WIDTH] = p[x+j+(y+i)*fb_info.w];
    return 0;
}
int repair_shape(int x,int y)
{
    int i = 0;
    int j = 0;
    for(i = 0;i < C_HEIGHT;i++)
    {
        for(j = 0;j < C_WIDTH;j++)
        {
            draw_point(x+j,y+i,shape_save[j+i*C_WIDTH]);
        }
    }
    return 0;
}

int draw_cursor(int x,int y)
{
    int i = 0;
    int j = 0;

    save_shape(x,y);
    for(i = 0;i < C_HEIGHT; i++)
    {
        for(j = 0;j < C_WIDTH; j++)
        {
            draw_point(x+j,y+i,cursor_pixel[j+C_WIDTH*i]);
        }
    }
    return 0;
}

int get_mouse_info(int fd,mouse_event * event)
{
    char buf[8] = {0};
    int n = 0;
    
    n = read(fd,buf,8);
    if(n <= 0 )
    {
        return 0;
    }
    else
    {
        event->button = (buf[0]&0x07);
        event->dx = buf[1];
        event->dy = buf[2];
        event->dz = buf[3];
    }
    return 0;
}

int mouse_doing(void)
{
    int fd = 0;
    int mx = 512;
    int my = 384;
    mouse_event *event = NULL;
    fd = open("/dev/input/mice",O_RDWR|O_NONBLOCK);
    if(fd < 0 )
    {
        perror("open");
        exit(1);
    }
    draw_cursor(mx,my);

    while(1)
    {
        if((get_mouse_info(fd,event) > 0))
        {
            repair_shape(mx,my);
            mx = event->dx;
            my = event->dy;
            mx = (mx >= 0) ? mx:0;
            my = (my >= 0) ? my:0;
            
            if(mx >= (fb_info.w - C_WIDTH))
            {
                mx = fb_info.w - C_WIDTH;
            }

            if(my >= (fb_info.h - C_HEIGHT))
            {
                my = fb_info.h - C_HEIGHT;
            }
            
            switch(event->button)
            {
                case 1:
                    draw_one_chess(mx,my);
                    save_shape(mx,my);
                    break;
                case 2:
                    break;
                case 3:
                    break;
                default :
                    break;
            }
            draw_cursor(mx,my);
        }
        usleep(100);
    }
    return 0;
}
