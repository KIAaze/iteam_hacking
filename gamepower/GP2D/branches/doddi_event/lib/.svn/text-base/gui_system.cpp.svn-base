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
#if 0
	map<int, void (*)(void)>		GuiManager::MouseLeftDownEvents;
	map<int, void (*)(void)>		GuiManager::MouseLeftUpEvents;
	map<int, void (*)(void)>		GuiManager::MouseRightDownEvents;
	map<int, void (*)(void)>		GuiManager::MouseRightUpEvents;
#endif
	vector<Widget*>					GuiManager::Canvases;


	GuiManager::GuiManager(inputHandler *ptrEventHandler) {


		CurrentUID = 0;

		RegisterMyself(ptrEventHandler);
	}
	GuiManager::~GuiManager() {
		
		for (int idx=0; idx < Canvases.size(); idx++) {
			delete Canvases[idx];
		}
	}

	int GuiManager::CreateCanvas(int xpos, int ypos, int width, int height) {

		Canvas *tempWidget = new Canvas(xpos, ypos, width, height, "Canvas");

		printf("canvas UID=%i created\n", tempWidget->GetUID());

		// Add the canvas to the list of canvases
		Canvases.push_back(tempWidget);		
		printf("Canvas added to gui manager\n");
		return tempWidget->GetUID();
	}

	int GuiManager::AddToCanvas(int ID, Widget *wid) {
		// TODO: Need to check if the canvas exists
		// TODO: Make the widget cordinates relative?????????
		printf("About to add child to canvas\n");
		//Adds a widget to the specified canvas
		Canvases[ID]->AddChild(wid);
	}

	// This has the resposibility of deleting the canvas which will then dlete all
	// associated widgets.
	int GuiManager::DeleteCanvas(int id) {

		// TODO: Remove from the list
		delete Canvases[id];
		vector<Widget*>::iterator it;
		it = Canvases.begin();
		for (int idx=0; idx<=id; idx++) {
			if (idx==id) {
				Canvases.erase(it);
				break;
			}
		}
	}

	// This registers all events for all widgets using the widgets UID
	// EventType is #define for the events that are allowed
	void GuiManager::RegisterEvent(int UID, void(*func)(), int EventType, int key) {
#if 0
		switch(EventType) {
			case SDL_BUTTON_LEFT:
				if (key==GP2D_MOUSEDOWN) {
					if (MouseLeftDownEvents[UID] == NULL) {
						MouseLeftDownEvents[UID] = func;
					}
				}
				else if (key==GP2D_MOUSEUP) {
					if (MouseLeftUpEvents[UID] == NULL) {
						MouseLeftUpEvents[UID] = func;
					}
				}
				break;
			case SDL_BUTTON_RIGHT:
				if (key==GP2D_MOUSEDOWN) {
					if (MouseLeftDownEvents[UID] == NULL) {
						MouseLeftDownEvents[UID] = func;
					}
				}
				else if (key==GP2D_MOUSEUP) {
					if (MouseRightUpEvents[UID] == NULL) {
						MouseRightUpEvents[UID] = func;
					}
				}
				break;
		}
#endif
	}

	// This update function is responsible for:
	// Finding the widget that the mouse is currently over - updating UniqueEventKey (UID)
	// Updating the mouse coords and status
	void GuiManager::OnUpdate(int mx, int my) {

		printf("Entering OnUpdate\n");

		Widget* thisWidget = NULL;

		unsigned int lastID = CurrentUID;
		unsigned int thisID=0;
		
		printf("GUI mouse coords: X=%i, Y=%i\n", mx, my);
		mouseX = mx, mouseY=my;

		// Loop round all available canvases and
		// check if the mouse coordinates are within the area
		// TODO: Should check what local canvas its on, if any and update widgets in that only
		for (int idx=0; idx < Canvases.size(); idx++) {
			thisWidget = Canvases[idx]->OnUpdate(mx, my);
			if (thisWidget!=NULL) {
				if (currentWidget==NULL) {
					CurrentUID = thisWidget->GetUID();
					//Remember this widget for next time
					currentWidget = thisWidget;
					break;
				}
				else if (thisWidget->GetUID() != currentWidget->GetUID()) {
					// We found a matching ID
					// TODO: How about when Canvases overlap!!!!!!!????????????
					printf("Found a widget\n");

					// TODO: Previous widget looses focus
					currentWidget->LostFocus();
					
					CurrentUID = thisWidget->GetUID();
					//Remember this widget for next time
					currentWidget = thisWidget;
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
		for (int idx=0; idx < Canvases.size(); idx++) {
			Canvases[idx]->Update();
		}
	}

	// Draw all base widgets that are visible
	// Each base widget is responsible for drawing its children
	void GuiManager::Draw() {
		for (int idx=0; idx < Canvases.size(); idx++) {
			Canvases[idx]->Draw();
		}		
	}

	// Calls only the relevant widgets callback for mouse*** by using UniqueEventKey (UID)
	void GuiManager::OnMouseLeftDown(int mx, int my) {
		printf("GUI Manager LMD\n");
		if (currentWidget != NULL) {
			currentWidget->MouseLeftDown();
		}
	}
	void GuiManager::OnMouseLeftUp(int mx, int my) {
		printf("GUI Manager LMU\n");
		if (currentWidget != NULL) {
			currentWidget->MouseLeftUp();
		}
	}
	void GuiManager::OnMouseRightDown(int mx, int my) {
		printf("GUI Manager RMD\n");
		if (currentWidget != NULL) {
			currentWidget->MouseRightDown();
		}
	}
	void GuiManager::OnMouseRightUp(int mx, int my) {
		printf("GUI Manager LMU\n");
		if (currentWidget != NULL) {
			currentWidget->MouseRightUp();
		}
	}

	void GuiManager::RegisterMyself(inputHandler *ptrEventHandler) {
		//Need to register all mouse events with the event handler
		ptrEventHandler->registerInputCallback(SDL_BUTTON_LEFT, OnMouseLeftDown, GP2D_MOUSEDOWN);
		ptrEventHandler->registerInputCallback(SDL_BUTTON_RIGHT, OnMouseRightDown, GP2D_MOUSEDOWN);
		ptrEventHandler->registerInputCallback(SDL_BUTTON_LEFT, OnMouseLeftUp, GP2D_MOUSEUP);
		ptrEventHandler->registerInputCallback(SDL_BUTTON_RIGHT, OnMouseRightUp, GP2D_MOUSEUP);

		ptrEventHandler->registerInputCallback(SDL_MOUSEMOTION, OnUpdate, GP2D_MOUSEMOTION);			
	}


	///////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////

	// Stores latest UniqueEventKey
	// Registers with its parent, i.e. parent->AddChild()
	Widget::Widget(int x, int y, int width, int height, string name) {
		UID = GuiManager::GlobalUID;
		GuiManager::GlobalUID++;

		WidgetName = name;
		wX = x; wY = y;
		wWidth = width;
		wHeight = height;

		isOver=false;
		isPressed[0] = false;
		isPressed[1] = false;
	}

	Widget::~Widget() {
		printf("%s is deleting children\n", WidgetName.c_str());

		int Size = Children.size();
		for (int idx1=0; idx1 < Size; idx1++) {
			delete Children[idx1];
			Children.pop_back();
		}
	}

	void Widget::AddChild(Widget* child) {
		printf("%s: adding child\n", WidgetName.c_str());
		Children.push_back(child);
	}

	int Widget::GetUID()	{
		return UID; 
	}

	// This function iterates through all its children
	// if it finds a match in one of its childred it uses the
	// childs value as return.
	Widget* Widget::OnUpdate(int mx, int my) {

		Widget *returnWidget;

		printf("%s: OnUpdate called\n", WidgetName.c_str());
		if ( mx>=wX && mx<=(wX+wWidth) && my>=wY && my<=(wY+wHeight)) {
			for (int idx=0; idx < Children.size(); idx++) {
				returnWidget = Children[idx]->OnUpdate(mx, my);
				if (returnWidget != NULL) {
					isOver = false;
					return returnWidget;
				}
			}
			isOver = true;
			return this;
		}
		isOver = false;
		return NULL;
	}

	// TODO: Need to implement an out of focus function
	// so that these isPressed can be cleared/
	// GuiManager can call out of focus before switching to the next in focus widget
	void	Widget::MouseLeftDown() {
		isPressed[0] = true;
	}
	void	Widget::MouseLeftUp() {
		isPressed[0] = false;
	}
	void	Widget::MouseRightDown() {
		isPressed[1] = true;
	}
	void	Widget::MouseRightUp() {
		isPressed[2] = false;
	}
	void	Widget::MouseMove() {
	}
	void	Widget::LostFocus() {
		isPressed[0] = false;
		isPressed[1] = false;
	}

	// Updates itself then all other children widgets.
	void Widget::Update() {
		for (int idx=0; idx < Children.size(); idx++) {
			Children[idx]->Update();
		}
	}

	// Draws itslelf then all other children widgets.		
	void Widget::Draw() {

		for (int idx=0; idx < Children.size(); idx++) {
			Children[idx]->Draw();
		}
	}

	Canvas::Canvas(int x, int y, int width, int height, string name) 
			: Widget(x, y, width, height, name)	{
		printf("Canvas widget created\n");
	}
	Widget* Canvas::OnUpdate(int mx, int my) {
		printf("Canvas OnUpate\n");
		return(Widget::OnUpdate(mx, my));
	}
	void	Canvas::MouseLeftDown() {
		printf("Canvas mouse down\n");
		Widget::MouseLeftDown();
	}
	void Canvas::Update() {
		Widget::Update();	
	}
	void Canvas::Draw() {
		// Convert it to local coordinate size
		GLfloat x = (SCREEN_WIDTH/2.0f)-wX;
		GLfloat y = (SCREEN_HEIGHT/2.0f)-wY;
		GLfloat w = (SCREEN_WIDTH/2.0f)-(wX+wWidth);
		GLfloat h = (SCREEN_HEIGHT/2.0f)-(wY+wHeight);

		DrawRectangle(x, y, w, h, 1,1,1);
		Widget::Draw();
	}
}
