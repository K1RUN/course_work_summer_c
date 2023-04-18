#ifndef MY_LINE_DRAW_H
#define MY_LINE_DRAW_H
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include "general.h"
#include "../Image/bmp_structs.h"

void Bresenham(Pixels img, Pixel point1, Pixel point2);
Pixel line_intercept(Vector direct1, Pixel point1, Vector direct2, Pixel point2);
#endif //MY_LINE_DRAW_H