#pragma once
#include "Includes.h"

// Ўирина и высота окна
#define MAIN_WIDTH   640
#define MAIN_HEIGHT  480

#define IDC_QUIT			100
#define IDC_CIRCLE			1001
#define IDC_TRIANGLE		1002
#define IDC_RECTANGLE		1003
#define IDC_TRAPEZE			1004

#define IDC_SETTINGSPEN		2000
#define IDC_COLORBRSH		2001
#define IDC_COLORFON		2002

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

BOOL   OnCreate(HWND hWnd, LPCREATESTRUCT lpCreateStruct);
void   OnCommand(HWND hWnd, INT id, HWND hWndCtl, UINT codeNotify);
void   OnPaint(HWND hWnd);
void   OnSize(HWND hWnd, UINT state, INT cx, INT cy);
void   OnGetMinMaxInfo(HWND hWnd, LPMINMAXINFO lpMinMaxInfo);
void   OnClose(HWND hWnd);
void   OnDestroy(HWND hWnd);