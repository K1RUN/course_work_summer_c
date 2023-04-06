#ifndef MY_LINE_DRAW_H
#define MY_LINE_DRAW_H
#define min(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a < _b ? _a : _b; })
#define max(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a > _b ? _a : _b; })
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include "general.h"
#include "../BMP_parser/bmp_structs.h"

void Bresenham(Pixels img, Pixel point1, Pixel point2);
void DDA(Pixels img, Pixel point1, Pixel point2);
void draw_triangle(Pixels img, Pixel vertex1, Pixel vertex2, Pixel vertex3);
#endif //MY_LINE_DRAW_H
