//
// Created by Tao Chiang on 5/28/2019.
//
#include "sound.h"

#include <windows.h>

#include <stdio.h>
#include <time.h>

int main ()
{
    Play_Sound_Demo (); // 单线程，会阻塞后面的语句
    Play_Sound(); // 多线程，同时可以执行后面的printf()
    while(1)
        printf ("233\n");
}
