//
// Created by liujunliang on 2019/5/13.
//
#include "graphics.h"
#include "extgraph.h"
#include "genlib.h"
#include "simpio.h"
#include "conio.h"
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

#include <windows.h>
#include <olectl.h>
#include <mmsystem.h>
#include <wingdi.h>
#include <ole2.h>
#include <ocidl.h>
#include <winuser.h>

#include "handlers.c"
#include "drawers.c"
#include "consts.c"


void timerEventHandler(int timerID);
void tetroMaitainer(int time,tetromino tetro);

tetromino generateTetromino(int type,int direction);


void Main(){
    NaT = generateTetromino((int)NULL,0);

    SetWindowTitle("Tetris");

    SetWindowSize(BLOCKSIZE*WIDTH,BLOCKSIZE*HEIGHT);
    InitGraphics();
    InitConsole();

    registerTimerEvent(timerEventHandler);
    registerMouseEvent(mouseEventHandler);
    registerMouseEvent(mouseEventHandler);


    for(int i = 0 ; i < 10 ;i++){
        for(int j=0;j < HEIGHT;j++){
            drawBlock(i,j,"Gray");
        }
    }
    for(int i = 10 ; i < 20 ;i++){
        for(int j=0;j < HEIGHT;j++){
            drawBlock(i,j,"White");
        }
    }
    for(int i = 20 ; i < 30 ;i++){
        for(int j=0;j < HEIGHT;j++){
            drawBlock(i,j,"Gray");
        }
    }
    tetromino tetro = generateTetromino(1,0);

    tetroMaitainer(-1,tetro);

    registerTimerEvent(timerEventHandler);

    startTimer(MAINTAINER, 16);
}

tetromino generateTetromino(int type,int direction){
    tetromino tetro;

    tetro.x = (int)0.5*WIDTH;
    tetro.y = (int)HEIGHT;
    tetro.type = type;
    tetro.direction = direction;
    tetro.color = COLOR[type];

    return tetro;
}



void timerEventHandler(int timerID){
    static int time = 0;
    time = (time+1)%10000; // !!!
    tetroMaitainer(time,NaT);
}

void tetroMaitainer(int time, tetromino tetro){
    static int curtime = 0;
    static tetromino curTetro;
    int dt;
    if(time>=0) {
        if (time > curtime) {
            dt = time - curtime;
        } else {
            dt = time + 1000 - curtime;
        }
    }
    if(tetro.type){
        curTetro = tetro;
        return;
    }

    tetro.x -= dt/10;
    drawTetro(tetro);


    curtime = time;
}
