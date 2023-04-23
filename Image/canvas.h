#ifndef MY_CANVAS_H
#define MY_CANVAS_H
#include "bmp_structs.h"
#include <stdlib.h>

Pixels create_canvas(size_t h, size_t w);
void free_canvas(Pixels canvas);
void canvas_draw(Pixels canvas, char *filename);
void canvas_write(Pixels canvas, char *filename_old, char *filename_new);
#endif //MY_CANVAS_H
