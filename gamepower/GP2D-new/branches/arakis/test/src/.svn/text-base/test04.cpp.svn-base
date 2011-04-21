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
    window->setWindowTitle("Gamepower 2D Testing App 4");
    window->createWindow(1024, 768, 24);
    window->setGraphicsDefaults();
    window->createNewCamera();

    GP2DInputHandler* handler = new GP2DInputHandler();
    handler->registerKeyAction(GP2DKeyEvent::GP2D_KEY_ESCAPE, new ExitAction());
    handler->registerGlobalKeyAction(new AllAction());

    GP2DTexture* texSusi = new GP2DTexture("susi.png");
    GP2DSprite* sprSusi1 = new GP2DSprite(texSusi);
    sprSusi1->setPosition(0.2f, 0.2f);
   
    GP2DCamera* cam = new GP2DCamera(window->getHeight() / 2);
    cam->setPosition(-0.0f, -0.0f);

    font = new GP2DFont("font.ttf", 12);
    GP2DText* text1 = new GP2DText(font);
    GP2DText* text2 = new GP2DText(font);
    text1->setRenderType(GP2DText::GP2D_RENDER_NICEST);
    text1->setX(0);
    text1->setY(0);
    text1->setZ(12);
    text2->setRenderType(GP2DText::GP2D_RENDER_NICEST);
    text2->setX(0);
    text2->setY(14);
    text2->setZ(12);
    text1->setText("Hi 1");
    text2->setText("Hi 2");
 
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
            objToMove->setY(objToMove->getY() + 1);
        }
        if(moveup) {
            objToMove->setY(objToMove->getY() - 1);
        }
      
        sprSusi1->draw();

			text1->setX(cam->getX());
			text1->setY(cam->getY());
			text2->setX(cam->getX());
			text2->setY(cam->getY()+12);
			
        text1->setText("Camera X: %i - Camera Y: %i",(int)cam->getX(),(int)cam->getY());
        text2->setText("Player X: %i - Player Y: %i",(int)sprSusi1->getX(),(int)sprSusi1->getY());
        text1->draw();
        text2->draw();
        
        window->sync();
        SDL_Delay(10);
    }
     
     engine->shutdownAll();
   
   return EXIT_SUCCESS;
}
