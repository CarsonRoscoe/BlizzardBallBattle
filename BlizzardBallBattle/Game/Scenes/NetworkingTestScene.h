#pragma once

#include "Scene.h"
#include "GameObject.h"
#include "Shader.h"

class NetworkingTestScene : public Scene {
private:
    Shader* ourShader;
    GameObject *player1, *player2;
    bool isConnected;
    void OnConnected();

public:
    void OnStart();
    void OnUpdate(int ticks);
    void OnEnd();
	void OnResume() {}
	void OnPause() {}
};