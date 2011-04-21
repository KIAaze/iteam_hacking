#include "input.hpp"

using namespace std;

namespace gp {

// Default implementation of the input handler:

GPInputHandler::GPInputHandler() :
        m_enabled(true) {
}
GPInputHandler::~GPInputHandler() {

}

gpBool GPInputHandler::isEnabled() const {
    return m_enabled;
}

void GPInputHandler::setEnabled(gpBool enabled) {
    m_enabled = enabled;
}

//=============================================================================

GPKeyboardHandler::GPKeyboardHandler() {
}

GPKeyboardHandler::~GPKeyboardHandler() {
    // TODO: delete actions?
}

void GPKeyboardHandler::registerKeyAction(GPKeyEvent::GPKey key, GPKeyAction* action) {
    m_input[key] = action;
}

void GPKeyboardHandler::unregisterKeyAction(GPKeyEvent::GPKey key) {
    // iterate over the 'OOP' key events
    map<GPKeyEvent::GPKey, GPKeyAction*>::iterator it;
    it = m_input.find(key);

    if(it != m_input.end()) {
        // XXX: I commented this out, because previously I `delete`d the action too.
        // I don't think that's good...
        // GPKeyAction* action = it->second;
        m_input.erase(key);
    }
}

void GPKeyboardHandler::unregisterGenericKeyAction(GPKeyAction* action) {
    m_globalKeyActions.erase(action);
}

void GPKeyboardHandler::registerGenericKeyAction(GPKeyAction* action) {
    m_globalKeyActions.insert(action);
}

void GPKeyboardHandler::handleEvent(SDL_Event& theEvent) {
    bool isKeyEvent =
        theEvent.type == SDL_KEYDOWN ||
        theEvent.type == SDL_KEYUP;

    // if not enabled, or it's not a keyevent, don't bother continuing
    if(!isKeyEvent || !isEnabled()) {
        return;
    }


    SDLKey key_sdl = theEvent.key.keysym.sym;
    SDLMod mod_sdl = theEvent.key.keysym.mod;
    gpUshort unicode_sdl = theEvent.key.keysym.unicode; // only works when SDL_EnableUNICODE(1)
    // since our map contains GPKeys, cast it from SDLKey to GPKey.
    GPKeyEvent::GPKey key = static_cast<GPKeyEvent::GPKey>(key_sdl);
    GPKeyEvent::GPKeyMod mod = static_cast<GPKeyEvent::GPKeyMod>(mod_sdl);

    GPKeyEvent event = GPKeyEvent(key, mod, unicode_sdl);

    // iterate over the 'OOP' key events
    map<GPKeyEvent::GPKey, GPKeyAction*>::iterator it;
    it = m_input.find(key);

    // if key binding is found...
    if(it != m_input.end()) {
        GPKeyAction* action = it->second;

        if(theEvent.type == SDL_KEYDOWN) {
            action->keyDown(event);
        } else if(theEvent.type == SDL_KEYUP) {
            action->keyUp(event);
        }
    }

    set<GPKeyAction*>::iterator it2;
    // iterate over every registered global key event here:
    for (it2 = m_globalKeyActions.begin(); it2 != m_globalKeyActions.end(); it2++) {
        // *it is a GPKeyAction*
        if(*it2 != NULL) {
            if(theEvent.type == SDL_KEYDOWN) {
                (*it2)->keyDown(event);
            } else if(theEvent.type == SDL_KEYUP) {
                (*it2)->keyUp(event);
            }
        }
    }

}

//=============================================================================

GPMouseHandler::GPMouseHandler() {
}

GPMouseHandler::~GPMouseHandler() {

}

void GPMouseHandler::registerMouseAction(GPMouseAction* action) {
    m_actions.insert(action);
}

void GPMouseHandler::unregisterMouseAction(GPMouseAction* action) {
    m_actions.erase(action);
}

void GPMouseHandler::unregisterAll() {
    m_actions.clear();
}

const GPPoint GPMouseHandler::getMousePosition() {
    int x, y;
    SDL_GetMouseState(&x, &y); //put mouse data in x an y
    GPPoint p;
    p.x = static_cast<gpFloat>(x);
    p.y = static_cast<gpFloat>(y);
    // return a point
    return p;
}


void GPMouseHandler::handleEvent(SDL_Event& theEvent) {
    bool isMouseEvent =
        theEvent.type == SDL_MOUSEBUTTONDOWN ||
        theEvent.type == SDL_MOUSEBUTTONUP ||
        theEvent.type == SDL_MOUSEMOTION;

    // are we supposed to proceed?
    //
    if(!isEnabled() || !isMouseEvent || m_actions.size() <= 0) {
        return;
    }

    // yes, mouseaction is defined, and enabled... now issue the callbacks.
    gpInt32 x = theEvent.motion.x;
    gpInt32 y = theEvent.motion.y;

    GPMouseEvent::GPMouseButton button;
    button = static_cast<GPMouseEvent::GPMouseButton>(theEvent.button.button);

    GPMouseEvent event(x, y, button);

    set<GPMouseAction*>::iterator it = m_actions.begin();
    while(it != m_actions.end()) {
        GPMouseAction* currAction = *it++;
        if(theEvent.type == SDL_MOUSEBUTTONDOWN) {
            m_mousePressed = true;
            currAction->mouseButtonDown(event);
        } else if(theEvent.type == SDL_MOUSEBUTTONUP) {
            m_mousePressed = false;
            if(m_mouseDragStarted) {
                currAction->mouseDragEnd(event);
                m_mouseDragStarted = false; // reset drag state.
            }
            currAction->mouseButtonUp(event);
        } else if(theEvent.type == SDL_MOUSEMOTION) {
            if(m_mousePressed) {
                m_mouseDragStarted = true; // enable drag state.
                currAction->mouseDragStart(event);
                m_mousePressed = false;
            }
            currAction->mouseMoved(event);
        }
    }
}

//=============================================================================

GPJoystickHandler::GPJoystickHandler() {
}

GPJoystickHandler::~GPJoystickHandler() {
}

void GPJoystickHandler::registerJoyAction(gpInt32 device, GPJoyAction* action) {
    m_mapJoystick[device] = action;
}

void GPJoystickHandler::unregisterJoyAction(gpInt32 device) {
    // iterate over the 'OOP' key events
    map<gpInt32, GPJoyAction*>::iterator it;
    it = m_mapJoystick.find(device);

    if(it != m_mapJoystick.end()) {
        // XXX: I commented this out, because previously I `delete`d the action too.
        // I don't think that's good...
        // GPJoyAction* action = it->second;
        m_mapJoystick.erase(device);
    }
}

void GPJoystickHandler::unregisterAll() {
    m_mapJoystick.clear();
}

void GPJoystickHandler::handleEvent(SDL_Event& theEvent) {
    bool isJoystickEvent =
        theEvent.type == SDL_JOYAXISMOTION ||
        theEvent.type == SDL_JOYBUTTONDOWN ||
        theEvent.type == SDL_JOYBUTTONUP;

    if(!isJoystickEvent || !isEnabled() || m_mapJoystick.size() == 0) {
        return;
    }

    gpInt32 device, button, value, state;
    GPJoyEvent::GPJoyAxis axis;
    axis = static_cast<GPJoyEvent::GPJoyAxis>(theEvent.jaxis.axis);
    button = theEvent.jbutton.button;
    value = theEvent.jaxis.value;
    state = theEvent.jbutton.state;
    device = -1;

    if(theEvent.type == SDL_JOYAXISMOTION){
        device = theEvent.jaxis.which;
    }
    if(theEvent.type == SDL_JOYBUTTONDOWN || theEvent.type == SDL_JOYBUTTONUP){
        device = theEvent.jbutton.which;
    }

    GPJoyEvent event(device, axis, value, button, state);
    map<gpInt32, GPJoyAction*>::iterator it;

    it = m_mapJoystick.find(device);
    if(it != m_mapJoystick.end()) {
        GPJoyAction* action = it->second;

        if(theEvent.type == SDL_JOYBUTTONDOWN) {
            action->buttonDown(event);
        } else if(theEvent.type == SDL_JOYBUTTONUP) {
            action->buttonUp(event);
        } else if(theEvent.type == SDL_JOYAXISMOTION) {
            action->axisChange(event);
        }
     }
}

//
void GPJoystickHandler::setJoystickEnabled(gpBool enabled) {
    if(enabled){
        SDL_JoystickEventState(SDL_ENABLE);
    } else {
        SDL_JoystickEventState(SDL_IGNORE);
    }
}

gpBool GPJoystickHandler::isJoystickEnabled() {
    return (SDL_JoystickEventState(SDL_QUERY) == SDL_ENABLE) ? true : false;
}

void GPJoystickHandler::scanJoysticks(){
    m_joystick.clear();
    for(gpInt32 i = 0; i <= SDL_NumJoysticks(); i++){
        m_joystick.push_back(SDL_JoystickOpen(i));
    }
    clog << SDL_NumJoysticks() << " joysticks found." << endl;
}

gpInt32 GPJoystickHandler::getNumJoysticks() {
    return SDL_NumJoysticks();
}


//=============================================================================

GPFocusHandler::GPFocusHandler() {
}

GPFocusHandler::~GPFocusHandler() {
}

void GPFocusHandler::registerFocusAction(GPFocusAction* action) {
    m_actions.insert(action);
}

void GPFocusHandler::unregisterFocusAction(GPFocusAction* action) {
    m_actions.erase(action);
}

void GPFocusHandler::unregisterAll() {
    m_actions.clear();
}

void GPFocusHandler::handleEvent(SDL_Event& event) {
    if(!isEnabled() || event.type != SDL_ACTIVEEVENT) {
        return; // no reason to continue from here.
    }

    if(event.type == SDL_ACTIVEEVENT) {
        set<GPFocusAction*>::iterator it = m_actions.begin();
        while(it != m_actions.end()) {
            GPFocusAction* action = *it++;
            if(event.active.gain == 0) {
                action->focusLost();
            } else {
                action->focusGained();
            }
        }
    }
}

//=============================================================================


GPInputProcessor::GPInputProcessor() {
}

GPInputProcessor::~GPInputProcessor() {
    m_handlers.clear();
}


void GPInputProcessor::addHandler(GPInputHandler* handler) {
    m_handlers.insert(handler);
}

void GPInputProcessor::pollEvents() {
    while(SDL_PollEvent(&m_event)) {
        set<GPInputHandler*>::iterator it;
        // iterate over every registered handler here:
        for (it = m_handlers.begin(); it != m_handlers.end(); it++) {
            if(*it != NULL) { // do null check please.
                // then handle the event using the SDL_Event. The function
                // handleEvent() is actually protected, but since we made
                // GPInputHandler a `friend' of this GPInputProcessor,
                // we can access that function!
                (*it)->handleEvent(m_event);
            }
        }
    }
}

//==============================================================================

// The GPKeyEvent.
GPKeyEvent::GPKeyEvent(const GPKey& key, const GPKeyMod& modifier, const gpShort unicode) :
        m_key(key),
        m_modifier(modifier),
        m_unicode(unicode) {
}
GPKeyEvent::~GPKeyEvent() { }

const GPKeyEvent::GPKey GPKeyEvent::getKey() const {
    return m_key;
}

const GPKeyEvent::GPKeyMod GPKeyEvent::getModifier() const {
    return m_modifier;
}

const gpUshort GPKeyEvent::getUnicode() const {
    return m_unicode;
}



//==============================================================================

GPMouseEvent::GPMouseEvent(gpInt32 x, gpInt32 y, GPMouseEvent::GPMouseButton button) :
    m_x(x),
    m_y(y),
    m_mouseButton(button) {

}

GPMouseEvent::~GPMouseEvent() {
}

const gpInt32 GPMouseEvent::getX() const {
    return m_x;
}

const gpInt32 GPMouseEvent::getY() const {
    return m_y;
}

const gpInt32 GPMouseEvent::getButton() const {
    return m_mouseButton;
}

//==============================================================================

GPJoyEvent::GPJoyEvent(gpInt32 device, GPJoyAxis axis, gpInt32 value, gpInt32 button, gpInt32 state) :
        m_joyDevice(device),
        m_joyButton(button),
        m_joyButtonState(state),
        m_joyAxis(axis),
        m_joyAxisValue(value) {
}

GPJoyEvent::~GPJoyEvent(){
}

const gpInt32 GPJoyEvent::getDevice() const {
    return m_joyDevice;
}

const gpInt32 GPJoyEvent::getButton() const {
    return m_joyButton;
}
const gpInt32 GPJoyEvent::getButtonState() const {
    return m_joyButtonState;
}
const GPJoyEvent::GPJoyAxis GPJoyEvent::getAxis() const {
    return m_joyAxis;
}

const gpInt32 GPJoyEvent::getAxisValue() const {
    return m_joyAxisValue;
}

//==============================================================================

/// Basic template implementation of the GPKeyAction.
GPKeyAction::GPKeyAction() { }
GPKeyAction::~GPKeyAction() { }
void GPKeyAction::keyDown(GPKeyEvent& event) { }
void GPKeyAction::keyUp(GPKeyEvent& event) { }


//==============================================================================


/// Basic template implementation of a GPMouseAction.
GPMouseAction::GPMouseAction() { }
GPMouseAction::~GPMouseAction() { }
void GPMouseAction::mouseButtonDown(GPMouseEvent& event) { }
void GPMouseAction::mouseButtonUp(GPMouseEvent& event) { }
void GPMouseAction::mouseMoved(GPMouseEvent& event) { }
void GPMouseAction::mouseDragStart(GPMouseEvent& event) { }
void GPMouseAction::mouseDragEnd(GPMouseEvent& event) { }

//==============================================================================

/// Basic template implementation of the GPJoyAction.
GPJoyAction::GPJoyAction() { }
GPJoyAction::~GPJoyAction() { }
void GPJoyAction::buttonDown(GPJoyEvent& event) { }
void GPJoyAction::buttonUp(GPJoyEvent& event) { }
void GPJoyAction::axisChange(GPJoyEvent& event) { }

//=============================================================================

GPFocusAction::GPFocusAction() { }
GPFocusAction::~GPFocusAction() { }
void GPFocusAction::focusGained() { }
void GPFocusAction::focusLost() { }


} // namespace gp

