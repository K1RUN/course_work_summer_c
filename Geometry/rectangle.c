#include "rectangle.h"

void draw_rect_borders(Pixels img, Rectangle rect, Rgb color) {
    int x_min = min(rect.v1.x, rect.v2.x); int x_max = max(rect.v1.x, rect.v2.x);
    int y_min = min(rect.v1.y, rect.v2.y); int y_max = max(rect.v1.y, rect.v2.y);
    Pixel top_left = {x_min, y_min, color}; Pixel top_right = {x_max, y_min, color};
    Pixel bottom_left = {x_min, y_max, color}; Pixel bottom_right = {x_max, y_max, color};
    Bresenham(img, top_left, top_right);
    Bresenham(img, top_left, bottom_left);
    Bresenham(img, bottom_left, bottom_right);
    Bresenham(img, top_right, bottom_right);
}

void fill_rect(Pixels img, Rectangle rect, Rgb color) {
    int x_min = min(rect.v1.x, rect.v2.x); int x_max = max(rect.v1.x, rect.v2.x);
    int y_min = min(rect.v1.y, rect.v2.y); int y_max = max(rect.v2.y, rect.v2.y);
    for(int i = y_min; i <= y_max; i++) {
        for(int j = x_min; j <= x_max; j++) {
            Pixel p = {j, i, color};
            set_pixel(img, p);
        }
    }
}