#pragma once
#include "Includes.h"

// ”правл€ющие кнопки - кнопки команд
#define IDC_QUIT		10100
#define IDC_PLUS        10110
#define IDC_MINUS       10120
#define IDC_MULTIPLY    10130
#define IDC_DIVIDE	    10140
#define IDC_RESET       10150

// –едакторы - строки ввода
#define IDC_EDIT1       10500
#define IDC_EDIT2       10510
#define IDC_EDITRESULT  10520

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
BOOL OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct);
void OnSize(HWND hwnd, UINT state, int cx, int cy);
void OnClose(HWND hwnd);
void OnDestroy(HWND hwnd);
//void OnGetMinMaxInfo(HWND hwnd, LPMINMAXINFO lpMinMaxInfo);
void OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
HBRUSH OnCtlColorStatic(HWND, HDC hdc, HWND, int);

void Reset();
void Plus();
void Minus();
void Multiply();
void Divide();