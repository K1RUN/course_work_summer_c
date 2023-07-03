#include "parse_fill.h"

void parse_fill(int argc, char* argv[]) {
    char* opts = "x:w:h:c:n:";
    fill_opts fill_opts;
    bool create_new_file = false;
    int longIndex;
    int sum = 0;
    int opt;
    char* old_filename = NULL; char* new_filename = NULL;
    opterr = 0;
    struct option longOpts[] = {
            {"coords", required_argument, 0, 'x'},
            {"width", required_argument, 0, 'w'},
            {"height", required_argument, 0, 'h'},
            {"color", required_argument, 0, 'c'},
            {"new", required_argument, 0, 'n'},
            {"file", required_argument, 0, 'f'},
            {NULL, 0, NULL, 0}
    };
    while((opt = getopt_long(argc, argv, opts, longOpts, &longIndex)) != -1) {
        switch(opt) {
            case 'x': {
                char* string = copy_string(optarg); Pixel x;
                if(scan_coords(string, &x) == false) {
                    fprintf(stderr, "Invalid option for start coordinate %s\n", optarg);
                    free(string);
                    return;
                }
                free(string);
                fill_opts.x = x; sum |= 1;
                break;
            }
            case 'w': {
                char* string = copy_string(optarg); int w;
                if(scan_number(string, &w) == false) {
                    fprintf(stderr, "Invalid option for width %s\n", optarg);
                    free(string);
                    return;
                }
                free(string);
                fill_opts.w = w; sum |= (1 << 1);
                break;
            }
            case 'h': {
                char* string = copy_string(optarg); int h;
                if(scan_number(string, &h) == false) {
                    fprintf(stderr, "Invalid option for height %s\n", optarg);
                    free(string);
                    return;
                }
                free(string);
                fill_opts.h = h; sum |= (1 << 2);
                break;
            }
            case 'c': {
                char* string = copy_string(optarg); Rgb color;
                if(scan_RGB(string, &color) == false) {
                    fprintf(stderr, "Invalid option for color\n");
                    free(string);
                    return;
                }
                free(string);
                fill_opts.color = color; sum |= (1 << 3);
                break;
            }
            case 'n': {
                free(new_filename);
                new_filename = copy_string(optarg);
                if(new_filename == NULL) {
                    fprintf(stderr, "Invalid option for a new file name\n");
                    free(old_filename);
                    return;
                }
                fill_opts.new_filename = new_filename;
                create_new_file = true;
                break;
            }
            case 'f': {
                free(old_filename);
                old_filename = copy_string(optarg);
                if(old_filename == NULL) {
                    fprintf(stderr, "Invalid option for an old file\n");
                    break;
                }
                sum |= (1 << 4);
                fill_opts.old_filename = old_filename; break;
            }
            case '?':
            default: {
                printf("Unknown flag\n");
            }
        }
    }
    if(sum < REQUIRED_FILL) {
        fprintf(stderr, "Too few params\n");
        print_help();
        free(new_filename);
        free(old_filename);
        return;
    }
    char* filename = fill_opts.old_filename;
    if(check_file(filename) == false) {
        free(new_filename);
        free(old_filename);
        return;
    }
    DIB_Header dibh = parse_dib(filename);
    Pixels img = create_canvas(dibh.image_height, dibh.image_width);
    canvas_draw(img, filename);
    canvas_fill(img, fill_opts.x, fill_opts.w, fill_opts.h, fill_opts.color);
    if(create_new_file == true) {
        canvas_write(img, filename, fill_opts.new_filename);
        free(fill_opts.new_filename);
    } else {
        canvas_write(img, filename, filename);
    }
    free_canvas(img);
    free(filename);
}