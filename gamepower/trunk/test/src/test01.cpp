#include <iostream>
#include "gp2d.h"

using namespace std;
using namespace gp;

bool quit = false;

GPEngine* engine = NULL;
GPWindow* window = NULL;
GPFramerate* framerater = NULL;
GPGameCamera* cam = NULL;


class ExitAction : public GPKeyAction {
public:
    ExitAction() {}
    ~ExitAction() {}

    void keyDown(GPKeyEvent& keyEvent) {
        clog << "Quitting!" << endl;
        quit = true;
    }
};

class GenericKeyAction : public GPKeyAction {
private:
    string str;

public:
    GenericKeyAction() {}
    ~GenericKeyAction() {}
    void keyDown(GPKeyEvent& keyEvent) {
        GPKeyEvent::GPKey key = keyEvent.getKey();
        GPKeyEvent::GPKeyMod mod = keyEvent.getModifier();
        gpUshort unicode = keyEvent.getUnicode();
        clog << key << endl;
        
        if(key == GPKeyEvent::GP_KEY_RETURN) {
            cout << str << endl;
            str.clear();
            return;
        } else if (key == GPKeyEvent::GP_KEY_BACKSPACE) {
            try {
                str.erase(str.length() - 1, 1);
            } catch (exception& e) {
                cerr << "Out of bounds!" << endl;
            }
            return;
        }
		
		if ( key == GPKeyEvent::GP_KEY_f ) {
			GPWindow* window = GPWindow::getInstance();
			window->toggleFullScreen();
			cam->updateCamera();
		}

        if(unicode != 0) {
            char cox = static_cast<char>(/*toascii(*/unicode/*)*/);
            str.append(sizeof(char), cox);
        }
    }
};

class MouseAction : public GPMouseAction {
public:
    MouseAction() {}
    ~MouseAction() {}

    void mouseButtonUp(GPMouseEvent& event) {
        clog << "HAI!" << endl;
    }

    void mouseButtonDown(GPMouseEvent& event) {
        clog << "Down" << endl;
    }

    void mouseDragStart(GPMouseEvent& event) {
        clog << "Drag start" << endl;
    }

    void mouseDragEnd(GPMouseEvent& event) {
        clog << "Drag end." << endl;
    }

};

class ActiveAction : public GPFocusAction {
public:
    ActiveAction() {}
    ~ActiveAction() {}

    void focusGained() {
        clog << "Gained" << endl;
    }

    void focusLost() {
        clog << "Lost" << endl;
    }
};

int main(int argc, char **argv) {
    engine = GPEngine::getInstance();
    engine->initAll();

    SDL_EnableUNICODE(true);
    
    window = GPWindow::getInstance();
    window->setRenderMode(GPWindow::GP_OPENGL);
    window->setWindowTitle("Gamepower 2D Testing App");
	window->setFlagResizable();
    window->createWindow(640, 480, 24);
    window->setGraphicsDefaults();

    GPKeyboardHandler* handler = new GPKeyboardHandler();
    handler->registerKeyAction(GPKeyEvent::GP_KEY_ESCAPE, new ExitAction());
    handler->registerGenericKeyAction(new GenericKeyAction());

    GPMouseHandler* mhandler = new GPMouseHandler();
    mhandler->registerMouseAction(new MouseAction());

    GPFocusHandler* fhandler = new GPFocusHandler();
    fhandler->registerFocusAction(new ActiveAction());

    GPInputProcessor* proc = new GPInputProcessor();
    proc->addHandler(handler);
    proc->addHandler(mhandler);
    proc->addHandler(fhandler);
    
    fhandler->setEnabled(false);
	
	GPSprite* lulz = new GPSprite(new GPTexture("sphere.png"));
	lulz->setPosition(0.0f,0.0f);
    lulz->setScale(0.5f,0.2f,1.0f);

    cam = new GPGameCamera(window->getHeight() / 2);
    cam->setPosition(0.0f, 0.0f);	

    while(!quit) {
        proc->pollEvents();
        window->clearScreen();
		
		lulz->draw();
		lulz->setVelocity_X(0.5f);
		
        window->sync();
        SDL_Delay(10);		
    }
    
    delete proc;
    delete window;

    engine->shutdownAll();

    delete engine;

    cout << "Finished" << endl;
    return 1;

}
