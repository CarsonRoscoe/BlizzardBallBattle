#pragma once

#include "GLHeaders.h"
#include "ISprite.h"
#include <array>
#include <iostream>


class Sprite : public ISprite {
private:
    GLuint textureBufferID;
    std::array<GLfloat, 8> textCoordinates;

public:
    Sprite(GLuint textureBufferID);
    ~Sprite();
    virtual void BindTextCoordinates(GLuint glCBO);
    virtual GLuint GetTextureBufferID();
    virtual std::array<GLfloat, 8> GetTextureCoordinates();
};