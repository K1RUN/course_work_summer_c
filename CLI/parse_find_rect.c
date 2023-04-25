#include "parse_find_rect.h"

void parse_find_rect(int argc, char* argv[]) {
    char* opts = "m:f:n:";
    find_rect findRect;
    bool create_new_file = false;
    int longIndex;
    int sum = 0;
    int opt;
    char* old_filename = NULL; char* new_filename = NULL;
    print_args(argc, argv);
    opterr = 0;
    struct option longOpts[] = {
            {"max", required_argument, 0, 'm'},
            {"fill", required_argument, 0, 'f'},
            {"new_file", required_argument, 0, 'n'},
            {"file", required_argument, 0, 'o'},
            {NULL, 0, NULL, 0}
    };
    while((opt = getopt_long(argc, argv, opts, longOpts, &longIndex)) != -1) {
        switch(opt) {
            case 'm': {
                char* string = copy_string(optarg); Rgb max_rect_color;
                if(scan_RGB(string, &max_rect_color) == false) {
                    fprintf(stderr, "Invalid option for max rectangle color %s\n", optarg);
                    free(string);
                    return;
                }
                free(string);
                findRect.max_rect_color = max_rect_color; sum |= 1;
                break;
            }
            case 'f': {
                char* string = copy_string(optarg); Rgb fill_color;
                if(scan_RGB(string, &fill_color) == false) {
                    fprintf(stderr, "Invalid option for filling color %s\n", optarg);
                    free(string);
                    return;
                }
                free(string);
                sum |= (1 << 1);
                findRect.fill_rect_color = fill_color; break;
            }
            case 'n': {
                free(new_filename);
                new_filename = copy_string(optarg);
                if(new_filename == NULL) {
                    fprintf(stderr, "Invalid option for a new file name\n");
                    return;
                }
                findRect.new_filename = new_filename;
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
                sum |= (1 << 2);
                findRect.old_filename = old_filename; break;
            }
            case '?':
            default: {
                printf("Unknown flag\n");
            }
        }
    }
    if(sum < REQUIRED_RECTANGLE) {
        fprintf(stderr, "Too few params\n");
        print_help();
        free(new_filename);
        free(old_filename);
        return;
    }
    printf("\nNEW\n");
    print_args(argc, argv);
    char* filename = findRect.old_filename;
    if(check_file(filename) == false) {
        free(new_filename);
        free(old_filename);
        return;
    }
    DIB_Header dibh = parse_dib(filename);
    Pixels img = create_canvas(dibh.image_height, dibh.image_width);
    canvas_draw(img, filename);
    find_and_recolor(img, findRect.max_rect_color, findRect.fill_rect_color);
    if(create_new_file == true) {
        canvas_write(img, filename, findRect.new_filename);
        free(findRect.new_filename);
    } else {
        canvas_write(img, filename, filename);
    }
    free_canvas(img);
    free(filename);
}