#ifndef MY_LINE_DRAW_H
#define MY_LINE_DRAW_H
#define BUF 10
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
void DDA(Pixel point1, Pixel point2, Pixel** arr);
void draw_triangle(Pixels img, Pixel vertex1, Pixel vertex2, Pixel vertex3);
Pixel get_inner_vertex(Pixel point1, Pixel point2, unsigned offset);
Rectangle Boundary(Pixel point1, Pixel point2, Pixel point3);
#endif //MY_LINE_DRAW_H
