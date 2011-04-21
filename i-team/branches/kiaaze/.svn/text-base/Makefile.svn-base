LIBRARY_DIR = .
CC=gcc

CFLAGSL32=-L. -L$(LIBRARY_DIR) -I. -I$(LIBRARY_DIR)/lib -I/usr/include/freetype2 -I/usr/include/SDL
LDFLAGSL32=-Bdynamic -lgp2d -lfreetype `sdl-config --cflags --libs` -lSDL_mixer  -lSDL_image -lSDL_gfx -lGLU
CFLAGSL64=-fPIC -L. -L$(LIBRARY_DIR) -I. -I$(LIBRARY_DIR)/lib -I/usr/include/freetype2
LDFLAGSL64=-Bdynamic -lgp2d -lfreetype `sdl-config --cflags --libs` -lSDL_mixer  -lSDL_image -lSDL_gfx -lGLU
CFLAGSW32=-L. -I.
LDFLAGSW32=-lgp2d -lmingw32 -lSDL -lSDL_image -lSDL_mixer -lSDL_gfx -mwindows -lopengl32 -lglu32 -lfreetype

EXE=iteam
HEADER_FILES=globals.h functions.h players.h weapons.h iteam_maths.h primitives.h physics.h iteam-ai.h settings.h explosions.h mainmenu.h
CPP_FILES=iteam.cpp functions.cpp players.cpp weapons.cpp iteam_maths.cpp primitives.cpp physics.cpp iteam-ai.cpp settings.cpp explosions.cpp mainmenu.cpp
OBJECTS=iteam.o functions.o players.o weapons.o iteam_maths.o primitives.o physics.o iteam-ai.o settings.o explosions.o mainmenu.o

.SUFFIXES: .cpp .o

.cpp.o:
	@echo "$< -> $@"
	$(CC) $(CFLAGSL32) -c $<

all: $(EXE)

$(EXE): $(OBJECTS)
	@echo "Linking..."
	$(CC) $(CFLAGSL32) $(LDFLAGSL32) $(OBJECTS) -o $(EXE)

linux32: iteam.o others
	$(CC) $(CFLAGSL32) -c iteam.cpp
	$(CC) $(CFLAGSL32) $(LDFLAGSL32) $(OBJECTS) -o $(EXE)

linux64: iteam.o others
	$(CC) $(CFLAGSL64) -c iteam.cpp
	$(CC) $(CFLAGSL64) $(LDFLAGSL64) $(OBJECTS) -o $(EXE)

win32: iteam.o others
	CC=g++
	$(CC) $(CFLAGSW32) -c iteam.cpp
	$(CC) $(CFLAGSW32) $(LDFLAGSW32) $(OBJECTS) -o $(EXE)

others: functions.cpp players.cpp weapons.cpp iteam_maths.cpp primitives.cpp physics.cpp iteam-ai.cpp settings.cpp explosions.cpp mainmenu.cpp
	$(CC) $(CFLAGSL32) -c functions.cpp
	$(CC) $(CFLAGSL32) -c players.cpp
	$(CC) $(CFLAGSL32) -c weapons.cpp
	$(CC) $(CFLAGSL32) -c iteam_maths.cpp
	$(CC) $(CFLAGSL32) -c primitives.cpp
	$(CC) $(CFLAGSL32) -c physics.cpp
	$(CC) $(CFLAGSL32) -c iteam-ai.cpp
	$(CC) $(CFLAGSL32) -c settings.cpp
	$(CC) $(CFLAGSL32) -c explosions.cpp
	$(CC) $(CFLAGSL32) -c mainmenu.cpp

clean:
	rm -v *.o $(EXE)
