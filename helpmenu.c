#include "helpmenu.h"
#include <stdio.h>

const char* helpmenu = "bmpp        commandline BMP processor [version 0.0]\n"
                                 "\n"
                                 "Usage:      bmpp [options] <file>.bmp\n"
                                 "\n"
                                 "Options:\n"
                                 "            -h, --help                  print this guide\n"
                                 "\n"
                                 "            --triangle [options]\n"
                                 "                -v1, --vertex1 x,y      set the coordinates of the first vertex\n"
                                 "                -v2, --vertex2 x,y      set the coordinates of the second vertex\n"
                                 "                -v3, --vertex3 x,y      set the coordinates of the third vertex\n"
                                 "                -w,  --width width      set the width of the triangle (optional, set to 1 by default)\n"
                                 "                -c,  --color color      set the color of the edges in hex format (#000000, #FFFFFF)\n"
                                 "                -f,  --fill color       set the fill color in hex format (#000000, #FFFFFF) (optional)\n"
                                 "\n"
                                 "            --find_rect [options]\n"
                                 "                -c1, --color1 color     color of the max rectangle\n"
                                 "                -c2, --color2 color     color to fill that rectangle\n"
                                 "\n"
                                 "            --collage [options]\n"
                                 "                -x, --number1 number    the number of the images by x-axis\n"
                                 "                -y, --number2 number    the number of the images by y-axis\n"
                                 "                -i, --images  images    the images to fill\n";

void print_help(){
    printf("%s", helpmenu);
}