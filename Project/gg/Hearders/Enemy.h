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
	MoveState movestate; //지정 위치, 랜덤
	Vector3D OriginPos; //원래위치
	Vector3D NextPos; //다음 위치
	Vector3D dPos; //이동단위 
	bool isFollow; //플레이어 따라다니는지
	bool isOrigin; //원래 위치로 가는 중인지
	
	CircleCollider collider;
	COLORREF color;

	//지정 위치
	Vector3D movementArr[WayPointCount]; //지정 위치 배열
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

	void CreateMovement(); //움직일 위치 생성
	void CreateWaypoint(); //지정 위치 생성
	void CreateAllrandom(); //랜덤 위치 생성
	void SetNextWayPoint(); //다음 지정 위치
	void SetNextRandom(); //다음 랜덤 위치

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
	//이동할 단위가 설정아 안됐으면 설정함
	if (dPos.GetLength() == 0)
	{
		dPos = GetDPos(GetCenter(), NextPos);
	}

	//이동
	Translate(dPos);

	//원래 위치로 가는 중인지
	if (isOrigin)
	{
		Vector3D tmpcenter = GetCenter(GetTrianlge());
		tmpcenter = tmpcenter - OriginPos;

		//원래 위치로 갔으면 원래 가려던 다음 위치로 감
		if (tmpcenter.GetLength() <= 10)
		{
			isOrigin = false;
			dPos = GetDPos(GetCenter(), NextPos);
		}
	}

	//다음위치에 도착했는지
	if (!isFollow && !isOrigin)
	{
		Vector3D tmpcenter = GetCenter(GetTrianlge());
		tmpcenter = tmpcenter - NextPos;

		//도착했으면 다음 위치 다시 생성
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

//플레이어 확인
inline void Enemy::Watching(Vector3D _player)
{
	Vector3D tmpcenter = GetCenter();
	tmpcenter = _player - tmpcenter;

	//플레이어를 찾음
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
		//플레이어를 따라다니다 놓쳤을 경우
		if (isFollow)
		{
			Vector3D tmpcenter = GetCenter(GetTrianlge());
			tmpcenter = tmpcenter - _player;

			//원래자리로 가게 설정
			if (tmpcenter.GetLength() > PlayerFindLength)
			{
				dPos = GetDPos(GetCenter(), OriginPos);
				isFollow = false;
				isOrigin = true;
			}
		}
	}

}

//플레이어 따라다니는 거리 설정
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

