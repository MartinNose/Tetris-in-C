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


string TETRO_COLOR[8] = {
        "",//for null
        "BLUE",
        "DarkBlue",
        "Orange",
        "Yellow",
        "Green",
        "Purple",
        "Red"
};

tetromino NaT;//Not a Tetromino
tetromino generateTetromino(int type,int direction);

void timerEventHandler(int timerID);
tetromino tetriMaintainer(int time, tetromino tetri);


void Main(){
    NaT = generateTetromino(0,0); // Not a Tetro

    SetWindowTitle("Tetris");

    SetWindowSize(BLOCKSIZE*WIDTH,BLOCKSIZE*HEIGHT);
    InitGraphics();
    InitConsole();

    drawInit();
    registerTimerEvent(timerEventHandler);
    //registerMouseEvent(mouseEventHandler);
    registerKeyboardEvent(keyboardEventHandler);

    tetromino tetro = generateTetromino(1,0);
    tetriMaintainer(-1, tetro);

    registerTimerEvent(timerEventHandler);

    startTimer(MAINTAINER, 16);
}

tetromino generateTetromino(int type,int direction){
    tetromino tetro;

    tetro.x = WIDTH/2;
    tetro.y = HEIGHT;
    tetro.type = type;
    tetro.direction = direction;
    tetro.color = TETRO_COLOR[type];

    if(type){
        drawTetro(tetro);
    }
    return tetro;
}

void timerEventHandler(int timerID){
    static int time = 0;
    tetromino tetri;
    time = (time+1)%10000; // !!!
    Clean();
    drawInit();
    tetri = tetriMaintainer(time, NaT);
    drawTetro(tetri);
}

tetromino tetriMaintainer(int time, tetromino tetri){
    static int curTime = 0;
    static tetromino curTetri;
    int dt;

    if(tetri.type && time < 0){
        curTetri = tetri;
        return NaT;
    }

    if(time >= 0 && curTetri.type) {
        if (time > curTime) {
            dt = time - curTime;
        } else {
            dt = time + 1000 - curTime;
        }
        if(dt == 24){
        curTetri.y -= 1;
        curTime = time;
        }
        return curTetri;
    }
}

