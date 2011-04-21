CC=g++ -g
LIBPATH=../bin/

#-----------------------------------------------------------------------------
# CFLAGS: Used for compiling. Flag -fPIC is specifically for compilation to
# shared libraries.
#-----------------------------------------------------------------------------
CFLAGS=-fPIC \
       `sdl-config --cflags` \
       -Wall -O2 \
       -I../ \
       -L$(LIBPATH)

#-----------------------------------------------------------------------------
# LDFLAGS: Used for the linker.
#-----------------------------------------------------------------------------
LDFLAGS=`sdl-config --libs` \
        -Wl,-rpath $(LIBPATH) \
        -L$(LIBPATH) \
        -lGL \
        -lSDL \
        -lSDLmain \
        -lSDL_ttf \
        -lgp2d

#-----------------------------------------------------------------------------
# A few variables:
#   BINARY_SO: the shared object's name to be generated.
#   BIN: the location where the binaries (*.o and executables) need to be
#   SRC: the source directory of the test.cpp's.
#-----------------------------------------------------------------------------
BINARY_SO=test
SRC=./
BIN=./

#-----------------------------------------------------------------------------
# The list of 'object' targets to generate.
#-----------------------------------------------------------------------------
OBJECTS_MAIN=$(BIN)/test.o

#-----------------------------------------------------------------------------
# Target `all':
#   Makes the shared object libgp2d.so
#-----------------------------------------------------------------------------
all: init $(OBJECTS_MAIN)
	$(CC) $(LDFLAGS) -o $(BIN)/$(BINARY_SO) $(OBJECTS_MAIN)

#-----------------------------------------------------------------------------
# Target `init':
#   Does pre-initialization before building anything, in this case creating a
#   directory to hold the binaries.
#-----------------------------------------------------------------------------
.PHONY: init
init:
	@mkdir -p $(BIN)

#-----------------------------------------------------------------------------
# Target `clean':
#   Cleans the generated object files by deleting the 'bin' dir.
#-----------------------------------------------------------------------------
.PHONY: clean
clean:
	rm test.o
	rm test

#-----------------------------------------------------------------------------
# The actual targets for compiling individual source files (along with their
# dependencies) are starting from here. Why did I write it like this? Well,
# mainly because it is very helpful in compiling it for testing purposes.
# If a source file is not changed, it won't be compiled. Speedier compile times!
#
# And every target starts with $(BIN)/ because the `all` target refers to the
# $(BIN)/xxx.o stuff too.
#-----------------------------------------------------------------------------
$(BIN)/test.o: $(SRC)/test.cpp $(SRC)/test.hpp
	$(CC) $(CFLAGS) -c $(SRC)/test.cpp -o $(BIN)/test.o
