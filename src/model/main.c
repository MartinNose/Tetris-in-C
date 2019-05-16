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

string TETRI_COLOR[8] = {
    "White",//for null
//    "BLUE",
    "Magenta",
//    "DarkBlue",
    "Blue",
//    "Orange",
    "Cyan",
    "Yellow",
    "Green",
    "Cyan",
    "Red"
};

tetrimino NaT;//Not a Tetrimino
tetrimino CurrentTetri;
tetrimino generateTetrimino (int type, int direction);

void timerEventHandler (int timerID);
tetrimino tetriMaintainer_on_gravity (int time, tetrimino tetri);
tetrimino tetriRandom();

void Main ()
{
    NaT = generateTetrimino (0, 0); // Not a Tetri

    SetWindowTitle ("Tetris");

    SetWindowSize (BLOCKSIZE * WIDTH, BLOCKSIZE * HEIGHT);
    InitGraphics ();
    InitConsole ();

    drawInit ();
    registerTimerEvent (timerEventHandler);
    //registerMouseEvent(mouseEventHandler);
    //registerKeyboardEvent(keyboardEventHandler);

    CurrentTetri = generateTetrimino (5, 3);
    tetriMaintainer_on_gravity (-1, CurrentTetri);

    registerTimerEvent (timerEventHandler);

    startTimer (MAINTAINER, 16);
}

tetrimino generateTetrimino (int type, int direction)
{
    tetrimino tetri;

    tetri.x = WIDTH / 2;
    tetri.y = HEIGHT;
    tetri.type = type;
    tetri.direction = direction;
    tetri.color = TETRI_COLOR[type];

    if (type) {
        drawTetri (tetri);
    }
    return tetri;
}

void timerEventHandler (int timerID)
{
    static int time = 0;
    tetrimino tetri;
    time = (time + 1) % 10000; // !!!
    Clean ();
    drawInit ();
    CurrentTetri= tetriMaintainer_on_gravity (time, NaT);
    drawTetri (CurrentTetri);
}

tetrimino tetriMaintainer_on_gravity (int time, tetrimino tetri)
{
    static int curTime = 0;
    static tetrimino curTetri;
    int dt;

    // Setting the current tetrimino in this function
    if (tetri.type && time < 0) {
        curTetri = tetri;
        return NaT;
    }

    if (time >= 0 && curTetri.type) {
        if (time > curTime) {
            dt = time - curTime;
        } else {
            dt = time + 1000 - curTime;
        }
        if (dt == 24) {
            curTetri.y -= 1;
            curTime = time;
        }
        return curTetri;
    }
}
tetrimino tetriRandom ()
{
    tetrimino NewTetrimino;
    int type = rand()%7;
    if(type == 0)type = 7;
    int direction = rand()%4;
    return generateTetrimino (type , direction);
}

