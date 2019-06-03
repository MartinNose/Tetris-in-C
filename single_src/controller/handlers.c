#include "graphics.h"

#include "consts.h"
#include "drawers.h"
#include "model.h"
#include <winuser.h>

#include "imgui.h"

void keyboardEventHandler (int key, int event)
{
    uiGetKeyboard (key, event);
    tetrimino temp = ctetri;
    if (!Rename) {
        switch (event) {
            case KEY_DOWN:
                switch (key) {
                    case VK_LEFT:temp.x -= 1;
                        break;
                    case VK_RIGHT:temp.x += 1;
                        break;
                    case VK_DOWN:temp.yVelocity = FAST;
                        break;
                    case VK_UP :temp.direction += 3;
                        temp.direction %= 4;
                        break;
                    case 0x5A: // Z
                        temp.direction++;
                        temp.direction %= 4;
                        break;
                    case VK_SPACE:temp = HardDrop (temp);

                        break;
                    case 0x52: // R
                        Restart ();
                        return;
                    case VK_ESCAPE: //P
                        temp = PauseEventHandler (temp);
                        break;
                    case 0x43: // C
                        temp = HoldEventHandler (temp);
                        break;
                        //MenuBar
                    case 0x4D://M
//                    MusicOn ^= 1;
                        BGM_maintainer (MusicOn ^ 1);
                        break;
                    case VK_F1:MouseMode ^= 1;
                        break;
                    default:uiGetKeyboard (key, event); // GUI获取键盘
                        break;
                }
                break;
            case KEY_UP:
                switch (key) {
                    case VK_DOWN:temp.yVelocity = SLOW;
                        break;
                    case VK_SPACE:if (temp.yVelocity != 0)Score += 60;

                        break;
                }
                break;
        }

        if ((!check_collision (temp) && !temp.isPaused) || key == VK_ESCAPE) {
            ctetri = temp;
        }
    }
}

void mouseEventHandler (int x, int y, int button, int event)
{
    uiGetMouse (x, y, button, event); //GUI获取鼠标
    int BlockX;

    xx = ScaleXInches (x);
    yy = GetWindowHeight () - ScaleXInches (y);

    BlockX = XInchScaleToBlock (xx) + LEFTBAR - 1;
    if (FALSE && !ifHover (xx, yy, 0, GetWindowWidth (), 0, GetWindowHeight ())) {
        MouseMode = FALSE;
        printf ("Debug mouse event...\n");
        printf ("%lf %lf\n", xx, yy);
    }
    if (MouseMode && InCheckerBoard (xx, yy)) {
        if (BlockX < ctetri.x) {
            for (int i = 0; i < ctetri.x - BlockX; i++) {
                keyboardEventHandler (VK_LEFT, KEY_DOWN);
            }
        } else {
            for (int i = 0; i < BlockX - ctetri.x; i++) {
                keyboardEventHandler (VK_RIGHT, KEY_DOWN);
            }
        }
        switch (event) {
            case BUTTON_DOWN:
                switch (button) {
                    case LEFT_BUTTON:keyboardEventHandler (VK_SPACE, KEY_DOWN);
                        break;
                    case RIGHT_BUTTON:keyboardEventHandler (0x43, KEY_DOWN);
                        break;
                }
                break;
            case ROLL_UP:keyboardEventHandler (VK_UP, KEY_DOWN);
                break;
            case ROLL_DOWN:keyboardEventHandler (0x5A, KEY_DOWN);
                break;
            case BUTTON_UP:
                switch (button) {
                    case LEFT_BUTTON:keyboardEventHandler (VK_SPACE, KEY_UP);
                        break;
                }
        }

    }
}

void CharEventHandler (char ch)
{
    uiGetChar (ch);
}
