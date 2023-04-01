#include "helpmenu.h"
#include "BMP_parser/bmp_parser.h"
#include "Testing/error_handler.h"
#include <stdio.h>
#include <stdbool.h>
#include <getopt.h>
#include <stdlib.h>

int main (int argc, char *argv[]) {
    char *filename = "sample.bmp";
    char *mode = "rb";
    if(argc == 1) {
        print_help();
    }
    if(!open_bmp(filename, mode)) return FOPEN_ERR;
    FILE* fp = fopen(filename, mode);
    Bitmap_File_Header bmfh;
    DIB_Header dibh;
    fread(&bmfh, 1, sizeof(Bitmap_File_Header), fp);
    print_file_header(bmfh);
    fread(&dibh, 1, sizeof(DIB_Header), fp);
    print_dib_header(dibh);
    unsigned int H = dibh.image_height;
    unsigned int W = dibh.image_width;
    unsigned short offset = W * sizeof(Rgb) % 4;
    offset = offset ? 4 - offset : 0;
    Rgb** height = malloc(H*sizeof(Rgb*));
    fseek(fp, bmfh.offset_to_pixels, SEEK_SET);
    for(unsigned int i = 0; i < H; i++){
        Rgb* width = calloc(W*sizeof(Rgb) + offset, 1);
        height[i] = width;
        fread(height[i], 1, W*sizeof(Rgb) + offset, fp);
    }
    for(int i = 0; i < H/2; i++){
        height[i][i].b = 0;
        height[i][i].r = 255;
        height[i][i].g = 0;
    }
    FILE* fout = fopen("result.bmp", "wb");
    fwrite(&bmfh, 1, sizeof(Bitmap_File_Header), fout);
    fwrite(&dibh, 1, sizeof(DIB_Header), fout);
    fseek(fout, bmfh.offset_to_pixels, SEEK_SET);
    for(unsigned int i = 0; i < H; i++){
        fwrite(height[i], 1, W*sizeof(Rgb) + offset, fout);
    }
    printf("%ld\n", sizeof(Rgb));
    fclose(fp);
    fclose(fout);
    return 0;
}