//
// Created by Tao Chiang on 5/21/2019.
//

#include <genlib.h>
#include "consts.h"


int typeInfo[][4][2] = { // 每种形状存进一个数组，而每个数组中包含一批二维数组（后期可以考虑状态压缩），注意每个物块其实都有4个block
    {{0, 0}, {0, 0}, {0, 0}, {0, 0}},
    {{0, 2}, {0, -1}, {0, 0}, {0, 1}}, // 0, 大长条
    {{-1, 1}, {-1, 0}, {0, 0}, {1, 0}}, // 1, L1
    {{-1, 0}, {0, 0}, {1, 0}, {1, 1}}, // 2, L2
    {{-1, -1}, {-1, 0}, {0, 0}, {0, -1}}, // 3, Square
    {{-1, 0}, {0, 0}, {0, -1}, {1, 0}}, // 4, Snake1
    {{-1, -1}, {0, -1}, {0, 0}, {1, 0}}, // 5, Snack2
    {{-1, -1}, {0, -1}, {0, 0}, {1, -1}}, // 6, Up
};

string TETRI_COLOR[8] = {
    "White",//for null
//    "BLUE",
    "Magenta",
//    "DarkBlue",
    "Blue",
//    "Orange",
    "Cyan",
    "Yellow",
    "Green",
    "Light Gray",
    "Red"
};



// Black, Dark Gray, Gray, Light Gray, White,
// *    Red, Yellow, Green, Cyan, Blue, Magenta
