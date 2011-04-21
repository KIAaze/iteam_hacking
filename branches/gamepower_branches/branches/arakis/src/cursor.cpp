#include "cursor.h"
using namespace std;

namespace gp2d {

	int cursorType::mouseX=0;
	int cursorType::mouseY=0;

	void showCursor() { SDL_ShowCursor ( SDL_ENABLE );  }
	void hideCursor() { SDL_ShowCursor ( SDL_DISABLE ); }
	
	cursorType::cursorType() {
		mouseX=0;
		mouseY=0;
		enabled=false;
		currentCursor=GP2D_CURSOR_NORMAL;
	}
	cursorType::~cursorType() {
		// TODO: ?????
		// ShowCursor(FALSE);
	}

	void cursorType::addCursor ( GP2DCursor type, GP2DTexture *tex ) {
		if ( type < GP2D_NUMCURSORS ) {
			if ( !glIsTexture ( tex->getId() ) ) {
				cout << "[cursorType::AddCursor] FATAL ERROR: no texture" << endl;
				exit ( 47 );
			}
			cursorTextures[type] = *tex;
			cout << "cursor " << type << " added" << endl;
		}
		else {
			cout << "Invalid cursor type" << endl;
		}
	}

	void cursorType::setCursor ( GP2DCursor type ) {

		if ( type < GP2D_NUMCURSORS ) {
			if ( glIsTexture ( cursorTextures[type].getId() ) ) {
				cout << "cursor " << type << " set" << endl;
				currentCursor = type;
			}
			else {
				cout << "FATAL ERROR: Cursor not initialised" << endl;
				exit ( 28 );
			}
		}
		else {
			cout << "Invalid cursor selected" << endl;
		}
	}

	void cursorType::enable ( bool enable ) {
		enabled = enable;
		if ( enable ) {	hideCursor(); } else { showCursor(); }
	}

	void cursorType::update ( int mx, int my ) {
		/*
          mouseX=mx-(VIEWPORT_WIDTH/2);
          mouseY=my-(VIEWPORT_HEIGHT/2);
		*/
		
		/*
		TODO: INPUTHANDLER SHOULD BE ONLY ONE INSTANCE, JUST
		LIKE ENGINE. OR FIND A WAY TO GET MOUSE X & Y 
		GLOBALLY
		*/
	}

#define CURSOR_SIZE	16
	void cursorType::draw(int x, int y) {
		/*
		if ( Enabled ) {
			if ( !glIsTexture ( CursorTextures[CurrentCursor].id ) ) {
				printf ( "FATAL ERROR: Cursor not initialised\n" );
				exit ( 28 );
			}

			glTranslatef ( mouseX+x,mouseY+y,0 );// Move to the sprite's coordinate.
			glRotatef ( 180,0,0,1 );// Rotate 180ร?ยบ in Z

			//PrintDebug("currentcursor=%i, is=%i\n", CurrentCursor, CursorTextures[CurrentCursor]->id);
			glBindTexture ( GL_TEXTURE_2D, CursorTextures[CurrentCursor].id );

			EnableTexturing();// Enable texturing, just in case
			glBlendFunc ( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );// Set blending parameters, for PNGs
			glEnable ( GL_BLEND );// Enable blending.

			glBegin ( GL_QUADS );
			glColor4f ( 1,1,1,1 );// Set the sprite's alpha
			glTexCoord2f ( 1, 1 ); glVertex3f ( -CURSOR_SIZE, -CURSOR_SIZE, 0 );
			glTexCoord2f ( 1, 0 ); glVertex3f ( -CURSOR_SIZE,  CURSOR_SIZE, 0 );
			glTexCoord2f ( 0, 0 ); glVertex3f ( CURSOR_SIZE,  CURSOR_SIZE, 0 );
			glTexCoord2f ( 0, 1 ); glVertex3f ( CURSOR_SIZE, -CURSOR_SIZE, 0 );
			glEnd();
		}
		*/
	}	
	
}
