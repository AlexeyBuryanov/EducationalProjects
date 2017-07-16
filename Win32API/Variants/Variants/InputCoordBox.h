#pragma once
#include "Includes.h"

BOOL CALLBACK InputCoord(HWND, UINT, WPARAM, LPARAM);
BOOL InputCoordOnInitDialog(HWND, HWND, LPARAM);
void InputCoordOnCommand(HWND, int, HWND, UINT);