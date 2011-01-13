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

typedef struct
{
    int dx;
    int dy;
    int dz;
    int button;
}mouse_event;

extern int draw_point(int x,int y,u32_t color);
extern void draw_board(void); 
extern void get_potin(int x,int y);
extern void draw_circle(int x0,int y0,int r,u32_t color);
#define X_STARTING 100
#define Y_STARTING 40
#define SPACE 30
#define C_WIDTH 10
#define C_HEIGHT  17
#endif
