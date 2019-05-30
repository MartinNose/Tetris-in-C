//
// Created by 87547 on 2019/5/30.
//

#ifndef PROJECTLIVER_DRAWERS_2P_H
#define PROJECTLIVER_DRAWERS_2P_H

#include "model_2p.h"
void DrawRect (double width, double height);
void drawBlock (int x, int y, string color);
void drawCheckerBoard(Checkerboard checkerboard);
void drawCheckerBoardList(Checkerboard *list);
void drawUI();
void Clean ();


void drawShadowBlock (int x, int y, string color);
void DrawShadow (tetrimino shadow);



#endif //PROJECTLIVER_DRAWERS_2P_H
