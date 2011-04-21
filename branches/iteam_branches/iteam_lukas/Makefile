CC=gcc -g

#-----------------------------------------------------------------------------
# CFLAGS: Used for compiling. Includes the -I flag to add a pointer to the
# necessary header files, and includes the -L flag to point to the generated
# libgp2d.so shared object file.
#-----------------------------------------------------------------------------
CFLAGS= -fPIC \
        -I. \
        -I/usr/local/include \
        `sdl-config --cflags` \
        -Wall -O2

#-----------------------------------------------------------------------------
# LDFLAGS: Used for the linker. These libraries also include the libgp2d.so
# file, which is expected in the ../bin/ directory (a result of the build of
# the GP2D framework.
#-----------------------------------------------------------------------------
LDFLAGS=`sdl-config --libs` \
        -lSDL \
        -lSDL_gfx \
        -lSDLmain \
        -lSDL_net \
        -lSDL_mixer \
        -lSDL_image \
        -lSDL_ttf \
        -lGL \
        -lGLU

#-----------------------------------------------------------------------------
# A few variables:
# 	BIN: the location where the binaries (*.o and executables) need to be
#	SRC: the source directory of the test.cpp's.
#-----------------------------------------------------------------------------
BINARY=iteam
BIN=./bin
SRC=./src

#-----------------------------------------------------------------------------
# The list of 'object' targets to generate.
#-----------------------------------------------------------------------------
OBJECTS_MAIN=${BIN}/iteam.o \
	${BIN}/sprite.o \
    ${BIN}/collisions.o \
    ${BIN}/camera.o \
    ${BIN}/physical.o \
    ${BIN}/player.o \
    ${BIN}/terrain.o \
    ${BIN}/font.o \
    ${BIN}/color.o \
    ${BIN}/text.o \
    ${BIN}/utility.o \
    ${BIN}/rocket.o \
    ${BIN}/susi.o \
    ${BIN}/bomb.o

#-----------------------------------------------------------------------------
# Target `all':
#	Builds the test files to objects, to executables.
#-----------------------------------------------------------------------------
.PHONY: all
all: init $(OBJECTS_MAIN)
	$(CC) $(CFLAGS) -o $(BIN)/$(BINARY) $(OBJECTS_MAIN) $(LDFLAGS)

#-----------------------------------------------------------------------------
# Target `init':
#	Does pre-initialization before building anything, in this case creating a
#	directory to hold the binaries.
#-----------------------------------------------------------------------------
.PHONY: init
init:
	@mkdir -p $(BIN)

#-----------------------------------------------------------------------------
# Target `clean':
#	Cleans the generated object files by deleting the 'bin' dir.
#-----------------------------------------------------------------------------
.PHONY: clean
clean:
	rm -rf ./bin

#-----------------------------------------------------------------------------
# Target for the objects:
#	Compiles the object files out of the source files.
#-----------------------------------------------------------------------------
$(BIN)/sprite.o: $(SRC)/sprite.cpp
	$(CC) $(CFLAGS) -c $(SRC)/sprite.cpp -o $(BIN)/sprite.o

$(BIN)/collisions.o: $(SRC)/collisions.cpp
	$(CC) $(CFLAGS) -c $(SRC)/collisions.cpp -o $(BIN)/collisions.o
    
$(BIN)/camera.o: $(SRC)/camera.cpp
	$(CC) $(CFLAGS) -c $(SRC)/camera.cpp -o $(BIN)/camera.o
    
$(BIN)/physical.o: $(SRC)/physical.cpp
	$(CC) $(CFLAGS) -c $(SRC)/physical.cpp -o $(BIN)/physical.o
    
$(BIN)/player.o: $(SRC)/player.cpp
	$(CC) $(CFLAGS) -c $(SRC)/player.cpp -o $(BIN)/player.o
    
$(BIN)/terrain.o: $(SRC)/terrain.cpp
	$(CC) $(CFLAGS) -c $(SRC)/terrain.cpp -o $(BIN)/terrain.o
	
$(BIN)/text.o: $(SRC)/text.cpp
	$(CC) $(CFLAGS) -c $(SRC)/text.cpp -o $(BIN)/text.o

$(BIN)/font.o: $(SRC)/font.cpp
	$(CC) $(CFLAGS) -c $(SRC)/font.cpp -o $(BIN)/font.o

$(BIN)/color.o: $(SRC)/color.cpp
	$(CC) $(CFLAGS) -c $(SRC)/color.cpp -o $(BIN)/color.o
	
$(BIN)/utility.o: $(SRC)/utility.cpp
	$(CC) $(CFLAGS) -c $(SRC)/utility.cpp -o $(BIN)/utility.o
	
$(BIN)/rocket.o: $(SRC)/weapons/rocket.cpp
	$(CC) $(CFLAGS) -c $(SRC)/weapons/rocket.cpp -o $(BIN)/rocket.o
	
$(BIN)/bomb.o: $(SRC)/weapons/bomb.cpp
	$(CC) $(CFLAGS) -c $(SRC)/weapons/bomb.cpp -o $(BIN)/bomb.o
	
$(BIN)/susi.o: $(SRC)/distros/susi.cpp
	$(CC) $(CFLAGS) -c $(SRC)/distros/susi.cpp -o $(BIN)/susi.o

$(BIN)/iteam.o: $(SRC)/iteam.cpp
	$(CC) $(CFLAGS) -c $(SRC)/iteam.cpp -o $(BIN)/iteam.o

