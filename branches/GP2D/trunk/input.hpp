#ifndef _GP_INPUT_H_
#define _GP_INPUT_H_

#include <SDL/SDL.h>
#include <SDL/SDL_joystick.h>
#include <map>
#include <set>
#include <vector>
#include <iostream>

#include "core.hpp"
#include "point.hpp"

namespace gp {

/*
 * TODO: I've refactored the classes in this header file. Things to do:
 *   - Removal of handlers (unregistration)
 *   - Removal of actions with the handlers
 *   - Code comments.
 */


/**
 * The GPKeyEvent encapsulates information about a keyboard action which
 * generated an event. This class is mostly useful when global key actions are
 * callbacked, because then you know what key was pressed.
 *
 * @author krpors
 */
class GPKeyEvent {
public:

    /**
     * Keys, which can be referenced by GPKeyEvent::GP_KEY_*
     */
    typedef enum GPKey {
        /* The keyboard syms have been cleverly chosen to map to ASCII */
        GP_KEY_UNKNOWN = 0,
        GP_KEY_FIRST = 0,
        GP_KEY_BACKSPACE = 8,
        GP_KEY_TAB = 9,
        GP_KEY_CLEAR = 12,
        GP_KEY_RETURN = 13,
        GP_KEY_PAUSE = 19,
        GP_KEY_ESCAPE = 27,
        GP_KEY_SPACE = 32,
        GP_KEY_EXCLAIM = 33,
        GP_KEY_QUOTEDBL = 34,
        GP_KEY_HASH = 35,
        GP_KEY_DOLLAR = 36,
        GP_KEY_AMPERSAND = 38,
        GP_KEY_QUOTE = 39,
        GP_KEY_LEFTPAREN = 40,
        GP_KEY_RIGHTPAREN = 41,
        GP_KEY_ASTERISK = 42,
        GP_KEY_PLUS = 43,
        GP_KEY_COMMA = 44,
        GP_KEY_MINUS = 45,
        GP_KEY_PERIOD = 46,
        GP_KEY_SLASH = 47,
        GP_KEY_0 = 48,
        GP_KEY_1 = 49,
        GP_KEY_2 = 50,
        GP_KEY_3 = 51,
        GP_KEY_4 = 52,
        GP_KEY_5 = 53,
        GP_KEY_6 = 54,
        GP_KEY_7 = 55,
        GP_KEY_8 = 56,
        GP_KEY_9 = 57,
        GP_KEY_COLON = 58,
        GP_KEY_SEMICOLON = 59,
        GP_KEY_LESS = 60,
        GP_KEY_EQUALS = 61,
        GP_KEY_GREATER = 62,
        GP_KEY_QUESTION = 63,
        GP_KEY_AT = 64,

        // skip uppercase letters, says SDL.

        GP_KEY_LEFTBRACKET = 91,
        GP_KEY_BACKSLASH = 92,
        GP_KEY_RIGHTBRACKET = 93,
        GP_KEY_CARET = 94,
        GP_KEY_UNDERSCORE = 95,
        GP_KEY_BACKQUOTE = 96,
        GP_KEY_a = 97,
        GP_KEY_b = 98,
        GP_KEY_c = 99,
        GP_KEY_d = 100,
        GP_KEY_e = 101,
        GP_KEY_f = 102,
        GP_KEY_g = 103,
        GP_KEY_h = 104,
        GP_KEY_i = 105,
        GP_KEY_j = 106,
        GP_KEY_k = 107,
        GP_KEY_l = 108,
        GP_KEY_m = 109,
        GP_KEY_n = 110,
        GP_KEY_o = 111,
        GP_KEY_p = 112,
        GP_KEY_q = 113,
        GP_KEY_r = 114,
        GP_KEY_s = 115,
        GP_KEY_t = 116,
        GP_KEY_u = 117,
        GP_KEY_v = 118,
        GP_KEY_w = 119,
        GP_KEY_x = 120,
        GP_KEY_y = 121,
        GP_KEY_z = 122,
        GP_KEY_DELETE = 127,
        /* End of ASCII mapped keysyms */

        /* International keyboard syms */
        GP_KEY_WORLD_0 = 160,      /* 0xA0 */
        GP_KEY_WORLD_1 = 161,
        GP_KEY_WORLD_2 = 162,
        GP_KEY_WORLD_3 = 163,
        GP_KEY_WORLD_4 = 164,
        GP_KEY_WORLD_5 = 165,
        GP_KEY_WORLD_6 = 166,
        GP_KEY_WORLD_7 = 167,
        GP_KEY_WORLD_8 = 168,
        GP_KEY_WORLD_9 = 169,
        GP_KEY_WORLD_10 = 170,
        GP_KEY_WORLD_11 = 171,
        GP_KEY_WORLD_12 = 172,
        GP_KEY_WORLD_13 = 173,
        GP_KEY_WORLD_14 = 174,
        GP_KEY_WORLD_15 = 175,
        GP_KEY_WORLD_16 = 176,
        GP_KEY_WORLD_17 = 177,
        GP_KEY_WORLD_18 = 178,
        GP_KEY_WORLD_19 = 179,
        GP_KEY_WORLD_20 = 180,
        GP_KEY_WORLD_21 = 181,
        GP_KEY_WORLD_22 = 182,
        GP_KEY_WORLD_23 = 183,
        GP_KEY_WORLD_24 = 184,
        GP_KEY_WORLD_25 = 185,
        GP_KEY_WORLD_26 = 186,
        GP_KEY_WORLD_27 = 187,
        GP_KEY_WORLD_28 = 188,
        GP_KEY_WORLD_29 = 189,
        GP_KEY_WORLD_30 = 190,
        GP_KEY_WORLD_31 = 191,
        GP_KEY_WORLD_32 = 192,
        GP_KEY_WORLD_33 = 193,
        GP_KEY_WORLD_34 = 194,
        GP_KEY_WORLD_35 = 195,
        GP_KEY_WORLD_36 = 196,
        GP_KEY_WORLD_37 = 197,
        GP_KEY_WORLD_38 = 198,
        GP_KEY_WORLD_39 = 199,
        GP_KEY_WORLD_40 = 200,
        GP_KEY_WORLD_41 = 201,
        GP_KEY_WORLD_42 = 202,
        GP_KEY_WORLD_43 = 203,
        GP_KEY_WORLD_44 = 204,
        GP_KEY_WORLD_45 = 205,
        GP_KEY_WORLD_46 = 206,
        GP_KEY_WORLD_47 = 207,
        GP_KEY_WORLD_48 = 208,
        GP_KEY_WORLD_49 = 209,
        GP_KEY_WORLD_50 = 210,
        GP_KEY_WORLD_51 = 211,
        GP_KEY_WORLD_52 = 212,
        GP_KEY_WORLD_53 = 213,
        GP_KEY_WORLD_54 = 214,
        GP_KEY_WORLD_55 = 215,
        GP_KEY_WORLD_56 = 216,
        GP_KEY_WORLD_57 = 217,
        GP_KEY_WORLD_58 = 218,
        GP_KEY_WORLD_59 = 219,
        GP_KEY_WORLD_60 = 220,
        GP_KEY_WORLD_61 = 221,
        GP_KEY_WORLD_62 = 222,
        GP_KEY_WORLD_63 = 223,
        GP_KEY_WORLD_64 = 224,
        GP_KEY_WORLD_65 = 225,
        GP_KEY_WORLD_66 = 226,
        GP_KEY_WORLD_67 = 227,
        GP_KEY_WORLD_68 = 228,
        GP_KEY_WORLD_69 = 229,
        GP_KEY_WORLD_70 = 230,
        GP_KEY_WORLD_71 = 231,
        GP_KEY_WORLD_72 = 232,
        GP_KEY_WORLD_73 = 233,
        GP_KEY_WORLD_74 = 234,
        GP_KEY_WORLD_75 = 235,
        GP_KEY_WORLD_76 = 236,
        GP_KEY_WORLD_77 = 237,
        GP_KEY_WORLD_78 = 238,
        GP_KEY_WORLD_79 = 239,
        GP_KEY_WORLD_80 = 240,
        GP_KEY_WORLD_81 = 241,
        GP_KEY_WORLD_82 = 242,
        GP_KEY_WORLD_83 = 243,
        GP_KEY_WORLD_84 = 244,
        GP_KEY_WORLD_85 = 245,
        GP_KEY_WORLD_86 = 246,
        GP_KEY_WORLD_87 = 247,
        GP_KEY_WORLD_88 = 248,
        GP_KEY_WORLD_89 = 249,
        GP_KEY_WORLD_90 = 250,
        GP_KEY_WORLD_91 = 251,
        GP_KEY_WORLD_92 = 252,
        GP_KEY_WORLD_93 = 253,
        GP_KEY_WORLD_94 = 254,
        GP_KEY_WORLD_95 = 255,      /* 0xFF */

        /* Numeric keypad */
        GP_KEY_KP0 = 256,
        GP_KEY_KP1 = 257,
        GP_KEY_KP2 = 258,
        GP_KEY_KP3 = 259,
        GP_KEY_KP4 = 260,
        GP_KEY_KP5 = 261,
        GP_KEY_KP6 = 262,
        GP_KEY_KP7 = 263,
        GP_KEY_KP8 = 264,
        GP_KEY_KP9 = 265,
        GP_KEY_KP_PERIOD = 266,
        GP_KEY_KP_DIVIDE = 267,
        GP_KEY_KP_MULTIPLY = 268,
        GP_KEY_KP_MINUS = 269,
        GP_KEY_KP_PLUS = 270,
        GP_KEY_KP_ENTER = 271,
        GP_KEY_KP_EQUALS = 272,

        /* Arrows + Home/End pad */
        GP_KEY_UP = 273,
        GP_KEY_DOWN = 274,
        GP_KEY_RIGHT = 275,
        GP_KEY_LEFT = 276,
        GP_KEY_INSERT = 277,
        GP_KEY_HOME = 278,
        GP_KEY_END = 279,
        GP_KEY_PAGEUP = 280,
        GP_KEY_PAGEDOWN = 281,

        /* Function keys */
        GP_KEY_F1 = 282,
        GP_KEY_F2 = 283,
        GP_KEY_F3 = 284,
        GP_KEY_F4 = 285,
        GP_KEY_F5 = 286,
        GP_KEY_F6 = 287,
        GP_KEY_F7 = 288,
        GP_KEY_F8 = 289,
        GP_KEY_F9 = 290,
        GP_KEY_F10 = 291,
        GP_KEY_F11 = 292,
        GP_KEY_F12 = 293,
        GP_KEY_F13 = 294,
        GP_KEY_F14 = 295,
        GP_KEY_F15 = 296,

        /* Key state modifier keys */
        GP_KEY_NUMLOCK = 300,
        GP_KEY_CAPSLOCK = 301,
        GP_KEY_SCROLLOCK = 302,
        GP_KEY_RSHIFT = 303,
        GP_KEY_LSHIFT = 304,
        GP_KEY_RCTRL = 305,
        GP_KEY_LCTRL = 306,
        GP_KEY_RALT = 307,
        GP_KEY_LALT = 308,
        GP_KEY_RMETA = 309,
        GP_KEY_LMETA = 310,
        GP_KEY_LSUPER = 311,      /* Left "Windows" key */
        GP_KEY_RSUPER = 312,      /* Right "Windows" key */
        GP_KEY_MODE = 313,      /* "Alt Gr" key */
        GP_KEY_COMPOSE = 314,      /* Multi-key compose key */

        /* Miscellaneous function keys */
        GP_KEY_HELP = 315,
        GP_KEY_PRINT = 316,
        GP_KEY_SYSREQ = 317,
        GP_KEY_BREAK = 318,
        GP_KEY_MENU = 319,
        GP_KEY_POWER = 320,      /* Power Macintosh power key */
        GP_KEY_EURO = 321,      /* Some european keyboards */
        GP_KEY_UNDO = 322,      /* Atari keyboard has Undo */

        /* Add any other keys here */

        GP_KEY_LAST
    } GPKey;

    /**
     * Modifiers belong to a key event. That's why they are put in the class.
     * It can be used by doing GPKeyEvent::GP_KEY_MOD_*.
     */
    enum GPKeyMod {
        GP_KEY_MOD_NONE  = 0x0000,
        GP_KEY_MOD_LSHIFT= 0x0001,
        GP_KEY_MOD_RSHIFT= 0x0002,
        GP_KEY_MOD_LCTRL = 0x0040,
        GP_KEY_MOD_RCTRL = 0x0080,
        GP_KEY_MOD_LALT  = 0x0100,
        GP_KEY_MOD_RALT  = 0x0200,
        GP_KEY_MOD_LMETA = 0x0400,
        GP_KEY_MOD_RMETA = 0x0800,
        GP_KEY_MOD_NUM   = 0x1000,
        GP_KEY_MOD_CAPS  = 0x2000,
        GP_KEY_MOD_MODE  = 0x4000,
        GP_KEY_MOD_RESERVED = 0x8000
    };


    /**
     * Creates a GPKeyEvent object.
     *
     * @param key The GPKey which generated the event.
     * @param modifer a possible modifier (like CTRL or ALT etc.)
     */
    GPKeyEvent(const GPKey& key, const GPKeyMod& modifier, const gpShort unicode);

    /**
     * Destructor for the GPKeyEvent. Currently does not much.
     */
    ~GPKeyEvent();

    /**
     * Gets the key which was pressed.
     *
     * @return The GPKey which was pressurized.
     */
    const GPKeyEvent::GPKey getKey() const;

    /**
     * Gets the modifier which was used.
     *
     * @return One of the GPKeyMod enum.
     */
    const GPKeyEvent::GPKeyMod getModifier() const;

    /**
     * Gets the unicode key.
     *
     * @return The unicode key as a unsigned short.
     */
    const gpUshort getUnicode() const;

private:
    /// The key which generated the event.
    GPKey m_key;

    /// A keyboard modifier (one of the GPKeyMod enumeration).
    GPKeyMod m_modifier;

    /// The unicode key. If SDL_EnableUNICODE(1) is set, this will be usable...
    gpUshort m_unicode;
};

//=============================================================================

/**
 * The GPMouseEvent is a class encapsulating information about a generated mouse
 * event, such as where (x,y) and the button pressed.
 *
 * @author krpors
 */
class GPMouseEvent {
private:
    ///  The x position on the screen where the event occurred.
    gpInt32 m_x;

    /// The y position on the screen where the event occurred.
    gpInt32 m_y;

    /// The mouse button which was pressed.
    gpInt32 m_mouseButton;

public:
    // defining some constants. Why in this class? Thats OOP. Encapsulation,
    // and keeping the values where they are supposed to be, to prevent overhead.
    enum GPMouseButton {
        GP_BUTTON_LEFT = SDL_BUTTON_LEFT,
        GP_BUTTON_RIGHT = SDL_BUTTON_RIGHT,
        GP_BUTTON_MIDDLE = SDL_BUTTON_MIDDLE,
        GP_BUTTON_WHEELUP = SDL_BUTTON_WHEELUP,
        GP_BUTTON_WHEELDOWN = SDL_BUTTON_WHEELDOWN
    };

    /**
     * Creates a GPMouseEvent;
     */
    GPMouseEvent(gpInt32 x, gpInt32 y, GPMouseButton mouseButton);

    /**
     * Deletes the GPMouseEvent.
     */
    ~GPMouseEvent();

    /**
     * Gets the x position of the event.
     *
     * @return the x pos on the window.
     */
    const gpInt32 getX() const;

    /**
     * Gets the y position of th event.
     *
     * @return the y pos on the window.
     */
    const gpInt32 getY() const;

    /**
     * Gets the button which generated the event.
     *
     * @return The button.
     */
    const gpInt32 getButton() const;
};

//=============================================================================

/**
 * The GPJoyEvent encapsulates information about an event generated
 * by a joystick action.
 *
 * @author DARKGuy
 */
class GPJoyEvent {
public:
    /// Enumeration for the axis directions.
    enum GPJoyAxis {
        GP_AXIS_HORIZONTAL,
        GP_AXIS_VERTICAL
    };

private:
    /// The joystick device.
    gpInt32 m_joyDevice;

    /// The joystick button being pressed.
    gpInt32 m_joyButton;

    ///  The state of the button.
    gpInt32 m_joyButtonState;

    /// The axis being used.
    GPJoyAxis m_joyAxis;

    /// The joystick axis value.
    gpInt32 m_joyAxisValue;

public:
    /**
     * Ctor for a GPJoyEvent.
     *
     * @param device The device.
     * @param axis The axis direction?
     * @param value The axis value.
     * @param button The button being pressurized.
     * @param state State of the button being pressed.
     */
    GPJoyEvent(gpInt32 device, GPJoyAxis axis, gpInt32 value, gpInt32 button, gpInt32 state);

    /**
     * Destructor.
     */
    ~GPJoyEvent();

    /**
     * Gets the device.
     *
     * @return The device which initiated the event.
     */
    const gpInt32 getDevice() const;

    /**
     * Gets the button which was pressed.
     *
     * @return The pressed button.
     */
    const gpInt32 getButton() const;

    /**
     * Gets the state of the button.
     *
     * @return The button.
     */
    const gpInt32 getButtonState() const;

    /**
     * Gets the axis.
     *
     * @return The axis ... direction?
     */
    const GPJoyAxis getAxis() const;

    /**
     * Gets the value the joystick is pulled towards the axis i dunno.
     *
     * @return Axis value.
     */
    const gpInt32 getAxisValue() const;

};

//=============================================================================


/**
 * The GPJoyAction class is a simple interface to how a joystick action can be
 * modelled. This class basically contains callback methods.
 *
 * You must simply extend this class, and write your own implementations for the
 * buttonUp(), buttonDown() and axisChange() functions.
 *
 * @author DARKGuy, krpors
 */
class GPJoyAction {
public:
    /**
     * Constructor for the GPKeyAction.
     */
    GPJoyAction();

    /**
     * Virtual destructor.
     */
    virtual ~GPJoyAction();

    /**
     * Callback method when a button is held down.
     *
     * @param event The generated event.
     */
    virtual void buttonDown(GPJoyEvent& joyEvent);

    /**
     * Callback method when a button is released.
     *
     * @param event The generated event.
     */
    virtual void buttonUp(GPJoyEvent& joyEvent);

    /**
     * Callback method when an axis change is happening.
     *
     * @param event The generated event.
     */
    virtual void axisChange(GPJoyEvent& joyEvent);

};

/**
 * The GPKeyAction class is a simple interface to how a key action can be
 * modelled. It basically has two methods which are usable: keyDown(GPKeyEvent&)
 * and keyUp(GPKeyEvent&). These are callback methods actually. This class sort
 * of behaves like the "Template Method" and "Command" design patterns.
 *
 * You must simply extend this class, and write your own implementations for the
 * keyDown and keyUp functions.
 *
 * @author krpors
 */
class GPKeyAction {
public:
    /**
     * Constructor for the GPKeyAction.
     */
    GPKeyAction();

    /**
     * Virtual destructor. If not declared as virtual, the compiler will
     * generate warnings. I'm not sure why though.
     */
    virtual ~GPKeyAction();

    /**
     * Callback method when a key is held down.
     *
     * @param event The generated SDL_Event.
     */
    virtual void keyDown(GPKeyEvent& keyEvent);

    /**
     * Callback method when a key is released.
     *
     * @param event The generated SDL_Event.
     */
    virtual void keyUp(GPKeyEvent& keyEvent);
};


/**
 * A GPMouseAction can only be registered once, since we only have one mouse to
 * press buttons on. This class simply supports callback operations for the
 * GPInputHandler: when it comes across a mouse event, it will issue the proper
 * callback from this class.
 *
 * @author krpors
 */
class GPMouseAction {
public:
    /**
     * Constructor.
     */
    GPMouseAction();

    /**
     * Virtual destructor.
     */
    virtual ~GPMouseAction();

    /**
     * When the mouse is simply moved, this callback method will be called.
     *
     * @param event The mouse event which was generated.
     */
    virtual void mouseMoved(GPMouseEvent& event);

    /**
     * When the mouse button is pressed, this callback method is called.
     *
     * @param event The mouse event which was generated.
     */
    virtual void mouseButtonDown(GPMouseEvent& event);

    /**
     * When the mouse button is released from pressure, this callback method is
     * called. This ALWAYS happens after mouseButtonDown(gpInt32,gpInt32,gpInt32).
     *
     * @param event The mouse event which was generated.
     */
    virtual void mouseButtonUp(GPMouseEvent& event);

    /**
     * When the mouse is clicked somewhere, held pressed, and moved somewhere
     * else on the screen (i.e. dragged), invoke this callback method.
     *
     * @param x The x position on the screen of the where the drag took place.
     * @param y The y position on the screen of the where the drag took place.
     * @param mouseButton One of: GP_BUTTON_LEFT, GP_BUTTON_RIGHT,
     *  GP_BUTTON_MIDDLE, all defined in this header file.
     */
    virtual void mouseDragStart(GPMouseEvent& event);

    /**
     * When the mouse is clicked somewhere, held pressed, and moved somewhere
     * else on the screen (i.e. dragged), and _released_, invoke this callback.
     *
     * @param x The x position on the screen of the where the drag ended.
     * @param y The y position on the screen of the where the drag ended.
     * @param mouseButton One of: GP_BUTTON_LEFT, GP_BUTTON_RIGHT,
     *  GP_BUTTON_MIDDLE, all defined in this header file.
     */
    virtual void mouseDragEnd(GPMouseEvent& event);
};

//=============================================================================

class GPFocusAction {
public:
    GPFocusAction();
    virtual ~GPFocusAction();

    virtual void focusGained();
    virtual void focusLost();
};

//=============================================================================

/**
 * The GPInputHandler is the base class for handling input events generated
 * by SDL. The class exposes one virtual function, handleEvent(SDL_Event&),
 * which is invoked by the GPInputProcessor to handle the dispatched event
 * by SDL. For instance, the default GPInputHandler implementations:
 * <ul>
 *   <li>GPKeyboardHandler</li>
 *   <li>GPMouseHandler</li>
 *   <li>GPJoystickHandler</li>
 *   <li>GPFocusHandler</li>
 * </ul>
 *
 * all implement the handleEvent(SDL_Event&) function, and handle only the
 * event which is needed at that time (keyboard, mouse or joystick events).
 *
 * @author krpors
 */
class GPInputHandler {
private:

    /// Boolean indicating whether this input handler should listen
    /// for events.
    gpBool m_enabled;

protected:

    /**
     * Pure virtual function, to handle an event dispatched by the
     * GPInputProcessor. Only that class can access this function because
     * it has been declared as a `friend' of GPInputHandler.
     */
    virtual void handleEvent(SDL_Event& event) = 0;

    /// Let the input processor have the ability to access protected functions.
    friend class GPInputProcessor;

public:

    /**
     * Constructor.
     */
    GPInputHandler();

    /**
     * Destructor.
     */
    virtual ~GPInputHandler();

    /**
     * Returns whether this input handler is enabled or not. Dependent on whether
     * it's true of false, the input handler will handle events or not.
     */
    gpBool isEnabled() const;

    /**
     * Sets this input handler as enabled(true) or not(false).
     *
     * @param enabled When true, enable event handling. If false, disables event
     *   handling.
     */
    void setEnabled(gpBool enabled);
};

//=============================================================================

/**
 * The GPKeyboardHandler is a default implementation of keyboard event
 * handling using callbacks with help of the GPKeyAction class.
 *
 * @author krpors
 */
class GPKeyboardHandler : public GPInputHandler {
private:
    /// The map with the Key:Action mapping.
    std::map<GPKeyEvent::GPKey, GPKeyAction*> m_input;

    /// The map for the global key actions.
    std::set<GPKeyAction*> m_globalKeyActions;

protected:

    /**
     * Handles the given SDL_Event, and filters it to handle key events
     * only.
     *
     * @param event The SDL_Event to handle.
     */
    void handleEvent(SDL_Event& event);

public:

    /**
     * Creates the keyboard handler.
     */
    GPKeyboardHandler();

    /**
     * Destroys the keyboard handler.
     */
    ~GPKeyboardHandler();

    /**
     * Registers a key event. This actually adds an entry to the map, where the
     * key paramater is also the key in the map, and the event parameter is the
     * GPKeyAction* value mapped to the key.
     *
     * @param key The actual SDLKey which is a key for the map.
     * @param event The GPKeyAction pointer for callbacking.
     */
    void registerKeyAction(GPKeyEvent::GPKey key, GPKeyAction* action);

    /**
     * Registers a generic key action, meaning the callback will happen on any
     * keypress.
     *
     * @param action The key action used for callbacks.
     */
    void registerGenericKeyAction(GPKeyAction* action);

    /**
     * Unregisters a key event by removing the specified key from the map.
     *
     * @param key The key to have its mapping removed.
     */
    void unregisterKeyAction(GPKeyEvent::GPKey key);

    /**
     * Unregisters a generic key action.
     *
     * @param action the action to remove from the map.
     */
    void unregisterGenericKeyAction(GPKeyAction* action);

    /**
     * Sets a key repeat to a specific initial delay, and a delay(interval)
     * after the initial delay. These are measured in milliseconds. Set to 0 if
     * you want to disable it.
     *
     * @param initialDelay The initial delay when repeats are going to be done,
     *   in milliseconds.
     * @param delay The amount of milliseconds a key is repeated.
     */
    static void setKeyRepeat(gpInt32 initialDelay, gpInt32 delay);
};

//=============================================================================

/**
 * The GPMouseHandler is a default implementation to mouse event handling using
 * callbacks with the GPMouseEvent class.
 *
 * @author krpors
 */
class GPMouseHandler : public GPInputHandler {
private:
    /// Set with mapped mouse actions.
    std::set<GPMouseAction*> m_actions;

    /**
     * When a mouse button is pressed, this gpBool is set to true. This way, a
     * 'drag' event can be callbacked. When the mouse is released, this will be
     * set to false.
     */
    gpBool m_mousePressed;

    /**
     * When a mouse drag is started, this will be set to true. When the mouse
     * button is released after dragging, this makes sure the keyUp event will
     * also generate a callback to mouseDragEnd().
     */
    gpBool m_mouseDragStarted;

protected:

    /**
     * Handles the given SDL_Event, and filters it to handle mouse events
     * only.
     *
     * @param event The SDL_Event to handle.
     */
    void handleEvent(SDL_Event& event);

public:
    /**
     * Constructor.
     */
    GPMouseHandler();

    /**
     * Destructor.
     */
    ~GPMouseHandler();

    /**
     * Registers a mouse action.
     *
     * @param action The GPMouseAction object for callbacks.
     */
    void registerMouseAction(GPMouseAction* action);

    /**
     * Unregisters a mouse action.
     *
     * @param action The action to unregister.
     */
    void unregisterMouseAction(GPMouseAction* action);

    /**
     * Unregisters all mouse actions, no callbacks will be registered
     * after this call.
     */
    void unregisterAll();

    /**
     * Gets the mouse position without using an event.
     *
     * @return A GPPoint instance where the mouse pointer is.
     */
    static const GPPoint getMousePosition();
};

//=============================================================================

/**
 * The GPJoystickHandler is a default implementation to joystick event handling
 * using callbacks with the GPJoystickEvent class.
 *
 * @author DARKGuy
 */
class GPJoystickHandler : public GPInputHandler {
private:
    /// Map with the mapped joystick to joystick actions.
    std::map<gpInt32, GPJoyAction*> m_mapJoystick;

    /// Vector with the joysticks.
    std::vector<SDL_Joystick*> m_joystick;
protected:

    /**
     * Handles the given SDL_Event, and filters it to handle joystick events
     * only.
     *
     * @param event The SDL_Event to handle.
     */
    void handleEvent(SDL_Event& event);
public:

    /**
     * Constructor.
     */
    GPJoystickHandler();

    /**
     * Destructor.
     */
    ~GPJoystickHandler();


    /**
     * Gets the amount of joysticks which have been scanned by scanJoysticks();
     *
     * @return The amount of joystix.
     */
    gpInt32 getNumJoysticks();

    /**
     * Registers a joystick callback action.
     *
     * @param action The joystick action to register.
     */
    void registerJoyAction(gpInt32 device, GPJoyAction* action);

    /**
     * Unregister the specified joystick action.
     *
     * @param device The device to remove the joystick action from.
     */
    void unregisterJoyAction(gpInt32 device);

    /**
     * Unregisters all joystick action callbacks.
     */
    void unregisterAll();

    /**
     * Scans for joystick and stuff. No idea.
     */
    void scanJoysticks();

    /**
     * This static function sets the joystick globally enabled or not.
     * That means invoking some SDL functions to set whether to receive
     * or ignore generated joystick events.
     *
     * @enabled When true, the joystick event state will be set to enabled.
     * If false, joystick event state will be ignored.
     */
    static void setJoystickEnabled(gpBool enabled);

    /**
     * Checks whether the joystick is enabled or not.
     *
     * @return true when enabled, or false if not (meaning events will be
     * ignored).
     */
    static gpBool isJoystickEnabled();



};

//=============================================================================

class GPFocusHandler : public GPInputHandler {
private:
    std::set<GPFocusAction*> m_actions;

public:
    GPFocusHandler();
    ~GPFocusHandler();

    void handleEvent(SDL_Event& event);
    void unregisterAll();
    void registerFocusAction(GPFocusAction* action);
    void unregisterFocusAction(GPFocusAction* action);
};

//=============================================================================

/**
 * The GPInputProcessor is a very simple class. The purpose of it, is poll SDL
 * for incoming events (key, mouse, joystick, etc.) and then dispatch that event
 * to every handler supplied.
 *
 * @author krpors
 */
class GPInputProcessor {
private:

    /// Set with all the added handlers.
    std::set<GPInputHandler*> m_handlers;

    /// The SDL_Event which is used with SDL_PollEvents.
    SDL_Event m_event;

public:

    /**
     * Creates the input processor.
     */
    GPInputProcessor();

    /**
     * Destroys the input processor instance.
     */
    ~GPInputProcessor();

    /**
     * Adds an input handler to the set of handlers.
     *
     * @param handler The GPInputHandler pointer.
     */
    void addHandler(GPInputHandler* handler);

    /**
     * Removes the specific handler from the set of handlers.
     *
     * @param handler the handler to remove.
     */
    void removeHandler(GPInputHandler* handler);

    /**
     * Polls for an events, dispatched by SDL. For every incoming
     * event, the specified handlers are invoked. Those handlers
     * will determine whether the SDL_Event given should be handled
     * or not.
     */
    void pollEvents();
};




} // namespace gp


#endif /*INPUT_H_*/
