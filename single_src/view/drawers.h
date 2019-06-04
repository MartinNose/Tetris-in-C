/*
 * This file maintains the viewer
 */

#ifndef _DRAWERS_H_
#define _DRAWERS_H_

#include "graphics.h"
#include "extgraph.h"
#include <stdio.h>
#include "consts.h"

//Funtions On Rendering Tetromino===================
/* Function: drawTetri
 * Usage: drawTetri(tetri)
 * -------------------------------------------------
 * This funciton can render a tetri based on the
 * tetrimino's cordinate.
 */
void drawTetri (tetrimino tetri);

/* Function: DrawNextTetrimino
 * Usage: DrawNextTerimino(next_tetrimino)
 * -------------------------------------------------
 * This function can render the Next Tetri in the que.
 */

void DrawNextTetrimino(tetrimino tetri);

/* Function: DrawHoldedTetrimino
 * Usage: DrawHoldedTetrimino(tetri);
 * -------------------------------------------------
 * This function can render the tetri holded by the user.
 */
void DrawHoldedTetrimino(tetrimino tetri);

/* Function:DrawShadow
 * Usage:Drawshadow(tetri);
 * -------------------------------------------------
 *This function is use to render a tetri's shadow on the
 * checkerboard.
 */
void DrawShadow(tetrimino shadow);

//==================================================

//Functions on Rendering UI====================================

/* Function: DrawSideBar
 * Usage: DrawSideBar
 * -------------------------------------------------
 * This is a tool function called by function drawUI,
 *  rendering the the sidebar of the game.
 */
void DrawSideBar();

/* Function: drawUI
 * Usage: drawUI(score)
 * -------------------------------------------------
 * This function is used to render the whole user interface.
 */
void drawUI(int score);

/* Function: drawCheckerBoard
 * Usage: drawCheckerBoard()
 * -------------------------------------------------
 * This function is used to render the whole checkerboard
 */
void drawCheckerBoard(Checkerboard checker);



/* Function:DrawDate
 * Usage:DrawData(24)
 * -------------------------------------------------
 * This function render the information in the sources_2p
 * that need to be shown on the user interface.
 */
void DrawData(int score);

/* Function: DrawBoard
 * Usage: DrawBoard(PAUSE)
 * -------------------------------------------------
 * This function is used to draw a menu in the UI
 */
void DrawBoard(int flag);

/* Function: drawBoardButtons
 * Usage: drawBoardButtons(2,4,PAUSE)
 * -------------------------------------------------
 * This function is use to show the buttons on a menu.
 */
void drawBoardButtons(double x, double y,int flag);

/* Function: Draw
 * Usage:
 * -------------------------------------------------
 *
 */
void DrawMenu();



/* Function: DrawBottomBar
 * Usage: DrawBottomBar()
 * -------------------------------------------------
 * This function is used to draw the bottom bar.
 */
void DrawBottomBar();



/* Function: DrawDynamicButtons
 * Usage: DrawDynamicButtons()
 * -------------------------------------------------
 * This function is used to draw the dynamic buttons
 */
void DrawDynamicButtons();



//Tool Functions=======================================

/* Function: DrawRect
 * Usage: DrawRect(w,h)
 * -------------------------------------------------
 * This function is used to draw a rectangle in the window.
 */
void DrawRect (double width, double height);

/* Function:DefineRGBColor
 * Usage:DefineRGBColor ("Gold",233,233,233)
 * -------------------------------------------------
 * This function is used to define a new color.
 */
void DefineRGBColor (string s, int r, int g, int b);

/* Function: DefineColors
 * Usage: DefineColors();
 * -------------------------------------------------
 * This function is used to define the colors used in
 * the game.
 */
void DefineColors();

/* Function: Clean
 * Usage: Clean
 * -----------------------------------------------------
 * This function is used to clean the window.
*/
void Clean ();

/* Function: drawBlock
 * Usage: drawBlock(x,y,"Red")
 * -----------------------------------------------------
 * This function is used to render the basic unit of a tetromino.
 */
void drawBlock (double x, int y, int type);

/* Function: drawShadowBlock
 * Usage: drawShadowBlock (int x, int y, string color)
 * -------------------------------------------------
 * This function is used to draw a unit of shadow block;
 */
void drawShadowBlock (int x, int y, string color);


/* Function: DrawGrid
 * Usage: DrawGrid
 * -------------------------------------------------
 * This function is used to render the block on the UI.
 */
void DrawGrid();


/* Function:RandColor
 * Usage: color = RandColor();
 * -------------------------------------------------
 * This function returns a random function
 */
int RandColor();


/* Function: drawBlock
 * Usage:  drawBlock(1,2,"Blue")
 * -------------------------------------------------
 * This function is used to draw a block on the checkerboard
 */
void drawBlock (double x, int y, int type);

/* Function: DebugTool
 * Usage: DebugTool();
 * -------------------------------------------------
 * This function can print the basic information
 */
void DebugTool();



/* Function: MessageBoxB
 * Usage:MessageBoxB(string title,string color)
 * -------------------------------------------------
 * This function can render a message box.
 */
void MessageBoxB(string title,string color);

void InitPics();

#endif //_DRAWERS_H_
