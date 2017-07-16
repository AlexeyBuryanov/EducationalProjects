#pragma once
#include "Includes.h"

#define FIELDSOUT_WIDTH   310   /* ширина окна */
#define FIELDSOUT_HEIGHT  310   /* высота окна */
#define FIELDSOUT_BACKGROUND  RGB(0xFF, 0xFF, 0xFF)

#define IDC_FIELDSOUT_CANCEL    10100
#define IDC_FIELDSOUT_OK        10101

#define IDC_FIELDSOUT_CHBOXNMSHOP  10500
#define IDC_FIELDSOUT_CHBOXNMGOODS 10501
#define IDC_FIELDSOUT_CHBOXCOST    10502

LRESULT CALLBACK FieldsOut_WndProc(HWND, UINT, WPARAM, LPARAM);

BOOL   FieldsOut_OnCreate(HWND hWnd, LPCREATESTRUCT lpCreateStruct);
void   FieldsOut_OnCommand(HWND hWnd, INT id, HWND hWndCtl, UINT codeNotify);
void   FieldsOut_OnSize(HWND hWnd, UINT state, INT cx, INT cy);
void   FieldsOut_OnGetMinMaxInfo(HWND hwnd, LPMINMAXINFO lpMinMaxInfo);
void   FieldsOut_OnClose(HWND hWnd);
void   FieldsOut_OnDestroy(HWND hWnd);
HBRUSH FieldsOut_OnCtlColorStatic(HWND, HDC hDC, HWND, INT);

void SetFieldsOut();