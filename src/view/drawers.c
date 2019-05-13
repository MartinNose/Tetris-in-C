#include "graphics.h"
#include "extgraph.h"
#include <stdio.h>

void drawBlock(double x, double y, double width, double height){
    SetPenColor("black");
    MovePen(x,y);
    DrawLine(width,0);
    DrawLine(0,height);
    DrawLine(-1*width,0);
    DrawLine(0,-1*width);
}