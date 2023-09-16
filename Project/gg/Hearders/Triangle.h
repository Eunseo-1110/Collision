#pragma once
#include "MyPoint.h"
#include "MyLine.h"
#include "MyWindows.h"
#include "Vector3D.h"
#include "MyMatrix.h"
#include <iostream>
using namespace std;

class Vertex
{
public:
	union
	{
		struct 
		{
			Vector3D _A, _B, _C;
		};
		Vector3D vertex[3];
	};

	Vertex() {}
	~Vertex() {}
};

class Triangle
{
protected:
	Vertex trianlgeVec;
	Vector3D center;

public:
	Triangle() {}
	Triangle(const Vector3D _triangle[3]);
	Triangle(const Triangle& _triangle);

	~Triangle() {}

	void SetTrianlge(const Vector3D _triangle[3]);
	void SetTrianlge(Vector3D _center);
	Vector3D& GetTiangleA();
	Vector3D& GetTiangleB();
	Vector3D& GetTiangleC();
	void GetTrianlge(Vector3D _triangle[3]);
	void GetTrianlge(Triangle& _triangle);
	Vector3D* GetTrianlge();
	void SetCenter(const Vector3D _center);
	Vector3D& GetCenter(Vector3D _triangle[3]);
	Vector3D& GetCenter();

	void Translate(Vector3D _dpos); //이동 
	void SetTriangleMulti(Matrix14 _mat14[3], Matrix4 _mat44);
	void SetRatateZ(Matrix4& mat, float theta); //Z축회전행렬세팅
	void RotateZ(float theta); //Z축회전회전
	void SetRatateX(Matrix4& mat, float theta);
	void RotateX(float theta);
	void SetRatateY(Matrix4& mat, float theta);
	void RotateY(float theta);
	void SetScale(Matrix4& mat, Vector3D scale);
	void Scale(Vector3D _scale);
	void Scale(float _scale);

	//삼각형을 그리는 함수들
	void DrawTriangle(HWND hWnd, HDC hdc); 
	void DrawTriangle(HWND hWnd, HDC hdc, COLORREF _color); //색지정
	void DrawTriangle(HDC hdc); //더블버퍼용
	void DrawTriangle(HDC hdc, COLORREF _color); //색지정, 더블버퍼용

	void operator=(const Triangle& _triangle);
};


inline Triangle::Triangle(const Vector3D _triangle[3])
{
	for (int i = 0; i < 3; i++)
	{
		trianlgeVec.vertex[i] = _triangle[i];
	}
	center = GetCenter(trianlgeVec.vertex);
}

inline Triangle::Triangle(const Triangle& _triangle)
{
	for (int i = 0; i < 3; i++)
	{
		trianlgeVec.vertex[i] = _triangle.trianlgeVec.vertex[i];
	}
	center = GetCenter(trianlgeVec.vertex);
}

inline void Triangle::SetTrianlge(const Vector3D _triangle[3])
{
	for (int i = 0; i < 3; i++)
	{
		trianlgeVec.vertex[i] = _triangle[i];
	}
	center = GetCenter(trianlgeVec.vertex);
}

inline void Triangle::SetTrianlge(Vector3D _center)
{
	trianlgeVec._A = Vector3D(_center.GetX() , _center.GetY() - 40, 0);
	trianlgeVec._B = Vector3D(_center.GetX() - 40, _center.GetY() + 30, 0);
	trianlgeVec._C = Vector3D(_center.GetX() + 40, _center.GetY() + 30, 0);
	center = GetCenter(trianlgeVec.vertex);
}

inline Vector3D& Triangle::GetTiangleA()
{
	return this->trianlgeVec._A;
}

inline Vector3D& Triangle::GetTiangleB()
{
	return this->trianlgeVec._B;
}

inline Vector3D& Triangle::GetTiangleC()
{
	return this->trianlgeVec._C;
}

inline void Triangle::GetTrianlge(Vector3D _triangle[3])
{
	for (int i = 0; i < 3; i++)
	{
		_triangle[i] = trianlgeVec.vertex[i];
	}
}

inline void Triangle::GetTrianlge(Triangle& _triangle)
{
	for (int i = 0; i < 3; i++)
	{
		_triangle.trianlgeVec.vertex[i] = trianlgeVec.vertex[i];
	}
}

inline Vector3D* Triangle::GetTrianlge()
{
	return this->trianlgeVec.vertex;
}

inline void Triangle::SetCenter(const Vector3D _center)
{
	center = _center;
}

inline Vector3D& Triangle::GetCenter(Vector3D _triangle[3])
{
	Vector3D temp;

	float xx = _triangle[0].GetX() + _triangle[1].GetX() + _triangle[2].GetX();
	float yy = _triangle[0].GetY() + _triangle[1].GetY() + _triangle[2].GetY();
	xx /= 3;
	yy /= 3;

	temp.SetX(xx);
	temp.SetY(yy);

	return temp;
}

inline Vector3D& Triangle::GetCenter()
{
	Vector3D temp;

	float xx = trianlgeVec.vertex[0].GetX() + trianlgeVec.vertex[1].GetX() + trianlgeVec.vertex[2].GetX();
	float yy = trianlgeVec.vertex[0].GetY() + trianlgeVec.vertex[1].GetY() + trianlgeVec.vertex[2].GetY();
	xx /= 3;
	yy /= 3;

	temp.SetX(xx);
	temp.SetY(yy);

	center = temp;
	return temp;
}

inline void Triangle::Translate(Vector3D _dpos)
{
	Matrix3 mat33;
	Matrix13 mat13[3];

	SetVecToMat1X3(mat13[0], trianlgeVec.vertex[0]);
	SetVecToMat1X3(mat13[1], trianlgeVec.vertex[1]);
	SetVecToMat1X3(mat13[2], trianlgeVec.vertex[2]);
	SetVecToMat3X3(mat33, _dpos);

	Matrix13 tmpmat[3];
	for (int i = 0; i < 3; i++)
	{
		tmpmat[i] = MatrixMulply(mat13[i], mat33);
	}

	for (int i = 0; i < 3; i++)
	{
		SetMat1X3ToVec(trianlgeVec.vertex[i], tmpmat[i]);
	}
}

inline void Triangle::SetTriangleMulti(Matrix14 _mat14[3], Matrix4 _mat44)
{
	for (int i = 0; i < 3; i++)
	{
		SetVecToMat1X4(_mat14[i], trianlgeVec.vertex[i]);
	}

	Matrix14 tmpmat[3];
	for (int i = 0; i < 3; i++)
	{
		tmpmat[i] = MatrixMulply(_mat14[i], _mat44);
	}

	for (int i = 0; i < 3; i++)
	{
		SetMat1X4ToVec(trianlgeVec.vertex[i], tmpmat[i]);
	}
}

inline void Triangle::SetRatateZ(Matrix4& mat, float theta)
{
	mat._11 = cos(theta);
	mat._12 = sin(theta);
	mat._21 = -sin(theta);
	mat._22 = cos(theta);
}

inline void Triangle::RotateZ(float theta)
{
	Matrix4 mat44;
	Matrix14 mat14[3];

	//원점으로 이동 (중심빼기)
	center = center * (-1);
	Translate(center);

	//회전
	SetRatateZ(mat44, theta);
	SetTriangleMulti(mat14, mat44);

	//원래 자리로 이동 (중심더하기)
	center = center * (-1);
	Translate(center);
	center = GetCenter(trianlgeVec.vertex);
}

inline void Triangle::SetRatateX(Matrix4& mat, float theta)
{
	mat._22 = cos(theta);
	mat._23 = sin(theta);
	mat._32 = -sin(theta);
	mat._33 = cos(theta);
}

inline void Triangle::RotateX(float theta)
{
	Matrix4 mat44;
	Matrix14 mat14[3];

	//원점으로 이동 (중심빼기)
	center = center * (-1);
	Translate(center);

	//회전
	SetRatateX(mat44, theta);
	SetTriangleMulti(mat14, mat44);

	//원래 자리로 이동 (중심더하기)
	center = center * (-1);
	Translate(center);
	center = GetCenter(trianlgeVec.vertex);
}

inline void Triangle::SetRatateY(Matrix4& mat, float theta)
{
	mat._11 = cos(theta);
	mat._13 = -sin(theta);
	mat._31 = sin(theta);
	mat._33 = cos(theta);
}

inline void Triangle::RotateY(float theta)
{
	Matrix4 mat44;
	Matrix14 mat14[3];

	//원점으로 이동 (중심빼기)
	center = center * (-1);
	Translate(center);

	//회전
	SetRatateY(mat44, theta);
	SetTriangleMulti(mat14, mat44);

	//원래 자리로 이동 (중심더하기)
	center = center * (-1);
	Translate(center);
	center = GetCenter(trianlgeVec.vertex);
}

inline void Triangle::SetScale(Matrix4& mat, Vector3D scale)
{
	mat._11 = scale.GetX();
	mat._22 = scale.GetY();
	mat._33 = scale.GetZ();
	mat._44 = 1;
}

inline void Triangle::Scale(Vector3D _scale)
{
	Matrix4 mat44;
	Matrix14 mat14[3];

	//원점으로 이동 (중심빼기)
	center = center * (-1);
	Translate(center);

	//회전
	SetScale(mat44, _scale);
	SetTriangleMulti(mat14, mat44);

	//원래 자리로 이동 (중심더하기)
	center = center * (-1);
	Translate(center);
	center = GetCenter(trianlgeVec.vertex);
}

inline void Triangle::Scale(float _scale)
{
	Matrix4 mat44;
	Matrix14 mat14[3];
	Vector3D scale;
	scale = Vector3D(_scale, _scale, _scale);

	//원점으로 이동 (중심빼기)
	center = center * (-1);
	Translate(center);

	//회전
	SetScale(mat44, scale);
	SetTriangleMulti(mat14, mat44);

	//원래 자리로 이동 (중심더하기)
	center = center * (-1);
	Translate(center);
	center = GetCenter(trianlgeVec.vertex);
}

inline void Triangle::DrawTriangle(HWND hWnd, HDC hdc)
{
	list<Point> tmplist1;
	list<Point> tmplist2;
	list<Point> tmplist3;

	GetLine(trianlgeVec.vertex[0].GetX(), trianlgeVec.vertex[1].GetX(), trianlgeVec.vertex[0].GetY(), trianlgeVec.vertex[1].GetY(), &tmplist1);
	GetLine(trianlgeVec.vertex[1].GetX(), trianlgeVec.vertex[2].GetX(), trianlgeVec.vertex[1].GetY(), trianlgeVec.vertex[2].GetY(), &tmplist2);
	GetLine(trianlgeVec.vertex[2].GetX(), trianlgeVec.vertex[0].GetX(), trianlgeVec.vertex[2].GetY(), trianlgeVec.vertex[0].GetY(), &tmplist3);

	SetPix(hdc, hWnd, tmplist1);
	SetPix(hdc, hWnd, tmplist2);
	SetPix(hdc, hWnd, tmplist3);
}

inline void Triangle::DrawTriangle(HDC hdc)
{
	list<Point> tmplist1;
	list<Point> tmplist2;
	list<Point> tmplist3;

	GetLine(trianlgeVec.vertex[0].GetX(), trianlgeVec.vertex[1].GetX(), trianlgeVec.vertex[0].GetY(), trianlgeVec.vertex[1].GetY(), &tmplist1);
	GetLine(trianlgeVec.vertex[1].GetX(), trianlgeVec.vertex[2].GetX(), trianlgeVec.vertex[1].GetY(), trianlgeVec.vertex[2].GetY(), &tmplist2);
	GetLine(trianlgeVec.vertex[2].GetX(), trianlgeVec.vertex[0].GetX(), trianlgeVec.vertex[2].GetY(), trianlgeVec.vertex[0].GetY(), &tmplist3);

	SetPix(hdc, tmplist1);
	SetPix(hdc, tmplist2);
	SetPix(hdc, tmplist3);
}

inline void Triangle::operator=(const Triangle& _triangle)
{
	for (int i = 0; i < 3; i++)
	{
		trianlgeVec.vertex[i] = _triangle.trianlgeVec.vertex[i];
	}
}

inline void Triangle::DrawTriangle(HWND hWnd, HDC hdc, COLORREF _color)
{
	list<Point> tmplist1;
	list<Point> tmplist2;
	list<Point> tmplist3;

	GetLine(trianlgeVec.vertex[0].GetX(), trianlgeVec.vertex[1].GetX(), trianlgeVec.vertex[0].GetY(), trianlgeVec.vertex[1].GetY(), &tmplist1);
	GetLine(trianlgeVec.vertex[1].GetX(), trianlgeVec.vertex[2].GetX(), trianlgeVec.vertex[1].GetY(), trianlgeVec.vertex[2].GetY(), &tmplist2);
	GetLine(trianlgeVec.vertex[2].GetX(), trianlgeVec.vertex[0].GetX(), trianlgeVec.vertex[2].GetY(), trianlgeVec.vertex[0].GetY(), &tmplist3);

	SetPix(hdc, hWnd, tmplist1, _color);
	SetPix(hdc, hWnd, tmplist2, _color);
	SetPix(hdc, hWnd, tmplist3, _color);
}

inline void Triangle::DrawTriangle(HDC hdc, COLORREF _color)
{
	list<Point> tmplist1;
	list<Point> tmplist2;
	list<Point> tmplist3;

	GetLine(trianlgeVec.vertex[0].GetX(), trianlgeVec.vertex[1].GetX(), trianlgeVec.vertex[0].GetY(), trianlgeVec.vertex[1].GetY(), &tmplist1);
	GetLine(trianlgeVec.vertex[1].GetX(), trianlgeVec.vertex[2].GetX(), trianlgeVec.vertex[1].GetY(), trianlgeVec.vertex[2].GetY(), &tmplist2);
	GetLine(trianlgeVec.vertex[2].GetX(), trianlgeVec.vertex[0].GetX(), trianlgeVec.vertex[2].GetY(), trianlgeVec.vertex[0].GetY(), &tmplist3);

	SetPix(hdc, tmplist1, _color);
	SetPix(hdc, tmplist2, _color);
	SetPix(hdc, tmplist3, _color);
}