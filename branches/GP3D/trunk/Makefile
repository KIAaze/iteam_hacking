#####################################################################################################################
# GAMEPOWER 3D                                                                                                      #
#####################################################################################################################
#                                                                                                                   #
# Makefile for compiling the library                                                                                #
#                                                                                                                   #
#####################################################################################################################
#                                                                                                                   #
# Type in a terminal before running -any- example that uses GP3D:                                                   #
# export LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH                                                                         #
#                                                                                                                   #
#####################################################################################################################
CFLAGS=-I.

all: main

main: lib/core.cpp lib/light.cpp lib/3dmath.cpp lib/effects.cpp lib/camera.cpp lib/primitive.cpp lib/fileio.cpp lib/loaders/md2.cpp
	g++ $(CFLAGS) -c -o core.o lib/core.cpp
	g++ $(CFLAGS) -c -o light.o lib/light.cpp
	g++ $(CFLAGS) -c -o 3dmath.o lib/3dmath.cpp
	g++ $(CFLAGS) -c -o effects.o lib/effects.cpp
	g++ $(CFLAGS) -c -o camera.o lib/camera.cpp
	g++ $(CFLAGS) -c -o primitive.o lib/primitive.cpp
	g++ $(CFLAGS) -c -o fileio.o lib/fileio.cpp
	g++ $(CFLAGS) -c -o md2.o lib/loaders/md2.cpp
	ld -o libgp3d.so core.o light.o 3dmath.o effects.o camera.o primitive.o md2.o fileio.o -shared
	rm core.o light.o 3dmath.o effects.o camera.o primitive.o md2.o fileio.o

clean:
	rm libgp3d.so
