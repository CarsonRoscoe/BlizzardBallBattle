#pragma once

#include "Scene.h"
#include "GameObject.h"
#include "Shader.h"

class MessagingTestScene : public Scene {
private:

public:
	void OnStart();
	void OnUpdate(int ticks);
	void OnEnd();
	void OnResume() {}
	void OnPause() {}
};