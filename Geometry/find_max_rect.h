#ifndef MY_FIND_MAX_RECT_H
#define MY_FIND_MAX_RECT_H
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "general.h"
#include "../BMP_parser/bmp_structs.h"
#include "../Stack/stack.h"

typedef struct {
    int** sub_matrix;
    size_t w;
    size_t h;
} Sub_matrix;

void destroy_matrix(Sub_matrix matrix);
Sub_matrix get_color_matrix(Pixels img, Rgb color);
bool color_eq(Rgb color1, Rgb color2);
void print_matrix(Sub_matrix matrix);
bool create_matrix(Sub_matrix* matrix, size_t h, size_t w);
void make_histogram(Sub_matrix* subMatrix);
Rectangle find_largest_rect(Sub_matrix histogram);
#endif //MY_FIND_MAX_RECT_H
