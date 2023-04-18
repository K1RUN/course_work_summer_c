#include "collage.h"

Pixels create_collage(Pixels image, int n, int m) {
    if(n > 0 && m > 0) {
        size_t new_h = n * image.h;
        size_t new_w = m * image.w;
        Pixels canvas = create_canvas(new_h, new_w);
        // TODO
    }
}