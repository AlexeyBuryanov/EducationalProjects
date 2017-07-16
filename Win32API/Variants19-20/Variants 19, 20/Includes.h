#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define BACKGROUND RGB(0xDC, 0xDC, 0xDC)
#define MAX_LOADSTRING 100

#include <Windows.h>
#include <windowsx.h>
#include <tchar.h>
#include <CommCtrl.h>
#pragma comment (lib, "comctl32.lib")


// ���� �������:
enum COLOR {
	RED, GREEN, BLUE, NO_COLOR
};

// ��� ������ �������� 19 ��� �������� ���������� � ���������� ���� ����� � ������� ����:
struct ParamV19 {
	COORD point;   // ����� ��� ����������������
	COORD point1;  // ���������� �������
	COLOR color;   // ����
	BOOL  bDraw;   // ���� ��������� �������
};

// ���������� ��� ���������� ��������:
enum MODE {
	INCREASE, DECREASE
};

// ��� ������ �������� 20 ��� �������� ���������� � ���������� ���� ����� � ������� ����:
struct ParamV20 {
	MODE mode;    // ����� �������������� ��������
	SIZE size;	  // ������
	RECT rect;    // ������������� �� �������� 20
	RECT view;    // ������������� ��� ������ �� ������� 
};