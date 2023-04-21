#include "helpmenu.h"



const char* helpmenu =         "██████  ███    ███ ██████  ██████  \n"
                               "██   ██ ████  ████ ██   ██ ██   ██      commandline BMP processor [version -1.0]\n"
                               "██████  ██ ████ ██ ██████  ██████  \n"
                               "██   ██ ██  ██  ██ ██      ██           Usage:      bmpp [options] <file>.bmp\n"
                               "██████  ██      ██ ██      ██      \n"
                               "\n"
                                 "Options:\n"
                                 "            -h, --help                     print this guide\n"
                                 "            -i, --file_info                print BMP file information\n"
                                 "\n"
                                 "            --triangle [options]\n"
                                 "                -a, --vertex1 x,y          set the coordinates of the first vertex\n"
                                 "                -b, --vertex2 x,y          set the coordinates of the second vertex\n"
                                 "                -c, --vertex3 x,y          set the coordinates of the third vertex\n"
                                 "                -w,  --width width         set the width of the triangle (optional, set to 1 by default)\n"
                                 "                -c,  --color color         set the color of the edges in RGB format (0,0,0; 255,255,255)\n"
                                 "                -f,  --fill color          set the fill color in RGB format (0,0,0; 255,255,255) (optional)\n"
                                 "\n"
                                 "            --find_rect [options]\n"
                                 "                -m, --max color            color of the max rectangle\n"
                                 "                -f, --fill color           color to fill that rectangle\n"
                                 "\n"
                                 "            --collage [options]\n"
                                 "                -x, --number1 number       the number of the images by x-axis\n"
                                 "                -y, --number2 number       the number of the images by y-axis\n"
                                 "                -i, --images  images       the images to fill\n"
                                 "\n";

void print_help(){
    printf("%s", helpmenu);
}