CXXFLAGS := -std=c++11 -g
LIBS := -lm -lGL -lGLU -lglut
HEADERS := Vector.h Camera.h Mesh.h SpatialObject.h Scenary.h Snake.h
OBJS := Snake3D.o Vector.o Camera.o Mesh.o SpatialObject.o Scenary.o Snake.o

all: Snake3D

Snake3D: $(OBJS) $(HEADERS)
	g++ $(CXXFLAGS) $(OBJS) -o $@ $(LIBS)

%.o: %.cxx
	g++ $(CXXFLAGS) -c $< -o $@

.PHONY: clean

clean:
	rm -r *.o Snake3D

## eof - Makefile
