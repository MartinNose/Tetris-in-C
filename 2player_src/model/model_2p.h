//
// Created by Tao Chiang on 5/17/2019.
//

#ifndef _MODEL_H_
#define _MODEL_H_

#include "consts_2p.h"

void InitModel();
static Checkerboard generateInitCheckerboard (int x);

tetrimino generateTetrimino (int type, int direction ,int index);

void timerEventHandler (int timerID);
tetrimino NextTetri (int position);



tetrimino tetriMaintainer_on_gravity (int time, tetrimino tetri);
tetrimino tetriRandom ();
bool check_collision (tetrimino tetri,Checkerboard checkerboard);
Checkerboard Settle_Tetri (tetrimino tetri, Checkerboard checker);
tetrimino HardDrop (tetrimino tetri);
tetrimino HoldEventHandler(tetrimino temp, int position);
tetrimino PauseEventHandler(tetrimino temp);

void GameOver(int i);
void ExitGame();
void Upload();
void reName();

bool CheckTop (int index);
tetrimino Restart ();

Checkerboard Settle (tetrimino tetri);


extern Checkerboard checkerboard;

extern tetrimino ctetri[2];
extern Checkerboard checkerboardlist[2];

extern int Score[2];
extern bool is_game_over[2];
extern double globalSpeed;
extern tetrimino que[2][2];
extern tetrimino HeldTetri[2];
extern bool isHoldLegal[2];
extern bool MusicOn;
extern bool MouseMode;
extern bool Rename;
extern char username[18];


void SaveGame();
bool LoadGame();

bool ifHover(double x, double y, double x1, double x2, double y1, double y2);
int XInchScaleToBlock(double x);
bool InCheckerBoard(double x, double y);

void BGM_maintainer(bool new_music_on);

extern double xx;
extern double yy;

//MenuBar======================================
extern bool isDisplayMenu1;
//=============================================

#endif //_MODEL_H_
