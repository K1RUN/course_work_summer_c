#include "parse_triangle.h"

bool scan_coords(char* coords, Pixel* p) {
    if(coords == NULL) {
        return false;
    }
    char* end1 = "\0"; char* end2 = "\0";
    char* part1 = strtok(coords, ",");
    char* part2 = strtok(NULL, ",");
    if(part1 != NULL && part2 != NULL) {
        int x = (int)strtol(part1, &end1, 10);
        int y = (int)strtol(part2, &end2, 10);
        // if end ptr is \0 then the whole sequence was scanned correctly
        if(*end1 == '\0' && *end2 == '\0') {
            p->x = x; p->y = y;
            return true;
        }
    }
    return false;
}

bool scan_number(char* string, int* dest) {
    if(string == NULL) {
        return false;
    }
    char* end = "\0";
    int num = (int)strtol(string, &end, 10);
    if(*end == '\0') {
        *dest = num;
        return true;
    }
    return false;
}

bool scan_RGB(char* rgb_str, Rgb* color) {
    if(rgb_str == NULL) {
        return false;
    }
    char* end1 = "\0"; char* end2 = "\0"; char* end3 = "\0";
    char* part1 = strtok(rgb_str, ",");
    char* part2 = strtok(NULL, ",");
    char* part3 = strtok(NULL, ",");
    if(part1 != NULL && part2 != NULL && part3 != NULL) {
        int R = (int)strtol(part1, &end1, 10);
        int G = (int)strtol(part2, &end2, 10);
        int B = (int)strtol(part3, &end3, 10);
        if(*end1 == '\0' && *end2 == '\0' && *end3 == '\0') {
            if(R < 0 || R > 255 && G < 0 || G > 255 && B < 0 || B > 255) {
                fprintf(stderr, "Warning: one of the color numbers is bigger than 1 byte\n");
            }
            color->r = (unsigned char)R; color->g = (unsigned char)G; color->b = (unsigned char)B;
            return true;
        }
        return false;
    }
}

void parse_triangle(int argc, char* argv[]) {
    char* opts = "a:b:c:w:e:f:n:";
    triangle_opts triangle;
    int longIndex;
    int sum = 0;
    int opt;
    bool to_fill = false; bool create_new_file = false;
    struct option longOpts[] = {
            {"vertex1", required_argument, 0, 'a'},
            {"vertex2", required_argument, 0, 'b'},
            {"vertex3", required_argument, 0, 'c'},
            {"width", required_argument, 0, 'w'},
            {"color", required_argument, 0, 'e'},
            {"fill", required_argument, 0, 'f'},
            {"new_file", required_argument, 0, 'n'},
            {NULL, 0, NULL, 0}
    };
    while((opt = getopt_long(argc, argv, opts, longOpts, &longIndex)) != -1) {
        switch(opt) {
            case 'a': {
                char* coords_str = copy_string(optarg);
                Pixel p;
                if(scan_coords(coords_str, &p) == false) {
                    fprintf(stderr, "Invalid option for coordinate %s\n", optarg); free(coords_str);
                    sum = 0;
                    return;
                }
                triangle.a = p;
                sum |= 1; free(coords_str);
                break;
            }
            case 'b': {
                char* coords_str = copy_string(optarg);
                Pixel p;
                if(scan_coords(coords_str, &p) == false) {
                    fprintf(stderr, "Invalid option for coordinate %s\n", optarg); free(coords_str);
                    return;
                }
                triangle.b = p;
                sum |= (1 << 1); free(coords_str);
                break;
            }
            case 'c': {
                char* coords_str = copy_string(optarg);
                Pixel p;
                if(scan_coords(coords_str, &p) == false) {
                    fprintf(stderr, "Invalid option for coordinate %s\n", optarg); free(coords_str);
                    return;
                }
                triangle.c = p;
                sum |= (1 << 2); free(coords_str);
                break;
            }
            case 'w': {
                char* string = copy_string(optarg); int width;
                if(scan_number(string, &width) == false) {
                    fprintf(stderr, "Invalid option for width %s\n", optarg); free(string);
                    return;
                }
                triangle.w = width;
                sum |= (1 << 3); free(string);
                break;
            }
            case 'e': {
                char* string = copy_string(optarg); Rgb edge_color;
                if(scan_RGB(string, &edge_color) == false) {
                    fprintf(stderr, "Invalid option for edge color %s\n", optarg); free(string);
                    return;
                }
                triangle.e = edge_color;
                sum |= (1 << 4); free(string);
                break;
            }
            case 'f': {
                char* string = copy_string(optarg); Rgb fill_color;
                if(scan_RGB(string, &fill_color) == false) {
                    fprintf(stderr, "Invalid option for fill color %s\n", optarg); free(optarg);
                    break;
                }
                triangle.f = fill_color;
                to_fill = true; free(string);
                break;
            }
            case 'n': {
                char* filename = copy_string(optarg);
                if(filename == NULL) {
                    fprintf(stderr, "Invalid option for new file\n");
                    // dropping sum just to avoid losing original file
                    break;
                }
                triangle.new_filename = filename;
                create_new_file = true;
                break;
            }
            case '?':
            default: {
                printf("Unknown %c\n", optopt);
            }
        }
    }
    // if one of the params is missing
    if(sum < REQUIRED) {
        fprintf(stderr, "Too few params\n");
        print_help();
        return;
    }
    // filename should be last in the input sequence
    char* filename = copy_string(*(argv + argc - 1));
    if(open_bmp(filename, "rb") == false) {
        return;
    }
    DIB_Header dibh = parse_dib(filename);
    Pixels img = create_canvas(dibh.image_width, dibh.image_height); canvas_draw(img, filename);
    draw_triangle(img, triangle.a, triangle.b, triangle.c, triangle.w,
                  triangle.e, to_fill, triangle.f);
    if(create_new_file == true) {
        canvas_write(img, filename, triangle.new_filename);
    } else {
        canvas_write(img, filename, filename);
    }
}
