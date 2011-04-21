#include "statemachine.h"
#include "engine.h"
#include "input.h"
#include "intro.h"
#include "menu.h"
using namespace std;
using namespace gp;

namespace game {

iteam* iteam::m_self = NULL;

iteam::iteam(){}
iteam::~iteam(){}
iteam* iteam::instance() {
    if(m_self == NULL) { m_self = new iteam(); }
    return m_self;
}

GPEngine* iteam::engine(){
	return m_engine;
}

GPWindow* iteam::window(){
	return m_window;
}

GPInputHandler* iteam::input(){
	return m_input;
}

GPDirector* iteam::director(){
	return m_camDirector;
}

GPGuiCamera* iteam::camGui(){
	return m_camGui;
}

GPGameCamera* iteam::camGame(){
	return m_camGame;
}

void iteam::init(){
	m_engine = GPEngine::getInstance();
	m_engine->initAll();
	
	m_window = GPWindow::getInstance();
	m_window->setRenderMode(GPWindow::GP_OPENGL);
	m_window->setWindowTitle("iteam");
	m_window->createWindow(1024, 768, 24);
	m_window->setGraphicsDefaults();
	// m_window->createNewCamera();
	
        m_camGame = new GPGameCamera();
        m_camGame->setPosition(100.0f, 100.0f);

        m_camGui = new GPGuiCamera();
        m_camGui->setDefaults();	
	
	m_camDirector = new GPDirector(m_camGame, m_camGui);
	
	m_input = new GPInputHandler();

        m_KeyboardHandler = new GPKeyboardHandler();
        m_KeyboardHandler->registerKeyAction(GPKeyEvent::GP_KEY_ESCAPE, new ExitAction());
        m_KeyboardHandler->registerGenericKeyAction(new AllAction());

        m_InputProcessor = new GPInputProcessor();
        m_InputProcessor->addHandler(handler);

	
	m_quit = false;
	setState(INTRO);
}

void iteam::quit(){
	m_quit = true;
}

void iteam::run(){
	m_input->registerGlobalKeyAction(new introAction());
	m_intro = new iteamIntro();
	m_menu = new iteamMenu();

	while(m_quit == false) {
		m_input->handleInputEvents();
		m_window->clearScreen();
		
		switch (getState()){
			case INTRO:
				m_intro->run();
			break;
				
			case FREE_INTRO:
				delete m_intro; m_intro = NULL;
				setNextState(MENU);
				nextState();
			break;
			
			case MENU:
				m_menu->run();
			break;
		}
		
		m_window->sync();
		SDL_Delay(10);
	}
}

}
