#pragma once
#include <windows.h>
#include <list>
#include "MyPoint.h"
#include <iostream>
using namespace std;

#pragma region Converting

//월드좌표 변환, float
void ConvertingWorld(float& _x, float& _y, RECT rect)
{
	float posx = _x;
	float posy = _y;

	int CenterX = rect.right / 2;
	int CenterY = rect.bottom / 2;

	posx = CenterX + posx;
	posy = CenterY - posy;

	_x = posx;
	_y = posy;
}

//월드좌표리스트 변환
void ConvertingWorld(list<Point>* p_arr, RECT rect)
{
	list<Point> pos;
	list<Point>::iterator iter;

	int CenterX = rect.right / 2;
	int CenterY = rect.bottom / 2;

	for (iter = p_arr->begin(); iter != p_arr->end(); ++iter)
	{
		Point tmp = *iter;
		tmp.x = CenterX + tmp.x;
		tmp.y = CenterY - tmp.y;
		pos.push_back(tmp);

	}

	p_arr->clear();
	p_arr->resize(pos.size());
	copy(pos.begin(), pos.end(), p_arr->begin());
}

//월드좌표 변환, Point
void ConvertingWorld(Point* p_arr, RECT rect)
{
	Point* pos = p_arr;

	int CenterX = rect.right / 2;
	int CenterY = rect.bottom / 2;

	pos->x = CenterX + pos->x;
	pos->y = CenterY - pos->y;

	p_arr = pos;
}

//로컬좌표 변환
void ConvertingLocal(Point* p_arr, RECT rect)
{
	Point pos;

	int CenterX = rect.right / 2;
	int CenterY = rect.bottom / 2;

	pos.x = p_arr->x - CenterX;
	pos.y = CenterY - p_arr->y;

	p_arr->x = pos.x;
	p_arr->y = pos.y;
}

#pragma endregion

#pragma region Coordinate System

//x,y 좌표축 생성
void SetPoint(int stpos, int mxpos, list<Point>* listX, list<Point>* listY)
{
	list<Point> pos;
	Point tmp;

	for (int i = stpos; i < mxpos; i++)
	{
		tmp.y = 0;
		tmp.x = i;
		listX->push_back(tmp);
	}

	for (int i = stpos; i < mxpos; i++)
	{
		tmp.x = 0;
		tmp.y = i;
		listY->push_back(tmp);
	}
}

#pragma endregion