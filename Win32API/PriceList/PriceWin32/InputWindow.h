#pragma once
#include "Includes.h"

#define INPUT_WIDTH   380   /* ширина окна */
#define INPUT_HEIGHT  360   /* высота окна */
#define INPUT_BACKGROUND  RGB(0xFF, 0xFF, 0xFF)

#define IDC_INPUT_CLOSE			10100
#define IDC_INPUT_SAVE			10101

#define IDC_INPUT_COMBO_SHOP    10200
#define IDC_INPUT_EDGOODS		10500
#define IDC_INPUT_EDCOST		10501

LRESULT CALLBACK Input_WndProc(HWND, UINT, WPARAM, LPARAM);

BOOL   Input_OnCreate(HWND hWnd, LPCREATESTRUCT lpCreateStruct);
void   Input_OnCommand(HWND hWnd, INT id, HWND hWndCtl, UINT codeNotify);
void   Input_OnSize(HWND hWnd, UINT state, INT cx, INT cy);
void   Input_OnGetMinMaxInfo(HWND hwnd, LPMINMAXINFO lpMinMaxInfo);
void   Input_OnClose(HWND hWnd);
void   Input_OnDestroy(HWND hWnd);
HBRUSH Input_OnCtlColorStatic(HWND, HDC hDC, HWND, INT);

void LoadShopNames();

void SetInput();