#include <iostream>
#include "gp2d.h"
using namespace std;
using namespace gp2d;

bool quit = false;
bool moveleft = false;
bool moveright = false;
bool moveup = false;
bool movedown = false;
bool coll = false;

GP2DFont* font;

class CollisionChecker : public GP2DCollisionEvent {
public:
    void collided(GP2DCollision& collision) {
    	coll = true;
    }
};

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

    GP2DEngine* engine = GP2DEngine::getInstance();
    engine->initAll();

    GP2DWindow* window = GP2DWindow::getInstance();
    window->setRenderMode(GP2DWindow::GP2D_OPENGL);
    window->setWindowTitle("Gamepower 2D Testing App 6");
    window->createWindow(1024, 768, 32);
    window->setGraphicsDefaults();
    GP2DGameCamera* cam = new GP2DGameCamera(window->getHeight() / 2);
    cam->setPosition(0.0f, 0.0f);

//    GP2DInputHandler* handler = new GP2DInputHandler();
//    handler->registerKeyAction(GP2DKeyEvent::GP2D_KEY_ESCAPE, new ExitAction());
//    handler->registerGlobalKeyAction(new AllAction());

    GP2DTexture* texSphere = new GP2DTexture("sphere.png");

    GP2DSprite* sphere1 = new GP2DSprite(texSphere);
    GP2DSprite* sphere2 = new GP2DSprite(texSphere);
    sphere1->setPosition(0.0f, 0.0f);
    sphere1->setWidth(128);
    sphere1->setHeight(128);

    sphere2->setPosition(180.0f, 180.0f);
    sphere2->setWidth(128);
    sphere2->setHeight(128);

    font = new GP2DFont("font.ttf", 24);
    GP2DText* text1 = new GP2DText(font);
    GP2DText* text2 = new GP2DText(font);
    GP2DText* text3 = new GP2DText(font);
    text1->setRenderType(GP2DText::GP2D_RENDER_NICEST);
    text2->setRenderType(GP2DText::GP2D_RENDER_NICEST);
    text3->setRenderType(GP2DText::GP2D_RENDER_NICEST);
    text1->setZ(12);
    text2->setZ(12);
    text3->setZ(12);
    text1->setX(0);
    text1->setY(0);
    text2->setX(0);
    text2->setY(-26);
    text3->setX(0);
    text3->setY(-(26+26));

    GP2DCollisionManager* collMgr = new GP2DCollisionManager();
    GP2DPixelCollision* pixcoll = new GP2DPixelCollision(*sphere1, *sphere2);
    collMgr->addCollision(pixcoll);
    collMgr->registerEvent(new CollisionChecker());

    while(!quit) {
//        handler->handleInputEvents();
        window->clearScreen();

        GP2DObject* objToMove = sphere1;
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
