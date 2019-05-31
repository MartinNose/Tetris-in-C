/*
 * This file maintains the controller
 */

#ifndef _HANDLERS_H_
#define _HANDLERS_H_
/*
 *  Function: mouseEventHandler
 *  Usage: mouseEventHandler (x,y,button,event)
 *  ---------------------------------------
 *  This function can handle the mouse event. 
 * */
void mouseEventHandler (int x, int y, int button, int event);

/*
 *  Function: keyboardEventHandler
 *  Usage: keyboardEventHandler(VK_DOWN,KEY_UP)
 *  ---------------------------------------
 *  This function can handle the keyboard event.
 * */

void keyboardEventHandler (int key, int event);

/*
 *  Function: CharEventHandler
 *  Usage: CharEventHandler(char c);
 *  ---------------------------------------
 *  This function can handle the char input event.
 * */

void CharEventHandler(char c);
#endif //_HANDLERS_H_
