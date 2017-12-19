#include "SceneManager.h"
#include <iostream>

SceneManager* SceneManager::instance;

SceneManager* SceneManager::GetInstance() {
    if (instance == NULL)
        instance = new SceneManager();
    return instance;
}

SceneManager::SceneManager() {
}

void SceneManager::PushScene(Scene *scene) {
    if (!scenes.empty()) 
        scenes.top()->OnPause();
    scenes.push(scene);
    scene->OnStart();
}

bool SceneManager::UpdateScene(int ticks) {
    if (scenes.empty()) 
        return false;
    scenes.top()->OnObjectsUpdate(ticks);
    scenes.top()->OnUpdate(ticks);
    return true;
}

bool SceneManager::HasScene() {
    return !scenes.empty();
}

bool SceneManager::PopScene() {
    if (scenes.empty()) 
        return false;
    scenes.top()->OnEnd();
    scenes.pop();
    scenes.top()->OnResume();
    return true;
}

Scene* SceneManager::GetCurrentScene() {
    if (scenes.empty()) 
        return NULL;
    return scenes.top();
}