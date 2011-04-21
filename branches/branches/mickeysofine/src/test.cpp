#include <iostream>

#include "gp2d.h"

using namespace std;
using namespace gp2d;

bool quit = false;

bool moveleft = false;
bool moveright = false;
bool moveup = false;
bool movedown = false;

class CollisionChecker : public GP2DCollisionEvent {
public:
    void collided(GP2DCollision& collision) {
        clog << collision.getObject1() << " collided with " << collision.getObject2() << endl;
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
         }else if(key == GP2DKeyEvent::GP2D_KEY_UP) {
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
int main() {    
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
   
   GP2DCollisionManager* collMgr = new GP2DCollisionManager();
   
   GP2DCamera* cam = new GP2DCamera(512);

   GP2DTexture* texSusi = new GP2DTexture("susi.png");
   GP2DTexture* texTerrain = new GP2DTexture("terrain.png");
   
   texTerrain->computeEdges();
   
   GP2DSprite* sprSusi1 = new GP2DSprite(texSusi);
   GP2DSprite* sprSusi2 = new GP2DSprite(texSusi);
   GP2DSprite* sprTerrain = new GP2DSprite(texTerrain);
   
   GP2DPixelCollision* pixcoll = new GP2DPixelCollision(*sprSusi1, *sprSusi2);
   collMgr->addCollision(pixcoll);
   collMgr->registerEvent(new CollisionChecker());
   
   sprSusi1->setPosition(-0.0f, 0.0f);  
   sprSusi2->setPosition(-69.0f, -69.0f);
   
   GP2DFont* font = new GP2DFont("font.ttf", 24);
   GP2DText* text = new GP2DText(font);
   text->setRenderType(GP2DText::GP2D_RENDER_NICEST);
   text->setX(-80);
   text->setY(-80);
   text->setZ(12);
   text->setText("Susi (HP: 100)");
   
   while(!quit) {
       handler->handleInputEvents();
       window->clearScreen();
       
       cam->setPosition(0.0f, 0.0f);
       
       GP2DObject* objToMove = sprSusi1;
       
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
       sprSusi2->draw();
       text->draw();
              
       
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
