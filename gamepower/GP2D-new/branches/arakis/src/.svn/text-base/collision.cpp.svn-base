#include "collision.h"

using namespace gp2d;
using namespace std;

//==============================================================================
// Base collision class:
//==============================================================================
GP2DCollision::GP2DCollision() {
}

GP2DCollision::~GP2DCollision(){
}

bool GP2DCollision::isColliding() {
    return false;
}

GP2DObject* GP2DCollision::getObject1() {
    return m_obj_first;
}

GP2DObject* GP2DCollision::getObject2() {
    return m_obj_secnd;
}

void GP2DCollision::setObject1(GP2DObject& object) {
    m_obj_first = &object;
}

void GP2DCollision::setObject2(GP2DObject& object) {
    m_obj_secnd = &object;
}

GP2DSprite* GP2DCollision::getSprite1() {
    return m_sprite_first;
}

GP2DSprite* GP2DCollision::getSprite2() {
    return m_sprite_secnd;
}

void GP2DCollision::setSprite1(GP2DSprite& sprite) {
    m_sprite_first = &sprite;
}

void GP2DCollision::setSprite2(GP2DSprite& sprite) {
    m_sprite_secnd = &sprite;
}

//==============================================================================
// Bounds collision class:
//==============================================================================
GP2DBoundsCollision::GP2DBoundsCollision(GP2DObject& first, GP2DObject& second) {
    setObject1(first);
    setObject2(second);
}

GP2DBoundsCollision::~GP2DBoundsCollision() {
    // do not delete the m_obj_first and second, because they might be used
    // elsewhere still in the program.
}


bool GP2DBoundsCollision::isColliding() {
    /*
     * This very simple bounds collision check does collision check based on the
     * bounds of a 2D object. Very simple and clean, but probably not very
     * practical for use. Anyway, the values used here are the X and Y values,
     * and the width/height of the GP2DObject in question.
     *
     * This also means that if the object is rotated or such, that the x and y
     * and width and height remains the same. This might pose a problem when the
     * object is rotated in the viewing space, because essentially, the boundaries
     * for collisions change that way.
     *
     * TODO: Must find a way to cleanly solve this. Probably somewhere in
     * GP2DObject, where the two-dimensional bounds must be calculated based on
     * rotation, sizing and all other possible operations.
     */
    const GP2DObject* first = getObject1();
    const GP2DObject* second = getObject2();

    float x1 = first->getX();
    float y1 = first->getY();
    float x1w = x1 + first->getWidth();
    float y1h = y1 - first->getHeight();

    float x2 = second->getX();
    float y2 = second->getY();
    float x2w = x2 + second->getWidth();
    float y2h = y2 - second->getHeight();

    bool collide_left = (x1w >= x2);
    bool collide_right = (x1 <= x2w);
    bool collide_top = (y1h <= y2);
    bool collide_bottom = (y1 >= y2h);

    return collide_left && collide_right && collide_top && collide_bottom;
}

//==============================================================================
// Pixel collision class:
//==============================================================================
GP2DPixelCollision::GP2DPixelCollision(GP2DSprite& first, GP2DSprite& second) {
    setObject1(first);
    setObject2(second);
    setSprite1(first);
    setSprite2(second);
}

GP2DPixelCollision::~GP2DPixelCollision() {
    // do not delete the m_obj_first and second, because they might be used
    // elsewhere still in the program.
}

/*
bool GP2DPixelCollision::isColliding() {
    const GP2DSprite* object1 = getSprite1();
    const GP2DSprite* object2 = getSprite2();
    const GP2DSprite* second = object2;
/*
    GLfloat x1 = first->getX();
    GLfloat y1 = first->getY();
    GLfloat x1w = x1 + first->getWidth();
    GLfloat y1h = y1 - first->getHeight();

    GLfloat x2 = second->getX();
    GLfloat y2 = second->getY();
    GLfloat x2w = x2 + second->getWidth();
    GLfloat y2h = y2 - second->getHeight();

    bool collide_left = (x1w >= x2);
    bool collide_right = (x1 <= x2w);
    bool collide_top = (y1h <= y2);
    bool collide_bottom = (y1 >= y2h);
*/
/*
    glLineWidth(25.0f);

	 glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0f,0.0f,0.0f);
    glBegin(GL_LINES);
        // top left to top right
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex3f(0,          0,  -5.0f);
        glVertex3f(second->getWidth(), 0,  -5.0f);
        // top right to bottom right
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex3f(second->getWidth(), 0,  -5.0f);
        glVertex3f(second->getWidth(), second->getHeight(),  -5.0f);
        // bottom left to bottom right
        glVertex3f(0, second->getHeight(),  -5.0f);
        glVertex3f(second->getWidth(), second->getHeight(),  -5.0f);
        // top left to bottom left
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex3f(0,  0,  -5.0f);
        glVertex3f(0,  second->getHeight(),  -5.0f);
    glEnd();


GLfloat left1, left2, over_left;
GLfloat right1, right2, over_right;
GLfloat top1, top2, over_top;
GLfloat bottom1, bottom2, over_bottom;
GLfloat over_width, over_height;
int i, j;
    unsigned char *pixel1, *pixel2;
		GLfloat top_off, left_off, right_off, bottom_off;

    left1 = object1->getX();
    left2 = object2->getX();
    right1 = object1->getX() + object1->getWidth();
    right2 = object2->getX() + object2->getWidth();
    top1 = object1->getY();
    top2 = object2->getY();
    bottom1 = object1->getY() + object1->getHeight();
    bottom2 = object2->getY() + object2->getHeight();

    // Trivial rejections:
    if (bottom1 < top2) return(0);
    if (top1 > bottom2) return(0);

    if (right1 < left2) return(0);
    if (left1 > right2) return(0);

    // Ok, compute the rectangle of overlap:
    if (bottom1 > bottom2) over_bottom = bottom2;
    else over_bottom = bottom1;

    if (top1 < top2) over_top = top2;
    else over_top = top1;

    if (right1 > right2) over_right = right2;
    else over_right = right1;

    if (left1 < left2) over_left = left2;
    else over_left = left1;

		right_off  = ( over_right - ( object2->getX()- ( object2->getWidth()/2 ) ) );
		top_off    = ( over_top - ( object2->getY()- ( object2->getHeight()/2 ) ) );
		left_off   = ( over_left - ( object2->getX()- ( object2->getWidth()/2 ) ) );
		bottom_off = ( over_bottom - ( object2->getY()- ( object2->getHeight()/2 ) ) );

		if ( right_off  > object2->getWidth() ) { right_off  = object2->getWidth();  }
		if ( top_off > object2->getHeight() ) { top_off = object2->getHeight(); }
		if ( left_off  < 0 ) { left_off = 0; }
		if ( bottom_off   < 0 ) { bottom_off = 0; }

		Uint8 pa2;
		Uint32 px,py;
		SDL_LockSurface(object1->getTexture()->getSurface());
		SDL_LockSurface(object2->getTexture()->getSurface());

		for ( px = ( Uint32 ) left_off; px <= ( Uint32 ) right_off;  px++ ) {
			for ( py = ( Uint32 ) top_off;  py <= ( Uint32 ) bottom_off; py++ ) {

// For every pixel in the region...
				pa2 = object1->getAlpha(object2->getTexture()->getSurface(),px,py);// Get the pixel's alpha from the second image.


	 glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0f,0.0f,0.0f);
    glBegin(GL_LINES);
        glColor3f(0.0f, 1.0f, 1.0f);
        glVertex3f(px-2,py-2,-5.0f);
        glVertex3f(px+2,py+2,-5.0f);
    glEnd();

				/*
					DEBUG INFO: Remove this comment and recompile the library for showing a red area marking
							the collision area found in the destination sprite.
					gp2d::DisableTexturing();
					gp2d::SetPointSize(1.0f);
					gp2d::BeginPoints();
						if(pa2>1){ SetColor3(1,0,0); gp2d::DrawPixel(px,py); }
					gp2d::EndPoints();
					gp2d::EnableTexturing();
				*/

// If there's collision in the destination image (alpha is not zero) unlock the surfaces and return a true value.
// if(pa2>1){ SDL_UnlockSurface(surface1); SDL_UnlockSurface(surface2); return(1); }
//				cout << "jaja" << pa2 << endl;
/*
				if ( (int)pa2>0 ) {
					SDL_UnlockSurface(object1->getTexture()->getSurface());
					SDL_UnlockSurface(object2->getTexture()->getSurface());
					return ( 1 );
				}
			}
		}

// No collision in the region, unlock the surfaces and return false.

		SDL_UnlockSurface(object1->getTexture()->getSurface());
		SDL_UnlockSurface(object2->getTexture()->getSurface());

    // Now compute starting offsets into both objects' bitmaps:
//    i = ((over_top - object1->getY()) * object1->getWidth()) + over_left;
//    pixel1 = object1->frames[object1->curr_frame] + i;

//    j = ((over_top - object2->getY()) * object2->getWidth()) + over_left;
//    pixel2 = object2->frames[object2->curr_frame] + j;

/*
    for (i=0; i < over_height; i++) {
        for (j=0; j < over_width; j++) {
				SDL_LockSurface(object1->getTexture()->getSurface());
				SDL_LockSurface(object2->getTexture()->getSurface());
        		if (object1->getAlpha(object1->getTexture()->getSurface(),i,j) && object2->getAlpha(object2->getTexture()->getSurface(),i,j)){
					SDL_UnlockSurface(object1->getTexture()->getSurface());
					SDL_UnlockSurface(object2->getTexture()->getSurface());
        			return (1);
        		}
				SDL_UnlockSurface(object1->getTexture()->getSurface());
				SDL_UnlockSurface(object2->getTexture()->getSurface());
*/
//            if (*pixel1 > 0) && (*pixel2 > 0) return(1);
//            pixel1++;
//            pixel2++;
//        }
//        pixel1 += (object1->getWidth() - over_width);
//        pixel2 += (object2->getWidth() - over_width);
//    }

    // Now start scanning the whole rectangle of overlap,
    // checking the corresponding pixel of each object's
    // bitmap to see if they're both non-zero:
    /*

    for (i=0; i < over_height; I++) {
        for (j=0; j < over_width; j++) {
            if (*pixel1 > 0) && (*pixel2 > 0) return(1);
            pixel1++;
            pixel2++;
        }
        pixel1 += (object1->width - over_width);
        pixel2 += (object2->width - over_width);
    }
	*/
/*
	 return 0;

//    return collide_left && collide_right && collide_top && collide_bottom;

}
*/

bool GP2DPixelCollision::isColliding() {
    const GP2DSprite* object1 = getSprite1();
    const GP2DSprite* object2 = getSprite2();

		GLfloat left1, left2, over_left;
		GLfloat right1, right2, over_right;
		GLfloat top1, top2, over_top;
		GLfloat bottom1, bottom2, over_bottom;
		GLfloat top_off, left_off, right_off, bottom_off;
		Uint32 px, py;
		Uint8  pr, pg, pb, pa2, pa1;

		SDL_Surface *surface1, *surface2;
		surface1 = object1->getTexture()->getSurface();
		surface2 = object2->getTexture()->getSurface();

// Alright... this is tricky. First, calculate the collision region just like in the function above.

		left1 =  object1->getX()- ( object1->getWidth()/2 );
		left2 =  object2->getX()- ( object2->getWidth()/2 );
		right1 = object1->getX()- ( object1->getWidth()/2 ) + object1->getWidth();
		right2 = object2->getX()- ( object2->getWidth()/2 ) + object2->getWidth();

		top1 =  object1->getY()- ( object1->getHeight()/2 );
		top2 =  object2->getY()- ( object2->getHeight()/2 );
		bottom1 = object1->getY()- ( object1->getHeight()/2 ) + object1->getHeight();
		bottom2 = object2->getY()- ( object2->getHeight()/2 ) + object2->getHeight();

 	   glMatrixMode(GL_MODELVIEW);
      glLoadIdentity();
      glTranslatef(0.0f,0.0f,0.0f);
      glColor3f(1.0f, 0.0f, 0.0f);
      drawRectangle(left1,top1,right1,bottom1,-20.0f);
      drawRectangle(left2,top2,right2,bottom2,-20.0f);

// Check for basic bounding box collision.
		if ( bottom1 < top2 ) return ( 0 );
		if ( top1 > bottom2 ) return ( 0 );

		if ( right1 < left2 ) return ( 0 );
		if ( left1 > right2 ) return ( 0 );

// We're colliding since no function has returned zero yet, so, calculate the overlapping rectangle
// we'll use for checking the pixels from each image.

		if ( bottom1 > bottom2 ) over_bottom = bottom2;
		else over_bottom = bottom1;

		if ( top1 < top2 ) over_top = top2;
		else over_top = top1;

		if ( right1 > right2 ) over_right = right2;
		else over_right = right1;

		if ( left1 < left2 ) over_left = left2;
		else over_left = left1;

 	   glMatrixMode(GL_MODELVIEW);
      glLoadIdentity();
      glTranslatef(0.0f,0.0f,0.0f);
      glColor3f(0.0f, 0.0f, 1.0f);
      drawRectangle(over_left,over_top,over_right,over_bottom,-20.0f);

		right_off  = ( over_right - ( object2->getX()- ( object2->getWidth()/2 ) ) );
		top_off    = ( over_top - ( object2->getY()- ( object2->getHeight()/2 ) ) );
		left_off   = ( over_left - ( object2->getX()- ( object2->getWidth()/2 ) ) );
		bottom_off = ( over_bottom - ( object2->getY()- ( object2->getHeight()/2 ) ) );

		if ( right_off  > object2->getWidth() ) { right_off  = object2->getWidth();  }
		if ( top_off > object2->getHeight() ) { top_off = object2->getHeight(); }
		if ( left_off  < 0 ) { left_off = 0; }
		if ( bottom_off   < 0 ) { bottom_off = 0; }

 	   glMatrixMode(GL_MODELVIEW);
      glLoadIdentity();
      glTranslatef(0.0f,0.0f,0.0f);
      glColor3f(1.0f, 0.0f, 1.0f);
      drawRectangle(left_off,top_off,right_off,bottom_off,-20.0f);

		int step = 1;

// We got the rectangle for both images, so, let's check for them now.
// Gotta lock the surfaces first - it's an SDL requirement.
		SDL_LockSurface ( surface1 );
		SDL_LockSurface ( surface2 );
		for ( px = ( Uint32 ) left_off; px <= ( Uint32 ) right_off;  px+=step ) {
			for ( py = ( Uint32 ) top_off;  py <= ( Uint32 ) bottom_off; py+=step ) {

// For every pixel in the region...

//				GetPixelRGBA(surface1,px,py,pr,pg,pb,pa1);// Get the pixel's alpha from the second image.
				GetPixelRGBA(surface2,px,py,pr,pg,pb,pa2);// Get the pixel's alpha from the second image.

 	   glMatrixMode(GL_MODELVIEW);
      glLoadIdentity();
      glTranslatef(0.0f,0.0f,0.0f);
      glColor3f(1.0f, 1.0f, 1.0f);
      drawRectangle(px,py,px+1,py+1,-20.0f);

				/*
					DEBUG INFO: Remove this comment and recompile the library for showing a red area marking
							the collision area found in the destination sprite.
					gp2d::DisableTexturing();
					gp2d::SetPointSize(1.0f);
					gp2d::BeginPoints();
						if(pa2>1){ SetColor3(1,0,0); gp2d::DrawPixel(px,py); }
					gp2d::EndPoints();
					gp2d::EnableTexturing();
				*/

// If there's collision in the destination image (alpha is not zero) unlock the surfaces and return a true value.
// if(pa2>1){ SDL_UnlockSurface(surface1); SDL_UnlockSurface(surface2); return(1); }
				if ( pa2>0 ) {
						SDL_UnlockSurface ( surface1 );
						SDL_UnlockSurface ( surface2 );

 	   glMatrixMode(GL_MODELVIEW);
      glLoadIdentity();
      glTranslatef(0.0f,0.0f,0.0f);
      glColor3f(1.0f, 0.0f, 1.0f);
      drawRectangle(px,py,px+1,py+1,-20.0f);

//						return ( 1 );
				}
			}
		}

// No collision in the region, unlock the surfaces and return false.

		SDL_UnlockSurface ( surface1 );
		SDL_UnlockSurface ( surface2 );

}

//==============================================================================
// Collision event. Empty implementation.
//==============================================================================
GP2DCollisionEvent::GP2DCollisionEvent() {
}

GP2DCollisionEvent::~GP2DCollisionEvent() {
}

void GP2DCollisionEvent::collided(GP2DCollision& collision) {
    cout << "GP2DCollisionEvent::collided()" << endl;
}

//==============================================================================
// Collision manager.
//==============================================================================

GP2DCollisionManager::GP2DCollisionManager() {
}

GP2DCollisionManager::~GP2DCollisionManager() {
    m_collisions.clear(); // clear out just to be sure.. probably not necessary,
                          // because the m_collisions goes out of scope anyway.
}

void GP2DCollisionManager::addCollision(GP2DCollision* coll) {
    // re-set the iterator to the first available spot in the vector.
    m_iter = m_collisions.begin();
    // now, add a collision to the vector
    m_collisions.insert(m_iter, coll);
}

void GP2DCollisionManager::registerEvent(GP2DCollisionEvent* event) {
    m_event = event;
}

void GP2DCollisionManager::handleCollisions() {
    vector<GP2DCollision*>::iterator it;
    for (it = m_collisions.begin() ; it < m_collisions.end(); it++) {
        GP2DCollision* coll = *it;
        if(coll->isColliding()) {
            // check if the registered callback event is NOT null
            if(m_event != NULL) {
                // not null? then callback damn it!
                m_event->collided(*coll);
            }
        }
    }
}
