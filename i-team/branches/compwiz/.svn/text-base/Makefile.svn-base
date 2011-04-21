LIBRARY_DIR = .
CC=g++

CFLAGSL32=-g -O0 -DUSE_EVENTCALLBACK -L. -L$(LIBRARY_DIR) -I. -I$(LIBRARY_DIR)/lib -I/usr/include/freetype2 
LDFLAGSL32=-g -O0 -Bdynamic -lgp2d -lfreetype `sdl-config --cflags --libs` -lSDL_mixer  -lSDL_image -lSDL_gfx -lGLU
CFLAGSL64=-DUSE_EVENTCALLBACK -fPIC -L. -L$(LIBRARY_DIR) -I. -I$(LIBRARY_DIR)/lib -I/usr/include/freetype2
LDFLAGSL64=-Bdynamic -lgp2d -lfreetype `sdl-config --cflags --libs` -lSDL_mixer  -lSDL_image -lSDL_gfx -lGLU
CFLAGSW32=-DUSE_EVENTCALLBACK -L. -I.
LDFLAGSW32=-lgp2d -lmingw32 -lSDL -lSDL_gfx -lSDL_image -lSDL_mixer -mwindows -lopengl32 -lglu32 -lfreetype

EXE=iteam
HEADER_FILES=globals.h functions.h players.h weapons.h iteam_maths.h primitives.h physics.h iteam-ai.h settings.h explosions.h mainmenu.h basicwidget.h
CPP_FILES=iteam.cpp functions.cpp players.cpp weapons.cpp iteam_maths.cpp primitives.cpp physics.cpp iteam-ai.cpp settings.cpp explosions.cpp mainmenu.cpp basicwidget.cpp
OBJECTS=iteam.o functions.o players.o weapons.o iteam_maths.o primitives.o physics.o iteam-ai.o settings.o explosions.o mainmenu.o basicwidget.o

.SUFFIXES: .cpp .o

.cpp.o:
	@echo "$< -> $@"
	$(CC) $(CFLAGSL32) -c $<

all: $(EXE)

$(EXE): $(OBJECTS)
	@echo "Linking..."
	$(CC) $(CFLAGSL32) $(LDFLAGSL32) $(OBJECTS) -o $(EXE)

linux32: objects_linux32
	$(CC) $(CFLAGSL32) $(LDFLAGSL32) $(OBJECTS) -o $(EXE)

linux64: objects_linux64
	$(CC) $(CFLAGSL64) $(LDFLAGSL64) $(OBJECTS) -o $(EXE)

win32: objects_win32
	@echo "Copying libgp2d.dll..."
	copy ..\..\gamepower\GP2D\trunk\libgp2d.dll . /Y
	@echo "Linking..."
	$(CC) $(CFLAGSW32) $(OBJECTS) -o $(EXE).exe $(LDFLAGSW32)

objects_linux32: iteam.cpp functions.cpp players.cpp weapons.cpp iteam_maths.cpp primitives.cpp physics.cpp iteam-ai.cpp settings.cpp explosions.cpp mainmenu.cpp basicwidget.cpp
	$(CC) $(CFLAGSL32) -c iteam.cpp
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
	$(CC) $(CFLAGSL32) -c basicwidget.cpp

objects_linux64: iteam.cpp functions.cpp players.cpp weapons.cpp iteam_maths.cpp primitives.cpp physics.cpp iteam-ai.cpp settings.cpp explosions.cpp mainmenu.cpp basicwidget.cpp
	$(CC) $(CFLAGSL64) -c iteam.cpp
	$(CC) $(CFLAGSL64) -c functions.cpp
	$(CC) $(CFLAGSL64) -c players.cpp
	$(CC) $(CFLAGSL64) -c weapons.cpp
	$(CC) $(CFLAGSL64) -c iteam_maths.cpp
	$(CC) $(CFLAGSL64) -c primitives.cpp
	$(CC) $(CFLAGSL64) -c physics.cpp
	$(CC) $(CFLAGSL64) -c iteam-ai.cpp
	$(CC) $(CFLAGSL64) -c settings.cpp
	$(CC) $(CFLAGSL64) -c explosions.cpp
	$(CC) $(CFLAGSL64) -c mainmenu.cpp
	$(CC) $(CFLAGSL64) -c basicwidget.cpp

objects_win32: iteam.cpp functions.cpp players.cpp weapons.cpp iteam_maths.cpp primitives.cpp physics.cpp iteam-ai.cpp settings.cpp explosions.cpp mainmenu.cpp basicwidget.cpp
	$(CC) $(CFLAGSW32) -c iteam.cpp
	$(CC) $(CFLAGSW32) -c functions.cpp
	$(CC) $(CFLAGSW32) -c players.cpp
	$(CC) $(CFLAGSW32) -c weapons.cpp
	$(CC) $(CFLAGSW32) -c iteam_maths.cpp
	$(CC) $(CFLAGSW32) -c primitives.cpp
	$(CC) $(CFLAGSW32) -c physics.cpp
	$(CC) $(CFLAGSW32) -c iteam-ai.cpp
	$(CC) $(CFLAGSW32) -c settings.cpp
	$(CC) $(CFLAGSW32) -c explosions.cpp
	$(CC) $(CFLAGSW32) -c mainmenu.cpp
	$(CC) $(CFLAGSW32) -c basicwidget.cpp

clean:
	rm -v *.o $(EXE)

cleanwin32:
	del *.o $(EXE) libgp2d.dll
