OBJECTS=vector.o surface.o color.o input_file.o output_file.o ray_trace.o main.o
OBJECTS_RANDOM=vector.o surface.o color.o input_file.o output_file.o ray_trace.o random_main.o
HEADERS=vector.h surface.h color.h input_file.h output_file.h ray_trace.h scene.h

TARGET=../bin/ray_trace ../bin/random_ray_trace
#-ansi -D_ISOC99_SOURCE
all: ${TARGET}

%.o: %.c ${HEADERS}
	gcc -g -Wall ${CFLAGS} -c $< -o $@

../bin/ray_trace: ${OBJECTS}
	gcc ${OBJECTS} -lm -o $@

../bin/random_ray_trace: ${OBJECTS_RANDOM}
	gcc ${OBJECTS_RANDOM} -lm -o $@

clean:
	rm -f ${TARGET} ${OBJECTS}
