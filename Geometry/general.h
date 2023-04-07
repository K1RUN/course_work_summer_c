#ifndef MY_GENERAL_H
#define MY_GENERAL_H
#include <stdbool.h>
#include <stdlib.h>
#include "../fixed.h"
#include "../BMP_parser/bmp_structs.h"

typedef struct {
    Pixel v1;
    Pixel v2;
} Rectangle;
bool in_area(Pixel point, size_t height, size_t width);
void set_pixel(Pixels img, Pixel point);
#endif //MY_GENERAL_H
