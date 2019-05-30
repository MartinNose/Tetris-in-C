//
// Created by Tao Chiang on 5/17/2019.
//

#ifndef _DRAWERS_H_
#define _DRAWERS_H_

#include "graphics.h"
#include "extgraph.h"
#include <stdio.h>
#include "consts.h"

void drawUI(int score);
void DrawSideBar();
void DrawNextTetrimino(tetrimino tetri);
void DrawHoldedTetrimino(tetrimino tetri);

void DefineColors();

void drawCheckerBoard(Checkerboard checker);

void Clean ();

void drawBlock (int x, int y, string color);

void drawTetri (tetrimino tetri);

void DrawRect (double width, double height);

void DrawShadow(tetrimino shadow);

void DrawData(int score);

void DrawGrid();

void DrawBoard(int flag);
void drawBoardButtons(double x, double y,int flag);
string RandColor();

void DrawMenu();

void DrawBottomBar();
void DrawDynamicButtons();

void DebugTool();
void MessageBoxB(string title,string color);
string drawCursor(string buffer);

#endif //_DRAWERS_H_
