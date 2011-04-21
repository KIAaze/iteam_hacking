#ifndef _GP2D_INPUT_H_
#define _GP2D_INPUT_H_

#include <SDL/SDL.h>
#include <SDL/SDL_joystick.h>
#include <map>
#include <set>
#include <vector>
#include <iostream>

#include "core.h"
#include "graphics.h"

namespace gp2d {

/*
 * TODO: I've refactored the classes in this header file. Things to do:
 *   - Removal of handlers (unregistration)
 *   - Removal of actions with the handlers
 *   - Code comments.
 */


/**
 * The GP2DKeyEvent encapsulates information about a keyboard action which
 * generated an event. This class is mostly useful when global key actions are
 * callbacked, because then you know what key was pressed.
 *
 * @author krpors
 */
class GP2DKeyEvent {
public:

    /**
     * Keys, which can be referenced by GP2DKeyEvent::GP2D_KEY_*
     */
    typedef enum GP2DKey {
        /* The keyboard syms have been cleverly chosen to map to ASCII */
        GP2D_KEY_UNKNOWN = 0,
        GP2D_KEY_FIRST = 0,
        GP2D_KEY_BACKSPACE = 8,
        GP2D_KEY_TAB = 9,
        GP2D_KEY_CLEAR = 12,
        GP2D_KEY_RETURN = 13,
        GP2D_KEY_PAUSE = 19,
        GP2D_KEY_ESCAPE = 27,
        GP2D_KEY_SPACE = 32,
        GP2D_KEY_EXCLAIM = 33,
        GP2D_KEY_QUOTEDBL = 34,
        GP2D_KEY_HASH = 35,
        GP2D_KEY_DOLLAR = 36,
        GP2D_KEY_AMPERSAND = 38,
        GP2D_KEY_QUOTE = 39,
        GP2D_KEY_LEFTPAREN = 40,
        GP2D_KEY_RIGHTPAREN = 41,
        GP2D_KEY_ASTERISK = 42,
        GP2D_KEY_PLUS = 43,
        GP2D_KEY_COMMA = 44,
        GP2D_KEY_MINUS = 45,
        GP2D_KEY_PERIOD = 46,
        GP2D_KEY_SLASH = 47,
        GP2D_KEY_0 = 48,
        GP2D_KEY_1 = 49,
        GP2D_KEY_2 = 50,
        GP2D_KEY_3 = 51,
        GP2D_KEY_4 = 52,
        GP2D_KEY_5 = 53,
        GP2D_KEY_6 = 54,
        GP2D_KEY_7 = 55,
        GP2D_KEY_8 = 56,
        GP2D_KEY_9 = 57,
        GP2D_KEY_COLON = 58,
        GP2D_KEY_SEMICOLON = 59,
        GP2D_KEY_LESS = 60,
        GP2D_KEY_EQUALS = 61,
        GP2D_KEY_GREATER = 62,
        GP2D_KEY_QUESTION = 63,
        GP2D_KEY_AT = 64,

        // skip uppercase letters, says SDL.

        GP2D_KEY_LEFTBRACKET = 91,
        GP2D_KEY_BACKSLASH = 92,
        GP2D_KEY_RIGHTBRACKET = 93,
        GP2D_KEY_CARET = 94,
        GP2D_KEY_UNDERSCORE = 95,
        GP2D_KEY_BACKQUOTE = 96,
        GP2D_KEY_a = 97,
        GP2D_KEY_b = 98,
        GP2D_KEY_c = 99,
        GP2D_KEY_d = 100,
        GP2D_KEY_e = 101,
        GP2D_KEY_f = 102,
        GP2D_KEY_g = 103,
        GP2D_KEY_h = 104,
        GP2D_KEY_i = 105,
        GP2D_KEY_j = 106,
        GP2D_KEY_k = 107,
        GP2D_KEY_l = 108,
        GP2D_KEY_m = 109,
        GP2D_KEY_n = 110,
        GP2D_KEY_o = 111,
        GP2D_KEY_p = 112,
        GP2D_KEY_q = 113,
        GP2D_KEY_r = 114,
        GP2D_KEY_s = 115,
        GP2D_KEY_t = 116,
        GP2D_KEY_u = 117,
        GP2D_KEY_v = 118,
        GP2D_KEY_w = 119,
        GP2D_KEY_x = 120,
        GP2D_KEY_y = 121,
        GP2D_KEY_z = 122,
        GP2D_KEY_DELETE = 127,
        /* End of ASCII mapped keysyms */

        /* International keyboard syms */
        GP2D_KEY_WORLD_0 = 160,      /* 0xA0 */
        GP2D_KEY_WORLD_1 = 161,
        GP2D_KEY_WORLD_2 = 162,
        GP2D_KEY_WORLD_3 = 163,
        GP2D_KEY_WORLD_4 = 164,
        GP2D_KEY_WORLD_5 = 165,
        GP2D_KEY_WORLD_6 = 166,
        GP2D_KEY_WORLD_7 = 167,
        GP2D_KEY_WORLD_8 = 168,
        GP2D_KEY_WORLD_9 = 169,
        GP2D_KEY_WORLD_10 = 170,
        GP2D_KEY_WORLD_11 = 171,
        GP2D_KEY_WORLD_12 = 172,
        GP2D_KEY_WORLD_13 = 173,
        GP2D_KEY_WORLD_14 = 174,
        GP2D_KEY_WORLD_15 = 175,
        GP2D_KEY_WORLD_16 = 176,
        GP2D_KEY_WORLD_17 = 177,
        GP2D_KEY_WORLD_18 = 178,
        GP2D_KEY_WORLD_19 = 179,
        GP2D_KEY_WORLD_20 = 180,
        GP2D_KEY_WORLD_21 = 181,
        GP2D_KEY_WORLD_22 = 182,
        GP2D_KEY_WORLD_23 = 183,
        GP2D_KEY_WORLD_24 = 184,
        GP2D_KEY_WORLD_25 = 185,
        GP2D_KEY_WORLD_26 = 186,
        GP2D_KEY_WORLD_27 = 187,
        GP2D_KEY_WORLD_28 = 188,
        GP2D_KEY_WORLD_29 = 189,
        GP2D_KEY_WORLD_30 = 190,
        GP2D_KEY_WORLD_31 = 191,
        GP2D_KEY_WORLD_32 = 192,
        GP2D_KEY_WORLD_33 = 193,
        GP2D_KEY_WORLD_34 = 194,
        GP2D_KEY_WORLD_35 = 195,
        GP2D_KEY_WORLD_36 = 196,
        GP2D_KEY_WORLD_37 = 197,
        GP2D_KEY_WORLD_38 = 198,
        GP2D_KEY_WORLD_39 = 199,
        GP2D_KEY_WORLD_40 = 200,
        GP2D_KEY_WORLD_41 = 201,
        GP2D_KEY_WORLD_42 = 202,
        GP2D_KEY_WORLD_43 = 203,
        GP2D_KEY_WORLD_44 = 204,
        GP2D_KEY_WORLD_45 = 205,
        GP2D_KEY_WORLD_46 = 206,
        GP2D_KEY_WORLD_47 = 207,
        GP2D_KEY_WORLD_48 = 208,
        GP2D_KEY_WORLD_49 = 209,
        GP2D_KEY_WORLD_50 = 210,
        GP2D_KEY_WORLD_51 = 211,
        GP2D_KEY_WORLD_52 = 212,
        GP2D_KEY_WORLD_53 = 213,
        GP2D_KEY_WORLD_54 = 214,
        GP2D_KEY_WORLD_55 = 215,
        GP2D_KEY_WORLD_56 = 216,
        GP2D_KEY_WORLD_57 = 217,
        GP2D_KEY_WORLD_58 = 218,
        GP2D_KEY_WORLD_59 = 219,
        GP2D_KEY_WORLD_60 = 220,
        GP2D_KEY_WORLD_61 = 221,
        GP2D_KEY_WORLD_62 = 222,
        GP2D_KEY_WORLD_63 = 223,
        GP2D_KEY_WORLD_64 = 224,
        GP2D_KEY_WORLD_65 = 225,
        GP2D_KEY_WORLD_66 = 226,
        GP2D_KEY_WORLD_67 = 227,
        GP2D_KEY_WORLD_68 = 228,
        GP2D_KEY_WORLD_69 = 229,
        GP2D_KEY_WORLD_70 = 230,
        GP2D_KEY_WORLD_71 = 231,
        GP2D_KEY_WORLD_72 = 232,
        GP2D_KEY_WORLD_73 = 233,
        GP2D_KEY_WORLD_74 = 234,
        GP2D_KEY_WORLD_75 = 235,
        GP2D_KEY_WORLD_76 = 236,
        GP2D_KEY_WORLD_77 = 237,
        GP2D_KEY_WORLD_78 = 238,
        GP2D_KEY_WORLD_79 = 239,
        GP2D_KEY_WORLD_80 = 240,
        GP2D_KEY_WORLD_81 = 241,
        GP2D_KEY_WORLD_82 = 242,
        GP2D_KEY_WORLD_83 = 243,
        GP2D_KEY_WORLD_84 = 244,
        GP2D_KEY_WORLD_85 = 245,
        GP2D_KEY_WORLD_86 = 246,
        GP2D_KEY_WORLD_87 = 247,
        GP2D_KEY_WORLD_88 = 248,
        GP2D_KEY_WORLD_89 = 249,
        GP2D_KEY_WORLD_90 = 250,
        GP2D_KEY_WORLD_91 = 251,
        GP2D_KEY_WORLD_92 = 252,
        GP2D_KEY_WORLD_93 = 253,
        GP2D_KEY_WORLD_94 = 254,
        GP2D_KEY_WORLD_95 = 255,      /* 0xFF */

        /* Numeric keypad */
        GP2D_KEY_KP0 = 256,
        GP2D_KEY_KP1 = 257,
        GP2D_KEY_KP2 = 258,
        GP2D_KEY_KP3 = 259,
        GP2D_KEY_KP4 = 260,
        GP2D_KEY_KP5 = 261,
        GP2D_KEY_KP6 = 262,
        GP2D_KEY_KP7 = 263,
        GP2D_KEY_KP8 = 264,
        GP2D_KEY_KP9 = 265,
        GP2D_KEY_KP_PERIOD = 266,
        GP2D_KEY_KP_DIVIDE = 267,
        GP2D_KEY_KP_MULTIPLY = 268,
        GP2D_KEY_KP_MINUS = 269,
        GP2D_KEY_KP_PLUS = 270,
        GP2D_KEY_KP_ENTER = 271,
        GP2D_KEY_KP_EQUALS = 272,

        /* Arrows + Home/End pad */
        GP2D_KEY_UP = 273,
        GP2D_KEY_DOWN = 274,
        GP2D_KEY_RIGHT = 275,
        GP2D_KEY_LEFT = 276,
        GP2D_KEY_INSERT = 277,
        GP2D_KEY_HOME = 278,
        GP2D_KEY_END = 279,
        GP2D_KEY_PAGEUP = 280,
        GP2D_KEY_PAGEDOWN = 281,

        /* Function keys */
        GP2D_KEY_F1 = 282,
        GP2D_KEY_F2 = 283,
        GP2D_KEY_F3 = 284,
        GP2D_KEY_F4 = 285,
        GP2D_KEY_F5 = 286,
        GP2D_KEY_F6 = 287,
        GP2D_KEY_F7 = 288,
        GP2D_KEY_F8 = 289,
        GP2D_KEY_F9 = 290,
        GP2D_KEY_F10 = 291,
        GP2D_KEY_F11 = 292,
        GP2D_KEY_F12 = 293,
        GP2D_KEY_F13 = 294,
        GP2D_KEY_F14 = 295,
        GP2D_KEY_F15 = 296,

        /* Key state modifier keys */
        GP2D_KEY_NUMLOCK = 300,
        GP2D_KEY_CAPSLOCK = 301,
        GP2D_KEY_SCROLLOCK = 302,
        GP2D_KEY_RSHIFT = 303,
        GP2D_KEY_LSHIFT = 304,
        GP2D_KEY_RCTRL = 305,
        GP2D_KEY_LCTRL = 306,
        GP2D_KEY_RALT = 307,
        GP2D_KEY_LALT = 308,
        GP2D_KEY_RMETA = 309,
        GP2D_KEY_LMETA = 310,
        GP2D_KEY_LSUPER = 311,      /* Left "Windows" key */
        GP2D_KEY_RSUPER = 312,      /* Right "Windows" key */
        GP2D_KEY_MODE = 313,      /* "Alt Gr" key */
        GP2D_KEY_COMPOSE = 314,      /* Multi-key compose key */

        /* Miscellaneous function keys */
        GP2D_KEY_HELP = 315,
        GP2D_KEY_PRINT = 316,
        GP2D_KEY_SYSREQ = 317,
        GP2D_KEY_BREAK = 318,
        GP2D_KEY_MENU = 319,
        GP2D_KEY_POWER = 320,      /* Power Macintosh power key */
        GP2D_KEY_EURO = 321,      /* Some european keyboards */
        GP2D_KEY_UNDO = 322,      /* Atari keyboard has Undo */

        /* Add any other keys here */

        GP2D_KEY_LAST
    } GP2DKey;

    /**
     * Modifiers belong to a key event. That's why they are put in the class.
     * It can be used by doing GP2DKeyEvent::GP2D_KEY_MOD_*.
     */
    enum GP2DKeyMod {
        GP2D_KEY_MOD_NONE  = 0x0000,
        GP2D_KEY_MOD_LSHIFT= 0x0001,
        GP2D_KEY_MOD_RSHIFT= 0x0002,
        GP2D_KEY_MOD_LCTRL = 0x0040,
        GP2D_KEY_MOD_RCTRL = 0x0080,
        GP2D_KEY_MOD_LALT  = 0x0100,
        GP2D_KEY_MOD_RALT  = 0x0200,
        GP2D_KEY_MOD_LMETA = 0x0400,
        GP2D_KEY_MOD_RMETA = 0x0800,
        GP2D_KEY_MOD_NUM   = 0x1000,
        GP2D_KEY_MOD_CAPS  = 0x2000,
        GP2D_KEY_MOD_MODE  = 0x4000,
        GP2D_KEY_MOD_RESERVED = 0x8000
    };


    /**
     * Creates a GP2DKeyEvent object.
     *
     * @param key The GP2DKey which generated the event.
     * @param modifer a possible modifier (like CTRL or ALT etc.)
     */
    GP2DKeyEvent(const GP2DKey& key, const GP2DKeyMod& modifier, const gp2dShort unicode);

    /**
     * Destructor for the GP2DKeyEvent. Currently does not much.
     */
    ~GP2DKeyEvent();

    /**
     * Gets the key which was pressed.
     *
     * @return The GP2DKey which was pressurized.
     */
    const GP2DKeyEvent::GP2DKey getKey() const;

    /**
     * Gets the modifier which was used.
     *
     * @return One of the GP2DKeyMod enum.
     */
    const GP2DKeyEvent::GP2DKeyMod getModifier() const;

    /**
     * Gets the unicode key.
     *
     * @return The unicode key as a unsigned short.
     */
    const gp2dUshort getUnicode() const;

private:
    /// The key which generated the event.
    GP2DKey m_key;

    /// A keyboard modifier (one of the GP2DKeyMod enumeration).
    GP2DKeyMod m_modifier;

    /// The unicode key. If SDL_EnableUNICODE(1) is set, this will be usable...
    gp2dUshort m_unicode;
};

//=============================================================================

/**
 * The GPMouseEvent is a class encapsulating information about a generated mouse
 * event, such as where (x,y) and the button pressed.
 *
 * @author krpors
 */
class GP2DMouseEvent {
private:
    ///  The x position on the screen where the event occurred.
    gp2dInt32 m_x;

    /// The y position on the screen where the event occurred.
    gp2dInt32 m_y;

    /// The mouse button which was pressed.
    gp2dInt32 m_mouseButton;

public:
    // defining some constants. Why in this class? Thats OOP. Encapsulation,
    // and keeping the values where they are supposed to be, to prevent overhead.
    enum GP2DMouseButton {
        GP2D_BUTTON_LEFT = SDL_BUTTON_LEFT,
        GP2D_BUTTON_RIGHT = SDL_BUTTON_RIGHT,
        GP2D_BUTTON_MIDDLE = SDL_BUTTON_MIDDLE,
        GP2D_BUTTON_WHEELUP = SDL_BUTTON_WHEELUP,
        GP2D_BUTTON_WHEELDOWN = SDL_BUTTON_WHEELDOWN
    };

    /**
     * Creates a GP2DMouseEvent;
     */
    GP2DMouseEvent(gp2dInt32 x, gp2dInt32 y, GP2DMouseButton mouseButton);

    /**
     * Deletes the GP2DMouseEvent.
     */
    ~GP2DMouseEvent();

    /**
     * Gets the x position of the event.
     *
     * @return the x pos on the window.
     */
    const gp2dInt32 getX() const;

    /**
     * Gets the y position of th event.
     *
     * @return the y pos on the window.
     */
    const gp2dInt32 getY() const;

    /**
     * Gets the button which generated the event.
     *
     * @return The button.
     */
    const gp2dInt32 getButton() const;
};

//=============================================================================

/**
 * The GP2DJoyEvent encapsulates information about an event generated
 * by a joystick action.
 *
 * @author DARKGuy
 */
class GP2DJoyEvent {
public:
    /// Enumeration for the axis directions.
    enum GP2DJoyAxis {
        GP2D_AXIS_HORIZONTAL,
        GP2D_AXIS_VERTICAL
    };

private:
    /// The joystick device.
    gp2dInt32 m_joyDevice;

    /// The joystick button being pressed.
    gp2dInt32 m_joyButton;

    ///  The state of the button.
    gp2dInt32 m_joyButtonState;

    /// The axis being used.
    GP2DJoyAxis m_joyAxis;

    /// The joystick axis value.
    gp2dInt32 m_joyAxisValue;

public:
    /**
     * Ctor for a GP2DJoyEvent.
     *
     * @param device The device.
     * @param axis The axis direction?
     * @param value The axis value.
     * @param button The button being pressurized.
     * @param state State of the button being pressed.
     */
    GP2DJoyEvent(gp2dInt32 device, GP2DJoyAxis axis, gp2dInt32 value, gp2dInt32 button, gp2dInt32 state);

    /**
     * Destructor.
     */
    ~GP2DJoyEvent();

    /**
     * Gets the device.
     *
     * @return The device which initiated the event.
     */
    const gp2dInt32 getDevice() const;

    /**
     * Gets the button which was pressed.
     *
     * @return The pressed button.
     */
    const gp2dInt32 getButton() const;

    /**
     * Gets the state of the button.
     *
     * @return The button.
     */
    const gp2dInt32 getButtonState() const;

    /**
     * Gets the axis.
     *
     * @return The axis ... direction?
     */
    const GP2DJoyAxis getAxis() const;

    /**
     * Gets the value the joystick is pulled towards the axis i dunno.
     *
     * @return Axis value.
     */
    const gp2dInt32 getAxisValue() const;

};

//=============================================================================


/**
 * The GP2DJoyAction class is a simple interface to how a joystick action can be
 * modelled. This class basically contains callback methods.
 *
 * You must simply extend this class, and write your own implementations for the
 * buttonUp(), buttonDown() and axisChange() functions.
 *
 * @author DARKGuy, krpors
 */
class GP2DJoyAction {
public:
    /**
     * Constructor for the GP2DKeyAction.
     */
    GP2DJoyAction();

    /**
     * Virtual destructor.
     */
    virtual ~GP2DJoyAction();

    /**
     * Callback method when a button is held down.
     *
     * @param event The generated event.
     */
    virtual void buttonDown(GP2DJoyEvent& joyEvent);

    /**
     * Callback method when a button is released.
     *
     * @param event The generated event.
     */
    virtual void buttonUp(GP2DJoyEvent& joyEvent);

    /**
     * Callback method when an axis change is happening.
     *
     * @param event The generated event.
     */
    virtual void axisChange(GP2DJoyEvent& joyEvent);

};

/**
 * The GP2DKeyAction class is a simple interface to how a key action can be
 * modelled. It basically has two methods which are usable: keyDown(GP2DKeyEvent&)
 * and keyUp(GP2DKeyEvent&). These are callback methods actually. This class sort
 * of behaves like the "Template Method" and "Command" design patterns.
 *
 * You must simply extend this class, and write your own implementations for the
 * keyDown and keyUp functions.
 *
 * @author krpors
 */
class GP2DKeyAction {
public:
    /**
     * Constructor for the GP2DKeyAction.
     */
    GP2DKeyAction();

    /**
     * Virtual destructor. If not declared as virtual, the compiler will
     * generate warnings. I'm not sure why though.
     */
    virtual ~GP2DKeyAction();

    /**
     * Callback method when a key is held down.
     *
     * @param event The generated SDL_Event.
     */
    virtual void keyDown(GP2DKeyEvent& keyEvent);

    /**
     * Callback method when a key is released.
     *
     * @param event The generated SDL_Event.
     */
    virtual void keyUp(GP2DKeyEvent& keyEvent);
};


/**
 * A GPMouseAction can only be registered once, since we only have one mouse to
 * press buttons on. This class simply supports callback operations for the
 * GPInputHandler: when it comes across a mouse event, it will issue the proper
 * callback from this class.
 *
 * @author krpors
 */
class GP2DMouseAction {
public:
    /**
     * Constructor.
     */
    GP2DMouseAction();

    /**
     * Virtual destructor.
     */
    virtual ~GP2DMouseAction();

    /**
     * When the mouse is simply moved, this callback method will be called.
     *
     * @param event The mouse event which was generated.
     */
    virtual void mouseMoved(GP2DMouseEvent& event);

    /**
     * When the mouse button is pressed, this callback method is called.
     *
     * @param event The mouse event which was generated.
     */
    virtual void mouseButtonDown(GP2DMouseEvent& event);

    /**
     * When the mouse button is released from pressure, this callback method is
     * called. This ALWAYS happens after mouseButtonDown(gp2dInt32,gp2dInt32,gp2dInt32).
     *
     * @param event The mouse event which was generated.
     */
    virtual void mouseButtonUp(GP2DMouseEvent& event);

    /**
     * When the mouse is clicked somewhere, held pressed, and moved somewhere
     * else on the screen (i.e. dragged), invoke this callback method.
     *
     * @param x The x position on the screen of the where the drag took place.
     * @param y The y position on the screen of the where the drag took place.
     * @param mouseButton One of: GP_BUTTON_LEFT, GP_BUTTON_RIGHT,
     *  GP_BUTTON_MIDDLE, all defined in this header file.
     */
    virtual void mouseDragStart(GP2DMouseEvent& event);

    /**
     * When the mouse is clicked somewhere, held pressed, and moved somewhere
     * else on the screen (i.e. dragged), and _released_, invoke this callback.
     *
     * @param x The x position on the screen of the where the drag ended.
     * @param y The y position on the screen of the where the drag ended.
     * @param mouseButton One of: GP_BUTTON_LEFT, GP_BUTTON_RIGHT,
     *  GP_BUTTON_MIDDLE, all defined in this header file.
     */
    virtual void mouseDragEnd(GP2DMouseEvent& event);
};

//=============================================================================

class GP2DFocusAction {
public:
    GP2DFocusAction();
    virtual ~GP2DFocusAction();

    virtual void focusGained();
    virtual void focusLost();
};

//=============================================================================

/**
 * The GP2DInputHandler is the base class for handling input events generated
 * by SDL. The class exposes one virtual function, handleEvent(SDL_Event&),
 * which is invoked by the GP2DInputProcessor to handle the dispatched event
 * by SDL. For instance, the default GP2DInputHandler implementations:
 * <ul>
 *   <li>GP2DKeyboardHandler</li>
 *   <li>GP2DMouseHandler</li>
 *   <li>GP2DJoystickHandler</li>
 *   <li>GP2DFocusHandler</li>
 * </ul>
 *
 * all implement the handleEvent(SDL_Event&) function, and handle only the
 * event which is needed at that time (keyboard, mouse or joystick events).
 *
 * @author krpors
 */
class GP2DInputHandler {
private:

    /// Boolean indicating whether this input handler should listen
    /// for events.
    gp2dBool m_enabled;

protected:

    /**
     * Pure virtual function, to handle an event dispatched by the
     * GP2DInputProcessor. Only that class can access this function because
     * it has been declared as a `friend' of GP2DInputHandler.
     */
    virtual void handleEvent(SDL_Event& event) = 0;

    /// Let the input processor have the ability to access protected functions.
    friend class GP2DInputProcessor;

public:

    /**
     * Constructor.
     */
    GP2DInputHandler();

    /**
     * Destructor.
     */
    virtual ~GP2DInputHandler();

    /**
     * Returns whether this input handler is enabled or not. Dependent on whether
     * it's true of false, the input handler will handle events or not.
     */
    gp2dBool isEnabled() const;

    /**
     * Sets this input handler as enabled(true) or not(false).
     *
     * @param enabled When true, enable event handling. If false, disables event
     *   handling.
     */
    void setEnabled(gp2dBool enabled);
};

//=============================================================================

/**
 * The GP2DKeyboardHandler is a default implementation of keyboard event
 * handling using callbacks with help of the GP2DKeyAction class.
 *
 * @author krpors
 */
class GP2DKeyboardHandler : public GP2DInputHandler {
private:
    /// The map with the Key:Action mapping.
    std::map<GP2DKeyEvent::GP2DKey, GP2DKeyAction*> m_input;

    /// The map for the global key actions.
    std::set<GP2DKeyAction*> m_globalKeyActions;

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
    GP2DKeyboardHandler();

    /**
     * Destroys the keyboard handler.
     */
    ~GP2DKeyboardHandler();

    /**
     * Registers a key event. This actually adds an entry to the map, where the
     * key paramater is also the key in the map, and the event parameter is the
     * GP2DKeyAction* value mapped to the key.
     *
     * @param key The actual SDLKey which is a key for the map.
     * @param event The GP2DKeyAction pointer for callbacking.
     */
    void registerKeyAction(GP2DKeyEvent::GP2DKey key, GP2DKeyAction* action);

    /**
     * Registers a generic key action, meaning the callback will happen on any
     * keypress.
     *
     * @param action The key action used for callbacks.
     */
    void registerGenericKeyAction(GP2DKeyAction* action);

    /**
     * Unregisters a key event by removing the specified key from the map.
     *
     * @param key The key to have its mapping removed.
     */
    void unregisterKeyAction(GP2DKeyEvent::GP2DKey key);

    /**
     * Unregisters a generic key action.
     *
     * @param action the action to remove from the map.
     */
    void unregisterGenericKeyAction(GP2DKeyAction* action);

    /**
     * Sets a key repeat to a specific initial delay, and a delay(interval)
     * after the initial delay. These are measured in milliseconds. Set to 0 if
     * you want to disable it.
     *
     * @param initialDelay The initial delay when repeats are going to be done,
     *   in milliseconds.
     * @param delay The amount of milliseconds a key is repeated.
     */
    static void setKeyRepeat(gp2dInt32 initialDelay, gp2dInt32 delay);
};

//=============================================================================

/**
 * The GP2DMouseHandler is a default implementation to mouse event handling using
 * callbacks with the GP2DMouseEvent class.
 *
 * @author krpors
 */
class GP2DMouseHandler : public GP2DInputHandler {
private:
    /// Set with mapped mouse actions.
    std::set<GP2DMouseAction*> m_actions;

    /**
     * When a mouse button is pressed, this gp2dBool is set to true. This way, a
     * 'drag' event can be callbacked. When the mouse is released, this will be
     * set to false.
     */
    gp2dBool m_mousePressed;

    /**
     * When a mouse drag is started, this will be set to true. When the mouse
     * button is released after dragging, this makes sure the keyUp event will
     * also generate a callback to mouseDragEnd().
     */
    gp2dBool m_mouseDragStarted;

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
    GP2DMouseHandler();

    /**
     * Destructor.
     */
    ~GP2DMouseHandler();

    /**
     * Registers a mouse action.
     *
     * @param action The GP2DMouseAction object for callbacks.
     */
    void registerMouseAction(GP2DMouseAction* action);

    /**
     * Unregisters a mouse action.
     *
     * @param action The action to unregister.
     */
    void unregisterMouseAction(GP2DMouseAction* action);
    
    /**
     * Unregisters all mouse actions, no callbacks will be registered
     * after this call.
     */
    void unregisterAll();

    /**
     * Gets the mouse position without using an event.
     *
     * @return A GP2DPoint instance where the mouse pointer is.
     */
    static const GP2DPoint getMousePosition();
};

//=============================================================================

/**
 * The GP2DJoystickHandler is a default implementation to joystick event handling
 * using callbacks with the GP2DJoystickEvent class.
 *
 * @author DARKGuy
 */
class GP2DJoystickHandler : public GP2DInputHandler {
private:
    /// Map with the mapped joystick to joystick actions.
    std::map<gp2dInt32, GP2DJoyAction*> m_mapJoystick;

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
    GP2DJoystickHandler();

    /**
     * Destructor.
     */
    ~GP2DJoystickHandler();


    /**
     * Gets the amount of joysticks which have been scanned by scanJoysticks();
     *
     * @return The amount of joystix.
     */
    gp2dInt32 getNumJoysticks();

    /**
     * Registers a joystick callback action.
     *
     * @param action The joystick action to register.
     */
    void registerJoyAction(gp2dInt32 device, GP2DJoyAction* action);

    /**
     * Unregister the specified joystick action.
     *
     * @param device The device to remove the joystick action from.
     */
    void unregisterJoyAction(gp2dInt32 device);
    
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
    static void setJoystickEnabled(gp2dBool enabled);

    /**
     * Checks whether the joystick is enabled or not.
     *
     * @return true when enabled, or false if not (meaning events will be
     * ignored).
     */
    static gp2dBool isJoystickEnabled();



};

//=============================================================================

class GP2DFocusHandler : public GP2DInputHandler {
private:
    std::set<GP2DFocusAction*> m_actions;

public:
    GP2DFocusHandler();
    ~GP2DFocusHandler();

    void handleEvent(SDL_Event& event);
    void unregisterAll();
    void registerFocusAction(GP2DFocusAction* action);
    void unregisterFocusAction(GP2DFocusAction* action);
};

//=============================================================================

/**
 * The GP2DInputProcessor is a very simple class. The purpose of it, is poll SDL
 * for incoming events (key, mouse, joystick, etc.) and then dispatch that event
 * to every handler supplied.
 *
 * @author krpors
 */
class GP2DInputProcessor {
private:

    /// Set with all the added handlers.
    std::set<GP2DInputHandler*> m_handlers;

    /// The SDL_Event which is used with SDL_PollEvents.
    SDL_Event m_event;

public:

    /**
     * Creates the input processor.
     */
    GP2DInputProcessor();

    /**
     * Destroys the input processor instance.
     */
    ~GP2DInputProcessor();

    /**
     * Adds an input handler to the set of handlers.
     *
     * @param handler The GP2DInputHandler pointer.
     */
    void addHandler(GP2DInputHandler* handler);

    /**
     * Removes the specific handler from the set of handlers.
     *
     * @param handler the handler to remove.
     */
    void removeHandler(GP2DInputHandler* handler);

    /**
     * Polls for an events, dispatched by SDL. For every incoming
     * event, the specified handlers are invoked. Those handlers
     * will determine whether the SDL_Event given should be handled
     * or not.
     */
    void pollEvents();
};




} // namespace gp2d


#endif /*INPUT_H_*/
