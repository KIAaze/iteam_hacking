/*

	This file is part of GamePower 3D.

	GamePower 3D is free software; you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation; either version 2 of the License, or
	(at your option) any later version.

	GamePower 3D is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with GamePower 3D; if not, write to the Free Software
	Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

===================================================================================
GAMEPOWER 3D ENGINE
===================================================================================
This engine requires:	* OpenGL/Mesa development libraries
								* C compiler (gcc 4.2 used)
								* SDL development libraries
								  (libsdl1.2-dev, libsdl-image1.2-dev)

FILE INPUT/OUTPUT FUNCTIONS FILE (version 0.0.3)
BY WYBIRAL

MODIFICATIONS BY:
DARKGuy
-> Separated the stuff in a .h and .cpp file, adapted it to GP3D's coding style
-> TODO: Make some general functions, as these are some that Wybiral wrote for his
   MD2-loading routines

===================================================================================
This is the file input/output functions file.
===================================================================================
CHANGELOG:

0.0.3:
-> First code release
===================================================================================
*/

#include "gp3d.h"
#include "fileio.h"

using namespace std;

namespace gp {

	// Read char from ifstream (1 byte)
	unsigned char readChr(ifstream &thisFile){
		char buffer;
		thisFile.get(buffer);
		return buffer;
	}

	// Read word from ifstream (2 bytes)
	int readWrd(ifstream &thisFile){
		int buffer;
		thisFile.read((char *)(&buffer), 2);
		return buffer;
	}

	// Read integer from ifstream (4 bytes)
	int readInt(ifstream &thisFile){
		int buffer;
		thisFile.read((char *)(&buffer), 4);
		return buffer;
	}

	// Read float from ifstream (4 bytes)
	float readFlt(ifstream &thisFile){
		float buffer;
		thisFile.read((char *)(&buffer), 4);
		return buffer;
	}

	// Read string from ifstream (bytes specified)
	string readStr(ifstream &thisFile, int length){
		char buffer[length];
		thisFile.read(buffer, length);
		return buffer;
	}

}
