#include "triangle.h"

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

Pixel center_of_mass(Pixel vertex1, Pixel vertex2, Pixel vertex3) {
    Pixel center = {(vertex1.x + vertex2.x + vertex3.x)/3, (vertex1.y + vertex2.y + vertex3.y)/3,
                    {0, 0, 255}};
    return center;
}

Pixel circumscribed_circle_cent(Pixel vertex1, Pixel vertex2, Pixel vertex3) {
    Pixel center;
    center.color.r = 255; center.color.g = 0; center.color.b = 0;
    int x1 = vertex1.x; int y1 = vertex1.y;
    int x2 = vertex2.x; int y2 = vertex2.y;
    int x3 = vertex3.x; int y3 = vertex3.y;
    int x12 = x1 - x2; int x23 = x2 - x3; int x31 = x3 - x1;
    int y12 = y1 - y2; int y23 = y2 - y3; int y31 = y3 - y1;
    int z1 = (x1 * x1) + (y1 * y1); int z2 = (x2 * x2) + (y2 * y2); int z3 = (x3 * x3) + (y3 * y3);
    int zx = y12 * z3 + y23 * z1 + y31 * z2; int zy = x12 * z3 + x23 * z1 + x31 * z2;
    int z = x12 * y31 - y12 * x31;
    int a = -zx/(2 * z); int b = zy/(2 * z);
    center.x = a; center.y = b;
    return center;
}

Pixel get_projection(Pixel p, Pixel vertex1, Pixel vertex2) {
    // direction vector coordinates
    int x1 = vertex2.x - vertex1.x; int y1 = vertex2.y - vertex1.y;
    Pixel center;
    center.color.r = 255; center.color.g = 0; center.color.b = 0;
    if(x1 == 0) {
        center.x = vertex1.x; center.y = p.y;
        return center;
    } else if (y1 == 0) {
        center.x = p.x; center.y = vertex1.y;
        return center;
    } else {
        float nx = (float) y1;
        float ny = (float) -x1;
        float v2x = (float) vertex2.x;
        float v2y = (float) vertex2.y;
        float v1x = (float) vertex1.x;
        float v1y = (float) vertex1.y;
        // two line intercept equation
        float dvy = (float) (v2y - v1y);
        float dvx = (float) (v2x - v1x);
        float k = (float) (dvy / dvx - ny / nx);
        float is_eq = (float) (v1x * dvy / dvx - p.x * ny / nx - v1y + p.y);
        float x = is_eq / k;
        float y = dvy * (x - v1x) / dvx + v1y;

        center.x = (int) (x < 0 ? (x - 0.5) : (x + 0.5));
        center.y = (int) (y < 0 ? (y - 0.5) : (y + 0.5));
        return center;
    }
}

Pixel incenter(Pixel vertex1, Pixel vertex2, Pixel vertex3) {
    Pixel center;
    center.color.r = 255; center.color.g = 0; center.color.b = 0;
    int x1 = vertex1.x; int y1 = vertex1.y;
    int x2 = vertex2.x; int y2 = vertex2.y;
    int x3 = vertex3.x; int y3 = vertex3.y;
    int x12 = x1 - x2; int x23 = x2 - x3; int x31 = x3 - x1;
    int y12 = y1 - y2; int y23 = y2 - y3; int y31 = y3 - y1;
    float l12 = (float)(sqrt(x12 * x12 + y12 * y12));
    float l23 = (float)(sqrt(x23 * x23 + y23 * y23));
    float l31 = (float)(sqrt(x31 * x31 + y31 * y31));
    float perimeter = (float)(l12 + l23 + l31);
    float x = (x1 * l23 + x2 * l31 + x3 * l12)/perimeter;
    float y = (y1 * l23 + y2 * l31 + y3 * l12)/perimeter;
    center.x = (int)(x < 0 ? (x - 0.5) : (x + 0.5));
    center.y = (int)(y < 0 ? (y - 0.5) : (y + 0.5));
    return center;
}

void Homothety(Pixels img, Pixel vertex1, Pixel vertex2, Pixel vertex3, Pixel center, unsigned thickness) {
    // arr for storing pixels that connect center of homothety and vertices
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
    // gets a point on a line, which locates in offset pixels from first point
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
    vertex1.color.r = 255; vertex1.color.g = 0; vertex1.color.b = 0;
    vertex2.color.r = 0; vertex2.color.g = 255; vertex2.color.b = 0;
    vertex3.color.r = 0; vertex3.color.g = 0; vertex3.color.b = 255;
    set_pixel(img, vertex1);
    set_pixel(img, vertex2);
    set_pixel(img, vertex3);
//    Pixel center = circumscribed_circle_cent(vertex1, vertex2, vertex3);
//    set_pixel(img, center);
    Pixel center = center_of_mass(vertex1, vertex2, vertex3);
    set_pixel(img, center);
//    Pixel proj1 = get_projection(center, vertex1, vertex2);
//    set_pixel(img, proj1);
//    Pixel proj2 = get_projection(center, vertex2, vertex3);
//    set_pixel(img, proj2);
//    Pixel proj3 = get_projection(center, vertex1, vertex3);
//    set_pixel(img, proj3);
    Homothety(img, vertex1, vertex2, vertex3, center, 20);
//    set_pixel(img, center);
//    Homothety(img, proj1, proj2, proj3, center, 10);
    Bresenham(img, center, vertex1);
    Bresenham(img, center, vertex2);
    Bresenham(img, center, vertex3);

}