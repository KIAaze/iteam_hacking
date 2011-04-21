LIBRARY_DIR = .
CC=g++

CFLAGSL32=-ggdb -O0 -L. -L$(LIBRARY_DIR) -I. -I$(LIBRARY_DIR)/lib -I/usr/include/freetype2 
LDFLAGSL32=-Bdynamic -lgp2d -lfreetype `sdl-config --cflags --libs` -lSDL_mixer  -lSDL_image -lSDL_gfx -lGLU
CFLAGSL64=-fPIC -L. -L$(LIBRARY_DIR) -I. -I$(LIBRARY_DIR)/lib -I/usr/include/freetype2
LDFLAGSL64=-Bdynamic -lgp2d -lfreetype `sdl-config --cflags --libs` -lSDL_mixer  -lSDL_image -lSDL_gfx -lGLU
CFLAGSW32=-L. -I.
LDFLAGSW32=-lgp2d -lmingw32 -lSDL -lSDL_gfx -lSDL_image -lSDL_mixer -mwindows -lopengl32 -lglu32 -lfreetype

EXE=iteam
HEADER_FILES=globals.h functions.h players.h Weapon.h WeaponComponent.h WeaponsList.h iteam_maths.h primitives.h physics.h iteam-ai.h settings.h explosions.h mainmenu.h basicwidget.h iteam-assert.h iteamGrenade.h iteamMissile.h iteamClusterBomb.h iteamDynamite.h WeaponListThumbnail.h iteam-ai.h
CPP_FILES=iteam.cpp functions.cpp players.cpp Weapon.cpp WeaponComponent.cpp WeaponsList.cpp iteam_maths.cpp primitives.cpp physics.cpp settings.cpp explosions.cpp mainmenu.cpp basicwidget.cpp iteamGrenade.cpp iteamMissile.cpp iteamClusterBomb.cpp iteamDynamite.cpp WeaponListThumbnail.cpp iteam-ai.
OBJECTS=iteam.o functions.o players.o Weapon.o WeaponComponent.o WeaponsList.o iteam_maths.o primitives.o physics.o settings.o explosions.o mainmenu.o basicwidget.o iteamGrenade.o iteamMissile.o iteamClusterBomb.o iteamDynamite.o WeaponListThumbnail.o iteam-ai.o

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

objects_linux32: iteam.cpp functions.cpp players.cpp Weapon.cpp iteam_maths.cpp primitives.cpp physics.cpp iteam-ai.cpp settings.cpp explosions.cpp mainmenu.cpp basicwidget.cpp WeaponComponent.cpp WeaponsList.cpp iteamGrenade.cpp iteamMissile.cpp iteamDynamite.cpp WeaponListThumbnail.cpp
	$(CC) $(CFLAGSL32) -c iteam.cpp
	$(CC) $(CFLAGSL32) -c functions.cpp
	$(CC) $(CFLAGSL32) -c players.cpp
	$(CC) $(CFLAGSL32) -c Weapon.cpp
	$(CC) $(CFLAGSL32) -c WeaponComponent.cpp
	$(CC) $(CFLAGSL32) -c WeaponsList.cpp
	$(CC) $(CFLAGSL32) -c iteam_maths.cpp
	$(CC) $(CFLAGSL32) -c primitives.cpp
	$(CC) $(CFLAGSL32) -c physics.cpp
	$(CC) $(CFLAGSL32) -c iteam-ai.cpp
	$(CC) $(CFLAGSL32) -c settings.cpp
	$(CC) $(CFLAGSL32) -c explosions.cpp
	$(CC) $(CFLAGSL32) -c mainmenu.cpp
	$(CC) $(CFLAGSL32) -c basicwidget.cpp
	$(CC) $(CFLAGSL32) -c iteamGrenade.cpp
	$(CC) $(CFLAGSL32) -c iteamMissile.cpp
	$(CC) $(CFLAGSL32) -c iteamClusterBomb.cpp
	$(CC) $(CFLAGSL32) -c iteamDynamite.cpp
	$(CC) $(CFLAGSL32) -c WeaponListThumbnail.cpp

objects_linux64: iteam.cpp functions.cpp players.cpp Weapon.cpp iteam_maths.cpp primitives.cpp physics.cpp iteam-ai.cpp settings.cpp explosions.cpp mainmenu.cpp basicwidget.cpp WeaponComponent.cpp WeaponsList.cpp iteamGrenade.cpp iteamMissile.cpp iteamDynamite.cpp WeaponListThumbnail.cpp
	$(CC) $(CFLAGSL64) -c iteam.cpp
	$(CC) $(CFLAGSL64) -c functions.cpp
	$(CC) $(CFLAGSL64) -c players.cpp
	$(CC) $(CFLAGSL64) -c Weapon.cpp
	$(CC) $(CFLAGSL64) -c WeaponComponent.cpp
	$(CC) $(CFLAGSL64) -c WeaponsList.cpp
	$(CC) $(CFLAGSL64) -c iteam_maths.cpp
	$(CC) $(CFLAGSL64) -c primitives.cpp
	$(CC) $(CFLAGSL64) -c physics.cpp
	$(CC) $(CFLAGSL64) -c iteam-ai.cpp
	$(CC) $(CFLAGSL64) -c settings.cpp
	$(CC) $(CFLAGSL64) -c explosions.cpp
	$(CC) $(CFLAGSL64) -c mainmenu.cpp
	$(CC) $(CFLAGSL64) -c basicwidget.cpp
	$(CC) $(CFLAGSL32) -c iteamGrenade.cpp
	$(CC) $(CFLAGSL32) -c iteamMissile.cpp
	$(CC) $(CFLAGSL32) -c iteamClusterBomb.cpp
	$(CC) $(CFLAGSL32) -c iteamDynamite.cpp
	$(CC) $(CFLAGSL32) -c WeaponListThumbnail.cpp

objects_win32: iteam.cpp functions.cpp players.cpp Weapon.cpp iteam_maths.cpp primitives.cpp physics.cpp iteam-ai.cpp settings.cpp explosions.cpp mainmenu.cpp basicwidget.cpp WeaponComponent.cpp WeaponsList.cpp iteamGrenade.cpp iteamMissile.cpp iteamDynamite.cpp WeaponListThumbnail.cpp
	$(CC) $(CFLAGSW32) -c iteam.cpp
	$(CC) $(CFLAGSW32) -c functions.cpp
	$(CC) $(CFLAGSW32) -c players.cpp
	$(CC) $(CFLAGSW32) -c Weapon.cpp
	$(CC) $(CFLAGSW32) -c WeaponComponent.cpp
	$(CC) $(CFLAGSW32) -c WeaponsList.cpp
	$(CC) $(CFLAGSW32) -c iteam_maths.cpp
	$(CC) $(CFLAGSW32) -c primitives.cpp
	$(CC) $(CFLAGSW32) -c physics.cpp
	$(CC) $(CFLAGSW32) -c iteam-ai.cpp
	$(CC) $(CFLAGSW32) -c settings.cpp
	$(CC) $(CFLAGSW32) -c explosions.cpp
	$(CC) $(CFLAGSW32) -c mainmenu.cpp
	$(CC) $(CFLAGSW32) -c basicwidget.cpp
	$(CC) $(CFLAGSL32) -c iteamGrenade.cpp
	$(CC) $(CFLAGSL32) -c iteamMissile.cpp
	$(CC) $(CFLAGSL32) -c iteamClusterBomb.cpp
	$(CC) $(CFLAGSL32) -c iteamDynamite.cpp
	$(CC) $(CFLAGSL32) -c WeaponListThumbnail.cpp

clean:
	rm -v *.o $(EXE)
cleanwin32:
	del *.o $(EXE) libgp2d.dll
