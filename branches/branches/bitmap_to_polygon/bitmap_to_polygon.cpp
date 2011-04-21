#include "gp2d/gp2d.h"
using namespace gp;

#include <deque>
#include <iostream>
using namespace std;

bool quit = false;

class ExitAction : public GPKeyAction {
public:
    ExitAction() {}
    ~ExitAction() {}

    void keyDown(GPKeyEvent& event) {
        cout << "Exiting" << endl;
        quit = true;
    }
};

GPVector GetFirst(SDL_Surface* bitmap)
{
    for (int x = bitmap->w - 1; x > -1; --x)
    {
        for (int y = 0; y < bitmap->h; ++y)
        {
            if (GetPixelA(bitmap,x,y))
            {
                cout<<"First="<<GPVector(x, y)<<endl;
                return GPVector(x, y);
            }
        }
    }
    return GPVector();
}

bool IsInLine(GPVector p1, GPVector p2, GPVector p3)
{
    int slope1 = (p1.getY() - p2.getY());
    int slope2 = (p2.getY() - p3.getY());
    return ( 0 == slope1 && 0 == slope2 ) ||
        ((p1.getX() - p2.getX()) / (double)slope1) == ((p2.getX() - p3.getX()) / (double)slope2);
}

deque <GPVector> Reduce(deque<GPVector> L) throw(GPException)
{
    deque<GPVector> result;
    GPVector p1 = L[L.size() - 2];
    GPVector p2 = L[L.size() - 1];
    GPVector p3;
    for (unsigned int index = 0; index < L.size(); ++index, p2 = p3)
    {
        p3 = L[index];
        if (!IsInLine( p1, p2, p3))
        {
            result.push_back(GPVector(p2.getX(), p2.getY()));
            p1 = p2;
        }
    }
    return result;
}

GPVector GetNextVertex(SDL_Surface* bitmap, GPVector current, GPVector last) throw(GPException)
{
    deque <GPVector> bitmapPoints(8);
    bitmapPoints[0]=GPVector (1,1);
    bitmapPoints[1]=GPVector (0,1);
    bitmapPoints[2]=GPVector (-1,1);
    bitmapPoints[3]=GPVector (-1,0);
    bitmapPoints[4]=GPVector (-1,-1);
    bitmapPoints[5]=GPVector (0,-1);
    bitmapPoints[6]=GPVector (1,-1);
    bitmapPoints[7]=GPVector (1,0);

    int offset = 0;
    GPVector point;
    for (unsigned int index = 0; index < bitmapPoints.size(); ++index)
    {
        point=current+bitmapPoints[index];
        if (point==last)
        {
            offset = index + 1;
            break;
        }
    }
    for (unsigned int index = 0; index < bitmapPoints.size(); ++index)
    {
        point=current+bitmapPoints[(index + offset) % bitmapPoints.size()];
        if (point.getX() >= 0 && point.getX() < bitmap->w &&
            point.getY() >= 0 && point.getY() < bitmap->h &&
            GetPixelA(bitmap,point.getX(),point.getY()) )
        {
            return point;
        }
    }
    throw GPException("The image has an area with less then 3 pixels (possibly an artifact).", "bitmap");
}

deque <GPVector> CreateFromBitmap(SDL_Surface* bitmap, GPVector first) throw(GPException)
{
    GPVector current = first;
    GPVector last = first - GPVector(0, 1);
    deque<GPVector> result;
    do
    {
        result.push_back(current);
        current = GetNextVertex(bitmap, current, last);
        last = result[result.size() - 1];
    } while (current != first);
    if (result.size() < 3) { throw GPException("The image has an area with less then 3 pixels (possibly an artifact).", "bitmap"); }

    deque<GPVector>::iterator iter = find(result.begin(), result.end(), GPVector(0,0,0));
    if (iter == result.end())
    {
      cout << "(0,0,0) not found\n";
    }
    else
    {
      cout << "found (0,0,0) at element " << iter - result.begin() << " (starts at 0)\n";
    }
    cout<<"result[0]="<<result[0]<<endl;

    return result;
}

deque <GPVector> CreateFromBitmap(SDL_Surface* bitmap)
{
    deque <GPVector> ret=Reduce(CreateFromBitmap(bitmap, GetFirst(bitmap)));
    cout<<"ret[0]="<<ret[0]<<endl;
    return ret;
}

deque <GPVector> CreateFromTexture(GPTexture* tex)
{
  SDL_Surface* surf = tex->getSurface();
  deque <GPVector> V=CreateFromBitmap(surf);
  int N=V.size();
  for(int i=0;i<N;i++) V[i].setY(-V[i].getY());
  return(V);
}

deque <GPVector> CreateBoundingBoxFromTexture(GPTexture* tex)
{
  SDL_Surface* surf = tex->getSurface();
  deque <GPVector> polygon(4);
  polygon[0]=GPVector(0,-surf->h);
  polygon[1]=GPVector(surf->w,-surf->h);
  polygon[2]=GPVector(surf->w,0);
  polygon[3]=GPVector(0,0);
  return(polygon);
}

class SimplePolygon : public GPObject {
  private:
    deque <GPVector> Vertices;
    GLfloat R,G,B,A;
  public:
    SimplePolygon(){setRGBA(1,1,1,1);};
    SimplePolygon(deque <GPVector> V):Vertices(V){setRGBA(1,1,1,1);};
    deque <GPVector> getVertices() {return(Vertices);};
    void setVertices(deque <GPVector> V) {Vertices=V;};
    void addVertex(GPVector V) {Vertices.push_back(V);};
    void popLastVertex() {Vertices.pop_back();};
    void popFirstVertex() {Vertices.pop_front();};
    void removeVertex(int DeadNode) {
        int N=Vertices.size();
        deque <GPVector> NewVertices(N-1);
        int dst_idx=0;
        for(int src_idx=0;src_idx<N;src_idx++){
            if(src_idx!=DeadNode){
                NewVertices[dst_idx]=Vertices[src_idx];
                dst_idx++;
            }
        }
        this->setVertices(NewVertices);
    };
    void setVertex(int i,GPVector V) {Vertices[i]=V;};
    void sortVertices() {sort(Vertices.begin(),Vertices.end());};
    GPVector getVertex(int i) {return Vertices[i];};
    int getSize(){return Vertices.size();};
    void clear(){Vertices.clear();};
    void setRGBA(GLfloat a_R, GLfloat a_G, GLfloat a_B, GLfloat a_A) {R=a_R;G=a_G;B=a_B;A=a_A;};
    void draw(){
      PolygonRGBA(this->getX(),this->getY(),Vertices,getScale_X(),getRotation_Z(),1,R,G,B,A);
    };
    void draw(GLfloat x, GLfloat y,GLfloat scale,GLfloat angle){
      PolygonRGBA(x+this->getX(),y+this->getY(),Vertices,scale*getScale_X(),angle+getRotation_Z(),1,R,G,B,A);
    };
    void scale(GLfloat S){
      for(unsigned int i=0;i<Vertices.size();i++) {Vertices[i]=S*Vertices[i];}
    }
};

class ConvexPolygon : public GPObject {
  private:
    deque <SimplePolygon> Polygons;
  public:
    ConvexPolygon(){};
    ConvexPolygon(deque <SimplePolygon> V):Polygons(V){};
    deque <SimplePolygon> getPolygons() {return(Polygons);};
    void setPolygons(deque <SimplePolygon> V) {Polygons=V;};
    void addPolygon(SimplePolygon V) {Polygons.push_back(V);};
    void setPolygon(int i,SimplePolygon V) {Polygons[i]=V;};
    SimplePolygon getPolygon(int i) {return Polygons[i];};
    int getSize(){return Polygons.size();};
    void clear(){Polygons.clear();};
    void draw(){for(unsigned int i=0;i<Polygons.size();i++) Polygons[i].draw(this->getX(),this->getY(),getScale_X(),getRotation_Z());};
};

ConvexPolygon CreateSetOfConvexPolygons(SimplePolygon P)
{
    ConvexPolygon C;
    return(C);
}

bool TurnRight(GPVector A,GPVector B,GPVector C)
{
    //cout<<"A="<<A<<" B="<<B<<" C="<<C<<endl;
    //cout<<"TurnRight="<<((B-A).cross(C-B).getZ()<0)<<endl;
    return((B-A).cross(C-B).getZ()<=0);
}

bool TurnLeft(GPVector A,GPVector B,GPVector C)
{
    return((B-A).cross(C-B).getZ()>=0);
}

bool Above(GPVector Point, GPVector leftmost, GPVector rightmost) {
    return((rightmost-leftmost).cross(Point-leftmost).getZ()>0);
}

//for clockwise polygons
SimplePolygon CreateConvexHull(SimplePolygon P)
{
    int NP=P.getSize();
    if(NP<=3) return(P);//don't waste time :p
    SimplePolygon C;
    C.addVertex(P.getVertex(0));
    C.addVertex(P.getVertex(1));
    int i=2;
    int NC;
    while((i%NP)!=0)
    {
        NC=C.getSize();
        if(TurnRight(C.getVertex(NC-2),C.getVertex(NC-1),P.getVertex(i)))
        {
            C.addVertex(P.getVertex(i));
            i=(i+1)%NP;
        }
        else
        {
            C.popLastVertex();
        }
    }
    //at this point we have i=0, but we haven't checked vertices 0 and N-1 yet.
    NC=C.getSize();
    if(TurnRight(C.getVertex(NC-2),C.getVertex(NC-1),P.getVertex(0)))
    {
        i=1;
    }
    else
    {
        C.popLastVertex();//remove vertex N-1
    }
    NC=C.getSize();
    if(TurnRight(C.getVertex(NC-1),C.getVertex(0),P.getVertex(1)))
    {
        i=2;
    }
    else
    {
        C.popFirstVertex();//remove vertex 0
    }
    
    return(C);
}

//for counter-clockwise polygons
SimplePolygon CreateConvexHull2(SimplePolygon P)
{
    int NP=P.getSize();
    if(NP<=3) return(P);//don't waste time :p
    SimplePolygon C;
    C.addVertex(P.getVertex(0));
    C.addVertex(P.getVertex(1));
    int i=2;
    int NC;
    while((i%NP)!=0)
    {
        NC=C.getSize();
        if(TurnLeft(C.getVertex(NC-2),C.getVertex(NC-1),P.getVertex(i)))
        {
            C.addVertex(P.getVertex(i));
            i=(i+1)%NP;
        }
        else
        {
            C.popLastVertex();
        }
    }
    //at this point we have i=0, but we haven't checked vertices 0 and N-1 yet.
    NC=C.getSize();
    if(TurnLeft(C.getVertex(NC-2),C.getVertex(NC-1),P.getVertex(0)))
    {
        i=1;
    }
    else
    {
        C.popLastVertex();//remove vertex N-1
    }
    NC=C.getSize();
    if(TurnLeft(C.getVertex(NC-1),C.getVertex(0),P.getVertex(1)))
    {
        i=2;
    }
    else
    {
        C.popFirstVertex();//remove vertex 0
    }
    
    return(C);
}

GPWindow* window;
GPGameCamera* cam;
deque <GPVector> CustomPoints;
SimplePolygon Triangle;
ConvexPolygon superman;
vector <SimplePolygon> CustomPolys;
vector <SimplePolygon> CustomPolysLower;
vector <SimplePolygon> CustomPolysUpper;
vector <SimplePolygon> CustomPolysMidline;
vector <SimplePolygon> CustomConvexHulls;

void wait(int ms)
{
    GPTimer timer;
    timer.start();
    while(timer.getTicks()<ms) {}
    timer.reset();//cout<<"Time over"<<endl; 
    timer.stop();
}

void SpecialDraw(deque <GPVector> pts,int N)
{
  for(int i=1;i<min(N,(int)pts.size());i++) LineRGBA(pts[i-1].getX(),pts[i-1].getY(),pts[i].getX(),pts[i].getY(),10,1,1,1,1);
}

//for any polygons
SimplePolygon CreateConvexHull3(SimplePolygon P)
{
    deque <GPVector> S=P.getVertices();
    sort(S.begin(),S.end());//Sort all points in S based on their position on the X axis
    GPVector left=S.front();//Designate point left as the leftmost point
    GPVector right=S.back();//Designate point right as the rightmost point
    S.pop_front();S.pop_back();//Remove left and right from S

    SimplePolygon Midline;
    Midline.addVertex(left);
    Midline.addVertex(right);
    CustomPolysMidline.push_back(Midline);
    CustomPolysMidline.back().setRGBA(1,1,1,1);

//     Midline.draw();
//     window->sync();
//     wait(1000);

    deque <GPVector> upper;
    deque <GPVector> lower;
    while(S.size()>0) {//While there are still points in S
      GPVector Point=S.front();S.pop_front();//remove Point from S
      if(Above(Point,left,right)) {//if Point is above the line from left to right
	  upper.push_back(Point);//add Point to the end of array upper
	}
      else {//else
	  lower.push_back(Point);//add Point to the end of array lower
	}
    }

//     for(int i=0;i<upper.size();i++) filledSquareRGBA(upper[i].getX(),upper[i].getY(),10,0,0,1,0,1);
//     for(int i=0;i<lower.size();i++) filledSquareRGBA(lower[i].getX(),lower[i].getY(),10,0,0,0,1,1);
//     window->sync();
//     wait(1000);

    //
    // Construct the lower hull
    //
    deque <GPVector> lower_hull;
    lower.push_back(right);
    lower_hull.push_back(left);//Add left to lower_hull
    while(lower.size()>0) {//While lower is not empty
      cout<<lower[0]<<endl;
      lower_hull.push_back(lower[0]);//add lower[0] to the end of lower_hull
//       SpecialDraw(lower_hull,lower_hull.size());window->sync();wait(1000);
      lower.pop_front();//remove lower[0] from lower
      int N=lower_hull.size();
      while(N>=3 && TurnRight(lower_hull[N-3],lower_hull[N-2],lower_hull[N-1])) {//while size(lower_hull) >= 3 and the last 3 points lower_hull are not convex
	lower_hull[N-2]=lower_hull[N-1];lower_hull.pop_back();//remove the next to last element from lower_hull
// 	SpecialDraw(lower_hull,lower_hull.size());window->sync();wait(1000);
	N=lower_hull.size();
      }
    }

    SimplePolygon LH(lower_hull);
/*    LH.setRGBA(0,0,1,1);
    SpecialDraw(lower_hull,lower_hull.size());*/
    CustomPolysLower.push_back(LH);
    CustomPolysLower.back().setRGBA(0,0,1,1);
//     window->sync();
//     wait(1000);

    //
    // Construct the upper hull
    //
    deque <GPVector> upper_hull;
    upper.push_back(right);
    upper_hull.push_back(left);//Add left to upper_hull
    while(upper.size()>0) {//While upper is not empty
      upper_hull.push_back(upper[0]);//add upper[0] to the end of upper_hull
//       SpecialDraw(upper_hull,upper_hull.size());window->sync();wait(1000);
      upper.pop_front();//remove upper[0] from upper
      int N=upper_hull.size();
      while(N>=3 && TurnLeft(upper_hull[N-3],upper_hull[N-2],upper_hull[N-1])) {//while size(upper_hull) >= 3 and the last 3 points upper_hull are not convex
	upper_hull[N-2]=upper_hull[N-1];upper_hull.pop_back();//remove the next to last element from upper_hull
// 	SpecialDraw(upper_hull,upper_hull.size());window->sync();wait(1000);
	N=upper_hull.size();
      }
    }

    SimplePolygon UH(upper_hull);
/*    UH.setRGBA(1,0,0,1);
    SpecialDraw(upper_hull,upper_hull.size());*/
    CustomPolysUpper.push_back(UH);
    CustomPolysUpper.back().setRGBA(1,0,0,1);
//     window->sync();
//     wait(1000);

    //
    //Merge upper_hull and lower_hull to form hull
    int Nu=upper_hull.size();
    int Nl=lower_hull.size();
    deque <GPVector> hull(Nu+Nl-2);
    for(int i=0;i<Nu;i++) hull[i]=upper_hull[i];
    for(int i=Nu;i<Nu+Nl-2;i++) hull[i]=lower_hull[(Nl-2)+(Nu)-i];

//     wait(1000);

    //return hull
    SimplePolygon C(hull);
    return(C);
}

bool IsInConvexPolygon(SimplePolygon poly,GPVector M)
{
    int N=poly.getSize();
    for(int i=0;i<N;i++)
    {
        GPVector A=poly.getVertex(i);
        GPVector B=poly.getVertex((i+1)%N);
        GPVector C=poly.getVertex((i+2)%N);
        if((B-A).cross(C-A).getZ()*(B-A).cross(M-A).getZ()<=0) return(false);
    }
    return(true);
}

SimplePolygon TriangleFromPolygon(SimplePolygon poly, int i)
{
        int N=poly.getSize();
        GPVector A,B,C;
        A=poly.getVertex((i-1+N)%N);
        B=poly.getVertex((i)%N);
        C=poly.getVertex((i+1)%N);
        SimplePolygon l_Triangle;
        l_Triangle.addVertex(A);
        l_Triangle.addVertex(B);
        l_Triangle.addVertex(C);
        return l_Triangle;
}

//For clockwise polygons only!
int FindAnEar(SimplePolygon poly, int start, SimplePolygon& Ear)
{
//     cout<<"=== FindAnEar START start="<<start<<"==="<<endl;
    int N=poly.getSize();
    if(N<=0) return(-1);
    start=(start+N)%N;
    for(int i=start;i<N;i++)
    {
//         cout<<"i="<<i<<endl;
        SimplePolygon PotentialEar=TriangleFromPolygon(poly,i);
        if(TurnRight(PotentialEar.getVertex(0),PotentialEar.getVertex(1),PotentialEar.getVertex(2)))
        {
//             cout<<"turn right OK"<<endl;
            bool IsEar=true;
            for(int j=0;j<N;j++)
            {
//                 cout<<"j="<<j<<endl;
                if(j!=(i-1+N)%N && j!=(i)%N && j!=(i+1)%N)
                {
//                     cout<<"j not a point from triangle"<<endl;
                    if(IsInConvexPolygon(PotentialEar,poly.getVertex(j))) {
//                         cout<<"No, it's not an ear"<<endl;
                        IsEar=false;break;
                    }
                }
            }
            if(IsEar)
            {
                Ear=PotentialEar;
                return(i);
            }
        }
    }
    return(-1);
}

ConvexPolygon Triangulate(SimplePolygon poly)
{
    ConvexPolygon CP;
    SimplePolygon tmp;
    int ear=0;
    while(ear>=0)
    {
        ear=FindAnEar(poly,0,tmp);
//         cout<<"ear="<<ear<<endl;
        if(ear>=0){
            CP.addPolygon(tmp);
            poly.removeVertex(ear);
        }
    }
    if(poly.getSize()>2)
    {
        cout<<"FATAL ERROR: Could not completely triangulate polygon!"<<endl;
//         abort();
    }
    return(CP);
}

GPVector screen2window ( GPWindow* a_window, GPCamera* cam , GPVector a_ScreenPoint )
{
    GPVector UC(cam->getX(),cam->getY());
    GPVector CS(-a_window->getWidth()/2.,a_window->getHeight()/2.);
    GPVector SM(a_ScreenPoint.getX(),-a_ScreenPoint.getY());
    return(UC+CS+SM);
//     return(GPVector(a_ScreenPoint.getX()-a_window->getWidth()/2.,-a_ScreenPoint.getY()+a_window->getHeight()/2.));
}

int ear=0;

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
            superman=Triangulate(Triangle);
        }
        else if(event.getButton()==3) {
            cout<<"Adding point to triangle"<<endl;
            Triangle.addVertex(GPVector(x,y));
        }
        else {
            cout<<"===CLEAR ALL==="<<endl;
            Triangle.clear();
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

    cam->setPosition(100.0f, 0.0f);

    cout<<"===LOADING==="<<endl;
    cout<<"===Susi==="<<endl;
    GPTexture* texSusi = new GPTexture("susi.png");
    GPSprite* sprSusi = new GPSprite(texSusi);
    sprSusi->setPosition(0.0f, 0.0f);
    deque <GPVector> shapeSusi=CreateFromTexture(texSusi);
    SimplePolygon bbSusi(CreateBoundingBoxFromTexture(texSusi));
    SimplePolygon polySusi(shapeSusi);
//    SimplePolygon hullSusi=CreateConvexHull(polySusi);
    SimplePolygon hullSusi=CreateConvexHull3(polySusi);
//     polySusi.scale(5);
//     polySusi.setPosition(-100,100);
    
//     hullSusi.setPosition(-100,100);

    ConvexPolygon ConvexSusi=Triangulate(polySusi);

    cout<<"===Missile==="<<endl;
    GPTexture* texMissile = new GPTexture("missile.png");
    GPSprite* sprMissile = new GPSprite(texMissile);
    sprMissile->setPosition(100.0f, -10.0f);
    deque <GPVector> shapeMissile=CreateFromTexture(texMissile);

    cout<<"===Leaves==="<<endl;
    GPTexture* texLeaves = new GPTexture("iteam_leaves_animation.png");
    GPSprite* sprLeaves = new GPSprite(texLeaves);
    sprLeaves->setPosition(0.0f, -100.0f);
    deque <GPVector> shapeLeaves=CreateFromTexture(texLeaves);

    cout<<"===Terrain==="<<endl;
    GPTexture* texTerrain = new GPTexture("terrain_small.png");
    GPSprite* sprTerrain = new GPSprite(texTerrain);
    sprTerrain->setPosition(0.0f, -100.0f);
    deque <GPVector> shapeTerrain=CreateFromTexture(texTerrain);
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

    sprSusi->setRotation_Z(45);
    sprSusi->setScale(2,2,1);
    sprSusi->setPosition(-50,-50);

    bbSusi.setRotation_Z(sprSusi->getRotation_Z());
    bbSusi.setScale_X(sprSusi->getScale_X());//Scale functions not practical
    bbSusi.setScale_Y(sprSusi->getScale_Y());
    bbSusi.setScale_Z(sprSusi->getScale_Z());
    bbSusi.setPosition(sprSusi->getX(),sprSusi->getY());

    polySusi.setRotation_Z(sprSusi->getRotation_Z());
    polySusi.setScale_X(sprSusi->getScale_X());//Scale functions not practical
    polySusi.setScale_Y(sprSusi->getScale_Y());
    polySusi.setScale_Z(sprSusi->getScale_Z());
    polySusi.setPosition(sprSusi->getX(),sprSusi->getY());

    hullSusi.setRotation_Z(sprSusi->getRotation_Z());
    hullSusi.setScale_X(sprSusi->getScale_X());//Scale functions not practical
    hullSusi.setScale_Y(sprSusi->getScale_Y());
    hullSusi.setScale_Z(sprSusi->getScale_Z());
    hullSusi.setPosition(sprSusi->getX(),sprSusi->getY());

    bbSusi.setRGBA(1,0,0,1);
    hullSusi.setRGBA(0,1,0,1);
    polySusi.setRGBA(0,0,1,1);

    while(!quit) {
        proc->pollEvents();
        window->clearScreen();

        sprSusi->draw();
        ConvexSusi.draw();

//         sprMissile->draw();
//         sprTerrain->draw();
//         sprLeaves->draw();

	for(unsigned int i=0;i<CustomPoints.size();i++)
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
	for(unsigned int i=0;i<CustomConvexHulls.size();i++) CustomConvexHulls[i].draw();
    Triangle.setRGBA(1,1,0,1);
    Triangle.draw();
    superman.draw();
	
//         filledPolygonRGBA(200,100,polygon.getVertices(),size,0,1,0,1);
//         PolygonRGBA(0,0,polygon.getVertices(),size,0,1,0,1);
//         polygon1.draw();
//         polygon2.draw();
//         CP.draw();
//         CP2.draw();

     	bbSusi.draw();
	    polySusi.draw();
        PolygonRGBA(sprSusi->getX(),sprSusi->getY(),shapeSusi,sprSusi->getScale_X(),sprSusi->getRotation_Z(),size,1,1,1,1);
        PolygonRGBA(sprSusi->getX(),sprSusi->getY(),bbSusi.getVertices(),sprSusi->getScale_X(),sprSusi->getRotation_Z(),size,1,1,1,1);
        hullSusi.setRotation_Z(sprSusi->getRotation_Z());
        hullSusi.setScale_X(sprSusi->getScale_X());//Scale functions not practical
        hullSusi.setScale_Y(sprSusi->getScale_Y());
        hullSusi.setScale_Z(sprSusi->getScale_Z());
        hullSusi.setPosition(sprSusi->getX(),sprSusi->getY());
        hullSusi.draw();
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
