//
// Created by 刘隽良 on 2019/5/15.
//
#ifndef _consts_h
#define _consts_h

#include <genlib.h>

#define BLOCKSIZE 0.5

#define WIDTH 32 //Width in inches
#define HEIGHT 18 //Height in inches

#define PreX 24
#define PreY 10

#define HoldX 24
#define HoldY 2

#define LevelX 2
#define LevelY 5

#define ScoreX 2
#define ScoreY 15

#define SpeedX 2
#define SpeedY 10



#define MAINTAINER 0
#define CheckerboardFLASH 1

#define ERA 1000

#define DEBUG_SLOW 0.06
#define SLOW 0.06
#define FAST 8

#define LevelGap 2000

typedef struct  {
    int x, y;
    int type; //对应一个二维数组表示形状  int shape[][],通过矩阵变换实现旋转 0 表示空对象
    string color;
    int direction;
    double yVelocity;
    bool isPulsed;
} tetrimino;

typedef struct {
    int block[14][25];
} Checkerboard;

extern int typeInfo[][4][2];

extern string TETRI_COLOR[8];

extern Checkerboard EmptyCheckerboard;
#endif