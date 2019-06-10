#include "handlers_2p.h"
#include "graphics.h"

#include "consts_2p.h"
#include "drawers_2p.h"
#include "model_2p.h"
#include <winuser.h>

#include "imgui.h"
void mouseEventHandler (int x, int y, int button, int event){
    uiGetMouse(x,y,button,event);
}
void keyboardEventHandler (int key, int event){
    tetrimino temp[2];
    temp[LEFT] = ctetri[LEFT];
    temp[RIGHT] = ctetri[RIGHT];
    int flag = 2;
        switch (event) {
            case KEY_DOWN:
                switch (key) {
                    case VK_LEFT:
                        temp[RIGHT].x -= 1;
                        flag = RIGHT;
                        break;
                    case VK_RIGHT:
                        temp[RIGHT].x += 1;
                        flag = RIGHT;
                        break;
                    case VK_DOWN:
                        temp[RIGHT].yVelocity = FAST;
                        flag = RIGHT;
                        break;
                    case VK_UP :
                        temp[RIGHT].direction += 3;
                        temp[RIGHT].direction %= 4;
                        flag = RIGHT;
                        break;
                    case 0x61: // numpad 1
                        temp[RIGHT].direction++;
                        temp[RIGHT].direction %= 4;
                        flag = RIGHT;
                        break;
                    case 0x60://numpad 0
                        temp[RIGHT] = HardDrop(temp[RIGHT]);
                        flag = RIGHT;
                        break;
                    case VK_ESCAPE: //P
                        //temp = PauseEventHandler(temp);
                        break;
//                    case 0x43: // C
//                        temp[LEFT] = HoldEventHandler(temp[LEFT]);
//                        flag = RIGHT;
//                        break;
                        //MenuBar
                    case 0x4D://M
//                    MusicOn ^= 1;
                        BGM_maintainer(MusicOn ^ 1);
                        break;
                    case 0x41: //A
                        temp[LEFT].x -= 1;
                        flag = LEFT;
                        break;
                    case 0x44://D
                        temp[LEFT].x += 1;
                        flag = LEFT;
                        break;
                    case 0x53://S
                        temp[LEFT].yVelocity = FAST;
                        flag = LEFT;
                        break;
                    case 0x57 ://W
                        temp[LEFT].direction += 3;
                        temp[LEFT].direction %= 4;
                        flag = LEFT;
                        break;
                    case 0x51: // Q
                        temp[LEFT].direction++;
                        temp[LEFT].direction %= 4;
                        flag = LEFT;
                        break;
                    case VK_SPACE:
                        temp[LEFT] = HardDrop(temp[LEFT]);
                        flag = LEFT;
                        break;
                    case 0x52: //R
                        Restart();
                        break;
                    default:
                        uiGetKeyboard(key, event); // GUIªÒ»°º¸≈Ã
                        break;
                }
                break;
            case KEY_UP:
                switch (key) {
                    case VK_SPACE:
                        if(!is_game_over[1]&&!temp[1].isPaused)
                            Score[1]+=60;
                        flag = LEFT;
                        break;
                    case 0x60:
                        if(!is_game_over[0]&&!temp[0].isPaused)
                            Score[0]+=60;
                        flag = RIGHT;
                        break;
                    case 0x53://S
                        temp[LEFT].yVelocity = globalSpeed[LEFT];
                        flag = LEFT;
                        break;
                    case VK_DOWN:
                        temp[LEFT].yVelocity = globalSpeed[RIGHT];
                        flag = LEFT;
                        break;
                }
                break;
        }
        if(flag!=2) {
            if (!check_collision(temp[flag], checkerboardlist[temp[flag].position])) {
                ctetri[flag] = temp[flag];
            }
        }
}
void CharEventHandler(char c){
    uiGetChar(c);
}

