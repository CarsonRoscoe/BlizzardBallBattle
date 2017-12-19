#include "HelperFunctions.h"
#include <stdlib.h>
#include <time.h>

std::string BuildPath(char* fileName) {
#ifdef __APPLE__
  return std::string("./BlizzardBallBattle/") + fileName;
#elif defined _WIN32 || defined _WIN64
  return fileName;
#endif 
}

//      5
//-15   0   15
//     -5

//     1
//-1   0    1
//     -1

void worldPositionToOpenGLPosition(float* x, float* y) {
  float glX = *x / GAME_WIDTH * 2.0;     //For worldX of -5/0/5, glX is -0.5/0/5. Adjust by scale.
  float glY = *y / getGameHeight() * 2.0 / ASPECT_RATIO; //For worldY of -3.5/0/5, glY is -0.5/0/5. Adjust by scale

  *x = glX;
  *y = glY;
}

void openGLPositionToWorldPosition(float* x, float* y) {

}

float getGameLeftX() {
  return - GAME_WIDTH / 2.0;
}

float getGameRightX() {
  return GAME_WIDTH / 2.0;
}
float getGameTopY() {
  return getGameHeight() / 2.0;
}
float getGameBottomY() {
  return -getGameHeight() / 2.0;
}

float getGameHeight() {
  return GAME_WIDTH / ASPECT_RATIO;
}

float getGameWidth() {
  return GAME_WIDTH;
}

float getUnitSize() {
  return SCREEN_WIDTH / GAME_WIDTH;
}

float getFullBarSize() {
  return SCREEN_HEIGHT - (((int)getGameHeight()) * getUnitSize());
}

float randomFloatInRange(float min, float max) {
	float random = ((float)rand()) / (float)RAND_MAX;
	float diff = max - min;
	float r = random * diff;
	return min + r;
}