#pragma once

#include "Scene.h"
#include "GameObject.h"
#include "Shader.h"

class PlayerTestScene : public Scene {
private:
	Shader* ourShader;
	GameObject *chensPlayer1, *chensPlayer2, *snowBall1, *snowBall2;

public:
	void OnStart();
	void OnUpdate(int ticks);
	void OnEnd();
	void OnResume() {}
	void OnPause() {}
};