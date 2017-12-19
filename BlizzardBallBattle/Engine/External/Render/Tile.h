#pragma once
/*
#include "GLHeaders.h"
#include "ISprite.h"
#include <array>
#include <iostream>
#include "TileSheetInfo.h"
#include <string>

class Tile : public ISprite {
private:
    int currentIndex;
    TileSheetInfo tileSheetInfo;
    std::array<GLfloat, 8> textCoordinates;
    void ReloadTextCoordinates();

public:
    Tile(TileSheetInfo tileSheetInfo);
    ~Tile();
    virtual void BindTextCoordinates(GLuint glCBO);
    virtual GLuint GetTextureBufferID();
    void SetTile(std::string tileName);
};*/