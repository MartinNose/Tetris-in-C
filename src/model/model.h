//
// Created by Tao Chiang on 5/17/2019.
//

#ifndef _MODEL_H_
#define _MODEL_H_

#include "consts.h"

void InitModel();

tetrimino generateTetrimino (int type, int direction);

void timerEventHandler (int timerID);
void game ();
tetrimino tetriMaintainer_on_gravity (int time, tetrimino tetri);
tetrimino tetriRandom ();
bool check_collision (tetrimino tetri);
void Settle_Tetri(tetrimino tetri);
tetrimino HardDrop(tetrimino tetri);
void Settle(tetrimino tetri);
int CheckLines ();
bool CheckTop ();
void RemoveLine (int row);
tetrimino Restart ();

extern int block_color[14][25];
extern Checkerboard checkerboard;

extern tetrimino ctetri;

//extern int score;
extern bool is_game_over;

#endif //_MODEL_H_
