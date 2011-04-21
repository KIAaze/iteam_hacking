#include <iostream>
#include "gp2d.h"

using namespace std;
using namespace gp2d;

bool quit = false;

GP2DEngine* engine = NULL;
GP2DWindow* window = NULL;
GP2DFramerate* framerater = NULL;


class ExitAction : public GP2DKeyAction {
public:
    ExitAction() {}
    ~ExitAction() {}

    void keyDown(GP2DKeyEvent& keyEvent) {
        clog << "Quitting!" << endl;
        quit = true;
    }
};

class GenericKeyAction : public GP2DKeyAction {
private:
    string str;

public:
    GenericKeyAction() {}
    ~GenericKeyAction() {}
    void keyDown(GP2DKeyEvent& keyEvent) {
        GP2DKeyEvent::GP2DKey key = keyEvent.getKey();
        GP2DKeyEvent::GP2DKeyMod mod = keyEvent.getModifier();
        gp2dUshort unicode = keyEvent.getUnicode();
        clog << key << endl;
        
        if(key == GP2DKeyEvent::GP2D_KEY_RETURN) {
            cout << str << endl;
            str.clear();
            return;
        } else if (key == GP2DKeyEvent::GP2D_KEY_BACKSPACE) {
            try {
                str.erase(str.length() - 1, 1);
            } catch (exception& e) {
                cerr << "Out of bounds!" << endl;
            }
            return;
        }

        if(unicode != 0) {
            char cox = static_cast<char>(/*toascii(*/unicode/*)*/);
            str.append(sizeof(char), cox);
        }
    }
};

class MouseAction : public GP2DMouseAction {
public:
    MouseAction() {}
    ~MouseAction() {}

    void mouseButtonUp(GP2DMouseEvent& event) {
        clog << "HAI!" << endl;
    }

    void mouseButtonDown(GP2DMouseEvent& event) {
        clog << "Down" << endl;
    }

    void mouseDragStart(GP2DMouseEvent& event) {
        clog << "Drag start" << endl;
    }

    void mouseDragEnd(GP2DMouseEvent& event) {
        clog << "Drag end." << endl;
    }

};

class ActiveAction : public GP2DFocusAction {
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
    engine = GP2DEngine::getInstance();
    engine->initAll();

    SDL_EnableUNICODE(true);
    
    window = GP2DWindow::getInstance();
    window->setRenderMode(GP2DWindow::GP2D_OPENGL);
    window->setWindowTitle("Gamepower 2D Testing App");
    window->createWindow(640, 480, 24);
    window->setGraphicsDefaults();

    GP2DKeyboardHandler* handler = new GP2DKeyboardHandler();
    handler->registerKeyAction(GP2DKeyEvent::GP2D_KEY_ESCAPE, new ExitAction());
    handler->registerGenericKeyAction(new GenericKeyAction());

    GP2DMouseHandler* mhandler = new GP2DMouseHandler();
    mhandler->registerMouseAction(new MouseAction());

    GP2DFocusHandler* fhandler = new GP2DFocusHandler();
    fhandler->registerFocusAction(new ActiveAction());

    GP2DInputProcessor* proc = new GP2DInputProcessor();
    proc->addHandler(handler);
    proc->addHandler(mhandler);
    proc->addHandler(fhandler);

    while(!quit) {
        proc->pollEvents();
    }
    
    delete proc;
    delete window;

    engine->shutdownAll();

    delete engine;

    cout << "Finished" << endl;
    return 1;

}
