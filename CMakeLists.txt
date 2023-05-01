cmake_minimum_required(VERSION 3.24)
project(bmpp C)

set(CMAKE_C_STANDARD 11)

add_executable(bmpp main.c CLI/helpmenu.c Image/bmp_parser.c Image/bmp_structs.h Geometry/line_draw.c Geometry/line_draw.h
                Geometry/general.c Geometry/general.h Geometry/triangle.c Geometry/triangle.h CLI/command_parser.c
                CLI/command_parser.h Stack/stack.c Stack/stack.h Geometry/find_max_rect.c Geometry/find_max_rect.h
                Geometry/rectangle.c Image/canvas.c Image/canvas.h Image/collage.h Image/collage.c CLI/commands.h
                CLI/parse_triangle.h CLI/parse_triangle.c CLI/commands.c CLI/parse_find_rect.h CLI/parse_find_rect.c
                CLI/parse_collage.h CLI/parse_collage.c)

target_link_libraries(bmpp m)