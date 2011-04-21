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

MD2 HEADER FILE (version 0.0.3)
BY WYBIRAL
-> TODO: Remove the STL templates/vectors for optimization

MODIFICATIONS BY:
DARKGuy
-> Separated the stuff in a .h and .cpp file, adapted it to GP3D's coding style

===================================================================================
This is the MD2 header file.
===================================================================================
CHANGELOG:

0.0.3:
-> First code release
===================================================================================
*/

#ifndef _GP3D_MD2_H
#define _GP3D_MD2_H
#include <fstream>
#include <string>
#include <vector>

using namespace std;

namespace gp {

	// Texture coord class
	class texCoord {
		public:
		float t[2];
		texCoord(float, float);
	};

	// Model frame class
	class modelFrame {
		public:
		vector<vec3> verts;
		vector<char> norms;
	};

	// Face class (stores vert index and texcoord index)
	class modelFace {
		public:
		int v[3];
		int t[3];
		modelFace(int, int, int, int, int, int);
	};

	// Model class
	class MD2 {
		public:
		vector<int> textures;       // GLint vector for texture handles
		vector<modelFace> faces;    // Model face vector (vector of face-vert index's and face-texcoord index's
		vector<modelFrame> frames;  // Model frame vector (vector of indexed vertices and normal index's
		vector<texCoord> texCoords; // Tex coord vector (vector of T,S data)
		vector<int> animSequence;   // Animation sequence vector (stores looping sequence of current animation by frame index's)
		int startFrame;             // Start frame, the previous or "base" frame
		float frameFactor;          // Frame factor, the percent between start frame and next frame
		int texture;                // Index of currently active texture

		void addTexture(string textureSrc); 			// Push a texture to the texture vector from a file source (C++ string)
		void addTexCoord(float, float);					// Push a texture coord to the vector from a T,S coord
		void addFace(int, int, int, int, int, int);	// Push a face to the vector using (vertIndex 1-3, texCoordIndex 1-3)
		void addFrame();										// Increase the frame count for push new frame attributes
		void addVertex(float, float, float);			// Push a vertex into the current frame (x, y, z)
		void addNormal(char);								// Push a normal index to the current frame
		void addToSequence(int);							// Adds a frame to the animation sequence
		void renderFrame(int);								// Renders a single frame
		void animateRender(float);							// Renders the animation
	};

	void LoadMD2(MD2&, string);

}

#endif
