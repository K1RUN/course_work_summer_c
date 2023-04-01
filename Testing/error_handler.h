#ifndef MY_ERROR_HANDLER_H
#define MY_ERROR_HANDLER_H

enum Errors{FOPEN_ERR = 1, FWRITE_ERR, FREAD_ERR};

void process_error(int);
#endif //MY_ERROR_HANDLER_H
