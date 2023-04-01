#include "helpmenu.h"
#include "BMP_parser/bmp_parser.h"
#include "BMP_parser/bmp_structs.h"
#include "Testing/error_handler.h"
#include <stdio.h>
#include <stdbool.h>
#include <getopt.h>
#include <stdlib.h>

void set_pixel(Rgb** matrix, Pixel point, Rgb color){

}

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
    Pixels image;
    image.h = dibh.image_height;
    image.w = dibh.image_width;
    unsigned short offset = image.w * sizeof(Rgb) % 4;
    offset = offset ? 4 - offset : 0;
    // width of every scanset including trash
    image.matrix = malloc(image.h * sizeof(Rgb*));
    fseek(fp, bmfh.offset_to_pixels, SEEK_SET);
    for(unsigned int i = 0; i < image.h; i++){
        image.matrix[i] = calloc(image.w*sizeof(Rgb), 1);
        if (fread(image.matrix[i], 1, image.w*sizeof(Rgb), fp) != image.w*sizeof(Rgb)) {
            process_error(FREAD_ERR); break;
        }
    }
    FILE* fout = fopen("result.bmp", "wb");
    fwrite(&bmfh, 1, sizeof(Bitmap_File_Header), fout);
    fwrite(&dibh, 1, sizeof(DIB_Header), fout);
    fseek(fout, bmfh.offset_to_pixels, SEEK_SET);
    char* garbage = calloc(offset * sizeof(Rgb), 1);
    for(unsigned int i = 0; i < image.h; i++){
        fwrite(image.matrix[i], 1, image.w * sizeof(Rgb), fout);
        fwrite(garbage, 1, offset, fout);
    }
    printf("%ld\n", sizeof(DIB_Header));
    fclose(fp);
    fclose(fout);
    return 0;
}