#pragma once

#define _CRT_SECURE_NO_WARNINGS
#define BACKGROUND RGB(0xDC, 0xDC, 0xDC)

#include <Windows.h>
#include <windowsx.h>
#include <tchar.h>

// Количество цветов в комбо-боксах
const UINT N_COLORS = 7;

enum Figures {
	FIG_NONE, FIG_CIRCLE, FIG_TRIANGLE, FIG_RECT, FIG_TRAPEZE 
};