//
// Created by liujunliang on 2019/5/13.
//
#include "graphics.h"
#include "consts.h"
#include "drawers.h"
#include "model.h"
#include <winuser.h>

void keyboardEventHandler (int key, int event)
{
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
                    temp.direction++;
                    temp.direction %= 4;
                    break;
                case VK_SPACE :
                    temp.yVelocity = FAST * 10;
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
    if (!check_collision (temp))
        ctetri = temp;

}
void mouseEventHandler (int x, int y, int button, int event)
{

}
