#include "gp2d/gp2d.h"
using namespace gp;

#include <deque>
#include <iostream>
using namespace std;

#include "polygon.cpp"

int ear=0;

SimplePolygon GSP;
SimplePolygon Rest;

class MouseAction : public GPMouseAction {
public:
    MouseAction() {}
    ~MouseAction() {}

    void mouseButtonUp(GPMouseEvent& event) {
//         clog << "HAI!" << event.getButton() << endl;
        GPVector ScreenCoords=GPVector(event.getX(),event.getY());
        GPVector WindowCoords=screen2window(window,cam,ScreenCoords);
        GLfloat x=WindowCoords.getX();
        GLfloat y=WindowCoords.getY();
        cout<<"("<<event.getX()<<","<<event.getY()<<")->("<<x<<","<<y<<")"<<endl;
        if(event.getButton()==1) {
/*            cout<<"Adding point"<<endl;
            CustomPoints.push_back(GPVector(x,y));*/
/*            SimplePolygon tmp;
            ear=FindAnEar(Triangle,ear,tmp);
            cout<<"ear="<<ear<<endl;
            CustomPolys.push_back(tmp);
            if(ear>=0) Triangle.removeVertex(ear);
            else ear=0;*/
/*            SimplePolygon Rest;
            superman=Triangulate(TestPolygon,Rest,false);*/
//             int start,stop;
//             int result=FindAConvexPolygon(TestPolygon, GSP, start, stop);
            superman=Convexify(TestPolygon, Rest, false);
            cout<<"Rest="<<Rest<<endl;


        }
        else if(event.getButton()==3) {
            cout<<"Adding point to triangle"<<endl;
            TestPolygon.addVertex(GPVector(x,y));
        }
        else {
            cout<<"===CLEAR ALL==="<<endl;
            TestPolygon.clear();
            GSP.clear();
            Rest.clear();
            superman.clear();
            CustomPoints.clear();
            CustomPolys.clear();
            CustomPolysLower.clear();
            CustomPolysUpper.clear();
            CustomPolysMidline.clear();
            CustomConvexHulls.clear();
        }
    }

    void mouseButtonDown(GPMouseEvent& event) {
//         clog << "Down" << endl;
    }

    void mouseDragStart(GPMouseEvent& event) {
//         clog << "Drag start" << endl;
    }

    void mouseDragEnd(GPMouseEvent& event) {
//         clog << "Drag end." << endl;
    }

};

int main (int argc, char*argv[])
{
//     GPVector a(0,0);
//     GPVector b(0,1);
//     GPVector c(-1,2);//turn left
//     GPVector d(0,2);//no turn
//     GPVector e(1,2);//turn right
// deque <GPVector> toto;
// toto.push_back(GPVector(4,0));
// toto.push_back(GPVector(3,1));
// toto.push_back(GPVector(2,2));
// toto.push_back(GPVector(1,3));
// toto.push_back(GPVector(0,4));
// for(int i=0;i<toto.size();i++) cout<<toto[i]<<endl;
// sort(toto.begin(),toto.end());
// for(int i=0;i<toto.size();i++) cout<<toto[i]<<endl;
// exit(0);

//     cout<<"TurnLeft(a,b,c)="<<TurnLeft(a,b,c)<<endl;
//     cout<<"TurnLeft(a,b,d)="<<TurnLeft(a,b,d)<<endl;
//     cout<<"TurnLeft(a,b,e)="<<TurnLeft(a,b,e)<<endl;
//     cout<<"TurnRight(a,b,c)="<<TurnRight(a,b,c)<<endl;
//     cout<<"TurnRight(a,b,d)="<<TurnRight(a,b,d)<<endl;
//     cout<<"TurnRight(a,b,e)="<<TurnRight(a,b,e)<<endl;
// 
//     exit(0);

    GPEngine* engine = GPEngine::getInstance();
    engine->initAll();

    window = GPWindow::getInstance();
    window->setRenderMode(GPWindow::GP_OPENGL);
    window->setWindowTitle("Gamepower 2D Testing App");
    window->createWindow(640, 480, 24);
    window->setGraphicsDefaults();

    GPKeyboardHandler* handler = new GPKeyboardHandler();
    handler->registerKeyAction(GPKeyEvent::GP_KEY_ESCAPE, new ExitAction());
    GPMouseHandler* mhandler = new GPMouseHandler();
    mhandler->registerMouseAction(new MouseAction());
    GPInputProcessor* proc = new GPInputProcessor();
    proc->addHandler(handler);
    proc->addHandler(mhandler);

    cam = new GPGameCamera(window->getHeight() / 2);

    cam->setPosition(200.0f, -300.0f);
//     cam->setPosition(0.0f, 0.0f);

    cout<<"===LOADING==="<<endl;
    cout<<"===Susi==="<<endl;
    GPTexture* texSusi = new GPTexture("susi.png");
    GPSprite* sprSusi = new GPSprite(texSusi);
    sprSusi->setPosition(0.0f, 0.0f);
    SimplePolygon shapeSusi=CreateFromTexture(texSusi);
    cout<<"shapeSusi="<<shapeSusi<<endl;
    SimplePolygon bbSusi(CreateBoundingBoxFromTexture(texSusi));
    SimplePolygon polySusi(shapeSusi);
//    SimplePolygon hullSusi=CreateConvexHull(polySusi);
    SimplePolygon hullSusi=CreateConvexHull3(polySusi);
//     polySusi.scale(5);
//     polySusi.setPosition(-100,100);
    
//     hullSusi.setPosition(-100,100);

    cout<<"===Missile==="<<endl;
    GPTexture* texMissile = new GPTexture("missile.png");
    GPSprite* sprMissile = new GPSprite(texMissile);
    sprMissile->setPosition(100.0f, -10.0f);
    SimplePolygon shapeMissile=CreateFromTexture(texMissile);

    cout<<"===Leaves==="<<endl;
    GPTexture* texLeaves = new GPTexture("iteam_leaves_animation.png");
    GPSprite* sprLeaves = new GPSprite(texLeaves);
    sprLeaves->setPosition(0.0f, -100.0f);
    SimplePolygon shapeLeaves=CreateFromTexture(texLeaves);

    cout<<"===Terrain==="<<endl;
    GPTexture* texTerrain = new GPTexture("terrain_small.png");
    GPSprite* sprTerrain = new GPSprite(texTerrain);
    sprTerrain->setPosition(0.0f, -100.0f);
    SimplePolygon shapeTerrain=CreateFromTexture(texTerrain);
    cout<<"===DONE==="<<endl;

    int size=10;

    ConvexPolygon CP;

    SimplePolygon polygon1;
    polygon1.addVertex(GPVector(0,0));
    polygon1.addVertex(GPVector(50,50));
    polygon1.addVertex(GPVector(100,0));
    polygon1.addVertex(GPVector(50,100));
    CP.addPolygon(polygon1);

    SimplePolygon polygon2;
    polygon2.addVertex(GPVector(0,100));
    polygon2.addVertex(GPVector(50,150));
    polygon2.addVertex(GPVector(100,100));
    polygon2.addVertex(GPVector(50,200));
    CP.addPolygon(polygon2);

    ConvexPolygon CP2=CP;

    CP.setPosition(0,0);
    CP2.setPosition(50,50);
    polygon1.setScale(2.0,2.0,1.0);
    cout<<"Scale X="<<polygon1.getScale_X()<<endl;
    cout<<"Scale Y="<<polygon1.getScale_Y()<<endl;
    cout<<"Scale Z="<<polygon1.getScale_Z()<<endl;

    CP2.setScale(0.5,0.5,1.0);
    CP2.setRotation_Z(-45);
    cout<<"Scale X="<<CP2.getScale_X()<<endl;
    cout<<"Scale Y="<<CP2.getScale_Y()<<endl;
    cout<<"Scale Z="<<CP2.getScale_Z()<<endl;

//     sprSusi->setRotation_Z(45);
    sprSusi->setScale(3,3,1);
    sprSusi->setPosition(-50,-50);

    bbSusi.setRotation_Z(sprSusi->getRotation_Z());
    bbSusi.setScale_X(sprSusi->getScale_X());//Scale functions not practical
    bbSusi.setScale_Y(sprSusi->getScale_Y());
    bbSusi.setScale_Z(sprSusi->getScale_Z());
    bbSusi.setPosition(sprSusi->getX(),sprSusi->getY());

    polySusi.ScaleForReal(5);
//     polySusi.setRotation_Z(sprSusi->getRotation_Z());
/*    polySusi.setScale_X(sprSusi->getScale_X());//Scale functions not practical
    polySusi.setScale_Y(sprSusi->getScale_Y());
    polySusi.setScale_Z(sprSusi->getScale_Z());*/
//     polySusi.setPosition(sprSusi->getX(),sprSusi->getY()+100);

    cout<<"polySusi="<<polySusi<<endl;

    hullSusi.setRotation_Z(sprSusi->getRotation_Z());
    hullSusi.setScale_X(sprSusi->getScale_X());//Scale functions not practical
    hullSusi.setScale_Y(sprSusi->getScale_Y());
    hullSusi.setScale_Z(sprSusi->getScale_Z());
    hullSusi.setPosition(sprSusi->getX(),sprSusi->getY());

    bbSusi.setRGBA(1,0,0,1);
    hullSusi.setRGBA(0,1,0,1);
    polySusi.setRGBA(0,0,1,1);

        SimplePolygon Rest;
        ConvexPolygon ConvexSusi=Convexify(polySusi,Rest,false);
    Rest.setRGBA(1,0,0,1);
    cout<<"Rest.getSize()="<<Rest.getSize()<<endl;

/*    ConvexSusi.setRotation_Z(sprSusi->getRotation_Z());
    ConvexSusi.setScale_X(sprSusi->getScale_X());//Scale functions not practical
    ConvexSusi.setScale_Y(sprSusi->getScale_Y());
    ConvexSusi.setScale_Z(sprSusi->getScale_Z());
    ConvexSusi.setPosition(sprSusi->getX(),sprSusi->getY());

    Rest.setRotation_Z(sprSusi->getRotation_Z());
    Rest.setScale_X(sprSusi->getScale_X());//Scale functions not practical
    Rest.setScale_Y(sprSusi->getScale_Y());
    Rest.setScale_Z(sprSusi->getScale_Z());
    Rest.setPosition(sprSusi->getX(),sprSusi->getY());*/
    
    cout<<"Rest="<<Rest<<endl;

    while(!quit) {
        proc->pollEvents();
        window->clearScreen();

        polySusi.draw();

if(true)
{
//         SimplePolygon Rest;
//         ConvexPolygon ConvexSusi=Triangulate(polySusi,Rest);
// 
// 
//     ConvexSusi.setRotation_Z(sprSusi->getRotation_Z());
//     ConvexSusi.setScale_X(sprSusi->getScale_X());//Scale functions not practical
//     ConvexSusi.setScale_Y(sprSusi->getScale_Y());
//     ConvexSusi.setScale_Z(sprSusi->getScale_Z());
//     ConvexSusi.setPosition(sprSusi->getX(),sprSusi->getY());
// 
//     Rest.setRotation_Z(sprSusi->getRotation_Z());
//     Rest.setScale_X(sprSusi->getScale_X());//Scale functions not practical
//     Rest.setScale_Y(sprSusi->getScale_Y());
//     Rest.setScale_Z(sprSusi->getScale_Z());
//     Rest.setPosition(sprSusi->getX()+200,sprSusi->getY());

//         sprSusi->draw();
        ConvexSusi.draw();
        Rest.draw();
}
//         sprMissile->draw();
//         sprTerrain->draw();
//         sprLeaves->draw();

/*	for(unsigned int i=0;i<CustomPoints.size();i++)
    {
        if(IsInConvexPolygon(Triangle,CustomPoints[i]))
            filledSquareRGBA(CustomPoints[i].getX(),CustomPoints[i].getY(),size,0,0,0,1,1);
        else
            filledSquareRGBA(CustomPoints[i].getX(),CustomPoints[i].getY(),size,0,1,0,0,1);
    }
	for(unsigned int i=0;i<CustomPoints.size();i++) filledSquareRGBA(CustomPoints[i].getX(),CustomPoints[i].getY(),size,0,1,0,0,1);
	for(unsigned int i=0;i<CustomPolys.size();i++) CustomPolys[i].draw();
	for(unsigned int i=0;i<CustomPolysLower.size();i++) CustomPolysLower[i].draw();
	for(unsigned int i=0;i<CustomPolysUpper.size();i++) CustomPolysUpper[i].draw();
	for(unsigned int i=0;i<CustomPolysMidline.size();i++) CustomPolysMidline[i].draw();
	for(unsigned int i=0;i<CustomConvexHulls.size();i++) CustomConvexHulls[i].draw();*/
    TestPolygon.setRGBA(1,1,0,1);
    TestPolygon.draw();
    Rest.setRGBA(1,0,0,1);
    Rest.draw();
    superman.setRGBA(1,1,1,1);
    superman.draw();
	
//         filledPolygonRGBA(200,100,polygon.getVertices(),size,0,1,0,1);
//         PolygonRGBA(0,0,polygon.getVertices(),size,0,1,0,1);
//         polygon1.draw();
//         polygon2.draw();
//         CP.draw();
//         CP2.draw();

/*     	bbSusi.draw();
	    polySusi.draw();
        PolygonRGBA(sprSusi->getX(),sprSusi->getY(),shapeSusi.getVertices(),sprSusi->getScale_X(),sprSusi->getRotation_Z(),size,1,1,1,1);
        PolygonRGBA(sprSusi->getX(),sprSusi->getY(),bbSusi.getVertices(),sprSusi->getScale_X(),sprSusi->getRotation_Z(),size,1,1,1,1);
        hullSusi.setRotation_Z(sprSusi->getRotation_Z());
        hullSusi.setScale_X(sprSusi->getScale_X());//Scale functions not practical
        hullSusi.setScale_Y(sprSusi->getScale_Y());
        hullSusi.setScale_Z(sprSusi->getScale_Z());
        hullSusi.setPosition(sprSusi->getX(),sprSusi->getY());
        hullSusi.draw();*/
//         PolygonRGBA(sprSusi->getX(),sprSusi->getY(),hullSusi.getVertices(),sprSusi->getScale_X(),sprSusi->getRotation_Z(),size,1,1,1,1);

//         filledPolygonRGBA(sprMissile->getX(),sprMissile->getY(),shapeMissile,sprMissile->getScale_X(),sprMissile->getRotation_Z(),size,1,1,1,1);
//         PolygonRGBA(sprLeaves->getX(),sprLeaves->getY(),shapeLeaves,sprLeaves->getScale_X(),sprLeaves->getRotation_Z(),size,1,1,1,1);
//         PolygonRGBA(sprTerrain->getX()-300,sprTerrain->getY(),shapeTerrain,sprTerrain->getScale_X(),sprTerrain->getRotation_Z(),size,1,1,1,1);
//         filledPolygonRGBA(sprTerrain->getX()-300,sprTerrain->getY()+300,shapeTerrain,sprTerrain->getScale_X(),sprTerrain->getRotation_Z(),size,1,1,1,1);

//         LineRGBA(0,-100,0,100,size,0,0,1,0.5);
//         LineRGBA(-100,0,100,0,size,0,0,1,0.5);

        window->sync();
        SDL_Delay(10);
    }

     engine->shutdownAll();

   return EXIT_SUCCESS;
}
