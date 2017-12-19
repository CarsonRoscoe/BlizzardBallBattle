#pragma once

#include "GameObject.h"
#include "Shader.h"
#include "Sprite.h"
#include <string>

//MenuSprite* TitleMenu("Title.png", x, y, scale = 1, nondefaultShader = nullptr);
class SimpleSprite : public GameObject {
private:
    Shader* shader;
    Sprite* sprite;
public:
    SimpleSprite(std::string path, float x, float y, float z = 0.0f, float scale = 1.0f, Shader* nonDefaultShader = nullptr);
    //~SimpleSprite();
};