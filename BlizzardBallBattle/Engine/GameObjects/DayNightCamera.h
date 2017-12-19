#pragma once

#include "Camera.h"
#include "FrameBufferObject.h"

class DayNightCamera : public Camera {
private:
    FrameBufferObject regularPass;
    FrameBufferObject ambientLighting;

public:
    void virtual ApplyRenderFilters(SpriteRendererManager* rendererManager);
    void virtual Init();
};