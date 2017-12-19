#pragma once

#include "GameObject.h"
#include "Renderer.h"
#include "Shader.h"
#include "ISprite.h"

class SpriteRenderer : public Renderer {
private:
  GLuint textureBufferID;
  Shader* activeShader;
  ISprite* activeSprite;

public:
    SpriteRenderer(GameObject* gameObject);
    void Render();
    void SetActiveShader(Shader* shader);
    void SetActiveSprite(ISprite* sprite);
    Shader* GetShader();
    ISprite* GetSprite();
    ~SpriteRenderer();
};
