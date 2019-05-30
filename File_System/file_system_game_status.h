/*
 * This file contains functions concerning saving and loading game status
 */

#ifndef _FILE_SYSTEM_GAME_STATUS_H_
#define _FILE_SYSTEM_GAME_STATUS_H_

#include "consts.h"

/*
 *
 */
bool File_Load_Saved_Game (Checkerboard *saved_board,
                           tetrimino *saved_tetri,
                           tetrimino *saved_que1,
                           tetrimino *saved_que2,
                           tetrimino *saved_held_tetri,
                           int *score,
                           bool *mouse_mode,
                           bool *music_on);

void File_Save_Game (Checkerboard *cur_board,
                     tetrimino *cur_tetri,
                     tetrimino *que1,
                     tetrimino *que2,
                     tetrimino *held_tetri,
                     int score,
                     bool mouse_mode,
                     bool music_on);

#endif //_FILE_SYSTEM_GAME_STATUS_H_
