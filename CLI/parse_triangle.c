#include "parse_triangle.h"

void parse_triangle(int argc, char* argv[]) {
    char* opts = "a:b:c:w:e:f:n:";
    triangle_opts triangle;
    int longIndex;
    int sum = 0;
    int opt;
    bool to_fill = false; bool create_new_file = false;
    char* old_filename = NULL;
    char* new_filename = NULL;
    print_args(argc, argv);
    opterr = 0;
    struct option longOpts[] = {
            {"vertex1", required_argument, 0, 'a'},
            {"vertex2", required_argument, 0, 'b'},
            {"vertex3", required_argument, 0, 'c'},
            {"width", required_argument, 0, 'w'},
            {"color", required_argument, 0, 'e'},
            {"fill", required_argument, 0, 'f'},
            {"new_file", required_argument, 0, 'n'},
            {"file", required_argument, 0, 'o'},
            {NULL, 0, NULL, 0}
    };
    while((opt = getopt_long(argc, argv, opts, longOpts, &longIndex)) != -1) {
        switch(opt) {
            case 'a': {
                char* coords_str = copy_string(optarg);
                Pixel p;
                if(scan_coords(coords_str, &p) == false) {
                    fprintf(stderr, "Invalid option for coordinate %s\n", optarg); free(coords_str);
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
                    fprintf(stderr, "Invalid option for fill color %s\n", optarg); free(string);
                    break;
                }
                triangle.f = fill_color;
                to_fill = true; free(string);
                break;
            }
            case 'n': {
                free(new_filename);
                new_filename = copy_string(optarg);
                if(new_filename == NULL) {
                    fprintf(stderr, "Invalid option for a new file name\n");
                    // dropping sum just to avoid losing original file
                    break;
                }
                triangle.new_filename = new_filename;
                create_new_file = true;
                break;
            }
            case 'o': {
                free(old_filename);
                old_filename = copy_string(optarg);
                if(old_filename == NULL) {
                    fprintf(stderr, "Invalid option for an old file\n");
                    break;
                }
                sum |= (1 << 5);
                triangle.old_filename = old_filename; break;
            }
            case '?':
            default: {
                printf("Unknown %c flag\n", optopt);
            }
        }
    }
    // if one of the params is missing
    if(sum < REQUIRED) {
        fprintf(stderr, "Too few params\n");
        print_help();
        return;
    }
    printf("\nNEW\n");
    print_args(argc, argv);
    // filename should be last in the input sequence
    char* filename = triangle.old_filename;
    if(check_file(filename) == false) {
        return;
    }
    DIB_Header dibh = parse_dib(filename);
    Pixels img = create_canvas(dibh.image_height, dibh.image_width); canvas_draw(img, filename);
    draw_triangle(img, triangle.a, triangle.b, triangle.c, triangle.w,
                  triangle.e, to_fill, triangle.f);
    if(create_new_file == true) {
        canvas_write(img, filename, triangle.new_filename);
        free(triangle.new_filename);
    } else {
        canvas_write(img, filename, filename);
    }
    free_canvas(img);
    free(filename);
}