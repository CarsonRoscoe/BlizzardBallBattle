#pragma once

#include "GameScene.h"
#include "GameObject.h"
#include "Shader.h"

class SceneTemplate : public GameScene {
private:
	Shader* ourShader;
	int p1ai, p2ai;

public:
	SceneTemplate(int p1ai, int p2ai);
	void OnStart();
	void OnResume() {};
	void OnUpdate(int ticks);
	void OnPause();
	void OnEnd();
	
};