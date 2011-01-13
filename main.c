#include <stdio.h>
#include <unistd.h>
//#include <string.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <errno.h>
#include "main.h"
#include "basic_shape.h"
#include "mouse_shape.h"   
//extern void get_point(int x,int y);
//extern void draw_circle(int x0,int y0,int r,u32_t color);
extern void draw_one_chess(int x,int y);

v_info fb_info;

void create_scr_fb(void)
{
    struct fb_var_screeninfo fb_var;
    u32_t *p = NULL;
    int fd;
    fd = open("/dev/fb0",O_RDWR);

    if(fd < 0)
    {
        perror("open");
        exit(1);
    }

    if((ioctl(fd,FBIOGET_VSCREENINFO,&fb_var) <  0))
    {
        perror("ioctl");
        exit(1);
    }
    
    fb_info.w = fb_var.xres;
    fb_info.h = fb_var.yres;
    fb_info.bpp = fb_var.bits_per_pixel;

    printf("w = %d\t,h = %d\t,pixel = %d\n",fb_info.w,fb_info.h,fb_info.bpp);
    p = mmap(NULL,fb_info.w*fb_info.h*fb_info.bpp/8,PROT_WRITE|PROT_READ,MAP_SHARED,fd,0);

    if( p == MAP_FAILED)
    {
        perror("map");
        exit(1);
    } 

    fb_info.fb_men = p; 
    close(fd);
} 

void scan_screen(void)
{
    int i,j;
    u32_t *p = NULL;
    p = fb_info.fb_men;
    for(i = 0;i < fb_info.h;i++)
    {
        for(j = 0;j < fb_info.w;j++)
        {
           p[i*fb_info.w+j]  = 0x000000ff;
        }
    }
}

//int draw_point(int x,int y,u32_t color)
//{
    //u32_t *p = NULL;
    //p = fb_info.fb_men;
    //p[x+fb_info.w*y] = color;
    //return 0;
//}

int main(void) 
{
    int x = 0,y = 0;
    create_scr_fb();
    //scan_screen();
    //scan_line();
    //draw_line(400,767,0,0,0x000000ff);
    //draw_line(256,192,768,576,0x000000ff);
    draw_board();
    #if 0
    while(1)
    {
        printf("please input the location of the point:\n");
        scanf("%d %d",&x,&y);
        draw_one_chess(x,y);
    }
    #endif
    mouse_doing();
        //repair_shape(120,100);
    return 0; 
}
