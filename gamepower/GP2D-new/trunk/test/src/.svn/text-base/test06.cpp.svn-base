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
    void collided(GPCollision& collision) {
    	coll = true;
    }
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

void drawGrid() {
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(0.5f, 1.0f, 0.5f, 0.2f);
    glBegin(GL_LINES);
        float range = 1000.0f;
        for(float i = -range; i <= range; i += 50) {
            glVertex2f(i, -range);
            glVertex2f(i, range);
            glVertex2f(-range, i);
            glVertex2f(range, i);
        }
    glEnd();

    glColor4f(0.0f, 1.0f, 0.0f, 0.5f);
    glLineWidth(5.0f);
    glBegin(GL_LINES);
        glVertex2f(-range, 0);
        glVertex2f(range, 0);

        glVertex2f(0, -range);
        glVertex2f(0, range);
    glEnd();
}

int main (int argc, char*argv[])
{

    GPEngine* engine = GPEngine::getInstance();
    engine->initAll();

    GPWindow* window = GPWindow::getInstance();
    window->setRenderMode(GPWindow::GP_OPENGL);
    window->setWindowTitle("Gamepower 2D Testing App 6");
    window->createWindow(1024, 768, 32);
    window->setGraphicsDefaults();
    GPGameCamera* cam = new GPGameCamera(window->getHeight() / 2);
    cam->setPosition(0.0f, 0.0f);

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
    GPText* text2 = new GPText(font);
    GPText* text3 = new GPText(font);
    text1->setRenderType(GPText::GP_RENDER_NICEST);
    text2->setRenderType(GPText::GP_RENDER_NICEST);
    text3->setRenderType(GPText::GP_RENDER_NICEST);
    text1->setZ(12);
    text2->setZ(12);
    text3->setZ(12);
    text1->setX(0);
    text1->setY(0);
    text2->setX(0);
    text2->setY(-26);
    text3->setX(0);
    text3->setY(-(26+26));

    GPCollisionManager* collMgr = new GPCollisionManager();
    GPPixelCollision* pixcoll = new GPPixelCollision(*sphere1, *sphere2);
    collMgr->addCollision(pixcoll);
    collMgr->registerEvent(new CollisionChecker());

    while(!quit) {
        proc->pollEvents();
        window->clearScreen();

        GPObject* objToMove = sphere1;
        cam->setPosition(objToMove->getX(), objToMove->getY());
        text2->setText("X: %i",(int)objToMove->getX());
        text3->setText("Y: %i",(int)objToMove->getY());

        if(moveleft)  { objToMove->setX(objToMove->getX() - 2); }
        if(moveright) { objToMove->setX(objToMove->getX() + 2); }
        if(movedown)  { objToMove->setY(objToMove->getY() - 2); }
        if(moveup)    { objToMove->setY(objToMove->getY() + 2); }

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
//        text2->draw();
//        text3->draw();

			drawGrid();

        window->sync();
        SDL_Delay(10);
    }

     engine->shutdownAll();

   return EXIT_SUCCESS;
}
