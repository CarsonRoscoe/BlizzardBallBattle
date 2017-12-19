#include "Transform.h"
#include <iostream>

Transform::operator GLfloat*() {
  if (values == nullptr) {
    values = new GLfloat[16]{
      1, 0, 0, 0,
      0, 1, 0, 0,
      0, 0, 1, 0,
      0, 0, 0, 1
    };
  } else if (values == NULL) {
    return nullptr;
  }


  float scaleRotCos = scale / GAME_WIDTH * 2.0 * cos(rotation * 3.14159 / 180.0);
  float scaleRotSin = scale / GAME_WIDTH * 2.0 * sin(rotation * 3.14159 / 180.0);

  float glX = x; //x = 5
  float glY = y; //y = 5

  worldPositionToOpenGLPosition(&glX, &glY);

  values[0] = scaleRotCos;
  values[1] = -scaleRotSin;
  values[4] = scaleRotSin;
  values[5] = scaleRotCos;
  values[12] = glX;
  values[13] = glY;

  return values;
}

Transform::Transform(GameObject* gameObject) : Component(gameObject) {
  scale = 1.0f;
  x = 0.0f;
  y = 0.0f;
  rotation = 0.0f;
  values = nullptr;
}

Transform::~Transform() {
  if (values != nullptr && values != NULL) {
    delete values;
    values = NULL;
  }
}

void Transform::addTranslation(float xToAdd, float yToAdd) {
  x += xToAdd;
  y += yToAdd;
}

void Transform::setPosition(float newX, float newY) {
  x = newX;
  y = newY;
}

void Transform::setPosition(float newX, float newY, float newZ) {

  x = newX;
  y = newY;
  z = newZ;
}

void Transform::addX(float xToAdd) {
  x += xToAdd;
}

void Transform::addY(float yToAdd) {
  y += yToAdd;
}

void Transform::addZ(float zToAdd) {
  z += zToAdd;
}

void Transform::setX(float newX) {
  x = newX;
}

void Transform::setY(float newY) {

  y = newY;
}

void Transform::setZ(float newZ) {
  z = newZ;
}

void Transform::addRotation(float byDegrees) {
  rotation += byDegrees;
}

void Transform::setRotation(float newAngle) {
  rotation = newAngle;
}

void Transform::setScale(float newScale) {
  scale = newScale;
}

float Transform::getX() {
  return x;
}

float Transform::getY() {
  return y;
}

float Transform::getZ() {
  return z;
}

float Transform::getRotation() {
  return rotation;
}

float Transform::getScale() {
  return scale;
}

void Transform::addScale(float toAdd) {
	scale += toAdd;
}