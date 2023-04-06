cmake_minimum_required(VERSION 3.24)
project(my C)

set(CMAKE_C_STANDARD 11)

add_executable(my main.c helpmenu.c Error_handling/log.c Error_handling/error_handler.c Error_handling/error_handler.h
                BMP_parser/bmp_parser.c BMP_parser/bmp_structs.h Geometry/line_draw.c Geometry/line_draw.h
                Geometry/general.c Geometry/general.h fixed.c fixed.h)

target_link_libraries(my m)