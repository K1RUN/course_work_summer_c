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
    if(!open_bmp(filename, "rb") || canvas.matrix == NULL) return;
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
    if(canvas.matrix == NULL) {
        return;
    }
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

Pixels canvas_copy(Pixels img, Pixel start, Pixel end) {
    if(img.matrix == NULL || in_area(start, img.h, img.w) == false ||
        in_area(end, img.h, img.w) == false) {
        fprintf(stderr, "Invalid image or coordinates were given\n");
        return (Pixels){};
    }
    if(end.x >= img.w) {
        end.x = img.w - 1;
    }
    if(end.y >= img.h) {
        end.y = img.h - 1;
    }
    Pixel min; min.x = min(start.x, end.x); min.y = min(start.y, end.y);
    Pixel max; max.x = max(start.x, end.x); max.y = max(start.y, end.y);
    Pixels canvas_cpy = create_canvas(max.y - min.y, max.x - min.x);
    for(size_t i = min.y; i < max.y; i++) {
        for(size_t j = min.x; j < max.x; j++) {
            Pixel p = {j - min.x, i - min.y, img.matrix[i][j]};
            set_pixel(canvas_cpy, p);
        }
    }
    return canvas_cpy;
}

bool canvas_paste(Pixels img_dest, Pixels canvas_cpy, Pixel start) {
    if(img_dest.matrix == NULL || canvas_cpy.matrix == NULL) {
        return false;
    }
    for(size_t i = start.y; i < canvas_cpy.h + start.y; i++) {
        for(size_t j = start.x; j < canvas_cpy.w + start.x; j++) {
            if(i >= 0 && j >= 0 && i < img_dest.h && j < img_dest.w) {
                Pixel p = {j, i, canvas_cpy.matrix[i - start.y][j - start.x]};
                set_pixel(img_dest, p);
            }
        }
    }
    return true;
}

void img_rotate(Pixels img, Pixel start, Pixel end, int angle) {
    if(img.matrix == NULL || in_area(start, img.h, img.w) == false ||
       in_area(end, img.h, img.w) == false) {
        fprintf(stderr, "Invalid image or coordinates for rotate were given\n");
        return;
    }
    angle = angle % 360;
    Pixels area = canvas_copy(img, start, end);
    Pixel min; min.x = min(start.x, end.x); min.y = min(start.y, end.y);
    Pixel max; max.x = max(start.x, end.x); max.y = max(start.y, end.y);
    Pixel center; center.x = (max.x - min.x) / 2; center.y = (max.y - min.y) / 2;
    const int rotate_90[4] = {0, -1, 1, 0};
    const int rotate_180[4] = {-1, 0, 0, -1};
    const int rotate_270[4] = {0, 1, -1, 0};
    const int mirror_Ox[4] = {1, 0, 0, -1};
    const int mirror_Oy[4] = {-1, 0, 0, 1};
    switch(angle) {
        case 90: {
            for (size_t i = min.y; i < max.y; i++) {
                for (size_t j = min.x; j < max.x; j++) {
                    size_t new_x = (j - center.x) * rotate_90[0] + (i - center.y) * rotate_90[1] + center.x;
                    size_t new_y = (j - center.x) * rotate_90[2] + (i - center.y) * rotate_90[3] + center.y;
                    Pixel p = {new_x, new_y, area.matrix[i - min.y][j - min.x]};
                    set_pixel(img, p);
                }
            }
            break;
        }
        case 180: {
            for(size_t i = min.y; i < max.y; i++) {
                for(size_t j = min.x; j < max.x; j++) {
                    size_t new_x = (j - center.x) * rotate_180[0] + (i - center.y) * rotate_180[1] + center.x;
                    size_t new_y = (j - center.x) * rotate_180[2] + (i - center.y) * rotate_180[3] + center.y;
                    Pixel p = {new_x, new_y, area.matrix[i - min.y][j - min.x]};
                    set_pixel(img, p);
                }
            }
            break;
        }
        case 270: {
            for(size_t i = min.y; i < max.y; i++) {
                for(size_t j = min.x; j < max.x; j++) {
                    size_t new_x = (j - center.x) * rotate_270[0] + (i - center.y) * rotate_270[1] + center.x;
                    size_t new_y = (j - center.x) * rotate_270[2] + (i - center.y) * rotate_270[3] + center.y;
                    Pixel p = {new_x, new_y, area.matrix[i - min.y][j - min.x]};
                    set_pixel(img, p);
                }
            }
            break;
        }
        default: {
            break;
        }
    }
    free_canvas(area);
}

void canvas_merge(Pixels canvas1, Pixels canvas2, char* filename_old, char* filename_new) {
    size_t w = max(canvas1.w, canvas2.w) * 2; size_t h = max(canvas1.h, canvas2.h) * 2;
    Pixels new_canvas = create_canvas(h,w);
    for(int i = 0; i < h; i++) {
        for(int j = 0; j < w; j++) {
            Rgb white = {255,255,255};
            new_canvas.matrix[i][j] = white;
        }
    }
    for(int i = 0; i < h * 2; i++) {
        if(i%2 == 0) {
            // canvas1
            for(int j = 0; j < w * 2; j++) {
                if(i < canvas1.h * 2 && j < canvas1.w * 2 && j % 2 == 0) {
                    new_canvas.matrix[i][j] = canvas1.matrix[i / 2][j / 2];
                }
            }
            for(int j = 0; j < w * 2; j++) {
                if(i < canvas2.h * 2 && j < canvas2.w * 2 && j % 2 != 0) {
                    new_canvas.matrix[i][j] = canvas2.matrix[i / 2][j / 2];
                }
            }
        } else if(i%2 != 0) {
            // canvas1
            for(int j = 0; j < w * 2; j++) {
                if(i < canvas2.h * 2 && j < canvas2.w * 2 && j % 2 == 0) {
                    new_canvas.matrix[i][j] = canvas2.matrix[i / 2][j / 2];
                }
            }
            for(int j = 0; j < w * 2; j++) {
                if(i < canvas1.h * 2 && j < canvas1.w * 2 && j % 2 != 0) {
                    new_canvas.matrix[i][j] = canvas1.matrix[i / 2][j / 2];
                }
            }
        }
    }
    canvas_write(new_canvas, filename_old, filename_new);
    free_canvas(canvas1);
    free_canvas(canvas2);
    free_canvas(new_canvas);
}

void canvas_fill(Pixels canvas, Pixel start, int width, int height, Rgb color) {
    if(width <= 0 || height <= 0) {
        fprintf(stderr, "Invalid height or width were given\n");
        return;
    }
    Pixel end = {start.x + width, start.y + height};
    Pixels canvas_crop = canvas_copy(canvas, start, end);
    for(int i = 0; i < canvas.h; i++) {
        for(int j = 0; j < canvas.w; j++) {
            canvas.matrix[i][j] = color;
        }
    }
    canvas_paste(canvas, canvas_crop, start);
    free_canvas(canvas_crop);
}