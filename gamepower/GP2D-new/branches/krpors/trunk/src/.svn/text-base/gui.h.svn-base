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
This engine requires:
    * OpenGL/Mesa development libraries
    * C compiler (gcc 4.2 used)
    * SDL development libraries
        - libsdl1.2-dev
        - libsdl-image1.2-dev
        - libsdl-mixer1.2-dev
    * FreeType development libraries
        - libfreetype6-dev

GUI FUNCTIONS (version 0.0.1)
By Judo
*/

#ifndef _GP2D_GUI_H
#define _GP2D_GUI_H

#include "core.h"
#include "input.h"

namespace gp2d {

class Widget {

public:

    /**
    * This constructor creates the inputHandler, disables global keys,
    * enables mouse events, and sets x and y coordinates and width and
    * height to 0 (or 0.0).
    */
    Widget();

    /**
    * Just a generic destructor.
    */
    ~Widget();

    /**
    * update() does two things:
    * 1.  Draws the Widget, using GP2DSprite's draw() function.
    * 2.  Calls on a function, if specified through onUpdate().
    */
    void update();

    /**
    * onUpdate() is used to set a pointer to a function, which is called
    * whenever the update() function is used.  If you want to remove a
    * callback, pass NULL to this function.
    *
    * @param function The function to be called.
    */
    void onUpdate(void (*callbackFunction));

    /**
    * setX() does exactly as the name implies: it changes/sets the x-
    * coordinate of this Widget.
    *
    * @param newX The new x-coordinate.
    */
    void setX(float newX);

    /**
    * setY() does exactly as the name implies: it changes/sets the y-
    * coordinate of this Widget.
    *
    * @param newY The new y-coordinate.
    */
    void setY(float newY);

    /**
    * loadTexture() not only loads the image to be used for the widget,
    * it also creates the GP2DSprite object.  The texture can be any
    * format that SDL supports.
    *
    * @param filePath The file path to the texture image.
    */
    void loadTexture(std::string filePath);

    /**
    * setTexture() is not very similar to loadTexture().  This function
    * only changes the Widget's pointer to a GP2DTexture.  This is the
    * best way to change an image on a mouseOver event or similar.  This
    * function does not read any files.
    *
    * @param newTexture The new GP2DTexture to be used as the image.
    */
    void setTexture(GP2DTexture newTexture);

    /**
    * registerMouseDown() registers an event that will be called on when
    * the left (?) mouse button is pressed down.
    *
    * @param button The button from GP2DMouseEvent::GP2DMouseButton enumeration
    *   which should be registered.
    * @param callbackFunction The function callback of prototype
    *   `void myFunc(GP2DMouseEvent&)`.
    */
    void registerMouseDown(GP2DMouseEvent::GP2DMouseButton button, void (*callbackFunction)(GP2DMouseEvent&));

    /**
    * registerMouseUp() registers an event that will be called on when
    * the left (?) mouse button is released.
    *
    * @param button The button from GP2DMouseEvent::GP2DMouseButton enumeration
    *   which should be registered.
    * @param callbackFunction The function callback of prototype
    *   `void myFunc(GP2DMouseEvent&)`.
    */
    void registerMouseUp(GP2DMouseEvent::GP2DMouseButton button, void (*callbackFunction)(GP2DMouseEvent&));

    /**
    * getUID() is a simple function to get the unique identifier of
    * the Widget.
    *
    * @return The Widget's ID.
    */
    int getUid();

    /**
    * setUID() is intended to be used by the Gui class.  It simply
    * sets a value (int) to the private uid variable, the identifier
    * for this object.
    *
    * @param uid The value to be set as the identifying number.
    */
    void setUid(int uid);

    /**
    * pollEvents calls on this Widget's GP2DInputHandler to poll mouse
    * events by using the handleInputEvents() function.
    */
    void pollEvents();

private:

    int uid;

    float width;
    float height;

    float x;  //in relation to the surface it's drawn on?
    float y;

    GP2DTexture* texture;
    GP2DSprite* sprite;
//    GP2DInputHandler* inputHandler;

    void (*onUpdateCallback);
    //void (*onMouseOverCallback);
    //void (*onMouseOutCallback);

};

class Gui {

public:

    /**
    * Constructor.
    * Please note that this class is not required to use the Widget
    * class, nor do the functions need to do what is specified below,
    * due to the use of virtual functions.
    */
    Gui();

    /**
    * Virtual destructor.
    * Used in this base class, it removes all Widgets.
    */
    virtual ~Gui();

    /**
    * This is the only function needed to be called back during a loop.
    * i.e. while(!quit) { guiPollEvents(); }
    * This is the function that handles collision detection between the
    * mouse and Widgets within the GUI.  It also calls on the focused
    * Widget's inputHandler to respond to events.
    */
    void guiPollEvents();

    /**
    * registerMouseButtonDown() and  adds an event to a Widget, specified by
    * the UID of the Widget.
    * *Down() is called when the left (?) mouse button is pressed down.
    * *Up() is called when the left (?) mouse button is released.
    *
    * @param uid The UID of the Widget which is being modified
    * @param button The button from GP2DMouseEvent::GP2DMouseButton enumeration
    *   which should be registered.
    * @param callbackFunction The function callback of prototype
    *   `void myFunc(GP2DMouseEvent&)`.
    */
    virtual void registerMouseButtonDown(int uid, GP2DMouseEvent::GP2DMouseButton button, void (*callbackFunction)(GP2DMouseEvent&));
    virtual void registerMouseButtonUp(int uid, GP2DMouseEvent::GP2DMouseButton button, void (*callbackFunction)(GP2DMouseEvent&));

    /**
    * setX() does exactly as the name implies: it changes/sets the x-
    * coordinate of this GUI, which, I suggest, should stay at 0.0
    *
    * @param newX The new x-coordinate.
    */
    virtual void setX(float newX);

    /**
    * setY() does exactly as the name implies: it changes/sets the y-
    * coordinate of this GUI, which, I suggest, should stay at 0.0
    *
    * @param newY The new y-coordinate.
    */
    virtual void setY(float newY);

    /**
    * setWidth() sets the width of the GUI canvas.  You'd probably want
    * this to be the same width as the game window if it's a main menu,
    * but, as seen with the Window class, it can also be used to create
    * an interface in-game, like GTK and QT do.
    *
    * @param newWidth The width, in pixels, of the GUI.
    */
    virtual void setWidth(int newWidth);

    /**
    * setHeight() sets the height of the GUI canvas.  You'd probably want
    * this to be the same height as the game window if it's a main menu,
    * but, as seen with the Window class, it can also be used to create
    * an interface in-game, like GTK and QT do.
    *
    * @param newHeight The height, in pixels, of the GUI.
    */
    virtual void setHeight(int newHeight);

    /**
    * adds a widget to the GUI canvas, returning the UID of the Widget.
    * The returned UID can, or should, be used to set the Widget's
    * properties.
    *  currentWidget = addWidget();
    *  setWidgetWidth(currentWidget, 640);
    *
    * @return An int identifying the newly-created Widget (UID).
    */
    int addWidget();

    /**
    * getWidget() returns a reference to the Widget specified by the UID.
    * For example, let's say we have Widget* currentWidget; and
    * we want to currentWidget->setX(0.0);.  We need a pointer to that
    * Widget, so we get it with this function:
    *  currentWidget = getWidget(1); //where 1 is the UID
    *
    * @param uid The ID of the desired Widget.
    *
    * @return A reference to a Widget.
    */
    Widget getWidget(int uid);

private:

    float x;
    float y;

    int width;
    int height;

    Widget* currentWidget;
    int uidCount;
    int currentUID;
    int mouseX, mouseY;

    std::map<int, Widget*> widgets;  //a list of widgets controlled by this object

};

class Window : public Gui {

    public:

        Window();
        ~Window();

    private:

};

} // namespace gp2d


#endif /*_GP2D_GUI_H*/

