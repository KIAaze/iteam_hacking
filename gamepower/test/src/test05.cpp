#include <iostream>
#include "gp2d.h"
using namespace std;
using namespace gp;

bool quit = false;
bool moveleft = false;
bool moveright = false;
bool moveup = false;
bool movedown = false;
bool coll = false;

GPFont* font;


class CollisionChecker : public GPCollisionEvent {
public:
    void collided(GPCollision& collision) { coll = true; }
};

class AllAction : public GPKeyAction {
public:
    AllAction() {}
    ~AllAction() {}

    void keyDown(GPKeyEvent& event) {
         GPKeyEvent::GPKey key = event.getKey();
         if (key == GPKeyEvent::GP_KEY_LEFT) {
             moveleft = true;
         } else if(key == GPKeyEvent::GP_KEY_RIGHT) {
             moveright = true;
         } else if(key == GPKeyEvent::GP_KEY_DOWN) {
             movedown = true;
         } else if(key == GPKeyEvent::GP_KEY_UP) {
             moveup = true;
         }
    }

    void keyUp(GPKeyEvent& event) {
         GPKeyEvent::GPKey key = event.getKey();
         if (key == GPKeyEvent::GP_KEY_LEFT) {
             moveleft = false;
         } else if(key == GPKeyEvent::GP_KEY_RIGHT) {
             moveright = false;
         } else if(key == GPKeyEvent::GP_KEY_DOWN) {
             movedown = false;
         } else if(key == GPKeyEvent::GP_KEY_UP) {
             moveup = false;
         }
    }
};

class ExitAction : public GPKeyAction {
public:
    ExitAction() {}
    ~ExitAction() {}

    void keyDown(GPKeyEvent& event) {
        cout << "Exiting" << endl;
        quit = true;
    }
};

int main (int argc, char*argv[])
{
    GPEngine* engine = GPEngine::getInstance();
    engine->initAll();

    GPWindow* window = GPWindow::getInstance();
    window->setRenderMode(GPWindow::GP_OPENGL);
    window->setWindowTitle("Gamepower 2D Testing App 5");
    window->createWindow(1024, 768, 24);
    window->setGraphicsDefaults();

    GPGameCamera* cam = new GPGameCamera(window->getHeight() / 2);
    cam->setPosition(-0.0f, -0.0f);

    GPKeyboardHandler* handler = new GPKeyboardHandler();
    handler->registerKeyAction(GPKeyEvent::GP_KEY_ESCAPE, new ExitAction());
    GPInputProcessor* proc = new GPInputProcessor();
    proc->addHandler(handler);

    GPTexture* texSphere = new GPTexture("sphere.png");

    GPSprite* sphere1 = new GPSprite(texSphere);
    GPSprite* sphere2 = new GPSprite(texSphere);
    sphere1->setPosition(0.0f, 0.0f);
    sphere1->setWidth(128);
    sphere1->setHeight(128);

    sphere2->setPosition(180.0f, 180.0f);
    sphere2->setWidth(128);
    sphere2->setHeight(128);

    font = new GPFont("font.ttf", 24);
    GPText* text1 = new GPText(font);
    text1->setRenderType(GPText::GP_RENDER_NICEST);
    text1->setZ(12);
    text1->setX(0);
    text1->setY(0);

    GPCollisionManager* collMgr = new GPCollisionManager();
    GPBoundsCollision* pixcoll = new GPBoundsCollision(*sphere1, *sphere2);
    collMgr->addCollision(pixcoll);
    collMgr->registerEvent(new CollisionChecker());

    while(!quit) {
        proc->pollEvents();
        window->clearScreen();

        GPObject* objToMove = sphere1;
        //cam->setPosition(objToMove->getX(), objToMove->getY());

        if(moveleft)  { objToMove->setX(objToMove->getX() - 1); }
        if(moveright) { objToMove->setX(objToMove->getX() + 1); }
        if(movedown)  { objToMove->setY(objToMove->getY() + 1); }
        if(moveup)    { objToMove->setY(objToMove->getY() - 1); }

			sphere1->draw();
			sphere2->draw();

			coll=false;
        collMgr->handleCollisions();
        if(coll==false){
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
