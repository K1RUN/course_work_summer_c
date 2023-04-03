#include "line_draw.h"

void drawLine(Pixels img, Pixel point1, Pixel point2) {
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