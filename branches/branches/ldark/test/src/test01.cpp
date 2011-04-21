#include <iostream>
#include "gp2d.h"

using namespace std;
using namespace gp2d;

bool quit = false;

bool moveleft = false;
bool moveright = false;
bool moveup = false;
bool movedown = false;

GP2DEngine* engine = NULL;

GP2DWindow* window = NULL;
GP2DGuiCamera* camGui = NULL;
GP2DGameCamera* camGame = NULL;

GP2DInputHandler* handler = NULL;

GP2DText* text = NULL;
GP2DFont* font = NULL;

GP2DAudioManager* audioMgr = NULL;
GP2DAudioClip* clip = NULL;
GP2DAudioClip* music = NULL;

GP2DFramerate* framerater = NULL;

float g_zcoord = -2.0f;

class CollisionChecker : public GP2DCollisionEvent {
public:
    void collided(GP2DCollision& collision) {
        GP2DObject* obj1 = collision.getObject1();
//        clog << collision.getObject1() << " collided with " << collision.getObject2() << endl;
        float meh = obj1->getY();
        obj1->setY(meh + 1);
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
         } else if (key == GP2DKeyEvent::GP2D_KEY_SPACE) {
             g_zcoord += 1.0f;
             clog << "Z coordinate is now " << g_zcoord << endl;
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

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(0.5f, 1.0f, 0.5f, 0.2f);
    float z = 0.0f;
    glBegin(GL_LINES);
        float range = 1000.0f;
        for(float i = -range; i <= range; i += 50) {
            glVertex3f(i, -range, z);
            glVertex3f(i, range, z);
            glVertex3f(-range, i, z);
            glVertex3f(range, i, z);
        }
    glEnd();

    glColor4f(0.0f, 1.0f, 0.0f, 0.5f);
    glLineWidth(1.0f);
    glBegin(GL_LINES);
        glVertex3f(-range, 0, z);
        glVertex3f(range, 0, z);

        glVertex3f(0, -range, z);
        glVertex3f(0, range, z);
    glEnd();
}


class CursorThread : public GP2DThread {
private:
    GP2DCursor* m_cursor;
public:
    CursorThread(GP2DCursor* cursor) {
        m_cursor = cursor;
    }

    void run() {
        while(!quit) {
            if(m_cursor != NULL) {
                m_cursor->setAnimNextFrame();
            }
            SDL_Delay(50);
        }
    }
};


/**
 * Main main main.
 */
int main(int argc, char* argv[]) {
    engine = GP2DEngine::getInstance();
    engine->initAll();

    window = GP2DWindow::getInstance();
    window->setRenderMode(GP2DWindow::GP2D_OPENGL);
    window->setWindowTitle("Gamepower 2D Testing App");
    window->createWindow(1024, 768, 24);
    window->setGraphicsDefaults();

    handler = new GP2DInputHandler();
    handler->registerKeyAction(GP2DKeyEvent::GP2D_KEY_ESCAPE, new ExitAction());
    handler->registerGlobalKeyAction(new AllAction());

    framerater = GP2DFramerate::getInstance();
    framerater->setMin(10);
    framerater->setMax(150);
    framerater->setFps(150);

    camGame = new GP2DGameCamera();
    camGame->setPosition(100.0f, 100.0f);

    camGui = new GP2DGuiCamera();
    camGui->setDefaults();

    GP2DTexture* texSusi = new GP2DTexture("susi.png");
    GP2DTexture* texTerrain = new GP2DTexture("terrain.png");
    GP2DTexture* texBottom = new GP2DTexture("bottom2.png");
    GP2DTexture* texPointer = new GP2DTexture("normal.png");

    GP2DSprite* sprSusi1 = new GP2DSprite(texSusi);
    GP2DSprite* sprSusi2 = new GP2DSprite(texSusi);
    GP2DSprite* sprTerrain = new GP2DSprite(texTerrain);
    GP2DSprite* sprBottom = new GP2DSprite(texBottom);

    GP2DCursor* cursorNormal = new GP2DCursor(texPointer);
	cursorNormal->createAnim(4,0, 0,0,64,64);
    cursorNormal->setWidth(64.0f);
    cursorNormal->setHeight(64.0f);
    cursorNormal->setAnimFrame(0);
	cursorNormal->setAnimLoop(true);

    sprSusi1->addBoundingBox(GP2DRect(0,0,10,10));
    sprTerrain->computeEdges();

    sprSusi1->setPosition(-0.0f, 0.0f);
    sprSusi2->setPosition(10.0f, 10.0f);

    sprBottom->setPosition(0.0f,sprBottom->getHeight());

    font = new GP2DFont("font.ttf", 24);

    text = new GP2DText(font);
    text->setRenderType(GP2DText::GP2D_RENDER_NICEST);
    text->setX(0);
    text->setY(0);
    text->setZ(12);
    text->setText("Susi (HP: 100)");

    GP2DDirector* director = new GP2DDirector(camGame, camGui);

    GP2DCursor::setDefPointerVisible(false);

    GP2DThread* thread = new CursorThread(cursorNormal);
    thread->setName("CursorThread");
    thread->start();

    while(!quit) {
        handler->handleInputEvents();
		window->clearScreen();

        GP2DObject* objToMove = sprSusi1;
        camGame->setPosition(objToMove->getX(), objToMove->getY());

        if(moveleft) {
            objToMove->setX(objToMove->getX() - 1);
            text->setX(objToMove->getX());
        }
        if(moveright) {
            objToMove->setX(objToMove->getX() + 1);
            text->setX(objToMove->getX());
        }
        if(movedown) {
            objToMove->setY(objToMove->getY() - 1);
            text->setY(objToMove->getY() + text->getHeight());
        }
        if(moveup) {
            objToMove->setY(objToMove->getY() + 1);
            text->setY(objToMove->getY() + text->getHeight());
        }

        director->useGameCamera();

        sprTerrain->draw();
        text->draw();
        sprSusi1->draw();


        drawGrid();

        // EPIC GUI STUFF SHOULD COME HEREZ0R!
        director->useGuiCamera();
        sprBottom->draw();
        cursorNormal->updatePosition();
        cursorNormal->draw();

        window->sync();

        framerater->delay();
    }

    delete thread;

    engine->shutdownAll();

    return EXIT_SUCCESS;
}

