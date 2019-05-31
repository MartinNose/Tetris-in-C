/*
 * This file contains functions concerning saving and loading game status
 */

#ifndef _FILE_SYSTEM_GAME_STATUS_H_
#define _FILE_SYSTEM_GAME_STATUS_H_

#include "consts.h"

/*
 * Function: File_Load_Saved_Game
 * Usage: give the pointers of some global variables to it,
 *        it will automatically write the data into the memory
 * -----------------------------------------------------------
 * This function loads the last saved game into your memory
 */
bool File_Load_Saved_Game (Checkerboard *saved_board,
                           tetrimino *saved_tetri,
                           tetrimino *saved_que1,
                           tetrimino *saved_que2,
                           tetrimino *saved_held_tetri,
                           int *score,
                           bool *mouse_mode,
                           bool *music_on);

/*
 * Function: File_Save_Game
 * Usage: Put the global variables into it,
 *        it will automatically write them into a file
 * ---------------------------------------------------
 * This function saves the game status from the memory
 * into the file on your disk
 */
void File_Save_Game (Checkerboard *cur_board,
                     tetrimino *cur_tetri,
                     tetrimino *que1,
                     tetrimino *que2,
                     tetrimino *held_tetri,
                     int score,
                     bool mouse_mode,
                     bool music_on);

#endif //_FILE_SYSTEM_GAME_STATUS_H_
