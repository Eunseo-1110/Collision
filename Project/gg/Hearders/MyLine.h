#pragma once
#include <list>
#include <iostream>
#include "MyPoint.h"
#include "Vector3D.h"
using namespace std;

#pragma region Line

//이동단위 넘겨줌
Vector3D GetDPos(Vector3D vec1, Vector3D vec2)
{
	Vector3D tmpPos;

	float x1 = vec1.GetX();
	float x2 = vec2.GetX();
	float y1 = vec1.GetY();
	float y2 = vec2.GetY();

	float dx, dy;
	float value;

	dx = x2 - x1;
	dy = y2 - y1;

	if (abs(dx) == 0 && abs(dy) == 0)
	{
		return tmpPos;
	}

	value = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
	dx = dx / value;
	dy = dy / value;

	tmpPos.SetXYZ(dx, dy, 0);
	return tmpPos;
}

//직선좌표 생성
void GetLine(float A, float B, float C, list<Point>* p_poslist)
{
	list<Point> pos;

	if (B == 0)
	{
		return;
	}

	list<Point>::iterator iter;
	for (iter = p_poslist->begin(); iter != p_poslist->end(); ++iter)
	{
		Point ps = *iter;
		ps.y = (C / B) - ((A / B) * ps.x);
		pos.push_back(ps);
	}
	p_poslist->clear();
	p_poslist->resize(pos.size());
	copy(pos.begin(), pos.end(), p_poslist->begin());
}

//좌표1에서 좌표2까지의 직선 생성 float
void GetLine(float x1, float x2, float y1, float y2, list<Point>* p_list)
{
	float dx, dy;
	float value;

	if (x2 < x1)
	{
		float temp = x1;
		x1 = x2;
		x2 = temp;

		temp = y1;
		y1 = y2;
		y2 = temp;
	}

	dx = x2 - x1;
	dy = y2 - y1;

	if (abs(dx) == 0 && abs(dy) == 0)
	{
		return;
	}

	value = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
	dx = dx / value;
	dy = dy / value;

	Point tmppos;
	tmppos.x = x1, tmppos.y = y1;

	while (true)
	{
		p_list->push_back(tmppos);

		tmppos.x += dx;
		tmppos.y += dy;

		if (tmppos.x >= x2)
			break;
	}
}

//좌표1에서 좌표2까지의 직선 생성 Point
void GetLine(Point pos1, Point pos2, list<Point>* p_list)
{
	Point dpos;
	float value;


	if (pos2.x < pos1.x)
	{
		float temp = pos1.x;
		pos1.x = pos2.x;
		pos2.x = temp;

		temp = pos1.y;
		pos1.y = pos2.y;
		pos2.y = temp;
	}

	dpos.x = pos2.x - pos1.x;
	dpos.y = pos2.y - pos1.y;

	if (abs(dpos.x) == 0 && abs(dpos.y) == 0)
	{
		return;
	}

	value = abs(dpos.x) > abs(dpos.y) ? abs(dpos.x) : abs(dpos.y);
	dpos.x = dpos.x / value;
	dpos.y = dpos.y / value;

	Point tmppos;
	tmppos.x = pos1.x, tmppos.y = pos1.y;

	p_list->clear();
	while (true)
	{
		p_list->push_back(tmppos);

		tmppos.x += dpos.x;
		tmppos.y += dpos.y;

		if (tmppos.x >= pos2.x)
			break;
	}
}

//좌표1에서 좌표2까지의 직선 생성, 망한코드
void GetLine(Point pos1, Point pos2, list<Point>* p_list, float speed)
{
	Point dpos;

	if (pos2.x < pos1.x)
	{
		float temp = pos1.x;
		pos1.x = pos2.x;
		pos2.x = temp;

		temp = pos1.y;
		pos1.y = pos2.y;
		pos2.y = temp;
	}

	dpos.x = pos2.x - pos1.x;
	dpos.y = pos2.y - pos1.y;

	if (abs(dpos.x) == 0 && abs(dpos.y) == 0)
	{
		return;
	}

	dpos.x = dpos.x / speed;
	dpos.y = dpos.y / speed;

	Point tmppos;
	tmppos.x = pos1.x, tmppos.y = pos1.y;

	p_list->clear();
	while (true)
	{
		p_list->push_back(tmppos);

		tmppos.x += dpos.x;
		tmppos.y += dpos.y;

		if (tmppos.x >= pos2.x)
			break;
	}
}

#pragma endregion