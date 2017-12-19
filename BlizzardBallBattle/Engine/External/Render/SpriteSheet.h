#pragma once

#include "GLHeaders.h"
#include "ISprite.h"
#include <array>
#include <iostream>

/*
TODO: With messaging system, create a "SpriteHUB" object that extends ISprite.
This SpriteHUB will let you set as many sprites as you want, with info on what event to trigger, or something like that.
Basically, easy system for switching between sprites
*/

class SpriteSheet : public ISprite {
private:
    GLuint textureBufferID;
    int currentIndex;
    int columnCount;
    int rowCount;
    int skipLastFrames;
    void ReloadTextCoordinates();
	std::array<GLfloat, 8> textCoordinates;

public:
    SpriteSheet(GLuint textureBufferID, int columnCount, int rowCount, int skipLastFrames = 0, int startIndex = 0);
    ~SpriteSheet();
    virtual void BindTextCoordinates(GLuint glCBO);
    virtual GLuint GetTextureBufferID();
    virtual std::array<GLfloat, 8> GetTextureCoordinates();
    void NextIndex();
    void ResetIndex();
    int GetRowCount();
    int GetColumnCount();
    int GetCurrentIndex();
};