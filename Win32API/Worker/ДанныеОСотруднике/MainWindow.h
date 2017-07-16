#pragma once
#include "Includes.h"

#define IDC_QUIT		  103	// выход
#define IDC_REPORT		  900	// отчёт
#define IDC_EDTINIT		  950	// инициалы

// Флажки, чек-боксы из группы "Знания"
#define IDC_CHBOXC        1000  // знание C++
#define IDC_CHBOXWINAPI   1001  // знание WinAPI
#define IDC_CHBOXHARD     1002  // знание Hardware
#define IDC_CHBOXANDROID  1003  // знание Android

// Переключатели, радиокнопки из группы "Должность"
#define IDC_RDBTNENG      1010  // Инженер
#define IDC_RDBTNDEV      1011  // Программист
#define IDC_RDBTNLEAD     1012  // Старший программист

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
