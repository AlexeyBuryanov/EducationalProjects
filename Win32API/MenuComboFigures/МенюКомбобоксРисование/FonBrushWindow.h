#pragma once
#include "Includes.h"

#define FONBRUSH_WIDTH   375   /* ширина окна */
#define FONBRUSH_HEIGHT  180   /* высота окна */
#define FONBRUSH_BACKGROUND  RGB(0xFF, 0xFF, 0xFF)

#define IDC_COMBO_         1000
#define IDC_OKAY           1500
#define IDC_CANCELE        2000

LRESULT CALLBACK FonBrush_WndProc(HWND, UINT, WPARAM, LPARAM);

BOOL   FonBrush_OnCreate(HWND hWnd, LPCREATESTRUCT lpCreateStruct);
void   FonBrush_OnSize(HWND hWnd, UINT state, INT cx, INT cy);
void   FonBrush_OnGetMinMaxInfo(HWND hwnd, LPMINMAXINFO lpMinMaxInfo);
void   FonBrush_OnClose(HWND hWnd);
void   FonBrush_OnDestroy(HWND hWnd);
void   FonBrush_OnCommand(HWND hWnd, INT id, HWND hWndCtl, UINT codeNotify);
HBRUSH FonBrush_OnCtlColorStatic(HWND, HDC hDC, HWND, INT);