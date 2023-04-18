#ifndef MY_RECTANGLE_H
#define MY_RECTANGLE_H
#include "../Image/bmp_structs.h"
#include "general.h"
#include "line_draw.h"
typedef struct {
    Pixel v1;
    Pixel v2;
} Rectangle;

void draw_rect_borders(Pixels img, Rectangle rect, Rgb color);
void fill_rect(Pixels img, Rectangle rect, Rgb color);
#endif //MY_RECTANGLE_H
