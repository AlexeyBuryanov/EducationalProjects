#pragma once
#include "WinMain.h"

#define EVENT_NONE  0   // нет щелчка ЛКМ или ПКМ
#define EVENT_LEFT  1   // щелчок ЛКМ
#define EVENT_RIGHT 2   // щелчок ПКМ

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
BOOL OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct);
void OnSize(HWND hwnd, UINT state, int cx, int cy);
void OnLButtonDown(HWND hwnd, BOOL fDoubleClick, int x, int y, UINT keyFlags);
void OnRButtonDown(HWND hwnd, BOOL fDoubleClick, int x, int y, UINT keyFlags);
void OnPaint(HWND hwnd);
void OnClose(HWND hwnd);
void OnDestroy(HWND hwnd);
void OnGetMinMaxInfo(HWND hwnd, LPMINMAXINFO lpMinMaxInfo);

void ProcFinish(HWND hwnd, RECT rect);