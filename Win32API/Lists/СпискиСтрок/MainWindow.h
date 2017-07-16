#pragma once
#include "Includes.h"

#define IDC_LISTBOX1       1000 // ������ 1
#define IDC_LISTBOX2       1010 // ������ 2
#define IDC_EDTTEXT        1100 // ���� ��� �����

#define IDC_BTNDELLEFT     2010 // ������� �����
#define IDC_BTNDELRIGHT    2020 // ������� ������

#define IDC_BTNCLR		   2040 // �������� ��
#define IDC_BTNCLRLEFT	   2050 // �������� �����
#define IDC_BTNCLRRIGHT	   2060 // �������� ������

#define IDC_BTNINPLEFT     2100 // �������� �����
#define IDC_BTNINPRIGHT    2200 // �������� ������

#define IDC_BTNPUSHRIGHT   2500 // ����������� � ������ ������ � ������
#define IDC_BTNPUSHLEFT    2600 // ����������� � ������� ������ � �����

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
