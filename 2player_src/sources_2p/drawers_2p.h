#ifndef _DRAWERS_2P_H
#define _DRAWERS_2P_H
#include "graphics.h"
#include "extgraph.h"
#include <stdio.h>
#include "consts_2p.h"

void DrawRect (double width, double height);
void drawBlock (int x, int y, string color);

void DefineRGBColor (string s, int r, int g, int b);
void DefineColors ();

void drawCheckerBoard(Checkerboard checkerboard);
void drawCheckerBoardList(Checkerboard *list);
void drawUI();
void Clean (int i);
void drawTetri(tetrimino tetri);

void drawShadowBlock (int x, int y, string color);
void DrawShadow (tetrimino shadow);



#endif //PROJECTLIVER_DRAWERS_2P_H
