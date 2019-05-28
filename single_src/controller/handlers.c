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
    switch (event) {
        case KEY_DOWN:
            switch (key) {
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
                    temp = Restart();
                    break;
                case 0x50: // P
                    temp = PauseEventHandler(temp);
                    break;
                case 0x43: // C
                    temp = HoldEventHandler(temp);
                    break;
                 //MenuBar
                case VK_SHIFT:isDisplayMenu1 ^= 1;
//                    printf ("%d\n", isDisplayMenu);
                    break;
                default:uiGetKeyboard (key, event); // GUI获取键盘
                    break;
            }
            break;
        case KEY_UP:
            switch (key) {
                case VK_DOWN:
                    temp.yVelocity = SLOW;
                    break;
            }
            break;

    }

    if ((!check_collision (temp) && !temp.isPaused)|| key == 0x50) {
        ctetri = temp;
    }

}

void mouseEventHandler (int x, int y, int button, int event)
{
    uiGetMouse (x, y, button, event); //GUI获取鼠标
}
