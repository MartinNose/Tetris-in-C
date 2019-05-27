#ifndef _DRAWERS_C
#define _DRAWERS_C

#include "drawers.h"
#include "consts.h"
#include "model.h"
void DefineRGBColor(string s,int r,int g,int b){
    DefineColor(s,r/255.0,g/255.0,b/255.0);
}
void DefineColors(){
    DefineRGBColor("Magenta",138,43,226); //blueviolet
    DefineRGBColor("Blue",30,144,255); //dodgerblue
    DefineRGBColor("Cyan",127,255,212); //aquamarine
    DefineRGBColor("Yellow",255,215,0); //gold
    DefineRGBColor("Green",34,139,34);//forestgreen
    DefineRGBColor("Light Gray",105,105,105);//dimgray
    DefineRGBColor("Red",220,20,60);//crimson
};

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

    //draw Checkerboard Grid
    for (int i = 10; i <= 22; i++) {
        MovePen(i*BLOCKSIZE,0);
        DrawLine(0,GetWindowHeight());
    }

    for (int j = 0; j <= HEIGHT; j++) {
        MovePen(10*BLOCKSIZE,j*BLOCKSIZE);
        DrawLine(12*BLOCKSIZE,0);
    }

    //draw Next Tetri area
    for(int i = PreX;i<=PreX + 6;i++){
        MovePen(i*BLOCKSIZE,PreY*BLOCKSIZE);
        DrawLine(0,6*BLOCKSIZE);
    }
    for(int i = PreY;i<=PreY + 6;i++){
        MovePen(PreX*BLOCKSIZE,i*BLOCKSIZE);
        DrawLine(6*BLOCKSIZE,0);
    }

    for(int i = HoldX;i<=HoldX + 6;i++){
        MovePen(i*BLOCKSIZE,HoldY*BLOCKSIZE);
        DrawLine(0,6*BLOCKSIZE);
    }
    for(int i = HoldY;i<=HoldY + 6;i++){
        MovePen(HoldX*BLOCKSIZE,i*BLOCKSIZE);
        DrawLine(6*BLOCKSIZE,0);
    }
//    for (int i = 0; i < WIDTH; i++) {
//        MovePen(i*BLOCKSIZE,0);
//        DrawLine(0,GetWindowHeight());
//    }
//    for (int j = 0; j < HEIGHT; j++) {
//        MovePen(0,j*BLOCKSIZE);
//        DrawLine(GetWindowWidth(),0);
//    }
}

void drawInit (int score, tetrimino NextTetri)
{
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < HEIGHT; j++) {
            drawBlock (i, j, "Gray");
        }
    }
    for (int i = 22; i < WIDTH; i++) {
        for (int j = 0; j < HEIGHT; j++) {
            if(!((i>=PreX && i < PreX + 6 && j >= PreY && j < PreY + 6)||(i>=HoldX && i < HoldX + 6 && j >= HoldY && j < HoldY + 6)))//to show Next Tetri
                drawBlock(i, j, "Gray");
        }
    }


    DrawNextTetrimino(NextTetri);
    if(HoldedTetri.type!=0)
        DrawHoldedTetrimino(HoldedTetri);

    DrawGrid ();
    DrawData(score);

}
void drawCheckerBoard(Checkerboard checker){
    for (int i = 1; i < 13; i++) {
        for (int j = 0; j < HEIGHT; j++) {
            drawBlock (i + 9, j, TETRI_COLOR[checker.block[i][j + 1]]);
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


void DrawData(int score){
    char buffer[100];
    SetPenColor("Black");
    sprintf(buffer,"Score: %d",score);
    MovePen(ScoreX*BLOCKSIZE,ScoreY*BLOCKSIZE);
    DrawTextString(buffer);

    sprintf(buffer,"Level: %d",score/LevelGap + 1);
    MovePen(LevelX*BLOCKSIZE,LevelY*BLOCKSIZE);
    DrawTextString(buffer);

    sprintf(buffer,"Speed: %.2f",ctetri.yVelocity/DEBUG_SLOW);
    if(ctetri.yVelocity>10){
        SetPenColor("White");
    }
    MovePen(SpeedX*BLOCKSIZE,SpeedY*BLOCKSIZE);
    DrawTextString(buffer);

}

void DrawNextTetrimino(tetrimino tetri){
    //MovePen();
    tetri.x = PreX+3;
    tetri.y = PreY+2;
    drawTetri(tetri);
}

void DrawHoldedTetrimino(tetrimino tetri){
    //MovePen();
    tetri.x = HoldX+3;
    tetri.y = HoldY+2;
    drawTetri(tetri);
}

string RandColor(){
    int flag;
    flag = rand()%7;
    if(flag != 0) flag = 7;
    return TETRI_COLOR[flag];
}

void DrawPulse(){
    for (int i = 1; i < 13; i++) {
        for (int j = 0; j < HEIGHT; j++) {
            drawBlock (i + 9, j, "Gray");
            if((i == 4 && j >= 2 && j <= 14)||((j==9||j==14)&&i>4&&i<=9)||(i==10 && j >= 9 && j <= 14)){
                drawBlock (i + 9, j, RandColor());
            }
        }
    }
    DrawGrid();
}


#endif