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

void timerEventHandler(int timerID)
{

}

void Main(){
    SetWindowTitle("Tetris");
    InitGraphics();
    SetWindowSize(BLOCKSIZE*WIDTH,BLOCKSIZE*HEIGHT);
    InitConsole();


    for(int i = 0 ; i < 10 ;i++){
        for(int j=0;j < HEIGHT;j++){
            drawBlock(i,j,"Gray");
        }
    }
    for(int i = 10 ; i < 20 ;i++){
        for(int j=0;j < HEIGHT;j++){
            drawBlock(i,j,"White");
        }
    }
    for(int i = 20 ; i < 30 ;i++){
        for(int j=0;j < HEIGHT;j++){
            drawBlock(i,j,"Gray");
        }
    }

    startTimer(TIMER_BLINK16, m_seconds16);
}
