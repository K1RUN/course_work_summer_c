cmake_minimum_required(VERSION 3.24)
project(my C)

set(CMAKE_C_STANDARD 11)

add_executable(my main.c CLI/helpmenu.c Error_handling/log.c Error_handling/error_handler.c Error_handling/error_handler.h
                Image/bmp_parser.c Image/bmp_structs.h Geometry/line_draw.c Geometry/line_draw.h
                Geometry/general.c Geometry/general.h Geometry/triangle.c Geometry/triangle.h CLI/command_parser.c
                CLI/command_parser.h Stack/stack.c Stack/stack.h Geometry/find_max_rect.c Geometry/find_max_rect.h
                Geometry/rectangle.c Image/canvas.c Image/canvas.h Image/collage.h Image/collage.c)

target_link_libraries(my m)