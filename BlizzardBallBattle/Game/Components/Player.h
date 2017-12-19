#pragma once

#include "GameObject.h"
#include "Transform.h"
#include "InputManager.h"
#include "GLHeaders.h"
#include "Shader.h"
#include "Battler.h"
#include "Snowball.h"
#include "Physics.h"

class Player : public Component {
private:
	SDL_Keycode leftKey;
	SDL_Keycode rightKey;
	SDL_Keycode upKey;
	SDL_Keycode downKey;
	SDL_Keycode shootKey, shootKey2;
	float distance;
	Battler* youBattler;
	float center;
	
public:
	Player(GameObject* gameObject, SDL_Keycode left,  SDL_Keycode right, SDL_Keycode up, SDL_Keycode down, SDL_Keycode shoot, SDL_Keycode shoot2);
	
	void ComputeMovement(float deltaTime);
	void OnStart(){};
	void OnUpdate(int ticks);
	void OnEnd(){};
};
