#ifndef MY_LINE_DRAW_H
#define MY_LINE_DRAW_H
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include "general.h"
#include "../Image/bmp_structs.h"

typedef struct line_coords {
    int x1; int y1;
    int x2; int y2;
} line_coords;

typedef struct {
    Pixel v1;
    Pixel v2;
} Rectangle;


bool is_in_triangle(Pixel vertex1, Pixel vertex2, Pixel vertex3, Pixel point);
void Bresenham(Pixels img, Pixel point1, Pixel point2);
Pixel line_intercept(Vector direct1, Pixel point1, Vector direct2, Pixel point2);
Rectangle Boundary_rect(Pixel p1, Pixel p2, Pixel p3, Pixel p4);
void plotLineWidth(Pixels img, Pixel point1, Pixel point2, float wd);
void draw_thick_line(Pixels img, Pixel p1, Pixel p2, Rgb color, unsigned int thickness);
line_coords Perpendicular(Pixel point1, Pixel point2, unsigned int len);
#endif //MY_LINE_DRAW_H