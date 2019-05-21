//
// Created by Tao Chiang on 5/17/2019.
//

#ifndef _MODEL_H_
#define _MODEL_H_

#include "consts.h"

void InitState ();
void InitModel();

tetrimino generateTetrimino (int type, int direction);

void timerEventHandler (int timerID);
tetrimino tetriMaintainer_on_gravity (int time, tetrimino tetri);
tetrimino tetriMaintainer_on_Keyboard (int RL, tetrimino tetri);
tetrimino tetriRandom ();
bool check_collision (tetrimino tetri);

extern int block_color[14][20];

#endif //_MODEL_H_
