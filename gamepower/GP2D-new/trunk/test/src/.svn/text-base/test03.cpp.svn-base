#include <iostream>
#include "gp2d.h"
using namespace std;
using namespace gp;

bool quit = false;
bool moveleft = false;
bool moveright = false;
bool moveup = false;
bool movedown = false;

GPFont* font;

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
    window->setWindowTitle("Gamepower 2D Testing App");
    window->createWindow(1024, 768, 24);
    window->setGraphicsDefaults();

    GPKeyboardHandler* handler = new GPKeyboardHandler();
    handler->registerKeyAction(GPKeyEvent::GP_KEY_ESCAPE, new ExitAction());
    handler->registerGenericKeyAction(new AllAction());

    GPInputProcessor* proc = new GPInputProcessor();
    proc->addHandler(handler);

    GPGameCamera* cam = new GPGameCamera(window->getHeight() / 2);

    cam->setPosition(0.0f, 0.0f);

    GPTexture* texSusi = new GPTexture("susi.png");
    GPSprite* sprSusi1 = new GPSprite(texSusi);
    GPSprite* sprSusi2 = new GPSprite(texSusi);
    sprSusi1->setPosition(0.0f, 0.0f);
    sprSusi2->setPosition(100.0f, 100.0f);

    font = new GPFont("font.ttf", 12);
    GPText* text1 = new GPText(font);
    GPText* text2 = new GPText(font);
    text1->setRenderType(GPText::GP_RENDER_NICEST);
    text1->setX(0);
    text1->setY(0);
    text1->setZ(12);
    text2->setRenderType(GPText::GP_RENDER_NICEST);
    text2->setX(0);
    text2->setY(14);
    text2->setZ(12);
    text1->setText("Hi 1");
    text2->setText("Hi 2");

    while(!quit) {
        proc->pollEvents();
        window->clearScreen();

        GPObject* objToMove = sprSusi1;
//         cam->setPosition(objToMove->getX(), objToMove->getY());

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

        sprSusi1->draw();
        sprSusi2->draw();

			text1->setX(cam->getX()-(window->getWidth()/2));
			text1->setY(cam->getY()+(window->getHeight()/2));
			text2->setX(cam->getX()-(window->getWidth()/2));
			text2->setY(cam->getY()+(window->getHeight()/2)-12);
//         text1->setText("Camera X: %i - Camera Y: %i",(int)cam->getX(),(int)cam->getY());
//         text2->setText("Player X: %i - Player Y: %i",(int)sprSusi1->getX(),(int)sprSusi1->getY());
//         text1->draw();
//         text2->draw();

        window->sync();
        SDL_Delay(10);
    }

     engine->shutdownAll();

   return EXIT_SUCCESS;
}
