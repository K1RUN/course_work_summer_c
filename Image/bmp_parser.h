#ifndef MY_BMP_PARSER_H
#define MY_BMP_PARSER_H
#include <stdbool.h>
#include <stdio.h>
#include "../Error_handling/error_handler.h"

#pragma pack(push, 1)
typedef struct {
    unsigned short signature;
    unsigned int file_size;
    unsigned short reserved1;
    unsigned short reserved2;
    unsigned int offset_to_pixels;
} Bitmap_File_Header;

typedef struct {
    unsigned int dib_header_size;
    unsigned int image_width;
    unsigned int image_height;
    unsigned short planes;
    unsigned short bits_per_pixel;
    unsigned int compression;
    unsigned int image_size;
    unsigned int xPixelsPerMeter;
    unsigned int yPixelsPerMeter;
    unsigned int colorsInColorTable;
    unsigned int importantColorCount;
} DIB_Header;

typedef struct {
    unsigned char b;
    unsigned char g;
    unsigned char r;
} Rgb;
#pragma pack (pop)

void print_file_header(Bitmap_File_Header bitmap);
void print_dib_header(DIB_Header bitmap);
bool open_bmp(char* filename, char* mode);
unsigned short get_offset(size_t width);
Bitmap_File_Header parse_bmfh(char* filename);
DIB_Header parse_dib(char* filename);
void print_info(char * filename);
bool check_file(char* filename);
#endif //MY_BMP_PARSER_H
