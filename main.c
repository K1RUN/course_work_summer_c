#include "CLI/helpmenu.h"
#include "BMP_parser/bmp_parser.h"
#include "BMP_parser/bmp_structs.h"
#include "Error_handling/error_handler.h"
#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>
#include "Geometry/triangle.h"
#include "Geometry/find_max_rect.h"

int main (int argc, char *argv[]) {
    char *filename = "tiny11_11.bmp";
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
    Pixel point1 = {1, 3, {255, 255, 255}};
    Pixel point2 = {7,  1, {255, 255, 255}};
    Pixel point3 = {6, 7, {255, 255, 255}};
    draw_triangle(image, point1, point2, point3);
    // finding the biggest white rect
    Rgb color = {255, 255, 255};
    Sub_matrix subMatrix = get_color_matrix(image, color);
    print_matrix(subMatrix);
    make_histogram(&subMatrix);
    printf("\n");
    print_matrix(subMatrix);
    Rectangle rect = find_largest_rect(subMatrix);
    Pixel p1 = rect.v1; Pixel p3 = rect.v2;
    Pixel p2 = {p1.x, p3.y, {0, 0, 255}};
    Pixel p4 = {p3.x, p1.y, {0, 0, 255}};
    p1.color.r = 255; p1.color.g = 0; p1.color.b = 0;
    p3.color.r = 255; p3.color.g = 0; p3.color.b = 0;
    Bresenham(image, p1, p2);
    Bresenham(image, p1, p4);
    Bresenham(image, p3, p2);
    Bresenham(image, p3, p4);
    for(unsigned int i = image.h; i > 0; i--) {
        // writing scansets in reverse order
        fwrite(image.matrix[i - 1], 1, image.w * sizeof(Rgb), fout);
        fwrite(garbage, 1, offset, fout);
    }
    printf("%ld\n", sizeof(Bitmap_File_Header));
    printf("%ld\n", sizeof(DIB_Header));
    fclose(fout);
    return 0;
}