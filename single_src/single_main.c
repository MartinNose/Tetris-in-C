//
// Created by liujunliang on 2019/5/13.
//

#include <time.h>

#include "drawers.h"
#include "consts.h"

#include "imgui.h"
#include "model.h"
#include "handlers.h"


tetrimino NaT;//Not a Tetrimino
//tetrimino CurrentTetri;

void Main ()
{
    NaT = generateTetrimino (0, 0);// Not a Tetri

    SetWindowTitle ("Tetris");

    SetWindowSize (BLOCKSIZE * WIDTH, BLOCKSIZE * HEIGHT);
    InitGraphics ();
//    InitConsole ();

    DefineColors();
    InitModel ();
    drawUI(0, NaT);
    srand((unsigned)time(NULL));

    registerTimerEvent (timerEventHandler);
    registerMouseEvent(mouseEventHandler);
    registerKeyboardEvent (keyboardEventHandler);

    startTimer (GAME, 10);
}
