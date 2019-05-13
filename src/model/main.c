//
// Created by liujunliang on 2019/5/13.
//
#include"graphics.h"
#include"handlers.c"
#include "drawers.c"

void Main(){
    SetWindowTitle("Tetris");
    InitGraphics();
    InitConsole();
    double x,y;
    x = GetWindowWidth();
    y = GetWindowHeight();
    for(int i=0; i < x;i++){
        for(int j=0;j < y;j++){
            drawBlock(i,j,1.0,1.0);
        }
    }
}
