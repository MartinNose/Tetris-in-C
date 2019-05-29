//
// Created by Tao Chiang on 5/28/2019.
//

#include "sound.h"
#include <windows.h>

#include <stdio.h>
#include <time.h>

DWORD WINAPI Sound_Func (LPVOID lpParam)
{
    Play_Sound_Demo ();
}

void Play_Sound()
{
    CreateThread (
        NULL,   // default security attributes
        0, // use default stack size
        Sound_Func, // thread function
        NULL,// argument to thread function
        0, // use default creation flags
        NULL);// returns the thread identifier
}

void Play_Sound_Demo ()
{
    Beep (494, 200);
    Beep (523, 300);
    Beep (578, 400);
    Beep (659, 500);
    Beep (698, 600);
    Beep (784, 700);
    Beep (880, 800);
//    Beep (932, 900);
//    Beep (1046, 1000);
//    Beep (1175, 1100);
//    Beep (1381, 1200);
//    Beep (1480, 1300);
//    Beep (1661, 1400);
}