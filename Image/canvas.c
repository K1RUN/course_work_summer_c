#include "canvas.h"

Pixels create_canvas(size_t h, size_t w) {
    Pixels canvas;
    canvas.w = w; canvas.h = h;
    canvas.matrix = malloc(canvas.h * sizeof(Rgb*));
    Rgb* tmp_scanline;
    for(int i = 0; i < canvas.h; i++) {
        tmp_scanline = malloc(canvas.w * sizeof(Rgb));
        if(tmp_scanline == NULL) {
            fprintf(stderr, "Error while memory allocating in create_canvas function");
            return canvas;
        }
        canvas.matrix[i] = tmp_scanline;
    }
    return canvas;
}

void free_canvas(Pixels canvas) {
    for(int i = 0; i < canvas.h; i++) {
        free(canvas.matrix[i]);
    }
    free(canvas.matrix);
}

void canvas_draw(Pixels canvas, char *filename) {
    if(!open_bmp(filename, "rb")) return;
    FILE *fp = fopen(filename, "rb");
    Bitmap_File_Header bmfh;
    bmfh = parse_bmfh(filename);
    fseek(fp, bmfh.offset_to_pixels, SEEK_SET);
    // padding size
    unsigned short offset = get_offset(canvas.w);
    for(unsigned int i = canvas.h; i != 0; i--){
        // scansets come in reverse order by default, so reading it inverse
        if (fread(canvas.matrix[i - 1], 1, canvas.w*sizeof(Rgb), fp) != canvas.w * sizeof(Rgb)) {
            fprintf(stderr, "Error while reading scanlines from a file\n");
            return;
        }
        fseek(fp, offset, SEEK_CUR);
    }
    fclose(fp);
}

void canvas_write(Pixels canvas, char *filename_old, char *filename_new) {
    Bitmap_File_Header bmfh; DIB_Header dibh;
    bmfh = parse_bmfh(filename_old);
    dibh = parse_dib(filename_old);
    if(!open_bmp(filename_new, "wb")) return;
    FILE *fout = fopen(filename_new, "wb");
    unsigned short offset = get_offset(canvas.w);
    size_t new_height = canvas.h; size_t new_width = canvas.w;
    size_t new_image_size = (canvas.w * sizeof(Rgb) + offset) * canvas.h;
    // VULNERABILITY: adding sizeof(dibh) to new_file_size may be wrong while working with files where
    // dib_header weights more than 40 bytes, so that is why dibh.dib_header_size is below in the sum
    size_t new_file_size = new_image_size + dibh.dib_header_size + sizeof(bmfh);
    bmfh.file_size = new_file_size;
    dibh.image_width = new_width; dibh.image_height = new_height;
    dibh.image_size = new_image_size;
    fwrite(&bmfh, 1, sizeof(Bitmap_File_Header), fout);
    fwrite(&dibh, 1, sizeof(DIB_Header), fout);
    fseek(fout, bmfh.offset_to_pixels, SEEK_SET);
    char* garbage = calloc(offset, 1);
    for(unsigned int i = canvas.h; i > 0; i--) {
        // writing scansets in reverse order
        fwrite(canvas.matrix[i - 1], 1, canvas.w * sizeof(Rgb), fout);
        fwrite(garbage, 1, offset, fout);
    }
    fclose(fout);
    free(garbage);
}