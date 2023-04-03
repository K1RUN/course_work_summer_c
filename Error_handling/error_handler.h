#ifndef MY_ERROR_HANDLER_H
#define MY_ERROR_HANDLER_H
#include "log.h"

enum Errors {FOPEN_ERR = 1, FWRITE_ERR, FREAD_ERR, BMPH_WRN, DIBH_WRN};

void process_error(int);
#endif //MY_ERROR_HANDLER_H
