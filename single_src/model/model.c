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

#include "imgui.h"

#include "file_system_linked_list.h"
#include "file_system_game_status.h"
#include "sound.h"


Checkerboard checkerboard;
// store the colors of block, white as 0, (x,y),  extended space are for easier(lazier) check...
tetrimino ctetri;

int Score = 0;
static int Mark[4] = {-1, -1, -1, -1};
static Checkerboard lastCheckerboard;
static Checkerboard clearCheckerboard;
tetrimino que[2];
tetrimino HeldTetri;
bool is_game_over = FALSE;
bool isHoldLegal = TRUE;
bool MusicOn = FALSE;
bool MouseMode = FALSE;
double globalSpeed;

double xx = 0;
double yy = 0;

//MenuBar============================================

//===================================================

static int countScore[] = {0, 100, 200, 500, 1000};

static void game ();
static void flash ();
static Checkerboard ClearLine (Checkerboard checkerboard, int row);
static Checkerboard ClearLines (Checkerboard checkerboard);
static Checkerboard RemoveLines (Checkerboard checkerboard1);
static Checkerboard RemoveLine (Checkerboard checkerboard1, int row);
static tetrimino NextTetri ();

tetrimino generateTetrimino (int type, int direction)
{
    tetrimino tetri;

    tetri.x = LEFTBAR + 6;
    tetri.y = HEIGHT;
    tetri.type = type;
    tetri.direction = direction;
//    tetri.color = TETRI_COLOR[type];
    tetri.yVelocity = 0;
    tetri.isPaused = FALSE;

    return tetri;
}
void timerEventHandler (int timerID)
{
    switch (timerID) {
        case GAME:
            if(!is_game_over)game ();
            else{
                drawCheckerBoard(checkerboard);
                drawUI(Score);
                DrawBoard(GAMEOVER);
            }
            break;
        case CheckerboardFLASH :
            flash ();
            break;
        //case GAMEOVER:

            break;
        case DEBUG:printf ("%f", GetWindowWidth ());
            break;
        case LOADING:
            MessageBoxB(NULL,NULL);
            break;
    }
}
static void game ()
{
    static int time = 0;
    if (ctetri.yVelocity == 0 && !ctetri.isPaused && !is_game_over) {
        ctetri = NextTetri ();
        ctetri = tetriMaintainer_on_gravity (time, ctetri);
    }

    time = (time + 1) % ERA; // !!!
    Clean ();

    drawCheckerBoard (checkerboard);
    ctetri = tetriMaintainer_on_gravity (time, ctetri);
    DrawShadow (HardDrop (ctetri));

    drawTetri (ctetri);
    drawUI (Score);

    if (ctetri.yVelocity == 0 && !ctetri.isPaused ) {
        Settle (ctetri); //add tetri to checker board
        globalSpeed = INIT_SPEED + INIT_SPEED * (Score / LevelGap); //update speed
        isHoldLegal = TRUE;
    }
    if(ctetri.isPaused){
        DrawBoard(PAUSE);
    }
    if (is_game_over) {
        GameOver ();
    }
}
static void flash ()
{
    static int times = 0;
    if (times % 2 == 0) {
        drawCheckerBoard (lastCheckerboard);
    } else {
        drawCheckerBoard (clearCheckerboard);
    }
    drawUI (Score);
    times++;
    if (times >= 6) {
        cancelTimer (CheckerboardFLASH);
        startTimer (GAME, 10);
        times = 0;
    }
}

tetrimino tetriMaintainer_on_gravity (int time, tetrimino tetri)
{
    static int curTime = 0;
    static double dy = 0;
    int dt;
    if (tetri.yVelocity == 0 && !tetri.isPaused) {
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

void Settle (tetrimino tetri)
{
    checkerboard = Settle_Tetri (tetri, checkerboard);
    lastCheckerboard = checkerboard;
    clearCheckerboard = ClearLines (checkerboard);
    if (Mark[0] != -1) {
        cancelTimer (GAME);
        startTimer (CheckerboardFLASH, 100);
        Play_Sound ();
    }
    checkerboard = RemoveLines (checkerboard);
    if (CheckTop () == FALSE) {
        is_game_over = TRUE;
    }
}

bool CheckTop ()
{
    bool isTopped = 0;
    for (int i = 1; i <= 12; i++) {
        if (checkerboard.block[i][19]) {
            isTopped = 1;
        }
    }
    if (isTopped) {
        return FALSE;
    } else {
        return TRUE;
    }
}

static Checkerboard ClearLines (Checkerboard checkerboard1)
{
    int num = 0;
    int i, j, line_ok;
    for (i = 1; i <= 18; i++) {
        line_ok = TRUE;
        for (j = 1; j <= 12; j++) {
            if (!checkerboard1.block[j][i]) {
                line_ok = FALSE;
                break;
            }
        }
        if (line_ok) {
            checkerboard1 = ClearLine (checkerboard1, i);
            Mark[num++] = i;
        }
    }
    Score += countScore[num];
    return checkerboard1;
}

static Checkerboard ClearLine (Checkerboard checkerboard1, int row)
{
    int j;
    for (j = 1; j <= 12; j++)
        checkerboard1.block[j][row] = 0;

    return checkerboard1;
}
static Checkerboard RemoveLines (Checkerboard checkerboard1)
{
    int i, j;
    for (i = 1, j = 0; i <= 18;) {
        if (i == Mark[j] - j) {
            checkerboard1 = RemoveLine (checkerboard1, i);
            Mark[j] = -1;
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

tetrimino NextTetri ()
{
    que[0] = que[1];
    que[1] = tetriRandom ();
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

static Checkerboard generateInitCheckerboard ()
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

    return EmptyCheckerboard;
}

void InitModel ()
{
    cancelTimer (GAMEOVER);
    checkerboard = generateInitCheckerboard ();
    ctetri = tetriRandom ();
    ctetri.yVelocity = INIT_SPEED;
    Score = 0;

    globalSpeed = INIT_SPEED;
    is_game_over = FALSE;
    isHoldLegal = TRUE;
    HeldTetri = generateTetrimino (0, 0);
    que[0] = tetriRandom ();
    que[1] = tetriRandom ();
    //For MenuBar
    //For Game STATE
//    MusicOn = TRUE;
    BGM_maintainer (TRUE);
    MouseMode = FALSE;
    setMenuColors ("Black", "White", "Light Gray", "White", 1);
}

bool check_collision (tetrimino tetri)
{
    switch (tetri.direction) {
        case 0:
            for (int i = 0; i < 4; i++) {
                if (checkerboard.block[tetri.x - LEFTBAR + 1 + typeInfo[tetri.type][i][0]][tetri.y
                                                                                           + typeInfo[tetri.type][i][1]
                                                                                           + 1])
                    return TRUE;
            }
            return FALSE;
            break;
        case 1:
            for (int i = 0; i < 4; i++) {
                if (checkerboard.block[tetri.x - LEFTBAR + 1 - typeInfo[tetri.type][i][1]][tetri.y
                                                                                           + typeInfo[tetri.type][i][0]
                                                                                           + 1])
                    return TRUE;
            }
            return FALSE;
            break;
        case 2:
            for (int i = 0; i < 4; i++) {
                if (checkerboard.block[tetri.x - LEFTBAR + 1 - typeInfo[tetri.type][i][0]][tetri.y
                                                                                           - typeInfo[tetri.type][i][1]
                                                                                           + 1])
                    return TRUE;
            }
            return FALSE;
            break;
        case 3:
            for (int i = 0; i < 4; i++) {
                if (checkerboard.block[tetri.x - LEFTBAR + 1 + typeInfo[tetri.type][i][1]][tetri.y
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
    while (!check_collision (tetri)) {
        tetri.y--;
    }
    tetri.y++;
    return tetri;
}

tetrimino Restart ()
{
    if (is_game_over) {
        is_game_over = FALSE;
        startTimer (GAME, 10);
    }

    InitModel ();
    drawUI (0);
}

tetrimino HoldEventHandler (tetrimino temp)
{
    if (isHoldLegal) {
        if (HeldTetri.type == 0) {
            HeldTetri = temp;
            temp = que[1];
        } else {
            temp = HeldTetri;
            temp.yVelocity = globalSpeed;
            HeldTetri = ctetri;
        }
        HeldTetri.y = 18;
        isHoldLegal = FALSE;
    }
    return temp;
}

tetrimino PauseEventHandler (tetrimino temp)
{
    if (!temp.isPaused) {
        temp.isPaused = TRUE;
        temp.yVelocity = 0;
    } else {
        temp.yVelocity = globalSpeed;
        temp.isPaused = FALSE;
    }
    return temp;
}

void ExitGame ()
{
    WinExec("launcher.exe", SW_SHOW);
    exit (0);
}

void GameOver ()
{
    is_game_over = TRUE;
    //cancelTimer (GAME);
    userNode *rank_list = Load_Rank ();
    //TODO INPUT
    rank_list = Add_Node (rank_list, Score, "game_debug");
    write_Rank (rank_list);

    //startTimer(GAMEOVER,10);
}

void Upload() {
    //TODO upload usename and score
}
void SaveGame()
{
    File_Save_Game (&checkerboard, &ctetri, &que[0], &que[1], &HeldTetri, Score, MouseMode, MusicOn);
    MessageBoxB("Saving Game","Red");
}

bool LoadGame()
{
    Checkerboard temp;
    tetrimino cur_tetri, que1, que2, held_tetri;
    int temp_score;
    bool Mouse_Mode, Music_on;


    if (File_Load_Saved_Game (&temp, &cur_tetri, &que1, &que2, &held_tetri, &temp_score, &Mouse_Mode, &Music_on))
    {
        checkerboard = temp;
        ctetri = cur_tetri;
        que[0] = cur_tetri;
        que[1] = que2; 
        HeldTetri = held_tetri;
        Score = temp_score;
        MouseMode = Mouse_Mode;
//        MusicOn = Music_on;
        BGM_maintainer (Music_on);
        MessageBoxB("Loading","Black");

        return TRUE;
    }
    return FALSE;

}
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

void BGM_maintainer(bool new_music_on)
{
    if (new_music_on && !MusicOn)
    {
        MusicOn = TRUE;
        PlaySound(BGM_Path, NULL, SND_FILENAME | SND_ASYNC);
    }
    else if (!new_music_on && MusicOn)
    {
        MusicOn = FALSE;
        PlaySound(NULL,NULL,SND_FILENAME); // 用于停止播放的音乐
    }
}