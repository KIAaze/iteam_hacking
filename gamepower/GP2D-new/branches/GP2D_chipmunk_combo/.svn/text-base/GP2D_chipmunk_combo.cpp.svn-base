#include "Chipmunk-4.1.0/src/chipmunk.h"

#include "gp2d/gp2d.h"
using namespace gp;

#include <stdlib.h>
#include <iostream>
#include <cmath>
using namespace std;

#include "polygon.cpp"

int Nshapes=0;
int TYPE=3;

ostream& operator<<(ostream& a, const cpVect& b)
{
        a<<"("<<b.x<<","<<b.y<<")";
        return(a);
};

void drawLine(GLfloat x1,GLfloat y1,GLfloat x2,GLfloat y2) {
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glColor4f(0.0f, 1.0f, 0.0f, 0.5f);
    glLineWidth(5.0f);
    glBegin(GL_LINES);
        glVertex2f(x1,y1);
        glVertex2f(x2,y2);
    glEnd();
}

class GP_chipmunk_combo
{
    public:
		char name[256];
		GPSprite sprite;
		cpBody* body;
		vector <cpShape*> shape;
		cpSpace* space;
    public:
        void Build(GPTexture* tex, cpSpace* a_space)
        {
            sprite=GPSprite(tex);
            space=a_space;

            ConvexPolygon polyset;

            SimplePolygon BB=CreateBoundingBoxFromTexture(tex);
//             polyset.addPolygon(BB);

/*            SimplePolygon BB=CreateBoundingBoxFromTexture(tex);
            SimplePolygon triangle1;
            SimplePolygon triangle2;
            triangle1.addVertex(BB.getVertex(0));
            triangle1.addVertex(BB.getVertex(1));
            triangle1.addVertex(BB.getVertex(2));
            triangle2.addVertex(BB.getVertex(2));
            triangle2.addVertex(BB.getVertex(3));
            triangle2.addVertex(BB.getVertex(0));
            polyset.addPolygon(triangle1);
            polyset.addPolygon(triangle2);*/
            
            polyset=CreateConvexPolySetFromTexture(tex,TYPE);

            cpFloat m=1;//mass
            cpFloat inertia=1;//inertia
            body=cpBodyNew(m,inertia);
            inertia=0;

            int N_polys=polyset.getSize();
            cout<<"N_polys="<<N_polys<<endl;

            shape.resize(N_polys);
            Nshapes+=N_polys;
            
            for(int i=0;i<N_polys;i++)
            {
                SimplePolygon poly=polyset.getPolygon(i);
                SDL_Surface* surf = tex->getSurface();
                poly.addVector(GPVector(-surf->w/2.0,surf->h/2.0));
                int N=poly.getSize();
                cpVect* verts=new cpVect[N];
                for(int j=0;j<N;j++)
                {
//                     verts[N-1-j]=cpv(poly.getVertex(j).getX(),poly.getVertex(j).getY());
                    verts[j]=cpv(poly.getVertex(j).getX(),poly.getVertex(j).getY());
                }
                cpVect offset=cpvzero;
                inertia+=cpMomentForPoly(m/(double)N_polys, poly.getSize(), verts, offset);
    
                shape[i] = cpPolyShapeNew(body, poly.getSize(), verts, offset);
                cpSpaceAddShape(space,shape[i]);
                delete verts;
            }

            cout<<"inertia="<<inertia<<endl;
//             cpBodySetMoment(body,inertia);
//             cpBodySetMoment(body,1/*inertia*/);
            SetBBInertia(m,BB,tex);
            cpSpaceAddBody(space,body);

        }
		GP_chipmunk_combo()
		{
			cout<<"GP_chipmunk_combo: default constructor called"<<endl;
			sprintf(name,"Default name");
		}
		GP_chipmunk_combo(const char* a_name)
		{
			cout<<"GP_chipmunk_combo: default constructor called"<<endl;
			sprintf(name,"%s",a_name);
		}
		GP_chipmunk_combo(GPTexture* tex, cpSpace* a_space)
		{
			cout<<"GP_chipmunk_combo: constructor called"<<endl;
			sprintf(name,"Default name");
            Build(tex,a_space);
		}
		GP_chipmunk_combo(GPTexture* tex, cpSpace* a_space,const char* a_name)
		{
			cout<<"GP_chipmunk_combo: constructor called"<<endl;
			sprintf(name,"%s",a_name);
            Build(tex,a_space);
		}
		~GP_chipmunk_combo() throw (GPException)
		{
			cout<<"GP_chipmunk_combo: destructor called"<<endl;
			cout<<"name="<<name<<endl;
			this->remove();
			for(unsigned int i=0;i<shape.size();i++) cpShapeFree(shape[i]);
            Nshapes-=shape.size();
			cpBodyFree(body);
		}
		
		//copy constructor
		GP_chipmunk_combo(const GP_chipmunk_combo& a_GP_chipmunk_combo)
		{
			cout<<"GP_chipmunk_combo: copy constructor called"<<endl;
			sprintf(name,"%s",a_GP_chipmunk_combo.name);

			sprite=a_GP_chipmunk_combo.sprite;
			body=cpBodyNew(a_GP_chipmunk_combo.body->m,a_GP_chipmunk_combo.body->i);
			(body->p).x=(a_GP_chipmunk_combo.body->p).x;
			(body->p).y=(a_GP_chipmunk_combo.body->p).y;
			body->a=a_GP_chipmunk_combo.body->a;
            space=a_GP_chipmunk_combo.space;
            cpSpaceAddBody(space,body);
            shape.resize(a_GP_chipmunk_combo.shape.size());
            Nshapes+=a_GP_chipmunk_combo.shape.size();
            
            for(unsigned int i=0;i<shape.size();i++)
            {
                //we cast shape into a temporary cpPolyShape variable to access the cpPolyShape properties
                cpPolyShape *foo=(cpPolyShape *)(a_GP_chipmunk_combo.shape[i]);
                shape[i]=cpPolyShapeNew(body, foo->numVerts, foo->verts, cpvzero);//We don't need an offset since foo->verts is already offset. ;)
    
                shape[i]->bb=a_GP_chipmunk_combo.shape[i]->bb;
                shape[i]->collision_type=a_GP_chipmunk_combo.shape[i]->collision_type;
                shape[i]->group=a_GP_chipmunk_combo.shape[i]->group;
                shape[i]->layers=a_GP_chipmunk_combo.shape[i]->layers;
                shape[i]->data=a_GP_chipmunk_combo.shape[i]->data;
                shape[i]->e=a_GP_chipmunk_combo.shape[i]->e;
                shape[i]->u=a_GP_chipmunk_combo.shape[i]->u;
                shape[i]->surface_v=a_GP_chipmunk_combo.shape[i]->surface_v;
                cpSpaceAddShape(space,shape[i]);
            }

		}
		//assignment operator
		GP_chipmunk_combo& operator=(const GP_chipmunk_combo& a_GP_chipmunk_combo)
		{
			cout<<"GP_chipmunk_combo: assignment operator called"<<endl;
			if(this != &a_GP_chipmunk_combo)
			{
				// first delete old
				this->remove();
				for(unsigned int i=0;i<shape.size();i++) cpShapeFree(shape[i]);
                Nshapes-=shape.size();

				cpBodyFree(body);
				
				//then copy
				sprintf(name,"%s",a_GP_chipmunk_combo.name);
				sprite=a_GP_chipmunk_combo.sprite;
				body=cpBodyNew(a_GP_chipmunk_combo.body->m,a_GP_chipmunk_combo.body->i);
				(body->p).x=(a_GP_chipmunk_combo.body->p).x;
				(body->p).y=(a_GP_chipmunk_combo.body->p).y;
				body->a=a_GP_chipmunk_combo.body->a;
                space=a_GP_chipmunk_combo.space;
                cpSpaceAddBody(space,body);

                shape.resize(a_GP_chipmunk_combo.shape.size());
                Nshapes+=a_GP_chipmunk_combo.shape.size();
                
                for(unsigned int i=0;i<shape.size();i++)
                {
                    //we cast shape into a temporary cpPolyShape variable to access the cpPolyShape properties
                    cpPolyShape *foo=(cpPolyShape *)(a_GP_chipmunk_combo.shape[i]);
                    shape[i]=cpPolyShapeNew(body, foo->numVerts, foo->verts, cpvzero);//We don't need an offset since foo->verts is already offset. ;)
                    shape[i]->bb=a_GP_chipmunk_combo.shape[i]->bb;
                    shape[i]->collision_type=a_GP_chipmunk_combo.shape[i]->collision_type;
                    shape[i]->group=a_GP_chipmunk_combo.shape[i]->group;
                    shape[i]->layers=a_GP_chipmunk_combo.shape[i]->layers;
                    shape[i]->data=a_GP_chipmunk_combo.shape[i]->data;
                    shape[i]->e=a_GP_chipmunk_combo.shape[i]->e;
                    shape[i]->u=a_GP_chipmunk_combo.shape[i]->u;
                    shape[i]->surface_v=a_GP_chipmunk_combo.shape[i]->surface_v;
                    cpSpaceAddShape(space,shape[i]);
                }
			}
			return *this;
		}
	
		void remove()
		{
			for(unsigned int i=0;i<shape.size();i++) cpSpaceRemoveShape(space, shape[i]);
			cpSpaceRemoveBody(space, body);
		}
		void setPosition(GLfloat x, GLfloat y)
		{
			(body->p).x=x;
			(body->p).y=y;
		}
		void setRotation_Z(GLfloat a)
		{
			body->a=DegToRad(a);
		}
		void draw()
		{
            int H=sprite.getHeight();
            int W=sprite.getWidth();
			int a=-W/2.;
			int b=H/2.;
			GLfloat alpha=body->a;
			GLfloat delta_x = a*cos(alpha)-b*sin(alpha);
			GLfloat delta_y = a*sin(alpha)+b*cos(alpha);
			sprite.setPosition((body->p).x+delta_x,(body->p).y+delta_y);
			sprite.setRotation_Z(RadToDeg(body->a));
			sprite.draw();
		}
        void SetElasticity(double E)
        {
            for(unsigned int i=0;i<shape.size();i++)
            {
                this->shape[i]->e=E;
            }
        };
        void SetFriction(double U)
        {
            for(unsigned int i=0;i<shape.size();i++)
            {
                this->shape[i]->u=U;
            }
        };
        void SetBBInertia(cpFloat mass, SimplePolygon poly, GPTexture* tex)
        {
            SDL_Surface* surf = tex->getSurface();
            poly.addVector(GPVector(-surf->w/2.0,surf->h/2.0));
            int N=poly.getSize();
            cpVect* verts=new cpVect[N];
            for(int j=0;j<N;j++)
            {
                //                     verts[N-1-j]=cpv(poly.getVertex(j).getX(),poly.getVertex(j).getY());
                verts[j]=cpv(poly.getVertex(j).getX(),poly.getVertex(j).getY());
            }
            cpVect offset=cpvzero;
            cpFloat inertia = cpMomentForPoly(mass, poly.getSize(), verts, offset);
            delete verts;

            cpBodySetMoment(body,inertia);
            cout<<"inertia="<<inertia<<endl;
        };
};

//some global variables. Should be put into some class which the handlers inherit (or need a way to pass args to handlers)
vector <GP_chipmunk_combo> SpriteVector;
cpSpace* space;//=cpSpaceNew();
GPTexture* texSusi;// = new GPTexture("susi.png");
GPTexture* texMissile;// = new GPTexture("susi.png");
GPTexture* texLeaves;// = new GPTexture("susi.png");
GPTexture* texSprite[5];

bool physics = false;

class TogglePhysics : public GPKeyAction {
public:
    void keyDown(GPKeyEvent& event) {
		physics=not(physics);
        cout << "Physics: " <<physics<< endl;
    }
};

class MouseAction : public GPMouseAction {
public:
    MouseAction() {}
    ~MouseAction() {}

    void mouseButtonUp(GPMouseEvent& event) {
        
        clog << "HAI!" << event.getButton() << endl;
		GPVector ScreenCoords=GPVector(event.getX(),event.getY());
        GPVector WindowCoords=screen2window(window,cam,ScreenCoords);
        GLfloat x=WindowCoords.getX();
        GLfloat y=WindowCoords.getY();
        cout<<"("<<event.getX()<<","<<event.getY()<<")->("<<x<<","<<y<<")"<<endl;
		if(event.getButton()==1) {
          SpriteVector.push_back(GP_chipmunk_combo(texSusi,space));
          SpriteVector[SpriteVector.size()-1].SetElasticity(1.0);
          SpriteVector[SpriteVector.size()-1].SetFriction(0.0);
        }
        else if(event.getButton()==3) {
          SpriteVector.push_back(GP_chipmunk_combo(texSprite[rand()%5],space));
          SpriteVector[SpriteVector.size()-1].SetElasticity(0.5);
          SpriteVector[SpriteVector.size()-1].SetFriction(1.0);
        }
        else {
          SpriteVector.push_back(GP_chipmunk_combo(texMissile,space));
          SpriteVector[SpriteVector.size()-1].SetElasticity(0.3);
          SpriteVector[SpriteVector.size()-1].SetFriction(0.2);
        }
		SpriteVector[SpriteVector.size()-1].setPosition(WindowCoords.getX(),WindowCoords.getY());
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

void SomeFunction(const GP_chipmunk_combo& s,GPTexture* a_texSusi, cpSpace* a_space)
{
  GP_chipmunk_combo B(a_texSusi,a_space);
  B=s;
}
int class_testing(GPTexture* a_texSusi, cpSpace* a_space)
{
  GP_chipmunk_combo A(a_texSusi,a_space);
  GP_chipmunk_combo B(A);
  //Or GP_chipmunk_combo B = A;
  A = A;
  SomeFunction(A,a_texSusi,a_space);
  GP_chipmunk_combo C = A;

  return 0;
}

void clean_physics()
{
	cout<<"===PRE-FREE==="<<endl;
// 	cpSpaceDestroy(space);
	SpriteVector.clear();
    cpSpaceFree(space);
	cout<<"===POST-FREE==="<<endl;
}

int main(void)
{
    cpInitChipmunk(); /* Actually, that's pretty much it */

	space=cpSpaceNew();

    space->gravity=cpv(0,-100);
	space->elasticIterations=7;

    cpFloat dt=0.008;

    cpBody* staticBody = cpBodyNew(INFINITY, INFINITY);
    cpShape* bottom=cpSegmentShapeNew(staticBody, cpv(-320,-240), cpv(320,-240), 5.0f);
    cpShape* leftside=cpSegmentShapeNew(staticBody, cpv(-320,-240), cpv(-320,240), 5.0f);
    cpShape* rightside=cpSegmentShapeNew(staticBody, cpv(320,-240), cpv(320,240), 5.0f);
    cpSpaceAddStaticShape(space,bottom);
    cpSpaceAddStaticShape(space,leftside);
    cpSpaceAddStaticShape(space,rightside);

    cpFloat dim=10;
    int count=1000;
    cpSpaceResizeStaticHash(space, dim, count);
    cpSpaceResizeActiveHash(space, dim, count);

    GPEngine* engine = GPEngine::getInstance();
    engine->initAll();
	window = GPWindow::getInstance();
    window->setRenderMode(GPWindow::GP_OPENGL);
    window->setWindowTitle("Gamepower 2D Testing App");
    window->createWindow(640, 480, 24);
    window->setGraphicsDefaults();

    GPKeyboardHandler* handler = new GPKeyboardHandler();
    handler->registerKeyAction(GPKeyEvent::GP_KEY_ESCAPE, new ExitAction());
    handler->registerKeyAction(GPKeyEvent::GP_KEY_SPACE, new TogglePhysics());

	GPMouseHandler* mhandler = new GPMouseHandler();
    mhandler->registerMouseAction(new MouseAction());

    GPInputProcessor* proc = new GPInputProcessor();
    proc->addHandler(handler);
    proc->addHandler(mhandler);

    cam = new GPGameCamera(window->getHeight() / 2);
    cam->setPosition(0.0f, 0.0f);

	texSprite[0] = new GPTexture("susi.png");
    texSprite[1] = new GPTexture("debin.png");
    texSprite[2] = new GPTexture("fidori.png");
    texSprite[3] = new GPTexture("genti.png");
    texSprite[4] = new GPTexture("lini.png");
    
    texSusi = new GPTexture("susi.png");
    texMissile = new GPTexture("missile.png");
    texLeaves = new GPTexture("iteam_leaves_animation.png");

    ConvexPolygon polySprite[5];
    ConvexPolygon polyMissile;

    cout<<"=================="<<endl;
    for(int l_TYPE=0;l_TYPE<4;l_TYPE++)
    {
        cout<<"++++++++++++++++"<<endl;
        cout<<"Susi:"<<endl;
        polySprite[0]=CreateConvexPolySetFromTexture(texSprite[0],l_TYPE);
        cout<<"Debin:"<<endl;
        polySprite[1]=CreateConvexPolySetFromTexture(texSprite[1],l_TYPE);
        cout<<"Fidori:"<<endl;
        polySprite[2]=CreateConvexPolySetFromTexture(texSprite[2],l_TYPE);
        cout<<"Genti:"<<endl;
        polySprite[3]=CreateConvexPolySetFromTexture(texSprite[3],l_TYPE);
        cout<<"Lini:"<<endl;
        polySprite[4]=CreateConvexPolySetFromTexture(texSprite[4],l_TYPE);
        cout<<"Missile:"<<endl;
        polyMissile=CreateConvexPolySetFromTexture(texMissile,l_TYPE);
    }
    cout<<"=================="<<endl;

    ConvexPolygon polyLeaves=CreateConvexPolySetFromTexture(texLeaves,TYPE);
    ConvexPolygon polySusi=CreateConvexPolySetFromTexture(texSusi,TYPE);
    
    polySusi.setPosition(0,0);
    polyMissile.setPosition(100,0);
    polyLeaves.setPosition(0,100);
    
    for(int i=0;i<5;i++) cout<<"polySprite[i].getSize()="<<polySprite[i].getSize()<<endl;
    cout<<"polySusi.getSize()="<<polySusi.getSize()<<endl;
    cout<<"polyMissile.getSize()="<<polyMissile.getSize()<<endl;
    cout<<"polyLeaves.getSize()="<<polyLeaves.getSize()<<endl;

    class_testing(texSusi,space);

//     vector <GP_chipmunk_combo> sprSusi1;
//     sprSusi1.push_back(GP_chipmunk_combo(texSusi,space));
//     sprSusi1[sprSusi1.size()-1].setPosition(0.0f, 0.0f);
//     GP_chipmunk_combo S(texSusi,space,"normal element");
//     S.setPosition(0,0);
//     S.setRotation_Z(0);

//     S.sprite.setRotCenter(64,-64,0);
//     cout<<"S.sprite.getRotCenter_X()="<<S.sprite.getRotCenter_X()<<endl;
//     cout<<"S.sprite.getRotCenter_Y()="<<S.sprite.getRotCenter_Y()<<endl;
//     cout<<"S.sprite.getRotCenter_Z()="<<S.sprite.getRotCenter_Z()<<endl;

    bottom->e=1.0;
    bottom->u=0.0;
/*    S.SetElasticity(0.0);
    S.SetFriction(0.0);*/
/*    cout<<"S elasticity="<<S.shape->e<<endl;
    cout<<"S friction="<<S.shape->u<<endl;*/
    cout<<"bottom elasticity="<<bottom->e<<endl;
    cout<<"bottom friction="<<bottom->u<<endl;
    
//     GP_chipmunk_combo B=S;
/*    B.setPosition(100,100);
    B.setRotation_Z(46);*/
//     GP_chipmunk_combo C=S;
/*    C.setPosition(200,200);
    C.setRotation_Z(180);*/
//     GP_chipmunk_combo D=S;
/*    D.setPosition(300,300);
    D.setRotation_Z(270);*/
	Uint32 start = 0;
	start = SDL_GetTicks();
	bool random_susi=true;

    GPFont* font = new GPFont("font.ttf", 12);
    GPText* text1 = new GPText(font);
    text1->setRenderType(GPText::GP_RENDER_NICEST);
    text1->setX(0);
    text1->setY(0);
    text1->setZ(12);
    text1->setText("Hi 1");

    int frames=0;
    GPTimer timer;
    timer.start();

    while(!quit) {

		proc->pollEvents();
        window->clearScreen();
// 		S.draw();
// 		B.draw();
// 		C.draw();
// 		D.draw();

        int FPS;
        int milliseconds=timer.getTicks();
//         cout<<timer.getTicks()<<endl;
        if(milliseconds>1000) {
            FPS=frames/(double)(milliseconds/1000.0);
/*            cout<<"frames="<<frames<<endl;
            cout<<"milliseconds="<<milliseconds<<endl;*/
            cout<<"FPS="<<FPS<<" SpriteVector.size()="<<SpriteVector.size()<<" Nshapes="<<Nshapes<<endl;
            frames=0;
            timer.reset();
        }
//         text1->setText("FPS=%i",FPS);
//         text1->draw();

//         polySusi.draw();
//         polyMissile.draw();
//         polyLeaves.draw();

// 		Uint32 T=SDL_GetTicks() - start;
// 		if(T>1000 && random_susi)
// 		{
// 			random_susi=false;
// 			int x = rand() % 640 - 320;
// 			int y = rand() % 480 - 240;
// 			cout << "Timer: " << T << " -> ("<<x<<","<<y<<")"<<endl;
// 			SpriteVector.push_back(GP_chipmunk_combo(texSusi,space,"vector element"));
// 			SpriteVector[SpriteVector.size()-1].setPosition(x,y);
// 			start = SDL_GetTicks();
// 		}

		for(unsigned int i=0;i<SpriteVector.size();i++)
		{
			SpriteVector[i].draw();
		}
/*		drawLine(100,240,100,-240);
		drawLine(320,100,-320,100);*/
		drawLine(-320,-240,320,-240);//bottom
        drawLine(-320,-240,-320,240);//left
        drawLine(320,-240,320,240);//right

// 		drawLine(0,0,320,240);//diagonal
// 		drawLine(0,0,320,0);//Xbottom
// 		drawLine(0,0,0,240);//Ybottom

		window->sync();
		if(physics) cpSpaceStep(space,dt);

        frames++;
    }

    delete font;
    delete text1;
    engine->shutdownAll();

	atexit(clean_physics);
    return(0);
}
