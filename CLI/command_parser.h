#ifndef MY_COMMAND_PARSER_H
#define MY_COMMAND_PARSER_H
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_RESET   "\x1b[0m"
#include "parse_triangle.h"
#include "parse_find_rect.h"
#include "parse_collage.h"
#include "parse_fill.h"
#include "commands.h"
#include "helpmenu.h"
#include "../Image/bmp_parser.h"
#include <getopt.h>
#include <stddef.h>
int parse_commands(int argc, char* argv[]);
#endif //MY_COMMAND_PARSER_H
