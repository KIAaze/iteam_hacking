CFLAGSL32=-I. -I/usr/include/freetype2 -Wall
CFLAGSL64=-I. -fPIC -I/usr/include/freetype2 -Wall
CFLAGSW32=-I. -Wall

#currently, only "all" avoids useless recompiling. It uses the linux32 flags however. Just run "make" to use it. :)
all:
	make -C ./lib
	cp ./lib/libgp2d.so .

test:
	make -C ./lib test
	cp ./lib/libgp2d.so .

linux32:
	make -C ./lib linux32
	cp ./lib/libgp2d.so .

linux64:
	make -C ./lib linux64
	cp ./lib/libgp2d.so .

win32:
	make -C ./lib win32
	copy .\lib\libgp2d.dll . /Y

win32_test:
	make -C ./lib win32_test
	copy .\lib\libgp2d.dll . /Y

clean:
	make -C ./lib clean
	rm -fv libgp2d.so

cleanwin32:
	make -C ./lib cleanwin32
	del libgp2d.dll
