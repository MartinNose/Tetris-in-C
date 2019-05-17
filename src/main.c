//
// Created by liujunliang on 2019/5/13.
//

#include "drawers.h"
#include "consts.h"

tetrimino NaT;//Not a Tetrimino
//tetrimino CurrentTetri;

#include "model.h"
#include "handlers.h"

void Main ()
{
    NaT = generateTetrimino (0, 0); // Not a Tetri

    SetWindowTitle ("Tetris");

    SetWindowSize (BLOCKSIZE * WIDTH, BLOCKSIZE * HEIGHT);
    InitGraphics ();
    InitConsole ();

    InitState ();
    drawInit ();

    registerTimerEvent (timerEventHandler);
    //registerMouseEvent(mouseEventHandler);
    registerKeyboardEvent (keyboardEventHandler);

    registerTimerEvent (timerEventHandler);

    startTimer (MAINTAINER, 16);
}

