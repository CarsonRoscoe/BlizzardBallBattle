#include "Vector2.h"

Vector2::Vector2(float x, float y): _x(x), _y(y) {
}

void Vector2::setX(float value) {
	_x = value;
}

float Vector2::getX() {
	return _x;
}

void Vector2::setY(float value) {
	_y = value;
}

float Vector2::getY() {
	return _y;
}

float Vector2::getMagnitude() {
	_magnitude = sqrt(pow(_x, 2) + pow(_y, 2));
	return _magnitude;
}

void Vector2::normalize() {
	getMagnitude();
	_x /= _magnitude;
	_y /= _magnitude;
}


//OPERATORS

Vector2* Vector2::operator*(float value)
{
	_x *= value;
	_y *= value;
	return this;
}

Vector2* Vector2::operator/(float value)
{
	_x /= value;
	_y /= value;
	return this;
}

Vector2* Vector2::operator+(Vector2 v)
{
	_x += v.getX();
	_y += v.getY();
	return this;
}

Vector2* Vector2::operator-(Vector2 v)
{
	_x -= v.getX();
	_y -= v.getY();
	return this;
}

Vector2* Vector2::operator-()
{
	_x = -_x;
	_y = -_y;
	return this;
}

void Vector2::rotateVector(float radians) {
	float tempCos = cos(radians);
	float tempSin = sin(radians);
	_x = tempCos * _x - tempSin * _y;
	_y = tempSin * _x + tempCos * _y;
}

/*ignore but dont delete

float Vector::getRotation() {
	if (_x > 0 && _y > 0) {
		_rotation = atan(_y / _x);
	}
	else if (_x < 0 && _y > 0) {
		_rotation = atan(-_x / _y) + M_PI / 2;
	}
	else if (_x < 0 && _y < 0){
		_rotation = atan(_y / _x) + M_PI;
	}
	else if (_x > 0 && _y < 0) {
		_rotation = atan(_x / -_y) + 3 * M_PI / 2;
	}
	else {
		_rotation = 0;
	}
	return _rotation;
}
*/