#include "CLI/helpmenu.h"
#include "Image/bmp_parser.h"
#include "Image/bmp_structs.h"
#include "Image/canvas.h"
#include "Error_handling/error_handler.h"
#include <stdio.h>
#include "Image/collage.h"
#include <getopt.h>
#include "Geometry/triangle.h"
#include "Geometry/find_max_rect.h"

int main (int argc, char *argv[]) {
    char *filename = "kirill.bmp";
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
    fclose(fp);
    Pixels image = create_canvas(dibh.image_height, dibh.image_width);
    canvas_draw(image, filename);
    create_collage(&image, 1, 100);
    canvas_write(image, filename, "result.bmp");
    free_canvas(image);
    return 0;
}