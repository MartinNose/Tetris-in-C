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

#define TIMER_BLINK16  1     /*250ms定时器事件标志号*/


const int m_seconds16 = 16;


enum Block_Color {
    Empty=0, Red=1, Blue=2
};


enum Block_Color blocks[10][21] = {0};


void DropMaintainer ()
{
    // TODO Model
    static int time = 0;
    time++;
    if (time == 666) // TODO cal ...
    {
        time = 0;
        // TODO Drop one block
        // Erase
        // DrawNew
    }
}

void timerEventHandler (int timerID)
{
    DropMaintainer ();
    // TODO Change Model()...
    // TODO refresh GUI
//    refreshGUI();
}

void Main ()
{
    SetWindowTitle ("Tetris");
    InitGraphics ();
    InitConsole ();
    double x, y;
    x = GetWindowWidth ();
    y = GetWindowHeight ();
    for (int i = 0; i < x * 3; i++) {
        for (int j = 0; j < y * 3; j++) {
            drawBlock (i / 3.0, j / 3.0, 1.0/3, 1.0/3);
        }
    }
    registerTimerEvent (timerEventHandler); /*注册定时器消息回调函数*/
    startTimer (TIMER_BLINK16, m_seconds16);
    SetPenColor ()
}
