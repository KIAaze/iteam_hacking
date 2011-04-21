#include <iostream>

#include <GP2D/gp2d.h>

using namespace std;
using namespace gp2d;

bool quit = false;

bool moveleft = false;
bool moveright = false;
bool moveup = false;
bool movedown = false;

GP2DFont* font;

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

void test() throw (GP2DException) {
    throw GP2DException("oh", "hai");
}

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

    GP2DInputHandler* handler = new GP2DInputHandler();
    handler->registerKeyAction(GP2DKeyEvent::GP2D_KEY_ESCAPE, new ExitAction());
    handler->registerGlobalKeyAction(new AllAction());

    GP2DAudioManager* audiomgr = GP2DAudioManager::getInstance();
    try {
        audiomgr->openAudio();
    } catch (GP2DException zz) {
        clog << zz.what() << endl;
    }

    delete audiomgr;

    GP2DCollisionManager* collMgr = new GP2DCollisionManager();

    GP2DCamera* cam = new GP2DCamera(512);
    cam->setPosition(100.0f, 100.0f);

    GP2DTexture* texSusi = new GP2DTexture("susi.png");
    GP2DTexture* texTerrain = new GP2DTexture("terrain.png");

    GP2DSprite* sprSusi1 = new GP2DSprite(texSusi);
    GP2DSprite* sprSusi2 = new GP2DSprite(texSusi);
    GP2DSprite* sprTerrain = new GP2DSprite(texTerrain);

    sprSusi1->addBoundingBox(GP2DRect(0,0,10,10));
    sprTerrain->computeEdges();

    GP2DPixelCollision* pixcoll = new GP2DPixelCollision(*sprSusi1, *sprTerrain);
    collMgr->addCollision(pixcoll);
    collMgr->registerEvent(new CollisionChecker());

    sprSusi1->setPosition(-0.0f, 0.0f);
    sprSusi2->setPosition(-69.0f, 0.0f);

    font = new GP2DFont("font.ttf", 24);
    GP2DText* text = new GP2DText(font);
    text->setRenderType(GP2DText::GP2D_RENDER_NICEST);
    text->setX(0);
    text->setY(0);
    text->setZ(12);
    text->setText("Susi (HP: 100)");

    while(!quit) {
        handler->handleInputEvents();
        window->clearScreen();

        GP2DObject* objToMove = sprSusi1;
        cam->setPosition(objToMove->getX(), objToMove->getY());

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

        sprTerrain->draw();
        sprSusi1->draw();
//        sprSusi2->draw();
//        text->draw();

        drawGrid();

        collMgr->handleCollisions();

        window->sync();

        SDL_Delay(10);
    }

    // free all the things.
    //   delete sprSusi1;
    //   delete sprSusi2;
    //   delete pixcoll;
    //   delete text;
    //   delete font;

     engine->shutdownAll();

   return EXIT_SUCCESS;
}

