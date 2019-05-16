//
// Created by liujunliang on 2019/5/13.
//
#include "graphics.h"
#include "consts.c"
#include <winuser.h>

tetrimino tetriMaintainer_on_Keyboard(int RL,tetrimino tetri){
    switch(RL) {
        case VK_RIGHT:
            tetri.x += 1;
            break;
        case VK_LEFT:
            tetri.x -= 1;
            break;
            //case VK_UP:
            //case VK_DOWN:
        default:
            break;
    }
    return tetri;
}

void keyboardEventHandler(int key, int event){
    switch (event) {
            case KEY_DOWN:
                //tetriMaintainer_on_Keyboard(key,NaT);
                break;
            case KEY_UP:
                break;
}
}


void mouseEventHandler(int x,int y, int button, int event){

}