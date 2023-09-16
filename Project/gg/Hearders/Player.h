#pragma once
#include "Triangle.h"
#include "CircleCollider.h"

class Player : public Triangle
{
	CircleCollider collider;
	COLORREF color;
	Vector3D dpos;
	Vector3D NextPos; //���� ��ġ
	float speed;
public:
	Player() 
	{ 
		collider.CreateCircleCollider(this->GetTrianlge()); 
		color = RGB(0, 0, 0);
		speed = 10;
	}
	Player(const Player& _player) : Triangle(_player)
	{
		collider = _player.collider;
		color = _player.color;
		speed = 10;
	}

	CircleCollider& GetCollider() { return collider; }
	void DrawPlayer(HDC _hdc, CircleCollider _enemyCollider);
	void SetColor(COLORREF _color) { color = _color; }
	COLORREF GetColor() { return color; }

	void SetSpeed(float _sp) { speed = _sp; }
	float GetSpeed() { return speed; }

	void SetPos(Vector3D _pos)
	{
		NextPos = _pos;
		//�̵��� ���� ����
		dpos = GetDPos(GetCenter(), NextPos);
		dpos = dpos * speed;
	}

	Vector3D& GetdPos() { return dpos; }
	void PlayerTranslate();
};

inline void Player::DrawPlayer(HDC _hdc, CircleCollider _enemyCollider)
{
	collider.DrawCircle(_hdc);
	if (collider.Collision(_enemyCollider))
	{
		color = RGB(255, 0, 0);
	}
	else
	{
		color = RGB(0, 0, 0);
	}
	this->DrawTriangle(_hdc, color);
}

inline void Player::PlayerTranslate()
{
	Vector3D tmpcenter = GetCenter(GetTrianlge());
	tmpcenter = tmpcenter - NextPos;
	//�̵��� ��ġ���� �̵��ߴ��� Ȯ���ϰ� �ƴϸ� �̵�
	if (tmpcenter.GetLength() >= 10)
	{
		Translate(dpos);
	}
}
