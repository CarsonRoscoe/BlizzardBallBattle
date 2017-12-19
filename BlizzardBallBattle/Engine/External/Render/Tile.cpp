#include "Tile.h"
#include <iostream>

/*ile::Tile(TileSheetInfo tileSheetInfo) {
    this->tileSheetInfo = tileSheetInfo;
}

SpriteSheet::~SpriteSheet() {

}

void SpriteSheet::BindTextCoordinates(GLuint glCBO) {
    glBindBuffer(GL_ARRAY_BUFFER, glCBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(textCoordinates), textCoordinates.data(), GL_STATIC_DRAW);
}

GLuint SpriteSheet::GetTextureBufferID() {
    return textureBufferID;
}

void SpriteSheet::SetTile(std::string tileName) {
    if (tileSheetInfo.mapping.count(tileName)) {
        int maxIndex = columnCount * rowCount - 1;
        if (++currentIndex > maxIndex - skipLastFrames) {
            currentIndex = 0;
        }
        ReloadTextCoordinates();
    } else {
        throw std::
    }
}

void Tile::ReloadTextCoordinates() {
    int maxIndex = columnCount * rowCount - 1;
    float columnPercent = 1.0f / ((float)columnCount); //1/2 = .5%, so 0%/50% or 0/1 out of 2
    int columnIndex = currentIndex % columnCount; //if index == 3, 3%2=1, index 3 is 2nd column
    float startX = (float)columnIndex * (float)columnPercent; //1 * 0.5 = 0.5f is start
    float endX = startX + columnPercent; //0.5f + 0.5f = 1.0f
    float rowPercent = 1.0f / ((float)rowCount);
    int rowIndex = currentIndex / columnCount; //if index == 3, 3%2=1, index 3 is in 2nd row
    float startY = 1 - (float)rowIndex * (float)rowPercent; //1 - 0.5f
    float endY = startY - rowPercent;
    startY = 1 - startY;
    endY = 1 - endY;
    std::cout << "ColumnPercent: " << columnPercent << " RowPercent: " << rowPercent << std::endl;
    std::cout << currentIndex << " x{" << startX << " : " << endX << "} y{" << startY << " : " << endY << "}" << std::endl;
    textCoordinates = {
        endX, startY,  //Top Right
        endX, endY,    //Bottom Right
        startX, endY,  //Bottom Left
        startX, startY //Top Left
  };
}*/