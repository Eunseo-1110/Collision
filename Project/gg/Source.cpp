#include <windows.h>	// ������ �������
#include <list>
using namespace std;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);	//CALLBACK ��ũ��
HINSTANCE g_hInst;					//�ν��Ͻ� �ڵ�
LPCTSTR lpszClass = TEXT("������");	 //���� ǥ���ٿ� ǥ�õǴ� ����

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpszCmdParam, int nCmdShow)   //main �Լ�
{
	HWND hWnd;		//������ �ڵ� ����
	MSG Message;		 //�޼��� ����ü ���� ����
	WNDCLASS WndClass;	 //Windows Class ����ü ���� ����
	g_hInst = hInstance;    //hInstance���� �ܺο����� ����� �� �ֵ��� ���������� ���� ����

	WndClass.cbClsExtra = 0;	//���� ����. ������ ���X
	WndClass.cbWndExtra = 0;	//���� ����
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);// �������� ��� ������ ����
	//WndClass.hbrBackground = (HBRUSH)(COLOR_BTNFACE + 1);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);    //�������� Ŀ��(���콺������) ����� ����
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);  //�������� Ŀ�� ������ ��� ����
	WndClass.hInstance = hInstance;		 //������ Ŭ������ ����ϴ� ���α׷� ��ȣ
	WndClass.lpfnWndProc = WndProc;		//������ �޼��� ó�� �Լ� ����
	WndClass.lpszClassName = lpszClass;		//������ Ŭ������ �̸� ����
	WndClass.lpszMenuName = NULL;		//�� ���α׷��� �޴� ����
	WndClass.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;	//�������� ��Ÿ���� ����

	RegisterClass(&WndClass);			//WNDCLASS ����ü�� ������ ����


	//�����츦 �����ϰ� â�� ǥ���ϴ� ����� ����
	hWnd = CreateWindow(lpszClass, lpszClass,
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT
		/* 100,100,500,500*/, NULL, (HMENU)NULL, hInstance, NULL);

	ShowWindow(hWnd, nCmdShow);

	//�޼��� ������ ����
	while (GetMessage(&Message, NULL, 0, 0)) {	//Queue�� �ִ� �޼����� �о���δ�
		TranslateMessage(&Message);   //Ű���� �Է� �޼����� �����Ͽ� ���α׷����� ���� ����� �� �ֵ���
		DispatchMessage(&Message);   //�޼����� �������� �޼��� ó�� �Լ� WndProc�� ����
	}
	return (int)Message.wParam;				//Ż�� �ڵ�. ���α׷� ����
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

	//�ݶ��̴��� ����
	_player.GetCollider().CreateCircleCollider(_player.GetTrianlge());
	for (int i = 0; i < EnemyCount; i++)
	{
		_enemy[i].GetCollider().CreateCircleCollider(_enemy[i].GetTrianlge());
	}

	//�浹 �� �÷��̾��� ���� �����Ѵ�.
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

	//�ﰢ���� �׸���
	for (int i = 0; i < EnemyCount; i++)
	{
		//�ݶ��̴��� �ﰢ���� �׸�
		_enemy[i].DrawEnemy(MemDC);
	}
	_player.DrawTriangle(MemDC, _player.GetColor());
	
	DeleteDC(MemDC);
	ReleaseDC(hWnd, hdc);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
#pragma region ���� ����
	HDC hdc;
	PAINTSTRUCT ps;

	static RECT rt;

	static list<Point> x;
	static	list<Point> y;

	//�÷��̾�� �� 
	static Player player;
	static Enemy enemy[EnemyCount];
#pragma endregion

	switch (iMessage) {
	case WM_CREATE:
	{
		srand(time(NULL));
		GetClientRect(hWnd, &rt);
		
		//���� �ιֹ���� �������� �ϰ� ���� �Ķ������� �ٲ���
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

#pragma region �÷��̾� �ﰢ�� ����
		Vector3D temppos[3];
		temppos[0] = Vector3D(tmp.x, tmp.y - 40, 0);
		temppos[1] = Vector3D(tmp.x - 40, tmp.y + 30,0);
		temppos[2] = Vector3D(tmp.x + 40, tmp.y + 30,0);
		player.SetTrianlge(temppos);
#pragma endregion
		Ready(hWnd, x, y, player, enemy);
		break;
	}
	// ���콺�� Ŭ���� ������ �÷��̾� �̵�
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
			//�� �̵�
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

