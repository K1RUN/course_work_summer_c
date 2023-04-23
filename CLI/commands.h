#ifndef MY_COMMANDS_H
#define MY_COMMANDS_H
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../Image/bmp_structs.h"
typedef enum primary_commands {
    UNKNOWN, TRIANGLE, FIND_RECT, COLLAGE, HELP, FILE_INFO
} primary_commands;

bool scan_coords(char* coords, Pixel* p);
bool scan_number(char* string, int* dest);
bool scan_RGB(char* rgb_str, Rgb* color);
char* copy_string(char* string);
void print_args(int argc, char* argv[]);
#endif //MY_COMMANDS_H