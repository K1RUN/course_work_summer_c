#ifndef MY_GENERAL_H
#define MY_GENERAL_H
#include <stdbool.h>
#include "../BMP_parser/bmp_structs.h"

bool in_area(Pixel point, size_t height, size_t width);
void set_pixel(Pixels img, Pixel point);
#endif //MY_GENERAL_H
