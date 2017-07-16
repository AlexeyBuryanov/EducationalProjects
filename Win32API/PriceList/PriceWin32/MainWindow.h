#pragma once
#include "Includes.h"
#include "Price.h"

// Ширина и высота окна
#define MAIN_WIDTH   645
#define MAIN_HEIGHT  520

#define IDC_MAIN_NEW        1000  /* Новый товар     */
#define IDC_MAIN_DEL        1001  /* Удалить товар   */
#define IDC_MAIN_QUIT	    1100  /* Выход           */

#define IDC_MAIN_SETSORT    1200  /* Сортировка      */
#define IDC_MAIN_SETVIEW    1300  /* Вид отображения */

#define IDC_MAIN_LISTGDS    2000  /* Список товаров  */
#define IDC_MAIN_STBAR      2001  /* Строка состояния */

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

BOOL   OnCreate(HWND hWnd, LPCREATESTRUCT lpCreateStruct);
void   OnCommand(HWND hWnd, INT id, HWND hWndCtl, UINT codeNotify);
void   OnSize(HWND hWnd, UINT state, INT cx, INT cy);
void   OnGetMinMaxInfo(HWND hWnd, LPMINMAXINFO lpMinMaxInfo);
void   OnPaint(HWND hWnd);
void   OnClose(HWND hWnd);
void   OnDestroy(HWND hWnd);
HBRUSH OnCtlColorStatic(HWND, HDC hDC, HWND, INT);
void OnMenuSelect(HWND hwnd, HMENU hmenu, int item, HMENU hmenuPopup, UINT flags);

void LoadFile();
void WriteFile();
void MakeOutStr(TCHAR *szBuf, Price price);
void ListToListbox();