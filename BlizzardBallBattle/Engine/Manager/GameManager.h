#pragma once

#include "Updateable.h"
#include "GLHeaders.h"
#include "GameObject.h"
#define GL3_PROTOTYPES 1
#include "Scene.h"
#include "Game.h"
#include <vector>

class GameManager : public Updateable 
{
public:
    GameManager();
    void OnStart();
    void OnUpdate(int ticks);
	void ClearObjectsToRemove();
    void OnEnd();
    static GameManager* GetInstance();

    void AddGameObject(int id, GameObject* obj);
    void RemoveGameObject(GameObject* objectToRemove);

private:
	std::vector<GameObject*> gameObjectsToRemove;
    std::map<int, GameObject*> globalGameObjects;
    static GameManager* instance;
    bool breakLoop = false;
    int lastTime = 0;
    //game instance.
    Game* game;
    
    void FPSThrottle(int ticks);
};