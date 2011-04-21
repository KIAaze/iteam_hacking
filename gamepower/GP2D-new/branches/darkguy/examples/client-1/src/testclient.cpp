#include <gp2d/gp2d.h>

/*

gp2d::Object* player;
gp2d::Object* background;
gp2d::Object* gui;
gp2d::GP2DInputHandler* handler;
gp2d::TCPClientSocket* socket;
bool quit = false;

void playerGoLeft() { player->x-=4; socket->Send("Left"); }
void playerGoRight(){ player->x+=4; socket->Send("Right"); }
void playerGoUp()   { player->y-=2; socket->Send("Up"); }
void playerGoDown() { player->y+=2; socket->Send("Down"); }

void gameQuit(){ quit = true; }
void gameChangeVideoMode(){ gp2d::switchVideoMode(); }

int main (int argc, char*argv[]){
    gp2d::setPath(gp2d::binaryPath(argv[0]));
    gp2d::useAbsolutePaths(false);

    gp2d::setDebug(true);
    gp2d::setVideoAPI(GP2D_SDL);
    gp2d::setVideoFlags();
    gp2d::init();
    gp2d::setVideoMode(640,400,32);
    gp2d::setWindowTitle("GP2D - Client socket test");

    player = new gp2d::Object();
    background = new gp2d::Object();
    gui = new gp2d::Object();

    player->newGraph(gp2d::loadImage("data/player.png"));
    player->x = (640/2)-((player->graph[0]->w)/2);
    player->y = 360-player->graph[0]->h;
    background->newGraph(gp2d::loadImage("data/stars.png"));
    gui->newGraph(gp2d::loadImage("data/gui.png"));

    handler = new gp2d::GP2DInputHandler();
    handler->registerKeyDown(gp2d::GP2DKeyEvent::GP2D_KEY_LEFT,   playerGoLeft        );
    handler->registerKeyDown(gp2d::GP2DKeyEvent::GP2D_KEY_RIGHT,  playerGoRight       );
    handler->registerKeyDown(gp2d::GP2DKeyEvent::GP2D_KEY_UP,     playerGoUp          );
    handler->registerKeyDown(gp2d::GP2DKeyEvent::GP2D_KEY_DOWN,   playerGoDown        );
    handler->registerKeyDown(gp2d::GP2DKeyEvent::GP2D_KEY_ESCAPE, gameQuit            );
    handler->registerKeyDown(gp2d::GP2DKeyEvent::GP2D_KEY_f,      gameChangeVideoMode );

    gp2d::setKeyRepeat(10,10);
	
	socket = new gp2d::TCPClientSocket();
	socket->Connect("localhost", 17000);

    while(quit != true){
        gp2d::cls();
        handler->handleInputEvents();

        background->draw();
        player->draw();
        gui->draw();

        gp2d::sync();
		
    }

	socket->Close();
    SDL_Quit();

}

*/

bool quit = false;
void Quit() { quit = true; }

int main() {

	std::string buffer;
	
	gp2d::GP2DInputHandler* handler;
	gp2d::TCPClientSocket* socket;
	handler = new gp2d::GP2DInputHandler();
	socket = new gp2d::TCPClientSocket();
	
	gp2d::setDebug(true);
    gp2d::setVideoAPI(GP2D_SDL);
    gp2d::setVideoFlags();
    gp2d::init();
    gp2d::setVideoMode(640,400,32);
    gp2d::setWindowTitle("GP2D - Client socket test");
	
	handler->registerKeyDown(gp2d::GP2DKeyEvent::GP2D_KEY_ESCAPE, Quit);
	
	socket->Connect("localhost", 17000);
	socket->Send("C JOIN Test 1");
	
	while(quit != true) {
		buffer = socket->Receive();
		std::cout << buffer << std::endl;
	}
	
	socket->Close();
    SDL_Quit();
	
	return 0;
}
