HEADERS=../src/vector.h ../src/surface.h ../src/color.h ../src/scene.h ../src/input_file.h

TARGETS=test_ray_trace
#-ansi -D_ISOC99_SOURCE
all: ${TARGETS}

%.o: %.c ${HEADERS}
	gcc -lm -g -Wall -I../src ${CFLAGS} -c $< -o $@

test_ray_trace: ../src/ray_trace.o ../src/color.o ../src/surface.o ../src/input_file.o test_ray_trace.o
	gcc $^ -lm -o $@

clean:
	rm -f ${TARGETS} *.o
