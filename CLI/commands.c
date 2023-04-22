#include "commands.h"

char* copy_string(char* string) {
    // extra byte for \0 character
    char* new_str = (char*)malloc((strlen(string) + 1) * sizeof(char));
    strcpy(new_str, string);
    return new_str;
}