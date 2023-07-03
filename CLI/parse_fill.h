#ifndef BMPP_PARSE_FILL_H
#define BMPP_PARSE_FILL_H
#include "commands.h"
#include "helpmenu.h"
#include "../Image/collage.h"
#include "../Image/bmp_structs.h"
#include "../Image/canvas.h"
#include <getopt.h>
#define REQUIRED_FILL 0b11111

void parse_fill(int argc, char* argv[]);
typedef struct fill_opts {
    Pixel x;
    int w;
    int h;
    Rgb color;
    char* new_filename;
    char* old_filename;
} fill_opts;
#endif //BMPP_PARSE_FILL_H
