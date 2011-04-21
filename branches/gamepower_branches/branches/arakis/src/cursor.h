#ifndef _GP2D_CURSOR_H
#define _GP2D_CURSOR_H
#include "gp2d.h"

namespace gp2d {

	void showCursor();
	void hideCursor();
	
	enum GP2D_CURSORTYPES {
		GP2D_CURSOR_NORMAL = 0,
		GP2D_CURSOR_WAITING,
		GP2D_CURSOR_CROSS,
		GP2D_NUMCURSORS
	};
	typedef enum GP2D_CURSORTYPES GP2DCursor;

	class cursorType {
		private:
			static int mouseX, mouseY;
			bool enabled;
			GP2DCursor currentCursor;
			GP2DTexture cursorTextures[3];
		public:
			cursorType();
			~cursorType();
			void addCursor ( GP2DCursor type, GP2DTexture *tex );
			void setCursor ( GP2DCursor type );
			static void update ( int mx, int my );
			void draw(int x, int y);
			void enable ( bool enable );
	};
}

#endif
