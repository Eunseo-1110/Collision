#pragma once
#include "MyWindows.h"
#include "Vector3D.h"
#include "Triangle.h"

//struct BoundCircle
//{
//	Vector3D center;
//	float radius;
//	COLORREF color;
//};

//BoundCircle CreateCircleCollider(Triangle _triangle)
//{
//	BoundCircle tempBB;
//
//	tempBB.center = _triangle.GetCenter();
//
//	float tempRadius = isMax(_triangle.GetTiangleA().GetLength(), _triangle.GetTiangleB().GetLength());
//	tempRadius = isMax(tempRadius, _triangle.GetTiangleC().GetLength());
//	tempBB.radius = tempRadius;
//
//	tempBB.color = RGB(0, 255, 0);
//
//	return tempBB;
//}
//
//void DrawCircle(HWND _hwnd,HDC _hdc, COLORREF _color, BoundCircle _bbCircle)
//{
//	_hdc = GetDC(_hwnd);
//
//	HBRUSH MyBrush, OldBrush;
//
//	MyBrush = CreateSolidBrush(_bbCircle.color);
//	OldBrush = (HBRUSH)SelectObject(_hdc, MyBrush);
//
//	Ellipse(_hdc, _bbCircle.center.GetX() - _bbCircle.radius, _bbCircle.center.GetY() - _bbCircle.radius,
//		_bbCircle.center.GetX() + _bbCircle.radius, _bbCircle.center.GetY() - _bbCircle.radius);
//
//	SelectObject(_hdc, OldBrush);
//	DeleteObject(MyBrush);
//
//	ReleaseDC(_hwnd, _hdc);
//}
//
//void DrawCircle(HDC _hdc, BoundCircle _bbCircle)
//{
//	HBRUSH MyBrush, OldBrush;
//
//	MyBrush = CreateSolidBrush(_bbCircle.color);
//	OldBrush = (HBRUSH)SelectObject(_hdc, MyBrush);
//
//	Ellipse(_hdc, _bbCircle.center.GetX() - _bbCircle.radius, _bbCircle.center.GetUnitY() - _bbCircle.radius,
//		_bbCircle.center.GetX() + _bbCircle.radius, _bbCircle.center.GetUnitY() - _bbCircle.radius);
//
//	SelectObject(_hdc, OldBrush);
//	DeleteObject(MyBrush);
//}
//
//bool Collision(BoundCircle _bbCircle1, BoundCircle _bbCircle2)
//{
//	Vector3D tempvec = _bbCircle1.center + _bbCircle2.center;
//
//	if (tempvec.GetLength() > _bbCircle1.radius)
//	{
//		return true;
//	}
//	if (tempvec.GetLength() > _bbCircle2.radius)
//	{
//		return true;
//	}
//
//	return false;
//}

float isMax(float _num1, float _num2)
{
	if (_num1 >= _num2)
	{
		return _num1;
	}
	return _num2;
}

class CircleCollider
{
	Vector3D center;
	float radius;
	COLORREF color;
public:
	CircleCollider() {}
	CircleCollider(const Triangle _triangle) { CreateCircleCollider(_triangle); }
	CircleCollider(const CircleCollider& _collider)
	{
		center = _collider.center;
		radius = _collider.radius;
		color = _collider.color;
	}

	COLORREF GetColor() { return this->color; }
	void SetColor(const COLORREF _color) { this->color = _color; }

	void CreateCircleCollider(Triangle _triangle);
	bool Collision(CircleCollider _bbCircle);
	void DrawCircle(HWND _hwnd, HDC _hdc);
	void DrawCircle(HDC _hdc);
};

inline void CircleCollider::CreateCircleCollider(Triangle _triangle)
{
	center = _triangle.GetCenter();

	float lengthA = abs(center.GetLength() - _triangle.GetTiangleA().GetLength());
	float lengthB = abs(center.GetLength() - _triangle.GetTiangleB().GetLength());
	float lengthC = abs(center.GetLength() - _triangle.GetTiangleC().GetLength());

	float tempRadius = isMax(lengthA, lengthB);
	tempRadius = isMax(tempRadius, lengthC);
	radius = tempRadius;

	//Green
	color = COLORREF(RGB(0, 255, 0));
}

inline bool CircleCollider::Collision(CircleCollider _bbCircle)
{
	Vector3D tmpcenter = center;
	tmpcenter = _bbCircle.center - tmpcenter ;

	float length = tmpcenter.GetLength();

	if (length <= this->radius + _bbCircle.radius)
	{
		return true;
	}

	return false;
}

inline void CircleCollider::DrawCircle(HWND _hwnd, HDC _hdc)
{
	_hdc = GetDC(_hwnd);
	
	HBRUSH MyBrush, OldBrush;
	
	MyBrush = CreateSolidBrush(this->color);
	OldBrush = (HBRUSH)SelectObject(_hdc, MyBrush);
	
	float r = this->radius;
	Ellipse(_hdc, this->center.GetX() - r, this->center.GetY() - r,
		this->center.GetX() + r, this->center.GetY() - r);
	
	SelectObject(_hdc, OldBrush);
	DeleteObject(MyBrush);
	
	ReleaseDC(_hwnd, _hdc);
}

inline void CircleCollider::DrawCircle(HDC _hdc)
{
	HPEN MyPen, OldPen;
	
	MyPen = CreatePen(PS_SOLID, 1, this->color);
	OldPen = (HPEN)SelectObject(_hdc, MyPen);
	
	float r = this->radius;
	Ellipse(_hdc, this->center.GetX() - r, this->center.GetY() - r,
		this->center.GetX() + r, this->center.GetY() + r);

	SelectObject(_hdc, OldPen);
	DeleteObject(MyPen);
}
