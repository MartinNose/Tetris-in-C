#ifndef _SOUND_H_
#define _SOUND_H_

#include<windows.h>

/*
 * Function: Play_Sound_Demo
 * Usage: Call it to make sound effects
 * ====================================
 * It runs in a new thread to avoid UI stuck
 */
void Play_Sound_Demo ();

/*
 * Function: Play_Sound
 * Usage: Call it to play music
 * ============================
 * It plays wave sound and it
 * also runs in a new thread
 */
void Play_Sound ();

#endif //_SOUND_H_
