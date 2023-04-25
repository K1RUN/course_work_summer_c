#include "parse_collage.h"

void parse_collage(int argc, char* argv[]) {
    char* opts = "x:y:n:";
    collage collage_opts;
    bool create_new_file = false;
    int longIndex;
    int sum = 0;
    int opt;
    char* old_filename = NULL; char* new_filename = NULL;
    print_args(argc, argv);
    opterr = 0;
    struct option longOpts[] = {
            {"x_num", required_argument, 0, 'x'},
            {"y_num", required_argument, 0, 'y'},
            {"new_file", required_argument, 0, 'n'},
            {"file", required_argument, 0, 'o'},
            {NULL, 0, NULL, 0}
    };
    while((opt = getopt_long(argc, argv, opts, longOpts, &longIndex)) != -1) {
        switch(opt) {
            case 'x': {
                char* string = copy_string(optarg); int x_num;
                if(scan_number(string, &x_num) == false) {
                    fprintf(stderr, "Invalid option for x number %s\n", optarg);
                    free(string);
                    return;
                }
                free(string);
                collage_opts.x_num = x_num; sum |= 1;
                break;
            }
            case 'y': {
                char* string = copy_string(optarg); int y_num;
                if(scan_number(string, &y_num) == false) {
                    fprintf(stderr, "Invalid option for y number %s\n", optarg);
                    free(string);
                    return;
                }
                free(string);
                collage_opts.y_num = y_num; sum |= (1 << 1);
                break;
            }
            case 'n': {
                free(new_filename);
                new_filename = copy_string(optarg);
                if(new_filename == NULL) {
                    fprintf(stderr, "Invalid option for a new file name\n");
                    return;
                }
                collage_opts.new_filename = new_filename;
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
                collage_opts.old_filename = old_filename; break;
            }
            case '?':
            default: {
                printf("Unknown flag\n");
            }
        }
    }
    if(sum < REQUIRED_COLLAGE) {
        fprintf(stderr, "Too few params\n");
        print_help();
        free(new_filename);
        free(old_filename);
        return;
    }
    printf("\nNEW\n");
    print_args(argc, argv);
    char* filename = collage_opts.old_filename;
    if(check_file(filename) == false) {
        free(new_filename);
        free(old_filename);
        return;
    }
    DIB_Header dibh = parse_dib(filename);
    Pixels img = create_canvas(dibh.image_height, dibh.image_width);
    canvas_draw(img, filename);
    create_collage(&img, collage_opts.y_num, collage_opts.x_num);
    if(create_new_file == true) {
        canvas_write(img, filename, collage_opts.new_filename);
        free(collage_opts.new_filename);
    } else {
        canvas_write(img, filename, filename);
    }
    free_canvas(img);
    free(filename);
}