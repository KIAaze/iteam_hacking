#include <iostream>
#include "gp2d.h"
#ifndef CALLBACK
#define CALLBACK
#endif

using namespace std;
using namespace gp;

bool quit = false;

GPEngine* engine = NULL;
GPWindow* window = NULL;
GPGuiCamera* camGui = NULL;
GPGameCamera* camGame = NULL;
GPInputHandler* handler = NULL;
GPFramerate* framerater = NULL;

class ExitAction : public GPKeyAction {
public:
    ExitAction() {}
    ~ExitAction() {}
    void keyDown(GPKeyEvent& event) {
        cout << "Exiting" << endl;
        quit = true;
    }
};





// CALLBACK functions for GLU_TESS ////////////////////////////////////////////
// NOTE: must be declared with CALLBACK directive
void CALLBACK tessBeginCB(GLenum which);
void CALLBACK tessEndCB();
void CALLBACK tessErrorCB(GLenum errorCode);
void CALLBACK tessVertexCB(const GLvoid *data);
void CALLBACK tessVertexCB2(const GLvoid *data);
void CALLBACK tessCombineCB(const GLdouble newVertex[3], const GLdouble *neighborVertex[4],
                            const GLfloat neighborWeight[4], GLdouble **outData);

// function declarations //////////////////////////////////////////////////////
GLuint tessellate1();
GLuint tessellate2();
GLuint tessellate3();

GLuint listId1, listId2, listId3;       // IDs of display lists
GLdouble vertices[64][6];               // arrary to store newly created vertices (x,y,z,r,g,b) by combine callback
int vertexIndex = 0;                    // array index for above array incremented inside combine callback









///////////////////////////////////////////////////////////////////////////////
// create a tessellation object and compile a quad into a display list
///////////////////////////////////////////////////////////////////////////////
GLuint tessellate1()
{
    GLuint id = glGenLists(1);  // create a display list
    if(!id) return id;          // failed to create a list, return 0

    GLUtesselator *tess = gluNewTess(); // create a tessellator
    if(!tess) return 0;  // failed to create tessellation object, return 0

    // define concave quad data (vertices only)
    //  0    2
    //  \ \/ /
    //   \3 /
    //    \/
    //    1
    GLdouble quad1[4][3] = { {-1,3,0}, {0,0,0}, {1,3,0}, {0,2,0} };

    // register callback functions
    gluTessCallback(tess, GLU_TESS_BEGIN, (void (CALLBACK *)())tessBeginCB);
    gluTessCallback(tess, GLU_TESS_END, (void (CALLBACK *)())tessEndCB);
    gluTessCallback(tess, GLU_TESS_ERROR, (void (CALLBACK *)())tessErrorCB);
    gluTessCallback(tess, GLU_TESS_VERTEX, (void (CALLBACK *)())tessVertexCB);

    // tessellate and compile a concave quad into display list
    // gluTessVertex() takes 3 params: tess object, pointer to vertex coords,
    // and pointer to vertex data to be passed to vertex callback.
    // The second param is used only to perform tessellation, and the third
    // param is the actual vertex data to draw. It is usually same as the second
    // param, but It can be more than vertex coord, for example, color, normal
    // and UV coords which are needed for actual drawing.
    // Here, we are looking at only vertex coods, so the 2nd and 3rd params are
    // pointing same address.
    glNewList(id, GL_COMPILE);
    glColor3f(1,1,1);
    gluTessBeginPolygon(tess, 0);                   // with NULL data
        gluTessBeginContour(tess);
            gluTessVertex(tess, quad1[0], quad1[0]);
            gluTessVertex(tess, quad1[1], quad1[1]);
            gluTessVertex(tess, quad1[2], quad1[2]);
            gluTessVertex(tess, quad1[3], quad1[3]);
        gluTessEndContour(tess);
    gluTessEndPolygon(tess);
    glEndList();

    gluDeleteTess(tess);        // delete after tessellation

    return id;      // return handle ID of a display list
}



///////////////////////////////////////////////////////////////////////////////
// tessellate a polygon with a hole and compile it into a display list
///////////////////////////////////////////////////////////////////////////////
GLuint tessellate2()
{
    GLuint id = glGenLists(1);  // create a display list
    if(!id) return id;          // failed to create a list, return 0

    GLUtesselator *tess = gluNewTess(); // create a tessellator
    if(!tess) return 0;         // failed to create tessellation object, return 0

    // define concave quad with a hole
    //  0--------3
    //  | 4----7 |
    //  | |    | |
    //  | 5----6 |
    //  1--------2
    GLdouble quad2[8][3] = { {-2,3,0}, {-2,0,0}, {2,0,0}, { 2,3,0},
                             {-1,2,0}, {-1,1,0}, {1,1,0}, { 1,2,0} };

    // register callback functions
    gluTessCallback(tess, GLU_TESS_BEGIN, (void (__stdcall*)(void))tessBeginCB);
    gluTessCallback(tess, GLU_TESS_END, (void (__stdcall*)(void))tessEndCB);
    gluTessCallback(tess, GLU_TESS_ERROR, (void (__stdcall*)(void))tessErrorCB);
    gluTessCallback(tess, GLU_TESS_VERTEX, (void (__stdcall*)())tessVertexCB);

    // tessellate and compile a concave quad into display list
    glNewList(id, GL_COMPILE);
    glColor3f(1,1,1);
    gluTessBeginPolygon(tess, 0);                       // with NULL data
        gluTessBeginContour(tess);                      // outer quad
            gluTessVertex(tess, quad2[0], quad2[0]);
            gluTessVertex(tess, quad2[1], quad2[1]);
            gluTessVertex(tess, quad2[2], quad2[2]);
            gluTessVertex(tess, quad2[3], quad2[3]);
        gluTessEndContour(tess);
        gluTessBeginContour(tess);                      // inner quad (hole)
            gluTessVertex(tess, quad2[4], quad2[4]);
            gluTessVertex(tess, quad2[5], quad2[5]);
            gluTessVertex(tess, quad2[6], quad2[6]);
            gluTessVertex(tess, quad2[7], quad2[7]);
        gluTessEndContour(tess);
    gluTessEndPolygon(tess);
    glEndList();

    gluDeleteTess(tess);        // delete after tessellation

    return id;      // return handle ID of a display list
}



///////////////////////////////////////////////////////////////////////////////
// tessellate a self-intersecting polygon and compile it into a display list
// Note that tessellator will find out the self-intersecting vertex where
// two edge lines are met, and pass it to your combine callback function.
// The combine callback must store the vertex coords into local memory in
// your application and also handle other vertex data, such as color, UVs.
///////////////////////////////////////////////////////////////////////////////
GLuint tessellate3()
{
    GLuint id = glGenLists(1);  // create a display list
    if(!id) return id;          // failed to create a list, return 0

    GLUtesselator *tess = gluNewTess(); // create a tessellator
    if(!tess) return 0;  // failed to create tessellation object, return 0

    GLdouble star[5][6] = { { 0.0, 3.0, 0,  1, 0, 0},       // 0: x,y,z,r,g,b
                            {-1.0, 0.0, 0,  0, 1, 0},       // 1:
                            { 1.6, 1.9, 0,  1, 0, 1},       // 2:
                            {-1.6, 1.9, 0,  1, 1, 0},       // 3:
                            { 1.0, 0.0, 0,  0, 0, 1} };     // 4:

    // register callback functions
    // This polygon is self-intersecting, so GLU_TESS_COMBINE callback function
    // must be registered. The combine callback will process the intersecting vertices.
    gluTessCallback(tess, GLU_TESS_BEGIN, (void (__stdcall*)(void))tessBeginCB);
    gluTessCallback(tess, GLU_TESS_END, (void (__stdcall*)(void))tessEndCB);
    gluTessCallback(tess, GLU_TESS_ERROR, (void (__stdcall*)(void))tessErrorCB);
    gluTessCallback(tess, GLU_TESS_VERTEX, (void (__stdcall*)(void))tessVertexCB2);
    gluTessCallback(tess, GLU_TESS_COMBINE, (void (__stdcall*)(void))tessCombineCB);

    // tessellate and compile a concave quad into display list
    // Pay attention to winding rules if multiple contours are overlapped.
    // The winding rules determine which parts of polygon will be filled(interior)
    // or not filled(exterior). For each enclosed region partitioned by multiple
    // contours, tessellator assigns a winding number to the region by using
    // given winding rule. The default winding rule is GLU_TESS_WINDING_ODD,
    // but, here we are using non-zero winding rule to fill the middle area.
    // BTW, the middle region will not be filled with the odd winding rule.
    gluTessProperty(tess, GLU_TESS_WINDING_RULE, GLU_TESS_WINDING_NONZERO);
    glNewList(id, GL_COMPILE);
    gluTessBeginPolygon(tess, 0);                   // with NULL data
        gluTessBeginContour(tess);
            gluTessVertex(tess, star[0], star[0]);
            gluTessVertex(tess, star[1], star[1]);
            gluTessVertex(tess, star[2], star[2]);
            gluTessVertex(tess, star[3], star[3]);
            gluTessVertex(tess, star[4], star[4]);
        gluTessEndContour(tess);
    gluTessEndPolygon(tess);
    glEndList();

    gluDeleteTess(tess);        // safe to delete after tessellation

    return id;      // return handle ID of a display list
}








///////////////////////////////////////////////////////////////////////////////
// GLU_TESS CALLBACKS
///////////////////////////////////////////////////////////////////////////////
void CALLBACK tessBeginCB(GLenum which)
{
    glBegin(which);
}



void CALLBACK tessEndCB()
{
    glEnd();
}



void CALLBACK tessVertexCB(const GLvoid *data)
{
    // cast back to double type
    const GLdouble *ptr = (const GLdouble*)data;

    glVertex3dv(ptr);
}



///////////////////////////////////////////////////////////////////////////////
// draw a vertex with color
///////////////////////////////////////////////////////////////////////////////
void CALLBACK tessVertexCB2(const GLvoid *data)
{
    // cast back to double type
    const GLdouble *ptr = (const GLdouble*)data;

    glColor3dv(ptr+3);
    glVertex3dv(ptr);
}



///////////////////////////////////////////////////////////////////////////////
// Combine callback is used to create a new vertex where edges intersect.
// In this function, copy the vertex data into local array and compute the
// color of the vertex. And send it back to tessellator, so tessellator pass it
// to vertex callback function.
//
// newVertex: the intersect point which tessellator creates for us
// neighborVertex[4]: 4 neighbor vertices to cause intersection (given from 3rd param of gluTessVertex()
// neighborWeight[4]: 4 interpolation weights of 4 neighbor vertices
// outData: the vertex data to return to tessellator
///////////////////////////////////////////////////////////////////////////////
void CALLBACK tessCombineCB(const GLdouble newVertex[3], const GLdouble *neighborVertex[4],
                            const GLfloat neighborWeight[4], GLdouble **outData)
{
    // copy new intersect vertex to local array
    // Because newVertex is temporal and cannot be hold by tessellator until next
    // vertex callback called, it must be copied to the safe place in the app.
    // Once gluTessEndPolygon() called, then you can safly deallocate the array.
    vertices[vertexIndex][0] = newVertex[0];
    vertices[vertexIndex][1] = newVertex[1];
    vertices[vertexIndex][2] = newVertex[2];

    // compute vertex color with given weights and colors of 4 neighbors
    // the neighborVertex[4] must hold required info, in this case, color.
    // neighborVertex was actually the third param of gluTessVertex() and is
    // passed into here to compute the color of the intersect vertex.
    vertices[vertexIndex][3] = neighborWeight[0] * neighborVertex[0][3] +   // red
                               neighborWeight[1] * neighborVertex[1][3] +
                               neighborWeight[2] * neighborVertex[2][3] +
                               neighborWeight[3] * neighborVertex[3][3];
    vertices[vertexIndex][4] = neighborWeight[0] * neighborVertex[0][4] +   // green
                               neighborWeight[1] * neighborVertex[1][4] +
                               neighborWeight[2] * neighborVertex[2][4] +
                               neighborWeight[3] * neighborVertex[3][4];
    vertices[vertexIndex][5] = neighborWeight[0] * neighborVertex[0][5] +   // blue
                               neighborWeight[1] * neighborVertex[1][5] +
                               neighborWeight[2] * neighborVertex[2][5] +
                               neighborWeight[3] * neighborVertex[3][5];


    // return output data (vertex coords and others)
    *outData = vertices[vertexIndex];   // assign the address of new intersect vertex

    ++vertexIndex;  // increase index for next vertex
}



void CALLBACK tessErrorCB(GLenum errorCode)
{
    const GLubyte *errorStr;

    errorStr = gluErrorString(errorCode);
    cerr << "[ERROR]: " << errorStr << endl;
}






/**
 * Main main main.
 */
int main(int argc, char* argv[]) {
    engine = GPEngine::getInstance();
    engine->initAll();

    window = GPWindow::getInstance();
    window->setRenderMode(GPWindow::GP_OPENGL);
    window->setWindowTitle("Gamepower 2D Testing App");
    window->createWindow(1024, 768, 24);
    window->setGraphicsDefaults();

    handler = new GPInputHandler();
    handler->registerKeyAction(GPKeyEvent::GP_KEY_ESCAPE, new ExitAction());

    framerater = GPFramerate::getInstance();
    framerater->setMin(10);
    framerater->setMax(150);
    framerater->setFps(150);

    camGame = new GPGameCamera();
    camGame->setPosition(0.0f, 0.0f);
	camGame->setRange(5);
	camGame->updateCamera();
    camGui = new GPGuiCamera();
    camGui->setDefaults();

    GPDirector* director = new GPDirector(camGame, camGui);
	
	
    // perform tessellation and compile into display lists
    listId1 = tessellate1();    // a concave quad
    listId2 = tessellate2();    // a quad with a hole in it
    listId3 = tessellate3();    // a self-intersecting star
	
	
    while(!quit) {
        handler->handleInputEvents();
		//window->clearScreen();

        director->useGameCamera();
		
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    glPushMatrix();
    // draw meshes
    glTranslatef(-4, -1.5f,0);
    glCallList(listId1);

    glTranslatef(4,0,0);
    glCallList(listId2);

    glTranslatef(4,0,0);
    glCallList(listId3);
    glPopMatrix();

        // EPIC GUI STUFF SHOULD COME HEREZ0R!
        // director->useGuiCamera();

        window->sync();
        framerater->delay();
    }

    engine->shutdownAll();

    return EXIT_SUCCESS;
}

