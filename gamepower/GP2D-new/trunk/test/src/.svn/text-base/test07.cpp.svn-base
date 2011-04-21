#include <iostream>
#include "gp2d.h"

using namespace std;
using namespace gp;

bool quit = false;
bool moveleft = false;
bool moveright = false;
bool moveup = false;
bool movedown = false;

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

/**
 * Main main main.
 */
int main (int argc, char*argv[])
{
    GPEngine* engine = GPEngine::getInstance();
    engine->initAll();

    GPWindow* window = GPWindow::getInstance();
    window->setRenderMode(GPWindow::GP_OPENGL);
    window->setWindowTitle("Gamepower 2D Testing App");
    window->createWindow(1024, 768, 24);
    window->setGraphicsDefaults();
//    window->createNewCamera();
//
//    GPCamera* cam = window->getCamera();
//    cam->setPosition(100.0f, 100.0f);

    GPKeyboardHandler* handler = new GPKeyboardHandler();
    handler->registerKeyAction(GPKeyEvent::GP_KEY_ESCAPE, new ExitAction());
    GPInputProcessor* proc = new GPInputProcessor();
    proc->addHandler(handler);

    GPTexture* texSusi = new GPTexture("susi.png");
    GPTexture* texTerrain = new GPTexture("terrain.png");

    GPSprite* sprSusi1 = new GPSprite(texSusi);
    GPSprite* sprTerrain = new GPSprite(texTerrain);

    sprSusi1->setPosition(-0.0f, 0.0f);
//    sprSusi1->createAnim(2,2);
    sprSusi1->setAnimLoop(true);

    while(!quit) {
        proc->pollEvents();
        window->clearScreen();

        GPObject* objToMove = sprSusi1;
//        cam->setPosition(objToMove->getX(), objToMove->getY());

        if(moveleft) {
            objToMove->setX(objToMove->getX() - 1);
        }
        if(moveright) {
            objToMove->setX(objToMove->getX() + 1);
        }
        if(movedown) {
            objToMove->setY(objToMove->getY() - 1);
        }
        if(moveup) {
            objToMove->setY(objToMove->getY() + 1);
        }

        sprTerrain->draw();

        SDL_Delay(500);
        sprSusi1->setAnimNextFrame();

        sprSusi1->draw();

        window->sync();

        SDL_Delay(10);
    }

     engine->shutdownAll();

   return EXIT_SUCCESS;
}
