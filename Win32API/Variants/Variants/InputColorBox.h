#pragma once
#include "Includes.h"
#include "MainWindow.h"  /* для COLOR_CONTROL */

BOOL CALLBACK InputColor(HWND, UINT, WPARAM, LPARAM);
BOOL InputColorOnInitDialog(HWND, HWND, LPARAM);
void InputColorOnCommand(HWND, int, HWND, UINT);

void SetInputColorParam(COLOR_CONTROL *Params);
void GetInputColorParam(COLOR_CONTROL *Params);