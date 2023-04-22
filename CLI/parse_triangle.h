#ifndef MY_PARSE_TRIANGLE_H
#define MY_PARSE_TRIANGLE_H
#include "command_parser.h"
#include <stdbool.h>
#include <string.h>
#include "../Geometry/general.h"
#include "../Image/bmp_structs.h"

typedef struct triangle_opts {
    Coords a, b, c;
    size_t w;
    Rgb e, f;
    char* filename;
} triangle_opts;

bool scan_coords(char* coords, Coords* p);
#endif //MY_PARSE_TRIANGLE_H
