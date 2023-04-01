#include "helpmenu.h"
#include "Testing/error_handler.h"
#include <stdio.h>
#include <stdbool.h>
#include <getopt.h>

#pragma pack (push, 1)
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

void print_file_header(Bitmap_File_Header bitmap) {
    printf("signature: %x (%hu)\n", bitmap.signature, bitmap.signature);
    printf("file size: %x (%u)\n", bitmap.file_size, bitmap.file_size);
    printf("reserved1: %hu\n", bitmap.reserved1);
    printf("reserved2: %hu\n", bitmap.reserved2);
    printf("offset_to_pixels: %x (%u)\n", bitmap.offset_to_pixels, bitmap.offset_to_pixels);
}

void print_dib_header(DIB_Header bitmap) {
    printf("dib header size: %x (%u)\n", bitmap.dib_header_size, bitmap.dib_header_size);
    printf("image width: %x (%u)\n", bitmap.image_width, bitmap.image_width);
    printf("image height: %x (%u)\n", bitmap.image_height, bitmap.image_height);
    printf("planes: %x (%hu)\n", bitmap.planes, bitmap.planes);
    printf("bits per pixel: %x (%hu)\n", bitmap.bits_per_pixel, bitmap.bits_per_pixel);
    printf("compression: %x (%u)\n", bitmap.compression, bitmap.compression);
    printf("image size: %x (%u)\n", bitmap.image_size, bitmap.image_size);
    printf("x pixels per meter: %x (%u)\n", bitmap.xPixelsPerMeter, bitmap.xPixelsPerMeter);
    printf("y pixels per meter: %x (%u)\n", bitmap.yPixelsPerMeter, bitmap.yPixelsPerMeter);
    printf("colors in color table: %x (%u)\n", bitmap.colorsInColorTable, bitmap.colorsInColorTable);
    printf("important color count: %x (%u)\n", bitmap.importantColorCount, bitmap.importantColorCount);
}

bool open_bmp(char* filename, char* mode) {
    FILE* fp = fopen(filename, mode);
    if(fp == NULL){
        process_error(FOPEN);
        return false;
    }
    return true;
}

int main (int argc, char *argv[]) {
    if(argc == 1) {
        print_help();
    }
    if(open_bmp("sample.bm", "rb")) {
        //
    } else {
        return 1;
    }

//    Bitmap_File_Header bmfh;
//    DIB_Header dibh;
//    fread(&bmfh, 1, sizeof(Bitmap_File_Header), fp);
//    fread(&dibh, 1, sizeof(DIB_Header), fp);
//    print_file_header(bmfh);
//    printf("---------------\n");
//    print_dib_header(dibh);
//    printf("%ld", sizeof(Bitmap_File_Header) + sizeof(DIB_Header));
//    fseek(fp, bmfh.offset_to_pixels, SEEK_SET);
}