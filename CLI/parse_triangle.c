#include "parse_triangle.h"

bool scan_coords(char* coords, Coords* p) {
    if(coords == NULL) {
        return false;
    }
    char* end1; char* end2;
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

void parse_triangle(int argc, char* argv[]) {
    char* opts = "a:b:c:w:c:f:";
    triangle_opts triangle;
    int longIndex;
    int command_flag;
    int sum;
    int opt;
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
                Coords p;
                if(scan_coords(coords_str, &p) == false) {
                    fprintf(stderr, "Invalid option for coordinate %s", optarg);
                    return;
                }
                triangle.a = p;
                break;
            }
        }
    }
}
