#ifndef MY_CANVAS_H
#define MY_CANVAS_H
#include "bmp_structs.h"
#include <stdlib.h>

Pixels create_canvas(size_t w, size_t h);
void free_canvas(Pixels canvas);
void canvas_draw(Pixels canvas, char *filename);
void canvas_write(Pixels canvas, char *filename_old, char *filename_new);
#endif //MY_CANVAS_H
