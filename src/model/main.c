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
//tetrimino CurrentTetri;

void InitState();

tetrimino generateTetrimino (int type, int direction);

void timerEventHandler (int timerID);
tetrimino tetriMaintainer_on_gravity (int time, tetrimino tetri);
tetrimino tetriMaintainer_on_Keyboard(int RL,   tetrimino tetri);
tetrimino tetriRandom();

#include "handlers.c"

void Main ()
{
    NaT = generateTetrimino (0, 0); // Not a Tetri

    SetWindowTitle ("Tetris");

    SetWindowSize (BLOCKSIZE * WIDTH, BLOCKSIZE * HEIGHT);
    InitGraphics ();
    InitConsole ();

    InitState();
    drawInit ();

    registerTimerEvent (timerEventHandler);
    //registerMouseEvent(mouseEventHandler);
    registerKeyboardEvent(keyboardEventHandler);



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
    static tetrimino tetri;
    if (!STATE.isFalling) {
        tetri = tetriRandom ();
        tetriMaintainer_on_gravity (time, tetri);
        STATE.isFalling = TRUE;
    }else{
        if( tetri.y < 0)
        {
            STATE.isFalling = FALSE;
        }
    }

    time = (time + 1) % ERA; // !!!
    Clean ();
    drawInit ();

    tetri = tetriMaintainer_on_gravity (time, tetri);
    if (STATE.ifKeyEvent){
        tetri = tetriMaintainer_on_Keyboard(STATE.KeyEvent,tetri);
        STATE.ifKeyEvent = FALSE;
    };

    drawTetri (tetri);
}
tetrimino tetriMaintainer_on_Keyboard(int RL,tetrimino tetri)
{
    switch ( RL ) {
        case VK_RIGHT:
            tetri.x += 1;
            break;
        case VK_LEFT:
            tetri.x -= 1;
            break;
        case VK_UP :
            tetri.direction++;
            tetri.direction %= 4;
            break;
            //case VK_UP:
            //case VK_DOWN:
            //case VK_SPACE:
            //case
        default:
            break;
    }
    if(tetri.x<0){
        tetri.x = 32 + tetri.x;
    }
    tetri.x = tetri.x  % WIDTH;
    return tetri;
}
tetrimino tetriMaintainer_on_gravity (int time, tetrimino tetri)
{
    static int curTime = 0;
    int dt,v;
    v = STATE.V;
    if (time > curTime)
    {
        dt = time - curTime;
    } else
    {
        dt = time + ERA - curTime;
    }
    if(STATE.isSoftDrop)
    {
        tetri.y -= v*dt;
        curTime = time;
        return tetri;
    }
    else
    {
        if (dt == 24)
        {
            tetri.y -= v;
            curTime = time;
        }
    }
    return tetri;
}

tetrimino tetriRandom ()
{
    static int last = 0;
    int type ;
    do {
        type = rand() % 7;
        if (type == 0) type = 7;
    }while(last == type);
    last = type;
    int direction = rand()%4;
    return generateTetrimino (type , direction);
}

void InitState()
{
    STATE.isFalling = FALSE;
    STATE.ifKeyEvent = FALSE;
    STATE.V = 1;
    STATE.isSoftDrop = FALSE;
    STATE.ifHardDrop = FALSE;
    STATE.isTurn     = FALSE;
}
