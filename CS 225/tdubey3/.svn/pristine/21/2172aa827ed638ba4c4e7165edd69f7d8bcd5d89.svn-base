COMPILER = clang++
COMPILER_FLAGS = -c -g -std=c++11 -Wall -stdlib=libc++ 
LINKER = clang++

mp1 : main.o png.o rgbapixel.o
		$(LINKER) main.o png.o rgbapixel.o -lpng -std=c++ly -stdlib=libc++ -lc++abi -o mp1
main.o : main.cpp png.h rgbapixel.h
		$(COMPILER) $(COMPILER_FLAGS) main.cpp
png.o : png.h
		$(COMPILER) $(COMPILER_FLAGS) png.cpp
rgbapixel.o : rgbapixel.h png.h
		$(COMPILER) $(COMPILER_FLAGS) rgbapixel.cpp
clean: 
		rm -f *.o
