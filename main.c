#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <errno.h>
#include "main.h"
#include "basic_shape.h"
#include "mouse_shape.h"   
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

    fb_info.fb_mem = p; 
    close(fd);
} 

void scan_screen(void)
{
    int i,j;
    u32_t *p = NULL;
    p = fb_info.fb_mem;
    for(i = 0;i < fb_info.h;i++)
    {
        for(j = 0;j < fb_info.w;j++)
        {
           p[i*fb_info.w+j]  = 0x000000ff;
        }
    }
}


int main(void) 
{
    create_scr_fb();
    draw_board();
    //mouse_doing();
    return 0; 
}
