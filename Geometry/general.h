#ifndef MY_GENERAL_H
#define MY_GENERAL_H
#include <stdbool.h>
#include <stdlib.h>
#include "../Image/bmp_structs.h"
#define BUF 10
#define min(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a < _b ? _a : _b; })
#define max(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a > _b ? _a : _b; })

typedef struct {
    int x; int y;
} Vector;

typedef struct {
    int x; int y;
} Coords;
bool in_area(Pixel point, size_t height, size_t width);
void set_pixel(Pixels img, Pixel point);
#endif //MY_GENERAL_H
