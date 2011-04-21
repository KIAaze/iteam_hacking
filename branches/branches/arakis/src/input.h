#ifndef _GP2D_INPUT_H_
#define _GP2D_INPUT_H_

#include <SDL/SDL.h>
#include <SDL/SDL_joystick.h>
#include <map>
#include <set>
#include <vector>
#include <iostream>

namespace gp2d {

/**
 * The GP2DKeyEvent encapsulates information about a keyboard action which
 * generated an event. This class is mostly useful when global key actions are
 * callbacked, because then you know what key was pressed.
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
    GP2DKeyEvent(const GP2DKey& key, const GP2DKeyMod& modifier);

    /**
     * Destructor for the GP2DKeyEvent. Currently does not much.
     */
    ~GP2DKeyEvent();

    /**
     * Gets the key which was pressed.
     *
     * @return The GP2DKey which was pressurized.
     */
    const GP2DKeyEvent::GP2DKey getKey(void);

    /**
     * Gets the modifier which was used.
     *
     * @return One of the GP2DKeyMod enum.
     */
    const GP2DKeyEvent::GP2DKeyMod getModifier(void);

private:
    // normally, I write private BEFORE public declarations. This one goes
    // after the public, because otherwise the GP2DKey and GP2DKeyMod enums cannot
    // be resolved.

    /// The key which generated the event.
    GP2DKey m_key;

    /// A keyboard modifier (one of the GP2DKeyMod enumeration).
    GP2DKeyMod m_modifier;
};



/**
 * The GPMouseEvent is a class encapsulating information about a generated mouse
 * event, such as where (x,y) and the button pressed.
 */
class GP2DMouseEvent {
private:
    ///  The x position on the screen where the event occurred.
    int m_x;

    /// The y position on the screen where the event occurred.
    int m_y;

    /// The mouse button which was pressed.
    int m_mouseButton;

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
    GP2DMouseEvent(int x, int y, GP2DMouseButton mouseButton);

    /**
     * Deletes the GP2DMouseEvent.
     */
    ~GP2DMouseEvent();

    /**
     * Gets the x position of the event.
     *
     * @return the x pos on the window.
     */
    const int getX();

    /**
     * Gets the y position of th event.
     *
     * @return the y pos on the window.
     */
    const int getY();

    /**
     * Gets the button which generated the event.
     *
     * @return The button.
     */
    const int getButton();
};


class GP2DJoyEvent {
private:
	int m_joyDevice;

	int m_joyButton;
	int m_joyButtonState;

	int m_joyAxis;
	int m_joyAxisValue;
public:
    enum GP2DJoyAxis {
        GP2D_AXIS_HORIZONTAL,
		GP2D_AXIS_VERTICAL
    };

	GP2DJoyEvent(int device, int axis, int value, int button, int state);
	~GP2DJoyEvent();

	 const int getDevice();

    const int getButton();
	 const int getButtonState();

    const int getAxis();
	 const int getAxisValue();

};

class GP2DJoyAction {
public:
    enum GP2DJoyAxis {
        GP2D_AXIS_HORIZONTAL,
		GP2D_AXIS_VERTICAL
    } GP2DJoyAxis;
    /**
     * Constructor for the GP2DKeyAction.
     */
    GP2DJoyAction();

    /**
     * Virtual destructor. If not declared as virtual, the compiler will
     * generate warnings. I'm not sure why though.
     */
    virtual ~GP2DJoyAction();

    /**
     * Callback method when a key is held down.
     *
     * @param event The generated SDL_Event.
     */
    virtual void buttonDown(GP2DJoyEvent& joyEvent);

    /**
     * Callback method when a key is released.
     *
     * @param event The generated SDL_Event.
     */
    virtual void buttonUp(GP2DJoyEvent& joyEvent);

    /**
     * Callback method when a key is held down.
     *
     * @param event The generated SDL_Event.
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
     * called. This ALWAYS happens after mouseButtonDown(int,int,int).
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




/**
 * The GPInputHandler is the base class which is responsible for handling input
 * events. Currently only mouse and keyboard events are supported. It is
 * programmed in such a way that it can respond to keyboard input and mouse
 * input events.
 *
 * Using the function handleInputEvents() it handles the events, naturally.
 *
 * @author krpors
 */
class GP2DInputHandler {
private:
    /**
     * A mapping between a key and an action.
     */
    std::map<GP2DKeyEvent::GP2DKey, GP2DKeyAction*> m_mapinput;

    /**
     * This map is used to map GP2DKeys with a void f(void) function pointer.
     * It is used when keyboard buttons are PRESSED down.
     */
    std::map<GP2DKeyEvent::GP2DKey, void(*)(void)> m_mapBasicKeydown;

    /**
     * This map is used to map GP2DKeys with a void f(void) function
     * pointer. It is used when keyboard buttons are RELEASED from
     * pressure.
     */
    std::map<GP2DKeyEvent::GP2DKey, void(*)(void)> m_mapBasicKeyup;

    /**
     * A map used to map a mouse button press with a function pointer.
     */
    std::map<GP2DMouseEvent::GP2DMouseButton, void(*)(GP2DMouseEvent&)> m_mapBasicMouseDown;

    /**
     * A map used to map a mouse button release with a function pointer.
     */
    std::map<GP2DMouseEvent::GP2DMouseButton, void(*)(GP2DMouseEvent&)> m_mapBasicMouseUp;

    /**
     * A set used to set mouse move function pointers.
     */
    std::set<void(*)(GP2DMouseEvent&)> m_setBasicMouseMove;

    /**
     * The map for the global key actions.
     */
    std::set<GP2DKeyAction*> m_globalKeyActions;

    std::vector<SDL_Joystick*> m_joystick;
    std::map<int, GP2DJoyAction*> m_mapJoystick;
	
    std::map<int, void(*)(void)> m_mapBasicJoyButtonDown;
	 std::map<int, void(*)(void)> m_mapBasicJoyButtonUp;
	 std::map<int, void(*)(int)> m_mapBasicJoyAxisChange;

    // XXX: more mouse actions, like global key actions?
    /// Only need to register one mouse event type (since we only have one mouse).

    GP2DMouseAction* m_mouseaction;

    /// The actual SDL_Event, used to define it with SDL_PollEvents().
    SDL_Event m_event;

    /**
     * When a mouse button is pressed, this bool is set to true. This way, a
     * 'drag' event can be callbacked. When the mouse is released, this will be
     * set to false.
     */
    bool m_mousePressed;

    /**
     * When a mouse drag is started, this will be set to true. When the mouse
     * button is released after dragging, this makes sure the keyUp event will
     * also generate a callback to mouseDragEnd().
     */
    bool m_mouseDragStarted;

    /**
     * When this variable is set to true, polling mapped key events by the
     * inputhandler will be done. This is to (temporarily) disable key inputs.
     */
    bool m_keyMapsEnabled;

    /**
     * When this variable is set to true, polling mouse events by the
     * inputhandler will be done. This is to (temporarily) disable mouse inputs.
     */
     bool m_mouseeventsEnabled;

    /**
     * When this variable is set to true, polling mouse events by the
     * inputhandler will be done. This is to (temporarily) disable mouse inputs.
     */
     bool m_joystickeventsEnabled;

     /**
      * When this variable is set to true, polling global key events by the
      * inputhandler will be done. This is to (temporarily) disable global key
      * inputs.
      */
     bool m_globalkeysEnabled;

     /**
      * Okay, the naming is probably terrible, but this method should handle
      * the 'basic' input handling which makes use of C style function pointers.
      */
     void handleFPKeyInputEvents();

     /**
      * Naming is terrible here too, but this method should handle the OOP style
      * of input handling (which is done using GoF's Command and Template design
      * patterns).
      */
     void handleOOPKeyInputEvents();

     /**
      * Naming is terrible here too, but this method should handle the 'basic'
      * mouse input events which make use of C style function pointers.
      */
     void handleFPMouseInputEvents();

     /**
      * Naming is terrible here too, but this method should handle the function
      * style pointer style of mouse input handling (which is done using GoF's
      * Command and Template design patterns).
      */
     void handleOOPMouseInputEvents();

     void handleFPJoystickInputEvents();
	 void handleOOPJoystickInputEvents();

public:

    /**
     * Constructor.
     */
    GP2DInputHandler();

    /**
     * Destructor. Clears the map from any pointers to GP2DKeyAction*'s, and the
     * possible registered GP2DMouseAction*.
     */
    ~GP2DInputHandler();

    /**
     * Sets listening for global keys to enabled or disabled.
     *
     * @param a_keyeventsEnabled true when the events must be callbacked, false
     *  if otherwise.
     */
    void setGlobalKeysEnabled(bool a_globalkeysEnabled);

    /**
     * Sets listening for mapped keys to enabled or disabled.
     *
     * @param a_keyeventsEnabled true when the events must be callbacked, false
     *  if otherwise.
     */
    void setKeyMapsEnabled(bool a_keyMapsEnabled);

    /**
     * Sets listening for mouse events to enabled or disabled.
     *
     * @param a_mouseeventsEnabled true when the events must be callbacked, false
     *  if otherwise.
     */
    void setMouseEnabled(bool a_mouseeventsEnabled);

    /**
     * Sets listening for joystick events to enabled or disabled.
     *
     * @param a_mouseeventsEnabled true when the events must be callbacked, false
     *  if otherwise.
     */
    void setJoystickEnabled(bool a_joystickeventsEnabled);

    /**
     * Sets a key repeat to a specific initial delay, and a delay(interval)
     * after the initial delay. These are measured in milliseconds. Set to 0 if
     * you want to disable it.
     *
     * @param initialDelay The initial delay when repeats are going to be done,
     *   in milliseconds.
     * @param delay The amount of milliseconds a key is repeated.
     */
    void setKeyRepeat(int initialDelay, int delay);

    /**
     * Handles events. This means polling them (SDL_PollEvents), checking if the
     * event was mapped, and then possibly executing them (invoking the callback).
     *
     * The events handles individual key events (mapped with registerKeyEvent),
     * and mouse events (mapped with registerMouseEvent). Mouse drag, movement,
     * mouse button down and mouse button up.
     */
    void handleInputEvents();

    /**
     * This will register a 'global' key event, meaning any keypress is
     * callbacked. This is especially handy if you want to register any keypress
     * because it is needed in the application (for example, when some chat
     * function is enabled, you want to catch all events from the keyboard).
     *
     * Every GP2DKeyAction* which is registered in a backed set. That means that
     * registering the same GP2DKeyAction* instance will not have any effect. If
     * we were to use a vector, one keypress would result in an x amount of
     * callbacks.
     *
     * @param event The action event callback object.
     */
    void registerGlobalKeyAction(GP2DKeyAction* action);

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
     * Registers a mouse event. When the mouse event given is NULL, nothing is
     * done. Use unregisterMouseEvent(void) instead. If the mouse event is not
     * NULL, a check is being made if a mouse event was registered previously.
     * If yes, it is deleted, and re-assigned. If not, it is simply assigned.
     */
    void registerMouseAction(GP2DMouseAction* action);

    /**
     * This function registers a GP2DKey key to a preferred function callback.
     * It has been put here to enable quick and fast mappings of keys to functions,
     * which will enable quick writing of some functionality within your GUI.
     *
     * This function is for when the specific key is held down.
     *
     * @param key The key, one of the GP2DKey enumeration.
     * @param callbackFunction The callback function which takes the form of
     *  `void myFunction(void)`.
     */
    void registerKeyDown(GP2DKeyEvent::GP2DKey key, void (*callbackFunction)(void));

    /**
     * This function registers a GP2DKey key to a preferred function callback.
     * It has been put here to enable quick and fast mappings of keys to functions,
     * which will enable quick writing of some functionality within your GUI.
     *
     * This function is for when the specific key is released from pressure.
     *
     * @param key The key, one of the GP2DKey enumeration.
     * @param callbackFunction The callback function which takes the form of
     *  `void myFunction(void)`.
     */
    void registerKeyUp(GP2DKeyEvent::GP2DKey key, void (*callbackFunction)(void));

    /**
     * This function registers a GP2DmouseButton with a preferred function
     * callback. It has been put here just like the registerKeyUp/Down to enable
     * fast mappings of buttons to functions, which will enable quick writing
     * of some functionality within your GUI.
     *
     * This function is for when a mouse button is held down.
     *
     * @param button The button from GP2DMouseEvent::GP2DMouseButton enumeration
     *   which should be registered.
     * @param callbackFunction The function callback of prototype
     *   `void myFunc(GP2DMouseEvent&)`.
     */
    void registerMouseDown(GP2DMouseEvent::GP2DMouseButton button, void (*callbackFunction)(GP2DMouseEvent&));

    /**
     * This function registers a GP2DmouseButton with a preferred function
     * callback. It has been put here just like the registerKeyUp/Down to enable
     * fast mappings of buttons to functions, which will enable quick writing
     * of some functionality within your GUI.
     *
     * This function is for when a mouse button is released.
     *
     * @param button The button from GP2DMouseEvent::GP2DMouseButton enumeration
     *   which should be registered.
     * @param callbackFunction The function callback of prototype
     *   `void myFunc(GP2DMouseEvent&)`.
     */
    void registerMouseUp(GP2DMouseEvent::GP2DMouseButton button, void (*callbackFunction)(GP2DMouseEvent&));

    /**
     * This function registers a GP2DmouseButton with a preferred function
     * callback. It has been put here just like the registerKeyUp/Down to enable
     * fast mappings of buttons to functions, which will enable quick writing
     * of some functionality within your GUI.
     *
     * This function is for when a mouse movement is made on the screen.
     *
     * @param callbackFunction The function callback of prototype
     *   `void myFunc(GP2DMouseEvent&)`.
     */
    void registerMouseMove(void (*callbackFunction)(GP2DMouseEvent&));

    /**
     * Unregisters a key action from the backed map.
     *
     * @param key The key to remove. The value which is used (a pointer) will be
     *   deleted.
     */
    void unregisterKeyAction(GP2DKeyEvent::GP2DKey key);

    /**
     * Unregisters the mouse action.
     */
    void unregisterMouseAction();

    /**
     * Unregisters a basic function callback. Since a function pointer is stored
     * in the map, the pointer itself cannot be deleted, so only the key is
     * removed. This function unregister a possible registered key down action.
     * If the specified key was not yet registered, nothing will be done.
     *
     * @param callbackFunction The function to unregister.
     */
    void unregisterKeyDown(GP2DKeyEvent::GP2DKey key);

    /**
     * Unregisters a basic function callback. Since a function pointer is stored
     * in the map, the pointer itself cannot be deleted, so only the key is
     * removed. This function unregister a possible registered key up action.
     * If the specified key was not yet registered, nothing will be done.
     *
     * @param callbackFunction The function to unregister.
     */
    void unregisterKeyUp(GP2DKeyEvent::GP2DKey key);

    /**
     * Unregisters a basic function callback. Since a function pointer is stored
     * in the map, the pointer itself cannot be deleted, so only the key is
     * removed. This function unregister a possible registered mouse down action.
     * If the specified key was not yet registered, nothing will be done.
     *
     * @param callbackFunction The function to unregister.
     */
    void unregisterMouseDown(GP2DMouseEvent::GP2DMouseButton button);

    /**
     * Unregisters a basic function callback. Since a function pointer is stored
     * in the map, the pointer itself cannot be deleted, so only the key is
     * removed. This function unregister a possible registered mouse up action.
     * If the specified key was not yet registered, nothing will be done.
     *
     * @param callbackFunction The function to unregister.
     */
    void unregisterMouseUp(GP2DMouseEvent::GP2DMouseButton button);

    /**
     * Unregisters a basic function callback. Since a function pointer is stored
     * in the map, the pointer itself cannot be deleted, so only the key is
     * removed. This function unregister a possible registered mouse move action.
     * If the specified key was not yet registered, nothing will be done.
     *
     * @param callbackFunction The function to unregister.
     */
    void unregisterMouseMove(void (*callbackFunction)(GP2DMouseEvent&));

    void scanJoysticks();
    int getNumJoysticks();
	void registerJoystick(int device, GP2DJoyAction* event);
	void registerJoyButtonDown(int button, void (*callbackFunction)(void));
	void registerJoyButtonUp(int button, void (*callbackFunction)(void));
	void registerAxisChange(int axis, void (*callbackFunction)(int));

};


} // namespace gp2d


#endif /*INPUT_H_*/
