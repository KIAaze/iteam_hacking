#include <iostream>
#include "gp2d.h"

using namespace std;
using namespace gp2d;

bool quit = false;

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
   window->setBackgroundColor(0,0,0);

   GP2DCamera* cam = new GP2DCamera(512);

   GP2DInputHandler* handler = new GP2DInputHandler();
   handler->registerKeyAction(GP2DKeyEvent::GP2D_KEY_ESCAPE, new ExitAction());

   GP2DFont txt("font.ttf", 64 << 2);

   std::string mystring;
   std::stringstream ss;
   mystring = "";
   GP2DText* txtFPS = new GP2DText(&txt, mystring);
   txtFPS->setColor(0,255,255);

   int counter=0;
   while(!quit) {
       handler->handleInputEvents();
       window->clearScreen();
       counter=counter+1;
       
       cam->setPosition(0.0f, 0.0f);

       ss << counter;
       ss >> mystring;
       txtFPS->setText(mystring);
       ss.clear();

       txtFPS->draw();       

       window->sync();
       
       SDL_Delay(20);
   }
   
   engine->shutdownAll();

   return EXIT_SUCCESS;
}
