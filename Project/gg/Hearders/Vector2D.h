#pragma once
#include "MyPoint.h"
#include <math.h>
#include <iostream>

class Vector2D
{
	float x;
	float y;
	float w;
	float unitx;
	float unity;

	float length;
	float lengPow;

public:
	Vector2D();
	Vector2D(float _x, float _y);
	Vector2D(Vector2D& _vec);

	~Vector2D() {};

	void SetX(float _x);
	void SetY(float _y);
	void SetXY(float _x, float _y);
	void SetXY(Point pos);

	float GetX();
	float GetY();
	void GetXY(float& _x, float& _y);
	Point GetXY();

	float GetLengthPow();
	float GetLength();

	float GetUnitX();
	float GetUnitY();

	bool operator ==(const Vector2D& vec2);
	Vector2D& operator+(const Vector2D& vec2);
	Vector2D& operator-(const Vector2D& vec2);
	Vector2D& operator*(const float scalar);
	void Normalrize();
	float DotProduct(const Vector2D& vec);
	float GetCosThe(const Vector2D& vec);
};

inline Vector2D::Vector2D()
{
	x = 0, y = 0; w = 1;
	unitx = 0; unity = 0;
	length = 0; lengPow = 0;
}

inline Vector2D::Vector2D(float _x, float _y)
{
	x = _x, y = _y; w = 1;
	unitx = 0; unity = 0;
	length = 0; lengPow = 0;
}

inline Vector2D::Vector2D(Vector2D& _vec)
{
	x = _vec.x, y = _vec.y; w = 1;
	unitx = 0; unity = 0;
	length = 0; lengPow = 0;
}

inline void Vector2D::SetX(float _x)
{
	x = _x;
}

inline void Vector2D::SetY(float _y)
{
	y = _y;
}

inline void Vector2D::SetXY(float _x, float _y)
{
	x = _x;  y = _y;
}

inline void Vector2D::SetXY(Point pos)
{
	x = pos.x;  y = pos.y;
}

inline float Vector2D::GetX()
{
	return x;
}

inline float Vector2D::GetY()
{
	return y;
}

inline void Vector2D::GetXY(float& _x, float& _y)
{
	_x = x;
	_y = y;
}

inline Point Vector2D::GetXY()
{
	Point tmp;
	tmp.x = this->x;
	tmp.y = this->y;
	return tmp;
}

inline float Vector2D::GetLengthPow()
{
	lengPow = pow(x, 2) + pow(y, 2);
	return lengPow;
}

inline float Vector2D::GetLength()
{
	length = sqrt(pow(x, 2) + pow(y, 2));
	return length;
}

inline float Vector2D::GetUnitX()
{
	if (unitx == 0)
	{
		Normalrize();
	}
	return unitx;
}

inline float Vector2D::GetUnitY()
{
	if (unity == 0)
	{
		Normalrize();
	}
	return unity;
}

inline bool Vector2D::operator==(const Vector2D& vec2)
{
	if (this->x == vec2.x && this->y == vec2.y)
		return true;
	else
		return false;
}

inline Vector2D& Vector2D::operator+(const Vector2D& vec2)
{
	Vector2D tmpvec;
	tmpvec.SetX(this->x + vec2.x);
	tmpvec.SetY(this->y + vec2.y);
	return tmpvec;
}

inline Vector2D& Vector2D::operator-(const Vector2D& vec2)
{
	Vector2D tmpvec;
	tmpvec.SetX(this->x - vec2.x);
	tmpvec.SetY(this->y - vec2.y);
	return tmpvec;
}

inline Vector2D& Vector2D::operator*(const float scalar)
{
	Vector2D tmpvec;
	tmpvec.SetX(this->x * scalar);
	tmpvec.SetY(this->y * scalar);
	return tmpvec;
}

inline void Vector2D::Normalrize()
{
	float len = this->GetLength();
	unitx = this->x / len;
	unity = this->y / len;
}

inline float Vector2D::DotProduct(const Vector2D& vec)
{
	float dot = DotProduct(vec);
	float costheta = dot / this->GetLength() * vec.length;
	return costheta;
}

inline float Vector2D::GetCosThe(const Vector2D& vec)
{
	float xx = this->x * vec.x;
	float yy = this->y * vec.y;
	float dot = xx + yy;
	return dot;
}
