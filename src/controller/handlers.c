//
// Created by liujunliang on 2019/5/13.
//
#include "graphics.h"
#include "consts.c"
#include "drawers.c"
#include <winuser.h>




void keyboardEventHandler(int key, int event){

    switch (event) {
            case KEY_DOWN:
                switch(key) {
                    case VK_LEFT:
                    case VK_RIGHT:
                        STATE.ifKeyEvent = TRUE;
                        STATE.KeyEvent = key;
                        break;
                    case VK_DOWN:
                        STATE.V = 2;
                }
                break;
            case KEY_UP:
                break;
    }
}


void mouseEventHandler(int x,int y, int button, int event){

}