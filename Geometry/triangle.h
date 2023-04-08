#ifndef MY_TRIANGLE_H
#define MY_TRIANGLE_H
#include <stdbool.h>
#include "../BMP_parser/bmp_structs.h"
#include "general.h"
#include "line_draw.h"

bool is_in_triangle(Pixel vertex1, Pixel vertex2, Pixel vertex3, Pixel point);
void Homothety(Pixels img, Pixel vertex1, Pixel vertex2, Pixel vertex3, Pixel center, unsigned thickness);
Pixel get_inner_vertex(Pixel point1, Pixel point2, unsigned offset);
Rectangle Boundary(Pixel point1, Pixel point2, Pixel point3);
void fill_triangle(Pixels img, Pixel vertex1, Pixel vertex2, Pixel vertex3, Pixel p);
void draw_triangle(Pixels img, Pixel vertex1, Pixel vertex2, Pixel vertex3);

#endif //MY_TRIANGLE_H
