#ifndef MY_CANVAS_H
#define MY_CANVAS_H
#include "bmp_structs.h"
#include "../Geometry/general.h"
#include <stdlib.h>

Pixels create_canvas(size_t h, size_t w);
void free_canvas(Pixels canvas);
void canvas_draw(Pixels canvas, char *filename);
void canvas_write(Pixels canvas, char *filename_old, char *filename_new);
Pixels canvas_copy(Pixels img, Pixel start, Pixel end);
bool canvas_paste(Pixels img_dest, Pixels canvas_cpy, Pixel start);
void img_rotate(Pixels img, Pixel start, Pixel end, int angle);
#endif //MY_CANVAS_H
