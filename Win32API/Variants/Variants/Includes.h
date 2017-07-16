#pragma once

#define _CRT_SECURE_NO_WARNINGS
#define BACKGROUND RGB(0xDC, 0xDC, 0xDC)
#define MAX_LOADSTRING 100

#include <Windows.h>
#include <windowsx.h>
#include <tchar.h>
#include <cmath>

// ��� ������ Coord ������������ � �������� 14
// ��� ���������� �����
struct Coord {
	double x;
	double y;
};

// ��� ������ ��� �������� ���������� � ���������� ���� �����
// � ���������� ���� ������ ����������� ������� �������� 14
struct ParamV14 {
	Coord Point1;   // ���������� ����� 1
	Coord Point2;   // ���������� ����� 2
	bool  bLength;  // ���� ������� ����� �������
	bool  bKoef;    // ���� ������� �������� ������������
};