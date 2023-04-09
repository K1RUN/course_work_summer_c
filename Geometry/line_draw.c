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