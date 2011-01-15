#include <stdio.h>
#include "main.h"
#include "basic_shape.h"
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <error.h>
#include <string.h>

#define T__ 0xffffffff
#define BORD 0x0
#define X__ 0xffff

extern v_info fb_info;
extern int draw_one_chess(int x,int y);

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
char who = 1;
char board[V_NUM*H_NUM];//to store the chessboard information
u32_t color_choice = 0x000000ff;

int save_shape(int x,int y)
{
    int i = 0;
    int j = 0;
    u32_t *p = fb_info.fb_mem;
    for(i = 0;i < C_HEIGHT; i++)
    {
        for(j = 0;j < C_WIDTH; j++)
        {
           shape_save[j +i*C_WIDTH] = p[x+j+(y+i)*fb_info.w];
        }
    }
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

int get_mouse_info(int fd,mouse_info_t * mouse_info)
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
        mouse_info->button = (buf[0]&0x07);
        mouse_info->dx = buf[1];
        mouse_info->dy = -buf[2];
        mouse_info->dz = buf[3];
    }
    return n;
}

int check_count(int x,int y)//get the relative position of x ang y 
{                           //on the board
    int i = x;              
    int j = y;
    
    i = (x - X_STARTING)/SPACE;
    j = (y - Y_STARTING)/SPACE;

    if((x - X_STARTING)%SPACE >= (SPACE/2))
    {
        i++;
    }
    if((y - Y_STARTING)%SPACE >= (SPACE/2))
    {
        j++;
    }
    board[i+j*V_NUM] = who;
    return 0;
}

int check_five(int x,int y)
{
    int i = 0;
    int j = 0;
    char storage = 0;
    char counter = 0;
    char n_x[4] = {0,1,1,1};
    char n_y[4] = {1,0,1,-1};
    char nx = 0;
    char ny = 0;

    storage = board[x+y*V_NUM];//notice there,get value on the board
                               //the first chess of the five being bo becked
    if(storage == 0)
    {
        return 0;
    }
    for(j = 0;j < 4;j++)
    {
        counter = 1;  
        nx = x;
        ny = y;
        for(i = 1;i < 5;i++)
        {
            nx += n_x[j];
            ny += n_y[j];
            if(board[nx+ny*V_NUM] == storage)  //notice  this line and the 141
            {                                   //line
                counter++;
            }
            else
            {
                break;
            }
        }
        if(counter == 5)
            return storage;//there storage is the last chess of the five 
    }
    return 0;
}

int check_all(void)
{
    int i = 0;
    int j = 0;
    for(i = 0;i < H_NUM;i++)
    {
        for(j = 0;j < V_NUM;j++)
        {
            if(check_five(j,i) != 0)
            {
                //printf("%d won!\n", who);
				return 1;
                
            }
        }
    }    
    return  0;
}

int print_choice(void)
{
    draw_circle(40,60,20,0x00ff0000);
    draw_circle(40,140,20,0x000000ff);
    return 0;
}

int mouse_doing(void)
{
    int fd = 0;
    int mx = 512;
    int my = 384;
    char victory = -1;
    mouse_info_t mouse_info;
    fd = open("/dev/input/mice",O_RDWR|O_NONBLOCK);
    if(fd < 0 )
    {
        perror("open");
        exit(1);
    }
    draw_cursor(mx,my);
    print_choice();

    while(1)
    {
        if(get_mouse_info(fd,&mouse_info) > 0)
        {
            repair_shape(mx,my);
            mx += mouse_info.dx;
            my += mouse_info.dy;

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
             draw_cursor(mx,my);

            switch(mouse_info.button)
            {
                case 1:
//printf("%d\n", event.button);                
                    repair_shape(mx, my);
                    if((draw_one_chess(mx,my)) == 0)
                    {
                        check_count(mx,my);
                        victory = check_all();
                    }
                    draw_cursor(mx, my);
                    break;
                case 2:
                    break;
                case 4:
                    break;
                default :
                    break;
            }
            if(victory == 1)
            {
                printf("Player %d won!\n",who);
                printf("Continue ? y/n \n");
                if(getchar() == '\n')
                {
                    break;
                }
                else
                {
					memset((u8_t *)fb_info.fb_mem, 0, fb_info.w*fb_info.h*fb_info.bpp/8);
					memset(board, 0, H_NUM*V_NUM);
					draw_board();
					print_choice();
					color_choice = 0x000000ff;
					who = 1;
					victory = -1;
					mx = 512;
					my = 384;
					draw_cursor(mx, my);
                }
                getchar();
            }
         }
        usleep(100);
    }
    return 0;
}
