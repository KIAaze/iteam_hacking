/*! \file physics.cpp
\brief Physics engine

Used to process movement of physical objects.
*/

#include <cstdio>
#include <cmath>
#include <map>

#include "gp2d.h"
//#include "physics.h"

namespace gp2d {
    
/***********************************************************************
*
*  GP2DPhysSolidObject methods
*
***********************************************************************/

GP2DPhysSolidObject::GP2DPhysSolidObject(void)
{
	// this function is required for it to be used as a base class
}

GP2DPhysSolidObject::GP2DPhysSolidObject(GLfloat width, GLfloat height,
    GLfloat mass, GP2DPhysShape shape, GP2DTexture* texture)
{
    m_x = 0.0f;
    m_y = 0.0f;
    m_width = width;
    m_height = height;
    m_mass = mass;
    m_shape = shape;
    m_gravityConstant = 9.8f;
    m_velocityX = 0.0f;
    m_velocityY = 0.0f;
    m_speed = 1.0f;
    m_texture = texture; // part of GP2DSprite
    m_framerate = GP2DFramerate::getInstance();
    if (m_shape == CIRCLE) {
        createAABB();
        buildEdges();
    }
}

GP2DPhysSolidObject::~GP2DPhysSolidObject()
{
}

GP2DPhysShape GP2DPhysSolidObject::getShape(void)
{
    return m_shape;
}

void GP2DPhysSolidObject::setMass(GLfloat newMass)
{
    m_mass = newMass;
}

GLfloat GP2DPhysSolidObject::getMass(void)
{
    return m_mass;
}

void GP2DPhysSolidObject::setGravity(GLfloat newGravityConstant)
{
    m_gravityConstant = newGravityConstant;
}

GLfloat GP2DPhysSolidObject::getGravity(void)
{
    return m_gravityConstant;
}

void GP2DPhysSolidObject::setSpeed(GLfloat rate)
{
    m_speed = rate;
}

GLfloat GP2DPhysSolidObject::getSpeed(void)
{
    return m_speed;
}

void GP2DPhysSolidObject::setAccelerationX(GLfloat newAcceleration)
{
    m_accelerationX = newAcceleration;
}

GLfloat GP2DPhysSolidObject::getAccelerationX(void)
{
    return m_accelerationX;
}

void GP2DPhysSolidObject::setAccelerationY(GLfloat newAcceleration)
{
    m_accelerationY = newAcceleration;
}

GLfloat GP2DPhysSolidObject::getAccelerationY(void)
{
    return m_accelerationY;
}

void GP2DPhysSolidObject::setVelocityX(GLfloat newVelocity)
{
    m_velocityX = newVelocity;
}

GLfloat GP2DPhysSolidObject::getVelocityX(void)
{
    return m_velocityX;
}

void GP2DPhysSolidObject::setVelocityY(GLfloat newVelocity)
{
    m_velocityY = newVelocity;
}

GLfloat GP2DPhysSolidObject::getVelocityY(void)
{
    return m_velocityY;
}

void GP2DPhysSolidObject::setCoordX(GLfloat x)
{
    if (m_shape == CIRCLE)
    {
        m_x = x;
    }
    else
    {
        std::map<unsigned short int, GP2DVector*>::iterator iter;
        for(iter = Points.begin(); iter != Points.end(); iter++)
        {
          iter->second->x = iter->second->x + x;
        }
    }
}

GLfloat GP2DPhysSolidObject::getCoordX(void)
{
    return m_x;
}

void GP2DPhysSolidObject::setCoordY(GLfloat y)
{
    if (m_shape == CIRCLE)
    {
        m_y = y;
    }
    else
    {
        std::map<unsigned short int, GP2DVector*>::iterator iter;
        for(iter = Points.begin(); iter != Points.end(); iter++)
        {
          iter->second->y = iter->second->y + y;
        }
    }
}

GLfloat GP2DPhysSolidObject::getCoordY(void)
{
    return m_y;
}

void GP2DPhysSolidObject::setPhysWidth(GLfloat width)
{
    m_width = width;
}

GLfloat GP2DPhysSolidObject::getPhysWidth(void)
{
    return m_width;
}

void GP2DPhysSolidObject::setPhysHeight(GLfloat height)
{
    m_height = height;
}

GLfloat GP2DPhysSolidObject::getPhysHeight(void)
{
    return m_height;
}

GP2DVector GP2DPhysSolidObject::getCenter(void)
{
    GP2DVector* result = new GP2DVector();;
    if (m_shape == CIRCLE)
    {
        result->x = m_x + m_width / 2.0f;
        result->y = m_y + m_height / 2.0f;
    }
    else if (m_shape == CONVEX_POLYGON)
    {
        // refer to
        // http://local.wasp.uwa.edu.au/~pbourke/geometry/polyarea/
        // for the formula, explanation, and example code
        GLfloat x = 0.0f;
        GLfloat y = 0.0f;
        int j;
        int n = Points.size();
        GLfloat factor = 0.0f;
        for (int i = 0; i < n; i++)
        {
            j = (i + 1) % n;
            factor = Points[i]->x * Points[j]->y - Points[j]->x *
                Points[i]->y;
            x -= (Points[i]->x + Points[j]->x) * factor;
            y -= (Points[i]->y + Points[j]->y) * factor;
        }
        factor = 1.0f / (m_area * 6.0f);
        x *= factor;
        y *= factor;
        result->x = x;
        result->y = y;
    }
    return (*result);
}

bool GP2DPhysSolidObject::movingRight(void)
{
    return m_movingRight;
}

bool GP2DPhysSolidObject::movingLeft(void)
{
    return m_movingLeft;
}

bool GP2DPhysSolidObject::movingUp(void)
{
    return m_movingUp;
}

bool GP2DPhysSolidObject::movingDown(void)
{
    return m_movingDown;
}

void GP2DPhysSolidObject::addPoint(GLfloat x, GLfloat y)
{
    Points[Points.size()] = new GP2DVector(x, y);
}

void GP2DPhysSolidObject::buildEdges(void)
{
    GP2DVector* p1 = new GP2DVector();
    GP2DVector* p2 = new GP2DVector();
    Edges.clear();
    for (unsigned int i = 0; i < Points.size(); i++)
    {
        //p1->x = Points[i]->x;
        //p1->y = Points[i]->y;
        p1 = Points[i];
        if (i + 1 >= Points.size())
        {
            //p2->x = Points[0]->x;
            //p2->y = Points[0]->y;
            p2 = Points[0];
        }
        else
        {
            //p2->x = Points[i + 1]->x;
            //p2->y = Points[i + 1]->y;
            p2 = Points[i + 1];
        }
        Edges[Edges.size()] =
            new GP2DVector(p2->x - p1->x, p2->y - p1->y);
    }
    createAABB();
    calculateArea();
}

void GP2DPhysSolidObject::step(GLfloat deltaTicks)
{
    GLfloat time = deltaTicks / 1000; // seconds
    m_velocityX += (m_velocityX + m_accelerationX * time) * m_speed;
    m_velocityY += (m_velocityY + m_accelerationY * time) * m_speed;
    m_velocityY += (m_velocityY + m_gravityConstant * time) * m_speed;
    m_x = m_x + (m_velocityX * time + 0.5f * m_accelerationX *
        pow(time, 2));
	m_y = m_y + (m_velocityY * time + 0.5f * m_accelerationY *
	    pow(time, 2));
    if (m_velocityX > 0) { m_movingRight = true; m_movingLeft = false; }
    else if (m_velocityX < 0) { m_movingLeft = true;
        m_movingRight = false; }
    else { m_movingRight = false; m_movingLeft = false; }
    if (m_velocityY > 0) { m_movingUp = true; m_movingDown = false; }
    else if (m_velocityY < 0) { m_movingDown = true;
        m_movingUp = false; }
    else { m_movingUp = false; m_movingDown = false; }
    //draw();
}

// protected method
void GP2DPhysSolidObject::createAABB(void)
{
    if (m_shape == CIRCLE)
    {
        m_AABB.x = getX();
        m_AABB.y = getY();
        m_AABB.width = m_width;
        m_AABB.height = m_height;
    }
    else if (m_shape == CONVEX_POLYGON)
    {
        GLfloat left = 0.0f; // furthest points in respective directions
        GLfloat right = 0.0f;
        GLfloat top = 0.0f;
        GLfloat bottom = 0.0f;
        for(unsigned int i = 0; i < Points.size(); i++)
        {
            if (Points[i]->x < left)
            {
                left = Points[i]->x;
            }
            else if (Points[i]->x > right)
            {
                right = Points[i]->x;
            }
            if (Points[i]->y < top)
            {
                top = Points[i]->y;
            }
            else if (Points[i]->y > bottom)
            {
                bottom = Points[i]->y;
            }
        }
        m_AABB.x = left;
        m_AABB.y = top;
        m_AABB.height = top + bottom;
        m_AABB.width = right + left;
    }
}

void GP2DPhysSolidObject::calculateArea(void)
{
    if (m_shape == CIRCLE)
    {
        m_area = 3.14159 * pow((m_width / 2), 2);
    }
    else if (m_shape == CONVEX_POLYGON)
    {
        // refer to
        // http://local.wasp.uwa.edu.au/~pbourke/geometry/polyarea/
        // for the formula, explanation, and example code
        int j;
        int n = Points.size();
        m_area = 0.0f;
        for (int i = 0; i < n; i++)
        {
            j = (i + 1) % n;
            m_area += Points[i]->x * Points[j]->y;
            m_area -= Points[i]->y * Points[j]->x;
        }
        m_area /= 2.0f;
        m_area = (m_area < 0.0f ? -m_area : m_area);
    }
}


/***********************************************************************
*
*  GP2DPhysWorld methods
*
***********************************************************************/

GP2DPhysWorld::GP2DPhysWorld(GLfloat width, GLfloat height)
{
    m_objectCount = 0;
    m_width = width;
    m_height = height;
}

GP2DPhysWorld::~GP2DPhysWorld(void)
{
    std::map<unsigned short int, GP2DPhysSolidObject*>::iterator iter;
    for(iter = Objects.begin(); iter != Objects.end(); iter++)
    {
      Objects.erase(iter);
    }
}

void GP2DPhysWorld::step(GLfloat deltaTicks)
{
    std::map<unsigned short int, GP2DPhysSolidObject*>::iterator iter;
    for(iter = Objects.begin(); iter != Objects.end(); iter++)
    {
        iter->second->step(deltaTicks);
    }
    // FIXME: Add collision detection and response
}

int GP2DPhysWorld::addObject(GLfloat width, GLfloat height, GLfloat mass, 
            GP2DPhysShape shape, GP2DTexture* texture, GLfloat x, GLfloat y)
{
    Objects[m_objectCount] = new GP2DPhysSolidObject(width, height,
        mass, shape, texture);
    Objects[m_objectCount]->setCoordX(x);
    Objects[m_objectCount]->setCoordY(y);
    m_objectCount += 1;
    return m_objectCount - 1;
}

void GP2DPhysWorld::removeObject(int id)
{
    Objects.erase(id);
}

bool GP2DPhysWorld::isColliding(GP2DPhysSolidObject* object1, 
            GP2DPhysSolidObject* object2)
{
    if (AABBtoAABB(object1->m_AABB, object2->m_AABB))
    {
        if (object1->getShape() == CIRCLE) {
            if (object2->getShape() == CIRCLE)
            {
                return circleToCircle(object1, object2);
            }
            /*else if (object2->getShape() == CONVEX_POLYGON)
            {
                return circleToConvexPolygon(object1, object2);
            }*/
        }
        else if (object1->getShape() == CONVEX_POLYGON) {
            if (object2->getShape() == CONVEX_POLYGON)
            {
                return convexPolygonToPolygon(object1, object2);
            }
            /*else if (object2->getShape() == CIRCLE)
            {
                return convexPolygonToCircle(object1, object2);
            }*/
        }
    }
    return false; // any downsides to doing this?
}

bool GP2DPhysWorld::AABBtoAABB(GP2DPhysAABB& box1,
    GP2DPhysAABB& box2)
{    
    if (!((box1.x + box1.width) >= box2.x)) return false;
    if (!(box1.x <= (box2.x + box2.width))) return false;
    if (!((box1.y - box1.height) <= box2.y)) return false;
    if (!(box1.y >= (box2.y - box2.height))) return false;
    
    return true;
}

bool GP2DPhysWorld::rectangleToCircle(GP2DPhysSolidObject* object1,
    GP2DPhysSolidObject* object2)
{
    return false; // FIXME
}

bool GP2DPhysWorld::circleToCircle(GP2DPhysSolidObject* object1,
    GP2DPhysSolidObject* object2)
{
    // x and y coordinates of the center of the first circle
    int objectCenterX1 = object1->getCoordX() +
        object1->getPhysWidth() / 2.0f;
    int objectCenterY1 = object1->getCoordY() +
        (object1->getPhysHeight() / 2.0f);

    // x and y coordinates of the center of the second circle
    int objectCenterX2 = object2->getCoordX() +
        (object2->getPhysWidth() / 2.0f);
    int objectCenterY2 = object2->getCoordY() +
        (object2->getPhysHeight() / 2.0f);

    int xDifference = objectCenterX2 - objectCenterX1; // x-plane difference
    int yDifference = objectCenterY2 - objectCenterY1; // y-plane difference

    // distance between the centers of the circles squared
    int centerDistanceSquared = (yDifference * yDifference) +
        (xDifference * xDifference);

    // sum of the radii squared, remember order of operations
    int radiusSumSquared = object1->getPhysWidth() / 2.0f
        + object2->getPhysWidth() / 2.0f;
    radiusSumSquared *= radiusSumSquared;

    return (centerDistanceSquared - radiusSumSquared <= 0); 
}

bool GP2DPhysWorld::convexPolygonToPolygon(GP2DPhysSolidObject* object1,
    GP2DPhysSolidObject* object2)
{
    int edgeCount1 = object1->Edges.size();
    int edgeCount2 = object2->Edges.size();
    
    GP2DVector* edge = new GP2DVector(object1->Edges[0]->x,
        object1->Edges[0]->y);
    
    // We must loop through <b>all</b> edges of the polygons, however
    // this isn't necessarily bad.  The loop exits if a separating axis
    // is found.  In other words, a chance for early out. (Right term?)
    for (int edgeIndex = 0; edgeIndex < edgeCount1 + edgeCount2;
        edgeIndex++)
    {
        if (edgeIndex < edgeCount1)
        {
            edge = object1->Edges[edgeIndex];
        }
        else
        {
            edge = object2->Edges[edgeIndex - edgeCount1];
        }
        GP2DVector* axis = new GP2DVector(-edge->y, edge->x);
        axis = axis->normalize();
        
        // project the polygon onto the axis
        GLfloat min1, min2, max1, max2;
        project(axis, object1, min1, max1);
        project(axis, object2, min2, max2); // min and max are references
        
        // check for a separating axis
        GLfloat intervalDistance;
        if (min1 < min2)
        {
            intervalDistance = min2 - max1;
        }
        else
        {
            intervalDistance = min1 - max2;
        }
        if (intervalDistance > 0)
        {
            // following the separating axis theoream, unless all
            // projected vectors overlap, there is no collision
            // between the convex polygons
            return false;
        }
    }
    return true;
}

bool GP2DPhysWorld::willCollide(GP2DPhysSolidObject* object1,
    GP2DPhysSolidObject* object2)
{
    GLfloat originalX1 = object1->getX();
    GLfloat originalY1 = object1->getY();
    object1->setX(object1->getX() + object1->getVelocityX());
    object1->setY(object1->getY() + object1->getVelocityY());
    GLfloat originalX2 = object2->getX();
    GLfloat originalY2 = object2->getY();
    object2->setX(object2->getX() + object2->getVelocityX());
    object2->setY(object2->getY() + object2->getVelocityY());
    bool result = isColliding(object1, object2);
    object1->setX(originalX1);
    object1->setY(originalY1);
    object2->setX(originalX2);
    object2->setY(originalY2);
    return result;
}

void GP2DPhysWorld::project(GP2DVector* axis,
    GP2DPhysSolidObject* toProject, GLfloat& min, GLfloat& max)
{
    GLfloat dotProduct = axis->dotProduct(*toProject->Points[0]); // we'll cycle through every point, so we might as well start at 0 since we can be certain it exists
    min = dotProduct;
    max = dotProduct;
    for (unsigned int i = 0; i < toProject->Points.size(); i++)
    {
        dotProduct = toProject->Points[i]->dotProduct(*axis);
        if (dotProduct < min)
        {
            min = dotProduct;
        }
        else if (dotProduct > max)
        {
            max = dotProduct;
        }
    }
}

/***********************************************************************
*
*  GP2DParticle methods
*
***********************************************************************/

GP2DParticle::GP2DParticle(void)
{
    // required to be used as a base class
}

GP2DParticle::GP2DParticle(GP2DParticleType type, float x, float y)
{
    setX(x);
    setY(y);
    m_type = type;
}

GP2DParticle::~GP2DParticle(void)
{
}

void GP2DParticle::setX(GLfloat newX)
{
    m_x = newX;
}

GLfloat GP2DParticle::getX(void)
{
    return m_x;
}

void GP2DParticle::setY(GLfloat newY)
{
    m_y = newY;
}

GLfloat GP2DParticle::getY(void)
{
    return m_y;
}

void GP2DParticle::setVelocityX(GLfloat newVelocity)
{
    m_velocityX = newVelocity;
}

GLfloat GP2DParticle::getVelocityX(void)
{
    return m_velocityX;
}

void GP2DParticle::setVelocityY(GLfloat newVelocity)
{
    m_velocityY = newVelocity;
}

GLfloat GP2DParticle::getVelocityY(void)
{
    return m_velocityY;
}

void GP2DParticle::step(GLfloat deltaTicks)
{
    switch (m_type) {
        case GAS:
            break;
    }
}

/***********************************************************************
*
*  GP2DParticleSystem methods
*
***********************************************************************/

GP2DParticleSystem::GP2DParticleSystem(void)
{
}

GP2DParticleSystem::~GP2DParticleSystem(void)
{
    std::map<unsigned short int, GP2DParticle*>::iterator iter;
    for(iter = m_particles.begin(); iter != m_particles.end(); iter++)
    {
      m_particles.erase(iter);
    }
}

void GP2DParticleSystem::addParticles(int numberOfParticles)
{
    // FIXME
}

void GP2DParticleSystem::step(GLfloat deltaTicks)
{
    
}

bool GP2DParticleSystem::isColliding(GP2DParticle* particle1,
    GP2DParticle* particle2)
{
    return (particle1->getX() == particle2->getX() && particle1->getY()
        == particle2->getY());
}

/***********************************************************************
*
*  GP2DVector methods
*
***********************************************************************/

GP2DVector::GP2DVector(void)
{
    x = 0.0f;
    y = 0.0f;
}

GP2DVector::GP2DVector(GLfloat xc, GLfloat yc)
{
    x = xc;
    y = yc;
}

GP2DVector::~GP2DVector(void)
{
}

GLfloat GP2DVector::magnitude(void)
{
    return sqrt(x * x + y * y);
}

GP2DVector* GP2DVector::normalize(void)
{
    GLfloat mag = magnitude();
	return new GP2DVector(x / mag, y / mag);
}

GLfloat GP2DVector::dotProduct(GP2DVector& other)
{
    return x * other.x + y * other.y;
}

/*GP2DVector GP2DVector::operator= (const GP2DVector& other1,
    const GP2DVector& other2) const
{
    GP2DVector result;
    result.x = other.x;
    result.y = other.y;
    return result;
}

GP2DVector GP2DVector::operator+ (const GP2DVector& other1,
    const GP2DVector& other2) const
{
    GP2DVector result;
    result.x = x + other.x;
    result.y = y + other.y;
    return result;
}

GP2DVector GP2DVector::operator- (const GP2DVector& other1,
    const GP2DVector& other2) const
{
    return GP2DVector(x - other.x, y - other.y);
}

GP2DVector GP2DVector::operator* (const GP2DVector& other1,
    const GP2DVector& other2) const
{
    return GP2DVector(x * other.x, y * other.y);
}

GP2DVector GP2DVector::operator/ (const GP2DVector& other1,
    const GP2DVector& other2) const
{
    return GP2DVector(x / other.x, y / other.y);
}*/

void GP2DVector::operator+= (const GP2DVector& other)
{
    x += other.x;
    y += other.y;
}

void GP2DVector::operator-= (const GP2DVector& other)
{
    x -= other.x;
    y -= other.y;
}

void GP2DVector::operator*= (const GP2DVector& other)
{
    x *= other.x;
    y *= other.y;
}

void GP2DVector::operator/= (const GP2DVector& other)
{
    x /= other.x;
    y /= other.y;
}

bool GP2DVector::operator== (const GP2DVector& other) const
{
    return (x == other.x && y == other.y);
}

bool GP2DVector::operator!= (const GP2DVector& other) const
{
    return (x != other.x || y != other.y);
}

} // namespace gp2d
