#pragma once
#include "Includes.h"

BOOL CALLBACK CurConvert(HWND, UINT, WPARAM, LPARAM);
BOOL CurConvertOnInitDialog(HWND, HWND, LPARAM);
void CurConvertOnCommand(HWND, int, HWND, UINT);

void Convert();

enum COURSE {
	NORM, PREFERENTIAL
};