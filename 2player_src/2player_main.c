//
// Created by liujunliang on 2019/5/13.
//

#include <time.h>
#include "graphics.h"

#include "consts_2p.h"
#include "model_2p.h"
#include "drawers_2p.h"



//#include "handlers.h"


tetrimino NaT;//Not a Tetrimino
//tetrimino CurrentTetri;

void Main ()
{
    NaT = generateTetrimino (0, 0,0);// Not a Tetri
//    que[0] = que[1] = NaT;
    SetWindowTitle ("Tetris");

    SetWindowSize (BLOCKSIZE * WIDTH, BLOCKSIZE * HEIGHT);
    InitGraphics ();
    //InitConsole ();

//    DefineColors();
    InitModel ();
    drawUI();
    srand((unsigned)time(NULL));

    registerTimerEvent (timerEventHandler);
//    registerMouseEvent(mouseEventHandler);
//    registerKeyboardEvent (keyboardEventHandler);
//    registerCharEvent(CharEventHandler);

    startTimer (GAME, 10);
    //startTimer(DEBUG, 1000);
}
