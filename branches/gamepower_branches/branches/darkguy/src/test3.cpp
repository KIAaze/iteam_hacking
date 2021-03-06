#include <iostream>

#include "gp2d.h"

using namespace gp2d;
using namespace std;

bool quit = false;
bool moveleft = false;
bool moveright = false;
bool moveup = false;
bool movedown = false;
bool coll = false;

GP2DFont* font;

class AllAction : public GP2DKeyAction {
public:
    AllAction() {}
    ~AllAction() {}

    void keyDown(GP2DKeyEvent& event) {
         GP2DKeyEvent::GP2DKey key = event.getKey();
         if (key == GP2DKeyEvent::GP2D_KEY_LEFT) {
             moveleft = true;
         } else if(key == GP2DKeyEvent::GP2D_KEY_RIGHT) {
             moveright = true;
         } else if(key == GP2DKeyEvent::GP2D_KEY_DOWN) {
             movedown = true;
         } else if(key == GP2DKeyEvent::GP2D_KEY_UP) {
             moveup = true;
         }
    }

    void keyUp(GP2DKeyEvent& event) {
         GP2DKeyEvent::GP2DKey key = event.getKey();
         if (key == GP2DKeyEvent::GP2D_KEY_LEFT) {
             moveleft = false;
         } else if(key == GP2DKeyEvent::GP2D_KEY_RIGHT) {
             moveright = false;
         } else if(key == GP2DKeyEvent::GP2D_KEY_DOWN) {
             movedown = false;
         } else if(key == GP2DKeyEvent::GP2D_KEY_UP) {
             moveup = false;
         }
    }
};

class ExitAction : public GP2DKeyAction {
public:
    ExitAction() {}
    ~ExitAction() {}

    void keyDown(GP2DKeyEvent& event) {
        cout << "Exiting" << endl;
        quit = true;
    }
};

int main (int argc, char*argv[])
{
    GP2DEngine* engine = GP2DEngine::getInstance();
    engine->initAll();

    GP2DWindow* window = GP2DWindow::getInstance();
    window->setRenderMode(GP2DWindow::GP2D_OPENGL);
    window->setWindowTitle("Gamepower 2D Testing App 3");
    window->createWindow(800, 600, 16);
    window->setGraphicsDefaults();

    GP2DGameCamera* cam = new GP2DGameCamera(window->getHeight() / 2);
    cam->setPosition(-0.0f, -0.0f);

    GP2DInputHandler* handler = new GP2DInputHandler();
    handler->registerKeyAction(GP2DKeyEvent::GP2D_KEY_ESCAPE, new ExitAction());
    handler->registerGlobalKeyAction(new AllAction());

    GP2DTexture* texPolygon = new GP2DTexture("polygon.png");

    GP2DSprite* polygon1 = new GP2DSprite(texPolygon);
    GP2DSprite* polygon2 = new GP2DSprite(texPolygon);
    polygon1->setPosition(0.0f, 0.0f);
    polygon1->setWidth(128);
    polygon1->setHeight(128);
	

    polygon2->setPosition(180.0f, 180.0f);
    polygon2->setWidth(128);
    polygon2->setHeight(128);

    font = new GP2DFont("font.ttf", 24);
    GP2DText* text1 = new GP2DText(font);
    text1->setRenderType(GP2DText::GP2D_RENDER_NICEST);
    text1->setZ(12);
    text1->setX(0);
    text1->setY(0);
    
    GP2DPhysWorld* world = new GP2DPhysWorld(5000, 5000);
    world->addObject(128.0f, 128.0f, 1.0f, CONVEX_POLYGON, texPolygon, 0.0f, 0.0f);
    world->Objects[0]->addPoint(0.0f, 0.0f);
    world->Objects[0]->addPoint(128.0f, 0.0f);
    world->Objects[0]->addPoint(128.0f, 128.0f);
    world->Objects[0]->addPoint(0.0f, 128.0f);
    world->Objects[0]->buildEdges(); // VERY IMPORTANT
    world->addObject(128.0f, 128.0f, 1.0f, CONVEX_POLYGON, texPolygon, 180.0f, 180.0f);
    world->Objects[1]->addPoint(180.0f, 0.0f);
    world->Objects[1]->addPoint(308.0f, 0.0f);
    world->Objects[1]->addPoint(308.0f, 308.0f);
    world->Objects[1]->addPoint(0.0f, 180.0f);
    world->Objects[1]->buildEdges();

    while(!quit) {
        handler->handleInputEvents();
        window->clearScreen();

        GP2DObject* objToMove = polygon1;
        // cam->setPosition(objToMove->getX(), objToMove->getY());

        if(moveleft)  { objToMove->setX(objToMove->getX() - 1); world->Objects[0]->setCoordX(- 1); }
        if(moveright) { objToMove->setX(objToMove->getX() + 1); world->Objects[0]->setCoordX(+ 1); }
        if(movedown)  { objToMove->setY(objToMove->getY() - 1); world->Objects[0]->setCoordY(- 1); }
        if(moveup)    { objToMove->setY(objToMove->getY() + 1); world->Objects[0]->setCoordY(+ 1); }
		
		glBegin(GL_LINES);
			glVertex2f(world->Objects[0]->Points[0]->x , world->Objects[0]->Points[0]->y);
			glVertex2f(world->Objects[0]->Points[1]->x , world->Objects[0]->Points[1]->y);
		
			glVertex2f(world->Objects[0]->Points[0]->x , world->Objects[0]->Points[0]->y);		
			glVertex2f(world->Objects[0]->Points[3]->x , world->Objects[0]->Points[3]->y);
		
			glVertex2f(world->Objects[0]->Points[1]->x , world->Objects[0]->Points[1]->y);
			glVertex2f(world->Objects[0]->Points[2]->x , world->Objects[0]->Points[2]->y);

			glVertex2f(world->Objects[0]->Points[2]->x , world->Objects[0]->Points[2]->y);
			glVertex2f(world->Objects[0]->Points[3]->x , world->Objects[0]->Points[3]->y);
		glEnd();
		
		glPointSize(10.0f);
		glBegin(GL_POINTS);
			glVertex2f(world->Objects[0]->Points[0]->x , world->Objects[0]->Points[0]->y);
			glVertex2f(world->Objects[0]->Points[1]->x , world->Objects[0]->Points[1]->y);
			glVertex2f(world->Objects[0]->Points[2]->x , world->Objects[0]->Points[2]->y);
			glVertex2f(world->Objects[0]->Points[3]->x , world->Objects[0]->Points[3]->y);
		glEnd();

		glBegin(GL_LINES);
			glVertex2f(world->Objects[1]->Points[0]->x , world->Objects[1]->Points[0]->y);
			glVertex2f(world->Objects[1]->Points[1]->x , world->Objects[1]->Points[1]->y);
		
			glVertex2f(world->Objects[1]->Points[0]->x , world->Objects[1]->Points[0]->y);		
			glVertex2f(world->Objects[1]->Points[3]->x , world->Objects[1]->Points[3]->y);
		
			glVertex2f(world->Objects[1]->Points[1]->x , world->Objects[1]->Points[1]->y);
			glVertex2f(world->Objects[1]->Points[2]->x , world->Objects[1]->Points[2]->y);

			glVertex2f(world->Objects[1]->Points[2]->x , world->Objects[1]->Points[2]->y);
			glVertex2f(world->Objects[1]->Points[3]->x , world->Objects[1]->Points[3]->y);
		glEnd();

		glBegin(GL_POINTS);
			glVertex2f(world->Objects[1]->Points[0]->x , world->Objects[1]->Points[0]->y);
			glVertex2f(world->Objects[1]->Points[1]->x , world->Objects[1]->Points[1]->y);
			glVertex2f(world->Objects[1]->Points[2]->x , world->Objects[1]->Points[2]->y);
			glVertex2f(world->Objects[1]->Points[3]->x , world->Objects[1]->Points[3]->y);
		glEnd();

		// polygon1->draw();
		// polygon2->draw();

		coll = world->isColliding(world->Objects[0], world->Objects[1]);
        if(coll == false){
        		text1->setText("Not colliding");
        } else {
        		text1->setText("Colliding!");
        }
        text1->draw();
		

        window->sync();
        SDL_Delay(10);
    }

     engine->shutdownAll();

   return EXIT_SUCCESS;
}

