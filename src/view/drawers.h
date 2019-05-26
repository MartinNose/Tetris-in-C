//
// Created by Tao Chiang on 5/17/2019.
//

#ifndef _DRAWERS_H_
#define _DRAWERS_H_

#include "graphics.h"
#include "extgraph.h"
#include <stdio.h>
#include "consts.h"

void drawInit (int score);

void drawCheckerBoard(Checkerboard checker);

void Clean ();

void drawBlock (int x, int y, string color);

void drawTetri (tetrimino tetri);

void DrawRect (double width, double height);

void DrawShadow(tetrimino shadow);

void DrawScore(int score);

void DrawGrid();



#endif //_DRAWERS_H_
