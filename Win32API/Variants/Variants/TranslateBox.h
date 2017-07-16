#pragma once

#include "Includes.h"

BOOL CALLBACK Translate(HWND, UINT, WPARAM, LPARAM);
BOOL TranslateOnInitDialog(HWND, HWND, LPARAM);
void TranslateOnCommand(HWND, int, HWND, UINT);

enum NUMBER_SYSTEM {
	OCTAL, DEC, HEXADECIMAL
};