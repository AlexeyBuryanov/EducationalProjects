#pragma once
#include "Includes.h"

BOOL CALLBACK ShowResult(HWND, UINT, WPARAM, LPARAM);
BOOL ShowResultOnInitDialog(HWND, HWND, LPARAM);
void ShowResultOnCommand(HWND, int, HWND, UINT);