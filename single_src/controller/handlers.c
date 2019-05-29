//
// Created by liujunliang on 2019/5/13.
//
#include "graphics.h"

#include "consts.h"
#include "drawers.h"
#include "model.h"
#include <winuser.h>

#include "imgui.h"


void keyboardEventHandler (int key, int event)
{
    uiGetKeyboard(key,event);
    tetrimino temp = ctetri;
    static bool ifControl = FALSE;
    switch (event) {
        case KEY_DOWN:
            switch (key) {
                case VK_CONTROL:
                    ifControl = TRUE;
                    break;
                case VK_LEFT:
                    temp.x -= 1;
                    break;
                case VK_RIGHT:
                    temp.x += 1;
                    break;
                case VK_DOWN:
                    temp.yVelocity = FAST;
                    break;
                case VK_UP :
                    temp.direction+=3;
                    temp.direction %= 4;
                    break;
                case 0x5A: // Z
                    temp.direction++;
                    temp.direction %= 4;
                    break;
                case VK_SPACE:
                    Score+=60;
                    temp = HardDrop(temp);
                    break;
                case 0x52: // R
                        Restart();
                    return;
                case VK_ESCAPE: //P
                    temp = PauseEventHandler(temp);
                    break;
                case 0x43: // C
                    temp = HoldEventHandler(temp);
                    break;
                 //MenuBar
                case 0x4D://M
                    MusicOn ^= 1;
                    //TODO stop music
                    break;
                default:uiGetKeyboard (key, event); // GUI获取键盘
                    break;
            }
            break;
        case KEY_UP:
            switch (key) {
                case VK_CONTROL:
                    ifControl = FALSE;
                case VK_DOWN:
                    temp.yVelocity = SLOW;
                    break;
            }
            break;
    }

    if ((!check_collision (temp) && !temp.isPaused)|| key == VK_ESCAPE) {
        ctetri = temp;
    }

}

void mouseEventHandler (int x, int y, int button, int event)
{
    uiGetMouse (x, y, button, event); //GUI获取鼠标
    //TODO   to key board

    xx = ScaleXInches(x);
    yy = ScaleXInches(y);
    

    if(MouseMode && InCheckerBoard(xx,yy)){

    }
}
