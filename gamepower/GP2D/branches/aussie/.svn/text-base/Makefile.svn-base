CFLAGSL32=-I. -I/usr/include/freetype2
CFLAGSL64=-I. -fPIC -m32 -I/usr/include/freetype2
CFLAGSW32=-I.

linux32:
	g++ $(CFLAGSL32) -c -o core.o        lib/core.cpp
	g++ $(CFLAGSL32) -c -o 3dmath.o      lib/3dmath.cpp
	g++ $(CFLAGSL32) -c -o audio.o       lib/audio.cpp
	g++ $(CFLAGSL32) -c -o camera.o      lib/camera.cpp
	g++ $(CFLAGSL32) -c -o sprite.o      lib/sprite.cpp
	g++ $(CFLAGSL32) -c -o freetype.o    lib/freetype.cpp
	g++ $(CFLAGSL32) -c -o fps.o         lib/fps.cpp
	g++ $(CFLAGSL32) -c -o collision.o   lib/collision.cpp
	g++ $(CFLAGSL32) -c -o timer.o       lib/timer.cpp
	g++ $(CFLAGSL32) -c -o spritesheet.o lib/spritesheet.cpp
	ld -o libgp2d.so core.o camera.o 3dmath.o sprite.o freetype.o fps.o audio.o collision.o timer.o spritesheet.o -shared
	rm *.o

linux64:
	g++ $(CFLAGSL64) -c -o core.o        lib/core.cpp
	g++ $(CFLAGSL64) -c -o 3dmath.o      lib/3dmath.cpp
	g++ $(CFLAGSL64) -c -o audio.o       lib/audio.cpp
	g++ $(CFLAGSL64) -c -o camera.o      lib/camera.cpp
	g++ $(CFLAGSL64) -c -o sprite.o      lib/sprite.cpp
	g++ $(CFLAGSL64) -c -o freetype.o    lib/freetype.cpp
	g++ $(CFLAGSL64) -c -o fps.o         lib/fps.cpp
	g++ $(CFLAGSL64) -c -o collision.o   lib/collision.cpp
	g++ $(CFLAGSL64) -c -o timer.o       lib/timer.cpp
	g++ $(CFLAGSL64) -c -o spritesheet.o lib/spritesheet.cpp
	ld -o libgp2d.so core.o camera.o 3dmath.o sprite.o freetype.o fps.o audio.o collision.o timer.o spritesheet.o -shared
	rm *.o
	
win32:
	g++ $(CFLAGSW32) -c -o core.o        lib/core.cpp
	g++ $(CFLAGSW32) -c -o 3dmath.o      lib/3dmath.cpp
	g++ $(CFLAGSW32) -c -o audio.o       lib/audio.cpp
	g++ $(CFLAGSW32) -c -o camera.o      lib/camera.cpp
	g++ $(CFLAGSW32) -c -o sprite.o      lib/sprite.cpp
	g++ $(CFLAGSW32) -c -o freetype.o    lib/freetype.cpp
	g++ $(CFLAGSW32) -c -o fps.o         lib/fps.cpp
	g++ $(CFLAGSW32) -c -o collision.o   lib/collision.cpp
	g++ $(CFLAGSW32) -c -o timer.o       lib/timer.cpp
	g++ $(CFLAGSW32) -c -o spritesheet.o lib/spritesheet.cpp
	ar rcs libgp2d.dll core.o camera.o 3dmath.o sprite.o freetype.o fps.o audio.o collision.o timer.o spritesheet.o
	del *.o
