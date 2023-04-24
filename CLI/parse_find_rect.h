#ifndef MY_PARSE_FIND_RECT_H
#define MY_PARSE_FIND_RECT_H
#include "commands.h"
#include "helpmenu.h"
#include "../Image/canvas.h"
#include "../Geometry/find_max_rect.h"
#include <getopt.h>
#define REQUIRED_RECTANGLE 0b111

void parse_find_rect(int argc, char* argv[]);
typedef struct {
    Rgb max_rect_color; Rgb fill_rect_color; char* new_filename; char* old_filename;
} find_rect;
#endif //MY_PARSE_FIND_RECT_H
