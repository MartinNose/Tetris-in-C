#include "graphics.h"
#include "extgraph.h"
#include <stdio.h>
#include "consts.c"

void drawBlock(double x, double y,string color){

    SetPenColor(color);
    StartFilledRegion(1);

    MovePen(x,y);

    DrawLine(BLOCKSIZE,0);
    DrawLine(0,BLOCKSIZE);
    DrawLine(-1*BLOCKSIZE,0);
    DrawLine(0,-1*BLOCKSIZE);

    EndFilledRegion();
}