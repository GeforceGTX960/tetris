#include "color.h"

const Color black = {0,0,0,255};
const Color red = {255,43,50,255};
const Color orange = {255,110,43,255};
const Color yellow = {255,220,22,255};
const Color green = {54,188,47,255};
const Color cyan = {15,179,224,255};
const Color blue = {33,97,224,255};
const Color purple = {140,71,224,255};

std::vector<Color> GetCellColors(){
    return {black, red, orange, yellow, green, cyan, blue, purple};
}