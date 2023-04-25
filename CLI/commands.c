#include "commands.h"

char* copy_string(char* string) {
    // extra byte for \0 character
    char* new_str = (char*)malloc((strlen(string) + 1) * sizeof(char));
    strcpy(new_str, string);
    return new_str;
}

void print_args(int argc, char* argv[]) {
    //DEBUGGING
    for(int i = 0; i < argc; i++) {
        printf("%d - %s\n", i, *(argv + i));
    }
}

bool scan_coords(char* coords, Pixel* p) {
    if(coords == NULL) {
        return false;
    }
    char* end1 = "\0"; char* end2 = "\0";
    char* part1 = strtok(coords, ",");
    char* part2 = strtok(NULL, ",");
    if(part1 != NULL && part2 != NULL) {
        int x = (int)strtol(part1, &end1, 10);
        int y = (int)strtol(part2, &end2, 10);
        // if end ptr is \0 then the whole sequence was scanned correctly
        if(*end1 == '\0' && *end2 == '\0') {
            p->x = x; p->y = y;
            return true;
        }
    }
    return false;
}

bool scan_number(char* string, int* dest) {
    if(string == NULL) {
        return false;
    }
    char* end = "\0";
    int num = (int)strtol(string, &end, 10);
    if(*end == '\0') {
        *dest = num;
        if(num <= 0) {
            fprintf(stderr, "Warning: non-positive number was given\n");
        }
        return true;
    }
    return false;
}

bool scan_RGB(char* rgb_str, Rgb* color) {
    if(rgb_str == NULL) {
        return false;
    }
    char* end1 = "\0"; char* end2 = "\0"; char* end3 = "\0";
    char* part1 = strtok(rgb_str, ",");
    char* part2 = strtok(NULL, ",");
    char* part3 = strtok(NULL, ",");
    if(part1 != NULL && part2 != NULL && part3 != NULL) {
        int R = (int)strtol(part1, &end1, 10);
        int G = (int)strtol(part2, &end2, 10);
        int B = (int)strtol(part3, &end3, 10);
        if(*end1 == '\0' && *end2 == '\0' && *end3 == '\0') {
            if(R < 0 || R > 255 || G < 0 || G > 255 || B < 0 || B > 255) {
                fprintf(stderr, "Warning: one of the colors is out of range\n");
            }
            color->r = (unsigned char)R; color->g = (unsigned char)G; color->b = (unsigned char)B;
            return true;
        }
    }
    return false;
}