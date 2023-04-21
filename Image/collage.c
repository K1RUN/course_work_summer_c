#include "collage.h"

void paste_images(Pixels canvas, Pixels image, size_t x, size_t y) {
    for(size_t i = y; i < image.h + y; i++) {
        for(size_t j = x; j < image.w + x; j++) {
            if(i < canvas.h && j < canvas.w) {
                canvas.matrix[i][j] = image.matrix[i - y][j - x];
            }
        }
    }
}

void create_collage(Pixels *image, int n, int m) {
    if(n > 0 && m > 0) {
        size_t new_h = n * image->h;
        size_t new_w = m * image->w;
        // image of a bigger size
        Pixels canvas = create_canvas(new_h, new_w);
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                paste_images(canvas, *image, image->w * j, image->h * i);
            }
        }
        free_canvas(*image);
        *image = canvas;
    }
}