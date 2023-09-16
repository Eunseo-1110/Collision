#pragma once
#include <windows.h>
#include <list>
#include <iostream>
#include "MyPoint.h"
#include "Vector3D.h"
using namespace std;

#pragma region DrawPix

//좌표출력 검은색 기본
void SetPix(HDC phdc, HWND phWnd, list<Point> p_poslist)
{
	phdc = GetDC(phWnd);

	list<Point>::iterator iter;
	for (iter = p_poslist.begin(); iter != p_poslist.end(); ++iter)
	{
		Point ps = *iter;
		SetPixel(phdc, ps.x, ps.y, RGB(0, 0, 0));
	}
	ReleaseDC(phWnd, phdc);
}

//좌표출력 색 지정
void SetPix(HDC phdc, HWND phWnd, list<Point> p_poslist, COLORREF rgb)
{
	phdc = GetDC(phWnd);

	list<Point>::iterator iter;
	for (iter = p_poslist.begin(); iter != p_poslist.end(); ++iter)
	{
		Point ps = *iter;
		SetPixel(phdc, ps.x, ps.y, rgb);
	}
	ReleaseDC(phWnd, phdc);
}

//double buffer only
void SetPix(HDC phdc, list<Point> p_poslist)
{
	list<Point>::iterator iter;
	for (iter = p_poslist.begin(); iter != p_poslist.end(); ++iter)
	{
		Point ps = *iter;
		SetPixel(phdc, ps.x, ps.y, RGB(0, 0, 0));
	}
}

//좌표출력 색 지정, double buffer only
void SetPix(HDC phdc, list<Point> p_poslist, COLORREF rgb)
{
	list<Point>::iterator iter;
	for (iter = p_poslist.begin(); iter != p_poslist.end(); ++iter)
	{
		Point ps = *iter;
		SetPixel(phdc, ps.x, ps.y, rgb);
	}
}

#pragma endregion

#pragma region TriangleETC

void DrawTriangle(Point ver[3], HWND& hWnd, HDC& hdc)
{
	list<Point> tmplist1;
	list<Point> tmplist2;
	list<Point> tmplist3;

	GetLine(ver[0].x, ver[1].x, ver[0].y, ver[1].y, &tmplist1);
	GetLine(ver[1].x, ver[2].x, ver[1].y, ver[2].y, &tmplist2);
	GetLine(ver[2].x, ver[0].x, ver[2].y, ver[0].y, &tmplist3);

	SetPix(hdc, hWnd, tmplist1);
	SetPix(hdc, hWnd, tmplist2);
	SetPix(hdc, hWnd, tmplist3);
}

void DrawTriangle(Vector3D ver[3], HWND& hWnd, HDC& hdc)
{
	list<Point> tmplist1;
	list<Point> tmplist2;
	list<Point> tmplist3;

	GetLine(ver[0].GetX(), ver[1].GetX(), ver[0].GetY(), ver[1].GetY(), &tmplist1);
	GetLine(ver[1].GetX(), ver[2].GetX(), ver[1].GetY(), ver[2].GetY(), &tmplist2);
	GetLine(ver[2].GetX(), ver[0].GetX(), ver[2].GetY(), ver[0].GetY(), &tmplist3);

	SetPix(hdc, hWnd, tmplist1);
	SetPix(hdc, hWnd, tmplist2);
	SetPix(hdc, hWnd, tmplist3);
}

void MoveTriangleList(Point _pos[2], list<Point>* posList)
{
	float speed = 10;

	GetLine(_pos[0], _pos[1], posList, speed);
}
#pragma endregion

void DrawBitmap(HDC hdc, int x, int y, HBITMAP hBit)
{
	HDC MemDC;
	HBITMAP OldBitmap;
	int bx, by;
	BITMAP bit;

	MemDC = CreateCompatibleDC(hdc);
	OldBitmap = (HBITMAP)SelectObject(MemDC, hBit);

	GetObject(hBit, sizeof(BITMAP), &bit);
	bx = bit.bmWidth;
	by = bit.bmHeight;

	BitBlt(hdc, x, y, bx, by, MemDC, 0, 0, SRCCOPY);
	SelectObject(MemDC, OldBitmap);
	DeleteDC(MemDC);
}



#pragma endregion