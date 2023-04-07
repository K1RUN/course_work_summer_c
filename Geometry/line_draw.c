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

void Homothety(Pixels img, Pixel vertex1, Pixel vertex2, Pixel vertex3, unsigned thickness) {
    // arr for storing pixels that connect center of homethety and vertices
    Pixel center = {(vertex1.x + vertex2.x + vertex3.x)/3, (vertex1.y + vertex2.y + vertex3.y)/3, {0, 0, 255}};
    Pixel *arr1 = (Pixel*)malloc(sizeof(Pixel) * BUF);
    Pixel *arr2 = (Pixel*)malloc(sizeof(Pixel) * BUF);
    Pixel *arr3 = (Pixel*)malloc(sizeof(Pixel) * BUF);
    DDA(vertex1, center, &arr1);
    Bresenham(img, vertex1, center);
    DDA(vertex2, center, &arr2);
    Bresenham(img, vertex2, center);
    DDA(vertex3, center, &arr3);
    Bresenham(img, vertex3, center);
    for(int i = 0; i < thickness; i++) {
        Pixel p1 = arr1[i];
        Pixel p2 = arr2[i];
        Pixel p3 = arr3[i];
        Bresenham(img, arr1[i], arr2[i]);
        Bresenham(img, arr2[i], arr3[i]);
        Bresenham(img, arr1[i], arr3[i]);
    }
}

void DDA(Pixel point1, Pixel point2, Pixel** arr) {
    int x1 = (int)point1.x;
    int x2 = (int)point2.x;
    int y1 = (int)point1.y;
    int y2 = (int)point2.y;
    const int deltaX = abs(x2 - x1);
    const int deltaY = abs(y2 - y1);
    const int signX = x1 < x2 ? 1 : -1;
    const int signY = y1 < y2 ? 1 : -1;
    int error = deltaX - deltaY;
    int arr_len = BUF;
    int i = 0;
    while(x1 != x2 || y1 != y2) {
        point1.x = x1; point1.y = y1;
        if(arr_len == i) {
            Pixel* tmp = (Pixel*)realloc(*arr, (arr_len + BUF) * sizeof(Pixel));
            if(tmp == NULL) {
                free(*arr);
                log_fatal("Error while reallocating memory");
                return;
            } else {
                *arr = tmp;
                arr_len += BUF;
            }
        }
        (*arr)[i++] = point1;
        int error2 = error;
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

Rectangle Boundary(Pixel point1, Pixel point2, Pixel point3) {
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
    Rectangle rect = Boundary(vertex1, vertex3, vertex2);
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
    Pixel center = {(vertex1.x + vertex2.x + vertex3.x)/3, (vertex1.y + vertex2.y + vertex3.y)/3, {0, 0, 255}};
    set_pixel(img, center);
    Homothety(img, vertex1, vertex2, vertex3, 30);
}