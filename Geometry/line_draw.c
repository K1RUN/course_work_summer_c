#include "line_draw.h"

void Bresenham(Pixels img, Pixel point1, Pixel point2) {
    // algorithm property: line approximation depends on the order of the argument points
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
        // color of the line is set by the first point
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

Pixel line_intercept(Vector direct1, Pixel point1, Vector direct2, Pixel point2) {
    // returns an interception point of two lines
    Pixel intercept;
    float x; float y;
    float d1y = (float)direct1.y; float d1x = (float)direct1.x;
    float d2y = (float)direct2.y; float d2x = (float)direct2.x;
    float y1 = (float)point1.y; float x1 = (float)point1.x;
    float y2 = (float)point2.y; float x2 = (float)point2.x;
    // situation where line is parallel to oX axis or oY axis
    if (direct1.x == 0 && direct2.x == 0 || direct2.y == 0 && direct1.y == 0) {
        intercept.x = -1; intercept.y = -1;
        return intercept;
    }
    if (direct1.x == 0 || direct2.x == 0) {
        if (direct1.x == 0) {
            x = (float)point1.x;
            y = (x - x2) * d2y/d2x + y2;
        } else if (direct2.x == 0) {
            x = (float)point2.x;
            y = (x - x1) * d1y/d1x + y1;
        }
        intercept.x = (int)(x < 0 ? (x - 0.5) : (x + 0.5));
        intercept.y = (int)(y < 0 ? (y - 0.5) : (y + 0.5));
        return intercept;
    } else {
        float k = (float)(d2y - (d1y * d2x)/d1x);
        float is_eq = (float)((-x1 * d1y * d2x)/d1x + (y1 - y2) * d2x + x2 * d2y);
        x = is_eq/k;
    }
    if (direct1.y == 0 || direct2.y == 0) {
        if (direct1.y == 0) {
            y = (float)point1.y;
        } else if (direct2.y == 0) {
            y = (float)point2.y;
        }
    } else {
        y = (x - x1) * d1y/d1x + y1;
    }
    // basically just transformed line intercept equation
    intercept.x = (int)(x < 0 ? (x - 0.5) : (x + 0.5));
    intercept.y = (int)(y < 0 ? (y - 0.5) : (y + 0.5));
    return intercept;
}

void plotLineWidth(Pixels img, Pixel point1, Pixel point2, float wd) {
    int x0 = point1.x; int y0 = point1.y;
    int x1 = point2.x; int y1 = point2.y;
    int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
    int dy = abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
    int err = dx - dy, e2, x2, y2;                          /* error value e_xy */
    float ed = dx + dy == 0 ? 1 : sqrt((float) dx * dx + (float) dy * dy);
    for (wd = (wd + 1) / 2;;) {                                   /* pixel loop */
        point1.x = x0;
        point1.y = y0;
        set_pixel(img, point1);
        e2 = err;
        x2 = x0;
        if (2 * e2 >= -dx) {                                           /* x step */
            for (e2 += dy, y2 = y0; e2 < ed * wd && (y1 != y2 || dx > dy); e2 += dx) {
                point1.x = x0;
                point1.y = (y2 += sy);
                set_pixel(img, point2);
            }
            if (x0 == x1) break;
            e2 = err;
            err -= dy;
            x0 += sx;
        }
        if (2 * e2 <= dy) {                                            /* y step */
            for (e2 = dx - e2; e2 < ed * wd && (x1 != x2 || dx < dy); e2 += dy) {
                point1.x = (x2 += sx);
                point1.y = y0;
                set_pixel(img, point1);
            }
            if (y0 == y1) break;
            err += dx;
            y0 += sy;
        }
    }
}

line_coords Perpendicular(Pixel point1, Pixel point2, unsigned int len) {
    // algorithm property: line approximation depends on the order of the argument points
    line_coords coords;
    int x1 = (int)point1.x;
    int x1_ = (int)point1.x;
    int x2 = (int)point2.x;
    int y1 = (int)point1.y;
    int y1_ = (int)point1.y;
    int y2 = (int)point2.y;
    const int deltaX = abs(x2 - x1);
    const int deltaY = abs(y2 - y1);
    const int signX = x1 < x2 ? 1 : -1;
    const int signY = y1 < y2 ? 1 : -1;
    int error = deltaX - deltaY;
    for(int i = 0; i < len; i++) {
        point1.x = x1; point1.y = y1;
        point2.x = x1_; point2.y = y1_;
        // color of the line is set by the first point
        int error2 = error * 2;
        if(error2 > -deltaY) {
            error -= deltaY;
            y1 -= signY;
            y1_ += signY;
        }
        if(error2 < deltaX) {
            error += deltaX;
            x1 += signX;
            x1_ -= signX;
        }
    }
    // sorting vertices (just because it is convenient to use)
    coords.y1 = y1;
    coords.y2 = y1_;
    coords.x1 = x1;
    coords.x2 = x1_;
    return coords;
}

Rectangle Boundary_rect(Pixel p1, Pixel p2, Pixel p3, Pixel p4) {
    int x_arr[4] = {p1.x, p2.x, p3.x, p4.x};
    int y_arr[4] = {p1.y, p2.y, p3.y, p4.y};
    int min_y = y_arr[0], max_y = 0;
    int min_x = x_arr[0], max_x = 0;
    for(int i = 0; i < 4; i++) {
        if(max_y < y_arr[i]) {
            max_y = y_arr[i];
        }
        if(max_x < x_arr[i]) {
            max_x = x_arr[i];
        }
        if(min_y > y_arr[i]) {
            min_y = y_arr[i];
        }
        if(min_x > x_arr[i]) {
            min_x = x_arr[i];
        }
    }
    Pixel tmp1 = {min_x, min_y};
    Pixel tmp2 = {max_x, max_y};
    Rectangle rect; rect.v1 = tmp1; rect.v2 = tmp2;
    return rect;
}

void draw_thick_line(Pixels img, Pixel p1, Pixel p2, Rgb color, unsigned int thickness) {
    if(thickness > 0) {
        Rectangle rect;
        Pixel n1, n2, n3, n4;
        if(p1.y > p2.y) {
            Pixel tmp;
            tmp = p1; p1 = p2; p2 = tmp;
        }
        line_coords coords1 = Perpendicular(p1, p2, thickness);
        line_coords coords2 = Perpendicular(p2, p1, thickness);
        n1.x = coords1.x1; n1.y = coords1.y1;
        n2.x = coords1.x2; n2.y = coords1.y2;
        n3.x = coords2.x1; n3.y = coords2.y1;
        n4.x = coords2.x2; n4.y = coords2.y2;
        // if line is parallel with one of the axis
        if(p1.x == p2.x || p1.y == p2.y) {
            rect.v1 = n1; rect.v2 = n4;
            fill_rect(img, rect, color);
            return;
        }
        Rectangle bound = Boundary_rect(n1, n2, n3, n4);
        Pixel tmp;
        Pixel top_1 = {bound.v2.x, bound.v1.y, 255, 255, 0};
        Pixel top_2 = {bound.v1.x, bound.v1.y, 255, 255, 0};
        Pixel bottom_1 = {bound.v1.x, bound.v2.y, 255, 255, 0};
        Pixel bottom_2 = {bound.v2.x, bound.v2.y, 255, 255, 0};
        if(abs(top_1.x - p1.x) > abs(top_2.x - p1.x)) {
            tmp = top_1; top_1 = top_2; top_2 = tmp;
        }
        if(abs(bottom_1.x - p2.x) > abs(bottom_2.x - p2.x)) {
            tmp = bottom_1; bottom_1 = bottom_2; bottom_2 = tmp;
        }
        tmp.color = color;
        for(int i = bound.v1.y; i <= bound.v2.y; i++) {
            tmp.y = i;
            for(int j = bound.v1.x; j <= bound.v2.x; j++) {
                tmp.x = j;
                if(is_in_triangle(top_1, n1, n2, tmp) == false &&
                    is_in_triangle(bottom_1, n3, n4, tmp) == false &&
                    is_in_triangle(top_2, n1, n4, tmp) == false &&
                    is_in_triangle(bottom_2, n2, n3, tmp) == false) {
                    set_pixel(img, tmp);
                }
            }
        }
    }
}