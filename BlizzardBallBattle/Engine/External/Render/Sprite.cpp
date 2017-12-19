#include "Sprite.h"

Sprite::Sprite(GLuint textureBufferID) {
    this->textureBufferID = textureBufferID;
    textCoordinates = {
        1.0f, 1.0f,  //Top Right
        1.0f, 0.0f,  //Bottom Right
        0.0f, 0.0f,  //Bottom Left
        0.0f, 1.0f   //Top Left
  };
}

Sprite::~Sprite() {

}

void Sprite::BindTextCoordinates(GLuint glCBO) {
    glBindBuffer(GL_ARRAY_BUFFER, glCBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(textCoordinates), textCoordinates.data(), GL_STATIC_DRAW);
}

std::array<GLfloat, 8> Sprite::GetTextureCoordinates() {
    return textCoordinates;
}

GLuint Sprite::GetTextureBufferID() {
    return textureBufferID;
}