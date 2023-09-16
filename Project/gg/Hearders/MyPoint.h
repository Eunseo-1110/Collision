#pragma once

#pragma region Point

//float�� ��ǥ ����ü
typedef struct Point
{
	float x;
	float y;

	Point() { x = 0; y = 0; }

	Point(float _x, float _y)
	{
		x = _x;
		y = _y;
	}

	Point(const Point& pos)
	{
		x = pos.x;
		y = pos.y;
	}
}Point;

#pragma endregion