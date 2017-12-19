#pragma once

#include "MenuScene_Alpha.h"
#include "SimpleSprite.h"

class LaunchMenuScene : public MenuScene_Alpha {
private:
    SimpleSprite* menuTitle, *howToText;
public:
    virtual void OnStart();
    virtual void OnUpdate(int ticks);
    virtual void OnEnd();
    virtual void OnPause();
    virtual void OnResume();
    ~LaunchMenuScene();

    void CreateScene();
    void DestroyScene();
};