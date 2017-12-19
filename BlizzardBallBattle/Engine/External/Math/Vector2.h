#pragma once
#define _USE_MATH_DEFINES

#include <cmath>

class Vector2 {
private:
	float _x;
	float _y;
	float _magnitude;
	float _rotation; //0 is right facing not implemented 
public:
	Vector2(float x, float y);
	void normalize();

	//__declspec (property (get = getMagnitude)) float magnitude;
	float getMagnitude();
	
	//__declspec (property (put = setX, get = getX)) float x;
	void setX(float value);
	float getX();

	//__declspec (property (put = setY, get = getY)) float y;
	void setY(float value);
	float getY();

	void rotateVector(float radians);

	Vector2* operator*(float value);
	Vector2* operator/(float value);
	Vector2* operator-(Vector2 v);
	Vector2* operator-();
	Vector2* operator+(Vector2 v);
};