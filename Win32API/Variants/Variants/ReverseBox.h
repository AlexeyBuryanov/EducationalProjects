#pragma once
#include "Includes.h"

BOOL CALLBACK Reverse(HWND, UINT, WPARAM, LPARAM);
BOOL ReverseOnInitDialog(HWND, HWND, LPARAM);
void ReverseOnCommand(HWND, int, HWND, UINT);

TCHAR *RUpper(TCHAR *szStr);