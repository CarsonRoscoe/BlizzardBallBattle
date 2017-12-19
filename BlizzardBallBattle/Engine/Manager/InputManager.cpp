#include "InputManager.h"

InputManager* InputManager::instance;

InputManager* InputManager::GetInstance() {
    if (instance == NULL)
        instance = new InputManager();
    return instance;
}

bool InputManager::onKeyPressed(SDL_Keycode code) {
    std::map<SDL_Keycode,KeyAction>::iterator it = keys.find(code);
    if (it != keys.end())
        return it->second == InputManager::KeyAction::PRESSED;
	return false;
}

bool InputManager::onKey(SDL_Keycode code) {
    std::map<SDL_Keycode,KeyAction>::iterator it = keys.find(code);
    if (it != keys.end()) 
        return it->second != InputManager::KeyAction::NONE;
	return false;
}

bool InputManager::onKeyReleased(SDL_Keycode code) {
    std::map<SDL_Keycode,KeyAction>::iterator it = keys.find(code);
    if (it != keys.end())
        return it->second == InputManager::KeyAction::RELEASED;
	return false;
}

InputManager::KeyAction InputManager::getKeyState(SDL_Keycode code) {
    std::map<SDL_Keycode,KeyAction>::iterator it = keys.find(code);
    if (it != keys.end())
        return it->second;
    else
        return InputManager::KeyAction::NONE;
}

void InputManager::UpdateKeys() {
    for (std::map<SDL_Keycode,KeyAction>::iterator it=keys.begin(); it!=keys.end(); ++it) {
        if (it->second == InputManager::KeyAction::PRESSED)
            it->second = InputManager::KeyAction::HELD;
        if (it->second == InputManager::KeyAction::RELEASED)
            it->second = InputManager::KeyAction::NONE;
    }
}

void InputManager::HandlePolledEvent(SDL_Event event)
{
    if (event.type != SDL_KEYDOWN && event.type != SDL_KEYUP)
        return;
    SDL_Keycode code = event.key.keysym.sym;
    std::map<SDL_Keycode,KeyAction>::iterator it = keys.find(code);
    if (event.type == SDL_KEYDOWN)
        if (it == keys.end() || (it != keys.end() && it->second != InputManager::KeyAction::HELD))
            keys[code] = InputManager::KeyAction::PRESSED;
    if (event.type == SDL_KEYUP)
        if (it != keys.end() && it->second == InputManager::KeyAction::HELD)
            keys[code] = InputManager::KeyAction::RELEASED;
}