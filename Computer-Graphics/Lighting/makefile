# Example 10
EXE=hw5

# Main target
all: $(EXE)

#  Msys/MinGW
ifeq "$(OS)" "Windows_NT"
CFLG=-O3 -Wall -DUSEGLEW
LIBS=-lfreeglut -lglew32 -lglu32 -lopengl32 -lm
CLEAN=rm -f *.exe *.o *.a
else
#  OSX
ifeq "$(shell uname)" "Darwin"
RES=$(shell uname -r|sed -E 's/(.).*/\1/'|tr 12 21)
CFLG=-O3 -Wall -Wno-deprecated-declarations -DRES=$(RES)
LIBS=-framework GLUT -framework OpenGL
#  Linux/Unix/Solaris
else
CFLG=-O3 -Wall
LIBS=-lglut -lGLU -lGL -lm
endif
#  OSX/Linux/Unix/Solaris
CLEAN=rm -f $(EXE) *.o *.a
endif

# Dependencies
hw5.o: hw5.cpp shape.h camera.h cone.h cube.h cylinder.h outpost.h pointcloud.h pyramid.h sphere.h
shape.o: shape.cpp shape.h
camera.o: shape.cpp shape.h camera.cpp camera.h
cone.o: shape.cpp shape.h cone.cpp cone.h
cube.o: shape.cpp shape.h cube.cpp cube.h
cylinder.o: shape.cpp shape.h cylinder.cpp cylinder.h
outpost.o: shape.cpp shape.h outpost.cpp outpost.h
pointcloud.o: shape.cpp shape.h pointcloud.cpp pointcloud.h
pyramid.o: shape.cpp shape.h pyramid.cpp pyramid.h
sphere.o: shape.cpp shape.h sphere.cpp sphere.h



#  Create archive
dep.a: shape.o camera.o cone.o cube.o cylinder.o outpost.o pointcloud.o pyramid.o sphere.o
	ar -rcs $@ $^

# Compile rules
.c.o:
	gcc -c $(CFLG)  $<
.cpp.o:
	g++ -c $(CFLG)  $<

#  Link
hw5:hw5.o   dep.a
	g++ $(CFLG) -o $@ $^  $(LIBS)

#  Clean
clean:
	$(CLEAN)
