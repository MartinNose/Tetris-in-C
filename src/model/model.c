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

int block_color[14][25] = {0};
Checkerboard checkerboard;
// store the colors of block, white as 0, (x,y),  extended space are for easier(lazier) check...
tetrimino ctetri;

static int score = 0;
bool is_game_over = FALSE;

tetrimino generateTetrimino (int type, int direction)
{
    tetrimino tetri;

    tetri.x = WIDTH / 2;
    tetri.y = HEIGHT;
    tetri.type = type;
    tetri.direction = direction;
    tetri.color = TETRI_COLOR[type];
    tetri.yVelocity = 0;

    return tetri;
}
void timerEventHandler (int timerID){
    switch(timerID){
        case MAINTAINER:
            game();
        case CheckerboardFLASH :
            break;

    }
}
void game ()
{
    static int time = 0;

    if (ctetri.yVelocity == 0) {
        ctetri = tetriRandom ();
        ctetri = tetriMaintainer_on_gravity (time, ctetri);
    }

    time = (time + 1) % ERA; // !!!
    Clean ();

    drawCheckerBoard(checkerboard);
    ctetri = tetriMaintainer_on_gravity (time, ctetri);
    DrawShadow(HardDrop(ctetri));

    drawTetri (ctetri);
    drawInit (score);

    if(ctetri.yVelocity == 0){
        Settle(ctetri);
    }

    if(is_game_over){
        cancelTimer(MAINTAINER);
        char buffer[32];
        sprintf (buffer, "%d", score);
        MessageBoxA (NULL, buffer, "Display", MB_ICONINFORMATION);
    }
}


tetrimino tetriMaintainer_on_gravity (int time, tetrimino tetri)
{
    static int curTime = 0;
    static double dy = 0;
    int dt;
    if (tetri.yVelocity == 0) {
        tetri.yVelocity = DEBUG_SLOW;
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
    int rownum;
    Settle_Tetri (tetri);
    rownum = CheckLines();
    int ds = 0;
    switch (rownum){
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
    score += ds;
    
    if (CheckTop () == FALSE) {
        is_game_over = TRUE;
    }
}

bool CheckTop ()
{
    bool isTopped = 0;
    for (int i = 1; i <= 12; i++) {
        if (block_color[i][19]){
            isTopped = 1;
            }
    }
    if (isTopped){
        return FALSE;
    }else{
        return TRUE;
    }
}

int CheckLines ()
{
    int num = 0;
    int i, j , line_ok;
    for (i = 1; i <= 18; ) {
        line_ok = TRUE;
        for (j = 1; j <= 12; j++) {
            if (!block_color[j][i]) {
                line_ok = FALSE;
                break;
            }
        }
        if (line_ok) {
            RemoveLine(i);
            num++;
        }
        else
        {
            i++;
        }
    }
    return num;
}



void RemoveLine (int row)
{
    int i, j;
    for (i = row; i <= 18; i++) {
        for (j = 1; j <= 12; j++)
            block_color[j][i] = block_color[j][i + 1];
    }
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
    for (i = 0; i < 20; i++)
        block_color[0][i] = block_color[13][i] = 1;
    for (i = 1; i < 13; i++)
        block_color[i][0] = 1; // block_color[i][19] =
    for (i = 1; i <= 12; i++)
    {
        for (j = 1; j < 20; j++)
            block_color[i][j] = 0;
    }
    // rewrite the boundary as 1
    score = 0;
//    block_color[3][3] = 2;
//    block_color[10][10] = 5;
//    block_color[10][18] = 3; // test, we can know that the y_max = 18
    for(i = 0;i<14;i++)
        for(j = 0;j<20;j++)
            EmptyCheckerboard.block[i][j] = 0;

    checkerboard = EmptyCheckerboard;
}

bool check_collision (tetrimino tetri)
{
    switch (tetri.direction) {
        case 0:
            for (int i = 0; i < 4; i++) {
                if (block_color[tetri.x + typeInfo[tetri.type][i][0] - 9][tetri.y + typeInfo[tetri.type][i][1] + 1])
                    return TRUE;
            }
            return FALSE;
            break;
        case 1:
            for (int i = 0; i < 4; i++) {
                if (block_color[tetri.x - typeInfo[tetri.type][i][1] - 9][tetri.y + typeInfo[tetri.type][i][0] + 1])
                    return TRUE;
            }
            return FALSE;
            break;
        case 2:
            for (int i = 0; i < 4; i++) {
                if (block_color[tetri.x - typeInfo[tetri.type][i][0] - 9][tetri.y - typeInfo[tetri.type][i][1] + 1])
                    return TRUE;
            }
            return FALSE;
            break;
        case 3:
            for (int i = 0; i < 4; i++) {
                if (block_color[tetri.x + typeInfo[tetri.type][i][1] - 9][tetri.y - typeInfo[tetri.type][i][0] + 1])
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
                block_color[tetri.x + typeInfo[tetri.type][i][0] - 9][tetri.y + typeInfo[tetri.type][i][1]
                                                                      + 1] = tetri.type;
            }
            break;
        case 1:
            for (int i = 0; i < 4; i++) {
                block_color[tetri.x - typeInfo[tetri.type][i][1] - 9][tetri.y + typeInfo[tetri.type][i][0]
                                                                      + 1] = tetri.type;
            }
            break;
        case 2:
            for (int i = 0; i < 4; i++) {
                block_color[tetri.x - typeInfo[tetri.type][i][0] - 9][tetri.y - typeInfo[tetri.type][i][1]
                                                                      + 1] = tetri.type;
            }
            break;
        case 3:
            for (int i = 0; i < 4; i++) {
                block_color[tetri.x + typeInfo[tetri.type][i][1] - 9][tetri.y - typeInfo[tetri.type][i][0]
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
    drawInit (0);
    tetri = tetriRandom();
    return tetri;
}