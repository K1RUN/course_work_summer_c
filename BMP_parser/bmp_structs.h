#ifndef MY_BMP_STRUCTS_H
#define MY_BMP_STRUCTS_H
#include <stddef.h>
#include "bmp_parser.h"

typedef struct {
    Rgb** matrix;
    size_t w;
    size_t h;
} Pixels;

typedef struct {
    unsigned int x;
    unsigned int y;
    unsigned int color;
} Pixel;
#endif //MY_BMP_STRUCTS_H
