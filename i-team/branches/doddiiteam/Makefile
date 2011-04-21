LIBRARY_DIR = ../gp2d

# export LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH
#CFLAGS=-I. -L. -I/usr/include/freetype2 -I$(LIBRARY_DIR)/lib
#CFLAGS=-I. -L$(LIBRARY_DIR) -I/usr/include/freetype2 -I$(LIBRARY_DIR)/lib
CFLAGS=-L$(LIBRARY_DIR) -I/usr/include/freetype2 -I$(LIBRARY_DIR)/lib

all: main

main:
#	export LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH
	gcc -o iteam iteam2.cpp players.cpp missiles.cpp game.cpp gamestate.cpp gamescene.cpp runninggamestates.cpp titlegamestate.cpp -Bdynamic $(CFLAGS) -lgp2d -lfreetype `sdl-config --cflags --libs` -lSDL_mixer  -lSDL_image -lGL -lGLU
	
