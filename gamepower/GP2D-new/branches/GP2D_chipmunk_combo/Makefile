BIN = GP2D_chipmunk_combo bitmap_to_polygon
SRC = GP2D_chipmunk_combo.cpp bitmap_to_polygon.cpp polygon.cpp
OBJ = $(SRC:.cpp=.o)

# OBJ=GP2D_chipmunk_combo.o bitmap_to_polygon.o

CXX=g++ -g -Wall
CPPFLAGS=-I.
LDFLAGS=-L. -lgp2d -lchipmunk

.PHONY: all clean cleanall libs libgp2d libchipmunk all_plus_libs

all: $(BIN)

#$(BIN): $(OBJ)
#	$(CXX) $(CFLAGS) $(LDFLAGS) -o $@ $<

GP2D_chipmunk_combo: GP2D_chipmunk_combo.o polygon.o
	$(CXX) $(CPPFLAGS) $(LDFLAGS) -o $@ $<

bitmap_to_polygon: bitmap_to_polygon.o polygon.o
	$(CXX) $(CPPFLAGS) $(LDFLAGS) -o $@ $<

libs: libgp2d libchipmunk

libgp2d:
	make -C ../../trunk/ -f Makefile.linux32
	ln -sf ../../trunk/bin/libgp2d.so .

libchipmunk:
	cd Chipmunk-4.1.0 && cmake .
	make -C ./Chipmunk-4.1.0
	ln -sf ./Chipmunk-4.1.0/src/libchipmunk.so.4 libchipmunk.so
	ln -sf ./Chipmunk-4.1.0/src/libchipmunk.so.4 libchipmunk.so.4

all_plus_libs: libs all

clean:
	rm -f *.o $(BIN)

cleanall: clean
	rm -f *.so
	make -C ../../trunk/ -f Makefile.linux32 clean
	make -C ./chipmunk clean
