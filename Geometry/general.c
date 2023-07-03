#include "general.h"

bool in_area(Pixel point, size_t height, size_t width) {
    if(point.x >= 0 && point.y >= 0){
        return true;
    }
    return false;
}

void set_pixel(Pixels img, Pixel point) {
    if (img.matrix == NULL || in_area(point, img.h, img.w) == false) return;
    img.matrix[point.y][point.x].r = point.color.r;
    img.matrix[point.y][point.x].g = point.color.g;
    img.matrix[point.y][point.x].b = point.color.b;
}