#include "gp2d/gp2d.h"
using namespace gp;

#include <deque>

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
//     if(p1.getY()==-43)
    int slope1 = (p1.getY() - p2.getY());
    int slope2 = (p2.getY() - p3.getY());
    return ( 0 == slope1 && 0 == slope2 ) ||
        ((p1.getX() - p2.getX()) / (double)slope1) == ((p2.getX() - p3.getX()) / (double)slope2);
}

ostream &operator<<(ostream &str, deque <GPVector> &Vertices)
{
    str<<"[";
    for (unsigned int idx = 0; idx < Vertices.size(); idx++) {
        str << Vertices[idx];
        if(idx!=Vertices.size()-1) str<<",";
    }
    str<<"]";
    return(str);
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
//     cout<<"Reduce: result="<<result<<endl;
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

// ostream &operator<<(ostream &str, SimplePolygon const &poly);
// ostream &operator<<(ostream &stream, SimplePolygon &poly);

class SimplePolygon : public GPObject {
  protected:
    deque <GPVector> Vertices;
    GLfloat R,G,B,A;
  public:
    SimplePolygon(){setRGBA(1,1,1,1);};
    SimplePolygon(deque <GPVector> V):Vertices(V){setRGBA(1,1,1,1);};
    deque <GPVector> getVertices() {return(Vertices);};
    void setVertices(deque <GPVector> V) {Vertices=V;};
    void addVertex(GPVector V) {Vertices.push_back(V);};
    void addVector(GPVector V) {
        for(unsigned int i=0;i<Vertices.size();i++) Vertices[i]+=V;
    };
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
    int removeVertices(int start, int stop) {
        int N=Vertices.size();
        start=(start+N)%N;
        stop=(stop+N)%N;
        int newsize=0;
        if(start==stop)
        {
            removeVertex(start);
            return(N-1);
        }
        if(start<stop) newsize=N-(stop-start+1);
        else newsize=N-(stop+1)-(N-start+1);
        
        deque <GPVector> NewVertices(newsize);
        
        int dst_idx=0;
        int src_idx=stop;
        while(src_idx!=start)
        {
            src_idx=(src_idx+1)%N;
            NewVertices[dst_idx]=Vertices[src_idx];
            dst_idx++;
        }
        this->setVertices(NewVertices);
        return(newsize);
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
    void ScaleForReal(GLfloat S){
      for(unsigned int i=0;i<Vertices.size();i++) {Vertices[i]=S*Vertices[i];}
    }
    friend ostream &operator<<(ostream &str, SimplePolygon &poly)
    {
        str<<"[";
        for (unsigned int idx = 0; idx < poly.Vertices.size(); idx++) {
            str << poly.Vertices[idx];
            if(idx!=poly.Vertices.size()-1) str<<",";
        }
        str<<"]";
        return(str);
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
    void setRGBA(GLfloat a_R, GLfloat a_G, GLfloat a_B, GLfloat a_A) {
        for(unsigned int i=0;i<Polygons.size();i++) Polygons[i].setRGBA(a_R,a_G,a_B,a_A);
    }
};

SimplePolygon CreateFromTexture(GPTexture* tex)
{
  SDL_Surface* surf = tex->getSurface();
  deque <GPVector> V=CreateFromBitmap(surf);
  int N=V.size();
  for(int i=0;i<N;i++) V[i].setY(-V[i].getY());
  SimplePolygon P(V);
  return(P);
}

//TODO: Optimize by using resize
SimplePolygon CreateBoundingBoxFromTexture(GPTexture* tex)
{
  SDL_Surface* surf = tex->getSurface();
  SimplePolygon BB;
  BB.addVertex(GPVector(0,-surf->h));
  BB.addVertex(GPVector(0,0));
  BB.addVertex(GPVector(surf->w,0));
  BB.addVertex(GPVector(surf->w,-surf->h));
//   BB.addVector(GPVector(-surf->w/2.0,surf->h/2.0));

/*  BB.addVertex(GPVector(surf->w,-surf->h));
  BB.addVertex(GPVector(surf->w,0));
  BB.addVertex(GPVector(0,0));
  BB.addVertex(GPVector(0,-surf->h));*/
  return(BB);
}

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

bool TurnRight_strict(GPVector A,GPVector B,GPVector C)
{
    //cout<<"A="<<A<<" B="<<B<<" C="<<C<<endl;
    //cout<<"TurnRight="<<((B-A).cross(C-B).getZ()<0)<<endl;
    return((B-A).cross(C-B).getZ()<0);
}

bool TurnLeft_strict(GPVector A,GPVector B,GPVector C)
{
    return((B-A).cross(C-B).getZ()>0);
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
SimplePolygon TestPolygon;
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
//       cout<<lower[0]<<endl;
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
//         if((B-A).cross(C-A).getZ()*(B-A).cross(M-A).getZ()<=0) return(false);
        if((B-A).cross(C-A).getZ()*(B-A).cross(M-A).getZ()<0) return(false);
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
int FindAnEar(SimplePolygon poly, int start, SimplePolygon& Ear, bool verbose)
{
//     cout<<"=== FindAnEar START start="<<start<<"==="<<endl;
    if(poly.getSize()<3) return(-1);

    int N=poly.getSize();
    if(N<=0) return(-1);
    start=(start+N)%N;//to make sure we start inside 0,N-1
    for(int idx=0;idx<N;idx++)
    {
        int i=(start+idx)%N;
//         cout<<"i="<<i<<endl;
        SimplePolygon PotentialEar=TriangleFromPolygon(poly,i);
        //TODO: Figure out whether we need TurnRight or TurnRight_strict to obtain a full triangulation without flat triangles
        if(TurnRight_strict(PotentialEar.getVertex(0),PotentialEar.getVertex(1),PotentialEar.getVertex(2)))
        {
            if(verbose) cout<<"turn right OK"<<endl;
            bool IsEar=true;
            for(int j=0;j<N;j++)
            {
                if(verbose) cout<<"j="<<j<<endl;
                if(j!=(i-1+N)%N && j!=(i)%N && j!=(i+1)%N)
                {
                    if(verbose) cout<<"j not a point from triangle"<<endl;
                    if(IsInConvexPolygon(PotentialEar,poly.getVertex(j))) {
                        if(verbose) cout<<"No, it's not an ear"<<endl;
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

ConvexPolygon Triangulate(SimplePolygon poly, SimplePolygon& Rest, bool verbose)
{
    ConvexPolygon CP;
    SimplePolygon tmp;
    int ear=0;
    while(ear>=0)
    {
//         if(poly.getSize()<5) verbose=true;
        ear=FindAnEar(poly,ear,tmp,verbose);
//         cout<<"ear="<<ear<<endl;
        if(ear>=0){
//             if(poly.getSize()<5) cout<<"poly.getSize()="<<poly.getSize()<<" removing ear="<<ear<<endl;
//             if(poly.getSize()<5) cout<<"before: poly="<<poly<<endl;

            CP.addPolygon(tmp);
            poly.removeVertex(ear);

//             if(poly.getSize()<5) cout<<"after: poly="<<poly<<endl;
//             CP.draw();
//             window->sync();
//             wait(1000);

        }
    }
    if(poly.getSize()>2)
    {
        cout<<"WARNING: Could not completely triangulate polygon!"<<endl;
//         abort();
    }
    Rest=poly;
    return(CP);
}

//Check if subpoly start,start+1,...,stop is a good subpolygon of poly
bool IsGoodSubPolygon(SimplePolygon poly, SimplePolygon PotentialGSP, int start, int stop)
{
//     cout<<"=== IsGoodSubPolygon START ==="<<endl;
//     cout<<"start="<<start<<endl;
//     cout<<"stop="<<stop<<endl;
    bool IsGSP=true;
    int N=poly.getSize();
    int j=stop+1;
    while(j!=start)
    {
//         cout<<"j="<<j<<endl;
        if(IsInConvexPolygon(PotentialGSP,poly.getVertex(j))) {
            IsGSP=false;break;
        }
        j=(j+1)%N;
    }
//     cout<<"=== IsGoodSubPolygon END ==="<<endl;
    return(IsGSP);
}

//For clockwise polygons only!
int FindAConvexPolygon(SimplePolygon poly, SimplePolygon& GSP, int& start, int& stop)
{
//     cout<<"=== FindAConvexPolygon START ==="<<endl;
    int N=poly.getSize();//We always need that. :)
    if(N<=0) return(-1);
    if(N<3) return(-1);

    SimplePolygon PotentialGSP;
    int ear=FindAnEar(poly, 0, PotentialGSP, false);
    if(ear<0) return(-1);

    //initial start/stop values
    start=(ear-1+N)%N;
    stop=(ear+1)%N;

    while(stop!=start)
    {
        stop=(stop+1)%N;
//         cout<<"stop="<<stop<<endl;
        PotentialGSP.addVertex(poly.getVertex(stop));
        int subN=PotentialGSP.getSize();
        GPVector A = PotentialGSP.getVertex(subN-3);
        GPVector B = PotentialGSP.getVertex(subN-2);
        GPVector C = PotentialGSP.getVertex(subN-1);
        GPVector D = PotentialGSP.getVertex(0);
        GPVector E = PotentialGSP.getVertex(1);
/*        cout<<"A="<<A<<endl;
        cout<<"B="<<B<<endl;
        cout<<"C="<<C<<endl;
        cout<<"D="<<D<<endl;
        cout<<"E="<<E<<endl;*/
        if( !TurnRight_strict(A,B,C) || !TurnRight_strict(B,C,D) || !TurnRight_strict(C,D,E) || !IsGoodSubPolygon(poly,PotentialGSP,start,stop) ) {
            PotentialGSP.popLastVertex();
            stop=stop-1;
            GSP=PotentialGSP;
//             cout<<"=== FindAConvexPolygon SUCCESS STOP ==="<<endl;
            return(stop);
        }
    }
//     cout<<"=== FindAConvexPolygon FAIL STOP ==="<<endl;
    return(-1);
}

//Yeah, that's a cool function name, isn't it? B)
ConvexPolygon Convexify(SimplePolygon poly, SimplePolygon& Rest, bool verbose)
{
// int FindAConvexPolygon(SimplePolygon poly, SimplePolygon& GSP)

    ConvexPolygon CP;
    SimplePolygon GSP;
    int start,stop;
    while(FindAConvexPolygon(poly,GSP,start,stop)>=0)
    {
        CP.addPolygon(GSP);
//         cout<<"start="<<start<<endl;
//         cout<<"stop="<<stop<<endl;
//         cout<<"poly="<<poly<<endl;
        poly.removeVertices(start+1,stop-1);
//         cout<<"poly="<<poly<<endl;
    }
    if(poly.getSize()>2)
    {
        cout<<"WARNING: Could not completely convexify polygon!"<<endl;
    }
    Rest=poly;
    return(CP);
}

ConvexPolygon CreateConvexPolySetFromTexture(GPTexture* tex, int type)
{
    SimplePolygon Rest;
    ConvexPolygon polyset;
    if(type==0){
        SimplePolygon BB=CreateBoundingBoxFromTexture(tex);
        polyset.addPolygon(BB);
        cout<<"Bounding box: polyset.getSize()="<<polyset.getSize()<<" BB.getSize()="<<BB.getSize()<<endl;
    }
    else if(type==1){
        SimplePolygon poly=CreateFromTexture(tex);
        SimplePolygon hull=CreateConvexHull3(poly);
        polyset.addPolygon(hull);
        cout<<"Convex hull: polyset.getSize()="<<polyset.getSize()<<" hull.getSize()="<<hull.getSize()<<endl;
    }
    else if(type==2){
        SimplePolygon poly=CreateFromTexture(tex);
        polyset=Triangulate(poly, Rest,false);
        cout<<"Triangulated shape: polyset.getSize()="<<polyset.getSize()<<endl;
    }
    else{
        SimplePolygon poly=CreateFromTexture(tex);
        polyset=Convexify(poly, Rest,false);
        cout<<"Convexified shape: polyset.getSize()="<<polyset.getSize()<<endl;
    }

    return(polyset);
}

ConvexPolygon CreateConvexPolySetFromTexture(GPTexture* tex, SimplePolygon& Rest)
{
    SimplePolygon poly=CreateFromTexture(tex);
    ConvexPolygon polyset=Convexify(poly, Rest,false);
    return(polyset);
}

//------------------------------------------
//Coordinate conversion utilities
GPVector cam2universe ( GPCamera* a_Cam, GPVector a_P )
{
		GPVector l_C(a_Cam->getX(),a_Cam->getY());
		return(l_C+a_P);
}

//TODO: Make sure wether it's SCREEN_* or VIEWPORT_*
//TODO: It would be nice if it weren't necessary to pass the GPCamera as argument
// GPVector screen2universe ( GPWindow* a_window, GPVector a_P )
// {
// 		GPCamera* a_Cam = a_window->getCamera(0);
// 		GPVector l_S(a_Cam->getX()-a_window->getWidth()/2.,a_Cam->getY()-a_window->getHeight()/2.);
// 		return(l_S+a_P);
// }

GPVector surface2universe ( GPSprite* a_surf, GPVector a_P )
{
		GPVector l_S(a_surf->getX()-a_surf->getWidth()/2.,a_surf->getY()-a_surf->getHeight()/2.);
		return(l_S+a_P);        
}

GPVector screen2window ( GPWindow* a_window, GPCamera* cam , GPVector a_ScreenPoint )
{
    GPVector UC(cam->getX(),cam->getY());
    GPVector CS(-a_window->getWidth()/2.,a_window->getHeight()/2.);
    GPVector SM(a_ScreenPoint.getX(),-a_ScreenPoint.getY());
    return(UC+CS+SM);
//     return(GPVector(a_ScreenPoint.getX()-a_window->getWidth()/2.,-a_ScreenPoint.getY()+a_window->getHeight()/2.));
}
//------------------------------------------

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

//TODO: Change ConvexPolygon class to a vtkUnstructuredGrid like structure because we need cells made of point indices
//Then adapt this function. ;)
// void SwapTriangles(ConvexPolygon& poly)
// {
//   cout << "swapping edges of triangles (Delaunay)" << endl;
// 
//   vector<bool> marked(poly.getSize());
// 
//   int N_swaps;
//   int N_total = 0;
//   int loop = 1;
//   do {
//     N_swaps = 0;
//     createCellToCell(cells, c2c, grid);
//     //NOTE: This for loop can eventually be removed because if undefined, it's probably false.
//     for (int i_cells = 0; i_cells < cells.size(); ++i_cells) {
//       marked[i_cells] = false;
//     };
//     foreach (vtkIdType id_cell, cells) {
//       if (!marked[_cells[id_cell]]) {
//         for (int j = 0; j < 3; ++j) {
//           bool swap = false;
//           stencil_t S = getStencil(id_cell, j);
//           if (S.valid) {
//             if (!marked[_cells[S.id_cell2]]) {
//               vec3_t x3[4], x3_0(0,0,0);
//               vec2_t x[4];
//               for (int k = 0; k < 4; ++k) {
//                 grid->GetPoints()->GetPoint(S.p[k], x3[k].data());
//                 x3_0 += x3[k];
//               };
//               vec3_t n1 = triNormal(x3[0], x3[1], x3[3]);
//               vec3_t n2 = triNormal(x3[1], x3[2], x3[3]);
//               n1.normalise();
//               n2.normalise();
//               if ( (n1*n2) > 0.8) {
//                 vec3_t n = n1 + n2;
//                 n.normalise();
//                 vec3_t ex = orthogonalVector(n);
//                 vec3_t ey = ex.cross(n);
//                 for (int k = 0; k < 4; ++k) {
//                   x[k] = vec2_t(x3[k]*ex, x3[k]*ey);
//                 };
//                 vec2_t r1, r2, r3, u1, u2, u3;
//                 r1 = 0.5*(x[0] + x[1]); u1 = turnLeft(x[1] - x[0]);
//                 r2 = 0.5*(x[1] + x[2]); u2 = turnLeft(x[2] - x[1]);
//                 r3 = 0.5*(x[1] + x[3]); u3 = turnLeft(x[3] - x[1]);
//                 double k, l;
//                 vec2_t xm1, xm2;
//                 bool ok = true;
//                 if (intersection(k, l, r1, u1, r3, u3)) {
//                   xm1 = r1 + k*u1;
//                   if (intersection(k, l, r2, u2, r3, u3)) {
//                     xm2 = r2 + k*u2;
//                   } else {
//                     ok = false;
//                   };
//                 } else {
//                   ok = false;
//                   swap = true;
//                 };
//                 if (ok) {
//                   if ((xm1 - x[2]).abs() < (xm1 - x[0]).abs()) {
//                     swap = true;
//                   };
//                   if ((xm2 - x[0]).abs() < (xm2 - x[2]).abs()) {
//                     swap = true;
//                   };
//                 };
//               };
//             };
//           };
//           if (swap) {
//             marked[_cells[S.id_cell1]] = true;
//             marked[_cells[S.id_cell2]] = true;
//             if (c2c[_cells[S.id_cell1]][0] != -1) {
//               marked[c2c[_cells[S.id_cell1]][0]] = true;
//             } else if (c2c[_cells[S.id_cell1]][1] != -1) {
//               marked[c2c[_cells[S.id_cell1]][1]] = true;
//             } else if (c2c[_cells[S.id_cell1]][2] != -1) {
//               marked[c2c[_cells[S.id_cell1]][2]] = true;
//             };
//             if (c2c[_cells[S.id_cell2]][0] != -1) {
//               marked[c2c[_cells[S.id_cell2]][0]] = true;
//             } else if (c2c[_cells[S.id_cell2]][1] != -1) {
//               marked[c2c[_cells[S.id_cell2]][1]] = true;
//             } else if (c2c[_cells[S.id_cell2]][2] != -1) {
//               marked[c2c[_cells[S.id_cell2]][2]] = true;
//             };
//             vtkIdType new_pts1[3], new_pts2[3];
//             new_pts1[0] = S.p[1];
//             new_pts1[1] = S.p[2];
//             new_pts1[2] = S.p[0];
//             new_pts2[0] = S.p[2];
//             new_pts2[1] = S.p[3];
//             new_pts2[2] = S.p[0];
//             grid->ReplaceCell(S.id_cell1, 3, new_pts1);
//             grid->ReplaceCell(S.id_cell2, 3, new_pts2);
//             ++N_swaps;
//             ++N_total;
//             break;
//           };
//         };
//       };
//     };
//     ++loop;
//   } while ((N_swaps > 0) && (loop <= 20));
//   cout << N_total << " triangles have been swapped" << endl;
// };
