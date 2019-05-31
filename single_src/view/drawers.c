#ifndef _DRAWERS_C
#define _DRAWERS_C

#include <windows.h>
#include <string.h>
#include <math.h>
#include "drawers.h"
#include "handlers.h"
#include "consts.h"
#include "model.h"
#include "imgui.h"

void DefineRGBColor (string s, int r, int g, int b)
{
    DefineColor (s, r / 255.0, g / 255.0, b / 255.0);
}
void DefineColors ()
{
    DefineRGBColor ("Magenta", 138, 43, 226); //blueviolet
    DefineRGBColor ("Blue", 30, 144, 255); //dodgerblue
    DefineRGBColor ("Cyan", 127, 255, 212); //aquamarine
    DefineRGBColor ("Yellow", 255, 215, 0); //gold
    DefineRGBColor ("Green", 34, 139, 34);//forestgreen
    DefineRGBColor ("Light Gray", 105, 105, 105);//dimgray
    DefineRGBColor ("Red", 220, 20, 60);//crimson
    DefineRGBColor ("Dark Turquoise", 0, 206, 209);//dark turquoise
    DefineRGBColor ("Midnight Blue", 25, 25, 112);
    DefineRGBColor ("Corn Silk", 255, 248, 220);
    DefineRGBColor ("Light Cyan", 224, 255, 255);
    DefineRGBColor ("Gainsboro", 220, 220, 220);
    DefineRGBColor ("White Smoke",245, 245, 245);
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
                drawBlock (
                    tetri.x + typeInfo[tetri.type][i][0],
                    tetri.y + typeInfo[tetri.type][i][1], TETRI_COLOR[tetri.type]);
            }
            break;
        case 1:
            for (int i = 0; i < 4; i++) {
                drawBlock (
                    tetri.x - typeInfo[tetri.type][i][1],
                    tetri.y + typeInfo[tetri.type][i][0], TETRI_COLOR[tetri.type]);
            }
            break;
        case 2:
            for (int i = 0; i < 4; i++) {
                drawBlock (
                    tetri.x - typeInfo[tetri.type][i][0],
                    tetri.y - typeInfo[tetri.type][i][1], TETRI_COLOR[tetri.type]);
            }
            break;
        case 3:
            for (int i = 0; i < 4; i++) {
                drawBlock (
                    tetri.x + typeInfo[tetri.type][i][1],
                    tetri.y - typeInfo[tetri.type][i][0], TETRI_COLOR[tetri.type]);
            }
            break;
    }
}
void DrawGrid ()
{
    SetPenColor ("Black");

    //draw Checkerboard Grid
    for (int i = LEFTBAR; i <= LEFTBAR + 12; i++) {
        MovePen (i * BLOCKSIZE, 0);
        DrawLine (0, GetWindowHeight ());
    }

    for (int j = 0; j <= HEIGHT; j++) {
        MovePen (LEFTBAR * BLOCKSIZE, j * BLOCKSIZE);
        DrawLine (12 * BLOCKSIZE, 0);
    }

    //draw Next Tetri area
    for (int i = PreX; i <= PreX + 4; i++) {
        MovePen (i * BLOCKSIZE, PreY * BLOCKSIZE);
        DrawLine (0, 4 * BLOCKSIZE);
    }
    for (int i = PreY; i <= PreY + 4; i++) {
        MovePen (PreX * BLOCKSIZE, i * BLOCKSIZE);
        DrawLine (4 * BLOCKSIZE, 0);
    }

    for (int i = HoldX; i <= HoldX + 4; i++) {
        MovePen (i * BLOCKSIZE, HoldY * BLOCKSIZE);
        DrawLine (0, 4 * BLOCKSIZE);
    }
    for (int i = HoldY; i <= HoldY + 4; i++) {
        MovePen (HoldX * BLOCKSIZE, i * BLOCKSIZE);
        DrawLine (4 * BLOCKSIZE, 0);
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
void DrawSideBar(){
    for (int i = 0; i < LEFTBAR; i++) {
        for (int j = 0; j < HEIGHT; j++) {
            drawBlock (i, j, "Gray");
        }
    }
    for (int i = LEFTBAR + 12; i < WIDTH; i++) {
        for (int j = 0; j < HEIGHT; j++) {
            if (!((i >= PreX && i < PreX + 4 && j >= PreY && j < PreY + 4)
                  || (i >= HoldX && i < HoldX + 4 && j >= HoldY && j < HoldY + 4)))//to show Next Tetri
                drawBlock (i, j, "Gray");
        }
    }
}

void drawUI (int score)
{
    DrawSideBar();

    DrawNextTetrimino (que[1]);
    DrawHoldedTetrimino (HeldTetri);


    DrawData (score);
    DrawMenu();
    DrawDynamicButtons();
    DrawBottomBar();

    DrawGrid ();

    //DebugTool();

}
void drawCheckerBoard (Checkerboard checker)
{
    for (int i = 1; i < 13; i++) {
        for (int j = 0; j < HEIGHT; j++) {
            drawBlock (i + LEFTBAR - 1, j, TETRI_COLOR[checker.block[i][j + 1]]);
        }
    }
}

void drawShadowBlock (int x, int y, string color)
{
    SetPenColor (color);

    SetPenSize (GetPenSize () + 3);
    MovePen (x * BLOCKSIZE, y * BLOCKSIZE);
    DrawRect (BLOCKSIZE, BLOCKSIZE);

    SetPenColor ("Black");
    SetPenSize (GetPenSize () - 3);
//    MovePen (x * BLOCKSIZE, y * BLOCKSIZE);
//    DrawRect (BLOCKSIZE, BLOCKSIZE);
}

void DrawShadow (tetrimino shadow)
{
    if (shadow.y > ctetri.y) {
        return;
    }
    switch (shadow.direction) {
        case 0:
            for (int i = 0; i < 4; i++) {
                drawShadowBlock (
                    shadow.x + typeInfo[shadow.type][i][0],
                    shadow.y + typeInfo[shadow.type][i][1], TETRI_COLOR[shadow.type]);
            }
            break;
        case 1:
            for (int i = 0; i < 4; i++) {
                drawShadowBlock (
                    shadow.x - typeInfo[shadow.type][i][1],
                    shadow.y + typeInfo[shadow.type][i][0], TETRI_COLOR[shadow.type]);
            }
            break;
        case 2:
            for (int i = 0; i < 4; i++) {
                drawShadowBlock (
                    shadow.x - typeInfo[shadow.type][i][0],
                    shadow.y - typeInfo[shadow.type][i][1], TETRI_COLOR[shadow.type]);
            }
            break;
        case 3:
            for (int i = 0; i < 4; i++) {
                drawShadowBlock (
                    shadow.x + typeInfo[shadow.type][i][1],
                    shadow.y - typeInfo[shadow.type][i][0], TETRI_COLOR[shadow.type]);
            }
            break;
    }
}

void DrawData (int score)
{
    char buffer[100];
    SetPenColor ("Black");
    sprintf (buffer, "Score: %d", score);
    MovePen (ScoreX * BLOCKSIZE, ScoreY * BLOCKSIZE);
    DrawTextString (buffer);

    sprintf (buffer, "Level: %d", score / LevelGap + 1);
    MovePen (LevelX * BLOCKSIZE, LevelY * BLOCKSIZE);
    DrawTextString (buffer);

    sprintf (buffer, "Speed: %.2f", ctetri.yVelocity / INIT_SPEED);
    if (ctetri.yVelocity > 10) {
        SetPenColor ("White");
    }
    MovePen (SpeedX * BLOCKSIZE, SpeedY * BLOCKSIZE);
    DrawTextString (buffer);

    SetPointSize(GetPointSize()*2);

    if(Rename) {
        SetStyle(2);
        setTextBoxColors ("Gray", RandColor(), "Gray", RandColor(), 0);
        textbox(GenUIID(0), BLOCKSIZE * 0.9, GetWindowHeight() - 3.3 * BLOCKSIZE, 4 * BLOCKSIZE, 1.20 * GetFontHeight(),
                username, sizeof(username));
        SetStyle(0);
    }else {
        SetStyle(2);
        SetPenColor("White");
        drawLabel(fabs(0.5 *((LEFTBAR-1)*BLOCKSIZE - TextStringWidth(username)) ),GetWindowHeight() - 3.1*BLOCKSIZE ,username);
        SetStyle(0);
    }
    SetPointSize(GetPointSize()/2);

    SetPenColor("Black");
    SetPointSize(GetPointSize()*2);
    SetStyle(2);
    drawLabel(BLOCKSIZE/5,GetWindowHeight() - 2 * BLOCKSIZE, "CurrentPlayer");
    SetPointSize(GetPointSize()/3);
    SetStyle(0);

}

void DrawNextTetrimino (tetrimino tetri)
{
    //MovePen();
    if (tetri.type == 0)return;
    tetri.x = PreX + 2;
    tetri.y = PreY + 1;
    drawTetri (tetri);
}

void DrawHoldedTetrimino (tetrimino tetri)
{
    //MovePen();
    if (tetri.type == 0)return;
    tetri.x = HoldX + 2;
    tetri.y = HoldY + 1;
    drawTetri (tetri);
}

string RandColor ()
{
    int flag;
    flag = rand ();
    if (flag % 2) {
        flag = rand () % 8;
    } else {
        if (rand () % 2 == 0)
            flag = 0;
    }
    return TETRI_COLOR[flag % 8];
}

void DrawBoard (int flag)
{
    for (int i = 1; i < 13; i++) {
        for (int j = 0; j < HEIGHT; j++) {
            if (flag == PAUSE) {
                drawBlock (i + LEFTBAR - 1, j, (Rename)?TETRI_COLOR[que[1].type]:RandColor ());
            } else {

            }
        }
    }
    int temp = GetPointSize ();
    DrawGrid ();
    double x = 0.5 * (GetWindowWidth () - 8 * BLOCKSIZE);
    double y = 0.5 * (GetWindowHeight () - 7 * BLOCKSIZE);
    SetPenColor ("Black");
    StartFilledRegion (1);
    MovePen (x, y);
    DrawRect (8 * BLOCKSIZE, 7 * BLOCKSIZE);
    EndFilledRegion ();
    SetPenColor ("White");

    SetPointSize (temp * 2);
    if (flag == PAUSE) {
        drawLabel (x + (8 * BLOCKSIZE - TextStringWidth ("Paused!")) / 2, y + 7 * BLOCKSIZE - GetFontHeight (), "Paused!");
        SetPointSize (temp);
        drawBoardButtons (x, y + 7 * BLOCKSIZE - 7 * BLOCKSIZE / 3, PAUSE);
    } else {
        drawLabel (x + (8 * BLOCKSIZE - TextStringWidth ("Game Over")) / 2, y + 7 * BLOCKSIZE - GetFontHeight (), "Game Over");
        SetPointSize (temp);
        drawBoardButtons (x, y + 7 * BLOCKSIZE - 7 * BLOCKSIZE / 3, GAMEOVER);
    }
}

void drawBoardButtons (double x, double y, int flag)
{
    double h, w = 8 * BLOCKSIZE; // 控件宽度
    char buffer[100];
    int row = 0;
    if (flag == PAUSE) {
        h = 7 * BLOCKSIZE / 6;  // 控件高度
        setButtonColors ("Corn Silk", "Black", "Light Cyan", "Midnight Blue", 1);
        SetStyle (1);
        if (button (GenUIID(0), x, y - h* row++, w, h, "Resume")) {
            keyboardEventHandler (VK_ESCAPE, KEY_DOWN);
        }
        if (button (GenUIID(0), x, y - h* row++, w, h, (Rename)?"Done":"Rename")) {
            reName();
        }
        if (button (GenUIID(0), x, y - h* row++, w, h, "RankList")) {
            WinExec ("leaderboard.exe", SW_SHOW);
        }
        if (button (GenUIID(0), x, y - h* row++, w, h, "Restart")) {
//          keyboardEventHandler (0x52, KEY_DOWN);
            Restart ();
        }
        if (button (GenUIID(0), x, y - h* row++, w, h, "Save")) {
            SaveGame ();
        }
        if (button (GenUIID(0), x, y - h* row, w, h, "Quit")) {
            ExitGame ();
        }
    } else { // GAME OVER Board
        h = 7 * BLOCKSIZE / 5;
        setButtonColors ("Corn Silk", "Black", "Light Cyan", "Midnight Blue", 1);
        setTextBoxColors("Black", "White", "Midnight Blue", "White", 1);
        SetStyle (1);
        sprintf(buffer, "Score: %d  ", Score);//Name: %s ,username
        drawLabel (x + (4 * BLOCKSIZE - TextStringWidth (buffer)) / 2, y + 1.50 * GetFontHeight (), buffer);
        drawLabel(x + 3.5*BLOCKSIZE , y +  1.50 * GetFontHeight (),username);
        if (button (GenUIID(0), x, y - h, w, h, (Rename)?"Done":"Rename")) {
            reName();
        }
        if (button (GenUIID(0), x, y - 2 * h, w, h, "Upload")) {
            Upload();
        }
        if (button (GenUIID(0), x, y - 3 * h, w, h, "RankList")) {
            WinExec ("leaderboard.exe", SW_SHOW);
        }
        if (button (GenUIID(0), x, y - 4 * h, w, h, "Restart")) {
            keyboardEventHandler (0x52, KEY_DOWN);
        }

        if (button (GenUIID(0), x, y - 5 * h, w, h, "Quit")) {
            ExitGame ();
        }
    }

}

void DrawMenu()
{
    static char *menuListFile[] = {
        "File",
        "NewGame  | Ctrl-O",
        "Save | Ctrl-S",
        "Load | Ctrl-L",
        "Exit to Launcher  | Ctrl-E"
    };
    static char *menuListGame[] = {
        "Game",
        "Pause | Ctrl-P",
        "Show Rank List | Ctrl-T",
        "MouseMode | Ctrl-H",
        "Restart | Ctrl-R"
    };
    static char *menuListHelp[] = {
        "Help",
        "About"
    };

    double fH = GetFontHeight ();
    double x = 0; //fH/8;
    double y = GetWindowHeight ();
    double h = fH * 1.5; // ??????
    double w = LEFTBAR * BLOCKSIZE / 3; // ???????
    double wlist = TextStringWidth (menuListFile[4]) * 1.2;
    double xindent = GetWindowWidth () / 20; // ????
    int selection;

    // File
    selection = menuList (GenUIID(0), x, y - h, w, wlist, h, menuListFile,
                          sizeof (menuListFile) / sizeof (menuListFile[0]));
    switch (selection) {
        case 0:break;
        case 1: // restart new game
//            keyboardEventHandler (0x52, KEY_DOWN);
            Restart ();
            break;
        case 2:SaveGame ();
            break;
        case 3:LoadGame ();
            break;
        case 4:ExitGame ();
            break;// choose to exit
    }
    // Game
    selection = menuList (GenUIID(0), x + w, y - h, w, wlist, h, menuListGame,
                          sizeof (menuListGame) / sizeof (menuListGame[0]));
    //menuListGame[1] = (ctetri.isPaused) ? "Resume | Ctrl-P" : "Pause | Ctrl-P";
    //menuListGame[3] = (MouseMode) ? "CancelMouse | Ctrl-H" : "MouseMode | Ctrl-H";
    switch (selection) {
        case 0:break;
        case 1: //pause
            keyboardEventHandler (VK_ESCAPE, KEY_DOWN);
            keyboardEventHandler (VK_ESCAPE, KEY_UP);
            break;
        case 2:
            WinExec ("leaderboard.exe", SW_SHOW);
            break;
        case 3:
            keyboardEventHandler(VK_F1,KEY_DOWN);
            keyboardEventHandler(VK_F1,KEY_UP);
            break;
        case 4://restart
//            keyboardEventHandler (0x52, KEY_DOWN);
            Restart ();
            break;
    }
    // Help
    selection = menuList (GenUIID(0), x + 2 * w, y - h, w, wlist, h, menuListHelp,
                          sizeof (menuListHelp) / sizeof (menuListHelp[0]));
    switch (selection) {
        case 0:break;
        case 1:
            MessageBoxA (NULL, "单人模式", "关于 | About", MB_ICONINFORMATION);
            break;
    }
}

void DrawBottomBar(){
    MovePen(0,0);
    SetPenColor("Light Gray");
    StartFilledRegion(1);
    DrawRect(LEFTBAR*BLOCKSIZE ,GetFontHeight()*1.5);
    EndFilledRegion();

    SetPenColor("Black");
    MovePen(0,GetFontHeight()*1.5);
    DrawLine(LEFTBAR*BLOCKSIZE,0);

    SetPenColor("White");
    char buffer[32];
    sprintf(buffer,"Music : %s  MouseMode : %s",(MusicOn)?"On":"Off",(MouseMode)?"On":"Off");
    drawLabel(0.1*BLOCKSIZE,GetFontHeight()/2,buffer);
//    MovePen(0,GetFontHeight()*1.1);
//    DrawLine(LEFTBAR*BLOCKSIZE,0);

};

void DrawDynamicButtons()
{
    double x , y = GetWindowHeight()/3;
    double h, w = (LEFTBAR-1) * BLOCKSIZE; // 控件宽度
    x = (LEFTBAR*BLOCKSIZE - w)/2;
    h = 7 * BLOCKSIZE / 6;  // 控件高度

        setButtonColors ("Corn Silk", "Black", "Light Cyan", "Midnight Blue", 1);
        SetStyle (1);
        if (button (GenUIID(0), x, y, w, h, "Accelerate!")) {
            keyboardEventHandler (VK_DOWN, KEY_DOWN);
        }
    if (button (GenUIID(0), x, y - h, w, h, "Rotate")) {
        keyboardEventHandler (VK_UP, KEY_DOWN);
    }
        if (button (GenUIID(0), x, y - 2*h, w, h, "Save")) {
            keyboardEventHandler(VK_CONTROL,KEY_DOWN);
            keyboardEventHandler(0x53,KEY_DOWN);
            keyboardEventHandler(VK_CONTROL,KEY_UP);
        }
    if (button (GenUIID(0), x, y - 2*h, w, h, (MouseMode)?"Cancel Mouse Mode":"Mouse Mode")) {
        MouseMode ^= 1;
    }

}
void DebugTool() {
    char buffer[100];
    sprintf(buffer, "cx : %f,cy: %f\n", xx, yy);
    drawLabel((LEFTBAR + 13) * BLOCKSIZE, GetWindowHeight() / 2, buffer);
    drawLabel((LEFTBAR + 13) * BLOCKSIZE, GetWindowHeight() / 2 - GetFontHeight(), (InCheckerBoard(xx,yy))?"InChe":"NoI");
    sprintf(buffer,"CBlock%d",XInchScaleToBlock(xx));
    drawLabel((LEFTBAR + 13) * BLOCKSIZE, GetWindowHeight() / 2 - 2*GetFontHeight(), buffer);
    sprintf(buffer,"TBlock%d",ctetri.x - LEFTBAR);
    drawLabel((LEFTBAR + 13) * BLOCKSIZE, GetWindowHeight() / 2 - 3*GetFontHeight(), buffer);
}

void MessageBoxB(string title1,string color1){
    static int count = 4;
    static string title,color;
    if(count == 4){
        cancelTimer(GAME);
        startTimer(LOADING,20);
        if(title1){
            title = title1;
        }
        if(color1){
            color = color1;
        }
        count--;
        return;
    }
    if(count == 0){
        //keyboardEventHandler(VK_ESCAPE,KEY_DOWN);
        cancelTimer(LOADING);
        count = 4;
        startTimer(GAME,10);
        return;
    }
    if(count == 3){
        cancelTimer(LOADING);
        startTimer(LOADING,1000);
    }


    double width = 7*BLOCKSIZE, heigt = 4 * BLOCKSIZE;
    char buffer[20];
    sprintf(buffer,"%s in %d ...",title,count--);


    MovePen(GetWindowWidth()/2 - width/2,GetWindowHeight()/2 - heigt/2);
    SetPenColor(color);
    StartFilledRegion(1);
    DrawRect(width,heigt);
    EndFilledRegion();

    SetPenColor("White");
    SetPointSize(GetPointSize()*2);
    drawLabel(GetWindowWidth()/2 - TextStringWidth(buffer)/2, GetWindowHeight()/2 - GetFontHeight()/3,buffer);
    SetPointSize(GetPointSize()/2);
}
#endif