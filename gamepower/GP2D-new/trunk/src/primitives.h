#ifndef PRIMITIVES_H_
#define PRIMITIVES_H_

#include "gp2d.h"
#include <deque>
using namespace std;

//Note: LineWidth may not work with certain graphic cards
namespace gp {
    class GPVector;

    int prepareGL(GLfloat x, GLfloat y, GLfloat a_Angle);

    int SquareRGBA(GLfloat x, GLfloat y, int SideLength, GLfloat a_Angle, GLfloat R, GLfloat G, GLfloat B, GLfloat A);

    int filledSquareRGBA(GLfloat x, GLfloat y, int SideLength, GLfloat a_Angle, GLfloat R, GLfloat G, GLfloat B, GLfloat A);
    
    int PolygonRGBA(GLfloat x, GLfloat y, deque <GPVector> polygon, GLfloat a_Scale, GLfloat a_Angle, int LineWidth, GLfloat R, GLfloat G, GLfloat B, GLfloat A);
    
    int filledPolygonRGBA(GLfloat x, GLfloat y, deque <GPVector> polygon, GLfloat a_Scale, GLfloat a_Angle, int LineWidth, GLfloat R, GLfloat G, GLfloat B, GLfloat A);
    
    int LineRGBA(GLfloat x1, GLfloat y1,GLfloat x2, GLfloat y2, int LineWidth, GLfloat R, GLfloat G, GLfloat B, GLfloat A);
} // namespace gp

#endif // PRIMITIVES_H_
