/*
 * This file maintains our model
 */

#ifndef _MODEL_H_
#define _MODEL_H_

#include "consts.h"
//Maintainers on game logic============================================

/*
 *  Function: InitModel
 *  Usage: InitModel()
 *  ------------------------------------------------
 *  This function is used to init the initial situation.
 *
 * */
void InitModel();

/*
 *  Function: generateTetrimino
 *  Usage: generateTetrimino (type, direction);
 *  ---------------------------------------
 *  This function can generate a tetri with given type
 *  and direction.
 * */

tetrimino generateTetrimino (int type, int direction);

/*
 * Function:timerEventHandler
 * Usage:timerEventHandler (GAME);
 * -----------------------------------------
 * This function can process the counter event;
 * */

void timerEventHandler (int timerID);

/*
 * Function: tetriMaintainer_on_gravity (int time, tetrimino tetri)
 * Usage: tetriMaintainer_on_gravity (time, tetri)
 * -----------------------------------------
 * This function can reflesh the tetri.
 * */

tetrimino tetriMaintainer_on_gravity (int time, tetrimino tetri);

/*
 * Function: GameOver
 * Usage: GameOver();
 * -----------------------------------------
 * This function can handler the gameover event.
 * */
void GameOver();


/*
 * Function: SaveGame
 * Usage: SaveGame()；
 * -----------------------------------------
 * This function can save the game state and write to src file.
 * */
void SaveGame();


/*
 * Function: LoadGame
 * Usage: LoadGame();
 * -----------------------------------------
 * This function can load the saved game.
 * */
bool LoadGame();

/*
 * Function: CheckTop
 * Usage: CheckTop()
 * -----------------------------------------
 * This function can check if the game is over.
 * */
bool CheckTop ();


/*
 * Function: Restart
 * Usage: Restart()
 * -----------------------------------------
 * This function can restart the game.
 * */
tetrimino Restart ();




//Tools====================================================================

/*
 * Function: tetriRandom();
 * Usage: tetri = tetriRandom();
 * -----------------------------------------
 * This function
 *
 *
 *
 * */
tetrimino tetriRandom ();

/*
 * Function: check_collision
 * Usage: if(check_collision (tetri)
 * -----------------------------------------
 * This function can check that if the tetri is contacted with the bound
 * */
bool check_collision (tetrimino tetri);

/*
 * Function: Settle_Tetri
 * Usage: Settle_Tetri(tetri, checkerboard)
 * -----------------------------------------
 * This function can write the settled tetri to the checkerboard.
 * */
Checkerboard Settle_Tetri (tetrimino tetri, Checkerboard checker);

/*
 * Function: Settle
 * Usage: Settle(tetri)
 * -----------------------------------------
 * This function can maintain the settle event.
 * */

void Settle(tetrimino tetri);

/*
 * Function: XInchScaleToBlock
 * Usage: width = XInchScaleToBlock(GetWindowWidth());
 * -----------------------------------------
 * This function can switch the length in pixles to inches.
 * */
int XInchScaleToBlock(double x);



/*
 * Function: InCheckerBoard
 * Usage: if(InCheckerBoard(tetri.x,tetri.y))
 * -----------------------------------------
 * This function can determine whether the given
 * cordinates is in checkerboard
 * */
bool InCheckerBoard(double x, double y);


/*
 * Function: ifHover
 * Usage: ifHover(x,y,x1,x2,y1,y2)
 * -----------------------------------------
 * This function can determine if (x,y) in the
 * rectangle with vertex coorditanes (x1,y1),(x2,y2)
 *
 *
 *
 * */
bool ifHover(double x, double y, double x1, double x2, double y1, double y2);

/*
 * Function: BGM_maintainer(new_music_on)
 * Usage: BGM_maintainer(bool new_music_on)
 * -----------------------------------------
 * This function can set the BGM on track.
 * */
void BGM_maintainer(bool new_music_on);


//Handlers on control event========================


/*
 * Function: HardDrop
 * Usage: shadow = HardDrop(tetri)
 * -----------------------------------------
 * This function can set the tetri to the bottom
 * directly.
 *
 *
 *
 * */
tetrimino HardDrop(tetrimino tetri);

/*
 * Function: HoldEventHandler
 * Usage: tetri = HoldEventHandler(tetri)
 * -----------------------------------------
 * This function can hanle the hold event.
 * */
tetrimino HoldEventHandler(tetrimino temp);


/*
 * Function: PauseEventHandler
 * Usage: temp = PauseEventHandler(temp);
 * -----------------------------------------
 * This function can handle the pause event.
 *
 *
 *
 * */
tetrimino PauseEventHandler(tetrimino temp);

/*
 * Function: ExitGame
 * Usage: ExitGame()
 * -----------------------------------------
 * This function makes user quit the game.
 * */
void ExitGame();



/*
 * Function: Upload
 * Usage: Upload()
 * -----------------------------------------
 * This function can upload the current game.
 *
 *
 *
 * */

void Upload();

/*
 * Function: reName
 * Usage: reName
 * -----------------------------------------
 * This function can handle the reName event.
 * */
void reName();


//Global Variables
extern Checkerboard checkerboard;
extern tetrimino ctetri;
extern int Score;
extern bool is_game_over;
extern double globalSpeed;
extern tetrimino que[2];
extern tetrimino HeldTetri;
extern bool isHoldLegal;
extern bool MusicOn;
extern bool MouseMode;
extern bool Rename;
extern char username[18];
extern double xx;
extern double yy;
extern bool isDisplayMenu;

//=============================================

#endif //_MODEL_H_
