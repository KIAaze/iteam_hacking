CC=g++ -g

#-----------------------------------------------------------------------------
# CFLAGS: Used for compiling. Flag -fPIC is specifically for compilation to
# shared libraries.
#-----------------------------------------------------------------------------
CFLAGS=-fPIC \
       `sdl-config --cflags` \
       -Wall -O2

#-----------------------------------------------------------------------------
# LDFLAGS: Used for the linker.
#-----------------------------------------------------------------------------
LDFLAGS=`sdl-config --libs` \
		-lGL \
        -lSDL \
        -lSDLmain \
        -lSDL_image \
        -lSDL_ttf \

#-----------------------------------------------------------------------------
# A few variables:
#   BINARY_SO: the shared object's name to be generated.
# 	BIN: the location where the binaries (*.o and executables) need to be
#	SRC: the source directory of the test.cpp's.
#-----------------------------------------------------------------------------
BINARY_SO=libgp2d.so
SRC=.
BIN=./bin

#-----------------------------------------------------------------------------
# The list of 'object' targets to generate.
#-----------------------------------------------------------------------------
OBJECTS_MAIN=$(BIN)/exception.o \
	$(BIN)/engine.o \
	$(BIN)/string.o \
	$(BIN)/sysinfo.o \
	$(BIN)/input.o \
	$(BIN)/thread.o \
	$(BIN)/color.o \
	$(BIN)/rect.o \
	$(BIN)/window.o \
	$(BIN)/object.o \
	$(BIN)/camera.o \
	$(BIN)/texture.o \
	$(BIN)/sprite.o

#-----------------------------------------------------------------------------
# Target `all':
#	Makes the shared object libgp2d.so
#-----------------------------------------------------------------------------
all: init $(OBJECTS_MAIN)
	$(CC) $(LDFLAGS) -shared -o $(BIN)/$(BINARY_SO) $(OBJECTS_MAIN)

#-----------------------------------------------------------------------------
# Target `init':
#	Does pre-initialization before building anything, in this case creating a
#	directory to hold the binaries.
#-----------------------------------------------------------------------------
.PHONY: init
init:
	@mkdir -p $(BIN)

#-----------------------------------------------------------------------------
# Target `install':
#	Installs the generated shared object and the header files into the
# 	destined directories (/usr/lib and /usr/include/GP2D). Sudo rights are
#   necessary to run this.
#-----------------------------------------------------------------------------
.PHONY: install
install:
	mkdir -p /usr/include/GP2D
	cp $(SRC)/*.hpppp /usr/include/GP2D
	cp $(BIN)/libgp2d.so /usr/lib

.PHONY: uninstall
uninstall:
	rm -rf /usr/include/GP2D
	rm /usr/lib/libgp2d.so

#-----------------------------------------------------------------------------
# Target `clean':
#	Cleans the generated object files by deleting the 'bin' dir.
#-----------------------------------------------------------------------------
.PHONY: clean
clean:
	rm -rf ./bin


#-----------------------------------------------------------------------------
# The actual targets for compiling individual source files (along with their
# dependencies) are starting from here. Why did I write it like this? Well,
# mainly because it is very helpful in compiling it for testing purposes.
# If a source file is not changed, it won't be compiled. Speedier compile times!
#
# And every target starts with $(BIN)/ because the `all` target refers to the
# $(BIN)/xxx.o stuff too.
#-----------------------------------------------------------------------------
$(BIN)/engine.o: $(SRC)/engine.cpp $(SRC)/engine.hpp
	$(CC) $(CFLAGS) -c $(SRC)/engine.cpp -o $(BIN)/engine.o

$(BIN)/exception.o: $(SRC)/exception.cpp $(SRC)/exception.hpp
	$(CC) $(CFLAGS) -c $(SRC)/exception.cpp -o $(BIN)/exception.o

$(BIN)/thread.o: $(SRC)/thread.cpp $(SRC)/thread.hpp
	$(CC) $(CFLAGS) -c $(SRC)/thread.cpp -o $(BIN)/thread.o

$(BIN)/color.o: $(SRC)/color.cpp $(SRC)/color.hpp
	$(CC) $(CFLAGS) -c $(SRC)/color.cpp -o $(BIN)/color.o

$(BIN)/window.o: $(SRC)/window.cpp $(SRC)/window.hpp
	$(CC) $(CFLAGS) -c $(SRC)/window.cpp -o $(BIN)/window.o

$(BIN)/object.o: $(SRC)/object.cpp $(SRC)/object.hpp
	$(CC) $(CFLAGS) -c $(SRC)/object.cpp -o $(BIN)/object.o

$(BIN)/camera.o: $(SRC)/camera.cpp $(SRC)/camera.hpp
	$(CC) $(CFLAGS) -c $(SRC)/camera.cpp -o $(BIN)/camera.o

$(BIN)/texture.o: $(SRC)/texture.cpp $(SRC)/texture.hpp
	$(CC) $(CFLAGS) -c $(SRC)/texture.cpp -o $(BIN)/texture.o

$(BIN)/sprite.o: $(SRC)/sprite.cpp $(SRC)/sprite.hpp
	$(CC) $(CFLAGS) -c $(SRC)/sprite.cpp -o $(BIN)/sprite.o

$(BIN)/rect.o: $(SRC)/rect.cpp $(SRC)/rect.hpp
	$(CC) $(CFLAGS) -c $(SRC)/rect.cpp -o $(BIN)/rect.o

$(BIN)/input.o: $(SRC)/input.cpp $(SRC)/input.hpp
	$(CC) $(CFLAGS) -c $(SRC)/input.cpp -o $(BIN)/input.o

$(BIN)/string.o: $(SRC)/string.cpp $(SRC)/string.hpp
	$(CC) $(CFLAGS) -c $(SRC)/string.cpp -o $(BIN)/string.o

$(BIN)/sysinfo.o: $(SRC)/sysinfo.cpp $(SRC)/sysinfo.hpp
	$(CC) $(CFLAGS) -c $(SRC)/sysinfo.cpp -o $(BIN)/sysinfo.o
