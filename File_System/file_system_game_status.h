//
// Created by Tao Chiang on 5/28/2019.
//

#ifndef _FILE_SYSTEM_GAME_STATUS_H_
#define _FILE_SYSTEM_GAME_STATUS_H_

#include "consts.h"

void Load_Saved_Game(Checkerboard** saved_board, tetrimino** saved_tetri, tetrimino** saved_next_tetri, tetrimino** saved_held_tetri);

void Save_Game(Checkerboard* cur_board, tetrimino* cur_tetri, tetrimino* next_tetri, tetrimino* held_tetri);

#endif //_FILE_SYSTEM_GAME_STATUS_H_
