#pragma once

#include "GameScene.h"
#include "Battler.h"

class GameScene_Alpha_Networked : public GameScene {
private:
	Battler *player1, *player2, *AI1T1, *AI2T1, *AI1T2, *AI2T2;
	bool isConnected;
	void OnConnected();

public:
	GameScene_Alpha_Networked();
	void OnStart();
	void OnResume(){};
	void OnUpdate(int ticks);
	void OnPause(){};
	void OnEnd();
};