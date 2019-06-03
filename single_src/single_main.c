/*
 * This file generates our single-mode game
 */
#include <time.h>

#include "drawers.h"
#include "consts.h"

#include "imgui.h"
#include "model.h"
#include "handlers.h"


tetrimino NaT;//Not a Tetrimino

void Main ()
{
    NaT = generateTetrimino (0, 0);// Not a Tetri
    que[0] = que[1] = NaT;
    SetWindowTitle ("Tetris");

    SetWindowSize (BLOCKSIZE * WIDTH, BLOCKSIZE * HEIGHT);
    InitGraphicsA ();
//    InitConsole ();

    DefineColors();
    InitModel ();
    Refresh_Variables();
    drawUI(0);
    srand((unsigned)time(NULL));

    registerTimerEvent (timerEventHandler);
    registerMouseEvent(mouseEventHandler);
    registerKeyboardEvent (keyboardEventHandler);
    registerCharEvent(CharEventHandler);

    startTimer (GAME, 10);
    //startTimer(DEBUG, 1000);
}
