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

MD2 FUNCTIONS FILE (version 0.0.3)
BY WYBIRAL
-> TODO: Remove the STL templates/vectors for optimization

MODIFICATIONS BY:
DARKGuy
-> Separated the stuff in a .h and .cpp file, adapted it to GP3D's coding style

===================================================================================
This is the MD2 functions file.
===================================================================================
CHANGELOG:

0.0.3:
-> First code release
===================================================================================
*/

#include "../gp3d.h"
#include "../3dmath.h"
#include "md2.h"

using namespace std;

namespace gp {

	texCoord::texCoord(float S, float T) {
		t[0] = S; t[1] = T;
	}

	modelFace::modelFace(int a, int b, int c, int d, int e, int f){
		v[0] = a; v[1] = b; v[2] = c;
		t[0] = d; t[1] = e; t[2] = f;
	}


	void MD2::addTexture(string textureSrc){
		textures.push_back(LoadTexture(textureSrc.c_str()));
	}
	// Push a texture coord to the vector from a T,S coord
	void MD2::addTexCoord(float s, float t){
		texCoords.push_back(texCoord(s, t));
	}
	// Push a face to the vector using (vertIndex 1-3, texCoordIndex 1-3)
	void MD2::addFace(int a, int b, int c, int d, int e, int f){
		faces.push_back(modelFace(a, b, c, d, e, f));
	}
	// Increase the frame count for push new frame attributes
	void MD2::addFrame(){
		frames.push_back(modelFrame());
	}
	// Push a vertex into the current frame (x, y, z)
	void MD2::addVertex(float x, float y, float z){
		frames.back().verts.push_back(vec3(x, y, z));
	}
	// Push a normal index to the current frame
	// Normals are pulled from an index array of normal X,Y,Z's
	void MD2::addNormal(char i){
		frames.back().norms.push_back(i);
	}
	void MD2::addToSequence(int frame){
		if(frame>=0 && frame<frames.size()){ animSequence.push_back( frame ); }
		else {
			printf("Attempt to add frame #%i failed!\n",frame);
			printf("Model only contains frame 0 to %i !\n",frames.size()-1);
			exit(1);
		}
	}
	// Render a single model frame (no interpolation)
	void MD2::renderFrame(int frame){
		glBindTexture(GL_TEXTURE_2D, textures[0]);
		glBegin(GL_TRIANGLES);
		for(int f=0; f<faces.size(); f++){
//			glNormal3fv(frames[frame].norms[faces[f].v[0]]);
			glTexCoord2fv(texCoords[faces[f].t[0]].t);
			glVertex3fv(frames[frame].verts[faces[f].v[0]].v);
//			glNormal3fv(frames[frame].norms[faces[f].v[1]]);
			glTexCoord2fv(texCoords[faces[f].t[1]].t);
			glVertex3fv(frames[frame].verts[faces[f].v[1]].v);
//			glNormal3fv(frames[frame].norms[faces[f].v[2]]);
			glTexCoord2fv(texCoords[faces[f].t[2]].t);
			glVertex3fv(frames[frame].verts[faces[f].v[2]].v);
		}
		glEnd();
	}

	void MD2::animateRender(float speed){
		if(startFrame>=animSequence.size()){startFrame=0;}
		int nextFrame = startFrame+1;
		if(nextFrame>=animSequence.size()){nextFrame=0;}

		vec3 v1, v2, v3;

		glBindTexture(GL_TEXTURE_2D, textures[0]);
		glBegin(GL_TRIANGLES);
		for(int f=0; f<faces.size(); f++){
			v1=frames[animSequence[startFrame]].verts[faces[f].v[0]] * (1.0-frameFactor);
			v1+=frames[animSequence[nextFrame]].verts[faces[f].v[0]] * frameFactor;
			v2=frames[animSequence[startFrame]].verts[faces[f].v[1]] * (1.0-frameFactor);
			v2+=frames[animSequence[nextFrame]].verts[faces[f].v[1]] * frameFactor;
			v3=frames[animSequence[startFrame]].verts[faces[f].v[2]] * (1.0-frameFactor);
			v3+=frames[animSequence[nextFrame]].verts[faces[f].v[2]] * frameFactor;
//			glNormal3fv(frames[f].norms[faces[f].v[0]]);
			glTexCoord2fv(texCoords[faces[f].t[0]].t);
			glVertex3fv(v1.v);
//			glNormal3fv(frames[f].norms[faces[f].v[1]]);
			glTexCoord2fv(texCoords[faces[f].t[1]].t);
			glVertex3fv(v2.v);
//			glNormal3fv(frames[f].norms[faces[f].v[2]]);
			glTexCoord2fv(texCoords[faces[f].t[2]].t);
			glVertex3fv(v3.v);
		}
		glEnd();
		frameFactor+=speed;
		if(frameFactor>1){frameFactor=0; startFrame++; }
	}


	void LoadMD2(MD2 &thisModel, string modelSrc){
		ifstream modelFile(modelSrc.c_str());
		// Read MD2 header
		const int ident      = readInt(modelFile);
		const int version    = readInt(modelFile);
		const int skinwidth  = readInt(modelFile); // Width of skin texture (pixels)
		const int skinheight = readInt(modelFile); // Height of skin texture (pixels)
		const int framesize  = readInt(modelFile);
		const int num_skins  = readInt(modelFile); // Skins
		const int num_xyz    = readInt(modelFile); // Vertices (x, y, z)
		const int num_st     = readInt(modelFile); // Texture coordinates (s, t)
		const int num_tris   = readInt(modelFile); // Triangles
		const int num_glcmds = readInt(modelFile); // GL Commands (which we aren't going to use)
		const int num_frames = readInt(modelFile); // Frames
		const int ofs_skins  = readInt(modelFile); // Skins
		const int ofs_st     = readInt(modelFile); // Texture coordinates (s,t)
		const int ofs_tris   = readInt(modelFile); // Triangles
		const int ofs_frames = readInt(modelFile); // Frames
		const int ofs_glcmds = readInt(modelFile); // GL Commands
		const int ofs_end    = readInt(modelFile); // End of file
		// Load skin file paths into array
		// The paths are in strings of 64 bytes...
		modelFile.seekg(ofs_skins, ios::beg);
		for(int i=0; i<num_skins; i++){
		 thisModel.addTexture(readStr(modelFile, 64));
		}
		// Load texture (s,t) coordinates into array
		// Actual (s,t) = (s/width, t/height)
		unsigned char t, s;
		modelFile.seekg(ofs_st, ios::beg);
		for(int i=0; i<num_st; i++){
			t = readWrd(modelFile);
			s = readWrd(modelFile);
			thisModel.addTexCoord((float)t/skinwidth, (float)s/skinheight);
		}
		// Load triangles vert and st indexs into arrays
		int v1, v2, v3;
		int t1, t2, t3;
		modelFile.seekg(ofs_tris, ios::beg);
		for(int i=0; i<num_tris; i++){
			v1 = readWrd(modelFile); v2 = readWrd(modelFile); v3 = readWrd(modelFile);
			t1 = readWrd(modelFile); t2 = readWrd(modelFile); t3 = readWrd(modelFile);
			thisModel.addFace(v1, v2, v3, t1, t2, t3);
		}
		// Load frames
		float data_scale[3];
		float data_translate[3];
		string data_name;
		// Temporary storage for vert x,y,z
		float x, y, z;
		char norm;
		modelFile.seekg(ofs_frames, ios::beg);
		for(int i=0; i<num_frames; i++){
			thisModel.addFrame();
			// Load frame scale
			data_scale[0] = readFlt(modelFile);
			data_scale[1] = readFlt(modelFile);
			data_scale[2] = readFlt(modelFile);
			// Load frame translate
			data_translate[0] = readFlt(modelFile);
			data_translate[1] = readFlt(modelFile);
			data_translate[2] = readFlt(modelFile);
			// Load frame name (we don't need this, it's just for skipping the bytes)
			data_name = readStr(modelFile, 16);
			// Load vertices and normal index
			for(int v=0; v<num_xyz; v++){
				// Load vertex
				x=(float)readChr(modelFile)*data_scale[0] + data_translate[0];
				y=(float)readChr(modelFile)*data_scale[1] + data_translate[1];
				z=(float)readChr(modelFile)*data_scale[2] + data_translate[2];
				thisModel.addVertex(x, y, z);
				// Load normal index for vertex
				norm = readChr(modelFile);
				thisModel.addNormal(norm);
			}
		}
	}

}
