#include "command_parser.h"

int parse_commands(int argc, char* argv[]) {
    opterr = 0;
    int command_flag = UNKNOWN;
    char* opts = "hi:";
    struct option longOpts[] = {
            {"help", no_argument, &command_flag, HELP},
            {"file_info", required_argument, &command_flag, FILE_INFO},
            {"triangle", no_argument, &command_flag, TRIANGLE},
            {"find_rect", no_argument, &command_flag, FIND_RECT},
            {"collage", no_argument, &command_flag, COLLAGE},
            {NULL, 0, NULL, 0}
    };
    int long_index;
    int opt = getopt_long(argc, argv, opts, longOpts, &long_index);
    if(opt != 0) {
        switch (opt) {
            case 'i': {
                printf("FILE_INFO");
                printf("%s", optarg);
                // TODO: parse file_info function;
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
                print_help(); break;
            }
            case FILE_INFO: {
                printf("FILE_INFO\n");
                printf("%s", optarg);
                break;
            }
            case TRIANGLE: {
                printf("TRIANGLE");
                // TODO: parse triangle function
                break;
            }
            case FIND_RECT: {
                printf("FIND_RECT");
                // TODO: parse find_rect function
                break;
            }
            case COLLAGE: {
                printf("COLLAGE");
                // TODO: parse collage function
                break;
            }
            case UNKNOWN:
            default: {
                printf("????");
                break;
            }
        }
    }
    return long_index;
}