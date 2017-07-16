#pragma once
#include "Includes.h"

// ������ � ������ ����
#define MAIN_WIDTH   640
#define MAIN_HEIGHT  480

#define IDC_BTNNEW     1000  /* ������ "����� �������" */
#define IDC_BTNOUT     1001  /* ������ "��������"      */
#define IDC_QUIT	   1100  /* ������ "�����"         */

#define IDC_LISTPT     2000  /* ������ ��������� */

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

BOOL OnCreate(HWND hWnd, LPCREATESTRUCT lpCreateStruct);
void OnSize(HWND hWnd, UINT state, INT cx, INT cy);
void OnLButtonDown(HWND hWnd, BOOL fDoubleClick, INT x, INT y, UINT keyFlags);
void OnRButtonDown(HWND hWnd, BOOL fDoubleClick, INT x, INT y, UINT keyFlags);
void OnPaint(HWND hWnd);
void OnClose(HWND hWnd);
void OnDestroy(HWND hWnd);
void OnGetMinMaxInfo(HWND hWnd, LPMINMAXINFO lpMinMaxInfo);
void OnCommand(HWND hWnd, INT id, HWND hWndCtl, UINT codeNotify);

void LoadFile();
void WriteFile();