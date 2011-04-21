#include "input.h"

using namespace std;

namespace gp2d {


/**
 * Creates the input handler.
 */
GP2DInputHandler::GP2DInputHandler() {
    // initialize the mouse event to NULL. This cannot happen directly in the
    // header file, because ISO C++ forbids that, for whatever obscure reason.
    m_mouseaction = NULL;
    
    m_mouseDragStarted = false;
    m_mousePressed = false;
    
    m_mouseeventsEnabled = true;
    m_globalkeysEnabled = true;
    m_keyMapsEnabled = true;
}

/**
 * Destroys the input handler.
 */
GP2DInputHandler::~GP2DInputHandler() {
    std::map<GP2DKeyEvent::GP2DKey, GP2DKeyAction*>::iterator iter;
    for (iter = m_mapinput.begin(); iter != m_mapinput.end(); ++iter) {
        m_mapinput.erase(iter->first);
        delete iter->second;
    }

    m_mapBasicKeydown.clear();
    m_mapBasicKeyup.clear();
    m_mapBasicMouseDown.clear();
    m_mapBasicMouseUp.clear();
    m_setBasicMouseMove.clear();
    
    delete m_mouseaction;
}

/**
 * Mapped keys enablance.
 */
void GP2DInputHandler::setKeyMapsEnabled(bool a_keyMapsEnabled) {
    m_keyMapsEnabled = a_keyMapsEnabled; 
}

/**
 * Mouse input enabled-ance.
 */
void GP2DInputHandler::setMouseEnabled(bool a_mouseeventsEnabled) {
    m_mouseeventsEnabled = a_mouseeventsEnabled;
}

/**
 * Global keys? Listen for them?
 */
void GP2DInputHandler::setGlobalKeysEnabled(bool a_globalkeysEnabled) {
    m_globalkeysEnabled = a_globalkeysEnabled;
}

/**
 * Registers a basic callback using a pointer to a function.
 */
void GP2DInputHandler::registerKeyUp(GP2DKeyEvent::GP2DKey key, void (*cbf)(void) ) {
    m_mapBasicKeyup[key] = cbf;
}

/**
 * Registers a basic callback using a pointer to a function.
 */
void GP2DInputHandler::registerKeyDown(GP2DKeyEvent::GP2DKey key, void (*cbf)(void) ) {
    m_mapBasicKeydown[key] = cbf;
}

/**
 * Registers a basic callback for a mouse down using a pointer to a function.
 */
void GP2DInputHandler::registerMouseDown(GP2DMouseEvent::GP2DMouseButton button, 
        void (*callbackFunction)(GP2DMouseEvent&)) {
    m_mapBasicMouseDown[button] = callbackFunction;
}

/**
 * Registers a basic callback for a mouse up using a pointer to a function.
 */
void GP2DInputHandler::registerMouseUp(GP2DMouseEvent::GP2DMouseButton button, 
        void (*callbackFunction)(GP2DMouseEvent&)) {
    m_mapBasicMouseUp[button] = callbackFunction;
}

/**
 * Registers a basic callback for a mouse up using a pointer to a function.
 */
void GP2DInputHandler::registerMouseMove(void (*callbackFunction)(GP2DMouseEvent&)) {
    m_setBasicMouseMove.insert(callbackFunction);
    cout << "Reigstered mouse move " << endl;
}


/**
 * Registers a key event.
 */
void GP2DInputHandler::registerKeyAction(GP2DKeyEvent::GP2DKey key, GP2DKeyAction* event) {
    m_mapinput[key] = event;
}

/**
 * Register a global key input callback.
 */
void GP2DInputHandler::registerGlobalKeyAction(GP2DKeyAction* action) {
    m_globalKeyActions.insert(action);
}

/**
 * Register a mouse event.
 */
void GP2DInputHandler::registerMouseAction(GP2DMouseAction* event) {    
    // then assign the new mouse event. But only if it is not null.
    // Use unregisterMouseEvent to delete the point0r.
    if(event != NULL) {
        m_mouseaction = event;
    }
}

/**
 * Remove a key action
 */
void GP2DInputHandler::unregisterKeyAction(GP2DKeyEvent::GP2DKey key) {
    // iterate over the 'OOP' key events
    map<GP2DKeyEvent::GP2DKey, GP2DKeyAction*>::iterator it;
    it = m_mapinput.find(key);
    
    if(it != m_mapinput.end()) {
        GP2DKeyAction* action = it->second;
        m_mapinput.erase(key);
        delete action;
    }
}

/**
 * Unregister mouse action.
 */
void GP2DInputHandler::unregisterMouseAction() {
    delete m_mouseaction;
}

/**
 * Remove the key down.
 */
void GP2DInputHandler::unregisterKeyDown(GP2DKeyEvent::GP2DKey key) {
    m_mapBasicKeydown.erase(key);
}

/**
 * Unregister the key up.
 */
void GP2DInputHandler::unregisterKeyUp(GP2DKeyEvent::GP2DKey key) {
    m_mapBasicKeyup.erase(key);
}

/**
 * Remove the mouse down.
 */
void GP2DInputHandler::unregisterMouseDown(GP2DMouseEvent::GP2DMouseButton button) {
    m_mapBasicMouseDown.erase(button);
}

/**
 * Remove mouse up.
 */
void GP2DInputHandler::unregisterMouseUp(GP2DMouseEvent::GP2DMouseButton button) {
    m_mapBasicMouseUp.erase(button);
}

/**
 * Remove the mouse move.
 */
void GP2DInputHandler::unregisterMouseMove(void (*callbackFunction)(GP2DMouseEvent&)) {
    m_setBasicMouseMove.erase(callbackFunction);
}

/**
 * Enables or disables key repeat. Key repeat is mostly useful in chat functions
 * etc.
 */
void GP2DInputHandler::setKeyRepeat(int initialDelay, int interval) {
    SDL_EnableKeyRepeat(initialDelay, interval);
}

/**
 * Handle function pointer style input events.
 */
void GP2DInputHandler::handleFPKeyInputEvents() {
    SDLKey key_sdl = m_event.key.keysym.sym;
    // SDLMod mod_sdl = m_event.key.keysym.mod;
    // since our map contains GP2DKeys, cast it from SDLKey to GP2DKey.
    GP2DKeyEvent::GP2DKey key = static_cast<GP2DKeyEvent::GP2DKey>(key_sdl);
    
    // TODO: what to do with the mod? Probably put it as a param in the callback?
    // GP2DKeyEvent::GP2DKeyMod mod = static_cast<GP2DKeyEvent::GP2DKeyMod>(mod_sdl);
    
    if(m_keyMapsEnabled) {
        if(m_event.type == SDL_KEYDOWN) {
            map<GP2DKeyEvent::GP2DKey, void(*)(void)>::iterator it_basic;
            it_basic = m_mapBasicKeydown.find(key);
            if(it_basic != m_mapBasicKeydown.end()) {
                void (*callback)(void);
                callback = it_basic->second;
                callback();
            }
        } else if(m_event.type == SDL_KEYUP) {
            map<GP2DKeyEvent::GP2DKey, void(*)(void)>::iterator it_basic;
            it_basic = m_mapBasicKeyup.find(key);
            if(it_basic != m_mapBasicKeyup.end()) {
                void (*callback)(void);
                callback = it_basic->second;
                callback();
            } 
        }
    }
}

/**
 * Handle the OO key input events.
 */
void GP2DInputHandler::handleOOPKeyInputEvents() {
    SDLKey key_sdl = m_event.key.keysym.sym;
    SDLMod mod_sdl = m_event.key.keysym.mod;
    // since our map contains GP2DKeys, cast it from SDLKey to GP2DKey.
    GP2DKeyEvent::GP2DKey key = static_cast<GP2DKeyEvent::GP2DKey>(key_sdl);
    GP2DKeyEvent::GP2DKeyMod mod = static_cast<GP2DKeyEvent::GP2DKeyMod>(mod_sdl);
    
    GP2DKeyEvent event = GP2DKeyEvent(key, mod);
    
    // are mapped key events enabled?
    if(m_keyMapsEnabled) {
        // iterate over the 'OOP' key events
        map<GP2DKeyEvent::GP2DKey, GP2DKeyAction*>::iterator it;
        it = m_mapinput.find(key);
        
        if(it != m_mapinput.end()) {
            GP2DKeyAction* action = it->second;
            
            if(m_event.type == SDL_KEYDOWN) {
                action->keyDown(event);
            } else if(m_event.type == SDL_KEYUP) {
                action->keyUp(event);
            }
        }
    }
    
    // are global keys enabled?
    if(m_globalkeysEnabled) {
        set<GP2DKeyAction*>::iterator it;
        // iterate over every registered global key event here:
        for (it = m_globalKeyActions.begin(); it != m_globalKeyActions.end(); it++) {
            // *it is a GP2DKeyAction*
            if(*it != NULL) {
                if(m_event.type == SDL_KEYDOWN) {
                    (*it)->keyDown(event);
                } else if(m_event.type == SDL_KEYUP) {
                    (*it)->keyUp(event);
                }
            }
        }
    }
}

void GP2DInputHandler::handleFPMouseInputEvents() {
    GP2DMouseEvent::GP2DMouseButton button;
    button = static_cast<GP2DMouseEvent::GP2DMouseButton>(m_event.button.button);
    
    // yes, there is, now issue the callbacks. 
    int x = m_event.motion.x;
    int y = m_event.motion.y;
    
    GP2DMouseEvent event(x, y, button);
    
    if(m_event.type == SDL_MOUSEBUTTONDOWN) {
        map<GP2DMouseEvent::GP2DMouseButton, void(*)(GP2DMouseEvent&)>::iterator it;
        it = m_mapBasicMouseDown.find(button);
        
        if(it != m_mapBasicMouseDown.end()) {
            void (*callbackFunction)(GP2DMouseEvent&);
            callbackFunction = it->second;
            callbackFunction(event);
        }
    } else if(m_event.type == SDL_MOUSEBUTTONUP) {
        map<GP2DMouseEvent::GP2DMouseButton, void(*)(GP2DMouseEvent&)>::iterator it;
        it = m_mapBasicMouseUp.find(button);
        
        if(it != m_mapBasicMouseUp.end()) {
            void (*callbackFunction)(GP2DMouseEvent&);
            callbackFunction = it->second;
            callbackFunction(event);
        }
    } else if (m_event.type == SDL_MOUSEMOTION) {
        set<void(*)(GP2DMouseEvent&)>::iterator it;
        for (it = m_setBasicMouseMove.begin(); it != m_setBasicMouseMove.end(); it++) {
            // *it is a function pointer
            if(*it != NULL) {
                (*it)(event); // call the callback function with a param.
            }
        }
    }
}

void GP2DInputHandler::handleOOPMouseInputEvents() {
    // is there a mouse event assigned to the input handler?
    if(m_mouseaction != NULL) {
        // yes, there is, now issue the callbacks. 
        int x = m_event.motion.x;
        int y = m_event.motion.y;
        
        GP2DMouseEvent::GP2DMouseButton button;
        button = static_cast<GP2DMouseEvent::GP2DMouseButton>(m_event.button.button);
        
        GP2DMouseEvent event(x, y, button);

        if(m_event.type == SDL_MOUSEBUTTONDOWN) {
            m_mousePressed = true;
            m_mouseaction->mouseButtonDown(event);
        } else if(m_event.type == SDL_MOUSEBUTTONUP) {
            m_mousePressed = false;
            if(m_mouseDragStarted) {
                m_mouseaction->mouseDragEnd(event);
                m_mouseDragStarted = false; // reset drag state.
            }
            m_mouseaction->mouseButtonUp(event);
        } else if(m_event.type == SDL_MOUSEMOTION) {
            if(m_mousePressed) {
                m_mouseDragStarted = true; // enable drag state.
                m_mouseaction->mouseDragStart(event);
                m_mousePressed = false;
            }
            m_mouseaction->mouseMoved(event);
        }
    }
}


/**
 * Handles input events.
 */
void GP2DInputHandler::handleInputEvents() {
    if(!m_mouseeventsEnabled && !m_keyMapsEnabled && !m_globalkeysEnabled) {
        // not necessary to check for input events in this handler.
        return;
    }
    
    while(SDL_PollEvent(&m_event)) {
        // simplify some booleans here
        bool isKeyEvent = 
            m_event.type == SDL_KEYDOWN || 
            m_event.type == SDL_KEYUP;
        bool isMouseEvent = 
            m_event.type == SDL_MOUSEBUTTONDOWN || 
            m_event.type == SDL_MOUSEBUTTONUP || 
            m_event.type == SDL_MOUSEMOTION;
                
        // checks if the event was a keyboard event.
        if(isKeyEvent) {
            handleFPKeyInputEvents();
            handleOOPKeyInputEvents();
            
        // Check  for mouse events...
        } else if(isMouseEvent && m_mouseeventsEnabled) {            
            handleFPMouseInputEvents();
            handleOOPMouseInputEvents();
        }
        
    } // end of polling events.
}

//==============================================================================
/// The GP2DKeyEvent.
GP2DKeyEvent::GP2DKeyEvent(const GP2DKey& key, const GP2DKeyMod& modifier) {
    m_key = key;
    m_modifier = modifier;
}
GP2DKeyEvent::~GP2DKeyEvent() { }

const GP2DKeyEvent::GP2DKey GP2DKeyEvent::getKey(void) {
    return m_key;
}

const GP2DKeyEvent::GP2DKeyMod GP2DKeyEvent::getModifier(void) {
    return m_modifier;
}


//==============================================================================

GP2DMouseEvent::GP2DMouseEvent(int x, int y, GP2DMouseEvent::GP2DMouseButton button) {
    m_x = x;
    m_y = y;
    m_mouseButton = button;
}

GP2DMouseEvent::~GP2DMouseEvent() {
}

const int GP2DMouseEvent::getX() {
    return m_x;
}

const int GP2DMouseEvent::getY() {
    return m_y;
}

const int GP2DMouseEvent::getButton() {
    return m_mouseButton;
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

} // namespace gp2d

