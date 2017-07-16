#pragma once
#include "Includes.h"

#define PENSETTINGS_WIDTH   375   /* ширина окна */
#define PENSETTINGS_HEIGHT  190   /* высота окна */
#define PENSETTINGS_BACKGROUND  RGB(0xFF, 0xFF, 0xFF)

#define IDC_PENWIDTH        1000
#define IDC_OK              1100
#define IDC_CANCEL          1200
#define IDC_COMBO           2000

LRESULT CALLBACK PenSettings_WndProc(HWND, UINT, WPARAM, LPARAM);

BOOL   PenSettings_OnCreate(HWND hWnd, LPCREATESTRUCT lpCreateStruct);
void   PenSettings_OnSize(HWND hWnd, UINT state, INT cx, INT cy);
void   PenSettings_OnGetMinMaxInfo(HWND hwnd, LPMINMAXINFO lpMinMaxInfo);
void   PenSettings_OnClose(HWND hWnd);
void   PenSettings_OnDestroy(HWND hWnd);
void   PenSettings_OnCommand(HWND hWnd, INT id, HWND hWndCtl, UINT codeNotify);
HBRUSH PenSettings_OnCtlColorStatic(HWND, HDC hDC, HWND, INT);