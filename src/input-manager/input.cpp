/////////////////////////////////////////////////////////////
// handles input management (keyboard, mouse and controller)
/////////////////////////////////////////////////////////////
#include "input.hpp"

// init static members
std::unordered_map<KeyCode, bool> Input::mCurrentKeyState;
std::unordered_map<KeyCode, bool> Input::mPreviousKeyState;

std::unordered_map<MouseCode, bool> Input::mCurrentMouseState;
std::unordered_map<MouseCode, bool> Input::mPreviousMouseState;

float Input::mMouseX = 0;
float Input::mMouseY = 0;

void Input::Update()
{
    mPreviousKeyState = mCurrentKeyState;
    mPreviousMouseState = mCurrentMouseState;
}

void Input::ProcessEvent(const SDL_Event& event)
{
    switch(event.type)
    {
        case SDL_EVENT_KEY_DOWN:
        {
            KeyCode key = SDLKeyToKeyCode(event.key.key);
            mCurrentKeyState[key] = true;
            break;
        }

        case SDL_EVENT_KEY_UP:
        {
            KeyCode key = SDLKeyToKeyCode(event.key.key);
            mCurrentKeyState[key] = false;
            break;
        }

        case SDL_EVENT_MOUSE_BUTTON_DOWN:
        {
            MouseCode mouse = SDLButtonToMouseButton(event.button.button);
            mCurrentMouseState[mouse] = true;
            break;
        }

        case SDL_EVENT_MOUSE_BUTTON_UP:
        {
            MouseCode mouse = SDLButtonToMouseButton(event.button.button);
            mCurrentMouseState[mouse] = false;
            break;
        }

        case SDL_EVENT_MOUSE_MOTION:
        {
            mMouseX = event.motion.x;
            mMouseY = event.motion.y;
            break;
        }
    }
}

bool Input::GetKeyDown(KeyCode key)
{
    return mCurrentKeyState[key] && !mPreviousKeyState[key];
}

bool Input::GetKey(KeyCode key)
{
    return mCurrentKeyState[key];
}

bool Input::GetMouseButtonDown(MouseCode mouse)
{
    return mCurrentMouseState[mouse] && !mPreviousMouseState[mouse];
}

bool Input::GetMouseButton(MouseCode mouse)
{
    return mCurrentMouseState[mouse];
}

void Input::GetMousePosition(float& x, float& y)
{
    x = mMouseX;
    y = mMouseY;
}

KeyCode Input::SDLKeyToKeyCode(SDL_Keycode sdlKey)
{
    // map each corresponding key from abstracted lingo I made :3
    switch(sdlKey)
    {
        case SDLK_A: return KeyCode::A;
        case SDLK_B: return KeyCode::B;
        case SDLK_C: return KeyCode::C;
        case SDLK_D: return KeyCode::D;
        case SDLK_E: return KeyCode::E;
        case SDLK_F: return KeyCode::F;
        case SDLK_G: return KeyCode::G;
        case SDLK_H: return KeyCode::H;
        case SDLK_I: return KeyCode::I;
        case SDLK_J: return KeyCode::J;
        case SDLK_K: return KeyCode::K;
        case SDLK_L: return KeyCode::L;
        case SDLK_M: return KeyCode::M;
        case SDLK_N: return KeyCode::N;
        case SDLK_O: return KeyCode::O;
        case SDLK_P: return KeyCode::P;
        case SDLK_Q: return KeyCode::Q;
        case SDLK_R: return KeyCode::R;
        case SDLK_S: return KeyCode::S;
        case SDLK_T: return KeyCode::T;
        case SDLK_U: return KeyCode::U;
        case SDLK_V: return KeyCode::V;
        case SDLK_W: return KeyCode::W;
        case SDLK_X: return KeyCode::X;
        case SDLK_Y: return KeyCode::Y;
        case SDLK_Z: return KeyCode::Z;

        case SDLK_1: return KeyCode::NUM1;
        case SDLK_2: return KeyCode::NUM2;
        case SDLK_3: return KeyCode::NUM3;
        case SDLK_4: return KeyCode::NUM4;
        case SDLK_5: return KeyCode::NUM5;
        case SDLK_6: return KeyCode::NUM6;
        case SDLK_7: return KeyCode::NUM7;
        case SDLK_8: return KeyCode::NUM8;
        case SDLK_9: return KeyCode::NUM9;
        case SDLK_0: return KeyCode::NUM0;

        case SDLK_SPACE: return KeyCode::SPACE;
        case SDLK_RETURN: return KeyCode::ENTER;
        case SDLK_ESCAPE: return KeyCode::ESCAPE;
        case SDLK_TAB: return KeyCode::TAB;
        case SDLK_BACKSPACE: return KeyCode::BACKSPACE;

        case SDLK_LSHIFT: return KeyCode::LSHIFT;
        case SDLK_RSHIFT: return KeyCode::RSHIFT;
        case SDLK_LCTRL: return KeyCode::LCONTROL;
        case SDLK_RCTRL: return KeyCode::RCONTROL;

        case SDLK_UP: return KeyCode::UPARROW;
        case SDLK_DOWN: return KeyCode::DOWNARROW;
        case SDLK_LEFT: return KeyCode::LEFTARROW;
        case SDLK_RIGHT: return KeyCode::RIGHTARROW;

        // Add more mappings as needed
        default: return KeyCode::ESCAPE; // Fallback
    }
}

MouseCode Input::SDLButtonToMouseButton(Uint8 sdlButton)
{
    switch(sdlButton)
    {
        case SDL_BUTTON_LEFT: return MouseCode::LEFTMOUSE;
        case SDL_BUTTON_RIGHT: return MouseCode::RIGHTMOUSE;
        case SDL_BUTTON_MIDDLE: return MouseCode::MIDDLEMOUSE;
        default: return MouseCode::LEFTMOUSE;
    }
}
