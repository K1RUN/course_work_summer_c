#include "find_max_rect.h"

bool color_eq(Rgb color1, Rgb color2) {
    return color1.r == color2.r && color1.g == color2.g && color1.b == color2.b;
}

void print_matrix(Sub_matrix matrix) {
    if(matrix.sub_matrix == NULL) return;
    for(int i = 0; i < matrix.h; i++){
        for(int j = 0; j < matrix.w; j++) {
            printf("%2d ", matrix.sub_matrix[i][j]);
        }
        printf("\n");
    }
}

Sub_matrix get_color_matrix(Pixels img, Rgb color) {
    // creates a matrix containing only 1's and 0's from an image
    Sub_matrix sub_matrix = {NULL, 0, 0};
    if(create_matrix(&sub_matrix, img.h, img.w) == false) {
        fprintf(stderr, "Error while creating a matrix");
        return sub_matrix;
    } else {
        sub_matrix.w = img.w; sub_matrix.h = img.h;
    }
    if(img.matrix == NULL) {
        fprintf(stderr, "An empty image was given");
        return sub_matrix;
    }
    for(int i = 0; i < img.h; i++) {
        for(int j = 0; j < img.w; j++) {
            if(color_eq(img.matrix[i][j], color) == true) {
                sub_matrix.sub_matrix[i][j] = 1;
            } else {
                sub_matrix.sub_matrix[i][j] = 0;
            }
        }
    }
    return sub_matrix;
}

void destroy_matrix(Sub_matrix *matrix) {
    for(int i = 0; i < matrix->h; i++) {
        free(matrix->sub_matrix[i]);
    }
    free(matrix->sub_matrix);
}

bool create_matrix(Sub_matrix* matrix, size_t h, size_t w) {
    if(matrix == NULL) return false;
    (matrix->sub_matrix) = malloc(sizeof(int*) * h);
    for(int i = 0; i < h; i++) {
        // extra 1 column for zeros in the right border of the matrix
        (matrix->sub_matrix)[i] = calloc(w + 1, sizeof(int));
    }
    return true;
}

bool make_histogram(Sub_matrix* subMatrix) {
    // returns if a matrix has a necessary color
    // takes the matrix of 1's and 0's and makes histogram of it
    bool has_color = false;
    Sub_matrix histogram;
    histogram.w = subMatrix->w; histogram.h = subMatrix->h;
    if(create_matrix(&histogram, subMatrix->h, subMatrix->w) == false){
        fprintf(stderr, "Error while allocating memory for sub matrix");
        return has_color;
    }
    // copying the first row of the subMatrix to a histogram
    memcpy(histogram.sub_matrix[0], (subMatrix->sub_matrix)[0], subMatrix->w * sizeof(int));
    int** ones_matrix = subMatrix->sub_matrix;
    for(int i = 1; i < subMatrix->h; i++) {
        for(int j = 0; j < subMatrix->w; j++) {
            if (ones_matrix[i - 1][j] == 1) {
                has_color = true;
                if (ones_matrix[i][j] != 0) { //zeros always stay the same
                    histogram.sub_matrix[i][j] = ones_matrix[i][j] + histogram.sub_matrix[i - 1][j];
                }
            } else {
                histogram.sub_matrix[i][j] = ones_matrix[i][j];
            }
        }
    }
    destroy_matrix(subMatrix);
    subMatrix->sub_matrix = histogram.sub_matrix;
    return has_color;
}

Rectangle find_largest_rect(Sub_matrix histogram) {
    // main algorithm
    Coords position = {0, 0};
    long max_area = -1;
    int height_max_area = -1;
    int x_end = 0;
    int i;
    for(i = 0; i < histogram.h; i++) {
        int j;
        Stack* pos = create_stack(10);
        Stack* heights = create_stack(10);
        for(j = 0; j < histogram.w; j++) {
            int h = histogram.sub_matrix[i][j];
            int last_h;
            if(peek(heights, &last_h) == false) {
                last_h = 0;
            }
            if(is_empty(pos) == true || h > last_h){
                push(pos, j);
                push(heights, h);
            } else if(h < last_h) {
                int pos_tmp = -1;
                while(is_empty(heights) == false && h < last_h) {
                    int tmp_h; pop(heights, &tmp_h);
                    pop(pos, &pos_tmp);
                    long area_tmp = tmp_h * (j - pos_tmp);
                    if(area_tmp > max_area) {
                        max_area = area_tmp;
                        position.x = pos_tmp; position.y = i;
                        height_max_area = tmp_h;
                        x_end = j;
                    }
                    if(peek(heights, &last_h) == false) {
                        last_h = -1;
                    }
                }
                push(heights, h);
                if(pos_tmp != -1) {
                    push(pos, pos_tmp);
                }
            }
        }
        while(is_empty(heights) == false) {
            int tmp_h; pop(heights, &tmp_h);
            int pos_tmp; pop(pos, &pos_tmp);
            long area_tmp = tmp_h * (j - pos_tmp);
            if(area_tmp > max_area) {
                max_area = area_tmp;
                position.x = pos_tmp; position.y = i;
                height_max_area = tmp_h;
                x_end = j;
            }
        }
        destroy_stack(heights);
        destroy_stack(pos);
    }
    Pixel v1 = {position.x, position.y - height_max_area + 1, {0, 0, 0}};
    Pixel v2 = {x_end - 1, position.y, {0, 0, 0}};
    Rectangle max_rect = {v1, v2};
    return max_rect;
}

void find_and_recolor(Pixels img, Rgb old_color, Rgb new_color) {
    Sub_matrix ones_matrix = get_color_matrix(img, old_color);
    if(make_histogram(&ones_matrix) == false) {
        printf("There is no rectangle of the given color\n");
        destroy_matrix(&ones_matrix);
        return;
    }
    Rectangle rect_coordinates = find_largest_rect(ones_matrix);
    fill_rect(img, rect_coordinates, new_color);
    destroy_matrix(&ones_matrix);
}