#include <iostream>
#include <cstdio>

#include "gp2d.h"

#define ADAMORJAMES_WONT_SHUT_UP true

using namespace gp2d;
using namespace std;

GP2DPhysWorld* zaWarudo;
GP2DTexture* texture;
GP2DPhysSolidObject* poly1;
GP2DPhysSolidObject* poly2;
GP2DPhysSolidObject* circle1;
GP2DPhysSolidObject* circle2;

int main(int argc, char** argv)
{
    zaWarudo = new GP2DPhysWorld(5000, 5000);
    
    poly1 = new GP2DPhysSolidObject(100.0f, 100.0f,
    100.0f, CONVEX_POLYGON, texture);
    poly1->addPoint(0.0f, 0.0f);
    poly1->addPoint(0.0f, 100.0f);
    poly1->addPoint(100.0f, 100.0f);
    poly1->addPoint(100.0f, 0.0f);
    poly1->buildEdges();

    poly2 = new GP2DPhysSolidObject(100.0f, 100.0f,
    100.0f, CONVEX_POLYGON, texture);
    poly2->addPoint(101.0f, 0.0f);
    poly2->addPoint(101.0f, 100.0f);
    poly2->addPoint(201.0f, 100.0f);
    poly2->addPoint(201.0f, 0.0f);
    poly2->buildEdges();
    
    cout << zaWarudo->isColliding(poly1, poly2) << endl;
    
    poly1 = new GP2DPhysSolidObject(100.0f, 100.0f,
    100.0f, CONVEX_POLYGON, texture);
    poly1->addPoint(0.0f, 0.0f);
    poly1->addPoint(0.0f, 100.0f);
    poly1->addPoint(100.0f, 100.0f);
    poly1->addPoint(100.0f, 0.0f);
    poly1->buildEdges();

    poly2 = new GP2DPhysSolidObject(100.0f, 100.0f,
    100.0f, CONVEX_POLYGON, texture);
    poly2->addPoint(0.0f, 0.0f);
    poly2->addPoint(0.0f, 100.0f);
    poly2->addPoint(100.0f, 100.0f);
    poly2->addPoint(100.0f, 0.0f);
    poly2->buildEdges();
    
    cout << zaWarudo->isColliding(poly1, poly2) << endl;
    
    poly1->setGravity(-0.1f);
    
    while(ADAMORJAMES_WONT_SHUT_UP)
    {
        poly1->step(100.0f);
        cout << poly1->getCoordX() << ", " <<
        poly1->getCoordY() << endl;
        SDL_Delay(500);
    }
    
    return 0;
}
