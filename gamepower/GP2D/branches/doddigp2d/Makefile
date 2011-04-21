# MAKEFILE FOR GP2D
# =================
# Make sure to copy the libgp2d.so file where your game binary is and 
# type this command:
#
# export LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH
#
# ====================================================================
CFLAGS=-I. -I/usr/include/freetype2

all: main

main:
	g++ $(CFLAGS) -c -o core.o     		lib/core.cpp
	g++ $(CFLAGS) -c -o 3dmath.o    	lib/3dmath.cpp
	g++ $(CFLAGS) -c -o audio.o     	lib/audio.cpp
	g++ $(CFLAGS) -c -o camera.o    	lib/camera.cpp
	g++ $(CFLAGS) -c -o spritesheet.o    	lib/spritesheet.cpp
	g++ $(CFLAGS) -c -o sprite.o    	lib/sprite.cpp
	g++ $(CFLAGS) -c -o freetype.o  	lib/freetype.cpp
	g++ $(CFLAGS) -c -o fps.o       	lib/fps.cpp
	g++ $(CFLAGS) -c -o collision.o 	lib/collision.cpp
	ld -o libgp2d.so core.o camera.o 3dmath.o spritesheet.o sprite.o freetype.o fps.o audio.o collision.o -shared
	rm *.o
clean:
	rm *.o
	rm libgp2d.so
