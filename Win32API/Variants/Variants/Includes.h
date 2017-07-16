#pragma once

#define _CRT_SECURE_NO_WARNINGS
#define BACKGROUND RGB(0xDC, 0xDC, 0xDC)
#define MAX_LOADSTRING 100

#include <Windows.h>
#include <windowsx.h>
#include <tchar.h>
#include <cmath>

// Тип данных Coord используется в варианте 14
// это координаты точки
struct Coord {
	double x;
	double y;
};

// Тип данных для передачи параметров в диалоговое окно ввода
// и диалоговое окно вывода результатов решения варианта 14
struct ParamV14 {
	Coord Point1;   // координаты точки 1
	Coord Point2;   // координаты точки 2
	bool  bLength;  // флаг расчета длины отрезка
	bool  bKoef;    // флаг расчета углового коэффициента
};