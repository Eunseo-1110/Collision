#include <windows.h>	// 윈도우 헤더파일
#include <list>
using namespace std;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);	//CALLBACK 매크로
HINSTANCE g_hInst;					//인스턴스 핸들
LPCTSTR lpszClass = TEXT("전은서");	 //제목 표시줄에 표시되는 내용

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpszCmdParam, int nCmdShow)   //main 함수
{
	HWND hWnd;		//윈도우 핸들 선언
	MSG Message;		 //메세지 구조체 변수 선언
	WNDCLASS WndClass;	 //Windows Class 구조체 변수 선언
	g_hInst = hInstance;    //hInstance값을 외부에서도 사용할 수 있도록 전역변수에 값을 저장

	WndClass.cbClsExtra = 0;	//예약 영역. 지금은 사용X
	WndClass.cbWndExtra = 0;	//예약 영역
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);// 윈도우의 배경 색상을 지정
	//WndClass.hbrBackground = (HBRUSH)(COLOR_BTNFACE + 1);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);    //윈도우의 커서(마우스포인터) 모양을 지정
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);  //윈도우의 커서 아이콘 모양 지정
	WndClass.hInstance = hInstance;		 //윈도우 클래스를 등록하는 프로그램 번호
	WndClass.lpfnWndProc = WndProc;		//윈도우 메세지 처리 함수 지정
	WndClass.lpszClassName = lpszClass;		//윈도우 클래스의 이름 지정
	WndClass.lpszMenuName = NULL;		//이 프로그램의 메뉴 지정
	WndClass.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;	//윈도우의 스타일을 정의

	RegisterClass(&WndClass);			//WNDCLASS 구조체의 번지를 전달


	//윈도우를 생성하고 창에 표시하는 기능을 수행
	hWnd = CreateWindow(lpszClass, lpszClass,
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT
		/* 100,100,500,500*/, NULL, (HMENU)NULL, hInstance, NULL);

	ShowWindow(hWnd, nCmdShow);

	//메세지 루프를 실행
	while (GetMessage(&Message, NULL, 0, 0)) {	//Queue에 있는 메세지를 읽어들인다
		TranslateMessage(&Message);   //키보드 입력 메세지를 가공하여 프로그램에서 쉽게 사용할 수 있도록
		DispatchMessage(&Message);   //메세지를 윈도우의 메세지 처리 함수 WndProc로 전달
	}
	return (int)Message.wParam;				//탈출 코드. 프로그램 종료
}

#include "Hearders/MyCoordinateS.h"
#include "Hearders/Triangle.h"
#include "Hearders/Enemy.h"
#include "Hearders/Player.h"
#include <cstdlib>
#include <time.h>

#define TIMERFIRST 1
#define TIMERSECOND 2
#define EnemyCount 3

HBITMAP MemBit;


void Ready(HWND hWnd, list<Point> _x, list<Point> _y, 
	Player _player, Enemy _enemy[EnemyCount])
{
	HBITMAP hOldBmp;
	HDC hdc, MemDC;
	hdc = GetDC(hWnd);
	RECT rt;
	GetClientRect(hWnd, &rt);

	if (MemBit)
	{
		DeleteObject(MemBit);
	}
	MemBit = CreateCompatibleBitmap(hdc, rt.right, rt.bottom);
	MemDC = CreateCompatibleDC(hdc);
	hOldBmp = (HBITMAP)SelectObject(MemDC, MemBit);

	PatBlt(MemDC, 0, 0, rt.right, rt.bottom, WHITENESS);
	SetPix(MemDC, _x);
	SetPix(MemDC, _y);

	//콜라이더를 생성
	_player.GetCollider().CreateCircleCollider(_player.GetTrianlge());
	for (int i = 0; i < EnemyCount; i++)
	{
		_enemy[i].GetCollider().CreateCircleCollider(_enemy[i].GetTrianlge());
	}

	//충돌 시 플레이어의 색을 변경한다.
	bool isColl = false;
	for (int i = 0; i < EnemyCount; i++)
	{
		if (_player.GetCollider().Collision(_enemy[i].GetCollider()))
		{
			isColl = true;
			break;
		}
	}
	if (isColl)
	{
		_player.SetColor(RGB(255, 0, 0));
	}
	else
	{
		_player.SetColor(RGB(0, 0, 0));
	}

	//삼각형을 그린다
	for (int i = 0; i < EnemyCount; i++)
	{
		//콜라이더와 삼각형을 그림
		_enemy[i].DrawEnemy(MemDC);
	}
	_player.DrawTriangle(MemDC, _player.GetColor());
	
	DeleteDC(MemDC);
	ReleaseDC(hWnd, hdc);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
#pragma region 변수 선언
	HDC hdc;
	PAINTSTRUCT ps;

	static RECT rt;

	static list<Point> x;
	static	list<Point> y;

	//플레이어와 적 
	static Player player;
	static Enemy enemy[EnemyCount];
#pragma endregion

	switch (iMessage) {
	case WM_CREATE:
	{
		srand(time(NULL));
		GetClientRect(hWnd, &rt);
		
		//적의 로밍방식을 랜덤으로 하고 색을 파란색으로 바꿔줌
		for (int i = 0; i < EnemyCount; i++)
		{
			enemy[i].SetState(AllRandom, hWnd);
			enemy[i].SetColor(RGB(0, 0, 255));
		}
		SetTimer(hWnd, TIMERFIRST, 10, NULL);

		SetPoint(-600, 600, &x, &y);
		ConvertingWorld(&x, rt);
		ConvertingWorld(&y, rt);
		
		Point tmp = Point(0, 0);
		ConvertingWorld(&tmp, rt);

#pragma region 플레이어 삼각형 생성
		Vector3D temppos[3];
		temppos[0] = Vector3D(tmp.x, tmp.y - 40, 0);
		temppos[1] = Vector3D(tmp.x - 40, tmp.y + 30,0);
		temppos[2] = Vector3D(tmp.x + 40, tmp.y + 30,0);
		player.SetTrianlge(temppos);
#pragma endregion
		Ready(hWnd, x, y, player, enemy);
		break;
	}
	// 마우스로 클릭한 곳으로 플레이어 이동
	case WM_LBUTTONDOWN:
	{
		Vector3D tmpvec;
		tmpvec.SetX(LOWORD(lParam));
		tmpvec.SetY(HIWORD(lParam));
		player.SetPos(tmpvec);
		break;
	}
	case WM_PAINT:
	{
		hdc = BeginPaint(hWnd, &ps);
		
		DrawBitmap(hdc, 0, 0, MemBit);

		EndPaint(hWnd, &ps);
		return 0;
	}
	case WM_TIMER:
		switch (wParam)
		{
		case TIMERFIRST:
			//적 이동
			for (int i = 0; i < EnemyCount; i++)
			{
				enemy[i].Move(player.GetCenter());
			}
			player.PlayerTranslate();

			InvalidateRect(hWnd, NULL, FALSE);
			Ready(hWnd, x, y, player, enemy);
			break;
		}
		break;
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		return 0;
	}
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}

