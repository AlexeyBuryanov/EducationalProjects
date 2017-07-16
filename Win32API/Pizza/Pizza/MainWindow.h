#pragma once
#include "Includes.h"

#define IDC_QUIT		  103	// �����
#define IDC_ORDER		  900	// ��������
#define IDC_EDTINIT		  950	// ��������
#define IDC_EDTTPHONE	  960	// �����

// ������, ���-����� �� ������ "�����"
#define IDC_CHBOXCHEESE   1000  // ���
#define IDC_CHBOXOLIVE    1001  // ������
#define IDC_CHBOXFUNGI    1002  // �����
#define IDC_CHBOXSAUSAGE  1003  // �������

// �������������, ����������� �� ������ "������"
#define IDC_RDBTN0        1010  // 0%
#define IDC_RDBTN5        1011  // 5%
#define IDC_RDBTN15       1012  // 15%

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
BOOL OnCreate(HWND hWnd, LPCREATESTRUCT lpCreateStruct);
void OnSize(HWND hWnd, UINT state, INT cx, INT cy);
void OnLButtonDown(HWND hWnd, BOOL fDoubleClick, INT x, INT y, UINT keyFlags);
void OnRButtonDown(HWND hWnd, BOOL fDoubleClick, INT x, INT y, UINT keyFlags);
void OnPaint(HWND hWnd);
void OnClose(HWND hWnd);
void OnDestroy(HWND hWnd);
//void OnGetMinMaxInfo(hWnd hWnd, LPMINMAXINFO lpMinMaxInfo);
void OnCommand(HWND hWnd, INT id, HWND hWndCtl, UINT codeNotify);
HBRUSH OnCtlColorStatic(HWND, HDC hdc, HWND, INT);
