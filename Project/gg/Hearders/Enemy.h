#pragma once
#include "Triangle.h"
#include "CircleCollider.h"
#define WayPointCount 4
#define PlayerFindLength 100

enum MoveState
{
	WayPoint,
	AllRandom
};

class Enemy : public Triangle
{
	MoveState movestate; //���� ��ġ, ����
	Vector3D OriginPos; //������ġ
	Vector3D NextPos; //���� ��ġ
	Vector3D dPos; //�̵����� 
	bool isFollow; //�÷��̾� ����ٴϴ���
	bool isOrigin; //���� ��ġ�� ���� ������
	
	CircleCollider collider;
	COLORREF color;

	//���� ��ġ
	Vector3D movementArr[WayPointCount]; //���� ��ġ �迭
	int moveIndex;

	RECT rt;

public:
	Enemy()
	{
		movestate = WayPoint;
		isFollow = false;
		isOrigin = false;
		CreateMovement();
		collider.CreateCircleCollider(this->GetTrianlge());
		color = RGB(0, 0, 0);
	}
	Enemy(MoveState _state, HWND& hWnd)
	{
		movestate = _state;
		GetClientRect(hWnd, &rt);
		isFollow = false;
		isOrigin = false;
		CreateMovement();
		collider.CreateCircleCollider(this->GetTrianlge());
		color = RGB(0, 0, 0);
	}

	Enemy(const Enemy& _enemy):Triangle(_enemy)
	{
		movestate = _enemy.movestate;
		OriginPos = _enemy.OriginPos;
		NextPos = _enemy.NextPos;
		dPos = _enemy.dPos;
		isFollow = _enemy.isFollow;
		isOrigin = _enemy.isOrigin;

		for (int i = 0; i < WayPointCount; i++)
		{
			movementArr[i] = _enemy.movementArr[i];
		}
		rt = _enemy.rt;

		this->collider = _enemy.collider;
		color = _enemy.color;
	}

	void SetState(MoveState _state, HWND& hWnd);

	void CreateMovement(); //������ ��ġ ����
	void CreateWaypoint(); //���� ��ġ ����
	void CreateAllrandom(); //���� ��ġ ����
	void SetNextWayPoint(); //���� ���� ��ġ
	void SetNextRandom(); //���� ���� ��ġ

	void Roming();
	void Watching(Vector3D _player); 
	void Following(Vector3D _player); 
	void Move(Vector3D _player);

	CircleCollider& GetCollider() { return collider; }
	void DrawEnemy(HDC _hdc);
	void SetColor(COLORREF _color) { color = _color; }
	COLORREF GetColor() { return color; }
};

inline void Enemy::SetState(MoveState _state, HWND& hWnd)
{
	movestate = _state;
	GetClientRect(hWnd, &rt);
	CreateMovement();
}

inline void Enemy::CreateMovement()
{
	switch (movestate)
	{
	case WayPoint:
		CreateWaypoint();
		break;
	case AllRandom:
		CreateAllrandom();
		break;
	}
}

inline void Enemy::CreateWaypoint()
{
	Vector3D temppos(100, 100, 1);
	movementArr[0] = temppos;
	temppos.SetX(temppos.GetX() + 1000);
	movementArr[1] = temppos;
	temppos.SetY(temppos.GetY() + 400);
	movementArr[2] = temppos;
	temppos.SetX(temppos.GetX() - 1000);
	movementArr[3] = temppos;

	moveIndex = 0;
	SetTrianlge(movementArr[moveIndex++]);
	NextPos = movementArr[moveIndex];
}

inline void Enemy::CreateAllrandom()
{
	int ranX = (rand() % rt.right - 300) + 300;
	int ranY = (rand() % rt.bottom - 300) + 300;
	Vector3D temppos(ranX, ranY, 1);

	SetTrianlge(temppos);

	ranX = (rand() % rt.right - 300) + 300;
	ranY = (rand() % rt.bottom - 300) + 300;
	temppos.SetXYZ(ranX, ranY, 1);
	NextPos = temppos;
}

inline void Enemy::SetNextRandom()
{
	int ranX = (rand() % rt.right - 300) + 300;
	int ranY = (rand() % rt.bottom - 300) + 300;
	Vector3D temppos(ranX, ranY, 1);

	NextPos = temppos;
}

inline void Enemy::SetNextWayPoint()
{
	if (moveIndex >= WayPointCount)
	{
		moveIndex = 0;
	}
	NextPos = movementArr[moveIndex++];

}

inline void Enemy::Roming()
{
	//�̵��� ������ ������ �ȵ����� ������
	if (dPos.GetLength() == 0)
	{
		dPos = GetDPos(GetCenter(), NextPos);
	}

	//�̵�
	Translate(dPos);

	//���� ��ġ�� ���� ������
	if (isOrigin)
	{
		Vector3D tmpcenter = GetCenter(GetTrianlge());
		tmpcenter = tmpcenter - OriginPos;

		//���� ��ġ�� ������ ���� ������ ���� ��ġ�� ��
		if (tmpcenter.GetLength() <= 10)
		{
			isOrigin = false;
			dPos = GetDPos(GetCenter(), NextPos);
		}
	}

	//������ġ�� �����ߴ���
	if (!isFollow && !isOrigin)
	{
		Vector3D tmpcenter = GetCenter(GetTrianlge());
		tmpcenter = tmpcenter - NextPos;

		//���������� ���� ��ġ �ٽ� ����
		if (tmpcenter.GetLength() <= 10)
		{
			switch (movestate)
			{
			case WayPoint:
				SetNextWayPoint();
				break;
			case AllRandom:
				SetNextRandom();
				break;
			}

			dPos = GetDPos(GetCenter(), NextPos);
		}
	}
}

//�÷��̾� Ȯ��
inline void Enemy::Watching(Vector3D _player)
{
	Vector3D tmpcenter = GetCenter();
	tmpcenter = _player - tmpcenter;

	//�÷��̾ ã��
	if (tmpcenter.GetLength() <= PlayerFindLength)
	{
		if (!isFollow)
		{
			OriginPos = GetCenter();
		}

		isFollow = true;
	}
	else
	{
		//�÷��̾ ����ٴϴ� ������ ���
		if (isFollow)
		{
			Vector3D tmpcenter = GetCenter(GetTrianlge());
			tmpcenter = tmpcenter - _player;

			//�����ڸ��� ���� ����
			if (tmpcenter.GetLength() > PlayerFindLength)
			{
				dPos = GetDPos(GetCenter(), OriginPos);
				isFollow = false;
				isOrigin = true;
			}
		}
	}

}

//�÷��̾� ����ٴϴ� �Ÿ� ����
inline void Enemy::Following(Vector3D _player)
{
	if (isFollow)
	{
		dPos = GetDPos(GetCenter(), _player);
	}
}

inline void Enemy::Move(Vector3D _player)
{
	Roming();
	Watching(_player);
	Following(_player);
}

inline void Enemy::DrawEnemy(HDC _hdc)
{
	collider.DrawCircle(_hdc);
	
	this->DrawTriangle(_hdc, color);

}

