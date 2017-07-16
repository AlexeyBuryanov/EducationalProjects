#pragma once
#include "Includes.h"

#define INPUT_WIDTH   375   /* ширина окна */
#define INPUT_HEIGHT  240   /* высота окна */
#define INPUT_BACKGROUND  RGB(0xFF, 0xFF, 0xFF)

#define IDC_INPUT_CLOSE    10100
#define IDC_INPUT_WRITE    10101

#define IDC_INPUT_EDFAMIO  10500
#define IDC_INPUT_EDWEIGHT 10501

LRESULT CALLBACK Input_WndProc(HWND, UINT, WPARAM, LPARAM);

BOOL Input_OnCreate(HWND hWnd, LPCREATESTRUCT lpCreateStruct);
void Input_OnSize(HWND hWnd, UINT state, INT cx, INT cy);
void Input_OnGetMinMaxInfo(HWND hwnd, LPMINMAXINFO lpMinMaxInfo);
void Input_OnClose(HWND hWnd);
void Input_OnDestroy(HWND hWnd);
void Input_OnCommand(HWND hWnd, INT id, HWND hWndCtl, UINT codeNotify);
HBRUSH Input_OnCtlColorStatic(HWND, HDC hDC, HWND, INT);

void SetInput();