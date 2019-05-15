#include "graphics.h"
#include "extgraph.h"
#include <stdio.h>

#include "consts.c"


void DrawRect(double width,double height){
    DrawLine(width,0);
    DrawLine(0,height);
    DrawLine(-1*width,0);
    DrawLine(0,-1*height);
}
void Clean(){
    SetEraseMode(1);
    StartFilledRegion(1);
    MovePen(0,0);
    DrawRect(GetWindowWidth(),GetWindowHeight());
    EndFilledRegion();
    SetEraseMode(0);
}
void drawBlock(int x, int y,string color){

    SetPenColor(color);
    StartFilledRegion(1);

    MovePen(x * BLOCKSIZE,y * BLOCKSIZE);

    DrawRect(BLOCKSIZE,BLOCKSIZE);

    EndFilledRegion();
}

void drawTetro(tetromino tetro){
    drawBlock(tetro.x,tetro.y - 1,"Red");
}
void drawInit(){
    for(int i = 0 ; i < 10 ;i++){
        for(int j = 0;j < HEIGHT;j++){
            drawBlock(i,j,"Gray");
        }
    }
    for(int i = 10 ; i < 22 ;i++){
        for(int j=0;j < HEIGHT;j++){
            drawBlock(i,j,"White");
        }
    }
    for(int i = 22 ; i < WIDTH ;i++){
        for(int j=0;j < HEIGHT;j++){
            drawBlock(i,j,"Gray");
        }
    }
}