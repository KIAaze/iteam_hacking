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

GUISYSTEM FUNCTIONS (version 0.0.1)
By Doddi
*/

#include "gp2d.h"
#include "core.h"
#include "gui_system.h"

namespace gp2d {

	Widget *GuiManager::currentWidget = NULL;
	int GuiManager::GlobalUID=0;
	int GuiManager::CurrentUID=0;
	int GuiManager::mouseX=0;
	int GuiManager::mouseY;
	list<Widget*> GuiManager::Canvases;

	// The Gui manager can be used in 2 ways.
	// 1. Using the event callback system, to use this a valid pointer to an event handling class needs to be passed
	// 2.
	GuiManager::GuiManager ( inputHandler *ptrEventHandler ) {

		CurrentUID = 0;

		if ( ptrEventHandler != NULL ) {
			RegisterMyself ( ptrEventHandler );
		}
	}
	GuiManager::~GuiManager() {
		list<Widget*>::iterator i;
		for ( i=Canvases.begin(); i != Canvases.end(); i++ ) {
			delete *i;
			Canvases.erase ( i );
		}
	}

	int GuiManager::CreateCanvas ( int xpos, int ypos, int width, int height ) {

		Canvas *tempWidget = new Canvas ( xpos, ypos, width, height, "Canvas" );

		PrintDebug ( "canvas UID=%i created\n", tempWidget->GetUID() );

		// Add the canvas to the list of canvases
		Canvases.push_back ( tempWidget );
		PrintDebug ( "Canvas added to gui manager\n" );
		return tempWidget->GetUID();
	}

	int GuiManager::AddToCanvas ( int ID, Widget *wid ) {
		// TODO: Need to check if the canvas exists
		// TODO: Make the widget cordinates relative?????????
		PrintDebug ( "About to add child to canvas\n" );
		//Adds a widget to the specified canvas
		list<Widget*>::iterator i;
		for ( i=Canvases.begin(); i != Canvases.end(); i++ ) {
			if ( ID == ( *i )->GetUID() ) {
				( *i )->AddChild ( wid );
			}
		}
		return 0;
	}

	// This has the resposibility of deleting the canvas which will then delete all
	// associated widgets.
	int GuiManager::DeleteCanvas ( int id ) {
		// TODO: Need to kow if the current widget is part
		// of the canvas about to be deleted
		currentWidget = NULL;
		list<Widget*>::iterator i;
		for ( i=Canvases.begin(); i != Canvases.end(); i++ ) {
			if ( id == ( *i )->GetUID() ) {
				delete *i;
				Canvases.erase ( i );
				break;
			}
		}
		return 0;
	}

	// This update function is responsible for:
	// Finding the widget that the mouse is currently over - updating UniqueEventKey (UID)
	// Updating the mouse coords and status
	void GuiManager::OnUpdate ( int mx, int my ) {

//		PrintDebug("Entering OnUpdate\n");

		Widget* thisWidget = NULL;

		// unsigned int lastID = CurrentUID;
		// unsigned int thisID=0;

		mouseX = mx, mouseY=my;

		// Loop round all available canvases and
		// check if the mouse coordinates are within the area
		// TODO: Should check what local canvas its on, if any and update widgets in that only
		list<Widget*>::iterator i;
		for ( i=Canvases.begin(); i != Canvases.end(); i++ ) {
			thisWidget = ( *i )->OnUpdate ( mx, my );
			if ( thisWidget!=NULL ) {
				if ( currentWidget==NULL ) {
					CurrentUID = thisWidget->GetUID();
//Remember this widget for next time
					currentWidget = thisWidget;
					currentWidget->GotFocus();
					break;
				} else if ( thisWidget->GetUID() != currentWidget->GetUID() ) {
// We found a matching ID
// TODO: How about when Canvases overlap!!!!!!!????????????
					currentWidget->LostFocus();

					CurrentUID = thisWidget->GetUID();
					//Remember this widget for next time
					currentWidget = thisWidget;

					currentWidget->GotFocus();
					break;
				}
			}
		}
	}

	// Updating all widgets that are currently enabled
	// Updating al widgets will allow them to be animated etc
	// TODO: Might need to pass TIME or Time elapsed??
	void GuiManager::Update() {
		// Loop round all available canvases and
		// call the Update for these
		// This will allow for animating button etc
		list<Widget*>::iterator i;
		for ( i=Canvases.begin(); i != Canvases.end(); i++ ) {
			( *i )->Update();
		}
	}

	// Draw all base widgets that are visible
	// Each base widget is responsible for drawing its children
	void GuiManager::Draw() {
		list<Widget*>::iterator i;
		for ( i=Canvases.begin(); i != Canvases.end(); i++ ) {
			( *i )->Draw();
		}
	}

	// Calls only the relevant widgets callback for mouse*** by using UniqueEventKey (UID)
	void GuiManager::OnMouseLeftDown ( int mx, int my ) {
		PrintDebug ( "GUI Manager LMD\n" );
		if ( currentWidget != NULL ) {
			currentWidget->MouseLeftDown();
		}
	}
	void GuiManager::OnMouseLeftUp ( int mx, int my ) {
		PrintDebug ( "GUI Manager LMU\n" );
		if ( currentWidget != NULL ) {
			currentWidget->MouseLeftUp();
		}
	}
	void GuiManager::OnMouseRightDown ( int mx, int my ) {
		PrintDebug ( "GUI Manager RMD\n" );
		if ( currentWidget != NULL ) {
			currentWidget->MouseRightDown();
		}
	}
	void GuiManager::OnMouseRightUp ( int mx, int my ) {
		PrintDebug ( "GUI Manager LMU\n" );
		if ( currentWidget != NULL ) {
			currentWidget->MouseRightUp();
		}
	}

	void GuiManager::RegisterMyself ( inputHandler *ptrEventHandler ) {
		//Need to register all mouse events with the event handler
		ptrEventHandler->registerInputCallback ( SDL_BUTTON_LEFT, OnMouseLeftDown, GP2D_MOUSEDOWN );
		ptrEventHandler->registerInputCallback ( SDL_BUTTON_RIGHT, OnMouseRightDown, GP2D_MOUSEDOWN );
		ptrEventHandler->registerInputCallback ( SDL_BUTTON_LEFT, OnMouseLeftUp, GP2D_MOUSEUP );
		ptrEventHandler->registerInputCallback ( SDL_BUTTON_RIGHT, OnMouseRightUp, GP2D_MOUSEUP );

		ptrEventHandler->registerInputCallback ( SDL_MOUSEMOTION, OnUpdate, GP2D_MOUSEMOTION );
	}


///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////

	// Stores latest UniqueEventKey
	// Registers with its parent, i.e. parent->AddChild()
	Widget::Widget ( int x, int y, int width, int height, string name ) {
		UID = GuiManager::GlobalUID;
		GuiManager::GlobalUID++;

		WidgetName = name;
		wX = ( -SCREEN_WIDTH/2.0f ) +x- ( width/2.0f );
		wY = ( -SCREEN_HEIGHT/2.0f ) +y- ( height/2.0f );
		wWidth = width;
		wHeight = height;

		isVisible=true;
		isEnabled=true;
		isOver=false;
		isPressed[0] = false;
		isPressed[1] = false;
	}

	Widget::~Widget() {
		list<Widget*>::iterator i;
		for ( i=Children.begin(); i != Children.end(); i++ ) {
			delete *i;
		}
		Children.clear();
	}

	void Widget::AddChild ( Widget* child ) {
		Children.push_back ( child );
	}

	int Widget::GetUID()	{
		return UID;
	}

	// This function iterates through all its children
	// if it finds a match in one of its children it uses the
	// child's value as return.
	Widget* Widget::OnUpdate ( int mx, int my ) {

		Widget *returnWidget=NULL;
		list<Widget*>::iterator i;

		float testX = mx- ( SCREEN_WIDTH/2.0f );
		float testY = my- ( SCREEN_HEIGHT/2.0f );
		if ( testX>=wX && testX<= ( wX+wWidth ) && testY>=wY && testY<= ( wY+wHeight ) ) {
			for ( i=Children.begin(); i != Children.end(); i++ ) {
				returnWidget = ( *i )->OnUpdate ( mx, my );
				if ( returnWidget != NULL ) {
					isOver = false;
					return returnWidget;
				}
			}
			isOver = true;
			return this;
		}

		// Not even in here - get out!
		isOver = false;
		return NULL;
	}

	void Widget::MouseLeftDown() {
		isPressed[0] = true;
	}
	void Widget::MouseLeftUp() {
		isPressed[0] = false;
	}
	void Widget::MouseRightDown() {
		isPressed[1] = true;
	}
	void Widget::MouseRightUp() {
		isPressed[2] = false;
	}
	void Widget::MouseMove() {
	}
	void Widget::LostFocus() {
		PrintDebug ( "%s Lost focus\n", WidgetName.c_str() );
		isPressed[0] = false;
		isPressed[1] = false;
	}
	void Widget::GotFocus() {
		PrintDebug ( "%s Got focus\n", WidgetName.c_str() );
	}

	// Updates itself then all other children widgets.
	void Widget::Update() {
		list<Widget*>::iterator i;
		for ( i=Children.begin(); i != Children.end(); i++ ) {
			( *i )->Update();
		}
	}

	// Draws itself then all other children widgets.
	void Widget::Draw() {
		if ( isVisible==true ) {
			list<Widget*>::iterator i;
			for ( i=Children.begin(); i != Children.end(); i++ ) {
				( *i )->Draw();
			}
		}
	}

	Canvas::Canvas ( int x, int y, int width, int height, string name )
			: Widget ( x, y, width, height, name )	{
		PrintDebug ( "Canvas widget created\n" );
	}

	// Canvas::~Canvas() {};

	Widget* Canvas::OnUpdate ( int mx, int my ) {
		return ( Widget::OnUpdate ( mx, my ) );
	}
	void	Canvas::MouseLeftDown() {
		PrintDebug ( "Canvas mouse down\n" );
		Widget::MouseLeftDown();
	}
	void Canvas::Update() {
		Widget::Update();
	}
	void Canvas::GotFocus() {
		Widget::GotFocus();
	}
	void Canvas::LostFocus() {
		Widget::LostFocus();
	}

	void Canvas::Draw() {
		Widget::Draw();
	}
}
