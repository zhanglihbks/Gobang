#ifndef _MAIN_H
#define _MAIN_H

#define H_NUM 24
#define V_NUM 30

typedef unsigned int u32_t;
typedef unsigned char u8_t;

typedef struct
{
    int w;
    int h;
    int bpp;
    void *fb_men;
}v_info;
extern int draw_point(int x,int y,u32_t color);
extern void draw_board(void); 
#endif
