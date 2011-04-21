BIN=bitmap_to_polygon
OBJ=bitmap_to_polygon.o

CXX=g++ -g -Wall
CPPFLAGS=-I.
LDFLAGS=-L. -lgp2d

.PHONY: all clean cleanall libs libgp2d all_plus_libs

all: $(BIN)

$(BIN): $(OBJ)
	$(CXX) $(CFLAGS) $(LDFLAGS) -o $@ $<

libs: libgp2d

libgp2d:
	make -C ../../trunk/ -f Makefile.linux32
	ln -sf ../../trunk/bin/libgp2d.so .

all_plus_libs: libs all

clean:
	rm -f *.o $(BIN)

cleanall: clean
	rm -f *.so
	make -C ../../trunk/ -f Makefile.linux32 clean
