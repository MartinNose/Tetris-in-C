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

const int m_seconds16 = 16;

void timerEventHandler (int timerID)
{

}

void Main(){
    SetWindowTitle("Tetris");
    InitGraphics();
    InitConsole();
    double x,y;
    x = GetWindowWidth()/BLOCKSIZE;
    y = GetWindowHeight()/BLOCKSIZE;

    for(int i = 0; i < x;i++){
        for(int j=0;j < y;j++){
            drawBlock(i,j,1.0,1.0);
        }
    }
    startTimer(TIMER_BLINK16, m_seconds16);
}
