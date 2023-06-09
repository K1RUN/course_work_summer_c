#include "command_parser.h"

int parse_commands(int argc, char* argv[]) {
    printf(ANSI_COLOR_GREEN);
    opterr = 0;
    int command_flag = UNKNOWN;
    char* opts = "hi:";
    struct option longOpts[] = {
            {"help", no_argument, &command_flag, HELP},
            {"info", required_argument, &command_flag, INFO},
            {"triangle", no_argument, &command_flag, TRIANGLE},
            {"find_rect", no_argument, &command_flag, FIND_RECT},
            {"collage", no_argument, &command_flag, COLLAGE},
            {"fill_outer", no_argument, &command_flag, FILL},
            {NULL, 0, NULL, 0}
    };
    int long_index;
    int opt = getopt_long(argc, argv, opts, longOpts, &long_index);
    if(opt != 0) {
        switch (opt) {
            case 'i': {
                print_info(optarg);
                break;
            }
            case 'h':
            default: {
                print_help();
            }
        }
    } else {
        switch(command_flag) {
            case HELP: {
                print_help();
                break;
            }
            case INFO: {
                print_info(optarg);
                break;
            }
            case TRIANGLE: {
                parse_triangle(argc, argv);
                break;
            }
            case FIND_RECT: {
                parse_find_rect(argc, argv);
                break;
            }
            case COLLAGE: {
                parse_collage(argc, argv);
                break;
            }
            case FILL: {
                parse_fill(argc, argv);
                break;
            }
            default: print_help();
        }
    }
    printf(ANSI_COLOR_RESET);
    return long_index;
}