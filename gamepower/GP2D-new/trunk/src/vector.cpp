#include "vector.h"
#include <cmath>

namespace gp {


GPVector::GPVector(const GPVector & p) :
        m_x(p.m_x), m_y(p.m_y), m_z(p.m_z) {
}

GPVector::GPVector(GLfloat xx, GLfloat yy, GLfloat zz) :
        m_x(xx), m_y(yy), m_z(zz) {
}

GPVector::GPVector(const gpFloat x0[]) :
        m_x(x0[0]), m_y(x0[1]), m_z(x0[2]) {
}

GPVector::~GPVector() {
}


GLfloat GPVector::operator()(gpInt32 i) const {
   //dereferencing operator const
   switch(i) {
      case 0:
         return m_x;
      case 1:
         return m_y;
      case 2:
         return m_z;
      default:
         cerr << "operator()(i): bad index (" << i << ") returning 0" << endl;
   }
   return 0.0f;
}


GLfloat & GPVector::operator () (int i) {
   //dereferencing operator
   switch(i) {
      case 0:
         return m_x;
      case 1:
         return m_y;
      case 2:
         return m_z;
      default:
         cerr<<"operator()(i): bad index ("<<i<<") returning &m_x"<<endl;
   }
   return m_x;
}


GLfloat GPVector::angle(const GPVector & q) const {
   // return the angle w.r.t. another 3-vector
   GLfloat ptot2 = mag2()*q.mag2();
   if(ptot2 <= 0) {
      return 0.0;
   } else {
      GLfloat arg = dot(q)/sqrt(ptot2);
      if(arg >  1.0) arg =  1.0;
      if(arg < -1.0) arg = -1.0;
      return acos(arg);
   }
}


GLfloat GPVector::mag() const {
   // return the magnitude (rho in spherical coordinate system)

   return sqrt(mag2());
}


GLfloat GPVector::perp() const {
   //return the transverse component  (R in cylindrical coordinate system)

   return sqrt(perp2());
}



GLfloat GPVector::perp(const GPVector & p) const {
   //return the transverse component (R in cylindrical coordinate system)

   return sqrt(perp2(p));
}


GLfloat GPVector::phi() const {
   //return the  azimuth angle. returns phi from -pi to pi
   return m_x == 0.0 && m_y == 0.0 ? 0.0 : atan2(m_y,m_x);
}


GLfloat GPVector::theta() const {
   //return the polar angle
   return m_x == 0.0 && m_y == 0.0 && m_z == 0.0 ? 0.0 : atan2(perp(),m_z);
}


GPVector GPVector::unit() const {
   // return unit vector parallel to this.
   GLfloat  tot = mag2();
   GPVector p(m_x,m_y,m_z);
   return tot > 0.0 ? p *= (1.0 / sqrt(tot)) : p;
}


void GPVector::rotateX(GLfloat angle) {
   //rotate vector around X
   GLfloat s = sin(angle);
   GLfloat c = cos(angle);
   GLfloat yy = m_y;
   m_y = c * yy - s * m_z;
   m_z = s * yy + c * m_z;
}


void GPVector::rotateY(GLfloat angle) {
   //rotate vector around Y
   GLfloat s = sin(angle);
   GLfloat c = cos(angle);
   GLfloat zz = m_z;
   m_z = c * zz - s * m_x;
   m_x = s * zz + c * m_x;
}


void GPVector::rotateZ(GLfloat angle) {
   //rotate vector around Z
   GLfloat s = sin(angle);
   GLfloat c = cos(angle);
   GLfloat xx = m_x;
   m_x = c * xx - s * m_y;
   m_y = s * xx + c * m_y;
}

void GPVector::rotateUz(const GPVector& NewUzVector) {
   // NewUzVector must be normalized !

   GLfloat u1 = NewUzVector.m_x;
   GLfloat u2 = NewUzVector.m_y;
   GLfloat u3 = NewUzVector.m_z;
   GLfloat up = u1*u1 + u2*u2;

   if (up) {
      up = sqrt(up);
      GLfloat px = m_x,  py = m_y,  pz = m_z;
      m_x = (u1*u3*px - u2*py + u1*up*pz)/up;
      m_y = (u2*u3*px + u1*py + u2*up*pz)/up;
      m_z = (u3*u3*px -    px + u3*up*pz)/up;
   } else if (u3 < 0.) { m_x = -m_x; m_z = -m_z; }      // phi=0  teta=pi
   else {};
}

void GPVector::rotate(gpFloat theta, const GPVector & axis) {
//M=point to rotate
//P=M projected on the axis
//O=origin
//if the point is on the axis, there's no need to rotate.
  if((this->cross(axis)).mag()!=0) {
    GPVector X,Y,Z,OP,PM;
    Z=axis.unit();
    OP=((*this)*Z)*Z;
    PM=(*this)-OP;
    X=PM.unit();
    Y=Z.cross(X);
    (*this)=OP+PM.mag()*(cos(theta)*X+sin(theta)*Y);
   }
}

void GPVector::setPtThetaPhi(GLfloat pt, GLfloat theta, GLfloat phi) {
   //set Pt, Theta and Phi
   m_x = pt * cos(phi);
   m_y = pt * sin(phi);
   GLfloat tanTheta = tan(theta);
   m_z = tanTheta ? pt / tanTheta : 0;
}

void GPVector::setTheta(GLfloat th)
{
   // Set theta keeping mag and phi constant.
   gpFloat ma = mag();
   gpFloat ph = phi();
   setX(ma * sin(th) * cos(ph));
   setY(ma * sin(th) * sin(ph));
   setZ(ma * cos(th));
}

void GPVector::setPhi(GLfloat ph) {
   // Set phi keeping mag and theta constant.
   GLfloat xy = perp();
   setX(xy * cos(ph));
   setY(xy * sin(ph));
}

void GPVector::setMagThetaPhi(GLfloat mag, GLfloat theta, GLfloat phi) {
   GLfloat amag = abs(mag);
   m_x = amag * sin(theta) * cos(phi);
   m_y = amag * sin(theta) * sin(phi);
   m_z = amag * cos(theta);
}

GPVector GPVector::operator + (const GPVector & b) {
   return GPVector(getX() + b.getX(), getY() + b.getY(), getZ() + b.getZ());
}

GPVector GPVector::operator - (const GPVector & b) {
   return GPVector(getX() - b.getX(), getY() - b.getY(), getZ() - b.getZ());
}

GPVector GPVector::operator * (GLfloat a) {
   return GPVector(a * getX(), a * getY(), a * getZ());
}

GPVector operator * (GLfloat a, const GPVector & p) {
   return GPVector(a * p.getX(), a * p.getY(), a*p.getZ());
}

GLfloat GPVector::operator * (const GPVector & b) {
   return this->dot(b);
}

void GPVector::print() const {
   //print vector parameters
    clog << "(x, y, z) = ("
         << getX() << ", " << getY() << ", " << getZ()
         << ") (rho, theta, phi) = ("
         << mag() << ", " << RadToDeg(theta()) << ", " << RadToDeg(phi()) << ")" <<  endl;
}

ostream &operator<<(ostream &str, const GPVector &V) {
    str << "(" << V.getX() << "," << V.getY() << "," << V.getZ() << ")";
    return str;
}

GPVector GPVector::NReflectVector(GPVector v) {
    GPVector vec=v.unit();
    return((*this) - 2.0f * (this->dot(vec)) * vec);
}

GPVector GPVector::TReflectVector(GPVector v) {
    GPVector vec = v.unit();
    return(-(*this) + 2.0f*(this->dot(vec))* vec);
}

gpFloat GPVector::getX() const {
    return m_x;
}

gpFloat GPVector::getY() const {
    return m_y;
}

gpFloat GPVector::getZ() const {
    return m_z;
}

void GPVector::setX(gpFloat xx) {
    m_x = xx;
}

void GPVector::setY(gpFloat yy) {
    m_y = yy;
}
void GPVector::setZ(gpFloat zz) {
    m_z = zz;
}

void GPVector::setXYZ(gpFloat xx, gpFloat yy, gpFloat zz) {
   m_x = xx;
   m_y = yy;
   m_z = zz;
}

void GPVector::getXYZ(gpFloat carray[]) const {
   carray[0] = m_x;
   carray[1] = m_y;
   carray[2] = m_z;
}

void GPVector::setMag(gpFloat ma) {
   gpFloat factor = mag();
   if (factor == 0) {
      cerr << "setMag: zero vector can't be stretched" << endl;
   } else {
      factor = ma / factor;
      setX(m_x * factor);
      setY(m_y * factor);
      setZ(m_z * factor);
   }
}

void GPVector::setPerp(gpFloat r) {
   gpFloat p = perp();
   if (p != 0.0) {
      m_x *= r/p;
      m_y *= r/p;
   }
}


gpFloat& GPVector::operator[](int i) {
    return operator()(i);
}

gpFloat GPVector::operator[] (int i) const {
    return operator()(i);
}

GPVector & GPVector::operator=(const GPVector & p) {
   m_x = p.m_x;
   m_y = p.m_y;
   m_z = p.m_z;
   return *this;
}

bool GPVector::operator==(const GPVector& v) const {
   return (v.m_x == m_x && v.m_y == m_y && v.m_z == m_z);
}

bool GPVector::operator != (const GPVector& v) const {
   return (v.m_x != m_x || v.m_y != m_y || v.m_z != m_z);
}

GPVector& GPVector::operator+=(const GPVector & p) {
   m_x += p.m_x;
   m_y += p.m_y;
   m_z += p.m_z;
   return *this;
}

GPVector& GPVector::operator-=(const GPVector & p) {
   m_x -= p.m_x;
   m_y -= p.m_y;
   m_z -= p.m_z;
   return *this;
}

GPVector GPVector::operator-() const {
   return GPVector(-m_x, -m_y, -m_z);
}

GPVector& GPVector::operator*=(gpFloat a) {
    m_x *= a;
    m_y *= a;
    m_z *= a;
    return *this;
}

gpFloat GPVector::dot(const GPVector & p) const {
    return m_x * p.m_x + m_y * p.m_y + m_z * p.m_z;
}

GPVector GPVector::cross(const GPVector & p) const {
    return GPVector(m_y * p.m_z - p.m_y * m_z, m_z * p.m_x - p.m_z * m_x, m_x * p.m_y - p.m_x * m_y);
}

gpFloat GPVector::mag2() const {
    return m_x*m_x + m_y*m_y + m_z*m_z;
}


GPVector GPVector::orthogonal() const {
    gpFloat xx = m_x < 0.0 ? -m_x : m_x;
    gpFloat yy = m_y < 0.0 ? -m_y : m_y;
    gpFloat zz = m_z < 0.0 ? -m_z : m_z;
    if (xx < yy) {
        return xx < zz ? GPVector(0,m_z,-m_y) : GPVector(m_y,-m_x,0);
    } else {
        return yy < zz ? GPVector(-m_z,0,m_x) : GPVector(m_y,-m_x,0);
    }
}

gpFloat GPVector::perp2() const {
    return m_x * m_x + m_y * m_y;
}

gpFloat GPVector::pt() const {
    return perp();
}

gpFloat GPVector::perp2(const GPVector& p) const {
    gpFloat tot = p.mag2();
    gpFloat ss  = dot(p);
    gpFloat per = mag2();
    if (tot > 0.0) {
        per -= ss * ss / tot;
    }
    if (per < 0) {
        per = 0;
    }
    return per;
}

gpFloat GPVector::pt(const GPVector & p) const {
   return perp(p);
}

gpFloat GPVector::cosTheta() const {
   gpFloat ptot = mag();
   return ptot == 0.0 ? 1.0 : m_z/ptot;
}

}
