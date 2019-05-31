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

#include "model_2p.h"
#include "consts_2p.h"
#include "drawers_2p.h"

#include "imgui.h"

#include "sound.h"


Checkerboard checkerboardlist[2];
// store the colors of block, white as 0, (x,y),  extended space are for easier(lazier) check...
tetrimino ctetri[2];

int Score[2] = {0};
static int Mark[2][4] = {-1, -1, -1, -1,-1, -1, -1, -1};
static Checkerboard lastCheckerboard[2];
static Checkerboard clearCheckerboard[2];
tetrimino que[2][2];
bool is_game_over[2] = {FALSE,FALSE};
bool MusicOn = FALSE;

tetrimino HeldTetri[2];
bool isHoldLegal[2] = {TRUE,TRUE};
double globalSpeed;

static int countScore[] = {0, 100, 200, 500, 1000};

static void game ();
static void flash (int i);
static Checkerboard ClearLine (Checkerboard checkerboard, int row);
static Checkerboard ClearLines (Checkerboard checkerboard);
static Checkerboard RemoveLines (Checkerboard checkerboard1);
static Checkerboard RemoveLine (Checkerboard checkerboard1, int row);

void InitModel ()
{
    checkerboardlist[0] = generateInitCheckerboard (LEFT);
    checkerboardlist[1] = generateInitCheckerboard (RIGHT);
    ctetri[0]  =  tetriRandom (0);
    ctetri[1] =   tetriRandom(1);
    ctetri[0].yVelocity =  ctetri[1].yVelocity = INIT_SPEED;
    Score[0] = 0;
    Score[1] = 0;

    HeldTetri[0] = generateTetrimino(0,0,0);
    HeldTetri[1] = generateTetrimino(0,0,1);

    globalSpeed = INIT_SPEED;
    is_game_over[0] = is_game_over[1]= FALSE;

    que[0][0] = que[0][1] = tetriRandom (0);
    que[1][0] = que[1][1] = tetriRandom (1);
//    MusicOn = TRUE;
    BGM_maintainer (TRUE);
    //MouseMode = FALSE;
}

tetrimino generateTetrimino (int type, int direction ,int index)
{
    tetrimino tetri;

    tetri.x = (index==LEFT)?(LEFTBAR + 6):(WIDTH - LEFTBAR - 6);
    tetri.y = HEIGHT;
    tetri.type = type;
    tetri.direction = direction;
    tetri.yVelocity = INIT_SPEED;
    tetri.isPaused = FALSE;
    tetri.position = index;
    //tetri.curChecker = checkerboardlist[index]; //TODO 改为position

    return tetri;
}
void timerEventHandler (int timerID)
{
    switch (timerID) {
        case GAME:
            if(!is_game_over[0] && !is_game_over[1])game ();
            else{
                drawUI();
            }
            break;
        case CheckerboardFLASH :
            flash (KEEP);
            break;
    }
}
static void game ()
{
    static int time = 0;
    for(int i= 0;i<2;i++) {
        if (ctetri[i].yVelocity == 0 && !is_game_over[i]) {
            ctetri[i] = NextTetri(i);
            ctetri[i] = tetriMaintainer_on_gravity(time, ctetri[i]);
        }

        time = (time + 1) % ERA; // !!!
        Clean(i);

        //drawCheckerBoard(checkerboardlist[i]);
        ctetri[i] = tetriMaintainer_on_gravity(time, ctetri[i]);



        if (ctetri[i].yVelocity == 0) {
            Settle(ctetri[i]); //add tetri to checker board
            //globalSpeed = INIT_SPEED + INIT_SPEED * (Score[i] / LevelGap); //TODO update speed
        }
        if (is_game_over[i]) {
            GameOver(i);
        }

    }
    drawCheckerBoardList(checkerboardlist);
    for(int i = 0;i<2;i++) {
        drawTetri(ctetri[i]);
        DrawShadow(HardDrop(ctetri[i]));
    }

    drawUI();
}
static void flash (int i)
{
//    static int times = 0;
//    static int index = 0;
//    if(i != KEEP){
//        index = i;
//    }
//    if (times % 2 == 0) {
//        drawCheckerBoard (lastCheckerboard[index]);
//    } else {
//        drawCheckerBoard (clearCheckerboard[index]);
//    }
//    drawCheckerBoard(checkerboardlist[i^1]);
//    drawUI ();
//    times++;
//    if (times >= 6) {
//        cancelTimer (CheckerboardFLASH);
//        startTimer (GAME, 10);
//        times = 0;
//    }
}

tetrimino tetriMaintainer_on_gravity (int time, tetrimino tetri) {
    static int curTime = 0;
    static double dy = 0;
    int dt;
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

    if (!check_collision (tetri,checkerboardlist[tetri.position])) {
        return tetri;
    } else {
        last.yVelocity = 0;
        return last;
    }
}

Checkerboard Settle (tetrimino tetri)
{
    Checkerboard checkerboard;
    checkerboard = checkerboardlist[tetri.position];
    checkerboardlist[tetri.position] = Settle_Tetri (tetri,checkerboardlist[tetri.position]);
    lastCheckerboard[tetri.position] = checkerboard;
    clearCheckerboard[tetri.position] = ClearLines (checkerboard);
    if (Mark[tetri.position][0] != -1) {
        cancelTimer (GAME);
        flash(tetri.position);
        startTimer (CheckerboardFLASH, 100);
        Play_Sound ();
    }
    checkerboard = RemoveLines (checkerboard);
    if (CheckTop (tetri.position) == FALSE) {
        is_game_over[tetri.position] = TRUE;
    }
    return checkerboard;
}

bool CheckTop (int index)
{
    bool isTopped = 0;
    for (int i = 1; i <= 12; i++) {
        if (checkerboardlist[index].block[i][19]) {
            isTopped = 1;
        }
    }
    if (isTopped) {
        return FALSE;
    } else {
        return TRUE;
    }
}


tetrimino NextTetri (int position)
{
    que[position][0] = que[position][1];
    que[position][1] = tetriRandom (position);
    return que[position][0];
}

tetrimino tetriRandom (int x)
{
    static int last = 0;
    int type;
    do {
        type = rand () % 7;
        if (type == 0) type = 7;
    } while (last == type);
    last = type;
    int direction = rand () % 2;
    return generateTetrimino (type, direction,x);
}

static Checkerboard generateInitCheckerboard (int x)
{
    int i, j;
    Checkerboard EmptyCheckerboard;
    for (i = 0; i < 14; i++)
        for (j = 0; j < 25; j++)
            EmptyCheckerboard.block[i][j] = 0;
    for (i = 0; i < 20; i++)
        EmptyCheckerboard.block[0][i] = EmptyCheckerboard.block[13][i] = 1;
    for (i = 1; i < 13; i++)
        EmptyCheckerboard.block[i][0] = 1; // block_color[i][19] =
    // rewrite the boundary as 1
    for (i = 1; i <= 12; i++) {
        for (j = 1; j < 20; j++)
            EmptyCheckerboard.block[i][j] = 0;
    }
    EmptyCheckerboard.x = x;
    return EmptyCheckerboard;
}



bool check_collision (tetrimino tetri,Checkerboard checkerboard)
{
    checkerboard = checkerboardlist[tetri.position];
    switch (tetri.direction) {
        case 0:
            for (int i = 0; i < 4; i++) {
                if (checkerboard.block[tetri.x - checkerboard.x + 1 + typeInfo[tetri.type][i][0]][tetri.y
                                                                                           + typeInfo[tetri.type][i][1]
                                                                                           + 1])
                    return TRUE;
            }
            return FALSE;
            break;
        case 1:
            for (int i = 0; i < 4; i++) {
                if (checkerboard.block[tetri.x - checkerboard.x + 1 - typeInfo[tetri.type][i][1]][tetri.y
                                                                                           + typeInfo[tetri.type][i][0]
                                                                                           + 1])
                    return TRUE;
            }
            return FALSE;
            break;
        case 2:
            for (int i = 0; i < 4; i++) {
                if (checkerboard.block[tetri.x - checkerboard.x + 1 - typeInfo[tetri.type][i][0]][tetri.y
                                                                                           - typeInfo[tetri.type][i][1]
                                                                                           + 1])
                    return TRUE;
            }
            return FALSE;
            break;
        case 3:
            for (int i = 0; i < 4; i++) {
                if (checkerboard.block[tetri.x - checkerboard.x + 1 + typeInfo[tetri.type][i][1]][tetri.y
                                                                                           - typeInfo[tetri.type][i][0]
                                                                                           + 1])
                    return TRUE;
            }
            return FALSE;
            break;
    }
}

Checkerboard Settle_Tetri (tetrimino tetri, Checkerboard checker)
{
    switch (tetri.direction) {
        case 0:
            for (int i = 0; i < 4; i++) {
                checker.block[tetri.x - LEFTBAR + 1 + typeInfo[tetri.type][i][0]][tetri.y + typeInfo[tetri.type][i][1]
                                                                                  + 1] = tetri.type;
            }
            break;
        case 1:
            for (int i = 0; i < 4; i++) {
                checker.block[tetri.x - LEFTBAR + 1 - typeInfo[tetri.type][i][1]][tetri.y + typeInfo[tetri.type][i][0]
                                                                                  + 1] = tetri.type;
            }
            break;
        case 2:
            for (int i = 0; i < 4; i++) {
                checker.block[tetri.x - LEFTBAR + 1 - typeInfo[tetri.type][i][0]][tetri.y - typeInfo[tetri.type][i][1]
                                                                                  + 1] = tetri.type;
            }
            break;
        case 3:
            for (int i = 0; i < 4; i++) {
                checker.block[tetri.x - LEFTBAR + 1 + typeInfo[tetri.type][i][1]][tetri.y - typeInfo[tetri.type][i][0]
                                                                                  + 1] = tetri.type;
            }
            break;
    }
    return checker;

}

tetrimino HardDrop (tetrimino tetri)
{
    while (!check_collision (tetri,checkerboardlist[tetri.position])) {
        tetri.y--;
    }
    tetri.y++;
    return tetri;
}

tetrimino Restart ()
{
    InitModel ();
    drawUI ();
}

tetrimino HoldEventHandler (tetrimino temp,int position)
{
    if (isHoldLegal[position]) {
        if (HeldTetri[position].type == 0) {
            HeldTetri[position] = temp;
            temp = que[position][1];
        } else {
            temp = HeldTetri[position];
            temp.yVelocity = globalSpeed;
            HeldTetri[position] = ctetri[position];
        }
        isHoldLegal[position] = FALSE;
    }
    return temp;
}



void ExitGame ()
{
    WinExec("launcher.exe", SW_SHOW);
    exit (0);
}

void GameOver (int i)
{
    is_game_over[i] = TRUE;
    cancelTimer (GAME);
    startTimer(GAMEOVER,10);
}
//On CheckerBoard=======================================================
static Checkerboard ClearLines (Checkerboard checkerboard)
{
    int num = 0;
    int i, j, line_ok;
    for (i = 1; i <= 18; i++) {
        line_ok = TRUE;
        for (j = 1; j <= 12; j++) {
            if (!checkerboard.block[j][i]) {
                line_ok = FALSE;
                break;
            }
        }
        if (line_ok) {
            checkerboard = ClearLine (checkerboard, i);
            Mark[checkerboard.position][num++] = i;
        }
    }
    Score[checkerboard.position] += countScore[num];
    return checkerboard;
}
static Checkerboard ClearLine (Checkerboard checkerboard, int row)
{
    int j;
    for (j = 1; j <= 12; j++)
        checkerboard.block[j][row] = 0;

    return checkerboard;
}
static Checkerboard RemoveLines (Checkerboard checkerboard1)
{
    int i, j;
    for (i = 1, j = 0; i <= 18;) {
        if (i == Mark[checkerboard1.position][j] - j) {
            checkerboard1 = RemoveLine (checkerboard1, i);
            Mark[checkerboard1.position][j] = -1;
            j++;
        } else {
            i++;
        }
    }
    return checkerboard1;
}
static Checkerboard RemoveLine (Checkerboard checkerboard1, int row)
{
    int i, j;
    for (i = row; i <= 18; i++) {
        for (j = 1; j <= 12; j++)
            checkerboard1.block[j][i] = checkerboard1.block[j][i + 1];
    }
    return checkerboard1;
}

//=========================================================================


//Assistants========================================================
int XInchScaleToBlock(double x){
    return (int)ceil(x/BLOCKSIZE) - LEFTBAR;
}

bool InCheckerBoard(double x, double y){
    return ifHover(x,y,LEFTBAR*BLOCKSIZE,(LEFTBAR+12)*BLOCKSIZE,0,GetWindowHeight());
}

bool ifHover(double x, double y, double x1, double x2, double y1, double y2)
{
    return (x >= x1 && x <= x2 && y >= y1 && y <= y2);
}
//on BGM================================================================
void BGM_maintainer(bool new_music_on)
{
//    if (new_music_on && !MusicOn)
//    {
//        MusicOn = TRUE;
//        PlaySound(BGM_Path, NULL, SND_FILENAME | SND_ASYNC);
//    }
//    else if (!new_music_on && MusicOn)
//    {
//        MusicOn = FALSE;
//        PlaySound(NULL,NULL,SND_FILENAME); // 用于停止播放的音乐
//    }
}
