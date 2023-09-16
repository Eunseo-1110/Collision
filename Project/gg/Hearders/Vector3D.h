#pragma once
#include "MyPoint.h"
#include <math.h>
#include <iostream>

class Vector3D
{
	float x;
	float y;
	float z;
	float w;
	float unitx;
	float unity;
	float unitz;

	float length;
	float lengPow;

public:
	Vector3D();
	Vector3D(float _x, float _y, float _z);
	Vector3D(Vector3D& _vec);

	~Vector3D() {};

	void SetX(float _x);
	void SetY(float _y);
	void SetZ(float _z);
	void SetXYZ(float _x, float _y, float _z);

	float GetX();
	float GetY();
	float GetZ();

	float GetLengthPos();
	float GetLength();

	float GetUnitX();
	float GetUnitY();
	float GetUnitZ();

	void operator=(const Vector3D& vec2);
	bool operator ==(const Vector3D& vec2);
	Vector3D& operator+(const Vector3D& vec2);
	Vector3D& operator-(const Vector3D& vec2);
	Vector3D& operator*(const float scalar);
	void Normalrize();
	float DotProduct(const Vector3D& vec);
	float GetCosThe(const Vector3D& vec);
	Vector3D& GetCrossProduct(const Vector3D& vec);
};

inline Vector3D::Vector3D()
{
	x = 0, y = 0; z = 0; w = 1;
	unitx = 0; unity = 0; unitz = 0;
	length = 0; lengPow = 0;
}

inline Vector3D::Vector3D(float _x, float _y, float _z)
{
	x = _x, y = _y; z = _z; w = 1;
	unitx = 0; unity = 0; unitz = 0;
	length = 0; lengPow = 0;
}

inline Vector3D::Vector3D(Vector3D& _vec)
{
	x = _vec.x, y = _vec.y; z = _vec.z; w = 1;
	unitx = 0; unity = 0; unitz = 0;
	length = 0; lengPow = 0;
}

inline void Vector3D::SetX(float _x)
{
	x = _x;
}

inline void Vector3D::SetY(float _y)
{
	y = _y;
}

inline void Vector3D::SetZ(float _z)
{
	z = _z;
}

inline void Vector3D::SetXYZ(float _x, float _y, float _z)
{
	x = _x;  y = _y;  z = _z;
}

inline float Vector3D::GetX()
{
	return x;
}

inline float Vector3D::GetY()
{
	return y;
}

inline float Vector3D::GetZ()
{
	return z;
}

inline float Vector3D::GetLengthPos()
{
	lengPow = pow(x, 2) + pow(y, 2) + pow(z, 2);
	return lengPow;
}

inline float Vector3D::GetLength()
{
	length = sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
	return length;
}

inline float Vector3D::GetUnitX()
{
	if (unitx == 0)
	{
		Normalrize();
	}
	return unitx;
}

inline float Vector3D::GetUnitY()
{
	if (unity == 0)
	{
		Normalrize();
	}
	return unity;
}

inline float Vector3D::GetUnitZ()
{
	if (unitz == 0)
	{
		Normalrize();
	}
	return unitz;
}

inline void Vector3D::operator=(const Vector3D& vec2)
{
	x = vec2.x, y = vec2.y; z = vec2.z; w = 1;
}

inline bool Vector3D::operator==(const Vector3D& vec2)
{
	if (this->x == vec2.x && this->y == vec2.y && this->z == vec2.z)
		return true;
	else
		return false;
}

inline Vector3D& Vector3D::operator+(const Vector3D& vec2)
{
	Vector3D tmpvec;
	tmpvec.SetX(this->x + vec2.x);
	tmpvec.SetY(this->y + vec2.y);
	tmpvec.SetZ(this->z + vec2.z);
	return tmpvec;
}

inline Vector3D& Vector3D::operator-(const Vector3D& vec2)
{
	Vector3D tmpvec;
	tmpvec.SetX(this->x - vec2.x);
	tmpvec.SetY(this->y - vec2.y);
	tmpvec.SetZ(this->z - vec2.z);
	return tmpvec;
}

inline Vector3D& Vector3D::operator*(const float scalar)
{
	Vector3D tmpvec;
	tmpvec.SetX(this->x * scalar);
	tmpvec.SetY(this->y * scalar);
	tmpvec.SetZ(this->z * scalar);
	return tmpvec;
}

inline void Vector3D::Normalrize()
{
	float len = this->GetLength();
	unitx = this->x / len;
	unity = this->y / len;
	unitz = this->z / len;
}

inline float Vector3D::DotProduct(const Vector3D& vec)
{
	float xx = this->x * vec.x;
	float yy = this->y * vec.y;
	float zz = this->z * vec.z;
	float dot = xx + yy + zz;
	return dot;
}

inline float Vector3D::GetCosThe(const Vector3D& vec)
{
	float dot = DotProduct(vec);
	float costheta = dot / (this->GetLength() * vec.length);
	return costheta;
}

inline Vector3D& Vector3D::GetCrossProduct(const Vector3D& vec)
{
	Vector3D temp;
	temp.SetX((this->GetY() * vec.z) - (this->GetZ() * vec.y));
	temp.SetY((this->GetZ() * vec.x) - (this->GetX() * vec.z));
	temp.SetZ((this->GetX() * vec.y) - (this->GetY() * vec.x));
	return temp;
}
