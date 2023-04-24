#ifndef MY_PARSE_COLLAGE_H
#define MY_PARSE_COLLAGE_H
#include "commands.h"
#include "helpmenu.h"
#include "../Image/canvas.h"
#include "../Image/collage.h"
#include <getopt.h>
#define REQUIRED_COLLAGE 0b111

void parse_collage(int argc, char* argv[]);
typedef struct {
    int x_num; int y_num; char* new_filename; char* old_filename;
} collage;
#endif //MY_PARSE_COLLAGE_H
