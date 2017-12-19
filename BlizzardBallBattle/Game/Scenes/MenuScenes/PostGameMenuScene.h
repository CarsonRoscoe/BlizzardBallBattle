#pragma once

#include "MenuScene_Alpha.h"
#include "SimpleSprite.h"
#include <string>

class PostGameMenuScene : public MenuScene_Alpha {
private:
    std::string winnerTextPath;
    SimpleSprite *winnerText, *spaceToReturnText;
public:
    PostGameMenuScene(int winningTeamID);
    virtual void OnStart();
    virtual void OnUpdate(int ticks);
    virtual void OnEnd() {}
	virtual void OnPause();
    virtual void OnResume() {}
    ~PostGameMenuScene();
};