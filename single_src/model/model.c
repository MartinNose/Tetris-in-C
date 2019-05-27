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

Checkerboard checkerboard;
// store the colors of block, white as 0, (x,y),  extended space are for easier(lazier) check...
tetrimino ctetri;

int Score = 0;
static int Mark[4] = {-1,-1,-1,-1};
static Checkerboard lastCheckerboard;
static Checkerboard clearCheckerboard;
tetrimino que[2];
tetrimino HoledTetri;
bool is_game_over = FALSE;

static int countScore(int num);
double globalSpeed;

static void game ();
static void flash ();
static Checkerboard ClearLine(Checkerboard checkerboard,int row);
static Checkerboard ClearLines(Checkerboard checkerboard);
static Checkerboard RemoveLines(Checkerboard checkerboard1);
static Checkerboard RemoveLine (Checkerboard checkerboard1,int row);
static tetrimino NextTetri();


tetrimino generateTetrimino (int type, int direction)
{
    tetrimino tetri;

    tetri.x = WIDTH / 2;
    tetri.y = HEIGHT;
    tetri.type = type;
    tetri.direction = direction;
    tetri.color = TETRI_COLOR[type];
    tetri.yVelocity = 0;
    tetri.isPulsed = FALSE;

    return tetri;
}
void timerEventHandler (int timerID){
    switch(timerID){
        case MAINTAINER:
            game();
            break;
        case CheckerboardFLASH :
            flash();
            break;
    }
}
static void game ()
{
    static int time = 0;

    if (ctetri.yVelocity == 0 && !ctetri.isPulsed) {
        ctetri = NextTetri ();
        ctetri = tetriMaintainer_on_gravity (time, ctetri);
    }

    time = (time + 1) % ERA; // !!!
    Clean ();

    drawCheckerBoard(checkerboard);
    ctetri = tetriMaintainer_on_gravity (time, ctetri);
    DrawShadow(HardDrop(ctetri));

    drawTetri (ctetri);
    drawInit (Score,que[1]);

    if(ctetri.yVelocity == 0 && !ctetri.isPulsed){
        Settle(ctetri); //add tetri to checker board
        globalSpeed = DEBUG_SLOW + DEBUG_SLOW * (Score/LevelGap); //update speed
    }
    if(ctetri.isPulsed){
        DrawPulse();
    }
    if(is_game_over){
        cancelTimer(MAINTAINER);
        char buffer[32];
        sprintf (buffer, "%d", Score);
        MessageBoxA (NULL, buffer, "Display", MB_ICONINFORMATION);
    }
}
static void flash (){
    static int times = 0;
    if(times %2 == 0){
        drawCheckerBoard(lastCheckerboard);
    }else{
        drawCheckerBoard(clearCheckerboard);
    }
    drawInit (Score,que[1]);
    times++;
    if(times >= 6){
        cancelTimer(CheckerboardFLASH);
        startTimer(MAINTAINER,10);
        times = 0;
    }
}

tetrimino tetriMaintainer_on_gravity (int time, tetrimino tetri)
{
    static int curTime = 0;
    static double dy = 0;
    int dt;
    if (tetri.yVelocity == 0 && !tetri.isPulsed) {
        tetri.yVelocity = globalSpeed;
    }
    tetrimino last = tetri;
    if (time > curTime) {
        dt = (time - curTime);
    } else {
        dt = (time + ERA - curTime);
    }

    dy += tetri.yVelocity * dt;
    if (dy >= 1) {
        tetri.y -= 1;
        dy = 0;
    }

    curTime = time;

    if (!check_collision (tetri)) {
        return tetri;
    } else {
        last.yVelocity = 0;
        return last;
    }

}


void Settle(tetrimino tetri){
    Settle_Tetri (tetri);
    lastCheckerboard = checkerboard;
    clearCheckerboard = ClearLines(checkerboard);
    if(Mark[0]!=-1) {
        cancelTimer(MAINTAINER);
        startTimer(CheckerboardFLASH, 100);
    }
    checkerboard = RemoveLines(checkerboard);
    if (CheckTop () == FALSE) {
        is_game_over = TRUE;
    }
}

static int countScore(int num){
    int ds = 0;
    switch (num){
        case 0: break;
        case 1:
            ds = 100;
            break;
        case 2:
            ds = 200;
            break;
        case 3:
            ds = 500;
            break;
        case 4:
            ds = 1000;
            break;
        default:break;
    }
    return ds;
}

bool CheckTop ()
{
    bool isTopped = 0;
    for (int i = 1; i <= 12; i++) {
        if (checkerboard.block[i][19]){
            isTopped = 1;
        }
    }
    if (isTopped){
        return FALSE;
    }else{
        return TRUE;
    }
}

static Checkerboard ClearLines(Checkerboard checkerboard1)
{
    int num = 0;
    int i, j , line_ok;
    for (i = 1; i <= 18;i++ ) {
        line_ok = TRUE;
        for (j = 1; j <= 12; j++) {
            if (!checkerboard1.block[j][i]) {
                line_ok = FALSE;
                break;
            }
        }
        if (line_ok) {
            checkerboard1 = ClearLine(checkerboard1,i);
            Mark[num++] = i;
        }
    }
    Score += countScore(num);
    return checkerboard1;
}

static Checkerboard ClearLine(Checkerboard checkerboard1,int row){
    int  j;
        for (j = 1; j <= 12; j++)
            checkerboard1.block[j][row] = 0;

    return checkerboard1;
}
static Checkerboard RemoveLines(Checkerboard checkerboard1){
    int i, j ;
    for (i = 1,j = 0; i <= 18; ) {
        if (i == Mark[j] - j) {
            checkerboard1 = RemoveLine(checkerboard1,i);
            Mark[j] = -1;
            j++;
        }
        else
        {
            i++;
        }
    }
    return checkerboard1;
}
static Checkerboard RemoveLine (Checkerboard checkerboard1,int row)
{
    int i, j;
    for (i = row; i <= 18; i++) {
        for (j = 1; j <= 12; j++)
            checkerboard1.block[j][i] = checkerboard1.block[j][i + 1];
    }
    return checkerboard1;
}

tetrimino NextTetri()
{
        que[0] = que[1];
        que[1] = tetriRandom();
        return que[0];
}

tetrimino tetriRandom ()
{
    static int last = 0;
    int type;
    do {
        type = rand () % 7;
        if (type == 0) type = 7;
    } while (last == type);
    last = type;
    int direction = rand () % 2;
    return generateTetrimino (type, direction);
}

void InitModel ()
{
    int i, j;
    for(i = 0;i<14;i++)
        for(j = 0;j<25;j++)
            EmptyCheckerboard.block[i][j] = 0;

    checkerboard = EmptyCheckerboard;
    for (i = 0; i < 20; i++)
        checkerboard.block[0][i] = checkerboard.block[13][i] = 1;
    for (i = 1; i < 13; i++)
        checkerboard.block[i][0] = 1; // block_color[i][19] =
    for (i = 1; i <= 12; i++)
    {
        for (j = 1; j < 20; j++)
            checkerboard.block[i][j] = 0;
    }
    // rewrite the boundary as 1
    Score = 0;
    globalSpeed = DEBUG_SLOW;

    que[0] = tetriRandom();
    que[1] = tetriRandom();
//    block_color[3][3] = 2;
//    block_color[10][10] = 5;
//    block_color[10][18] = 3; // test, we can know that the y_max = 18

}

bool check_collision (tetrimino tetri)
{
    switch (tetri.direction) {
        case 0:
            for (int i = 0; i < 4; i++) {
                if (checkerboard.block[tetri.x + typeInfo[tetri.type][i][0] - 9][tetri.y + typeInfo[tetri.type][i][1] + 1])
                    return TRUE;
            }
            return FALSE;
            break;
        case 1:
            for (int i = 0; i < 4; i++) {
                if (checkerboard.block[tetri.x - typeInfo[tetri.type][i][1] - 9][tetri.y + typeInfo[tetri.type][i][0] + 1])
                    return TRUE;
            }
            return FALSE;
            break;
        case 2:
            for (int i = 0; i < 4; i++) {
                if (checkerboard.block[tetri.x - typeInfo[tetri.type][i][0] - 9][tetri.y - typeInfo[tetri.type][i][1] + 1])
                    return TRUE;
            }
            return FALSE;
            break;
        case 3:
            for (int i = 0; i < 4; i++) {
                if (checkerboard.block[tetri.x + typeInfo[tetri.type][i][1] - 9][tetri.y - typeInfo[tetri.type][i][0] + 1])
                    return TRUE;
            }
            return FALSE;
            break;
    }
}

void Settle_Tetri (tetrimino tetri)
{
    switch (tetri.direction) {
        case 0:
            for (int i = 0; i < 4; i++) {
                checkerboard.block[tetri.x + typeInfo[tetri.type][i][0] - 9][tetri.y + typeInfo[tetri.type][i][1]
                                                                      + 1] = tetri.type;
            }
            break;
        case 1:
            for (int i = 0; i < 4; i++) {
                checkerboard.block[tetri.x - typeInfo[tetri.type][i][1] - 9][tetri.y + typeInfo[tetri.type][i][0]
                                                                      + 1] = tetri.type;
            }
            break;
        case 2:
            for (int i = 0; i < 4; i++) {
                checkerboard.block[tetri.x - typeInfo[tetri.type][i][0] - 9][tetri.y - typeInfo[tetri.type][i][1]
                                                                      + 1] = tetri.type;
            }
            break;
        case 3:
            for (int i = 0; i < 4; i++) {
                checkerboard.block[tetri.x + typeInfo[tetri.type][i][1] - 9][tetri.y - typeInfo[tetri.type][i][0]
                                                                      + 1] = tetri.type;
            }
            break;
    }

}

tetrimino HardDrop (tetrimino tetri)
{
    while (!check_collision (tetri)) {
        tetri.y--;
    }
    tetri.y++;
    return tetri;
}

tetrimino Restart ()
{
    if(is_game_over) {
        is_game_over = FALSE;
        startTimer(MAINTAINER,10);
    }

    tetrimino tetri;
    InitModel ();
    drawInit (0,que[1]);
    tetri = NextTetri();
    return tetri;
}