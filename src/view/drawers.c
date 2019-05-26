#ifndef _DRAWERS_C
#define _DRAWERS_C

#include "drawers.h"
#include "consts.h"
#include "model.h"


void DrawRect (double width, double height)
{
    DrawLine (width, 0);
    DrawLine (0, height);
    DrawLine (-1 * width, 0);
    DrawLine (0, -1 * height);
}
void Clean ()
{
    SetEraseMode (1);
    StartFilledRegion (1);
    MovePen (0, 0);
    DrawRect (GetWindowWidth (), GetWindowHeight ());
    EndFilledRegion ();
    SetEraseMode (0);
}
void drawBlock (int x, int y, string color)
{
    SetPenColor (color);
    StartFilledRegion (1);

    MovePen (x * BLOCKSIZE, y * BLOCKSIZE);

    DrawRect (BLOCKSIZE, BLOCKSIZE);

    EndFilledRegion ();

    SetPenColor ("Black");
//    MovePen (x * BLOCKSIZE, y * BLOCKSIZE);
//    DrawRect (BLOCKSIZE, BLOCKSIZE);
}

void drawTetri (tetrimino tetri)
{
    switch (tetri.direction) {
        case 0:
            for (int i = 0; i < 4; i++) {
                drawBlock (tetri.x + typeInfo[tetri.type][i][0], tetri.y + typeInfo[tetri.type][i][1], tetri.color);
            }
            break;
        case 1:
            for (int i = 0; i < 4; i++) {
                drawBlock (tetri.x - typeInfo[tetri.type][i][1], tetri.y + typeInfo[tetri.type][i][0], tetri.color);
            }
            break;
        case 2:
            for (int i = 0; i < 4; i++) {
                drawBlock (tetri.x - typeInfo[tetri.type][i][0], tetri.y - typeInfo[tetri.type][i][1], tetri.color);
            }
            break;
        case 3:
            for (int i = 0; i < 4; i++) {
                drawBlock (tetri.x + typeInfo[tetri.type][i][1], tetri.y - typeInfo[tetri.type][i][0], tetri.color);
            }
            break;
    }
}
void DrawGrid(){
    SetPenColor("Black");
    for (int i = 10; i < 22; i++) {
        MovePen(i*BLOCKSIZE,0);
        DrawLine(0,GetWindowHeight());
    }
    for (int j = 0; j < HEIGHT; j++) {
        MovePen(10*BLOCKSIZE,j*BLOCKSIZE);
        DrawLine(12*BLOCKSIZE,0);
    }
}

void drawInit (int score)
{
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < HEIGHT; j++) {
            drawBlock (i, j, "Gray");
        }
    }
    for (int i = 22; i < WIDTH; i++) {
        for (int j = 0; j < HEIGHT; j++) {
            drawBlock(i, j, "Gray");
        }
    }
    DrawGrid ();
    DrawScore(score);
}
void drawCheckerBoard(){
    for (int i = 1; i < 13; i++) {
        for (int j = 0; j < HEIGHT; j++) {
            drawBlock (i + 9, j, TETRI_COLOR[block_color[i][j + 1]]);
        }
    }
}

void drawShadowBlock(int x, int y, string color)
{
    SetPenColor (color);

    SetPenSize(GetPenSize()+3);
    MovePen (x * BLOCKSIZE, y * BLOCKSIZE);
    DrawRect (BLOCKSIZE, BLOCKSIZE);

    SetPenColor ("Black");
    SetPenSize(GetPenSize()-3);
//    MovePen (x * BLOCKSIZE, y * BLOCKSIZE);
//    DrawRect (BLOCKSIZE, BLOCKSIZE);
}

void DrawShadow(tetrimino shadow){
    if(shadow.y>ctetri.y){
        return;
    }
    switch (shadow.direction) {
        case 0:
            for (int i = 0; i < 4; i++) {
                drawShadowBlock (shadow.x + typeInfo[shadow.type][i][0], shadow.y + typeInfo[shadow.type][i][1], shadow.color);
            }
            break;
        case 1:
            for (int i = 0; i < 4; i++) {
                drawShadowBlock (shadow.x - typeInfo[shadow.type][i][1], shadow.y + typeInfo[shadow.type][i][0], shadow.color);
            }
            break;
        case 2:
            for (int i = 0; i < 4; i++) {
                drawShadowBlock (shadow.x - typeInfo[shadow.type][i][0], shadow.y - typeInfo[shadow.type][i][1], shadow.color);
            }
            break;
        case 3:
            for (int i = 0; i < 4; i++) {
                drawShadowBlock (shadow.x + typeInfo[shadow.type][i][1], shadow.y - typeInfo[shadow.type][i][0], shadow.color);
            }
            break;
    }
}


void DrawScore(int score){
    char s[100];
    sprintf(s,"Score: %d",score);
    MovePen(2*BLOCKSIZE,15*BLOCKSIZE);
    DrawTextString(s);
}

#endif