//
// Created by 刘隽良 on 2019/5/15.
//
#ifndef _consts_h
#define _consts_h

#include <genlib.h>

#define BLOCKSIZE 0.5

#define WIDTH 32 //Width in inches
#define HEIGHT 18 //Height in inches

#define MAINTAINER 0

#define ERA 1000
//struct block{
//    int x,y;
//    string color;
//};

#define SLOW 0.08
#define FAST 0.6

typedef struct tetriminoes {
    int x, y;
    int type; //对应一个二维数组表示形状  int shape[][],通过矩阵变换实现旋转 0 表示空对象
    string color;
    int direction;
} tetrimino;

struct state {
    bool isFalling;
    bool ifKeyEvent;
    bool ifHardDrop;
    bool isTurn;
    double Velocity;
    int KeyEvent;
    int V;
} STATE;

static int typeInfo[][4][2] = { // 每种形状存进一个数组，而每个数组中包含一批二维数组（后期可以考虑状态压缩），注意每个物块其实都有4个block
    {{0, 0}, {0, 0}, {0, 0}, {0, 0}},
    {{0, -2}, {0, -1}, {0, 0}, {0, 1}}, // 0, 大长条
    {{-1, 2}, {-1, 1}, {0, 1}, {1, 1}}, // 1, L1
    {{1, 2}, {-1, 1}, {0, 1}, {1, 1}}, // 2, L2
    {{-1, 1}, {-1, 0}, {0, 0}, {0, 1}}, // 3, Square
    {{-1, 0}, {0, 0}, {0, 1}, {1, 1}}, // 4, Snake1
    {{-1, 0}, {0, 0}, {0, 1}, {1, 0}}, // 5, Up
    {{-1, 1}, {0, 1}, {0, 0}, {1, 0}}, // 6, Snack2
};

#endif