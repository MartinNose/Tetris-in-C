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
    que[0] = que[1] = NaT;
    SetWindowTitle ("Tetris");

    SetWindowSize (BLOCKSIZE * WIDTH, BLOCKSIZE * HEIGHT);
    InitGraphics ();
    //InitConsole ();

    DefineColors();
    InitModel ();
    drawUI(0);
    srand((unsigned)time(NULL));

    registerTimerEvent (timerEventHandler);
    registerMouseEvent(mouseEventHandler);
    registerKeyboardEvent (keyboardEventHandler);

    startTimer (GAME, 10);
    //startTimer(DEBUG, 1000);
}
