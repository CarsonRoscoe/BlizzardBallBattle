#pragma once

#include "GameObject.h"

class Scene : public Updateable {
private:
	std::vector<int> idsToRemove;

public:
    std::map<int, GameObject*> sceneObjects;

    //Called on unpausing from the SceneManager's scene stack.
    virtual void OnResume() = 0;

    //Called by manager, do not override, used to update game objects in scene.
    void OnObjectsUpdate(int ticks);

    //Called when pausing the scene when another scene is added on top of SceneManager's stack.
    virtual void OnPause() = 0;

    //Add a game object that belongs to this scene. Global objects will not be here, but in Game Manager.
    void AddGameObject(int id, GameObject* obj);
     
    //Remove a game object from the scene
    void RemoveGameObject(int id);

	void Purge();
};