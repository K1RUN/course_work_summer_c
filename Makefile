COMPILER=gcc
CFLAGS=-c

all: build clean

build: stack.o general.o bmp_parser.o canvas.o collage.o find_max_rect.o line_draw.o rectangle.o triangle.o \
	commands.o helpmenu.o parse_collage.o parse_find_rect.o parse_triangle.o command_parser.o parse_fill.o main.o
	$(COMPILER) stack.o general.o bmp_parser.o canvas.o collage.o find_max_rect.o line_draw.o rectangle.o triangle.o \
    commands.o helpmenu.o parse_collage.o parse_find_rect.o parse_triangle.o command_parser.o parse_fill.o main.o -o bmpp -lm
stack.o: Stack/stack.c Stack/stack.h
	$(COMPILER) $(CFLAGS) Stack/stack.c
#Image
general.o: Geometry/general.c Geometry/general.h Image/bmp_structs.h
	$(COMPILER) $(CFLAGS) Geometry/general.c
bmp_parser.o: Image/bmp_parser.c Image/bmp_parser.h
	$(COMPILER) $(CFLAGS) Image/bmp_parser.c
canvas.o: Image/canvas.c Image/canvas.h Image/bmp_structs.h Geometry/general.h
	$(COMPILER) $(CFLAGS) Image/canvas.c
collage.o: Image/collage.c Image/collage.h Image/canvas.h Image/bmp_structs.h
	$(COMPILER) $(CFLAGS) Image/collage.c
#Geometry
find_max_rect.o: Geometry/find_max_rect.c Geometry/find_max_rect.h Geometry/rectangle.h Geometry/general.h \
	Image/bmp_structs.h Stack/stack.h
	$(COMPILER) $(CFLAGS) Geometry/find_max_rect.c
line_draw.o: Geometry/line_draw.c Geometry/line_draw.h Geometry/general.h Image/bmp_structs.h
	$(COMPILER) $(CFLAGS) Geometry/line_draw.c
rectangle.o: Geometry/rectangle.c Geometry/rectangle.h Geometry/general.h Geometry/line_draw.h Image/bmp_structs.h
	$(COMPILER) $(CFLAGS) Geometry/rectangle.c
triangle.o: Geometry/triangle.c Geometry/triangle.h Geometry/general.h Geometry/line_draw.h Geometry/rectangle.h \
	Image/bmp_structs.h
	$(COMPILER) $(CFLAGS) Geometry/triangle.c
#CLI
commands.o: CLI/commands.c CLI/commands.h Image/bmp_structs.h
	$(COMPILER) $(CFLAGS) CLI/commands.c
helpmenu.o: CLI/helpmenu.c CLI/helpmenu.h
	$(COMPILER) $(CFLAGS) CLI/helpmenu.c
parse_collage.o: CLI/parse_collage.c CLI/parse_collage.h CLI/parse_fill.h CLI/commands.h CLI/helpmenu.h Image/collage.h Image/canvas.h
	$(COMPILER) $(CFLAGS) CLI/parse_collage.c
parse_find_rect.o: CLI/parse_find_rect.c CLI/parse_find_rect.h CLI/commands.h CLI/helpmenu.h Image/canvas.h \
				Geometry/find_max_rect.h
	$(COMPILER) $(CFLAGS) CLI/parse_find_rect.c
parse_triangle.o: CLI/parse_triangle.c CLI/parse_triangle.h CLI/helpmenu.h CLI/commands.h Geometry/general.h \
				Geometry/triangle.h Image/canvas.h Image/bmp_structs.h
	$(COMPILER) $(CFLAGS) CLI/parse_triangle.c
command_parser.o: CLI/command_parser.c CLI/command_parser.h CLI/parse_triangle.h CLI/parse_find_rect.h \
				CLI/parse_collage.h CLI/commands.h CLI/helpmenu.h Image/bmp_parser.h
	$(COMPILER) $(CFLAGS) CLI/command_parser.c
parse_fill.o: CLI/parse_fill.c CLI/parse_fill.h CLI/commands.h CLI/helpmenu.h Image/canvas.h Image/collage.h \
				Image/bmp_structs.h
	$(COMPILER) $(CFLAGS) CLI/parse_fill.c
main.o: main.c CLI/command_parser.h
	$(COMPILER) $(CFLAGS) main.c
clean: build
	rm -rf *.o
