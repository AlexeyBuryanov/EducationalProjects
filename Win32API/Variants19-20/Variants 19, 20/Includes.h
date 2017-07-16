#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define BACKGROUND RGB(0xDC, 0xDC, 0xDC)
#define MAX_LOADSTRING 100

#include <Windows.h>
#include <windowsx.h>
#include <tchar.h>
#include <CommCtrl.h>
#pragma comment (lib, "comctl32.lib")


// Цвет отрезка:
enum COLOR {
	RED, GREEN, BLUE, NO_COLOR
};

// Тип данных Варианта 19 для передачи параметров в диалоговое окно ввода и главное окно:
struct ParamV19 {
	COORD point;   // Точка для позиционирования
	COORD point1;  // Координаты отрезка
	COLOR color;   // Цвет
	BOOL  bDraw;   // Флаг отрисовки отрезка
};

// Увеличение или уменьшение квадрата:
enum MODE {
	INCREASE, DECREASE
};

// Тип данных Варианта 20 для передачи параметров в диалоговое окно ввода и главное окно:
struct ParamV20 {
	MODE mode;    // Режим преобразования квадрата
	SIZE size;	  // Размер
	RECT rect;    // Прямоугольник по варианту 20
	RECT view;    // Прямоугольник для вывода по команде 
};