#ifndef _DRAWERS_C
#define _DRAWERS_C

#include "drawers.h"
#include "handlers.h"
#include "consts.h"
#include "model.h"
#include "imgui.h"

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
    DefineRGBColor("Dark Turquoise",0,206,209);//dark turquoise
    DefineRGBColor("Midnight Blue",25,25,112);
    DefineRGBColor("Corn Silk",255,248,220);
    DefineRGBColor("Light Cyan",224,255,255);
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
    for (int i = LEFTBAR; i <= LEFTBAR+12; i++) {
        MovePen(i*BLOCKSIZE,0);
        DrawLine(0,GetWindowHeight());
    }

    for (int j = 0; j <= HEIGHT; j++) {
        MovePen(LEFTBAR*BLOCKSIZE,j*BLOCKSIZE);
        DrawLine(12*BLOCKSIZE,0);
    }

    //draw Next Tetri area
    for(int i = PreX;i<=PreX + 4;i++){
        MovePen(i*BLOCKSIZE,PreY*BLOCKSIZE);
        DrawLine(0,4*BLOCKSIZE);
    }
    for(int i = PreY;i<=PreY + 4;i++){
        MovePen(PreX*BLOCKSIZE,i*BLOCKSIZE);
        DrawLine(4*BLOCKSIZE,0);
    }

    for(int i = HoldX;i<=HoldX + 4;i++){
        MovePen(i*BLOCKSIZE,HoldY*BLOCKSIZE);
        DrawLine(0,4*BLOCKSIZE);
    }
    for(int i = HoldY;i<=HoldY + 4;i++){
        MovePen(HoldX*BLOCKSIZE,i*BLOCKSIZE);
        DrawLine(4*BLOCKSIZE,0);
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

void drawUI(int score, tetrimino NextTetri)
{
    for (int i = 0; i < LEFTBAR; i++) {
        for (int j = 0; j < HEIGHT; j++) {
            drawBlock (i, j, "Gray");
        }
    }
    for (int i = LEFTBAR + 12; i < WIDTH; i++) {
        for (int j = 0; j < HEIGHT; j++) {
            if(!((i>=PreX && i < PreX + 4 && j >= PreY && j < PreY + 4)||(i>=HoldX && i < HoldX + 4 && j >= HoldY && j < HoldY + 4)))//to show Next Tetri
                drawBlock(i, j, "Gray");
        }
    }

    drawMenu();
    DrawNextTetrimino(NextTetri);
    DrawHoldedTetrimino(HoldedTetri);


    DrawGrid ();
    DrawData(score);

}
void drawCheckerBoard(Checkerboard checker){
    for (int i = 1; i < 13; i++) {
        for (int j = 0; j < HEIGHT; j++) {
            drawBlock (i + LEFTBAR - 1, j, TETRI_COLOR[checker.block[i][j + 1]]);
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

    sprintf(buffer,"Speed: %.2f",ctetri.yVelocity/INIT_SPEED);
    if(ctetri.yVelocity>10){
        SetPenColor("White");
    }
    MovePen(SpeedX*BLOCKSIZE,SpeedY*BLOCKSIZE);
    DrawTextString(buffer);

}

void DrawNextTetrimino(tetrimino tetri){
    //MovePen();
    tetri.x = PreX+2;
    tetri.y = PreY+1;
    drawTetri(tetri);
}

void DrawHoldedTetrimino(tetrimino tetri){
    //MovePen();
    if(tetri.type == 0 )return;
    tetri.x = HoldX+2;
    tetri.y = HoldY+1;
    drawTetri(tetri);
}

string RandColor(){
    int flag;
    flag = rand();
    if(flag%2){
        flag = rand()%7;
    }else {
        flag = 0;
    }
    return TETRI_COLOR[flag];
}

void DrawPulseBoard(){
    for (int i = 1; i < 13; i++) {
        for (int j = 0; j < HEIGHT; j++) {
            drawBlock (i + LEFTBAR - 1, j, RandColor());
        }
    }
    int temp = GetPointSize();
    DrawGrid();
    double x = 0.5*(GetWindowWidth()-8*BLOCKSIZE);
    double y = 0.5*(GetWindowHeight() - 7*BLOCKSIZE);
    SetPenColor("Black");
    StartFilledRegion(1);
    MovePen(x,y);
    DrawRect(8*BLOCKSIZE,7*BLOCKSIZE);
    EndFilledRegion();
    SetPenColor("White");

    SetPointSize(temp*2);
    drawLabel(x+(8*BLOCKSIZE-TextStringWidth("Paused!"))/2,y+7*BLOCKSIZE- GetFontHeight(),"Paused!");
    SetPointSize(temp);
    drawPauseButtons(x,y+7*BLOCKSIZE-7*BLOCKSIZE/3);
}


void drawPauseButtons(double x, double y)
{

    double h = 7*BLOCKSIZE/6;  // 控件高度
    double w = 8 * BLOCKSIZE; // 控件宽度

    setButtonColors("Corn Silk", "Black", "Light Cyan", "Midnight Blue", 1);
    SetStyle(1);
    if (button(GenUIID(0), x,y,w,h,"Resume"))
    {
        keyboardEventHandler(0x50,KEY_DOWN);
    }
    if (button(GenUIID(0), x, y - h, w, h, "RankList"))
    {

    }
    if (button(GenUIID(0), x, y - 2*h, w, h, "Restart"))
    {
        keyboardEventHandler(0x52, KEY_DOWN);
    }
    if (button(GenUIID(0), x, y - 3*h, w, h, "Save"))
    {

    }
    if (button(GenUIID(0), x, y - 4*h, w, h, "QUIT"))
    {

    }
    SetStyle(0);
}


void drawMenu() {
    static bool isPaused = FALSE;

    static char *menuListFile[] = {
            "File",
            "NewGame  | Ctrl-O", // ???????????[Ctrl-X]?????????????????β
            "Save",
            "Exit to Launcher  | Ctrl-E"
    };
    static char *menuListGame[] = {
            "Game",
            "Pause",
            "Show Rank List | Ctrl-T",
            "Restart"
    };
    static char *menuListHelp[] = {
            "Help",
            "About"
    };

    double fH = GetFontHeight();
    double x = 0; //fH/8;
    double y = GetWindowHeight();
    double h = fH * 1.5; // ??????
    double w = LEFTBAR * BLOCKSIZE / 3; // ???????
    double wlist = TextStringWidth(menuListFile[3]) * 1.2;
    double xindent = GetWindowWidth() / 20; // ????
    int selection;

    // File
    selection = menuList(GenUIID(0), x, y - h, w, wlist, h, menuListFile,
                         sizeof(menuListFile) / sizeof(menuListFile[0]));
    switch (selection) {
        case 0:
            break;
        case 3:
            ExitGame();
            break;// choose to exit
    }
    // Game
    selection = menuList(GenUIID(0), x + w, y - h, w, wlist, h, menuListGame,
                         sizeof(menuListGame) / sizeof(menuListGame[0]));
    menuListGame[1] = (ctetri.isPaused)?"Resume":"Pause";
    switch (selection) {
        case 0:
            break;
        case 1://pause
            keyboardEventHandler(0x50,KEY_DOWN);
            break;
        case 3://restart
            keyboardEventHandler(0x52, KEY_DOWN);
            break;
    }
    // Help
    selection = menuList(GenUIID(0), x + 2 * w, y - h, w, wlist, h, menuListHelp,
                         sizeof(menuListHelp) / sizeof(menuListHelp[0]));
    switch (selection) {
        case 0:
            break;
        case 3:
            break;// choose to exit
    }
}




#endif