#include <iostream>
#include <GP2D/gp2d.h>

using namespace std;
using namespace gp2d;

bool quit = false;
bool moveleft = false;
bool moveright = false;
bool moveup = false;
bool movedown = false;

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

/**
 * Main main main.
 */
int main (int argc, char*argv[])
{
    GP2DEngine* engine = GP2DEngine::getInstance();
    engine->initAll();

    GP2DWindow* window = GP2DWindow::getInstance();
    window->setRenderMode(GP2DWindow::GP2D_OPENGL);
    window->setWindowTitle("Gamepower 2D Testing App");
    window->createWindow(1024, 768, 24);
    window->setGraphicsDefaults();
    window->createNewCamera();

    GP2DCamera* cam = window->getCamera();
    cam->setPosition(100.0f, 100.0f);

    GP2DInputHandler* handler = new GP2DInputHandler();
    handler->registerKeyAction(GP2DKeyEvent::GP2D_KEY_ESCAPE, new ExitAction());
    handler->registerGlobalKeyAction(new AllAction());

    GP2DTexture* texSusi = new GP2DTexture("susi.png");
    GP2DTexture* texTerrain = new GP2DTexture("terrain.png");

    GP2DSprite* sprSusi1 = new GP2DSprite(texSusi);
    GP2DSprite* sprTerrain = new GP2DSprite(texTerrain);

    sprSusi1->setPosition(-0.0f, 0.0f);
    //formerly called createAnimation()
    sprSusi1->createAnim(2,2);
    //formerly called setLoop();
    sprSusi1->setAnimLoop(true);

    while(!quit) {
        handler->handleInputEvents();
        window->clearScreen();

        GP2DObject* objToMove = sprSusi1;
        cam->setPosition(objToMove->getX(), objToMove->getY());

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
        //sprSusi1->setNextFrame();
        sprSusi1->setAnimNextFrame();

        sprSusi1->draw();

        window->sync();

        SDL_Delay(10);
    }

     engine->shutdownAll();

   return EXIT_SUCCESS;
}
