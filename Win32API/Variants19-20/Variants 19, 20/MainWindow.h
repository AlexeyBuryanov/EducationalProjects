#pragma once
#include "Includes.h"

// Ўирина и высота главного окна
#define MAIN_WIDTH   ((int)0x80000000)
#define MAIN_HEIGHT  ((int)0x80000000)

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
BOOL    OnCreate(HWND, LPCREATESTRUCT);
void    OnCommand(HWND, int, HWND, UINT);
void    OnSize(HWND, UINT, int, int);
void    OnGetMinMaxInfo(HWND, LPMINMAXINFO);
void    OnPaint(HWND);
void    OnClose(HWND);
void    OnDestroy(HWND);
HBRUSH  OnCtlColorStatic(HWND, HDC, HWND, int);
void    OnMenuSelect(HWND, HMENU, int, HMENU, UINT);