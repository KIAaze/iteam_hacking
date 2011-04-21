LIBRARY_DIR = ../../gp2d/trunk
CFLAGSL32=-L. -L$(LIBRARY_DIR) -I. -I$(LIBRARY_DIR)/lib -I/usr/include/freetype2
CFLAGSL64=-fPIC -L. -L$(LIBRARY_DIR) -I. -I$(LIBRARY_DIR)/lib -I/usr/include/freetype2
CFLAGSW32=-L. -I.
LINKERL32=-Bdynamic -lgp2d -lfreetype `sdl-config --cflags --libs` -lSDL_mixer  -lSDL_image -lGL -lGLU
LINKERL64=-Bdynamic -lgp2d -lfreetype `sdl-config --cflags --libs` -lSDL_mixer  -lSDL_image -lGL -lGLU
LINKERW32=-lgp2d -lmingw32 -lSDL -lSDL_image -lSDL_mixer -mwindows -lopengl32 -lglu32 -lfreetype
FILES=iteam.cpp functions.cpp players.cpp weapons.cpp mainmenu.cpp

linux32:
	gcc $(CFLAGSL32) -o iteam $(FILES) $(LINKERL32)

linux64:
	gcc $(CFLAGSL64) -o iteam $(FILES) $(LINKERL64)
	
win32:
	g++ $(CFLAGSW32) -o iteam $(FILES) $(LINKERW32)
