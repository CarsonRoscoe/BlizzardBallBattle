#pragma once

#include "GameObject.h"
#include "SpriteRendererManager.h"

class Camera : public GameObject {
private:
    static Camera* activeCamera;
    bool init;

protected:
    void virtual Init();
    void EnsureInit();

public:
    Camera();
    void virtual ApplyRenderFilters(SpriteRendererManager* rendererManager);
    void virtual NotifyInactivity();
    
    static void SetActiveCamera(Camera* camera);
    static Camera*  GetActiveCamera();
};