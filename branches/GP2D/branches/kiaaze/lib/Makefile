CC=g++

CFLAGSL32=-I. -I/usr/include/freetype2 -I/usr/include/SDL
CFLAGSL64=-I. -fPIC -I/usr/include/freetype2
CFLAGSW32=-I.

EXE=libgp2d.so

HEADER_FILES = gp2d.h 3dmath.h audio.h camera.h collision.h core.h fps.h freetype.h GUI_area.h GUI_button.h GUI_C.h GUI.h GUI_font.h GUI_generic.h GUI_image.h GUI_loadimage.h GUI_menu.h GUI_output.h GUI_scrollbar.h gui_system.h GUI_termwin.h GUI_widget.h inputhandler.h sprite.h spritesheet.h timer.h

CPP_FILES = 3dmath.cpp audio.cpp camera.cpp collision.cpp core.cpp fps.cpp freetype.cpp GUI_area.cpp GUI_button.cpp GUI_C.cpp GUI.cpp GUI_font.cpp GUI_generic.cpp GUI_image.cpp GUI_loadimage.cpp GUI_menu.cpp GUI_output.cpp GUI_scrollbar.cpp gui_system.cpp GUI_termwin.cpp GUI_widget.cpp inputhandler.cpp sprite.cpp spritesheet.cpp timer.cpp

OBJECTS = 3dmath.o audio.o camera.o collision.o core.o fps.o freetype.o GUI_area.o GUI_button.o GUI_C.o GUI.o GUI_font.o GUI_generic.o GUI_image.o GUI_loadimage.o GUI_menu.o GUI_output.o GUI_scrollbar.o gui_system.o GUI_termwin.o GUI_widget.o inputhandler.o sprite.o spritesheet.o timer.o

.SUFFIXES: .cpp .o

.cpp.o:
	@echo "$< -> $@"
	$(CC) $(CFLAGSL32) -c -o $@ $<

all: $(EXE)

$(EXE): $(OBJECTS)
	@echo "Linking..."
	gcc -o $(EXE) $(OBJECTS) -shared

linux32: $(EXE)  others
	gcc -o $(EXE) $(OBJECTS) -shared

linux64: $(EXE)  others
	gcc -o $(EXE) $(OBJECTS) -shared

win32: $(EXE)  others
	ar rcs libgp2d.dll $(OBJECTS)

others: $(CPP_FILES)
	$(CC) $(CFLAGSL32) -c 3dmath.cpp
	$(CC) $(CFLAGSL32) -c audio.cpp
	$(CC) $(CFLAGSL32) -c camera.cpp
	$(CC) $(CFLAGSL32) -c collision.cpp
	$(CC) $(CFLAGSL32) -c core.cpp
	$(CC) $(CFLAGSL32) -c fps.cpp
	$(CC) $(CFLAGSL32) -c freetype.cpp
	$(CC) $(CFLAGSL32) -c GUI_area.cpp
	$(CC) $(CFLAGSL32) -c GUI_button.cpp
	$(CC) $(CFLAGSL32) -c GUI_C.cpp
	$(CC) $(CFLAGSL32) -c GUI.cpp
	$(CC) $(CFLAGSL32) -c GUI_font.cpp
	$(CC) $(CFLAGSL32) -c GUI_generic.cpp
	$(CC) $(CFLAGSL32) -c GUI_image.cpp
	$(CC) $(CFLAGSL32) -c GUI_loadimage.cpp
	$(CC) $(CFLAGSL32) -c GUI_menu.cpp
	$(CC) $(CFLAGSL32) -c GUI_output.cpp
	$(CC) $(CFLAGSL32) -c GUI_scrollbar.cpp
	$(CC) $(CFLAGSL32) -c gui_system.cpp
	$(CC) $(CFLAGSL32) -c GUI_termwin.cpp
	$(CC) $(CFLAGSL32) -c GUI_widget.cpp
	$(CC) $(CFLAGSL32) -c inputhandler.cpp
	$(CC) $(CFLAGSL32) -c sprite.cpp
	$(CC) $(CFLAGSL32) -c spritesheet.cpp
	$(CC) $(CFLAGSL32) -c timer.cpp

clean:
	rm -v *.o $(EXE)
