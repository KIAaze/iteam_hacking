LIBRARY_DIR = ../../gp2d/trunk
CFLAGSL32=-L. -L$(LIBRARY_DIR) -I. -I$(LIBRARY_DIR)/lib -I/usr/include/freetype2
CFLAGSL64=-fPIC -L. -L$(LIBRARY_DIR) -I. -I$(LIBRARY_DIR)/lib -I/usr/include/freetype2
CFLAGSW32=-L. -I.

linux32:
	gcc $(CFLAGSL32) -o iteam iteam.cpp functions.cpp players.cpp -Bdynamic -lgp2d -lfreetype `sdl-config --cflags --libs` -lSDL_mixer  -lSDL_image -lGL -lGLU

linux64:
	gcc $(CFLAGSL64) -o iteam iteam.cpp functions.cpp players.cpp -Bdynamic -lgp2d -lfreetype `sdl-config --cflags --libs` -lSDL_mixer  -lSDL_image -lGL -lGLU
	
win32:
	g++ $(CFLAGSW32) -o iteam iteam.cpp functions.cpp players.cpp -lgp2d -lmingw32 -lSDL -lSDL_image -lSDL_mixer -mwindows -lopengl32 -lglu32 -lfreetype
