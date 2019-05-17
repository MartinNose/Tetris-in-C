//
// Created by Tao Chiang on 5/17/2019.
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
#include <math.h>

#include <windows.h>
#include <olectl.h>
#include <mmsystem.h>
#include <wingdi.h>
#include <ole2.h>
#include <ocidl.h>
#include <winuser.h>

#include "model.h"
#include "consts.h"
#include "drawers.h"


static string TETRI_COLOR[8] = {
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
            STATE.isTurn = FALSE;
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
    static double dy = 0;
    int dt ;


    if (time > curTime)
    {
        dt = (time - curTime);
    } else
    {
        dt = (time + ERA - curTime);
    }

    dy += STATE.Velocity * dt;
    if(dy >= 1) {
        tetri.y -= 1;
        dy = 0;
    }//printf("%d\n",dt);

    curTime = time;
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
    STATE.Velocity = SLOW;
    STATE.ifHardDrop = FALSE;
    STATE.isTurn     = FALSE;
}
