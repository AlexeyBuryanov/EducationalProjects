#pragma once
#include "Includes.h"

#define IDC_QUIT		  103	// �����
#define IDC_REPORT		  900	// �����
#define IDC_EDTINIT		  950	// ��������

// ������, ���-����� �� ������ "������"
#define IDC_CHBOXC        1000  // ������ C++
#define IDC_CHBOXWINAPI   1001  // ������ WinAPI
#define IDC_CHBOXHARD     1002  // ������ Hardware
#define IDC_CHBOXANDROID  1003  // ������ Android

// �������������, ����������� �� ������ "���������"
#define IDC_RDBTNENG      1010  // �������
#define IDC_RDBTNDEV      1011  // �����������
#define IDC_RDBTNLEAD     1012  // ������� �����������

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
