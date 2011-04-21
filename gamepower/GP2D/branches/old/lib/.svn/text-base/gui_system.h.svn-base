/*
	This file is part of GamePower 2D.

    GamePower 2D is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    GamePower 2D is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with GamePower 2D; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

===================================================================================
GAMEPOWER 2D ENGINE
===================================================================================
This engine requires:	* OpenGL/Mesa development libraries
								* C compiler (gcc 4.2 used)
								* SDL development libraries
								  - libsdl1.2-dev
                          - libsdl-image1.2-dev
                          - libsdl-mixer1.2-dev
                        * FreeType development libraries
                          - libfreetype6-dev

INPUTHANDLER FUNCTIONS (version 0.0.1)
By Doddi
*/

#ifndef _GP2D_GUISYSTEM_H
#define _GP2D_GUISYSTEM_H

#include "gp2d.h"
#include <list>

namespace gp2d {

	class Widget {

		public:
			// Stores latest UniqueEventKey
			// Registers with its parent, i.e. parent->AddChild()
			Widget ( int x, int y, int width, int height, string name );
			virtual ~Widget();
			void AddChild ( Widget *child );

			int	GetUID();
			virtual Widget	*OnUpdate ( int mx, int my );
			virtual void	MouseLeftDown();
			virtual void	MouseLeftUp();
			virtual void	MouseRightDown();
			virtual void	MouseRightUp();
			virtual void	LostFocus();
			virtual void	GotFocus();
			virtual void	MouseMove();
			virtual void 	Update();// Updates itself then all other children widgets.
			virtual void 	Draw();// Draws itslelf then all other children widgets.

			std::string WidgetName;
			unsigned long UID;
			float wX, wY;
			float wWidth, wHeight;
			bool isVisible;
			bool isEnabled;
			bool isOver;
			bool isPressed[2];

			std::list<Widget*> Children;
		private:

	};

	class Canvas : public Widget {
		public:
			Canvas ( int x, int y, int width, int height, string name );

			virtual Widget* OnUpdate ( int mx, int my );
			virtual void MouseLeftDown();
			virtual void GotFocus();
			virtual void LostFocus();
			virtual void Update();
			virtual void Draw();
		private:

	};

	class GuiManager {

		public:
			GuiManager ( inputHandler *ptrEventHandler );
			~GuiManager();

// A canvas is a base widget upon where all other widget types can be placed
			static int CreateCanvas ( int xpos, int ypos, int width, int height );
			static int DeleteCanvas ( int id );
			static int AddToCanvas ( int ID, Widget *wid );

// This registers all events for all widgets using the widgets UID
// EventType is #define for the events that are allowed KEYUP, MOUSEDOWN, TIMER?? etc
			static void RegisterEvent ( int UID, void ( *func ) ( void ), int EventType, int key );


// Updating all widgets that are currently enabled
			static void Update();

// Draw all base widgets that are visible
// Each base widget is responsible for drawing its children
			static void Draw();

// *********************************************************************
// ******* Generic callback function for event handler ****************
// *********************************************************************
			static void RegisterMyself ( inputHandler *ptrEventHandler );
// Finding the widget that the mouse is currently over - updating UniqueEventKey (UID)
			static void OnUpdate ( int mx, int my );
// Calls only the relevant widgets callback for mouse*** by using UniqueEventKey (UID)
			static void OnMouseLeftDown ( int mx, int my );
			static void OnMouseLeftUp ( int mx, int my );
			static void OnMouseRightDown ( int mx, int my );
			static void OnMouseRightUp ( int mx, int my );

			static int GlobalUID;// This stores the next available UID for a widget
		private:
			static Widget *currentWidget;
			static int CurrentUID;// Holds the current widget that the mouse is over
			static int mouseX, mouseY;

// all base widgets are located in the gui manager
			static std::list<Widget*> Canvases;//These act like the canvas for the screen on which all other widgets can be placed
	};

}
#endif

