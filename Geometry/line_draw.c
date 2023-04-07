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

bool is_in_triangle(Pixel vertex1, Pixel vertex2, Pixel vertex3, Pixel point) {
    // checking if vectors containing our vertices are under right hand rule
    int base_vect_mul = (vertex2.x - vertex1.x) * (vertex3.y - vertex1.y) -
                        (vertex2.y - vertex1.y) * (vertex3.x - vertex1.x);
    int k = base_vect_mul < 0 ? 1 : -1;
    // using vector multiplication properties https://erkaman.github.io/posts/fast_triangle_rasterization.html
    int vect_mul1 = k * ((vertex2.y - vertex1.y) * (point.x - vertex1.x) - (vertex2.x - vertex1.x) * (point.y - vertex1.y));
    int vect_mul2 = k * ((vertex3.x - vertex1.x) * (point.y - vertex1.y) - (vertex3.y - vertex1.y) * (point.x - vertex1.x));
    int vect_mul3 = k * ((vertex3.y - vertex2.y) * (point.x - vertex2.x) - (vertex3.x - vertex2.x) * (point.y - vertex2.y));
    if(vect_mul1 > 0 && vect_mul2 > 0 && vect_mul3 > 0) {
        return true;
    } else {
        return false;
    }
}


void Homothety(Pixels img, Pixel vertex1, Pixel vertex2, Pixel vertex3, unsigned thickness) {
    // arr for storing pixels that connect center of homethety and vertices
    Pixel center = {(vertex1.x + vertex2.x + vertex3.x)/3, (vertex1.y + vertex2.y + vertex3.y)/3, {0, 0, 255}};
    Pixel inner_vert1 = get_inner_vertex(vertex1, center, thickness);
    Pixel inner_vert2 = get_inner_vertex(vertex2, center, thickness);
    Pixel inner_vert3 = get_inner_vertex(vertex3, center, thickness);
    Rectangle rect = Boundary(vertex1, vertex3, vertex2);
    Pixel p = vertex3;
    for(int i = rect.v1.y; i <= rect.v2.y; i++) {
        for(int j = rect.v1.x; j <= rect.v2.x; j++) {
            p.x = j; p.y = i;
            if(is_in_triangle(vertex1, vertex2, vertex3, p) == true &&
            is_in_triangle(inner_vert1, inner_vert2, inner_vert3, p) == false) {
                set_pixel(img, p);
            }
        }
    }
}

Pixel get_inner_vertex(Pixel point1, Pixel point2, unsigned offset) {
    int x1 = (int)point1.x;
    int x2 = (int)point2.x;
    int y1 = (int)point1.y;
    int y2 = (int)point2.y;
    const int deltaX = abs(x2 - x1);
    const int deltaY = abs(y2 - y1);
    const int signX = x1 < x2 ? 1 : -1;
    const int signY = y1 < y2 ? 1 : -1;
    int error = deltaX - deltaY;
    int count = 0;
    while(x1 != x2 || y1 != y2) {
        if(count == offset) {
            return point1;
        }
        point1.x = x1; point1.y = y1;
        int error2 = error * 2;
        if(error2 > -deltaY) {
            error -= deltaY;
            x1 += signX;
        }
        if(error2 < deltaX) {
            error += deltaX;
            y1 += signY;
        }
        count++;
    }
    return point1;
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

void fill_triangle(Pixels img, Pixel vertex1, Pixel vertex2, Pixel vertex3, Pixel p) {
    Rectangle rect = Boundary(vertex1, vertex3, vertex2);
    for (int i = rect.v1.y; i <= rect.v2.y; i++) {
        for (int j = rect.v1.x; j <= rect.v2.x; j++) {
            p.x = j;
            p.y = i;
            if (is_in_triangle(vertex1, vertex2, vertex3, p) == true) {
                set_pixel(img, p);
            }
        }
    }
}

void draw_triangle(Pixels img, Pixel vertex1, Pixel vertex2, Pixel vertex3) {
    Pixel p = {0, 0, 255, 255, 255};
    fill_triangle(img, vertex1, vertex2, vertex3, p);
    Bresenham(img, vertex1, vertex2);
    Bresenham(img, vertex2, vertex3);
    Bresenham(img, vertex1, vertex3);
    set_pixel(img, vertex1);
    set_pixel(img, vertex2);
    set_pixel(img, vertex3);
    Homothety(img, vertex1, vertex2, vertex3, 20);
//    Bresenham(img, center, vertex3);
//    Bresenham(img, center, vertex2);
//    Bresenham(img, center, vertex1);
}