#include "general.h"


bool in_area(Pixel point, size_t height, size_t width) {
    if(point.y < height && point.x < width){
        return true;
    }
    return false;
}

void set_pixel(Pixels img, Pixel point) {
    if (img.matrix == NULL || in_area(point, img.h, img.w) == false) return;
    img.matrix[point.x][point.y].r = point.color.r;
    img.matrix[point.x][point.y].g = point.color.g;
    img.matrix[point.x][point.y].b = point.color.b;
}