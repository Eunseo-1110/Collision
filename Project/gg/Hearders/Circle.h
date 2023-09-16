#pragma once
#include <iostream>
#include "MyPoint.h"
#include <list>
using namespace std;

#pragma region Circle

//원 클래스
class Circle
{
	Point pos[10];
	int radius;
	int size;
public:
	Circle() { radius = 10; size = 0; }

	void SetXY(float p_x, float p_y)
	{
		Point tmp;
		pos[size].x = p_x;
		pos[size].y = p_y;
		++size;
	}
	void GetPos(Point** p_arr)
	{
		*p_arr = pos;
	}
	int GetSize() { return size; }

	void SetRadius(int p_r) { radius = p_r; }
	int GetRadius() { return radius; }
};

//원생성
void GetCircle(float A, float B, float rad, list<Point>* p_poslist)
{
	float x, y;
	Point pos;

	for (x = -rad; x <= rad; x++)
	{
		y = sqrt(float(rad * rad - x * x));

		pos.x = x + A;
		pos.y = y + B;
		p_poslist->push_back(pos);
		pos.y = -y + B;
		p_poslist->push_back(pos);
	}
}

#pragma endregion