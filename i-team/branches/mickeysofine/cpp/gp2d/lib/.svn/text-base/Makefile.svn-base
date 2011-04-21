CC=g++

CFLAGSL32=-g -O0 -I. -I/usr/include/freetype2 -I/usr/include/SDL -Wall
CFLAGSL64=-I. -fPIC -I/usr/include/freetype2 -Wall
CFLAGSW32=-I. -Wall

EXE=libgp2d.so

HEADER_FILES = gp2d.h 3dmath.h audio.h camera.h collision.h core.h fps.h freetype.h gui_system.h GUI_termwin.h GUI_widget.h inputhandler.h sprite.h spritesheet.h timer.h

CPP_FILES = 3dmath.cpp audio.cpp camera.cpp collision.cpp core.cpp fps.cpp freetype.cpp gui_system.cpp inputhandler.cpp sprite.cpp spritesheet.cpp timer.cpp

OBJECTS = 3dmath.o audio.o camera.o collision.o core.o fps.o freetype.o gui_system.o inputhandler.o sprite.o spritesheet.o timer.o

.SUFFIXES: .cpp .o

.cpp.o:
	@echo "$< -> $@"
	$(CC) $(CFLAGSL32) -c -o $@ $<

all: $(EXE)

$(EXE): $(OBJECTS)
	@echo "Linking..."
	gcc -o $(EXE) $(OBJECTS) -shared

linux32: objects_linux32
	gcc -o $(EXE) $(OBJECTS) -shared

linux64: objects_linux64
	gcc -o $(EXE) $(OBJECTS) -shared

win32: objects_win32
	ar rcs libgp2d.dll $(OBJECTS)

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

clean:
	rm -v *.o $(EXE)

cleanwin32:
	del *.o libgp2d.dll
