#include "error_handler.h"

void process_error(int error_id){
    switch(error_id){
        case FOPEN_ERR: {
            log_fatal("Cannot open the file");
            break;
        }
        case FWRITE_ERR: {
            log_fatal("Cannot write to a file");
            break;
        }
        case FREAD_ERR: {
            log_fatal("Cannot read from the file");
            break;
        }
        case BMPH_WRN: {
            log_warn("Something wrong with reading a bmp header");
        }
        default: {
            log_warn("Unknown error occurred");
        }
    }
}