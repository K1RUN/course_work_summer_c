#include "bmp_parser.h"

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
    if(fp == NULL) {
        fprintf(stderr, "Failed while opening the bmp file\n");
        return false;
    }
    fclose(fp);
    return true;
}

bool check_file(char* filename) {
    if(open_bmp(filename, "rb") == false) return false;
    Bitmap_File_Header bmfh = parse_bmfh(filename);
    DIB_Header dibh = parse_dib(filename);
    if(bmfh.signature != 0x4d42) {
        fprintf(stderr, "File %s is not a BMP file\n", filename);
        return false;
    }
    if(dibh.dib_header_size != 40) {
        fprintf(stderr, "This version of BMP is not supported in this program\n");
        return false;
    }
    if(dibh.compression != 0) {
        fprintf(stderr, "BMP image has a compression property\n");
        return false;
    }
    return true;
}

unsigned short get_offset(size_t width) {
    unsigned short offset = width * sizeof(Rgb) % 4;
    offset = offset ? 4 - offset : 0;
    return offset;
}

Bitmap_File_Header parse_bmfh(char* filename) {
    Bitmap_File_Header bmfh;
    bmfh.signature = 0;
    if(!open_bmp(filename, "rb")) return bmfh;
    FILE *fp = fopen(filename, "rb");
    fread(&bmfh, 1, sizeof(Bitmap_File_Header), fp);
    fclose(fp);
    return bmfh;
}

DIB_Header parse_dib(char* filename) {
    DIB_Header dibh;
    dibh.dib_header_size = 0;
    if(!open_bmp(filename, "rb")) return dibh;
    FILE *fp = fopen(filename, "rb");
    fseek(fp, sizeof(Bitmap_File_Header), SEEK_SET);
    fread(&dibh, 1, sizeof(DIB_Header), fp);
    fclose(fp);
    return dibh;
}

void print_info(char* filename) {
    if(open_bmp(filename, "rb") == false) {
        fprintf(stderr, "There is no file with name %s in current directory\n", filename);
        return;
    }
    printf("FILE INFO\n");
    Bitmap_File_Header bmfh = parse_bmfh(filename);
    if(bmfh.signature != 0x4d42) {
        fprintf(stderr, "This file is not in a bmp format\n");
        return;
    }
    DIB_Header dibh = parse_dib(filename);
    print_file_header(bmfh);
    print_dib_header(dibh);
}