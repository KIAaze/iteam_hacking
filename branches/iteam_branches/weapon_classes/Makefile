LIBRARY_DIR = .
CC=g++ -g -Wall

CFLAGSL32=-O0 -DUSE_EVENTCALLBACK -L. -L$(LIBRARY_DIR) -I. -I$(LIBRARY_DIR)/lib -I/usr/include/freetype2 
LDFLAGSL32=-O0 -Bdynamic -lgp2d -lfreetype `sdl-config --cflags --libs` -lSDL_mixer  -lSDL_image -lSDL_gfx -lGLU
CFLAGSL64=-DUSE_EVENTCALLBACK -fPIC -L. -L$(LIBRARY_DIR) -I. -I$(LIBRARY_DIR)/lib -I/usr/include/freetype2
LDFLAGSL64=-Bdynamic -lgp2d -lfreetype `sdl-config --cflags --libs` -lSDL_mixer  -lSDL_image -lSDL_gfx -lGLU
CFLAGSW32=-DUSE_EVENTCALLBACK -L. -I.
LDFLAGSW32=-lgp2d -lmingw32 -lSDL -lSDL_gfx -lSDL_image -lSDL_mixer -mwindows -lopengl32 -lglu32 -lfreetype

EXE=iteam

HEADER_FILES=globals.h functions.h Player.h iteam_maths.h primitives.h physics.h settings.h Explosion.h Weapon.h SpriteMap.h iteamGrenade.h iteamMissile.h iteamClusterbomb.h iteamDynamite.h iteamRazor.h iteamMultirazor.h iteamMedipack.h

CPP_FILES=iteam.cpp functions.cpp Player.cpp iteam_maths.cpp primitives.cpp physics.cpp settings.cpp Explosion.cpp Weapon.cpp SpriteMap.cpp iteamGrenade.cpp iteamMissile.cpp iteamClusterbomb.cpp iteamDynamite.cpp iteamRazor.cpp iteamMultirazor.cpp iteamMedipack.cpp

OBJECTS=iteam.o functions.o Player.o iteam_maths.o primitives.o physics.o settings.o Explosion.o Weapon.o SpriteMap.o iteamGrenade.o iteamMissile.o iteamClusterbomb.o iteamDynamite.o iteamRazor.o iteamMultirazor.o iteamMedipack.o

.SUFFIXES: .cpp .o

.cpp.o:
	@echo "$< -> $@"
	$(CC) $(CFLAGSL32) -c $<

all: $(EXE)

#WARNING: If you use this it will create a symlink ../gp2d to GP2D/trunk, removing any existing destination files
all_pluslib: library links $(EXE)

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

objects_linux32: iteam.cpp functions.cpp Player.cpp iteam_maths.cpp primitives.cpp physics.cpp settings.cpp Explosion.cpp iteamGrenade.cpp iteamMissile.cpp iteamClusterbomb.cpp iteamDynamite.cpp iteamRazor.cpp iteamMultirazor.cpp iteamMedipack.cpp
	$(CC) $(CFLAGSL32) -c iteam.cpp
	$(CC) $(CFLAGSL32) -c functions.cpp
	$(CC) $(CFLAGSL32) -c Player.cpp
	$(CC) $(CFLAGSL32) -c iteam_maths.cpp
	$(CC) $(CFLAGSL32) -c primitives.cpp
	$(CC) $(CFLAGSL32) -c physics.cpp
	$(CC) $(CFLAGSL32) -c settings.cpp
	$(CC) $(CFLAGSL32) -c Explosion.cpp
	$(CC) $(CFLAGSL32) -c Weapon.cpp
	$(CC) $(CFLAGSL32) -c SpriteMap.cpp

	$(CC) $(CFLAGSL32) -c iteamGrenade.cpp
	$(CC) $(CFLAGSL32) -c iteamMissile.cpp
	$(CC) $(CFLAGSL32) -c iteamClusterbomb.cpp
	$(CC) $(CFLAGSL32) -c iteamDynamite.cpp
	$(CC) $(CFLAGSL32) -c iteamRazor.cpp
	$(CC) $(CFLAGSL32) -c iteamMultirazor.cpp
	$(CC) $(CFLAGSL32) -c iteamMedipack.cpp

objects_linux64: iteam.cpp functions.cpp Player.cpp iteam_maths.cpp primitives.cpp physics.cpp settings.cpp Explosion.cpp iteamGrenade.cpp iteamMissile.cpp iteamClusterbomb.cpp iteamDynamite.cpp iteamRazor.cpp iteamMultirazor.cpp iteamMedipack.cpp
	$(CC) $(CFLAGSL64) -c iteam.cpp
	$(CC) $(CFLAGSL64) -c functions.cpp
	$(CC) $(CFLAGSL64) -c Player.cpp
	$(CC) $(CFLAGSL64) -c iteam_maths.cpp
	$(CC) $(CFLAGSL64) -c primitives.cpp
	$(CC) $(CFLAGSL64) -c physics.cpp
	$(CC) $(CFLAGSL64) -c settings.cpp
	$(CC) $(CFLAGSL64) -c Explosion.cpp
	$(CC) $(CFLAGSL64) -c Weapon.cpp
	$(CC) $(CFLAGSL64) -c SpriteMap.cpp

	$(CC) $(CFLAGSL64) -c iteamGrenade.cpp
	$(CC) $(CFLAGSL64) -c iteamMissile.cpp
	$(CC) $(CFLAGSL64) -c iteamClusterbomb.cpp
	$(CC) $(CFLAGSL64) -c iteamDynamite.cpp
	$(CC) $(CFLAGSL64) -c iteamRazor.cpp
	$(CC) $(CFLAGSL64) -c iteamMultirazor.cpp
	$(CC) $(CFLAGSL64) -c iteamMedipack.cpp

objects_win32: iteam.cpp functions.cpp Player.cpp iteam_maths.cpp primitives.cpp physics.cpp settings.cpp Explosion.cpp iteamGrenade.cpp iteamMissile.cpp iteamClusterbomb.cpp iteamDynamite.cpp iteamRazor.cpp iteamMultirazor.cpp iteamMedipack.cpp
	$(CC) $(CFLAGSW32) -c iteam.cpp
	$(CC) $(CFLAGSW32) -c functions.cpp
	$(CC) $(CFLAGSW32) -c Player.cpp
	$(CC) $(CFLAGSW32) -c iteam_maths.cpp
	$(CC) $(CFLAGSW32) -c primitives.cpp
	$(CC) $(CFLAGSW32) -c physics.cpp
	$(CC) $(CFLAGSW32) -c settings.cpp
	$(CC) $(CFLAGSW32) -c Explosion.cpp
	$(CC) $(CFLAGSW32) -c Weapon.cpp
	$(CC) $(CFLAGSW32) -c SpriteMap.cpp

	$(CC) $(CFLAGSW32) -c iteamGrenade.cpp
	$(CC) $(CFLAGSW32) -c iteamMissile.cpp
	$(CC) $(CFLAGSW32) -c iteamClusterbomb.cpp
	$(CC) $(CFLAGSW32) -c iteamDynamite.cpp
	$(CC) $(CFLAGSW32) -c iteamRazor.cpp
	$(CC) $(CFLAGSW32) -c iteamMultirazor.cpp
	$(CC) $(CFLAGSW32) -c iteamMedipack.cpp
clean:
	rm -fv *.o $(EXE)

cleanwin32:
	del *.o $(EXE) libgp2d.dll

library:
	make -C ../../../gamepower/GP2D/trunk

#create a link to GP2D/trunk. This is necessary to maintain compatibilty with the iteam-installer while keeping the full svn checkout easily compilable. (I always make full svn checkouts. (KIAaze))
#WARNING: If you use this it will create a symlink ../gp2d to GP2D/trunk, removing any existing destination files
links:
	ln -sf ../gamepower/GP2D/trunk/ ../gp2d

cleanlib:
	make -C ../../../gamepower/GP2D/trunk clean

cleanall: clean cleanlib
