#include "error_handler.h"
#include "log.h"



void process_error(int error_id){
    switch(error_id){
        case FOPEN: {
            log_fatal("Cannot open the file");
            break;
        }
        case FWRITE: {
            log_fatal("Cannot write to a file");
            break;
        }
        default: {
            log_warn("Unknown error occurred");
        }
    }
}