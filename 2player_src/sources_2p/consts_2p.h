#ifndef _consts_2p_h
#define _consts_2p_h

#include <genlib.h>

#define WIDTH 30 //Width in inches
#define HEIGHT 18 //Height in inches
#define LEFTBAR 3 //Left Bar Width

#define LEFT 0
#define RIGHT 1

#define KEEP 2

#define GAME 0
#define CheckerboardFLASH 1
#define GAMEOVER 2
#define DEBUG 3
#define LOADING 4

#define ERA 1000

#define INIT_SPEED 0.07
#define SLOW 0.06
#define FAST 8

#define LevelGap 10000

#define PAUSE 0

#define USERNAMELONG 16
typedef struct {
    int block[14][25];
    int x;
    int position;
} Checkerboard;

typedef struct  {
    int x, y;
    int type; //对应一个二维数组表示形状  int shape[][],通过矩阵变换实现旋转 0 表示空对象
//    string color;
    int direction;
    double yVelocity;
    bool isPaused;
    int position;
} tetrimino;


extern int typeInfo[][4][2];

extern string TETRI_COLOR[8];

extern char *const BGM_Path;

extern double BLOCKSIZE;

#endif