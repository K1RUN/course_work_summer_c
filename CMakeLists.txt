cmake_minimum_required(VERSION 3.24)
project(my C)

set(CMAKE_C_STANDARD 11)

add_executable(my main.c helpmenu.c Testing/log.c Testing/error_handler.c BMP_parser/bmp_parser.c BMP_parser/bmp_structs.h)
