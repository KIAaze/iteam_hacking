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

#include "gui.h"


namespace GP2D {

/*
*  First up, the Widget class.  Unlike the previous system, this is not a base
*  class, nor does it have children.  The GUI class, however, is able cable of
*  creating children.
*/

Widget::Widget() {
    inputHandler = new GP2DInputHandler;
    inputHandler->setGlobalKeysEnabled(false);
    inputHandler->setMouseEnabled(true);
    width = 0.0;
    height = 0.0;
    x = 0.0;
    y = 0.0;
}

Widget::~Widget(void) {
}

void Widget::update() {
    sprite->draw();
    if (*onUpdateCallback != NULL) {
        Widget->onUpdateCallback();
    }
}

// THE ABOVE AND BELOW FUNCTIONS ALMOST CERTAINLY DO NOT WORK
// I really doubt the syntax is correct :(

void Widget::onUpdate(void (*callbackFunction)) {
    Widget->onUpdateCallback = callbackFunction;
}

void Widget::loadTexture(std::string filePath) {
    texture = new GP2DTexture(filePath);
    sprite = new GP2DSprite(texture);
    width = texture->getWidth();
    height = texture->getHeight();
}

void Widget::setTexture(GP2DTexture* newTexture) {
    texture = newTexture;
}

void Widget::registerMouseDown(GP2DMouseEvent::GP2DMouseButton button, void (*callbackFunction)(GP2DMouseEvent&)) {
        inputHandler->registerMouseDown(GP2DMouseEvent::GP2DMouseButton button, void (*callbackFunction)(GP2DMouseEvent&));
}

void Widget::registerMouseUp(GP2DMouseEvent::GP2DMouseButton button, void (*callbackFunction)(GP2DMouseEvent&)) {
        inputHandler->registerMouseUp(GP2DMouseEvent::GP2DMouseButton button, void (*callbackFunction)(GP2DMouseEvent&));
}

int Widget::getUid() {
    return uid;
}

void Widget::setUid(int newUid) {
    uid = newUid;
}

void Widget::pollEvents() {
    inputHandler->handleInputEvents();
}

/*
*  Gui class
*/

Gui::Gui(void) {
    uidCount = 0;
    currentUID = 0;
    currentWidget = NULL;
}

Gui::~Gui(void) {
    map<int, Widget*>::iterator i;
    for(i = widgets.begin() ; i != widgets.end() ; i++) {
        delete *i;
        widget.erase(i);
    }
}

void Gui::pollEvents() {
    //This function is incomplete
    currentWidget->pollEvents();
}

void Gui::registerMouseButtonDown(int uid, GP2DMouseEvent::GP2DMouseButton button, void (*callbackFunction)(GP2DMouseEvent&)) {
    currentUID = uid;
    widgets[uid]->registerMouseDown(GP2DMouseEvent::GP2DMouseButton button, void (*callbackFunction)(GP2DMouseEvent&));
}

void Gui::registerMouseButtonUp(int uid, GP2DMouseEvent::GP2DMouseButton button, void (*callbackFunction)(GP2DMouseEvent&)) {
    currentUID = uid;
    widgets[uid]->registerMouseUp(GP2DMouseEvent::GP2DMouseButton button, void (*callbackFunction)(GP2DMouseEvent&));
}

void Gui::setX(float newX) {
    x = newX;
}

void Gui::setY(float newY) {
    y = newY;
}

void Gui::setWidth(int newWidth) {
    //What surface does this class use, anyway?
}

void Gui::setHeight(int newHeight) {
    //see above
}

int Gui::addWidget() {
    currentUID = uidCount;
    uidCount += 1;
    widgets[uidCount] = new Widget();
    widgets[uidCount]->
    return currentUID;
}

Widget Gui::getWidget(int uid) {
    return &widgets[uid];
}
