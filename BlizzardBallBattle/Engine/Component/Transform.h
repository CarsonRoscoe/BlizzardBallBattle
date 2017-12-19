#pragma once

#include <GL/glew.h>
#include <math.h>
#include "HelperFunctions.h"
#include <iostream>
#include "Component.h"

class Transform : public Component {
private:
  float x;
  float y;
  float z;
  float rotation;
  float scale;
  GLfloat* values;

public:
  Transform(GameObject* gameObject);
  ~Transform();
  void addTranslation(float xToAdd, float yToAdd);

  void OnStart() {};
  void OnUpdate(int ticks) {};
  void OnEnd() {};

  void addX(float xToAdd);
  void addY(float yToAdd);
  void addZ(float zToAdd);
  void setX(float newX);
  float getX();

  //__declspec (property (put = setY, get = getY)) float y;
  void setY(float newY);

  void setZ(float zToSet);
  void setPosition(float newX, float newY);
  void setPosition(float newX, float newY, float newZ);
  void addRotation(float byDegrees);
  void addScale(float scaleToAdd);
  void setScale(float newScale);
  float getY();
  float getZ();
  float getScale();

  //__declspec (property (put = setRotation, get = getRotation)) float rotation;
  void setRotation(float newAngle);
  float getRotation();
  operator GLfloat*();
};