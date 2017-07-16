#pragma once
#include "Includes.h"

BOOL CALLBACK InputLineSeg(HWND, UINT, WPARAM, LPARAM);
BOOL InputLineSegOnInitDialog(HWND, HWND, LPARAM);
void InputLineSegOnCommand(HWND, int, HWND, UINT);