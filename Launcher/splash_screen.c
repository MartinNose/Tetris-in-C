#include "graphics.h"
#include "extgraph.h"
#include "genlib.h"
#include "simpio.h"
#include "random.h"
#include "strlib.h"
#include "conio.h"
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <windows.h>
#include <olectl.h>
#include <mmsystem.h>
#include <wingdi.h>
#include <ole2.h>
#include <ocidl.h>
#include <winuser.h>
#define SYSCOLOR "Red"
#define TIMER_BLINK10  1     /*50ms定时器事件标志号*/
#define TIMER_BLINK1500 2     /*1000ms定时器时间标志号*/
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
    DefineRGBColor ("White Smoke", 245, 245, 245);
    DefineRGBColor ("Seashell", 255, 245, 238);//有点像肉色
    DefineRGBColor ("Wheat", 245, 222, 179);//小麦色
    DefineRGBColor ("Pink", 255, 192, 203);
    DefineRGBColor ("Thistle", 216, 191, 216);//马卡龙紫
    DefineRGBColor ("MistyRose", 255, 228, 225);//浅粉色
    DefineRGBColor ("Azure", 135, 206, 250);//浅蓝色
    DefineRGBColor ("SeaGreen", 193, 255, 193);//马卡龙绿
};
const int mseconds10 = 50;
const int mseconds1500 = 1500;
typedef struct {/*矩形类型*/
    double x1, y1;/*左下角坐标*/
    double x2, y2;/*右上角坐标*/
    int PenSize; /*粗细*/
    string color; /*颜色*/
} *RectT;
double x, y;
void fillRectangle (double x, double y, double w, double h)
{
    MovePen (x, y);
    StartFilledRegion (1); // 开始
    DrawLine (0, h);
    DrawLine (w, 0);
    DrawLine (0, -h);
    DrawLine (-w, 0);
    EndFilledRegion ();   // 结束
}
void draw1 (void)
{

    double x, y;
    x = GetWindowWidth () / 36;
    y = GetWindowHeight () / 41;
    SetPenColor ("Red");
    MovePen (16 * x, 25 * y);
    fillRectangle (0, 0, 36 * x, 41 * y);
    /*以下绘制Tetris!*/
    SetPenColor ("White");
    fillRectangle (6 * x, 26 * y, 3 * x, y);
    fillRectangle (7 * x, 19 * y, x, 7 * y);
    fillRectangle (10 * x, 19 * y, x, 6 * y);
    fillRectangle (10 * x, 19 * y, 3 * x, y);
    fillRectangle (12 * x, 20 * y, x, y);
    fillRectangle (10 * x, 22 * y, 3 * x, y);
    fillRectangle (10 * x, 24 * y, 3 * x, y);
    fillRectangle (12 * x, 22 * y, x, 2 * y);
    fillRectangle (14 * x, 19 * y, x, 9 * y);
    fillRectangle (14 * x, 19 * y, 2 * x, y);
    fillRectangle (14 * x, 24 * y, 2 * x, y);
    fillRectangle (17 * x, 19 * y, x, 6 * y);
    fillRectangle (17 * x, 24 * y, 2 * x, y);
    fillRectangle (20 * x, 19 * y, x, 6 * y);
    fillRectangle (20 * x, 26 * y, x, y);
    fillRectangle (22 * x, 19 * y, 3 * x, 1 * y);
    fillRectangle (22 * x, 21 * y, 1 * x, 4 * y);
    fillRectangle (22 * x, 21 * y, 3 * x, 2 * y);
    fillRectangle (24 * x, 20 * y, 1 * x, 1 * y);
    fillRectangle (22 * x, 24 * y, 3 * x, 1 * y);
    fillRectangle (26 * x, 19 * y, 1 * x, 1 * y);
    fillRectangle (26 * x, 21 * y, 1 * x, 6 * y);

    /*绘制分隔条*/
    fillRectangle (0, 10 * y, 36 * x, 1 * y);
    /*绘制底部彩块*/
    SetPenColor ("Yellow");
    fillRectangle (0 * x, 7 * y, 5 * x, 3 * y);
    fillRectangle (2 * x, 4 * y, 6 * x, 3 * y);
    SetPenColor ("Blue");
    fillRectangle (0 * x, 0 * y, 8 * x, 4 * y);
    fillRectangle (0 * x, 0 * y, 2 * x, 7 * y);
    SetPenColor ("Green");
    fillRectangle (5 * x, 7 * y, 6 * x, 3 * y);
    fillRectangle (8 * x, 0 * y, 3 * x, 7 * y);
    SetPenColor ("Gray");
    fillRectangle (11 * x, 7 * y, 12 * x, 3 * y);
    SetPenColor ("Black");
    fillRectangle (11 * x, 0 * y, 3 * x, 7 * y);
    fillRectangle (11 * x, 0 * y, 9 * x, 4 * y);
    SetPenColor ("Red");
    fillRectangle (14 * x, 4 * y, 12 * x, 3 * y);
    SetPenColor ("Green");
    fillRectangle (20 * x, 0 * y, 9 * x, 4 * y);
    fillRectangle (26 * x, 0 * y, 3 * x, 7 * y);
    SetPenColor ("Yellow");
    fillRectangle (23 * x, 7 * y, 6 * x, 3 * y);
    fillRectangle (29 * x, 4 * y, 3 * x, 6 * y);
    SetPenColor ("Green");
    fillRectangle (32 * x, 4 * y, 6 * x, 6 * y);
    SetPenColor ("Blue");
    fillRectangle (29 * x, 0 * y, 7 * x, 4 * y);

}
void draw2 (void)
{
    double x, y;
    x = GetWindowWidth () / 36;
    y = GetWindowHeight () / 41;
    SetPenColor ("Red");
    MovePen (16 * x, 25 * y);
    fillRectangle (0, 0, 36 * x, 41 * y);
    /*以下绘制Tetris!*/
    SetPenColor ("Yellow");
    fillRectangle (6 * x, 26 * y, 3 * x, y);
    SetPenColor ("Wheat");
    fillRectangle (7 * x, 19 * y, x, 7 * y);
    SetPenColor ("Pink");
    fillRectangle (10 * x, 19 * y, x, 6 * y);
    SetPenColor ("Azure");
    fillRectangle (10 * x, 19 * y, 3 * x, y);
    SetPenColor ("SeaGreen");
    fillRectangle (12 * x, 20 * y, x, y);
    SetPenColor ("Cyan");
    fillRectangle (10 * x, 22 * y, 3 * x, y);
    SetPenColor ("Azure");
    fillRectangle (10 * x, 24 * y, 3 * x, y);
    SetPenColor ("MistyRose");
    fillRectangle (12 * x, 22 * y, x, 2 * y);
    SetPenColor ("SeaGreen");
    fillRectangle (14 * x, 19 * y, x, 9 * y);
    SetPenColor ("Pink");
    fillRectangle (14 * x, 19 * y, 2 * x, y);
    SetPenColor ("Yellow");
    fillRectangle (14 * x, 24 * y, 2 * x, y);
    SetPenColor ("SeaShell");
    fillRectangle (17 * x, 19 * y, x, 6 * y);
    SetPenColor ("Wheat");
    fillRectangle (17 * x, 24 * y, 2 * x, y);
    SetPenColor ("MistyRose");
    fillRectangle (20 * x, 19 * y, x, 6 * y);
    SetPenColor ("Wheat");
    fillRectangle (20 * x, 26 * y, x, y);
    SetPenColor ("Yellow");
    fillRectangle (22 * x, 19 * y, 3 * x, 1 * y);
    SetPenColor ("MistyRose");
    fillRectangle (22 * x, 21 * y, 1 * x, 4 * y);
    SetPenColor ("Gainsboro");
    fillRectangle (22 * x, 21 * y, 3 * x, 2 * y);
    SetPenColor ("Pink");
    fillRectangle (24 * x, 20 * y, 1 * x, 1 * y);
    SetPenColor ("SeaGreen");
    fillRectangle (22 * x, 24 * y, 3 * x, 1 * y);
    SetPenColor ("SeaGreen");
    fillRectangle (26 * x, 19 * y, 1 * x, 1 * y);
    SetPenColor ("Pink");
    fillRectangle (26 * x, 21 * y, 1 * x, 6 * y);

    /*绘制分隔条*/
    SetPenColor ("White");
    fillRectangle (0, 10 * y, 36 * x, 1 * y);
    /*绘制底部彩块*/
    SetPenColor ("Red");
    fillRectangle (0 * x, 7 * y, 5 * x, 3 * y);
    fillRectangle (2 * x, 4 * y, 6 * x, 3 * y);
    SetPenColor ("Wheat");
    fillRectangle (0 * x, 0 * y, 8 * x, 4 * y);
    fillRectangle (0 * x, 0 * y, 2 * x, 7 * y);
    SetPenColor ("Yellow");
    fillRectangle (5 * x, 7 * y, 6 * x, 3 * y);
    fillRectangle (8 * x, 0 * y, 3 * x, 7 * y);
    SetPenColor ("Blue");
    fillRectangle (11 * x, 7 * y, 12 * x, 3 * y);
    SetPenColor ("Brown");
    fillRectangle (11 * x, 0 * y, 3 * x, 7 * y);
    fillRectangle (11 * x, 0 * y, 9 * x, 4 * y);
    SetPenColor ("Pink");
    fillRectangle (14 * x, 4 * y, 12 * x, 3 * y);
    SetPenColor ("Red");
    fillRectangle (20 * x, 0 * y, 9 * x, 4 * y);
    fillRectangle (26 * x, 0 * y, 3 * x, 7 * y);
    SetPenColor ("Thistle");
    fillRectangle (23 * x, 7 * y, 6 * x, 3 * y);
    fillRectangle (29 * x, 4 * y, 3 * x, 6 * y);
    SetPenColor ("Gray");
    fillRectangle (32 * x, 4 * y, 6 * x, 6 * y);
    SetPenColor ("SeaGreen");
    fillRectangle (29 * x, 0 * y, 7 * x, 4 * y);
}
void PrintPercentage ()
{
    static int cnt = 0;
    char buffer[10];
    sprintf (buffer, "Loading...%d%%", cnt);
    MovePen (GetWindowWidth () / 2 - TextStringWidth (buffer) / 2, GetWindowHeight () * 0.36);
    cnt += 4;
    SetPointSize (25);
    SetPenColor ("White");
    DrawTextString (buffer);
    if (cnt == 100)
    {
        WinExec ("launcher.exe", SW_SHOW);
        exit (0);
    }
}
void TimerEventProcess (int timerID);

void Main ()
{
    SetWindowSize (6, 4.5);
    InitGraphicsB ();
    DefineColors ();
    registerTimerEvent (TimerEventProcess);

    startTimer (TIMER_BLINK10, mseconds10);
//    startTimer (TIMER_BLINK1500, mseconds1500);
}
void TimerEventProcess (int timerID)
{
    static int flag = 1;
    switch (timerID) {
        case TIMER_BLINK10: { /*50ms光标闪烁定时器*/
            if (flag == 1) {
                draw1 ();
                flag = 2;
            } else {
                draw2 ();
                flag = 1;
            }
            PrintPercentage ();
            break;
        }
        case TIMER_BLINK1500: {
            WinExec ("launcher.exe", SW_SHOW);
            exit (0);
        }
        default: break;
    }
}
