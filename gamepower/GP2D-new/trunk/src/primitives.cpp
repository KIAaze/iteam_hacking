#include "primitives.h"

namespace gp {

    int prepareGL(GLfloat x, GLfloat y, GLfloat a_Angle) {
      glMatrixMode(GL_MODELVIEW);
      glLoadIdentity();
      glTranslatef(x,y,0);
    
/*      glRotatef(getRotation_X(), 1.0f, 0.0f, 0.0f);
      glRotatef(getRotation_Y(), 0.0f, 1.0f, 0.0f);*/
      glRotatef(a_Angle, 0.0f, 0.0f, 1.0f);

      // blending function, used to make alpha parts transparent or some sort.
      glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
      glEnable(GL_BLEND);
      // enable alpha
      glAlphaFunc(GL_GREATER, 0.1f);
      glEnable(GL_ALPHA_TEST);
      return(0);
    }
    
    int SquareRGBA(GLfloat x, GLfloat y, int SideLength, GLfloat a_Angle, GLfloat R, GLfloat G, GLfloat B, GLfloat A) {
      prepareGL(x,y,a_Angle);
    
      GLfloat size=SideLength/2.0;
      glBegin(GL_LINES);                  // Start Drawing Quads
          glColor4f(R,G,B,A);              // Set The Color
          glVertex2f(-size,size);          // (Top Left)
          glVertex2f(size,size);          // (Top Right)
          glVertex2f(size,-size);          // (Bottom Right)
          glVertex2f(-size,-size);          // (Bottom Left)
      glEnd();                        // Done Drawing A Quad
      return(0);
    }

    int filledSquareRGBA(GLfloat x, GLfloat y, int SideLength, GLfloat a_Angle, GLfloat R, GLfloat G, GLfloat B, GLfloat A) {
      prepareGL(x,y,a_Angle);
    
      GLfloat size=SideLength/2.0;
      glBegin(GL_QUADS);                  // Start Drawing Quads
          glColor4f(R,G,B,A);              // Set The Color
          glVertex2f(-size,size);          // (Top Left)
          glVertex2f(size,size);          // (Top Right)
          glVertex2f(size,-size);          // (Bottom Right)
          glVertex2f(-size,-size);          // (Bottom Left)
      glEnd();                        // Done Drawing A Quad
      return(0);
    }
    
    int PolygonRGBA(GLfloat x, GLfloat y, deque <GPVector> polygon, GLfloat a_Scale, GLfloat a_Angle, int LineWidth, GLfloat R, GLfloat G, GLfloat B, GLfloat A) {
      prepareGL(x,y,a_Angle);
    
      int N=polygon.size();
      glPointSize(LineWidth);
      glBegin(GL_LINES);
        glColor4f(R,G,B,A);              // Set The Color
        for(int i=0;i<N;i++) {
          glVertex2f(a_Scale*polygon[i].getX(),a_Scale*polygon[i].getY());
          glVertex2f(a_Scale*polygon[(i+1)%N].getX(),a_Scale*polygon[(i+1)%N].getY());
        }
      glEnd();
      return(0);
    }
    
    int filledPolygonRGBA(GLfloat x, GLfloat y, deque <GPVector> polygon, GLfloat a_Scale, GLfloat a_Angle, int LineWidth, GLfloat R, GLfloat G, GLfloat B, GLfloat A) {
      prepareGL(x,y,a_Angle);
    
      int N=polygon.size();
      glPointSize(LineWidth);
      glBegin(GL_POLYGON);
        glColor4f(R,G,B,A);              // Set The Color
        for(int i=0;i<N;i++) glVertex2f(a_Scale*polygon[i].getX(),a_Scale*polygon[i].getY());
      glEnd();
      return(0);
    }
    
    int LineRGBA(GLfloat x1, GLfloat y1,GLfloat x2, GLfloat y2, int LineWidth, GLfloat R, GLfloat G, GLfloat B, GLfloat A) {
      prepareGL(0,0,0);
    
      glPointSize(LineWidth);
      glBegin(GL_LINES);
          glColor4f(R,G,B,A);              // Set The Color
          glVertex2f(x1,y1);
          glVertex2f(x2,y2);
      glEnd();
      return(0);
    }
}
