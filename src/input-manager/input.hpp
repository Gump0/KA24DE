#ifndef INPUT_H
#define INPUT_H

#include <SDL3/SDL.h>
#include <unordered_map>
//---------------------------------------------------------------------------------
enum KeyCode
{
    // keyboard inputs
    A, B, C, D, E, F, G,
    H, I ,J, K, L, M, N,
    O, P, Q, R, S, T, U,
    V, W, X, Y, Z,

    // numbers
    NUM1, NUM2, NUM3, NUM4, NUM5,
    NUM6, NUM7, NUM8, NUM9, NUM0,

    // special keys
    ENTER, ESCAPE, BACKSPACE, SPACE,

    // modifiers
    TAB, CAPS, LSHIFT, RSHIFT,
    LCONTROL, RCONTROL, LALT, RALT,

    // arrow keys
    LEFTARROW, RIGHTARROW, UPARROW, DOWNARROW
};

enum MouseCode
{
    LEFTMOUSE,
    RIGHTMOUSE,
    MIDDLEMOUSE
};
//---------------------------------------------------------------------------------
class Input
{
public:
    static void Update();

    static void ProcessEvent(const SDL_Event& event);

    // get key event
    static bool GetKeyDown(KeyCode key);    // returns true once the moment a key is pressed down
    static bool GetKey(KeyCode key);        // returns true when key is down (repeated)

    // get mouse event
    static bool GetMouseButtonDown(MouseCode mouse);
    static bool GetMouseButton(MouseCode mouse);

    static void GetMousePosition(float& x, float& y);

private:
    // Track current and previous frame states
    static std::unordered_map<KeyCode, bool> mCurrentKeyState;
    static std::unordered_map<KeyCode, bool> mPreviousKeyState;

    static std::unordered_map<MouseCode, bool> mCurrentMouseState;
    static std::unordered_map<MouseCode, bool> mPreviousMouseState;

    static float mMouseX;
    static float mMouseY;

    // helper function to convert SDL => keycode
    static KeyCode SDLKeyToKeyCode(SDL_Keycode sdlKey);
    static MouseCode SDLButtonToMouseButton(Uint8 sdlButton);
};

#endif
