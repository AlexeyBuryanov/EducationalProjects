#pragma once
#include "Includes.h"

#define IDC_LISTBOX1       1000 // список 1
#define IDC_LISTBOX2       1010 // список 2
#define IDC_EDTTEXT        1100 // поле для ввода

#define IDC_BTNDELLEFT     2010 // удалить слева
#define IDC_BTNDELRIGHT    2020 // удалить справа

#define IDC_BTNCLR		   2040 // очистить всё
#define IDC_BTNCLRLEFT	   2050 // очистить слева
#define IDC_BTNCLRRIGHT	   2060 // очистить справа

#define IDC_BTNINPLEFT     2100 // добавить влево
#define IDC_BTNINPRIGHT    2200 // добавить вправо

#define IDC_BTNPUSHRIGHT   2500 // переместить с левого списка в правый
#define IDC_BTNPUSHLEFT    2600 // переместить с правого списка в левый

#define IDC_QUIT	        100

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
BOOL OnCreate(HWND hWnd, LPCREATESTRUCT lpCreateStruct);
void OnSize(HWND hWnd, UINT state, INT cx, INT cy);
void OnLButtonDown(HWND hWnd, BOOL fDoubleClick, INT x, INT y, UINT keyFlags);
void OnRButtonDown(HWND hWnd, BOOL fDoubleClick, INT x, INT y, UINT keyFlags);
void OnPaint(HWND hWnd);
void OnClose(HWND hWnd);
void OnDestroy(HWND hWnd);
void OnCommand(HWND hWnd, INT id, HWND hWndCtl, UINT codeNotify);
HBRUSH OnCtlColorStatic(HWND, HDC hdc, HWND, INT);
