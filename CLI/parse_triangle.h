#ifndef MY_PARSE_TRIANGLE_H
#define MY_PARSE_TRIANGLE_H
#include "command_parser.h"
#include <stdbool.h>
#include <string.h>
#include "../Geometry/general.h"
#include "../Geometry/triangle.h"
#include "../Image/canvas.h"
#include "../Image/bmp_structs.h"

typedef struct triangle_opts {
    Pixel a, b, c;
    int w;
    Rgb e, f;
    char* new_filename;
} triangle_opts;

typedef enum secondary_commands_triangle {
    // bitmasks for optional and required arguments for triangle
    // 96 == 0b1100000, 31 == 0b0011111
    // 2 ones at the beginning are set for optional flags
    // another 4 - for required flags
    // using this logic in check sum while parsing rectangles
    OPTIONAL = 96, REQUIRED = 31
} secondary_commands_triangle;
bool scan_coords(char* coords, Pixel* p);
void parse_triangle(int argc, char* argv[]);
#endif //MY_PARSE_TRIANGLE_H
