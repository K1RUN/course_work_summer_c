#ifndef MY_ERROR_HANDLER_H
#define MY_ERROR_HANDLER_H

enum Errors{FOPEN = 1, FWRITE};

void process_error(int);
#endif //MY_ERROR_HANDLER_H
