#ifndef MY_COMMANDS_H
#define MY_COMMANDS_H
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
typedef enum primary_commands {
    UNKNOWN, TRIANGLE, FIND_RECT, COLLAGE, HELP, FILE_INFO
} primary_commands;

typedef enum secondary_commands {
    REQUIRED = 10, OPTIONAL = 0
} secondary_commands;

char* copy_string(char* string);
#endif //MY_COMMANDS_H