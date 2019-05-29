#include "graphics.h"
#include "extgraph.h"
#include "genlib.h"
#include "simpio.h"
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

#include "imgui.h"

// 全局变量
static double winwidth, winheight;   // 窗口尺寸
static int enable_rotation = 1;   // 允许旋转
static int show_more_buttons = 0; // 显示更多按钮

static bool isDisplayMenu = FALSE;

// 清屏函数，provided in libgraphics
void DisplayClear (void);

// 用户的显示函数
void display (void);

void DrawBasic ();
void RefreshDisplay();

void drawButtons();

// 用户的键盘事件响应函数
void KeyboardEventProcess (int key, int event)
{
//    printf ("%d\n", key);
    switch (event) {
        case KEY_DOWN:
            switch (key) {
                case 16:isDisplayMenu ^= 1;
//                    printf ("%d\n", isDisplayMenu);
                    break;
                default:uiGetKeyboard (key, event); // GUI获取键盘
                    break;
            }
            break;
        case KEY_UP:
            switch (key) {
                case 16:break;
                default:uiGetKeyboard (key, event); // GUI获取键盘
                    break;
            }
        default:break;
    }
    if (isDisplayMenu)
        display (); // 刷新显示
    else
    {
        RefreshDisplay();
    }
}

// 用户的鼠标事件响应函数
void MouseEventProcess (int x, int y, int button, int event)
{
    uiGetMouse (x, y, button, event); //GUI获取鼠标
    if (isDisplayMenu) {
        display (); // 刷新显示
    } else {
        RefreshDisplay();
    }
}

// 用户主程序入口
// 仅初始化执行一次
void Main ()
{
    // 初始化窗口和图形系统
    SetWindowTitle ("Teris Launcher");
    //SetWindowSize(10, 10); // 单位 - 英寸
    //SetWindowSize(20, 10);
    //SetWindowSize(10, 20);  // 如果屏幕尺寸不够，则按比例缩小
    InitGraphics ();

    // 获得窗口尺寸
    winwidth = GetWindowWidth ();
    winheight = GetWindowHeight ();

    setMenuColors("Black", "White", "Gray", "White", 1);

    // 注册时间响应函数
    registerKeyboardEvent (KeyboardEventProcess);// 键盘
    registerMouseEvent (MouseEventProcess);      // 鼠标


    DrawBasic ();
    // 打开控制台，方便输出变量信息，便于调试
    // InitConsole();
    PlaySound("C:\\Users\\Tao Chiang\\Desktop\\Skyworld.wav", NULL, SND_FILENAME | SND_ASYNC);
}

// 菜单演示程序
void drawMenu ()
{
    static char *menuListFile[] = {"File",
                                   "Leader Board  | Ctrl-B", // 快捷键必须采用[Ctrl-X]格式，放在字符串的结尾
//                                    "Close",
                                   "Exit             | Ctrl-E"};
    static char *menuListTool[] = {"Tool",
                                   "Triangle",
                                   "Circle",
                                   "Stop Rotation | Ctrl-T"};
    static char *menuListHelp[] = {"Help",
                                   "Show More  | Ctrl-M",
                                   "About"};
    static char *selectedLabel = NULL;

    double fH = GetFontHeight ();
    double x = 0; //fH/8;
    double y = winheight;
    double h = fH * 1.5; // 控件高度
//    double w = TextStringWidth (menuListHelp[0]) * 2; // 控件宽度
    double w = winwidth / 3;
    double wlist = TextStringWidth (menuListTool[3]) * 1.2;
    double xindent = winheight / 20; // 缩进
    int selection;

    // File 菜单
    selection = menuList (GenUIID(0), x,
                          y - h, w, wlist, h, menuListFile, sizeof (menuListFile) / sizeof (menuListFile[0]));
    if (selection > 0) selectedLabel = menuListFile[selection];
    if (selection == 1)
        WinExec("leaderboard.exe", SW_SHOW);
    if (selection == 2)
        exit (-1); // choose to exit

    // Tool 菜单
    menuListTool[3] = enable_rotation ? "Stop Rotation | Ctrl-T" : "Start Rotation | Ctrl-T";
    selection = menuList (GenUIID(0),
                          x + w, y - h, w, wlist, h, menuListTool, sizeof (menuListTool) / sizeof (menuListTool[0]));
    if (selection > 0) selectedLabel = menuListTool[selection];
    if (selection == 3)
        enable_rotation = !enable_rotation;

    // Help 菜单
    menuListHelp[1] = show_more_buttons ? "Show Less | Ctrl-M" : "Show More | Ctrl-M";
    selection = menuList (GenUIID(0),
                          x + 2 * w,
                          y - h, w, wlist, h, menuListHelp, sizeof (menuListHelp) / sizeof (menuListHelp[0]));
    if (selection > 0) selectedLabel = menuListHelp[selection];
    if (selection == 1)
        show_more_buttons = !show_more_buttons;
    if (selection == 2)
        MessageBoxA (NULL, "这是我们的大作业！", "关于 | About", MB_ICONINFORMATION);;
}

void display ()
{
    // 清屏
    RefreshDisplay ();
    // 绘制和处理菜单
    drawMenu ();
}

void RefreshDisplay ()
{
    DisplayClear ();
    DrawBasic ();
}

void DrawBasic ()
{
//    SetPenColor ("Black");
//    DrawLine (1,1);
    SetFont ("微软雅黑");
    drawButtons ();
    SetPenColor ("Black");
//    printf("%s\n", GetFont ());
    SetFont ("微软雅黑");
    SetPointSize(64);
    MovePen (winwidth/2 - TextStringWidth("Teris")/2, winheight/2 + 1);
    DrawTextString ("Teris");
    SetPointSize (13);
}

void drawButtons()
{
    double fH = GetFontHeight();
    double h = fH*2;  // 控件高度
    double x = winwidth/2.5;
    double y = winheight/2-h;
    double w = winwidth/5; // 控件宽度
//
//    if (button(GenUIID(0), x, y, w, h, show_more_buttons ? "Show Less Buttons" : "Show More Buttons"))
//        show_more_buttons = ! show_more_buttons;
//
//    if( show_more_buttons ) {
//        int k;
//        for( k = 0; k<3; k++ ) {
//            char name[128]; sprintf(name, "Button Array %d", k);
//            // use GenUIID(k) to have different ID for multiple buttons by the same code
//            button(GenUIID(k), x + w*1.2, y - k*h*2, w, h, name);
//        }
//    }

    x = winwidth / 2 - 1;
    y = winheight / 2 - 0.6;
    setButtonColors("Black", "White", "Gray", "White", 1);
    if (button(GenUIID(0), x, y, 2, 1.2, "Single Mode"))
    {
        WinExec("single_main.exe", SW_SHOW);
    }
    if (button(GenUIID(0), x, y - 0.8, 2, 0.6, "Leader Board"))
    {
        WinExec("leaderboard.exe", SW_SHOW);
    }

}