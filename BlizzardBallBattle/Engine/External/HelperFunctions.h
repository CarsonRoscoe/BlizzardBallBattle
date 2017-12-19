#pragma once

#include <string>
#include "SharedConstants.h"

std::string BuildPath(char* fileName);

//Pass in the reference to x/y floats that contain the current world position, it will update the variables to their GL positions
void worldPositionToOpenGLPosition(float* x, float* y);

//Pass in the reference to x/y floats that contain the current GL position, it will update the variables to their World positions
void openGLPositionToWorldPosition(float* x, float* y);

float getGameHeight();
float getGameWidth();
float getGameLeftX();
float getGameRightX();
float getGameTopY();
float getGameBottomY();
float getUnitSize();
float getFullBarSize();
float randomFloatInRange(float min, float max);