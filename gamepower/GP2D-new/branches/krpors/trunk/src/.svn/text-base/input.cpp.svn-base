#include "input.h"

using namespace std;

namespace gp2d {

// Default implementation of the input handler:

GP2DInputHandler::GP2DInputHandler() :
        m_enabled(true) {
}
GP2DInputHandler::~GP2DInputHandler() {

}

gp2dBool GP2DInputHandler::isEnabled() const {
    return m_enabled;
}

void GP2DInputHandler::setEnabled(gp2dBool enabled) {
    m_enabled = enabled;
}

//=============================================================================

GP2DKeyboardHandler::GP2DKeyboardHandler() {
}

GP2DKeyboardHandler::~GP2DKeyboardHandler() {
    // TODO: delete actions?
}

void GP2DKeyboardHandler::registerKeyAction(GP2DKeyEvent::GP2DKey key, GP2DKeyAction* action) {
    m_input[key] = action;
}

void GP2DKeyboardHandler::unregisterKeyAction(GP2DKeyEvent::GP2DKey key) {
    // iterate over the 'OOP' key events
    map<GP2DKeyEvent::GP2DKey, GP2DKeyAction*>::iterator it;
    it = m_input.find(key);

    if(it != m_input.end()) {
        // XXX: I commented this out, because previously I `delete`d the action too.
        // I don't think that's good...
        // GP2DKeyAction* action = it->second;
        m_input.erase(key);
    }
}

void GP2DKeyboardHandler::unregisterGenericKeyAction(GP2DKeyAction* action) {
    m_globalKeyActions.erase(action);
}

void GP2DKeyboardHandler::registerGenericKeyAction(GP2DKeyAction* action) {
    m_globalKeyActions.insert(action);
}

void GP2DKeyboardHandler::handleEvent(SDL_Event& theEvent) {
    bool isKeyEvent =
        theEvent.type == SDL_KEYDOWN ||
        theEvent.type == SDL_KEYUP;

    // if not enabled, or it's not a keyevent, don't bother continuing
    if(!isKeyEvent || !isEnabled()) {
        return;
    }


    SDLKey key_sdl = theEvent.key.keysym.sym;
    SDLMod mod_sdl = theEvent.key.keysym.mod;
    gp2dUshort unicode_sdl = theEvent.key.keysym.unicode; // only works when SDL_EnableUNICODE(1)
    // since our map contains GP2DKeys, cast it from SDLKey to GP2DKey.
    GP2DKeyEvent::GP2DKey key = static_cast<GP2DKeyEvent::GP2DKey>(key_sdl);
    GP2DKeyEvent::GP2DKeyMod mod = static_cast<GP2DKeyEvent::GP2DKeyMod>(mod_sdl);

    GP2DKeyEvent event = GP2DKeyEvent(key, mod, unicode_sdl);

    // iterate over the 'OOP' key events
    map<GP2DKeyEvent::GP2DKey, GP2DKeyAction*>::iterator it;
    it = m_input.find(key);

    // if key binding is found...
    if(it != m_input.end()) {
        GP2DKeyAction* action = it->second;

        if(theEvent.type == SDL_KEYDOWN) {
            action->keyDown(event);
        } else if(theEvent.type == SDL_KEYUP) {
            action->keyUp(event);
        }
    }

    set<GP2DKeyAction*>::iterator it2;
    // iterate over every registered global key event here:
    for (it2 = m_globalKeyActions.begin(); it2 != m_globalKeyActions.end(); it2++) {
        // *it is a GP2DKeyAction*
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

GP2DMouseHandler::GP2DMouseHandler() {
}

GP2DMouseHandler::~GP2DMouseHandler() {

}

void GP2DMouseHandler::registerMouseAction(GP2DMouseAction* action) {
    m_actions.insert(action);
}

void GP2DMouseHandler::unregisterMouseAction(GP2DMouseAction* action) {
    m_actions.erase(action);
}

void GP2DMouseHandler::unregisterAll() {
    m_actions.clear();
}

const GP2DPoint GP2DMouseHandler::getMousePosition() {
    int x, y;
    SDL_GetMouseState(&x, &y); //put mouse data in x an y
    GP2DPoint p;
    p.x = static_cast<gp2dFloat>(x);
    p.y = static_cast<gp2dFloat>(y);
    // return a point
    return p;
}


void GP2DMouseHandler::handleEvent(SDL_Event& theEvent) {
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
    gp2dInt32 x = theEvent.motion.x;
    gp2dInt32 y = theEvent.motion.y;

    GP2DMouseEvent::GP2DMouseButton button;
    button = static_cast<GP2DMouseEvent::GP2DMouseButton>(theEvent.button.button);

    GP2DMouseEvent event(x, y, button);

    set<GP2DMouseAction*>::iterator it = m_actions.begin();
    while(it != m_actions.end()) {
        GP2DMouseAction* currAction = *it++;
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

GP2DJoystickHandler::GP2DJoystickHandler() {
}

GP2DJoystickHandler::~GP2DJoystickHandler() {
}

void GP2DJoystickHandler::registerJoyAction(gp2dInt32 device, GP2DJoyAction* action) {
    m_mapJoystick[device] = action;
}

void GP2DJoystickHandler::unregisterJoyAction(gp2dInt32 device) {
    // iterate over the 'OOP' key events
    map<gp2dInt32, GP2DJoyAction*>::iterator it;
    it = m_mapJoystick.find(device);

    if(it != m_mapJoystick.end()) {
        // XXX: I commented this out, because previously I `delete`d the action too.
        // I don't think that's good...
        // GP2DJoyAction* action = it->second;
        m_mapJoystick.erase(device);
    }
}

void GP2DJoystickHandler::unregisterAll() {
    m_mapJoystick.clear();
}

void GP2DJoystickHandler::handleEvent(SDL_Event& theEvent) {
    bool isJoystickEvent =
        theEvent.type == SDL_JOYAXISMOTION ||
        theEvent.type == SDL_JOYBUTTONDOWN ||
        theEvent.type == SDL_JOYBUTTONUP;

    if(!isJoystickEvent || !isEnabled() || m_mapJoystick.size() == 0) {
        return;
    }

    gp2dInt32 device, button, value, state;
    GP2DJoyEvent::GP2DJoyAxis axis;
    axis = static_cast<GP2DJoyEvent::GP2DJoyAxis>(theEvent.jaxis.axis);
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

    GP2DJoyEvent event(device, axis, value, button, state);
    map<gp2dInt32, GP2DJoyAction*>::iterator it;

    it = m_mapJoystick.find(device);
    if(it != m_mapJoystick.end()) {
        GP2DJoyAction* action = it->second;

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
void GP2DJoystickHandler::setJoystickEnabled(gp2dBool enabled) {
    if(enabled){
        SDL_JoystickEventState(SDL_ENABLE);
    } else {
        SDL_JoystickEventState(SDL_IGNORE);
    }
}

gp2dBool GP2DJoystickHandler::isJoystickEnabled() {
    return (SDL_JoystickEventState(SDL_QUERY) == SDL_ENABLE) ? true : false;
}

void GP2DJoystickHandler::scanJoysticks(){
    m_joystick.clear();
    for(gp2dInt32 i = 0; i <= SDL_NumJoysticks(); i++){
        m_joystick.push_back(SDL_JoystickOpen(i));
    }
    clog << SDL_NumJoysticks() << " joysticks found." << endl;
}

gp2dInt32 GP2DJoystickHandler::getNumJoysticks() {
    return SDL_NumJoysticks();
}


//=============================================================================

GP2DFocusHandler::GP2DFocusHandler() {
}

GP2DFocusHandler::~GP2DFocusHandler() {
}

void GP2DFocusHandler::registerFocusAction(GP2DFocusAction* action) {
    m_actions.insert(action);
}

void GP2DFocusHandler::unregisterFocusAction(GP2DFocusAction* action) {
    m_actions.erase(action);
}

void GP2DFocusHandler::unregisterAll() {
    m_actions.clear();
}

void GP2DFocusHandler::handleEvent(SDL_Event& event) {
    if(event.type == SDL_ACTIVEEVENT) {
        set<GP2DFocusAction*>::iterator it = m_actions.begin();
        while(it != m_actions.end()) {
            GP2DFocusAction* action = *it++;
            if(event.active.gain == 0) {
                action->focusLost();
            } else {
                action->focusGained();
            }
        }
    }
}

//=============================================================================


GP2DInputProcessor::GP2DInputProcessor() {
}

GP2DInputProcessor::~GP2DInputProcessor() {
    m_handlers.clear();
}


void GP2DInputProcessor::addHandler(GP2DInputHandler* handler) {
    m_handlers.insert(handler);
}

void GP2DInputProcessor::pollEvents() {
    while(SDL_PollEvent(&m_event)) {
        set<GP2DInputHandler*>::iterator it;
        // iterate over every registered handler here:
        for (it = m_handlers.begin(); it != m_handlers.end(); it++) {
            if(*it != NULL) { // do null check please.
                // then handle the event using the SDL_Event. The function
                // handleEvent() is actually protected, but since we made
                // GP2DInputHandler a `friend' of this GP2DInputProcessor,
                // we can access that function!
                (*it)->handleEvent(m_event);
            }
        }
    }
}

//==============================================================================

// The GP2DKeyEvent.
GP2DKeyEvent::GP2DKeyEvent(const GP2DKey& key, const GP2DKeyMod& modifier, const gp2dShort unicode) :
        m_key(key),
        m_modifier(modifier),
        m_unicode(unicode) {
}
GP2DKeyEvent::~GP2DKeyEvent() { }

const GP2DKeyEvent::GP2DKey GP2DKeyEvent::getKey() const {
    return m_key;
}

const GP2DKeyEvent::GP2DKeyMod GP2DKeyEvent::getModifier() const {
    return m_modifier;
}

const gp2dUshort GP2DKeyEvent::getUnicode() const {
    return m_unicode;
}



//==============================================================================

GP2DMouseEvent::GP2DMouseEvent(gp2dInt32 x, gp2dInt32 y, GP2DMouseEvent::GP2DMouseButton button) :
    m_x(x),
    m_y(y),
    m_mouseButton(button) {

}

GP2DMouseEvent::~GP2DMouseEvent() {
}

const gp2dInt32 GP2DMouseEvent::getX() const {
    return m_x;
}

const gp2dInt32 GP2DMouseEvent::getY() const {
    return m_y;
}

const gp2dInt32 GP2DMouseEvent::getButton() const {
    return m_mouseButton;
}

//==============================================================================

GP2DJoyEvent::GP2DJoyEvent(gp2dInt32 device, GP2DJoyAxis axis, gp2dInt32 value, gp2dInt32 button, gp2dInt32 state) :
        m_joyDevice(device),
        m_joyButton(button),
        m_joyButtonState(state),
        m_joyAxis(axis),
        m_joyAxisValue(value) {
}

GP2DJoyEvent::~GP2DJoyEvent(){
}

const gp2dInt32 GP2DJoyEvent::getDevice() const {
    return m_joyDevice;
}

const gp2dInt32 GP2DJoyEvent::getButton() const {
    return m_joyButton;
}
const gp2dInt32 GP2DJoyEvent::getButtonState() const {
    return m_joyButtonState;
}
const GP2DJoyEvent::GP2DJoyAxis GP2DJoyEvent::getAxis() const {
    return m_joyAxis;
}

const gp2dInt32 GP2DJoyEvent::getAxisValue() const {
    return m_joyAxisValue;
}

//==============================================================================

/// Basic template implementation of the GP2DKeyAction.
GP2DKeyAction::GP2DKeyAction() { }
GP2DKeyAction::~GP2DKeyAction() { }
void GP2DKeyAction::keyDown(GP2DKeyEvent& event) { }
void GP2DKeyAction::keyUp(GP2DKeyEvent& event) { }


//==============================================================================


/// Basic template implementation of a GP2DMouseAction.
GP2DMouseAction::GP2DMouseAction() { }
GP2DMouseAction::~GP2DMouseAction() { }
void GP2DMouseAction::mouseButtonDown(GP2DMouseEvent& event) { }
void GP2DMouseAction::mouseButtonUp(GP2DMouseEvent& event) { }
void GP2DMouseAction::mouseMoved(GP2DMouseEvent& event) { }
void GP2DMouseAction::mouseDragStart(GP2DMouseEvent& event) { }
void GP2DMouseAction::mouseDragEnd(GP2DMouseEvent& event) { }

//==============================================================================

/// Basic template implementation of the GP2DJoyAction.
GP2DJoyAction::GP2DJoyAction() { }
GP2DJoyAction::~GP2DJoyAction() { }
void GP2DJoyAction::buttonDown(GP2DJoyEvent& event) { }
void GP2DJoyAction::buttonUp(GP2DJoyEvent& event) { }
void GP2DJoyAction::axisChange(GP2DJoyEvent& event) { }

//=============================================================================

GP2DFocusAction::GP2DFocusAction() { }
GP2DFocusAction::~GP2DFocusAction() { }
void GP2DFocusAction::focusGained() { }
void GP2DFocusAction::focusLost() { }


} // namespace gp2d

