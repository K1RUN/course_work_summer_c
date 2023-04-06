#include "line_draw.h"

void Bresenham(Pixels img, Pixel point1, Pixel point2) {
    int x1 = (int)point1.x;
    int x2 = (int)point2.x;
    int y1 = (int)point1.y;
    int y2 = (int)point2.y;
    const int deltaX = abs(x2 - x1);
    const int deltaY = abs(y2 - y1);
    const int signX = x1 < x2 ? 1 : -1;
    const int signY = y1 < y2 ? 1 : -1;
    int error = deltaX - deltaY;
    set_pixel(img, point2);
    while(x1 != x2 || y1 != y2) {
        point1.x = x1; point1.y = y1;
        set_pixel(img, point1);
        int error2 = error * 2;
        if(error2 > -deltaY) {
            error -= deltaY;
            x1 += signX;
        }
        if(error2 < deltaX) {
            error += deltaX;
            y1 += signY;
        }
    }
}

void DDA(Pixels img, Pixel point1, Pixel point2) {
    int dx = (int)(point2.x - point1.x);
    int dy = (int)(point2.y - point1.y);
    int step;
    if(abs(dx) > abs(dy)) {
        step = abs(dx);
    } else {
        step = abs(dy);
    }
    double Xi = (double)dx / (double)step;
    double Yi = (double)dy / (double)step;
    double X_round = 0;
    double Y_round = 0;
    for(int i = 1; i <= step; i++) {
        set_pixel(img, point1);
        X_round += Xi;
        Y_round += Yi;
        point1.x = (int)(X_round < 0 ? (X_round - 0.5) : (X_round + 0.5));
        point1.y = (int)(Y_round < 0 ? (Y_round - 0.5) : (Y_round + 0.5));
    }
}

Rectangle Boundary(Pixels img, Pixel point1, Pixel point2, Pixel point3) {
    // coordinates for left upper vertex of the rectangle
    int x1 = min(point1.x, point2.x);
    x1 = min(x1, point3.x);
    int y1 = min(point1.y, point2.y);
    y1 = min(y1, point3.y);
    int x2 = max(point1.x, point2.x);
    x2 = max(x2, point3.x);
    int y2 = max(point1.y, point2.y);
    y2 = max(y2, point3.y);
    Rectangle rect;
    rect.v1.x = x1; rect.v1.y = y1;
    rect.v2.x = x2; rect.v2.y = y2;
    return rect;
}

void draw_triangle(Pixels img, Pixel vertex1, Pixel vertex2, Pixel vertex3) {
    Rectangle rect = Boundary(img, vertex1, vertex3, vertex2);
    Pixel p = {0, 0, {255, 255, 255}};
    for(int i = rect.v1.y; i <= rect.v2.y; i++) {
        for(int j = rect.v1.x; j <= rect.v2.x; j++) {
            // checking if vectors containing our vertices are under right hand rule
            int base_vect_mul = (vertex2.x - vertex1.x) * (vertex3.y - vertex1.y) -
                                (vertex2.y - vertex1.y) * (vertex3.x - vertex1.x);
            int k = base_vect_mul < 0 ? 1 : -1;
            p.x = j; p.y = i;
            // using vector multiplication properties https://erkaman.github.io/posts/fast_triangle_rasterization.html
            int vect_mul1 = k * ((vertex2.y - vertex1.y) * (p.x - vertex1.x) - (vertex2.x - vertex1.x) * (p.y - vertex1.y));
            int vect_mul2 = k * ((vertex3.x - vertex1.x) * (p.y - vertex1.y) - (vertex3.y - vertex1.y) * (p.x - vertex1.x));
            int vect_mul3 = k * ((vertex3.y - vertex2.y) * (p.x - vertex2.x) - (vertex3.x - vertex2.x) * (p.y - vertex2.y));
            if(vect_mul1 > 0 && vect_mul2 > 0 && vect_mul3 > 0) {
                    set_pixel(img, p);
                    // TODO
            }
        }
    }
    Bresenham(img, vertex1, vertex2);
    Bresenham(img, vertex2, vertex3);
    Bresenham(img, vertex1, vertex3);
    vertex1.color.g = 0; vertex1.color.r = 255; vertex1.color.b = 0;
    vertex2.color.g = 255; vertex2.color.r = 0; vertex2.color.b = 0;
    vertex3.color.g = 0; vertex3.color.r = 0; vertex3.color.b = 255;
    set_pixel(img, vertex1);
    set_pixel(img, vertex2);
    set_pixel(img, vertex3);
//    Pixel center = {(vertex1.x + vertex2.x + vertex3.x)/3, (vertex1.y + vertex2.y + vertex3.y)/3, {0, 0, 255}};
//    set_pixel(img, center);
}