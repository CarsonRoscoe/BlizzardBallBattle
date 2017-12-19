#pragma once

#include "GLHeaders.h"
#include <map>
#include <iostream>

class InputManager
{
  public:
    enum KeyAction
    {
        NONE,
        PRESSED,
        HELD,
        RELEASED
    };

    static InputManager* GetInstance();

    bool onKeyPressed(SDL_Keycode code);
    bool onKey(SDL_Keycode code);
    bool onKeyReleased(SDL_Keycode code);
    KeyAction getKeyState(SDL_Keycode code);
    void HandlePolledEvent(SDL_Event event);
    void UpdateKeys();

private:
    
        static InputManager *instance;
        std::map<SDL_Keycode, KeyAction> keys;

};