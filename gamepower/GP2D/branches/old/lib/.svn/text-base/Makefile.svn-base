# Target and source directories.
SRC=.
BIN=.

# The binary shared object and executable target files.
BINARY_SO=libgp2d.so
BINARY_EXEC=gp2dtest
WIN32_BINARY_EXEC=gp2dtest.exe

CC=g++

CFLAGSL32=-g -O0 -I. -I/usr/include/freetype2 -I/usr/include/SDL -Wall
CFLAGSL64=-I. -fPIC -I/usr/include/freetype2 -Wall

CFLAGSW32=-L. -I. -Wall
#LDFLAGSW32=-lmingw32 -lSDLmain -lSDL -lSDL_gfx -lSDL_image -lSDL_mixer -mwindows -lopengl32 -lglu32 -lfreetype -L. -lgp2d

#CFLAGSW32=-DUSE_EVENTCALLBACK -L. -I.
LDFLAGSW32=-lgp2d -lmingw32 -lSDL -lSDL_gfx -lSDL_image -lSDL_mixer -mwindows -lopengl32 -lglu32 -lfreetype

LDFLAGS=`freetype-config --libs` \
		`sdl-config --libs` \
        -lSDL \
        -lSDLmain \
        -lSDL_net \
        -lSDL_mixer \
        -lSDL_image \
        -lSDL_gfx \
        -lGL \
        -lGLU

EXE=libgp2d.so
WIN32_EXE=libgp2d.dll

HEADER_FILES = gp2d.h 3dmath.h audio.h camera.h collision.h core.h fps.h freetype.h gui_system.h GUI_termwin.h GUI_widget.h inputhandler.h sprite.h spritesheet.h timer.h utilities.h

CPP_FILES = 3dmath.cpp audio.cpp camera.cpp collision.cpp core.cpp fps.cpp freetype.cpp gui_system.cpp inputhandler.cpp sprite.cpp spritesheet.cpp timer.cpp utilities.cpp

OBJECTS = 3dmath.o audio.o camera.o collision.o core.o fps.o freetype.o gui_system.o inputhandler.o sprite.o spritesheet.o timer.o utilities.o

OBJECTS_TEST=$(BIN)/test.o $(OBJECTS)

.SUFFIXES: .cpp .o

.cpp.o:
	@echo "$< -> $@"
	$(CC) $(CFLAGSL32) -c -o $@ $<

all: $(EXE)

$(EXE): $(OBJECTS)
	@echo "Linking..."
	gcc -o $(EXE) $(OBJECTS) -shared

$(WIN32_EXE): win32

linux32: objects_linux32
	gcc -o $(EXE) $(OBJECTS) -shared

linux64: objects_linux64
	gcc -o $(EXE) $(OBJECTS) -shared

win32: objects_win32
	ar rcs $(WIN32_EXE) $(OBJECTS)

objects_linux32: $(CPP_FILES)
	$(CC) $(CFLAGSL32) -c 3dmath.cpp
	$(CC) $(CFLAGSL32) -c audio.cpp
	$(CC) $(CFLAGSL32) -c camera.cpp
	$(CC) $(CFLAGSL32) -c collision.cpp
	$(CC) $(CFLAGSL32) -c core.cpp
	$(CC) $(CFLAGSL32) -c fps.cpp
	$(CC) $(CFLAGSL32) -c freetype.cpp
	$(CC) $(CFLAGSL32) -c gui_system.cpp
	$(CC) $(CFLAGSL32) -c inputhandler.cpp
	$(CC) $(CFLAGSL32) -c sprite.cpp
	$(CC) $(CFLAGSL32) -c spritesheet.cpp
	$(CC) $(CFLAGSL32) -c timer.cpp
	$(CC) $(CFLAGSL32) -c utilities.cpp

objects_linux64: $(CPP_FILES)
	$(CC) $(CFLAGSL64) -c 3dmath.cpp
	$(CC) $(CFLAGSL64) -c audio.cpp
	$(CC) $(CFLAGSL64) -c camera.cpp
	$(CC) $(CFLAGSL64) -c collision.cpp
	$(CC) $(CFLAGSL64) -c core.cpp
	$(CC) $(CFLAGSL64) -c fps.cpp
	$(CC) $(CFLAGSL64) -c freetype.cpp
	$(CC) $(CFLAGSL64) -c gui_system.cpp
	$(CC) $(CFLAGSL64) -c inputhandler.cpp
	$(CC) $(CFLAGSL64) -c sprite.cpp
	$(CC) $(CFLAGSL64) -c spritesheet.cpp
	$(CC) $(CFLAGSL64) -c timer.cpp
	$(CC) $(CFLAGSL64) -c utilities.cpp

objects_win32: $(CPP_FILES)
	$(CC) $(CFLAGSW32) -c 3dmath.cpp
	$(CC) $(CFLAGSW32) -c audio.cpp
	$(CC) $(CFLAGSW32) -c camera.cpp
	$(CC) $(CFLAGSW32) -c collision.cpp
	$(CC) $(CFLAGSW32) -c core.cpp
	$(CC) $(CFLAGSW32) -c fps.cpp
	$(CC) $(CFLAGSW32) -c freetype.cpp
	$(CC) $(CFLAGSW32) -c gui_system.cpp
	$(CC) $(CFLAGSW32) -c inputhandler.cpp
	$(CC) $(CFLAGSW32) -c sprite.cpp
	$(CC) $(CFLAGSW32) -c spritesheet.cpp
	$(CC) $(CFLAGSW32) -c timer.cpp
	$(CC) $(CFLAGSW32) -c utilities.cpp
	$(CC) $(CFLAGSW32) -c test.cpp

clean:
	rm -fv *.o $(EXE) $(BINARY_EXEC)

cleanwin32:
	del *.o libgp2d.dll gp2dtest.exe

.PHONY: test
test: init $(EXE) $(OBJECTS_TEST)
	$(CC) $(LDFLAGS) -o $(BIN)/$(BINARY_EXEC) $(OBJECTS_TEST)

.PHONY: win32_test
win32_test: init $(WIN32_EXE) $(OBJECTS_TEST)
	$(CC) $(CFLAGSW32) test.o -o $(BIN)/$(WIN32_BINARY_EXEC) $(LDFLAGSW32)

$(BIN)/test.o: $(SRC)/test.cpp
	@echo "Hey, I've been called instead of the .cpp.o thingy! :D"
	$(CC) $(CFLAGSL32) -c $(SRC)/test.cpp -o $(BIN)/test.o

.PHONY: init
init:
	@echo "I don't do anything. :p"
