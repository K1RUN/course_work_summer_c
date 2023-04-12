#include "CLI/helpmenu.h"
#include "BMP_parser/bmp_parser.h"
#include "BMP_parser/bmp_structs.h"
#include "Error_handling/error_handler.h"
#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>
#include "Geometry/triangle.h"
#include "Geometry/rectangle.h"
#include "Geometry/find_max_rect.h"

int main (int argc, char *argv[]) {
    char *filename = "simpsonsvr.bmp";
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
    Pixels image;
    image.h = dibh.image_height;
    // width of every scanset including trash
    image.w = dibh.image_width;
    unsigned short offset = image.w * sizeof(Rgb) % 4;
    offset = offset ? 4 - offset : 0;
    image.matrix = malloc(image.h * sizeof(Rgb*));
    fseek(fp, bmfh.offset_to_pixels, SEEK_SET);
    for(unsigned int i = image.h; i != 0; i--){
        // scansets come in reverse order by default, so reading it inverse
        image.matrix[i - 1] = calloc(image.w*sizeof(Rgb), 1);
        if (fread(image.matrix[i - 1], 1, image.w*sizeof(Rgb), fp) != image.w*sizeof(Rgb)) {
            process_error(FREAD_ERR); break;
        }
        fseek(fp, offset, SEEK_CUR);
    }
    fclose(fp);
    FILE* fout = fopen("result.bmp", "wb");
    fwrite(&bmfh, 1, sizeof(Bitmap_File_Header), fout);
    fwrite(&dibh, 1, sizeof(DIB_Header), fout);
    fseek(fout, bmfh.offset_to_pixels, SEEK_SET);
    char* garbage = calloc(offset, 1);
    // finding the biggest white rect
    Rgb white = {255, 255, 255};
    Rgb red = {0, 0, 255};
    find_and_recolor(image, white, red);
    for(unsigned int i = image.h; i > 0; i--) {
        // writing scansets in reverse order
        fwrite(image.matrix[i - 1], 1, image.w * sizeof(Rgb), fout);
        fwrite(garbage, 1, offset, fout);
    }
    fclose(fout);
    return 0;
}