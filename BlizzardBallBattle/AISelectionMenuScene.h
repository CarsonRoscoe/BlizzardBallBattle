#pragma once

#include "MenuScene_Alpha.h"
#include "SimpleSprite.h"
#include <string>

class AISelectionMenuScene : public MenuScene_Alpha {
private:
	SimpleSprite *title, *ai1Preview, *ai2Preview, *ai3Preview;
	SimpleSprite *oneStatus, *twoStatus;
	bool p1Done, p2Done;
	int p1Result, p2Result;

public:
	AISelectionMenuScene();
	virtual void OnStart();
	virtual void OnUpdate(int ticks);
	virtual void OnEnd() {}
	virtual void OnPause();
	virtual void OnResume() {}
	bool TryEnd();

	~AISelectionMenuScene();
};