/*
 * This file is used to test the sound module
 */
#include "sound.h"

#include <windows.h>

#include <stdio.h>
#include <time.h>

int main ()
{
    Play_Sound_Demo (); // 单线程，会阻塞后面的语句
    Play_Sound (); // 多线程，同时可以执行后面的printf()
//    Play_Sound_Demo (); // 单线程，会阻塞后面的语句
//    PlaySound(NULL,NULL,SND_FILENAME); // 用于停止播放的音乐
    while (1)
        printf ("233\n");
}
