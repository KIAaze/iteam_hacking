#include "gp2d.hpp"
#include "test.hpp"

#include <iostream>

using namespace gp;
using namespace std;

GPEngine* engine = new GPEngine();
GPWindow* window = new GPWindow();

int main (int argc, char*argv[])
{
    engine->initialize();
    window->create(640,480,24);
    window->setTitle("GP2D Test program");
    
    int a = 0;    
    while(a < 100)
    {
        a++;
        window->clear();
        window->render();
        engine->wait(1);
    }
    
    engine->shutdown();
}
