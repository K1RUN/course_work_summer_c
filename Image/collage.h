#ifndef MY_COLLAGE_H
#define MY_COLLAGE_H
#include "bmp_structs.h"
#include "canvas.h"

void create_collage(Pixels* image, int n, int m);
void paste_images(Pixels canvas, Pixels image, size_t x, size_t y);
#endif //MY_COLLAGE_H
