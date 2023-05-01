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
    if(vect_mul1 >= 0 && vect_mul2 >= 0 && vect_mul3 >= 0) {
        return true;
    } else {
        return false;
    }
}

void draw_edge(Pixels img, Pixel p1, Pixel p2, Pixel p3, Rgb color, unsigned int thickness) {
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
            int x_min = min(rect.v1.x, rect.v2.x); int x_max = max(rect.v1.x, rect.v2.x);
            int y_min = min(rect.v1.y, rect.v2.y); int y_max = max(rect.v1.y, rect.v2.y);
            for(int i = y_min; i <= y_max; i++) {
                for(int j = x_min; j <= x_max; j++) {
                    Pixel p = {j, i, color};
                    if (is_in_triangle(p1, p2, p3, p) == true) {
                        set_pixel(img, p);
                    }
                }
            }
            return;
        }
        Rectangle bound = Boundary_rect(n1, n2, n3, n4);
        Pixel tmp; tmp.color.r = 120;
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
                   is_in_triangle(bottom_2, n2, n3, tmp) == false &&
                   is_in_triangle(p1, p2, p3, tmp) == true) {
                        set_pixel(img, tmp);
                }
            }
        }
    }
}

void draw_thick_edges(Pixels img, Pixel vertex1, Pixel vertex2, Pixel vertex3, Rgb color, unsigned thickness){
    draw_edge(img, vertex1, vertex2, vertex3, color, thickness);
    draw_edge(img, vertex2, vertex3, vertex1, color, thickness);
    draw_edge(img, vertex1, vertex3, vertex2, color, thickness);
}

Pixel center_of_mass(Pixel vertex1, Pixel vertex2, Pixel vertex3) {
    Pixel center = {(vertex1.x + vertex2.x + vertex3.x)/3, (vertex1.y + vertex2.y + vertex3.y)/3,
                    {0, 0, 255}};
    return center;
}

Pixel circumscribed_circle_cent(Pixel vertex1, Pixel vertex2, Pixel vertex3) {
    // center of the outer circle of the triangle
    // https://www.cyberforum.ru/geometry/thread1190053.html - algorithm
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
    // returns projection of the point p on a line containing vertex1 and vertex2
    // direction vector coordinates
    // my algorithm
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
        // my algorithm
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
    // center of the incircle of the triangle
    // https://www.mathopenref.com/coordincenter.html - algorithm
    // https://www.wolframalpha.com/widgets/view.jsp?id=f0ee3310223fe38a989b2c818709393
    Pixel center;
    center.color.r = 255; center.color.g = 0; center.color.b = 0;
    float x1 = (float)vertex1.x; float y1 = (float)vertex1.y;
    float x2 = (float)vertex2.x; float y2 = (float)vertex2.y;
    float x3 = (float)vertex3.x; float y3 = (float)vertex3.y;
    float x12 = x1 - x2; float x23 = x2 - x3; float x31 = x3 - x1;
    float y12 = y1 - y2; float y23 = y2 - y3; float y31 = y3 - y1;
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

bool draw_width_incenter(Pixels img, Pixel vertex1, Pixel vertex2, Pixel vertex3, unsigned thickness) {
    // WARNING color of the width is given by the vertex1 color
    // getting projection point of incenter on each edge of the triangle
    Pixel center = incenter(vertex3, vertex2, vertex1);
    Pixel proj1 = get_projection(center, vertex1, vertex2);
    Pixel proj2 = get_projection(center, vertex2, vertex3);
    Pixel proj3 = get_projection(center, vertex1, vertex3);
    // getting point which is located on offset pixel away from projections in triangle
    Pixel inner_offset1 = get_inner_vertex(proj1, center, thickness);
    Pixel inner_offset2 = get_inner_vertex(proj2, center, thickness);
    Pixel inner_offset3 = get_inner_vertex(proj3, center, thickness);
    // getting normal vectors of each edge (perpendiculars that connect an incenter with it projections on each edge)
    Vector normal1 = {center.x - proj1.x, center.y - proj1.y};
    Vector normal2 = {center.x - proj2.x, center.y - proj2.y};
    Vector normal3 = {center.x - proj3.x, center.y - proj3.y};
    // direct vectors of the inner triangle edges (actually they are perpendicular to previous normals)
    Vector direct1 = {-normal1.y, normal1.x};
    Vector direct2 = {-normal2.y, normal2.x};
    Vector direct3 = {-normal3.y, normal3.x};
    // calculating vertices of the inner triangle (they are intercept of each edge)
    // WARNING https://www.desmos.com/calculator/2iiwgyekaf
    Pixel inner_vert1 = line_intercept(direct1, inner_offset1, direct2, inner_offset2);
    Pixel inner_vert2 = line_intercept(direct1, inner_offset1, direct3, inner_offset3);
    Pixel inner_vert3 = line_intercept(direct2, inner_offset2, direct3, inner_offset3);
    if (inner_vert1.x == -1 || inner_vert2.x == -1 || inner_vert3.x == -1) {
        // may be some situations where is not possible to draw an inner rectangle due to rounding to int
        return false;
    }
    // setting boundaries for triangle (to iterate within it)
    Rectangle rect = Boundary(vertex1, vertex3, vertex2);
    Pixel p = vertex1;
    for(int i = rect.v1.y; i <= rect.v2.y; i++) {
        for(int j = rect.v1.x; j <= rect.v2.x; j++) {
            p.x = j; p.y = i;
            if(is_in_triangle(vertex1, vertex2, vertex3, p) == true &&
               is_in_triangle(inner_vert1, inner_vert2, inner_vert3, p) == false) {
                set_pixel(img, p);
            }
        }
    }
    return true;
}

void draw_width_center_mass(Pixels img, Pixel vertex1, Pixel vertex2, Pixel vertex3, unsigned thickness) {
    // arr for storing pixels that connect center of homethety and vertices
    Pixel center = center_of_mass(vertex3, vertex2, vertex1);
    Pixel inner_vert1 = get_inner_vertex(vertex1, center, thickness);
    Pixel inner_vert2 = get_inner_vertex(vertex2, center, thickness);
    Pixel inner_vert3 = get_inner_vertex(vertex3, center, thickness);
    Rectangle rect = Boundary(vertex1, vertex3, vertex2);
    Pixel p = vertex1;
    for (int i = rect.v1.y; i <= rect.v2.y; i++) {
        for (int j = rect.v1.x; j <= rect.v2.x; j++) {
            p.x = j;
            p.y = i;
            if (is_in_triangle(vertex1, vertex2, vertex3, p) == true &&
                is_in_triangle(inner_vert1, inner_vert2, inner_vert3, p) == false) {
                set_pixel(img, p);
            }
        }
    }
}


Pixel get_inner_vertex(Pixel point1, Pixel point2, unsigned offset) {
    // gets a point on a line, which is located in offset pixels from first point
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
        point1.x = x1; point1.y = y1;
        if(count == offset) {
            return point1;
        }
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
    // WARNING filling color is set by the color of pixel p
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

void draw_outer_triangle(Pixels img, Pixel vertex1, Pixel vertex2, Pixel vertex3) {
    Bresenham(img, vertex1, vertex2);
    Bresenham(img, vertex2, vertex3);
    Bresenham(img, vertex1, vertex3);
}

void draw_triangle(Pixels img, Pixel vertex1, Pixel vertex2, Pixel vertex3, int thickness, Rgb line_color, bool fill, Rgb fill_color) {
    if(vertex1.x == vertex2.x && vertex1.x == vertex3.x || vertex1.y == vertex2.y && vertex1.y == vertex3.y) {
        fprintf(stderr, "Wrong pixels");
        return;
    }
    vertex1.color.r = line_color.r; vertex1.color.g = line_color.g; vertex1.color.b = line_color.b;
    vertex2.color.r = line_color.r; vertex2.color.g = line_color.g; vertex2.color.b = line_color.b;
    vertex3.color.r = line_color.r; vertex3.color.g = line_color.g; vertex3.color.b = line_color.b;
    if(fill == true) {
        Pixel p = {0, 0};
        p.color.r = fill_color.r;
        p.color.g = fill_color.g;
        p.color.b = fill_color.b;
        fill_triangle(img, vertex1, vertex2, vertex3, p);
    }
    if(thickness <= 0) {
        fprintf(stderr, "wrong thickness value was given");
        return;
    }
    draw_outer_triangle(img, vertex1, vertex2, vertex3);
    if(thickness != 1){
        draw_thick_edges(img, vertex1, vertex2, vertex3, line_color, thickness);
    }
}