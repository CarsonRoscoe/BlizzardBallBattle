#pragma once

#include "GameObject.h"
#include "ComponentTemplate.h"
#include "Example.h"

class GameObjectTemplate : public GameObject {
private:
    ////Private Variables
    ExampleClass* dataToDestroyForExample;

    ////Private Methods

public:
    ////Public Variables

    ////Public Methods
    //The constructor that is called on creation
    GameObjectTemplate();
    //The destructor that is called on deletion
    ~GameObjectTemplate();
    //Any public methods you want other Components/GameObjects to have access too
    void ExampleMethod();

    void OnStart(){};
    void OnUpdate(int ticks){};
    void OnEnd(){};
};