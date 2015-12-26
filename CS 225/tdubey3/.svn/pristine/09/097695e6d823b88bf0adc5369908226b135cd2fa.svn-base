EXENAME = mp2
OBJS = main.o png.o image.o rgbapixel.o
EXETEST = testimage
OBJTEST = testimage.o png.o image.o rgbapixel.o
EXETESTS = testscene
OBJTESTS = testscene.o png.o image.o rgbapixel.o scene.o

CXX = clang++
CXXFLAGS = -std=c++1y -stdlib=libc++ -c -g -O0 -Wall -Wextra -pedantic 
LD = clang++
LDFLAGS = -std=c++1y -stdlib=libc++ -lpng -g -lc++abi

all : $(EXENAME)

$(EXENAME) : $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS) -o $(EXENAME)

testscene : $(OBJTESTS)
	$(LD) $(OBJTESTS) $(LDFLAGS) -o $(EXETESTS)

testscene.o : testscene.cpp image.h png.h rgbapixel.h scene.h
	$(CXX) $(CXXFLAGS) testscene.cpp

testimage : $(OBJTEST)
	$(LD) $(OBJTEST) $(LDFLAGS) -o $(EXETEST)

testimage.o : testimage.cpp image.h png.h rgbapixel.h
	$(CXX) $(CXXFLAGS) testimage.cpp

main.o : main.cpp image.h png.h rgbapixel.h
	$(CXX) $(CXXFLAGS) main.cpp

png.o : png.cpp png.h rgbapixel.h
	$(CXX) $(CXXFLAGS) png.cpp

scene.o : scene.cpp scene.h image.o
	$(CXX) $(CXXFLAGS) scene.cpp

image.o : image.cpp image.h png.o
	$(CXX) $(CXXFLAGS) image.cpp

rgbapixel.o : rgbapixel.cpp rgbapixel.h
	$(CXX) $(CXXFLAGS) rgbapixel.cpp

compareimage:
	diff inverted.png soln_inverted.png && diff flipped.png soln_flipped.png && diff brightened.png soln_brightened.png

comparescene:
	diff scene.png soln_scene.png && diff scene2.png soln_scene2.png && diff scene3.png soln_scene3.png && diff scene4.png soln_scene4.png && diff scene5.png soln_scene5.png && diff scene6.png soln_scene6.png && diff scene7.png soln_scene7.png && diff scene8.png soln_scene8.png

clean :
	-rm -f *.o $(EXENAME) $(EXETEST)
