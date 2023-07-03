#ifndef MY_PARSE_TRIANGLE_H
#define MY_PARSE_TRIANGLE_H
#include <stdbool.h>
#include <getopt.h>
#include <string.h>
#include "helpmenu.h"
#include "commands.h"
#include "../Geometry/general.h"
#include "../Geometry/triangle.h"
#include "../Image/canvas.h"
#include "../Image/bmp_structs.h"
#define REQUIRED_TRIANGLE 0b111111
// bitmasks for required argument, using this logic in check sum while parsing rectangles

typedef struct triangle_opts {
    Pixel a, b, c;
    int w;
    Rgb e, f;
    char* new_filename;
    char* old_filename;
} triangle_opts;

void parse_triangle(int argc, char* argv[]);
#endif //MY_PARSE_TRIANGLE_H
